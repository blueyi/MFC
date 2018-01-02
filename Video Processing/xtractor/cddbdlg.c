/*
 * cddbdlg.c - Copyright (C) 1999,2000 Jay A. Key
 *
 * CDDB options dialog for options property sheet.  CDDB servers and
 * proxy server are configured here.
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
#include <windowsx.h>
#include <commctrl.h>
#include <winsock.h>
#include "resources.h"
#include "globals.h"
#include "cddbdlg.h"
#include "threads.h"

BOOL ValidateCDDBDlg( HWND hWnd );
BOOL ValidateProxyDlg( HWND hWnd );
void ConfigureCDDBDlg( HWND hWnd );
void InsertCDDBQueryDialogItems( HWND hWnd, LPCDDBQUERY lpq );
void DoCDDBSitesQuery( HWND hWnd );
DWORD DoCDDBSitesQueryThread( LPVOID lpParam );
BOOL CALLBACK CDDBSiteQueryDlgProc( HWND hWnd, UINT uMsg, WPARAM wParam,
				    LPARAM lParam );
void FinishCDDBSitesQuery( HWND hWnd, BOOL bCancelled );
void InsertSites( HWND hWnd );
void SetCDDBServer( HWND hWnd );

// save old settings for output dialog config
static BOOL bInInit = FALSE;
static BOOL bTmpUseProxy;
static BOOL bTmpSavePass;
static BOOL bInCDDBSitesQuery = FALSE;
static char szTmpCDDBServer[81];
static char szTmpProxyAddr[81];
static char szTmpCGI[81];
static char szTmpSubmitCGI[81];
static int  iTmpHTTPPort;
static char szTmpProxyUser[81];
static char szTmpProxyPass[17];
static CDDBSITE sites[8];
static int numSites = 0;
static const CDDBSITE defSites[1] = {
  { "freedb.freedb.org", TRUE, 80, "/~cddb/cddb.cgi", "", "", "" }
};


static int iTmpProxyPort;

/*
 * Called in response to PSN_KILLACTIVE.  Should validate all values in the
 * dialog, and save them to the temp variables.
 */
BOOL ValidateCDDBDlg( HWND hWnd )
{
//  iTmpProxyPort = GetDlgItemInt( hWnd, IDE_PROXYPORT, NULL, FALSE );
//  GetDlgItemText( hWnd, IDE_PROXYSRVR, szTmpProxyAddr, 81 );
  GetDlgItemText( hWnd, IDE_CDDBSERVER, szTmpCDDBServer, 81 );
  GetDlgItemText( hWnd, IDE_CDDBCGI, szTmpCGI, 81 );
  GetDlgItemText( hWnd, IDE_CDDBSUBMIT, szTmpSubmitCGI, 81 );
  iTmpHTTPPort = GetDlgItemInt( hWnd, IDE_SERVERPORT, NULL, FALSE );
//  GetDlgItemText( hWnd, IDE_PROXYUSER, szTmpProxyUser, 81 );
//  GetDlgItemText( hWnd, IDE_PROXYPASS, szTmpProxyPass, 17 );

  return TRUE;
}


/*
 * Called in response to PSN_KILLACTIVE.  Should validate all values in the
 * dialog, and save them to the temp variables.
 */
BOOL ValidateProxyDlg( HWND hWnd )
{
  iTmpProxyPort = GetDlgItemInt( hWnd, IDE_PROXYPORT, NULL, FALSE );
  GetDlgItemText( hWnd, IDE_PROXYSRVR, szTmpProxyAddr, 81 );
//  GetDlgItemText( hWnd, IDE_CDDBSERVER, szTmpCDDBServer, 81 );
//  GetDlgItemText( hWnd, IDE_CDDBCGI, szTmpCGI, 81 );
//  GetDlgItemText( hWnd, IDE_CDDBSUBMIT, szTmpSubmitCGI, 81 );
//  iTmpHTTPPort = GetDlgItemInt( hWnd, IDE_SERVERPORT, NULL, FALSE );
  GetDlgItemText( hWnd, IDE_PROXYUSER, szTmpProxyUser, 81 );
  GetDlgItemText( hWnd, IDE_PROXYPASS, szTmpProxyPass, 17 );

  return TRUE;
}




