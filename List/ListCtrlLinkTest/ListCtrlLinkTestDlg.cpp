// ListCtrlLinkTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ListCtrlLinkTest.h"
#include "ListCtrlLinkTestDlg.h"

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
// CListCtrlLinkTestDlg dialog

CListCtrlLinkTestDlg::CListCtrlLinkTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CListCtrlLinkTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CListCtrlLinkTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CListCtrlLinkTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListCtrlLinkTestDlg)
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CListCtrlLinkTestDlg, CDialog)
	//{{AFX_MSG_MAP(CListCtrlLinkTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlLinkTestDlg message handlers

BOOL CListCtrlLinkTestDlg::OnInitDialog()
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
	
	//Data for test
	//Initializing list
	m_listCtrl.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 40);
	m_listCtrl.InsertColumn(1, _T("Age"), LVCFMT_LEFT, 40);
	m_listCtrl.InsertColumn(2, _T("Company"), LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(3, _T("Email"), LVCFMT_LEFT, 200);

	m_listCtrl.InsertItem( 0, _T("Ana"));
	m_listCtrl.SetItemText(0, 1, _T("26"));
	m_listCtrl.SetItemText(0, 2, _T("Stanford"), _T("http://www.stanford.edu"));
	m_listCtrl.SetItemText(0, 3, _T("Unpublished"));

	m_listCtrl.InsertItem( 1, _T("John"));
	m_listCtrl.SetItemText(1, 1, _T("21"));
	m_listCtrl.SetItemText(1, 2, _T("Yahoo"), _T("http://www.yahoo.com"));
	m_listCtrl.SetItemText(1, 3, _T("john@ficticious.edu"), _T("mailto:john@ficticious.edu"));

	m_listCtrl.InsertItem( 2, _T("Cassio"));
	m_listCtrl.SetItemText(2, 1, _T("29"));
	m_listCtrl.SetItemText(2, 2, _T("Symantec"), _T("http://www.symantec.com"));
	m_listCtrl.SetItemText(2, 3, _T("cassio@some_email.org"), _T("mailto:cassio@some_email.org"));
	
	m_listCtrl.InsertItem( 3, _T("Peter"));
	m_listCtrl.SetItemText(3, 1, _T("64"));
	m_listCtrl.SetItemText(3, 2, _T("Retired"));
	m_listCtrl.SetItemText(3, 3, _T("peter@happy_man.org"), _T("mailto:peter@happy_man.org"));

	m_listCtrl.Init();

	m_listCtrl.SetItemData(0, 123);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CListCtrlLinkTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CListCtrlLinkTestDlg::OnPaint() 
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
HCURSOR CListCtrlLinkTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
