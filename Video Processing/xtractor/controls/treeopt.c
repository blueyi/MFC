/*
 * treeopt.c - Copyright (C) 1999,2000 Jay A. Key
 *
 * Implementation of a property sheet dialog with a TreeView control
 * on the left, rather than tabs on the top.
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
#include <stdio.h>
#include <malloc.h>
#include "treeopt.h"

void dbprintf( char *fmt, ... );

typedef struct _tag_int_prefsheet {
  LPCTSTR lpszTemplate;        // the dialog template to use
  DLGPROC dlgproc;             // callback function
  BOOL isDefault;
  HWND hWnd;
  char szCaption[257];
  struct _tag_int_prefsheet *sibling;
  struct _tag_int_prefsheet *child;
} INTPREFSHEET, *LPINTPREFSHEET;


typedef struct {
  char szCaption[1024];
  HINSTANCE hInst;
  short cx;
  short cy;
  short dx;
  short dy;
  LPCTPREFDIALOG lpPrefDlg;
  LPINTPREFSHEET lpPrefSheet;
  HWND hCurrentPrefWnd;
} PREFDLGEXTRA, *LPPREFDLGEXTRA;

typedef int (* SENDNOTIFY)(HWND, HWND);

LPWORD lpwAlign( LPWORD lpIn );
BOOL CALLBACK TreeOptionDialogProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
int createButton( LPBYTE lpStart, LPCSTR lpszText, DWORD style, short x, short y, short cx, short cy, WORD id ) ;
int createStatic( LPBYTE lpStart, LPCSTR lpszText, DWORD style, short x, short y, short cx, short cy, WORD id ) ;
int createEdit( LPBYTE lpStart, LPCSTR lpszText, DWORD style, short x, short y, short cx, short cy, WORD id );
void paintCaption( HWND hWnd );
void computeDialogDimensions( LPINTPREFSHEET lpParent, short *cx, short *cy );
void initializeDialog( HWND hWnd, HGLOBAL hMem );
HTREEITEM insertPrefPageTitles( HWND hWnd, LPINTPREFSHEET lpSheet, HTREEITEM hParent );
BOOL HandleTreeMessage( HWND, LPARAM, LPPREFDLGEXTRA );
void computeDialogOffset( HWND hWnd, HGLOBAL hMem );
char *treeMessage2String( int code );
void modifyDialogStyle( LPDLGTEMPLATE lpDlg );
LPINTPREFSHEET copyPrefSheets( LPPREFSHEET sheets );
void freePrefSheets( LPINTPREFSHEET lpSheet );
BOOL sendNotifications( HWND hParent, LPINTPREFSHEET lpSheet, SENDNOTIFY func );
int sendSetActive( HWND hParent, HWND hPage );
int sendKillActive( HWND hParent, HWND hPage );
int sendApply( HWND hParent, HWND hPage );
int sendQueryCancel( HWND hParent, HWND hPage );


#define IDBN_CANCEL     9001
#define IDBN_OK         9002
#define ID_TREEVIEW     9003
#define IDPLACEHOLDER   9004
#define IDCAPTION       9005
#define IDBN_APPLY      9006

static int cnt = 0;

#include <pshpack2.h>
typedef struct {
    WORD   dlgVer; // 0x001
    WORD   signature; // 0xFFFF
    DWORD  helpID;
    DWORD  exStyle;
    DWORD  style;
    WORD   cDlgItems;
    short  x;
    short  y;
    short  cx;
    short  cy;
} DLGTEMPLATEEX;
#include <poppack.h> /* Resume normal packing */


BOOL WINAPI DllMain( HANDLE hModule, DWORD dwReason, LPVOID lpReserved )
{
  switch( dwReason )
    {
    case DLL_PROCESS_ATTACH:
      OutputDebugString( "DLL_PROCESS_ATTACH" );
      break;
    case DLL_PROCESS_DETACH:
      OutputDebugString( "DLL_PROCESS_DETACH" );
      break;
    case DLL_THREAD_ATTACH:
      OutputDebugString( "DLL_THREAD_ATTACH" );
      break;
    case DLL_THREAD_DETACH:
      OutputDebugString( "DLL_THREAD_ATTACH" );
      break;
    }
  return TRUE;
}



