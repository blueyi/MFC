/*
 * dirsel.c - Copyright (C) 1999,2000 Jay A. Key
 *
 * Directory select dialog.  Not yet implemented.
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
#include "globals.h"
#include "resources.h"


typedef struct {
  BOOL bAutoCreate;
  char szIn[MAX_PATH+1];
  char szOut[MAX_PATH+1];
  HIMAGELIST hImageList;
} DIRSEL, FAR *LPDIRSEL;


BOOL CALLBACK DirSelProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
HWND CreateTreeControl( HWND hParent, LPDIRSEL lpd );
void FillTree( HWND hTree );
void AddDriveToTree( HWND hWnd, HTREEITEM hParent, char *drive, UINT dtype );
BOOL ChildExists( HWND hWnd, HTREEITEM hParent, char *fname );
void HandleTreeMessage( HWND, LPARAM );
char *GetItemPath( HWND hWnd, HTREEITEM hItem, char *path, int maxPathLen );
void ValidateSelDir( HWND hWnd );
BOOL DirExists( char * );
BOOL InvalidDir( char *szDir );
void DisplayDirInTree( char *lpszDir, HTREEITEM hParent, HWND hTreeWnd );


#define DRIVE_DIRECTORY  999


/*
 * Pops up a dialog with a tree-control that allows the selection/creation
 * of a directory.  If bAutoCreate is TRUE, the directory will automatically
 * be created when the user presses OK (user can override this behaviour)
 */
BOOL SelectDirectory( HWND hParent, LPTSTR lpszDir, int len, BOOL bAutoCreate )
{
  BOOL retVal = FALSE;
  LPDIRSEL lpDirSel;

  lpDirSel = (LPDIRSEL)GlobalAlloc( GPTR, sizeof(DIRSEL) );

  if ( !lpDirSel )
    return FALSE;

  lstrcpy( lpDirSel->szIn, lpszDir );
  lstrcpy( lpDirSel->szOut, lpszDir );
  lpDirSel->bAutoCreate = bAutoCreate;

  DialogBoxParam( ghInstance, "DirSelectDialog", hParent, (DLGPROC)DirSelProc, (LPARAM)lpDirSel );

  if ( lstrcmp( lpDirSel->szIn, lpDirSel->szOut ) )
    {
      retVal = TRUE;
      lstrcpyn( lpszDir, lpDirSel->szOut, len );

      CreateDirectory( lpszDir, NULL );
    }

  GlobalFree( (HGLOBAL)lpDirSel );

  return retVal;
}


BOOL CALLBACK DirSelProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
  WORD wCtrlId;
  LPDIRSEL lpd;
  NMHDR *lpn;

  lpd = (LPDIRSEL)GetWindowLong( hWnd, GWL_USERDATA );

  switch( uMsg )
    {
    case WM_INITDIALOG:
      SetWindowLong( hWnd, GWL_USERDATA, (LONG)lParam );
      lpd = (LPDIRSEL)lParam;
      SetDlgItemText( hWnd, IDE_DIRSEL, lpd->szIn );
      CheckDlgButton( hWnd, IDCKB_AUTOCREATE, lpd->bAutoCreate?BST_CHECKED:BST_UNCHECKED );
      DisplayDirInTree( lpd->szIn, NULL, CreateTreeControl( hWnd, lpd ) );
      break;


    case WM_COMMAND:
      wCtrlId = LOWORD(wParam);
      switch( wCtrlId )
	{
	case IDCANCEL:
	case IDBN_DIRSELCANCEL:
	  EndDialog( hWnd, 0 );
	  break;

	case IDE_DIRSEL:
	  if ( HIWORD(wParam) == EN_UPDATE || HIWORD(wParam) == EN_CHANGE )
	    ValidateSelDir( hWnd );
	  break;

	case IDBN_DIRSELOK:
	  GetDlgItemText( hWnd, IDE_DIRSEL, lpd->szOut, MAX_PATH+1 );
	  EndDialog( hWnd, 0 );
	  break;

	case IDCKB_AUTOCREATE:
	  ValidateSelDir( hWnd );
	  break;
	}
      break;

    case WM_NOTIFY:
      lpn = (NMHDR *)lParam;
      if ( lpn->idFrom == ID_DIRSELTREE )
	HandleTreeMessage( lpn->hwndFrom, lParam );
      break;

    default:
      return FALSE;
    }

  // message processed
  return TRUE;
}


