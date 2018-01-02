/*
 * xtractor.c - Copyright (C) 1999,2000 Jay A. Key
 *
 * Main file for CD-DA X-Tractor, a CD audio extaction tool for 32-bit
 * windows platforms.
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
#include "xtractor.h"

char szClassName[] = "xtractor";

static int  iStatusHeight = 0;
static int  iToolbarHeight;
HWND hStatus = NULL;
HWND hTrackWnd = NULL;
static HWND hToolbar = NULL;
static HWND hEditArtist, hEditAlbum;
static HIMAGELIST hImgLists[3] = { NULL, NULL, NULL };
static WNDPROC lpfnToolbarProc = NULL;

static char regKeyName[] = "SOFTWARE\\AKSoft\\X-Tractor";
static unsigned long ulOldAutorun = (unsigned long)0x95;
static char szOldAutoPlay[256] = "Play";
static char regAutoPlay[] = "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer";
static char regAutoAudioCD[] = "AudioCD\\Shell";


/*
 * Global variables
 */
int WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine,
		    int nCmdShow )
{
  WNDCLASSEX wc;
  HWND hWnd;
  MSG msg;
  RECT rc;
  static int aStatusWidths[3] = {40, 290,-1};
  INITCOMMONCONTROLSEX ic;

  ic.dwSize = sizeof(ic);
  ic.dwICC = ICC_WIN95_CLASSES;
  InitCommonControlsEx(&ic);

  ghInstance = hInst;

  hPrevInst = hPrevInst;
  lpszCmdLine = lpszCmdLine;

  InitTrackWnd( hInst );
  InitAKRip( );
  InitGauge( hInst );
  InitBmpPanel();

  ZeroMemory( &wc, sizeof(wc) );
  wc.cbSize        = sizeof(WNDCLASSEX);
  wc.style         = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc   = (WNDPROC)akripWndProc;
  wc.hInstance     = hInst;
  wc.hIcon         = LoadIcon( hInst, "ALTRIP3" );
  wc.hCursor       = LoadCursor( NULL, IDC_ARROW );
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
  wc.lpszClassName = szClassName;
  wc.lpszMenuName  = "akripMenu";
  wc.hIconSm       = LoadIcon( hInst, "ALTRIP3" );

  if ( !RegisterClassEx( &wc ) )
    return FALSE;

  hWnd = CreateWindowEx( WS_EX_APPWINDOW, szClassName, "CD-DA X-Tractor",
			 WS_OVERLAPPEDWINDOW,
			 CW_USEDEFAULT, CW_USEDEFAULT,
			 540, 400,
			 NULL, NULL, hInst, NULL );

  if ( !hWnd )
    return FALSE;

  hToolbar = createToolbar( hWnd, hInst );
  iToolbarHeight = WindowHeight( hToolbar );

  hStatus = CreateStatusWindow( WS_VISIBLE | WS_CHILD | SBARS_SIZEGRIP,
				"", hWnd, IDM_STATUSBAR );
  SendMessage( hStatus, SB_SETPARTS, 3, (LPARAM)aStatusWidths );
  iStatusHeight = WindowHeight( hStatus );

  ComputeTrackWndRect( hWnd, &rc );
  hTrackWnd = createTrackWnd( hWnd, hInst, IDM_TRACKWND, &rc );

  if ( bAutoTOC )
    {
      SendMessage( hWnd, WM_COMMAND, MAKEWPARAM( IDM_REFRESH, BN_CLICKED ), 0L );
      if ( bAutoCheck )
	SendMessage( hTrackWnd, WM_CHECKTRACK, (WPARAM)ALLTRACKS, (LPARAM)TRUE );
    }

  ShowWindow( hWnd, nCmdShow );
  UpdateWindow( hWnd );

  disableAutoPlay();

  while( GetMessage( &msg, NULL, 0, 0 ) )
    {
      TranslateMessage( &msg );
      DispatchMessage( &msg );
    }

  restoreAutoPlay();

  if ( hImgLists[0] ) ImageList_Destroy( hImgLists[0] );
  if ( hImgLists[1] ) ImageList_Destroy( hImgLists[1] );
  if ( hImgLists[2] ) ImageList_Destroy( hImgLists[2] );
  
  if ( hCddbEntry )
    cddbFreeEntry( hCddbEntry );

  return msg.wParam;
}


LRESULT CALLBACK akripWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
  RECT rc;

  switch( uMsg )
    {
    case WM_CREATE:
      CheckEnableID3MenuItem( hWnd );
      CheckEnableCDDBMenuItem( hWnd );
      if ( GetDllVersion( "comctl32.dll" ) < MAKELONG(4,71) )
	{
	  // disallow switching between 8- and 24-bit bitmaps in the toolbar
	  bHiColor = FALSE;
	  EnableMenuItem( GetMenu( hWnd ), IDM_HICOLOR, MF_BYCOMMAND | MF_GRAYED );
	}
      CheckEnableHiColorMenuItem( hWnd );
    break;

    case WM_COMMAND:
      switch( LOWORD( wParam ) )
	{
	case IDM_EXIT:
	  DestroyWindow( hWnd );
	  break;
	case IDM_REFRESH:
	  if ( !bInCDDBQuery )
	    {
	      RefreshTrackList( );
	      asSetID3Info( ID3_ERASE, NULL, 0 );
	      SetEditItemText( IDE_ARTIST, "" );
	      SetEditItemText( IDE_ALBUM, "" );
              // make sure we have a cd in the drive
              if ( !SendMessage( hTrackWnd, WM_NUMTRACKS, 0, 0 ) )
              {
                SetStatusMessage( "No CD" );
                break;
              }
	      if ( bAutoCheck )
		SendMessage( hTrackWnd, WM_CHECKTRACK, (WPARAM)ALLTRACKS, (LPARAM)TRUE );
	      if ( bCDDB )
		DoCDDBQuery( hWnd );
	    }
	  break;
	case IDM_RIP:
	  DialogBoxParam( ghInstance, "RipTrackDialog", hWnd, (DLGPROC)RipTrackDlgProc, (LPARAM)hTrackWnd );
	  break;
	case IDM_ID3:
	case IDM_ID3TAGEDIT:
	  DialogBox( ghInstance, "ID3InfoDialog", hWnd, (DLGPROC)ID3InfoDlgProc );
	  break;
	case IDM_CDPARMS:
	  DialogBox( ghInstance, "CDPropertiesDialog", hWnd, (DLGPROC)CDPropertiesDlgProc );
	  break;
	case IDM_CDSETTINGS:
	case IDM_OPTIONS:
	  DoConfig( hWnd, ghInstance, 0 );
	  break;
	case IDM_DIRSETTINGS:
	  DoConfig( hWnd, ghInstance, 1 );
	  break;
	case IDM_MP3SETTINGS:
	  DoConfig( hWnd, ghInstance, 2 );
	  break;
	case IDM_VORBSETTINGS:
	  DoConfig( hWnd, ghInstance, 3 );
	  break;
	case IDM_CDDBSETTINGS:
	  DoConfig( hWnd, ghInstance, 4 );
	  break;
	case IDM_MISCOPT:
	  DoConfig( hWnd, ghInstance, 5 );
	  break;
	case IDM_CHECKALL:
	  SendMessage( hTrackWnd, WM_CHECKTRACK, ALLTRACKS, (LPARAM)TRUE );
	  break;
	case IDM_INVERT:
	  SendMessage( hTrackWnd, WM_INVERTCHECK, ALLTRACKS, 0L );
	  break;
	case IDM_RENAME:
	  SendMessage( hTrackWnd, WM_RENSELTRACK, 0, 0L );
	  break;
	case IDE_ARTIST:
	case IDE_ALBUM:
	  if ( (int)HIWORD( wParam ) == EN_CHANGE )
	    GetEditItemText( (int)LOWORD( wParam ), (HWND)lParam );
	  break;
	case IDM_ENABLEID3:
	  bID3 = !bID3;
	  CheckEnableID3MenuItem( hWnd );
	  break;
	case IDM_ENABLECDDB:
	  bCDDB = !bCDDB;
	  CheckEnableCDDBMenuItem( hWnd );
	  break;
	case IDM_HICOLOR:
	  bHiColor = !bHiColor;
	  CheckEnableHiColorMenuItem( hWnd );
	  AddToolbarImages( ghInstance, hToolbar, FALSE, TRUE );
	  break;
	case IDM_ABOUT:
	  DynamicAboutDialog( hWnd );
	  break;
	case IDM_HELPTOPICS:
	  ShowHelpFile( hWnd, IDM_HELPTOPICS );
	  break;
	case IDM_RIPSEGMENT:
	  RipTrackSegment( hWnd, hTrackWnd );
	  break;
	case IDM_CDPLAYERINI:
	  WriteInfo2CDPlayerINI( hTrackWnd );
	  break;
	case IDM_SUBMITCDDB:
	  DoCDDBSubmit( hWnd, hTrackWnd );
	}
      break;

    case WM_DESTROY:
      DeinitAKRip( );
      PostQuitMessage( 0 );
      break;

    case WM_NOTIFY:
      switch( wParam )
	{
	case IDM_TOOLBAR:
	  handleToolbarNotify( hWnd, uMsg, wParam, lParam );
	  break;
	}
      break;

    case WM_SYSCOLORCHANGE:
      SendMessage( hToolbar, uMsg, wParam, lParam );
      SendMessage( hTrackWnd, uMsg, wParam, lParam );
      break;

    case WM_PAINT:
      doPaint( hWnd );
      break;

    case WM_SIZE:
      SendMessage( hToolbar, TB_AUTOSIZE, 0, 0L );
      GetClientRect( hWnd, &rc );
      MoveWindow( hStatus, 0, rc.bottom - iStatusHeight, rc.right - rc.left, rc.bottom, TRUE );
      ComputeTrackWndRect( hWnd, &rc );
      MoveWindow( hTrackWnd, 0, rc.top, rc.right - rc.left, rc.bottom - rc.top, TRUE );
      break;

    default:
      return DefWindowProc( hWnd, uMsg, wParam, lParam );
    }

  return 0L;
}