int CreateTreeOptionDialog( LPCTPREFDIALOG lpPrefDlg )
{
  LPDLGTEMPLATE lpDlg;
  LPDLGITEMTEMPLATE lpDlgItem;
  LPBYTE lpMem;
  HGLOBAL hMem, hMemExtra;
  LONG dlgbase;
  int n;
  int x, y, w, h;
  short cx, cy;
  INITCOMMONCONTROLSEX ic;
  LPPREFDLGEXTRA dlgextra;
//  LPSTR lpszTitle;
  int retval;
  
  
  ic.dwSize = sizeof(ic);
  ic.dwICC = ICC_WIN95_CLASSES;
  InitCommonControlsEx( &ic );
  
  dlgbase = GetDialogBaseUnits();
  
  hMemExtra = GlobalAlloc( GMEM_ZEROINIT, sizeof(PREFDLGEXTRA) );
  dlgextra = (LPPREFDLGEXTRA)GlobalLock( hMemExtra );
  
  dlgextra->lpPrefSheet = copyPrefSheets( lpPrefDlg->lpPrefSheet );
  
  hMem = GlobalAlloc( GMEM_ZEROINIT, 4096 );
  lpMem = (LPBYTE)GlobalLock( hMem );

  w = 263;
  h = 218;
  x = 0;
  y = 0;
  
  cx = 263 - 71;
  cy = 218 - 53;
  
  computeDialogDimensions( dlgextra->lpPrefSheet, &cx, &cy );

  // set width to cx+81, heigth= cy+53
  w = cx + 71;
  h = cy + 53;
  
  
  lpDlg = (LPDLGTEMPLATE)lpMem;
  lpDlg->style = WS_POPUP | WS_BORDER | WS_SYSMENU | DS_MODALFRAME | WS_CAPTION | DS_SETFOREGROUND | DS_3DLOOK | DS_SETFONT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
  lpDlg->cdit      = 6;
  lpDlg->x         = 10;
  lpDlg->y         = 10;
  lpDlg->cx        = w;
  lpDlg->cy        = h;
  lpMem += sizeof(DLGTEMPLATE);
  lpMem += 4;  // add two NULL words to signify that we don't have a menu or class
  n = MultiByteToWideChar( CP_ACP, 0, lpPrefDlg->lpszTitle, -1, (LPWSTR)lpMem, 256 );
  lpMem += (n * 2);
#if 1
  // add font since we specified DS_SETFONT, 8pt MS Sans Serif
  lpMem[0]         = 8;
  lpMem[1]         = 0;
  lpMem += 2;
  n = MultiByteToWideChar( CP_ACP, 0, "MS Sans Serif", -1, (LPWSTR)lpMem, 50 );
  lpMem += (n * 2);
#else
  // no font
#endif
  
  
  // add the OK pushbutton
  lpMem += createButton( lpMem, "OK", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                         w-165, h-21, 50, 14, IDBN_OK );
  
  // add the pushbutton
  lpMem += createButton( lpMem, "Cancel", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                         w-111, h-21, 50, 14, IDBN_CANCEL );

  // add the apply button
  lpMem += createButton( lpMem, "&Apply", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_DISABLED,
                         w-57, h-21, 50, 14, IDBN_APPLY );
  
  // Add a TreeView
  lpMem = (LPBYTE)lpwAlign( (LPWORD)lpMem );
  lpDlgItem = (LPDLGITEMTEMPLATE)lpMem;
  lpDlgItem->style  = WS_CHILD | WS_VISIBLE | WS_BORDER | TVS_SHOWSELALWAYS | TVS_LINESATROOT | TVS_HASLINES | TVS_HASBUTTONS;
  lpDlgItem->x      = 7;
  lpDlgItem->y      = 7;
  lpDlgItem->cx     = 70;
  lpDlgItem->cy     = h - 35;
  lpDlgItem->id     = ID_TREEVIEW;
  lpMem += sizeof(DLGITEMTEMPLATE);
  n = MultiByteToWideChar( CP_ACP, 0, "SysTreeView32", -1, (LPWSTR)lpMem, 50 );
  lpMem += (n * 2);
  // no title or creation data
  lpMem += 4;
  
  // add the caption text
  lpMem += createButton( lpMem, lpPrefDlg->lpszTitle, WS_CHILD | BS_FLAT,
                         84, 7, w - 91, 14, IDCAPTION );

  // place the child dialog pref sheet at (74,25) with max dimensions
  // of (w-81,h-53).  Mark its place with a static text.  We'll remove it
  // later
  lpMem += createButton( lpMem, "Text", WS_CHILD | BS_FLAT, 84, 25, w-71, h-53, IDPLACEHOLDER );

  GlobalUnlock( hMem );

  dlgextra->cx = 263 - 81;
  dlgextra->cy = 218 - 53;
  dlgextra->lpPrefDlg = lpPrefDlg;
  dlgextra->szCaption[1023] = 0;
  dlgextra->hInst = lpPrefDlg->hInst;
  lstrcpyn( dlgextra->szCaption, lpPrefDlg->lpszTitle, 1023 );
  GlobalUnlock( hMemExtra );

  retval = DialogBoxIndirectParam( lpPrefDlg->hInst, 
                                   (LPDLGTEMPLATE)hMem, 
                                   lpPrefDlg->hWndParent, 
                                   TreeOptionDialogProc, 
                                   (LPARAM)hMemExtra );

  
  dlgextra = (LPPREFDLGEXTRA)GlobalLock( hMemExtra );
  GlobalUnlock( hMemExtra );
  GlobalFree( hMemExtra );
  GlobalFree( hMem );
  
  return retval;
}




