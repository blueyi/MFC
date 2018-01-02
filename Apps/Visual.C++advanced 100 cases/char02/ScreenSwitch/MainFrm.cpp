// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MultiScreen.h"
#include "doc.h"
#include "MainFrm.h"
#include "mainview.h"
#include "view2.h"
#include "view3.h"
#include "view4.h"

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
	ON_COMMAND(IDM_FORM1, OnForm1)
	ON_COMMAND(IDM_FORM2, OnForm2)
	ON_COMMAND(IDM_FORM3, OnForm3)
	ON_COMMAND(IDM_FORM4, OnForm4)
	ON_UPDATE_COMMAND_UI(IDM_FORM1, OnUpdateForm1)
	ON_UPDATE_COMMAND_UI(IDM_FORM2, OnUpdateForm2)
	ON_UPDATE_COMMAND_UI(IDM_FORM3, OnUpdateForm3)
	ON_UPDATE_COMMAND_UI(IDM_FORM4, OnUpdateForm4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

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

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

//---------------------------------------------------------------
//	Desc:	Switchs out the current view with a new view and eliminate the old view
//	Params:	A paramater to indicate what view to switch in can be anything you wish
//	returns:
//---------------------------------------------------------------
void CMainFrame::SwitchToForm(int nForm)
{
	CView* pOldActiveView = GetActiveView();			// save old view
	CView* pNewActiveView = (CView*)GetDlgItem(nForm);  // get new view

	if (pNewActiveView == NULL)     // if it hasn't been created yet
	{                               // create it here
		switch(nForm) // these IDs are the dialog IDs of the view but can use anything
		{
		case IDD_MULTISCREEN_FORM:
		 						pNewActiveView = (CView*)new CMainView;
		 						break;
		case IDD_MULTISCREEN_FORM2:
		 						pNewActiveView = (CView*)new CView2;
		 						break;
		case IDD_MULTISCREEN_FORM3:
		 						pNewActiveView = (CView*)new CView3;
		 						break;
		case IDD_MULTISCREEN_FORM4:
		 						pNewActiveView = (CView*)new CView4;
		 						break;
		}
		CCreateContext context;       // attach the document to the new view
		context.m_pCurrentDoc = pOldActiveView->GetDocument();
		pNewActiveView->Create(NULL, NULL, 0L, CFrameWnd::rectDefault, // and the frame
			this, nForm, &context);
		pNewActiveView->OnInitialUpdate();       
	}

	SetActiveView(pNewActiveView);			// change the active view
	pNewActiveView->ShowWindow(SW_SHOW);	// show the new window
	pOldActiveView->ShowWindow(SW_HIDE);	// hide the old

		
	::SetWindowWord(pNewActiveView->m_hWnd, GWL_ID, AFX_IDW_PANE_FIRST);  // gotta have it
	RecalcLayout();				//	adjust frame
	delete	pOldActiveView;		//	kill old view 							  							  
}

//---------------------------------------------------------------
//	Desc:	Handle the menus and popups from the views here
//	Params:	
//	returns:
//---------------------------------------------------------------
void CMainFrame::OnForm1() 
{
	SwitchToForm(IDD_MULTISCREEN_FORM);
	
}
//---------------------------------------------------------------
//	Desc:
//	Params:
//	returns:
//---------------------------------------------------------------
void CMainFrame::OnForm2() 
{
	SwitchToForm(IDD_MULTISCREEN_FORM2);
	
}
//---------------------------------------------------------------
//	Desc:
//	Params:
//	returns:
//---------------------------------------------------------------
void CMainFrame::OnForm3() 
{
	SwitchToForm(IDD_MULTISCREEN_FORM3);
	
}
//---------------------------------------------------------------
//	Desc:
//	Params:
//	returns:
//---------------------------------------------------------------
void CMainFrame::OnForm4() 
{
	SwitchToForm(IDD_MULTISCREEN_FORM4);
	
}
//---------------------------------------------------------------
//	Desc:		Gray out the current view to eliminate recursion
//	Params:
//	returns:
//---------------------------------------------------------------
void CMainFrame::OnUpdateForm1(CCmdUI* pCmdUI) 
{

	pCmdUI->Enable(GetActiveView()->GetRuntimeClass()!=RUNTIME_CLASS(CMainView));
}
//---------------------------------------------------------------
//	Desc:
//	Params:
//	returns:
//---------------------------------------------------------------
void CMainFrame::OnUpdateForm2(CCmdUI* pCmdUI) 
{

	pCmdUI->Enable(GetActiveView()->GetRuntimeClass()!=RUNTIME_CLASS(CView2));
}
//---------------------------------------------------------------
//	Desc:
//	Params:
//	returns:
//---------------------------------------------------------------
void CMainFrame::OnUpdateForm3(CCmdUI* pCmdUI) 
{

	pCmdUI->Enable(GetActiveView()->GetRuntimeClass()!=RUNTIME_CLASS(CView3));
}
//---------------------------------------------------------------
//	Desc:
//	Params:
//	returns:
//---------------------------------------------------------------
void CMainFrame::OnUpdateForm4(CCmdUI* pCmdUI) 
{
	
	pCmdUI->Enable(GetActiveView()->GetRuntimeClass()!=RUNTIME_CLASS(CView4));
}
