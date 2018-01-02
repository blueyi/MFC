#define STRICT

/**************************************************************************
   Include Files
**************************************************************************/

#include <windows.h>
#include <windowsx.h>
#include "globals.h"
#include "resource.h"

/**************************************************************************
   Local Function Prototypes
**************************************************************************/

DWORD DetermineVersion(void);
BOOL CALLBACK MainDlgProc(HWND, UINT, WPARAM, LPARAM);

/**************************************************************************
   Global Variables
**************************************************************************/

DWORD       g_dwPlatform;
HINSTANCE   g_hInstance = NULL;

/**************************************************************************

   WinMain()

**************************************************************************/

int PASCAL WinMain(  HINSTANCE hInstance, 
                     HINSTANCE hPrevInstance, 
                     LPSTR lpszCmdLine,
                     int nCmdShow)
{
//save our hInstance
g_hInstance = hInstance;

// Find out what OS we're running on in case we have to call any platform
// specific code.
g_dwPlatform = DetermineVersion();

//this will be needed later
CoInitialize(NULL);

//create the main dialog box
DialogBox(g_hInstance, MAKEINTRESOURCE(IDD_MAIN_DIALOG), NULL, MainDlgProc);

CoUninitialize();

return 0;
}

/**************************************************************************

   DetermineVersion()

**************************************************************************/

DWORD DetermineVersion(void)
{
OSVERSIONINFO os;

GetVersionEx(&os);
return (os.dwPlatformId);
}

/**************************************************************************

   ErrorHandlerEx()

**************************************************************************/

void ErrorHandlerEx( WORD wLine, LPSTR lpszFile )
{
    LPVOID lpvMessage;
    DWORD  dwError;
    TCHAR  szBuffer[256];

    // The the text of the error message
    dwError = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                            FORMAT_MESSAGE_FROM_SYSTEM, 
                            NULL, 
                            GetLastError(), 
                            MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), 
                            (LPTSTR)&lpvMessage, 
                            0, 
                            NULL);

    // Check to see if an error occured calling FormatMessage()
    if (0 == dwError)
    {
        wsprintf(szBuffer, TEXT("An error occured calling FormatMessage().")
                 TEXT("Error Code %d"), GetLastError());
        MessageBox(NULL, szBuffer, TEXT("Generic"), MB_ICONSTOP | 
                   MB_ICONEXCLAMATION);
        return;
    }

    // Display the error message
    wsprintf(szBuffer, TEXT("Generic, Line=%d, File=%s"), wLine, lpszFile);
    MessageBox(NULL, lpvMessage, szBuffer, MB_ICONEXCLAMATION | MB_OK);

    return;
}

/**************************************************************************

   MainDlgProc()

**************************************************************************/

BOOL CALLBACK MainDlgProc( HWND hWnd, 
                           UINT uMsg, 
                           WPARAM wParam, 
                           LPARAM lParam)
{
switch(uMsg)
   {
   case WM_INITDIALOG:
      return TRUE;

   case WM_COMMAND:
      switch (GET_WM_COMMAND_ID(wParam, lParam))
         {
         case IDC_ADD_GROUP:
            AddGroup(hWnd);
            break;
            
         case IDC_DEL_GROUP:
            DeleteGroup(hWnd);
            break;
         
         case IDC_ADD_ITEM:
            AddItem(hWnd);
            break;
            
         case IDC_DEL_ITEM:
            DeleteItem(hWnd);
            break;
         
         case IDOK:
            EndDialog(hWnd, 0);
            break;
         }
      return (TRUE);
   }
   
return (FALSE);
}
