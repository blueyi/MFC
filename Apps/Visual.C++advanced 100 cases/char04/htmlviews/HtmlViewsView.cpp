// HtmlViewsView.cpp : implementation of the CHtmlViewsView class
//

#include "stdafx.h"
#include "HtmlViews.h"

#include "HtmlViewsDoc.h"
#include "HtmlViewsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHtmlViewsView

IMPLEMENT_DYNCREATE(CHtmlViewsView, CHView)

BEGIN_MESSAGE_MAP(CHtmlViewsView, CHView)
	//{{AFX_MSG_MAP(CHtmlViewsView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CHView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CHView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CHView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHtmlViewsView construction/destruction

CHtmlViewsView::CHtmlViewsView()
{
	// TODO: add construction code here

}

CHtmlViewsView::~CHtmlViewsView()
{
}

BOOL CHtmlViewsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHtmlViewsView drawing

void CHtmlViewsView::OnDraw(CDC* pDC)
{
	CHtmlViewsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CHtmlViewsView printing

BOOL CHtmlViewsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CHtmlViewsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CHtmlViewsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CHtmlViewsView diagnostics

#ifdef _DEBUG
void CHtmlViewsView::AssertValid() const
{
	CHView::AssertValid();
}

void CHtmlViewsView::Dump(CDumpContext& dc) const
{
	CHView::Dump(dc);
}

CHtmlViewsDoc* CHtmlViewsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHtmlViewsDoc)));
	return (CHtmlViewsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHtmlViewsView message handlers

