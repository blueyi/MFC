// MainFrm.cpp : implementation of the CMainFrame class
//
// 1998 Kirk Stowell ( kstowel@sprynet.com )
// www.geocities.com/SiliconValley/Haven/8230/index.html
//
// You are free to use, modify and distribute this source, as long as
// there is no charge, and this HEADER stays intact. This source is
// supplied "AS-IS", and without WARRANTY OF ANY KIND, and the user
// holds the author blameless for any or all problems that may arise
// from the use of this code.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "demo_ui_explorer.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////
// CAnimate : implementation of the CAnimate class
//

IMPLEMENT_DYNAMIC(CAnimate, CAnimateCtrl)

BEGIN_MESSAGE_MAP(CAnimate, CAnimateCtrl)
	//{{AFX_MSG_MAP(CAnimate)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int CAnimate::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CAnimateCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	Open( IDR_AVI ); // open the avi resource.
	Play( 0, -1,-1 );// play avi resource.
	
	return 0;
}

////////////////////////////////////////////////////////////////
// CCombo : implementation of the CCombo class
//

IMPLEMENT_DYNAMIC(CCombo, CComboBox)

BEGIN_MESSAGE_MAP(CCombo, CComboBox)
	//{{AFX_MSG_MAP(CCombo)
	ON_WM_CREATE()
	ON_CONTROL_REFLECT(CBN_DROPDOWN, OnDropDown)
	ON_CONTROL_REFLECT(CBN_SELENDOK, OnSelendok)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////
// Note that I have to resize the window when I get CBN_DROPDOWN
//

void CCombo::OnDropDown()
{
	// use same width but taller height
	CRect rc;
	GetWindowRect(&rc);
	SetWindowPos(NULL,0,0,rc.Width(),200,SWP_NOMOVE|SWP_NOACTIVATE);
}

int CCombo::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CString m_csText("http://www.geocities.com/SiliconValley/Haven/8230/index.html");

	// Add items to control
	for( int i = 0; i < 5; i++ ) {
		AddString( m_csText );
	}

	SetCurSel(0);

	m_font.CreatePointFont( 80, _T("MS Sans Serif") );
	SetFont(&m_font);
	
	return 0;
}

void CCombo::OnSelendok() 
{
	CString cs; cs.Format("You selected item %d",GetCurSel());
	AfxMessageBox(cs);
}

////////////////////////////////////////////////////////////////
// CRebar : implementation of the CRebar class
//

// This is the virtual function you have to override to add bands
BOOL CRebar::OnCreateBands()
{
	// Load the background bitmap. Thanks to Christian Skovdal Andersen
	// for pointing this out!
	m_hBmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_BITMAP1),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);
	ASSERT(m_hBmp);
	m_rbbi.hbmBack = m_hBmp;

	if( !CreateToolbarBand()) {
		return -1;
	}
	if( !CreateAviCtrlBand()) {
		return -1;
	}
	if( !CreateIE4TbarBand()) {
		return -1;
	}
	if( !CreateComboBxBand()) {
		return -1;
	}

	return 0; // OK
}

BOOL CRebar::CreateToolbarBand()
{
	// Create toolbar
	if (!m_wndToolBar.Create( this,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|
		CBRS_TOOLTIPS|CBRS_SIZE_DYNAMIC|CBRS_FLYBY|CBRS_ORIENT_HORZ ) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return FALSE;
	}

	// Create and initialize image list used for child toolbar
	m_list1.Create( IDB_BITMAP2, 16, 1, RGB(192,192,192));

	// Create and initialize hot image list used for child toolbar
	m_list2.Create( IDB_BITMAP3, 16, 1, RGB(192,192,192));

	// Add image lists to toolbar
	m_wndToolBar.SetImageList(&m_list1, TB_SETHOTIMAGELIST );
	m_wndToolBar.SetImageList(&m_list2, TB_SETIMAGELIST );

	// Set the toolbar to draw no gripper( were using rebar gripper),
	// and style to transparent
	m_wndToolBar.DrawNoGripper();
	m_wndToolBar.ModifyStyle( 0, TBSTYLE_TRANSPARENT );

	// Add Rebar band
	m_rbbi.hwndChild	= m_wndToolBar;
	m_rbbi.cxMinChild	= 50;
	m_rbbi.cyMinChild	= 25;
	if (!InsertBand(-1, &m_rbbi))
		return FALSE;

	return TRUE;
}

BOOL CRebar::CreateAviCtrlBand()
{
	// Create animation control
	m_wndAvi.Create( WS_VISIBLE|WS_CHILD|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
		CRect(0,0,0,0), this, 1001 );

	// Add Rebar band
	m_rbbi.hwndChild	= m_wndAvi;
	m_rbbi.cxMinChild	= 47;
	m_rbbi.cyMinChild	= 25;
	m_rbbi.clrBack		= RGB(0,0,0);
	m_rbbi.hbmBack      = NULL;

	m_rbbi.fStyle     = RBBS_FIXEDBMP|RBBS_FIXEDSIZE;
	if (!InsertBand(-1, &m_rbbi))
		return FALSE;

	return TRUE;
}

