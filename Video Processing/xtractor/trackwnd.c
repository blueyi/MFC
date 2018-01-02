/*
 * trackwnd.c - Copyright (C) 1999,2000 Jay A. Key
 *
 * Implementation of the TrackWnd window class.  TrackWnd is intended to
 * be a child window of the main application window, and supports the 
 * displaying, editing and selectind of CD audio tracks.  Includes a header
 * control for changing the width of the items displayed on screen.
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
#include <string.h>

#include "xtractor.h"
#include "resources.h"
#include "trackwnd.h"
#include "globals.h"
#include "statusbar.h"

typedef struct
{
  int iNum;
  int iMax;
  int iTextHeight;
  int vw, vh;
  int dx, dy;              // scroll bar offsets into virtual window
  int iHeaderHeight;
  int hx[5];               // header x offsets
  int hw[5];               // header widths
  int iFound;
  HWND hHeader;
  BOOL bVScroll, bHScroll;
  HFONT hFont;
  HPEN hBrownPen, hBlackPen;
  HPEN hDataTrackPen;
  int iSelected;
  ADDTRACK *tracks;
} TRACKWNDEXTRA, *LPTRACKWNDEXTRA;


LRESULT CALLBACK TrackWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
void doTrackWndPaint( HWND hWnd, LPTRACKWNDEXTRA lpe );
void RecalcWindow( HWND hWnd, LPTRACKWNDEXTRA lpe );
void DeleteTrack( HWND hWnd, int iTrack, LPTRACKWNDEXTRA lpe );
void HandleVScroll( HWND, int, int, LPTRACKWNDEXTRA );
void HandleHScroll( HWND, int, int, LPTRACKWNDEXTRA );
void ComputeHeaderPos( HWND hHdr, HWND hParent );
HWND createHeader( HWND hWnd, HINSTANCE hInst );
char *notifyString( UINT code );
BOOL handleHeaderNotify( HWND hWnd, LPARAM lParam, LPTRACKWNDEXTRA lpe );
BOOL HandleLMouseDown( HWND hWnd, LPTRACKWNDEXTRA lpe, LPARAM lParam );
BOOL HandleRMouseDown( HWND hWnd, LPTRACKWNDEXTRA lpe, LPARAM lParam );
int CheckBoxHit( LPTRACKWNDEXTRA lpe, LPARAM lParam );
BOOL HandleCheckTrack( HWND hWnd, LPTRACKWNDEXTRA lpe, int trackNo, BOOL bChecked );
BOOL HandleInvertCheck( HWND hWnd, LPTRACKWNDEXTRA lpe, int trackNo );
int doContextMenu( HWND hWnd, LPARAM lParam );
BOOL RenameSelectedTrack( HWND hWnd, LPTRACKWNDEXTRA lpe );
LRESULT processFindFirst( LPTRACKWNDEXTRA lpe, LPADDTRACK lpAddTrack );
LRESULT processFindNext( LPTRACKWNDEXTRA lpe, LPADDTRACK lpAddTrack );
void convertuMsg( UINT uMsg, char * s );
void logWindowsProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
LRESULT CALLBACK EditSubclassWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
void SetTrackWndText( HWND hWnd );
LRESULT numChecked( LPTRACKWNDEXTRA lpe );
int doTrackContextMenu( HWND hParent, HWND hChild, LPARAM lParam );
BOOL setTrackStatus( LPTRACKWNDEXTRA lpe, int idx, LPCSTR s );
#define DATATRACK      0
#define CHECKEDTRACK   1
#define UNCHECKEDTRACK 2
#define INVERTCHECK    0
#define SETCHECKED     1
#define SETUNCHECKED   2
int SetCheckBox( ADDTRACK *t, int val );
HDC GetDrawDC( HWND hWnd );
HBRUSH CreateTrackWndBrush( void );
HFONT CreateTrackWndFont( HDC hDC );


static char szTrackWndClass[] = "akripTrackWnd";
HWND hHeader;
static int iCtlId = 10000;
static BOOL bInEditTrack = FALSE;
static HWND hEdit = NULL;

int InitTrackWnd( HINSTANCE hInst )
{
  WNDCLASSEX wc;
  HBRUSH hBrush;

  hBrush = CreateTrackWndBrush();

  ZeroMemory( &wc, sizeof(wc) );
  wc.cbSize          = sizeof(wc);
  wc.style           = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc     = (WNDPROC)TrackWndProc;
  wc.hInstance       = hInst;
  wc.hCursor         = LoadCursor( NULL, IDC_ARROW );
  wc.hbrBackground   = hBrush;
  wc.lpszClassName   = szTrackWndClass;

  if ( !RegisterClassEx( &wc ) )
    return 0;

  return -1;
}


LRESULT CALLBACK TrackWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
  LPTRACKWNDEXTRA lpe;
  RECT rc;

  logWindowsProc( hWnd, uMsg, wParam, lParam );

  lpe = (LPTRACKWNDEXTRA)GetWindowLong( hWnd, GWL_USERDATA);
  if ( !lpe && ( uMsg != WM_CREATE ) )
    return DefWindowProc( hWnd, uMsg, wParam, lParam );

  switch( uMsg )
    {
    case WM_COMMAND:
      switch( HIWORD(wParam) )
        {
        case EN_SETFOCUS: break;
        case EN_KILLFOCUS: break;
        }
      break;

    case WM_CONTEXTMENU:
      doTrackContextMenu( GetParent(hWnd), hWnd, lParam );
      break;

    case WM_SETFOCUS:
      //OutputDebugString( "TrackWnd gaining focus" );
      break;

    case WM_KILLFOCUS:
      //OutputDebugString( "TrackWnd losing focus" );
      break;

    case WM_NOTIFY:
      if ( wParam == IDM_HEADER )
        return handleHeaderNotify( hWnd, lParam, lpe );
      break;

    case WM_DESTROY:
      lpe = (LPTRACKWNDEXTRA)GetWindowLong( hWnd, GWL_USERDATA );
      if ( lpe )
        {
	  if ( lpe->hFont )
	    DeleteObject( lpe->hFont );
          if ( lpe->tracks )
            GlobalFree( (HGLOBAL)lpe->tracks );
          if ( lpe->hBrownPen )
            DeleteObject( lpe->hBrownPen );
          if ( lpe->hBlackPen )
            DeleteObject( lpe->hBlackPen );
	  if ( lpe->hDataTrackPen )
	    DeleteObject( lpe->hDataTrackPen );
          GlobalFree( lpe );
        }
      return DefWindowProc( hWnd, uMsg, wParam, lParam );

    case WM_CREATE:
      lpe = (LPTRACKWNDEXTRA)GlobalAlloc( GPTR, sizeof(TRACKWNDEXTRA) );
      lpe->tracks = (LPADDTRACK)GlobalAlloc( GPTR, sizeof(ADDTRACK)*100 );
      lpe->iNum = 0;
      lpe->iMax = 100;
      lpe->hBrownPen = CreatePen( PS_SOLID, 1, 0x00003384 );
      lpe->hBlackPen = CreatePen( PS_SOLID, 1, 0x00000000 );
      lpe->hDataTrackPen = CreatePen( PS_SOLID, 1, 0x00121212 );
      lpe->iSelected = -1;
      lpe->iFound = -1;
      SetWindowLong( hWnd, GWL_USERDATA, (LONG)lpe );
      UpdateStatusBar();
      break;

    case WM_PAINT:
      doTrackWndPaint( hWnd, lpe );
      break;

    case WM_VSCROLL:
      HandleVScroll( hWnd, (int)LOWORD(wParam), (int)HIWORD(wParam), lpe );
      RecalcWindow( hWnd, lpe );
      GetClientRect( hWnd, &rc );
      rc.top += (lpe->iHeaderHeight+1);
      InvalidateRect( hWnd, &rc, TRUE );
      UpdateWindow( hWnd );
      break;

    case WM_HSCROLL:
      HandleHScroll( hWnd, (int)LOWORD(wParam), (int)HIWORD(wParam), lpe );
      RecalcWindow( hWnd, lpe );
      GetClientRect( hWnd, &rc );
      rc.top += (lpe->iHeaderHeight+1);
      InvalidateRect( hWnd, &rc, TRUE );
      UpdateWindow( hWnd );
      break;

    case WM_SIZE:
      RecalcWindow( hWnd, lpe );
      break;

    case WM_ADDTRACK:
      if ( lpe->iNum >= lpe->iMax )
        break;
      memcpy( &(lpe->tracks[lpe->iNum]), (void *)lParam, sizeof(ADDTRACK) );
      lpe->iNum++;
      RecalcWindow( hWnd, lpe );
      GetClientRect( hWnd, &rc );
      rc.top += (lpe->iHeaderHeight+1);
      InvalidateRect( hWnd, &rc, TRUE );
      UpdateWindow( hWnd );
      UpdateStatusBar();
      break;

    case WM_CHECKTRACK:
      if ( HandleCheckTrack( hWnd, lpe, (int)wParam, (BOOL)lParam ) )
        {
          GetClientRect( hWnd, &rc );
          rc.top += (lpe->iHeaderHeight+1);
          InvalidateRect( hWnd, &rc, TRUE );
          UpdateWindow( hWnd );
        }
      UpdateStatusBar();
      break;

    case WM_INVERTCHECK:
      if ( HandleInvertCheck( hWnd, lpe, (int)wParam ) )
        {
          GetClientRect( hWnd, &rc );
          rc.top += (lpe->iHeaderHeight+1);
          InvalidateRect( hWnd, &rc, TRUE );
          UpdateWindow( hWnd );
        }
      UpdateStatusBar();
      break;

    case WM_DELTRACK:
      DeleteTrack( hWnd, (int)wParam, lpe );
      RecalcWindow( hWnd, lpe );
      GetClientRect( hWnd, &rc );
      rc.top += (lpe->iHeaderHeight+1);
      InvalidateRect( hWnd, &rc, TRUE );
      UpdateWindow( hWnd );
      UpdateStatusBar();
      break;

    case WM_SELTRACK:
      if ( lpe->iSelected != (int)wParam )
        {
          lpe->iSelected = (int)wParam;
          GetClientRect( hWnd, &rc );
          rc.top += (lpe->iHeaderHeight+1);
          InvalidateRect( hWnd, &rc, TRUE );
          UpdateWindow( hWnd );
        }
      break;

    case WM_MOUSEMOVE:
      // grrr... it's an evil hack, but I need for the MouseCapture to 
      // remain with the edit control.  When the user selects text with the
      // mouse, the edit control automatically captures the mouse (even if
      // it already has the mouse captured.  Then it releases it, but not
      // until after the WM_*BUTTONUP message.  Until I write a custom
      // edit control, I'll have to use this workaround.
      if ( bInEditTrack && hEdit )
        SetCapture( hEdit );
      break;

    case WM_LBUTTONDOWN:
      if ( HandleLMouseDown( hWnd, lpe, lParam ) )
        {
          GetClientRect( hWnd, &rc );
          rc.top += (lpe->iHeaderHeight+1);
          InvalidateRect( hWnd, &rc, TRUE );
          UpdateWindow( hWnd );
        }
      break;

    case WM_RBUTTONDOWN:
      if ( HandleRMouseDown( hWnd, lpe, lParam ) )
        {
          GetClientRect( hWnd, &rc );
          rc.top += (lpe->iHeaderHeight+1);
          InvalidateRect( hWnd, &rc, TRUE );
          UpdateWindow( hWnd );
        }
      break;

    case WM_RENSELTRACK:
      if ( RenameSelectedTrack( hWnd, lpe ) )
        {
          GetClientRect( hWnd, &rc );
          rc.top += (lpe->iHeaderHeight+1);
          InvalidateRect( hWnd, &rc, TRUE );
          UpdateWindow( hWnd );
        }
      break;

    // copies the first checked track found into (LPADDTRACK)lParam .
    // Returns index of the track, or -1 if no track found
    case WM_FINDFIRSTTRACK:
      return processFindFirst( lpe, (LPADDTRACK)lParam );
      break;

    // returns NULL if no more tracks are selected, otherwise LPADDTRACK
    case WM_FINDNEXTTRACK:
      return processFindNext( lpe, (LPADDTRACK)lParam );
      break;

    case WM_SETSELTEXT:
      lstrcpy( lpe->tracks[lpe->iSelected].name, (char *)lParam );
      GetClientRect( hWnd, &rc );
      rc.top += (lpe->iHeaderHeight+1);
      InvalidateRect( hWnd, &rc, TRUE );
      UpdateWindow( hWnd );
      break;

    case WM_SETTRACKTEXT:
      if ( (int)wParam < lpe->iNum )
        {
          lstrcpyn( lpe->tracks[wParam].name, (char *)lParam, MAX_PATH );
          lpe->tracks[wParam].name[MAX_PATH] = '\0';
          GetClientRect( hWnd, &rc );
          rc.top += (lpe->iHeaderHeight+1);
          InvalidateRect( hWnd, &rc, TRUE );
          UpdateWindow( hWnd );
        }
      break;

    case WM_SETTRACKSTATUS:
      if ( setTrackStatus( lpe, (int)wParam, (LPCSTR)lParam ) )
        {
          GetClientRect( hWnd, &rc );
          rc.top += (lpe->iHeaderHeight+1);
          InvalidateRect( hWnd, &rc, TRUE );
          UpdateWindow( hWnd );
        }
      break;

    case WM_NUMCHECKED:
      return numChecked( lpe );

    case WM_NUMTRACKS:
      return (LRESULT)lpe->iNum;

    case WM_GETTRACK:
      if ( lParam )
        {
          memcpy( (BYTE *)lParam, (BYTE *)&lpe->tracks[wParam], sizeof(ADDTRACK) );
          return (LRESULT)lParam;
        }
      break;

    case WM_CAPTURECHANGED:
      //OutputDebugString( "TrackWndProc: WM_CAPTURECHANGED" );
      break;

    default:
      return DefWindowProc( hWnd, uMsg, wParam, lParam );
    }

  return 0L;
}


HWND createTrackWnd( HWND hParent, HINSTANCE hInst, int idCtrl, LPRECT lprc )
{
  LPTRACKWNDEXTRA lpe;
  HWND hRet;
  HDC hDC;
  SIZE s;
  RECT rc;
  HFONT hOldFont;

  hRet = CreateWindowEx( 0, szTrackWndClass, "A Bogus Name",
                         WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL,
                         lprc->left, lprc->top,
                         lprc->right - lprc->left, lprc->bottom - lprc->top,
                         hParent, (HMENU)idCtrl, hInst, NULL );


  /*
   * compute text height
   */
  lpe = (LPTRACKWNDEXTRA)GetWindowLong( hRet, GWL_USERDATA );
  hDC = GetWindowDC( hRet );
  lpe->hFont = CreateTrackWndFont( hDC );
  hOldFont = SelectObject( hDC, lpe->hFont );
  GetTextExtentPoint32( hDC, "ABCDEFGHIJKLMNOPQRSTUVWYXZabcdefghijklmnopqrstuvwxyz", 52, &s );
  SelectObject( hDC, hOldFont );
  lpe->iTextHeight = s.cy;
  ReleaseDC( hRet, hDC );

  lpe->hHeader = createHeader( hRet, hInst );
  GetClientRect( lpe->hHeader, &rc );
  lpe->iHeaderHeight = rc.bottom - rc.top + 1;

  return hRet;
}



