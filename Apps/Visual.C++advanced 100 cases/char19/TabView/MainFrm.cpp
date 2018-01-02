// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "tab.h"

#include "viewTwo.h"
#include "TabView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

   cs.dwExStyle |= WS_EX_CLIENTEDGE;

	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
/*
   long lStyleEx = ::GetWindowLong( m_hWnd, GWL_EXSTYLE );
   lStyleEx |= WS_EX_CLIENTEDGE;
   ::SetWindowLong( m_hWnd, GWL_EXSTYLE, lStyleEx );
  */ 
	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
   m_splitterTabWnd.AddView( RUNTIME_CLASS( CTabView ),"View nr 1" );   
   m_splitterTabWnd.AddView( RUNTIME_CLASS( CviewTwo ),"View nr 2" );   
   m_splitterTabWnd.AddView( RUNTIME_CLASS( CTabView ),"View three is same as one" );   
   m_splitterTabWnd.Create( this, pContext );
   
   SetActiveView((CView *)m_splitterTabWnd.GetPane(0,0));

   return TRUE;
}



