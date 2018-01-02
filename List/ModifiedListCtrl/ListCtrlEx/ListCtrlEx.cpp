/////////////////////////////////////////////////////////////////////////////
// ListCtrlEx.cpp : implementation file
/////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "ListCtrlEx.h"

#include "..\MainView.h"

/////////////////////////////////////////////////////////////////////////////
// MESSAGE MAP
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
	ON_WM_MEASUREITEM_REFLECT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx
/////////////////////////////////////////////////////////////////////////////
CListCtrlEx::CListCtrlEx() {
	//*** Creates table list font
	m_pFont = new CFont;

	if(!m_pFont) {
		_M("Empty table list font!");
		return;
	}

	//*** The structure of the table list font
	LOGFONT ListFont = {
		-15, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 1, 2, 2,	FF_DONTCARE, 
		_T("MS Sans Serif")
	};

	//*** Initializes the list font
	m_pFont->CreateFontIndirect(&ListFont);
	
	//*** The table list height
	m_nListHeight = 40;

	//*** The table rows count
	m_nRowCount = 10;

	//*** The table columns count
	m_nColCount = 6;  // = nHdrCount in MainView::OnCreate

}  // CListCtrlEx

/////////////////////////////////////////////////////////////////////////////
// Table rows array
// 10 = m_nRowCount & 6 = m_nColCount
/////////////////////////////////////////////////////////////////////////////
TCHAR *CListCtrlEx::m_apRowText[10][6] = {
		{_T(" 1"),	_T("123"), _T("Sales Representative"),	_T("Andrew Overling"),   _T("01.01.1981"),	_T("555-1111")},
		{_T(" 2"),	_T("321"), _T("Vice President, Sales"), _T("Janet Savolio"),	   _T("02.02.1982"),	_T("555-2222")},
		{_T(" 3"),	_T("444"), _T("Sales Representative"),	_T("Alex Romb"),		     _T("03.03.1983"),	_T("555-3333")},
		{_T(" 4"),	_T("222"), _T("Sales Manager"),					_T("Roy Trix"),				   _T("04.04.1984"),	_T("555-4444")},
		{_T(" 5"),	_T("458"), _T("Sales Representative"),	_T("Steven Puller"),		 _T("05.05.1985"),	_T("555-5555")},
		{_T(" 6"),	_T("753"), _T("Sales Manager"),					_T("Brad Hamer"),				 _T("06.06.1986"),	_T("555-6666")},
		{_T(" 7"),	_T("159"), _T("Sales Manager"),					_T("Margaret Luchanan"), _T("07.07.1987"),	_T("555-7777")},
		{_T(" 8"),	_T("111"), _T("Secretary"),							_T("Nancy Kuller"),			 _T("08.08.1988"),	_T("555-8888")},
		{_T(" 9"),	_T("777"), _T("Sales Analyst"),					_T("Anatoly Suren"),		 _T("09.09.1989"),	_T("555-9999")},
		{_T("10"),	_T("555"), _T("Cleaning Woman"),				_T("Susan Scrub"),			 _T("10.10.1990"),	_T("555-0000")}
};

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx
/////////////////////////////////////////////////////////////////////////////
CListCtrlEx::~CListCtrlEx() {
}  // ~CListCtrlEx

/////////////////////////////////////////////////////////////////////////////
// TestGetItemText
/////////////////////////////////////////////////////////////////////////////
void CListCtrlEx::TestGetItemText(UINT nRow, UINT nCol, TCHAR *szStr) {
	if(nRow < 0 || nRow >= m_nRowCount || nCol < 0 || nCol >= m_nColCount)
			wcscpy(szStr, _T("***"));
	else
			wcscpy(szStr, m_apRowText[nRow][nCol]);
}  // TestGetItemText

/////////////////////////////////////////////////////////////////////////////
// MeasureItem
/////////////////////////////////////////////////////////////////////////////
void CListCtrlEx::MeasureItem(LPMEASUREITEMSTRUCT pMIS) {
	//*** The table list height
	pMIS->itemHeight = m_nListHeight;
}  // MeasureItem

/////////////////////////////////////////////////////////////////////////////
// OnChildNotify
/////////////////////////////////////////////////////////////////////////////
BOOL CListCtrlEx::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult) {
	NMHDR *pNMHdr = reinterpret_cast<NMHDR *>(lParam);

	LV_DISPINFO *pLVDI = reinterpret_cast<LV_DISPINFO *>(lParam);
	LV_ITEM *pItem = &pLVDI->item;

	wchar_t szStr[MAXITEMTEXT];
	
	if(message == WM_NOTIFY) {
		switch(pNMHdr->code) {
			case LVN_GETDISPINFO: {
				if(pItem->mask & LVIF_TEXT) {
					TestGetItemText(pItem->iItem, pItem->iSubItem, szStr);					
					wcscpy((wchar_t *)(pItem->pszText), szStr);
				}

				break;
			}
		}
	}

	return CListCtrl::OnChildNotify(message, wParam, lParam, pResult);
}  // OnChildNotify

