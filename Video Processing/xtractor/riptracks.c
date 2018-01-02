/*
 * riptracks.c - Copyright (C) 1999,2000 Jay A. Key
 *
 * Contains the RipTrack() function.  The rip dialog proc, plus the
 * read and encode threads are all contained in this file.  The read 
 * thread is also responsible for jitter correction.  A good example of 
 * how to rip a track from a CD via AKRip32.dll
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
#include <time.h>
#include <malloc.h>
#include <math.h>
#include "akrip/akrip32.h"
#include "resources.h"
#include "globals.h"
#include "riptracks.h"
#include "trackwnd.h"
#include "gauge.h"
#include "id3.h"
#include "enc/xtenc.h"
#include "threads.h"

DWORD RipThread( LPENCODETHREAD pet );
DWORD EncodeThread( LPENCODETHREAD pet );
LPTRACKBUF newTrackBuf( DWORD numFrames );
void RipTrack( HWND hDlg, int idx, LPADDTRACK lpAddTrack, BOOL bWritePlaylist );
int writeAndFlush( FILE *fp, BYTE *buf, int len );
void writeWavHeader( FILE *fp, DWORD len );
BOOL loadBladeEnc( void );
void setRipTrackStatus( LPENCODETHREAD e );
BOOL LoadEncoderFunctions( ENCODER nEncoder );
void UpdateTime (long numWritten);
BOOL isOldLameEnc( void );
void TransmogrifyTrackName( ADDTRACK *t, char *szFname, int len, char *szDir, int dirlen );
FILE *OpenPlaylist( HWND hWnd );
void WritePlaylistEntry( FILE *fp, ADDTRACK *t, char *szFilename );
int AskOverwrite( HWND hWnd );
double readTrackLevel( LPENCODETHREAD pet, double skipRatio );
void normalize( BYTE *p, DWORD numBytes, double dNormFactor );
void dbprintf( char *fmt, ... );
DWORD maxBufferSize( DWORD trackLen, DWORD minFrames );
void GenerateNameFromMacro( ADDTRACK *t, char *szMangle, char *szFname, int len );

static ENCODETHREAD e;
static ADDTRACK rtAddTrack;
//static BOOL bSecond = FALSE;
static FILE *fpPlaylist;

//static int iEnc = XT_ENC_BLADE;

/*
 * 1. initializes the common data structure
 * 2. starts the threads
 * 
 * 
 */
