#include "stdafx.h"
#include "traytest.h"
#include "MainFrm.h"
#include "Splash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CTrayApp, CWinApp)
	//{{AFX_MSG_MAP(CTrayApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CTrayApp::CTrayApp()
{
  bDisplayingAboutBox = FALSE;
}

CTrayApp theApp;

BOOL CTrayApp::InitInstance()
{
	Enable3dControls();

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);

	CMainFrame* pMainFrame = new CMainFrame;
	m_pMainWnd = pMainFrame;
	if (!pMainFrame->Create(NULL, _T("Traytest")))
		return FALSE;

	m_pMainWnd->ShowWindow(SW_HIDE);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


void CTrayApp::OnAppAbout()
{
  //avoid bringing up two versions of the dialog
  if (bDisplayingAboutBox)
    return;

  bDisplayingAboutBox = TRUE;
	CDialog(IDD_ABOUTBOX).DoModal();
  bDisplayingAboutBox = FALSE;
}

