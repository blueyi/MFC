// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "GLDouglas.h"

#include "MainFrm.h"
#include "GLDouglasDoc.h"

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
	ON_COMMAND(ID_ANIMATION_START, OnAnimationStart)
	ON_COMMAND(ID_ANIMATION_STOP, OnAnimationStop)
	ON_UPDATE_COMMAND_UI(ID_ANIMATION_START, OnUpdateAnimationStart)
	ON_UPDATE_COMMAND_UI(ID_ANIMATION_STOP, OnUpdateAnimationStop)
	ON_COMMAND(ID_DATASAMPLE_LOADSAMPLE, OnDatasampleLoadsample)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

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
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndToolBarShrink.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarShrink.LoadToolBar(IDR_SHRINK))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	m_wndToolBarShrink.Create();
	m_wndToolBarShrink.SetMainFrame(this);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBarShrink.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	DockControlBarLeftOf(&m_wndToolBarShrink, &m_wndToolBar);

	return 0;
}

void CMainFrame::DockControlBarLeftOf(CToolBar *Bar, CToolBar *LeftOf)
{
	CRect rect;
	DWORD dw;
	UINT n;
	
	// get MFC to adjust the dimensions of all docked ToolBars
	// so that GetWindowRect will be accurate
	RecalcLayout(TRUE);
	
	LeftOf->GetWindowRect(&rect);
	rect.OffsetRect(1,0);
	dw=LeftOf->GetBarStyle();
	n = 0;
	n = (dw&CBRS_ALIGN_TOP) ? AFX_IDW_DOCKBAR_TOP : n;
	n = (dw&CBRS_ALIGN_BOTTOM && n==0) ? AFX_IDW_DOCKBAR_BOTTOM : n;
	n = (dw&CBRS_ALIGN_LEFT && n==0) ? AFX_IDW_DOCKBAR_LEFT : n;
	n = (dw&CBRS_ALIGN_RIGHT && n==0) ? AFX_IDW_DOCKBAR_RIGHT : n;
	
	// When we take the default parameters on rect, DockControlBar will dock
	// each Toolbar on a seperate line. By calculating a rectangle, we
	// are simulating a Toolbar being dragged to that location and docked.
	DockControlBar(Bar,n,&rect);
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


void CMainFrame::OnAnimationStart() 
{
	CGLDouglasApp* pApp = (CGLDouglasApp*)AfxGetApp();
	pApp->SetView( GetActiveView());
	CGLDouglasDoc* pDoc = (CGLDouglasDoc*)GetActiveDocument();
	pDoc->GetHull().ComputeBoundingBox();

	Invalidate(FALSE);
}

void CMainFrame::OnAnimationStop() 
{
	CGLDouglasApp* pApp = (CGLDouglasApp*)AfxGetApp();
	pApp->SetView( NULL);
	CGLDouglasDoc* pDoc = (CGLDouglasDoc*)GetActiveDocument();
	pDoc->GetHull().ComputeBoundingBox();

	Invalidate(FALSE);
}

void CMainFrame::OnUpdateAnimationStart(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( ((CGLDouglasApp*)AfxGetApp())->GetView() != NULL);
}

void CMainFrame::OnUpdateAnimationStop(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( ((CGLDouglasApp*)AfxGetApp())->GetView() == NULL);
}

void CMainFrame::OnDatasampleLoadsample() 
{
	using namespace std;
	using namespace hull;

	CFileDialog dlg(true);

	if( dlg.DoModal() != IDOK)
		return;

	CGLDouglasApp* pApp = (CGLDouglasApp*)AfxGetApp();
	pApp->SetView( NULL);

	CGLDouglasDoc* pDoc = (CGLDouglasDoc*)GetActiveDocument();
	CDPHullGL::Hull& dp=pDoc->GetHull().GetHull();

	CDPHullGL::Hull::PointContainer& pc = dp.GetPoints();
	list<CDPHullGL::Hull::PointContainer::value_type> lPoints;
	CDPHullGL::Hull::PointContainer::value_type p;

	FILE * fp = NULL;
	
	TCHAR szLine[ 50 ] = "";
	
	fp = fopen( dlg.GetPathName(), _T("rt") );
	
	pc.clear();
	while( fgets( szLine, sizeof( szLine ), fp ) )
	{
		double dLat = 0, dLon= 0; 
		
		int t = _stscanf( szLine,
			_T("%lf %lf"),&dLat,&dLon );
		
		if ( t == 2 )
		{
			p.x=dLat; p.y=dLon;
			lPoints.push_back(p);
		}
	} 
	
	fclose( fp );
	
	pc.resize( lPoints.size());
	UINT i=0;
	while (!lPoints.empty())
	{
		pc[i++]=lPoints.front();
		lPoints.pop_front();
	}
	

	// discard doubles...
	pDoc->GetHull().GetHull().DiscardDoublePoints();

	pDoc->GetHull().GetHull().ComputeBoundingBox();

	InvalidateRect(NULL,FALSE);
}
