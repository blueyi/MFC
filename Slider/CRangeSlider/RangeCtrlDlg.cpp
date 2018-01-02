// RangeCtrlDlg.cpp : implementation file//

#include "stdafx.h"
#include "RangeCtrl.h"
#include "RangeCtrlDlg.h"
#include <math.h>

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
// CRangeCtrlDlg dialog

CRangeCtrlDlg::CRangeCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRangeCtrlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRangeCtrlDlg)
	m_Min = 0.0;
	m_Max = 1.0;
	m_Left = 0.25;
	m_Right = 0.75;
	m_VisualMax = 0.6;
	m_VisualMin = 0.4;
	m_bVisualMinMax = TRUE;
	m_bInvertedMode = FALSE;
	m_bVerticalMode = FALSE;
	m_Feedback = TRUE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRangeCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRangeCtrlDlg)
	DDX_Control(pDX, IDC_FEEDBACK, c_Feedback);
	DDX_Control(pDX, IDC_VISUALMIN, c_VisualMin);
	DDX_Control(pDX, IDC_VISUALMAX, c_VisualMax);
	DDX_Control(pDX, IDC_VISUAL_MINMAX, c_VisualMinMax);
	DDX_Text(pDX, IDC_MIN, m_Min);
	DDX_Text(pDX, IDC_MAX, m_Max);
	DDX_Text(pDX, IDC_LEFT, m_Left);
	DDX_Text(pDX, IDC_RIGHT, m_Right);
	DDX_Text(pDX, IDC_VISUALMAX, m_VisualMax);
	DDX_Text(pDX, IDC_VISUALMIN, m_VisualMin);
	DDX_Check(pDX, IDC_VISUAL_MINMAX, m_bVisualMinMax);
	DDX_Check(pDX, IDC_INVERTEDMODE, m_bInvertedMode);
	DDX_Check(pDX, IDC_VERTICALMODE, m_bVerticalMode);
	DDX_Check(pDX, IDC_FEEDBACK, m_Feedback);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_RANGESLIDER, c_RangeSlider);
}