void doTrackWndPaint( HWND hWnd, LPTRACKWNDEXTRA lpe )
{
  PAINTSTRUCT p;
  HDC hDC;
  RECT rc;
  int i;
  int oldBkMode;
  int hw[5];            // width of header items
  int hx[5];            // x offset of header items
  DWORD len;
  //char buf[32];
  POINT pts[5];
  HPEN hOldPen;
  COLORREF oldBkColor = 0;
  COLORREF oldTextColor = 0;
  char buf[81];
  HFONT hOldFont;
  DRAWTEXTPARAMS dtp;

  GetClientRect( hWnd, &rc );
  hDC = BeginPaint( hWnd, &p );

  hOldFont = SelectObject( hDC, lpe->hFont );

  /*
   * compute the offsets for each header section
   */
  ZeroMemory( hw, sizeof(int[5]) );
  ZeroMemory( hx, sizeof(int[5]) );
  for( i = 0; i < 4; i++ )
    {
      HD_ITEM hi;
      ZeroMemory( &hi, sizeof(hi) );
      hi.mask = HDI_WIDTH;
      SendMessage( lpe->hHeader, HDM_GETITEM, i, (LPARAM)&hi );
      hw[i] = hi.cxy;
      hx[i+1] = hx[i] + hw[i];
    }

  oldBkMode = SetBkMode( hDC, TRANSPARENT );

  ZeroMemory( &dtp, sizeof(dtp) );
  dtp.cbSize = sizeof(dtp);
  dtp.iLeftMargin = 1;
  for( i = 0; i < lpe->iNum; i++ )
    {
      // compute rectangle for track title
      rc.left = hx[1] + 5 - lpe->dx;
      rc.right = rc.left + hw[1] - 10;
      rc.top = 6 + (lpe->iHeaderHeight + i*(lpe->iTextHeight+4) ) - lpe->dy;
      rc.bottom = rc.top + 16;

      if ( i == lpe->iSelected )
        {
          SetBkMode( hDC, OPAQUE );
          oldBkColor = SetBkColor( hDC, RGB(20,20,140) );
          oldTextColor = SetTextColor( hDC, oldBkColor );
        }
      // we use DrawTextEx with a 1 unit left margin to avoid clipping
      // certain characters like 'W'
      DrawTextEx( hDC, lpe->tracks[i].name, lstrlen( lpe->tracks[i].name ), &rc, DT_VCENTER | DT_NOPREFIX, &dtp );
      if ( i == lpe->iSelected )
        {
          SetBkMode( hDC, TRANSPARENT );
          SetBkColor( hDC, oldBkColor );
          SetTextColor( hDC, oldTextColor );
        }

      // compute rectangle for status text
      rc.left = hx[3] + 5 - lpe->dx;
      rc.right = rc.left + hw[3] - 10;
      DrawText( hDC, lpe->tracks[i].status, lstrlen( lpe->tracks[i].status ),
                &rc, DT_VCENTER );

      rc.left = hx[2] + 5 - lpe->dx;
      rc.right = rc.left + hw[2] - 10;

      if ( !lpe->tracks[i].bData )
	{
	  len = lpe->tracks[i].len / 75;
	  wsprintf( buf, "%02d:%02d", len / 60, len % 60 );
	}
      else
	lstrcpy( buf, "--:--" );
      DrawText( hDC, buf, lstrlen( buf ), &rc, DT_VCENTER );

      // draw check box
      // We select the brown pen anyway to make sure we have a valid value
      // for hOldPen for later calls to SelectObject()
      hOldPen = SelectObject( hDC, lpe->hBrownPen );
      if ( !lpe->tracks[i].bData )
	{
	  pts[0].x = pts[3].x = pts[4].x = ((hx[1]+1)/2 - 4) - lpe->dx;
	  pts[1].x = pts[2].x = pts[0].x + 8;
	  pts[0].y = pts[1].y = pts[4].y = rc.top + 5;
	  pts[2].y = pts[3].y = rc.top + 13;
	  Polyline( hDC, pts, 5 );
	}

      if ( lpe->tracks[i].bChecked && !lpe->tracks[i].bData )
        {
          SelectObject( hDC, lpe->hBlackPen );
          pts[0].x += 2;
          pts[0].y += 3;
          pts[1].x = pts[0].x + 2;
          pts[1].y = pts[0].y + 3;
          pts[2].x = pts[1].x + 7;
          pts[2].y = pts[1].y - 7;
          Polyline( hDC, pts, 3 );

          pts[0].x += 1;
          pts[1].x = pts[0].x + 2;
          pts[1].y = pts[0].y + 3;
          pts[2].x = pts[1].x + 7;
          pts[2].y = pts[1].y - 7;
          Polyline( hDC, pts, 3 );
        }
      SelectObject( hDC, hOldPen );
    }

  SetBkMode( hDC, oldBkMode );

  SelectObject( hDC, hOldFont );

  EndPaint( hWnd, &p );
}


