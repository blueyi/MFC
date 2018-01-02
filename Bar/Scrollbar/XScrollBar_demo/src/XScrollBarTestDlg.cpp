// XScrollBarTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XScrollBarTest.h"
#include "XScrollBarTestDlg.h"
#include "horz.h"
#include "vert.h"
#include "about.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXScrollBarTestDlg dialog

BEGIN_MESSAGE_MAP(CXScrollBarTestDlg, CDialog)
	//{{AFX_MSG_MAP(CXScrollBarTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_HORZ, OnButtonHorz)
	ON_BN_CLICKED(IDC_BUTTON_VERT, OnButtonVert)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_ONLINE_HELP, OnOnlineHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CXScrollBarTestDlg::CXScrollBarTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXScrollBarTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXScrollBarTestDlg)
	//}}AFX_DATA_INIT

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXScrollBarTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXScrollBarTestDlg)
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CXScrollBarTestDlg message handlers

BOOL CXScrollBarTestDlg::OnInitDialog()
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

	// Set the icon for this dialog. The framework does this automatically
	// when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CXScrollBarTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CXScrollBarTestDlg::OnPaint() 
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

HCURSOR CXScrollBarTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CXScrollBarTestDlg::OnButtonHorz() 
{
	CHorz dlg;
	dlg.DoModal();
}

void CXScrollBarTestDlg::OnButtonVert() 
{
	CVert dlg;
	dlg.DoModal();
}

void CXScrollBarTestDlg::OnOnlineHelp() 
{
	CString strHelp = _T("");
	VERIFY(strHelp.LoadString(IDS_ONLINE_HELP));
	CXHyperLink::GotoURL(strHelp, SW_SHOW, TRUE);	
}
