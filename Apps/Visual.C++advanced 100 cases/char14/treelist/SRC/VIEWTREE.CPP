// View.cpp : implementation of the CTreeListView class
//

#include "stdafx.h"
#include "TreeList.h"

#include "Doc.h"
#include "ViewTree.h"
#include "ViewList.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeListView

IMPLEMENT_DYNCREATE(CTreeListView, CTreeView)

BEGIN_MESSAGE_MAP(CTreeListView, CTreeView)
	//{{AFX_MSG_MAP(CTreeListView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemexpanding)
	ON_NOTIFY_REFLECT(TVN_SELCHANGING, OnSelchanging)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeListView construction/destruction

CTreeListView::CTreeListView()
{
	m_pImageList = NULL;
	m_bInit = FALSE;
}

CTreeListView::~CTreeListView()
{
	delete m_pImageList;
}

/////////////////////////////////////////////////////////////////////////////
BOOL CTreeListView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName,
						 DWORD dwStyle, const RECT& rect, 
						 CWnd* pParentWnd, UINT nID, 
						 CCreateContext* pContext) 
{
	dwStyle |= TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT;	
	return CWnd::Create(lpszClassName, lpszWindowName, 
					dwStyle, rect, pParentWnd, nID, pContext);
}

/////////////////////////////////////////////////////////////////////////////
BOOL CTreeListView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTreeListView drawing

void CTreeListView::OnDraw(CDC* pDC)
{
	CTreeListDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTreeListView printing

BOOL CTreeListView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTreeListView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTreeListView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTreeListView diagnostics

#ifdef _DEBUG
void CTreeListView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CTreeListView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CTreeListDoc* CTreeListView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTreeListDoc)));
	return (CTreeListDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTreeListView message handlers

/////////////////////////////////////////////////////////////////////////////
void CTreeListView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();


	// since we left the default AppWizard button/menu set, the
	//	user could open a new document - this would cause us to
	//	do this stuff twice - just once per app, thank you.
	if( !m_bInit )
	{
		m_bInit = TRUE;

		CTreeCtrl& cThisTree = GetTreeCtrl();

		// load bitmaps for drive types & desktop - ten images
		CBitmap bitmap;
		m_pImageList = new CImageList();
		// 16x16 pixels, 8 of them
		m_pImageList->Create(16, 16, TRUE, 8, 4);
/*
#define IDB_REMOVE                      200
#define IDB_FIXED                       201
#define IDB_REMOTE                      202
#define IDB_CD                          203
#define IDB_DESKTOP                     204
#define IDB_FOLDCLS                     205
#define IDB_FOLDOPEN                    206
#define IDB_DOC                         207
*/
		// the 8 images have conseq resource numbers
		//	see resource.h
		for( int i = IDB_REMOVE; i <= IDB_DOC; i++)  
		{
			bitmap.LoadBitmap( i );
			m_pImageList->Add( &bitmap, (COLORREF)0xFFFFFF);
			bitmap.DeleteObject();
		}
		cThisTree.SetImageList( m_pImageList, TVSIL_NORMAL );

		// TODO: You may populate your TreeView with items by directly accessing
		//  its tree control through a call to GetTreeCtrl().

		// Good advice! let's do it with my helper function
		FillEmptyTree();
	}
}

///////////////////////////////////////////////////
void CTreeListView::FillEmptyTree(void)
{
	// The real Explorer has a more sophisticated approach
	//	so that the tree can be built quickly. Also, it uses
	//	a thread (note progressive painting in Explorer).
	CWaitCursor cWait;

	CTreeCtrl& cThisTree = GetTreeCtrl();

	// form the one and only tree root - the desktop
	TV_INSERTSTRUCT	strInsert;

	// must use a selectedimage even if same
	strInsert.item.mask = TVIF_TEXT | 
							TVIF_IMAGE | 
							TVIF_SELECTEDIMAGE;

	// a root item - so parent is NULL
	strInsert.hParent = NULL;
	// index of the image in the list
	strInsert.item.iImage = IDB_DESKTOP - IDB_REMOVE;
	strInsert.item.iSelectedImage = strInsert.item.iImage;
	// force to "Desktop" - the real Explorer uses the
	//	registry-based items (like "Computer")
	strInsert.item.pszText = (LPSTR)"Desktop";
	HTREEITEM hDesktop = cThisTree.InsertItem(&strInsert);

	// do the "drive type" work

	// get bitmask: LSB = A; LSB+1 = B; and so on
	DWORD dwDrives = GetLogicalDrives();
	UINT uType;
	char szDrive[20]; 

	szDrive[1] = ':';
	szDrive[2] = '\0';
	// do all 32 just for kicks
	for( int i = 0; i < 32; i++ )
	{
		// all drives have this as their parent
		strInsert.hParent = hDesktop;

		szDrive[0] = 'A' + (char)i;
		DWORD dwTemp = dwDrives;
		if( dwTemp & 1 )
		{
			strInsert.item.pszText = (LPSTR)szDrive;
			ASSERT(strlen(szDrive)== 2);
			char szTemp[5];
			strcpy(szTemp, szDrive);
			strcat(szTemp, "\\.");
			uType = GetDriveType( (LPCTSTR)szTemp );

			/* a reminder - similar order as bitmap numbers
			#define DRIVE_REMOVABLE   2
			#define DRIVE_FIXED       3
			#define DRIVE_REMOTE      4
			#define DRIVE_CDROM       5
			*/
			switch(uType)
			{
			case DRIVE_REMOVABLE:
				{
					strInsert.item.iImage = 
							IDB_REMOVE - IDB_REMOVE;
					break;
				}
			case DRIVE_FIXED:
				{
					strInsert.item.iImage = 
							IDB_FIXED - IDB_REMOVE;
					break;
				}
			case DRIVE_REMOTE:
				{
					strInsert.item.iImage = 
							IDB_REMOTE - IDB_REMOVE;
					break;
				}
			case DRIVE_CDROM:
				{
					strInsert.item.iImage = 
							IDB_CD - IDB_REMOVE;
					break;
				}
			default :
				{
					strInsert.item.iImage = 0;
					break;
				}
			}

			strInsert.item.iSelectedImage = strInsert.item.iImage;

			HTREEITEM hItemDrive;
			hItemDrive = cThisTree.InsertItem(&strInsert);

			// now give it one phony child - real app
			//	might recurse the tree unless time was an issue
			strInsert.hParent = hItemDrive;
			CString sDrive = "Phony Item under ";
			sDrive += szDrive;
			strInsert.item.pszText = (LPSTR)(const char *)sDrive;
			strInsert.item.iImage = 
							IDB_FOLDCLS - IDB_REMOVE;
			strInsert.item.iSelectedImage = 
							IDB_FOLDOPEN - IDB_REMOVE;
			cThisTree.InsertItem(&strInsert);
		}
		dwDrives = dwDrives >> 1;
	}

	//expand the Desktop
	cThisTree.Expand( hDesktop, TVE_EXPAND );
	
	// don't select anything yet - the List's OnInitialUpdate
	//	has not been called yet
} 

