// ValidatingEditDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ValidatingEditDemo.h"
#include "ValidatingEditDemoDlg.h"

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
// CValidatingEditDemoDlg dialog

CValidatingEditDemoDlg::CValidatingEditDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CValidatingEditDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CValidatingEditDemoDlg)
	m_bCheckNumericCannotBeNegative = FALSE;
	m_strEditAlphanumericInvalidCharacters = _T("'*\"+?><:\\");
	m_dEditCurrencyAsDouble = 0.0;
	m_strEditMaskedMask = _T("(###) ###-#### x####");
	m_nEditNumericRightDigits = 9;
	m_nEditNumericLeftDigits = 4;
	m_dEditNumericAsDouble = 0.0;
	m_nEditAlphanumericMaxCharacters = 20;
	m_bCheckTime24HourFormat = m_ctlEditTimeDataEntry.IsShowing24HourFormat();
	m_bCheckTimeShowSeconds = FALSE;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CValidatingEditDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CValidatingEditDemoDlg)
	DDX_Control(pDX, IDC_EDIT_TIME_DATA_ENTRY, m_ctlEditTimeDataEntry);
	DDX_Control(pDX, IDC_SPIN_NUMERIC_RIGHT_DIGITS, m_ctlSpinNumericRightDigits);
	DDX_Control(pDX, IDC_SPIN_NUMERIC_LEFT_DIGITS, m_ctlSpinNumericLeftDigits);
	DDX_Control(pDX, IDC_SPIN_ALPHANUMERIC_MAX_CHARACTERS, m_ctlSpinAlphanumericMaxCharacters);
	DDX_Control(pDX, IDC_EDIT_CURRENCY_DATA_ENTRY, m_ctlEditCurrencyDataEntry);
	DDX_Control(pDX, IDC_EDIT_NUMERIC_DATA_ENTRY, m_ctlEditNumericDataEntry);
	DDX_Control(pDX, IDC_EDIT_MASKED_NUMERIC_DATA_ENTRY, m_ctlEditMaskedDataEntry);
	DDX_Control(pDX, IDC_EDIT_DATE_DATA_ENTRY, m_ctlEditDateDataEntry);
	DDX_Control(pDX, IDC_EDIT_ALPHANUMERIC_DATA_ENTRY, m_ctlEditAlphanumericDataEntry);
	DDX_Check(pDX, IDC_CHECK_NUMERIC_CANNOT_BE_NEGATIVE, m_bCheckNumericCannotBeNegative);
	DDX_Text(pDX, IDC_EDIT_ALPHANUMERIC_INVALID_CHARACTERS, m_strEditAlphanumericInvalidCharacters);
	DDX_Text(pDX, IDC_EDIT_CURRENCY_AS_DOUBLE, m_dEditCurrencyAsDouble);
	DDX_Text(pDX, IDC_EDIT_MASKED_NUMERIC_MASK, m_strEditMaskedMask);
	DDX_Text(pDX, IDC_EDIT_NUMERIC_RIGHT_DIGITS, m_nEditNumericRightDigits);
	DDV_MinMaxInt(pDX, m_nEditNumericRightDigits, 0, 20);
	DDX_Text(pDX, IDC_EDIT_NUMERIC_LEFT_DIGITS, m_nEditNumericLeftDigits);
	DDV_MinMaxInt(pDX, m_nEditNumericLeftDigits, 1, 20);
	DDX_Text(pDX, IDC_EDIT_NUMERIC_AS_DOUBLE, m_dEditNumericAsDouble);
	DDX_Text(pDX, IDC_EDIT_ALPHANUMERIC_MAX_CHARACTERS, m_nEditAlphanumericMaxCharacters);
	DDV_MinMaxInt(pDX, m_nEditAlphanumericMaxCharacters, 0, 200);
	DDX_Check(pDX, IDC_CHECK_TIME_24HOUR_FORMAT, m_bCheckTime24HourFormat);
	DDX_Check(pDX, IDC_CHECK_TIME_SHOW_SECONDS, m_bCheckTimeShowSeconds);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_DATE_MAX, m_dateMax);	
	DDX_Control(pDX, IDC_DATE_MIN, m_dateMin);	
}