BOOL CALLBACK TreeOptionDialogProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
  NMHDR *lpn;
  HGLOBAL hMem;
  LPPREFDLGEXTRA dlgextra;
  int count;
    
  switch ( uMsg )
  {
    case WM_INITDIALOG:
      SetWindowLong( hWnd, GWL_USERDATA, lParam );
      computeDialogOffset( hWnd, (HGLOBAL)lParam );
      initializeDialog( hWnd, (HGLOBAL)lParam );
      return FALSE;
    
    case WM_COMMAND:
      count = ++cnt;
      hMem = (HGLOBAL)GetWindowLong( hWnd, GWL_USERDATA );
      dlgextra = (LPPREFDLGEXTRA)GlobalLock( hMem );
      switch ( LOWORD(wParam) )
      {
        case IDCANCEL:
        case IDBN_CANCEL:
          if ( !sendNotifications( hWnd, dlgextra->lpPrefSheet, sendQueryCancel ) )
            EndDialog( hWnd, 0 );
          break;
        
        // Sends the PSN_KILLACTIVE message to all pages to validate.  If 
        // all OK, then sends the PSN_APPLY message to all pages.
        case IDBN_OK:
          if ( !sendNotifications( hWnd, dlgextra->lpPrefSheet, sendKillActive )
               && !sendNotifications( hWnd, dlgextra->lpPrefSheet, sendApply ) )
            EndDialog( hWnd, 1 );
          break;
        
        // sends the PSN_KILLACTIVE message to the current window to validate.
        // if succssfull, then sends the PSN_APPLY message to all windows.
        case IDBN_APPLY:
          if ( !sendKillActive( hWnd, dlgextra->hCurrentPrefWnd ) 
               && !sendNotifications( hWnd, dlgextra->lpPrefSheet, sendApply ) )
            EnableWindow( GetDlgItem( hWnd, IDBN_APPLY ), FALSE );
          break;
      }
      GlobalUnlock( hMem );
      break;
    
    case WM_PAINT:
      paintCaption( hWnd );
      return FALSE;
      break;
    
    case WM_NOTIFY:
      lpn = (NMHDR *)lParam;
      if ( lpn->idFrom == ID_TREEVIEW )
      {
        BOOL retval;
        
        hMem = (HGLOBAL)GetWindowLong( hWnd, GWL_USERDATA );
        dlgextra = (LPPREFDLGEXTRA)GlobalLock( hMem );
	retval = HandleTreeMessage( lpn->hwndFrom, lParam, dlgextra );
        GlobalUnlock( hMem );
        return retval;
      }
      break;
      
    case WM_DESTROY:
      hMem = (HGLOBAL)GetWindowLong( hWnd, GWL_USERDATA );
      dlgextra = (LPPREFDLGEXTRA)GlobalLock( hMem );
      freePrefSheets( dlgextra->lpPrefSheet );
      GlobalUnlock( hMem );
      return FALSE;
      break;
    
    // should enable the apply button
    case PSM_CHANGED:
      EnableWindow( GetDlgItem( hWnd, IDBN_APPLY ), TRUE );
      break;
      
    case PSM_UNCHANGED:
//      EnableWindow( GetDlgItem( hWnd, IDBN_APPLY ), FALSE );
      break;
      
    default:
      return FALSE;
  }
  
  return TRUE;
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



int createButton( LPBYTE lpStart, LPCSTR lpszText, DWORD style, short x, short y, short cx, short cy, WORD id ) 
{
  LPBYTE lpMem = lpStart;
  LPDLGITEMTEMPLATE lpDlgItem;
  int n;
  
  lpMem = (LPBYTE)lpwAlign( (LPWORD)lpMem );
  lpDlgItem = (LPDLGITEMTEMPLATE)lpMem;
  lpDlgItem->style  = style;
  lpDlgItem->x      = x;
  lpDlgItem->y      = y;
  lpDlgItem->cx     = cx;
  lpDlgItem->cy     = cy;
  lpDlgItem->id     = id;
  lpMem += sizeof(DLGITEMTEMPLATE);
  // predefined button class
  lpMem[0] = 0xFF;
  lpMem[1] = 0xFF;
  lpMem[2] = 0x80;
  lpMem[3] = 0x00;
  // no menu
  lpMem += 4;
  n = MultiByteToWideChar( CP_ACP, 0, lpszText, -1, (LPWSTR)lpMem, lstrlen( lpszText ) * 4 );
  lpMem += (n * 2);
  // no creation data
  lpMem += 2;
  
  return (int)(lpMem - lpStart);
}


