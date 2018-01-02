// $$Root$$.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "$$Root$$.h"
#include "MainSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C$$Safe_root$$App

BEGIN_MESSAGE_MAP(C$$Safe_root$$App, CWinApp)
	//{{AFX_MSG_MAP(C$$Safe_root$$App)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C$$Safe_root$$App construction

C$$Safe_root$$App::C$$Safe_root$$App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only C$$Safe_root$$App object

C$$Safe_root$$App theApp;

/////////////////////////////////////////////////////////////////////////////
// C$$Safe_root$$App initialization

BOOL C$$Safe_root$$App::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CMainSheet *pSheet = new CMainSheet;
	m_pMainWnd = pSheet;

$$IF(MODAL)
	int nResponse = pSheet->DoModal();
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
	return (FALSE);
$$ELSE	// Modeless

$$IF(START_ON_TASKBAR)
	BOOL bStartOnTaskBarAllowed = GetProfileInt (_T ("StartUp"), _T ("StartOnTaskBarAllowed"), FALSE);
	DWORD dwStyle = (bStartOnTaskBarAllowed && GetProfileInt (_T ("StartUp"), _T ("StartOnTaskBar"), TRUE)) ? WS_MINIMIZE : WS_VISIBLE;
$$ELSE
	DWORD dwStyle = WS_VISIBLE;
$$ENDIF //START_ON_TASKBAR

$$IF(MINIMIZEBOX)
	dwStyle |= WS_MINIMIZEBOX;
$$ENDIF //MINIMIZEBOX

	pSheet->Create (NULL, WS_SYSMENU|WS_POPUP|WS_CAPTION|DS_MODALFRAME|dwStyle);
	return (TRUE);
$$ENDIF	//MODAL
}
