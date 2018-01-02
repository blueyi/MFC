// TransparentControlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TransparentControl.h"
#include "TransparentControlDlg.h"
#include ".\transparentcontroldlg.h"

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
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	
END_MESSAGE_MAP()


// CTransparentControlDlg dialog



CTransparentControlDlg::CTransparentControlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTransparentControlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pMemDC = NULL;
	m_pOldBitmap = NULL;
	m_pBitmapMem = NULL;
	m_nBkResID = IDB_BITMAP_BK;

}

void CTransparentControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTransparentControlDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_MESSAGE( WM_TRANSPARENT_BK, OnTransaprentBk)
	ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
END_MESSAGE_MAP()


// CTransparentControlDlg message handlers

BOOL CTransparentControlDlg::OnInitDialog()
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

	m_static1.SubclassDlgItem( IDC_STATIC_1, this);
	m_Button1.SubclassDlgItem( IDC_BUTTON1, this);
	m_sliderctrl.SubclassDlgItem( IDC_SLIDER1, this);
	m_ButtonEx1.SubclassDlgItem( IDC_BUTTON3, this);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTransparentControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTransparentControlDlg::OnPaint() 
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
		//CDialog::OnPaint();
		CPaintDC dc(this);
		CRect rtClient;
		GetClientRect(&rtClient);

		if ( m_pMemDC )
		{
			dc.BitBlt( 0,0,rtClient.Width(), rtClient.Height(), m_pMemDC, 0,0, SRCCOPY);
		}
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTransparentControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CTransparentControlDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
	//return CDialog::OnEraseBkgnd(pDC);
}

LRESULT CTransparentControlDlg::OnTransaprentBk( WPARAM wParam, LPARAM lParam)
{
	HDC hdc = ( HDC)wParam;
	HWND hwnd = ( HWND)lParam;
    CTransparentHelper::OnTranparentControl( m_pMemDC->GetSafeHdc(), (WPARAM)hdc, (LPARAM)hwnd);
	return TRUE;
}

void CTransparentControlDlg::BuildBkDC()
{
	CBitmap bmpbk;
	bmpbk.LoadBitmap(  m_nBkResID);
	BITMAP bmpInfo;
	bmpbk.GetBitmap( &bmpInfo);

	CDC* pWndDC = GetDC();
	CDC memdc;
	memdc.CreateCompatibleDC( pWndDC);
	CBitmap* pOld = memdc.SelectObject( &bmpbk);


	CRect rtClient;
	GetClientRect(&rtClient);

	if ( m_pMemDC )
	{
		m_pMemDC->SelectObject( m_pOldBitmap);
		delete m_pBitmapMem;
		m_pBitmapMem = NULL;
		delete m_pMemDC;
		m_pMemDC = NULL;
	}
	
	if ( m_pMemDC == NULL )
	{
		m_pMemDC = new CDC;
		m_pMemDC->CreateCompatibleDC( pWndDC);

		m_pBitmapMem = new CBitmap;
		m_pBitmapMem->CreateCompatibleBitmap( pWndDC, rtClient.Width(), rtClient.Height());
		m_pOldBitmap = (CBitmap*)m_pMemDC->SelectObject( m_pBitmapMem);
	}

	m_pMemDC->StretchBlt( 0,0, rtClient.Width(), rtClient.Height(), &memdc, 0,0,bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
    memdc.SelectObject( pOld);
	ReleaseDC( pWndDC);

	//when the parent dialog's background is rebuild, notify the child which has an transparent tag.
	CTransparentHelper::NotifyTransparentChild( GetSafeHwnd());
}

void CTransparentControlDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

    BuildBkDC();
	Invalidate(FALSE);
	// TODO: Add your message handler code here
}

void CTransparentControlDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	CRect rt1;
	GetDlgItem( IDC_BUTTON1)->GetWindowRect( &rt1);
	ScreenToClient( &rt1);
	rt1.OffsetRect( 10,0);
	GetDlgItem( IDC_BUTTON1)->MoveWindow( &rt1, TRUE);
	GetDlgItem( IDC_BUTTON1)->Invalidate( TRUE);
}



void CTransparentControlDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	if ( m_nBkResID == IDB_BITMAP_BK1)
	{
       m_nBkResID = IDB_BITMAP_BK;
	}
	else
	{
	   m_nBkResID = IDB_BITMAP_BK1;
	}
    
	BuildBkDC();
	Invalidate(TRUE);
}
