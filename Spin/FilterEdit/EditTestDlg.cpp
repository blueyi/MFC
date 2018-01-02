// EditTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EditTest.h"
#include "EditTestDlg.h"

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
// CEditTestDlg dialog

CEditTestDlg::CEditTestDlg(CWnd* pParent /*=NULL*/) :
	CDialog(CEditTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEditTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditTestDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEditTestDlg, CDialog)
	//{{AFX_MSG_MAP(CEditTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO_DATE, OnRadioDate)
	ON_BN_CLICKED(IDC_RADIO_TIME, OnRadioTime)
	ON_BN_CLICKED(IDC_RADIO_DATE_TIME, OnRadioDateTime)
	ON_BN_CLICKED(IDC_CHECK_ALLOW_NULL, OnCheckAllowNull)
	//}}AFX_MSG_MAP
	ON_WM_MOVE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditTestDlg message handlers

BOOL CEditTestDlg::OnInitDialog()
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

//	m_EditDate.Create(ES_CENTER | ES_AUTOHSCROLL, CRect(0, 0, 20, 20), this, IDC_EDIT_DATE);

	m_EditDate.SubclassDlgItem (IDC_EDIT_DATE, this);
	m_EditDate.SetBackgroundColourFocus (RGB (150, 200, 255));
	m_EditDate.CreateToolTip (this);

	m_SpinDate.SubclassDlgItem (IDC_SPIN_DATE, this);

	static_cast<CButton *>(GetDlgItem (IDC_RADIO_DATE))->SetCheck (TRUE);

	m_EditUInt.SubclassDlgItem (IDC_EDIT_UINT, this);
	m_EditUInt.SetRange (5, 99);
	m_EditUInt.LimitText (2);
	m_EditUInt.SetWavyLineColour (RGB (255, 255, 255));
	m_EditUInt.SetBackgroundColourFocus (RGB (150, 200, 255));
	m_EditUInt.SetForegroundColourError (RGB (255, 255, 255));
	m_EditUInt.SetBackgroundColourError (RGB (255, 0, 0));

	m_SpinUInt.SubclassDlgItem (IDC_SPIN_UINT, this);

	m_EditYear.SubclassDlgItem (IDC_EDIT_YEAR, this);

	m_EditPrice.SubclassDlgItem (IDC_EDIT_PRICE, this);
	m_EditPrice.SetBackgroundColourFocus (RGB (150, 200, 255));
	m_EditPrice.SetBackgroundColourOK (RGB (150, 255, 200));
	m_EditPrice.SetAllowEmpty(true);
//	m_EditPrice.CreateToolTip (this);

	m_EditEmail.SubclassDlgItem (IDC_EDIT_EMAIL, this);
//	m_EditEmail.SetRegEx (_T(".*"));
	m_EditEmail.SetRegEx (_T("^((\\\"[^\\\"\\f\\n\\r\\t\\v\\b]+\\\")|([\\w\\!\\#\\$")
		_T("\\%\\&\\'\\*\\+\\-\\~\\/\\^\\`\\|\\{\\}]+(\\.[\\w\\!\\#\\$\\%\\&\\'\\")
		_T("*\\+\\-\\~\\/\\^\\`\\|\\{\\}]+)*))@((\\[(((25[0-5])|(2[0-4][0-9])|([0")
		_T("-1]?[0-9]?[0-9]))\\.((25[0-5])|(2[0-4][0-9])|([0-1]?[0-9]?[0-9]))\\.(")
		_T("(25[0-5])|(2[0-4][0-9])|([0-1]?[0-9]?[0-9]))\\.((25[0-5])|(2[0-4][0-9")
		_T("])|([0-1]?[0-9]?[0-9])))\\])|(((25[0-5])|(2[0-4][0-9])|([0-1]?[0-9]?[")
		_T("0-9]))\\.((25[0-5])|(2[0-4][0-9])|([0-1]?[0-9]?[0-9]))\\.((25[0-5])|(")
		_T("2[0-4][0-9])|([0-1]?[0-9]?[0-9]))\\.((25[0-5])|(2[0-4][0-9])|([0-1]?[")
		_T("0-9]?[0-9])))|((([A-Za-z0-9\\-])+\\.)+[A-Za-z\\-]+))$"));
	m_EditEmail.SetReadOnly();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEditTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEditTestDlg::OnPaint() 
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
HCURSOR CEditTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CEditTestDlg::OnOK() 
{
	if (m_EditDate.IsInputValid () && m_EditUInt.IsInputValid () &&
		m_EditPrice.IsInputValid () && m_EditEmail.IsInputValid ())
	{
		COleDateTime dt = m_EditDate.GetDateTime();
		int iYear = dt.GetYear ();
		int iMonth = dt.GetMonth ();
		int iDay = dt.GetDay ();
		int iHour = dt.GetHour ();
		int iMinute = dt.GetMinute ();
		int iSecond = dt.GetSecond ();

		CString strPrice;

		m_EditPrice.GetWindowText(strPrice);
		CDialog::OnOK();
	}
}

void CEditTestDlg::OnMove (int x, int y)
{
	CWnd *pWndOK = GetDlgItem (IDOK);
	CWnd *pFocus = GetFocus ();

	CDialog::OnMove (x, y);

	if (pWndOK && pFocus)
	{
		// This allows the balloon help to be moved with the dialog
		pWndOK->SetFocus ();
		pFocus->SetFocus ();
	}
}

void CEditTestDlg::OnRadioDate() 
{
	m_EditDate.SetMode (FilterEdit::CDateTimeEdit::eDate);
	m_EditDate.SetFocus ();
}

void CEditTestDlg::OnRadioTime()
{
	m_EditDate.SetMode (FilterEdit::CDateTimeEdit::eTimeHHMM);
	m_EditDate.SetFocus ();
}

void CEditTestDlg::OnRadioDateTime() 
{
	m_EditDate.SetMode (FilterEdit::CDateTimeEdit::eDateTimeHHMMSS);
	m_EditDate.SetFocus ();
}

void CEditTestDlg::OnCheckAllowNull() 
{
	BOOL bChecked = static_cast<CButton *>
		(GetDlgItem (IDC_CHECK_ALLOW_NULL))->GetCheck ();

	m_EditDate.SetAllowEmpty (bChecked != 0);

	if (bChecked)
	{
		m_EditDate.IsInputValid (true);
	}

	m_EditDate.SetFocus ();
}
