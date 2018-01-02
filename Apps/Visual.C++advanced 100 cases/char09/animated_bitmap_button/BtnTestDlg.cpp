// BtnTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BtnTest.h"
#include "CAniButton.h"
#include "BtnTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBtnTestDlg dialog

CBtnTestDlg::CBtnTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBtnTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBtnTestDlg)
	m_bGlobeEnabled = FALSE;
	m_bFreeEnabled = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBtnTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBtnTestDlg)
	DDX_Control(pDX, IDC_FREE, m_btnFree);
	DDX_Control(pDX, IDC_FLAG, m_btnFlag);
	DDX_Control(pDX, IDC_GLOBE3, m_btnGlobe3);
	DDX_Control(pDX, IDC_GLOBE2, m_btnGlobe2);
	DDX_Control(pDX, IDC_GLOBE1, m_btnGlobe1);
	DDX_Check(pDX, IDC_GLOBE_ENABLE, m_bGlobeEnabled);
	DDX_Check(pDX, IDC_FREE_ENABLE, m_bFreeEnabled);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBtnTestDlg, CDialog)
	//{{AFX_MSG_MAP(CBtnTestDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	ON_BN_CLICKED(IDC_GLOBE_ENABLE, OnGlobeEnable)
	ON_BN_CLICKED(IDC_GLOBE1, OnGlobe)
	ON_BN_CLICKED(IDC_GLOBE2, OnGlobe)
	ON_BN_CLICKED(IDC_GLOBE3, OnGlobe)
	ON_BN_CLICKED(IDC_FREE, OnGlobe)
	ON_BN_CLICKED(IDC_FLAG, OnGlobe)
	ON_BN_CLICKED(IDC_FREE_ENABLE, OnFreeEnable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBtnTestDlg message handlers

BOOL CBtnTestDlg::SetupAniButtons()
{

	m_btnGlobe1.AutoLoad(IDC_GLOBE1,         // Resource ID
                         this,               // Parent Window
                         IDB_GLOBE_BUTTON,   // Main Bitmap Resource ID
                         IDB_GLOBE_DISABLED, // Disabled Bitmap Resource ID
                         5,                  // Frames per Second
                         0,                  // Calculate Number of Frames
                         TRUE);              // Stretch To fit
	
	m_btnGlobe2.AutoLoad(IDC_GLOBE2,         // Resource ID
                         this,               // Parent Window
                         IDB_GLOBE_BUTTON,   // Main Bitmap Resource ID
                         IDB_GLOBE_DISABLED, // Disabled Bitmap Resource ID
                         10,                 // Frames per Second
                         0,                  // Calculate Number of Frames
                         FALSE,              // Do NOT Stretch to fit
                         TRUE,               // Replace Face Color
                         IDC_PLANE_CURSOR);  // Cursor Resourse ID
    	
	m_btnGlobe3.AutoLoad(IDC_GLOBE3,         // Resource ID
                         this,               // Parent Window
                         IDB_GLOBE_BUTTON,   // Main Bitmap Resource ID
                         IDB_GLOBE_DISABLED, // Disabled Bitmap Resource ID
                         5,                  // Frames per Second
                         0,                  // Calculate Number of Frames
                         FALSE,              // Do NOT Stretch to fit
                         FALSE);             // Do NOT Replace Face Color
	
    
    m_btnFree.AutoLoad(IDC_FREE, this, IDB_FREE_BUTTON,
                       IDB_FREE_DISABLED, 2);
	
    m_btnFlag.AutoLoad(IDC_FLAG, this, IDB_FLAG_BUTTON,
                       0, 5, 10, FALSE, TRUE, IDR_BALDIE);

    // I'm not in the mood for error checking...
    return TRUE;
}


BOOL CBtnTestDlg::OnInitDialog()
{
    // Initialize all of our CAniButtons before we
    // do anything else!
    SetupAniButtons();

	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_bGlobeEnabled = TRUE;
    m_btnFree.EnableWindow(FALSE);
    UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBtnTestDlg::OnPaint() 
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
HCURSOR CBtnTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBtnTestDlg::OnPaletteChanged(CWnd* pFocusWnd) 
{
    //
    // If this window is not the window getting focus,
    // redraw the AniButtons...
    //
    if(pFocusWnd != this)
    {
        m_btnGlobe1.Invalidate();
        m_btnGlobe2.Invalidate();
        m_btnGlobe3.Invalidate();
        m_btnFree.Invalidate();
        m_btnFlag.Invalidate();
    }
}

BOOL CBtnTestDlg::OnQueryNewPalette() 
{
    //
    // Since there are five buttons on this dialog,
    // we will need to choose one to be the Foreground palette.
    // This is done with the call to RealizePalette.
    // Then just redraw the other buttons.
    //
    m_btnGlobe1.RealizePalette();
    m_btnGlobe2.Invalidate();
    m_btnGlobe3.Invalidate();
    m_btnFree.Invalidate();
    m_btnFlag.Invalidate();
	
	return CDialog::OnQueryNewPalette();
}


void CBtnTestDlg::OnGlobeEnable() 
{
    UpdateData();
    m_btnGlobe1.EnableWindow(m_bGlobeEnabled);
    m_btnGlobe2.EnableWindow(m_bGlobeEnabled);
    m_btnGlobe3.EnableWindow(m_bGlobeEnabled);
}

void CBtnTestDlg::OnFreeEnable() 
{
    UpdateData();
    m_btnFree.EnableWindow(m_bFreeEnabled);
}

void CBtnTestDlg::OnGlobe() 
{
	AfxMessageBox("*Click*");
}

