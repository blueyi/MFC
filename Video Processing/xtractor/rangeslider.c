#include <windows.h>
#include "rangeslider.h"
#include "globals.h"


#define HEIGHTSLIDER 13

typedef struct {
  DWORD min;
  DWORD max;
  DWORD start;
  DWORD finish;
  int xOfsStart;        // possibly useless
  SHORT xStart;         // x-offset of starting position
  SHORT yStart;         // y-offset of starting position
  int which;
  RECT rc;
  BOOL bInDrag;
  HDC hCompDC;
  HBITMAP hBmp;
  HBITMAP hTop;
  HBITMAP hBottom;
  HPEN hDkGreyPen;
  HPEN hLtGreyPen;
  HPEN hBlackPen;
  HPEN hWhitePen;
  HBRUSH hBackground;
  HBRUSH hGreenBrush;
  int numTics;
  DWORD tic[100];
} RANGESLIDERSTRUCT, FAR *LPRANGESLIDERSTRUCT;


void PaintRangeSliderWnd( HWND hWnd, LPRANGESLIDERSTRUCT lpr );
LRESULT CALLBACK RangeSliderBarProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
void CreateSliderBitmaps( HDC hDC, LPRANGESLIDERSTRUCT lpr );
BOOL SliderHitTest( HWND hWnd, int which, LPARAM lParam, LPRANGESLIDERSTRUCT lpr );
BOOL sliderHandleLButtonDown( HWND hWnd, LPRANGESLIDERSTRUCT lpr, LPARAM lParam );
BOOL sliderHandleLButtonUp( HWND hWnd, LPRANGESLIDERSTRUCT lpr, LPARAM lParam );
BOOL sliderHandleMouseMove( HWND hWnd, LPRANGESLIDERSTRUCT lpr, LPARAM lParam );
BOOL sliderHandleSnap( HWND hWnd, WPARAM wParam, BOOL bRight, LPRANGESLIDERSTRUCT lpr );
BOOL SliderLeftHitTest( HWND hWnd, int which, LPARAM lParam,
			 LPRANGESLIDERSTRUCT lpr );
BOOL SliderRightHitTest( HWND hWnd, int which, LPARAM lParam,
			 LPRANGESLIDERSTRUCT lpr );
BOOL SendSliderNotifyChanging( HWND hWnd, LPRANGESLIDERSTRUCT lpr, DWORD dwNew );
BOOL SendSliderNotifyChanged( HWND hWnd, LPRANGESLIDERSTRUCT lpr );


static char szRangeSliderClass[] = "ak_rangeslider";


int InitRangeSliderClass( void )
{
  WNDCLASSEX wc;
  
  ZeroMemory( &wc, sizeof(wc) );
  wc.cbSize          = sizeof(wc);
  wc.style           = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc     = (WNDPROC)RangeSliderBarProc;
  wc.hInstance       = ghInstance;
  wc.hCursor         = LoadCursor( NULL, IDC_ARROW );
  wc.hbrBackground   = (HBRUSH)(COLOR_BTNFACE+1);
  wc.lpszClassName   = szRangeSliderClass;

  if ( !RegisterClassEx( &wc ) )
    return 0;

  return -1;
}


/*
 * Implements a sliding range bar control.  The control is used to select
 * a range using two slide controls -- one on top and one on bottom.
 *
 * Message          wParam      lParam
 * ---------------- ----------- ------------------------------------------
 * RSB_SETMIN       bRepaint    minimum allowed value
 * RSB_SETMAX       bRepaint    maxiumum allowed value
 * RSB_GETMIN       0           0
 * RSB_GETMAX       0           0
 * RSB_RESET        0           0
 * RSB_SETSTART     bRepaint    starting position of selected range
 * RSB_SETFINISH    bRepaint    ending position of selected range
 * RSB_SNAP         top/bottom  0 = left, 1 = right
 */
