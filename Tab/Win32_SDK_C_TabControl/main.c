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

/* 
 * Either define WIN32_LEAN_AND_MEAN, or one or more of NOCRYPT,
 * NOSERVICE, NOMCX and NOIME, to decrease compile time (if you
 * don't need these defines -- see windows.h).
 */

#define WIN32_LEAN_AND_MEAN
/* #define NOCRYPT */
/* #define NOSERVICE */
/* #define NOMCX */
/* #define NOIME */

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <tchar.h>
#include <stdio.h>
#include "resource.h"
#include "TabCtrl.h"


/** Macroes *****************************************************************/

#define Refresh(A) RedrawWindow(A,NULL,NULL,RDW_ERASE|RDW_INVALIDATE|RDW_ALLCHILDREN|RDW_UPDATENOW);

/** Global variables ********************************************************/

static HANDLE ghInstance;
static SIZE gMinSize;

static TABCTRL TabCtrl_1, TabCtrl_2;

/** Prototypes **************************************************************/

BOOL CALLBACK FormMain_DlgProc (HWND, UINT, WPARAM, LPARAM);

/** Global handles **********************************************************/

static HWND		frmMain;
static HMENU 	mnuMain;

static void InitHandles (HWND hwndParent)
{
	static BOOL initialized=FALSE;
	if(!initialized)
	{
		if (frmMain != hwndParent)
			frmMain = hwndParent;

		//Get a handle to the Menu Bar
		if (mnuMain != GetMenu(hwndParent))
			mnuMain = GetMenu(hwndParent);

		initialized=TRUE;
	}
}

/****************************************************************************
 *                                                                          *
 * Function: DoEvents					                                    *
 *                                                                          *
 * Purpose: DoEvents is a statement that yields execution of the current	*
 * thread so that the operating system can process other events.			*
 * This function cleans out the message loop and executes any other pending	*
 * business.																*
 *																			*
 ****************************************************************************/

void DoEvents (void)
{
	MSG Msg;
	while (PeekMessage(&Msg,NULL,0,0,PM_REMOVE))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
}

/****************************************************************************
 *                                                                          *
 * Function: GetVersionInfo                                                 *
 *                                                                          *
 * Purpose : Returns the Info associated with a version info entry string.  *
 *                                                                          *
 * History : Date      Reason                                               *
 *           00/00/00  Adapted from luetz                                   *
 *					   www.codeproject.com/cpp/GetLocalVersionInfos.asp		*
 *                                                                          *
 * Usage : GetVersionInfo(FieldDescriptionString)                           *
 *                                                                          *
 *		   Where FieldDescriptionString = "Comments"						*
 *										  "CompanyName"						*
 *										  "FileDescription"					*
 *										  "InternalName"					*
 *										  "LegalCopyright"					*
 *										  "LegalTrademarks"					*
 *										  "OriginalFilename"				*
 *										  "PrivateBuild"					*
 *										  "ProductName"						*
 *										  "ProductVersion"					*
 *										  "SpecialBuild"					*
 *                                                                          *
 ****************************************************************************/