int createStatic( LPBYTE lpStart, LPCSTR lpszText, DWORD style, short x, short y, short cx, short cy, WORD id ) 
{
  LPBYTE lpMem = lpStart;
  LPDLGITEMTEMPLATE lpDlgItem;
  int n;
  
  lpMem = (LPBYTE)lpwAlign( (LPWORD)lpMem );
  lpDlgItem = (LPDLGITEMTEMPLATE)lpMem;
  lpDlgItem->style  = style;
  lpDlgItem->x      = x;
  lpDlgItem->y      = y;
  lpDlgItem->cx     = cx;
  lpDlgItem->cy     = cy;
  lpDlgItem->id     = id;
  lpMem += sizeof(DLGITEMTEMPLATE);
  // predefined static class
  lpMem[0] = 0xFF;
  lpMem[1] = 0xFF;
  lpMem[2] = 0x82;
  lpMem[3] = 0x00;
  // no menu
  lpMem += 4;
  n = MultiByteToWideChar( CP_ACP, 0, lpszText, -1, (LPWSTR)lpMem, lstrlen( lpszText ) * 4 );
  lpMem += (n * 2);
  // no creation data
  lpMem += 2;
  
  return (int)(lpMem - lpStart);
}


int createEdit( LPBYTE lpStart, LPCSTR lpszText, DWORD style, short x, short y, short cx, short cy, WORD id ) 
{
  LPBYTE lpMem = lpStart;
  LPDLGITEMTEMPLATE lpDlgItem;
  int n;
  
  lpMem = (LPBYTE)lpwAlign( (LPWORD)lpMem );
  lpDlgItem = (LPDLGITEMTEMPLATE)lpMem;
  lpDlgItem->style  = style;
  lpDlgItem->x      = x;
  lpDlgItem->y      = y;
  lpDlgItem->cx     = cx;
  lpDlgItem->cy     = cy;
  lpDlgItem->id     = id;
  lpMem += sizeof(DLGITEMTEMPLATE);
  // predefined edit class
  lpMem[0] = 0xFF;
  lpMem[1] = 0xFF;
  lpMem[2] = 0x81;
  lpMem[3] = 0x00;
  // no menu
  lpMem += 4;
  n = MultiByteToWideChar( CP_ACP, 0, lpszText, -1, (LPWSTR)lpMem, lstrlen( lpszText ) * 4 );
  lpMem += (n * 2);
  // no creation data
  lpMem += 2;
  
  return (int)(lpMem - lpStart);
}


