// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "TreeList.h"

#include "MainFrm.h"

#include "Doc.h"
#include "ViewTree.h"
#include "ViewList.h"


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
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpFinder)
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
}

CMainFrame::~CMainFrame()
{
}

/////////////////////////////////////////////////////////////////////////////
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
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

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// fix the caption
	DWORD x = 0;
	x |= FWS_ADDTOTITLE;
	cs.style &= ~x;
	
	// size the window
	float fClientWidth = (float)0.75;// think of this as a percentage  of the screen that the
									// client will consume
	int hr = ::GetSystemMetrics( SM_CXSCREEN );
	int vr = ::GetSystemMetrics( SM_CYSCREEN );
	cs.cx = (int)((float)hr * fClientWidth);  // consume fClientWidth% of the x pixels
	cs.cy = (int)((float)vr * fClientWidth);  // consume fClientWidth% of the y pixels
	cs.x  = (hr - cs.cx)/2;  // centers the window
	cs.y  = (vr - cs.cy)/2;  // centers the window

	// call the base class and return
	BOOL b = CFrameWnd::PreCreateWindow(cs);
	return(b);
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
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, 
								CCreateContext* pContext) 
{
	// may want to read Q99562 and Q141334

	if (m_wndSplitter.CreateStatic(this,1,2)) 
	{
		CRect rect;
		GetClientRect(&rect);
		CSize sizeTree = rect.Size();

		sizeTree.cx = rect.Width()/4; 

		if (m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CTreeListView),
										sizeTree,pContext))
		{
			if (m_wndSplitter.CreateView(0,1,RUNTIME_CLASS(CMyListView),
										CSize(0,0),pContext))
			{
				return TRUE;	
			}
		}
	}

	return FALSE;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}






