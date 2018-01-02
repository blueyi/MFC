// MyInterfaceView.cpp : implementation of the CMyInterfaceView class
//

#include "stdafx.h"
#include "MyInterface.h"

#include "MyInterfaceDoc.h"
#include "MyInterfaceView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyInterfaceView

IMPLEMENT_DYNCREATE(CMyInterfaceView, CView)

BEGIN_MESSAGE_MAP(CMyInterfaceView, CView)
	//{{AFX_MSG_MAP(CMyInterfaceView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyInterfaceView construction/destruction

CMyInterfaceView::CMyInterfaceView()
{
	// TODO: add construction code here

}

CMyInterfaceView::~CMyInterfaceView()
{
}

BOOL CMyInterfaceView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyInterfaceView drawing

void CMyInterfaceView::OnDraw(CDC* pDC)
{
	CMyInterfaceDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMyInterfaceView printing

BOOL CMyInterfaceView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyInterfaceView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyInterfaceView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyInterfaceView diagnostics

#ifdef _DEBUG
void CMyInterfaceView::AssertValid() const
{
	CView::AssertValid();
}

void CMyInterfaceView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyInterfaceDoc* CMyInterfaceView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyInterfaceDoc)));
	return (CMyInterfaceDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyInterfaceView message handlers
