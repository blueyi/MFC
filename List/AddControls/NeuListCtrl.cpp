// NeuListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "NeuListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNeuListCtrl


CNeuListCtrl::CNeuListCtrl()
{
	m_pControlPtrArray = new CPtrArray();
	m_iCurSelctedItemIndex = -1;
	m_iControlIDCounter = 786;
}

CNeuListCtrl::~CNeuListCtrl()
{
	ReleaseControls();
}


BEGIN_MESSAGE_MAP(CNeuListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CNeuListCtrl)
	ON_WM_KEYDOWN()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNeuListCtrl message handlers


BOOL CNeuListCtrl::Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID )
{
	BOOL bCreated = CListCtrl::Create(dwStyle, rect, pParentWnd,nID );
	return bCreated;
}

void CNeuListCtrl::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(m_iCurSelctedItemIndex > -1)
	{
		GetAndDisplayControlsData();
	}
	
	NM_LISTVIEW * pNMListView = (NM_LISTVIEW*) pNMHDR;
	
	if(pNMListView->iItem < 0 || pNMListView->iSubItem < 0)
	{
		return;
	}
	int iItem = pNMListView->iItem;
	m_iCurSelctedItemIndex = iItem;
	m_iSubItem = pNMListView->iSubItem;
	
	/*LVHITTESTINFO hittestinfo;
	hittestinfo.iItem = iItem;
	hittestinfo.iSubItem = m_iSubItem;
	hittestinfo.pt = pNMListView->ptAction;
	HitTest(&hittestinfo);
	*/	
	if(iItem >= 0)
	{
		BOOL bChecked = TRUE;
	/*	BOOL bChecked = GetCheck(iItem);

		if(hittestinfo.flags == LVHT_ONITEMSTATEICON)
		{	
			bChecked = !bChecked;
		}
	*/
		MapControlsForSubItems();
		ShowControls(TRUE);
		EnableControls(bChecked);
		SetItemState(m_iCurSelctedItemIndex,LVIS_SELECTED,LVIS_SELECTED);
	}
	
	*pResult = 0;
}

BOOL CNeuListCtrl::DestroyWindow() 
{
	return CListCtrl::DestroyWindow();
}

void CNeuListCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CListCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
	return; 
	switch(nChar)
	{
		case VK_UP:
			if(m_iCurSelctedItemIndex-1 > -1)
				m_iCurSelctedItemIndex--;
		break;
		case VK_DOWN:
			if(m_iCurSelctedItemIndex+1 < GetItemCount())
				m_iCurSelctedItemIndex++;
		break;
		case VK_LEFT:
			 if(m_iSubItem-1 < -1)
				 m_iSubItem--;
		break;
		case VK_RIGHT:
			if(m_iSubItem +1 < GetHeaderCtrl()->GetItemCount())
				m_iSubItem++;
		break;

	}
	BOOL bChecked = GetCheck(m_iCurSelctedItemIndex );
	ShowControls(TRUE);
	EnableControls(bChecked);
	MapControlsForSubItems();
	SetItemState(m_iCurSelctedItemIndex,LVIS_SELECTED,LVIS_SELECTED);
}

void CNeuListCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect  rc;
	GetParent()->GetClientRect(&rc);

	if (rc.Size() == CSize(0,0))
		return;

	CDC     MemoryDC;
	CBitmap Bitmap;
	CBrush  Brush;

	CRect rcWnd;
	GetWindowRect(&rcWnd);
	int rcWndW = rcWnd.Width(), rcWndH = rcWnd.Height();

	// Paint to a compatible DC
	MemoryDC.CreateCompatibleDC(&dc);
	Bitmap.CreateCompatibleBitmap(&dc, rcWndW, rcWndH);
	CBitmap *pOldBitmap = MemoryDC.SelectObject(&Bitmap);

	// Fill background (does what WM_ERASEBKGND would do)
	Brush.CreateSolidBrush(GetBkColor());
	MemoryDC.FillRect(&CRect(0,0, rcWndW,rcWndH), &Brush);

	Print(&MemoryDC, PRF_CLIENT|PRF_CHILDREN);
	Print(&MemoryDC, PRF_NONCLIENT);

	// Offset the MemoryDC drawing rectangle by rcBounds 
	CRect rcDraw = rc - rc.TopLeft();

	// Dump bits to real device context.
	dc.BitBlt(rc.left,rc.top, rc.Width(),rc.Height(), &MemoryDC, rcDraw.left,rcDraw.top, SRCCOPY);

	MemoryDC.SelectObject(pOldBitmap);
	

	CListCtrl::OnPaint();
}

