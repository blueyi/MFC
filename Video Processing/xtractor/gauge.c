/*
 * gauge.c - Copyright (C) 1999,2000 Jay A. Key
 *
 * Implementation of 3D-look gauge control
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
#include "gauge.h"

/*******************************************************************/
/* Typedefs                                                        */
/*******************************************************************/
typedef struct
{
  UINT     uRange;
  UINT     uPosition;
  COLORREF rgbTextColor;
  COLORREF rgbBkColor;
  HPEN     hDarkGrayPen;
  HPEN     hLiteGrayPen;
  HBRUSH   hFgBrush;
  HBRUSH   hStockWhiteBrush;
  BOOL     bDispPct;
  HDC      hDC;
  HBITMAP  hBmp;
} GAUGESTRUCT, FAR *LPGAUGESTRUCT;


/*******************************************************************/
/* Local Variables                                                 */
/*******************************************************************/
char szGaugeClassName[] = "AKProgMeter";


/*******************************************************************/
/* Prototypes                                                      */
/*******************************************************************/
LRESULT CALLBACK GaugeWndProc( HWND, UINT, WPARAM, LPARAM );
void PaintGauge( HWND hWnd );
void InitGaugeWnd( HWND hWnd );
UINT percent( UINT a, UINT b );

#define INVRECT FALSE


BOOL InitGauge( HINSTANCE hInst )
{
  static BOOL bRegistered = FALSE;
  WNDCLASSEX wc;

  if ( bRegistered )
    return TRUE;

  ZeroMemory( &wc, sizeof(wc) );
  wc.cbSize        = sizeof(wc);
  wc.style         = CS_HREDRAW | CS_VREDRAW | CS_PARENTDC;
  wc.lpfnWndProc   = (WNDPROC)GaugeWndProc;
  wc.hInstance     = hInst;
  wc.hCursor       = LoadCursor( NULL, IDC_ARROW );
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wc.lpszClassName = szGaugeClassName;

  if ( !RegisterClassEx( &wc ) )
    return FALSE;

  bRegistered = TRUE;

  return TRUE;
}


void InitGaugeWnd( HWND hWnd )
{
  LPGAUGESTRUCT lpg;
  LOGBRUSH lb;
  HDC hDC;
  RECT rc;
  int x, y;

  lpg = GlobalAlloc( GPTR, sizeof(GAUGESTRUCT) );

  hDC = GetDC( hWnd );
  GetClientRect( hWnd, &rc );
  x = rc.right - rc.left + 2;
  y = rc.bottom - rc.top + 2;
  lpg->hBmp = CreateCompatibleBitmap( hDC, x, y );
  lpg->hDC = CreateCompatibleDC( hDC );
  SelectObject( lpg->hDC, lpg->hBmp );
  ReleaseDC( hWnd, hDC );

  lpg->uRange        = 100;
  lpg->uPosition     = 0;
  lpg->rgbTextColor  = RGB( 0, 255, 0 );
  lpg->rgbBkColor    = RGB( 255, 255, 255 );
  lpg->bDispPct      = TRUE;
  lpg->hDarkGrayPen  = CreatePen( PS_SOLID, 1, RGB(128, 128, 128) );
  lpg->hLiteGrayPen  = CreatePen( PS_SOLID, 1, RGB(192, 192, 192) );
  lb.lbStyle         = PS_SOLID;
  lb.lbColor         = RGB( 0, 255, 0 );
  lpg->hFgBrush      = CreateBrushIndirect( &lb );
  lpg->hStockWhiteBrush = (HBRUSH)GetStockObject( WHITE_BRUSH );
  
  SetWindowLong( hWnd, GWL_USERDATA, (LONG)lpg );
}


