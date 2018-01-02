// Wzd2View.cpp : implementation file
//

#include "stdafx.h"
#include "wzd.h"
#include "Wzd2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWzd2View

IMPLEMENT_DYNCREATE(CWzd2View, CView)

CWzd2View::CWzd2View()
{
}

CWzd2View::~CWzd2View()
{
}


BEGIN_MESSAGE_MAP(CWzd2View, CView)
	//{{AFX_MSG_MAP(CWzd2View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWzd2View drawing

void CWzd2View::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CWzd2View diagnostics

#ifdef _DEBUG
void CWzd2View::AssertValid() const
{
	CView::AssertValid();
}

void CWzd2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWzd2View message handlers
