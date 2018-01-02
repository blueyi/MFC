// LeftView.cpp : implementation file
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LeftView.h"
#include "Demo_OutlookDoc.h"
#include "Demo_OutlookView.h"
#include "RightView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

CLeftView::CLeftView()
{
}

CLeftView::~CLeftView()
{
}

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	//{{AFX_MSG_MAP(CLeftView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemexpanding)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

void CLeftView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers

int CLeftView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_TreeCtrl = &GetTreeCtrl();
	m_TreeCtrl->ModifyStyle (0, TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT);

	m_Font.CreatePointFont (85, _T("Tahoma"));
    m_TreeCtrl->SetFont (&m_Font);

	PopulateTreeControls();
	return 0;
}

static CString csTreeItems[] =
{
	_T("Outlook Today - [Mailbox - Kirk Stowell]"),
	_T("Public Folders"),
	_T("Calendar"),
	_T("Contacts"),
	_T("Deleted Items (4)"),
	_T("Drafts"),
	_T("Inbox (50)"),
	_T("Journal"),
	_T("Notes"),
	_T("Outbox"),
	_T("Sent Items"),
	_T("Tasks")
};

static UINT nImages[] =
{
	IDI_ICON_OUTLOOK,
	IDI_ICON_PUBLIC,
	IDI_ICON_CALENDAR,
	IDI_ICON_CONTACTS,
	IDI_ICON_DELETED,
	IDI_ICON_DRAFTS,
	IDI_ICON_INBOX,
	IDI_ICON_JOURNAL,
	IDI_ICON_NOTES,
	IDI_ICON_OUTBOX,
	IDI_ICON_SENT,
	IDI_ICON_TASKS
};

void CLeftView::PopulateTreeControls()
{
	// create the image list for the tree control
	// and set the tree style using defaults
	// Set the image list for the menu control
	m_ImageList.Create (16, 16, true, 2, 1);
	HICON hIcon;
	
	for (int i =0; i < 12; ++i) {
		hIcon= AfxGetApp()->LoadIcon (nImages[i]);
		m_ImageList.Add (hIcon);
	}

	m_TreeCtrl->SetImageList( &m_ImageList, TVSIL_NORMAL );

	// add the parent items
	m_htParent = m_TreeCtrl->InsertItem( csTreeItems[0], 0, 0 );
	m_TreeCtrl->InsertItem( csTreeItems[1], 1, 1 );

	// add childeren items
	AddTreeChildren( m_htParent );
	m_TreeCtrl->Expand(m_htParent, TVE_EXPAND);
}

void CLeftView::AddTreeChildren( HTREEITEM htiParent )
{
	HTREEITEM hti1, hti2;

	m_TreeCtrl->InsertItem( csTreeItems[2], 2, 2, htiParent );
	m_TreeCtrl->InsertItem( csTreeItems[3], 3, 3,htiParent );
	hti1 = m_TreeCtrl->InsertItem( csTreeItems[4], 4, 4, htiParent );
	m_TreeCtrl->InsertItem( csTreeItems[5], 5, 5, htiParent );
	hti2 = m_TreeCtrl->InsertItem( csTreeItems[6], 6, 6, htiParent );
	m_TreeCtrl->InsertItem( csTreeItems[7], 7, 7, htiParent );
	m_TreeCtrl->InsertItem( csTreeItems[8], 8, 8, htiParent );
	m_TreeCtrl->InsertItem( csTreeItems[9], 9, 9, htiParent );
	m_TreeCtrl->InsertItem( csTreeItems[10], 10, 10, htiParent );
	m_TreeCtrl->InsertItem( csTreeItems[11], 11, 11, htiParent );

	m_TreeCtrl->SetItemState( hti1, TVIS_BOLD, TVIS_BOLD );
	m_TreeCtrl->SetItemState( hti2, TVIS_BOLD, TVIS_BOLD );
}

// GetLastItem  - Gets last item in the branch
// Returns      - Last item
// hItem        - Node identifying the branch. NULL will 
//                return the last item in outine

HTREEITEM CLeftView::GetLastItem( HTREEITEM hItem )
{
        // Last child of the last child of the last child ...
        HTREEITEM htiNext;

        if( hItem == NULL ){
                // Get the last item at the top level
                htiNext = m_TreeCtrl->GetRootItem();
                while( htiNext ){
                        hItem = htiNext;
                        htiNext = m_TreeCtrl->GetNextSiblingItem( htiNext );
                }
        }

        while( m_TreeCtrl->ItemHasChildren( hItem ) ){
                htiNext = m_TreeCtrl->GetChildItem( hItem );
                while( htiNext ){
                        hItem = htiNext;
                        htiNext = m_TreeCtrl->GetNextSiblingItem( htiNext );
                }
        }

        return hItem;
}

