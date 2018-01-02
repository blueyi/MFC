// HDDemoView.cpp : implementation of the CHDDemoView class
//

#include "stdafx.h"
#include "HDDemo.h"

#include "HDDemoDoc.h"
#include "HDDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHDDemoView

IMPLEMENT_DYNCREATE(CHDDemoView, CView)

BEGIN_MESSAGE_MAP(CHDDemoView, CView)
	//{{AFX_MSG_MAP(CHDDemoView)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHDDemoView construction/destruction

CHDDemoView::CHDDemoView()
{
	// TODO: add construction code here

}

CHDDemoView::~CHDDemoView()
{
}

BOOL CHDDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHDDemoView drawing

void CHDDemoView::OnDraw(CDC* pDC)
{
	CHDDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CHDDemoView printing

BOOL CHDDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CHDDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CHDDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CHDDemoView diagnostics

#ifdef _DEBUG
void CHDDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CHDDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHDDemoDoc* CHDDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHDDemoDoc)));
	return (CHDDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