LPSTR GetVersionInfo(LPSTR csEntry)
{
	LPSTR csRet;
	static char errStr[MAX_PATH];

	HRSRC hVersion = FindResource(GetModuleHandle(NULL), 
	MAKEINTRESOURCE(VS_VERSION_INFO), RT_VERSION );
	if (hVersion!=NULL)
	{
		HGLOBAL hGlobal = LoadResource(GetModuleHandle(NULL), hVersion );
 
		if (hGlobal!=NULL)  
		{  
			LPVOID versionInfo=LockResource(hGlobal);
  
			if (versionInfo!=NULL)
			{
				DWORD vLen,langD;
				BOOL retVal;    
				LPVOID retbuf=NULL;
				static char fileEntry[256];

				sprintf(fileEntry,"\\VarFileInfo\\Translation");
				retVal = VerQueryValue(versionInfo,fileEntry,&retbuf,(UINT *)&vLen);
				if (retVal && vLen==4) 
				{
					memcpy(&langD,retbuf,4);            
					sprintf(fileEntry, "\\StringFileInfo\\%02X%02X%02X%02X\\%s",
					(langD & 0xff00)>>8,langD & 0xff,(langD & 0xff000000)>>24, 
					(langD & 0xff0000)>>16, csEntry);            
				}
				else
				{ 
				sprintf(fileEntry, "\\StringFileInfo\\%04X04B0\\%s", 
				GetUserDefaultLangID(), csEntry);
				}
				if (retVal==VerQueryValue(versionInfo,fileEntry,&retbuf,(UINT *)&vLen))
				{ 
					csRet=(char*)retbuf;
				}
				else
				{
					sprintf(errStr,"%s Not Available",csEntry);
					csRet = errStr;
				}
			}
		}
		UnlockResource(hGlobal);  
		FreeResource(hGlobal);  
	}
	return csRet;
}

static BOOL FormMain_OnNotify(HWND hwnd, INT id, LPNMHDR pnm)
{
    switch(id)
	{
		case TAB_CONTROL_1:
			return TabCtrl_1.Notify(pnm);

		case TAB_CONTROL_2:
			return TabCtrl_2.Notify(pnm);

		//
		// TODO: Add other control id case statements here. . .
		//
	}
	return FALSE;
}

void FormMain_OnClose(HWND hwnd)
{
	PostQuitMessage(0);// turn off message loop
	TabControl_Destroy(&TabCtrl_1);
	TabControl_Destroy(&TabCtrl_2);
	EndDialog(hwnd, 0);
}

/****************************************************************************
 *                                                                          *
 * Functions: FormMain_OnCommand related event code                         *
 *                                                                          *
 * Purpose : Handle WM_COMMAND messages: this is the heart of the app.		*
 *                                                                          *
 * History : Date      Reason                                               *
 *           00/00/00  Created                                              *
 *                                                                          *
 ****************************************************************************/
void mnuAbout_Click (HWND hwnd)
{
	char buf[MAX_PATH];
	sprintf(buf,"Version = %s\n",GetVersionInfo("ProductVersion"));

	MessageBox (hwnd,buf,GetVersionInfo("ProductName"),MB_OK);
}

void cmdClick1_Click (HWND hwnd)
{
	MessageBox(hwnd, "Command 1 Clicked",
					"Info", MB_OK | MB_ICONERROR | MB_TOPMOST);
}

void cmdClick2_Click (HWND hwnd)
{
	MessageBox(hwnd, "Command 2 Clicked",
					"Info", MB_OK | MB_ICONERROR | MB_TOPMOST);
}

void cmdClick3_Click (HWND hwnd)
{
	MessageBox(hwnd, "Command 3 Clicked",
					"Info", MB_OK | MB_ICONERROR | MB_TOPMOST);
}

void cmdClick4_Click (HWND hwnd)
{
	Static_SetText(GetDlgItem(hwnd,LBL_1),"Command 4 Clicked");
}

void cmdClick5_Click (HWND hwnd)
{
	Static_SetText(GetDlgItem(hwnd,LBL_1),"Command 5 Clicked");
}

void cmdClick6_Click (HWND hwnd)
{
	Static_SetText(GetDlgItem(hwnd,LBL_2),"Command 6 Clicked");
}

void cmdClick7_Click (HWND hwnd)
{
	Static_SetText(GetDlgItem(hwnd,LBL_2),"Command 7 Clicked");
}

void cmdClick8_Click (HWND hwnd)
{
	MessageBox(hwnd, "Command 8 Clicked",
					"Info", MB_OK | MB_ICONERROR | MB_TOPMOST);
}

void cmdClick9_Click (HWND hwnd)
{
	MessageBox(hwnd, "Command 9 Clicked",
					"Info", MB_OK | MB_ICONERROR | MB_TOPMOST);
}

