/*
 * about.c - Copyright (C) 1999,2000 Jay A. Key
 *
 * "About" dialog for CD-DA X-Tractor
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
#include "resources.h"
#include "globals.h"
#include "enc/bladedll.h"
#include "enc/xtenc.h"

LRESULT CALLBACK BmpPanelProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
void PaintBmpPanel( HWND hWnd );
LPWORD lpwAlign( LPWORD lpIn );
void SetAboutDlgText( HWND hWnd );
void GetVersionInfo( int iEnc, BE_VERSION *bev );

BOOL CALLBACK AboutDialogProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
  lParam = lParam;
  switch( uMsg )
    {
    case WM_INITDIALOG:
      CreateWindowEx( WS_EX_CLIENTEDGE, szBmpPanel, "",
		      WS_CHILD | WS_VISIBLE, 8, 8, 124, 164,
		      hWnd, (HMENU)ID_BMPPANEL, ghInstance, "AboutBmp" );
      SetAboutDlgText( hWnd );
      break;

    case WM_COMMAND:
      switch( LOWORD(wParam) )
	{
	case IDCANCEL:
	case IDBN_ABOUTOK:
	  EndDialog( hWnd, 0 );
	  break;
	}
      break;

    default:
      return FALSE;
    }

  return TRUE;
}


void InitBmpPanel( void )
{
  WNDCLASSEX wc;

  if ( !atomBmpPanel )
    {
      ZeroMemory( &wc, sizeof(wc) );
      wc.cbSize      = sizeof(wc);
      wc.style       = CS_HREDRAW | CS_VREDRAW;
      wc.lpfnWndProc = BmpPanelProc;
      wc.hInstance   = ghInstance;
      wc.hCursor     = LoadCursor( NULL, IDC_ARROW );
      wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
      wc.lpszClassName = szBmpPanel;

      atomBmpPanel = RegisterClassEx( &wc );
    }
}


LRESULT CALLBACK BmpPanelProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
  HBITMAP hBmp;
  LPBYTE lpb;

  switch( uMsg )
    {
    case WM_CREATE:
      lpb = (LPBYTE)((LPCREATESTRUCT)lParam)->lpCreateParams;
      hBmp = LoadBitmap( ghInstance, (char *)lpb );
      if ( hBmp )
	{
	  SetWindowLong( hWnd, GWL_USERDATA, (LONG)hBmp );
	}
      break;

    case WM_PAINT:
      PaintBmpPanel( hWnd );
      break;

    case WM_DESTROY:
      return DefWindowProc( hWnd, uMsg, wParam, lParam );
    }
  return DefWindowProc( hWnd, uMsg, wParam, lParam );
}


void PaintBmpPanel( HWND hWnd )
{
  HDC hDC, hCompDC;
  HBITMAP hBmp;
  PAINTSTRUCT ps;
  RECT rc;

  hDC = BeginPaint( hWnd, &ps );

  hBmp = (HBITMAP)GetWindowLong( hWnd, GWL_USERDATA );
  if ( hBmp )
    {
      hCompDC = CreateCompatibleDC( hDC );
      SelectObject( hCompDC, hBmp );
      GetClientRect( hWnd, &rc );
      BitBlt( hDC, 0, 0, rc.right, rc.bottom, hCompDC, 0, 0, SRCCOPY );
      DeleteDC( hCompDC );
    }
  EndPaint( hWnd, &ps );
}


/*
 * Create dialog that is 320x200 pixels, centered.
 */
