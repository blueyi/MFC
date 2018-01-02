// AdEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AdEdit.h"
#include "AdEditDlg.h"

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
// CAdEditDlg dialog

CAdEditDlg::CAdEditDlg(CWnd* pParent /*=NULL*/)
: CDialog(CAdEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAdEditDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAdEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdEditDlg)
	//	DDX_Control(pDX, IDC_EDIT, m_MyEdit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAdEditDlg, CDialog)
//{{AFX_MSG_MAP(CAdEditDlg)
ON_WM_SYSCOMMAND()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_BTNSUB, OnBtnsub)
ON_BN_CLICKED(IDC_BTNUNSUB, OnBtnunsub)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdEditDlg message handlers

BOOL CAdEditDlg::OnInitDialog()
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
	//此处完成动态子类化
	m_MyEdit.SubclassDlgItem(IDC_EDIT,this);
	m_MyEdit.Initial();
	GetDlgItem(IDC_EDIT)->SetFocus();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAdEditDlg::OnSysCommand(UINT nID, LPARAM lParam)
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



// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAdEditDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//子类化
void CAdEditDlg::OnBtnsub() 
{
	m_MyEdit.SubclassWindow(GetDlgItem(IDC_EDIT)->m_hWnd);
	GetDlgItem(IDC_BTNUNSUB)->EnableWindow(true);
	GetDlgItem(IDC_BTNSUB)->EnableWindow(false);
	m_MyEdit.SetFocus();
}

//反子类化
void CAdEditDlg::OnBtnunsub() 
{
	m_MyEdit.UnsubclassWindow();
	GetDlgItem(IDC_BTNUNSUB)->EnableWindow(false);
	GetDlgItem(IDC_BTNSUB)->EnableWindow(true); 
	GetDlgItem(IDC_EDIT)->SetFocus();
//注意，如果这里用m_MyEdit.SetFocus();会产生错误，
//因为m_MyEdit已经不能处理该窗口需要消息类完成的操作
}