void paintCaption( HWND hWnd ) 
{
  RECT fadeRect, rect;
  HWND hWndFade = GetDlgItem( hWnd, IDCAPTION );
  PAINTSTRUCT ps;
  HPEN pen;
  HDC hdc;
  HBRUSH brush;
  COLORREF c1, c2, textColor;
  float r1,g1,b1;
  float r2,g2,b2;
  float r3, g3, b3;
  int dx;
  float t, dt;
  int x;
  POINT p[3];
  HGLOBAL hMem = (HGLOBAL)GetWindowLong( hWnd, GWL_USERDATA );
  LPPREFDLGEXTRA dlgextra;
//  LPCSTR lpszCaption;


  computeDialogOffset( hWnd, hMem );

  dlgextra = (LPPREFDLGEXTRA)GlobalLock( hMem );
  
  GetClientRect( hWndFade, &fadeRect );
  
  MapWindowPoints( hWndFade, hWnd, (LPPOINT)&fadeRect, 2);

  hdc = BeginPaint( hWnd, &ps );

  c1 = GetSysColor( COLOR_ACTIVECAPTION );
  c2 = GetSysColor( COLOR_3DFACE );
  textColor = GetSysColor( COLOR_CAPTIONTEXT );

  r1 = GetRValue( c1 );
  g1 = GetGValue( c1 );
  b1 = GetBValue( c1 );
  r2 = GetRValue( c2 );
  g2 = GetGValue( c2 );
  b2 = GetBValue( c2 );


  rect = fadeRect;
  fadeRect.left += 2;
  fadeRect.right--;
  fadeRect.top += 2;
  fadeRect.bottom--;
  dx = fadeRect.right - fadeRect.left;
  dt = 1/(float)dx;
  t = 1;
  
  pen = CreatePen( PS_SOLID, 1, GetSysColor( COLOR_3DSHADOW ) );
  pen = SelectObject( hdc, pen );
  p[0].x = rect.left;          p[0].y = rect.bottom;
  p[1].x = rect.left;          p[1].y = rect.top;
  p[2].x = rect.right + 1;     p[2].y = rect.top;
  Polyline( hdc, p, 3 );
  pen = SelectObject( hdc, pen );
  DeleteObject( pen );

  pen = CreatePen( PS_SOLID, 1, GetSysColor( COLOR_3DDKSHADOW ) );
  pen = SelectObject( hdc, pen );
  p[0].x = rect.left + 1;      p[0].y = rect.bottom -1;
  p[1].x = rect.left + 1;      p[1].y = rect.top + 1;
  p[2].x = rect.right;         p[2].y = rect.top + 1;
  Polyline( hdc, p, 3 );
  pen = SelectObject( hdc, pen );
  DeleteObject( pen );
  
  pen = CreatePen( PS_SOLID, 1, GetSysColor( COLOR_3DHILIGHT ) );
  pen = SelectObject( hdc, pen );
  p[0].x = rect.left+1;        p[0].y = rect.bottom;
  p[1].x = rect.right;         p[1].y = rect.bottom;
  p[2].x = rect.right;         p[2].y = rect.top + 1;
  Polyline( hdc, p, 3 );
  pen = SelectObject( hdc, pen );
  DeleteObject( pen );
  
  pen = CreatePen( PS_SOLID, 1, GetSysColor( COLOR_3DLIGHT ) );
  pen = SelectObject( hdc, pen );
  p[0].x = rect.left + 2;      p[0].y = rect.bottom - 1;
  p[1].x = rect.right - 1;     p[1].y = rect.bottom - 1;
  p[2].x = rect.right - 1;     p[2].y = rect.top + 2;
  Polyline( hdc, p, 3 );
  pen = SelectObject( hdc, pen );
  DeleteObject( pen );

  for( x = 0; x < dx; x++ )
  {
    RECT rect;
    
    r3 = r1*t + r2*(1-t);
    g3 = g1*t + g2*(1-t);
    b3 = b1*t + b2*(1-t);

    rect = fadeRect;

    rect.left += x;
    rect.right = rect.left + 1;

    brush = CreateSolidBrush(RGB(r3, g3, b3));
    FillRect(hdc, &rect, brush);
    DeleteObject(brush);

    t -= dt;
  }
  
  fadeRect.left += 5;

  SetTextColor( hdc, textColor );
  SetBkMode( hdc, TRANSPARENT );

  DrawText( hdc, dlgextra->szCaption, lstrlen( dlgextra->szCaption ), &fadeRect,
            DT_VCENTER|DT_SINGLELINE|DT_LEFT );

  rect.left = dlgextra->dx;
  rect.top = dlgextra->dy;
  rect.right = rect.left + 20;
  rect.bottom = rect.top + 20;

  GlobalUnlock( hMem );
  
  EndPaint( hWnd, &ps );
}


void computeDialogDimensions( LPINTPREFSHEET lpParent, short *cx, short *cy )
{
  DLGTEMPLATE *dlgtmp;
  DLGTEMPLATEEX *dlgtmpex;
  HRSRC hDialog;
  HGLOBAL hMem;
  LPBYTE lpTmp;
  size_t captionLen;
  
  if ( lpParent == NULL )
    return;
  
  hDialog = FindResource( NULL, lpParent->lpszTemplate, RT_DIALOG );
  if ( hDialog != NULL )
  {
    hMem = LoadResource( NULL, hDialog );
    dlgtmp = (DLGTEMPLATE *)LockResource( hMem );
    dlgtmpex = (DLGTEMPLATEEX *)dlgtmp;
    if ( dlgtmpex == NULL )
    {
      return;
    }
    
    if( (dlgtmpex->dlgVer == 1) && (dlgtmpex->signature == 0xFFFF) )
    {
      // How big is this extended dialog?
      if ( dlgtmpex->cx > *cx )
        *cx = dlgtmpex->cx;

      if ( dlgtmpex->cy > *cy )
        *cy = dlgtmpex->cy;

      lpTmp = ((LPBYTE)dlgtmpex) + sizeof(DLGTEMPLATEEX);
    }
    else
    {
      // How big is this dialog?
      if ( dlgtmp->cx > *cx )
        *cx = dlgtmp->cx;

      if ( dlgtmp->cy > *cy )
        *cy = dlgtmp->cy;

      lpTmp = ((LPBYTE)dlgtmp) + sizeof(DLGTEMPLATE);
    }

    if ( !lpParent->szCaption[0] )
    {
      // skip the menu
      if ( *((LPWORD)lpTmp) == 0xFFFF )
        lpTmp += 4;  // skip 0xFFFF and the menu ordinal
      else
        lpTmp += (wcslen((wchar_t *)lpTmp) + 1) * 2;
    
      // skip the classname
      lpTmp += (wcslen((wchar_t *)lpTmp) + 1) * 2;
    
      captionLen = wcslen( (wchar_t *)lpTmp ) + 1;
      WideCharToMultiByte( CP_ACP, 0, (LPCWSTR)lpTmp, captionLen, lpParent->szCaption, 257, NULL, NULL );
    }
  }
  
  FreeResource( hDialog );
  
  // cycle through all of the dialogs
  computeDialogDimensions( lpParent->sibling, cx, cy );
  computeDialogDimensions( lpParent->child, cx, cy );
}