LRESULT CALLBACK RangeSliderBarProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
  LPRANGESLIDERSTRUCT lpr;
  DWORD dwTmp;

  lpr = (LPRANGESLIDERSTRUCT)GetWindowLong( hWnd, GWL_USERDATA );
  if ( !lpr && (uMsg != WM_CREATE) )
    return DefWindowProc( hWnd, uMsg, wParam, lParam );

  switch( uMsg )
    {
    case WM_CREATE:
      dwTmp = sizeof(*lpr);
      lpr = (LPRANGESLIDERSTRUCT)GlobalAlloc( GPTR, sizeof(*lpr) );
      lpr->min = 0;
      lpr->max = 100;
      lpr->start = 0;
      lpr->finish = 0;
      lpr->hTop = (HBITMAP)LoadBitmap( ghInstance, "SliderTop" );
      lpr->hBottom = (HBITMAP)LoadBitmap( ghInstance, "SliderBottom" );
      lpr->hWhitePen = (HPEN)GetStockObject( WHITE_PEN );
      lpr->hBlackPen = (HPEN)GetStockObject( BLACK_PEN );
      lpr->hDkGreyPen = CreatePen( PS_SOLID, 1, RGB( 128, 128, 128 ) );
      lpr->hLtGreyPen = CreatePen( PS_SOLID, 1, RGB( 192, 192, 192 ) );
      lpr->hBackground = CreateSolidBrush( GetSysColor( COLOR_MENU ) );
      lpr->hGreenBrush = CreateSolidBrush( RGB( 0, 255, 0 ) );
      GetClientRect( hWnd, &lpr->rc );
      SetWindowLong( hWnd, GWL_USERDATA, (LONG)lpr );
      break;

    case WM_DESTROY:
      DeleteObject( lpr->hTop );
      DeleteObject( lpr->hBottom );
      DeleteObject( lpr->hDkGreyPen );
      DeleteObject( lpr->hLtGreyPen );
      DeleteObject( lpr->hBackground );
      DeleteObject( lpr->hGreenBrush );
      if ( lpr->hCompDC )
	ReleaseDC( hWnd, lpr->hCompDC );
      if ( lpr->hBmp )
	DeleteObject( lpr->hBmp );
      GlobalFree( (HGLOBAL)lpr );
      break;

    case WM_PAINT:
      PaintRangeSliderWnd( hWnd, lpr );
      break;

    case WM_LBUTTONDOWN:
      if ( sliderHandleLButtonDown( hWnd, lpr, lParam ) )
	{
	  InvalidateRect( hWnd, &lpr->rc, FALSE );
	  UpdateWindow( hWnd );
	}
      break;

    case WM_LBUTTONUP:
      if ( sliderHandleLButtonUp( hWnd, lpr, lParam ) )
	{
	  InvalidateRect( hWnd, &lpr->rc, FALSE );
	  UpdateWindow( hWnd );
	}
      break;

    case WM_MOUSEMOVE:
      if ( sliderHandleMouseMove( hWnd, lpr, lParam ) )
	{
	  InvalidateRect( hWnd, &lpr->rc, FALSE );
	  UpdateWindow( hWnd );
	}
      break;

    case WM_SETFOCUS:
      break;

    case RSB_SETMIN:
      dwTmp = (DWORD)lParam;
      if ( dwTmp >= lpr->max )
	dwTmp = lpr->max - 1;
      lpr->min = dwTmp;
      break;

    case RSB_SETMAX:
      dwTmp = (DWORD)lParam;
      if ( dwTmp <= lpr->min )
	dwTmp = lpr->min + 1;
      lpr->max = dwTmp;
      break;

    case RSB_SETSTART:
      dwTmp = (DWORD)lParam;
      if ( dwTmp < lpr->min )
	dwTmp = lpr->min;
      else if ( dwTmp >= lpr->max )
	dwTmp = lpr->max-1;
      lpr->start = dwTmp;
      if ( wParam )
	{
	  InvalidateRect( hWnd, &lpr->rc, FALSE );
	  UpdateWindow( hWnd );
	}
      break;

    case RSB_SETFINISH:
      dwTmp = (DWORD)lParam;
      if ( dwTmp <= lpr->min )
	dwTmp = lpr->min + 1;
      else if ( dwTmp > lpr->max )
	dwTmp = lpr->max;
      lpr->finish = dwTmp;
      if ( wParam )
	{
	  InvalidateRect( hWnd, &lpr->rc, FALSE );
	  UpdateWindow( hWnd );
	}
      break;

    case RSB_GETMIN:
      return (LRESULT)lpr->min;

    case RSB_GETMAX:
      return (LRESULT)lpr->max;

    case RSB_GETSTART:
      return (LRESULT)lpr->start;

    case RSB_GETFINISH:
      return (LRESULT)lpr->finish;

    case RSB_SETTIC:
      if ( lpr->numTics < 100 )
	lpr->tic[lpr->numTics++] = (DWORD)lParam;
      break;

    case RSB_SNAP:
      if ( sliderHandleSnap( hWnd, wParam, (BOOL)lParam, lpr ) )
	{
	  InvalidateRect( hWnd, &lpr->rc, FALSE );
	  UpdateWindow( hWnd );
	}
      break;

    default:
      return DefWindowProc( hWnd, uMsg, wParam, lParam );
    }

  return 0L;
}


