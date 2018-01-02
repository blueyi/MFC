// STabCtrlExampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "STabCtrlExample.h"
#include "STabCtrlExampleDlg.h"

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
// CSTabCtrlExampleDlg dialog

CSTabCtrlExampleDlg::CSTabCtrlExampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSTabCtrlExampleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSTabCtrlExampleDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSTabCtrlExampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSTabCtrlExampleDlg)
	DDX_Control(pDX, IDC_STATIC3, m_Static3);
	DDX_Control(pDX, IDC_STATIC2, m_Static2);
	DDX_Control(pDX, IDC_STATIC1, m_Static1);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
	DDX_Control(pDX, IDC_RADIO1, m_EnableRadioCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSTabCtrlExampleDlg, CDialog)
	//{{AFX_MSG_MAP(CSTabCtrlExampleDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO2, OnDisable)
	ON_BN_CLICKED(IDC_RADIO1, OnEnable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSTabCtrlExampleDlg message handlers

BOOL CSTabCtrlExampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	//////////////////////////////////////////////////////////////////////
	// STabCtrl initialization

	PSTR pszTabItems[] =
	{
		"Tab Sheet 1",
		"Tab Sheet 2",
		"Tab Sheet 3",
		NULL
	};

	TC_ITEM tcItem;

	for(INT i = 0;
		pszTabItems[i] != NULL;
		i++)
	{
		tcItem.mask = TCIF_TEXT;
		tcItem.pszText = pszTabItems[i];
		tcItem.cchTextMax = strlen(pszTabItems[i]);
		m_TabCtrl.InsertItem(i,&tcItem);
	}

	// attach controls to tabs pages.

	m_TabCtrl.AttachControlToTab(&m_Static1,0);	// attach first static text to first page
	m_TabCtrl.AttachControlToTab(&m_Static2,1);	// attach second static text to second page
	m_TabCtrl.AttachControlToTab(&m_Static3,2);	// attach third static text to third page

	// initialize tab to first page.
	m_TabCtrl.SetCurSel(0);

	m_EnableRadioCtrl.SetCheck (TRUE);

	// end of STabCtrl initialization
	//////////////////////////////////////////////////////////////////////
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSTabCtrlExampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSTabCtrlExampleDlg::OnPaint() 
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
HCURSOR CSTabCtrlExampleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSTabCtrlExampleDlg::OnDisable() 
{
	// TODO: Add your control notification handler code here
	m_TabCtrl.EnableWindow (FALSE);
}

void CSTabCtrlExampleDlg::OnEnable() 
{
	// TODO: Add your control notification handler code here
	m_TabCtrl.EnableWindow (TRUE);
}