HFONT CreateTrackWndFont( HDC hDC )
{
  LOGFONT lf;
  HFONT retVal;

  ZeroMemory( &lf, sizeof(lf) );
  lf.lfHeight = -MulDiv( 9, GetDeviceCaps( hDC, LOGPIXELSY), 72 );
  lf.lfCharSet = DEFAULT_CHARSET;
  lf.lfOutPrecision = OUT_TT_PRECIS;
  lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
  lf.lfQuality = DEFAULT_QUALITY;
  lf.lfPitchAndFamily = FF_SWISS | DEFAULT_PITCH;
  lf.lfWeight = FW_BOLD;
//  strcpy( lf.lfFaceName, "Courier New" );
  strcpy( lf.lfFaceName, "Arial" );

  retVal = CreateFontIndirect( &lf );
  return retVal;
}


void RecalcWindow( HWND hWnd, LPTRACKWNDEXTRA lpe )
{
  RECT rc;
  SCROLLINFO si;
  int i;

  /*
   * compute the offsets for each header section, used for mouse hit testing
   * The paint code will recompute on a per paint basis
   */
  ZeroMemory( lpe->hw, sizeof(int[5]) );
  ZeroMemory( lpe->hx, sizeof(int[5]) );
  for( i = 0; i < 3; i++ )
    {
      HD_ITEM hi;
      ZeroMemory( &hi, sizeof(hi) );
      hi.mask = HDI_WIDTH;
      SendMessage( lpe->hHeader, HDM_GETITEM, i, (LPARAM)&hi );
      lpe->hw[i] = hi.cxy;
      lpe->hx[i+1] = lpe->hx[i] + lpe->hw[i];
    }

  GetClientRect( hWnd, &rc );
  lpe->vh = lpe->iNum * (lpe->iTextHeight + 4) + lpe->iHeaderHeight + 5;

  ZeroMemory( &si, sizeof(si) );
  si.cbSize = sizeof(si);
  si.fMask  = SIF_PAGE | SIF_RANGE;
  si.nMin   = 0;
  si.nMax   = lpe->vh;
  si.nPage  = rc.bottom;
  si.nPos   = lpe->dy;

#if 0
  if ( !lpe->bVScroll )
#endif
    si.fMask |= SIF_POS;

  SetScrollInfo( hWnd, SB_VERT, &si, TRUE );

  if ( lpe->bVScroll && ( lpe->vh < rc.bottom ) )
    lpe->bVScroll = FALSE;
  else if ( !lpe->bVScroll && ( lpe->vh > rc.bottom ) )
    lpe->bVScroll = TRUE;

  if ( lpe->bVScroll == FALSE )
    lpe->dy = 0;

  ZeroMemory( &si, sizeof(si) );
  si.cbSize = sizeof(si);
  si.fMask  = SIF_PAGE | SIF_RANGE;
  si.nMin   = 0;
  si.nMax   = lpe->vw;
  si.nPage  = rc.right;
  si.nPos   = lpe->dx;

  if ( !lpe->bHScroll )
    si.fMask |= SIF_POS;

  SetScrollInfo( hWnd, SB_HORZ, &si, TRUE );

  if ( lpe->bHScroll && ( lpe->vw < rc.right ) )
    lpe->bHScroll = FALSE;
  else if ( !lpe->bHScroll && ( lpe->vw > rc.right ) )
    lpe->bHScroll = TRUE;

  if ( lpe->bHScroll == FALSE )
    lpe->dx = 0;

  ComputeHeaderPos( lpe->hHeader, hWnd );
}


