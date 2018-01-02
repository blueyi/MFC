/*
 * config.c - Copyright (C) 1999,2000 Jay A. Key
 *
 * Creates and displays the configuration property sheet.
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
#include "resources.h"
#include "globals.h"
#include "gauge.h"
#include "statusbar.h"
#include "controls/treeopt.h"

#if (__IBMC__)                         /* BWT (20000127)                   */
WINCOMMCTRLAPI void WINAPI InitCommonControls(void);   /* BWT (20000127)   */
#endif                                 /* BWT (20000127)                   */

void GetSetOutputDlgCurrentVals( BOOL bGet );
void GetSetCDDlgCurrentVals( BOOL bGet );
void GetSetMP3DlgCurrentVals( BOOL bGet );
void GetSetCDDBDlgCurrentVals( BOOL bGet );
void GetSetMiscDlgCurrentVals( BOOL bGet );
void GetSetVorbDlgCurrentVals( BOOL bGet );

void centerDialog( HWND hWnd );
BOOL CALLBACK GenericDlgProc( HWND hWnd, UINT uMsg, WPARAM wParam,
                             LPARAM lParam );
BOOL CALLBACK CDDlgProc( HWND hWnd, UINT uMsg, WPARAM wParam,
                             LPARAM lParam );
BOOL CALLBACK OutputDlgProc( HWND hWnd, UINT uMsg, WPARAM wParam,
                             LPARAM lParam );
BOOL CALLBACK MP3DlgProc( HWND hWnd, UINT uMsg, WPARAM wParam,
                             LPARAM lParam );
BOOL CALLBACK CDDBDlgProc( HWND hWnd, UINT uMsg, WPARAM wParam,
                           LPARAM lParam );
BOOL CALLBACK ProxyDlgProc( HWND hWnd, UINT uMsg, WPARAM wParam,
                           LPARAM lParam );
BOOL CALLBACK MiscDlgProc( HWND hWnd, UINT uMsg, WPARAM wParam,
			   LPARAM lParam );
BOOL CALLBACK VorbDlgProc( HWND hWnd, UINT uMsg, WPARAM wParam,
			   LPARAM lParam );


void centerDialog( HWND hWnd )
{
  RECT r, rs;
  LONG x, y, w, h;

  if ( !hWnd )
    return;

  GetWindowRect( hWnd, &r );
  GetWindowRect( GetDesktopWindow(), &rs );
  w = r.right - r.left;
  h = r.bottom - r.top;
  x = ( rs.left + rs.right ) / 2 - ( w / 2 );
  y = ( rs.top + rs.bottom ) / 2 - ( h / 2 );
  MoveWindow( hWnd, x, y, w, h, TRUE );
}


BOOL CALLBACK GenericDlgProc( HWND hWnd, UINT uMsg, WPARAM wParam,
                             LPARAM lParam )
{
  //char buf[81];
  NMHDR *l = (NMHDR *)lParam;
  //WORD wID;

  switch( uMsg )
    {
    case WM_COMMAND:
      //wID = LOWORD( wParam );
      break;

    case WM_CREATE:
      break;

    case WM_NOTIFY:
      switch( l->code )
        {
        case PSN_SETACTIVE:  // sent before page is shown
          break;

        case PSN_KILLACTIVE:  //losing focus
          SetWindowLong( hWnd, DWL_MSGRESULT, FALSE );
          break;

        case PSN_QUERYCANCEL:
          break;

        case PSN_APPLY:
          break;

        case PSN_HELP:
          break;

        case PSN_RESET:
          break;

        default:
          break;
        }
      break;
    }

  return FALSE;
}


