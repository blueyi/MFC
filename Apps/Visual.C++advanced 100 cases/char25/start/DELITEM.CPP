/**************************************************************************

   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright (C) 1993-1995  Microsoft Corporation.  All Rights Reserved.

   File:          DelItem.cpp
   
   Description:   Provides the functionality for deleting a shortcut 
                  from the start menu.

**************************************************************************/

#define STRICT

/**************************************************************************
   Include Files
**************************************************************************/

#include <windows.h>
#include <windowsx.h>
#include <shlobj.h>
#include "globals.h"
#include "resource.h"

/**************************************************************************
   Local Function Prototypes
**************************************************************************/

BOOL DeleteLink(HWND, LPSTR);
BOOL GetShortcut(HWND, LPSTR, LPSTR);

/**************************************************************************
   Global Variables
**************************************************************************/

/**************************************************************************

   DeleteItem()

**************************************************************************/

BOOL DeleteItem(HWND hWnd)
{
LPITEMIDLIST   pidlStartMenu;
char           szShortcut[MAX_PATH],
               szPath[MAX_PATH];

//get the pidl for the start menu
SHGetSpecialFolderLocation(NULL, CSIDL_STARTMENU, &pidlStartMenu);

//get the path for the start menu folder
SHGetPathFromIDList(pidlStartMenu, szPath);

if(!GetShortcut(hWnd, szPath, szShortcut))
   return FALSE;

if(!DeleteLink(hWnd, szShortcut))
   return FALSE;

return TRUE;
}

/**************************************************************************

   DeleteLink()

**************************************************************************/

BOOL DeleteLink(HWND hWnd, LPSTR lpszShortcut)
{
char  szFile[MAX_PATH];
SHFILEOPSTRUCT fos;

ZeroMemory(szFile, sizeof(szFile));
lstrcpy(szFile, lpszShortcut);

ZeroMemory(&fos, sizeof(fos));
fos.hwnd = hWnd;
fos.wFunc = FO_DELETE;
fos.pFrom = szFile;
fos.fFlags = FOF_SILENT | FOF_ALLOWUNDO;   //send to the recycle bin
SHFileOperation(&fos);

return TRUE;
}

/**************************************************************************

   GetShortcut()

**************************************************************************/

BOOL GetShortcut(HWND hWnd, LPSTR lpszInitDir, LPSTR lpszShortcut)
{
BOOL           ret;
OPENFILENAME   ofn;
char           szFileName[_MAX_PATH] = "",
               szTitleName[_MAX_FNAME + _MAX_EXT] = "";


static CHAR szFilter[] = "Shortcuts\0*.lnk;*.pif\0";

ZeroMemory(&ofn, sizeof(OPENFILENAME));

ofn.lStructSize       = sizeof (OPENFILENAME);
ofn.hwndOwner         = hWnd;
ofn.lpstrFilter       = szFilter;
ofn.nFilterIndex      = 0;
ofn.nMaxFile          = _MAX_PATH;
ofn.nMaxFileTitle     = _MAX_FNAME + _MAX_EXT;
ofn.lpstrTitle        = "Select Shortcut to Delete";
ofn.lpstrFile         = szFileName;
ofn.lpstrFileTitle    = szTitleName;
ofn.lpstrInitialDir   = lpszInitDir;
ofn.Flags             = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_EXPLORER | OFN_NODEREFERENCELINKS;

ret = GetOpenFileName (&ofn) ;

if(ret)
   {
   //the common dialog adds an extension
   lstrcpy(lpszShortcut, szFileName);
   }

return ret;
}

