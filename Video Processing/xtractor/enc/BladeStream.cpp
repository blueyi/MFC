/*
 * BladeStream.cpp - Copyright (C) 2000 Jay A. Key
 *
 * Implementation of the BladeStream class.  Provides an interface to 
 * both BladeEnc.dll and to the older versions of lame_enc.dll.
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
#include <stdlib.h>
#include "BladeStream.h"

void dbprintf( char *, ... );

BladeStream::BladeStream( char *szDll ):MP3Stream()
{
#ifdef _DEBUG
  dbprintf( "BladeStream::BladeStream( %s )", szDll );
#endif

  lstrcpy( _ext, "MP3" );
  lstrcpy( _mode, "w+b" );
  _hDLL = LoadLibrary( szDll );

  if ( !_hDLL )
    return;

  LoadEncoderFunctions();
#if 0
  {
    BE_VERSION bv;
    _beVersion( &bv );
    dbprintf( "dllversion: %d.%d - %d.%d, rel: %d-%d-%d",
	      bv.byDLLMajorVersion, bv.byDLLMinorVersion,
	      bv.byMajorVersion, bv.byMinorVersion,
	      bv.byDay, bv.byMonth, bv.wYear );
  }
#endif
}


int BladeStream::Init( void )
{
  BE_CONFIG b;
  DWORD dwSamples, dwOutput;
  BE_ERR err;

#ifdef _DEBUG
  dbprintf( "BladeStream::Init" );
#endif

  ZeroMemory( &b, sizeof(b) );
  b.dwConfig = BE_CONFIG_MP3;
  b.format.mp3.dwSampleRate = 44100;
#if 1
  b.format.mp3.byMode = (BYTE)_nMode;
  b.format.mp3.wBitrate = _wBitrate;
  b.format.mp3.bCRC = _bCRC;
  b.format.mp3.bPrivate = _bPrivate;
  b.format.mp3.bOriginal = _bOriginal;
  b.format.mp3.bCopyright = _bCopyright;
#else
  b.format.mp3.byMode = BE_MP3_MODE_STEREO;
  b.format.mp3.wBitrate = 128;
  dbprintf( "    dwSampleRate: %d", b.format.mp3.dwSampleRate );
  dbprintf( "          byMode: %d", b.format.mp3.byMode );
  dbprintf( "        wBitrate: %d", b.format.mp3.wBitrate );
#endif

  err = _beInitStream( &b, &dwSamples, &dwOutput, &_hEncStream );
  _dwSampleBytes = dwSamples * 2;
  _pInput = new BYTE[_dwSampleBytes];
  _pOutput = new BYTE[dwOutput];
  return 0;
}


int BladeStream::SetOption( int opt, char *pszData )
{
#ifdef _DEBUG
  dbprintf( "BladeStream::SetOption( int, char * )" );
#endif

  return this->MP3Stream::SetOption( opt, pszData );
}


int BladeStream::SetOption( int opt, int iData )
{
#ifdef _DEBUG
  dbprintf( "BladeStream::SetOption( int, int )" );
#endif

  return this->MP3Stream::SetOption( opt, iData );
}



int encBladeAvail( void )
{
  HMODULE hDLL;
  BEVERSION beVersion;

  hDLL = LoadLibrary( "bladeenc.dll" );
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
