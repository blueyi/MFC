// ListCtrlExtention.cpp : implementation file
//

#include "stdafx.h"
#include "HeaderCtrlEx.h"
#include "ListCtrlExtention.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListCtrlExtention

CListCtrlExtention::CListCtrlExtention()
{
}

CListCtrlExtention::~CListCtrlExtention()
{
}


BEGIN_MESSAGE_MAP(CListCtrlExtention, CListCtrl)
	//{{AFX_MSG_MAP(CListCtrlExtention)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlExtention message handlers

int CListCtrlExtention::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	
	m_NewHeaderFont.CreatePointFont(190,"MS Serif");

	CHeaderCtrl* pHeader = NULL;
	pHeader=GetHeaderCtrl();

	if(pHeader==NULL)
		return -1;
	
	VERIFY(m_HeaderCtrl.SubclassWindow(pHeader->m_hWnd));	

	m_HeaderCtrl.SetFont(&m_NewHeaderFont);
	HDITEM hdItem;

	hdItem.mask = HDI_FORMAT;

	for(int i=0; i<m_HeaderCtrl.GetItemCount(); i++)
	{
		m_HeaderCtrl.GetItem(i,&hdItem);

		hdItem.fmt|= HDF_OWNERDRAW;
		
		m_HeaderCtrl.SetItem(i,&hdItem);
	}
	return 0;


}
