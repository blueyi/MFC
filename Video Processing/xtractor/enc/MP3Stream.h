/*
 * MP3Stream.h - Copyright (C) 2000 Jay A. Key
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
#ifndef __MP3STREAM_H_INC
#define __MP3STREAM_H_INC

#include "encbase.h"
#include "bladedll.h"

typedef enum {
  XT_ID3_LEVEL0 = 0,
  XT_ID3_LEVEL1,
  XT_ID3_LEVEL2
};

/*
 * Generic to all of the MP3 encoders
 */
class MP3Stream : public BaseEncoderStream
{
 public:
  MP3Stream();
  virtual ~MP3Stream();
  virtual unsigned int Encode( unsigned char *pData, unsigned int len );
  virtual int Flush( void );
  virtual int Close( void );
  virtual int OpenOutputFile( void );
  virtual int SetOption( int opt, char *pszData );
  virtual int SetOption( int opt, int iVal );

 protected:
  int LoadEncoderFunctions( void );
  int WriteID3V1Tag( void );

  // DLL stuff
  HBE_STREAM _hEncStream;
  HMODULE _hDLL;
  BEINITSTREAM   _beInitStream;
  BEENCODECHUNK  _beEncodeChunk;
  BEDEINITSTREAM _beDeinitStream;
  BECLOSESTREAM  _beCloseStream;
  BEVERSION      _beVersion;
  BEWRITEVBRHEADER _beWriteVBRHeader;
  DWORD _dwSampleBytes;
  DWORD _dwInputLen;
  BYTE *_pInput;
  BYTE *_pOutput;
  // ID3 info
  char _szArtist[31];
  char _szTitle[31];
  char _szAlbum[31];
  char _szYear[5];
  BYTE _bGenre;
  // init info
  WORD _wBitrate;
  int _nMode;
  BOOL _bCRC;
  BOOL _bCopyright;
  BOOL _bPrivate;
  BOOL _bOriginal;
  BOOL _bID3;
  int _iID3Level;
  BYTE _trackNum;
};

#endif
