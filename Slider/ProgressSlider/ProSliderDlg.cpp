// ProSliderDlg.cpp : implementation file
//
//	See disclaimer.txt or ProSliderCtrl.h for copyright & usage issues
//  © Copyright 2004 Cem KARACA.


#include "stdafx.h"
#include "ProSlider.h"
#include "ProSliderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog 
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	srand((unsigned)time( NULL ) );
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CProSliderDlg dialog



CProSliderDlg::CProSliderDlg(CWnd* pParent /*=NULL*/)
: CDialog(CProSliderDlg::IDD, pParent),
m_TimerValue1(20),
m_TimerValue(40),
m_SliderPos(0),
m_ProgressPos(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProSliderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_sl1);
	DDX_Control(pDX, IDC_SLIDER2, m_sl2);
	DDX_Control(pDX, IDC_SLIDER3, m_ProSlider);
	DDX_Control(pDX, IDC_SLIDER4, m_VerProSlider);
	DDX_Control(pDX, IDC_STATIC1, m_Static1);
	DDX_Control(pDX, IDC_STATIC2, m_Static2);
	DDX_Control(pDX, IDC_BUTTON1, m_btnStart);
	DDX_Control(pDX, IDC_BUTTON2, m_btnStop);
	DDX_Control(pDX, IDC_EDIT1, m_EditTimer);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	DDX_Control(pDX, IDC_EDIT2, m_EditTimer1);
	DDX_Control(pDX, IDC_BUTTON3, m_btnStart1);
	DDX_Control(pDX, IDC_BUTTON4, m_btnStop1);
	DDX_Control(pDX, IDC_BUTTON5, m_bnBorders);
	DDX_Control(pDX, IDC_BUTTON6, m_bnFreeze);
}

