// DemoTBarCView.cpp : implementation of the CDemoTBarCView class
//

#include "stdafx.h"
#include "DemoTBarC.h"

#include "DemoTBarCDoc.h"
#include "DemoTBarCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoTBarCView

IMPLEMENT_DYNCREATE(CDemoTBarCView, CView)

BEGIN_MESSAGE_MAP(CDemoTBarCView, CView)
	//{{AFX_MSG_MAP(CDemoTBarCView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoTBarCView construction/destruction

CDemoTBarCView::CDemoTBarCView()
{
	// TODO: add construction code here

}

CDemoTBarCView::~CDemoTBarCView()
{
}

BOOL CDemoTBarCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDemoTBarCView drawing

void CDemoTBarCView::OnDraw(CDC* pDC)
{
	CDemoTBarCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDemoTBarCView printing

BOOL CDemoTBarCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDemoTBarCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDemoTBarCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDemoTBarCView diagnostics

#ifdef _DEBUG
void CDemoTBarCView::AssertValid() const
{
	CView::AssertValid();
}

void CDemoTBarCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDemoTBarCDoc* CDemoTBarCView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemoTBarCDoc)));
	return (CDemoTBarCDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemoTBarCView message handlers
