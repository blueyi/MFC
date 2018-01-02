/*
 * encbase.h - Copyright (C) 2000 Jay A. Key
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
#ifndef __ENC_H_INC
#define __ENC_H_INC

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "xtenc.h"

// The basic encoder stream class -- should never be instantiated
class BaseEncoderStream
{
 public:
  BaseEncoderStream();
  virtual ~BaseEncoderStream() { if ( _fpOut ) fclose( _fpOut ); };
  virtual int Init( void ) { return 1; };
  virtual int SetOption( int opt, char *pszData );
  virtual int SetOption( int opt, int iData );
  virtual int OpenOutputFile( void );
  virtual int CheckOutputFileExists( void );
  virtual int WriteHeader( void ) { return 0; };
  virtual unsigned int Encode( unsigned char *pData, unsigned int len ) { return 0; };
  virtual int Flush( void ) { return 0; };
  virtual int Close( void );
  virtual char *FileExtension( void ) { return _ext; };
  virtual char *FileName( void ) { return _fname; };
  virtual int VerifyDirectoryExists( char *szDir );
  virtual int CreateDir( char *szDir );
  int ComputeFileDir( char *szDir, int maxLen );
  int ComputeFileName( char *szName, int maxLen );

 protected:
  char _basedir[MAX_PATH+1];
  char _fname[MAX_PATH+1];
  char _filedir[MAX_PATH+1];
  char _ext[4];
  char _mode[5];
  char _expFileName[MAX_PATH+1];
  FILE *_fpOut;
  BOOL _bWrite;
};


void dbprintf( char *, ... );

#endif
