// PeekPocket.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PeekPocket.h"
#include "PPDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPeekPocketApp

BEGIN_MESSAGE_MAP(CPeekPocketApp, CWinApp)
END_MESSAGE_MAP()


// CPeekPocketApp construction
CPeekPocketApp::CPeekPocketApp()
	: CWinApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CPeekPocketApp object
CPeekPocketApp theApp;

// CPeekPocketApp initialization

BOOL CPeekPocketApp::InitInstance()
{
    // SHInitExtraControls should be called once during your application's initialization to initialize any
    // of the Windows Mobile specific controls such as CAPEDIT and SIPPREF.
    SHInitExtraControls();

	// Standard initialization
	SetRegistryKey(_T("PeekPocket"));

	CPPDlg dlg;
	
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}

	// Since the dialog has been closed, return false so that we exit the
	//  application, rather than start the application's message pump.
	return TRUE;
}