BEGIN_MESSAGE_MAP(CValidatingEditDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CValidatingEditDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT_ALPHANUMERIC_INVALID_CHARACTERS, OnChangeEditAlphanumericInvalidCharacters)
	ON_BN_CLICKED(IDC_CHECK_NUMERIC_CANNOT_BE_NEGATIVE, OnCheckNumericCannotBeNegative)
	ON_EN_CHANGE(IDC_EDIT_MASKED_NUMERIC_MASK, OnChangeEditMaskedMask)
	ON_EN_CHANGE(IDC_EDIT_CURRENCY_DATA_ENTRY, OnChangeEditCurrencyDataEntry)
	ON_EN_CHANGE(IDC_EDIT_NUMERIC_DATA_ENTRY, OnChangeEditNumericDataEntry)
	ON_EN_CHANGE(IDC_EDIT_ALPHANUMERIC_MAX_CHARACTERS, OnChangeEditAlphanumericMaxCharacters)
	ON_EN_CHANGE(IDC_EDIT_NUMERIC_LEFT_DIGITS, OnChangeEditNumericLeftDigits)
	ON_EN_CHANGE(IDC_EDIT_NUMERIC_RIGHT_DIGITS, OnChangeEditNumericRightDigits)
	ON_BN_CLICKED(IDC_CHECK_TIME_24HOUR_FORMAT, OnCheckTime24HourFormat)
	ON_BN_CLICKED(IDC_CHECK_TIME_SHOW_SECONDS, OnCheckTimeShowSeconds)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATE_MIN, OnChangeDateRange)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATE_MAX, OnChangeDateRange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CValidatingEditDemoDlg message handlers

BOOL CValidatingEditDemoDlg::OnInitDialog() 
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

	// Initialize the controls

	// Make the group headings bold
	CFont* pFont = GetFont();
	LOGFONT lf;
	pFont->GetLogFont(&lf);	
	static CFont fontBold;
	lf.lfWeight = FW_BOLD;
	fontBold.CreateFontIndirect(&lf);  
	GetDlgItem(IDC_STATIC_NUMERIC)->SetFont(&fontBold);
	GetDlgItem(IDC_STATIC_CURRENCY)->SetFont(&fontBold);
	GetDlgItem(IDC_STATIC_MASKED_NUMERIC)->SetFont(&fontBold);
	GetDlgItem(IDC_STATIC_ALPHANUMERIC)->SetFont(&fontBold);
	GetDlgItem(IDC_STATIC_DATE)->SetFont(&fontBold);
	GetDlgItem(IDC_STATIC_TIME)->SetFont(&fontBold);

	// Adjust the locale to the user's settings.
	_tsetlocale(LC_ALL, _T(""));

	// Set the max and min date ranges
	COleDateTime dtMin(1980, 01, 01, 0, 0, 0);
	COleDateTime dtMax(2100, 12, 31, 0, 0, 0);

	m_dateMin.SetTime(dtMin);	
	m_dateMax.SetTime(dtMax);
	m_ctlEditDateDataEntry.SetRange(dtMin, dtMax);

	m_ctlEditDateDataEntry.ModifyFlags(CAMSDateEdit::OnKillFocus_Beep_IfInvalid, 0);
	
	m_ctlSpinAlphanumericMaxCharacters.SetRange(0, 200);
	m_ctlSpinNumericLeftDigits.SetRange(1, 20);
	m_ctlSpinNumericRightDigits.SetRange(0, 20);

	// Allow automatic input of the decimal after the maximum number of whole digits has been entered
	m_ctlEditNumericDataEntry.ModifyFlags(CAMSNumericEdit::AddDecimalAfterMaxWholeDigits, 0);

	UpdateData(FALSE);

	// Call the OnChange handlers
	OnChangeEditAlphanumericInvalidCharacters();
	OnChangeEditAlphanumericMaxCharacters();
	OnCheckNumericCannotBeNegative();
	OnCheckTime24HourFormat();
	OnChangeEditMaskedMask();
	OnChangeEditNumericLeftDigits();
	OnChangeEditNumericRightDigits();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CValidatingEditDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CValidatingEditDemoDlg::OnPaint() 
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
HCURSOR CValidatingEditDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CValidatingEditDemoDlg::OnChangeEditAlphanumericInvalidCharacters() 
{
	UpdateData();

	m_ctlEditAlphanumericDataEntry.SetInvalidCharacters(m_strEditAlphanumericInvalidCharacters);
	if (m_strEditAlphanumericInvalidCharacters.IsEmpty())
		m_ctlEditAlphanumericDataEntry.SetText("");
}