BOOL CRebar::CreateIE4TbarBand()
{
	LPSTR lpText[] = {"Back","Forward","Stop","Refresh","Home","Search","Favorites","History","Channels","Fullscreen","Mail","Print","Edit"};

	// Create the toolbar
	if (!m_wndIE4tBar.Create( this,WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|
		CBRS_TOOLTIPS|CBRS_SIZE_DYNAMIC|CBRS_FLYBY|CBRS_ORIENT_HORZ ) ||
		!m_wndIE4tBar.LoadToolBar(IDR_IE4))
	{
		TRACE0("Failed to create toolbar\n");
		return FALSE;      // fail to create
	}

	// Create and initialize image list used for child toolbar
	CBitmap bmp1;
	bmp1.LoadBitmap( IDB_BITMAP4 );
	m_list3.Create( 21,20,ILC_COLORDDB|ILC_MASK,13,1);
	m_list3.Add( &bmp1, RGB(192,192,192) );

	// Create and initialize hot image list used for child toolbar
	CBitmap bmp2;
	bmp2.LoadBitmap( IDB_BITMAP5 );
	m_list4.Create( 21,20,ILC_COLORDDB|ILC_MASK,13,1);
	m_list4.Add( &bmp2, RGB(192,192,192) );

	// Add image lists to toolbar
	m_wndIE4tBar.SetImageList(&m_list3, TB_SETHOTIMAGELIST );
	m_wndIE4tBar.SetImageList(&m_list4, TB_SETIMAGELIST );
	
	// Set the toolbar to draw no gripper( were using rebar gripper),
	// and style to transparent and autosize
	m_wndIE4tBar.DrawNoGripper();
	m_wndIE4tBar.ModifyStyle( 0, TBSTYLE_TRANSPARENT|TBSTYLE_AUTOSIZE);

	// Set the back and forward buttons to have a drop list.
    m_wndIE4tBar.SetButtonDropDown( IDC_STATIC_BACK );
    m_wndIE4tBar.SetButtonDropDown( IDC_STATIC_FORWARD );

	// Add text to toolbar buttons.
	for( int i = IDC_STATIC_BACK, x = 0; i <= IDC_STATIC_EDIT; i++, x++ ) {
		m_wndIE4tBar.SetButtonText(
			m_wndIE4tBar.CommandToIndex( i ), lpText[x] );
	}

	// Add Rebar band
	m_rbbi.hbmBack		= m_hBmp;
	m_rbbi.hwndChild	= m_wndIE4tBar;
	m_rbbi.cxMinChild	= 50;
	m_rbbi.cyMinChild	= 40;
	m_rbbi.fStyle     = RBBS_FIXEDBMP|RBBS_BREAK;
	if (!InsertBand(-1, &m_rbbi))
		return FALSE;

	return TRUE;
}

BOOL CRebar::CreateComboBxBand()
{
	// Create combo box
	m_wndCombo.Create(WS_VISIBLE|WS_CHILD|WS_VSCROLL|CBS_DROPDOWNLIST|
		WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CRect(0,0,0,0), this, 1001);

	// Band 3: Add combo box band.
	m_rbbi.hwndChild	= m_wndCombo;
	m_rbbi.cxMinChild	= 150;
	m_rbbi.cyMinChild	= 25;
	m_rbbi.fStyle     = RBBS_FIXEDBMP|RBBS_BREAK;
	m_rbbi.fMask     |= RBBIM_TEXT;
	m_rbbi.lpText     = _T("Address:");
	if (!InsertBand(-1, &m_rbbi))
		return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(IDC_STATIC_BACK, OnStatic)
	ON_COMMAND(IDC_STATIC_CHANNELS, OnStatic)
	ON_COMMAND(IDC_STATIC_EDIT, OnStatic)
	ON_COMMAND(IDC_STATIC_FAVORITES, OnStatic)
	ON_COMMAND(IDC_STATIC_FORWARD, OnStatic)
	ON_COMMAND(IDC_STATIC_FULLSCREEN, OnStatic)
	ON_COMMAND(IDC_STATIC_HISTORY, OnStatic)
	ON_COMMAND(IDC_STATIC_HOME, OnStatic)
	ON_COMMAND(IDC_STATIC_MAIL, OnStatic)
	ON_COMMAND(IDC_STATIC_PRINT, OnStatic)
	ON_COMMAND(IDC_STATIC_REFRESH, OnStatic)
	ON_COMMAND(IDC_STATIC_SEARCH, OnStatic)
	ON_COMMAND(IDC_STATIC_STOP, OnStatic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Create rebar control
	if (!m_wndRebar.Create(this,
		WS_CHILD|WS_VISIBLE|WS_BORDER|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|
			RBS_TOOLTIPS|RBS_BANDBORDERS|RBS_VARHEIGHT))
	{
		TRACE0("Failed to create cool bar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// Install cool menus.
	m_menuManager.Install((CFrameWnd*)this);
	m_menuManager.LoadToolbar(IDR_MAINFRAME);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

// dummy command that IE4 style toolbar uses.
void CMainFrame::OnStatic()
{
}

