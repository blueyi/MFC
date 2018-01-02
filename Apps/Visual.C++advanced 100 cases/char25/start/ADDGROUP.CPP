/**************************************************************************

   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright (C) 1993-1995  Microsoft Corporation.  All Rights Reserved.

   File:          AddGroup.cpp
   
   Description:   Provides the functionality for adding a group to the 
                  programs folder under the start menu.

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

BOOL CreateFolder(LPSTR);
BOOL GetFolderName(HWND, LPSTR);
BOOL CALLBACK GetFolderNameDlgProc(HWND, UINT, WPARAM, LPARAM);

/**************************************************************************
   Global Variables
**************************************************************************/

BOOL AddGroup(HWND hWnd)
{
LPITEMIDLIST   pidlStartMenu,
               pidlDestination;
char           szTemp[MAX_PATH],
               szPath[MAX_PATH];

//get the pidl for the start menu - thgis will be used to intialize the folder browser
SHGetSpecialFolderLocation(NULL, CSIDL_PROGRAMS, &pidlStartMenu);

//get the parent of the new folder
if(!GetFolder(hWnd, &pidlDestination, pidlStartMenu, szTemp, "Select Location for Folder"))
   return FALSE;

//get the path for the folder
SHGetPathFromIDList(pidlDestination, szPath);

//get the name of the new folder
GetFolderName(hWnd, szPath);

//create the folder
CreateFolder(szPath);

return TRUE;
}

/**************************************************************************

   CreateFolder()

**************************************************************************/

BOOL CreateFolder(LPSTR lpszFolder) 
{ 
//create the folder
CreateDirectory(lpszFolder, NULL);

//notify the shell that you made a change
SHChangeNotify(SHCNE_MKDIR, SHCNF_PATH, lpszFolder, 0);

return TRUE;
}

/**************************************************************************

   GetFolderName()

**************************************************************************/

BOOL GetFolderName(HWND hWnd, LPSTR lpszPath)
{
return DialogBoxParam(  g_hInstance, 
                        MAKEINTRESOURCE(IDD_GET_NAME), 
                        hWnd,
                        GetFolderNameDlgProc,
                        (LPARAM)lpszPath);
}

/**************************************************************************

   GetFolderNameDlgProc()

**************************************************************************/

BOOL CALLBACK GetFolderNameDlgProc( HWND hWnd, 
                                    UINT uMsg, 
                                    WPARAM wParam, 
                                    LPARAM lParam)
{
static LPSTR   lpszFolder;

switch(uMsg)
   {
   case WM_INITDIALOG:
      lpszFolder = (LPSTR)lParam;
      
      SetWindowText(hWnd, "Enter Folder Name");
      SetDlgItemText(hWnd, IDC_STATIC_TEXT, "Enter a name for the folder");
      return TRUE;

   case WM_COMMAND:
      switch (GET_WM_COMMAND_ID(wParam, lParam))
         {
         case IDOK:
            {
            char  szTemp[MAX_PATH];
            
            GetDlgItemText(hWnd, IDC_TEXT, szTemp, sizeof(szTemp));
            lstrcat(lpszFolder, "\\");
            lstrcat(lpszFolder, szTemp);
            EndDialog(hWnd, TRUE);
            }      
            break;
            
         case IDCANCEL:
            EndDialog(hWnd, FALSE);
            break;
         }
      return TRUE;
   }
   
return FALSE;
}

