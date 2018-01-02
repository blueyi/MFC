#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <shlobj.h>


#ifdef __cplusplus
extern "C" {            // Assume C declarations for C++
#endif                  // __cplusplus


//////////////////////////////////////////////////////////////////////////////
// Constants and Enumerations



//////////////////////////////////////////////////////////////////////////////
// Global Variables

extern HINSTANCE g_hInstance;                                   // main.c
extern DWORD g_dwPlatformId;                                    // main.c

//////////////////////////////////////////////////////////////////////////////
// Prototypes

void ErrorHandlerEx(WORD, LPSTR);                                 // main.c
BOOL AddItem(HWND);                                               // AddItem.cpp
BOOL GetFolder(HWND, LPITEMIDLIST*, LPITEMIDLIST, LPSTR, LPCSTR); //AddItem.cpp
BOOL AddGroup(HWND);                                              // AddGroup.cpp
BOOL DeleteItem(HWND);                                            // DelItem.cpp
BOOL DeleteGroup(HWND);                                           // DelItem.cpp




//////////////////////////////////////////////////////////////////////////////
// Macros

#define ErrorHandler() ErrorHandlerEx(__LINE__, __FILE__)




#ifdef __cplusplus
}                       // Assume C declarations for C++
#endif                  // __cplusplus


#endif                  // __GLOBALS_H__
