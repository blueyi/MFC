/*
 * vorbis_dll.c - Copyright (C) 2000 Jay A. Key
 *
 * 32-bit Windows DLL wrapper for Ogg Vorbis bitstream encoding.
 * Implements its interface as an extension to the Blade Encoder DLL API.
 *
 * Must be linked with the Ogg Vorbis SDK to be usefull.
 *
 **********************************************************************
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 **********************************************************************
 *
 */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

//#include "vorbis/modes.h"

#include "vorbis/vorbisenc.h"
#include "vorbis/codec.h"

#define _BLADEDLL
#include "bladedll.h"

void dbprintf( char *fmt, ... );
int AddComment( vorbis_comment *vc, char *szField, char *szData );
int InitComments( PBE_CONFIG pb, vorbis_comment *vc );
float bitrateToQuality( long bitrate );

#define READ 1024
#define MAXOUTPUTBUF (20*READ)
typedef struct {
  ogg_stream_state os;
  ogg_page         og;
  ogg_packet       op;
  vorbis_comment   vc;
  vorbis_dsp_state vd;
  vorbis_block     vb;
  vorbis_info      vi;
  int              eos;
  char             readbuffer[READ*4+44];
} VDSTREAM, *PVDSTREAM;

static BOOL bFirst = TRUE;

#define MAXSTREAMS 10
PVDSTREAM aStreams[MAXSTREAMS];

BOOL thisStreamSucks( HBE_STREAM hbeStream );


BOOL WINAPI DllMain( HANDLE hModule, DWORD dwReason, LPVOID lpReserved )
{
  return TRUE;
}


void InitDll( void )
{
  ZeroMemory( &aStreams[0], sizeof(aStreams) );
  bFirst = FALSE;
}


/***************************************************************************
 *
 * beInitStream:
 *   Used to obtain a HANDLE to an encoder stream.  Up to MAXSTREAMS handles
 * may be open at any one given instant.  dwSamples will receive the maximum
 * number of 16-bit samples (dwSamples *2 = # of bytes), dwBufferSize will
 * receive the size of the output buffer that the calling application should
 * provide, and phbeStream will receive the stream handle.
 *
 ***************************************************************************/
__declspec(dllexport) BE_ERR beInitStream( PBE_CONFIG pbeConfig, PDWORD dwSamples, PDWORD dwBufferSize, PHBE_STREAM phbeStream )
{
  int i;
  DWORD dwStream = 0xFFFFFFFF;
  PVDSTREAM pvd;
  //  vorbis_info      vi;

  if ( bFirst )
    InitDll();

  // find an unsused stream
  for( i = 0; i < MAXSTREAMS; i++ )
    {
      if ( aStreams[i] == NULL )
	{
	  aStreams[i] = (PVDSTREAM)GlobalAlloc( GPTR, sizeof(VDSTREAM) );
	  dwStream = (DWORD)i;
	  break;
	}
    }

  if ( dwStream == 0xFFFFFFFF || aStreams[dwStream] == NULL )
    {
      return BE_ERR_NO_MORE_HANDLES;
    }

  *dwSamples = READ * 2;
  // this is probably overkill, but since the current version (beta 4)
  // seems to return as much as 17 KB on the first read, clients need to
  // allocate a large output buffer
  *dwBufferSize = MAXOUTPUTBUF;

  *phbeStream = dwStream + 1;

  pvd = aStreams[dwStream];

  if ( pbeConfig->format.vorb.version >= VORBENCSTRUCTVER )
    {
      vorbis_info_init( &pvd->vi );
      vorbis_encode_init_vbr( &pvd->vi, pbeConfig->format.vorb.channels,
        pbeConfig->format.vorb.rate, pbeConfig->format.vorb.quality );
    }
  else if ( pbeConfig->format.vorb.version == 2 )
    {
      float quality;
/*
      long minbitrate, maxbitrate, nominalbitrate;
      minbitrate = pbeConfig->format.vorb.minbitrate;
      nominalbitrate = pbeConfig->format.vorb.nominalbitrate;
      maxbitrate = pbeConfig->format.vorb.maxbitrate;
      if ( minbitrate > 0 )
        minbitrate *= 1000;
      if ( maxbitrate > 0 )
        maxbitrate *= 1000;
//      nominalbitrate *= 1000;
*/
      quality = bitrateToQuality( pbeConfig->format.vorb.nominalbitrate );

      // use the vorb2 struct instead
      vorbis_info_init( &pvd->vi );
      vorbis_encode_init_vbr( &pvd->vi, pbeConfig->format.vorb.channels,
        pbeConfig->format.vorb.rate, quality );
    }
  else if ( pbeConfig->format.vorb.version == 1 )
    {
      // simulate the old version
      long bitrate;
      float quality;
      switch( pbeConfig->format.vorb.mode )
      {
        case 0:
        default:
          // select ~128kbps stream
          bitrate = 128000;
          break;
        case 1:
	        // select ~160kbps stream
          bitrate = 160000;
          break;
        case 2:
          // select ~192kbps stream
          bitrate = 192000;
          break;
        case 3:
          // select ~256kbps stream
          bitrate = 256000;
          break;
        case 4:
          // select ~350kbps stream
          bitrate = 350000;
          break;
      }
      quality = bitrateToQuality( bitrate );
      vorbis_info_init( &pvd->vi );
      vorbis_encode_init_vbr( &pvd->vi, pbeConfig->format.vorb.channels,
        pbeConfig->format.vorb.rate, quality );
    }
  else
  {
    // just use 128000 if using a *really* old version
    float quality = bitrateToQuality( 128 );
    vorbis_info_init( &pvd->vi );
    vorbis_encode_init_vbr( &pvd->vi, pbeConfig->format.vorb.channels,
      pbeConfig->format.vorb.rate, quality );
  }

  InitComments( pbeConfig, &pvd->vc );

  vorbis_analysis_init( &pvd->vd, &pvd->vi );
  vorbis_block_init( &pvd->vd, &pvd->vb );

  srand(time(NULL));
  ogg_stream_init( &pvd->os, 1500 );

  {
    ogg_packet header;
    ogg_packet header_comm;
    ogg_packet header_code;

    vorbis_analysis_headerout( &pvd->vd, &pvd->vc, &header, &header_comm, &header_code );
    ogg_stream_packetin( &pvd->os, &header );
    ogg_stream_packetin( &pvd->os, &header_comm );
    ogg_stream_packetin( &pvd->os, &header_code );
  }

  return BE_ERR_SUCCESSFUL;
}


