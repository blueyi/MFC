/*
 * encbase.cpp - Copyright (C) 2000 Jay A. Key
 *
 * Implementation of the BaseEncoderStream class.  Serves as a parent
 * class for all of the encoder streams.
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
#include <string.h>
#include "encbase.h"

static BOOL bInitChars = FALSE;
static unsigned char validFnameChar[256];
static unsigned char validDirChar[256];

void replaceInvalidChars( char *, BOOL isDir );


BaseEncoderStream::BaseEncoderStream()
{
#ifdef _DEBUG
  dbprintf( "BaseEncoderStream::BaseEncoderStream" );
#endif
  _fpOut = NULL;
  ZeroMemory( _basedir, MAX_PATH+1 );
  ZeroMemory( _fname, MAX_PATH+1 );
  ZeroMemory( _filedir, MAX_PATH+1 );
  ZeroMemory( _expFileName, MAX_PATH+1 );
  ZeroMemory( _ext, 4 );
  _bWrite = TRUE;
}


int BaseEncoderStream::Close( void )
{
#ifdef _DEBUG
  dbprintf( "BaseEncoderStream::Close" );
#endif
  if ( _fpOut )
    {
      fclose( _fpOut );
      _fpOut = NULL;
    }

  return 1;
}


int BaseEncoderStream::SetOption( int opt, char *pszData )
{
  int retVal = 0;
  int i;

#ifdef _DEBUG
  dbprintf( "BaseEncoderStream::SetOption( int, char *)" );
#endif

  switch( opt )
    {
    case XT_OPT_BASEDIR:
      _basedir[MAX_PATH] = '\0';
      strncpy( _basedir, pszData, MAX_PATH );
      i = lstrlen( _basedir );
      if ( (i != 0) && (_basedir[i-1] == '\\') )
	_basedir[i-1] = '\0';
      retVal = 1;
      break;
    case XT_OPT_FILENAME:
      _fname[MAX_PATH] = '\0';
      ZeroMemory( _fname, MAX_PATH+1 );
      strncpy( _fname, pszData, MAX_PATH );
      replaceInvalidChars( _fname, false );
      retVal = 1;
      break;
    case XT_OPT_FILEDIR:
      _filedir[MAX_PATH] = '\0';
      ZeroMemory( _filedir, MAX_PATH+1 );
      strncpy( _filedir, pszData, MAX_PATH-1 );
      i = lstrlen( _filedir );
      // append a backslash if necessary
      if ( (i != 0) && (_filedir[i-1] != '\\') )
	_filedir[i] = '\\';
      dbprintf( "set _filedir to \"%s\"", _filedir );
      replaceInvalidChars( _filedir, true );
      retVal = 1;
      break;
    case XT_OPT_FILEEXT:
      _ext[3] = '\0';
      strncpy( _ext, pszData, 3 );
      retVal = 1;
      break;
    case XT_OPT_OPENMODE:
      _mode[4] = '\0';
      strncpy( _ext, pszData, 4 );
      retVal = 1;
      break;
    }
  return retVal;
}


int BaseEncoderStream::SetOption( int opt, int iData )
{
#ifdef _DEBUG
  dbprintf( "BaseEncoderStream::SetOption( int, int)" );
#endif

  switch( opt )
    {
    case XT_OPT_NOWRITE:
      _bWrite = (iData == 0);
      return 1;
    }

  return 0;
}


int BaseEncoderStream::OpenOutputFile( void )
{
  char szFname[MAX_PATH+1];

#ifdef _DEBUG
  dbprintf( "BaseEncoderStream::OpenOutputFile" );
#endif
  
  // create the output directory if necessary
  if ( !ComputeFileDir( szFname, MAX_PATH+1 ) 
       || !VerifyDirectoryExists( szFname ) )
    CreateDir( szFname );

  _fpOut = NULL;
  if ( _bWrite )
    {
      if ( !ComputeFileName( szFname, MAX_PATH+1 ) )
        return FALSE;
//      wsprintf( szFname, "%s\\%s%s.%s", _basedir, _filedir, _fname, _ext );
      dbprintf( "szFname: \"%s\"", szFname );
      _fpOut = fopen( szFname, _mode );
      return ( _fpOut != NULL );
    }

  return TRUE;
}


int BaseEncoderStream::CheckOutputFileExists( void )
{
  char szFname[MAX_PATH+1];
  
  FILE *fp;
  if ( !ComputeFileName( szFname, MAX_PATH+1 ) )
    return FALSE;
  
//  wsprintf( szFname, "%s\\%s%s.%s", _basedir, _filedir, _fname, _ext );
  fp = fopen( szFname, "rb" );
  if ( fp == NULL )
  {
    return FALSE;
  }
  else
  {
    fclose( fp );
    return TRUE;
  }
}




void dbprintf( char *fmt, ... )
{
  char buf[512];
  va_list arg;

  va_start( arg, fmt );

  vsprintf( buf, fmt, arg );
  OutputDebugString( buf );

  va_end( arg );
}


void replaceInvalidChars( char *s, BOOL isDir )
{
  if ( !bInitChars )
    {
      bInitChars = TRUE;      
      memset( validFnameChar, 0xFF, 256 );
      validFnameChar['\\'] = 0;
      validFnameChar['/'] = 0;
      validFnameChar[':'] = 0;
      validFnameChar['*'] = 0;
      validFnameChar['?'] = 0;
      validFnameChar['\"'] = 0;
      validFnameChar['<'] = 0;
      validFnameChar['>'] = 0;
      validFnameChar['|'] = 0;
      memset( validDirChar, 0xFF, 256 );
      validDirChar['/'] = 0;
      validDirChar[':'] = 0;
      validDirChar['*'] = 0;
      validDirChar['?'] = 0;
      validDirChar['\"'] = 0;
      validDirChar['<'] = 0;
      validDirChar['>'] = 0;
      validDirChar['|'] = 0;
    }

  while( s && *s )
    {
      if ( isDir )
      {
        if ( !validDirChar[(unsigned char)*s] )
    	  *s = '_';
      }
      else
      {
        if ( !validFnameChar[(unsigned char)*s] )
    	  *s = '_';
      }
      s++;
    }
}


int BaseEncoderStream::CreateDir( char *szDir )
{
  char *szTmp = (char *)malloc( MAX_PATH + 1 );
  char *szTmpDir = (char *)malloc( lstrlen( szDir ) + 1 );
  lstrcpy( szTmpDir, szDir );
  char *p = szTmp;
  ZeroMemory( szTmp, MAX_PATH + 1 );
  
  char *q = strstr( szTmpDir, ":" );
  if ( q - szTmpDir == 1 )
  {
    p[0] = szTmpDir[0];
    p[1] = szTmpDir[1];
    p[2] = '\\';
    p += 3;
  }
  
  dbprintf( "evaluating %s", szTmpDir + lstrlen(szTmp) );
  for ( q = strtok( szTmpDir + lstrlen(szTmp), "\\" ); q != NULL; q = strtok( NULL, "\\" ) )
  {
    replaceInvalidChars( q, false );
    lstrcat( p, q );
    lstrcat( p, "\\" );
    p += lstrlen( p );
    if ( !VerifyDirectoryExists( szTmp ) )
    {
      dbprintf( "Creating dir: %s", szTmp );
      CreateDirectory( szTmp, NULL );
    }
  }

  free( szTmp );
  free( szTmpDir );
  return VerifyDirectoryExists( szDir );
}


int BaseEncoderStream::VerifyDirectoryExists( char *szDir )
{
  int retval;
  char *szTmp = (char *)malloc( MAX_PATH + 1 );
  
  ZeroMemory( szTmp, MAX_PATH+1 );
  GetCurrentDirectory( MAX_PATH + 1, szTmp );
  retval = SetCurrentDirectory( szDir );
  SetCurrentDirectory( szTmp );
  
  free( szTmp );
  return retval;
}


int BaseEncoderStream::ComputeFileDir( char *szDir, int maxLen )
{
  int len;
  len = lstrlen( _basedir ) + lstrlen( _filedir ) + 2;
  if ( len > maxLen )
    return 0;
  wsprintf( szDir, "%s\\%s", _basedir, _filedir );
  return 1;
}

int BaseEncoderStream::ComputeFileName( char *szName, int maxLen )
{
  int len;
  len = lstrlen( _basedir );
  len += lstrlen( _filedir );
  len += lstrlen( _fname );
  len += lstrlen( _ext );
  len += 3;
  if ( len >= maxLen )
    return 0;
  wsprintf( szName, "%s\\%s%s.%s", _basedir, _filedir, _fname, _ext );
  return 1;
}

