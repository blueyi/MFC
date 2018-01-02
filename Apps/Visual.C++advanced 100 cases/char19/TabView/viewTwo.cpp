// viewTwo.cpp : implementation file
//

#include "stdafx.h"
#include "tab.h"
#include "viewTwo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CviewTwo

IMPLEMENT_DYNCREATE(CviewTwo, CView)

CviewTwo::CviewTwo()
{
}

CviewTwo::~CviewTwo()
{
}


BEGIN_MESSAGE_MAP(CviewTwo, CView)
	//{{AFX_MSG_MAP(CviewTwo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static char ppszText[][60] =
{
   "Look in CMainFrame::OnCreateClient() for informaiton",
   "about what you have to do for creating a tab-view i",
   "your application",
   "You can use this functionality to create tab-view in any",
   "window that is derived from CFrameWnd.",
   NULL
};

void CviewTwo::OnDraw(CDC* pDC)
{
	int iCounter = 0;

   CDocument* pDoc = GetDocument();

   while( *ppszText[iCounter] )
   {
      pDC->TextOut( 10,iCounter * 20, ppszText[iCounter], strlen(ppszText[iCounter]) );
      iCounter++;
   }

}

/////////////////////////////////////////////////////////////////////////////
// CviewTwo diagnostics

#ifdef _DEBUG
void CviewTwo::AssertValid() const
{
	CView::AssertValid();
}

void CviewTwo::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CviewTwo message handlers