LRESULT CALLBACK GaugeWndProc( HWND hWnd, UINT uMsg, WPARAM wParam,
			       LPARAM lParam )
{
  LPGAUGESTRUCT lpg;
  UINT uNewPos;
  BOOL bRepaint;

  lpg = (LPGAUGESTRUCT)GetWindowLong( hWnd, GWL_USERDATA );

  switch( uMsg )
    {
    case WM_CREATE:
      InitGaugeWnd( hWnd );
      break;

    case WM_DESTROY:
      DeleteObject( lpg->hDarkGrayPen );
      DeleteObject( lpg->hLiteGrayPen );
      DeleteObject( lpg->hFgBrush );
      DeleteDC( lpg->hDC );
      DeleteObject( lpg->hBmp );
      GlobalFree( lpg );
      return DefWindowProc( hWnd, uMsg, wParam, lParam );

    case WM_PAINT:
      PaintGauge( hWnd );
      break;

    case GM_SETRANGE:
      lpg->uRange = (UINT)wParam;
      if ( lpg->uPosition > lpg->uRange )
	lpg->uPosition = lpg->uRange;
      InvalidateRect( hWnd, NULL, INVRECT );
      UpdateWindow( hWnd );
      break;

    case GM_GETRANGE:
      return (LRESULT)lpg->uRange;

    case GM_SETPOS:
      bRepaint = ( percent( lpg->uPosition, lpg->uRange ) !=
		   percent( (UINT)wParam, lpg->uRange ) );
      lpg->uPosition = (UINT)wParam;
      if ( bRepaint )
	{
	  InvalidateRect( hWnd, NULL, INVRECT );
	  UpdateWindow( hWnd );
	}
      break;

    case GM_GETPOS:
      return (LRESULT)lpg->uPosition;

    case GM_SETDELTAPOS:
      uNewPos = (UINT)((int)lpg->uPosition + (int)wParam);
      bRepaint = ( percent( lpg->uPosition, lpg->uRange ) !=
		   percent( uNewPos, lpg->uRange ) );
      lpg->uPosition = uNewPos;
      if ( lpg->uPosition > lpg->uRange )
	lpg->uPosition = lpg->uRange;
      if ( bRepaint )
	{
	  InvalidateRect( hWnd, NULL, INVRECT );
	  UpdateWindow( hWnd );
	}
      break;

    case GM_DISPPCT:
      lpg->bDispPct = (BOOL)wParam;
      InvalidateRect( hWnd, NULL, INVRECT );
      UpdateWindow( hWnd );
      break;

    default:
      return DefWindowProc( hWnd, uMsg, wParam, lParam );
    }

  return 0L;
}


void PaintGauge( HWND hWnd )
{
  RECT rc, rc1;
  HDC hDC;
  PAINTSTRUCT ps;
  HPEN hOldPen;
  LPGAUGESTRUCT lpg;
  int x;
  float f;
  char buf[81];
  SIZE textSize;

  lpg = (LPGAUGESTRUCT)GetWindowLong( hWnd, GWL_USERDATA );
  if ( !lpg )
    return;

  hDC = BeginPaint( hWnd, &ps );

  // draw the 3-d indent
  GetClientRect( hWnd, &rc );

  FillRect( lpg->hDC, &rc, lpg->hStockWhiteBrush );

  hOldPen = SelectObject( lpg->hDC, GetStockObject( BLACK_PEN ) );
  MoveToEx( lpg->hDC, rc.left+1, rc.bottom-3, NULL );
  LineTo( lpg->hDC, rc.left+1, rc.top+1 );
  LineTo( lpg->hDC, rc.right-2, rc.top+1 );

  SelectObject( lpg->hDC, lpg->hDarkGrayPen );
  MoveToEx( lpg->hDC, rc.left, rc.bottom-2, NULL );
  LineTo( lpg->hDC, rc.left, rc.top );
  LineTo( lpg->hDC, rc.right-1, rc.top );

  SelectObject( lpg->hDC, lpg->hLiteGrayPen );
  MoveToEx( lpg->hDC, rc.left+1, rc.bottom-2, NULL );
  LineTo( lpg->hDC, rc.right-2, rc.bottom-2 );
  LineTo( lpg->hDC, rc.right-2, rc.top );

  // draw the percentage
  f = (float)100.0 * (float)lpg->uPosition / (float)lpg->uRange;
  if ( lpg->bDispPct )
    {
      sprintf( buf, "%1.1f", f );
      lstrcat( buf, "%" );
    }
  else
    lstrcpy( buf, "" );

  InflateRect( &rc, -2, -2 );
  rc1 = rc;
  x = rc.right - rc.left + 1;
  rc1.right = rc.left + (int)((float)x * f / 100.0);

  SetBkColor( lpg->hDC, lpg->rgbTextColor );
  SetTextColor( lpg->hDC, RGB(0,0,0) );

  GetTextExtentPoint32( lpg->hDC, buf, lstrlen( buf ), &textSize );
  ExtTextOut( lpg->hDC, (rc.right-rc.left+1-textSize.cx)/2,
	      (rc.bottom-rc.top+1-textSize.cy)/2 + 1,
	      ETO_OPAQUE | ETO_CLIPPED, &rc1, buf, lstrlen( buf ), NULL );

  SetBkColor( lpg->hDC, lpg->rgbBkColor );
  SetTextColor( lpg->hDC, RGB(0,0,0) );

  rc1.left = rc1.right;
  rc1.right = rc.right;

  ExtTextOut( lpg->hDC, (rc.right-rc.left+1-textSize.cx)/2,
	      (rc.bottom-rc.top+1-textSize.cy)/2 + 1,
	      ETO_OPAQUE | ETO_CLIPPED, &rc1, buf, lstrlen( buf ), NULL );

  SelectObject( lpg->hDC, hOldPen );

  GetClientRect( hWnd, &rc );
  BitBlt( hDC, 0, 0, rc.right, rc.bottom, 
	  lpg->hDC, 0, 0, SRCCOPY );

  EndPaint( hWnd, &ps );
}


UINT percent( UINT a, UINT b )
{
  return ( a * 1000 ) / b;
}