void FormMain_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
		case MNU_ABOUT:
			mnuAbout_Click (hwnd);
		break;

		case MNU_QUIT:
			FormMain_OnClose (hwnd);
		break;

		case CMD_CLICK_1:
			cmdClick1_Click (hwnd);
		break;

		case CMD_CLICK_2:
			cmdClick2_Click (hwnd);
		break;

		case CMD_CLICK_3:
			cmdClick2_Click (hwnd);
		break;

		case CMD_CLICK_4:
			cmdClick4_Click (hwnd);
		break;

		case CMD_CLICK_5:
			cmdClick5_Click (hwnd);
		break;

		case CMD_CLICK_6:
			cmdClick6_Click (hwnd);
		break;

		case CMD_CLICK_7:
			cmdClick7_Click (hwnd);
		break;

		case CMD_CLICK_8:
			cmdClick8_Click (hwnd);
		break;

		case CMD_CLICK_9:
			cmdClick9_Click (hwnd);
		break;

		default: break;
	}
}

void FormMain_OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	RECT  rc;
   	GetClientRect(hwnd,&rc);

	MoveWindow(TabCtrl_1.hTab,0,0,(rc.right - rc.left)/2-4,rc.bottom - rc.top,FALSE);
	for(int i=0;i<TabCtrl_1.tabPageCount;i++)
		TabCtrl_1.StretchTabPage(TabCtrl_1.hTab,i);

	MoveWindow(TabCtrl_2.hTab,(rc.right - rc.left)/2,0,(rc.right - rc.left)/2-4,rc.bottom - rc.top,FALSE);
	for(int i=0;i<TabCtrl_2.tabPageCount;i++)
		TabCtrl_2.CenterTabPage(TabCtrl_2.hTab,i);

	Refresh(hwnd);
}

