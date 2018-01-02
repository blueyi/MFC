// DemoListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DemoList.h"
#include "DemoListDlg.h"

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
// CDemoListDlg dialog

CDemoListDlg::CDemoListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemoListDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemoListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoListDlg)
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemoListDlg, CDialog)
	//{{AFX_MSG_MAP(CDemoListDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoListDlg message handlers

BOOL CDemoListDlg::OnInitDialog()
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
	
	// TODO: Add extra initialization here
	m_ListCtrl.SetColColor(0,RGB(10,150,20)); //设置列背景色
	m_ListCtrl.SetColColor(2,RGB(30,100,90)); //设置列背景色
	m_ListCtrl.SetBkColor(RGB(50,10,10));        //设置背景色
	m_ListCtrl.SetItemColor(1,1,RGB(100,100,10)); //设置指定单元背景色
	m_ListCtrl.SetRowHeigt(25);               //设置行高度
	m_ListCtrl.SetHeaderHeight(1.5);          //设置头部高度
	m_ListCtrl.SetHeaderFontHW(16,0);         //设置头部字体高度,和宽度,0表示缺省，自适应 
	m_ListCtrl.SetHeaderTextColor(RGB(255,200,100)); //设置头部字体颜色
	m_ListCtrl.SetTextColor(RGB(0,255,255));  //设置文本颜色
	m_ListCtrl.SetHeaderBKColor(100,255,100,8); //设置头部背景色
	m_ListCtrl.SetFontHW(15,0);               //设置字体高度，和宽度,0表示缺省宽度
	m_ListCtrl.SetColTextColor(2,RGB(255,255,100)); //设置列文本颜色
	m_ListCtrl.SetItemTextColor(3,1,RGB(255,0,0));  //设置单元格字体颜色

	m_ListCtrl.InsertColumn(0,_T("名字"),LVCFMT_CENTER,55);
	m_ListCtrl.InsertColumn(1,_T("身高"),LVCFMT_CENTER,60);
	m_ListCtrl.InsertColumn(2,_T("体重"),LVCFMT_CENTER,60);
	m_ListCtrl.InsertColumn(3,_T("测量时间"),LVCFMT_CENTER,180);

	m_ListCtrl.InsertItem(0,"张三");
	m_ListCtrl.SetItemText(0,1,"178CM");
	m_ListCtrl.SetItemText(0,2,"70KG");
	m_ListCtrl.SetItemText(0,3,"2009年1月15日23时40分");

	m_ListCtrl.InsertItem(1,"王五");
	m_ListCtrl.SetItemText(1,1,"178cm");
	m_ListCtrl.SetItemText(1,2,"70kg");
	m_ListCtrl.SetItemText(1,3,"2009年1月15日23时40分");

	m_ListCtrl.InsertItem(2,"阿花");
	m_ListCtrl.SetItemText(2,1,"168cm");
	m_ListCtrl.SetItemText(2,2,"60kg");
	m_ListCtrl.SetItemText(2,3,"2009年1月15日23时40分");

	SetWindowLong(m_ListCtrl.m_hWnd ,GWL_EXSTYLE,WS_EX_CLIENTEDGE);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES);                     //设置扩展风格为网格
	::SendMessage(m_ListCtrl.m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE,
		LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDemoListDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDemoListDlg::OnPaint() 
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
HCURSOR CDemoListDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