BOOL CNeuListCtrl::OnEraseBkgnd(CDC* pDC) 
{
	return true;
}

void CNeuListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
	
	LockWindowUpdate();
	
	///////// Check Item is in Visible Area ///////////////

	BOOL bShowItem = FALSE;
	int iTopMostItemIndex = GetTopIndex();
	for(int i = iTopMostItemIndex ; i < (iTopMostItemIndex + GetCountPerPage() ) ; i++)
	{
		if(m_iCurSelctedItemIndex == i)
		{
			bShowItem = TRUE;
			break;
		}
	}
	
	ShowControls(FALSE);
	/////////////////////////////////////////////////////	
	switch(nSBCode)
	{
		case SB_BOTTOM :
			
			break;
		case SB_ENDSCROLL:
			if(bShowItem)
			{
				ShowControls(TRUE);
				MapControlsForSubItems();
			}
			break;
		case SB_LINEDOWN :
			break;

		case SB_LINEUP:
			break;
		case SB_PAGEDOWN:
			break;
		case SB_PAGEUP	:
			break;
		case SB_THUMBPOSITION :
			break;
		case SB_THUMBTRACK	:
			break;
		case SB_TOP :
			break;
	}
	UnlockWindowUpdate();
}

void CNeuListCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CListCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
	
	LockWindowUpdate();
	
	///////// Check Item is in Visible Area ///////////////

	BOOL bShowItem = FALSE;
	int iTopMostItemIndex = GetTopIndex();
	for(int i = iTopMostItemIndex ; i < (iTopMostItemIndex + GetCountPerPage() ) ; i++)
	{
		if(m_iCurSelctedItemIndex == i)
		{
			bShowItem = TRUE;
			break;
		}
	}
	
	ShowControls(FALSE);
	/////////////////////////////////////////////////////	
	switch(nSBCode)
	{
		case SB_BOTTOM :
			
			break;
		case SB_ENDSCROLL:
			if(bShowItem)
			{
				ShowControls(TRUE);
				MapControlsForSubItems();
			}
			break;
		case SB_LINERIGHT:
			break;
		case SB_LINELEFT :
			break;
		case SB_PAGELEFT:
			break;
		case SB_PAGERIGHT	:
			break;
		case SB_THUMBPOSITION :
			break;
		case SB_THUMBTRACK	:
			break;
		case SB_TOP :
			break;
	}
	UnlockWindowUpdate();
}



void CNeuListCtrl::SetItemControl(enCONTROLTYPE enControlType,int iIndex)
{
	SubItemControlsInfo * pSubItemInfo = new SubItemControlsInfo();
	pSubItemInfo->m_enControlType = enControlType;
	pSubItemInfo->m_iItemIndex = iIndex;
	if(m_iCurSelctedItemIndex < 0)
		m_iCurSelctedItemIndex = 0;

	CFont * pFont = GetFont();
	DWORD dwStyle = WS_BORDER|WS_CHILD | WS_TABSTOP;
	CRect ControlSize (10, 10, 100, 100);
	
	switch(enControlType)
	{
		case EDITBOX:
			pSubItemInfo->m_pWnd = new CEdit();
			((CEdit*)pSubItemInfo->m_pWnd)->Create (dwStyle|ES_NUMBER,ControlSize,this ,m_iControlIDCounter);	
			break;
		case CHECKBOX:
			pSubItemInfo->m_pWnd = new CButton();
			((CButton*)pSubItemInfo->m_pWnd)->Create ("",dwStyle|BS_AUTOCHECKBOX,ControlSize,this ,m_iControlIDCounter);	
	
			break;
		case COMBOBOX:
			pSubItemInfo->m_pWnd = new CComboBox();
			((CComboBox*)pSubItemInfo->m_pWnd)->Create(dwStyle|WS_VSCROLL|CBS_DROPDOWNLIST,ControlSize, this,m_iControlIDCounter);
			break;
		case LISTBOX:
			pSubItemInfo->m_pWnd = new CListBox();
			((CListBox*)pSubItemInfo->m_pWnd)->Create (WS_VSCROLL|dwStyle,ControlSize,this ,m_iControlIDCounter);
			break;
		case BUTTON:
			pSubItemInfo->m_pWnd = new CButton();
			((CButton*)pSubItemInfo->m_pWnd)->Create ("",dwStyle,ControlSize,this ,m_iControlIDCounter);
			break;
	}
	pSubItemInfo->m_pWnd->SetFont(pFont);
	int iDupIndex = ControlIndexDuplicating(iIndex);

	if(iDupIndex > -1)
	{
		DetachControl(iDupIndex);
	}
	m_pControlPtrArray->Add(pSubItemInfo);
	if(enControlType != NONE)
	{
		m_iControlIDCounter+=4;
	}
}