/*
 * Subclass wndproc for Toolbar.  Handles the WM_SYSCOLORCHANGE and
 * also the tooltip messages
 */
#define WM_SETSUBCLASSPROC  (WM_USER+999)
LRESULT CALLBACK SubToolbarProc( HWND hWnd, UINT uMsg, WPARAM wParam,
				 LPARAM lParam )
{
  LPTOOLTIPTEXT lpt = (LPTOOLTIPTEXT)lParam;

  if ( uMsg == WM_SETSUBCLASSPROC )
    {
      lpfnToolbarProc = (WNDPROC)GetWindowLong( hWnd, GWL_WNDPROC );
      SetWindowLong( hWnd, GWL_WNDPROC, (LONG)SubToolbarProc );
      return 0L;
    }

#if 0
  dbprintf( "SubToolbarProc: %04X %04X(%d) %08X(%d) %08X(%d)", hWnd,
	    uMsg, uMsg, wParam, wParam, lParam, lParam );
#endif
  switch( uMsg )
    {
    case WM_SYSCOLORCHANGE:
      AddToolbarImages( ghInstance, hWnd, TRUE, FALSE );
      return CallWindowProc( lpfnToolbarProc, hWnd, uMsg, wParam, lParam );

    case WM_NOTIFY:
      if ( lpt->hdr.code == TTN_GETDISPINFOA || lpt->hdr.code == TTN_GETDISPINFOW )
	{
	  lpt->hinst = ghInstance;
	  lpt->lpszText = MAKEINTRESOURCE(lpt->hdr.idFrom);
	  return 0L;
	}
      break;

    default:
      break;
    }

  return CallWindowProc( lpfnToolbarProc, hWnd, uMsg, wParam, lParam );
}


/*
 * Subclass wndproc for Toolbar.  Handles the WM_SYSCOLORCHANGE and
 * also the tooltip messages
 */
LRESULT CALLBACK SubToolbarEditProc( HWND hWnd, UINT uMsg, WPARAM wParam,
				 LPARAM lParam )
{
  static WNDPROC aWndProc[2] = { NULL, NULL };
  int nID;

  if ( uMsg == WM_SETSUBCLASSPROC )
    {
      WNDPROC lpfnProc = (WNDPROC)GetWindowLong( hWnd, GWL_WNDPROC );
      if ( hWnd == hEditAlbum )
	aWndProc[0] = lpfnProc;
      else
	aWndProc[1] = lpfnProc;
      SetWindowLong( hWnd, GWL_WNDPROC, (LONG)SubToolbarEditProc );
      return 0L;
    }

  switch( uMsg )
    {
    case WM_KEYUP:
      nID = (int)wParam;
      if ( nID == VK_TAB )
	{
	  if ( hWnd == hEditAlbum )
	    SetFocus( hEditArtist );
	  else
	    SetFocus( hEditAlbum );
	  return 0;
	}
      break;

    case WM_KEYDOWN:
      nID = (int)wParam;
      if ( nID == VK_TAB )
	{
	  return 0;
	}
      break;

    case WM_CHAR:
      if ( (TCHAR)wParam == 0x09 ) // tab char?
	return 0;
      break;

    default:
      break;
    }

  if ( hWnd == hEditAlbum )
    return CallWindowProc( aWndProc[0], hWnd, uMsg, wParam, lParam );
  else if ( hWnd == hEditArtist )
    return CallWindowProc( aWndProc[1], hWnd, uMsg, wParam, lParam );

  // should never get here
  return 0;
}


HIMAGELIST CreateToolbarImageList( HWND hWnd, HINSTANCE hInst, int idResource )
{
  HIMAGELIST retVal;
  HBITMAP hBmp, hOldBmp;
  COLORREF c;
  HDC hDC, hCompDC;

  retVal = ImageList_Create( 50, 50, ILC_COLOR24 | ILC_MASK, 5, 0 );
  hBmp = LoadBitmap( hInst, MAKEINTRESOURCE(idResource) );
  /*
   * We need to get the background color as it is mapped onto the display,
   * and not as it was saved.  In 24-bit color, it doesn't really matter,
   * but on some 16-bit displays, RGB(192,192,192) is mapped to other colors
   */
  hDC = GetDC( hWnd );
  hCompDC = CreateCompatibleDC( hDC );
  hOldBmp = SelectObject( hCompDC, hBmp );
  c = GetPixel( hCompDC, 0, 0 );  // get the background color to use
  SelectObject( hCompDC, hOldBmp );
  ReleaseDC( hWnd, hDC );
  DeleteDC( hCompDC );
  //  ImageList_AddMasked( retVal, hBmp, RGB(192,192,192) );
  //  dbprintf( "Background color: %d %d %d", (c>>16)&0xFF, (c>>8)&0xFF, c&0xFF );
  ImageList_AddMasked( retVal, hBmp, c );
  DeleteObject( hBmp );

  return retVal;
}