void DeleteTrack( HWND hWnd, int iTrack, LPTRACKWNDEXTRA lpe )
{
  int i;

  hWnd = hWnd;
  if ( iTrack == (int)ALLTRACKS )
    {
      lpe->iSelected = -1;
      lpe->iNum = 0;
      return;
    }

  if ( iTrack > lpe->iNum )
    return;

  lpe->iSelected = -1;
  for( i = iTrack; i < lpe->iNum; i++ )
    {
      lpe->tracks[i] = lpe->tracks[i+1];
    }
  lpe->iNum--;
}


void HandleHScroll( HWND hWnd, int nScrollCode, int nPos, LPTRACKWNDEXTRA lpe )
{
  hWnd = hWnd; nScrollCode = nScrollCode; nPos = nPos; lpe = lpe;
}

void HandleVScroll( HWND hWnd, int nScrollCode, int nPos, LPTRACKWNDEXTRA lpe )
{
  RECT rc;
  SCROLLINFO si;

  GetClientRect( hWnd, &rc );

  si.cbSize   = sizeof(si);
  si.fMask    = SIF_ALL;
  GetScrollInfo( hWnd, SB_VERT, &si );

  // one line of text takes up lpe->iTextHeight + 4 units
  switch( nScrollCode )
    {
    case SB_BOTTOM: break;
    case SB_ENDSCROLL: break;
    case SB_LINEDOWN:
      lpe->dy = min( lpe->dy + lpe->iTextHeight + 4, 
                     lpe->vh - (rc.bottom-1) );
      break;

    case SB_LINEUP:
      lpe->dy = max( 0, lpe->dy - (lpe->iTextHeight+4) );
      break;

    case SB_PAGEDOWN:
      lpe->dy = min( lpe->dy + rc.bottom, lpe->vh - (rc.bottom-1) );
      break;

    case SB_PAGEUP:
      lpe->dy = max( 0, lpe->dy - rc.bottom );
      break;

    case SB_THUMBPOSITION:
      lpe->dy = nPos;
      break;

    case SB_THUMBTRACK:
      lpe->dy = nPos;
      break;

    case SB_TOP: break;
      break;

    default: 
      //OutputDebugString( "Unknown scroll-bar message" );
      break;
    }
}




