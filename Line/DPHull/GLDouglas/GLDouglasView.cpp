// GLDouglasView.cpp : implementation of the CGLDouglasView class
//

#include "stdafx.h"
#include "GLDouglas.h"

#include "GLDouglasDoc.h"
#include "GLDouglasView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGLDouglasView

IMPLEMENT_DYNCREATE(CGLDouglasView, CView)

BEGIN_MESSAGE_MAP(CGLDouglasView, CView)
	//{{AFX_MSG_MAP(CGLDouglasView)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGLDouglasView construction/destruction

CGLDouglasView::CGLDouglasView()
{
	// TODO: add construction code here

}

CGLDouglasView::~CGLDouglasView()
{
}

BOOL CGLDouglasView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGLDouglasView drawing

void CGLDouglasView::OnDraw(CDC* pDC)
{
	CGLDouglasDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	double dLimits[4];
	CString str;

	pDoc->GetLimits(dLimits);
	m_view.SetLimits(dLimits);
	m_view.PostReshape();

	m_wgl.Begin(pDC);
		// setting view
		m_view.Reshape();	

		// clearing buffer
		glClearColor(1.0, 1.0, 1.0, 0.0);
 		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// drawing line
		pDoc->Draw(m_wgl);

	m_wgl.End();

	// Swap buffers.
	SwapBuffers(pDC->m_hDC) ;
}

/////////////////////////////////////////////////////////////////////////////
// CGLDouglasView diagnostics

#ifdef _DEBUG
void CGLDouglasView::AssertValid() const
{
	CView::AssertValid();
}

void CGLDouglasView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGLDouglasDoc* CGLDouglasView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGLDouglasDoc)));
	return (CGLDouglasDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGLDouglasView message handlers

BOOL CGLDouglasView::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

void CGLDouglasView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

	m_view.SetViewport(0,0,cx,cy);

	m_view.PostReshape();	
}

void CGLDouglasView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

	m_view.GetState()->SetLineWidth(2);
	
	((CGLDouglasApp*)AfxGetApp())->SetView(this);
}

