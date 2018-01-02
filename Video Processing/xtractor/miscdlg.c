/*
 * miscdlg.c - Copyright (C) 1999,2000 Jay A. Key
 *
 * Property sheet dialog for misc. options, including m3u playlist 
 * generation.
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
int getM3UFile( HWND hWnd );

// save old settings
static BOOL bTmpWritePlaylist;
static BOOL bTmpUseAlbumName;
static char szTmpPlaylist[MAX_PATH+1];
static char szTmpMangleString[MAX_PATH+1];

static BOOL bInInit = FALSE;

/*
 * Called in response to PSN_KILLACTIVE.  Should validate all values in the
 * dialog, and save them to the temp variables.
 */
BOOL ValidateMiscDlg( HWND hWnd )
{
  return TRUE;
}



/*
 * Called in response to PSN_SETACTIVE.  Sets dialog items with the values
 * from the temp variables.
 */
void ConfigureMiscDlg( HWND hWnd )
{
  bInInit = TRUE;

  CheckDlgButton( hWnd, IDCKB_M3UENABLE, bTmpWritePlaylist?BST_CHECKED:BST_UNCHECKED );
  if ( bTmpUseAlbumName )
    CheckRadioButton( hWnd, IDRBN_M3UALBUMNAME, IDRBN_M3USPECIFYNAME, IDRBN_M3UALBUMNAME );
  else
    CheckRadioButton( hWnd, IDRBN_M3UALBUMNAME, IDRBN_M3USPECIFYNAME, IDRBN_M3USPECIFYNAME );

  if ( szTmpPlaylist[0] )
    SetDlgItemText( hWnd, IDE_M3UFILE, szTmpPlaylist );

  if ( szMangleString[0] )
    SetDlgItemText( hWnd, IDE_FNAMEMACRO, szMangleString );

  bInInit = FALSE;
}


BOOL CALLBACK MiscDlgProc( HWND hWnd, UINT uMsg, WPARAM wParam,
			   LPARAM lParam )
{
  NMHDR *l = (NMHDR *)lParam;
  WORD wID;
  WORD wNotify;
  BOOL bChanged;

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
	case IDCKB_M3UENABLE:
	  bTmpWritePlaylist = !bTmpWritePlaylist;
	  break;

	case IDRBN_M3UALBUMNAME:
	  bTmpUseAlbumName = TRUE;
	  break;

	case IDRBN_M3USPECIFYNAME:
	  bTmpUseAlbumName = FALSE;
	  break;

	case IDBN_M3UBROWSE:
	  if ( !getM3UFile( hWnd ) )
	    bChanged = FALSE;
	  else
	    {
	      CheckRadioButton( hWnd,
				IDRBN_M3UALBUMNAME,
				IDRBN_M3USPECIFYNAME,
				IDRBN_M3USPECIFYNAME );
	      bTmpUseAlbumName = FALSE;
	    }
	  break;

	case IDE_M3UFILE:
	  if ( wNotify != EN_CHANGE )
	    bChanged = FALSE;
	  else
	    GetDlgItemText( hWnd, IDE_M3UFILE, szTmpPlaylist, MAX_PATH+1 );
	  break;

	case IDE_FNAMEMACRO:
	  if ( wNotify != EN_CHANGE )
	    bChanged = FALSE;
	  else
	    GetDlgItemText( hWnd, IDE_FNAMEMACRO, szTmpMangleString, MAX_PATH+1 );
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
	  ConfigureMiscDlg( hWnd );
	  break;

	case PSN_KILLACTIVE:  //losing focus
#if 1
	  if ( ValidateMiscDlg( hWnd ) )
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
	  bWritePlaylist = bTmpWritePlaylist;
	  bUseAlbumName = bTmpUseAlbumName;
	  lstrcpy( szPlaylist, szTmpPlaylist );
	  lstrcpy( szMangleString, szTmpMangleString );
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

// gets the name of the playlist file.  returns 1 if successful, 0 on cancel
int getM3UFile( HWND hWnd )
{
  OPENFILENAME o;
  char buf[MAX_PATH+1];

  lstrcpy( buf, "foo.m3u" );

  ZeroMemory( &o, sizeof(o) );
  o.lStructSize    = sizeof(o);
  o.hwndOwner      = hWnd;
  o.hInstance      = ghInstance;
  o.lpstrFilter    = "M3U Playlists\0*.M3U\0";
  o.lpstrFile      = buf;
  o.nMaxFile       = MAX_PATH+1;
  o.lpstrTitle     = "Select Playlist File";
  o.Flags          = OFN_CREATEPROMPT | OFN_NOCHANGEDIR;
  o.lpstrDefExt    = "m3u";

  if ( GetOpenFileName( &o ) )
    {
      SetDlgItemText( hWnd, IDE_M3UFILE, o.lpstrFile );
      return 1;
    }

  return 0;
}


/*
 * Used to initialize the values in the dialog.  If bGet is TRUE, values are
 * read and stored in tmp variables.  Otherwise, the values of the tmp vars
 * are written to the dialogs values.
 */
void GetSetMiscDlgCurrentVals( BOOL bGet )
{
  if ( bGet )
    {
      bTmpWritePlaylist = bWritePlaylist;
      bTmpUseAlbumName = bUseAlbumName;
      lstrcpy( szTmpPlaylist, szPlaylist );
      lstrcpy( szTmpMangleString, szMangleString );
    }
  else
    {
      bWritePlaylist = bTmpWritePlaylist;
      bUseAlbumName = bTmpUseAlbumName;
      lstrcpy( szPlaylist, szTmpPlaylist );
      lstrcpy( szMangleString, szTmpMangleString );
    }
}
