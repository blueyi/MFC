/*
 * vorbdlg.c - Copyright (C) 1999,2000 Jay A. Key
 *
 * Property sheet dialog for vorb_enc.dll configuration
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
#include <commdlg.h>
#include "resources.h"
#include "globals.h"

void dbprintf( char *, ... );

// save old settings
static WORD wTmpVorbBitrate;
static char szTmpVorbVersion[81];
static char szTmpVorbOrganization[81];
static char szTmpVorbDescription[81];
static char szTmpVorbGenre[81];
static char szTmpVorbDate[81];
static char szTmpVorbLocation[81];
static char szTmpVorbCopyright[81];
#define NUMBITRATES   7
static WORD bitrates[7] = { 64, 96, 128, 160, 192, 256, 350 };

static BOOL bInInit = FALSE;
static BOOL bListsInit = FALSE;

/*
 * Called in response to PSN_KILLACTIVE.  Should validate all values in the
 * dialog, and save them to the temp variables.
 */
BOOL ValidateVorbDlg( HWND hWnd )
{
  return TRUE;
}



/*
 * Called in response to PSN_SETACTIVE.  Sets dialog items with the values
 * from the temp variables.
 */
#if 0
#define IDCBX_VORBBITRATE     2500
#define IDE_VORBVERSION       2501
#define IDE_VORBORGANIZATION  2502
#define IDE_VORBDESCRIPTION   2503
#define IDE_VORBGENRE         2504
#define IDE_VORBDATE          2505
#define IDE_VORBLOCATION      2506
#define IDE_VORBCOPYRIGHT     2507
#endif
void ConfigureVorbDlg( HWND hWnd )
{
  int i;
  BOOL bFound = FALSE;

  bInInit = TRUE;

  // config info here
  if ( !bListsInit )
    {
      char szTmp[32];
      for( i = 0; i < NUMBITRATES; i++ )
	{
	  wsprintf( szTmp, "%d", bitrates[i] );
	  SendDlgItemMessage( hWnd, IDCBX_VORBBITRATE, CB_ADDSTRING,
			      0, (LPARAM)szTmp );
	}

      bListsInit = TRUE;
    }

  for( i = 0; i < NUMBITRATES; i++ )
    {
      if ( wTmpVorbBitrate == bitrates[i] )
	{
	  SendDlgItemMessage( hWnd, IDCBX_VORBBITRATE, CB_SETCURSEL, (WPARAM)i, 0L );
	  bFound = TRUE;
	}
    }

  if ( !bFound )
    {
      SendDlgItemMessage( hWnd, IDCBX_VORBBITRATE, CB_SETCURSEL, (WPARAM)1, 0L );
      wTmpVorbBitrate = 128;
    }

  SetDlgItemText( hWnd, IDE_VORBVERSION, szTmpVorbVersion );
  SetDlgItemText( hWnd, IDE_VORBORGANIZATION, szTmpVorbOrganization );
  SetDlgItemText( hWnd, IDE_VORBDESCRIPTION, szTmpVorbDescription );
  SetDlgItemText( hWnd, IDE_VORBGENRE, szTmpVorbGenre );
  SetDlgItemText( hWnd, IDE_VORBDATE, szTmpVorbDate );
  SetDlgItemText( hWnd, IDE_VORBLOCATION, szTmpVorbLocation );
  SetDlgItemText( hWnd, IDE_VORBCOPYRIGHT, szTmpVorbCopyright );

  bInInit = FALSE;
}


