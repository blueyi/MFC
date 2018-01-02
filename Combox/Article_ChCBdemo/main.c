#define UNICODE
#define _UNICODE

/****************************************************************************
 *                                                                          *
 * File    : main.c                                                         *
 *                                                                          *
 * Purpose : Generic dialog based Win32 application.                        *
 *                                                                          *
 * History : Date      Reason                                               *
 *           00/00/00  Created                                              *
 *                                                                          *
 ****************************************************************************/

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <tchar.h>
#include "main.h"
#include "CheckedCombo.h"

#define HEIGHT(rect) (LONG)(rect.bottom - rect.top)
#define WIDTH(rect) (LONG)(rect.right - rect.left)

#define NELEMS(a)  (sizeof(a) / sizeof((a)[0]))

/** Prototypes **************************************************************/

static LRESULT CALLBACK MainDlgProc(HWND, UINT, WPARAM, LPARAM);

/** Global variables ********************************************************/

static HANDLE ghInstance;

void Main_OnClose(HWND hwnd)
{
	EndDialog(hwnd, FALSE);
}

void Main_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch(id)
	{
		case IDOK:
		{
			EndDialog(hwnd, TRUE);
		}
			break;
	}
}

HBRUSH SetColor(HDC hdc, COLORREF TxtColr, COLORREF BkColr)
{
    static HBRUSH ReUsableBrush;
	DeleteObject(ReUsableBrush);
    ReUsableBrush = CreateSolidBrush(BkColr);
    SetTextColor(hdc, TxtColr);
    SetBkColor(hdc, BkColr);
    return ReUsableBrush;
}

LRESULT CALLBACK ComboColor_Proc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
        case WM_DESTROY: //Unsubclass the ComboBox
        {
			WNDPROC wp = (WNDPROC)GetProp(hwnd, _T("wprc"));
			if(NULL != wp)
			{
	            SetWindowLongPtr(hwnd, GWLP_WNDPROC, (DWORD) wp);
	            RemoveProp(hwnd, _T("wprc"));
	            return CallWindowProc(wp, hwnd, msg, wParam, lParam);
			}
        }
		case WM_CTLCOLORLISTBOX:
		case WM_CTLCOLOREDIT:
			return (LRESULT) SetColor((HDC)(wParam), GetSysColor(COLOR_BTNTEXT), RGB(255,255,191));

		default: return CallWindowProc((WNDPROC)GetProp(hwnd, _T("wprc")),
                            hwnd, msg, wParam, lParam);
	}
}

BOOL Main_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	HWND hCombo = GetDlgItem(hwnd,IDC_COMBO);

    //Subclass child and save the OldProc
    SetProp(hCombo, _T("wprc"), (HANDLE)GetWindowLongPtr(hCombo, GWLP_WNDPROC));
    SubclassWindow(hCombo, ComboColor_Proc);

	CheckedComboBox_SetFlatStyleChecks(hCombo, TRUE);
	
	ComboBox_AddString(hCombo,_T("Red"));
	ComboBox_AddString(hCombo,_T("Green"));
	ComboBox_AddString(hCombo,_T("Blue"));
	ComboBox_AddString(hCombo,_T("Black"));
	ComboBox_AddString(hCombo,_T("White"));
	ComboBox_AddString(hCombo,_T("Yellow"));
	ComboBox_AddString(hCombo,_T("Brown"));

	

	return FALSE;
}

void Main_OnSize(HWND hwnd, UINT state, int cx, int cy)
{
    RECT rcOk = {0};
    GetWindowRect(GetDlgItem(hwnd,IDOK),&rcOk);
	MapWindowPoints(HWND_DESKTOP, hwnd, (LPPOINT) & rcOk.left, 2);

    RECT rcCB = {0};
    GetWindowRect(GetDlgItem(hwnd,IDC_COMBO),&rcCB);
	MapWindowPoints(HWND_DESKTOP, hwnd, (LPPOINT) & rcCB.left, 2);

    MoveWindow(GetDlgItem(hwnd,IDC_COMBO),rcCB.left,rcCB.top,
        cx - (WIDTH(rcOk) + 10), cy, TRUE);

    MoveWindow(GetDlgItem(hwnd,IDOK), cx - WIDTH(rcOk),
        rcOk.top, WIDTH(rcOk),HEIGHT(rcOk),TRUE);
}

BOOL CALLBACK Main_DlgProc (HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		HANDLE_DLGMSG (hwndDlg, WM_CLOSE, Main_OnClose);
		HANDLE_DLGMSG (hwndDlg, WM_COMMAND, Main_OnCommand);
		HANDLE_DLGMSG (hwndDlg, WM_INITDIALOG, Main_OnInitDialog);
		HANDLE_DLGMSG (hwndDlg, WM_SIZE, Main_OnSize);
		default: return FALSE;
	}
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    INITCOMMONCONTROLSEX icc;
    WNDCLASSEX wcx;

    ghInstance = hInstance;

    icc.dwSize = sizeof(icc);
    icc.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&icc);

	InitCheckedComboBox(hInstance);

    /* Get system dialog information */
    wcx.cbSize = sizeof(wcx);
    if (!GetClassInfoEx(NULL, MAKEINTRESOURCE(32770), &wcx))
        return 0;

    /* Add our own stuff */
    wcx.hInstance = hInstance;
    wcx.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDR_ICO_MAIN));
    wcx.lpszClassName = _T("CheckedCClass");
    if (!RegisterClassEx(&wcx))
        return 0;

    /* The user interface is a modal dialog box */
    return DialogBox(hInstance, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)Main_DlgProc);
}
