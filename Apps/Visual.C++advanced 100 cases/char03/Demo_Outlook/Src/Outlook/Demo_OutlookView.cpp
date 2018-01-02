// Demo_OutlookView.cpp : implementation of the CDemo_OutlookView class
//

#include "stdafx.h"
#include "Demo_Outlook.h"

#include "Demo_OutlookDoc.h"
#include "Demo_OutlookView.h"
#include "LeftView.h"
#include "RightView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemo_OutlookView

IMPLEMENT_DYNCREATE(CDemo_OutlookView, CView)

BEGIN_MESSAGE_MAP(CDemo_OutlookView, CView)
	//{{AFX_MSG_MAP(CDemo_OutlookView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemo_OutlookView construction/destruction

CDemo_OutlookView::CDemo_OutlookView()
{
	// TODO: add construction code here

}

CDemo_OutlookView::~CDemo_OutlookView()
{
}

BOOL CDemo_OutlookView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDemo_OutlookView drawing

void CDemo_OutlookView::OnDraw(CDC* pDC)
{
	CDemo_OutlookDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDemo_OutlookView printing

BOOL CDemo_OutlookView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDemo_OutlookView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDemo_OutlookView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDemo_OutlookView diagnostics

#ifdef _DEBUG
void CDemo_OutlookView::AssertValid() const
{
	CView::AssertValid();
}

void CDemo_OutlookView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDemo_OutlookDoc* CDemo_OutlookView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemo_OutlookDoc)));
	return (CDemo_OutlookDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemo_OutlookView message handlers

int CDemo_OutlookView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// CPaneContainerView is used to control the right pane that CMainFrame
	// sets up. In this case we create a second splitter window.
	m_wndSplitter.CreateStatic(this, 1,2);
	
	// The context information is passed on from the framework
	CCreateContext *pContext = (CCreateContext*)lpCreateStruct->lpCreateParams;
	
	// Create two views
	if (!m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CLeftView),
		CSize(175,0), pContext))
	{
		TRACE0("Failed to create CLeftView\n");
		return -1;
	}

	if (!m_wndSplitter.CreateView(0,1,RUNTIME_CLASS(CRightView),
		CSize(0,0), pContext))
	{
		TRACE0("Failed to create CRightView\n");
		return -1;
	}
	
	return 0;
}

void CDemo_OutlookView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	m_wndSplitter.MoveWindow(-2,-2,cx+4,cy+4);
}