void RipTrack( HWND hDlg, int idx, LPADDTRACK lpAddTrack, BOOL bWritePlaylist )
{
  DWORD dwRipThreadID, dwEncThreadID;
  static DWORD numBufFrames = 12;
  static char outputName[MAX_PATH+1];
  static char outputPath[MAX_PATH+1];

  dwRipThreadID = dwEncThreadID = 0;  // eliminate spurious warning in gcc

  ZeroMemory( &e, sizeof(e) );

  e.idx = idx;

  time( &e.tstart );

  e.hDlg = hDlg;

  e.hEnc = xtGetEncoder( iEncoder );

  ModifyCDParms( hCD, CDP_OVERLAP, numOverlap );
  ModifyCDParms( hCD, CDP_JITTER, jitterCheck );
  ModifyCDParms( hCD, CDP_READMODE, readMode );

  e.startFrame = lpAddTrack->start;
  e.trackLen = lpAddTrack->len;
  e.endFrame = e.startFrame + e.trackLen;

  InitializeCriticalSection( &e.cs );

  e.hRipCancel = CreateEvent( NULL, FALSE, FALSE, NULL );

  SendDlgItemMessage( hDlg, IDG_RIPPROG, GM_SETRANGE,
		      (WPARAM)((UINT)e.trackLen * 2352),
		      0L );
  SendDlgItemMessage( hDlg, IDG_RIPPROG, GM_SETPOS, 0, 0L );

//  wrqInitQueue( &e.q, maxRip * 2352 * numBufFrames );
//  wrqInitQueue( &e.q, 2352 * (e.endFrame - e.startFrame + 1) );
  e.queueSize = maxBufferSize( (e.endFrame - e.startFrame + 1),
                               maxRip * numBufFrames );
  if ( (e.queueSize == (e.endFrame - e.startFrame + 1)) 
        && (iNormalizeScanPercent = 100) )
    e.bRip2Memory = TRUE;
  else
    e.bRip2Memory = FALSE;
  wrqInitQueue( &e.q, e.queueSize );

  SendDlgItemMessage( hDlg, IDG_READBUF, GM_DISPPCT, (WPARAM)FALSE, 0L );
  SendDlgItemMessage( hDlg, IDG_READBUF, GM_SETRANGE,
		      (WPARAM)wrqFreeSpace( &e.q ), 0L );

  // Set ID3 info for track.
  xtSetAsciiOption( e.hEnc, XT_OPT_TRACK, lpAddTrack->name );
  xtSetAsciiOption( e.hEnc, XT_OPT_ALBUM, szAlbumTitle );
  xtSetAsciiOption( e.hEnc, XT_OPT_ARTIST, szArtistName );
  if ( asGetID3IntInfo( ID3_GENRE ) != -1 )
    xtSetIntOption( e.hEnc, XT_OPT_ID3GENRE, asGetID3IntInfo( ID3_GENRE ) );
  xtSetAsciiOption( e.hEnc, XT_OPT_ID3YEAR, asGetID3AsciiInfo( ID3_YEAR ) );

  if ( !bID3 )
    xtSetIntOption( e.hEnc, XT_OPT_ID3LEVEL, 0 );
  else
    xtSetIntOption( e.hEnc, XT_OPT_ID3LEVEL, 1 );

  xtSetIntOption( e.hEnc, XT_OPT_CBITRATE, wBitrate );
  xtSetIntOption( e.hEnc, XT_OPT_MAXBITRATE, wMaxBitrate );
  xtSetIntOption( e.hEnc, XT_OPT_NOMINALBITRATE, wVorbBitrate );
  xtSetIntOption( e.hEnc, XT_OPT_MP3MODE, wMode );
  xtSetIntOption( e.hEnc, XT_OPT_ORIGINAL, bOriginal );
  xtSetIntOption( e.hEnc, XT_OPT_CRC, bCRC );
  xtSetIntOption( e.hEnc, XT_OPT_COPYRIGHT, bCopyright );
  xtSetIntOption( e.hEnc, XT_OPT_PRIVATE, bPrivate );
  xtSetIntOption( e.hEnc, XT_OPT_MPEGQUALITY, nQuality );
  xtSetIntOption( e.hEnc, XT_OPT_MPEGVERSION, MPEG1 );
  xtSetIntOption( e.hEnc, XT_OPT_ENABLEVBR, bVBR );
  xtSetIntOption( e.hEnc, XT_OPT_VBRQUALITY, nVBRQuality );
  xtSetIntOption( e.hEnc, XT_OPT_TRACKNUM, lpAddTrack->trackNo );

#ifdef _NO_WRITE_OUTPUT
  xtSetIntOption( e.hEnc, XT_OPT_NOWRITE, 1 );
#endif

  wsprintf( outputName, "%s", lpAddTrack->name );
  SetDlgItemText( hDlg, IDT_TRACKNAME, outputName );
  if ( lpAddTrack->bComplete )
    TransmogrifyTrackName( lpAddTrack, outputName, MAX_PATH+1, outputPath, MAX_PATH+1 );

  xtSetAsciiOption( e.hEnc, XT_OPT_BASEDIR, szMP3OutputDir );
  xtSetAsciiOption( e.hEnc, XT_OPT_FILENAME, outputName );
  xtSetAsciiOption( e.hEnc, XT_OPT_FILEDIR, outputPath );
  
  xtSetIntOption( e.hEnc, XT_OPT_LAME_MODE, wLameMode );
  
  
  if ( xtCheckOutputFileExists( e.hEnc ) )
    {
      int mbretval;
      mbretval = MessageBox( hDlg, "The output file already exists.  Click OK to overwrite the file, or Cancel to quit.", "Overwrite?", MB_OKCANCEL | MB_ICONWARNING | MB_APPLMODAL );
      if ( mbretval == IDCANCEL ) 
        {
          // abort
          SendMessage( hDlg, WM_CANCELRIP, 0, 0 );
          return;
        }
    }
  
  if ( !xtOpenOutputFile( e.hEnc ) )
  {
    MessageBox( hDlg, "The output file could not be opened!", "Error", MB_OK | MB_ICONWARNING | MB_APPLMODAL );
    SendMessage( hDlg, WM_CANCELRIP, 0, 0 );
    return;
  }


  if ( bWritePlaylist )
    {
      static char szFullFileName[MAX_PATH+1];
      xtGetOutputFileName( e.hEnc, szFullFileName, MAX_PATH+1 );
      WritePlaylistEntry( fpPlaylist, lpAddTrack , szFullFileName );
      fflush( fpPlaylist );
      
      lstrcat( outputName, "." );
      lstrcat( outputName, xtGetExtension( e.hEnc ) );
    }

  e.maxbufread = 4096;
  switch( iEncoder )
    {
    case XT_ENC_RAW:
      //e.maxbufread = 2352;
      wsprintf( outputName, "Raw data" );
      break;

    case XT_ENC_LAME1:
      wsprintf( outputName, "%d kbps MP3 via Lame_Enc DLL", wBitrate );
      break;

    case XT_ENC_LAME2:
      wsprintf( outputName, "%d kbps MP3 via Lame_Enc DLL", wBitrate );
      if ( bVBR )
	wsprintf( outputName + lstrlen( outputName ),
		  ", VBR max bitrate %d, VBR quality %d",
		  wMaxBitrate, nVBRQuality );
      break;

    case XT_ENC_BLADE:
      wsprintf( outputName, "%d kbps MP3 via BladeEnc DLL", wBitrate );
      break;

    case XT_ENC_WAV:
      //e.maxbufread = 2352;
      wsprintf( outputName, "WAV file" );
      break;

    case XT_ENC_VORBIS:
      wsprintf( outputName, "Ogg Vorbis via Vorb_Enc DLL" );
      break;
    }

  SetDlgItemText( hDlg, IDT_OUTPUTOPTTEXT, outputName );

  e.aHandles[RIPTHREAD] = CREATETHREAD( NULL, 0, (LPTHREAD_START_ROUTINE)RipThread,
				(LPVOID)&e, 0, &dwRipThreadID );
  e.aHandles[ENCTHREAD] = CREATETHREAD( NULL, 0, (LPTHREAD_START_ROUTINE)EncodeThread,
				(LPVOID)&e, 0, &dwEncThreadID );

  if ( bNiceThreads )
    {
      SetThreadPriority( e.aHandles[RIPTHREAD], THREAD_PRIORITY_IDLE );
      SetThreadPriority( e.aHandles[ENCTHREAD], THREAD_PRIORITY_IDLE );
    }
}


