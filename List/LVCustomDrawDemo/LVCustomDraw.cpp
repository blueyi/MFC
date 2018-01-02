// LVCustomDraw.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "LVCustomDraw.h"
#include "wizard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLVCustomDrawApp

BEGIN_MESSAGE_MAP(CLVCustomDrawApp, CWinApp)
	//{{AFX_MSG_MAP(CLVCustomDrawApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLVCustomDrawApp construction

CLVCustomDrawApp::CLVCustomDrawApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CLVCustomDrawApp object

CLVCustomDrawApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CLVCustomDrawApp initialization

BOOL CLVCustomDrawApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	CWizard dlg ( _T("") );
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


/////////////////////////////////////////////////////////////////////////////
// Global functions

void FillListCtrl ( CListCtrl& list )
{
    list.InsertColumn ( 0, _T("Un"), LVCFMT_LEFT, -1, 0 );
    list.InsertColumn ( 1, _T("Deux"), LVCFMT_LEFT, -1, 1 );
    list.InsertColumn ( 2, _T("Trois"), LVCFMT_LEFT, -1, 2 );

    list.InsertItem ( 0, _T("Stan") );
    list.SetItemText ( 0, 1, _T("Kyle") );
    list.SetItemText ( 0, 2, _T("Cartman") );

    list.InsertItem ( 1, _T("Wendy") );
    list.SetItemText ( 1, 1, _T("Mr. Hat") );
    list.SetItemText ( 1, 2, _T("Miss Ellen") );

    list.InsertItem ( 2, _T("Kenny") );
    list.SetItemText ( 2, 1, _T("Officer Barbrady") );
    list.SetItemText ( 2, 2, _T("Chef") );

    list.InsertItem ( 3, _T("Damien") );
    list.SetItemText ( 3, 1, _T("Santa") );
    list.SetItemText ( 3, 2, _T("Frosty") );

    list.InsertItem ( 4, _T("Brian Boitano") );
    list.SetItemText ( 4, 1, _T("Mr. Garrison") );
    list.SetItemText ( 4, 2, _T("Brett Favre") );

    list.InsertItem ( 5, _T("Trey") );
    list.SetItemText ( 5, 1, _T("Matt") );
    list.SetItemText ( 5, 2, _T("BASEketball") );

    list.SetColumnWidth ( 0, LVSCW_AUTOSIZE_USEHEADER );
    list.SetColumnWidth ( 1, LVSCW_AUTOSIZE_USEHEADER );
    list.SetColumnWidth ( 2, LVSCW_AUTOSIZE_USEHEADER );
}