/*
 * Called in response to PSN_SETACTIVE.  Sets dialog items with the values
 * from the temp variables.
 */
void ConfigureCDDBDlg( HWND hWnd )
{
  bInInit = FALSE;

  // if a CDDB operation is active, disable everything in this dialog
//  CheckDlgButton( hWnd, IDCKB_USEPROXY, bTmpUseProxy?BST_CHECKED:BST_UNCHECKED );
//  CheckDlgButton( hWnd, IDCKB_SAVEPASS, bTmpSavePass?BST_CHECKED:BST_UNCHECKED );

//  SendDlgItemMessage( hWnd, IDE_PROXYSRVR, EM_SETLIMITTEXT, 80, 0L );
//  SetDlgItemText( hWnd, IDE_PROXYSRVR, szTmpProxyAddr );

//  SendDlgItemMessage( hWnd, IDE_PROXYPORT, EM_SETLIMITTEXT, 5, 0L );
 // SetDlgItemInt( hWnd, IDE_PROXYPORT, iTmpProxyPort, FALSE );
  
  SetDlgItemInt( hWnd, IDE_SERVERPORT, iTmpHTTPPort, FALSE );

  SendDlgItemMessage( hWnd, IDE_CDDBSERVER, EM_SETLIMITTEXT, 80, 0L );
  SendDlgItemMessage( hWnd, IDE_CDDBCGI, EM_SETLIMITTEXT, 80, 0L );
  SendDlgItemMessage( hWnd, IDE_CDDBSUBMIT, EM_SETLIMITTEXT, 80, 0L );
//  SendDlgItemMessage( hWnd, IDE_PROXYUSER, EM_SETLIMITTEXT, 80, 0L );
//  SendDlgItemMessage( hWnd, IDE_PROXYPASS, EM_SETLIMITTEXT, 16, 0L );
  SetDlgItemText( hWnd, IDE_CDDBSERVER, szTmpCDDBServer );
  SetDlgItemText( hWnd, IDE_CDDBCGI, szTmpCGI );
  SetDlgItemText( hWnd, IDE_CDDBSUBMIT, szTmpSubmitCGI );
//  SetDlgItemText( hWnd, IDE_PROXYUSER, szTmpProxyUser );
//  SetDlgItemText( hWnd, IDE_PROXYPASS, szTmpProxyPass );
  

  // for now both buttons are disabled
  SendDlgItemMessage( hWnd, IDBN_SELECTCDDB, WM_ENABLE, 0, 0L );
  SendDlgItemMessage( hWnd, IDBN_RESETCDDB, WM_ENABLE, 0, 0L );

  // sets the dialog's items with the temporary values.
  if ( bInCDDBQuery )
    {
      SendDlgItemMessage( hWnd, IDE_CDDBSERVER, WM_ENABLE, 0, 0L );
      SendDlgItemMessage( hWnd, IDBN_SELECTCDDB, WM_ENABLE, 0, 0L );
      SendDlgItemMessage( hWnd, IDLB_SERVERLIST, WM_ENABLE, 0, 0L );
      SendDlgItemMessage( hWnd, IDBN_RESETCDDB, WM_ENABLE, 0, 0L );
//      SendDlgItemMessage( hWnd, IDCKB_USEPROXY, WM_ENABLE, 0, 0L );
//      SendDlgItemMessage( hWnd, IDE_PROXYSRVR, WM_ENABLE, 0, 0L );
//      SendDlgItemMessage( hWnd, IDE_PROXYPORT, WM_ENABLE, 0, 0L );
      SendDlgItemMessage( hWnd, IDE_SERVERPORT, WM_ENABLE, 0, 0L );
//      SendDlgItemMessage( hWnd, IDE_PROXYUSER, WM_ENABLE, 0, 0L );
//      SendDlgItemMessage( hWnd, IDE_PROXYPORT, WM_ENABLE, 0, 0L );
    }

  if ( numSites == 0 )
    {
      numSites = 1;
      sites[0] = defSites[0];
    }

  InsertSites( hWnd );

  bInInit = TRUE;
}