void CNeuListCtrl::MapControlsForSubItems()
{
	int iItem = m_iCurSelctedItemIndex;
	CRect CtrlRect;
	CRect iconRect;
	SubItemControlsInfo * pSubItemControlsInfo;

	CString strData = "";
	for(int i =0 ;i <m_pControlPtrArray->GetSize() ;i++)
	{
		pSubItemControlsInfo = (SubItemControlsInfo *) m_pControlPtrArray->GetAt(i);

		if(pSubItemControlsInfo)
		{
			GetSubItemRect(iItem,pSubItemControlsInfo->m_iItemIndex,LVIR_LABEL,CtrlRect);
			GetSubItemRect(iItem,pSubItemControlsInfo->m_iItemIndex,LVIR_ICON,iconRect);
			
			CtrlRect.bottom+=3;
			if(pSubItemControlsInfo->m_iItemIndex == 0)
			{
				CtrlRect.left+=iconRect.right;
			}

			if(pSubItemControlsInfo->m_pWnd)
					pSubItemControlsInfo->m_pWnd->MoveWindow(&CtrlRect);

			strData = GetItemText(m_iCurSelctedItemIndex,pSubItemControlsInfo->m_iItemIndex);		
			
			switch(pSubItemControlsInfo->m_enControlType)
			{
				case CHECKBOX:
					strData = GetItemText(m_iCurSelctedItemIndex ,pSubItemControlsInfo->m_iItemIndex);
					((CButton*)pSubItemControlsInfo->m_pWnd)->SetCheck(strData == "TRUE");
					//strData = ((CButton*)pSubItemControlsInfo->m_pWnd)->GetCheck()?"TRUE":"FALSE";
					SetItemText(m_iCurSelctedItemIndex ,pSubItemControlsInfo->m_iItemIndex,strData);	
					break;		

				case EDITBOX:
					pSubItemControlsInfo->m_pWnd->SetWindowText(strData);
					break;

				case COMBOBOX:
					((CComboBox*)pSubItemControlsInfo->m_pWnd)->SelectString(-1,strData);
					break;
				case LISTBOX:
					((CListBox*)pSubItemControlsInfo->m_pWnd)->SelectString(-1,strData);
					CtrlRect.bottom += (((CListBox*)pSubItemControlsInfo->m_pWnd)->GetCount ()-1)*2;((CListBox*)pSubItemControlsInfo->m_pWnd)->GetItemHeight(0);
					pSubItemControlsInfo->m_pWnd->MoveWindow(&CtrlRect);
					break;
			}
		}
	}
}

void CNeuListCtrl::EnableControls(BOOL bEnable)
{
	SubItemControlsInfo * pSubItemControlsInfo;

	for(int i =0 ;i <m_pControlPtrArray->GetSize() ;i++)
	{
		pSubItemControlsInfo = (SubItemControlsInfo *) m_pControlPtrArray->GetAt(i);
		if(pSubItemControlsInfo)
		{
			if(pSubItemControlsInfo->m_pWnd)
				pSubItemControlsInfo->m_pWnd->EnableWindow(bEnable);
		}
	}
}

void CNeuListCtrl::ShowControls(BOOL bShow)
{
	SubItemControlsInfo * pSubItemControlsInfo;

	for(int i =0 ;i <m_pControlPtrArray->GetSize() ;i++)
	{
		pSubItemControlsInfo = (SubItemControlsInfo *) m_pControlPtrArray->GetAt(i);
		if(pSubItemControlsInfo)
		{
			if(pSubItemControlsInfo->m_pWnd)
				pSubItemControlsInfo->m_pWnd->ShowWindow(bShow);
		}
	}
}

BOOL CNeuListCtrl::AddToControlsData(int iIndex, CString strData)
{
	
	SubItemControlsInfo * pSubItemInfo;
	for(int i = 0 ; i < m_pControlPtrArray->GetSize(); i++)
	{
		pSubItemInfo = (SubItemControlsInfo *) m_pControlPtrArray->GetAt(i);
			
		if(pSubItemInfo->m_iItemIndex == iIndex)
		{
			switch(pSubItemInfo->m_enControlType )
			{
				case EDITBOX:case CHECKBOX:case BUTTON:
					pSubItemInfo->m_pWnd->SetWindowText(strData);
					break;
				case COMBOBOX:
					((CComboBox*)pSubItemInfo->m_pWnd)->AddString(strData);
					break;
				case LISTBOX:
					((CListBox*)pSubItemInfo->m_pWnd)->AddString(strData);
					break;
			}
			return TRUE;
		}
	}
	return FALSE;
}

