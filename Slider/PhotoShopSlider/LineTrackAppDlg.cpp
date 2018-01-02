// LineTrackAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LineTrackApp.h"
#include "LineTrackAppDlg.h"

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
// CLineTrackAppDlg dialog

CLineTrackAppDlg::CLineTrackAppDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLineTrackAppDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLineTrackAppDlg)
	m_strNum1 = _T("");
	m_strNum2 = _T("");
	m_strNum3 = _T("");
	m_strNum4 = _T("");
	m_strNum5 = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLineTrackAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLineTrackAppDlg)
	DDX_Control(pDX, IDC_EDIT5, m_wndEdit5);
	DDX_Control(pDX, IDC_EDIT4, m_wndEdit4);
	DDX_Control(pDX, IDC_EDIT3, m_wndEdit3);
	DDX_Control(pDX, IDC_EDIT2, m_wndEdit2);
	DDX_Control(pDX, IDC_EDIT1, m_wndEdit1);
	DDX_Text(pDX, IDC_EDIT1, m_strNum1);
	DDV_MaxChars(pDX, m_strNum1, 3);
	DDX_Text(pDX, IDC_EDIT2, m_strNum2);
	DDV_MaxChars(pDX, m_strNum2, 3);
	DDX_Text(pDX, IDC_EDIT3, m_strNum3);
	DDV_MaxChars(pDX, m_strNum3, 3);
	DDX_Text(pDX, IDC_EDIT4, m_strNum4);
	DDV_MaxChars(pDX, m_strNum4, 3);
	DDX_Text(pDX, IDC_EDIT5, m_strNum5);
	DDV_MaxChars(pDX, m_strNum5, 3);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLineTrackAppDlg, CDialog)
	//{{AFX_MSG_MAP(CLineTrackAppDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, OnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeEdit5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLineTrackAppDlg message handlers

BOOL CLineTrackAppDlg::OnInitDialog()
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


//-------------------------------------------------------------------------------
//注册控件
m_wndLineTrackBar1.SubclassDlgItem(IDC_CUSTOM1, this);
//初始化控件
//此控件在设置nLower,nZero,nUpper,nStep参数后会自动适应大小
//	m_wndLineTrackBar1.InitControl (IDC_EDIT1,RGB(0,0,0),0, 100,200,1);
	m_wndLineTrackBar1.InitControl (IDC_EDIT1);
	m_wndLineTrackBar2.SubclassDlgItem(IDC_CUSTOM2, this);
	m_wndLineTrackBar2.InitControl (IDC_EDIT2,RGB(255,0,0),0, 50,100,2);
	m_wndLineTrackBar3.SubclassDlgItem(IDC_CUSTOM3, this);
	m_wndLineTrackBar3.InitControl (IDC_EDIT3,RGB(0,255,0),0, 10,20,10);
//注意以下两个初始函数的最后一个参数为TRUE,点中以下两控件将使它们的协作控件得到焦点,
	m_wndLineTrackBar4.SubclassDlgItem(IDC_CUSTOM4, this);
	m_wndLineTrackBar4.InitControl (IDC_EDIT4,RGB(0,0,255),0, 0,200,1,TRUE);
	m_wndLineTrackBar5.SubclassDlgItem(IDC_CUSTOM5, this);
	m_wndLineTrackBar5.InitControl (IDC_EDIT5,RGB(255,0,255),0, 150,200,1,TRUE);
//-------------------------------------------------------------------------------


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLineTrackAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CLineTrackAppDlg::OnPaint() 
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
HCURSOR CLineTrackAppDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CLineTrackAppDlg::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	m_nNum1=atoi(m_strNum1);
	m_wndLineTrackBar1.SetPos (m_nNum1);

	UpdateData(FALSE);
}

void CLineTrackAppDlg::OnChangeEdit2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	m_nNum2=atoi(m_strNum2);
	m_wndLineTrackBar2.SetPos (m_nNum2);

	UpdateData(FALSE);

}

void CLineTrackAppDlg::OnChangeEdit3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	m_nNum3=atoi(m_strNum3);
	m_wndLineTrackBar3.SetPos (m_nNum3);

	UpdateData(FALSE);
	
}

void CLineTrackAppDlg::OnChangeEdit4() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	m_nNum4=atoi(m_strNum4);
	m_wndLineTrackBar4.SetPos (m_nNum4);

	UpdateData(FALSE);

}

void CLineTrackAppDlg::OnChangeEdit5() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	m_nNum5=atoi(m_strNum5);
	m_wndLineTrackBar5.SetPos (m_nNum5);

	UpdateData(FALSE);
	
}