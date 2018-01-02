// ExListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ExListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExListCtrl

CExListCtrl::CExListCtrl()
{
	nBorder = 0;
}

CExListCtrl::~CExListCtrl()
{
}


BEGIN_MESSAGE_MAP(CExListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CExListCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExListCtrl message handlers

int CExListCtrl::InsertItem(const LVITEM* pItem)
{
	int nRet = CListCtrl::InsertItem(pItem);
	ResetColumnWidth();
	return nRet;
}

int CExListCtrl::InsertItem(int nItem, LPCTSTR lpszItem)
{
	int nRet = CListCtrl::InsertItem(nItem, lpszItem);
	ResetColumnWidth();
	return nRet;
}

int CExListCtrl::InsertItem(int nItem, LPCTSTR lpszItem, int nImage)
{
	int nRet = CListCtrl::InsertItem(nItem, lpszItem, nImage);
	ResetColumnWidth();
	return nRet;
}

int CExListCtrl::InsertItem(UINT nMask, int nItem, LPCTSTR lpszItem, UINT nState,
		UINT nStateMask, int nImage, LPARAM lParam)
{
	int nRet = CListCtrl::InsertItem(nMask, nItem, lpszItem, nState, nStateMask, nImage, lParam);
	ResetColumnWidth();
	return nRet;
}

BOOL CExListCtrl::DeleteItem(int nItem)
{
	BOOL bRet = CListCtrl::DeleteItem(nItem);
	ResetColumnWidth();
	return bRet;
}

BOOL CExListCtrl::DeleteAllItems()
{
	BOOL bRet = DeleteAllItems();
	ResetColumnWidth();
	return bRet;

}

int CExListCtrl::InsertColumn(int nCol, const LVCOLUMN* pColumn)
{
	ASSERT(::IsWindow(m_hWnd));
	ASSERT(GetHeaderCtrl()->GetItemCount()==0);

	LVCOLUMN lvcol = {0};
	CopyMemory(&lvcol, pColumn, sizeof(LVCOLUMN));
	CRect rc;
	GetClientRect(rc);
	lvcol.cx = rc.Width();
	
	return CListCtrl::InsertColumn(nCol, &lvcol);
}

int CExListCtrl::InsertColumn(int nCol, LPCTSTR lpszColumnHeading,
		int nFormat, int nWidth, int nSubItem)
{
	ASSERT(::IsWindow(m_hWnd));
	ASSERT(GetHeaderCtrl()->GetItemCount()==0);

	CRect rc;
	GetClientRect(rc);
	nWidth = rc.Width();

	return CListCtrl::InsertColumn(nCol, lpszColumnHeading, nFormat, nWidth, nSubItem);
}

void CExListCtrl::ResetColumnWidth()
{
	ASSERT(GetHeaderCtrl()->GetItemCount()==1);

	CRect rc;
	GetClientRect(rc);
	int nItemCount = GetItemCount();
	if (nItemCount == 0)
	{
		if (GetColumnWidth(0) != rc.Width())
		{
			SetColumnWidth(0, rc.Width());
		}
	}
	else
	{
		CRect rcItem;
		GetItemRect(0, rcItem, LVIR_BOUNDS);
		if (rcItem.Height()*nItemCount > rc.Height())
		{
			CRect rcWnd;
			GetWindowRect(rcWnd);
			int nScroll = GetSystemMetrics(SM_CXVSCROLL);
			if (GetColumnWidth(0) != rcWnd.Width()-nScroll-nBorder)
			{
				SetColumnWidth(0, rcWnd.Width()-nScroll-nBorder);
			}
		}
		else
		{
			if (GetColumnWidth(0) != rc.Width())
			{
				SetColumnWidth(0, rc.Width());
			}
		}
	}
}

void CExListCtrl::PreSubclassWindow() 
{
	CRect rcWnd,rc;
	GetWindowRect(rcWnd);
	GetClientRect(rc);
	nBorder = rcWnd.Width()-rc.Width();
	
	CListCtrl::PreSubclassWindow();
}