BOOL RipTrackDlgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
  WORD wID;
  //static BOOL bDone = FALSE;
  static HWND hTrckWnd = NULL;
  int idx = -1;

  switch( uMsg )
    {
    case WM_DESTROY:
      bRippingTracks = FALSE;
      EndDialog( hWnd, 0 );
      break;

    // called when the file exists and user cancels the rip
    case WM_CANCELRIP:
      DeleteCriticalSection( &e.cs );
      wrqDeinitQueue( &e.q );
      EndDialog( hWnd, 0 );
      break;

    case WM_TRACKDONE:
      DeleteCriticalSection( &e.cs );
      wrqDeinitQueue( &e.q );
      // set the status text for the last track ripped
      setRipTrackStatus( &e );
      // if more tracks to rip and the last one finished successfully,
      // call RipTrack again
      idx = SendMessage( hTrckWnd,WM_FINDNEXTTRACK,0,(LPARAM)&rtAddTrack);
      if ( (idx != -1) && (e.status == EST_SUCCESS) && !IsDlgButtonChecked( hWnd, IDCKB_FINISHTRACK ) )
	{
	  rtAddTrack.bComplete = TRUE;
	  rtAddTrack.trackNo = idx + 1;
	  RipTrack( hWnd, idx, &rtAddTrack, TRUE );
	}
      else
	{
	  bRippingTracks = FALSE;
	  if ( fpPlaylist )
	    fclose( fpPlaylist );
	  EndDialog( hWnd, 0 );
	}
      break;

    case WM_INITDIALOG:
      //bDone = FALSE;
      //bSecond = FALSE;
      fpPlaylist = NULL;
      if ( bWritePlaylist )
	{
	  fpPlaylist = OpenPlaylist( hWnd );
	  if ( !fpPlaylist )
	    {
	      EndDialog( hWnd, 0 );
	      break;
	    }
	}
      hTrckWnd = (HWND)lParam;
      bRippingTracks = TRUE;
      idx = SendMessage(hTrckWnd,WM_FINDFIRSTTRACK,0,
			       (LPARAM)&rtAddTrack);
      if ( idx != -1 )
	{
	  rtAddTrack.bComplete = TRUE;
	  rtAddTrack.trackNo = idx + 1;
	  RipTrack( hWnd, idx, &rtAddTrack, TRUE );
	}
      else
	{
	  MessageBox( GetParent(hTrckWnd), "No tracks selected", "Warning!",
		      MB_ICONEXCLAMATION | MB_OK );
	  bRippingTracks = FALSE;
	  EndDialog( hWnd, 0 );
	}
      break;

    case WM_COMMAND:
      wID = LOWORD( wParam );
      if ( wID == IDBN_CANCELRIP || wID == 2 )
	{
	  if ( /* bDone || */ (MessageBox( hWnd, "Really stop?", "Abort?", MB_APPLMODAL | MB_YESNO | MB_ICONEXCLAMATION ) == IDYES) )
	    {
	      e.bForceRipExit = TRUE;
	      e.bForceEncExit = TRUE;
	      e.status = EST_ABORTED;
	      SetEvent( e.hRipCancel );
	      EnableWindow( GetDlgItem( hWnd, IDBN_CANCELRIP ),FALSE );
	    }
	}
      return TRUE;
    }

  return FALSE;
}


BOOL RipTrackSegmentDlgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
  WORD wID;
  ADDTRACK *pAddTrack;

  switch( uMsg )
    {
    case WM_DESTROY:
      bRippingTracks = FALSE;
      EndDialog( hWnd, 0 );
      break;
    
    // called when the file exists and user cancels the rip
    case WM_CANCELRIP:
      DeleteCriticalSection( &e.cs );
      wrqDeinitQueue( &e.q );
      EndDialog( hWnd, 0 );
      break;

    case WM_TRACKDONE:
      DeleteCriticalSection( &e.cs );
      wrqDeinitQueue( &e.q );
      if ( e.status != EST_SUCCESS )
	{
	}
      bRippingTracks = FALSE;
      EndDialog( hWnd, 0 );
      break;

    case WM_INITDIALOG:
      bRippingTracks = TRUE;
      pAddTrack = (ADDTRACK *)lParam;
      pAddTrack->bComplete = FALSE;
      pAddTrack->trackNo = 0;
      RipTrack( hWnd, -1, (LPADDTRACK)lParam, FALSE );
      break;

    case WM_COMMAND:
      wID = LOWORD( wParam );
      if ( wID == IDBN_CANCELRIP || wID == 2 )
	{
	  if ( MessageBox( hWnd, "Really stop?", "Abort?", MB_APPLMODAL | MB_YESNO | MB_ICONEXCLAMATION ) == IDYES )
	    {
	      e.bForceRipExit = TRUE;
	      e.status = EST_ABORTED;
	      SetEvent( e.hRipCancel );
	      EnableWindow( GetDlgItem( hWnd, IDBN_CANCELRIP ),FALSE );
	    }
	}
      return TRUE;
    }

  return FALSE;
}


LPTRACKBUF newTrackBuf( DWORD numFrames )
{
  LPTRACKBUF t;
  int numAlloc;

  numAlloc = (((int)numFrames)*2352) + TRACKBUFEXTRA;

  t = (LPTRACKBUF)malloc( numAlloc );

  if ( !t )
    return NULL;

  t->startFrame = 0;
  t->numFrames = 0;
  t->maxLen = numFrames * 2352;
  t->len = 0;
  t->status = 0;
  t->startOffset = 0;

  return t;
}


#define _ALWAYS_READ_MAX
/*
 * Thread responsible for reading the data from the CD and placing it in
 * a queue for the encode thread.
 *
 * trying a new strategy -- always read the full maxRip frames, and truncate
 * if it's too many, but after the read.  Some of the SCSI read modes were
 * crapping out on the last read when I suddenly requested a different number
 * of frames.  To switch back to the old method, undefine _ALWAYS_READ_MAX
 *
 * CDRM_JITTERONERR uses two full-size TRACKBUFs on a rotating basis.  On the
 * read it uses t1, and then on the next read switches to t2.  If an error
 * is returned from the read function, then the buffer from the previous read
 * is used to jitter correct the current one.
 */
