// MyBarBottom.cpp : implementation file
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
#include "MyBarBottom.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyBarBottom

CMyBarBottom::CMyBarBottom()
{
	// TODO: add construction code here.
}

CMyBarBottom::~CMyBarBottom()
{
	// TODO: add destruction code here.
}

#define IDC_LIST_CTRL 1000

BEGIN_MESSAGE_MAP(CMyBarBottom, CControlBar)
	//{{AFX_MSG_MAP(CMyBarBottom)
	ON_WM_CREATE()
	ON_WM_WINDOWPOSCHANGED()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyBarBottom message handlers

static int _gColText[] =
{
	IDS_COL_1,
	IDS_COL_2,
	IDS_COL_3
};

static int _gColSize[] =
{
	100,
	250,
	250
};

static CString _gListText[] =
{
	_T("test one"),
	_T("test two"),
	_T("test three")
};

int CMyBarBottom::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	if (!m_ListCtrl.Create (WS_CHILD|WS_VISIBLE|LVS_REPORT,
		CRect(0,0,0,0), this, IDC_LIST_CTRL))
	{
		TRACE0("Failed to create view for CMyBarLeft\n");
		return -1;
	}

	m_ListCtrl.ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	AddExStyle (LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);
	BuildColumns(3, _gColSize, _gColText);

	for (int i = 0; i < 5; ++i)
		FormatList (_gListText);

	return 0;
}

void CMyBarBottom::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	CControlBar::OnWindowPosChanged(lpwndpos);
	
	// TODO: Add your message handler code here
	if (IsFloating()) {
		m_ListCtrl.MoveWindow( 5, 5, lpwndpos->cx-10, lpwndpos->cy-10 );
	}

	else if (IsHorzDocked()) {
		m_ListCtrl.MoveWindow( 17, 3, lpwndpos->cx-25, lpwndpos->cy-17 );
	}

	else {
		m_ListCtrl.MoveWindow( 3, 17, lpwndpos->cx-17, lpwndpos->cy-30 );
	}
}

void CMyBarBottom::AddExStyle(DWORD dwNewStyle)
{
	// Returns the current extended style ( a DWORD ).
	DWORD dwStyle = ::SendMessage (m_ListCtrl.m_hWnd, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0);

	// Add the full row select and grid line style to the existing extended styles.
	dwStyle |= dwNewStyle;

	// Sets the current extended style ( a DWORD ).
	::SendMessage (m_ListCtrl.m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, dwStyle);
}

void CMyBarBottom::BuildColumns(int nCols, int * nWidth, int * iCol)
{
	ASSERT(nCols);
	ASSERT(nWidth);
	ASSERT(iCol);
	ASSERT(m_ListCtrl);

	//insert columns
	int i;
	LV_COLUMN lvc;

	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	CString	strTemp;
	for(i = 0; i < nCols; i++)
	{
		lvc.iSubItem = i;
		strTemp.LoadString(iCol[i]);
		lvc.pszText = (char*)(LPCTSTR)strTemp;
		lvc.cx = nWidth[i];
		lvc.fmt = LVCFMT_LEFT;
		m_ListCtrl.InsertColumn(i,&lvc);
	}
}

void CMyBarBottom::FormatList(CString * csText)
{
	int			nI = m_ListCtrl.GetItemCount();
	LV_ITEM		lvi;

	if (csText)
	{
		lvi.mask = LVIF_TEXT | LVIF_STATE;
		lvi.iItem = nI;
		lvi.iSubItem = 0;
		lvi.iImage = 0;
		lvi.stateMask = LVIS_STATEIMAGEMASK;
		lvi.state = INDEXTOSTATEIMAGEMASK(1);
		lvi.pszText = (char*)(LPCTSTR)csText[0];
		int result = m_ListCtrl.InsertItem(&lvi);
		if (result != -1)
		{
			SetLVCheck (nI, TRUE);
			m_ListCtrl.SetItemText(nI, 1, csText[1]);
			m_ListCtrl.SetItemText(nI, 2, csText[2]);
		}
	}
}

void CMyBarBottom::SetLVCheck(WPARAM ItemIndex, BOOL bCheck)
{
	LV_ITEM lvi;
	lvi.stateMask = LVIS_STATEIMAGEMASK;
	lvi.state = UINT((int(bCheck) + 1) << 12);
	::SendMessage (m_ListCtrl.m_hWnd, LVM_SETITEMSTATE, (WPARAM)ItemIndex,
		(LPARAM)(LV_ITEM FAR*)&lvi);
}
