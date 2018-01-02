// WindowTabCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MDIWindList.h"
#include "WindowTabCtrl.h"
#include "ViewManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWindowTabCtrl

CWindowTabCtrl::CWindowTabCtrl()
{
}

CWindowTabCtrl::~CWindowTabCtrl()
{
}


BEGIN_MESSAGE_MAP(CWindowTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CWindowTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, OnSelchange)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWindowTabCtrl message handlers

void CWindowTabCtrl::OnSelchange(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int idx = GetCurSel();

	TC_ITEM ti;
	ti.mask = TCIF_PARAM;
	GetItem(idx, &ti);
	CView * pView = (CView *) ti.lParam;
	((CMDIFrameWnd *)AfxGetMainWnd())->MDIActivate(pView->GetParent());
	*pResult = 0;
}

int CWindowTabCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTabCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	HFONT hf = (HFONT) GetStockObject(DEFAULT_GUI_FONT);
	CFont * ft = CFont::FromHandle(hf);
	SetFont(ft);
		
	return 0;
}

void CWindowTabCtrl::ResizeTabs()
{
	CRect rc;
	GetClientRect(rc);
	int iNumWin = theViewManager.GetWindowNum();
	int x = 140; // def item width
	if ((x+4) * iNumWin > rc.Width()) x = (rc.Width()) / iNumWin - 4;
	SetItemSize(CSize(x,rc.Height()));
}

void CWindowTabCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CTabCtrl::OnSize(nType, cx, cy);
	ResizeTabs();
}
