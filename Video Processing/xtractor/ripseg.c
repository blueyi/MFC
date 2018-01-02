/*
 * ripseg.c - Copyright (C) 2000 Jay A. Key
 *
 * Code to handle ripping absolute segments.
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
#include "trackwnd.h"
#include "resources.h"
#include "globals.h"
#include "rangeslider.h"


typedef struct {
  TOC toc;
  LPADDTRACK addTrack;
} RSDWINDOW, FAR *LPRSDWINDOW;

BOOL RipTrackSegmentDlgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

BOOL CALLBACK RipSegmentDlgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
void InitializeSliders( HWND hWnd );
void MSB2DWORD( DWORD *d, BYTE *b );
char *scrollString( int nCode );
int InitRangeSliderClass( void );
BOOL ripsegHandleSliderNotify( HWND hWnd, LPARAM lParam );
char *ripsegGenAddressString( HWND hWnd, DWORD addr, char *buf, int len );
char *ripsegGenLenString( HWND hWnd, DWORD addr, char *buf, int len );
BOOL ripsegSaveValues( HWND hWnd );
void ripsegSetAddressText( HWND hWnd, DWORD addr, BOOL bStart );


static BOOL bInitClass = FALSE;
static int segno = 0;


BOOL RipTrackSegment( HWND hParent, HWND hTrckWnd )
{
  ADDTRACK addTrack;

  if ( !bInitClass && !InitRangeSliderClass( ) )
    return FALSE;
  bInitClass = TRUE;

  if ( DialogBoxParam( ghInstance, "RipSegmentDialog", hParent, (DLGPROC)RipSegmentDlgProc, (LPARAM)&addTrack ) )
    {
      DialogBoxParam( ghInstance, "RipTrackDialog", hParent, (DLGPROC)RipTrackSegmentDlgProc, (LPARAM)&addTrack );
    }

  return TRUE;
}


BOOL CALLBACK RipSegmentDlgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
  NMHDR *l;
  LPRSDWINDOW lpw;

  switch( uMsg )
    {
    case WM_INITDIALOG:
      lpw = (LPRSDWINDOW)GlobalAlloc( GPTR, sizeof(RSDWINDOW) );
      lpw->addTrack = (LPADDTRACK)lParam;
      SetWindowLong( hWnd, GWL_USERDATA, (LONG)lpw );
      // set values for ID_STARTSLIDER and ID_ENDSLIDER
      InitializeSliders( hWnd );
      break;

    case WM_DESTROY:
      l = (NMHDR *)GetWindowLong( hWnd, GWL_USERDATA );
      if ( l )
	GlobalFree( (HGLOBAL)l );
      break;

    case WM_COMMAND:
      switch( LOWORD(wParam) )
	{
	case IDE_START:
	  if ( HIWORD(wParam) == EN_KILLFOCUS )
	    {
	      DWORD d;
	      d = GetDlgItemInt( hWnd, IDE_START, NULL, FALSE );
	      SendDlgItemMessage( hWnd, ID_SLIDER, RSB_SETSTART, TRUE, d );
	      ripsegSetAddressText( hWnd, d, TRUE );
	    }
	  break;

	case IDE_FINISH:
	  if ( HIWORD(wParam) == EN_KILLFOCUS )
	    {
	      DWORD d;
	      d = GetDlgItemInt( hWnd, IDE_FINISH, NULL, FALSE );
	      SendDlgItemMessage( hWnd, ID_SLIDER, RSB_SETFINISH, TRUE, d );
	      ripsegSetAddressText( hWnd, d, FALSE );
	    }
	  break;

	case IDCANCEL:
	case IDBN_RIPSEGCANCEL:
	  EndDialog( hWnd, 0 );
	  break;
	case IDBN_RIPSEGOK:
	  if ( ripsegSaveValues( hWnd ) )
	    EndDialog( hWnd, 1 );
	  break;
	}
      break;

    case WM_NOTIFY:
      l = (NMHDR *)lParam;
      if ( l->idFrom == ID_SLIDER )
	return ripsegHandleSliderNotify( hWnd, lParam );

    default:
      return FALSE;
    }

  return TRUE;
}



/*
 * Sets the initial range and positions of the sliders based on the CD which
 * is in the drive
 */
