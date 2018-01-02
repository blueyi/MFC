// IbTabCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "tabctrl.h"
#include "IbTabCtrl.h"
#include ".\ibtabctrl.h"


// CIbTabCtrl

IMPLEMENT_DYNAMIC(CIbTabCtrl, CTabCtrl)
CIbTabCtrl::CIbTabCtrl()
{
	m_iPrevPage = 0;
}

CIbTabCtrl::~CIbTabCtrl()
{
}


BEGIN_MESSAGE_MAP(CIbTabCtrl, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, OnTcnSelchange)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

// CIbTabCtrl message handlers
void CIbTabCtrl::addNewPage(CString strPage, CWnd * pPage)
{
	this->InsertItem(this->GetItemCount(),strPage);  
	pPage->ShowWindow(SW_HIDE); 
	m_oPages.Add(pPage); 
}

void CIbTabCtrl::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	CWnd * pPage;
	int iCurrent;
	iCurrent = this->GetCurFocus();
	pPage = m_oPages.GetAt(iCurrent);
	setPage(pPage);
	m_iPrevPage = iCurrent;
}

void CIbTabCtrl::setPage(CWnd* pWnd)
{
	CWnd * pPage;
	pPage = m_oPages.GetAt(m_iPrevPage);
	pPage->ShowWindow(SW_HIDE); 
	CRect oRect,oWRect,oPWRect,oIRect;
	GetItemRect(0,oIRect); 
	GetClientRect(oRect); 
	GetWindowRect(oWRect);
	GetParent()->GetWindowRect(oPWRect);   
	pWnd->SetWindowPos(this,oWRect.left-oPWRect.left,oWRect.top-oPWRect.top,oRect.Width()- 5,oRect.Height()-oIRect.Height() - 6,SWP_SHOWWINDOW);   
}

void CIbTabCtrl::setDefaultPage(int iIndex)
{
	CWnd * pPage;
	m_iPrevPage = iIndex;
	if(iIndex >=0 && iIndex < m_oPages.GetCount())
	{
		pPage = m_oPages.GetAt(iIndex);
		setPage(pPage);		
	}
}

void CIbTabCtrl::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CTabCtrl::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
}

void CIbTabCtrl::removePage(int iIndex)
{
	// TODO: Add your message handler code here

	if(m_oPages.GetCount() > 0)
	{
		if(iIndex >=0 && iIndex < m_oPages.GetCount())
		{
			
			if(iIndex < m_oPages.GetCount())
			{
				CWnd * pPage;
				pPage = m_oPages.GetAt(iIndex); 
				m_oPages.RemoveAt(iIndex); 
				pPage->DestroyWindow();
				this->DeleteItem(iIndex);
				if(m_oPages.GetCount()>0)
				{
					pPage = m_oPages.GetAt(0);
					m_iPrevPage = 0;
					setPage(pPage);
					this->SetCurFocus(0); 

				}
			}
		}
	}
}