HBRUSH CNeuListCtrl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CListCtrl::OnCtlColor(pDC, pWnd, nCtlColor);
	
	SubItemControlsInfo * pItemInfo;
	for(int i =0 ;i < m_pControlPtrArray->GetSize() ;i++)
	{
		pItemInfo = (SubItemControlsInfo*) m_pControlPtrArray->GetAt(i);
		if(pWnd == pItemInfo->m_pWnd)
		{
			hbr = ::CreateSolidBrush(pItemInfo->m_BKColor);
		}
	}
		
	return hbr;
}

void CNeuListCtrl::GetAndDisplayControlsData()
{
	CString strData = "";
	int iCurIndex = -1 ;
	for(int i =0 ;i < m_pControlPtrArray->GetSize();i++)
	{
		SubItemControlsInfo * pSubItemInfo;

		pSubItemInfo = (SubItemControlsInfo *) m_pControlPtrArray->GetAt(i);
			
		switch(pSubItemInfo->m_enControlType)
		{
			case CHECKBOX:
				strData = ((CButton*)pSubItemInfo->m_pWnd)->GetCheck()?"TRUE":"FALSE";
				SetItemText(m_iCurSelctedItemIndex ,pSubItemInfo->m_iItemIndex,strData);	
				break;		

			case EDITBOX:
				pSubItemInfo->m_pWnd->GetWindowText(strData);
				SetItemText(m_iCurSelctedItemIndex ,pSubItemInfo->m_iItemIndex,strData);
				break;

			case COMBOBOX:
				iCurIndex = ((CComboBox*)pSubItemInfo->m_pWnd)->GetCurSel();
				if(iCurIndex != LB_ERR)
				{
					((CComboBox*)pSubItemInfo->m_pWnd)->GetLBText(iCurIndex,strData);
					SetItemText(m_iCurSelctedItemIndex ,pSubItemInfo->m_iItemIndex,strData);
				}
				break;
			case LISTBOX:
				iCurIndex = ((CListBox*)pSubItemInfo->m_pWnd)->GetCurSel();
				if(iCurIndex != LB_ERR)
				{
					((CListBox*)pSubItemInfo->m_pWnd)->GetText(iCurIndex,strData);
					SetItemText(m_iCurSelctedItemIndex ,pSubItemInfo->m_iItemIndex,strData);
				}
				break;
		}
	}

}

BOOL CNeuListCtrl::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	SubItemControlsInfo * pSubItemInfo;
	ControlMessageInfo MessageInfo;
	if(nCode == HDN_TRACK)
	{
		AfxMessageBox("Error");
	}
	for(int i =0 ;i < m_pControlPtrArray->GetSize() ;i++)
	{
		pSubItemInfo = (SubItemControlsInfo *) m_pControlPtrArray->GetAt(i);
		if(pSubItemInfo->m_pWnd)
		{
			if(pSubItemInfo->m_pWnd->GetDlgCtrlID() == (int) nID)
			{
				for(int ii =0 ;ii < pSubItemInfo->m_arrControlMessageInfo.GetSize() ;ii++)
				{
					MessageInfo = (ControlMessageInfo)pSubItemInfo->m_arrControlMessageInfo.GetAt(ii);
					if(MessageInfo.m_iMessageID == nCode)
					{
						MessageInfo.pEventHandler(pSubItemInfo->m_pWnd);
						break;
					}
				}
			}
		}
	}
	return CListCtrl::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CNeuListCtrl::AttachEvent_HandlerForItemControl(int iIndex, UINT unMessage, void (__cdecl *pEventHandler)(LPVOID lpvoid))
{
	SubItemControlsInfo * pSubItemInfo;
	for(int i =0 ;i < m_pControlPtrArray->GetSize() ;i++)
	{
		pSubItemInfo = (SubItemControlsInfo *) m_pControlPtrArray->GetAt(i);
		if(pSubItemInfo->m_iItemIndex == iIndex)
		{	
			ControlMessageInfo MessageInfo;
			MessageInfo.m_iMessageID = unMessage;
			MessageInfo.pEventHandler = pEventHandler;
			pSubItemInfo->m_arrControlMessageInfo.Add(MessageInfo);
			break;
		}
	}
}

