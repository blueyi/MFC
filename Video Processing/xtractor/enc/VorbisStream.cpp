/*
 * VorbisStream.cpp - Copyright (C) 2000 Jay A. Key
 *
 * Implementation for the VorbisStream class, which is an interface
 * to the vorb_enc.dll Ogg Vorbis encoder.
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
#include "VorbisStream.h"
#include "utf8.h"


VorbisStream::VorbisStream():MP3Stream()
{
#ifdef _DEBUG
  dbprintf( "VorbisStream::VorbisStream" );
#endif

  _bitrate[0] = -1;
  _bitrate[1] = 128;
  _bitrate[2] = -1;

  lstrcpy( _ext, "ogg" );
  lstrcpy( _mode, "wb" );
  _hDLL = LoadLibrary( "vorb_enc.dll" );
  if ( !_hDLL )
    return;

  LoadEncoderFunctions();

}


int VorbisStream::Init( void )
{
  BE_CONFIG b;
  DWORD dwSamples, dwOutput;

#ifdef _DEBUG
  dbprintf( "VorbisStream::Init" );
#endif
  
  ZeroMemory( &b, sizeof(b) );
  b.dwConfig = BE_CONFIG_VORBIS;
  b.format.vorb.version = VORBENCSTRUCTVER;
  b.format.vorb.channels = 2;
  b.format.vorb.rate = 44100;
  b.format.vorb.szTitle = Utf8Encode( _szTitle );
  b.format.vorb.szArtist = Utf8Encode( _szArtist );
  b.format.vorb.szAlbum = Utf8Encode( _szAlbum );
  b.format.vorb.szDate = Utf8Encode( _szYear );
  b.format.vorb.minbitrate = _bitrate[0];
  b.format.vorb.nominalbitrate = _bitrate[1];
  b.format.vorb.maxbitrate = _bitrate[2];

  _beInitStream( &b, &dwSamples, &dwOutput, &_hEncStream );
  _dwSampleBytes = dwSamples / 2;
  _pInput = new BYTE[_dwSampleBytes];
  _pOutput = new BYTE[dwOutput];
  
  if ( b.format.vorb.szTitle )
    free( b.format.vorb.szTitle );
  if ( b.format.vorb.szArtist )
    free( b.format.vorb.szArtist );
  if ( b.format.vorb.szAlbum )
    free( b.format.vorb.szAlbum );
  if ( b.format.vorb.szDate )
    free( b.format.vorb.szDate );
  
  return 1;
}


char *VorbisStream::Utf8Encode( char * sz )
{
  char *szRetVal = NULL;
  if ( !sz )
    return NULL;
  dbprintf( "converting %s to unicode", sz );
  
  if ( !utf8_encode( sz, &szRetVal ) )
  {
    char * tmp = szRetVal;
    while ( *(++tmp) )
    {
      dbprintf( "utf8 char %d (%02x)", *tmp, *tmp );
    }
    
    return szRetVal;
  }
  
  return NULL;
}



int VorbisStream::SetOption( int opt, int iVal )
{
#ifdef _DEBUG
  dbprintf( "VorbisStream::SetOption( int, int )" );
#endif

  switch( opt )
    {
    case XT_OPT_ID3LEVEL:
      // Ensure that no ID3 tag can be written
      _iID3Level = 0;
      break;

    case XT_OPT_UPPERBITRATE:
      _bitrate[2] = (long)iVal;
      break;
    case XT_OPT_VBITRATE:
    case XT_OPT_NOMINALBITRATE:
      _bitrate[1] = (long)iVal;
      break;
    case XT_OPT_LOWERBITRATE:
      _bitrate[0] = (long)iVal;
      break;
    default:
      return this->MP3Stream::SetOption( opt, iVal );
    }
  return 1;
}


int VorbisStream::SetOption( int opt, char *pszData )
{
#ifdef _DEBUG
  dbprintf( "VorbisStream::SetOption( int, char * )" );
#endif
  switch( opt )
    {
    default:
      return this->MP3Stream::SetOption( opt, pszData );
    }

  return 1;
}




int encOggAvail( void )
{
  HMODULE hDLL;
  BEVERSION beVersion;

  hDLL = LoadLibrary( "vorb_enc.dll" );
  if ( !hDLL )
    return 0;

  beVersion = (BEVERSION)GetProcAddress( hDLL, "beVersion" );
  if ( !beVersion )
    {
      FreeLibrary( hDLL );
      return 0;
    }

  FreeLibrary( hDLL );
  return 1;
}
