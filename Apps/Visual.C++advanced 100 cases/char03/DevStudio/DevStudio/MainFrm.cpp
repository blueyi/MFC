// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Demo_DevStudio.h"
#include "TreeViewClass.h"
#include "TreeViewFile.h"
#include "TreeViewResource.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_COMMAND_EX(CG_ID_VIEW_OUTPUT, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_OUTPUT, OnUpdateControlBarMenu)
	ON_COMMAND_EX(CG_ID_VIEW_WORKSPACE, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_WORKSPACE, OnUpdateControlBarMenu)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
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
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
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

	// Install cool menus.
	InstallCoolMenus(this, IDR_MAINFRAME);

	// Create the image list to be used with the control bars.
	m_ImageList.Create(IDB_IMAGELIST, 13, 1, RGB(0,255,0));

	// CG: The following block was inserted by the 'Dialog Bar' component
	{
		m_wndWorkspace.SetBtnImageList (&m_ImageList);
		m_wndWorkspace.SetMenuID(IDR_POPUP);

		// Initialize dialog bar m_wndWorkspace
		if (!m_wndWorkspace.Create(this, CG_ID_VIEW_WORKSPACE,
			_T("Workspace"), CSize(220,200)))
		{
			TRACE0("Failed to create dialog bar m_wndWorkspace\n");
			return -1;		// fail to create
		}

		// Add the views to the tab control.
		m_wndWorkspace.AddView(_T("Class"),    RUNTIME_CLASS(CTreeViewClass));
		m_wndWorkspace.AddView(_T("Resource"), RUNTIME_CLASS(CTreeViewResource));
		m_wndWorkspace.AddView(_T("Files"),    RUNTIME_CLASS(CTreeViewFile));

		// Define the image list to use with the tab control
		m_TabImages.Create (IDB_IL_TAB, 16, 1, RGB(0,255,0));
		m_wndWorkspace.SetTabImageList(&m_TabImages);

	    // allow bar to be resized when floating
	    m_wndWorkspace.SetBarStyle(m_wndWorkspace.GetBarStyle() |
		    CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

		m_wndWorkspace.EnableDocking(CBRS_ALIGN_ANY);
		EnableDocking(CBRS_ALIGN_ANY);
		DockControlBar(&m_wndWorkspace, AFX_IDW_DOCKBAR_LEFT);
	}

	// CG: The following block was inserted by the 'Dialog Bar' component
	{
		m_wndOutput.SetBtnImageList (&m_ImageList);
		m_wndOutput.SetMenuID(IDR_POPUP);

		// Initialize dialog bar m_wndOutput
		if (!m_wndOutput.Create(this, CG_ID_VIEW_OUTPUT,
			_T("Output"), CSize(200,100)))
		{
			TRACE0("Failed to create dialog bar m_wndOutput\n");
			return -1;		// fail to create
		}

	    // allow bar to be resized when floating
	    m_wndOutput.SetBarStyle(m_wndOutput.GetBarStyle() |
		    CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

		m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
		EnableDocking(CBRS_ALIGN_ANY);
		DockControlBar(&m_wndOutput, AFX_IDW_DOCKBAR_BOTTOM);
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIFrameWnd::PreCreateWindow(cs);
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
