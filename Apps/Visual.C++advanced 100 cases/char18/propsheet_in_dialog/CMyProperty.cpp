#include "stdafx.h"
#include "CMyProperty.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CMyPropertySheet

CMyPropertySheet::CMyPropertySheet()
{
}

CMyPropertySheet::~CMyPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CMyPropertySheet, CTabCtrl)
        //{{AFX_MSG_MAP(CMyPropertySheet)
        ON_NOTIFY_REFLECT(TCN_SELCHANGE, OnSelchange)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Change the tab on the top
void CMyPropertySheet::OnSelchange(NMHDR* pNMHDR, LRESULT* pResult)
{
	SetActivePage (GetCurSel ());
	*pResult = 0;
}


////////////////////////////////////////////////////////////////////////////

// This page will be the active page
int CMyPropertySheet::SetActivePage (int nPage) {
	CMyPropertyPage*	pPropPage;

	int		nN;
	if (nPage < 0 || nPage > m_nPages) nPage = 0;
	
	// get the actual page
	pPropPage = (CMyPropertyPage *) m_Dialogs.GetAt (m_nActPage);
	// deactevate it
	nN = pPropPage->m_pDialogPage->SetWindowPos (NULL,
		pPropPage->m_Rect.left, pPropPage->m_Rect.top, 0, 0, SWP_HIDEWINDOW |
		SWP_NOSIZE);

	// get the new page
	pPropPage = (CMyPropertyPage *) m_Dialogs.GetAt (nPage);
	nN = pPropPage->m_pDialogPage->SetWindowPos (NULL,
		pPropPage->m_Rect.left, pPropPage->m_Rect.top, 0, 0, SWP_SHOWWINDOW |
		SWP_NOSIZE);
	
	m_nActPage = nPage;

	// set the CTabCtrl-element
	SetCurSel(m_nActPage);

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////

// Set this page as the active page
int CMyPropertySheet::SetActivePage (CMyPropDialog* pPage){
	CMyPropertyPage*	pPropPage;
	int	nPage, nPageFound=0;
	for (nPage = 0; nPage <= m_nPages; nPage++) {
		pPropPage = (CMyPropertyPage *) m_Dialogs.GetAt (nPage);
		if (pPropPage->m_pDialogPage == pPage) {
			nPageFound = nPage;
			break;
		}
	}

	SetActivePage (nPageFound);
	
	return TRUE;
}
////////////////////////////////////////////////////////////////////////////

// Show the next or previous page
int CMyPropertySheet::DispPage (int nCommand){
	int	nPage;
	nPage = m_nActPage;

	if (nCommand == ID_NEXT_FIELD) 
		nPage++;
	else
		nPage--;

	// are there correct page numbers?
	if (nPage < 0) nPage = m_nPages;
	if (nPage > m_nPages) nPage = 0;

	SetActivePage (nPage);
	return TRUE;
}
////////////////////////////////////////////////////////////////////////////

// Get page number X
CMyPropDialog* CMyPropertySheet::GetPage (int nPage){
	CMyPropertyPage*	pPropPage;

	if (nPage < 0 || nPage > m_nPages) nPage = 0;

	pPropPage = (CMyPropertyPage *) m_Dialogs.GetAt (nPage);
	return pPropPage->m_pDialogPage;
}

////////////////////////////////////////////////////////////////////////////

// Get the active = current page
CMyPropDialog* CMyPropertySheet::GetActivePage (void){
	CMyPropertyPage*	pPropPage;

	pPropPage = (CMyPropertyPage *) m_Dialogs.GetAt (m_nActPage);
	return pPropPage->m_pDialogPage;
	
}

////////////////////////////////////////////////////////////////////////////

// Get the number of possible pages
int CMyPropertySheet::GetPageCount (void) {
	return	m_nPages;
}
	

////////////////////////////////////////////////////////////////////////////

// CMyPropDialog 
CMyPropDialog::CMyPropDialog(CWnd* pParent /*=NULL*/)
	: CDialog()
//	: CDialog(CMyPropDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyPropDialog)
		// 
	//}}AFX_DATA_INIT
}


void CMyPropDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyPropDialog)
		// 
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyPropDialog, CDialog)
	//{{AFX_MSG_MAP(CMyPropDialog)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////

// Messages for CMyPropDialog 

////////////////////////////////////////////////////////////////////////////

// handle CTRL-PGUP & PGDN
BOOL CMyPropDialog::PreTranslateMessage(MSG* pMsg) 
{
	// TODO:

	//First Property Sheet tab key translation
	//Ctrl+PageUp, and Ctrl+PageDown 

	if (pMsg->message == WM_KEYDOWN && GetAsyncKeyState(VK_CONTROL) < 0 &&
		pMsg->wParam == VK_PRIOR) {
		((CMyPropertySheet *) GetParent ())->DispPage (ID_PREV_FIELD);
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && GetAsyncKeyState(VK_CONTROL) < 0 &&
		pMsg->wParam == VK_NEXT) {
		((CMyPropertySheet *) GetParent ())->DispPage (ID_NEXT_FIELD);
		return TRUE;
	}
		
	
	return CDialog::PreTranslateMessage(pMsg);
}

////////////////////////////////////////////////////////////////////////////

// 
BOOL CMyPropDialog::OnCmdMsg(UINT nID, int nCode, void* pExtra,
AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// TODO: do nothing here
	return CDialog::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


////////////////////////////////////////////////////////////////////////////

// CTabCtrl-Handling
BOOL CMyPropertySheet::PreTranslateMessage(MSG* pMsg) 
{
	// TODO:

	// First Property Sheet tab key translation
	// Ctrl+PageUp, and Ctrl+PageDown 

	if (pMsg->message == WM_KEYDOWN && GetAsyncKeyState(VK_CONTROL) < 0 &&
		pMsg->wParam == VK_PRIOR) {
		DispPage (ID_PREV_FIELD);
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && GetAsyncKeyState(VK_CONTROL) < 0 &&
		pMsg->wParam == VK_NEXT) {
		DispPage (ID_NEXT_FIELD);
		return TRUE;
	}
		
	return CTabCtrl::PreTranslateMessage(pMsg);
}

void CMyPropertySheet::PostNcDestroy() 
{
	// TODO: Free and unlock
	
	int		nN;
	CMyPropertyPage*	pPropPage;

	// pPropPages deleten
	for (nN = 0; nN <= m_nPages; nN++) {
		//  get page per page
		pPropPage = (CMyPropertyPage *) m_Dialogs.GetAt (0);
		if (pPropPage->m_hLocal) {	// you created the dialog on the fly?
			LocalUnlock (pPropPage->m_hLocal);	//pBuffer =
							// (BYTE*)LocalLock(pPropPage->m_hLocal);
			LocalFree (pPropPage->m_hLocal);	// LocalAlloc(LHND, nBufferSize);
		}
		m_Dialogs.RemoveAt (0);
		delete (pPropPage);
	}
	CTabCtrl::PostNcDestroy();
	// delete (this);		// free Resources
	// only needed if you work with NEW
}

void CMyPropDialog::PostNcDestroy() 
{
	// TODO: 
	
	CDialog::PostNcDestroy();
	delete (this);		// free it
}


////////////////////////////////////////////////////////////////////////////


