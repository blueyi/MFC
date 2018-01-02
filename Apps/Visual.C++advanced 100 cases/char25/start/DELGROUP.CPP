/**************************************************************************

   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright (C) 1993-1995  Microsoft Corporation.  All Rights Reserved.

   File:          DelGroup.cpp
   
   Description:   Provides the functionality for deleting a group.

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

BOOL DeleteFolder(HWND, LPSTR);

/**************************************************************************
   Global Variables
**************************************************************************/

/**************************************************************************

   DeleteGroup()

**************************************************************************/

BOOL DeleteGroup(HWND hWnd)
{
LPITEMIDLIST   pidlPrograms,
               pidlFolder;
char           szPath[MAX_PATH];

//get the pidl for the programs group - this will be used to initialize the folder browser
SHGetSpecialFolderLocation(NULL, CSIDL_PROGRAMS, &pidlPrograms);

//get the group/folder to be deleted
if(!GetFolder(hWnd, &pidlFolder, pidlPrograms, szPath, "Select group to delete"))
   return FALSE;

//get the path for the chosen group/folder
SHGetPathFromIDList(pidlFolder, szPath);

//delete the group/folder
if(!DeleteFolder(hWnd, szPath))
   return FALSE;

return TRUE;
}

/**************************************************************************

   DeleteFolder()

**************************************************************************/

BOOL DeleteFolder(HWND hWnd, LPSTR lpszFolder)
{
char              szFile[MAX_PATH];
SHFILEOPSTRUCT    fos;
WIN32_FIND_DATA   FindData;
HANDLE            hFind;
BOOL              bFindFile = TRUE;

//we can't remove a directory that is not empty, so we need to empty this one

lstrcpy(szFile, lpszFolder);
lstrcat(szFile, "\\*.*");

ZeroMemory(&fos, sizeof(fos));
fos.hwnd = hWnd;
fos.wFunc = FO_DELETE;
fos.fFlags = FOF_SILENT | FOF_ALLOWUNDO;   //send to the recycle bin

hFind = FindFirstFile(szFile, &FindData);

while((INVALID_HANDLE_VALUE != hFind) && bFindFile)
   {
   if(*(FindData.cFileName) != '.')
      {
      //copy the path and file name to our temp buffer
      lstrcpy(szFile, lpszFolder);
      lstrcat(szFile, "\\");
      lstrcat(szFile, FindData.cFileName);
      //add a second NULL because SHFileOperation is looking for this
      lstrcat(szFile, "\0");

      //delete the file
      fos.pFrom = szFile;
      SHFileOperation(&fos);
      }

   //find the next file
   bFindFile = FindNextFile(hFind, &FindData);
   }

FindClose(hFind);   

return RemoveDirectory(lpszFolder);
}

