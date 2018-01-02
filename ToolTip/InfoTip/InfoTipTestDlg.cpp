// InfoTipTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "InfoTipTest.h"
#include "InfoTipTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
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
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfoTipTestDlg dialog

CInfoTipTestDlg::CInfoTipTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInfoTipTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInfoTipTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInfoTipTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInfoTipTestDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInfoTipTestDlg, CDialog)
	//{{AFX_MSG_MAP(CInfoTipTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfoTipTestDlg message handlers

BOOL CInfoTipTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_hIcon1 = (HICON)::LoadImage(AfxFindResourceHandle(MAKEINTRESOURCE(IDI_ICON1), RT_GROUP_ICON), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 0, 0, 0);
	m_hIcon2 = (HICON)::LoadImage(AfxFindResourceHandle(MAKEINTRESOURCE(IDI_ICON2), RT_GROUP_ICON), MAKEINTRESOURCE(IDI_ICON2), IMAGE_ICON, 0, 0, 0);
	m_hIcon3 = (HICON)::LoadImage(AfxFindResourceHandle(MAKEINTRESOURCE(IDI_ICON3), RT_GROUP_ICON), MAKEINTRESOURCE(IDI_ICON3), IMAGE_ICON, 0, 0, 0);

	// Create the tool tip
	m_Tip.Create(this);

	// Add the tools
	m_Tip.AddTool(GetDlgItem(IDC_BUTTON2), _T("Press this button to set the font!"), m_hIcon2);
	m_Tip.AddTool(GetDlgItem(IDC_EDIT1), _T("This is an edit control!"), m_hIcon3);
	m_Tip.AddTool(GetDlgItem(IDOK), _T("This is the OK button!\nPress it to close the dialog..."), NULL);
	m_Tip.AddTool(GetDlgItem(IDCANCEL), _T("This is the Cancel button!\nPress it to close the dialog..."), NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CInfoTipTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CInfoTipTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CInfoTipTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CInfoTipTestDlg::OnButton1() 
{
	m_Tip.SetIcon(m_hIcon1);
	m_Tip.Show("Example of mult-line\nImmediate tooltip text!");	
}

BOOL CInfoTipTestDlg::PreTranslateMessage(MSG* pMsg) 
{
	m_Tip.RelayEvent(pMsg);
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CInfoTipTestDlg::OnButton2() 
{
	CFontDialog		FontDlg;
	LOGFONT			LogFont;

	// Show the common font dialog
	FontDlg.m_cf.lStructSize	= sizeof(CHOOSEFONT);
	FontDlg.m_cf.hwndOwner		= GetSafeHwnd();
	FontDlg.m_cf.lpLogFont		= &LogFont;
	FontDlg.m_cf.Flags			|= CF_BOTH | CF_INITTOLOGFONTSTRUCT;
	FontDlg.m_cf.Flags			&= ~CF_EFFECTS;

	if (FontDlg.DoModal() == IDOK)
	{
		m_Font.DeleteObject();
		m_Font.CreateFontIndirect(&LogFont);
		m_Tip.SetFont(&m_Font);
	}
}

void CInfoTipTestDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	::DestroyIcon(m_hIcon1);
	::DestroyIcon(m_hIcon2);
	::DestroyIcon(m_hIcon3);
}
