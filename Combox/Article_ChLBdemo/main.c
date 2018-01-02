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
#include "CheckedList.h"

#define HEIGHT(rect) (LONG)(rect.bottom - rect.top)
#define WIDTH(rect) (LONG)(rect.right - rect.left)
#define NELEMS(a)  (sizeof(a) / sizeof((a)[0]))
#define Refresh(hwnd) RedrawWindow((hwnd), NULL, NULL, \
    RDW_ERASE|RDW_INVALIDATE|RDW_UPDATENOW)

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
		case IDC_LIST:
		{
			switch(codeNotify)
			{
				case LBCN_ITEMCHECK:
					Static_SetText(GetDlgItem(hwnd,IDC_LBL),_T("ItemCheck"));
					break;
				case LBN_SELCHANGE:
					Static_SetText(GetDlgItem(hwnd,IDC_LBL),_T("SelectedIndexChanged"));
					break;
			}
		}
			break;
	}
}

BOOL Main_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	HWND hList = GetDlgItem(hwnd,IDC_LIST);

	CheckedListBox_SetFlatStyleChecks(hList, TRUE);
	
	ListBox_AddString(hList,_T("Ford"));
	ListBox_AddString(hList,_T("Toyota"));
	ListBox_AddString(hList,_T("Chevy"));
	ListBox_AddString(hList,_T("Volkswagon"));
	ListBox_AddString(hList,_T("Dodge"));
	ListBox_AddString(hList,_T("Honda"));
	ListBox_AddString(hList,_T("Plymouth"));
	ListBox_AddString(hList,_T("Mercedes"));
	ListBox_AddString(hList,_T("Hyundai"));
	ListBox_AddString(hList,_T("Zaparozhets"));
	ListBox_AddString(hList,_T("Volvo"));
	ListBox_AddString(hList,_T("Kia"));
	ListBox_AddString(hList,_T("BMW"));
	ListBox_AddString(hList,_T("Citroen"));

	return FALSE;
}

void Main_OnSize(HWND hwnd, UINT state, int cx, int cy)
{
    RECT rcOk = {0};
    GetWindowRect(GetDlgItem(hwnd,IDOK),&rcOk);

    RECT rcLb = {0};
    GetWindowRect(GetDlgItem(hwnd,IDC_LBL),&rcLb);

    MoveWindow(GetDlgItem(hwnd,IDC_LIST),0,0,
        cx, cy - (HEIGHT(rcOk) + 2),TRUE);
    MoveWindow(GetDlgItem(hwnd,IDOK), cx - WIDTH(rcOk),
        cy - HEIGHT(rcOk), WIDTH(rcOk),HEIGHT(rcOk),TRUE);

    //Refresh label
    MoveWindow(GetDlgItem(hwnd,IDC_LBL), 1,
        cy - HEIGHT(rcOk) + 1, cx - WIDTH(rcOk) - 4, HEIGHT(rcOk) - 2,TRUE);
    Refresh(GetDlgItem(hwnd,IDC_LBL)); //And label contents

}

/// @brief Set the colors used to paint controls in WM_CTLCOLORLISTBOX handler.
///
/// @param hdc Handle of a device context.
/// @param TxtColr Desired text color.
/// @param BkColr Desired back color.
///
/// @returns HBRUSH A reusable brush object.
HBRUSH SetColor(HDC hdc, COLORREF TxtColr, COLORREF BkColr)
{
    static HBRUSH ReUsableBrush;
	DeleteObject(ReUsableBrush);
    ReUsableBrush = CreateSolidBrush(BkColr);
    SetTextColor(hdc, TxtColr);
    SetBkColor(hdc, BkColr);
    return ReUsableBrush;
}

HBRUSH Main_OnCtlColorListbox(HWND hwnd, HDC hdc, HWND hwndChild, int type)
{
	return SetColor(hdc, GetSysColor(COLOR_BTNTEXT), GetSysColor(COLOR_BTNFACE));
}

BOOL CALLBACK Main_DlgProc (HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		HANDLE_DLGMSG (hwndDlg, WM_CLOSE, Main_OnClose);
		HANDLE_DLGMSG (hwndDlg, WM_COMMAND, Main_OnCommand);
		HANDLE_DLGMSG (hwndDlg, WM_INITDIALOG, Main_OnInitDialog);
		HANDLE_DLGMSG (hwndDlg, WM_SIZE, Main_OnSize);
		HANDLE_DLGMSG (hwndDlg, WM_CTLCOLORLISTBOX, Main_OnCtlColorListbox);

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

	InitCheckedListBox(hInstance);

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
