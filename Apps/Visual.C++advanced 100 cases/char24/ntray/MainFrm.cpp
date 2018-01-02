#include "stdafx.h"
#include "traytest.h"
#include "MainFrm.h"
#include "Splash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define WM_TRAYNOTIFY WM_USER + 100


IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_HAPPY, OnHappy)
	ON_UPDATE_COMMAND_UI(ID_HAPPY, OnUpdateHappy)
	ON_COMMAND(ID_SAD, OnSad)
	ON_UPDATE_COMMAND_UI(ID_SAD, OnUpdateSad)
	ON_COMMAND(ID_ANIMATED, OnAnimated)
	ON_UPDATE_COMMAND_UI(ID_ANIMATED, OnUpdateAnimated)
	//}}AFX_MSG_MAP
  ON_MESSAGE(WM_TRAYNOTIFY, OnTrayNotification)
END_MESSAGE_MAP()


CMainFrame::CMainFrame()
{
  m_bHappy = TRUE;
  m_hIcons[0] = AfxGetApp()->LoadIcon(IDR_HAPPY);
  m_hIcons[1] = AfxGetApp()->LoadIcon(IDR_SAD);
}


CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	// CG: The following line was added by the Splash Screen component.
	CSplashWnd::ShowSplashScreen(this);

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_TrayIcon.Create(this, IDR_TRAYPOPUP, _T("Demo Tray Application"), m_hIcons, 2, 500, WM_TRAYNOTIFY))
	{
		AfxMessageBox(_T("Failed to create tray icon"), MB_OK | MB_ICONSTOP);
		return -1;
	}

	return 0;
}


LRESULT CMainFrame::OnTrayNotification(WPARAM wParam, LPARAM lParam)
{
  //Delegate all the work back to the default implementation in
  //CTrayNotifyIcon.
  return m_TrayIcon.OnTrayNotification(wParam, lParam);
}


void CMainFrame::OnHappy() 
{
	m_bHappy = !m_bHappy;

  if (m_bHappy)
  {
    m_TrayIcon.SetIcon(AfxGetApp()->LoadIcon(IDR_HAPPY));
    m_TrayIcon.SetTooltipText(_T("I'm Happy!"));
  }
  else
  {
    m_TrayIcon.SetIcon(AfxGetApp()->LoadIcon(IDR_SAD));
    m_TrayIcon.SetTooltipText(_T("I'm Sad!"));
  }
}

void CMainFrame::OnUpdateHappy(CCmdUI* pCmdUI) 
{
  if (m_TrayIcon.UsingAnimatedIcon())
    pCmdUI->Enable(FALSE);
  else
	  pCmdUI->SetCheck(m_bHappy);
}

void CMainFrame::OnSad() 
{
	OnHappy();
}

void CMainFrame::OnUpdateSad(CCmdUI* pCmdUI) 
{
  if (m_TrayIcon.UsingAnimatedIcon())
    pCmdUI->Enable(FALSE);
  else
  	pCmdUI->SetCheck(!m_bHappy);
}

void CMainFrame::OnAnimated() 
{
	if (m_TrayIcon.UsingAnimatedIcon())
  {
    m_TrayIcon.SetIcon(m_hIcons[0]);
  }
  else
  {
    m_TrayIcon.SetIcon(m_hIcons, 2, 500);
  }
}

void CMainFrame::OnUpdateAnimated(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_TrayIcon.UsingAnimatedIcon());
}
