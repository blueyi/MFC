// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ThumbViewer.h"

#include "MainFrm.h"
#include "ThumbViewerDoc.h"
#include "ThumbViewerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_DIRECTORY_BAR, OnViewDirectoryBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DIRECTORY_BAR, OnUpdateViewDirectoryBar)
	ON_COMMAND(ID_VIEW_PREVIEW_BAR, OnViewPreviewBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PREVIEW_BAR, OnUpdateViewPreviewBar)
	ON_WM_CLOSE()
	ON_COMMAND(ID_STOP_THREAD, OnStopThread)
	ON_UPDATE_COMMAND_UI(ID_STOP_THREAD, OnUpdateStopThread)
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
	m_bShowPreviewBar=m_bShowDirectoryBar=TRUE;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	if (!m_wndDirTreeBar.Create(_T("Directory"), this, CSize(300, 100),
				    TRUE , AFX_IDW_CONTROLBAR_FIRST + 33))
	{
		return -1;
		// fail to create
	}
	m_wndDirTreeBar.SetBarStyle(m_wndDirTreeBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_wndDirTreeBar.EnableDocking(CBRS_ALIGN_LEFT|CBRS_ALIGN_RIGHT);

	EnableDocking(CBRS_ALIGN_ANY);

#ifdef _SCB_REPLACE_MINIFRAME
    m_pFloatingFrameClass = RUNTIME_CLASS(CSCBMiniDockFrameWnd);
#endif

	if (!m_wndPreviewBar.Create(_T("Image Preview"), this, CSize(150, 500),
				    TRUE , AFX_IDW_CONTROLBAR_FIRST + 33))
	{
		return -1;
		// fail to create
	}
	m_wndPreviewBar.SetBarStyle(m_wndPreviewBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_wndPreviewBar.EnableDocking(CBRS_ALIGN_LEFT|CBRS_ALIGN_RIGHT);

	EnableDocking(CBRS_ALIGN_ANY);

#ifdef _SCB_REPLACE_MINIFRAME
    m_pFloatingFrameClass = RUNTIME_CLASS(CSCBMiniDockFrameWnd);
#endif

	
	DockControlBar(&m_wndDirTreeBar, AFX_IDW_DOCKBAR_LEFT);

	RecalcLayout();
	CRect rBar;
	m_wndDirTreeBar.GetWindowRect(rBar);
	rBar.OffsetRect(0, 1);
	
	DockControlBar(&m_wndPreviewBar, AFX_IDW_DOCKBAR_LEFT, rBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
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


void CMainFrame::OnViewDirectoryBar() 
{
	// TODO: Add your command handler code here
	if(m_bShowDirectoryBar)
	{
		::ShowWindow(m_wndDirTreeBar.m_hWnd,SW_HIDE);			
		DockControlBar(&m_wndDirTreeBar,AFX_IDW_DOCKBAR_LEFT);				
		m_bShowDirectoryBar=FALSE;

		RecalcLayout(TRUE);
	}
	else
	{
		::ShowWindow(m_wndDirTreeBar.m_hWnd,SW_SHOW);
		DockControlBar(&m_wndDirTreeBar,AFX_IDW_DOCKBAR_LEFT);
		RecalcLayout(TRUE);
		m_bShowDirectoryBar=TRUE;
	}
}

void CMainFrame::OnUpdateViewDirectoryBar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bShowDirectoryBar);
}

void CMainFrame::OnViewPreviewBar() 
{
	// TODO: Add your command handler code here
	if(m_bShowPreviewBar)
	{
		::ShowWindow(m_wndPreviewBar.m_hWnd,SW_HIDE);			
		DockControlBar(&m_wndPreviewBar,AFX_IDW_DOCKBAR_LEFT);				
		m_bShowPreviewBar=FALSE;

		RecalcLayout(TRUE);
	}
	else
	{
		::ShowWindow(m_wndPreviewBar.m_hWnd,SW_SHOW);
		DockControlBar(&m_wndPreviewBar,AFX_IDW_DOCKBAR_LEFT);
		RecalcLayout(TRUE);
		m_bShowPreviewBar=TRUE;
	}
}

void CMainFrame::OnUpdateViewPreviewBar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bShowPreviewBar);	
}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CThumbViewerView* pView=(CThumbViewerView*)GetActiveView();
	if(pView->IsRunning()==true)
		AfxMessageBox(_T("Please terminate thread before closing window"));
	else
		CFrameWnd::OnClose();
}

void CMainFrame::OnStopThread() 
{
	// TODO: Add your command handler code here
	CThumbViewerView* pView=(CThumbViewerView*)GetActiveView();
	pView->TerminateThread();
}

void CMainFrame::OnUpdateStopThread(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CThumbViewerView* pView=(CThumbViewerView*)GetActiveView();
	if(pView->IsRunning()==true)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}