void TabCtrl1_TabPages_OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	/////////////////////////////////////////////////////
	// Sizeing and positioning of Tab Page Widgets shall
	// be handled here so that they remain consistent with
	// the tab page.
	// Remember that the hwnd changes with each successive tab page

	RECT  rc, chRc;
	int h, w;
	GetClientRect(hwnd, &rc);

	if(hwnd==TabCtrl_1.hTabPages[0])
	{
		GetWindowRect(GetDlgItem(hwnd,CMD_CLICK_1),&chRc);
		h=chRc.bottom-chRc.top;
		w=chRc.right-chRc.left;
		MoveWindow(GetDlgItem(hwnd,CMD_CLICK_1),rc.left+(rc.right-rc.left-w)/2,rc.top+(rc.bottom-rc.top)/4-h/2,chRc.right - chRc.left,chRc.bottom - chRc.top,FALSE);

		GetWindowRect(GetDlgItem(hwnd,CMD_CLICK_2),&chRc);
		h=chRc.bottom-chRc.top;
		w=chRc.right-chRc.left;
		MoveWindow(GetDlgItem(hwnd,CMD_CLICK_2),rc.left+(rc.right-rc.left-w)/2,rc.top+(rc.bottom-rc.top)/2-h/2,chRc.right - chRc.left,chRc.bottom - chRc.top,FALSE);

		GetWindowRect(GetDlgItem(hwnd,CMD_CLICK_3),&chRc);
		h=chRc.bottom-chRc.top;
		w=chRc.right-chRc.left;
		MoveWindow(GetDlgItem(hwnd,CMD_CLICK_3),rc.left+(rc.right-rc.left-w)/2,rc.top+(rc.bottom-rc.top)/4*3-h/2,chRc.right - chRc.left,chRc.bottom - chRc.top,FALSE);
	}
	else if(hwnd==TabCtrl_1.hTabPages[1])
	{
		MoveWindow(GetDlgItem(hwnd,FRA_TAB_PAGE_2),4,0,rc.right - rc.left-4,rc.bottom - rc.top,FALSE);

		GetWindowRect(GetDlgItem(hwnd,CMD_CLICK_4),&chRc);
		h=chRc.bottom-chRc.top;
		w=chRc.right-chRc.left;
		MoveWindow(GetDlgItem(hwnd,CMD_CLICK_4),rc.left+(rc.right-rc.left-w)/3*2,rc.top+(rc.bottom-rc.top)/4-h/2,chRc.right - chRc.left,chRc.bottom - chRc.top,FALSE);

		GetWindowRect(GetDlgItem(hwnd,LBL_1),&chRc);
		h=chRc.bottom-chRc.top;
		w=chRc.right-chRc.left;
		MoveWindow(GetDlgItem(hwnd,LBL_1),rc.left+(rc.right-rc.left-w)/2,rc.top+(rc.bottom-rc.top)/2-h/2,chRc.right - chRc.left,chRc.bottom - chRc.top,FALSE);

		GetWindowRect(GetDlgItem(hwnd,CMD_CLICK_5),&chRc);
		h=chRc.bottom-chRc.top;
		w=chRc.right-chRc.left;
		MoveWindow(GetDlgItem(hwnd,CMD_CLICK_5),rc.left+(rc.right-rc.left-w)/3,rc.top+(rc.bottom-rc.top)/4*3-h/2,chRc.right - chRc.left,chRc.bottom - chRc.top,FALSE);
	}
	else if(hwnd==TabCtrl_1.hTabPages[2])
	{
		MoveWindow(GetDlgItem(hwnd,FRA_TAB_PAGE_3),4,0,rc.right - rc.left-4,rc.bottom - rc.top,FALSE);

		GetWindowRect(GetDlgItem(hwnd,CMD_CLICK_6),&chRc);
		h=chRc.bottom-chRc.top;
		w=chRc.right-chRc.left;
		MoveWindow(GetDlgItem(hwnd,CMD_CLICK_6),rc.left+(rc.right-rc.left-w)/3,rc.top+(rc.bottom-rc.top)/4-h/2,chRc.right - chRc.left,chRc.bottom - chRc.top,FALSE);

		GetWindowRect(GetDlgItem(hwnd,LBL_2),&chRc);
		h=chRc.bottom-chRc.top;
		w=chRc.right-chRc.left;
		MoveWindow(GetDlgItem(hwnd,LBL_2),rc.left+(rc.right-rc.left-w)/2,rc.top+(rc.bottom-rc.top)/2-h/2,chRc.right - chRc.left,chRc.bottom - chRc.top,FALSE);

		GetWindowRect(GetDlgItem(hwnd,CMD_CLICK_7),&chRc);
		h=chRc.bottom-chRc.top;
		w=chRc.right-chRc.left;
		MoveWindow(GetDlgItem(hwnd,CMD_CLICK_7),rc.left+(rc.right-rc.left-w)/3*2,rc.top+(rc.bottom-rc.top)/4*3-h/2,chRc.right - chRc.left,chRc.bottom - chRc.top,FALSE);
	}
	else //hwnd==TabCtrl_1.hTabPages[3]
	{
		MoveWindow(GetDlgItem(hwnd,FRA_TAB_PAGE_4),4,0,rc.right - rc.left-4,rc.bottom - rc.top,FALSE);
	}
}