DWORD RipThread( LPENCODETHREAD pet )
{
  LPTRACKBUF tbuf, t1, t2, tover, tTmp;
  DWORD num2rip, dwStatus;
  HANDLE hWait[2];
  int retries;
  BOOL useT1 = FALSE;
  HWND hReadGauge;
  BOOL bWaited;
  double dRecLevel = 1.0;
  double dNormFactor = 1.0;
  //char buf[81];

  dwStatus = 0;

  hWait[0] = CreateEvent( NULL, FALSE, FALSE, NULL ); 
  hWait[1] = pet->hRipCancel;

  // initialize all buffers
  tbuf = t1 = t2 = tover = tTmp = NULL;

  tbuf = t1 = newTrackBuf( maxRip );
  switch ( readMode )
    {
    case CDRM_JITTER:
      tover = newTrackBuf( numOverlap );
      break;
    case CDRM_JITTERONERR:
      t2 = newTrackBuf( maxRip );
      break;
    default:
    case CDRM_NOJITTER:
      readMode = CDRM_NOJITTER;
      break;
    }

  num2rip = maxRip;

  hReadGauge = GetDlgItem( e.hDlg, IDG_READBUF );

  // should we attempt to normalize the extracted audio
  if ( bNormalize )
  {
    double dPct;
    char tmpbuf[40];
    GetDlgItemText( pet->hDlg, IDT_RIPPCT, tmpbuf, 40 );
    SetDlgItemText( pet->hDlg, IDT_RIPPCT, "Scan %:" );
    // determine the max record level for the track
    dRecLevel = readTrackLevel( pet, iNormalizeScanPercent / 100.0 );
    dPct = (double)iNormalizePercent / 100.0;
    // the normalize ratio must be between 0.1 and 1.0
    if ( dPct > 1.0 )
      dPct = 1.0;
    else if ( dPct < 0.0 )
      dPct = 0.1;
    dNormFactor = (32767.0 * dPct) / dRecLevel;
    SetDlgItemText( pet->hDlg, IDT_RIPPCT, tmpbuf );
  }

  while( TRUE )
    {
      bWaited = FALSE;
      
      if ( e.startFrame >= (e.endFrame - 1) )
      {
	break;
      }

      if ( e.bForceRipExit )
	{
	  e.bForceEncExit = TRUE;
	  goto asRipExit;
	}

      EnterCriticalSection( &e.cs );
      if ( e.endFrame - e.startFrame < maxRip )
	num2rip = e.endFrame - e.startFrame;
      LeaveCriticalSection( &e.cs );
      
      while( (DWORD)wrqFreeSpace( &e.q ) < 2352 * num2rip )
	{
	  DWORD waitSize;
	  waitSize = e.queueSize * 8 / 10;
	  bWaited = TRUE;
	  if ( e.bForceRipExit )
	    {
	      e.bForceEncExit = TRUE;
	      goto asRipExit;
	    }
	  ResetEvent( hWait[0] );
#if 0
	  dbprintf( "Setting wait to %ld", 2352 * maxRip * 10 );
	  wrqSetWait( &e.q, hWait[0], 2352 * maxRip * 10 );
	  WaitForMultipleObjects( 2, hWait, FALSE, 60000 );
	  dbprintf( "Done waiting..." );
#else
	  wrqSetWait( &e.q, hWait[0], waitSize );
	  WaitForMultipleObjects( 2, hWait, FALSE, 180000 );
#endif
	  if ( e.bForceRipExit )
	    {
	      e.bForceEncExit = TRUE;
	      goto asRipExit;
	    }
	}

      switch( readMode )
	{
	case CDRM_JITTER:
	  EnterCriticalSection( &e.cs );
	  tbuf->startFrame = e.startFrame;
	  LeaveCriticalSection( &e.cs );
#ifndef _ALWAYS_READ_MAX
	  tbuf->numFrames = num2rip;
#else
          if ( e.startFrame + maxRip > lastAudioFrame )
            tbuf->numFrames = lastAudioFrame - e.startFrame;
          else
            tbuf->numFrames = maxRip;
#endif
	  tbuf->startOffset = 0;
	  tbuf->len = 0;
	  for( dwStatus = SS_ERR, retries = 3; dwStatus != SS_COMP && retries; retries-- )
	    {
	      dwStatus = ReadCDAudioLBAEx( hCD, tbuf, tover );
	    }
	  break;

	case CDRM_JITTERONERR:
	  if ( useT1 )
	    {
	      tbuf = t1;
	      tTmp = t2;
	    }
	  else
	    {
	      tbuf = t2;
	      tTmp = t1;
	    }
	  EnterCriticalSection( &e.cs );
	  tbuf->startFrame = e.startFrame;
	  LeaveCriticalSection( &e.cs );

#ifndef _ALWAYS_READ_MAX
	  tbuf->numFrames = num2rip;
#else
          if ( e.startFrame + maxRip > lastAudioFrame )
            tbuf->numFrames = lastAudioFrame - e.startFrame;
          else
            tbuf->numFrames = maxRip;
#endif
	  tbuf->startOffset = 0;
	  tbuf->len = 0;

	  // try to force jitter correction after a wait
//	  if ( !bWaited )
//	    dwStatus = ReadCDAudioLBA( hCD, tbuf );
//	  else
//	    dwStatus = SS_ERR;
          dwStatus = ReadCDAudioLBA( hCD, tbuf );

	  // after an error or a wait, dwStatus will be SS_ERR
	  if ( dwStatus == SS_ERR )
	    {
	      if ( tTmp->len )
		{
		  tTmp->startOffset += ((tTmp->numFrames - jitterCheck)*2352);
		  tTmp->startFrame += ( tTmp->numFrames - jitterCheck );
		  tTmp->numFrames = jitterCheck;
		  tTmp->len = jitterCheck * 2352;
		}
	      else
		tTmp->len = tTmp->startOffset = tTmp->numFrames;

	      for( retries = 3; (dwStatus != SS_COMP) && retries; retries-- )
		{
		  dwStatus = ReadCDAudioLBAEx( hCD, tbuf, tTmp );
		}
	    }
	  useT1 = !useT1;
	  break;

	case CDRM_NOJITTER:
	  EnterCriticalSection( &e.cs );
	  tbuf->startFrame = e.startFrame;
	  LeaveCriticalSection( &e.cs );

	  tbuf->numFrames = num2rip;
	  tbuf->startOffset = 0;
	  tbuf->len = 0;

	  for( retries = 3, dwStatus = SS_ERR; (dwStatus != SS_COMP) && retries; retries -- )
	    dwStatus = ReadCDAudioLBA( hCD, tbuf );
	  break;
	}

      if ( dwStatus != SS_COMP )
	{
	  // display the error here
          e.status = EST_ERROR;
	  e.bForceEncExit = TRUE;
	  goto asRipExit;
	}
      
#ifdef _ALWAYS_READ_MAX
      if ( (maxRip > num2rip) && (tbuf->numFrames > num2rip) )
	{
	  tbuf->numFrames = num2rip;
	  tbuf->len = tbuf->numFrames * 2352;
	}
#endif

      if ( bNormalize )
        normalize( tbuf->buf + tbuf->startOffset, tbuf->len, dNormFactor );
      wrqEnqueue( &e.q, tbuf->buf + tbuf->startOffset, tbuf->len );
#if 0
      SendDlgItemMessage( e.hDlg, IDG_READBUF, GM_SETPOS,
			  (WPARAM)wrqNumUsed( &e.q ), 0L );
#else
      PostMessage( hReadGauge, GM_SETPOS, (WPARAM)wrqNumUsed( &e.q ), 0L );
#endif
      EnterCriticalSection( &e.cs );
      e.startFrame += tbuf->numFrames;
      LeaveCriticalSection( &e.cs );
    }
  
  e.bNormalExit = TRUE;

  ResetEvent( hWait[0] );
  wrqSetWait( &e.q, hWait[0], e.q.dataLen - 500 );
  WaitForSingleObject( hWait[0], 5000 );

 asRipExit:
  if ( e.bForceRipExit && (WaitForSingleObject( e.aHandles[ENCTHREAD], 120000 ) == WAIT_TIMEOUT) )
    {
      e.bForceEncExit = TRUE;
      if ( WaitForSingleObject( e.aHandles[ENCTHREAD], 30000 ) == WAIT_TIMEOUT )
	{
	  TerminateThread( e.aHandles[ENCTHREAD], 0xDEADBEEF );
	}
    }

  free( t1 );
  if ( t2 )
    free( t2 );
  if ( tover )
    free( tover );

  time( &e.tnow );

  CloseHandle( hWait[0] );
//  CloseHandle( hWait[1] );

//  PostMessage( e.hDlg, WM_TRACKDONE, 0, 0L );

  return 0xDEADBEEF;
}