BOOL SliderHitTest( HWND hWnd, int which, LPARAM lParam,
		    LPRANGESLIDERSTRUCT lpr )
{
  int xOfs;
  POINTS pt;

  pt = MAKEPOINTS( lParam );

  switch( which )
    {
    case TOPSLIDER:
      xOfs = (lpr->rc.right-7) * lpr->start / (lpr->max - lpr->min);
      if ( (pt.x >= xOfs) && (pt.x <= (xOfs + 7)) &&
	   (pt.y >= 0) && (pt.y <= 14) )
	{
	  OutputDebugString( "SliderHitTest: TOPSLIDER hit!" );
	  return TRUE;
	}
      break;

    case BOTTOMSLIDER:
      xOfs = (lpr->rc.right-7) * lpr->finish / (lpr->max - lpr->min);
      if ( (pt.x >= xOfs) && (pt.x <= (xOfs + 7)) &&
	   (pt.y >= 25+HEIGHTSLIDER) && (pt.y <= 39+HEIGHTSLIDER) )
	{
	  OutputDebugString( "SliderHitTest: BOTTOMSLIDER hit!" );
	  return TRUE;
	}
      break;
    }

  OutputDebugString( "SliderHitTest: no slider hit..." );
  return FALSE;
}


BOOL SliderLeftHitTest( HWND hWnd, int which, LPARAM lParam,
			LPRANGESLIDERSTRUCT lpr )
{
  int xOfs;
  POINTS pt;

  pt = MAKEPOINTS( lParam );

  switch( which )
    {
    case TOPSLIDER:
      xOfs = (lpr->rc.right-7) * lpr->start / (lpr->max - lpr->min);
      if ( (pt.x < xOfs) && (pt.y >= 0) && (pt.y <= 14) )
	{
	  return TRUE;
	}
      break;

    case BOTTOMSLIDER:
      xOfs = (lpr->rc.right-7) * lpr->finish / (lpr->max - lpr->min);
      if ( (pt.x < xOfs) && (pt.y >= 25+HEIGHTSLIDER) && (pt.y <= 39+HEIGHTSLIDER) )
	{
	  return TRUE;
	}
      break;
    }

  return FALSE;
}


BOOL SliderRightHitTest( HWND hWnd, int which, LPARAM lParam,
			 LPRANGESLIDERSTRUCT lpr )
{
  int xOfs;
  POINTS pt;

  pt = MAKEPOINTS( lParam );

  switch( which )
    {
    case TOPSLIDER:
      xOfs = (lpr->rc.right-7) * lpr->start / (lpr->max - lpr->min);
      if ( (pt.x > xOfs+7) && (pt.y >= 0) && (pt.y <= 14) )
	{
	  return TRUE;
	}
      break;

    case BOTTOMSLIDER:
      xOfs = (lpr->rc.right-7) * lpr->finish / (lpr->max - lpr->min);
      if ( (pt.x > xOfs+7) && (pt.y >= 25+HEIGHTSLIDER) && (pt.y <= 39+HEIGHTSLIDER) )
	{
	  return TRUE;
	}
      break;
    }

  return FALSE;
}