void TabCtrl2_TabPages_OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	/////////////////////////////////////////////////////
	// Sizeing and positioning of Tab Page Widgets shall
	// be handled here so that they remain consistent with
	// the tab page.
	// Remember that the hwnd changes with each successive tab page

	RECT  rc, chRc;
	int h, w;
	GetClientRect(hwnd, &rc);

	if(hwnd==TabCtrl_2.hTabPages[0])
	{
		MoveWindow(GetDlgItem(hwnd,FRA_TAB_PAGE_5),4,0,rc.right - rc.left-4,rc.bottom - rc.top,FALSE);
	}
	else if(hwnd==TabCtrl_2.hTabPages[1])
	{
		MoveWindow(GetDlgItem(hwnd,FRA_TAB_PAGE_6),4,0,rc.right - rc.left-4,rc.bottom - rc.top,FALSE);

		GetWindowRect(GetDlgItem(hwnd,CMD_CLICK_8),&chRc);
		h=chRc.bottom-chRc.top;
		w=chRc.right-chRc.left;
		MoveWindow(GetDlgItem(hwnd,CMD_CLICK_8),rc.left+(rc.right-rc.left-w)/2,rc.top+(rc.bottom-rc.top)/4-h/2,chRc.right - chRc.left,chRc.bottom - chRc.top,FALSE);

		GetWindowRect(GetDlgItem(hwnd,CMD_CLICK_9),&chRc);
		h=chRc.bottom-chRc.top;
		w=chRc.right-chRc.left;
		MoveWindow(GetDlgItem(hwnd,CMD_CLICK_9),rc.left+(rc.right-rc.left-w)/2,rc.top+(rc.bottom-rc.top)/4*3-h/2,chRc.right - chRc.left,chRc.bottom - chRc.top,FALSE);
	}
	else if(hwnd==TabCtrl_2.hTabPages[2])
	{
		MoveWindow(GetDlgItem(hwnd,FRA_TAB_PAGE_7),4,0,rc.right - rc.left-4,rc.bottom - rc.top,FALSE);
	}
	else //hwnd==TabCtrl_2.hTabPages[3]
	{
		MoveWindow(GetDlgItem(hwnd,FRA_TAB_PAGE_8),4,0,rc.right - rc.left-4,rc.bottom - rc.top,FALSE);
	}
}

BOOL FormMain_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	InitHandles (hwnd); // this line must be first!

	//----This section must be second----//

	static LPSTR tabnames[]= {"Tab Page 1", "Tab Page 2", "Tab Page 3", "Tab Page 4", 0};
	static LPSTR dlgnames[]= {MAKEINTRESOURCE(TAB_CONTROL_1_PAGE_1),
						  	  MAKEINTRESOURCE(TAB_CONTROL_1_PAGE_2),
						  	  MAKEINTRESOURCE(TAB_CONTROL_1_PAGE_3),
						  	  MAKEINTRESOURCE(TAB_CONTROL_1_PAGE_4),0};

	New_TabControl( &TabCtrl_1, // address of TabControl struct
					GetDlgItem(hwnd, TAB_CONTROL_1), // handle to tab control
					tabnames, // text for each tab
					dlgnames, // dialog id's of each tab page dialog
					&FormMain_DlgProc, //parent dialog proc
					&TabCtrl1_TabPages_OnSize, // optional address of size function or NULL
					TRUE); // stretch tab page to fit tab ctrl

	static LPSTR tab2names[]= {"Page 1", "Page 2", "Page 3", "Page 4", 0};
	static LPSTR dlg2names[]= {MAKEINTRESOURCE(TAB_CONTROL_2_PAGE_1),
							   MAKEINTRESOURCE(TAB_CONTROL_2_PAGE_2),
							   MAKEINTRESOURCE(TAB_CONTROL_2_PAGE_3),
							   MAKEINTRESOURCE(TAB_CONTROL_2_PAGE_4),0};

	New_TabControl( &TabCtrl_2,
					GetDlgItem(hwnd, TAB_CONTROL_2),
					tab2names,
					dlg2names,
					&FormMain_DlgProc,
					&TabCtrl2_TabPages_OnSize,
					TRUE);

	Edit_SetText(GetDlgItem(TabCtrl_2.hTabPages[0],LBL_3),
		"Use the Tab key to navagate between\r\ntab controls.\r\n\r\n"
		"Use the arrow keys or PageUp/Down keys\r\nto select a tab.\r\n\r\n"
		"Use the arrow keys to enter a tab page.\r\n\r\n"
		"Use the Tab key or arrow keys to navagate\r\ntab page child commands.\r\n\r\n"
		"Use Enter key to execute selected command.\r\n\r\n"
		"Try resizing the dialog while looking\r\nat different tabs.");

	//----Everything else must follow the above----//

	//Get the initial Width and height of the dialog
	//in order to fix the minimum size of dialog
	RECT rc;
	GetWindowRect(hwnd,&rc);
	gMinSize.cx = (rc.right - rc.left);
	gMinSize.cy = (rc.bottom - rc.top);

	return 0;
}

