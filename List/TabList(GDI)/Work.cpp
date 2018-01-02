
#include "stdafx.h"
#include "Work.h"

#include "MainFrm.h"

/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CWorkApp, CWinApp)
	//{{AFX_MSG_MAP(CWorkApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

CWorkApp::CWorkApp()
{
}

/////////////////////////////////////////////////////////////////////////////

CWorkApp theApp;

/////////////////////////////////////////////////////////////////////////////

BOOL CWorkApp::InitInstance()
{
	AfxEnableControlContainer();

#ifdef _AFXDLL
	Enable3dControls();		
#else
	Enable3dControlsStatic();	
#endif

	SetRegistryKey(_T("Working Ready"));

	CWorkFrm* pFrame = new CWorkFrm;
	m_pMainWnd = pFrame;

	pFrame->LoadFrame(IDR_MAINFRAME,WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,	NULL);

	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////