void InitializeSliders( HWND hWnd )
{
  LPTOC toc;
  LPRSDWINDOW lpw;
  BOOL bMSF;
  DWORD dwAddr, dwLen;
  BYTE i;
  char buf[128];

  lpw = (LPRSDWINDOW)GetWindowLong( hWnd, GWL_USERDATA );
  toc = &lpw->toc;

  bMSF = QueryCDParms( hCD, CDP_MSF, NULL );
  ModifyCDParms( hCD, CDP_MSF, (DWORD)FALSE );

  ReadTOC( hCD, toc );
  ModifyCDParms( hCD, CDP_MSF, (DWORD)bMSF );

  if ( toc->firstTrack == toc->lastTrack )
    return;

  MSB2DWORD( &dwAddr, toc->tracks[0].addr );
  SendDlgItemMessage( hWnd, ID_SLIDER, RSB_SETMIN, 0, dwAddr );
  SendDlgItemMessage( hWnd, ID_SLIDER, RSB_SETTIC, 0, dwAddr );

  MSB2DWORD( &dwAddr, toc->tracks[toc->lastTrack - toc->firstTrack+1].addr );
  SendDlgItemMessage( hWnd, ID_SLIDER, RSB_SETMAX, 0, dwAddr );
  SendDlgItemMessage( hWnd, ID_SLIDER, RSB_SETTIC, 0, dwAddr );

  for( i = toc->firstTrack + 1; i <= toc->lastTrack; i++ )
    {
      MSB2DWORD( &dwAddr, toc->tracks[i-toc->firstTrack].addr );
      SendDlgItemMessage( hWnd, ID_SLIDER, RSB_SETTIC, FALSE,
			  dwAddr );
    }

  dwLen = dwAddr = SendDlgItemMessage( hWnd, ID_SLIDER, RSB_GETMIN, 0, 0L );
  SendDlgItemMessage( hWnd, ID_SLIDER, RSB_SETSTART, 0, dwAddr );
  dwAddr = SendDlgItemMessage( hWnd, ID_SLIDER, RSB_GETMAX, 0, 0L );
  SendDlgItemMessage( hWnd, ID_SLIDER, RSB_SETFINISH, 0, dwAddr );
  dwLen = dwAddr - dwLen;

  ripsegGenLenString( hWnd, dwLen, buf, 128 );
  SetDlgItemText( hWnd, IDT_TRACKLEN, buf );

  dwAddr = SendDlgItemMessage( hWnd, ID_SLIDER, RSB_GETSTART, 0, 0L );
  ripsegSetAddressText( hWnd, dwAddr, TRUE );
  SetDlgItemInt( hWnd, IDE_START, dwAddr, FALSE );

  dwAddr = SendDlgItemMessage( hWnd, ID_SLIDER, RSB_GETFINISH, 0, 0L );
  ripsegSetAddressText( hWnd, dwAddr, FALSE );
  SetDlgItemInt( hWnd, IDE_FINISH, dwAddr, FALSE );

  wsprintf( buf, "Custom Segment %d", ++segno );
  SetDlgItemText( hWnd, IDE_SEGMENTFNAME, buf );
  SetFocus( GetDlgItem( hWnd, ID_SLIDER ) );
}


void ripsegSetAddressText( HWND hWnd, DWORD addr, BOOL bStart )
{
  char buf[128];
  DWORD dwStart, dwFinish;

  ripsegGenAddressString( hWnd, addr, buf, 128 );
  if ( bStart )
    SetDlgItemText( hWnd, IDT_STARTTEXT, buf );
  else
    SetDlgItemText( hWnd, IDT_FINISHTEXT, buf );

  dwStart = GetDlgItemInt( hWnd, IDE_START, NULL, FALSE );
  dwFinish = GetDlgItemInt( hWnd, IDE_FINISH, NULL, FALSE );

  ripsegGenLenString( hWnd, dwFinish - dwStart, buf, 128 );
  SetDlgItemText( hWnd, IDT_TRACKLEN, buf );
}



BOOL ripsegHandleSliderNotify( HWND hWnd, LPARAM lParam )
{
  LPRSBNOTIFY l = (LPRSBNOTIFY)lParam;
  char buf[128];

  switch( l->hdr.code )
    {
    case RSBN_STARTCHANGING:
      // sent whenever the top slider is moving, but before updated
      if ( l->newStart < l->finish )
	{
	  ripsegGenAddressString( hWnd, l->newStart, buf, 128 );
	  SetDlgItemText( hWnd, IDT_STARTTEXT, buf );
	  ripsegGenLenString( hWnd, l->finish - l->newStart, buf, 128 );
	  SetDlgItemText( hWnd, IDT_TRACKLEN, buf );
	  SetWindowLong( hWnd, DWL_MSGRESULT, TRUE ); // allow the change
	}
      else
	{
	  ripsegGenAddressString( hWnd, l->start, buf, 128 );
	  SetDlgItemText( hWnd, IDT_STARTTEXT, buf );
	  ripsegGenLenString( hWnd, l->finish - l->start, buf, 128 );
	  SetDlgItemText( hWnd, IDT_TRACKLEN, buf );
	  SetWindowLong( hWnd, DWL_MSGRESULT, FALSE ); // disallow the change
	}
      break;

    case RSBN_STARTCHANGED:
      // sent after the top slider has moved and been updated
      ripsegGenAddressString( hWnd, l->start, buf, 128 );
      SetDlgItemText( hWnd, IDT_STARTTEXT, buf );
      SetDlgItemInt( hWnd, IDE_START, l->start, FALSE );
      ripsegGenLenString( hWnd, l->finish - l->start, buf, 128 );
      SetDlgItemText( hWnd, IDT_TRACKLEN, buf );
      break;

    case RSBN_FINISHCHANGING:
      // sent whenever the bottom slider is moving, but before updated
      if ( l->newFinish > l->start )
	{
	  ripsegGenAddressString( hWnd, l->newFinish, buf, 128 );
	  SetDlgItemText( hWnd, IDT_FINISHTEXT, buf );
	  ripsegGenLenString( hWnd, l->newFinish - l->start, buf, 128 );
	  SetDlgItemText( hWnd, IDT_TRACKLEN, buf );
	  SetWindowLong( hWnd, DWL_MSGRESULT, TRUE ); // allow the change
	}
      else
	{
	  ripsegGenAddressString( hWnd, l->finish, buf, 128 );
	  SetDlgItemText( hWnd, IDT_FINISHTEXT, buf );
	  ripsegGenLenString( hWnd, l->finish - l->start, buf, 128 );
	  SetDlgItemText( hWnd, IDT_TRACKLEN, buf );
	  SetWindowLong( hWnd, DWL_MSGRESULT, FALSE ); // disallow the change
	}
      break;

    case RSBN_FINISHCHANGED:
      // sent after the bottom slider has moved and been updated
      ripsegGenAddressString( hWnd, l->finish, buf, 128 );
      SetDlgItemText( hWnd, IDT_FINISHTEXT, buf );
      SetDlgItemInt( hWnd, IDE_FINISH, l->finish, FALSE );
      ripsegGenLenString( hWnd, l->finish - l->start, buf, 128 );
      SetDlgItemText( hWnd, IDT_TRACKLEN, buf );
      break;

    default:
      return FALSE;
    }

  return TRUE;
}


