// ToolTipZENDlg.cpp : implementation file
//
/*
Author:     Zarembo Maxim
Country:    Belarus
City:       Minsk
e-mail:     mzarembo@iba.by
WWW:        http://maxim.z.tripod.com/ 
ICQ:        64569598
*/


#include "stdafx.h"
#include "ToolTipZEN.h"
#include "ToolTipZENDlg.h"

#define IDC_BUTTON 6318233
CRect rect(0,0,90,30);

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolTipZENDlg dialog

CToolTipZENDlg::CToolTipZENDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CToolTipZENDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CToolTipZENDlg)
	m_x = 0;
	m_y = 0;
	m_text = _T("");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CToolTipZENDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolTipZENDlg)
	DDX_Text(pDX, IDC_EDIT1, m_x);
	DDX_Text(pDX, IDC_EDIT2, m_y);
	DDX_Text(pDX, IDC_EDIT3, m_text);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CToolTipZENDlg, CDialog)
	//{{AFX_MSG_MAP(CToolTipZENDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON, OnButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolTipZENDlg message handlers

BOOL CToolTipZENDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	bToolTip=true;
	m_but.Create("ToolTipOn",BS_CENTER|WS_CHILD|WS_VISIBLE|BS_FLAT|WS_EX_CLIENTEDGE|WS_EX_STATICEDGE,rect,this,IDC_BUTTON);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CToolTipZENDlg::OnPaint() 
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

HCURSOR CToolTipZENDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CToolTipZENDlg::OnButton() 
{
	UpdateData(true);

	if (m_text.GetLength()<1) 
	{		
		m_text="Programm by Zarembo Maxim.";
	}

	if (bToolTip)
	{
		unsigned int uid = 0;       // for ti initialization

		// CREATE A TOOLTIP WINDOW
		hwndTT = CreateWindowEx(WS_EX_TOPMOST,
								TOOLTIPS_CLASS,
								NULL,
								TTS_NOPREFIX | TTS_ALWAYSTIP,		
								CW_USEDEFAULT,
								CW_USEDEFAULT,
								CW_USEDEFAULT,
								CW_USEDEFAULT,
								NULL,
								NULL,
								NULL,
								NULL
							   );

		// INITIALIZE MEMBERS OF THE TOOLINFO STRUCTURE
		ti.cbSize = sizeof(TOOLINFO);
		ti.uFlags = TTF_TRACK;
		ti.hwnd = NULL;
		ti.hinst = NULL;
		ti.uId = uid;
		ti.lpszText = (LPSTR)(LPCSTR) m_text;		
        // ToolTip control will cover the whole window
		ti.rect.left = 0;
		ti.rect.top = 0;
		ti.rect.right = 0;
		ti.rect.bottom = 0;

		// SEND AN ADDTOOL MESSAGE TO THE TOOLTIP CONTROL WINDOW
		::SendMessage(hwndTT, TTM_ADDTOOL, 0, (LPARAM) (LPTOOLINFO) &ti);

		::SendMessage(hwndTT, TTM_TRACKPOSITION, 0, (LPARAM)(DWORD) MAKELONG(m_x, m_y));
		::SendMessage(hwndTT, TTM_TRACKACTIVATE, true, (LPARAM)(LPTOOLINFO) &ti);

		m_but.DestroyWindow();
		m_but.Create("ToolTipOff",BS_CENTER|WS_CHILD|WS_VISIBLE|BS_FLAT|WS_EX_CLIENTEDGE|WS_EX_STATICEDGE,rect,this,IDC_BUTTON);
		bToolTip=false;
	}
	else
	{
		::SendMessage(hwndTT, TTM_TRACKACTIVATE, false, (LPARAM)(LPTOOLINFO) &ti);
		m_but.DestroyWindow();
		m_but.Create("ToolTipOn",BS_CENTER|WS_CHILD|WS_VISIBLE|BS_FLAT|WS_EX_CLIENTEDGE|WS_EX_STATICEDGE,rect,this,IDC_BUTTON);
		bToolTip=true;
	}
}
