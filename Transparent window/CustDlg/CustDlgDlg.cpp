// CustDlgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CustDlg.h"
#include "CustDlgDlg.h"
#include "BmpBkgndDlg.h"

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
// CCustDlgDlg dialog

CCustDlgDlg::CCustDlgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCustDlgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCustDlgDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_clrText = RGB(13,125,188);
	m_clrBkgnd = RGB(188,197,230);
	m_brBkgnd.CreateSolidBrush(m_clrBkgnd);
	m_brControlBkgnd1.CreateSolidBrush(RGB(18,222,193));
	m_brControlBkgnd2.CreateSolidBrush(RGB(244,222,43));
	m_hCat1 = (HBITMAP)::LoadImage(AfxGetResourceHandle(),(LPCTSTR)IDB_BITMAP1,IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION);
	m_hCat2 = (HBITMAP)::LoadImage(AfxGetResourceHandle(),MAKEINTRESOURCE(IDB_BITMAP2),IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION);;

}

CCustDlgDlg::~CCustDlgDlg()
{
	m_brBkgnd.DeleteObject();
	m_brControlBkgnd1.DeleteObject();
	m_brControlBkgnd2.DeleteObject();
	DeleteObject(m_hCat1);
	DeleteObject(m_hCat2);
}

void CCustDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustDlgDlg)
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_BTN_CHG, m_btnChg);
	DDX_Control(pDX, IDC_BTN_ABOUT, m_btnAbout);
	DDX_Control(pDX, IDC_BTN_OPEN, m_btnOpen);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCustDlgDlg, CDialog)
	//{{AFX_MSG_MAP(CCustDlgDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_OPEN, OnBtnOpen)
	ON_BN_CLICKED(IDC_BTN_CHG, OnBtnChg)
	ON_BN_CLICKED(IDC_BTN_ABOUT, OnBtnAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustDlgDlg message handlers

BOOL CCustDlgDlg::OnInitDialog()
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
	m_btnOK.SetInactiveBgColor(RGB(244,222,43));
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCustDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCustDlgDlg::OnPaint() 
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
HCURSOR CCustDlgDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CCustDlgDlg::OnEraseBkgnd(CDC* pDC) 
{
	CRect rcClient;
	GetClientRect(&rcClient);
	pDC->FillRect(&rcClient,&m_brBkgnd);

	return TRUE;

//	return CDialog::OnEraseBkgnd(pDC);
}

HBRUSH CCustDlgDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	TCHAR szClassName[64];

	::GetClassName(pWnd->GetSafeHwnd(),szClassName,64);
	if(lstrcmpi(szClassName,_T("Edit")) == 0) //是Edit 控件
	{
		DWORD dwStyle = pWnd->GetStyle();
		if((dwStyle & ES_MULTILINE)  == ES_MULTILINE) //多行edit控件
		{
			pDC->SetTextColor(m_clrText);
			return hbr;
		}
		else
		{
			pDC->SetTextColor(m_clrText);
			pDC->SetBkMode(TRANSPARENT);

			return (HBRUSH)m_brBkgnd;
		}
	}
	else //不是编辑控件
	{
		if(pWnd->GetDlgCtrlID() == IDC_STC_REDTEXT)
		{
			pDC->SetTextColor(RGB(255,0,0));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)m_brBkgnd;
		}
		else if(pWnd->GetDlgCtrlID() == IDC_STC_BLUETEXT)
		{
			pDC->SetTextColor(RGB(0,0,255));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)m_brBkgnd;
		}
		else if(pWnd->GetDlgCtrlID() == IDC_STC_BLUETEXTWHITEBACK)
		{
			pDC->SetTextColor(RGB(0,0,255));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)m_brControlBkgnd1;
		}
		else if(pWnd->GetDlgCtrlID() == IDC_CHK_GREEN)
		{
			pDC->SetTextColor(RGB(0,255,0));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)m_brBkgnd;
		}
		else if(pWnd->GetDlgCtrlID() == IDC_RAD_BLUE)
		{
			pDC->SetTextColor(RGB(0,0,255));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)m_brBkgnd;
		}
		else if(pWnd->GetDlgCtrlID() == IDC_CHK_GREEN2)
		{
			pDC->SetTextColor(RGB(0,255,0));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)m_brControlBkgnd2;
		}
		else if(pWnd->GetDlgCtrlID() == IDC_RADIO2)
		{
			pDC->SetTextColor(RGB(0,0,255));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)m_brControlBkgnd2;
		}
		else
		{
			pDC->SetTextColor(m_clrText);
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)m_brBkgnd;
		}
	}
}

//@**#---2005-08-20 11:44:07 (NoName)---#**@
////这是版本1的代码
//HBRUSH CCustDlgDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
//{
//	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
//	
//	if(pWnd->GetDlgCtrlID() == IDC_EDIT_MULTI_LINE) //IDC_EDIT_MULTI_LINE是多行Edir控件的ID
//	{
//		pDC->SetTextColor(m_clrText);
//
//		return hbr;
//	}
//	else
//	{
//		pDC->SetTextColor(m_clrText);
//		pDC->SetBkMode(TRANSPARENT);
//
//		return (HBRUSH)m_brBkgnd;
//	}
//}

void CCustDlgDlg::OnBtnOpen() 
{
	CBmpBkgndDlg dlg;
	dlg.DoModal();
}

void CCustDlgDlg::OnBtnChg() 
{
	static BOOL bSign = TRUE;
	if(bSign)
	{
		GetDlgItem(IDC_STC_PICTURE)->SendMessage(STM_SETIMAGE,IMAGE_BITMAP, (LPARAM)m_hCat1);
		bSign = FALSE;
	}
	else
	{
		GetDlgItem(IDC_STC_PICTURE)->SendMessage(STM_SETIMAGE,IMAGE_BITMAP, (LPARAM)m_hCat2);	
		bSign = TRUE;
	}
}

void CCustDlgDlg::OnBtnAbout() 
{
	CAboutDlg dlg;
	dlg.DoModal();
}