void DynamicAboutDialog( HWND hParent )
{
  LPDLGTEMPLATE lpDlg;
  LPDLGITEMTEMPLATE lpDlgItem;
  LPBYTE lpMem;
  LONG dlgbase;
  int n;

  dlgbase = GetDialogBaseUnits();

  lpMem = GlobalAlloc( GPTR, 2048 );
  lpDlg = (LPDLGTEMPLATE)lpMem;

  lpDlg->style     = DS_MODALFRAME | WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_CHILD | WS_POPUP | WS_OVERLAPPED | DS_SETFOREGROUND;
  lpDlg->cdit      = 2;
  lpDlg->x         = 0;
  lpDlg->y         = 0;
  lpDlg->cx        = 320 * 4 / LOWORD( dlgbase );
  lpDlg->cy        = 210 * 8 / HIWORD( dlgbase );

  lpMem += sizeof(DLGTEMPLATE);
  lpMem += 4;   // dialog has no menu and uses the default class
  n = MultiByteToWideChar( CP_ACP, 0, "About CD-DA X-Tractor", -1, (LPWSTR)lpMem, 256 );
  lpMem += (n * 2);

  lpMem = (LPBYTE)lpwAlign( (LPWORD)lpMem );

  /*
   * Add a push button control
   */
  // add the pushbutton
  lpDlgItem = (LPDLGITEMTEMPLATE)lpMem;
  lpDlgItem->style  = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON;
  lpDlgItem->x      = 34 * 4 / LOWORD( dlgbase );
  lpDlgItem->y      = 180 * 8 / HIWORD( dlgbase );
  lpDlgItem->cx     = 60 * 4 / LOWORD( dlgbase );
  lpDlgItem->cy     = 24 * 8 / HIWORD( dlgbase );
  lpDlgItem->id     = IDBN_ABOUTOK;

  lpMem += sizeof(DLGITEMTEMPLATE);
  // class
  lpMem[0] = 0xFF;
  lpMem[1] = 0xFF;
  lpMem[2] = 0x80;
  lpMem[3] = 0x00;
  // unicode string
  lpMem[4] = 'O';
  lpMem[5] = 0;
  lpMem[6] = 'K';
  lpMem[7] = 0;
  lpMem[8] = 0;
  lpMem[9] = 0;
  // creation data
  lpMem[10] = 0;
  lpMem[11] = 0;
  lpMem += 12;

  lpMem = (LPBYTE)lpwAlign( (LPWORD)lpMem );

  /*
   * Add another control
   */
  lpDlgItem = (LPDLGITEMTEMPLATE)lpMem;
  lpDlgItem->style  = WS_CHILD | WS_VISIBLE;
  lpDlgItem->x      = 160 * 4 / LOWORD( dlgbase );
  lpDlgItem->y      = 28 * 8 / HIWORD( dlgbase );
  lpDlgItem->cx     = 150 * 4 / LOWORD( dlgbase );
  lpDlgItem->cy     = 156 * 8 / HIWORD( dlgbase );
  lpDlgItem->id     = IDT_ABOUTTXT;

  lpMem += sizeof(DLGITEMTEMPLATE);
  lpMem[0] = 0xFF;
  lpMem[1] = 0xFF;
  lpMem[2] = 0x82;
  lpMem[3] = 0x00;
  lpMem[4] = 0;
  lpMem[5] = 0;
  lpMem[6] = 0;
  lpMem[7] = 0;

  if ( DialogBoxIndirect( ghInstance, lpDlg, hParent, AboutDialogProc ) == -1 )
    {
      //wsprintf( (char *)lpDlg, "DialogBoxIndirect() == -1, GetLastError() == %d", GetLastError() );
      //OutputDebugString( (char *)lpDlg );
    }

  GlobalFree( lpDlg );
}


LPWORD lpwAlign( LPWORD lpIn )
{
  ULONG ul;

  ul = (ULONG)lpIn;
  ul += 3;
  ul >>= 2;
  ul <<= 2;
  return (LPWORD)ul;
}


void SetAboutDlgText( HWND hWnd )
{
  char buf[256];
  char *p;
  BE_VERSION bev;

  wsprintf( buf, "CD-DA X-Tractor %s\n\nReleased under the GNU Public License.\n\n", szVersion );
  p = buf + lstrlen(buf);
  switch( iEncoder )
    {
    case XT_ENC_RAW:
      wsprintf( p, "No encoder selected.\n\n" );
      break;
    case XT_ENC_WAV:
      wsprintf( p, "Using internal WAV encoder.\n\n" );
      break;
    case XT_ENC_BLADE:
      GetVersionInfo( XT_ENC_BLADE, &bev );
      wsprintf( p, "MP3 encoder:\nBladeEnc DLL v%d.%02d (engine v%d.%02d).\n\n", bev.byDLLMajorVersion, bev.byDLLMinorVersion, bev.byMajorVersion, bev.byMinorVersion );
      break;
    case XT_ENC_LAME1:
    case XT_ENC_LAME2:
      GetVersionInfo( XT_ENC_LAME1, &bev );
      wsprintf( p, "MP3 encoder:\nLame_Enc DLL v%d.%02d (engine v%d.%02d).\n\n", bev.byDLLMajorVersion, bev.byDLLMinorVersion, bev.byMajorVersion, bev.byMinorVersion );
      break;
    case XT_ENC_VORBIS:
      GetVersionInfo( XT_ENC_VORBIS, &bev );
      wsprintf( p, "Ogg Vorbis encoder:\nVorb_Enc DLL v%d.%02d (engine v%d.%02d).\n\n", bev.byDLLMajorVersion, bev.byDLLMinorVersion, bev.byMajorVersion, bev.byMinorVersion );
      break;
    }

  SetDlgItemText( hWnd, IDT_ABOUTTXT, buf );
}



BOOL CALLBACK CDPropertiesDlgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
  lParam = lParam;

  switch( uMsg )
    {
    case WM_INITDIALOG:
      break;

    case WM_DESTROY:
      break;

    case WM_COMMAND:
      switch( LOWORD(wParam) )
	{
	case IDCANCEL:
	case IDBN_ABOUTOK:
	  EndDialog( hWnd, 0 );
	  break;
	}
      break;

    default:
      return FALSE;
    }

  return TRUE;
}


void GetVersionInfo( int iEnc, BE_VERSION *bev )
{
  HMODULE hDLL = NULL;

  ZeroMemory( bev, sizeof(BE_VERSION) );
  switch( iEnc )
    {
    case XT_ENC_LAME1:
    case XT_ENC_LAME2:
      hDLL = LoadLibrary( "lame_enc.dll" );
      break;

    case XT_ENC_BLADE:
      hDLL = LoadLibrary( "bladeenc.dll" );
      break;

    case XT_ENC_VORBIS:
      hDLL = LoadLibrary( "vorb_enc.dll" );
      break;
    }

  if ( hDLL )
    {
      BEVERSION beVersion;

      beVersion = (BEVERSION)GetProcAddress( hDLL, "beVersion" );
      if ( beVersion )
	beVersion( bev );
      FreeLibrary( hDLL );
    }
}
