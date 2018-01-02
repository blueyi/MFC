
//////////////////////////////////////////////////////////////////////////////
//类名：CFireCtrlDlg
//功能：火焰效果示例实现对话框
//作者：徐景周(jingzhou_xu@163.net)
//组织：未来工作室(Future Studio)
//日期：2001.12.1
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "FireCtrl.h"
#include "FireCtrlDlg.h"

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
	CPictureEx	m_Flag;				//GIF动态图像显示
	CHyperLink	m_Mail;				//超链接形式显示EMAIL
	CWBButton	m_OK;				//位图按钮
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
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
	DDX_Control(pDX, IDC_FLAG, m_Flag);
	DDX_Control(pDX, IDC_STATIC_MAIL, m_Mail);
	DDX_Control(pDX, IDOK, m_OK);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////
//名称：OnInitDialog
//功能：初始化"关于"对话框
//作者：徐景周(jingzhou_xu@163.net)
//组织：未来工作室(Future Studio)
//日期：2001.12.1
/////////////////////////////////////////////////////////////////////////////
BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//设置“关于”对话框的位图按钮显示
	m_OK.LoadBitmaps(IDB_BUTTON,5, 5, 5, 5, 4 );

	//加入EMAIL的超连接
    m_Mail.SetURL(_T("mailto:jingzhou_xu@163.net"));
	m_Mail.SetUnderline(FALSE);	

	//显示动态GIF图像logo
	if(m_Flag.Load(MAKEINTRESOURCE(IDR_FLAG),_T("GIF")))
	{
		m_Flag.SetBkColor(RGB(160,180,220));
		m_Flag.Draw();	
	}	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// CFireCtrlDlg dialog

CFireCtrlDlg::CFireCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFireCtrlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFireCtrlDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFireCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFireCtrlDlg)
	DDX_Control(pDX, IDC_ABOUT, m_About);
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDC_FIRE, m_FireCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFireCtrlDlg, CDialog)
	//{{AFX_MSG_MAP(CFireCtrlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFireCtrlDlg message handlers
//////////////////////////////////////////////////////////////////////////////
//名称：OnInitDialog
//功能：初始化对话框
//作者：徐景周(jingzhou_xu@163.net)
//组织：未来工作室(Future Studio)
//日期：2001.12.1
/////////////////////////////////////////////////////////////////////////////
BOOL CFireCtrlDlg::OnInitDialog()
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
	
	//初始置窗体位于最顶层
	SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	//设置位图按钮显示
	m_OK.LoadBitmaps(IDB_BUTTON,5, 5, 5, 5, 4 );
	m_About.LoadBitmaps(IDB_BUTTON,5, 5, 5, 5, 4 );
	
	//初始使用默认火焰控件类中的默认调色板颜色值
	RGBTRIPLE *rgbPalette = NULL;
	m_FireCtrl.SetPalette(rgbPalette);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFireCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFireCtrlDlg::OnPaint() 
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
HCURSOR CFireCtrlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//////////////////////////////////////////////////////////////////////////////
//名称：OnAbout
//功能：弹出"关于"对话框
//作者：徐景周(jingzhou_xu@163.net)
//组织：未来工作室(Future Studio)
//日期：2001.12.1
/////////////////////////////////////////////////////////////////////////////
void CFireCtrlDlg::OnAbout() 
{
	CAboutDlg AboutDlg;

	AboutDlg.DoModal();	
}
