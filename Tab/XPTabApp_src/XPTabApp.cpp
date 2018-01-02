/////////////////////////////////////////////////////////////////////////////
// XPTabApp.cpp : Defines the class behaviors for the application.
/////////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "XPTabApp.h"

#include "Resource.h"
#include "XPTabDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXPTabApp
BEGIN_MESSAGE_MAP(CXPTabApp, CWinApp)
	//{{AFX_MSG_MAP(CXPTabApp)
	//}}AFX_MSG
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// The one and only CXPTabApp object
CXPTabApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CXPTabApp initialization

BOOL CXPTabApp::InitInstance()
{
	// Standard initialization
	Enable3dControls();			// Call this when using MFC in a shared DLL
	
	// Optional: init registry for this application
	free((void*)m_pszProfileName);
	CString sProfileName="XPTabApp";
	m_pszProfileName=strdup(sProfileName);
	SetRegistryKey(_T("Samples"));

	CXPTabDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////