BOOL CALLBACK VorbDlgProc( HWND hWnd, UINT uMsg, WPARAM wParam,
			   LPARAM lParam )
{
  NMHDR *l = (NMHDR *)lParam;
  WORD wID;
  WORD wNotify;
  BOOL bChanged;
  int i;

  switch( uMsg )
    {
    case WM_INITDIALOG:
      break;

    case WM_COMMAND:
      wID = LOWORD( wParam );
      wNotify = HIWORD( wParam );
      bChanged = TRUE;
      switch( wID )
	{
	case IDE_VORBVERSION:
	  if ( wNotify == EN_CHANGE )
	    GetDlgItemText( hWnd, IDE_VORBVERSION, szTmpVorbVersion, 81 );
	  else
	    bChanged = FALSE;
	  break;

	case IDE_VORBORGANIZATION:
	  if ( wNotify == EN_CHANGE )
	    GetDlgItemText( hWnd, IDE_VORBORGANIZATION, szTmpVorbOrganization, 81 );
	  else
	    bChanged = FALSE;
	  break;

	case IDE_VORBDESCRIPTION:
	  if ( wNotify == EN_CHANGE )
	    GetDlgItemText( hWnd, IDE_VORBDESCRIPTION, szTmpVorbDescription, 81 );
	  else
	    bChanged = FALSE;
	  break;

	case IDE_VORBGENRE:
	  if ( wNotify == EN_CHANGE )
	    GetDlgItemText( hWnd, IDE_VORBGENRE, szTmpVorbGenre, 81 );
	  else
	    bChanged = FALSE;
	  break;

	case IDE_VORBDATE:
	  if ( wNotify == EN_CHANGE )
	    GetDlgItemText( hWnd, IDE_VORBDATE, szTmpVorbDate, 81 );
	  else
	    bChanged = FALSE;
	  break;

	case IDE_VORBLOCATION:
	  if ( wNotify == EN_CHANGE )
	    GetDlgItemText( hWnd, IDE_VORBLOCATION, szTmpVorbLocation, 81 );
	  else
	    bChanged = FALSE;
	  break;

	case IDE_VORBCOPYRIGHT:
	  if ( wNotify == EN_CHANGE )
	    GetDlgItemText( hWnd, IDE_VORBCOPYRIGHT, szTmpVorbCopyright, 81 );
	  else
	    bChanged = FALSE;
	  break;

	case IDCBX_VORBBITRATE:
	  if ( wNotify == CBN_SELCHANGE )
	    {
	      i = SendDlgItemMessage( hWnd, IDCBX_VORBBITRATE, CB_GETCURSEL, 0, 0L );
	      wTmpVorbBitrate = bitrates[i];
	    }
	  else
	    bChanged = FALSE;
	  break;

	default:
	  break;
	}
      if ( !bInInit && bChanged )
	SendMessage( (HWND)GetWindowLong( hWnd, GWL_HWNDPARENT ),
		     PSM_CHANGED, (WPARAM)hWnd, 0L );
      break;

    case WM_NOTIFY:
      switch( l->code )
	{
	case PSN_SETACTIVE:  // sent before page is shown
	  ConfigureVorbDlg( hWnd );
	  break;

	case PSN_KILLACTIVE:  //losing focus
#if 1
	  if ( ValidateVorbDlg( hWnd ) )
	    // ok to lose focus
	    SetWindowLong( hWnd, DWL_MSGRESULT, FALSE );
	  else
	    {
	      // don't use allow loss of focus
	      SetWindowLong( hWnd, DWL_MSGRESULT, TRUE );
	      return TRUE;
	    }
#endif
	  break;

	case PSN_QUERYCANCEL:
	  break;

	case PSN_APPLY:
	  // save the temp variables
	  wVorbBitrate = wTmpVorbBitrate;
	  lstrcpy( szVorbVersion, szTmpVorbVersion );
	  lstrcpy( szVorbOrganization, szTmpVorbOrganization );
	  lstrcpy( szVorbDescription, szTmpVorbDescription );
	  lstrcpy( szVorbGenre, szTmpVorbGenre );
	  lstrcpy( szVorbDate, szTmpVorbDate );
	  lstrcpy( szVorbLocation, szTmpVorbLocation );
	  lstrcpy( szVorbCopyright, szTmpVorbCopyright );
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
void GetSetVorbDlgCurrentVals( BOOL bGet )
{
  if ( bGet )
    {
      // set temp vars
      wTmpVorbBitrate = wVorbBitrate;
      lstrcpy( szTmpVorbVersion, szVorbVersion );
      lstrcpy( szTmpVorbOrganization, szVorbOrganization );
      lstrcpy( szTmpVorbDescription, szVorbDescription );
      lstrcpy( szTmpVorbGenre, szVorbGenre );
      lstrcpy( szTmpVorbDate, szVorbDate );
      lstrcpy( szTmpVorbLocation, szVorbLocation );
      lstrcpy( szTmpVorbCopyright, szVorbCopyright );
      bListsInit = FALSE;
    }
  else
    {
      // save temp vars back to global vars
      wVorbBitrate = wTmpVorbBitrate;
      lstrcpy( szVorbVersion, szTmpVorbVersion );
      lstrcpy( szVorbOrganization, szTmpVorbOrganization );
      lstrcpy( szVorbDescription, szTmpVorbDescription );
      lstrcpy( szVorbGenre, szTmpVorbGenre );
      lstrcpy( szVorbDate, szTmpVorbDate );
      lstrcpy( szVorbLocation, szTmpVorbLocation );
      lstrcpy( szVorbCopyright, szTmpVorbCopyright );
    }
}