/*
 * modified to use the encoder interface -- much simpler code now, since
 * all WAV, MP3, Ogg specific code is in the encoder interface DLL
 */
#define MAXBUFREAD (4*1024)
DWORD EncodeThread( LPENCODETHREAD pet )
{
  DWORD numQueued;
  unsigned char *pBuf;

  UpdateTime( -1 );

  pBuf = (unsigned char *)malloc( pet->maxbufread );

  xtInit( pet->hEnc );
//  xtOpenOutputFile( pet->hEnc );

  while( TRUE )
    {
      unsigned char *pTmp;
 
      pTmp = pBuf;

      if ( pet->bForceEncExit )
      {
	break;
      }

      numQueued = wrqNumUsed( &pet->q );
      if ( !numQueued && pet->bNormalExit )
	break;

      if ( numQueued )
	{
	  DWORD num2dequeue = numQueued;
	  if ( num2dequeue > pet->maxbufread )
	    num2dequeue = pet->maxbufread;
	  num2dequeue = wrqDequeue( &pet->q, &pTmp, num2dequeue );
	  if ( num2dequeue )
	    xtEncode( pet->hEnc, pTmp, num2dequeue );
	  UpdateTime( num2dequeue );
	}
    }
      
  xtFlush( pet->hEnc );
  xtClose( pet->hEnc );

  if ( pBuf )
    free( pBuf );

  CloseHandle( pet->hRipCancel );
  PostMessage( pet->hDlg, WM_TRACKDONE, 0, 0L );
  
  return 0xDEADBEEF;
}


int writeAndFlush( FILE *fp, BYTE *buf, int len )
{
  static int wafNumWritten = 0;
  int retVal = 0;

  wafNumWritten += len;
  retVal = fwrite( buf, 1, len, fp );
  if ( wafNumWritten > 20480 )
    {
      fflush( fp );
      wafNumWritten = 0;
    }

  return retVal;
}