HWND createHeader( HWND hWnd, HINSTANCE hInst )
{
  HD_ITEM hdi;
  HWND hRet;

  hRet = CreateWindowEx( 0L, WC_HEADER, "",
                         WS_CHILD | WS_BORDER | HDS_HORZ,
                         0, 0, 0, 0,
                         hWnd, (HMENU)IDM_HEADER, hInst, NULL );
  if ( !hRet )
    return NULL;

  ComputeHeaderPos( hRet, hWnd );

  hdi.mask    = HDI_FORMAT | HDI_WIDTH;
  hdi.cxy     = 30;
  hdi.fmt     = HDF_LEFT | HDF_STRING;
  SendMessage( hRet, HDM_INSERTITEM, 9999, (LPARAM)&hdi );

  hdi.mask    = HDI_TEXT | HDI_FORMAT | HDI_WIDTH;
  hdi.pszText = "Title";
  hdi.cxy     = 200;
  hdi.cchTextMax = lstrlen( hdi.pszText );
  hdi.fmt     = HDF_LEFT | HDF_STRING;
  SendMessage( hRet, HDM_INSERTITEM, 9999, (LPARAM)&hdi );

  hdi.mask    = HDI_TEXT | HDI_FORMAT | HDI_WIDTH;
  hdi.pszText = "Time";
  hdi.cxy     = 70;
  hdi.cchTextMax = lstrlen( hdi.pszText );
  hdi.fmt     = HDF_LEFT | HDF_STRING;
  SendMessage( hRet, HDM_INSERTITEM, 9999, (LPARAM)&hdi );

  hdi.mask    = HDI_TEXT | HDI_FORMAT | HDI_WIDTH;
  hdi.pszText = "Status";
  hdi.cxy     = 200;
  hdi.cchTextMax = lstrlen( hdi.pszText );
  hdi.fmt     = HDF_LEFT | HDF_STRING;
  SendMessage( hRet, HDM_INSERTITEM, 9999, (LPARAM)&hdi );

  return hRet;
}



void ComputeHeaderPos( HWND hHdr, HWND hParent )
{
  WINDOWPOS wp;
  HD_LAYOUT hdl;
  RECT rc;

  GetClientRect( hParent, &rc );
  hdl.prc = &rc;
  hdl.pwpos = &wp;
  SendMessage( hHdr, HDM_LAYOUT, 0, (LPARAM)&hdl );
  SetWindowPos( hHdr, wp.hwndInsertAfter, wp.x, wp.y, wp.cx, wp.cy,
                wp.flags | SWP_SHOWWINDOW );
}


BOOL handleHeaderNotify( HWND hWnd, LPARAM lParam, LPTRACKWNDEXTRA lpe )
{
  HD_NOTIFY *lphd = (HD_NOTIFY *)lParam;
  LPNMHDR lpnm = (LPNMHDR)lParam;

#if 0
  if ( lpnm->code <= HDN_FIRST && lpnm->code >= HDN_LAST )
    {
      wsprintf( buf, "Header notify[%04X:%d:%d]: %s", lphd->hdr.hwndFrom, lphd->iItem,lphd->iButton,  notifyString( lphd->hdr.code ) );
    }
  else
    wsprintf( buf, "Header notify[%04X]: %s", lphd->hdr.hwndFrom,  notifyString( lphd->hdr.code ) );

  OutputDebugString( buf );
#endif

  switch( lpnm->code )
    {
    case HDN_ITEMCHANGED:
      RecalcWindow( hWnd, lpe );
      InvalidateRect( hWnd, NULL, TRUE );
      UpdateWindow( hWnd );
      break;

    case HDN_BEGINTRACK:
      SetFocus( hWnd );
      // prevent the first header from changing
      if ( lphd->iItem == 0 )
        return TRUE;
      break;
    }

  return FALSE;
}


#ifndef NM_CUSTOMDRAW
#define NM_CUSTOMDRAW     (NM_FIRST-12)
#endif

#ifndef NM_RELEASEDCAPTURE
#define NM_RELEASEDCAPTURE   (NM_FIRST-16)
#endif

