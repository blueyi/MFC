#include "stdafx.h"
#include "ColorCtrls.h"
#include "ColorCtrlsDlg.h"
#include "RGB.h"

CColorCtrlsDlg::CColorCtrlsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CColorCtrlsDlg::IDD, pParent)
{

        //{{AFX_DATA_INIT(CColorCtrlsDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CColorCtrlsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorCtrlsDlg)
	DDX_Control(pDX, IDC_COLOR_STATIC, m_stcColor);
	DDX_Control(pDX, IDC_DISABLED_BUTTON, m_btnDisabled);
	DDX_Control(pDX, IDC_COLOR_EDIT, m_edtColor);
	DDX_Control(pDX, IDC_COLOR_COMBO, m_cbColor);
	DDX_Control(pDX, IDC_COLOR_BUTTON, m_btnColor);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CColorCtrlsDlg, CDialog)
	//{{AFX_MSG_MAP(CColorCtrlsDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DRAWITEM()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorCtrlsDlg message handlers

BOOL CColorCtrlsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_btnDisabled.SetDisabledColors(RGB_WHITE, RGB_BLACK);
	m_btnDisabled.SetColors(RGB_RED, RGB_BLACK, RGB_RED, RGB_WHITE);
	m_cbColor.SetColors(RGB_BLUE, RGB_GREEN, RGB_WHITE, RGB_RED);
	m_btnColor.SetColors(RGB_GREEN, RGB_BLACK, RGB_WHITE, RGB_RED);
	m_stcColor.SetColors(RGB_GREEN, RGB_BLUE, RGB_WHITE, RGB_RED);

	m_edtColor.SetColors(RGB_GREEN, RGB_BLUE, RGB_WHITE, RGB_RED);
	m_edtColor.SetDisabledColors(RGB_RED, RGB_BLACK);
	m_edtColor.SetWindowText("some text");

	m_cbColor.AddString("one");
	m_cbColor.AddString("two");
	m_cbColor.AddString("three");
	m_cbColor.SetCurSel(0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CColorCtrlsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
        CDialog::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CColorCtrlsDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	if (IsIconic())
	{

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

HCURSOR CColorCtrlsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

HBRUSH CColorCtrlsDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr;
	CBrush cbr;
	hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
/*	if( nCtlColor == CTLCOLOR_STATIC || nCtlColor == CTLCOLOR_MSGBOX )
        {
		cbr.CreateSolidBrush(RGB_RED);
		hbr = cbr;
		m_edtColor.OnCtlColor(pDC, pWnd, nCtlColor);
		//AfxMessageBox("onctlcolor in ccolorctrlsdlg");
	}
	else
	{

	}
	*/
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
