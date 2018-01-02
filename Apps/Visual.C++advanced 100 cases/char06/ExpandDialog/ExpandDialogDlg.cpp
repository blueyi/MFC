// ExpandDialogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ExpandDialog.h"
#include "ExpandDialogDlg.h"

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
// CExpandDialogDlg dialog

CExpandDialogDlg::CExpandDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExpandDialogDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExpandDialogDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExpandDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExpandDialogDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExpandDialogDlg, CDialog)
	//{{AFX_MSG_MAP(CExpandDialogDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MORE_BUTTON, OnMoreButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExpandDialogDlg message handlers

BOOL CExpandDialogDlg::OnInitDialog()
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
	
	// 在对话框为缩小状态时，初始显示它
	ExtendDlg(IDC_SEPARATE,FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CExpandDialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CExpandDialogDlg::OnPaint() 
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
HCURSOR CExpandDialogDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CExpandDialogDlg::ExtendDlg(int nResourceID, BOOL bExpand)
{
	// 如果bExpand==TRUE，则扩展对话框为最大；
	// 否则缩小对话框，新的对话框的底部为资源nResourceID控件分割
	static CRect rcLarge;
	static CRect rcSmall;
	CString sExpand;
	
	// 在开始时，保存对话框的最大和最小尺寸
	if(rcLarge.IsRectNull())
	{
		CRect rcLandmark;
		// 得到分割条的指针
		CWnd* pWndLandmark=GetDlgItem(nResourceID);
		ASSERT(pWndLandmark);

		// 得到对话框的尺寸
		GetWindowRect(rcLarge);
		// 得到分割条在对话框中的位置
		pWndLandmark->GetWindowRect(rcLandmark);

		rcSmall=rcLarge;
		rcSmall.bottom=rcLandmark.top;
	}

	if(bExpand)
	{
		// 扩展对话框：重新设置对话框到其原始（最大）尺寸（rcLarge）
		SetWindowPos(NULL,0,0,rcLarge.Width(),rcLarge.Height(),
					SWP_NOMOVE|SWP_NOZORDER);

		sExpand="<<&Less";
		EnableVisibleChildren();
	}
	else
	{
		// 缩小对话框：重新设置对话框到其最小尺寸（rcSmall）
		SetWindowPos(NULL,0,0,rcSmall.Width(),rcSmall.Height(),
					SWP_NOMOVE|SWP_NOZORDER);

		sExpand="&More>>";
		EnableVisibleChildren();
	}

	// 设置按钮的文字
	SetDlgItemText(IDC_MORE_BUTTON,sExpand);
}

void CExpandDialogDlg::EnableVisibleChildren()
{
	// 下面的代码使不在当前对话框中的按钮失效。
	// 这样可以避免使用Tab键或者快捷键移动到隐藏的控件

	// 得到第一个子控件
	CWnd* pWndCtrl=GetWindow(GW_CHILD);
	CRect rcRest;
	CRect rcControl;
	CRect rcShow;

	GetWindowRect(rcShow);

	// 遍历对话框中的控件
	while(pWndCtrl!=NULL)
	{
		pWndCtrl->GetWindowRect(rcControl);

		if(rcRest.IntersectRect(rcShow,rcControl))
			pWndCtrl->EnableWindow(TRUE);
		else
			pWndCtrl->EnableWindow(FALSE);

		// 得到在控件组中的下一个
		pWndCtrl=pWndCtrl->GetWindow(GW_HWNDNEXT);
	}
}

void CExpandDialogDlg::OnMoreButton() 
{
	// 变量bExpand用于跟踪对话框扩展/缩减的状态
	static BOOL bExpand = TRUE;

	// 以IDC_SEPARATE分割对话框
	ExtendDlg(IDC_SEPARATE,bExpand);
	bExpand=!bExpand;
}
