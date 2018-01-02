/*
 * test.c - Copyright (C) 2000 Jay A. Key
 *
 * Test harness for xtenc.dll
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
#include <string.h>
#include <time.h>
#include "xtenc.h"
#include "BladeDll.h"

int getMode( char *sMode );
int printUsage( void );
void doEncode( FILE *fp, HXTENCODER hEnc );

int main( int argc, char **argv  )
{
  FILE *fpIn;
  int mode;
  HXTENCODER hEnc;
  char *args[4];
  time_t t1, t0;
  double t;


#ifndef _PROFILE_TEST
  if ( xtFormatAvail( XT_FMT_RAW ) )
    printf( "Raw format available\n" );

  if ( xtFormatAvail( XT_FMT_WAV ) )
    printf( "WAV format available\n" );

  if ( xtFormatAvail( XT_FMT_MP3 ) )
    printf( "MP3 format available\n" );

  if ( xtFormatAvail( XT_FMT_OGG ) )
    printf( "OGG/Vorbis format available\n" );

  if ( xtEncoderAvail( XT_ENC_LAME1 ) )
    printf( "Old style lame_enc.dll detected\n" );

  if ( xtEncoderAvail( XT_ENC_LAME2 ) )
    printf( "New style lame_enc.dll detected\n" );

  if ( xtEncoderAvail( XT_ENC_BLADE ) )
    printf( "bladeenc.dll detected\n" );

  if ( xtEncoderAvail( XT_ENC_VORBIS ) )
    printf( "vorb_enc.dll detected\n" );
#endif

#ifndef _DEBUG
  if ( argc != 4 )
    {
      printUsage();
      return 0;
    }
#endif

  args[0] = argv[0];
#ifndef _DEBUG
  args[1] = argv[1];
  args[2] = argv[2];
  args[3] = argv[3];
#else
  args[1] = "vorb";
  args[2] = "\\wav\\foo.wav";
  args[3] = "foo";
#endif

  mode = getMode( args[1] );
  if ( mode == -1 )
    {
      printf( "Illegal mode: %s\n", args[1] );
      printUsage();
      return 0;
    }

  fpIn = fopen( args[2], "rb" );
  if ( !fpIn )
    {
      printf( "Unable to open file \"%s\"\n", args[2] );
      printUsage();
      return 0;
    }

  hEnc = xtGetEncoder( mode );
  if ( hEnc == 0 )
    {
      printf( "xtGetEncoder() returned NULL\n" );
      printUsage();
      return 0;
    }

  xtSetAsciiOption( hEnc, XT_OPT_BASEDIR, "." );
  xtSetAsciiOption( hEnc, XT_OPT_FILENAME, args[3] );
  xtSetAsciiOption( hEnc, XT_OPT_ARTIST, "8 1/2 Souvenirs" );
  xtSetAsciiOption( hEnc, XT_OPT_ALBUM, "Happy Feet" );
  xtSetAsciiOption( hEnc, XT_OPT_TRACK, "Happy Feet" );
  xtSetAsciiOption( hEnc, XT_OPT_ID3YEAR, "1997" );
  xtSetIntOption( hEnc, XT_OPT_ID3GENRE, 8 );
  xtSetIntOption( hEnc, XT_OPT_ID3LEVEL, 1 );
  xtSetIntOption( hEnc, XT_OPT_CBITRATE, 128 );
  xtSetIntOption( hEnc, XT_OPT_MAXBITRATE, 224 );
  xtSetIntOption( hEnc, XT_OPT_MP3MODE, BE_MP3_MODE_STEREO );
  xtSetIntOption( hEnc, XT_OPT_ENABLEVBR, TRUE );

  xtInit( hEnc );

  time( &t0 );
  doEncode( fpIn, hEnc );
  time( &t1 );

  t = difftime( t1, t0 );
  printf( "Total time: %0.2f sec.\n", t );

  return 0;
}


int getMode( char *sMode )
{
  static char *szMode[] = { "raw", "wav", "lame1", "lame2", "blade", "vorb", NULL };
  int i;

  if ( !sMode )
    return -1;

  i = 0;
  while( szMode[i] )
    {
      if ( !strcmpi( sMode, szMode[i] ) )
	return i;
      i++;
    }

  return -1;
}


int printUsage( void )
{
  printf( "Usage: test <mode> <infile> <outfile-base>\n" );
  printf( "     : <mode> may be one of raw, wav, lame1, lame2, blade or vorb\n" );
  return 0;
}


void doEncode( FILE *fp, HXTENCODER hEnc )
{
  static unsigned char buf[1024];
  unsigned long dwRead;
  unsigned long dwTotal = 0;

#ifndef _PROFILE_TEST
  xtOpenOutputFile( hEnc );
#endif

  // skip WAV header
  fread( buf, 1, 44, fp );

  while( !feof( fp ) )
    {
      dwRead = fread( buf, 1, 1024, fp );
      dwTotal += dwRead;
      //printf( "%7d bytes read...\n", dwTotal );
      if ( dwRead )
	{
	  dwRead = xtEncode( hEnc, buf, dwRead );
#if 0
	  if ( dwRead )
	    printf( "Wrote %d bytes\n", dwRead );
#else
	  if ( dwRead == 1045 )
	    dwRead = 1045;
#endif
	}
    }
  xtFlush( hEnc );
  xtClose( hEnc );
}