/***************************************************************************
 *
 * beVersion:
 *   Fills in a BE_VERSION struct with current information
 *
 ***************************************************************************/
__declspec(dllexport) void beVersion( PBE_VERSION pbeVersion )
{
  static char *months[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
  char szDate[20];
  char szTmp[5];
  int i;

  if ( bFirst )
    InitDll();

  pbeVersion->byDLLMajorVersion = 0;
  pbeVersion->byDLLMinorVersion = 30;

  pbeVersion->byMajorVersion = 0;
  pbeVersion->byMinorVersion = 0;

  // extract month
  pbeVersion->byMonth = 1;
  strncpy( szTmp, szDate, 3 );
  for( i = 0; i < 12; i++ )
    {
      if ( !strcmp(szTmp,months[i]) )
	{
	  pbeVersion->byMonth = i+1;
	  break;
	}
    }
  pbeVersion->byDay = atoi(szDate+4);

  pbeVersion->wYear = atoi(szDate+7 );

  ZeroMemory( pbeVersion->zHomepage, BE_MAX_HOMEPAGE );
  strcpy( pbeVersion->zHomepage, "Linked with Ogg Vorbis 1.0rc3 available at http://www.xiph.org/ogg/vorbis/" );
}


/***************************************************************************
 *
 * beEncodeChunk:
 *   
 ***************************************************************************/
__declspec(dllexport) BE_ERR beEncodeChunk( HBE_STREAM hbeStream, DWORD nSamples, PSHORT pSamples, PBYTE pOutput, PDWORD pdwOutput )
{
  PVDSTREAM pvd;
  int i;
  float **buffer;
  signed char *b;
  int count;
  int eos;
  DWORD dwTotal;

  if ( bFirst )
    InitDll();

  if ( thisStreamSucks( hbeStream ) )
    return BE_ERR_INVALID_HANDLE;

  if ( nSamples == 0 )
    return BE_ERR_SUCCESSFUL;

  pvd = aStreams[hbeStream-1];

  buffer = vorbis_analysis_buffer( &pvd->vd, READ );

  b = (signed char *)pSamples;
#if 1
  for( i = 0; i < nSamples/2; i++ )
    {
      buffer[0][i] = ((b[i*4+1]<<8)|(0x00FF&(int)b[i*4]))/32768.0f;
      buffer[1][i] = ((b[i*4+3]<<8)|(0x00FF&(int)b[i*4+2]))/32768.0f;
    }
#endif

  vorbis_analysis_wrote( &pvd->vd, i );

  *pdwOutput = 0;
  dwTotal = 0;
  count = 0;
  eos = 0;
  while ( vorbis_analysis_blockout( &pvd->vd, &pvd->vb ) == 1 )
    {
      count++;
	
      vorbis_analysis( &pvd->vb, &pvd->op );
      ogg_stream_packetin( &pvd->os, &pvd->op );
      while( !eos && ( ogg_stream_pageout( &pvd->os, &pvd->og ) != 0 ) )
	{
	  dwTotal = *pdwOutput;
	  dwTotal += (pvd->og.header_len + pvd->og.body_len);
	  if ( dwTotal > MAXOUTPUTBUF ) {
	    return BE_ERR_BUFFER_TOO_SMALL;
	  }
	  *pdwOutput = dwTotal;
	  memcpy( pOutput, pvd->og.header, pvd->og.header_len );
	  pOutput += pvd->og.header_len;
	  memcpy( pOutput, pvd->og.body, pvd->og.body_len );
	  pOutput += pvd->og.body_len;
	  if ( ogg_page_eos(&pvd->og) )
	    eos = 1;
	}
    }

  return BE_ERR_SUCCESSFUL;
}


/***************************************************************************
 *
 * beDeinitStream:
 *   Flushes the stream.  Should be called prior to beCloseStream.
 *
 ***************************************************************************/
__declspec(dllexport) BE_ERR beDeinitStream( HBE_STREAM hbeStream, PBYTE pOutput, PDWORD pdwOutput )
{
  PVDSTREAM pvd;

  if ( bFirst )
    InitDll();

  if ( thisStreamSucks( hbeStream ) )
    return BE_ERR_INVALID_HANDLE;

  pvd = aStreams[hbeStream-1];

  vorbis_analysis_wrote( &pvd->vd, 0 );

  *pdwOutput = 0;
  while ( vorbis_analysis_blockout( &pvd->vd, &pvd->vb ) == 1 )
    {
      int i;

      vorbis_analysis( &pvd->vb, &pvd->op );
      ogg_stream_packetin( &pvd->os, &pvd->op );
      i = ogg_stream_pageout( &pvd->os, &pvd->og );
      if ( i != 0 )
	{
	  memcpy( pOutput, pvd->og.header, pvd->og.header_len );
	  pOutput += pvd->og.header_len;
	  memcpy( pOutput, pvd->og.body, pvd->og.body_len );
	  pOutput += pvd->og.body_len;
	  *pdwOutput += (pvd->og.header_len + pvd->og.body_len);
	}
      if ( *pdwOutput > 10*READ )
	return BE_ERR_BUFFER_TOO_SMALL;
    }

  return BE_ERR_SUCCESSFUL;
}


/***************************************************************************
 *
 * beCloseStream:
 *   Closes the stream and deallocates all allocated memory
 *
 ***************************************************************************/
__declspec(dllexport) BE_ERR beCloseStream( HBE_STREAM hbeStream )
{
  PVDSTREAM pvd;

  if ( bFirst )
    InitDll();

  if ( thisStreamSucks( hbeStream ) )
    return BE_ERR_INVALID_HANDLE;

  pvd = aStreams[hbeStream-1];

  ogg_stream_clear( &pvd->os );
  vorbis_block_clear( &pvd->vb );
  vorbis_dsp_clear( &pvd->vd );

  GlobalFree( (HGLOBAL)aStreams[hbeStream-1] );
  aStreams[hbeStream-1] = NULL;

  return BE_ERR_SUCCESSFUL;
}


/*
 * returns TRUE if the handle is invalid, FALSE if it's OK
 */
BOOL thisStreamSucks( HBE_STREAM hbeStream )
{
  DWORD dwStream = hbeStream - 1;

  if ( bFirst )
    InitDll();

  if ( (dwStream > MAXSTREAMS) || (aStreams[dwStream] == NULL) )
    return TRUE;
  return FALSE;
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


int InitComments( PBE_CONFIG pb, vorbis_comment *vc )
{
  int i = 0;

  vorbis_comment_init( vc );

  if ( pb->dwConfig == BE_CONFIG_VORBIS )
    {
      i += AddComment( vc, "ARTIST", pb->format.vorb.szArtist );
      i += AddComment( vc, "TITLE", pb->format.vorb.szTitle );
      i += AddComment( vc, "VERSION", pb->format.vorb.szVersion );
      i += AddComment( vc, "ALBUM", pb->format.vorb.szAlbum );
      i += AddComment( vc, "ORGANIZATION", pb->format.vorb.szOrganization );
      i += AddComment( vc, "DESCRIPTION", pb->format.vorb.szDescription );
      i += AddComment( vc, "GENRE", pb->format.vorb.szGenre );
      i += AddComment( vc, "DATE", pb->format.vorb.szDate );
      i += AddComment( vc, "LOCATION", pb->format.vorb.szLocation );
      i += AddComment( vc, "COPYRIGHT", pb->format.vorb.szCopyright );
    }

  if ( !i )
    vorbis_comment_add( vc, "DESCRIPTION=Encoded by vorb_enc.dll" );

  return 0;
}


int AddComment( vorbis_comment *vc, char *szField, char *szData )
{
  char buf[128], *p;

  if ( !szField || !szData || !vc )
    return 0;

  ZeroMemory( buf, 128 );
  wsprintf( buf, "%s=", szField );
  p = buf + lstrlen(buf);
  strncpy( p, szData, 128 - (lstrlen(buf)+1) );
  vorbis_comment_add( vc, buf );

  return 1;
}


float bitrateToQuality( long bitrate )
{
  long br[10] = {
    65, 85, 100, 110, 130, 170, 210, 250, 290, 390
  };
  int i;
  for ( i = 0; i < 10; i++ ) {
    if ( bitrate < br[i] )
      return (float)i/10.0f;
  }
  return 1.0;
}