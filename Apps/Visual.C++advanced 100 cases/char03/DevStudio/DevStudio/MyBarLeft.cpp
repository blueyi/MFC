// MyBarLeft.cpp : implementation file
// 
// Copyright © 1998 Written by Kirk Stowell    
//		mailto:kstowel@sprynet.com 
//		http://www.geocities.com/SiliconValley/Haven/8230 
// 
// This code may be used in compiled form in any way you desire. This   
// file may be redistributed unmodified by any means PROVIDING it is    
// not sold for profit without the authors written consent, and    
// providing that this notice and the authors name and all copyright    
// notices remains intact. If the source code in this file is used in    
// any  commercial application then a statement along the lines of    
// "Portions Copyright © 1998 Kirk Stowell" must be included in    
// the startup banner, "About" box or printed documentation. An email    
// letting me know that you are using it would be nice as well. That's    
// not much to ask considering the amount of work that went into this.   
//   
// This file is provided "as is" with no expressed or implied warranty.   
// The author accepts no liability for any damage/loss of business that   
// this product may cause.   
// 
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyBarLeft.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyBarLeft

CMyBarLeft::CMyBarLeft()
{
	// TODO: add construction code here.
}

CMyBarLeft::~CMyBarLeft()
{
	// TODO: add destruction code here.
}

#define IDC_TREE_CTRL 1000

BEGIN_MESSAGE_MAP(CMyBarLeft, CCJControlBar)
	//{{AFX_MSG_MAP(CMyBarLeft)
	ON_WM_CREATE()
	ON_WM_WINDOWPOSCHANGED()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyBarLeft message handlers

static CString csTree[] =
{
	_T("Root Tree Item"),
	_T("Parent Tree Item"),
	_T("Child Tree Item")
};

int CMyBarLeft::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CCJControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	if (!m_TreeCtrl.Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP |
		TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT,
		CRect(0,0,0,0), this, IDC_TREE_CTRL))
	{
		TRACE0("Failed to create view for CMyBarLeft\n");
		return -1;
	}

	m_TreeCtrl.ModifyStyleEx(0,WS_EX_CLIENTEDGE|WS_EX_DLGMODALFRAME);

	// create the image list for the tree control
	// and set the tree style using defaults
	m_ImageList.Create (IDB_IL_FILE, 16, 1, RGB(0,128,128));
	m_TreeCtrl.SetImageList (&m_ImageList, TVSIL_NORMAL);

	// add the parent item, make it bold
	HTREEITEM htiParent = m_TreeCtrl.InsertItem(csTree[0]);
	HTREEITEM htiChild; // child item

	htiChild = m_TreeCtrl.InsertItem( csTree[1], 1, 1, htiParent, TVI_LAST );
	m_TreeCtrl.SetItemState( htiChild, TVIS_BOLD, TVIS_BOLD );

	// add the children of the parent item
	for( int i = 1; i < 10; i++ ) {
		m_TreeCtrl.InsertItem( csTree[2], 2, 3, htiChild, TVI_LAST );
	}

	m_TreeCtrl.Expand(htiParent, TVE_EXPAND);
	m_TreeCtrl.Expand(htiChild, TVE_EXPAND);

	return 0;
}

void CMyBarLeft::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	CCJControlBar::OnWindowPosChanged(lpwndpos);
	
	// TODO: Add your message handler code here
	if (IsFloating()) {
		m_TreeCtrl.MoveWindow( 5, 5, lpwndpos->cx-10, lpwndpos->cy-10 );
	}

	else if (IsHorzDocked()) {
		m_TreeCtrl.MoveWindow( 17, 3, lpwndpos->cx-25, lpwndpos->cy-17 );
	}

	else {
		m_TreeCtrl.MoveWindow( 3, 17, lpwndpos->cx-17, lpwndpos->cy-30 );
	}
}