BEGIN_MESSAGE_MAP(CProSliderDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
//	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON1, OnBnStart)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnStop)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT1, OnEnChangeEdit)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnStart1)
	ON_BN_CLICKED(IDC_BUTTON4, OnBnStop1)
	ON_EN_CHANGE(IDC_EDIT2, OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON5, OnBnBorders)
	ON_BN_CLICKED(IDC_BUTTON7, OnBnStepIt)
	ON_BN_CLICKED(IDC_BUTTON8, OnBnRandom)
	ON_BN_CLICKED(IDC_BUTTON6, OnBnFreeze)
END_MESSAGE_MAP()


// CProSliderDlg message handlers

BOOL CProSliderDlg::OnInitDialog()
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
	m_btnStop.EnableWindow(FALSE);
	m_btnStop1.EnableWindow(FALSE);
	// debug screen init
	CString lpszString;
	lpszString.Format("%d",this->m_TimerValue);
	m_EditTimer.SetWindowText(lpszString);
	lpszString.Format("%d",this->m_TimerValue1);
	m_EditTimer1.SetWindowText(lpszString);
	m_Progress.SetRange(0,1000);
	// control screen members
	m_sl1.SetRange(0,1000);
	m_sl1.SetPageSize(10);
	m_sl2.SetRange(0,1000);
	m_sl2.SetPageSize(10);
	// Pro Slider init
	this->m_ProSlider.SetRange(0,1000);		// Horizantal slider
	this->m_VerProSlider.SetRange(0,1000);	// Vertical slider
	// Pro Progress init
	m_ProSlider._SetRange(0,1000);			// slider ranges
	m_VerProSlider._SetRange(0,1000);
	m_ProSlider.SetTicFreq(10);				// not necessary

	m_sl1.SetFocus();			// use arrow keys to move sl1 when app inits
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CProSliderDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CProSliderDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CProSliderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Starts animation
void CProSliderDlg::OnBnStart()
{
	m_btnStop.EnableWindow();
	m_btnStart.EnableWindow(FALSE);
	SetTimer(WM_ANIM,m_TimerValue,NULL);
	m_SliderPos=0;
}

// stops the animation
void CProSliderDlg::OnBnStop()
{
	m_btnStop.EnableWindow(FALSE);
	m_btnStart.EnableWindow();
	this->KillTimer(WM_ANIM);
	m_SliderPos=0;
}


void CProSliderDlg::OnTimer(UINT nIDEvent)
{
	switch(nIDEvent)
	{
	case WM_ANIM:
		{
			m_sl1.SetPos(m_SliderPos+=5);
			int nMin,nMax;
			m_sl1.GetRange(nMin,nMax);
			if(m_SliderPos>nMax) this->OnBnStop();
		}
		break;
	case WM_ANIM1:
		{
			m_sl2.SetPos(m_ProgressPos+=5);
			int nMin,nMax;
			m_sl2.GetRange(nMin,nMax);
			if(m_ProgressPos>nMax) this->OnBnStop1();
		}
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

// 
BOOL CProSliderDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	CString lpszValue;
	NMHDR *pParam = reinterpret_cast<NMHDR*>(lParam);
	if(pParam->hwndFrom == m_sl1.m_hWnd)
	{
		int value = m_sl1.GetPos();
		m_ProSlider.SetPos(value);
		m_VerProSlider.SetPos(value);
		lpszValue.Format("%d",value);
		m_Static1.SetWindowText(lpszValue);
	}
	if(pParam->hwndFrom == m_sl2.m_hWnd)
	{
		int value = m_sl2.GetPos();
		m_Progress.SetPos(value);
		m_ProSlider._SetPos(value);
		m_VerProSlider._SetPos(value);
		lpszValue.Format("%d",value);
		m_Static2.SetWindowText(lpszValue);
	}
	return CDialog::OnNotify(wParam, lParam, pResult);
}

void CProSliderDlg::OnEnChangeEdit()
{
	CString rString;
	this->m_EditTimer.GetWindowText(rString);
	this->m_TimerValue = atoi(rString);
}

void CProSliderDlg::OnBnStart1()
{
	m_btnStop1.EnableWindow();
	m_btnStart1.EnableWindow(FALSE);
	SetTimer(WM_ANIM1,m_TimerValue1,NULL);
	m_ProgressPos=0;
}

void CProSliderDlg::OnBnStop1()
{
	m_btnStop1.EnableWindow(FALSE);
	m_btnStart1.EnableWindow();
	this->KillTimer(WM_ANIM1);
	m_ProgressPos=0;
}

void CProSliderDlg::OnEnChangeEdit2()
{
	CString rString;
	this->m_EditTimer1.GetWindowText(rString);
	this->m_TimerValue1 = atoi(rString);	
}

void CProSliderDlg::OnBnBorders()
{
	m_ProSlider._IsEnabled()?m_ProSlider._EnableBorders(FALSE):m_ProSlider._EnableBorders(TRUE);
	m_ProSlider._IsEnabled()?m_bnBorders.SetWindowText("No Borders"):m_bnBorders.SetWindowText("Borders");
	m_VerProSlider._IsEnabled()?m_VerProSlider._EnableBorders(FALSE):m_VerProSlider._EnableBorders(TRUE);
}

void CProSliderDlg::OnBnStepIt()
{
	m_Progress.StepIt();
	m_ProSlider._StepIt();
	m_VerProSlider._StepIt();
}

void CProSliderDlg::OnBnRandom()
{
	this->m_ProSlider._SetBkColor(RGB(BYTE(nexp(255.f)),BYTE(nexp(255.f)),BYTE(nexp(255.f))));
	this->m_ProSlider._SetThumbColor(RGB(BYTE(nexp(255.f)),BYTE(nexp(255.f)),BYTE(nexp(255.f))));
	this->m_ProSlider._SetChColor(RGB(BYTE(nexp(255.f)),BYTE(nexp(255.f)),BYTE(nexp(255.f))));
	this->m_VerProSlider._SetBkColor(RGB(BYTE(nexp(255.f)),BYTE(nexp(255.f)),BYTE(nexp(255.f))));	
}

double CProSliderDlg::nexp(double mean)	// For better colors :)
{
	int i;
	double res;
	i = rand();
	res=(double)i/RAND_MAX;
	return(-mean*log(res) );
}

void CProSliderDlg::OnBnFreeze()
{
	BOOL ret = m_ProSlider.Freeze();
	ret?m_bnFreeze.SetWindowText("Freeze"):m_bnFreeze.SetWindowText("Defreeze");
}
