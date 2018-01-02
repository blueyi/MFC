// EditList.cpp : implementation file
//

#include "stdafx.h"
#include "ComboItem.h"
#include "EditItem.h"
#include "SliderItem.h"
#include "EditList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditList

CEditList::CEditList()
{
	m_fGetType = NULL;
	m_pSliderCtrl=NULL;
}

CEditList::~CEditList()
{
}


BEGIN_MESSAGE_MAP(CEditList, CListCtrl)
	//{{AFX_MSG_MAP(CEditList)
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndlabeledit)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_NOTIFY_REFLECT(LVN_KEYDOWN, OnKeydown)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditList message handlers

void CEditList::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO *plvDispInfo = (LV_DISPINFO*)pNMHDR;
 	LV_ITEM *plvItem = &plvDispInfo->item;

	if( plvItem->iItem != -1 &&  // valid item
		plvItem->pszText )		// valid text
	{
		SetItemText( plvItem->iItem, plvItem->iSubItem, plvItem->pszText);				
		
		// this will invoke an ItemChanged handler in parent
		if ( plvItem->iSubItem != 0 )
		{
			char szText[0x10+1];
			GetItemText( plvItem->iItem, 0, szText, 0x10);				
			SetItemText( plvItem->iItem, 0, szText);				
		}	
	}

	*pResult = 0;
}


void CEditList::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if( GetFocus() != this) 
		SetFocus();

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if ( m_fGetType && m_fGetType( pNMListView->iSubItem ) == eCombo )
	{
		ComboItem(pNMListView->iItem, pNMListView->iSubItem);
	}else if ( m_fGetType && m_fGetType( pNMListView->iSubItem ) == eSlider )
	{
		SliderItem(pNMListView->iItem, pNMListView->iSubItem);
	}else
	{
		EditItem (pNMListView->iItem, pNMListView->iSubItem);
	}

	*pResult = 0;
}

BOOL CEditList::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style |= WS_CHILD |
				LVS_REPORT |
				LVS_SINGLESEL |
				LVS_SHOWSELALWAYS;	
	return CListCtrl::PreCreateWindow(cs);
}



void CEditList::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;

	switch(pLVKeyDow->wVKey)
	{
		case VK_DELETE: 
			{
				int nItem = GetSelectionMark();
				if(nItem!=-1) // valid item 					
				{
					DeleteItem( nItem );
				}
			}	break;

		default :break;
	}
	*pResult = 0;

}

int CEditList::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here	
	SetExtendedStyle( GetExtendedStyle() | LVS_EX_CHECKBOXES );
	
	return 0;
}

CComboBox * CEditList::ComboItem(int nItem, int nSubItem)
{
	CString strFind = GetItemText(nItem, nSubItem);

	//basic code start
	CRect rect;
	int offset = 0;
	// Make sure that the item is visible
	if( !EnsureVisible(nItem, TRUE)) 
		return NULL;

	GetSubItemRect(nItem, nSubItem, LVIR_BOUNDS, rect);
	// Now scroll if we need to expose the column
	CRect rcClient;
	GetClientRect(rcClient);
	if( offset + rect.left < 0 || offset + rect.left > rcClient.right )
	{
		CSize size;
		size.cx = offset + rect.left;
		size.cy = 0;
		Scroll(size);
		rect.left -= size.cx;
	}
	
	rect.left += offset;	
	rect.right = rect.left + GetColumnWidth(nSubItem);
	if(rect.right > rcClient.right) 
	   rect.right = rcClient.right;
	//basic code end

	rect.bottom += 40 * rect.Height();//dropdown area
	
	DWORD dwStyle =  WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL|CBS_DROPDOWNLIST | CBS_DISABLENOSCROLL;
	CComboBox *pList = new CComboItem(nItem, nSubItem, &m_strList);
	pList->Create(dwStyle, rect, this, IDC_COMBOBOXINLISTVIEW);
	pList->ModifyStyleEx(0,WS_EX_CLIENTEDGE);//can we tell at all
	
	pList->ShowDropDown();
	pList->SelectString(-1, strFind.GetBuffer(1));

	return pList;
}

CEdit *CEditList::EditItem(int nItem, int nSubItem)
{
	CRect rect;
	int offset = 0;
	if(!EnsureVisible(nItem, TRUE))
	{ 
		return NULL;	
	}
	
	GetSubItemRect(nItem, nSubItem, LVIR_BOUNDS, rect);
	// Now scroll if we need to expose the column
	CRect rcClient;
	GetClientRect(rcClient);
	if( offset + rect.left < 0 || offset + rect.left > rcClient.right )
	{
		CSize size(offset + rect.left,0);		
		Scroll(size);
		rect.left -= size.cx;
	}
	rect.left += offset;	
	rect.right = rect.left + GetColumnWidth(nSubItem);
	if(rect.right > rcClient.right) 
		rect.right = rcClient.right;
	
	// Get Column alignment	
	LV_COLUMN lvcol;
	lvcol.mask = LVCF_FMT;
	GetColumn(nSubItem, &lvcol);
	
	DWORD dwStyle;
	if((lvcol.fmt & LVCFMT_JUSTIFYMASK) == LVCFMT_LEFT)
		dwStyle = ES_LEFT;
	else if((lvcol.fmt & LVCFMT_JUSTIFYMASK) == LVCFMT_RIGHT)
		dwStyle = ES_RIGHT;
	else 
		dwStyle = ES_CENTER;	
	
	
	dwStyle |=WS_BORDER|WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL;
	CEdit *pEdit = new CEditItem(nItem, nSubItem, GetItemText(nItem, nSubItem));
	
	pEdit->Create(dwStyle, rect, this, IDC_EDITCTRL);
	
	return pEdit;
}

CSliderCtrl* CEditList::SliderItem(int nItem, int nSubItem)
{	
	//basic code start
	CRect rect;
	int offset = 0;
	// Make sure that the item is visible
	if( !EnsureVisible(nItem, TRUE)) 
		return NULL;
	
	GetSubItemRect(nItem, nSubItem, LVIR_BOUNDS, rect);
	// Now scroll if we need to expose the column
	CRect rcClient;
	GetClientRect(rcClient);
	if( offset + rect.left < 0 || offset + rect.left > rcClient.right )
	{
		CSize size;
		size.cx = offset + rect.left;
		size.cy = 0;
		Scroll(size);
		rect.left -= size.cx;
	}
	
	rect.left += offset;	
	rect.right = rect.left + GetColumnWidth(nSubItem);
	if(rect.right > rcClient.right) 
		rect.right = rcClient.right;
	//basic code end
	
	DWORD dwStyle = TBS_HORZ|TBS_NOTICKS|TBS_BOTH;  
	CSliderCtrl *pSlider = new CSliderItem(nItem,nSubItem);
	pSlider->Create(dwStyle,rect,this,IDC_SLIDERINLISTVIEW);
	pSlider->ShowWindow(SW_SHOW);
	pSlider->ModifyStyle(0,WS_EX_CLIENTEDGE);

	m_pSliderCtrl=pSlider;
	return pSlider;

}


BOOL CEditList::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class

	if (m_pSliderCtrl)
	{
		int i=m_pSliderCtrl->GetPos();
		if (i>50)
		{
			MessageBox("Slider Pos > 50");
		}
	}

	return CListCtrl::OnNotify(wParam, lParam, pResult);
}