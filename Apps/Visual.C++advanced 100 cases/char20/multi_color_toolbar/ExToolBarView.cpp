// ExToolBarView.cpp : implementation of the CExToolBarView class
//

#include "stdafx.h"
#include "ExToolBar.h"

#include "ExToolBarDoc.h"
#include "ExToolBarView.h"
#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExToolBarView

IMPLEMENT_DYNCREATE(CExToolBarView, CView)

BEGIN_MESSAGE_MAP(CExToolBarView, CView)
	//{{AFX_MSG_MAP(CExToolBarView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExToolBarView construction/destruction

CExToolBarView::CExToolBarView()
{
	// TODO: add construction code here

}

CExToolBarView::~CExToolBarView()
{
}

BOOL CExToolBarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CExToolBarView drawing

void CExToolBarView::OnDraw(CDC* pDC)
{
	CExToolBarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

}

/////////////////////////////////////////////////////////////////////////////
// CExToolBarView printing

BOOL CExToolBarView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CExToolBarView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CExToolBarView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CExToolBarView diagnostics

#ifdef _DEBUG
void CExToolBarView::AssertValid() const
{
	CView::AssertValid();
}

void CExToolBarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExToolBarDoc* CExToolBarView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExToolBarDoc)));
	return (CExToolBarDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExToolBarView message handlers
