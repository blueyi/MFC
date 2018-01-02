// splitTab.cpp : implementation file
//

#include "stdafx.h"
#include "tab.h"

#include "TabView.h"
//#include "wndTab.h"
#include "splitTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CsplitterTabWnd

IMPLEMENT_DYNCREATE(CsplitterTabWnd, CSplitterWnd)

CsplitterTabWnd::CsplitterTabWnd()
{
   m_cxSplitter    = m_cySplitter    = 0;   // size of splitter bar
   m_cxSplitterGap = m_cySplitterGap = 0;   // amount of space between panes
   m_cxBorder      = m_cyBorder      = 0;   // borders in client area
}

CsplitterTabWnd::~CsplitterTabWnd()
{
}

void CsplitterTabWnd::RecalcLayout()
{
   CWnd* pWnd;
   CRect rectClient;

   GetClientRect( rectClient );

   // Set position for the tab window
   pWnd = GetPane( 1, 0 );

   pWnd->SetWindowPos( this, 
                       rectClient.left,
                       rectClient.bottom - 20,
                       rectClient.right,
                       20,
                       SWP_NOACTIVATE|SWP_NOZORDER );

   // Set position for the working-window
   pWnd = GetPane( 0, 0 );
   pWnd->SetWindowPos( this, 
                       rectClient.left,
                       rectClient.top,
                       rectClient.right,
                       rectClient.bottom - 20, 
                       SWP_NOACTIVATE|SWP_NOZORDER );

}


BOOL CsplitterTabWnd::Create( CWnd* pwndParent, CCreateContext* pContext )
{
   SIZE  size;
   CRect rect;
   
   CreateStatic( pwndParent, 2, 1, WS_CHILD );

   pwndParent->GetClientRect( &rect );
   
   size.cx = rect.right;
   size.cy = rect.bottom - 20;
   
   VERIFY( CreateView( 0, 0, RUNTIME_CLASS(CTabView), size, pContext ) );

   size.cy = 20;
   VERIFY( CreateView( 1, 0, RUNTIME_CLASS(CwndTab), size, pContext ) );

   
   
   ShowWindow( SW_SHOWNORMAL );
   UpdateWindow();

   return TRUE;

}

BEGIN_MESSAGE_MAP(CsplitterTabWnd, CSplitterWnd)
	//{{AFX_MSG_MAP(CsplitterTabWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CsplitterTabWnd::OnLButtonDown(UINT nFlags, CPoint point)
{     
    // prevent the user from dragging the splitter bar
	return;
}

BOOL CsplitterTabWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{   
    // Don't allow the cursor to change over splitbar
	return FALSE;
	
}

void CsplitterTabWnd::OnMouseMove(UINT nFlags, CPoint point)
{       
    // Don't allow the cursor to change over splitbar
    CWnd::OnMouseMove(nFlags, point);
}

void CsplitterTabWnd::OnSize(UINT nType, int cx, int cy) 
{
	//CSplitterWnd::OnSize(nType, cx, cy);

   if (nType != SIZE_MINIMIZED && cx > 0 && cy > 0)
   {
		RecalcLayout();
   }
	
}