#define HEIGHTSLIDER 13
void PaintRangeSliderWnd( HWND hWnd, LPRANGESLIDERSTRUCT lpr )
{
  PAINTSTRUCT p;
  RECT rc;
  HDC hDC, hCompDC;
  HBITMAP hBmp;
  POINT pt[10];
  int w, h, xOfs, i;

  hDC = BeginPaint( hWnd, &p );
  rc = lpr->rc;

  w = rc.right;
  h = rc.bottom;

#if 1
  if ( !lpr->hCompDC )
    lpr->hCompDC = CreateCompatibleDC( hDC );
  hCompDC = lpr->hCompDC;
  if ( !lpr->hBmp )
    lpr->hBmp = CreateCompatibleBitmap( hDC, w, h );
  hBmp = lpr->hBmp;
#else
  hCompDC = CreateCompatibleDC( hDC );
  hBmp = CreateCompatibleBitmap( hDC, w, h );
#endif
  SelectObject( hCompDC, hBmp );

  FillRect( hCompDC, &rc, lpr->hBackground );

  // Draw the tic marks
  SelectObject( hCompDC, lpr->hBlackPen );
  for( i = 0; i < lpr->numTics; i++ )
    {
      xOfs = ((w - 7) * lpr->tic[i] / (lpr->max - lpr->min)) + 3;
      pt[0].x = xOfs; pt[0].y = 15;
      pt[1].x = xOfs; pt[1].y = 19;
      Polyline( hCompDC, pt, 2 );
      pt[0].y = 24 + HEIGHTSLIDER;
      pt[1].y = 20 + HEIGHTSLIDER;
      Polyline( hCompDC, pt, 2 );
    }

  rc.left = 1;
  rc.right = w - 1;
  rc.top = 20;
  rc.bottom = rc.top + HEIGHTSLIDER;
  FillRect( hCompDC, &rc, (HBRUSH)GetStockObject( WHITE_BRUSH ) );

  // draw 3-d edge
  SelectObject( hCompDC, lpr->hDkGreyPen );
  pt[0].x = rc.left; pt[0].y = rc.top + HEIGHTSLIDER - 2;
  pt[1].x = rc.left; pt[1].y = rc.top; 
  pt[2].x = rc.right - 1; pt[2].y = rc.top;
  Polyline( hCompDC, pt, 3 );

  SelectObject( hCompDC, lpr->hBlackPen );
  pt[0].x++;  pt[0].y--;
  pt[1].x++;  pt[1].y++;
  pt[2].x--;  pt[2].y++;
  Polyline( hCompDC, pt, 3 );

  SelectObject( hCompDC, lpr->hLtGreyPen );
  pt[0].y++;
  pt[1].x = rc.right-2; pt[1].y = pt[0].y;
  pt[2].x = rc.right-2; pt[2].y--;
  Polyline( hCompDC, pt, 3 );

  rc.top += 2;
  rc.bottom -= 2;
  rc.left = ((w - 7) * lpr->start / (lpr->max - lpr->min)) + 3;
  // we have to increment the right corner, since FillRect fills up to, but
  // not including the right and bottom edges.
  rc.right = ((w - 7) * lpr->finish / (lpr->max - lpr->min)) + 4;

  FillRect( hCompDC, &rc, lpr->hGreenBrush );

  BitBlt( hDC, 0, 0, w, h, hCompDC, 0, 0, SRCCOPY );

  rc.left = 3;
  rc.right = w - 4;
  rc.top = 20;
  rc.bottom = rc.top + HEIGHTSLIDER;

  //xOfs = (rc.right - rc.left) * lpr->start / (lpr->max - lpr->min);
  xOfs = (w-7) * lpr->start / (lpr->max - lpr->min);
  SelectObject( hCompDC, lpr->hTop );
  BitBlt( hDC, xOfs, 0, 7, 14, hCompDC, 0, 0, SRCCOPY );

  xOfs = (w-7) * lpr->finish / (lpr->max - lpr->min);
  SelectObject( hCompDC, lpr->hBottom );

  BitBlt( hDC, xOfs, 25 + HEIGHTSLIDER, 7, 14, hCompDC, 0, 0, SRCCOPY );

  //DeleteDC( hCompDC );
  //DeleteObject( hBmp );

  EndPaint( hWnd, &p );
}