HWND CreateTreeControl( HWND hParent, LPDIRSEL lpd )
{
  HWND hRet;
  RECT r;

  r.left = 10;
  r.top = 24;
  r.right = 170;
  r.bottom = 160;
  MapDialogRect( hParent, &r );

  hRet = CreateWindowEx( WS_EX_CLIENTEDGE, WC_TREEVIEW, "",
			 WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES |
			 TVS_HASBUTTONS | TVS_LINESATROOT | TVS_SHOWSELALWAYS,
			 r.left, r.top, r.right - r.left, r.bottom - r.top,
			 hParent, (HMENU)ID_DIRSELTREE, ghInstance, NULL );

  if ( !hRet )
    return hRet;

  lpd->hImageList = ImageList_LoadImage( ghInstance,
					 MAKEINTRESOURCE(idImageList ),
					 16,
					 0,
					 CLR_DEFAULT,
					 IMAGE_BITMAP,
					 LR_DEFAULTCOLOR );
  TreeView_SetImageList( hRet, lpd->hImageList, TVSIL_NORMAL );

  FillTree( hRet );

  return hRet;
}



void FillTree( HWND hTree )
{
  char drive[4];
  char ch;

  for( ch = 'C'; ch <= 'Z'; ch++ )
    {
      UINT retVal;
      lstrcpy( drive, "C:\\" );
      drive[0] = ch;
      retVal = GetDriveType( drive );
      if ( ( retVal == DRIVE_FIXED ) || ( retVal == DRIVE_REMOTE ) )
	{
	  drive[2] = '\0';
	  AddDriveToTree( hTree, NULL, drive, retVal );
	}
    }
}


