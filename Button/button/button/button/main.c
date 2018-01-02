/* File main.c
 * (application code)
 */

#include <tchar.h>
#include <windows.h>
#include <commctrl.h>

#include "resource.h"
#include "custom.h"


static INT_PTR CALLBACK
MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg) {
        case WM_COMMAND:
            switch(wParam) {
                case ID_REAL:   MessageBox(hDlg, _T("Clicked the real button."), _T("Click!"), MB_OK); break;
                case ID_CUSTOM: MessageBox(hDlg, _T("Clicked the custom control."), _T("Click!"), MB_OK); break;
            }
            break;

        case WM_CLOSE:
            PostQuitMessage(0);
            break;

        default:
            return FALSE;
    }

    return TRUE;
}

int APIENTRY
_tWinMain(HINSTANCE hInst, HINSTANCE hInstPrev, TCHAR* lpszCmdLine, int iCmdShow)
{
    MSG msg;
    HWND hDlg;

    // Make sure linker does not omit COMCTL32.DLL:
    InitCommonControls();

    // Register the custom control class:
    CustomRegister();

    hDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_MAIN), NULL, MainDlgProc);

    ShowWindow(hDlg, iCmdShow);

    while(GetMessage(&msg, NULL, 0, 0)) {
        if(IsDialogMessage(hDlg, &msg))
            continue;

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}
