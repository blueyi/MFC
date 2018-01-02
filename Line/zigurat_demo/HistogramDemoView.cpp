// HistogramDemoView.cpp : implementation of the CHistogramDemoView class
//

#include "stdafx.h"
#include "HistogramDemo.h"

#include "HistogramDemoDoc.h"
#include "HistogramDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHistogramDemoView

IMPLEMENT_DYNCREATE(CHistogramDemoView, CView)

BEGIN_MESSAGE_MAP(CHistogramDemoView, CView)
	//{{AFX_MSG_MAP(CHistogramDemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHistogramDemoView construction/destruction

CHistogramDemoView::CHistogramDemoView()
{
	// TODO: add construction code here

}

CHistogramDemoView::~CHistogramDemoView()
{
}

BOOL CHistogramDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHistogramDemoView drawing

void CHistogramDemoView::OnDraw(CDC* pDC)
{
	CHistogramDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CHistogramDemoView diagnostics

#ifdef _DEBUG
void CHistogramDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CHistogramDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHistogramDemoDoc* CHistogramDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHistogramDemoDoc)));
	return (CHistogramDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHistogramDemoView message handlers
