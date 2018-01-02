// DemoListDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DemoList.h"
#include "DemoListDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CDemoListDlg 对话框




CDemoListDlg::CDemoListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoListDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemoListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}

BEGIN_MESSAGE_MAP(CDemoListDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CDemoListDlg 消息处理程序

BOOL CDemoListDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
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
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDemoListDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CDemoListDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

