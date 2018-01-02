// ListCtrlEx.cpp : implementation file
//

#include "stdafx.h"
#include "PeekPocket.h"
#include "ListCtrlEx.h"

// CListCtrlEx
IMPLEMENT_DYNAMIC(CListCtrlEx, CListCtrl)

CListCtrlEx::CListCtrlEx()
{
}

CListCtrlEx::~CListCtrlEx()
{
}

BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY_REFLECT(NM_RECOGNIZEGESTURE, OnRecognizeGesture)
END_MESSAGE_MAP()

// CListCtrlEx message handlers
void CListCtrlEx::OnLButtonDown(UINT nFlags, CPoint point)
{
	//CWnd::OnLButtonDown would call SHRecognizeGesture which would pop up the dots
	Default();
}

//////////////////////////////////////////////////////////////////////////
void CListCtrlEx::OnRecognizeGesture(NMHDR* pNMHDR, LRESULT* pResult)
{
	//do nothing
	*pResult = TRUE;
} 

