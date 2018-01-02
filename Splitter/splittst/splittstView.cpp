// splittstView.cpp : implementation of the CSplittstView class
//

#include "stdafx.h"
#include "splittst.h"

#include "splittstDoc.h"
#include "splittstView.h"

#include "mainfrm.h"
#include "form1.h"
#include "form2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplittstView

IMPLEMENT_DYNCREATE(CSplittstView, CListView)

BEGIN_MESSAGE_MAP(CSplittstView, CListView)
	//{{AFX_MSG_MAP(CSplittstView)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplittstView construction/destruction

CSplittstView::CSplittstView()
{
	// TODO: add construction code here

}

CSplittstView::~CSplittstView()
{
}

BOOL CSplittstView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSplittstView drawing

void CSplittstView::OnDraw(CDC* pDC)
{
	CSplittstDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CSplittstView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	GetListCtrl().InsertItem(0,_T("Form1"));
	GetListCtrl().InsertItem(1,_T("Form2"));

	GetListCtrl().SetItemState(0,3,3);
	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CSplittstView diagnostics

#ifdef _DEBUG
void CSplittstView::AssertValid() const
{
	CListView::AssertValid();
}

void CSplittstView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CSplittstDoc* CSplittstView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSplittstDoc)));
	return (CSplittstDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSplittstView message handlers

void CSplittstView::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	CString szText=GetListCtrl().GetItemText(pNMListView->iItem,pNMListView->iSubItem);

	if (pNMListView->uNewState == 3)
	{
		CMainFrame *pMainFrame=(CMainFrame*)AfxGetMainWnd();
		if (szText==_T("Form1"))
		{
			pMainFrame->m_wndSplitter.ReplaceView(0,1,RUNTIME_CLASS(CForm1),CSize(100,100));	
		}
		else if (szText==_T("Form2"))
		{
			pMainFrame->m_wndSplitter.ReplaceView(0,1,RUNTIME_CLASS(CForm2),CSize(100,100));	
		}
	}
	
	*pResult = 0;
}