BEGIN_MESSAGE_MAP(CRangeCtrlDlg, CDialog)
	//{{AFX_MSG_MAP(CRangeCtrlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_KILLFOCUS(IDC_MAX, OnKillfocusMax)
	ON_EN_KILLFOCUS(IDC_MIN, OnKillfocusMin)
	ON_BN_CLICKED(IDC_VISUAL_MINMAX, OnVisualMinmax)
	ON_EN_KILLFOCUS(IDC_VISUALMAX, OnKillfocusVisualminmax)
	ON_BN_CLICKED(IDC_INVERTEDMODE, OnInvertedmode)
	ON_BN_CLICKED(IDC_VERTICALMODE, OnVerticalmode)
	ON_EN_KILLFOCUS(IDC_LEFT, OnKillfocusLeft)
	ON_EN_KILLFOCUS(IDC_RIGHT, OnKillfocusRight)
	ON_EN_KILLFOCUS(IDC_VISUALMIN, OnKillfocusVisualminmax)
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(RANGE_CHANGED, OnRangeChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRangeCtrlDlg message handlers

BOOL CRangeCtrlDlg::OnInitDialog()
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
	
	// CRect rc (10,10,300,30);
	// c_RangeSlider.Create(WS_CHILD |WS_VISIBLE|PBS_SMOOTH| WS_TABSTOP , rc, this, 2);
	c_RangeSlider.SetMinMax(m_Min,m_Max);
	c_RangeSlider.SetRange(m_Left,m_Right);
	c_RangeSlider.SetVisualMode(m_bVisualMinMax);
	c_RangeSlider.SetVisualMinMax(m_VisualMin, m_VisualMax);
	
	c_VisualMin.EnableWindow(m_bVisualMinMax);
	c_VisualMax.EnableWindow(m_bVisualMinMax);
	c_Feedback.EnableWindow(m_bVisualMinMax);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRangeCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRangeCtrlDlg::OnPaint() 
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
HCURSOR CRangeCtrlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

LRESULT CRangeCtrlDlg::OnRangeChange(WPARAM wParam, LPARAM /* lParam */) {
	UpdateData();
	c_RangeSlider.GetRange(m_Left, m_Right);
	if (m_Feedback) {
		double delta = fabs(m_Max - m_Min) / 10.0;

			// Keep VisualMin in the vicinity of m_Left.
		while (m_VisualMin - m_Left >= delta) {
			m_VisualMin -= delta;
		} 
		
		while (m_VisualMin - m_Left <= 0.0) 
			if (m_VisualMin + delta > m_VisualMax) {
				m_VisualMin = m_VisualMax;
				break;
			} else
				m_VisualMin += delta;

			// Keep VisualMax in the vicinity of m_Right.
		while (m_Right - m_VisualMax >= delta ) {
			m_VisualMax += delta;
		}

		while (m_Right - m_VisualMax < 0.0) 
			if (m_VisualMax - delta <= m_VisualMin) {
				m_VisualMax = m_VisualMin;
				break;
			} else 
				m_VisualMax -= delta;


		c_RangeSlider.SetVisualMinMax(m_VisualMin, m_VisualMax);
		c_RangeSlider.GetVisualMinMax(m_VisualMin, m_VisualMax);
	}
	UpdateData(FALSE);
	return static_cast<LRESULT>(0);
}

void CRangeCtrlDlg::OnKillfocusMax() 
{
	double oldMax = m_Max;
	UpdateData();

	if (oldMax != m_Max)
		c_RangeSlider.SetMinMax(m_Min, m_Max);
}

void CRangeCtrlDlg::OnKillfocusMin() 
{
	double oldMin = m_Min;
	UpdateData();

	if (oldMin != m_Min)
		c_RangeSlider.SetMinMax(m_Min, m_Max);
}

void CRangeCtrlDlg::OnVisualMinmax() 
{
	UpdateData();
	if (m_bVisualMinMax) {
		c_VisualMax.EnableWindow();
		c_VisualMin.EnableWindow();
		c_Feedback.EnableWindow();
		c_RangeSlider.SetVisualMode();
	} else { 
		c_VisualMax.EnableWindow(FALSE);
		c_VisualMin.EnableWindow(FALSE);
		c_Feedback.EnableWindow(FALSE);
		c_RangeSlider.SetVisualMode(FALSE);
	}
}

void CRangeCtrlDlg::OnKillfocusVisualminmax() 
{
	UpdateData();
	c_RangeSlider.SetVisualMinMax(m_VisualMin, m_VisualMax);
}


void CRangeCtrlDlg::OnInvertedmode() 
{
	UpdateData();
	c_RangeSlider.SetInvertedMode(m_bInvertedMode);
}

void CRangeCtrlDlg::OnVerticalmode() 
{
	static CRect oldRect (0,0,0,0);

	if (oldRect.IsRectNull()) {
		c_RangeSlider.GetWindowRect(&oldRect);
		ScreenToClient(&oldRect);
	}

	UpdateData();
	if (m_bVerticalMode) {
		c_RangeSlider.SetWindowPos(NULL, 
			oldRect.top, oldRect.left, oldRect.Height(), oldRect.Width() * 5 / 8, SWP_NOZORDER | SWP_SHOWWINDOW);
		c_RangeSlider.SetVerticalMode();
		c_RangeSlider.Invalidate();
	} else {
		c_RangeSlider.SetWindowPos(NULL, 
			oldRect.top, oldRect.left, oldRect.Width(), oldRect.Height(), SWP_NOZORDER | SWP_SHOWWINDOW);
		c_RangeSlider.SetVerticalMode(FALSE);
		c_RangeSlider.Invalidate();
	}
}


void CRangeCtrlDlg::OnKillfocusLeft() 
{
	UpdateData();
	c_RangeSlider.SetRange(m_Left, m_Right);
}

void CRangeCtrlDlg::OnKillfocusRight() 
{
	UpdateData();
	c_RangeSlider.SetRange(m_Left, m_Right);
}
