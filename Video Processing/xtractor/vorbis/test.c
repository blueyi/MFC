#include <windows.h>
#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include "BladeDll.h"

BOOL loadVorbEnc( void );
BOOL openFiles( char *lpszInFile, char *lpszOutFile );
int encodeThePuppy( DWORD );

static HANDLE hBladeDll = NULL;
static BEINITSTREAM   beInitStream;
static BEENCODECHUNK  beEncodeChunk;
static BEDEINITSTREAM beDeinitStream;
static BECLOSESTREAM  beCloseStream;
static BEVERSION      beVersion;
static FILE *fpIn = NULL;
static FILE *fpOut = NULL;
static BE_VERSION bev;

int main( int argc, char **argv )
{
  time_t t0, t1;
  double t;
  DWORD bitrate;

#ifdef SPEEDTEST
  if ( !openFiles( "e:\\music\\test.wav", "e:\\music\\test.ogg" ) )
    {
      printf( "Unable to open input and/or output files\n" );
      return 0;
    }
#else
  if ( argc != 4 )
    {
      printf( "Usage: test <infile.wav> <outfile.ogg> <bitrate (Kbps)>\n" );
      return 0;
    }

  bitrate = strtoul( argv[3], NULL, 10 );
  if ( bitrate < 32 ||  bitrate > 350 )
    {
      fprintf( stderr, "Invalid bitrate: must be inbetween 32 and 350\n" );
      return 0;
    }

  if ( !openFiles( argv[1], argv[2] ) )
    {
      printf( "Unable to open input and/or output files\n" );
      return 0;
    }
#endif

  if ( !loadVorbEnc() )
    {
      printf( "Error loading vorb_enc.dll\n" );
      return 0;
    }

  time( &t0 );
  encodeThePuppy( bitrate );
  time( &t1 );

  t = difftime( t1, t0 );
  printf( "Total time elapsed: %0.2f sec.\n", t );

  if ( fpIn )
    fclose( fpIn );
  if ( fpOut )
    fclose( fpOut );

  return 0;
}


BOOL loadVorbEnc( void )
{
#if 1
  hBladeDll = LoadLibrary( "vorb_enc.dll" );
#else
  hBladeDll = LoadLibrary( "BladeEnc.dll" );
#endif
  if ( !hBladeDll )
    return FALSE;

  beInitStream = (BEINITSTREAM)GetProcAddress( hBladeDll, "beInitStream" );
  beEncodeChunk = (BEENCODECHUNK)GetProcAddress( hBladeDll, "beEncodeChunk" );
  beDeinitStream = (BEDEINITSTREAM)GetProcAddress( hBladeDll, "beDeinitStream" );
  beCloseStream = (BECLOSESTREAM)GetProcAddress( hBladeDll, "beCloseStream" );
  beVersion = (BEVERSION)GetProcAddress( hBladeDll, "beVersion" );

  if ( !beInitStream || !beEncodeChunk || !beDeinitStream ||
       !beCloseStream || !beVersion )
    {
      FreeLibrary( hBladeDll );
      hBladeDll = FALSE;
      return FALSE;
    }

  ZeroMemory( &bev, sizeof(bev) );
  beVersion( &bev );
  return TRUE;
}



BOOL openFiles( char *lpszInFile, char *lpszOutFile )
{
  fpIn = fopen( lpszInFile, "rb" );
  if ( !fpIn )
    return FALSE;

#ifdef SPEEDTEST
  fpOut = NULL;
#else
  fpOut = fopen( lpszOutFile, "wb" );
  if ( !fpOut )
    return FALSE;
#endif

  return TRUE;
}



int encodeThePuppy( DWORD bitrate )
{
  HBE_STREAM hbeStream;
  BE_CONFIG b;
  BE_ERR err;
  DWORD dwSamples, dwMP3BufferSize, dwSampleBytes;
  BYTE *pInput, *pOutput;
  DWORD dwNumRead;

  ZeroMemory( &b, sizeof(b) );
  b.dwConfig = BE_CONFIG_VORBIS;
  b.format.vorb.channels      = 2;
  b.format.vorb.rate          = 44100;
  b.format.vorb.szTitle       = "Test track";
  b.format.vorb.szDescription = "Test recording using vorb_enc.dll";
  if ( bev.byDLLMajorVersion == 0 && bev.byDLLMinorVersion == 20 )
    {
      printf( "Detected vorb_enc.dll v0.20\n" );
      b.format.vorb.version       = 2;
      b.format.vorb.minbitrate    = -1;
      b.format.vorb.maxbitrate    = -1;
      b.format.vorb.nominalbitrate = bitrate;
    }
  else
    {
      // roll back to the original release
      b.format.vorb.version       = 1;
      b.format.vorb.mode          = 0;
    }

  err = beInitStream( &b, &dwSamples, &dwMP3BufferSize, &hbeStream );
  dwSampleBytes = 2 * dwSamples;

  pInput = (unsigned char *)malloc( dwSampleBytes );
  pOutput = (unsigned char *)malloc( dwMP3BufferSize );

  // skip the wav header
  fread( pInput, 1, 44, fpIn );
  while( !feof( fpIn ) )
    {
      DWORD dwNumRead;
      dwNumRead = fread( pInput, 1, dwSampleBytes, fpIn );

      if ( dwNumRead )
	{
	  if ( beEncodeChunk( hbeStream, dwNumRead/2, (PSHORT)pInput, pOutput, &dwNumRead ) != BE_ERR_SUCCESSFUL )
	    {
	      fprintf( stderr, "Error from Encoder... aborting!\n" );
	      goto abortPoint;
	    }
	  if ( dwNumRead && fpOut )
	    {
#ifndef SPEEDTEST
	      fwrite( pOutput, 1, dwNumRead, fpOut );
	      printf( "wrote %d bytes\n", dwNumRead );
#endif
	    }
	}
    }

abortPoint:  
  beDeinitStream( hbeStream, pOutput, &dwNumRead );
  if ( dwNumRead && fpOut )
    {
#ifndef SPEEDTEST
      fwrite( pOutput, 1, dwNumRead, fpOut );
      printf( "wrote %d bytes\n", dwNumRead );
#endif
    }
  beCloseStream( hbeStream );

  free( pInput );
  free( pOutput );

  return 0;
}
