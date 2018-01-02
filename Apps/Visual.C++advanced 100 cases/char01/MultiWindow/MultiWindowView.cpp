// MultiWindowView.cpp : implementation of the CMultiWindowView class
//

#include "stdafx.h"
#include "MultiWindow.h"

#include "MultiWindowDoc.h"
#include "MultiWindowView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiWindowView

IMPLEMENT_DYNCREATE(CMultiWindowView, CView)

BEGIN_MESSAGE_MAP(CMultiWindowView, CView)
	//{{AFX_MSG_MAP(CMultiWindowView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiWindowView construction/destruction

CMultiWindowView::CMultiWindowView()
{
	// TODO: add construction code here

}

CMultiWindowView::~CMultiWindowView()
{
}

BOOL CMultiWindowView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMultiWindowView drawing

void CMultiWindowView::OnDraw(CDC* pDC)
{
	CMultiWindowDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMultiWindowView printing

BOOL CMultiWindowView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMultiWindowView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMultiWindowView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMultiWindowView diagnostics

#ifdef _DEBUG
void CMultiWindowView::AssertValid() const
{
	CView::AssertValid();
}

void CMultiWindowView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMultiWindowDoc* CMultiWindowView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMultiWindowDoc)));
	return (CMultiWindowDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMultiWindowView message handlers
