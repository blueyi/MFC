// TextInStatusView.cpp : implementation of the CTextInStatusView class
//

#include "stdafx.h"
#include "TextInStatus.h"

#include "TextInStatusDoc.h"
#include "TextInStatusView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextInStatusView

IMPLEMENT_DYNCREATE(CTextInStatusView, CView)

BEGIN_MESSAGE_MAP(CTextInStatusView, CView)
	//{{AFX_MSG_MAP(CTextInStatusView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextInStatusView construction/destruction

CTextInStatusView::CTextInStatusView()
{
	// TODO: add construction code here

}

CTextInStatusView::~CTextInStatusView()
{
}

BOOL CTextInStatusView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTextInStatusView drawing

void CTextInStatusView::OnDraw(CDC* pDC)
{
	CTextInStatusDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTextInStatusView printing

BOOL CTextInStatusView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTextInStatusView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTextInStatusView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTextInStatusView diagnostics

#ifdef _DEBUG
void CTextInStatusView::AssertValid() const
{
	CView::AssertValid();
}

void CTextInStatusView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTextInStatusDoc* CTextInStatusView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTextInStatusDoc)));
	return (CTextInStatusDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTextInStatusView message handlers