char *notifyString( UINT code )
{
  static char buf[60];
  switch( code )
    {
    case NM_CUSTOMDRAW: return "NM_CUSTOMDRAW";
    case NM_CLICK: return "NM_CLICK";
    case NM_DBLCLK: return "NM_DBLCLK";
    case NM_KILLFOCUS: return "NM_KILLFOCUS";
    case NM_OUTOFMEMORY: return "NM_OUTOFMEMORY";
    case NM_RCLICK: return "NM_RCLICK";
    case NM_RDBLCLK: return "NM_RDBLCLK";
    case NM_RETURN: return "NM_RETURN";
    case NM_SETFOCUS: return "NM_SETFOCUS";
    case NM_RELEASEDCAPTURE: return "NM_RELEASEDCAPTURE";
    case HDN_BEGINTRACK: return "HDN_BEGINTRACK";
    case HDN_DIVIDERDBLCLICK: return "NM_DIVIDERDBLCLICK";
    case HDN_ENDTRACK: return "HDN_ENDTRACK";
    case HDN_ITEMCHANGED: return "HDN_ITEMCHANGED";
    case HDN_ITEMCHANGING: return "HDN_ITEMCHANGING";
    case HDN_ITEMCLICK: return "HDN_ITEMCLICK";
    case HDN_ITEMDBLCLICK: return "HDN_ITEMDBLCLICK";
    case HDN_TRACK: return "HDN_TRACK";
    default: wsprintf( buf, "unknown %04X (%d)", code, code ); return buf;
    }
}

/*
 * determines if a mouse click (in window coordinates) was on a check box.
 * If so, returns the index of the track.  If not, returns -1
 */
int CheckBoxHit( LPTRACKWNDEXTRA lpe, LPARAM lParam )
{
  int i, x, y;
  int mx, my;

  mx = (int)LOWORD(lParam) + lpe->dx;
  my = (int)HIWORD(lParam) + lpe->dy;

  for( i = 0; i < lpe->iNum; i++ )
    {
      x = (lpe->hx[1] + 1) / 2 - 4;   // left side x value
      y = 11 + lpe->iHeaderHeight + i*(lpe->iTextHeight + 4);
      if ( (mx >= x) && (mx <= (x+8)) && (my >= y) && (my <= (y+8)) )
        return i;
    }

  return -1;
}


/*
 * Determines if a mouse click was on a track name on the screen.  lParam
 * is expected to be in client coordinates, as sent with the WM_LBUTTONDOWN,
 * etc. messages.  Returns the index of the track hit, or -1 if not on a
 * track name
 */
int TrackNameHit( LPTRACKWNDEXTRA lpe, LPARAM lParam )
{
  int i, x, y;
  int mx, my;
  RECT rc;

  // if it's within the header, return -1 (no track hit)
  if ( ((int)HIWORD(lParam)) <= lpe->iHeaderHeight )
    return -1;

  mx = (int)LOWORD(lParam) + lpe->dx;
  my = (int)HIWORD(lParam) + lpe->dy;


  for( i = 0; i < lpe->iNum; i++ )
    {
      x = lpe->hx[1] + 1;
      y = 6 + lpe->iHeaderHeight + i*(lpe->iTextHeight + 4);

      rc.left = x;
      rc.right = x + lpe->hw[1];
      rc.top = y;
      rc.bottom = y + lpe->iTextHeight;

      if ( (mx >= rc.left) && (mx <= rc.right) && (my >= rc.top) &&
           (my <= rc.bottom) )
        return i;
    }

  return -1;
}

/*
 * returns TRUE if the mouse click was on either a check box or a track name,
 * and will require a repaint
 */
BOOL HandleLMouseDown( HWND hWnd, LPTRACKWNDEXTRA lpe, LPARAM lParam )
{
  int i;

  SetFocus( hWnd );

  // determine if the click was on a check box
  i = CheckBoxHit( lpe, lParam );
  if ( i != -1 )
    {
      if ( !lpe->tracks[i].bData )
	{
	  SetCheckBox( &lpe->tracks[i], INVERTCHECK );
	  UpdateStatusBar();
	  return TRUE;
	}
      return FALSE;
    }

  i = TrackNameHit( lpe, lParam );
  if ( i != -1 )
    {
      lpe->iSelected = i;
      return TRUE;
    }

  return FALSE;
}

/*
 * returns TRUE if the mouse click was on either a check box or a track name,
 * and will require a repaint
 */
BOOL HandleRMouseDown( HWND hWnd, LPTRACKWNDEXTRA lpe, LPARAM lParam )
{
  int i;

  SetFocus( hWnd );

  // did we hit a track name?
  i = TrackNameHit( lpe, lParam );
  if ( i != -1 )
    {
      lpe->iSelected = i;
      return TRUE;
    }

  return FALSE;
}


/*
 * if trackNo == -1, then check/uncheck all
 */
BOOL HandleCheckTrack( HWND hWnd, LPTRACKWNDEXTRA lpe, int trackNo, BOOL bChecked )
{
  int i;

  hWnd = hWnd;
  if ( trackNo == (int)ALLTRACKS )
    {
      for( i = 0; i < lpe->iNum; i++ )
	SetCheckBox( &lpe->tracks[i], bChecked?SETCHECKED:SETUNCHECKED );
      return TRUE;
    }

  if ( trackNo < 0 || trackNo >= lpe->iNum )
    return FALSE;

  SetCheckBox( &lpe->tracks[trackNo], bChecked?SETCHECKED:SETUNCHECKED );

  return TRUE;
}

/*
 * if trackNo == -1, then check/uncheck all
 */
BOOL HandleInvertCheck( HWND hWnd, LPTRACKWNDEXTRA lpe, int trackNo )
{
  int i;

  hWnd = hWnd;
  if ( trackNo == (int)ALLTRACKS )
    {
      for( i = 0; i < lpe->iNum; i++ )
	SetCheckBox( &lpe->tracks[i], INVERTCHECK );
      return TRUE;
    }

  if ( trackNo < 0 || trackNo >= lpe->iNum )
    return FALSE;

  SetCheckBox( &lpe->tracks[trackNo], INVERTCHECK );

  return TRUE;
}


