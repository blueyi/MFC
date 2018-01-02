/*
 * xtenc.c - Copyright (C) 2000 Jay A. Key
 *
 * Generic encoder interface DLL for CD-DA X-Tractor.  Provides a 
 * common interface to MP3, Ogg Vorbis, WAV and raw data encoders/writers
 * allowing the easier addition of new encoders
 *
 **********************************************************************
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 */
#include <windows.h>
#include <stdio.h>
#include "encbase.h"
#include "RawStream.h"
#include "WavStream.h"
#include "MP3Stream.h"
#include "VorbisStream.h"
#include "BladeStream.h"
#include "LameStream.h"

BOOL bInit = FALSE;
BaseEncoderStream *aEncStreams[32];

#ifdef __cplusplus
extern "C" {
#endif

int fmtMP3Avail( void );
int fmtOggAvail( void );

BOOL WINAPI DllMain( HANDLE hModule, DWORD dwReason, LPVOID lpReserved )
{
  switch( dwReason )
    {
    case DLL_PROCESS_ATTACH:
      OutputDebugString( "DLL_PROCESS_ATTACH" );
      break;
    case DLL_PROCESS_DETACH:
      OutputDebugString( "DLL_PROCESS_DETACH" );
      break;
    case DLL_THREAD_ATTACH:
      OutputDebugString( "DLL_THREAD_ATTACH" );
      break;
    case DLL_THREAD_DETACH:
      OutputDebugString( "DLL_THREAD_ATTACH" );
      break;
    }
  return TRUE;
}


void InitEncoders( void )
{
  int i;
  for( i = 0; i < 32; i++ )
    aEncStreams[i] = NULL;
  bInit = TRUE;
}


int getUnusedSlot( void )
{
  int i;
  static int last = -1;

  if ( last == -1 && aEncStreams[0] == NULL )
    {
      last = 0;
      return 0;
    }

  for( i = 1; i <= 32; i++ )
    {
      int j = (i+last)%32;
      if ( aEncStreams[j] == NULL )
	{
	  last = j;
	  return j;
	}
    }

  return -1;
}

HXTENCODER xtGetEncoder( int which )
{
  int i;

  if ( !bInit )
    InitEncoders();

  i = getUnusedSlot();
  if ( i == -1 )
    return 0;

  switch( which )
    {
    case XT_ENC_RAW:
      aEncStreams[i] = new RawStream();
      break;

    case XT_ENC_WAV:
      aEncStreams[i] = new WavStream();
      break;

    case XT_ENC_VORBIS:
      aEncStreams[i] = new VorbisStream();
      break;

    case XT_ENC_LAME1:
      aEncStreams[i] = new BladeStream( "lame_enc.dll" );
      break;

    case XT_ENC_BLADE:
      aEncStreams[i] = new BladeStream( "bladeenc.dll" );
      break;

    case XT_ENC_LAME2:
      aEncStreams[i] = new LameStream();
      break;

    default:
      return 0;
    }

  return i+1;
}


int xtSetAsciiOption( HXTENCODER hEnc, int iOpt, char *pszVal )
{
  int i;

  i = hEnc - 1;

  if ( (i < 0) || (i >= 32) || (aEncStreams[i] == NULL) )
    return 0;

  return aEncStreams[i]->SetOption( iOpt, pszVal );
}


int xtSetIntOption( HXTENCODER hEnc, int iOpt, int iVal )
{
  int i;

  i = hEnc - 1;

  if ( (i < 0) || (i >= 32) || (aEncStreams[i] == NULL) )
    return 0;

  return aEncStreams[i]->SetOption( iOpt, iVal );
}


int xtOpenOutputFile( HXTENCODER hEnc )
{
  int i = hEnc - 1;

  if ( (i < 0) || (i >= 32) || (aEncStreams[i] == NULL) )
    return 0;

  return aEncStreams[i]->OpenOutputFile();
}


int xtCheckOutputFileExists( HXTENCODER hEnc )
{
  int i = hEnc - 1;

  if ( (i < 0) || (i >= 32) || (aEncStreams[i] == NULL) )
    return 0;

  return aEncStreams[i]->CheckOutputFileExists();
}


int xtEncode( HXTENCODER hEnc, unsigned char *buf, int len )
{
  int i = hEnc - 1;

  if ( (i < 0) || (i >= 32) || (aEncStreams[i] == NULL) )
    return 0;

  return aEncStreams[i]->Encode( buf, len );
}

int xtClose( HXTENCODER hEnc )
{
  int i = hEnc - 1;
  int retVal;

  if ( (i < 0) || (i >= 32) || (aEncStreams[i] == NULL) )
    return 0;

  retVal = aEncStreams[i]->Close();
  aEncStreams[i] = NULL;
  return retVal;
}


int xtFlush( HXTENCODER hEnc )
{
  int i = hEnc - 1;

  if ( (i < 0) || (i >= 32) || (aEncStreams[i] == NULL) )
    return 0;

  return aEncStreams[i]->Flush();
}


int xtInit( HXTENCODER hEnc )
{
  int i = hEnc - 1;

  if ( (i < 0) || (i >= 32) || (aEncStreams[i] == NULL) )
    return 0;

  return aEncStreams[i]->Init();
}


int xtFormatAvail( int fmt )
{
  switch( fmt )
    {
    case XT_FMT_RAW:
    case XT_FMT_WAV:
      return TRUE;
      
    case XT_FMT_MP3:
      return fmtMP3Avail();

    case XT_FMT_OGG:
      return fmtOggAvail();
    }

  return 0;
}

int xtEncoderAvail( int enc )
{
  switch( enc )
    {
    case XT_ENC_RAW:
    case XT_ENC_WAV:
      return 1;

    case XT_ENC_LAME1:
    case XT_ENC_LAME2:
      return encLameAvail( enc );

    case XT_ENC_BLADE:
      return encBladeAvail();

    case XT_ENC_VORBIS:
      return encOggAvail();
    }
  return 0;
}

char *xtGetExtension( HXTENCODER hEnc )
{
  static char szExt[128];
  int i = hEnc - 1;

  if ( (i < 0) || (i >= 32) || (aEncStreams[i] == NULL) )
    return 0;

  lstrcpy( szExt, aEncStreams[i]->FileExtension() );

  return szExt;
}


char *xtGetFilename( HXTENCODER hEnc )
{
  static char szFname[MAX_PATH+1];
  int i = hEnc - 1;

  if ( (i < 0) || (i >= 32) || (aEncStreams[i] == NULL) )
    return 0;

  wsprintf( szFname, "%s.%s", aEncStreams[i]->FileName(), aEncStreams[i]->FileExtension() );

  return szFname;
}


int xtGetOutputFileName( HXTENCODER hEnc, char *szBuf, int len )
{
  int i = hEnc - 1;

  if ( (i < 0) || (i >= 32) || (aEncStreams[i] == NULL) )
    return 0;

  return aEncStreams[i]->ComputeFileName( szBuf, len );
}


int fmtMP3Avail( void )
{
  if ( encLameAvail( XT_ENC_LAME1 ) || encLameAvail( XT_ENC_LAME2 ) ||
       encBladeAvail() )
    return 1;
  return 0;
}


int fmtOggAvail( void )
{
  if ( encOggAvail() )
    return 1;
  return 0;
}


#ifdef __cplusplus
}
#endif