BOOL sliderHandleLButtonDown( HWND hWnd, LPRANGESLIDERSTRUCT lpr, 
			      LPARAM lParam )
{
  POINTS pt = MAKEPOINTS( lParam );

  if ( !lpr->bInDrag )
    {
      if ( SliderHitTest( hWnd, TOPSLIDER, lParam, lpr ) )
	{
	  SetCapture( hWnd );
	  lpr->bInDrag = TRUE;
	  lpr->which = TOPSLIDER;
	}
      else if ( SliderHitTest( hWnd, BOTTOMSLIDER, lParam, lpr ) )
	{
	  SetCapture( hWnd );
	  lpr->bInDrag = TRUE;
	  lpr->which = BOTTOMSLIDER;
	  lpr->xOfsStart = (lpr->rc.right - 7) * lpr->finish / (lpr->max - lpr->min) + 3;
	}
      else if ( SliderLeftHitTest( hWnd, TOPSLIDER, lParam, lpr ) )
	{
	  SendMessage( hWnd, RSB_SNAP, TOPSLIDER, 0 );
	  return TRUE;
	}
      else if ( SliderLeftHitTest( hWnd, BOTTOMSLIDER, lParam, lpr ) )
	{
	  SendMessage( hWnd, RSB_SNAP, BOTTOMSLIDER, 0 );
	  return TRUE;
	}
      else if ( SliderRightHitTest( hWnd, TOPSLIDER, lParam, lpr ) )
	{
	  SendMessage( hWnd, RSB_SNAP, TOPSLIDER, 1 );
	  return TRUE;
	}
      else if ( SliderRightHitTest( hWnd, BOTTOMSLIDER, lParam, lpr ) )
	{
	  SendMessage( hWnd, RSB_SNAP, BOTTOMSLIDER, 1 );
	  return TRUE;
	}
      if ( lpr->bInDrag )
	{
	  lpr->xStart = pt.x;
	  lpr->yStart = pt.y;
	}
    }

  return FALSE;
}


BOOL sliderHandleLButtonUp( HWND hWnd, LPRANGESLIDERSTRUCT lpr, LPARAM lParam )
{
  if ( lpr->bInDrag )
    {
      ReleaseCapture();
      lpr->bInDrag = FALSE;
      SendSliderNotifyChanged( hWnd, lpr );
    }

  return FALSE;
}



BOOL sliderHandleMouseMove( HWND hWnd, LPRANGESLIDERSTRUCT lpr, LPARAM lParam )
{
  int xOfs;
  POINTS pt;
  DWORD dwNewValue;

  pt = MAKEPOINTS( lParam );

  if ( lpr->bInDrag )
    {
      xOfs = pt.x - 3;
      if ( xOfs < 0 )
	xOfs = 0;
      else if ( xOfs > (lpr->rc.right - 7) )
	xOfs = lpr->rc.right - 7;

      switch( lpr->which )
	{
	case TOPSLIDER:
	  dwNewValue = xOfs * (lpr->max - lpr->min) / (lpr->rc.right - 7);
	  if ( SendSliderNotifyChanging( hWnd, lpr, dwNewValue ) )
	    {
	      lpr->start = dwNewValue;
	      //SendSliderNotifyChanged( hWnd, lpr );
	    }
	  return TRUE;

	case BOTTOMSLIDER:
	  dwNewValue = xOfs * (lpr->max - lpr->min) / (lpr->rc.right - 7);
	  if ( SendSliderNotifyChanging( hWnd, lpr, dwNewValue ) )
	    {
	      lpr->finish = dwNewValue;
	      //SendSliderNotifyChanged( hWnd, lpr );
	    }
	  return TRUE;
	}
    }

  return FALSE;
}