int doTrackContextMenu( HWND hParent, HWND hChild, LPARAM lParam )
{
  HMENU hMenu, hPopup;
  LPTRACKWNDEXTRA lpe;
  int i;
  POINT p;
  LPARAM lp2;

  p.x = (LONG)LOWORD(lParam);
  p.y = (LONG)HIWORD(lParam);
  ScreenToClient( hChild, &p );
  lp2 = MAKELPARAM( p.x, p.y );

  lpe = (LPTRACKWNDEXTRA)GetWindowLong( hChild, GWL_USERDATA);

  if ( p.y < lpe->iHeaderHeight )
    return 0;

  // if it hit a track name, then we need to pop up the track context menu
  // otherwise, we need a generic context menu
  i = TrackNameHit( lpe, lp2 );
  if ( i != -1 )
    {
      hMenu = LoadMenu( ghInstance, "trackPopupMenu" );
      if ( !hMenu )
        return 0;

      hPopup = GetSubMenu( hMenu, 0 );
      TrackPopupMenu( hPopup, TPM_LEFTALIGN | TPM_RIGHTBUTTON,
                      LOWORD(lParam), HIWORD(lParam), 0, hParent, NULL );
    }
  else
    {
      hMenu = LoadMenu( ghInstance, "genericPopupMenu" );
      if ( !hMenu )
        return 0;

      // pop up a more generic menu
      hPopup = GetSubMenu( hMenu, 0 );
      TrackPopupMenu( hPopup, TPM_LEFTALIGN | TPM_RIGHTBUTTON,
                      LOWORD(lParam), HIWORD(lParam), 0, hParent, NULL );
    }

  DestroyMenu( hMenu );

  return 1;
}



/*
 * Pops up a sub-classed single-line edit on top of track title.  Must ensure
 * that the selected track is visible.  Captures mouse input to catch when
 * user clicks elsewhere, and saves the text.
 */
BOOL RenameSelectedTrack( HWND hWnd, LPTRACKWNDEXTRA lpe )
{
  int hw[5];            // width of header items
  int hx[5];            // x offset of header items
  int i;
  RECT rc;
  //HWND hEdit;

  if ( bInEditTrack )
    return FALSE;

  bInEditTrack = TRUE;

  if ( (lpe->iSelected < 0) || (lpe->iSelected >= lpe->iNum) )
    return FALSE;

  /*
   * compute the offsets for each header section
   */
  ZeroMemory( hw, sizeof(int[5]) );
  ZeroMemory( hx, sizeof(int[5]) );
  for( i = 0; i < 3; i++ )
    {
      HD_ITEM hi;
      ZeroMemory( &hi, sizeof(hi) );
      hi.mask = HDI_WIDTH;
      SendMessage( lpe->hHeader, HDM_GETITEM, i, (LPARAM)&hi );
      hw[i] = hi.cxy;
      hx[i+1] = hx[i] + hw[i];
    }

  i = lpe->iSelected;
  rc.left = hx[1] + 5 - lpe->dx;
  rc.right = rc.left + hw[1] - 10;
  rc.top = 4 + (lpe->iHeaderHeight + i*(lpe->iTextHeight+4) ) - lpe->dy;
  rc.bottom = rc.top + 20;

  hEdit = CreateWindowEx( 0L, "EDIT", lpe->tracks[lpe->iSelected].name,
                          WS_BORDER | WS_CHILD | WS_VISIBLE
                          | ES_AUTOHSCROLL | ES_LEFT,
                          rc.left, rc.top,
                          rc.right - rc.left, rc.bottom - rc.top,
                          hWnd, (HMENU)++iCtlId, ghInstance, NULL );

  // Save old window proc
  SetWindowLong( hEdit, GWL_USERDATA, GetWindowLong( hEdit, GWL_WNDPROC ) );
  // Set new window proc
  SetWindowLong( hEdit, GWL_WNDPROC, (LONG)EditSubclassWndProc );

  SetFocus( hEdit );
  SendMessage( hEdit, EM_SETLIMITTEXT, (WPARAM)(MAX_PATH+1), 0L );
  SendMessage( hEdit, EM_SETSEL, 0, -1L );
  //SendMessage( hEdit, WM_STARTMOUSECAPTURE, 0, 0L );

  SetCapture( hEdit );

  return TRUE;
}


LRESULT processFindFirst( LPTRACKWNDEXTRA lpe, LPADDTRACK lpAddTrack )
{
  int i;

  if ( lpAddTrack == NULL )
    return -1L;

  for( i = 0; i < lpe->iNum; i++ )
    {
      if ( lpe->tracks[i].bChecked )
        {
          *lpAddTrack = lpe->tracks[i];
          lpe->iFound = i;
          return i;
        }
    }

  return -1L;
}


LRESULT processFindNext( LPTRACKWNDEXTRA lpe, LPADDTRACK lpAddTrack )
{
  int i;

  if ( lpAddTrack == NULL )
    return -1L;

  for( i = lpe->iFound + 1; i < lpe->iNum; i++ )
    {
      if ( lpe->tracks[i].bChecked )
        {
          *lpAddTrack = lpe->tracks[i];
          lpe->iFound = i;
          return i;
        }
    }

  return -1L;
}


BOOL setTrackStatus( LPTRACKWNDEXTRA lpe, int idx, LPCSTR s )
{
  if ( !lpe || !s )
    return FALSE;

  lstrcpyn( lpe->tracks[idx].status, s, 61 );
  return TRUE;
}


#ifndef WM_MOUSEHOVER
#define WM_MOUSEHOVER 0x2A1
#endif
#ifndef WM_MOUSELEAVE
#define WM_MOUSELEAVE 0x2A3
#endif
void logWindowsProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
#if 0
  char szMsg[40];
  static UINT filtered[] = {
    WM_MOUSEMOVE, WM_MOUSEHOVER, WM_MOUSELEAVE, WM_SETCURSOR, WM_NCHITTEST, 0
  };
  int i;

  hWnd = hWnd, wParam = wParam; lParam = lParam;

  for( i = 0; filtered[i]; i++ )
    if ( uMsg == filtered[i] )
      return;
  
  convertuMsg( uMsg, szMsg );
#else
  hWnd = hWnd; uMsg = uMsg; wParam = wParam; lParam = lParam;
#endif
}


