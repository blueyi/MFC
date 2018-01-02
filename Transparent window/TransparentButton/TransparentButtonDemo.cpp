// TransparentButtonDemo.cpp : Defines the class behaviors for the application.
//

/********************************************************************
*
*	TRANSPARENT BUTTON DEMO
*
*	This is a demo program to show the use of a bitmap-on-bitmap
*	approach when using button controls, and how these buttons can
*	be displayed with various degrees of transparency on a dynamic
*	background.  The buttons also produce anti-aliased edging for a
*	nice clean interface.
*
*	The dialog-based application is displayed as a circle to give a
*	stylistic effect to the typically mundane MFC program.
*
*	Thanks very much to many contributors at www.codeproject.com and
*	www.codeguru.com, including:
*
*	Niek Albers and Frederick Ackers for the CHoverButtonEx class
*	Paul Nettle for the WinDIB class and alphaBlend routine
*	Keith Rule for CMemDC
*
*	If this demo works, and you liked it, it was written by 
*
*						  Bob Carboni
*					www.carbonisoftware.com
*
*	If not, I don't know who put this pile of crap together...
*
********************************************************************/

#include "stdafx.h"
#include "TransparentButtonDemo.h"
#include "TransparentButtonDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTransparentButtonDemoApp

BEGIN_MESSAGE_MAP(CTransparentButtonDemoApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTransparentButtonDemoApp construction

CTransparentButtonDemoApp::CTransparentButtonDemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CTransparentButtonDemoApp object

CTransparentButtonDemoApp theApp;


// CTransparentButtonDemoApp initialization

BOOL CTransparentButtonDemoApp::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CTransparentButtonDemoDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
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
