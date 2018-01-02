// tabView.cpp : implementation of the CTabView class
//

#include "stdafx.h"
#include "tab.h"

#include "tabDoc.h"
#include "tabView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabView

IMPLEMENT_DYNCREATE(CTabView, CView)

BEGIN_MESSAGE_MAP(CTabView, CView)
	//{{AFX_MSG_MAP(CTabView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabView construction/destruction

CTabView::CTabView()
{
	// TODO: add construction code here

}

CTabView::~CTabView()
{
}

BOOL CTabView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

static char ppszText[][60] =
{
   "This program is an example how you can create",
   "view's and switch between them by clicking on a",
   "tab.", 
   "The code is not well dokumented (done intentionally).",
   "But if you want a better version with comments in code",
   "and more features.",
   "Send a mail to \"hulken@algonet.se\".",
   " ",
   "IF YOU WANT TO EXCHANGE CODE AND IDEAS, PLEASE SEND",
   "A MAIL TO ME.",
   " ",
   "// Per Ghosh",
   NULL
};

void CTabView::OnDraw(CDC* pDC)
{
	int iCounter = 0;

   CTabDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

   while( *ppszText[iCounter] )
   {
      pDC->TextOut( 10,iCounter * 20, ppszText[iCounter], strlen(ppszText[iCounter]) );
      iCounter++;
   }
}

/////////////////////////////////////////////////////////////////////////////
// CTabView diagnostics

#ifdef _DEBUG
void CTabView::AssertValid() const
{
	CView::AssertValid();
}

void CTabView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTabDoc* CTabView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTabDoc)));
	return (CTabDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTabView message handlers

