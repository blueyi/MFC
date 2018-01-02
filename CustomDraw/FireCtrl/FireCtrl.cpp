//////////////////////////////////////////////////////////////////////////////
//类名：CFireCtrlApp
//功能：应用程序的初始化
//作者：徐景周(jingzhou_xu@163.net)
//组织：未来工作室(Future Studio)
//日期：2001.12.1
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "FireCtrl.h"
#include "FireCtrlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFireCtrlApp

BEGIN_MESSAGE_MAP(CFireCtrlApp, CWinApp)
	//{{AFX_MSG_MAP(CFireCtrlApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFireCtrlApp construction

CFireCtrlApp::CFireCtrlApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFireCtrlApp object

CFireCtrlApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CFireCtrlApp initialization
//////////////////////////////////////////////////////////////////////////////
//名称：InitInstance
//功能：初始化程序实例
//作者：徐景周(jingzhou_xu@163.net)
//组织：未来工作室(Future Studio)
//日期：2001.12.1
/////////////////////////////////////////////////////////////////////////////
BOOL CFireCtrlApp::InitInstance()
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

	//此程序只能运行一次，用互斥量来判断程序是否已运行
    HANDLE m_hMutex=CreateMutex(NULL,TRUE, m_pszAppName); 
    if(GetLastError()==ERROR_ALREADY_EXISTS) { return FALSE; }

	//设置对话框背景和文本颜色
	SetDialogBkColor(RGB(160,180,220),RGB(0,0,0));

	CFireCtrlDlg dlg;
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