int AddToolbarImages( HINSTANCE hInst, HWND hWnd, BOOL bSysColorChange,
		      BOOL bToggleHiColor )
{
  TBADDBITMAP tbBitmaps;
  HIMAGELIST hOldImageList[3] = { NULL, NULL, NULL };
  int iBmp, iHotBmp;

  if ( bHiColor )
    {
      iBmp = idToolbar24Bmp;
      iHotBmp = idToolbarHot24Bmp;
    }
  else
    {
      iBmp = idToolbarBmp;
      iHotBmp = idToolbarHotBmp;
    }

  // check if we can use the flat toolbar with "hot" buttons
  if ( GetDllVersion( "comctl32.dll" ) < MAKELONG(4,71) )
    {
      /*
       * Only add the bitmap on initial creation when using older version
       * of comctl32.dll.  Otherwise we ignore the call.
       */
      if ( !bSysColorChange && !bToggleHiColor )
	{
	  // use old style
	  tbBitmaps.hInst = NULL;
	  tbBitmaps.nID = (UINT)LoadBitmap( hInst, MAKEINTRESOURCE( iBmp ) );
	  SendMessage( hWnd, TB_ADDBITMAP, 5, (LPARAM)&tbBitmaps );
	}
    }
  else
    {
      /*
       * We'll actually change imagelists for v4.71+ of comctl32.dll.
       */
      if ( bSysColorChange || bToggleHiColor )
	{
	  hOldImageList[0] = hImgLists[0];
	  hOldImageList[1] = hImgLists[1];
	  hOldImageList[2] = hImgLists[2];
	}
      // create image lists
      hImgLists[0] = CreateToolbarImageList( hWnd, hInst, iBmp );
      SendMessage( hWnd, TB_SETIMAGELIST, 0, (LPARAM)hImgLists[0] );
#if _CONFIG_FLAT_TOOLBAR
      hImgLists[1] = CreateToolbarImageList( hWnd, hInst, iHotBmp );
      SendMessage( hWnd, TB_SETHOTIMAGELIST, 0, (LPARAM)hImgLists[1] );
#endif
    }

  if ( hOldImageList[0] ) ImageList_Destroy( hOldImageList[0] );
  if ( hOldImageList[1] ) ImageList_Destroy( hOldImageList[1] );
  if ( hOldImageList[2] ) ImageList_Destroy( hOldImageList[2] );

  // force a repaint of the toolbar
  InvalidateRect( hWnd, NULL, FALSE );
  UpdateWindow( hWnd );

  return 0;
}


/*
 * Creates the toolbar, loads bitmap resources, etc.  InitCommonControls()
 * must be called prior to calling this function
 */
HWND createToolbar( HWND hWnd, HINSTANCE hInst )
{
  HWND hRet;
  TBBUTTON tb[4];
  int idx = 0;
  RECT rc;
  DWORD dwToolbarStyle = WS_CHILD | WS_BORDER | WS_VISIBLE | TBSTYLE_TOOLTIPS;

  memset( tb, 0, sizeof(TBBUTTON[4]) );
  tb[idx].iBitmap = 0;
  tb[idx].idCommand = IDM_REFRESH;
  tb[idx].fsState = TBSTATE_ENABLED;
  tb[idx].fsStyle = TBSTYLE_BUTTON;
  tb[idx].dwData = 0;
  tb[idx++].iString = -1;

  tb[idx].iBitmap = 2;
  tb[idx].idCommand = IDM_RIP;
  tb[idx].fsState = TBSTATE_ENABLED;
  tb[idx].fsStyle = TBSTYLE_BUTTON;
  tb[idx].dwData = 0;
  tb[idx++].iString = -1;

  tb[idx].iBitmap = 3;
  tb[idx].idCommand = IDM_OPTIONS;
  tb[idx].fsState = TBSTATE_ENABLED;
  tb[idx].fsStyle = TBSTYLE_BUTTON;
  tb[idx].dwData = 0;
  tb[idx++].iString = -1;

  tb[idx].iBitmap = 4;
  tb[idx].idCommand = IDM_ID3;
  tb[idx].fsState = TBSTATE_ENABLED;
  tb[idx].fsStyle = TBSTYLE_BUTTON;
  tb[idx].dwData = 0;
  tb[idx++].iString = -1;

  hRet = CreateWindowEx( WS_EX_TOOLWINDOW, TOOLBARCLASSNAME, "",
			 dwToolbarStyle,
			 0, 0, 100, 64,
			 hWnd, (HMENU)IDM_TOOLBAR, hInst, NULL );

#if _CONFIG_FLAT_TOOLBAR
  dwToolbarStyle = (DWORD)SendMessage( hRet, TB_GETSTYLE, 0, 0L );
  dwToolbarStyle |= TBSTYLE_FLAT;
  SendMessage( hRet, TB_SETSTYLE, 0, (LPARAM)dwToolbarStyle );
#endif

  SendMessage( hRet, TB_BUTTONSTRUCTSIZE, sizeof(TBBUTTON), 0L );
  SendMessage( hRet, TB_SETBITMAPSIZE, 0, MAKELONG( 50, 46 ) );
  SendMessage( hRet, TB_SETBUTTONSIZE, 0, MAKELONG( 58, 53 ) );
  SendMessage( hRet, TB_AUTOSIZE, 0, 0L );
  AddToolbarImages( hInst, hRet, FALSE, FALSE );

  SendMessage( hRet, TB_ADDBUTTONS, idx, (LPARAM)&tb );
  SubToolbarProc( hRet, WM_SETSUBCLASSPROC, 0, 0L );

  SendMessage( hRet, TB_GETITEMRECT, (WPARAM)(idx-1), (LPARAM)&rc );

  CreateWindowEx( 0L, "STATIC", "Artist: ",
		  SS_RIGHT | WS_CHILD | WS_VISIBLE,
		  rc.right + 10, rc.top + 6, 60, 20, hRet,
		  (HMENU)NULL, hInst, NULL );
  CreateWindowEx( 0L, "STATIC", "Album: ",
		  SS_RIGHT | WS_CHILD | WS_VISIBLE,
		  rc.right + 10, rc.top + 32, 60, 20, hRet,
		  (HMENU)NULL, hInst, NULL );
  hEditArtist = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", "",
		  ES_LEFT | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL
		  | WS_BORDER | WS_TABSTOP | WS_GROUP ,
		  rc.right + 72, rc.top + 2, 210, 24, hRet,
		  (HMENU)IDE_ARTIST, hInst, NULL );

  hEditAlbum = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", "",
		  ES_LEFT | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL
		  | WS_BORDER | WS_TABSTOP,
		  rc.right + 72, rc.top + 26, 210, 24, hRet,
		  (HMENU)IDE_ALBUM, hInst, NULL );

  SubToolbarEditProc( hEditAlbum, WM_SETSUBCLASSPROC, 0, 0L );
  SubToolbarEditProc( hEditArtist, WM_SETSUBCLASSPROC, 0, 0L );

  return hRet;
}


void doPaint( HWND hWnd )
{
  PAINTSTRUCT p;
  HDC hDC;

  hDC = BeginPaint( hWnd, &p );
  if ( !hDC )
    return;

  EndPaint( hWnd, &p );
}


void handleToolbarNotify( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
#if 0
  LPTOOLTIPTEXT lpt = (LPTOOLTIPTEXT)lParam;

  if ( lpt->hdr.code == TTN_NEEDTEXT )
    {
      // we should put in tool-text code here
      //OutputDebugString( "Got a TTN_NEEDTEXT" );
    }
#else
  hWnd = hWnd; uMsg = uMsg; wParam = wParam; lParam = lParam;
#endif
}


int WindowHeight( HWND hWnd )
{
  RECT rc;

  GetWindowRect( hWnd, &rc );
  return ( rc.bottom - rc.top );
}


void DoCDDBQuery( HWND hWnd )
{
  DWORD dwThreadID;

  bInCDDBQuery = TRUE;

  CREATETHREAD( NULL, 0, (LPTHREAD_START_ROUTINE)DoCDDBQueryThread,
		(LPVOID)hWnd, 0, &dwThreadID );
}


