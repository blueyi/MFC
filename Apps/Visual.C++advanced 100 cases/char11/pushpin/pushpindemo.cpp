#include "stdafx.h"
#include "pushpindemo.h"
#include "pushpindemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CPushpin2App, CWinApp)
	//{{AFX_MSG_MAP(CPushpin2App)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CPushpin2App::CPushpin2App()
{
}

CPushpin2App theApp;

BOOL CPushpin2App::InitInstance()
{
	Enable3dControls();

	CPushpin2Dlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();

	return FALSE;
}