void convertuMsg( UINT uMsg, char * s )
{
  switch( uMsg )
    {
    case WM_COMMAND: lstrcpy( s, "WM_COMMAND" ); break;
    case WM_INITDIALOG: lstrcpy( s, "WM_INITDIALOG" ); break;
    default:
      wsprintf( s, "%d", uMsg );
      break;
    }
}

LRESULT CALLBACK EditSubclassWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
  WNDPROC lpfnWndProc;
  int x, y;
  RECT rc;

  lpfnWndProc = (WNDPROC)GetWindowLong( hWnd, GWL_USERDATA );

#if 0
  switch( uMsg )
    {
    case EM_CANUNDO: OutputDebugString( "EM_CANUNDO" ); break;
    case EM_CHARFROMPOS: OutputDebugString( "EM_CHARFROMPOS" ); break;
    case EM_EMPTYUNDOBUFFER: OutputDebugString( "EM_EMPTYUNDOBUFFER" ); break;
    case EM_GETFIRSTVISIBLELINE: OutputDebugString( "EM_GETFIRSTVISIBLELINE" ); break;
    case EM_GETLIMITTEXT: OutputDebugString( "EM_GETLIMITTEXT" ); break;
    case EM_GETLINE: OutputDebugString( "EM_GETLINE" ); break;
    case EM_GETMARGINS: OutputDebugString( "EM_GETMARGINS" ); break;
    case EM_GETMODIFY: OutputDebugString( "EM_GETMODIFY" ); break;
    case EM_GETRECT: OutputDebugString( "EM_GETRECT" ); break;
    case EM_GETSEL: OutputDebugString( "EM_GETSEL" ); break;
    case EM_LINELENGTH: OutputDebugString( "EM_LINELENGTH" ); break;
    case EM_POSFROMCHAR: OutputDebugString( "EM_POSFROMCHAR" ); break;
    case EM_REPLACESEL: OutputDebugString( "EM_REPLACESEL" ); break;
    case EM_SETLIMITTEXT: OutputDebugString( "EM_SETLIMITTEXT" ); break;
    case EM_SETMARGINS: OutputDebugString( "EM_SETMARGINS" ); break;
    case EM_SETMODIFY: OutputDebugString( "EM_SETMODIFY" ); break;
    case EM_SETREADONLY: OutputDebugString( "EM_SETREADONLY" ); break;
    case EM_SETSEL: OutputDebugString( "EM_SETSEL" ); break;
    case EM_UNDO: OutputDebugString( "EM_UNDO" ); break;
    case WM_COMMAND:
      switch( HIWORD(wParam) )
        {
        case EN_SETFOCUS: OutputDebugString( "EN_SETFOCUS: edit control" ); break;
        case EN_KILLFOCUS: OutputDebugString( "EN_KILLFOCUS: edit control" ); break;
        case EN_CHANGE: OutputDebugString( "EN_CHANGE" ); break;
        case EN_ERRSPACE: OutputDebugString( "EN_ERRSPACE" ); break;
        case EN_MAXTEXT: OutputDebugString( "EN_MAXTEXT" ); break;
        case EN_UPDATE: OutputDebugString( "EN_UPDATE" ); break;
        }
      break;
    }
#endif

  switch( uMsg )
    {
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
      GetClientRect( hWnd, &rc );
      x = (int)LOWORD( lParam );
      y = (int)HIWORD( lParam );
      if ( (x < 0) || ( y < 0) || (x > rc.right) || (y > rc.bottom) )
        {
          POINT p;

          SetTrackWndText( hWnd );
          ReleaseCapture();
          bInEditTrack = FALSE;
          p.x = x; p.y = y; MapWindowPoints( hWnd, GetParent(hWnd ), &p, 1 );
          SendMessage( GetParent(hWnd), uMsg, wParam,
                       (LPARAM)MAKELONG( p.x, p.y ) );
          DestroyWindow( hWnd );
          return 0L;
        }
      break;

    case WM_LBUTTONUP:
      break;

    case WM_KEYDOWN:
      if ( (int)wParam == 27 ) // escape key
        {
          //SetTrackWndText( hWnd );
	  bInEditTrack = FALSE;
          DestroyWindow( hWnd );
          return 0L;
        }
      break;

    case WM_CAPTURECHANGED:
      break;
    }

  return CallWindowProc( lpfnWndProc, hWnd, uMsg, wParam, lParam );
}


void SetTrackWndText( HWND hWnd )
{
  char buf[MAX_PATH+1];

  ZeroMemory( buf, MAX_PATH+1 );
  SendMessage( hWnd, WM_GETTEXT, MAX_PATH+1, (LPARAM)buf );
  SendMessage( GetParent( hWnd ), WM_SETSELTEXT, 0, (LPARAM)buf );
}


LRESULT numChecked( LPTRACKWNDEXTRA lpe )
{
  int i;
  LRESULT retVal = 0;

  for( i = 0; lpe && (i < lpe->iNum); i++ )
    if ( lpe->tracks[i].bChecked )
      retVal++;

  return retVal;
}


int SetCheckBox( ADDTRACK *t, int val )
{
  if ( t->bData )
    return DATATRACK;

  switch( val )
    {
    case INVERTCHECK:
      t->bChecked = !t->bChecked;
      return t->bChecked?CHECKEDTRACK:UNCHECKEDTRACK;
    case SETCHECKED:
      t->bChecked = TRUE;
      return CHECKEDTRACK;
    case SETUNCHECKED:
      t->bChecked = FALSE;
      return UNCHECKEDTRACK;
    }
  return UNCHECKEDTRACK;
}


HDC GetDrawDC( HWND hWnd )
{
  HDC hRetVal, hDC;

  hDC = GetDC( hWnd );
  hRetVal = CreateCompatibleDC( hDC );
  ReleaseDC( hWnd, hDC );

  return hRetVal;
}


HBRUSH CreateTrackWndBrush( void )
{
  LOGBRUSH lb;
  HBRUSH hBrush;

  ZeroMemory( &lb, sizeof(lb) );
  lb.lbStyle = BS_SOLID;
  lb.lbColor = RGB( 240, 255, 220 );
  lb.lbHatch = 0;
  hBrush = CreateBrushIndirect( &lb );

  return hBrush;
}
