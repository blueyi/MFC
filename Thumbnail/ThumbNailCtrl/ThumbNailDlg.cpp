// ThumbNailDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ThumbNail.h"
#include "ThumbNailDlg.h"

#include "thumbnailcontrol.h"

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
// CThumbNailDlg dialog

CThumbNailDlg::CThumbNailDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CThumbNailDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CThumbNailDlg)
	m_sMsg = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CThumbNailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CThumbNailDlg)
	DDX_Text(pDX, IDC_MSG, m_sMsg);
	//}}AFX_DATA_MAP
  DDX_Control(pDX, IDC_FRAME_THUMB, m_cThumbFrame);

}

BEGIN_MESSAGE_MAP(CThumbNailDlg, CDialog)
	//{{AFX_MSG_MAP(CThumbNailDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
  ON_REGISTERED_MESSAGE( UWM_ON_TNB_LCLICKED, OnTnbLClicked )
  ON_REGISTERED_MESSAGE( UWM_ON_TNB_RCLICKED, OnTnbRClicked )
  ON_WM_SIZE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThumbNailDlg message handlers

BOOL CThumbNailDlg::OnInitDialog()
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

  m_cThumbFrame.InitializeVariables( 50, 50 );

  //m_cThumbFrame.InitializeVariables( 160, 120 );

  m_cThumbFrame.Add( "fish.bmp" );
  m_cThumbFrame.Add( "pinboard.bmp" );
  m_cThumbFrame.Add( "chess.bmp" );
  m_cThumbFrame.Add( "box.bmp" );
  m_cThumbFrame.Add( "fish.bmp" );
  m_cThumbFrame.Add( "pinboard.bmp" );
  m_cThumbFrame.Add( "chess.bmp" );
  m_cThumbFrame.Add( "box.bmp" );

  m_cThumbFrame.RecalButtonPos();
  m_cThumbFrame.RecalScrollBars();


  m_childDialog.Create(IDD_DIALOG1,this);
  m_childDialog.ShowWindow(SW_SHOW);

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CThumbNailDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CThumbNailDlg::OnPaint() 
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
HCURSOR CThumbNailDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//---------------------------------------------------------------------------
//*******************
//*  OnTnbLClicked  *
//*******************
// 
// SYNOPSIS     : 
// 
// DESCRIPTION  : [TODO]
// 
// INPUTS       : WPARAM wParam - 
//		            LPARAM lParam - Not used.
// 
// RETURNS      : 1 - failure, 0 - success
// 
// NOTE         : [TODO]
// 
// TODO         : [TODO]
// 
LRESULT CThumbNailDlg::OnTnbLClicked( WPARAM wParam, LPARAM /* lParam  */ )
  {
  CThumbnailButton *pBtn = (CThumbnailButton*) wParam;

  m_cThumbFrame.UpdateSelected(pBtn);
  m_cThumbFrame.Invalidate();

  if( ::IsWindow(pBtn->m_hWnd) )
    {
    m_sMsg = pBtn->GetFullpath();
    UpdateData( FALSE );

    return 0;
    }

  return 1;
  }


LRESULT CThumbNailDlg::OnTnbRClicked( WPARAM wParam, LPARAM /* lParam */ )
  {
  CThumbnailButton *pBtn = (CThumbnailButton*) wParam;
  if( ::IsWindow(pBtn->m_hWnd) )
    {

		//******************************************************************
		//*  KNOWN ISSUE: ResetTrackFlag should immediately be called if	 *
    //*  the AfxMessageBox is called.                                  *
		//******************************************************************
    AfxMessageBox( pBtn->GetFullpath() );
    pBtn->ResetTrackFlag();

    m_sMsg = pBtn->GetFullpath();
    UpdateData( FALSE );

    return 0;
    }

  return 1;
  }


void CThumbNailDlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);
    
    // TODO: Add your message handler code here
    if(m_childDialog.GetSafeHwnd())
        m_childDialog.MoveWindow(0,0,cx,cy-300);
}