void writeWavHeader( FILE *fp, DWORD len )
{
  WAVHDR wav;

  if ( !fp )
    return;

  memcpy( wav.riff, "RIFF", 4 );
  wav.len = len + 44 - 8;
  memcpy( wav.cWavFmt, "WAVEfmt ", 8 );
  wav.dwHdrLen = 16;
  wav.wFormat = 1;
  wav.wNumChannels = 2;
  wav.dwSampleRate = 44100;
  wav.dwBytesPerSec = 44100*2*2;
  wav.wBlockAlign = 4;
  wav.wBitsPerSample = 16;
  memcpy( wav.cData, "data", 4 );
  wav.dwDataLen = len;
  fseek( fp, 0, SEEK_SET );

  fwrite( &wav, 1, sizeof(wav), fp );
}




/***************************************************************************/
/*                                                                         */
/* UpdateTime                                                              */
/*                                                                         */
/* Update the elapsed/remaining time field on the dialog.  If we're        */
/* supplied with negative bytes, we assume we're initialising our static   */
/* variables.                                                              */
/*                                                                         */
/* Written by B. Thompson, January 27, 2000                                */
/*                                                                         */
/* Modified by A. Key:                                                     */
/*                                                                         */
/* Now takes into account the normalization pass when displaying elapsed   */
/* time and in calculating estimated time left.                          */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
void UpdateTime (long numWritten)
{
  static
  time_t   startTime = 0;              /* Start time stamp                 */
  static
  DWORD    totalWritten = 0;           /* Total bytes written              */
  static
  DWORD    timeLeft = 0;               /* Time remaining                   */
  static
  DWORD    numToWrite;                 /* Total number to be written       */
  static
  HWND     hRipGauge, hReadGauge;      /* Dialog controls                  */

  time_t   currTime;                   /* Current time stamp               */
  long     secsElapsed;                /* Elapsed seconds since last hour  */
  long     secsLeft;                   /* Remaining seconds since last hour*/
  char     estTime[24];                /* Estimated time                   */
  static DWORD startTick = 0;
  static double dx, dt;

  time(&currTime);

  if (numWritten < 0)
    {                                                     /* Initialisation*/
      time(&startTime);
      totalWritten = 0;
      numToWrite = e.trackLen * 2352;
      hRipGauge = GetDlgItem(e.hDlg, IDG_RIPPROG);
      hReadGauge = GetDlgItem(e.hDlg, IDG_READBUF);
      startTick = 0;
      SetDlgItemText(e.hDlg, IDT_ESTTIME, "Normalization pass...");
      PostMessage( hReadGauge, GM_SETPOS, 0, 0L );
      return;
    }                                                             /* End if*/
    
  if ( startTick == 0 )
    startTick = GetTickCount();
    
  totalWritten += numWritten;
  if (!totalWritten)
    return;                                        /* Avoid divide by zero!*/

  dt = (double)(GetTickCount() - startTick);
  dx = (double)totalWritten;
//  dbprintf( "hist[%d]: %f %f", MAXHIST-1, hist[MAXHIST-1].t, hist[MAXHIST-1].x );

  /* wait until we have enough data to compute the time left */
  if ( dt < 1000.0 )
    return;

  currTime -= startTime;                          /* Elapsed time (seconds)*/
  if (currTime != (time_t)timeLeft)
    {                                        /* At least one second elapsed*/
#if 0
      timeLeftd = currTime;
      timeLeftd *= numToWrite;
      timeLeftd /= totalWritten;
      timeLeftd -= currTime;

      timeLeft = (DWORD)timeLeftd;
#else
      if ( dx != 0 )
        timeLeft = (DWORD)(((double)(numToWrite - totalWritten) * dt) / dx);
      else
        timeLeft = 100000;
      timeLeft /= 1000;  // adjust for milliseconds
#endif
      secsElapsed = currTime % 3600;
      secsLeft = (long)(timeLeft % 3600);
//    sprintf(estTime, "%i %i", totalWritten, numToWrite);
      sprintf(estTime, "%li:%02li:%02li (%ld:%02ld:%02ld)",
              currTime / 3600, secsElapsed / 60, secsElapsed % 60,
              timeLeft / 3600, secsLeft / 60, secsLeft % 60);
      SetDlgItemText(e.hDlg, IDT_ESTTIME, estTime);
    }                                                             /* End if*/
    timeLeft = currTime;                              /* For next iteration*/
    
    PostMessage( hRipGauge, GM_SETDELTAPOS, (WPARAM)((UINT)numWritten), 0L );
    PostMessage( hReadGauge, GM_SETPOS, (WPARAM)wrqNumUsed( &e.q ), 0L );
}                                             /* End of UpdateTime function*/


/*
 * GenerateNameFromMacro
 *   Applies the file-naming macro to the info in the ADDTRACK struct
 */
void GenerateNameFromMacro( ADDTRACK *t, char *szMangle, char *szFname, int len )
{
  char *p;
  int state;

  if ( !t || !szFname || (len<=0) )
    return;

  p = szMangle;
  state = 0;
  while( *p && len>0 )
    {
      switch( state )
	{
	case 0:  // normal (start) state
	  if ( *p == '$' )
	    {
	      state = 1;
	      break;
	    }
	  *szFname++ = *p;
	  len--;
	  break;

	case 1:  // we just read a '$'
	  switch( *p )
	    {
	    case '$':
	      *szFname++ = '$';
	      len--;
	      break;
	    case 't':
	    case 'T':
	      // write track number
	      if ( t->trackNo != 0 )
		{
		  _snprintf( szFname, len, "%02d", t->trackNo );
		  //wsprintf( szFname, "%02d", t->trackNo );
		}
	      break;
	    case 'n':
	    case 'N':
	      _snprintf( szFname, len, "%s", t->name );
	      break;
	    case 'a':
	    case 'A':
	      // write artist name
	      _snprintf( szFname, len, "%s", szArtistName );
	      break;
	    case 'l':
	    case 'L':
	      // write album name
	      _snprintf( szFname, len, "%s", szAlbumTitle );
	      break;
	    }
	  state = 0;
	  break;
	}
      len -= lstrlen( szFname );
      szFname += lstrlen( szFname );
      p++;
    }
}

