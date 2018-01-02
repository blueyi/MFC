// AlphaBlendingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AlphaBlending.h"
#include "AlphaBlendingDlg.h"

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
// CAlphaBlendingDlg dialog

CAlphaBlendingDlg::CAlphaBlendingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAlphaBlendingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAlphaBlendingDlg)
	m_editAlpha = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAlphaBlendingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlphaBlendingDlg)
	DDX_Control(pDX, IDC_SLIDER1, m_TransSlider);
	DDX_Control(pDX, IDC_STATIC_CANVAS, m_stCanvas);
	DDX_Text(pDX, IDC_EDIT_ALPHA, m_editAlpha);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAlphaBlendingDlg, CDialog)
	//{{AFX_MSG_MAP(CAlphaBlendingDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_EN_CHANGE(IDC_EDIT_ALPHA, OnAlpha)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, OnReleasedcaptureSlider1)
	ON_BN_CLICKED(IDC_BUTTON_ANIMATE, OnButtonAnimate)
	ON_BN_CLICKED(IDC_BUTTON2, OnStop)
	ON_BN_CLICKED(IDC_BUTTON_MOVE, OnButtonMove)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlphaBlendingDlg message handlers

BOOL CAlphaBlendingDlg::OnInitDialog()
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
	
	// TODO: Add extra initialization here
	m_TransSlider.SetRange(0,100);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAlphaBlendingDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAlphaBlendingDlg::OnPaint() 
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
HCURSOR CAlphaBlendingDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAlphaBlendingDlg::OnButtonApply() 
{
	// TODO: Add your control notification handler code here
	m_stCanvas.mFade = 1;//fade out
	m_stCanvas.fadeEffect();		
}

void CAlphaBlendingDlg::OnAlpha() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData(TRUE);
	int val = atoi(m_editAlpha.GetBuffer(m_editAlpha.GetLength()));
	m_stCanvas.mAlpha = val;
	m_stCanvas.applyChange();
	// TODO: Add your control notification handler code here
	
}

void CAlphaBlendingDlg::OnReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here	
	m_stCanvas.mAlpha = m_TransSlider.GetPos();
	m_stCanvas.applyChange();
	*pResult = 0;
}

void CAlphaBlendingDlg::OnButtonAnimate() 
{
	// TODO: Add your control notification handler code here
	m_stCanvas.mFade = 0;//fade out
	m_stCanvas.fadeEffect();	
}

void CAlphaBlendingDlg::OnStop() 
{
	// TODO: Add your control notification handler code here
	m_stCanvas.mAlpha = 0;
	m_stCanvas.applyChange();
	m_stCanvas.fadeEffect(0);
}

void CAlphaBlendingDlg::OnButtonMove() 
{
	// TODO: Add your control notification handler code here
	m_stCanvas.mFade = 2;//move image
	m_stCanvas.fadeEffect();		
}