HTREEITEM insertPrefPageTitles( HWND hWnd, LPINTPREFSHEET lpSheet, HTREEITEM hParent )
{
  DLGTEMPLATE *dlgtmp;
  DLGTEMPLATEEX *dlgtmpex;
  LPBYTE p;
  HRSRC hDialog;
  HGLOBAL hMem;
  HTREEITEM hItem;
  HTREEITEM hRetVal1, hRetVal2;
//  LPINTPREFSHEET pNewSheet;
  
  dbprintf( "lpSheet --> %08X", lpSheet );
  
  if ( lpSheet == NULL )
    return NULL;
  
  dbprintf( "  looking for %s", lpSheet->lpszTemplate?lpSheet->lpszTemplate:"" );
  hDialog = FindResource( NULL, lpSheet->lpszTemplate, RT_DIALOG );
  dbprintf( "  hDialog: %08X", hDialog );
  if ( hDialog != NULL )
  {
    int captionLength = 0;
    LPSTR buf;
    TV_INSERTSTRUCT tvi;
    
    hMem = LoadResource( NULL, hDialog );
    p = (LPBYTE)LockResource( hMem );
    dlgtmp = (DLGTEMPLATE *)p;
    dlgtmpex = (DLGTEMPLATEEX *)dlgtmp;
    if ( dlgtmpex == NULL )
    {
      return NULL;
    }
    
    if( (dlgtmpex->dlgVer == 1) && (dlgtmpex->signature == 0xFFFF) )
    {
      p += sizeof(DLGTEMPLATEEX);
    }
    else
    {
      p += sizeof(DLGTEMPLATE);
    }
    
    // skip the menu
    if ( *((WORD *)p) == 0xFFFF )
      p += 4;
    else
      p += ((wcslen((wchar_t *)p) + 1) * 2);
    
    // skip the classname
    p += ((wcslen((wchar_t *)p) + 1) * 2);
    
    captionLength = wcslen((wchar_t *)p);
    buf = (LPSTR)malloc( captionLength + 2 );
    ZeroMemory( buf, captionLength + 2 );
    WideCharToMultiByte( CP_ACP, 0, (wchar_t *)p,
                         captionLength, buf, captionLength, NULL, NULL );
    
    ZeroMemory( &tvi, sizeof(tvi) );
    tvi.hParent = hParent;
    tvi.hInsertAfter = TVI_LAST;
    tvi.item.mask = TVIF_STATE | TVIF_TEXT | TVIF_PARAM;
    tvi.item.stateMask = TVIS_EXPANDED | TVIS_SELECTED;
    tvi.item.pszText = buf;
    tvi.item.cchTextMax = lstrlen( buf ) + 1;
    tvi.item.lParam = (LPARAM)lpSheet;
    hItem = (HTREEITEM)TreeView_InsertItem( hWnd, &tvi );
    
    free( buf );
  }
  
  FreeResource( hDialog );
  
  // cycle through all of the dialogs
  hRetVal1 = insertPrefPageTitles( hWnd, lpSheet->sibling, hParent );
  dbprintf( "inserting child page %08X", lpSheet->child );
  hRetVal2 = insertPrefPageTitles( hWnd, lpSheet->child, hItem );
  
  if ( lpSheet->isDefault )
    return hItem;
  
  if ( hRetVal1 )
    return hRetVal1;
  
  return hRetVal2;
}

