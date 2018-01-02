// OSDetectView.cpp : implementation of the COSDetectView class
//

#include "stdafx.h"
#include "OSDetect.h"

#include "OSDetectDoc.h"
#include "OSDetectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COSDetectView

IMPLEMENT_DYNCREATE(COSDetectView, CView)

BEGIN_MESSAGE_MAP(COSDetectView, CView)
	//{{AFX_MSG_MAP(COSDetectView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COSDetectView construction/destruction

COSDetectView::COSDetectView()
{
	// TODO: add construction code here

}

COSDetectView::~COSDetectView()
{
}

BOOL COSDetectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COSDetectView drawing

void COSDetectView::OnDraw(CDC* pDC)
{
	COSDetectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// COSDetectView diagnostics

#ifdef _DEBUG
void COSDetectView::AssertValid() const
{
	CView::AssertValid();
}

void COSDetectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COSDetectDoc* COSDetectView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COSDetectDoc)));
	return (COSDetectDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COSDetectView message handlers
