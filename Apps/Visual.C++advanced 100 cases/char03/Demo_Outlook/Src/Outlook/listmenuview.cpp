// ListMenuView.cpp : implementation file
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ListMenuView.h"
#include "Demo_OutlookDoc.h"
#include "Demo_OutlookView.h"
#include "LeftView.h"
#include "MainFrm.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Menu Information for the Content Bar
CContentItems ContentInfo[] =
{
	CContentItems (0, _T("Outlook Today")),
	CContentItems (1, _T("Inbox (50)"	)),
	CContentItems (2, _T("Calendar"		)),
	CContentItems (3, _T("Contacts"		)),
	CContentItems (4, _T("Tasks"		)),
	CContentItems (5, _T("Journal"		)),
	CContentItems (6, _T("Notes"		)),
	CContentItems (7, _T("Deleted Items (4)"))
};

/////////////////////////////////////////////////////////////////////////////
// CListMenuView

IMPLEMENT_DYNCREATE(CListMenuView, CView)

CListMenuView::CListMenuView()
{
}

CListMenuView::~CListMenuView()
{
}

BEGIN_MESSAGE_MAP(CListMenuView, CView)
	//{{AFX_MSG_MAP(CListMenuView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(WM_OUTLOOKBAR_NOTIFY, OnOutbarNotify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CListMenuView drawing

void CListMenuView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CListMenuView diagnostics

#ifdef _DEBUG
void CListMenuView::AssertValid() const
{
	CView::AssertValid();
}

void CListMenuView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CListMenuView message handlers

int CListMenuView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Create the pager control and set its parent to 'this'
	if (!m_Pager.Create(WS_CHILD|WS_VISIBLE|PGS_VERT,
		CRect(0,0,0,0), this, IDC_PAGER_CONTROL ))
	{
		TRACE0("Failed to create CPagerCtrl...\n");
		return -1;
	}

	// Define the style to use with the COutlookBar.
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | LBS_OWNERDRAWVARIABLE | 
		LBS_NOINTEGRALHEIGHT | WS_TABSTOP;

	// Create the COutlookBar, and set its parent to CPagerCtrl.
	if (!m_OutBar.Create( dwStyle, CRect(0,0,0,0),
		&m_Pager, IDC_OUTLOOK_BAR ))
	{
		TRACE0("Failed to create COutlookBar...\n");
		return -1;
	}
	
	// Set the CWnd object you want messages sent to.
	m_OutBar.SetOwner (this);

	// Set the Vert/Horz scroll area for pager.
	m_Pager.SetScrollArea(0,575);

	// Set the child HWND to COutlookBar, and button size to 15.
	m_Pager.SetChild(m_OutBar.m_hWnd);
	m_Pager.SetButtonSize(15);

	// Initialize menu control.
	InitializeMenuControl();

	return 0;
}

void CListMenuView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

	// Size the outlook style menu, and set 
	// the column size same as view
	m_Pager.MoveWindow(0,0,cx,cy);
	m_OutBar.Invalidate(true);
}

static UINT nImages[] =
{
	IDI_ICON_OUTLOOK,
	IDI_ICON_INBOX,
	IDI_ICON_CALENDAR,
	IDI_ICON_CONTACTS,
	IDI_ICON_TASKS,
	IDI_ICON_JOURNAL,
	IDI_ICON_NOTES,
	IDI_ICON_DELETED
};

void CListMenuView::InitializeMenuControl()
{
    // Define the font to be used for the menu control
	m_Font.CreatePointFont (85, _T("Tahoma"));
    m_OutBar.SetFont(&m_Font);

	// Set the image list for the menu control
	m_OutBar.m_ImageList.Create (16, 16, true, 2, 1);
	m_OutBar.m_ImageListNormal.Create (32, 32, true, 2, 1);

	HICON hIcon;
	
	for (int i =0; i < 8; ++i) {
		hIcon= AfxGetApp()->LoadIcon (nImages[i]);
		m_OutBar.m_ImageList.Add (hIcon);
		m_OutBar.m_ImageListNormal.Add (hIcon);
	}

	m_OutBar.SetItems(ContentInfo, sizeof(ContentInfo)/sizeof(CContentItems));
}

BOOL CListMenuView::OnOutbarNotify(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		case OBM_ITEMCLICK:
			
			// Get the right pane from CMainFrame.
			CDemo_OutlookView* pMainView;
			pMainView = (CDemo_OutlookView*)
				((CMainFrame*)GetParentFrame())->m_wndSplitter.GetPane (0,1);

			// Get the tree view pane contained in the right pane.
			CLeftView* pView;
			pView = (CLeftView*)pMainView->m_wndSplitter.GetPane (0,0);

			// Select the tree item.
			pView->m_TreeCtrl->SelectItem (
				pView->FindItem(ContentInfo[(int)lParam].GetText(),
				TRUE, TRUE, TRUE, pView->m_htParent));

			// Set the tree view in focus.
			pView->SetFocus();

			return TRUE;
	}
	
	return FALSE;
}