/*
 * "Snaps" a slider either left or right to the nearest tic mark.
 *
 * wParam: which slider (TOPSLIDER or BOTTOMSLIDER)
 * lParam: left (0) or right (1)
 */
BOOL sliderHandleSnap( HWND hWnd, WPARAM wParam, BOOL bRight, LPRANGESLIDERSTRUCT lpr )
{
  int i;
  DWORD dwPos;
  DWORD dwCurrent;

  if ( (wParam != TOPSLIDER) && (wParam != BOTTOMSLIDER) )
    return FALSE;

  if ( lpr->numTics == 0 )
    return FALSE;

  if ( bRight )
    dwPos = lpr->min;
  else
    dwPos = lpr->max;

  lpr->which = (int)wParam;

  // find the leftmost or rightmost tic mark
  for( i = 0; i < lpr->numTics; i++ )
    {
      if ( bRight )
	{
	  if ( lpr->tic[i] > dwPos )
	    dwPos = lpr->tic[i];
	}
      else
	{
	  if ( lpr->tic[i] < dwPos )
	    dwPos = lpr->tic[i];
	}
    }

  dwCurrent = (wParam == TOPSLIDER)?lpr->start:lpr->finish;
  for( i = 0; i < lpr->numTics; i++ )
    {
      if ( bRight )
	{
	  if ( (lpr->tic[i] > dwCurrent) && (lpr->tic[i] < dwPos) )
	    dwPos = lpr->tic[i];
	}
      else
	{
	  if ( (lpr->tic[i] < dwCurrent) && (lpr->tic[i] > dwPos) )
	    dwPos = lpr->tic[i];
	}
    }

  lpr->which = (int)wParam;
  if ( wParam == TOPSLIDER )
    {
      if ( SendSliderNotifyChanging( hWnd, lpr, dwPos ) )
	lpr->start = dwPos;
    }
  else
    {
      if ( SendSliderNotifyChanging( hWnd, lpr, dwPos ) )
	lpr->finish = dwPos;
    }

  SendSliderNotifyChanged( hWnd, lpr );  

  return TRUE;
}


BOOL SendSliderNotifyChanging( HWND hWnd, LPRANGESLIDERSTRUCT lpr, DWORD dwNew )
{
  RSBNOTIFY rsb;

  ZeroMemory( &rsb, sizeof(rsb) );

  rsb.hdr.hwndFrom = hWnd;
  rsb.hdr.idFrom = (UINT)GetWindowLong( hWnd, GWL_ID );
  rsb.which = lpr->which;
  if ( lpr->which == TOPSLIDER )
    {
      rsb.hdr.code = RSBN_STARTCHANGING;
      rsb.newStart = dwNew;
      rsb.newFinish = lpr->finish;
    }
  else
    {
      rsb.hdr.code = RSBN_FINISHCHANGING;
      rsb.newStart = lpr->start;
      rsb.newFinish = dwNew;
    }
  rsb.start = lpr->start;
  rsb.finish = lpr->finish;

  if ( SendMessage( GetParent( hWnd ), WM_NOTIFY, (WPARAM)rsb.hdr.idFrom,
		    (LPARAM)&rsb ) )
    return TRUE;

  return FALSE;
}


BOOL SendSliderNotifyChanged( HWND hWnd, LPRANGESLIDERSTRUCT lpr )
{
  RSBNOTIFY rsb;

  ZeroMemory( &rsb, sizeof(rsb) );

  rsb.hdr.hwndFrom = hWnd;
  rsb.hdr.idFrom = (UINT)GetWindowLong( hWnd, GWL_ID );
  rsb.which = lpr->which;
  if ( lpr->which == TOPSLIDER )
    {
      rsb.hdr.code = RSBN_STARTCHANGED;
    }
  else
    {
      rsb.hdr.code = RSBN_FINISHCHANGED;
    }
  rsb.start = lpr->start;
  rsb.finish = lpr->finish;
  rsb.newStart = lpr->start;
  rsb.newFinish = lpr->finish;

  SendMessage( GetParent( hWnd ), WM_NOTIFY, (WPARAM)rsb.hdr.idFrom,
		    (LPARAM)&rsb );

  return TRUE;
}