/*
 * Called in response to PSN_SETACTIVE.  Sets dialog items with the values
 * from the temp variables.
 */
void ConfigureProxyDlg( HWND hWnd )
{
  bInInit = FALSE;

  // if a CDDB operation is active, disable everything in this dialog
  CheckDlgButton( hWnd, IDCKB_USEPROXY, bTmpUseProxy?BST_CHECKED:BST_UNCHECKED );
  CheckDlgButton( hWnd, IDCKB_SAVEPASS, bTmpSavePass?BST_CHECKED:BST_UNCHECKED );

  SendDlgItemMessage( hWnd, IDE_PROXYSRVR, EM_SETLIMITTEXT, 80, 0L );
  SetDlgItemText( hWnd, IDE_PROXYSRVR, szTmpProxyAddr );

  SendDlgItemMessage( hWnd, IDE_PROXYPORT, EM_SETLIMITTEXT, 5, 0L );
  SetDlgItemInt( hWnd, IDE_PROXYPORT, iTmpProxyPort, FALSE );
  
//  SetDlgItemInt( hWnd, IDE_SERVERPORT, iTmpHTTPPort, FALSE );

//  SendDlgItemMessage( hWnd, IDE_CDDBSERVER, EM_SETLIMITTEXT, 80, 0L );
//  SendDlgItemMessage( hWnd, IDE_CDDBCGI, EM_SETLIMITTEXT, 80, 0L );
//  SendDlgItemMessage( hWnd, IDE_CDDBSUBMIT, EM_SETLIMITTEXT, 80, 0L );
  SendDlgItemMessage( hWnd, IDE_PROXYUSER, EM_SETLIMITTEXT, 80, 0L );
  SendDlgItemMessage( hWnd, IDE_PROXYPASS, EM_SETLIMITTEXT, 16, 0L );
//  SetDlgItemText( hWnd, IDE_CDDBSERVER, szTmpCDDBServer );
//  SetDlgItemText( hWnd, IDE_CDDBCGI, szTmpCGI );
//  SetDlgItemText( hWnd, IDE_CDDBSUBMIT, szTmpSubmitCGI );
  SetDlgItemText( hWnd, IDE_PROXYUSER, szTmpProxyUser );
  SetDlgItemText( hWnd, IDE_PROXYPASS, szTmpProxyPass );
  

  // for now both buttons are disabled
  SendDlgItemMessage( hWnd, IDBN_SELECTCDDB, WM_ENABLE, 0, 0L );
  SendDlgItemMessage( hWnd, IDBN_RESETCDDB, WM_ENABLE, 0, 0L );

  // sets the dialog's items with the temporary values.
  if ( bInCDDBQuery )
    {
//      SendDlgItemMessage( hWnd, IDE_CDDBSERVER, WM_ENABLE, 0, 0L );
//      SendDlgItemMessage( hWnd, IDBN_SELECTCDDB, WM_ENABLE, 0, 0L );
//      SendDlgItemMessage( hWnd, IDLB_SERVERLIST, WM_ENABLE, 0, 0L );
//      SendDlgItemMessage( hWnd, IDBN_RESETCDDB, WM_ENABLE, 0, 0L );
      SendDlgItemMessage( hWnd, IDCKB_USEPROXY, WM_ENABLE, 0, 0L );
      SendDlgItemMessage( hWnd, IDE_PROXYSRVR, WM_ENABLE, 0, 0L );
      SendDlgItemMessage( hWnd, IDE_PROXYPORT, WM_ENABLE, 0, 0L );
//      SendDlgItemMessage( hWnd, IDE_SERVERPORT, WM_ENABLE, 0, 0L );
      SendDlgItemMessage( hWnd, IDE_PROXYUSER, WM_ENABLE, 0, 0L );
      SendDlgItemMessage( hWnd, IDE_PROXYPORT, WM_ENABLE, 0, 0L );
    }

//  if ( numSites == 0 )
//    {
//      numSites = 1;
//      sites[0] = defSites[0];
//    }

//  InsertSites( hWnd );

  bInInit = TRUE;
}


