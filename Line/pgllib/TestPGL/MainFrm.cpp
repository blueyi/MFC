// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "testpgl.h"

#include "MainFrm.h"


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
	ON_COMMAND(ID_GRAPH_GENERATEGRAPH, OnGraphGenerategraph)
	ON_COMMAND(ID_GRAPH_SHOW, OnGraphShow)
	ON_COMMAND(ID_TEST_CHANGEMENU, OnTestChangemenu)
	ON_COMMAND(ID_TEST_STARTANIMATION, OnTestStartanimation)
	ON_COMMAND(ID_TEST_STOPANIMATION, OnTestStopanimation)
	ON_COMMAND(ID_EXAMPLES_SIMPLELINE, OnExamplesSimpleline)
	ON_COMMAND(ID_EXAMPLES_SIMPLELINEWITHLEVELOFDETAIL, OnExamplesSimplelinewithlevelofdetail)
	ON_COMMAND(ID_EXAMPLES_CUSTOMIZINGTHEAXIS, OnExamplesCustomizingtheaxis)
	ON_COMMAND(ID_EXAMPLES_SUBPLOTTING, OnExamplesSubplotting)
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
	CoInitialize(NULL);
}

CMainFrame::~CMainFrame()
{
	CoUninitialize();
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




void CMainFrame::OnGraphGenerategraph() 
{
	// setting graph
	CPGLGraph* pGraph = ((CTestpglApp*)AfxGetApp())->GenerateGraph();
	pGraph->ZoomAll(TRUE);
   ((CPGLGraphView*)GetActiveView())->SetGraph(pGraph );

	GetActiveView()->InvalidateRect(NULL,FALSE);
}

void CMainFrame::OnGraphShow() 
{
	CPGLGraph* pGraph = ((CTestpglApp*)AfxGetApp())->GenerateGraph();
	pGraph->ZoomAll(TRUE);

	CPGLGraphBitDlg graphdlg(this, pGraph);

	graphdlg.DoModal();
}

void CMainFrame::OnTestChangemenu() 
{
	CPGLGraphView* pGraphView = (CPGLGraphView*)GetActiveView();

	CMenu* pNewMenu = pGraphView->LoadMenu();

	// Remove and destroy the old menu
	SetMenu(NULL);
	::DestroyMenu(m_hMenuDefault);

   // Add the new menu
   SetMenu(pNewMenu);

   // Assign default menu
   m_hMenuDefault = pNewMenu->GetSafeHmenu();  // or m_NewMenu.m_hMenu;
}

void CMainFrame::OnTestStartanimation() 
{

	CPGLGraphView* pGraphView = (CPGLGraphView*)GetActiveView();
	CPGLGraph* pGraph = pGraphView->GetGraph();
	if (!pGraph)
		return;
	
	// get pointer to line
	((CTestpglApp*)AfxGetApp())->SetIdleView(GetActiveView());
	((CTestpglApp*)AfxGetApp())->SetAnimatedLine(pGraph);
	InvalidateRect(NULL,FALSE);
}

void CMainFrame::OnTestStopanimation() 
{
	((CTestpglApp*)AfxGetApp())->SetIdleView(NULL);
	((CTestpglApp*)AfxGetApp())->SetAnimatedLine(NULL);
	InvalidateRect(NULL,FALSE);
}


void CMainFrame::GetExample1(CPGLRegion* pGraph)
{
	ASSERT_VALID(pGraph);
	// generate data
	int nPoints = 60;
	double* pX=new double[nPoints];
	double* pY=new double[nPoints];
	for (UINT i=0;i<nPoints;i++)
	{
		pX[i]=i;
		pY[i]=sin(i/(double)nPoints*2*3.14)*1.1;
	}

	//Create a 2D line:
	CPGLLine2D* pLine = new CPGLLine2D();

	/*Attach the data to the line. PGL will handle the memory afterwards. That is, it will delete 
	the pointers of data at the object destruction. This means <code>pX,pY</code> MUST have been 
	allocated on the heap !
	*/
	pLine->SetDatas( nPoints /* number of points */, pX /* x(i) */, pY /* y(i) */);

	//(Optional)Change some properties of the line:
	pLine->SetLineWidth(2);

	//Add the line to the graph (note that an object can be added to only one graph):
	pGraph->AddObject(pLine);
}

void CMainFrame::GetExample2(CPGLRegion* pGraph)
{
	ASSERT_VALID(pGraph);
	// getting example 1
	GetExample1(pGraph);

	// generate data
	int nPoints = 60;
	double* pX=new double[nPoints];
	double* pY=new double[nPoints];
	for (UINT i=0;i<nPoints;i++)
	{
		pX[i]=i;
		pY[i]=sin(i/(double)nPoints*2*3.14)*1.1;
	}

	//Create a 2D line:
	CPGLLine2DLOD* pLineLOD = new CPGLLine2DLOD();


	pLineLOD->SetDatas( nPoints /* number of points */, pX /* x(i) */, pY /* y(i) */);
	// Setting tolerance
	pLineLOD->GetHull().ShrinkNorm(0.1,0.0);
	pLineLOD->SetLineWidth(2);

	// changing color
	pLineLOD->SetColor(0,0,1);
	// showing box at approximation points
	pLineLOD->SetPointType(PGL_POINT_SQUARE);
	// setting diameter of box
	pLineLOD->SetPointWidth(4);

	// adding line
	pGraph->AddObject(pLineLOD);

	// Setting title
	CString str;
	str.Format("Approximated curve: %d points", pLineLOD->GetHull().GetKeySize());
	pGraph->GetAxe()->SetTitle(str);
}

void CMainFrame::GetExample3(CPGLRegion* pGraph)
{
	ASSERT_VALID(pGraph);
	GetExample2(pGraph);

	//////////////////////////////////////////////////////////////////////////////////////
	///
	/// Customizing the axis:
	// getting pointer to the axis
	CPGLAxe2D* pAxis = pGraph->GetAxe();


	// Changing the title
	// Setting title
	CString str;
	str.Format("A modified title");
	pAxis->SetTitle(str);
	pAxis->GetTitle()->SetColor(0,0.5f,0);
	
	// setting grid off
	pAxis->SetShowGrid(1,FALSE);

	// show right label
	pAxis->GetRightLabel()->Show();
	pAxis->GetRightLabel()->SetString("This is the right label");
	// show numberinf
	pAxis->GetRightNumber()->Show();

	// changing number of ticks on the top axis
	pAxis->SetTopSecondTicksNb(5);

	// setting time label
	pAxis->SetTimeLabel(TRUE);
	pAxis->SetTimeLabelFormat(COleDateTime(2000,1,1,12,0,0) /* Time at zero. */, 
			COleDateTimeSpan(0,0,30,0)	/* Time per unit */,
			"%H:%M" /* String format */);
/*
	// rotating text so it does not override
	pAxis->GetBottomNumber()->SetAngle(-5);
	pAxis->GetBottomNumber()->SetAlign(PGL_TEXT_ALIGN_LEFT);

	This feature is not well supported yet.
*/

	// hiding bottom label
	pAxis->GetBottomLabel()->Show(FALSE);
	pAxis->GetLeftLabel()->Show(FALSE);
}

void CMainFrame::GetExample4(CPGLRegion* pGraph)
{
	ASSERT_VALID(pGraph);
	int m=2;
	int n=2;

	CPGLRegion* pChildRegion;
	
	// divide graph : waring this functions will delete all objects of the graph
	pGraph->Divide(m,n);

	// iterating over childs
	// adding first example at (0,0)
	pChildRegion = pGraph->GetChild(0*n+0);
	GetExample1(pChildRegion);

	// adding second example at (1,0)
	pChildRegion = pGraph->GetChild(1*n+0);
	GetExample2(pChildRegion);

	// adding third example at (0,1)
	pChildRegion = pGraph->GetChild(0*n+1);
	GetExample3(pChildRegion);

	// hiding fourth graph
	pChildRegion = pGraph->GetChild(1*n+1);
	pChildRegion->GetAxe()->Hide();

	// zooming all and recurse in childs
	pGraph->ZoomAll(TRUE);
}

void CMainFrame::OnExamplesSimpleline() 
{
	CPGLGraph* pGraph = new CPGLGraph;
	
	GetExample1(pGraph);

	// Tell PGL to zoom the line
	pGraph->ZoomAll();

	//Create a dialog box and display the plot:
	CPGLGraphBitDlg graphdlg(this, pGraph);
	graphdlg.DoModal();
}

void CMainFrame::OnExamplesSimplelinewithlevelofdetail() 
{
	CPGLGraph* pGraph = new CPGLGraph;
	GetExample2(pGraph);

	// Tell PGL to zoom the line
	pGraph->ZoomAll();

	//Create a dialog box and display the plot:
	CPGLGraphBitDlg graphdlg(this, pGraph);
	graphdlg.DoModal();
}

void CMainFrame::OnExamplesCustomizingtheaxis() 
{
	CPGLGraph* pGraph = new CPGLGraph;
	GetExample3(pGraph);

	// Tell PGL to zoom the line
	pGraph->ZoomAll();

	//Create a dialog box and display the plot:
	CPGLGraphBitDlg graphdlg(this, pGraph);
	graphdlg.DoModal();
}

void CMainFrame::OnExamplesSubplotting() 
{
	CPGLGraph* pGraph = new CPGLGraph;

	GetExample4(pGraph);

	// subplottting again
	CPGLRegion* pChildRegion = pGraph->GetChild(pGraph->GetNChilds()-1);
	ASSERT_VALID(pChildRegion);
	GetExample4(pChildRegion);

	// Tell PGL to zoom the line
	pGraph->ZoomAll();

	//Create a dialog box and display the plot:
	CPGLGraphBitDlg graphdlg(this, pGraph);
	graphdlg.DoModal();
}
