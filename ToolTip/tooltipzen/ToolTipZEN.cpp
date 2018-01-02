// ToolTipZEN.cpp : Defines the class behaviors for the application.
//
/*
Author:     Zarembo Maxim
Country:    Belarus
City:       Minsk
e-mail:     mzarembo@iba.by
WWW:        http://maxim.z.tripod.com/ 
ICQ:        64569598
*/

#include "stdafx.h"
#include "ToolTipZEN.h"
#include "ToolTipZENDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolTipZENApp

BEGIN_MESSAGE_MAP(CToolTipZENApp, CWinApp)
	//{{AFX_MSG_MAP(CToolTipZENApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolTipZENApp construction

CToolTipZENApp::CToolTipZENApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CToolTipZENApp object

CToolTipZENApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CToolTipZENApp initialization

BOOL CToolTipZENApp::InitInstance()
{
	// Standard initialization

	CToolTipZENDlg dlg;
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