BOOL CALLBACK CDDBDlgProc( HWND hWnd, UINT uMsg, WPARAM wParam,
			     LPARAM lParam )
{
  //  char buf[81];
  NMHDR *l = (NMHDR *)lParam;
  WORD wID;
  WORD wNotify;
  BOOL bChanged;

  switch( uMsg )
    {
    case WM_INITDIALOG:
      //hOutDlg = hWnd;
      break;

    case WM_COMMAND:
      wID = LOWORD( wParam );
      wNotify = HIWORD( wParam );
      bChanged = TRUE;
      switch( wID )
	{
	case IDCKB_USEPROXY:
	  bTmpUseProxy = !bTmpUseProxy;
	  break;
        
        case IDCKB_SAVEPASS:
          bTmpSavePass = !bTmpSavePass;
          break;

	case IDE_PROXYPORT:
	case IDE_PROXYSRVR:
	case IDE_CDDBSERVER:
	case IDE_CDDBCGI:
	case IDE_CDDBSUBMIT:
        case IDE_SERVERPORT:
        case IDE_PROXYUSER:
        case IDE_PROXYPASS:
	  if ( wNotify != EN_CHANGE )
	    bChanged = FALSE;
	  break;

	case IDLB_SERVERLIST:
	  if ( wNotify == LBN_DBLCLK )
	    {
	      SetCDDBServer( hWnd );
	      //SetFocus( GetDlgItem( hWnd, IDE_CDDBSERVER ) );
	    }
	  break;

	case IDBN_SELECTCDDB:
	  // Start the sites query
	  DialogBox( ghInstance, "CDDBSiteQueryDialog", hWnd, (DLGPROC)CDDBSiteQueryDlgProc );
	  InsertSites( hWnd );
	  bChanged = FALSE;
	  break;

	case IDBN_RESETCDDB:
	  numSites = 1;
	  InsertSites( hWnd );
	  bChanged = FALSE;
	  break;

	default:
	  bChanged = FALSE;
	  break;
	}
      if ( bInInit && bChanged )
	SendMessage( (HWND)GetWindowLong( hWnd, GWL_HWNDPARENT ),
		     PSM_CHANGED, (WPARAM)hWnd, 0L );
      break;

    case WM_NOTIFY:
      switch( l->code )
	{
	case PSN_SETACTIVE:  // sent before page is shown
	  ConfigureCDDBDlg( hWnd );
	  break;

	case PSN_KILLACTIVE:  //losing focus
	  if ( ValidateCDDBDlg( hWnd ) )
	    // ok to lose focus
	    SetWindowLong( hWnd, DWL_MSGRESULT, FALSE );
	  else
	    {
	      // don't use allow loss of focus
	      SetWindowLong( hWnd, DWL_MSGRESULT, TRUE );
	      return TRUE;
	    }
	  break;

	case PSN_QUERYCANCEL:
	  break;

	case PSN_APPLY:
	  // copy temp vars to global vars
	  bUseProxy = bTmpUseProxy;
          bSavePass = bTmpSavePass;
	  lstrcpy( szProxyAddr, szTmpProxyAddr );
	  lstrcpy( szCGI, szTmpCGI );
	  lstrcpy( szSubmitCGI, szTmpSubmitCGI );
	  lstrcpy( szCDDBServer, szTmpCDDBServer );
          lstrcpy( szProxyUser, szTmpProxyUser );
          lstrcpy( szProxyPass, szTmpProxyPass );
	  iProxyPort = iTmpProxyPort;
          iHTTPPort = iTmpHTTPPort;
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


BOOL CALLBACK ProxyDlgProc( HWND hWnd, UINT uMsg, WPARAM wParam,
			     LPARAM lParam )
{
  //  char buf[81];
  NMHDR *l = (NMHDR *)lParam;
  WORD wID;
  WORD wNotify;
  BOOL bChanged;

  switch( uMsg )
    {
    case WM_INITDIALOG:
      //hOutDlg = hWnd;
      break;

    case WM_COMMAND:
      wID = LOWORD( wParam );
      wNotify = HIWORD( wParam );
      bChanged = TRUE;
      switch( wID )
	{
	case IDCKB_USEPROXY:
	  bTmpUseProxy = !bTmpUseProxy;
	  break;
        
        case IDCKB_SAVEPASS:
          bTmpSavePass = !bTmpSavePass;
          break;

	case IDE_PROXYPORT:
	case IDE_PROXYSRVR:
        case IDE_PROXYUSER:
        case IDE_PROXYPASS:
	  if ( wNotify != EN_CHANGE )
	    bChanged = FALSE;
	  break;

	default:
	  bChanged = FALSE;
	  break;
	}
      if ( bInInit && bChanged )
	SendMessage( (HWND)GetWindowLong( hWnd, GWL_HWNDPARENT ),
		     PSM_CHANGED, (WPARAM)hWnd, 0L );
      break;

    case WM_NOTIFY:
      switch( l->code )
	{
	case PSN_SETACTIVE:  // sent before page is shown
	  ConfigureProxyDlg( hWnd );
	  break;

	case PSN_KILLACTIVE:  //losing focus
	  if ( ValidateProxyDlg( hWnd ) )
	    // ok to lose focus
	    SetWindowLong( hWnd, DWL_MSGRESULT, FALSE );
	  else
	    {
	      // don't use allow loss of focus
	      SetWindowLong( hWnd, DWL_MSGRESULT, TRUE );
	      return TRUE;
	    }
	  break;

	case PSN_QUERYCANCEL:
	  break;

	case PSN_APPLY:
	  // copy temp vars to global vars
	  bUseProxy = bTmpUseProxy;
          bSavePass = bTmpSavePass;
	  lstrcpy( szProxyAddr, szTmpProxyAddr );
          lstrcpy( szProxyUser, szTmpProxyUser );
          lstrcpy( szProxyPass, szTmpProxyPass );
	  iProxyPort = iTmpProxyPort;
          iHTTPPort = iTmpHTTPPort;
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


/*
 * Used to initialize the values in the dialog.  If bGet is TRUE, values are
 * read and stored in tmp variables.  Otherwise, the values of the tmp vars
 * are written to the dialogs values.
 */
void GetSetCDDBDlgCurrentVals( BOOL bGet )
{
  if ( bGet )
    {
      bTmpUseProxy = bUseProxy;
      bTmpSavePass = bSavePass;
      lstrcpy( szTmpProxyAddr, szProxyAddr );
      iTmpProxyPort = iProxyPort;
      lstrcpy( szTmpCGI, szCGI );
      lstrcpy( szTmpSubmitCGI, szSubmitCGI );
      lstrcpy( szTmpCDDBServer, szCDDBServer );
      iTmpHTTPPort = iHTTPPort;
      lstrcpy( szTmpProxyUser, szProxyUser );
      lstrcpy( szTmpProxyPass, szProxyPass );
    }
  else
    {
      bUseProxy = bTmpUseProxy;
      bSavePass = bTmpSavePass;
      lstrcpy( szProxyAddr, szTmpProxyAddr );
      lstrcpy( szCGI, szTmpCGI );
      lstrcpy( szSubmitCGI, szTmpSubmitCGI );
      lstrcpy( szCDDBServer, szTmpCDDBServer );
      iProxyPort = iTmpProxyPort;
      iHTTPPort = iTmpHTTPPort;
      lstrcpy( szProxyPass, szTmpProxyPass );
      lstrcpy( szProxyUser, szTmpProxyUser );
    }
}



BOOL CALLBACK MultipleCDDBQueryDlgProc( HWND hWnd, UINT uMsg, WPARAM wParam,
					LPARAM lParam )
{
  WORD wID;
  WORD wNotify;
  LPCDDBQUERY lpq;

  if ( uMsg != WM_INITDIALOG )
    lpq = (LPCDDBQUERY)GetWindowLong( hWnd, GWL_USERDATA );

  switch( uMsg )
    {
    case WM_INITDIALOG:
      lpq = (LPCDDBQUERY)lParam;
      InsertCDDBQueryDialogItems( hWnd, lpq );
      SetWindowLong( hWnd, GWL_USERDATA, (LONG)lpq );
      lpq->num = 0;  // default to the first entry
      break;

    case WM_COMMAND:
      wID = LOWORD( wParam );
      wNotify = HIWORD( wParam );
      switch( wID )
	{
	case IDBN_CDDBQUERYOK:
	  lpq->num = SendDlgItemMessage( hWnd, IDLB_CDDBQUERYSELECT,
					 LB_GETCURSEL, 0, 0L );
	  EndDialog( hWnd, 1 );
	  break;
	case IDBN_CDDBQUERYCNCL:
	  lpq->num = -1;
	  EndDialog( hWnd, 0 );
	  break;
	}
      break;
    }

  return FALSE;
}


void InsertCDDBQueryDialogItems( HWND hWnd, LPCDDBQUERY lpq )
{
  int i;
  char buf[256];

  for( i = 0; i < lpq->num; i++ )
    {
      wsprintf( buf, "%s %s %s / %s", lpq->q[i].categ, lpq->q[i].cddbId,
		lpq->q[i].artist, lpq->q[i].title );
      SendDlgItemMessage( hWnd, IDLB_CDDBQUERYSELECT, LB_ADDSTRING,
			     0, (LPARAM)buf );
    }
  if ( lpq->num )
    SendDlgItemMessage( hWnd, IDLB_CDDBQUERYSELECT, LB_SETCURSEL, 0, 0L );
}



#define WM_SITEQUERYDONE   (WM_USER+1001)

BOOL CALLBACK CDDBSiteQueryDlgProc( HWND hWnd, UINT uMsg, WPARAM wParam,
				    LPARAM lParam )
{
  static BOOL bCancelled;
  HWND hEdit;
  WORD wID;

  switch( uMsg )
    {
    case WM_COMMAND:
      wID = LOWORD( wParam );
      switch( wID )
	{
	case IDBN_SITEQUERYCANCEL:
	  WSACancelBlockingCall();
	  break;
	}
      break;

    case WM_CTLCOLORSTATIC:
      hEdit = GetDlgItem( hWnd, IDE_SITEQUERY );
      if ( hEdit == (HWND)lParam )
	{
	  OutputDebugString( "WM_CTLCOLORSTATIC" );
	  //SetBkColor( (HDC)wParam, RGB(255,255,255) );
	  //SetTextColor( (HDC)wParam, RGB(0,0,0) );
	  //SetDlgMsgResult( hWnd, uMsg, GetStockObject( WHITE_BRUSH ) );
	}
      break;

    case WM_CTLCOLOREDIT:
      //SetWindowLong( hWnd, DWL_MSGRESULT, NULL );
      OutputDebugString( "WM_CTLCOLOREDIT" );
      //SetBkColor( (HDC)wParam, RGB(255,255,255) );
      //SetTextColor( (HDC)wParam, RGB(0,0,0) );
      break;

    case WM_INITDIALOG:
      bCancelled = FALSE;
      SendDlgItemMessage( hWnd, IDE_SITEQUERY, EM_SETREADONLY,
			  (WPARAM)TRUE, 0L );
      DoCDDBSitesQuery( hWnd );
      break;

    case WM_SITEQUERYDONE:
      FinishCDDBSitesQuery( hWnd, bCancelled );
      EndDialog( hWnd, 1 );
      break;

    default:
      return FALSE;
    }

  return TRUE;
}


void DoCDDBSitesQuery( HWND hWnd )
{
  DWORD dwThreadID;
  LPCDDBSITELIST lps;

  bInCDDBSitesQuery = TRUE;

  lps = (LPCDDBSITELIST)GlobalAlloc( GPTR, sizeof(CDDBSITELIST) );
  lps->s = (LPCDDBSITE)GlobalAlloc( GPTR, sizeof(CDDBSITE) * 8 );
  lps->num = 8;

  SetWindowLong( hWnd, GWL_USERDATA, (LONG)lps );

  CREATETHREAD( NULL, 0, (LPTHREAD_START_ROUTINE)DoCDDBSitesQueryThread,
		(LPVOID)hWnd, 0, &dwThreadID );
}


DWORD DoCDDBSitesQueryThread( LPVOID lpParam )
{
  LPCDDBSITELIST lps;
  HWND hWnd;
  char *logBuf, *p;

  hWnd = (HWND)lpParam;

  lps = (LPCDDBSITELIST)GetWindowLong( hWnd, GWL_USERDATA );;

  p = logBuf = (char *)GlobalAlloc( GPTR, 4096 );
  ZeroMemory( logBuf, 4096 );

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
  CDDBSetOption( CDDB_OPT_AGENT, "xtractor 0.13", 0 );
  CDDBSetOption( CDDB_OPT_HTTPPORT, "", iHTTPPort );

  wsprintf( p, "Contacting CDDB server \"%s:%d%s\"\r\n", szCDDBServer, 80,
	    szCGI );
  p += lstrlen( p );
  if ( bUseProxy )
    {
      wsprintf( p, "via proxy \"%s:%d\"\r\n", szProxyAddr, iProxyPort );
      p += lstrlen( p );
    }

  SendDlgItemMessage( hWnd, IDE_SITEQUERY, WM_SETTEXT, 0, (LPARAM)logBuf );
  SendDlgItemMessage( hWnd, IDE_SITEQUERY, EM_SETSEL, (WPARAM)(-1), (LPARAM)logBuf );

  CDDBGetServerList( lps );

  bInCDDBSitesQuery = FALSE;

  PostMessage( hWnd, WM_SITEQUERYDONE, 0, 0L );

  GlobalFree( (HGLOBAL)logBuf );

  return 0;
}


/*
 * If not cancelled, place the returned sites in the parent dialog's
 * sitelist
 */
void FinishCDDBSitesQuery( HWND hWnd, BOOL bCancelled )
{
  LPCDDBSITELIST lps;
  int i;
  //char buf[256];

  lps = (LPCDDBSITELIST)GetWindowLong( hWnd, GWL_USERDATA );

  if ( !bCancelled )
    {
      // add freedb.freedb.org by default
      sites[0] = defSites[0];

      // add the rest
      for( i = 0, numSites = 1; i < lps->num && numSites < 8; i++ )
	{
	  if ( lps->s[i].bHTTP &&
	       lstrcmp( lps->s[i].szServer, "freedb.freedb.org" ) )
	    {
	      sites[numSites] = lps->s[i];
	      numSites++;
	    }
	}

      // display them in the listbox
    }

  GlobalFree( (HGLOBAL)lps->s );
  GlobalFree( (HGLOBAL)lps );
}


void InsertSites( HWND hWnd )
{
  char buf[256];
  int i;

  // clear the list
  SendDlgItemMessage( hWnd, IDLB_SERVERLIST, LB_RESETCONTENT, 0, 0L );

  for( i = 0; i < numSites; i++ )
    {
      LONG lErr;
      
      //server:port cgi location
      wsprintf( buf, "%s:%d %s %s", sites[i].szServer, sites[i].iPort,
		sites[i].szCGI, sites[i].szLocation );
      lErr = SendDlgItemMessage( hWnd, IDLB_SERVERLIST, LB_ADDSTRING,
				 0, (LPARAM)buf );
      
      if ( lErr == LB_ERR )
	wsprintf( buf, "GetLastError() == %d", GetLastError() );
    }
}


void SetCDDBServer( HWND hWnd )
{
  int i;

  i = SendDlgItemMessage( hWnd, IDLB_SERVERLIST, LB_GETCURSEL, 0, 0L );

  if ( i == LB_ERR )
    return;

  SendDlgItemMessage( hWnd, IDE_CDDBSERVER, WM_SETTEXT, 0, (LPARAM)sites[i].szServer );
  SendDlgItemMessage( hWnd, IDE_CDDBCGI, WM_SETTEXT, 0, (LPARAM)sites[i].szCGI );
  SendDlgItemMessage( hWnd, IDE_CDDBSUBMIT, WM_SETTEXT, 0, (LPARAM)"/~cddb/submit.cgi" );
  iTmpHTTPPort = sites[i].iPort;
  SetDlgItemInt( hWnd, IDE_SERVERPORT, iTmpHTTPPort, FALSE );
}
