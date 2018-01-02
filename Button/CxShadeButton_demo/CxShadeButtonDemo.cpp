// CxShadeButtonDemo.cpp : Defines the class behaviors for the application.
//
#include "stdafx.h"
#include "CxShadeButtonDemo.h"
#include "CxShadeButtonDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCxShadeButtonDemoApp
BEGIN_MESSAGE_MAP(CCxShadeButtonDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CCxShadeButtonDemoApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CCxShadeButtonDemoApp construction
CCxShadeButtonDemoApp::CCxShadeButtonDemoApp()
{}
/////////////////////////////////////////////////////////////////////////////
// The one and only CCxShadeButtonDemoApp object
CCxShadeButtonDemoApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CCxShadeButtonDemoApp initialization
BOOL CCxShadeButtonDemoApp::InitInstance()
{
	AfxEnableControlContainer();
	// Standard initialization
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CCxShadeButtonDemoDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