void computeDialogOffset( HWND hWnd, HGLOBAL hMem )
{
  HWND hStatic;
  RECT rc;
  LPPREFDLGEXTRA dlgextra = (LPPREFDLGEXTRA)GlobalLock( hMem );
  POINT p;
  
  // find our placeholder for the child preference sheets
  hStatic = GetDlgItem( hWnd, IDPLACEHOLDER );
  GetWindowRect( hStatic, &rc );
  p.x = rc.left;
  p.y = rc.top;
  if ( !ScreenToClient( hWnd, &p ) )
  {
//    printf( "ScreenToClient failed!!! %ld\n", GetLastError() );
  }
  dlgextra->dx = p.x;
  dlgextra->dy = p.y;
  
  GlobalUnlock( hMem );
}


void initializeDialog( HWND hWnd, HGLOBAL hMem )
{
  LPPREFDLGEXTRA dlgextra = (LPPREFDLGEXTRA)GlobalLock( hMem );
  HWND hTreeWnd;
  HTREEITEM hItem;
  
  fflush( stdout );
  
  
//  computeDialogDimensions( dlgextra->lpPrefDlg->lpPrefSheet, &(dlgextra->cx), &(dlgextra->cy) );
  hTreeWnd = GetDlgItem( hWnd, ID_TREEVIEW );
  hItem = insertPrefPageTitles( hTreeWnd, dlgextra->lpPrefSheet, NULL );
  if ( hItem != NULL )
    TreeView_Select( hTreeWnd, hItem, TVGN_CARET );
   
  TreeView_GetRoot( hTreeWnd );
  
  GlobalUnlock( hMem );
}


BOOL HandleTreeMessage( HWND hTreeWnd, LPARAM lParam, LPPREFDLGEXTRA dlgextra )
{
  LPNM_TREEVIEW lpn = (LPNM_TREEVIEW)lParam;
  TVITEM *item;
  LPINTPREFSHEET lpSheet;
  HRSRC hDialog;
  HGLOBAL hMem;
  LPDLGTEMPLATE lpDialogTemplate;
  HWND hParent;
  int status = 0;
  
  switch( lpn->hdr.code )
  {
    case TVN_SELCHANGING:
      hParent = GetParent( hTreeWnd );
      status = sendKillActive( hParent, dlgextra->hCurrentPrefWnd );
      if ( status )
      {
        SetWindowLong( hParent, DWL_MSGRESULT, TRUE );
        return TRUE;
      }
      break;
    
    case TVN_SELCHANGED:
      hParent = GetParent( hTreeWnd );
      item = &lpn->itemNew;
      lpSheet = (LPINTPREFSHEET)item->lParam;
      hDialog = FindResource( NULL, lpSheet->lpszTemplate, RT_DIALOG );
      if ( !hDialog )
        break;
      
      if ( !lpSheet->hWnd )
      {
        hMem = LoadResource( NULL, hDialog );
        lpDialogTemplate = (LPDLGTEMPLATE)LockResource( hMem );
        modifyDialogStyle( lpDialogTemplate );
        lpSheet->hWnd = CreateDialogIndirect( dlgextra->hInst, lpDialogTemplate, hParent, lpSheet->dlgproc );
        FreeResource( hDialog );
        SetWindowPos( lpSheet->hWnd, NULL, dlgextra->dx, dlgextra->dy,
                      0, 0, SWP_NOSIZE | SWP_NOZORDER );
        status = sendSetActive( hParent, lpSheet->hWnd );
      }
      
      // if the child dialog returned 0 (ie, responded correctly to PSN_SETACTIVE)
      if ( status == 0 )
      {
        if ( dlgextra->hCurrentPrefWnd )
          ShowWindow( dlgextra->hCurrentPrefWnd, SW_HIDE );
      
        dlgextra->hCurrentPrefWnd = lpSheet->hWnd;
        ShowWindow( lpSheet->hWnd, SW_SHOW );
    
        lstrcpyn( dlgextra->szCaption, lpSheet->szCaption, 1023 );
        InvalidateRect( hParent, NULL, FALSE );
      }
      break;
      
    default:
      break;
  }

  return FALSE;
}


void modifyDialogStyle( LPDLGTEMPLATE lpDlg )
{
  DLGTEMPLATEEX *lpDlgEx;
  DWORD *lpStyle;
  
  lpDlgEx = (DLGTEMPLATEEX *)lpDlg;
  
  if ( (lpDlgEx->dlgVer == 1) && (lpDlgEx->style == 0xFFFF) )
    lpStyle = &lpDlgEx->style;
  else
    lpStyle = &lpDlg->style;
  
  *lpStyle |= (WS_CHILD | DS_CONTROL);
  *lpStyle &= ~DS_MODALFRAME;
  *lpStyle &= ~WS_CAPTION;
  *lpStyle &= ~WS_SYSMENU;
  *lpStyle &= ~WS_POPUP;
  *lpStyle &= ~WS_DISABLED;
  *lpStyle &= ~WS_VISIBLE;
  *lpStyle &= ~WS_THICKFRAME;
}


