// VGisView.cpp : implementation of the CVGisView class
//

#include "stdafx.h"
#include "VGis.h"

#include "VGisDoc.h"
#include "VGisView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVGisView

IMPLEMENT_DYNCREATE(CVGisView, CView)

BEGIN_MESSAGE_MAP(CVGisView, CView)
	//{{AFX_MSG_MAP(CVGisView)
	ON_WM_SIZE()
	ON_COMMAND(IDM_DRAW_LINE, OnDrawLine)
	ON_COMMAND(IDM_DRAW_ARC, OnDrawArc)
	ON_COMMAND(IDM_DRAW_CIRCLE, OnDrawCircle)
	ON_COMMAND(IDM_DRAW_LINE_NET, OnDrawLineNet)
	ON_COMMAND(IDM_DRAW_MLINE, OnDrawMline)
	ON_COMMAND(IDM_DRAW_NET, OnDrawNet)
	ON_COMMAND(IDM_DRAW_RGN, OnDrawRgn)
	ON_COMMAND(IDM_DRAW_TEXT, OnDrawText)
	ON_COMMAND(IDM_DRAW_BIG, OnDrawBig)
	ON_COMMAND(IDM_DRAW_SMALL, OnDrawSmall)
	ON_COMMAND(IDM_MOVE, OnMove)
	ON_COMMAND(IDM_ALL, OnAll)
	ON_COMMAND(IDM_RECTBIG, OnRectbig)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVGisView construction/destruction

CVGisView::CVGisView()
{
	// TODO: add construction code here

}

CVGisView::~CVGisView()
{
}

BOOL CVGisView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CVGisView drawing

void CVGisView::OnDraw(CDC* pDC)
{
	CVGisDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	m_Gis.Draw(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CVGisView printing

BOOL CVGisView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVGisView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVGisView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CVGisView diagnostics

#ifdef _DEBUG
void CVGisView::AssertValid() const
{
	CView::AssertValid();
}

void CVGisView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVGisDoc* CVGisView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVGisDoc)));
	return (CVGisDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVGisView message handlers

void CVGisView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CRect rect;
	this->GetClientRect(&rect);
	m_Gis.Create(this,rect);
}

void CVGisView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (m_Gis.m_hWnd)
		m_Gis.MoveWindow(0,0,cx,cy);
}

void CVGisView::OnDrawLine() 
{
	// TODO: Add your command handler code here
	m_Gis.SetDraw(G_LINE);
}

void CVGisView::OnDrawArc() 
{
	// TODO: Add your command handler code here
	m_Gis.SetDraw(G_ARC);	
}

void CVGisView::OnDrawCircle() 
{
	// TODO: Add your command handler code here
	m_Gis.SetDraw(G_CIRCLE);
}

void CVGisView::OnDrawLineNet() 
{
	// TODO: Add your command handler code here
	m_Gis.SetDraw(G_LINENET);
}

void CVGisView::OnDrawMline() 
{
	// TODO: Add your command handler code here
	m_Gis.SetDraw(G_MLINE);
}

void CVGisView::OnDrawNet() 
{
	// TODO: Add your command handler code here
	m_Gis.SetDraw(G_TAG);
}

void CVGisView::OnDrawRgn() 
{
	// TODO: Add your command handler code here
	m_Gis.SetDraw(G_MLINERGN);
}

void CVGisView::OnDrawText() 
{
	// TODO: Add your command handler code here
	m_Gis.SetDraw(G_LABEL);
}

CView  *g_pView;

void CVGisView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class
	g_pView=this;
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CVGisView::OnDrawBig() 
{
	// TODO: Add your command handler code here
	m_Gis.SetDraw(G_BIG);
}

void CVGisView::OnDrawSmall() 
{
	// TODO: Add your command handler code here
	m_Gis.SetDraw(G_SMALL);
}

void CVGisView::OnMove() 
{
	// TODO: Add your command handler code here
	m_Gis.SetDraw(G_MOVE);
//	this->Invalidate();
}

void CVGisView::OnAll() 
{
	// TODO: Add your command handler code here
	m_Gis.AllGraph();
}

void CVGisView::OnRectbig() 
{
	// TODO: Add your command handler code here
	m_Gis.SetDraw(G_RECT);
}

void CVGisView::Serialize(CArchive& ar) 
{
	m_Gis.Serialize(ar);
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}