DWORD DoCDDBQueryThread( LPVOID lpParam )
{
  CDDBQUERYITEM cdq[32];
  CDDBQUERY query;
  char linebuf[81];
  int i, numTracks;
  BOOL bCDDB = FALSE;
  char *buf;
  HWND hWnd = (HWND)lpParam;
//  HCDDBENTRY hCddbEntry;

  ZeroMemory( cdq, sizeof(cdq) );

  buf = (char *)GlobalAlloc( GPTR, 32000 );

#if 1
  CDDBSetOption( CDDB_OPT_USECDPLAYERINI, "", TRUE );
#endif
  CDDBSetOption( CDDB_OPT_SERVER, szCDDBServer, 0 );
  CDDBSetOption( CDDB_OPT_CGI, szCGI, 0 );
  CDDBSetOption( CDDB_OPT_USEPROXY, "", bUseProxy );
  CDDBSetOption( CDDB_OPT_PROTOLEVEL, "", 5 );
  if ( bUseProxy )
    {
      CDDBSetOption( CDDB_OPT_PROXY, szProxyAddr, 0 );
      CDDBSetOption( CDDB_OPT_PROXYPORT, "", iProxyPort );
      if ( szProxyUser[0] != '\0' && szProxyPass[0] != '\0' )
      {
        char auth[98];
        wsprintf( auth, "%s:%s", szProxyUser, szProxyPass );
        CDDBSetOption( CDDB_OPT_USERAUTH, auth, 0 );
      }
    }
  CDDBSetOption( CDDB_OPT_USER, "user@akrip.sourceforge.net", 0 );
  wsprintf( buf, "xtractor v%d.%02d", iMajorVer, iMinorVer );
  CDDBSetOption( CDDB_OPT_AGENT, buf, 0 );

  SetStatusMessage( "Contacting CDDB Server..." );
  query.num = 32;
  query.q = cdq;
  bCDDB = (CDDBQuery( hCD, &query ) == SS_COMP);
#if 0
  if ( !bCDDB )
    OutputDebugString( "Something\'s not quite right here..." );
  wsprintf( linebuf, "After CDDBQuery(), num == %d", query.num );
  OutputDebugString( linebuf );
#endif
  if ( bCDDB && (query.num == 0) )
    {
      SetStatusMessage( "No matches in CDDB database..." );
      goto exitPoint;
    }

  if ( query.num )
    {
      // If we're in the middle of a rip operation, just use the first one
      // as a default.  Otherwise, pop up a dialog to let the user choose
      // which one to use
      if ( bRippingTracks || (query.num == 1) )
	{
	  SetStatusMessage( "Retrieving CD info..." );
	  query.num = 0;
	  bCDDB = (CDDBGetDiskInfo( &cdq[0], buf, 32000 ) == SS_COMP);
	  if ( !bCDDB )
	    {
	      SetStatusMessage( "Error retrieving CDDB info..." );
	    }
	}
      else
	{
	  DialogBoxParam( ghInstance, "MultipleCDDBQueryDialog", hWnd,
			  (DLGPROC)MultipleCDDBQueryDlgProc, (LPARAM)&query );
	  if ( query.num < 0 )
	    {
	      SetStatusMessage( "CDDB Query cancelled..." );
	      bCDDB = FALSE;
	    }
	  else
	    {
	      SetStatusMessage( "Retrieving CD info..." );
	      bCDDB = (CDDBGetDiskInfo( &cdq[query.num], buf, 32000 ) == SS_COMP);
	      if ( !bCDDB )
		{
		  SetStatusMessage( "Error retrieving CDDB info..." );
		}
	    }
	}
    }


  // probably want to pop up an error message here
  if ( !bCDDB )
    goto exitPoint;

  SetEditItemText( IDE_ARTIST, cdq[query.num].artist );
  SetEditItemText( IDE_ALBUM, cdq[query.num].title );
  id3CDDBCat2Genre( cdq[query.num].categ );
  if ( lstrcmp( cdq[query.num].categ, "cdplayerini" ) )
  {
    bCddbRetrievedGenre = TRUE;
    lstrcpy( szCddbRetrievedGenre, cdq[query.num].categ );
  }
  else
    bCddbRetrievedGenre = FALSE;
  
  if ( hCddbEntry != NULL )
  {
    cddbFreeEntry( hCddbEntry );
    hCddbEntry = NULL;
  }
  hCddbEntry = cddbNewEntry( buf );
  cddbSetOption( hCddbEntry, CDCACHE_OPT_CHECKCDLEN, 0 );
  if ( !cddbParseEntry( hCddbEntry ) )
  {
//    MessageBox( hWnd, "parse failed!", "Danger, Will Robinson!", MB_OK | MB_ICONSTOP );
  }
  else
  {
    char szTmp[81];
    cddbGetArtist( hCddbEntry, szTmp, 81 );
    SetEditItemText( IDE_ARTIST, szTmp );
    cddbGetTitle( hCddbEntry, szTmp, 81 );
    SetEditItemText( IDE_ALBUM, szTmp );
    numTracks = cddbGetNumTracks( hCddbEntry );
    iCddbEntryRev = cddbGetEntryVersion( hCddbEntry );
//    wsprintf( szTmp, "Set Rev to %d", iCddbEntryRev );
//    MessageBox( hWnd, szTmp, "Info", MB_OK );
    for( i = 0; i < numTracks; i++ )
    {
      cddbGetTrackTitle( hCddbEntry, i, linebuf, 81 );
      SendMessage( hTrackWnd, WM_SETTRACKTEXT, (WPARAM)i, (LPARAM)linebuf );
    }
  }
//  cddbFreeEntry( hCddbEntry );

  UpdateStatusBar();
  
exitPoint:
  GlobalFree( (HGLOBAL)buf );  
  bInCDDBQuery = FALSE;

  return 0;
}


void SetTrackText( char *buf, int i )
{
  char *p;

  p = strstr( buf, "=" );
  if ( p )
    {
      p++;
      if ( *p )
	SendMessage( hTrackWnd, WM_SETTRACKTEXT, (WPARAM)i, (LPARAM)p );
    }
}


void RefreshTrackList( void )
{
  ADDTRACK at;
  int i;
  DWORD dwStatus;

  SendMessage( hTrackWnd, WM_DELTRACK, ALLTRACKS, 0L );
  iCddbEntryRev = -1;
  bCddbRetrievedGenre = FALSE;
  szCddbRetrievedGenre[0] = '\0';

  ZeroMemory( &lbaToc, sizeof(TOC) );
  ModifyCDParms( hCD, CDP_MSF, (DWORD)FALSE );
  dwStatus = ReadTOC( hCD, &lbaToc );

  ZeroMemory( &msfToc, sizeof(TOC) );
  ModifyCDParms( hCD, CDP_MSF, (DWORD)TRUE );
  dwStatus = ReadTOC( hCD, &msfToc );
  
  bTocRead = TRUE;

  if ( dwStatus != SS_COMP )
    return;
  
  for( i = lbaToc.firstTrack; i <= lbaToc.lastTrack; i++ )
    {
      TOCTRACK *t;
      int idx;

      idx = i - lbaToc.firstTrack;

      ZeroMemory( &at, sizeof(at) );
      wsprintf( at.name, "Track %02d", i );

      t = &(lbaToc.tracks[idx]);
      MSB2DWORD( &(at.start), t->addr );
      if ( t->ADR & 0x04 )
	{
	  // will need to fix the leadout detection code here
	  at.bData = TRUE;
	  lstrcpy( at.name, "Data Track" );
	}

      t = &(lbaToc.tracks[idx+1]);
      MSB2DWORD( &(at.len), t->addr );
      at.len -= at.start;

      #define LEADOUT  (150*75)
      // if the next track is a data track, subtract 150 seconds of leadout
      if ( (t->ADR & 0x04) && (at.len > LEADOUT) )
	at.len -= LEADOUT;
      
      if ( (t->ADR & 0x04) || (t->trackNumber == 0xAA) )
      {
        lastAudioFrame = at.start + at.len - 1;
        dbprintf( "Set lastAudioFrame to %d", lastAudioFrame );
      }
      
      SendMessage( hTrackWnd, WM_ADDTRACK, 0, (LPARAM)&at );
    }
}



/*
 * Save parameters to the registry
 */
