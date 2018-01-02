/**************************************************************************

   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright (C) 1993-1995  Microsoft Corporation.  All Rights Reserved.

   File:          AddItem.cpp
   
   Description:   Provides the functionality for adding a shortcut to 
                  the start menu.

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
extern "C" {

BOOL GetShortcut(HWND, LPSTR);
BOOL GetProgram(HWND, LPSTR);
BOOL GetShortcutName(HWND, LPSTR);
BOOL CALLBACK GetShortcutNameDlgProc(HWND, UINT, WPARAM, LPARAM);
HRESULT CreateLink(LPCSTR, LPSTR, LPSTR);

}

/**************************************************************************
   Global Variables
**************************************************************************/

char  g_szProgram[MAX_PATH];

/**************************************************************************

   AddItem()

**************************************************************************/

BOOL AddItem(HWND hWnd)
{
char  szProgram[MAX_PATH],
      szShortcut[MAX_PATH];

//get the program to create the shortcut for
if(!GetProgram(hWnd, szProgram))
   return FALSE;

//get the location of the new shortcut
if(!GetShortcut(hWnd, szShortcut))
   return FALSE;

//create the shortcut
CreateLink(szProgram, szShortcut, "");

return TRUE;
}

/**************************************************************************

   GetShortcut()

**************************************************************************/

BOOL GetShortcut(HWND hWnd, LPSTR lpszPath)
{
LPITEMIDLIST   pidlStartMenu,
               pidlDestination;
char           szTemp[MAX_PATH];

//get the pidl for the start menu
SHGetSpecialFolderLocation(NULL, CSIDL_STARTMENU, &pidlStartMenu);

//get the destination folder
if(!GetFolder(hWnd, &pidlDestination, pidlStartMenu, szTemp, "Select Location for Shortcut"))
   return FALSE;

//get the path for the folder
SHGetPathFromIDList(pidlDestination, lpszPath);

//append the shorcut filename
if(!GetShortcutName(hWnd, lpszPath))
   return FALSE;

//add .LNK to the shortcut file name
lstrcat(lpszPath, ".lnk");

return TRUE;
}

/**************************************************************************

   GetFolder()

**************************************************************************/

BOOL GetFolder(   HWND hwndParent,
                  LPITEMIDLIST *ppidlDestination,
                  LPITEMIDLIST pidlRoot,
                  LPSTR lpszDisplayName,
                  LPCSTR lpszTitle)
{
BROWSEINFO  BrInfo;

ZeroMemory(&BrInfo, sizeof(BrInfo));
BrInfo.hwndOwner        = hwndParent;
BrInfo.pidlRoot         = pidlRoot; //browse from the start menu down
BrInfo.pszDisplayName   = lpszDisplayName;
BrInfo.lpszTitle        = lpszTitle;

//use the shell's folder browser
*ppidlDestination = SHBrowseForFolder(&BrInfo);

//did the user select the cancel button
if(NULL == *ppidlDestination)
   return FALSE;

return TRUE;
}

/**************************************************************************

   GetProgram()

**************************************************************************/

BOOL GetProgram(HWND hWnd, LPSTR lpszSource)
{
BOOL           ret;
OPENFILENAME   ofn;
char           szFileName[_MAX_PATH] = "",
               szTitleName[_MAX_FNAME + _MAX_EXT] = "";


static CHAR szFilter[] = "Programs\0*.exe\0";

ZeroMemory(&ofn, sizeof(OPENFILENAME));

ofn.lStructSize       = sizeof (OPENFILENAME);
ofn.hwndOwner         = hWnd;
ofn.lpstrFilter       = szFilter;
ofn.nFilterIndex      = 0;
ofn.nMaxFile          = _MAX_PATH;
ofn.nMaxFileTitle     = _MAX_FNAME + _MAX_EXT;
ofn.lpstrTitle        = "Select Program";
ofn.lpstrFile         = szFileName;
ofn.lpstrFileTitle    = szTitleName;
ofn.Flags             = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_EXPLORER;

ret = GetOpenFileName (&ofn) ;

if(ret)
   {
   lstrcpy(lpszSource, szFileName);
   
   GetFileTitle(szFileName, g_szProgram, sizeof(g_szProgram));
   }

return ret;
}

