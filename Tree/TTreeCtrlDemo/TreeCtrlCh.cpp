// TreeCtrlCh.cpp : implementation file
//Written By Ran Wainstein 02/01/2002 
//Thanks to yaniv ben ari 

#include "stdafx.h"
#include "TreeCtrlCh.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlCh

CTreeCtrlCh::CTreeCtrlCh()
{
}

CTreeCtrlCh::~CTreeCtrlCh()
{

}


BEGIN_MESSAGE_MAP(CTreeCtrlCh, CTreeCtrl)
	//{{AFX_MSG_MAP(CTreeCtrlCh)
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlCh message handlers

void CTreeCtrlCh::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CTreeCtrl::PreSubclassWindow();
	EnableToolTips(TRUE);
}


int CTreeCtrlCh::OnToolHitTest(CPoint point, TOOLINFO * pTI) const
{
	RECT rect;

	UINT nFlags;
	HTREEITEM hitem = HitTest( point, &nFlags );
	if( nFlags & TVHT_ONITEMLABEL  )
	{
	

		GetItemRect( hitem, &rect, TRUE );
		pTI->hwnd = m_hWnd;
		pTI->uId = (UINT)hitem;
		pTI->lpszText = LPSTR_TEXTCALLBACK;
		pTI->rect = rect;
		return pTI->uId;
	}
	
	return -1;
}

//here we supply the text for the item 
BOOL CTreeCtrlCh::OnToolTipText( UINT id, NMHDR * pNMHDR, LRESULT * pResult )
{
	// need to handle both ANSI and UNICODE versions of the message
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	CString strTipText;
	UINT nID = pNMHDR->idFrom;
	// Do not process the message from built in tooltip 
	if( nID == (UINT)m_hWnd &&
		(( pNMHDR->code == TTN_NEEDTEXTA && pTTTA->uFlags & TTF_IDISHWND ) ||
		( pNMHDR->code == TTN_NEEDTEXTW && pTTTW->uFlags & TTF_IDISHWND ) ) )
		return FALSE;

	// Get the mouse position
	const MSG* pMessage;
	CPoint pt;
	pMessage = GetCurrentMessage(); // get mouse pos 
	ASSERT ( pMessage );
	pt = pMessage->pt;
	ScreenToClient( &pt );

	UINT nFlags;
	HTREEITEM hitem = HitTest( pt, &nFlags ); //Get item pointed by mouse

	
	strTipText.Format( "%s", GetItemText( (HTREEITEM ) nID));  //get item text
	DWORD dw = GetItemData((HTREEITEM ) nID); //get item data
	ItemDataABSTRACT* ItemData = (ItemDataABSTRACT*)dw; //CAST item data
	if (ItemData!=NULL)
	{
		CString s = ItemData->GetToolTipString(); //pure virtual function
		strTipText=" " + s; //add node text to node data text
	}
#ifndef _UNICODE
	if (pNMHDR->code == TTN_NEEDTEXTA)
		lstrcpyn(pTTTA->szText, strTipText, 80);
	else
		_mbstowcsz(pTTTW->szText, strTipText, 80);
#else
	if (pNMHDR->code == TTN_NEEDTEXTA)
		_wcstombsz(pTTTA->szText, strTipText, 80);
	else
		lstrcpyn(pTTTW->szText, strTipText, 80);
#endif
	*pResult = 0;

	return TRUE;    // message was handled
}

 


//delete all allocated mamory for item data 
void CTreeCtrlCh::CleanItemData()
{

	HTREEITEM root = GetFirstVisibleItem();
	if (root==NULL)
		return ;
	do 
	{
		
		DWORD data = GetItemData(root);
		if (data!=NULL)
		{
			ItemDataABSTRACT* ItemData = (ItemDataABSTRACT*)data;

			delete ItemData ;
		}
		DeleteBranchData(root);
		
	}while ((root = GetNextSiblingItem(root))!=NULL);
	
}


void CTreeCtrlCh::OnDestroy() 
{
	CleanItemData();
	CTreeCtrl::OnDestroy();
	
	// TODO: Add your message handler code here
	
}


void CTreeCtrlCh::DeleteBranchData( HTREEITEM hti)
{
        if( ItemHasChildren( hti ) )
		{
			
            hti = GetChildItem( hti );
            do
			{

				DWORD data = GetItemData(hti);
				if (data!=NULL)
				{
					ItemDataABSTRACT* ItemData = (ItemDataABSTRACT*)data;

					delete ItemData ;
				}

		
               DeleteBranchData( hti);
            }while( (hti = GetNextSiblingItem( hti )) != NULL );
        }
        
}

