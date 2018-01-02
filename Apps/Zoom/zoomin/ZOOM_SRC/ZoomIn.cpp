// ZoomIn.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "ZoomIn.h"
#include "TrayWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZoomInApp

BEGIN_MESSAGE_MAP(CZoomInApp, CWinApp)
	//{{AFX_MSG_MAP(CZoomInApp)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_HELP, OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// The one and only CZoomInApp object

CZoomInApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CZoomInApp initialization

BOOL CZoomInApp::InitInstance()
{
	CString strWindowName;
	strWindowName.LoadString(IDS_HIDEWINDOW);
	HWND hwndPrevious = FindWindow(NULL, strWindowName);
	if (hwndPrevious)
	{
        SetForegroundWindow(hwndPrevious);
		PostMessage(hwndPrevious, WM_COMMAND, ID_TRAY_CHANGESETTINGS, 0);
        return FALSE;
	}

	// Place the INI file in the current directory to
	// make cleanup much simpler.

	CString strPath;
	GetModuleFileName(AfxGetInstanceHandle(),
		strPath.GetBuffer(_MAX_PATH), _MAX_PATH);
	strPath.ReleaseBuffer();

	int nIndex = strPath.Find(_T(".exe"));
	if (nIndex != -1)
	{
		strPath = strPath.Left(nIndex) + _T(".ini");
		free((void*)m_pszProfileName);
		m_pszProfileName = _tcsdup(strPath);	
	}

	// Create the frame window, but make it hidden from view

	CTrayWnd* pTrayWnd = new CTrayWnd;
	if (!pTrayWnd->LoadFrame(IDR_MENU))
		return FALSE;
	pTrayWnd->ShowWindow(SW_HIDE);
	pTrayWnd->UpdateWindow();
	m_pMainWnd = pTrayWnd;

	return TRUE;
}

void CZoomInApp::OnHelp()
{
	// Do nothing here because context-sensitive help
	//  is handled in MainSheet.cpp
}