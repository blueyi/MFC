// XxView.cpp : implementation of the CXxView class
//

#include "stdafx.h"
#include "Xx.h"

#include "XxDoc.h"
#include "XxView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXxView

IMPLEMENT_DYNCREATE(CXxView, CView)

BEGIN_MESSAGE_MAP(CXxView, CView)
	//{{AFX_MSG_MAP(CXxView)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXxView construction/destruction

CXxView::CXxView()
{
	// TODO: add construction code here

}

CXxView::~CXxView()
{
}

BOOL CXxView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CXxView drawing

void CXxView::OnDraw(CDC* pDC)
{
	CXxDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CXxView printing

BOOL CXxView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CXxView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CXxView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CXxView diagnostics

#ifdef _DEBUG
void CXxView::AssertValid() const
{
	CView::AssertValid();
}

void CXxView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CXxDoc* CXxView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXxDoc)));
	return (CXxDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXxView message handlers

void CXxView::OnTimer(UINT nIDEvent) 
{
	
	
	CView::OnTimer(nIDEvent);
}