void CNeuListCtrl::AdjustControlsAccordingToHeaderWidth(HD_NOTIFY *pNotify)
{
	if(m_iCurSelctedItemIndex < 0 )
		return ;
	int iItem = pNotify->iItem;
	int iWidth = pNotify->pitem->cxy;
	int iSubItem = 0 ; 
	CRect CtrlRect;
	CRect iconRect;
	SubItemControlsInfo * pSubItemControlsInfo;

	CString strData = "";
	
	BOOL bSetItem = FALSE ;
	
	int iIncreaseWidth = 0;

	for(int i =0 ;i <m_pControlPtrArray->GetSize() ;i++)
	{
		pSubItemControlsInfo = (SubItemControlsInfo *) m_pControlPtrArray->GetAt(i);

		if(pSubItemControlsInfo)
		{
			GetSubItemRect(m_iCurSelctedItemIndex,pSubItemControlsInfo->m_iItemIndex,LVIR_LABEL,CtrlRect);
			GetSubItemRect(m_iCurSelctedItemIndex,pSubItemControlsInfo->m_iItemIndex,LVIR_ICON,iconRect);
			
			if(pSubItemControlsInfo->m_iItemIndex == iItem)
			{
				bSetItem = TRUE;
				if(iItem == 0)
					iIncreaseWidth = iWidth - (CtrlRect.Width()+iconRect.right);
				else
					iIncreaseWidth = iWidth - CtrlRect.Width();
			}
			else
			{
				CtrlRect.left +=iIncreaseWidth;
			}
			CtrlRect.right += iIncreaseWidth;
		
			if(pSubItemControlsInfo->m_pWnd)
			{
				if(bSetItem)
				{
					pSubItemControlsInfo->m_pWnd->MoveWindow(&CtrlRect);
				}
			}
			strData = GetItemText(m_iCurSelctedItemIndex,pSubItemControlsInfo->m_iItemIndex);		
			switch(pSubItemControlsInfo->m_enControlType)
			{
				case CHECKBOX:
					strData = ((CButton*)pSubItemControlsInfo->m_pWnd)->GetCheck()?"TRUE":"FALSE";
					SetItemText(m_iCurSelctedItemIndex ,pSubItemControlsInfo->m_iItemIndex,strData);	
					break;		
				case EDITBOX:
					pSubItemControlsInfo->m_pWnd->SetWindowText(strData);
					break;

				case COMBOBOX:
					((CComboBox*)pSubItemControlsInfo->m_pWnd)->SelectString(-1,strData);
					break;
				case LISTBOX:
					((CListBox*)pSubItemControlsInfo->m_pWnd)->SelectString(-1,strData);
					CtrlRect.bottom += (((CListBox*)pSubItemControlsInfo->m_pWnd)->GetCount ()-1)*((CListBox*)pSubItemControlsInfo->m_pWnd)->GetItemHeight(0);
					pSubItemControlsInfo->m_pWnd->MoveWindow(&CtrlRect);
					break;
			}
		}
	}
	EnableControls(TRUE);
	ShowControls(TRUE);
	Invalidate();
}

int CNeuListCtrl::ControlIndexDuplicating(int iIndex)
{
	SubItemControlsInfo  * pInfo;
	for(int i =0 ;i < m_pControlPtrArray->GetSize () ;i++)
	{
		pInfo = (SubItemControlsInfo *) m_pControlPtrArray->GetAt (i);
		if(pInfo->m_iItemIndex == iIndex)
		{
			return i;
		}
	}
	return -1;
}

void CNeuListCtrl::ReleaseControls()
{
	for(int i =0 ;i < m_pControlPtrArray->GetSize() ;i++)
	{
		DetachControl(i);
	}
}

BOOL CNeuListCtrl::DetachControl(int index)
{
	SubItemControlsInfo * pInfo;
	
	pInfo = (SubItemControlsInfo *)m_pControlPtrArray->GetAt(index);
	if(pInfo)
	{
		if(pInfo->m_pWnd)
		{
			pInfo->m_pWnd->DestroyWindow();
			pInfo->m_pWnd->m_hWnd = NULL;
			delete pInfo->m_pWnd;
			pInfo->m_pWnd = NULL;
		}
		delete pInfo;
		m_pControlPtrArray->RemoveAt(index);
		return TRUE;
	}
	return FALSE;
}

void CNeuListCtrl::SetControlBKColor(int index ,COLORREF col)
{
	SubItemControlsInfo  * pInfo;
	for(int i =0 ;i < m_pControlPtrArray->GetSize () ;i++)
	{
		pInfo = (SubItemControlsInfo *) m_pControlPtrArray->GetAt (i);
		if(pInfo->m_iItemIndex == index)
		{
			pInfo->m_BKColor = col;
		}
	}	
	Invalidate();
}


