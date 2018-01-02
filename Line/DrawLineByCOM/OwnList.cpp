// OwnList.cpp : implementation file
// See OwnList.h for details on how to use this class
//

#include "stdafx.h"
#include "OwnList.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "RTDemoDoc.h"
#include "RTDemoView.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COwnerDrawListBox

COwnerDrawListBox::COwnerDrawListBox()
{
}

COwnerDrawListBox::~COwnerDrawListBox()
{
}


BEGIN_MESSAGE_MAP(COwnerDrawListBox, CListBox)
	//{{AFX_MSG_MAP(COwnerDrawListBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// COwnerDrawListBox message handlers
void COwnerDrawListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	int Index = (int)lpDrawItemStruct->itemData; // RGB in item data

	// White space
	CRect rcItem(lpDrawItemStruct->rcItem);
	rcItem.right /= 5;
	rcItem.InflateRect(-2, -2);

	CChildFrame* pChild = (CChildFrame*)(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->MDIGetActive());
	CRTDemoView* pView = ((CRTDemoView*)pChild->m_wndSplitter.GetPane(0, 0));
	pView->GetColorAndName(Index, m_nColor, m_szName); 

	// Paint the color item in the color requested
	CBrush brush(m_nColor);
	pDC->FillRect(rcItem, &brush);
	pDC->Draw3dRect(rcItem, GetSysColor(COLOR_BTNHILIGHT), GetSysColor(COLOR_BTNSHADOW));

	int bm  = pDC->SetBkMode(TRANSPARENT);
	pDC->TextOut( rcItem.right + 10, rcItem.top + 2, m_szName);
	pDC->SetBkMode(bm);

	// Focus rect
	if (lpDrawItemStruct->itemAction & ODA_FOCUS)
		pDC->DrawFocusRect(&lpDrawItemStruct->rcItem);
}

int COwnerDrawListBox::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct) 
{
	int Index1 = (int)lpCompareItemStruct->itemData1;
	int Index2 = (int)lpCompareItemStruct->itemData2;
	if (Index1 > Index2)	return 1;
	else if (Index1 == Index2)	return 0;       // exact match
	else	return -1;
}

#define COLOR_ITEM_HEIGHT   20
void COwnerDrawListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// all items are of fixed size
	// must use LBS_OWNERDRAWVARIABLE for this to work
	lpMeasureItemStruct->itemHeight = COLOR_ITEM_HEIGHT;
}
