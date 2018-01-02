/*
 * LameStream.cpp - Copyright (C) 2000 Jay A. Key
 *
 * Implementation of the LameStream class.  Implements the interface for
 * the newer lame_enc.dll, ie. with VBR support.
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
#include "LameStream.h"


LameStream::LameStream( ):MP3Stream()
{
#ifdef _DEBUG
  dbprintf( "LameStream::LameStream" );
#endif

  lstrcpy( _ext, "MP3" );
  lstrcpy( _mode, "w+b" );
  _hDLL = LoadLibrary( "lame_enc.dll" );

  _bWriteVBRHeader = TRUE;
  _nQuality = HIGH_QUALITY;
  _nMPEGVersion = MPEG1;
  _bEnableVBR = TRUE;
  _nVBRQuality = 5;

  if ( !_hDLL )
    return;

  LoadEncoderFunctions();
}


int LameStream::Init( void )
{
  BE_CONFIG b;
  DWORD dwSamples, dwOutput;

#ifdef _DEBUG
  dbprintf( "LameStream::Init" );
#endif
  
  ZeroMemory( &b, sizeof(b) );
  b.dwConfig = BE_CONFIG_LAME;
  b.format.LHV1.dwStructVersion        = 1;
  b.format.LHV1.dwStructSize           = sizeof(BE_CONFIG);
  b.format.LHV1.dwSampleRate           = 44100;
  b.format.LHV1.dwReSampleRate         = 0;
  b.format.LHV1.nMode                  = _nMode;
  b.format.LHV1.dwBitrate              = _wBitrate;
  b.format.LHV1.dwMaxBitrate           = _wMaxBitrate;
  b.format.LHV1.nQuality               = (MPEG_QUALITY)_nQuality;
  b.format.LHV1.dwMpegVersion          = _nMPEGVersion;
  b.format.LHV1.bCRC                   = _bCRC;
  b.format.LHV1.bPrivate               = _bPrivate;
  b.format.LHV1.bOriginal              = _bOriginal;
  b.format.LHV1.bCopyright             = _bCopyright;
  b.format.LHV1.bWriteVBRHeader        = _bWriteVBRHeader;
  b.format.LHV1.bEnableVBR             = _bEnableVBR;
  b.format.LHV1.nVBRQuality            = _nVBRQuality;

  _beInitStream( &b, &dwSamples, &dwOutput, &_hEncStream );
  _dwSampleBytes = dwSamples * 2;
  _pInput = new BYTE[_dwSampleBytes];
  _pOutput = new BYTE[dwOutput];
  return 0;
}


int LameStream::SetOption( int opt, char *pszData )
{
#ifdef _DEBUG
  dbprintf( "LameStream::SetOption( int, char * )" );
#endif

  return this->MP3Stream::SetOption( opt, pszData );
}


int LameStream::SetOption( int opt, int iData )
{
#ifdef _DEBUG
  dbprintf( "LameStream::SetOptiont( int, int )" );
#endif

  switch( opt )
    {
    case XT_OPT_MAXBITRATE:
      _wMaxBitrate = (WORD)iData;

    case XT_OPT_MPEGQUALITY:
      _nQuality = iData;
      break;

    case XT_OPT_MPEGVERSION:
      _nMPEGVersion = iData;
      break;

    case XT_OPT_ENABLEVBR:
      _bEnableVBR = (BOOL)iData;
      break;

    case XT_OPT_VBRQUALITY:
      _nVBRQuality = iData;
      break;
    
    case XT_OPT_LAME_MODE:
      _nMode = iData;
      break;

    default:
      return this->MP3Stream::SetOption( opt, iData );
    }
  return 1;
}


int LameStream::Close( void )
{
  char szFname[MAX_PATH+1];

#ifdef _DEBUG
  dbprintf( "LameStream::Close" );
#endif

  if ( _bWrite )
    {
      this->BaseEncoderStream::Close();

      wsprintf( szFname, "%s\\%s%s.%s", _basedir, _filedir, _fname, _ext );
      if ( _beWriteVBRHeader && _bWriteVBRHeader )
	{
	  dbprintf( "Writing VBR header to \"%s\"", szFname );
	  _beWriteVBRHeader( szFname );
	}

      if ( _iID3Level > 0 )
	{
	  // reopen the file to write the tag
	  _fpOut = fopen( szFname, "ab" );
	  WriteID3V1Tag();
	}

      if ( _fpOut )
	fclose( _fpOut );
    }

  _fpOut = NULL;

  return 0;
}


int encLameAvail( int enc )
{
  HMODULE hDLL;
  BEVERSION beVersion;
  BE_VERSION v;
  DWORD dwEngine, dwDLL;
  BOOL bOld = FALSE;
  int retVal = 0;

  hDLL = LoadLibrary( "lame_enc.dll" );
  if ( !hDLL )
    return 0;

  beVersion = (BEVERSION)GetProcAddress( hDLL, "beVersion" );
  if ( !beVersion )
    {
      FreeLibrary( hDLL );
      return 0;
    }

  beVersion( &v );
  dwEngine = (((DWORD)v.byMajorVersion)<<8) + v.byMinorVersion;
  dwDLL = (((DWORD)v.byDLLMajorVersion)<<8) + v.byDLLMinorVersion;
  if ( ( dwEngine < 0x0336 ) || ( dwDLL < 0x0104 ) )
    bOld = TRUE;
  if ( bOld && ( enc == XT_ENC_LAME1 ) )
    retVal = 1;
  else if ( !bOld && ( enc == XT_ENC_LAME2 ) )
    retVal = 1;

  FreeLibrary( hDLL );
  return retVal;
}


#if 0
int LameStream::Flush( void )
{
  DWORD dwTmp;
  int retVal = 0;

#ifdef _DEBUG
  dbprintf( "MP3Stream::Flush" );
#endif

  if ( _hEncStream == 0 )
    return 0;

  if ( _dwInputLen )
    {
      _beEncodeChunk( _hEncStream, _dwInputLen/2, (PSHORT)_pInput, _pOutput, &dwTmp );
      retVal += (int)dwTmp;
      if ( dwTmp && _bWrite )
	fwrite( _pOutput, 1, dwTmp, _fpOut );
    }

  _beDeinitStream( _hEncStream, _pOutput, &dwTmp );
  retVal += (int)dwTmp;
  if ( dwTmp && _bWrite )
    fwrite( _pOutput, 1, dwTmp, _fpOut );

  return retVal;
}
#endif