/////////////////////////////////////////////////////////////////////////////
void CTreeListView::OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	// NOTE: not all of the stuff in NM_TREEVIEW is valid.
	//	Only the itemNew .state and .hItem and .lParam are.

	// this empty handler just here to let you experiment

	*pResult = 0;
}

/////////////////////////////////////////////////////////////////////////////
void CTreeListView::OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	// this empty handler just here to let you experiment

	*pResult = 0;
}

/////////////////////////////////////////////////////////////////////////////
void CTreeListView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	// get tree
	CTreeCtrl& cThisTree = GetTreeCtrl();

	// get list
	CMainFrame * pFWnd = (CMainFrame *)AfxGetMainWnd();
	CMyListView * pView = (CMyListView*)pFWnd->m_wndSplitter.GetPane(0,1);
	ASSERT( pView != NULL);
	CListCtrl& cThisList = pView->GetListCtrl();

	// I am going to re-fill the list, so reset it now
	cThisList.DeleteAllItems();

	// what item got selected?
	TV_ITEM strTvItem;
	char szText[64]; // 64 should be enuf
	strTvItem.mask = TVIF_CHILDREN | TVIF_TEXT;
	strTvItem.hItem = pNMTreeView->itemNew.hItem;
	strTvItem.pszText = (LPSTR)szText;
	strTvItem.cchTextMax = 64;
	cThisTree.GetItem( &strTvItem );

	//prep a structure for the list
	LV_ITEM lvitem;
	// text and image
	lvitem.mask = LVIF_TEXT | LVIF_IMAGE;
	// must be zero for the 0th column
	lvitem.iSubItem = 0;
	// fill in pszText, iItem and iImage later 

	// Children? cChildren is a code - not a count
	if( strTvItem.cChildren == 1 )
	{
		// yes, we have children - populate list with them
		strTvItem.mask = TVIF_TEXT | TVIF_IMAGE;

		HTREEITEM hChild;
		hChild = cThisTree.GetNextItem( 
						pNMTreeView->itemNew.hItem,
						TVGN_CHILD);
		
		int i = 0;
		while( hChild != NULL )
		{
			strTvItem.hItem = hChild;

			cThisTree.GetItem( &strTvItem );
			
			// make list entry

			// form the list control structure
			// text 
			lvitem.pszText = strTvItem.pszText;
			// point to the row number
			lvitem.iItem = i;	  
			// image - same list at the tree's
			lvitem.iImage = strTvItem.iImage;
			// do the insert
			int nRet = cThisList.InsertItem( &lvitem ); 
			// a check
			ASSERT( nRet != -1 );

			// fill other columns with stuff

			// do col 1
			BOOL bRet = cThisList.SetItemText( 
								i, 1, "Drive Stuff" );	 
			ASSERT( bRet );

			// do col 2
			bRet = cThisList.SetItemText( 
								i, 2, "My Stuff" );	 
			ASSERT( bRet );

			// do col 3
			bRet = cThisList.SetItemText( 
								i, 3, "More Stuff" );	 
			ASSERT( bRet );

			hChild = cThisTree.GetNextItem( hChild,TVGN_NEXT );
			i++;
		}
	}
	else if( strTvItem.cChildren == 0)
	{
		// form the list control structure
		// text 
		lvitem.pszText = "Some File";
		// point to the row number - I know there is only one file
		lvitem.iItem = 0;	  
		// image - the DOC icon
		lvitem.iImage = IDB_DOC-IDB_REMOVE;
		// do the insert
		int nRet = cThisList.InsertItem( &lvitem ); 
		// a check
		ASSERT( nRet != -1 );

		// fill other columns with stuff

		// do col 1
		BOOL bRet = cThisList.SetItemText( 
							0, 1, "File Stuff" );	 
		ASSERT( bRet );

		// do col 2
		bRet = cThisList.SetItemText( 
							0, 2, "My Stuff" );	 
		ASSERT( bRet );

		// do col 3
		bRet = cThisList.SetItemText( 
							0, 3, "More Stuff" );	 
		ASSERT( bRet );
	}

	*pResult = 0;
}




