// ViewGrid.cpp : implementation file
//

#include "stdafx.h"
#include "TreeList.h"

#include "doc.h"
#include "ViewTree.h"
#include "ViewList.h"
#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyListView

IMPLEMENT_DYNCREATE(CMyListView, CListView)

BEGIN_MESSAGE_MAP(CMyListView, CListView)
	//{{AFX_MSG_MAP(CMyListView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMyListView::CMyListView()
{
}

CMyListView::~CMyListView()
{
}

BOOL CMyListView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	dwStyle	|=	LVS_REPORT;				// report mode

	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

/////////////////////////////////////////////////////////////////////////////
BOOL CMyListView::PreCreateWindow(CREATESTRUCT& cs) 
{
	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyListView drawing

void CMyListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMyListView diagnostics

#ifdef _DEBUG
void CMyListView::AssertValid() const
{
	CListView::AssertValid();
}

void CMyListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CTreeListDoc* CMyListView::GetDocument() // non-debug version is inline
{
	return STATIC_DOWNCAST(CTreeListDoc, m_pDocument);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyListView message handlers

void CMyListView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	
	// get list
	CListCtrl& cThisList = GetListCtrl();

	// get tree view
	CMainFrame * pFWnd = (CMainFrame *)AfxGetMainWnd();
	CTreeListView * pView = (CTreeListView*)pFWnd->m_wndSplitter.GetPane(0,0);
	ASSERT( pView != NULL);
	ASSERT( pView->m_pImageList != NULL);

	// make image list identical to tree's (not LVSIL_NORMAL)
	cThisList.SetImageList( pView->m_pImageList, LVSIL_SMALL );

	// build list columns
	CRect cr;
	GetClientRect(&cr);

	int nWidth = cr.Width()/4;

	// set up the grid column titles
	CString s;
	LV_COLUMN lvcol;
	lvcol.cx = nWidth;
	lvcol.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lvcol.fmt = LVCFMT_LEFT;
	lvcol.pszText = (LPSTR)"Name";
	lvcol.iSubItem = 0;
	cThisList.InsertColumn( 0, &lvcol );

	// second col
	lvcol.fmt = LVCFMT_RIGHT;
	lvcol.pszText = (LPSTR)"Size";
	lvcol.iSubItem = 1;
	cThisList.InsertColumn( 1, &lvcol );

	// third col
	lvcol.fmt = LVCFMT_LEFT;
	lvcol.pszText = (LPSTR)"Type";
	lvcol.iSubItem = 2;
	cThisList.InsertColumn( 2, &lvcol );

	// fourth col
	lvcol.pszText = (LPSTR)"Modified";
	lvcol.iSubItem = 3;
	cThisList.InsertColumn( 3, &lvcol );
}