void DeinitAKRip( void )
{
  HKEY hKey;
  DWORD dwDisposition, driveInfo, dwAutoTOC;
  DWORD dwTmp;
  LONG retVal;

  retVal = RegCreateKeyEx( HKEY_LOCAL_MACHINE, regKeyName, 0L,
			 "", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
			 NULL, &hKey, &dwDisposition );
  if ( retVal != ERROR_SUCCESS )
    {
      return;
    }

  RegSetValueEx( hKey, "numRip", 0L, REG_DWORD, (BYTE *)(&maxRip),
		 sizeof(DWORD) );
  RegSetValueEx( hKey, "jitterCheck", 0L, REG_DWORD, (LPBYTE)&jitterCheck,
		 4L );
  RegSetValueEx( hKey, "overlap", 0L, REG_DWORD, (LPBYTE)&numOverlap, 4L );
  RegSetValueEx( hKey, "readMode", 0L, REG_DWORD, (LPBYTE)&readMode, 4L );
  dwAutoTOC = (DWORD)bAutoTOC;
  RegSetValueEx( hKey, "autoTOC", 0L, REG_DWORD, (LPBYTE)&dwAutoTOC, 4L );
  dwTmp = (DWORD)bAutoCheck;
  RegSetValueEx( hKey, "autoCheck", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
  dwTmp = (DWORD)wBitrate;
  RegSetValueEx( hKey, "bitrate", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
  dwTmp = (DWORD)wMaxBitrate;
  RegSetValueEx( hKey, "maxbitrate", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
  dwTmp = (DWORD)wMode;
  RegSetValueEx( hKey, "mpegmode", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
  dwTmp = (DWORD)wLameMode;
  RegSetValueEx( hKey, "lamemode", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
  dwTmp = (DWORD)bID3;
  RegSetValueEx( hKey, "id3level", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
  dwTmp = bCRC;
  RegSetValueEx( hKey, "crc", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
  dwTmp = bUseProxy;
  RegSetValueEx( hKey, "useproxy", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
  dwTmp = iProxyPort;
  RegSetValueEx( hKey, "proxyport", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
  RegSetValueEx( hKey, "proxyaddr", 0L, REG_SZ, szProxyAddr, lstrlen(szProxyAddr)+1 );
  RegSetValueEx( hKey, "proxyuser", 0L, REG_SZ, szProxyUser, lstrlen(szProxyUser)+1 );
  dwTmp = bSavePass;
  RegSetValueEx( hKey, "savepass", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
  if ( bSavePass )
    RegSetValueEx( hKey, "proxypass", 0L, REG_SZ, szProxyPass, lstrlen( szProxyPass ) + 1 );
  RegSetValueEx( hKey, "cddbaddr", 0L, REG_SZ, szCDDBServer, lstrlen(szCDDBServer)+1 );
  RegSetValueEx( hKey, "cddbcgi", 0L, REG_SZ, szCGI, lstrlen(szCGI)+1 );
  RegSetValueEx( hKey, "cddbsubmitcgi", 0L, REG_SZ, szSubmitCGI, lstrlen(szSubmitCGI)+1 );
  dwTmp = bCDDB;
  RegSetValueEx( hKey, "enablecddb", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
  dwTmp = iEncoder;
  RegSetValueEx( hKey, "defaultEncoder", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
  dwTmp = (DWORD)bHiColor;
  RegSetValueEx( hKey, "hicolor", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
  dwTmp = (DWORD)bNiceThreads;
  RegSetValueEx( hKey, "nicethreads", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
  dwTmp = 0;
  if ( bVBR )
    dwTmp |= 0x80000000;
  if ( bVBRHeader )
    dwTmp |= 0x40000000;
  dwTmp |= ( (wMaxBitrate & 0x1FF) << 21 );
  dwTmp |= ( (nQuality & 0x03) << 19 );
  dwTmp |= ( (nVBRQuality & 0x0F) << 15 );
  RegSetValueEx( hKey, "lameopts", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
  dwTmp = (DWORD)bWritePlaylist;
  RegSetValueEx( hKey, "writeplaylist", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
  dwTmp = (DWORD)wVorbBitrate;
  RegSetValueEx( hKey, "vorbbitrate", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
  dwTmp = (DWORD)bNormalize;
  RegSetValueEx( hKey, "normalize", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
  dwTmp = (DWORD)iNormalizePercent;
  RegSetValueEx( hKey, "normalizepct", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
  dwTmp = (DWORD)iNormalizeScanPercent;
  RegSetValueEx( hKey, "normalizescanpct", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );

  if ( cdlistIdx >= 0 )
    {
      driveInfo = ((DWORD)bReadType) << 24 |
	((DWORD)cdlist.cd[cdlistIdx].ha) << 16 |
	((DWORD)cdlist.cd[cdlistIdx].tgt) << 8 |
	((DWORD)cdlist.cd[cdlistIdx].lun);
      RegSetValueEx( hKey, "driveInfo", 0L, REG_DWORD,
		     (LPBYTE)&driveInfo, 4L );
    }
  else
    RegDeleteValue( hKey, "driveInfo" );

  RegSetValueEx( hKey, "mp3Outputdir", 0L, REG_SZ, (LPBYTE)szMP3OutputDir,
		 lstrlen( szMP3OutputDir)+1 );
  RegSetValueEx( hKey, "cddbuseremail", 0L, REG_SZ, szUserEmail,
		 lstrlen(szUserEmail)+1 );
  RegSetValueEx( hKey, "fnamemacro", 0L, REG_SZ, szMangleString,
		 lstrlen( szMangleString ) + 1 );

  RegCloseKey( hKey );
}

/*
 * void InitAKRip( void );
 *
 * Reads initialization values from the registry, if present.  Currently
 * looks for the following values:
 *   numRip      - (DWORD) number of frames to read at once
 *   jitterCheck - (DWORD) number of frames to try to match
 *   overlap     - (DWORD) number of frames of overlap (at least
 *                 jitterCheck + 1
 *   autoTOC     - (DWORD) boolean, whether to automatically scan the TOC on
 *                 startup
 *   driveInfo   - (DWORD) ha, tgt, lun identifier of last CD unit used
 *   driveString - (REG_SZ) string identifier of CD unit
 *   driveVendor - (REG_SZ) vendor identifier of CD unit
 *   driveProdID - (REG_SZ) product identifier of CD unit
 *   driveRev    - (REG_SZ) hardware revision number of CD unit
 *   driveVendSp - (REG_SZ) vendor specific info for CD unit
 *   
 */
void InitAKRip( void )
{
  HKEY hKey;
  DWORD dwDisposition, driveInfo, dwAutoTOC;
  DWORD dwTmp;
  LONG retVal;
  CDREC cd;

  // scan the list of available cd drives
  ZeroMemory( &cdlist, sizeof(CDLIST) );
  cdlist.max = MAXCDLIST;
  GetCDList( &cdlist );
  cdlistIdx = -1;

  memset( &cd, 0, sizeof(cd) );
  memset( validFnameChar, 0xFF, 256 );
  validFnameChar['\\'] = 0;
  validFnameChar['/'] = 0;
  validFnameChar[':'] = 0;
  validFnameChar['*'] = 0;
  validFnameChar['?'] = 0;
  validFnameChar['\"'] = 0;
  validFnameChar['<'] = 0;
  validFnameChar['>'] = 0;
  validFnameChar['|'] = 0;

  retVal = RegCreateKeyEx( HKEY_LOCAL_MACHINE, regKeyName, 0L,
			 "", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
			 NULL, &hKey, &dwDisposition );
  if ( retVal != ERROR_SUCCESS )
    {
      // UserOutput( UO_ERROPENREG, regKeyName, retVal );
      return;
    }

  if ( !readRegDWORD( hKey, "numRip", &maxRip ) )
    {
      maxRip = 26;  /* default value */
      RegSetValueEx( hKey, "numRip", 0L, REG_DWORD, (BYTE *)(&maxRip),
		     sizeof(DWORD) );
    }
  if ( !readRegDWORD( hKey, "jitterCheck", &jitterCheck ) )
    {
      jitterCheck = 1;
      RegSetValueEx( hKey, "jitterCheck", 0L, REG_DWORD,
		     (LPBYTE)&jitterCheck, 4L );
    }
  if ( !readRegDWORD( hKey, "overlap", &numOverlap ) )
    {
      numOverlap = jitterCheck + 2;
      RegSetValueEx( hKey, "overlap", 0L, REG_DWORD,
		     (LPBYTE)&numOverlap, 4L );
    }

  if ( !readRegDWORD( hKey, "autoTOC", &dwAutoTOC ) )
    {
      dwAutoTOC = 1;
      RegSetValueEx( hKey, "autoTOC", 0L, REG_DWORD,
		     (LPBYTE)&dwAutoTOC, 4L );
    }
  bAutoTOC = (BOOL)dwAutoTOC;

  if ( !readRegDWORD( hKey, "autoCheck", &dwAutoTOC ) )
    {
      dwAutoTOC = 1;
      RegSetValueEx( hKey, "autoCheck", 0L, REG_DWORD,
		     (LPBYTE)&dwAutoTOC, 4L );
    }
  bAutoCheck = (BOOL)dwAutoTOC;

  if ( !readRegDWORD( hKey, "nicethreads", &dwTmp ) )
    {
      dwTmp = 1;
      RegSetValueEx( hKey, "nicethreads", 0L, REG_DWORD,
		     (LPBYTE)&dwTmp, 4L );
    }
  bNiceThreads = (BOOL)dwTmp;

  if ( !readRegDWORD( hKey, "readMode", &readMode ) )
    {
      readMode = CDRM_JITTERONERR;
      RegSetValueEx( hKey, "readMode", 0L, REG_DWORD,
		     (LPBYTE)&readMode, 4L );
    }

  if ( readRegDWORD( hKey, "bitrate", &dwTmp ) )
    wBitrate = (WORD)dwTmp;
  else
    {
      wBitrate = 192;
      dwTmp = 192L;
      RegSetValueEx( hKey, "bitrate", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
    }

  if ( readRegDWORD( hKey, "maxbitrate", &dwTmp ) )
    wMaxBitrate = (WORD)dwTmp;
  else
    {
      wMaxBitrate = 320;
      dwTmp = 320L;
      RegSetValueEx( hKey, "maxbitrate", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
    }

  if ( readRegDWORD( hKey, "mpegmode", &dwTmp ) )
    wMode = (WORD)dwTmp;
  else
    {
      wMode = BE_MP3_MODE_STEREO;
      dwTmp = BE_MP3_MODE_STEREO;
      RegSetValueEx( hKey, "mpegmode", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
    }

  if ( readRegDWORD( hKey, "lamemode", &dwTmp ) )
    wLameMode = (WORD)dwTmp;
  else
    {
      wLameMode = BE_MP3_MODE_STEREO;
      dwTmp = BE_MP3_MODE_STEREO;
      RegSetValueEx( hKey, "lamemode", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
    }

  if ( readRegDWORD( hKey, "id3level", &dwTmp ) )
    bID3 = (BOOL)dwTmp;
  else
    {
      bID3 = FALSE;
      dwTmp = (DWORD)FALSE;
      RegSetValueEx( hKey, "id3level", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
    }

  if ( readRegDWORD( hKey, "crc", &dwTmp ) )
    bCRC = (BOOL)dwTmp;
  else
    {
      bCRC = FALSE;
      dwTmp = (DWORD)FALSE;
      RegSetValueEx( hKey, "crc", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
    }

  if ( readRegDWORD( hKey, "useproxy", &dwTmp ) )
    bUseProxy = (BOOL)dwTmp;
  else
    {
      bUseProxy = FALSE;
      dwTmp = (DWORD)FALSE;
      RegSetValueEx( hKey, "useproxy", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
    }

  if ( readRegDWORD( hKey, "lameopts", &dwTmp ) )
    {
      bVBR        = (BOOL)(dwTmp & 0x80000000);
      bVBRHeader  = (BOOL)(dwTmp & 0x40000000);
      wMaxBitrate = (WORD)((dwTmp >> 21) & 0x1FF);
      nQuality    = (dwTmp >> 19) & 0x03;
      nVBRQuality = (dwTmp >> 15) & 0x0F;
    }
  
  if ( readRegDWORD( hKey, "writeplaylist", &dwTmp ) )
    bWritePlaylist = (BOOL)dwTmp;
  else
    {
      dwTmp = (DWORD)bWritePlaylist;
      RegSetValueEx( hKey, "writeplaylist", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
    }

  if ( readRegDWORD( hKey, "defaultEncoder", &dwTmp ) )
    {
      iEncoder = (int)dwTmp;
      if ( !xtEncoderAvail( iEncoder ) )
	iEncoder = XT_ENC_WAV;
    }
  else
    {
      iEncoder = XT_ENC_WAV;
      dwTmp = XT_ENC_WAV;
      RegSetValueEx( hKey, "defaultEncoder", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
   }

  if ( readRegDWORD( hKey, "proxyport", &dwTmp ) )
    iProxyPort = (int)dwTmp;
  else
    {
      iProxyPort = 0;
      dwTmp = 0;
      RegSetValueEx( hKey, "proxyport", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
    }

  if ( !readRegSZ( hKey, "proxyaddr", szProxyAddr, 81 ) )
    lstrcpy( szProxyAddr, "" );
  
  if ( !readRegSZ( hKey, "proxyuser", szProxyUser, 81 ) )
    lstrcpy( szProxyUser, "" );
  
  if ( readRegDWORD( hKey, "savepass", &dwTmp ) )
    bSavePass = (BOOL)dwTmp;
  else
    bSavePass = FALSE;
    
  if ( !readRegSZ( hKey, "proxypass", szProxyPass, 17 ) )
    lstrcpy( szProxyPass, "" );

  if ( !readRegSZ( hKey, "cddbaddr", szCDDBServer, 81 ) )
    lstrcpy( szCDDBServer, "www.freedb.org" );

  if ( !readRegSZ( hKey, "cddbcgi", szCGI, 81 ) )
    lstrcpy( szCGI, "/~cddb/cddb.cgi" );

  if ( !readRegSZ( hKey, "cddbsubmitcgi", szSubmitCGI, 81 ) )
    lstrcpy( szSubmitCGI, "/~cddb/submit.cgi" );

  if ( readRegDWORD( hKey, "enablecddb", &dwTmp ) )
    bCDDB = (BOOL)dwTmp;
  else
    {
      bCDDB = FALSE;
      dwTmp = 0;
      RegSetValueEx( hKey, "enablecddb", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
    }

  if ( readRegDWORD( hKey, "hicolor", &dwTmp ) )
    bHiColor = (BOOL)dwTmp;
  else
    {
      bHiColor = DisplayIsHiColor();
      dwTmp = (DWORD)bHiColor;
      RegSetValueEx( hKey, "hicolor", 0L, REG_DWORD, (LPBYTE)&dwTmp, 4L );
    }

  if ( readRegDWORD( hKey, "vorbbitrate", &dwTmp ) )
    wVorbBitrate = (WORD)dwTmp;

  if ( readRegDWORD( hKey, "driveInfo", &driveInfo ) )
    {
      //      BYTE bRead;
      GETCDHAND cdh;

      cd.ha = (BYTE)((0x00FF0000 & driveInfo) >> 16);
      cd.tgt = (BYTE)((0x0000FF00 & driveInfo) >> 8 );
      cd.lun = (BYTE)(0x000000FF & driveInfo);
      bReadType = (BYTE)((0xFF000000 & driveInfo) >> 24);
      memset( &cdh, 0, sizeof(GETCDHAND) );
      cdh.size       = sizeof(GETCDHAND);
      cdh.ver        = 1;
      cdh.ha         = cd.ha;
      cdh.tgt        = cd.tgt;
      cdh.lun        = cd.lun;
      cdh.readType   = bReadType;
      cdh.numOverlap = (unsigned char)numOverlap;
      cdh.numJitter  = (unsigned char)jitterCheck;
      hCD = GetCDHandle( &cdh );
      if ( !hCD )
	MessageBox( NULL, "Unable to allocate default CD device", "X-Tractor",
		    MB_APPLMODAL | MB_ICONSTOP | MB_OK );
      else
	{
	  BYTE i;
	  // locate the drive in the list of available drives
	  for( i = 0; i < cdlist.num; i++ )
	    {
	      if ( (cdh.ha  == cdlist.cd[i].ha) &&
		   (cdh.tgt == cdlist.cd[i].tgt) &&
		   (cdh.lun == cdlist.cd[i].lun) )
		cdlistIdx = i;
	    }
	}
    }
  else
    {
      hCD = findAvailableCD( );
    }

  if ( !readRegSZ( hKey, "mp3OutputDir", szMP3OutputDir, MAX_PATH + 1 ) )
    GetCurrentDirectory( MAX_PATH + 1, szMP3OutputDir );

  if ( !readRegSZ( hKey, "cddbuseremail", szUserEmail, 257 ) )
    lstrcpy( szUserEmail, "" );

  if ( !readRegSZ( hKey, "fnamemacro", szMangleString, MAX_PATH + 1 ) )
    lstrcpy( szMangleString, "$N" );
  
  if ( readRegDWORD( hKey, "normalize", &dwTmp ) )
    bNormalize = (BOOL)dwTmp;
  if ( readRegDWORD( hKey, "normalizepct", &dwTmp ) )
    iNormalizePercent = (int)dwTmp;
  if ( readRegDWORD( hKey, "normalizescanpct", &dwTmp ) )
    iNormalizeScanPercent = (int)dwTmp;

  asSetID3Info( ID3_TITLE, "", 0 );
  asSetID3Info( ID3_ARTIST, "", 0 );
  asSetID3Info( ID3_ALBUM, "", 0 );
  asSetID3Info( ID3_YEAR, "", 0 );
  asSetID3Info( ID3_GENRE, NULL, 0 );

  if ( hKey )
    RegCloseKey( hKey );
}


HCDROM findAvailableCD( void )
{
  GETCDHAND cdh;
  BYTE i;

  if ( hCD )
    {
      CloseCDHandle( hCD );
      hCD = NULL;
    }

  ZeroMemory( &cdh, sizeof(cdh) );
  for( i = 0; i < cdlist.num && !hCD; i++ )
    {
      cdh.size        = sizeof(GETCDHAND);
      cdh.ver         = 1;
      cdh.ha          = cdlist.cd[i].ha;
      cdh.tgt         = cdlist.cd[i].tgt;
      cdh.lun         = cdlist.cd[i].lun;
      cdh.readType    = bReadType;
      cdh.numOverlap  = (unsigned char)numOverlap;
      cdh.numJitter   = (unsigned char)jitterCheck;
      hCD = GetCDHandle( &cdh );
      if ( hCD )
	cdlistIdx = i;
    }

  return hCD;
}


/*
 * Reads a DWORD from the registry given an already open key
 * The value read is stored into pdw, and the function returns
 * 0 if it fails
 */
int readRegDWORD( HKEY hKey, LPCTSTR lpszValue, DWORD *pdw )
{
  DWORD dwSize = 4L;
  DWORD dwType;
  LONG retVal;

  retVal = RegQueryValueEx( hKey, lpszValue, NULL, &dwType, (LPBYTE)pdw,
			    &dwSize );
  if ( retVal != ERROR_SUCCESS )
    {
      return 0;
    }

  return -1;
}
 

/*
 * Reads an ASCIIZ string from the registry given an already open key
 * The value read is stored into lpszData, and the function returns
 * 0 if it fails
 */
int readRegSZ( HKEY hKey, LPCTSTR lpszValue, LPSTR lpszData, DWORD dwDataLen )
{
  DWORD dwType;
  LONG retVal;

  retVal = RegQueryValueEx( hKey, lpszValue, NULL, &dwType, (LPBYTE)lpszData,
			    &dwDataLen );
  if ( (retVal != ERROR_SUCCESS) || (dwType != REG_SZ) )
    {
      return 0;
    }

  return -1;
}


/*
 * Sets the registry to disable autoplay under Win95.  Probably won't
 * work under NT due to security settings
 */
void disableAutoPlay( void )
{
  HKEY hKey;
  unsigned long ulDisable = (unsigned long)0xFF;
  DWORD dwDataSize = sizeof( ulDisable );
  DWORD dwDataType;
  LONG lErr = 0;

  if ( ( lErr = RegOpenKeyEx( HKEY_CURRENT_USER, regAutoPlay, 0,
		     KEY_ALL_ACCESS, &hKey ) ) == ERROR_SUCCESS )
    {
      if ( RegQueryValueEx( hKey, "NoDriveTypeAutoRun", 0, NULL,
			    (unsigned char *)&ulOldAutorun,
			    &dwDataSize ) == ERROR_SUCCESS )
	{
	  RegSetValueEx( hKey, "NoDriveTypeAutoRun", 0, REG_BINARY,
			 (unsigned char *)&ulDisable, 4 );
	}
      else
	ulOldAutorun = (unsigned long)0x95;

      RegFlushKey( hKey );
      RegCloseKey( hKey );
    }

  if ( ( lErr = RegOpenKeyEx( HKEY_CLASSES_ROOT, regAutoAudioCD, 0,
                              KEY_ALL_ACCESS, &hKey ) ) == ERROR_SUCCESS )
    {
      dwDataSize = 256;
      if ( RegQueryValueEx( hKey, "", NULL, &dwDataType,
                            szOldAutoPlay,
                            &dwDataSize ) == ERROR_SUCCESS )
        {
          RegSetValueEx( hKey, "", 0, REG_SZ, (unsigned char *)"", 1 );
        }

      RegFlushKey( hKey );
      RegCloseKey( hKey );
    }
}


void restoreAutoPlay( void )
{
  HKEY hKey;

  if ( RegOpenKeyEx( HKEY_CURRENT_USER, regAutoPlay, 0,
		     KEY_ALL_ACCESS, &hKey ) == ERROR_SUCCESS )
    {
      RegSetValueEx( hKey, "NoDriveTypeAutoRun", 0, REG_BINARY,
		     (unsigned char *)&ulOldAutorun, 4 );

      RegFlushKey( hKey );
      RegCloseKey( hKey );
    }

  if ( RegOpenKeyEx( HKEY_CLASSES_ROOT, regAutoAudioCD, 0,
                     KEY_ALL_ACCESS, &hKey ) == ERROR_SUCCESS )
    {
      RegSetValueEx( hKey, "", 0, REG_SZ,
                     (unsigned char *)&szOldAutoPlay,
                     lstrlen(szOldAutoPlay)+1 );

      RegFlushKey( hKey );
      RegCloseKey( hKey );
    }
}


BOOL DirExists( char *dir )
{
  char curDir[MAX_PATH+1];
  //  BOOL bSet;

  if ( !GetCurrentDirectory( MAX_PATH + 1, curDir ) )
    return FALSE;

  if ( !SetCurrentDirectory( dir ) )
     return FALSE;
  SetCurrentDirectory( curDir );

  return TRUE;
}


void MSB2DWORD( DWORD *d, BYTE *b )
{
  DWORD retVal;

  retVal = (DWORD)b[0];
  retVal = (retVal<<8) + (DWORD)b[1];
  retVal = (retVal<<8) + (DWORD)b[2];
  retVal = (retVal<<8) + (DWORD)b[3];

  *d = retVal;
}


void GetEditItemText( int iCtlId, HWND hCtl )
{
  char buf[257];

  ZeroMemory( buf, sizeof(buf) );
  SendMessage( hCtl, WM_GETTEXT, sizeof(buf), (LPARAM)buf );
  switch( iCtlId )
    {
    case IDE_ARTIST:
      lstrcpyn( szArtistName, buf, 257 );
      asSetID3Info( ID3_ARTIST, buf, 0 );
      break;
    case IDE_ALBUM:
      lstrcpyn( szAlbumTitle, buf, 257 );
      asSetID3Info( ID3_ALBUM, buf, 0 );
      break;
    }
}


void SetEditItemText( int iCtlId, char *s )
{
  switch( iCtlId )
    {
    case IDE_ARTIST:
      SendMessage( hEditArtist, WM_SETTEXT, 0, (LPARAM)s );
      break;
    case IDE_ALBUM:
      SendMessage( hEditAlbum, WM_SETTEXT, 0, (LPARAM)s );
      break;
    }
}



void CheckEnableID3MenuItem( HWND hWnd )
{
  HMENU hPopup;

  hPopup = GetSubMenu( GetMenu(hWnd), 3 ); // get handle to Tools menu
  if ( bID3 )
    CheckMenuItem( hPopup, IDM_ENABLEID3, MF_BYCOMMAND | MF_CHECKED );
  else
    CheckMenuItem( hPopup, IDM_ENABLEID3, MF_BYCOMMAND | MF_UNCHECKED );
}


void CheckEnableCDDBMenuItem( HWND hWnd )
{
  HMENU hPopup;

  hPopup = GetSubMenu( GetMenu(hWnd), 3 ); // get handle to Tools menu
  if ( bCDDB )
    CheckMenuItem( hPopup, IDM_ENABLECDDB, MF_BYCOMMAND | MF_CHECKED );
  else
    CheckMenuItem( hPopup, IDM_ENABLECDDB, MF_BYCOMMAND | MF_UNCHECKED );
}


void CheckEnableHiColorMenuItem( HWND hWnd )
{
  HMENU hPopup;

  hPopup = GetSubMenu( GetMenu(hWnd), 2 );  //options menu
  if ( bHiColor )
    CheckMenuItem( hPopup, IDM_HICOLOR, MF_BYCOMMAND | MF_CHECKED );
  else
    CheckMenuItem( hPopup, IDM_HICOLOR, MF_BYCOMMAND | MF_UNCHECKED );
}



void ShowHelpFile( HWND hWnd, int topic )
{
  char buf[MAX_PATH+1];

  topic = topic;

  GetCurrentDirectory( MAX_PATH+1, buf );
#if 0
  lstrcat( buf, "\\help" );
  ShellExecute( hWnd, "open", "index.html", NULL, buf, SW_SHOWNORMAL );
#else
  lstrcat( buf, "\\htmlhelp" );
  ShellExecute( hWnd, "open", "xtractor.chm", NULL, buf, SW_SHOWNORMAL );
#endif
}



void setRipTrackStatus( LPENCODETHREAD e )
{
  char buf[61];
  char buf2[81];
  char *p = buf;
  double d;
  int a,b;

  time( &e->tnow );
  d = difftime( e->tnow, e->tstart );
  switch( e->status )
    {
    case EST_SUCCESS:
      lstrcpy( buf, "OK, " );
      DiffTimeToString( d, buf+4 );
      p += lstrlen( buf );
      d = ((double)(e->trackLen/75)) / d;
      a = (int)d;
      b = (int)((d-(double)a) * 100.0);
      wsprintf( p, ", %s: %d.%02dx", (iEncoder>=XT_ENC_LAME1)?"rip/encode":"rip", a, b );
      wsprintf( buf2, "lstrlen(buf) == %d", lstrlen(buf) );
      OutputDebugString( buf2 );
      break;
    case EST_ERROR:
      wsprintf( buf, "Error: 0x%04X", GetAspiLibAspiError() );
      break;
    case EST_ENCODERINITERR:
      wsprintf( buf, "Error initializing encoder" );
      break;
    case EST_ABORTED:
      lstrcpy( buf, "Rip Aborted" );
      break;
    default:
      lstrcpy( buf, "" );
      break;
    }
  SendMessage( hTrackWnd, WM_SETTRACKSTATUS, (WPARAM)e->idx,
	       (LPARAM)buf );
}

void DiffTimeToString( double d, char *buf )
{
  unsigned long hrs, min, sec;
  
  hrs = (unsigned long)(d / 3600.0);
  min = (unsigned long)((d - (double)((hrs) * 3600))/60.0);
  sec = ((unsigned long)d) - (hrs)*3600 - (min)*60;

  wsprintf( buf, "%02d:%02d", hrs * 60 + min, sec );
}

#if 0
static void GetLineFromBuf( char *tgt, char **src, int len )
{
  char *p;

  if ( !src || !*src || !tgt )
    return;

  p = *src;

  ZeroMemory( tgt, len );
  len--;

  while( *p && len )
    {
      if ( *p == '\n' )
        break;
      *tgt++ = *p;
      p++;
      len--;
    }

  // advance *src to end of last read string
  if ( *p == '\n' )
    p++;
  *src = p;

  len = lstrlen( tgt );
  if ( tgt[len-2] == '\r' )
    tgt[len-2] = '\0';
  if ( (tgt[len-1] == '\r') || (tgt[len-1] == '\n') )
    tgt[len-1] = '\0';
}
#endif


void dbprintf( char *fmt, ... )
{
  char buf[512];
  va_list arg;

  va_start( arg, fmt );

  vsprintf( buf, fmt, arg );
  OutputDebugString( buf );

  va_end( arg );
}

/*
 * Attempt to determine the version of comctl32.dll available.
 */
#if (!_CONFIG_DLLVERINFO)
typedef struct
{
  DWORD cbSize;
  DWORD dwMajorVersion;
  DWORD dwMinorVersion;
  DWORD dwBuildNumber;
  DWORD dwPlatformID;
} DLLVERSIONINFO;
typedef HRESULT CALLBACK (*DLLGETVERSIONPROC)(DLLVERSIONINFO *);
#endif

DWORD GetDllVersion( LPCTSTR lpszDllName )
{
  HINSTANCE hDll;
  DWORD retVal = 0;

  hDll = LoadLibrary( lpszDllName );
  if ( hDll )
    {
      DLLGETVERSIONPROC pDllGetVer;

      pDllGetVer = (DLLGETVERSIONPROC)GetProcAddress( hDll, "DllGetVersion" );
      if ( pDllGetVer )
	{
	  DLLVERSIONINFO dvi;
	  HRESULT hr;

	  ZeroMemory( &dvi, sizeof(dvi) );
	  dvi.cbSize = sizeof(dvi);

	  hr = (*pDllGetVer)(&dvi);
	  if ( SUCCEEDED(hr) )
	    {
	      retVal = MAKELONG( dvi.dwMajorVersion, dvi.dwMinorVersion );
	    }

	  FreeLibrary( hDll );
	}
    }

  return retVal;
}


/*
 * Returns TRUE if color depth >= 16 bpp
 */
BOOL DisplayIsHiColor( void )
{
  HDC hDC;
  int iBPP;

  hDC = GetDC( NULL );

  iBPP = GetDeviceCaps( hDC, BITSPIXEL );

  ReleaseDC( NULL, hDC );

  return (iBPP >= 16);
}


void ComputeTrackWndRect( HWND hParent, LPRECT lprc )
{
  GetClientRect( hParent, lprc );

  lprc->top += (iToolbarHeight+1);
  lprc->bottom -= iStatusHeight;
}


void WriteInfo2CDPlayerINI( HWND hTrackWnd )
{
  ADDTRACK t;
  int i, n;
  DWORD dwIndex;
  static char *szCDPlayerIni = "cdplayer.ini";
  char section[24];
  char buf[32];

  dbprintf( "In WriteInfo2CDPlayerINI()" );
  dwIndex = genCDPlayerIniIndex( hCD );
  dbprintf( "Index: %X", dwIndex );

  n = SendMessage( hTrackWnd, WM_NUMTRACKS, 0, 0L );
  if ( n == 0 )
    {
      return;
    }

  wsprintf( section, "%X", dwIndex );
  WritePrivateProfileString( section, "EntryType", "1", szCDPlayerIni );
  WritePrivateProfileString( section, "artist", szArtistName, szCDPlayerIni );
  WritePrivateProfileString( section, "title", szAlbumTitle, szCDPlayerIni );
  WritePrivateProfileString( section, "genre", asGetID3AsciiInfo( ID3_GENRE ), szCDPlayerIni );
  wsprintf( buf, "%d", n );
  WritePrivateProfileString( section, "numtracks", buf , szCDPlayerIni );

  for( i = 0; i < n; i++ )
    {
      wsprintf( buf, "%d", i );
      SendMessage( hTrackWnd, WM_GETTRACK, (WPARAM)i, (LPARAM)&t );
      WritePrivateProfileString( section, buf, t.name, szCDPlayerIni );
    }
}


DWORD genCDPlayerIniIndex( HCDROM hCD )
{
  DWORD retVal = 0;
  BOOL bMSF;
  int i;
  TOC toc;
  DWORD dwAddr;

  bMSF = QueryCDParms( hCD, CDP_MSF, NULL );
  ModifyCDParms( hCD, CDP_MSF, TRUE );

  memset( &toc, 0, sizeof(toc) );
  ReadTOC( hCD, &toc );

  for( i = 0; i <= (toc.lastTrack - toc.firstTrack); i++ )
    {
      if ( !(toc.tracks[i].ADR & 0x04 ) )
        {
          MSB2DWORD( &dwAddr, toc.tracks[i].addr );
          retVal += dwAddr;
        }
    }

  ModifyCDParms( hCD, CDP_MSF, bMSF );

  return retVal;
}
