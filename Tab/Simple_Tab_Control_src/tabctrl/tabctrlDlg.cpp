// tabctrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "tabctrl.h"
#include "tabctrlDlg.h"
#include ".\tabctrldlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtabctrlDlg dialog



CtabctrlDlg::CtabctrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CtabctrlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtabctrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TABV, m_ctrlTabV);
}

BEGIN_MESSAGE_MAP(CtabctrlDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_RP1, OnBnClickedButtonRp1)
	ON_BN_CLICKED(IDC_BUTTON_RP2, OnBnClickedButtonRp2)
	ON_BN_CLICKED(IDC_BUTTON_RP3, OnBnClickedButtonRp3)
END_MESSAGE_MAP()


// CtabctrlDlg message handlers

BOOL CtabctrlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_oPPOne.Create(IDD_PP_ONE); 
	m_oPPTwo.Create(IDD_PP_TWO); 
	m_oPPThree.Create(IDD_PP_THREE); 

	m_ctrlTabV.addNewPage("My Page 1",&m_oPPOne); 
	m_ctrlTabV.addNewPage("My Page 2",&m_oPPTwo); 
	m_ctrlTabV.addNewPage("My Page 3",&m_oPPThree); 

	m_ctrlTabV.setDefaultPage(0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CtabctrlDlg::OnPaint() 
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
HCURSOR CtabctrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CtabctrlDlg::OnBnClickedButtonRp1()
{
	// TODO: Add your control notification handler code here
	m_ctrlTabV.removePage(0);
}

void CtabctrlDlg::OnBnClickedButtonRp2()
{
	// TODO: Add your control notification handler code here
	m_ctrlTabV.removePage(1);
}

void CtabctrlDlg::OnBnClickedButtonRp3()
{
	// TODO: Add your control notification handler code here
	m_ctrlTabV.removePage(2);
}