char *treeMessage2String( int code ) 
{
  switch ( code )
  {
    case TVN_SELCHANGING:
      return "TVN_SELCHANGING";
    case TVN_SELCHANGED:
      return "TVN_SELCHANGED";
    case TVN_GETDISPINFO:
      return "TVN_GETDISPINFO";
    case TVN_SETDISPINFO:
      return "TVN_SETDISPINFO";
    case TVN_ITEMEXPANDING:
      return "TVN_ITEMEXPANDING";
    case TVN_ITEMEXPANDED:
      return "TVN_ITEMEXPANDED";
    case TVN_BEGINDRAG:
      return "TVN_BEGINDRAG";
    case TVN_BEGINRDRAG:
      return "TVN_BEGINRDRAG";
    case TVN_DELETEITEM:
      return "TVN_DELETEITEM";
    case TVN_BEGINLABELEDIT:
      return "TVN_BEGINLABELEDIT";
    case TVN_ENDLABELEDIT:
      return "TVN_ENDLABELEDIT";
    default:
      return "unknown notification message";
  }
}


LPINTPREFSHEET copyPrefSheets( LPPREFSHEET sheets )
{
  LPINTPREFSHEET retval;
  
  if ( sheets == NULL )
    return NULL;
  
  retval = (LPINTPREFSHEET)GlobalAlloc( GPTR, sizeof(INTPREFSHEET) );

  retval->lpszTemplate  = sheets->lpszTemplate;
  retval->dlgproc       = sheets->dlgproc;
  retval->isDefault     = sheets->isDefault;
  retval->hWnd          = NULL;
  retval->sibling       = copyPrefSheets( sheets->sibling );
  retval->child         = copyPrefSheets( sheets->child );
  
  if ( sheets->lpszCaption )
    lstrcpyn( retval->szCaption, sheets->lpszCaption, 256 );
  
  return retval;
}


void freePrefSheets( LPINTPREFSHEET lpSheet )
{
  if ( lpSheet == NULL )
    return;
  
  freePrefSheets( lpSheet->sibling );
  freePrefSheets( lpSheet->child );
  
  GlobalFree( (HGLOBAL)lpSheet );
}



int sendSetActive( HWND hParent, HWND hPage )
{
  PSHNOTIFY n;
  
  ZeroMemory( &n, sizeof(n) );
  n.hdr.code = PSN_SETACTIVE;
  n.hdr.hwndFrom = hParent;
  return SendMessage( hPage, WM_NOTIFY, 0, (LPARAM)&n );
}


int sendApply( HWND hParent, HWND hPage )
{
  PSHNOTIFY n;
  
  ZeroMemory( &n, sizeof(n) );
  n.hdr.code = PSN_APPLY;
  n.hdr.hwndFrom = hParent;
  return SendMessage( hPage, WM_NOTIFY, 0, (LPARAM)&n );
}


int sendQueryCancel( HWND hParent, HWND hPage )
{
  PSHNOTIFY n;
  
  ZeroMemory( &n, sizeof(n) );
  n.hdr.code = PSN_QUERYCANCEL;
  n.hdr.hwndFrom = hParent;
  return SendMessage( hPage, WM_NOTIFY, 0, (LPARAM)&n );
}


int sendKillActive( HWND hParent, HWND hPage )
{
  PSHNOTIFY n;
  int ret;
  
  if ( !hPage )
    return 0;
  
  ZeroMemory( &n, sizeof(n) );
  n.hdr.code = PSN_KILLACTIVE;
  n.hdr.hwndFrom = hParent;
  ret = SendMessage( hPage, WM_NOTIFY, 0, (LPARAM)&n );
  
  return ret;
}


/*
 * A return value of TRUE indicates that at least one of the property pages
 * returned TRUE.  Generally, this indicates failure for property sheets.
 */
BOOL sendNotifications( HWND hParent, LPINTPREFSHEET lpSheet, SENDNOTIFY func )
{
  if ( (lpSheet == NULL) || (lpSheet->hWnd == NULL) )
    return FALSE;
  
  if ( func( hParent, lpSheet->hWnd ) )
    return TRUE;
  
  if ( sendNotifications( hParent, lpSheet->child, func ) )
    return TRUE;
  
  if ( sendNotifications( hParent, lpSheet->sibling, func ) )
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
