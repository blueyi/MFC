// StealthView.cpp : implementation of the CStealthView class
//

#include "stdafx.h"
#include "Stealth.h"

#include "StealthDoc.h"
#include "StealthView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStealthView

IMPLEMENT_DYNCREATE(CStealthView, CView)

BEGIN_MESSAGE_MAP(CStealthView, CView)
	//{{AFX_MSG_MAP(CStealthView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStealthView construction/destruction

CStealthView::CStealthView()
{
	// TODO: add construction code here

}

CStealthView::~CStealthView()
{
}

BOOL CStealthView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CStealthView drawing

void CStealthView::OnDraw(CDC* pDC)
{
	CStealthDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CStealthView printing

BOOL CStealthView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CStealthView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CStealthView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CStealthView diagnostics

#ifdef _DEBUG
void CStealthView::AssertValid() const
{
	CView::AssertValid();
}

void CStealthView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStealthDoc* CStealthView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStealthDoc)));
	return (CStealthDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStealthView message handlers
