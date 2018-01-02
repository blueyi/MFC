/*
 * LameStream.h - Copyright (C) 2000 Jay A. Key
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
#ifndef __LAMESTREAM_H_INC
#define __LAMESTREAM_H_INC

#include "MP3Stream.h"

class LameStream : public MP3Stream
{
 public:
  LameStream( );
  virtual int Init( void );
  virtual int SetOption( int opt, char *pszData );
  virtual int SetOption( int opt, int iVal );
  //virtual int Flush( void );
  virtual int Close( void );

 private:
  BOOL _bWriteVBRHeader;
  WORD _wMaxBitrate;
  int _nQuality;
  int _nMPEGVersion;
  BOOL _bEnableVBR;
  int _nVBRQuality;
};

int encLameAvail( int enc );

#endif
