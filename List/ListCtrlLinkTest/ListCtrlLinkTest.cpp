// ListCtrlLinkTest.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ListCtrlLinkTest.h"
#include "ListCtrlLinkTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListCtrlLinkTestApp

BEGIN_MESSAGE_MAP(CListCtrlLinkTestApp, CWinApp)
	//{{AFX_MSG_MAP(CListCtrlLinkTestApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlLinkTestApp construction

CListCtrlLinkTestApp::CListCtrlLinkTestApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CListCtrlLinkTestApp object

CListCtrlLinkTestApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CListCtrlLinkTestApp initialization

BOOL CListCtrlLinkTestApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	//warning C4996: 'CWinApp::Enable3dControls' was declared deprecated
	//Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CListCtrlLinkTestDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
