// CNumSpinCtrlDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CNumSpinCtrlDemo.h"
#include "CNumSpinCtrlDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCNumSpinCtrlDemoDlg dialog

CCNumSpinCtrlDemoDlg::CCNumSpinCtrlDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCNumSpinCtrlDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCNumSpinCtrlDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCNumSpinCtrlDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCNumSpinCtrlDemoDlg)
	DDX_Control(pDX, IDC_SPIN_VALUE, m_spinValue);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCNumSpinCtrlDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CCNumSpinCtrlDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_TRIM_ZEROS, OnCheckTrimZeros)
	ON_EN_CHANGE(IDC_EDIT_FORMATTING_STRING, OnChangeEditFormattingString)
	ON_EN_CHANGE(IDC_EDIT_MAX_VAL, OnChangeEditMaxVal)
	ON_EN_CHANGE(IDC_EDIT_MIN_VAL, OnChangeEditMinVal)
	ON_EN_CHANGE(IDC_EDIT_NUM_DECIMALS, OnChangeEditNumDecimals)
	ON_EN_CHANGE(IDC_EDIT_POS, OnChangeEditPos)
	ON_BN_CLICKED(IDC_RADIO_FORMAT_STRING, OnRadioFormatString)
	ON_BN_CLICKED(IDC_RADIO_NUM_DECIMALS, OnRadioNumDecimals)
	ON_EN_CHANGE(IDC_EDIT_DELTA, OnChangeEditDelta)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCNumSpinCtrlDemoDlg message handlers

BOOL CCNumSpinCtrlDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_spinValue.SetDecimalPlaces (3);
	m_spinValue.SetTrimTrailingZeros (FALSE);
	m_spinValue.SetRangeAndDelta (0.1, 1.0, 0.05);
	m_spinValue.SetPos (0.5);

	SetDlgItemText (IDC_EDIT_MIN_VAL, "0.1");
	SetDlgItemText (IDC_EDIT_MAX_VAL, "1.0");
	SetDlgItemText (IDC_EDIT_DELTA, "0.05");
	SetDlgItemText (IDC_EDIT_POS, "0.5");
	SetDlgItemText (IDC_EDIT_FORMATTING_STRING, "%e");
	SetDlgItemText (IDC_EDIT_NUM_DECIMALS, "3");
	((CButton*)GetDlgItem (IDC_RADIO_FORMAT_STRING))->SetCheck (0);
	((CButton*)GetDlgItem (IDC_RADIO_NUM_DECIMALS))->SetCheck (1);
	((CButton*)GetDlgItem (IDC_CHECK_TRIM_ZEROS))->SetCheck (0);
	OnRadioNumDecimals();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCNumSpinCtrlDemoDlg::OnPaint() 
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
HCURSOR CCNumSpinCtrlDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCNumSpinCtrlDemoDlg::OnChangeEditFormattingString() 
{
	CString str;
	GetDlgItemText (IDC_EDIT_FORMATTING_STRING, str);
	m_spinValue.SetFormatString (str);
	UpdateValue();
}

void CCNumSpinCtrlDemoDlg::OnChangeEditMaxVal() 
{
	CString str;
	GetDlgItemText (IDC_EDIT_MAX_VAL, str);

	double lower, upper, delta;
	m_spinValue.GetRangeAndDelta (lower, upper, delta);

	upper = atof (str);
	if (upper > lower)
	{
		m_spinValue.SetRangeAndDelta (lower, upper, delta);
	}
}

void CCNumSpinCtrlDemoDlg::OnChangeEditMinVal() 
{
	CString str;
	GetDlgItemText (IDC_EDIT_MIN_VAL, str);
	
	double lower, upper, delta;
	m_spinValue.GetRangeAndDelta (lower, upper, delta);
	
	lower = atof (str);
	if (upper > lower)
	{
		m_spinValue.SetRangeAndDelta (lower, upper, delta);
	}
}

void CCNumSpinCtrlDemoDlg::OnChangeEditDelta() 
{
	CString str;
	GetDlgItemText (IDC_EDIT_DELTA, str);
	
	double lower, upper, delta;
	m_spinValue.GetRangeAndDelta (lower, upper, delta);
	
	delta = atof (str);
	if (delta != 0.0)
	{
		m_spinValue.SetRangeAndDelta (lower, upper, delta);
	}
}

void CCNumSpinCtrlDemoDlg::OnChangeEditPos() 
{
	CString str;
	GetDlgItemText (IDC_EDIT_POS, str);
	double pos = atof (str);
	m_spinValue.SetPos (pos);
}

void CCNumSpinCtrlDemoDlg::OnChangeEditNumDecimals() 
{
	CString str;
	GetDlgItemText (IDC_EDIT_NUM_DECIMALS, str);
	int num_decimals = atoi (str);
	m_spinValue.SetDecimalPlaces (num_decimals);
	m_spinValue.SetFormatString (NULL); // to override custom string
	UpdateValue();
}

void CCNumSpinCtrlDemoDlg::OnCheckTrimZeros() 
{
	int check = ((CButton*)GetDlgItem (IDC_CHECK_TRIM_ZEROS))->GetCheck ();
	m_spinValue.SetTrimTrailingZeros(check == 1);
	m_spinValue.SetFormatString (NULL); // to override custom string
	UpdateValue();
}

void CCNumSpinCtrlDemoDlg::OnRadioFormatString() 
{
	EnableFormatStringControls (TRUE);
	OnChangeEditFormattingString ();
}

void CCNumSpinCtrlDemoDlg::OnRadioNumDecimals() 
{
	EnableFormatStringControls (FALSE);
	OnChangeEditNumDecimals ();
	OnCheckTrimZeros ();
}

void CCNumSpinCtrlDemoDlg::EnableFormatStringControls(BOOL bEnable)
{
	GetDlgItem (IDC_EDIT_FORMATTING_STRING)->EnableWindow (bEnable);

	GetDlgItem (IDC_EDIT_NUM_DECIMALS)->EnableWindow (!bEnable);
	GetDlgItem (IDC_CHECK_TRIM_ZEROS)->EnableWindow (!bEnable);
}

void CCNumSpinCtrlDemoDlg::UpdateValue()
{
	m_spinValue.SetPos(m_spinValue.GetPos()); //update edit control
}
