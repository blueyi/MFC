/*
 * MP3Stream.cpp - Copyright (C) 2000 Jay A. Key
 *
 * Implementation of the MP3Stream class.  All of the classes which
 * provide an interface to a BladeEnc-ish encoder dll will implement
 * subclasses of this base class.
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
#include "MP3Stream.h"

MP3Stream::MP3Stream():BaseEncoderStream()
{
#ifdef _DEBUG
  dbprintf( "MP3Stream::MP3Stream" );
#endif

  _hDLL = NULL;
  _bID3 = FALSE;
  _iID3Level = XT_ID3_LEVEL0;
  _wBitrate = 128;
  ZeroMemory( _szArtist, 31 );
  ZeroMemory( _szTitle, 31 );
  ZeroMemory( _szAlbum, 31 );
  ZeroMemory( _szYear, 5 );
  _bGenre = 17; // default to "rock"
  _beInitStream     = NULL;
  _beEncodeChunk    = NULL;
  _beDeinitStream   = NULL;
  _beVersion        = NULL;
  _beWriteVBRHeader = NULL;
  _dwSampleBytes = 0;
  _dwInputLen = 0;
  _hEncStream = 0;
  lstrcpy( _ext, "MP3" );
  lstrcpy( _mode, "w+b" );
  _nMode = BE_MP3_MODE_STEREO;
  _bCRC =_bCopyright = _bPrivate = _bOriginal = FALSE;
  _trackNum = 0;
}


MP3Stream::~MP3Stream()
{
#ifdef _DEBUG
  dbprintf( "MP3Stream::~MP3Stream" );
#endif

  if ( _hDLL )
    FreeLibrary( _hDLL );
  if ( _pOutput )
    delete _pOutput;
  if ( _pInput )
    delete _pInput;
  
}


unsigned int MP3Stream::Encode( unsigned char *pData, unsigned int len )
{
  DWORD dwTmp;
  unsigned int retVal = 0;
  BE_ERR err;

  if ( _hEncStream == 0 )
    {
      return 0;
    }

  // if we've got left-over input from the last bit, add enough to it
  if ( _dwInputLen != 0 )
    {
      if ( _dwInputLen + len < _dwSampleBytes )
	{
	  // just buffer it
	  memcpy( _pInput + _dwInputLen, pData, len );
	  _dwInputLen += len;
	  return 0;
	}
      else
	{
	  memcpy( _pInput + _dwInputLen, pData, _dwSampleBytes - _dwInputLen );
	  pData += (_dwSampleBytes - _dwInputLen);
	  len -= (_dwSampleBytes - _dwInputLen);
	  _dwInputLen = _dwSampleBytes;
	}
    }

  if ( _dwInputLen )
    {
      dwTmp = 0;
      err = _beEncodeChunk( _hEncStream, _dwInputLen/2, (PSHORT)_pInput, _pOutput, &dwTmp );
      if ( _fpOut && _bWrite )
	fwrite( _pOutput, 1, dwTmp, _fpOut );
      retVal += dwTmp;
      _dwInputLen = 0;
    }

  while( len >= _dwSampleBytes )
    {
      dwTmp = 0;
      err = _beEncodeChunk( _hEncStream, _dwSampleBytes/2, (PSHORT)pData, _pOutput, &dwTmp );
#if 0
      if ( err != BE_ERR_SUCCESSFUL )
	printf( "We have a problem, Houston!\n" );
#endif
      if ( _fpOut && _bWrite )
	fwrite( _pOutput, 1, dwTmp, _fpOut );
      retVal += dwTmp;
      len -= _dwSampleBytes;
      pData += _dwSampleBytes;
    }
  if ( len )
    memcpy( _pInput, pData, len );
  _dwInputLen = len;

  return retVal;
}


int MP3Stream::Flush( void )
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
      if ( dwTmp && _fpOut && _bWrite )
	fwrite( _pOutput, 1, dwTmp, _fpOut );
    }

  _beDeinitStream( _hEncStream, _pOutput, &dwTmp );
  retVal += (int)dwTmp;
  if ( dwTmp && _fpOut && _fpOut )
    fwrite( _pOutput, 1, dwTmp, _fpOut );

  return retVal;
}


int MP3Stream::Close( void )
{
#ifdef _DEBUG
  dbprintf( "MP3Stream::Close" );
#endif

  if ( _iID3Level > 0 )
    {
      WriteID3V1Tag();
    }

  if ( _fpOut )
    fclose( _fpOut );
  if ( _hEncStream )
    _beCloseStream( _hEncStream );

  _fpOut = NULL;
  _beCloseStream = NULL;

  return 1;
}


int MP3Stream::OpenOutputFile( void )
{
#ifdef _DEBUG
  dbprintf( "MP3Stream::OpenOutputFile" );
#endif

  if ( !this->BaseEncoderStream::OpenOutputFile() )
    return 0;

  // write ID3V2 tag here or any other voodoo at the beginning of file

  return 1;
}


int MP3Stream::LoadEncoderFunctions( void )
{
#ifdef _DEBUG
  dbprintf( "MP3Stream::LoadEncoderFunctions" );
#endif

  if ( !_hDLL )
    return 0;

  _beInitStream = (BEINITSTREAM)GetProcAddress( _hDLL, "beInitStream" );
  _beEncodeChunk = (BEENCODECHUNK)GetProcAddress( _hDLL, "beEncodeChunk" );
  _beDeinitStream = (BEDEINITSTREAM)GetProcAddress( _hDLL, "beDeinitStream" );
  _beCloseStream = (BECLOSESTREAM)GetProcAddress( _hDLL, "beCloseStream" );
  _beVersion = (BEVERSION)GetProcAddress( _hDLL, "beVersion" );
  _beWriteVBRHeader = (BEWRITEVBRHEADER)GetProcAddress( _hDLL, "beWriteVBRHeader" );

  if ( !_beInitStream || !_beEncodeChunk || !_beDeinitStream ||
       !_beCloseStream || !_beVersion )
    {
      FreeLibrary( _hDLL );
      _hDLL = NULL;
      return 0;
    }

  return 1;
}


int MP3Stream::SetOption( int opt, int iVal )
{
#ifdef _DEBUG
  dbprintf( "MP3Stream::SetOption( int, int )" );
#endif

  switch( opt )
    {
    case XT_OPT_ID3LEVEL:
      dbprintf( "Setting ID3_LEVEL to %d", iVal );
      _iID3Level = iVal;
      break;

    case XT_OPT_ID3GENRE:
      _bGenre = (BYTE)iVal;
      break;

    case XT_OPT_CBITRATE:
      _wBitrate = (WORD)iVal;
      break;

    case XT_OPT_MP3MODE:
      _nMode = iVal;
      break;

    case XT_OPT_ORIGINAL:
      _bOriginal = (BOOL)iVal;
      break;

    case XT_OPT_CRC:
      _bCRC = (BOOL)iVal;
      break;

    case XT_OPT_COPYRIGHT:
      _bCopyright = (BOOL)iVal;
      break;

    case XT_OPT_PRIVATE:
      _bPrivate = (BOOL)iVal;
      break;

    case XT_OPT_TRACKNUM:
      _trackNum = (BYTE)iVal;
      break;

    default:
      return this->BaseEncoderStream::SetOption( opt, iVal );
    }

  return 1;
}


int MP3Stream::SetOption( int opt, char *pszData )
{
#ifdef _DEBUG
  dbprintf( "MP3Stream::SetOption( int, char * )" );
#endif

  switch( opt )
    {
    case XT_OPT_ID3YEAR:
      strncpy( _szYear, pszData, 4 ); _szYear[4] = '\0';
      break;

    case XT_OPT_ARTIST:
      strncpy( _szArtist, pszData, 30 ); _szArtist[30] = '\0';
      break;

    case XT_OPT_ALBUM:
      strncpy( _szAlbum, pszData, 30 ); _szAlbum[30] = '\0';
      break;

    case XT_OPT_TRACK:
      strncpy( _szTitle, pszData, 30 ); _szTitle[30] = '\0';
      break;

    default:
      return this->BaseEncoderStream::SetOption( opt, pszData );
    }

  return 1;
}


int MP3Stream::WriteID3V1Tag( void )
{
  unsigned char buf[129];
  unsigned char *p = buf;

#ifdef _DEBUG
  dbprintf( "MP3Stream::WriteID3V1Tag" );
#endif

  if ( !_fpOut || !_bWrite )
    return 0;

  // don't write the tag if any of the info is missing
  if ( (lstrlen( _szAlbum ) == 0)
       || (lstrlen( _szArtist ) == 0)
       || (lstrlen( _szTitle ) == 0) )
    return 0;

  memset( buf, 0, 129 );
  memcpy( p, "TAG", 3 ); p += 3;
  memcpy( p, _szTitle, lstrlen( _szTitle ) ); p += 30;
  memcpy( p, _szArtist, lstrlen( _szArtist ) ); p += 30;
  memcpy( p, _szAlbum, lstrlen( _szAlbum ) ); p += 30;
  memcpy( p, _szYear, 4 ); p += 4;
  buf[126] = _trackNum;
  buf[127] = _bGenre;

  fwrite( buf, 1, 128, _fpOut );
  return 1;
}
