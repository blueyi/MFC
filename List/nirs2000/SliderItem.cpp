// SliderItem.cpp : implementation file
//

#include "stdafx.h"
#include "sample.h"
#include "SliderItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSliderItem

CSliderItem::CSliderItem( int nItem, int nSubItem)
{
	//EnableAutomation();
	m_nItem		= nItem;
	m_nSubItem	= nSubItem;

	m_bVK_ESCAPE = FALSE;
}

CSliderItem::~CSliderItem()
{
}

void CSliderItem::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CSliderCtrl::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CSliderItem, CSliderCtrl)
	//{{AFX_MSG_MAP(CSliderItem)
	ON_WM_NCDESTROY()
	ON_WM_CHAR()
	ON_WM_KILLFOCUS()
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CSliderItem, CSliderCtrl)
	//{{AFX_DISPATCH_MAP(CSliderItem)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ISliderItem to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {F93D8D8D-D847-44EB-BAA2-1A2A489AC389}
static const IID IID_ISliderItem =
{ 0xf93d8d8d, 0xd847, 0x44eb, { 0xba, 0xa2, 0x1a, 0x2a, 0x48, 0x9a, 0xc3, 0x89 } };

BEGIN_INTERFACE_MAP(CSliderItem, CSliderCtrl)
	INTERFACE_PART(CSliderItem, IID_ISliderItem, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSliderItem message handlers

BOOL CSliderItem::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if( pMsg->message == WM_KEYDOWN )	
	{		
		if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)	
		{
			::TranslateMessage(pMsg);
			::DispatchMessage(pMsg);			
			return 1;
		}	
	}	
	return CSliderCtrl::PreTranslateMessage(pMsg);
}

void CSliderItem::OnNcDestroy() 
{
	CSliderCtrl::OnNcDestroy();
	
	// TODO: Add your message handler code here
	delete this;
}

void CSliderItem::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(nChar == VK_ESCAPE || nChar == VK_RETURN)	
	{		
		if( nChar == VK_ESCAPE)
			m_bVK_ESCAPE = 1;
		GetParent()->SetFocus();		
		return;	
	}	
	CSliderCtrl::OnChar(nChar, nRepCnt, nFlags);
}

void CSliderItem::OnKillFocus(CWnd* pNewWnd) 
{
	CSliderCtrl::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
/*
	int nIndex = GetCurSel();

	CString str;	
	GetWindowText(str);
	// Send Notification to parent of ListView ctrl	
	LV_DISPINFO lvDispinfo;
	lvDispinfo.hdr.hwndFrom = GetParent()->m_hWnd;
	lvDispinfo.hdr.idFrom = GetDlgCtrlID();//that's us
	lvDispinfo.hdr.code = LVN_ENDLABELEDIT;
	lvDispinfo.item.mask = LVIF_TEXT | LVIF_PARAM;	
	lvDispinfo.item.iItem = m_nItem;
	lvDispinfo.item.iSubItem = m_nSubItem;
	lvDispinfo.item.pszText = m_bVK_ESCAPE ? NULL : LPTSTR((LPCTSTR)str);
	lvDispinfo.item.cchTextMax = str.GetLength();
	lvDispinfo.item.lParam = GetItemData(GetCurSel());
	if(nIndex!=CB_ERR)
		GetParent()->GetParent()->SendMessage(
		WM_NOTIFY,
		GetParent()->GetDlgCtrlID(),
		(LPARAM)&lvDispinfo);
	PostMessage(WM_CLOSE);*/

}

int CSliderItem::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CSliderCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CFont* font = GetParent()->GetFont();	
	SetFont(font);

	SetRange(0,100); 
	SetPageSize(10);
	SetLineSize(1); 

	SetFocus();	
	return 0;
}

void CSliderItem::OnSize(UINT nType, int cx, int cy) 
{
	CSliderCtrl::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}
