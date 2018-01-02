// TrayCalender.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"

#include "TrayCalender.h"
#include "MainFrm.h"
#include "Splash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Define the Section and Keys to use for registry storage
LPCTSTR szSection       = _T("Settings");
LPCTSTR szAutoShuffle   = _T("Auto shuffle");
LPCTSTR szShuffleDelay  = _T("Shuffle delay");
LPCTSTR szCheckDate     = _T("Check date");


/////////////////////////////////////////////////////////////////////////////
// CTrayCalenderApp

BEGIN_MESSAGE_MAP(CTrayCalenderApp, CWinApp)
	//{{AFX_MSG_MAP(CTrayCalenderApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrayCalenderApp construction

CTrayCalenderApp::CTrayCalenderApp()
{
	m_strWindowName		 = _T("Simple Tray Calender");	// Window/Application name

	m_bAutoShuffle	     = TRUE;
	m_nShuffleDelay	     = 20;							// Auto-shuffle after 20 secs
	m_bCheckDate	     = TRUE;

	m_bShuffled			 = FALSE;						// Have we auto-shuffled yet?
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTrayCalenderApp object

CTrayCalenderApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTrayCalenderApp initialization

BOOL CTrayCalenderApp::FirstInstance()
{
	// Determine if another window with our class name exists...
	CWnd *PrevCWnd = CWnd::FindWindow(NULL, m_strWindowName);
	return (PrevCWnd == NULL);
}

void CTrayCalenderApp::GetApplicationSettings()
{
	m_bAutoShuffle		 = GetProfileInt(szSection, szAutoShuffle,   m_bAutoShuffle);
	m_nShuffleDelay		 = GetProfileInt(szSection, szShuffleDelay,  m_nShuffleDelay);
	m_bCheckDate		 = GetProfileInt(szSection, szCheckDate,     m_bCheckDate);
}

void CTrayCalenderApp::SaveApplicationSettings()
{
	WriteProfileInt(szSection, szAutoShuffle,   m_bAutoShuffle);
	WriteProfileInt(szSection, szShuffleDelay,  m_nShuffleDelay);
	WriteProfileInt(szSection, szCheckDate,     m_bCheckDate);
}

BOOL CTrayCalenderApp::InitInstance()
{
	if (!FirstInstance())
		return FALSE;

	SetRegistryKey(_T("Codeguru samples"));

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);

	m_StartTime = CTime::GetCurrentTime();

	m_CurrentDay = m_StartTime.GetDay(); // 1-31

	m_hIcon = LoadIcon(IDI_ICON1+m_CurrentDay-1);
	if (m_hIcon == NULL)
	{
		AfxMessageBox(_T("Unable to get todays icon."));
		return FALSE;
	}

	GetApplicationSettings();

	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// For debugging (or something...)
	//pMainFrame->ActivateFrame();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

#include "HyperLink.h"

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CHyperLink m_MailButton;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_HYPERLINK, m_MailButton);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_MailButton.SetURL(_T("mailto:wb@263.net"));

	m_MailButton.SetColours(m_MailButton.GetLinkColour(),m_MailButton.GetLinkColour());
	m_MailButton.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND));

	::SetCursor(::LoadCursor(NULL, IDC_ARROW));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// App command to run the dialog
void CTrayCalenderApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CTrayCalenderApp commands

// Called when the application gets its death sentence.
int CTrayCalenderApp::ExitInstance() 
{
	SaveApplicationSettings();						// Save the settings
	DestroyIcon(m_hIcon);							// ditch the icon
	return CWinApp::ExitInstance();					// get outta here
}

HICON CTrayCalenderApp::CheckDate()
{
	CTime time = CTime::GetCurrentTime();
	int Day = time.GetDay();
	HICON hIcon;

	if (Day != m_CurrentDay) {
		m_CurrentDay = Day;
		hIcon = LoadIcon(IDI_ICON1+m_CurrentDay-1);		// Try get new icon
		if (hIcon == NULL)
		{
			AfxMessageBox(_T("Unable to get icon for change of day. Sigh..."));
			return NULL;
		}
		DestroyIcon(m_hIcon);							// ditch the previous icon
		m_hIcon = hIcon;
		return hIcon;
	}
	return NULL;
}
