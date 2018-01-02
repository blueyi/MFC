// CxShadeButtonDemoDlg.cpp : implementation file
//
#include "stdafx.h"
#include "CxShadeButtonDemo.h"
#include "CxShadeButtonDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCxShadeButtonDemoDlg dialog
CCxShadeButtonDemoDlg::CCxShadeButtonDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCxShadeButtonDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCxShadeButtonDemoDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCxShadeButtonDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCxShadeButtonDemoDlg)
	DDX_Control(pDX, IDC_BUTTON13, m_btn13);
	DDX_Control(pDX, IDC_BUTTON12, m_btn12);
	DDX_Control(pDX, IDC_BUTTON11, m_btn11);
	DDX_Control(pDX, IDC_BUTTON9, m_btn9);
	DDX_Control(pDX, IDC_BUTTON8, m_btn8);
	DDX_Control(pDX, IDC_BUTTON6, m_btn6);
	DDX_Control(pDX, IDC_BUTTON7, m_btn7);
	DDX_Control(pDX, IDC_BUTTON5, m_btn5);
	DDX_Control(pDX, IDC_BUTTON4, m_btn4);
	DDX_Control(pDX, IDC_BUTTON3, m_btn3);
	DDX_Control(pDX, IDC_BUTTON2, m_btn2);
	DDX_Control(pDX, IDC_BUTTON10, m_btn10);
	DDX_Control(pDX, IDC_BUTTON1, m_btn1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCxShadeButtonDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CCxShadeButtonDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCxShadeButtonDemoDlg message handlers

BOOL CCxShadeButtonDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_btn1.SetToolTipText("Metal");
	m_btn2.SetToolTipText("Hard Bump");
	m_btn3.SetToolTipText("Soft Bump");
	m_btn4.SetToolTipText("Noise");
	m_btn5.SetToolTipText("V Bump");
	m_btn6.SetToolTipText("H Bump");
	m_btn7.SetToolTipText("V Shade");
	m_btn8.SetToolTipText("H Shade");
	m_btn9.SetToolTipText("Diagonal green");
	m_btn10.SetToolTipText("Diagonal red");
	
	m_btn1.SetShade(SHS_METAL);
	m_btn2.SetShade(SHS_HARDBUMP);
	m_btn3.SetShade(SHS_SOFTBUMP);
	m_btn4.SetShade(SHS_NOISE,33);
	m_btn5.SetShade(SHS_VBUMP,8,20,5,RGB(55,55,255));
	m_btn6.SetShade(SHS_HBUMP,8,20,5,RGB(55,55,255));
	m_btn7.SetShade(SHS_VSHADE,8,20,5,RGB(55,55,255));
	m_btn8.SetShade(SHS_HSHADE,8,20,5,RGB(55,55,255));
	m_btn9.SetShade(SHS_DIAGSHADE,8,10,5,RGB(55,255,55));
	m_btn10.SetShade(SHS_DIAGSHADE,8,10,5,RGB(255,55,55));

	m_btn9.SetTextColor(RGB(0,99,0));
	m_btn10.SetTextColor(RGB(99,0,0));

	m_btn11.SetShade(SHS_METAL);
	m_btn11.SetFlat(1);
	m_btn12.SetShade(SHS_METAL);
	m_btn12.SetFlat(1);
	m_btn12.SetIcon(IDI_ICON2);
	m_btn12.SetToolTipText("Ok");
	m_btn13.SetShade(SHS_METAL);
	m_btn13.SetFlat(1);
	m_btn13.SetIcon(IDI_ICON1,BS_RIGHT);
	m_btn13.SetTextAlign(BS_LEFT);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCxShadeButtonDemoDlg::OnPaint() 
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

HCURSOR CCxShadeButtonDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
