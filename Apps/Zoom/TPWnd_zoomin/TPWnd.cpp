// TPWnd.cpp : Defines the class behaviors for the application.
// Download by http://www.codefans.net

#include "stdafx.h"
#include "TPWnd.h"
#include "TPWndDlg.h"

#include "XTPWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTPWndApp

BEGIN_MESSAGE_MAP(CTPWndApp, CWinApp)
	//{{AFX_MSG_MAP(CTPWndApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPWndApp construction

CTPWndApp::CTPWndApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTPWndApp object

CTPWndApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTPWndApp initialization

BOOL CTPWndApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	SetDialogBkColor(RGB(255, 255, 255), RGB(0, 0, 0));
	//建立透明窗体
	CXTPWnd *pWnd = new CXTPWnd;
	m_pMainWnd = pWnd;
	if (!pWnd->m_zoom)
	{
		return FALSE;
	}
	pWnd->XCreate();
	return TRUE;

	//...
	CTPWndDlg dlg;
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