/*
 * TransmogrifyTrackName
 *   Responsible for applying track macros to generate the output filename.
 * If the string is empty, then a default name is applied.  Otherwise,
 * the string is used generate a filename based on information in the 
 * ADDTRACK structure.
 */
void TransmogrifyTrackName( ADDTRACK *t, char *szFname, int len, char *szDir, int dirlen )
{
  char *szTmpName;
  char *szTmpDir;
  char *szTmpMangleString;
  char *p, *q;
  
  szTmpMangleString = (char *)malloc( MAX_PATH + 1 );
  ZeroMemory( szTmpMangleString, MAX_PATH + 1 );
  if ( szMangleString[0] == '\0' )
    lstrcpy( szTmpMangleString, "Track $t" );
  else
    lstrcpyn( szTmpMangleString, szMangleString, MAX_PATH );

  szTmpName = (char *)malloc( MAX_PATH*2+1 );
  szTmpDir = (char *)malloc( MAX_PATH*2+1 );
  ZeroMemory( szTmpName, MAX_PATH*2+1 );
  ZeroMemory( szTmpDir, MAX_PATH*2+1 );
  
  // determine if there is a filename component in the macro
  // by finding the last backslash.  if there was a path
  // compenent, p will contain it, and q will have the filename.
  // otherwise, p will have the filename macro and q will be
  // NULL
  q = NULL;
  p = szTmpMangleString;
  for ( p += (lstrlen(p) - 1); p > szTmpMangleString; p-- )
  {
    if ( *p == '\\' )
    {
      *p = '\0';
      q = p + 1;
      p = szTmpMangleString + 1;
    }
  }
  
  if ( szMangleString[0] != '\0' )
    {
//      GenerateNameFromMacro( t, szTmpMangleString, szTmpName, MAX_PATH*2+1 );
      if ( q )
      {
        GenerateNameFromMacro( t, p, szTmpDir, MAX_PATH*2+1 );
        GenerateNameFromMacro( t, q, szTmpName, MAX_PATH*2+1 );
      }
      else
      {
        GenerateNameFromMacro( t, p, szTmpName, MAX_PATH*2+1 );
      }
    }
  else
    {
      *szDir = '\0';
      if ( t->name )
	lstrcpyn( szTmpName, t->name, MAX_PATH*2 );
      else
	wsprintf( szTmpName, "Track %d", t->trackNo );
    }

  ZeroMemory( szFname, len );
  ZeroMemory( szDir, dirlen );
  strncpy( szFname, szTmpName, len-1 );
  strncpy( szDir, szTmpDir, dirlen-1 );
  
  free( szTmpName );
  free( szTmpDir );
  free( szTmpMangleString );
}


FILE *OpenPlaylist( HWND hWnd )
{
  FILE *fpRetVal;
  char buf[MAX_PATH+1];
  char *pStartFilename;
  BOOL bExists = FALSE;
  int i;

  if ( bUseAlbumName )
    {
      lstrcpy( buf, szMP3OutputDir );
      if ( buf[lstrlen(buf)-1] != '\\' )
	lstrcat( buf, "\\" );
      pStartFilename = buf + lstrlen(buf);
      if ( lstrlen( szAlbumTitle ) > 0 )
	lstrcat( buf, szAlbumTitle );
      else
	lstrcat( buf, "Default Playlist" );
      lstrcat( buf, ".m3u" );
    }
  else
    {
      lstrcpy( buf, szPlaylist );
      pStartFilename = buf;
    }
  
  // replace invalid characters in filename
  for( i = 0; i < lstrlen( pStartFilename ); i++ )
    {
      unsigned char ch;
      ch = (unsigned char)pStartFilename[i];
      if ( !validFnameChar[ch] )
        pStartFilename[i] = '_';
    }

  fpRetVal = fopen( buf, "rt" );
  if ( fpRetVal )
    {
      bExists = TRUE;
      fclose( fpRetVal );
    }

  if ( !bExists )
    {
      fpRetVal = fopen( buf, "wt" );
      if ( fpRetVal )
	fprintf( fpRetVal, "#EXTM3U\n" );
      return fpRetVal;
    }

  switch( AskOverwrite( hWnd ) )
    {
    case IDYES:
      fpRetVal = fopen( buf, "wt" );
      if ( fpRetVal )
	fprintf( fpRetVal, "#EXTM3U\n" );
      break;
    case IDNO:
      fpRetVal = fopen( buf, "at" );
      break;
    default:
    case IDCANCEL:
      fpRetVal = NULL;
      break;
    }

  return fpRetVal;
}


void WritePlaylistEntry( FILE *fp, ADDTRACK *t, char *szFilename )
{
  if ( !fp || !t )
    return;

  fprintf( fp, "#EXTINF:%d,%s - %s\n", (int)(t->len / 75),
	   szArtistName,
	   t->name );
  fprintf( fp, "%s\n", szFilename );
}


int AskOverwrite( HWND hWnd )
{
  int i;

  i = MessageBox( hWnd,
		  "Warning - the playlist already exists.  To overwrite the existing playlist, select \"Yes\".  To append entries to the existing playlist, select \"No\".  To abort, select \"Cancel\"",
		  "Overwrite Playlist?",
		  MB_YESNOCANCEL | MB_ICONQUESTION | MB_APPLMODAL );
  return i;
}