int DoConfig( HWND hParent, HINSTANCE hInst, UINT uiStartPage )
{
  CTPREFDIALOG prefDlg;
  PREFSHEET prefSheet[7];
  
  int retVal;
//  int i = 0;

  ZeroMemory( &prefDlg, sizeof(prefDlg) );
  prefDlg.hWndParent = hParent;
  prefDlg.hInst = hInst;
  prefDlg.lpszTitle = "CD-DA X-Tractor Options";
  prefDlg.lpPrefSheet = prefSheet;

  ZeroMemory( &prefSheet[0], sizeof(PREFSHEET) );
  prefSheet[0].lpszTemplate  = "CDControlDialog";
  prefSheet[0].lpszCaption   = "CD Options";
  prefSheet[0].dlgproc       = CDDlgProc;
  prefSheet[0].sibling       = &prefSheet[1];

  ZeroMemory( &prefSheet[1], sizeof(PREFSHEET) );
  prefSheet[1].lpszTemplate  = "DirectoryDialog";
  prefSheet[1].lpszCaption   = "Output Options";
  prefSheet[1].dlgproc       = OutputDlgProc;
  prefSheet[1].sibling       = &prefSheet[2];

  ZeroMemory( &prefSheet[2], sizeof(PREFSHEET) );
  prefSheet[2].lpszTemplate  = "MP3OptionsDialog";
  prefSheet[2].lpszCaption   = "MP3 Options";
  prefSheet[2].dlgproc       = MP3DlgProc;
  prefSheet[2].sibling       = &prefSheet[3];

  ZeroMemory( &prefSheet[3], sizeof(PREFSHEET) );
  prefSheet[3].lpszTemplate  = "VorbOptionsDialog";
  prefSheet[3].lpszCaption   = "Ogg Vorbis Options";
  prefSheet[3].dlgproc       = VorbDlgProc;
  prefSheet[3].sibling       = &prefSheet[4];

  ZeroMemory( &prefSheet[4], sizeof(PREFSHEET) );
  prefSheet[4].lpszTemplate  = "CDDBOptionsDialog";
  prefSheet[4].lpszCaption   = "Freedb Options";
  prefSheet[4].dlgproc       = CDDBDlgProc;
  prefSheet[4].sibling       = &prefSheet[5];
  prefSheet[4].child         = &prefSheet[6];

  ZeroMemory( &prefSheet[5], sizeof(PREFSHEET) );
  prefSheet[5].lpszTemplate  = "MiscOptionsDialog";
  prefSheet[5].lpszCaption   = "Miscellaneous Options";
  prefSheet[5].dlgproc       = MiscDlgProc;
  prefSheet[5].sibling       = NULL;

  ZeroMemory( &prefSheet[6], sizeof(PREFSHEET) );
  prefSheet[6].lpszTemplate  = "ProxyOptionsDialog";
  prefSheet[6].lpszCaption   = "HTTP Proxy Settings";
  prefSheet[6].dlgproc       = ProxyDlgProc;
  prefSheet[6].sibling       = NULL;

  prefSheet[uiStartPage].isDefault = TRUE;

  GetSetCDDlgCurrentVals( TRUE );  // read current values
  GetSetOutputDlgCurrentVals( TRUE );  // read current values
  GetSetMP3DlgCurrentVals( TRUE );
  GetSetCDDBDlgCurrentVals( TRUE );
  GetSetMiscDlgCurrentVals( TRUE );
  GetSetVorbDlgCurrentVals( TRUE );

  retVal = CreateTreeOptionDialog( &prefDlg );

  // cancel == 0; OK == 1; 
  if ( retVal <= 0 )
    return 0;  

  // save the info
  GetSetCDDlgCurrentVals( FALSE );
  GetSetOutputDlgCurrentVals( FALSE );
  GetSetMP3DlgCurrentVals( FALSE );
  GetSetCDDBDlgCurrentVals( FALSE );
  GetSetMiscDlgCurrentVals( FALSE );
  GetSetVorbDlgCurrentVals( FALSE );

  UpdateStatusBar();

  return 0;
}


