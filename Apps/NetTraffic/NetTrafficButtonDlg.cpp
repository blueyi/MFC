/*******************************************

	MFTrafficButton

	Version:	1.0
	Date:		31.10.2001
	Author:		Michael Fatzi
	Mail:		Michael_Fatzi@hotmail.com
	Copyright 1996-1997, Keith Rule

	You may freely use or modify this code provided this
	Copyright is included in all derived versions.
	
	History: 10.2001 Startup

	Handy little button control to display current 
	nettraffic as graph in a button.

********************************************/

// NetTrafficButtonDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "NetTrafficButton.h"
#include "NetTrafficButtonDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// Lets get a pointer to myself
	CNetTrafficButtonDlg* me;
// Remeber the selected interface number
	int SelectedInterface;
// A handy callback function...
	void CALLBACK interfaceHasChanged(int interfacenumber);


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

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
		// Keine Nachrichten-Handler
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetTrafficButtonDlg Dialogfield

CNetTrafficButtonDlg::CNetTrafficButtonDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNetTrafficButtonDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetTrafficButtonDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// Important to set!!!!
	me = this;
}

void CNetTrafficButtonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetTrafficButtonDlg)
	DDX_Control(pDX, IDC_BUTTON3, m_cOutgoing);
	DDX_Control(pDX, IDC_BUTTON2, m_cIncoming);
	DDX_Control(pDX, IDC_BUTTON1, m_cTotalTraffic);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNetTrafficButtonDlg, CDialog)
	//{{AFX_MSG_MAP(CNetTrafficButtonDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetTrafficButtonDlg Message handler

BOOL CNetTrafficButtonDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	

	// Not necessary but nice initalisation of the controls
	int SelectedInterface	= 0;	// Let us use the first found network connection
	UINT timerresolution	= 1000;	// Well, I think a refresh of the netstatus every second is enough
	UINT gridresolution		= 100;	// To fake the Taskmanager....

	m_cTotalTraffic.SetInterfaceNumber(SelectedInterface);							// Interface to monitor
	m_cTotalTraffic.SelectTrafficType(MFTrafficButton::Traffic_Total);				// In this case the total traffic is monitored
	m_cTotalTraffic.SetInterfaceNumberNotificationFunction(interfaceHasChanged);	// Set the callback handler to get informed...
	m_cTotalTraffic.SetUpdateSpeed(timerresolution, gridresolution);

	m_cOutgoing.SetInterfaceNumber(SelectedInterface);
	m_cOutgoing.SelectTrafficType(MFTrafficButton::Traffic_Outgoing);
	m_cOutgoing.SetInterfaceNumberNotificationFunction(interfaceHasChanged);
	m_cOutgoing.SetUpdateSpeed(timerresolution, gridresolution);

	m_cIncoming.SetInterfaceNumber(SelectedInterface);
	m_cIncoming.SelectTrafficType(MFTrafficButton::Traffic_Incoming);
	m_cIncoming.SetInterfaceNumberNotificationFunction(interfaceHasChanged);
	m_cIncoming.SetUpdateSpeed(timerresolution, gridresolution);

	
	return TRUE;  
}

void CNetTrafficButtonDlg::OnSysCommand(UINT nID, LPARAM lParam)
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


void CNetTrafficButtonDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CNetTrafficButtonDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


// 'So called' callback function for handling messages from the Buttons
// Here you can react on interface number changes
void CALLBACK interfaceHasChanged(int interfacenumber)
{
	SelectedInterface = interfacenumber;
	CString text;
	text.Format("NetTrafficButton using Interface: %d",SelectedInterface);
	me->SetWindowText(text);
}