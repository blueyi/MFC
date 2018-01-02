// TestSheet.cpp : implementation file
//

#include "stdafx.h"
#include "splitter.h"
#include "TestSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestSheet

IMPLEMENT_DYNAMIC(CTestSheet, CPropertySheet)

CTestSheet::CTestSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CTestSheet::CTestSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CTestSheet::~CTestSheet()
{
}


BOOL CTestSheet::OnInitDialog()
{
   CPropertySheet::OnInitDialog();
   ModifyStyle(0,WS_THICKFRAME);
//   return TRUE;
  
   RECT rc;

   int cx = GetSystemMetrics(SM_CXMAXIMIZED);
   int cy = GetSystemMetrics(SM_CYMAXIMIZED) - 5;

   // resize the sheet
   GetWindowRect (&rc);
   ScreenToClient (&rc);

   int dx1 = -rc.left;
   int dx2 = cx-rc.right;
   int dy1 = -rc.top;
   int dy2 = cy-rc.bottom;

   rc.left += dx1;
   rc.top   += dy1;
   rc.right += dx2;
   rc.bottom += dy2;
   MoveWindow (&rc);

   // resize the CTabCtrl
   CTabCtrl* pTab = GetTabControl();
   ASSERT (pTab);
   pTab->GetWindowRect (&rc);
   ScreenToClient (&rc);
   rc.right += dx2;
   rc.bottom += dy2 - 5;
   pTab->MoveWindow (&rc);

   // resize the page
   CPropertyPage* pPage = GetActivePage();
   ASSERT (pPage);
   // store page size in m_PageRect
   pPage->GetWindowRect (&m_PageRect);
   ScreenToClient (&m_PageRect);
   m_PageRect.right += dx2;
   m_PageRect.bottom += dy2 - 5;
   pPage->MoveWindow (&m_PageRect);

   // move the OK, Cancel, and Apply buttons
   GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
   GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);
   GetDlgItem(ID_APPLY_NOW)->ShowWindow(SW_HIDE);
   GetDlgItem(IDHELP)->ShowWindow(SW_HIDE);
   	    

 	if (m_statusBar.Create(this))
	{                           
	}             

   // And position the control bars
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0); 

  
	// Finally, center the dialog on the screen
	CenterWindow();

  return TRUE;
}

#define WM_RESIZEPAGE WM_USER + 111

BEGIN_MESSAGE_MAP(CTestSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CTestSheet)
  ON_MESSAGE (WM_RESIZEPAGE, OnResizePage)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestSheet message handlers
BOOL CTestSheet::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
   NMHDR* pnmh = (LPNMHDR) lParam;

   // the sheet resizes the page whenever it is activated
   // so we need to resize it to what we want
   if (TCN_SELCHANGE == pnmh->code)
       // user-defined message needs to be posted because page must
       // be resized after TCN_SELCHANGE has been processed
       PostMessage (WM_RESIZEPAGE);

   return CPropertySheet::OnNotify(wParam, lParam, pResult);
}


LONG CTestSheet::OnResizePage(UINT, LONG)
{
   // resize the page using m_PageRect which was set in OnInitDialog()
   CPropertyPage* pPage = GetActivePage();
   ASSERT (pPage);
   pPage->MoveWindow (&m_PageRect);

   return 0;
}