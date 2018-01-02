/*
 * statusbar.c - Copyright (C) 1999,2000 Jay A. Key
 *
 * Routines to handle setting information on the application's status bar
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
#include <commctrl.h>
#include "globals.h"
#include "trackwnd.h"
#include "enc/xtenc.h"

void StatusSetMP3( void );

extern HWND hStatus;
extern HWND hTrackWnd;

void StatusSetMP3( void )
{
  switch( iEncoder )
    {
    case XT_ENC_RAW:
      SendMessage( hStatus, SB_SETTEXT, 0, (LPARAM)"Raw" );
      break;

    case XT_ENC_WAV:
      SendMessage( hStatus, SB_SETTEXT, 0, (LPARAM)"WAV" );
      break;

    case XT_ENC_LAME1:
    case XT_ENC_LAME2:
    case XT_ENC_BLADE:
      SendMessage( hStatus, SB_SETTEXT, 0, (LPARAM)"MP3" );
      break;

    case XT_ENC_VORBIS:
      SendMessage( hStatus, SB_SETTEXT, 0, (LPARAM)"Ogg" );
      break;

    default:
      break;
    }
}


void StatusSetNumSelected( void )
{
  int iNumChecked;
  int i, iNumTracks;
  char buf[81];
  ADDTRACK at;
  DWORD dwTotalTime = 0;
  DWORD h, m, s;

  iNumChecked = (int)SendMessage( hTrackWnd, WM_NUMCHECKED, 0, 0L );
  iNumTracks = (int)SendMessage( hTrackWnd, WM_NUMTRACKS, 0, 0L );
  for( i = 0; i < iNumTracks; i++ )
    {
      SendMessage( hTrackWnd, WM_GETTRACK, (WPARAM)i, (LPARAM)&at );
      if ( at.bChecked )
	dwTotalTime += at.len;
    }

  dwTotalTime /= 75;
  s = dwTotalTime % 60;
  dwTotalTime -= s;
  m = (dwTotalTime % 3600) / 60;
  dwTotalTime -= m * 60;
  h = dwTotalTime / 3600;

  if ( iNumChecked )
    wsprintf( buf, "%d selected, %02d:%02d:%02d total playing time", iNumChecked, h, m, s );
  else
    wsprintf( buf, "No tracks selected" );
  SendMessage( hStatus, SB_SETTEXT, 1, (LPARAM)buf );
}


void SetStatusMessage( char *szBuf )
{
  SendMessage( hStatus, SB_SETTEXT, 1, (LPARAM)szBuf );
}


/*
 * Generic function for updating the status bar
 */
void UpdateStatusBar( void )
{
  if ( !hStatus )
    return;

  StatusSetMP3();
  StatusSetNumSelected();
}
