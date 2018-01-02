// TreeViewFile.cpp : implementation file
//

#include "stdafx.h"
#include "Demo_DevStudio.h"
#include "TreeViewFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeViewFile

IMPLEMENT_DYNCREATE(CTreeViewFile, CTreeView)

CTreeViewFile::CTreeViewFile()
{
}

CTreeViewFile::~CTreeViewFile()
{
}


BEGIN_MESSAGE_MAP(CTreeViewFile, CTreeView)
	//{{AFX_MSG_MAP(CTreeViewFile)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemexpanding)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeViewFile drawing

void CTreeViewFile::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CTreeViewFile diagnostics

#ifdef _DEBUG
void CTreeViewFile::AssertValid() const
{
	CTreeView::AssertValid();
}

void CTreeViewFile::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTreeViewFile message handlers

void CTreeViewFile::OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CTreeViewFile::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

static CString csTree[] =
{
	_T("Workspace 'demo': 1 project(s)"),
	_T("Demo files"),
	_T("File Folder")
};

int CTreeViewFile::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_TreeCtrl = &GetTreeCtrl();
	
	// create the image list for the tree control
	m_ImageList.Create (IDB_IL_FILE, 16, 1, RGB(0,255,0));
	m_TreeCtrl->SetImageList (&m_ImageList, TVSIL_NORMAL);

	// add the parent item, make it bold
	HTREEITEM htiParent = m_TreeCtrl->InsertItem (csTree[0]);
	HTREEITEM htiChild; // child item

	htiChild = m_TreeCtrl->InsertItem (csTree[1], 1, 1, htiParent, TVI_LAST);
	m_TreeCtrl->SetItemState (htiChild, TVIS_BOLD, TVIS_BOLD);

	// add the children of the parent item
	for (int i = 1; i < 4; i++) {
		m_TreeCtrl->InsertItem (csTree[2], 2, 3, htiChild, TVI_LAST);
	}

	m_TreeCtrl->Expand (htiParent, TVE_EXPAND);
	m_TreeCtrl->Expand (htiChild, TVE_EXPAND);
	return 0;
}

BOOL CTreeViewFile::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style |= TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT;
	return CTreeView::PreCreateWindow(cs);
}