void CValidatingEditDemoDlg::OnChangeEditAlphanumericMaxCharacters() 
{
	if (::IsWindow(m_ctlEditNumericDataEntry.m_hWnd))
		UpdateData();

	m_ctlEditAlphanumericDataEntry.SetMaxCharacters(m_nEditAlphanumericMaxCharacters);
}

void CValidatingEditDemoDlg::OnCheckNumericCannotBeNegative() 
{
	UpdateData();
	m_ctlEditNumericDataEntry.AllowNegative(!m_bCheckNumericCannotBeNegative);
	m_ctlEditNumericDataEntry.SetFocus();
}

void CValidatingEditDemoDlg::OnCheckTime24HourFormat() 
{
	UpdateData();
	m_ctlEditTimeDataEntry.Show24HourFormat(!!m_bCheckTime24HourFormat);
	m_ctlEditTimeDataEntry.SetFocus();
}

void CValidatingEditDemoDlg::OnCheckTimeShowSeconds() 
{
	UpdateData();
	m_ctlEditTimeDataEntry.ShowSeconds(!!m_bCheckTimeShowSeconds);
	m_ctlEditTimeDataEntry.SetFocus();
}

void CValidatingEditDemoDlg::OnChangeEditMaskedMask() 
{
	UpdateData();
	m_ctlEditMaskedDataEntry.SetMask(m_strEditMaskedMask);
	if (m_strEditMaskedMask.IsEmpty())
		m_ctlEditMaskedDataEntry.SetText("");
}

void CValidatingEditDemoDlg::OnChangeEditCurrencyDataEntry() 
{
	m_dEditCurrencyAsDouble = m_ctlEditCurrencyDataEntry.GetDouble();
	UpdateData(FALSE);
}

void CValidatingEditDemoDlg::OnChangeEditNumericDataEntry() 
{
	m_dEditNumericAsDouble = m_ctlEditNumericDataEntry.GetDouble();
	UpdateData(FALSE);
}

void CValidatingEditDemoDlg::OnChangeEditNumericLeftDigits() 
{
	if (::IsWindow(m_ctlEditNumericDataEntry.m_hWnd))
		UpdateData();

	m_ctlEditNumericDataEntry.SetMaxWholeDigits(m_nEditNumericLeftDigits);
}

void CValidatingEditDemoDlg::OnChangeEditNumericRightDigits() 
{
	if (::IsWindow(m_ctlEditNumericDataEntry.m_hWnd))
		UpdateData();

	m_ctlEditNumericDataEntry.SetMaxDecimalPlaces(m_nEditNumericRightDigits);
}

void CValidatingEditDemoDlg::OnChangeDateRange(NMHDR*, LRESULT* pResult)
{
	*pResult = 0;

	COleDateTime dtMin, dtMax;
	m_dateMin.GetTime(dtMin);
	m_dateMax.GetTime(dtMax);

	m_ctlEditDateDataEntry.SetRange(dtMin, dtMax);
}