#if 0
int DoConfigOld( HWND hParent, HINSTANCE hInst, UINT uiStartPage )
{
  HPROPSHEETPAGE hPg[6];
  PROPSHEETPAGE p;
  PROPSHEETHEADER ph;
  //char buf[81];
  int retVal;
  int i = 0;

  InitCommonControls();

  memset( &p, 0, sizeof(p) );
  p.dwSize      = sizeof(p);
  p.dwFlags     = PSP_DEFAULT;
  p.hInstance   = hInst;
#ifdef __GNUC__
  p.u.pszTemplate = "CDControlDialog";
#else
  p.pszTemplate = "CDControlDialog";
#endif
  p.pfnDlgProc  = (DLGPROC)CDDlgProc;

  hPg[i++] = CreatePropertySheetPage( &p );

  memset( &p, 0, sizeof(p) );
  p.dwSize      = sizeof(p);
  p.dwFlags     = PSP_DEFAULT;
  p.hInstance   = hInst;
#ifdef __GNUC__
  p.u.pszTemplate = "DirectoryDialog";
#else
  p.pszTemplate = "DirectoryDialog";
#endif
  p.pfnDlgProc  = (DLGPROC)OutputDlgProc;

  hPg[i++] = CreatePropertySheetPage( &p );

  memset( &p, 0, sizeof(p) );
  p.dwSize      = sizeof(p);
  p.dwFlags     = PSP_DEFAULT;
  p.hInstance   = hInst;
#ifdef __GNUC__
  p.u.pszTemplate = "MP3OptionsDialog";
#else
  p.pszTemplate = "MP3OptionsDialog";
#endif
  p.pfnDlgProc  = (DLGPROC)MP3DlgProc;

  hPg[i++] = CreatePropertySheetPage( &p );

  memset( &p, 0, sizeof(p) );
  p.dwSize      = sizeof(p);
  p.dwFlags     = PSP_DEFAULT;
  p.hInstance   = hInst;
#ifdef __GNUC__
  p.u.pszTemplate = "VorbOptionsDialog";
#else
  p.pszTemplate = "VorbOptionsDialog";
#endif
  p.pfnDlgProc  = (DLGPROC)VorbDlgProc;

  hPg[i++] = CreatePropertySheetPage( &p );

  memset( &p, 0, sizeof(p) );
  p.dwSize      = sizeof(p);
  p.dwFlags     = PSP_DEFAULT;
  p.hInstance   = hInst;
#ifdef __GNUC__
  p.u.pszTemplate = "CDDBOptionsDialog";
#else
  p.pszTemplate = "CDDBOptionsDialog";
#endif
  p.pfnDlgProc  = (DLGPROC)CDDBDlgProc;

  hPg[i++] = CreatePropertySheetPage( &p );

  memset( &p, 0, sizeof(p) );
  p.dwSize      = sizeof(p);
  p.dwFlags     = PSP_DEFAULT;
  p.hInstance   = hInst;
#ifdef __GNUC__
  p.u.pszTemplate = "MiscOptionsDialog";
#else
  p.pszTemplate = "MiscOptionsDialog";
#endif
  p.pfnDlgProc  = (DLGPROC)MiscDlgProc;

  hPg[i++] = CreatePropertySheetPage( &p );

  memset( &ph, 0, sizeof(ph) );
  ph.dwSize      = sizeof(ph);
  ph.dwFlags     = PSH_DEFAULT;
  ph.hwndParent  = hParent;
  ph.hInstance   = hInst;
#ifdef __GNUC__
  ph.u.pszIcon  = "GUIRIPLG";
  ph.u2.nStartPage = uiStartPage;
  ph.u3.phpage   = hPg;
#else
  ph.pszIcon  = "GUIRIPLG";
  ph.nStartPage = uiStartPage;
  ph.phpage   = hPg;
#endif
  ph.pszCaption  = "CD-DA X-Tractor Options";
  ph.nPages      = i;

  GetSetCDDlgCurrentVals( TRUE );  // read current values
  GetSetOutputDlgCurrentVals( TRUE );  // read current values
  GetSetMP3DlgCurrentVals( TRUE );
  GetSetCDDBDlgCurrentVals( TRUE );
  GetSetMiscDlgCurrentVals( TRUE );
  GetSetVorbDlgCurrentVals( TRUE );

  retVal = PropertySheet( &ph );

  // cancel == 0; OK == 1; 
  if ( retVal <= 0 )
    return 0;  

  // save the info
  GetSetCDDlgCurrentVals( FALSE );
  GetSetOutputDlgCurrentVals( FALSE );
  GetSetMP3DlgCurrentVals( FALSE );
  GetSetCDDBDlgCurrentVals( FALSE );
  GetSetMiscDlgCurrentVals( FALSE );
  GetSetVorbDlgCurrentVals( FALSE );

  UpdateStatusBar();

  return 0;
}
#endif
