// XScrollBarTest.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "XScrollBarTest.h"
#include "XScrollBarTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXScrollBarTestApp

BEGIN_MESSAGE_MAP(CXScrollBarTestApp, CWinApp)
	//{{AFX_MSG_MAP(CXScrollBarTestApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXScrollBarTestApp construction

CXScrollBarTestApp::CXScrollBarTestApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CXScrollBarTestApp object

CXScrollBarTestApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CXScrollBarTestApp initialization

BOOL CXScrollBarTestApp::InitInstance()
{
#if _MFC_VER < 0x700
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif

	CXScrollBarTestDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return FALSE;
}
