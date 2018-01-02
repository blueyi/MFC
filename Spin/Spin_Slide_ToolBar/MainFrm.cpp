// MainFrm.cpp : implementation of the CMainFrame class
//

/*##################################################################

  Author:	Masoud Samimi
  Website:	www.geocities.com/samimi73
  Email:	marcello43@hotmail.com

  Program:	Spinners Toolbar
  History:	05.01.1999 (dd.mm.yy)
  
  Purpose: Please visit my website, it is expalined there.
  

Important Notice:

	This Method and the Application is Copyright(c) Masoud Samimi 1999,2000.
	You can freely use it as long as you credit me for it.

	No guarantee/warantee, expressed or implied is given on this app and I will not be responsible 
	for any damage to you, your property or any other person from using it.
	USE IT ON YOUR OWN RISK.

	Thankyou and have FUNNE =-)

	Masoud Samimi.

##################################################################*/
#include "stdafx.h"
#include "SpinnerTB.h"
#include "resource.h"
#include "MainFrm.h"

#include "SpinnerTBDoc.h"
#include "SpinnerTBView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(IDR_SPINNER_BAR, OnSpinnerbar)
	ON_UPDATE_COMMAND_UI(IDR_SPINNER_BAR, OnUpdateSpinnerbar)
	ON_COMMAND(ID_VIEW_SLIDERBAR, OnViewSliderbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SLIDERBAR, OnUpdateViewSliderbar)
	//}}AFX_MSG_MAP

	// Message map entry for RGB status pane update
	ON_MESSAGE (WM_USER_UPDATE_COLOR, OnUpdateTextColor)

	// Message map entries for Red, Green & Blue spinners update
	ON_MESSAGE (WM_USER_UPDATE_SPINNER_RED, OnUpdateSpinnerColorRed)
	ON_MESSAGE (WM_USER_UPDATE_SPINNER_GREEN, OnUpdateSpinnerColorGreen)
	ON_MESSAGE (WM_USER_UPDATE_SPINNER_BLUE, OnUpdateSpinnerColorBlue)
	
	// Message entry for Gradient fill update
	ON_MESSAGE (WM_USER_UPDATE_GRADIENT, OnUpdateGradientFill)
	ON_MESSAGE (WM_USER_UPDATE_GRADIENT_STATUS, OnUpdateGradientPane)
	
END_MESSAGE_MAP()


static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_SEPARATOR,           // status line indicator
	ID_SEPARATOR,           // status line indicator

	//ID_INDICATOR_CAPS,
	//ID_INDICATOR_NUM,
	//ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
		
	
}

CMainFrame::~CMainFrame()
{
	m_pActiveView = NULL;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT , WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
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

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.SetWindowText(_T("Main Toolbar"));
	
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
		
	CreateSpinnerBar();
	CreateSlideBar();
	

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

BOOL CMainFrame::CreateSpinnerBar()
{

	//##########################################//
	// Creation

	if (!m_wndSpinBar.CreateEx(this, TBSTYLE_FLAT , WS_CHILD | WS_VISIBLE | CBRS_BOTTOM
	| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_FIXED))

		return FALSE;

	m_wndSpinBar.LoadToolBar (IDR_SPINNER_BAR);
	m_wndSpinBar.SetWindowText(_T("RGB Spinners: From 0 to 255  _&_ Slider 0 to 255"));
	m_wndSpinBar.EnableDocking (CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
	DockControlBar(&m_wndSpinBar);
	
    return TRUE;

}

BOOL CMainFrame::CreateSlideBar()
{

	//##########################################//
	// Creation of slider toolbar 
	// Note: Just a demo, dondomuch ;-)

	if (!m_wndSlideBar.CreateEx(this, TBSTYLE_FLAT , WS_CHILD | WS_VISIBLE | CBRS_BOTTOM
	| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_FIXED))

		return FALSE;

	m_wndSlideBar.LoadToolBar (IDR_SLIDER_BAR);
	m_wndSlideBar.SetWindowText(_T("Rotation:        X                                    Y                                Z"));
	m_wndSlideBar.EnableDocking (CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
	DockControlBar(&m_wndSlideBar);
	
    return TRUE;

}

void CMainFrame::OnSpinnerbar() 
{
	// TODO: Add your command handler code here
	if(m_wndSpinBar)
	{
		if(m_wndSpinBar.IsWindowVisible())
			ShowControlBar(&m_wndSpinBar, FALSE, FALSE);
		else
			ShowControlBar(&m_wndSpinBar, TRUE, FALSE);
	}
}


void CMainFrame::OnUpdateSpinnerbar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_wndSpinBar) {
		if(m_wndSpinBar.IsWindowVisible())
			pCmdUI->SetCheck(TRUE);
		else
			pCmdUI->SetCheck(FALSE);
	}
	else
		pCmdUI->SetCheck(FALSE);
}



LRESULT CMainFrame::OnUpdateTextColor (WPARAM wParam, LPARAM lParam)
{
    
	// Red, Green & Blue pane updates
	m_wndStatusBar.SetPaneText (1, (LPCTSTR) lParam, TRUE);
	
	return 0;
}

LRESULT CMainFrame::OnUpdateSpinnerColorRed(WPARAM wParam, LPARAM lParam)
{
    
	m_wndSpinBar.m_wndSpin_r.SetPos((UINT) lParam);

	return 0;
}

LRESULT CMainFrame::OnUpdateSpinnerColorGreen(WPARAM wParam, LPARAM lParam)
{
    
	m_wndSpinBar.m_wndSpin_g.SetPos((UINT) lParam);
		
	return 0;
}

LRESULT CMainFrame::OnUpdateSpinnerColorBlue(WPARAM wParam, LPARAM lParam)
{
    
	m_wndSpinBar.m_wndSpin_b.SetPos((UINT) lParam);
	
	return 0;
}

LRESULT CMainFrame::OnUpdateGradientFill(WPARAM wParam, LPARAM lParam)
{
    
	m_wndSpinBar.m_wndSlider.SetPos((UINT) lParam);

	return 0;
}

LRESULT CMainFrame::OnUpdateGradientPane(WPARAM wParam, LPARAM lParam)
{
    
	// Gradient update
	m_wndStatusBar.SetPaneText (2, (LPCTSTR) lParam, TRUE);

	return 0;
}

void CMainFrame::OnViewSliderbar() 
{
	// TODO: Add your command handler code here
	if(m_wndSlideBar)
	{
		if(m_wndSlideBar.IsWindowVisible())
			ShowControlBar(&m_wndSlideBar, FALSE, FALSE);
		else
			ShowControlBar(&m_wndSlideBar, TRUE, FALSE);
	}
}

void CMainFrame::OnUpdateViewSliderbar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		if(m_wndSlideBar) {
		if(m_wndSlideBar.IsWindowVisible())
			pCmdUI->SetCheck(TRUE);
		else
			pCmdUI->SetCheck(FALSE);
	}
	else
		pCmdUI->SetCheck(FALSE);
}
