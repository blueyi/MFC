// MSDITestView.cpp : implementation of the CMSDITestView class
//

#include "stdafx.h"
#include "MSDITest.h"

#include "MSDITestDoc.h"
#include "MSDITestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMSDITestView

IMPLEMENT_DYNCREATE(CMSDITestView, CView)

BEGIN_MESSAGE_MAP(CMSDITestView, CView)
	//{{AFX_MSG_MAP(CMSDITestView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMSDITestView construction/destruction

CMSDITestView::CMSDITestView()
{
	// TODO: add construction code here

}

CMSDITestView::~CMSDITestView()
{
}

BOOL CMSDITestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMSDITestView drawing

void CMSDITestView::OnDraw(CDC* pDC)
{
	CMSDITestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMSDITestView printing

BOOL CMSDITestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMSDITestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMSDITestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMSDITestView diagnostics

#ifdef _DEBUG
void CMSDITestView::AssertValid() const
{
	CView::AssertValid();
}

void CMSDITestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMSDITestDoc* CMSDITestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMSDITestDoc)));
	return (CMSDITestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMSDITestView message handlers