/**************************************************************************

   GetShortcutName()

**************************************************************************/

BOOL GetShortcutName(HWND hWnd, LPSTR lpszPath)
{
return DialogBoxParam(  g_hInstance, 
                        MAKEINTRESOURCE(IDD_GET_NAME), 
                        hWnd,
                        GetShortcutNameDlgProc,
                        (LPARAM)lpszPath);
}

/**************************************************************************

   GetShortcutNameDlgProc()

**************************************************************************/

BOOL CALLBACK GetShortcutNameDlgProc(  HWND hWnd, 
                                       UINT uMsg, 
                                       WPARAM wParam, 
                                       LPARAM lParam)
{
static LPSTR   lpszShorcut;

switch(uMsg)
   {
   case WM_INITDIALOG:
      lpszShorcut = (LPSTR)lParam;
      
      SetWindowText(hWnd, "Enter Shortcut Name");
      SetDlgItemText(hWnd, IDC_STATIC_TEXT, "Enter a name for the shortcut");
      SetDlgItemText(hWnd, IDC_TEXT, g_szProgram);
      return TRUE;

   case WM_COMMAND:
      switch (GET_WM_COMMAND_ID(wParam, lParam))
         {
         case IDOK:
            {
            char  szTemp[MAX_PATH];
            
            GetDlgItemText(hWnd, IDC_TEXT, szTemp, sizeof(szTemp));
            lstrcat(lpszShorcut, "\\");
            lstrcat(lpszShorcut, szTemp);
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

/**************************************************************************

   CreateLink()

   uses the shell's IShellLink and IPersistFile interfaces to create and 
   store a shortcut to the specified object. 
 
   Returns the result of calling the member functions of the interfaces. 
 
   lpszPathObj - address of a buffer containing the path of the object 

   lpszPathLink - address of a buffer containing the path where the shell 
      link is to be stored 

   lpszDesc - address of a buffer containing the description of the shell 
      link 
 
**************************************************************************/

HRESULT CreateLink(  LPCSTR lpszSource, 
                     LPSTR lpszTarget, 
                     LPSTR lpszDesc) 
{ 
HRESULT hres; 
IShellLink* pShellLink; 

//CoInitialize must be called before this
// Get a pointer to the IShellLink interface. 
hres = CoCreateInstance(   CLSID_ShellLink, 
                           NULL, 
                           CLSCTX_INPROC_SERVER, 
                           IID_IShellLink, 
                           (LPVOID*)&pShellLink); 
if (SUCCEEDED(hres)) 
   { 
   IPersistFile* pPersistFile; 

   // Set the path to the shortcut target, and add the description. 
   pShellLink->SetPath(lpszSource); 
   pShellLink->SetDescription(lpszDesc); 

   // Query IShellLink for the IPersistFile interface for saving the 
   // shortcut in persistent storage. 
   hres = pShellLink->QueryInterface(IID_IPersistFile, (LPVOID*)&pPersistFile); 

   if (SUCCEEDED(hres)) 
      { 
      WCHAR wsz[MAX_PATH]; 

      // Ensure that the string is ANSI. 
      MultiByteToWideChar( CP_ACP, 
                           0, 
                           lpszTarget, 
                           -1, 
                           wsz, 
                           MAX_PATH); 

      // Save the link by calling IPersistFile::Save. 
      hres = pPersistFile->Save(wsz, TRUE); 
 
      if(FAILED(hres)) 
         ErrorHandler();

      pPersistFile->Release(); 
      } 

   pShellLink->Release(); 
   } 

return hres; 
}