void FormMain_OnGetMinMaxInfo(HWND hwnd, LPMINMAXINFO lpMinMaxInfo)
{
    lpMinMaxInfo->ptMinTrackSize.x = gMinSize.cx; //<-- Min. width (in pixels) of your window
    lpMinMaxInfo->ptMinTrackSize.y = gMinSize.cy; //<-- Min. height (in pixels) of your window

/*  lpMinMaxInfo->ptMaxTrackSize.x = 640; //<-- Max. width (in pixels) of your window
    lpMinMaxInfo->ptMaxTrackSize.y = 480; //<-- Max. height (in pixels) of your window
    lpMinMaxInfo->ptMaxPosition.x = 0;    //<-- Left position (in pixels) of your window when maximized
    lpMinMaxInfo->ptMaxPosition.y = 0;    //<-- Top position (in pixels) of your window when maximized
 */
}

/****************************************************************************
 *                                                                          *
 * Function: MainDlgProc                                                    *
 *                                                                          *
 * Purpose : Process messages for the Main dialog.                          *
 *                                                                          *
 * History : Date      Reason                                               *
 *           00/00/00  Created                                              *
 *                                                                          *
 ****************************************************************************/

BOOL CALLBACK FormMain_DlgProc (HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		HANDLE_MSG (hwndDlg, WM_CLOSE, FormMain_OnClose);
		HANDLE_MSG (hwndDlg, WM_COMMAND, FormMain_OnCommand);
		HANDLE_MSG (hwndDlg, WM_INITDIALOG, FormMain_OnInitDialog);
		HANDLE_MSG (hwndDlg, WM_SIZE, FormMain_OnSize);
		HANDLE_MSG (hwndDlg, WM_GETMINMAXINFO, FormMain_OnGetMinMaxInfo);
		HANDLE_MSG (hwndDlg, WM_NOTIFY, FormMain_OnNotify);
		//// TODO: Add dialog message crackers here...

	default: return FALSE;
	}
}

/****************************************************************************
 *                                                                          *
 * Function: WinMain                                                        *
 *                                                                          *
 * Purpose : Initialize the application.  Register a window class,          *
 *           create and display the main window and enter the               *
 *           message loop.                                                  *
 *                                                                          *
 * History : Date      Reason                                               *
 *           00/00/00  Created                                              *
 *                                                                          *
 ****************************************************************************/

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    WNDCLASSEX wcx;
    
    ghInstance = hInstance;

    // Initialize common controls. Also needed for MANIFEST's.
    InitCommonControls();

    // Load Rich Edit control support.
    // TODO: uncomment one of the lines below, if you are using a Rich Edit control.
    // LoadLibrary(_T("riched32.dll"));  // Rich Edit v1.0
    // LoadLibrary(_T("riched20.dll"));  // Rich Edit v2.0, v3.0

    // Get system dialog information.
    wcx.cbSize = sizeof(wcx);
    if (!GetClassInfoEx(NULL, MAKEINTRESOURCE(32770), &wcx))
        return 0;

    // Add our own stuff.
    wcx.hInstance = hInstance;
    wcx.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDR_ICO_MAIN));
    wcx.lpszClassName = _T("TabCtrlDmoClass");
    if (!RegisterClassEx(&wcx))
        return 0;

    // The user interface is a modal dialog box.
    return DialogBox(hInstance, MAKEINTRESOURCE(FRM_MAIN), NULL, (DLGPROC)FormMain_DlgProc);
}