void AddDriveToTree( HWND hWnd, HTREEITEM hParent, char *drive, UINT dtype )
{
  TV_INSERTSTRUCT tvi;
  HTREEITEM hDriveRoot;
  HTREEITEM hItem;
  WIN32_FIND_DATA wd;
  HANDLE hFF;
  char findBuf[MAX_PATH+1];
  BOOL bFileFound;

  // add the root entry first
  if ( !hParent )
    {
      ZeroMemory( &tvi, sizeof(tvi) );
      tvi.hInsertAfter    = TVI_SORT;
      tvi.item.mask       = TVIF_STATE | TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
      tvi.item.stateMask  = TVIS_EXPANDED | TVIS_SELECTED;
      tvi.item.pszText    = drive;
      if ( dtype == DRIVE_FIXED )
	{
	  tvi.item.iImage     = 0;
	  tvi.item.iSelectedImage = 0;
	}
      else if ( dtype == DRIVE_REMOTE )
	{
	  tvi.item.iImage     = 1;
	  tvi.item.iSelectedImage = 1;
	}
      hDriveRoot = (HTREEITEM)TreeView_InsertItem( hWnd, &tvi );
    }
  else
    hDriveRoot = hParent;

  // add first-level subdirectories
  wsprintf( findBuf, "%s%s*.*", drive, drive[lstrlen(drive)-1]!='\\'?"\\":"" );
  hFF = FindFirstFile( findBuf, &wd );
  bFileFound = ( hFF != INVALID_HANDLE_VALUE );
  while( bFileFound )
    {
      if ( (wd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
	   lstrcmp( wd.cFileName, "." ) && lstrcmp( wd.cFileName, ".." ) )
	{
	  if ( !ChildExists( hWnd, hDriveRoot, wd.cFileName ) )
	    {
	      ZeroMemory( &tvi, sizeof(tvi) );
	      tvi.hInsertAfter      = TVI_SORT;
	      tvi.hParent           = hDriveRoot;
	      tvi.item.mask         = TVIF_STATE | TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	      tvi.item.stateMask    = TVIS_EXPANDED | TVIS_SELECTED;
	      tvi.item.pszText      = wd.cFileName;
	      tvi.item.cchTextMax   = lstrlen( wd.cFileName ) + 1;
	      tvi.item.iImage       = 3;
	      tvi.item.iSelectedImage = 4;
	      hItem = (HTREEITEM)TreeView_InsertItem( hWnd, &tvi );
	    }
	}
      bFileFound = FindNextFile( hFF, &wd );
      if ( !bFileFound )
	FindClose( hFF );
    }
  // select the root item?
  hItem = (HTREEITEM)TreeView_GetChild( hWnd, hDriveRoot );
}


BOOL ChildExists( HWND hWnd, HTREEITEM hParent, char *fname )
{
  HTREEITEM hItem;
  TV_ITEM tv;
  char pszBuf[MAX_PATH+1];

  hItem = (HTREEITEM)TreeView_GetChild( hWnd, hParent );
  while( hItem )
    {
      ZeroMemory( &tv, sizeof(tv) );
      tv.mask       = TVIF_TEXT;
      tv.pszText    = pszBuf;
      tv.cchTextMax = MAX_PATH+1;
      tv.hItem      = hItem;
      if ( TreeView_GetItem( hWnd, &tv ) )
	{
	  if ( !lstrcmpi( pszBuf, fname ) )
	    return TRUE;
	}
      hItem = (HTREEITEM)TreeView_GetNextSibling( hWnd, hItem );
    }

  return FALSE;
}


void HandleTreeMessage( HWND hWnd, LPARAM lParam )
{
  LPNM_TREEVIEW lpn = (LPNM_TREEVIEW)lParam;
  char path[MAX_PATH+1];
  HTREEITEM hChild;

  switch( lpn->hdr.code )
    {
    case TVN_ITEMEXPANDING:
      // add or remove grandchildren, use lpn->action to determine
      // if it is going to expand (TVE_EXPAND) or collapse (TVE_COLLAPSE)
      if ( lpn->action & TVE_EXPAND )
	{
	  // check for new children
	  hChild = (HTREEITEM)TreeView_GetChild( hWnd, lpn->itemNew.hItem );
	  while( hChild )
	    {
	      GetItemPath( hWnd, hChild, path, MAX_PATH+1 );
	      AddDriveToTree( hWnd, hChild, path, DRIVE_DIRECTORY );
	      hChild = (HTREEITEM)TreeView_GetNextSibling( hWnd, hChild );
	    }
	}
      else  // ( lpn->action & TVE_COLLAPSE )
	{
	  hChild = (HTREEITEM)TreeView_GetChild( hWnd, lpn->itemNew.hItem );
	  while( hChild )
	    {
	      HTREEITEM hGrandchild;
	      hGrandchild = (HTREEITEM)TreeView_GetChild( hWnd, hChild );
	      while( hGrandchild )
		{
		  TreeView_DeleteItem( hWnd, hGrandchild );
		  hGrandchild = (HTREEITEM)TreeView_GetChild( hWnd, hChild );
		}
	      hChild = (HTREEITEM)TreeView_GetNextSibling( hWnd, hChild );
	    }
	}
      break;

    case TVN_SELCHANGED:
      GetItemPath( hWnd, lpn->itemNew.hItem, path, MAX_PATH+1 );
      SetDlgItemText( GetParent( hWnd ), IDE_DIRSEL, path );
      break;

    default:
      break;
    }
}


char *GetItemPath( HWND hWnd, HTREEITEM hItem, char *path, int maxPathLen )
{
  TV_ITEM tvi;
  HTREEITEM hParent;
  char pszTemp[MAX_PATH+1];

  path[0] = '\0';

  hParent = (HTREEITEM)TreeView_GetParent( hWnd, hItem );
  if ( hParent )
    GetItemPath( hWnd, hParent, path, maxPathLen );

  pszTemp[0] = '\0';
  tvi.mask       = TVIF_TEXT;
  tvi.pszText    = pszTemp;
  tvi.cchTextMax = MAX_PATH+1;
  tvi.hItem      = hItem;
  if ( TreeView_GetItem( hWnd, &tvi ) )
    {
      strcat( path, tvi.pszText );
      strcat( path, "\\" );
    }

  return path;
}


void ValidateSelDir( HWND hWnd )
{
  char buf[MAX_PATH+1];

  buf[0] = '\0';
  GetDlgItemText( hWnd, IDE_DIRSEL, buf, MAX_PATH+1 );

  if ( !buf[0] || InvalidDir( buf ) )
    {
      EnableWindow( GetDlgItem( hWnd, IDBN_DIRSELOK ), FALSE );
      return;
    }

  if ( IsDlgButtonChecked( hWnd, IDCKB_AUTOCREATE ) ||
       DirExists( buf ) )
    {
      EnableWindow( GetDlgItem( hWnd, IDBN_DIRSELOK ), TRUE );
      return;
    }

  EnableWindow( GetDlgItem( hWnd, IDBN_DIRSELOK ), FALSE );
}


/*
 * Returns TRUE if the directory szDir is not syntactically correct
 */
BOOL InvalidDir( char *szDir )
{
  return FALSE;
}


void DisplayDirInTree( char *lpszDir, HTREEITEM hParent, HWND hTreeWnd )
{
  int i;
  char *buf;
  HTREEITEM hChild;
  TV_ITEM tvi;
  char *itemBuf;
  static char foobuf[256];
  
  wsprintf( foobuf, "DisplayDirInTree( \"%s\", %04X, %04X )", lpszDir, hParent, hTreeWnd );
  OutputDebugString( foobuf );

  if ( *lpszDir == '\0' )
    {
      // display the parent item and return
      TreeView_SelectItem( hTreeWnd, hParent );
      TreeView_Expand( hTreeWnd, hParent, TVE_EXPAND );
      return;
    }

  buf = (char *)GlobalAlloc( GPTR, lstrlen( lpszDir ) + 1 );
  itemBuf = (char *)GlobalAlloc( GPTR, MAX_PATH+1 );

  lstrcpy( buf, lpszDir );
  for( i = 0; buf[i]; i++ )
    {
      if ( buf[i] == '\\' )
	buf[i] = 0;
    }

  if ( !hParent )
    {
      OutputDebugString( "Getting the parent..." );
      hChild = TreeView_GetRoot( hTreeWnd );
      TreeView_SelectItem( hTreeWnd, hChild );
    }
  else
    {
      hChild = TreeView_GetChild( hTreeWnd, hParent );
      TreeView_SelectItem( hTreeWnd, hChild );
    }

  if ( !hChild )
    OutputDebugString( "No child found..." );

  while( hChild )
    {
      tvi.mask     = TVIF_TEXT;
      tvi.pszText  = itemBuf;
      tvi.cchTextMax = MAX_PATH+1;
      tvi.hItem    = hChild;
      if ( TreeView_GetItem( hTreeWnd, &tvi ) )
	{
	  OutputDebugString( itemBuf );
	  if ( !lstrcmpi( buf, itemBuf ) )
	    {
	      DisplayDirInTree( lpszDir + lstrlen(buf) + 1, hChild, hTreeWnd );
	      hChild = NULL;
	    }
	}
      else
	OutputDebugString( "TreeView_GetItem failed!" );
      if ( hChild )
	hChild = TreeView_GetNextSibling( hTreeWnd, hChild );
    }

  GlobalFree( (HGLOBAL)buf );
  GlobalFree( (HGLOBAL)itemBuf );
}