// GetNextItem  - Get next item as if outline was completely expanded
// Returns      - The item immediately below the reference item
// hItem        - The reference item
HTREEITEM CLeftView::GetNextItem( HTREEITEM hItem )
{
        HTREEITEM       hti;

        if( m_TreeCtrl->ItemHasChildren( hItem ) )
                return m_TreeCtrl->GetChildItem( hItem );           // return first child
        else{
                // return next sibling item
                // Go up the tree to find a parent's sibling if needed.
                while( (hti = m_TreeCtrl->GetNextSiblingItem( hItem )) == NULL ){
                        if( (hItem = m_TreeCtrl->GetParentItem( hItem ) ) == NULL )
                                return NULL;
                }
        }
        return hti;
}

// GetNextItem  - Get previous item as if outline was completely expanded
// Returns              - The item immediately above the reference item
// hItem                - The reference item
HTREEITEM CLeftView::GetPrevItem( HTREEITEM hItem )
{
        HTREEITEM       hti;

        hti = m_TreeCtrl->GetPrevSiblingItem(hItem);
        if( hti == NULL )
                hti = m_TreeCtrl->GetParentItem(hItem);
        else
                hti = GetLastItem(hti);
        return hti;
}

// FindItem		- Finds an item that contains the search string
// Returns		- Handle to the item or NULL
// str			- String to search for
// bCaseSensitive	- Should the search be case sensitive
// bDownDir		- Search direction - TRUE for down
// bWholeWord		- True if search should match whole words
// hItem		- Item to start searching from. NULL for
//			- currently selected item
HTREEITEM CLeftView::FindItem(CString &str, 
				BOOL bCaseSensitive /*= FALSE*/, 
				BOOL bDownDir /*= TRUE*/, 
				BOOL bWholeWord /*= FALSE*/, 
				HTREEITEM hItem /*= NULL*/)
{
	int lenSearchStr = str.GetLength();
	if( lenSearchStr == 0 ) return NULL;

	HTREEITEM htiSel = hItem ? hItem : m_TreeCtrl->GetSelectedItem();
	HTREEITEM htiCur = bDownDir ?GetNextItem( htiSel ) : GetPrevItem( htiSel );
	CString sSearch = str;

	if( htiCur == NULL )
	{
		if( bDownDir )  htiCur = m_TreeCtrl->GetRootItem();
		else htiCur = GetLastItem( NULL );
	}

	if( !bCaseSensitive )
		sSearch.MakeLower();

	while( htiCur && htiCur != htiSel )
	{
		CString sItemText = m_TreeCtrl->GetItemText( htiCur );
		if( !bCaseSensitive )
			sItemText.MakeLower();

		int n;
		while( (n = sItemText.Find( sSearch )) != -1 )
		{
			// Search string found
			if( bWholeWord )
			{
				// Check preceding char
				if( n != 0 )
				{
					if( isalpha(sItemText[n-1]) || 
					    	sItemText[n-1] == '_' ){
						// Not whole word
						sItemText = sItemText.Right(
							sItemText.GetLength() - n - 
							lenSearchStr );
						continue;
					}
				}

				// Check succeeding char
				if( sItemText.GetLength() > n + lenSearchStr
					&& ( isalpha(sItemText[n+lenSearchStr]) ||
					sItemText[n+lenSearchStr] == '_' ) )
				{
					// Not whole word
					sItemText = sItemText.Right( sItemText.GetLength() 
							- n - sSearch.GetLength() );
					continue;
				}
			}
			
			if( IsFindValid( htiCur ) )
				return htiCur;
			else break;
		}


		htiCur = bDownDir ? GetNextItem( htiCur ) : GetPrevItem( htiCur );
		if( htiCur == NULL )
		{
			if( bDownDir )  htiCur = m_TreeCtrl->GetRootItem();
			else htiCur = GetLastItem( NULL );
		}
	}
	return NULL;
}

// IsFindValid	- Virtual function used by FindItem to allow this
//		  function to filter the result of FindItem
// Returns	- True if item matches the criteria
// Arg		- Handle of the item
BOOL CLeftView::IsFindValid( HTREEITEM )
{
	return TRUE;
}

void CLeftView::OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CLeftView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	// Get the right pane from CMainFrame.
	CDemo_OutlookView* pMainView;
	pMainView = (CDemo_OutlookView*)
		((CMainFrame*)GetParentFrame())->m_wndSplitter.GetPane (0,1);
	
	// Get the list view pane contained in the right pane.
	CRightView* pView;
	pView = (CRightView*)pMainView->m_wndSplitter.GetPane (0,1);
	
	int nImage;

	HTREEITEM hti = m_TreeCtrl->GetSelectedItem();

	if (hti)
	{
		m_TreeCtrl->GetItemImage (hti, nImage, nImage);
		m_cs[0].Format ("%d",nImage);
		m_cs[1] = m_TreeCtrl->GetItemText (hti);

		// Add string to list control.
		pView->PopulateList(m_cs);
	}

	*pResult = 0;
}