char *ripsegGenAddressString( HWND hWnd, DWORD addr, char *buf, int len )
{
  BYTE i, num;
  LPTOC t;
  LPRSDWINDOW lpw;
  DWORD ofs, addr1, addr2;
  DWORD m, s, f;
  char tmp[128];

  if ( !buf )
    return NULL;

  ZeroMemory( buf, len );

  lpw = (LPRSDWINDOW)GetWindowLong( hWnd, GWL_USERDATA );

  t = &lpw->toc;
  num = t->lastTrack - t->firstTrack + 1;
  for( i = 0; i < num; i++ )
    {
      MSB2DWORD( &addr1, t->tracks[i].addr );;
      MSB2DWORD( &addr2, t->tracks[i+1].addr );;
      if ( (addr >= addr1) && (addr < addr2) )
	{
	  ofs = addr - addr1;
	  f = ofs % 75;
	  ofs /= 75;
	  s = ofs % 60;
	  m = ofs / 60;
	  wsprintf( tmp, "Track %d: %02d:%02d:%02d (%d)",
		    i+1, m, s, f, addr );
	  lstrcpyn( buf, tmp, len-1 );
	  return buf;
	}
    }

  return buf;
}


char *ripsegGenLenString( HWND hWnd, DWORD addr, char *buf, int len )
{
  DWORD m, s, f, dwLen;
  char tmp[128];

  if ( !buf )
    return NULL;

  ZeroMemory( buf, len );

  dwLen = addr;

  if ( (int)addr < 0 )
    addr = 0;

  f = addr % 75;
  addr /= 75;
  s = addr % 60;
  m = addr / 60;
  wsprintf( tmp, "%d frames (%02d:%02d:%02d)", dwLen, m, s, f );
  lstrcpyn( buf, tmp, len-1 );

  return buf;
}



BOOL ripsegSaveValues( HWND hWnd )
{
  DWORD dwStart, dwEnd;
  char buf[MAX_PATH+1];
  LPRSDWINDOW lpw;
  BOOL bOK;

  lpw = (LPRSDWINDOW)GetWindowLong( hWnd, GWL_USERDATA );

  dwStart = GetDlgItemInt( hWnd, IDE_START, &bOK, FALSE );
  dwEnd = GetDlgItemInt( hWnd, IDE_FINISH, &bOK, FALSE );
  GetDlgItemText( hWnd, IDE_SEGMENTFNAME, buf, MAX_PATH );

  if ( dwStart >= dwEnd )
    {
      MessageBox( hWnd, "The start frame must be less than the end frame.  Please correct and try again.", "Huh?!?", MB_APPLMODAL | MB_ICONERROR | MB_OK );      return FALSE;
    }

  if ( buf[0] == '\0' )
    {
      MessageBox( hWnd, "Please enter the output filename for the segment to be ripped.", "Huh?!?", MB_APPLMODAL | MB_ICONERROR | MB_OK );
      return FALSE;
    }

  lpw->addTrack->start = dwStart;
  lpw->addTrack->len = dwEnd - dwStart;
  lpw->addTrack->bComplete = FALSE;
  if ( !lstrlen( buf ) )
    wsprintf( buf, "Custom Segment %d", ++segno );
  lstrcpy( lpw->addTrack->name, buf );

  return TRUE;
}
