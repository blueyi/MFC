// MDIWindListView.cpp : implementation of the CMDIWindListView class
//

#include "stdafx.h"
#include "MDIWindList.h"

#include "MDIWindListDoc.h"
#include "MDIWindListView.h"

#include "ViewManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMDIWindListView

IMPLEMENT_DYNCREATE(CMDIWindListView, CView)

BEGIN_MESSAGE_MAP(CMDIWindListView, CView)
	//{{AFX_MSG_MAP(CMDIWindListView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMDIWindListView construction/destruction

CMDIWindListView::CMDIWindListView()
{
	theViewManager.AddView("", this);
}

CMDIWindListView::~CMDIWindListView()
{
	theViewManager.RemoveView(this);
}

BOOL CMDIWindListView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMDIWindListView drawing

void CMDIWindListView::OnDraw(CDC* pDC)
{
	CMDIWindListDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMDIWindListView printing

BOOL CMDIWindListView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMDIWindListView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMDIWindListView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMDIWindListView diagnostics

#ifdef _DEBUG
void CMDIWindListView::AssertValid() const
{
	CView::AssertValid();
}

void CMDIWindListView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMDIWindListDoc* CMDIWindListView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMDIWindListDoc)));
	return (CMDIWindListDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMDIWindListView message handlers

void CMDIWindListView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	CMDIWindListDoc * pDoc = GetDocument();
	CString cs = pDoc->GetTitle();
	cs += " -with custom text for window list";
	theViewManager.SetViewName(cs, this);
}

void CMDIWindListView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	theViewManager.OnActivateView(bActivate, this);

	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}
