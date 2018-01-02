// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ExToolBar.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateFileNew)
	ON_COMMAND(ID_SHOWTEXT, OnShowtext)
	ON_UPDATE_COMMAND_UI(ID_SHOWTEXT, OnUpdateShowtext)
	ON_COMMAND(ID_ICONMODE, OnIconmode)
	ON_UPDATE_COMMAND_UI(ID_ICONMODE, OnUpdateIconmode)
	ON_WM_PAINT()
	ON_WM_SETTINGCHANGE()
	ON_WM_SYSCOLORCHANGE()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	//ON_COMMAND(ID_APP, OnApp)
	ON_COMMAND(ID_FILETYPE, OnFiletype)
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
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_stdToolBar.Create(this) ||
		!m_stdToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

    m_stdToolBar.SetBitmap( IBD_SM,         COOBmpToolBar::SmallHot,         RGB( 30, 179, 223 ) );
    m_stdToolBar.SetBitmap( IDB_SM_BW,      COOBmpToolBar::SmallStandard,   RGB( 30, 179, 223 ) );
    m_stdToolBar.SetBitmap( IDB_SM_DB,      COOBmpToolBar::SmallDisable,     RGB( 172, 172, 172 ) );
    m_stdToolBar.SetBitmap( IDB_LG,         COOBmpToolBar::LargeHot,         RGB( 33, 231, 222 ) );
    m_stdToolBar.SetBitmap( IDB_LG_BW,      COOBmpToolBar::LargeStandard,   RGB( 33, 231, 222 ) );
    m_stdToolBar.SetBitmap( IDB_LG_DB,      COOBmpToolBar::LargeDisable,     RGB( 170, 170, 170 ) );
    m_stdToolBar.SetBitmap( IDB_SM_16,      COOBmpToolBar::SmallHot,         RGB( 0, 255, 255 ), false );
    m_stdToolBar.SetBitmap( IDB_SM_BW_16,   COOBmpToolBar::SmallStandard,   RGB( 0, 255, 255 ), false );
    m_stdToolBar.SetBitmap( IDB_SM_DB_16,   COOBmpToolBar::SmallDisable,     RGB( 192, 192, 192 ), false );
    m_stdToolBar.SetBitmap( IDB_LG_16,      COOBmpToolBar::LargeHot,         RGB( 0, 255, 255 ), false );
    m_stdToolBar.SetBitmap( IDB_LG_BW_16,   COOBmpToolBar::LargeStandard,   RGB( 0, 255, 255 ), false );
    m_stdToolBar.SetBitmap( IDB_LG_DB_16,   COOBmpToolBar::LargeDisable,     RGB( 192, 192, 192 ), false );
    m_stdToolBar.InitImageList();

    // set button to dropdown list
    m_stdToolBar.SetButtonDropDown( ID_FILE_OPEN );
    m_stdToolBar.SetButtonDropDown( ID_FILE_SAVE );
    
    if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!m_IconToolBar.Create(this) ||
		!m_IconToolBar.LoadToolBar(IDR_ICONTOOLBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

    m_IconToolBar.SetIcon( IDR_MAINFRAME  );
    m_IconToolBar.SetIcon( IDR_EXTOOLTYPE );
    m_IconToolBar.InitImageList();

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_stdToolBar.SetBarStyle(m_stdToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_IconToolBar.SetBarStyle(m_stdToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_stdToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_IconToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_stdToolBar);
	DockControlBar(&m_IconToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnUpdateFileNew(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    //pCmdUI->SetCheck( TRUE );	
}

void CMainFrame::OnShowtext() 
{
	// TODO: Add your command handler code here
	m_stdToolBar.SetTextMode( !m_stdToolBar.GetTextMode() );
	m_IconToolBar.SetTextMode( m_stdToolBar.GetTextMode() );
}

void CMainFrame::OnUpdateShowtext(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    pCmdUI->SetCheck( m_stdToolBar.GetTextMode() );	
}

void CMainFrame::OnIconmode() 
{
    m_stdToolBar.SetIconMode( !m_stdToolBar.GetIconMode() );
    m_IconToolBar.SetIconMode( m_stdToolBar.GetIconMode() );
}

void CMainFrame::OnUpdateIconmode(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    pCmdUI->SetCheck( m_stdToolBar.GetIconMode() );	
	
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	
	// TODO: Add your message handler code here
    
	// Do not call CMDIFrameWnd::OnPaint() for painting messages

	
	return CMDIFrameWnd::OnCreateClient(lpcs, pContext);
}

void CMainFrame::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
    
	// Do not call CMDIFrameWnd::OnPaint() for painting messages

}

void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection) 
{
	CMDIFrameWnd::OnSettingChange(uFlags, lpszSection);
	
	// TODO: Add your message handler code here
	
}

void CMainFrame::OnSysColorChange() 
{
	CMDIFrameWnd::OnSysColorChange();
	
	// TODO: Add your message handler code here
	
}

void CMainFrame::OnEditCopy() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnEditCut() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnEditPaste() 
{
	// TODO: Add your command handler code here
	
}


void CMainFrame::OnApp() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnFiletype() 
{
	// TODO: Add your command handler code here
	
}
