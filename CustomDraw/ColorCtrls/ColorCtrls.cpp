// ColorCtrls.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ColorCtrls.h"
#include "ColorCtrlsDlg.h"
#include "RGB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorCtrlsApp

BEGIN_MESSAGE_MAP(CColorCtrlsApp, CWinApp)
	//{{AFX_MSG_MAP(CColorCtrlsApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorCtrlsApp construction

CColorCtrlsApp::CColorCtrlsApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CColorCtrlsApp object

CColorCtrlsApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CColorCtrlsApp initialization

BOOL CColorCtrlsApp::InitInstance()
{
//	SetDialogBkColor(RGB_BLACK, RGB_WHITE);
        
        AfxEnableControlContainer();

	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CColorCtrlsDlg dlg;
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
