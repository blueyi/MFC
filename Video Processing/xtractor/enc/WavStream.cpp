/*
 * WavStream.cpp - Copyright (C) 2000 Jay A. Key
 *
 * Implementation for the WavStream class.  Writes data to a WAV file.
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
#include "WavStream.h"

#pragma pack(push)
#pragma pack(1)
/*
 * WAV file header format
 */
typedef struct
{
  BYTE  riff[4];            /* must be "RIFF"                */
  DWORD len;                /* #bytes + 44 - 8               */
  BYTE  cWavFmt[8];         /* must be "WAVEfmt"             */
  DWORD dwHdrLen;
  WORD  wFormat;
  WORD  wNumChannels;
  DWORD dwSampleRate;
  DWORD dwBytesPerSec;
  WORD  wBlockAlign;
  WORD  wBitsPerSample;
  BYTE  cData[4];            /* must be "data"               */
  DWORD dwDataLen;           /* #bytes                       */
} WAVHDR, *PWAVHDR, *LPWAVHDR;
#pragma pack(pop)



WavStream::WavStream() : BaseEncoderStream()
{
  lstrcpy( _ext, "wav" );
  lstrcpy( _mode, "w+b" );
  _totalWritten = 0;
}


unsigned int WavStream::Encode( unsigned char *pData, unsigned int len )
{
  if ( !_fpOut )
    return 0;

  _totalWritten += len;

  if ( _bWrite )
    return fwrite( pData, 1, len, _fpOut );
  else
    return len;
}


int WavStream::SetOption( int opt, char *pszData )
{
  return this->BaseEncoderStream::SetOption( opt, pszData );
}



int WavStream::SetOption( int opt, int iData )
{
  return this->BaseEncoderStream::SetOption( opt, iData );
}



int WavStream::OpenOutputFile( void )
{
  if ( _bWrite )
    {
      if ( !this->BaseEncoderStream::OpenOutputFile() )
	return 0;
      this->WriteWavHeader();
    }
  return 1;
}


int WavStream::Close( void )
{
  if ( _bWrite )
    {
      this->WriteWavHeader();
      return this->BaseEncoderStream::Close();
    }
  return 1;
}


void WavStream::WriteWavHeader( void )
{
  WAVHDR wav;

  dbprintf( "WavStream::WriteWavHeader(%d) (sizeof(wav):%d)", _totalWritten, sizeof(WAVHDR) );
  dbprintf( "WavStream::WriteWavHeader, _fpOut: %08X", _fpOut );

  ZeroMemory( &wav, sizeof(wav) );

  memcpy( wav.riff, "RIFF", 4 );
  wav.len = _totalWritten + 44 - 8;
  memcpy( wav.cWavFmt, "WAVEfmt ", 8 );
  wav.dwHdrLen = 16;
  wav.wFormat = 1;
  wav.wNumChannels = 2;
  wav.dwSampleRate = 44100;
  wav.dwBytesPerSec = 44100*2*2;
  wav.wBlockAlign = 4;
  wav.wBitsPerSample = 16;
  memcpy( wav.cData, "data", 4 );
  wav.dwDataLen = _totalWritten;
  fseek( _fpOut, 0, SEEK_SET );

  fwrite( &wav, 1, sizeof(wav), _fpOut );
}
