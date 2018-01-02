// WzdView.cpp : implementation of the CWzdView class
//

#include "stdafx.h"
#include "Wzd.h"

#include "WzdDoc.h"
#include "WzdView.h"

#include "WzdDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWzdView

IMPLEMENT_DYNCREATE(CWzdView, CView)

BEGIN_MESSAGE_MAP(CWzdView, CView)
	//{{AFX_MSG_MAP(CWzdView)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_POPUP_WZD1, OnPopupWzd1)
	ON_COMMAND(ID_POPUP_WZD2, OnPopupWzd2)
	ON_COMMAND(ID_POPUP_WZD3, OnPopupWzd3)
	ON_COMMAND(ID_POPUP_WZD4, OnPopupWzd4)
	ON_COMMAND(ID_POPUP_WZD5, OnPopupWzd5)
	ON_COMMAND(ID_POPUP_WZD6, OnPopupWzd6)
	ON_COMMAND(ID_POPUP_WZD7, OnPopupWzd7)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWzdView construction/destruction

CWzdView::CWzdView()
{
	// TODO: add construction code here

}

CWzdView::~CWzdView()
{
}

BOOL CWzdView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CWzdView drawing

void CWzdView::OnDraw(CDC* pDC)
{
	CWzdDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CWzdView printing

BOOL CWzdView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWzdView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CWzdView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CWzdView diagnostics

#ifdef _DEBUG
void CWzdView::AssertValid() const
{
	CView::AssertValid();
}

void CWzdView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWzdDoc* CWzdView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWzdDoc)));
	return (CWzdDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWzdView message handlers

void CWzdView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CWzdDialog dlg;
	dlg.DoModal();

	CView::OnRButtonDown(nFlags, point);
}

void CWzdView::OnPopupWzd1() 
{
	// TODO: Add your command handler code here
	
}

void CWzdView::OnPopupWzd2() 
{
	// TODO: Add your command handler code here
	
}

void CWzdView::OnPopupWzd3() 
{
	// TODO: Add your command handler code here
	
}

void CWzdView::OnPopupWzd4() 
{
	// TODO: Add your command handler code here
	
}

void CWzdView::OnPopupWzd5() 
{
	// TODO: Add your command handler code here
	
}

void CWzdView::OnPopupWzd6() 
{
	// TODO: Add your command handler code here
	
}

void CWzdView::OnPopupWzd7() 
{
	// TODO: Add your command handler code here
	
}
