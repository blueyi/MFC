// MainFrm.cpp : implementation of the CMainFrame class
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Demo_Outlook.h"
#include "Demo_OutlookDoc.h"
#include "Demo_OutlookView.h"
#include "ListMenuView.h"

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
	ON_COMMAND(IDC_STATIC_DROP, OnStaticDrop)
	ON_CBN_SELENDOK(IDC_COMBO, OnSelendokFlatCombo)
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

	// Add a drop down to button
	m_wndToolBar.SetButtonDropDown( IDC_STATIC_DROP );

	// Insert the CCJComboBox control
	m_Combo = (CCJComboBox*)m_wndToolBar.InsertControl(
		RUNTIME_CLASS(CCJComboBox), _T(""), CRect(-165,-200,0,0), IDC_COMBO,
		WS_CHILD | CBS_DROPDOWNLIST | CBS_AUTOHSCROLL | WS_VSCROLL | CBS_HASSTRINGS );

	m_Combo->AddString("Messages with AutoPreview");
	m_Combo->SetCurSel(0);

	// Install cool menus.
	InstallCoolMenus((CFrameWnd*)this, IDR_MAINFRAME);

	return 0;
}

void CMainFrame::OnSelendokFlatCombo() 
{
	AfxMessageBox(_T("Flat Combo Box selection made..."));
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

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
  // Create the splitter window with two columns
  if (!m_wndSplitter.CreateStatic(this, 1, 2))
  {
    TRACE0("Failed to create splitter window\n");
    return FALSE;
  }

  // "Outlook" view first
  if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CListMenuView),
		CSize(100, 0), pContext))
  {
    TRACE0("Failed to create CListMenuView\n"); 
    return FALSE;
  }

  // "Flexible pane": The second pane may present its own
  // splitter windows.
  if (!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CDemo_OutlookView),
		CSize(0, 0), pContext))
  {
    TRACE0("Failed to create CDemo_OutlookView\n"); 
    return FALSE;
  }
 
  // Set the active view
  SetActiveView((CView*) m_wndSplitter.GetPane(0, 0));
  return TRUE;
}

void CMainFrame::OnStaticDrop() 
{
	// TODO: Add your command handler code here
	
}
