// FlatSplitter_DemoView.cpp : implementation of the CFlatSplitter_DemoView class
//

#include "stdafx.h"
#include "FlatSplitter_Demo.h"

#include "FlatSplitter_DemoDoc.h"
#include "RightView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlatSplitter_DemoView

IMPLEMENT_DYNCREATE(CRightView, CView)

BEGIN_MESSAGE_MAP(CRightView, CView)
	//{{AFX_MSG_MAP(CRightView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRightView construction/destruction

CRightView::CRightView()
{
	// TODO: add construction code here

}

CRightView::~CRightView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CRightView drawing

void CRightView::OnDraw(CDC* pDC)
{
	CRect rect,rcClient;
	GetClientRect(rcClient);

	COLORREF crLight = GetSysColor(COLOR_BTNHIGHLIGHT);
	COLORREF crShadow = GetSysColor(COLOR_BTNSHADOW);
	COLORREF crFrame = GetSysColor(COLOR_WINDOWFRAME);
	COLORREF crBtnFace = GetSysColor(COLOR_BTNFACE);

	pDC->SetBkMode(TRANSPARENT);
	CGdiObject *pOldFont = pDC->SelectStockObject(ANSI_VAR_FONT);

	rect = rcClient;

	// title rect
	rect.bottom = rect.top + 22;
	pDC->FillSolidRect(rect,crBtnFace);
	pDC->Draw3dRect(rect,crLight,crShadow);
	pDC->DrawText("   Text Editor:",rect,DT_SINGLELINE|DT_VCENTER);

	// rect that makes the edit control look even more sunken (windoze default)
	rect.top = rect.bottom;
	rect.bottom = rcClient.bottom;
	pDC->Draw3dRect(rect,crFrame,crBtnFace);

	pDC->SelectObject(pOldFont);
}

/////////////////////////////////////////////////////////////////////////////
// CRightView message handlers

int CRightView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_wndEdit.Create(WS_VISIBLE|WS_CHILD|ES_MULTILINE|WS_VSCROLL|ES_AUTOVSCROLL,CRect(0,0,0,0),this,0);
	
	CFont font;
	font.CreateStockObject(ANSI_FIXED_FONT);
	m_wndEdit.SetFont(&font);
	
	return 0;
}

void CRightView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	m_wndEdit.MoveWindow(1,23,cx-2,cy-24);
	
}