/////////////////////////////////////////////////////////////////////////////
// SetColItemText
/////////////////////////////////////////////////////////////////////////////
void CListCtrlEx::SetColItemText(CDC *pDC, CString& stColText, 
			CRect& TextRect, UINT nJustify) {
	int x = 0;  // x-coordinate of reference point
	int y = 0;  // y-coordinate of reference point
  UINT nOptions = 0;  // Text-output options ETO_CLIPPED|ETO_OPAQUE

	int nTextLen = stColText.GetLength();
	HDC hDC = pDC->m_hDC;
	SIZE Size = {0};

	if(!GetTextExtentPoint(hDC, stColText, nTextLen, &Size)) {
		_M("Failed to call GetTextExtentPoint for table list!");
		return;
	}

	// Align the text in the whole table
	CRect TmpRect(TextRect);

	// x-coordinate of reference point
	x = (TextRect.left + TextRect.right - Size.cx)/2 - 1;
	x = (x < TextRect.left + 2) ? TextRect.left + 2 : x;

	// y-coordinate of reference point
	y = (TextRect.bottom - TextRect.top - Size.cy)/2 - 1;
	
	//*** Specifies that the current background color fills the rectangle
	nOptions |= ETO_OPAQUE;

	//*** Draw the background fast
	pDC->ExtTextOut(TextRect.left, TextRect.top, nOptions, TextRect, NULL, 0, NULL);

	TmpRect.left++;  // Cosmetic
	TmpRect.top += y;	 // y-coordinate of reference point
	TmpRect.InflateRect(-3, 0);	 // Text does not touch borders
	
	UINT nFormat = 0;

	switch(nJustify & LVCFMT_JUSTIFYMASK) {
		case LVCFMT_LEFT:
			nFormat = DT_LEFT;
			break;
		case LVCFMT_RIGHT:
			nFormat = DT_RIGHT;
			break;
		case LVCFMT_CENTER:
			nFormat = DT_CENTER;
			break;
		default:
			_M("CListCtrlEx: Error of the text formatting!");
			return;
	}

	//*** Writes the text in the TmpRect
	::DrawText(hDC, stColText, nTextLen, TmpRect, nFormat);
}  // SetColItemText

/////////////////////////////////////////////////////////////////////////////
// SetRowText
/////////////////////////////////////////////////////////////////////////////
void CListCtrlEx::SetRowText(LPDRAWITEMSTRUCT pDIS) {
	CString sItemText;

	// Retrieve the item rectangle size. 
	CRect TextRect = pDIS->rcItem;

	// You should get the pointer to the device context from the "pDIS" ptr.
	CDC *pDC = CDC::FromHandle(pDIS->hDC);
	
	//*** Selects necessary font
	pDC->SelectObject(m_pFont);

	UINT nColumn = 0;

	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT;

	while(nColumn < m_nColCount && GetColumn(nColumn, &lvc)) {
		// Get the text to be drawn and calculate its bounding rectangle
		sItemText = GetItemText(pDIS->itemID, nColumn);
		TextRect.right = TextRect.left + GetColumnWidth(nColumn);

		if(pDC->RectVisible(TextRect))
				SetColItemText(pDC, sItemText, TextRect, lvc.fmt);

		// Move the left side of the previous rect already forward to be good for 
		// the next Text. The right of the previous bounding rect is the left of 
		// the following
		TextRect.left = TextRect.right;
		
		nColumn++;
	}

	//*** Back to the old state
	pDIS->rcItem.right = TextRect.right;
	pDIS->rcItem.bottom = TextRect.bottom;

	//*** Restore system font
	pDC->SelectStockObject(SYSTEM_FONT);
}  // SetRowText

/////////////////////////////////////////////////////////////////////////////
// DrawItem
/////////////////////////////////////////////////////////////////////////////
void CListCtrlEx::DrawItem(LPDRAWITEMSTRUCT pDIS) {
	if(pDIS->itemID == -1)
			return;

	// You should get the pointer to the device context from the "pDIS" ptr.
	CDC *pDC = CDC::FromHandle(pDIS->hDC);

	switch(pDIS->itemAction) {	
		case ODA_DRAWENTIRE: {
			//*** Populate the listview with column text
			SetRowText(pDIS);
			break;
		} 
		default: {
			TCHAR szStr[MAXITEMTEXT];

			swprintf(
					szStr, 
					_T("CGridListEx::DrawItem : Unexpected case in switch : %i"),
					pDIS->itemAction
					);

			_M(szStr);
		}
	}
}  // DrawItem

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