/*
 * Scans the track to find the maximum level.  By setting the 
 * skipRatio, it is possible to scan only a certain percentage
 * of the frames.  For faster CD units, you should not skip
 * any frames.  Setting skipRatio:
 *    0.1   :  Will read 10% of frames (read one, skip nine)
 *    0.5   :  Will read 50% of frames (read one, skip one)
 *    1.0   :  Will read 100% of frames
 * skipRatio must be between 0.1 and 1.0 (inclusive).
 * If pet->bRip2Memory is used, then
 */
double readTrackLevel( LPENCODETHREAD pet, double skipRatio )
{
  LPTRACKBUF tbuf;
  DWORD num2rip, dwStatus, dwStartFrame, dwEndFrame;
  DWORD numRead = 0;
  int retries;
  DWORD i;
  HWND hRipGauge;
  BOOL bWaited;
  DWORD skip, skipped;
  short absMax = 0;
  WORD newRange;
  int oldRange;

  num2rip = maxRip;
  // adjust to get a value of 0.1, 0.2, ..., 0.9, 1.0
  if ( skipRatio <= 0.0 )
    skipRatio = 0.1;
  else if ( skipRatio > 1.0 )
    skipRatio = 1.0;
  else
    skipRatio = floor( skipRatio * 10.0 ) / 10.0;
  skip = (DWORD)(1.0/skipRatio) - 1;
  
  tbuf = newTrackBuf( maxRip );
  
  dwStartFrame = pet->startFrame;
  dwEndFrame = pet->endFrame;
  
  hRipGauge = GetDlgItem( pet->hDlg, IDG_RIPPROG );
  oldRange = SendMessage( hRipGauge, GM_GETRANGE, 0, 0 );
  newRange = (WORD)(dwEndFrame - dwStartFrame);
  SendMessage( hRipGauge, GM_SETRANGE, (WPARAM)newRange, 0L );
  SendMessage( hRipGauge, GM_SETPOS, 0, 0L );


  skipped = 0;
  while( TRUE )
    {
      bWaited = FALSE;
      
      if ( dwStartFrame >= (dwEndFrame - 1) )
	break;

      if ( pet->bForceRipExit )
	{
	  pet->bForceEncExit = TRUE;
	  goto asRipExit;
	}

      tbuf->startFrame = dwStartFrame;

      if ( (dwEndFrame - dwStartFrame) < num2rip )
        num2rip = dwEndFrame - dwStartFrame;
      tbuf->numFrames = num2rip;
      tbuf->startOffset = 0;
      tbuf->len = 0;

      if ( (skip != 0) && (skipped < skip) )
      {
        skipped++;
        continue;
      }
      else
      {
        skipped = 0;
        for( retries = 3, dwStatus = SS_ERR; (dwStatus != SS_COMP) && retries; retries -- )
          dwStatus = ReadCDAudioLBA( hCD, tbuf );

        if ( dwStatus != SS_COMP )
        {
          // display the error here
          e.status = EST_ERROR;
	  e.bForceEncExit = TRUE;
	  goto asRipExit;
	}
      
        // find max level in current block
        for( i = 0; i < tbuf->len; i += 2 )
        {
          short num;
          BYTE *p;
          p = &tbuf->buf[tbuf->startOffset + i];
          num = (short)((p[1]<<8) | (0x00ff&(short)p[0]));
          if ( abs(num) > absMax )
            absMax = abs(num);
        }
      }
      
      dwStartFrame += (skip + num2rip);
      numRead += (skip + num2rip);
      PostMessage( hRipGauge, GM_SETDELTAPOS, (WPARAM)(skip + num2rip), 0L );
    }
  
 asRipExit:
  free( tbuf );
    
  SendDlgItemMessage( pet->hDlg, IDG_RIPPROG, GM_SETRANGE,
		      (WPARAM)oldRange,
		      0L );
  SendDlgItemMessage( pet->hDlg, IDG_RIPPROG, GM_SETPOS, 0, 0L );
    
  return (double)absMax;
}


void normalize( BYTE *p, DWORD numBytes, double dNormFactor )
{
  DWORD i;
  for( i = 0; i < numBytes; i += 2 )
  {
    short n;
    n = (short)((p[i+1]<<8) | (0x00ff&(short)p[i]));
    n = (short)(n * dNormFactor);
    p[i+1] = (BYTE)(n>>8);
    p[i] = (BYTE)n;
  }
}


/*
 * Takes the trackLen (in 2352-byte frames), and examines 
 * available memory.  Returns the size that should be allocated
 * for the read-ahead buffer.  It will always return at least
 * enough to hold minFrames.
 */
DWORD maxBufferSize( DWORD trackLen, DWORD minFrames )
{
  MEMORYSTATUS memstat;
  DWORD desiredMem = trackLen * 2352;
  DWORD minMem = minFrames * 2352;
  
  ZeroMemory( &memstat, sizeof(memstat) );
  GlobalMemoryStatus( &memstat );
  dbprintf( "memory load: %ld", memstat.dwMemoryLoad );
  dbprintf( "avail. phys. memory: %ld", memstat.dwAvailPhys );
  dbprintf( "avail. virt. memory: %ld", memstat.dwAvailVirtual );
  if ( memstat.dwMemoryLoad >= 80 )
    return minFrames * 2352;
  
  if ( memstat.dwAvailPhys >= desiredMem )
    return desiredMem;
  
  if ( memstat.dwAvailVirtual >= desiredMem )
    return desiredMem / 2;
  
  desiredMem = memstat.dwAvailPhys / 2;
  return (minMem>desiredMem)?minMem:desiredMem;
}