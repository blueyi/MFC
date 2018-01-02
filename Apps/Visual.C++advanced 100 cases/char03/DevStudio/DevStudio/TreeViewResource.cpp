// TreeViewResource.cpp : implementation file
//

#include "stdafx.h"
#include "Demo_DevStudio.h"
#include "TreeViewResource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeViewResource

IMPLEMENT_DYNCREATE(CTreeViewResource, CTreeView)

CTreeViewResource::CTreeViewResource()
{
}

CTreeViewResource::~CTreeViewResource()
{
}


BEGIN_MESSAGE_MAP(CTreeViewResource, CTreeView)
	//{{AFX_MSG_MAP(CTreeViewResource)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemexpanding)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeViewResource drawing

void CTreeViewResource::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CTreeViewResource diagnostics

#ifdef _DEBUG
void CTreeViewResource::AssertValid() const
{
	CTreeView::AssertValid();
}

void CTreeViewResource::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTreeViewResource message handlers

void CTreeViewResource::OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CTreeViewResource::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

static CString csTree[] =
{
	_T("Demo resources"),
	_T("Accelerator"),
	_T("Bitmap"),
	_T("Dialog"),
	_T("Icon"),
	_T("Menu"),
	_T("String Table"),
	_T("Toolbar"),
	_T("Version")
};

int CTreeViewResource::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_TreeCtrl = &GetTreeCtrl();
	
	// create the image list for the tree control
	m_ImageList.Create (IDB_IL_RSRC, 16, 1, RGB(0,255,0));
	m_TreeCtrl->SetImageList (&m_ImageList, TVSIL_NORMAL);

	// add the parent item
	HTREEITEM htItem = m_TreeCtrl->InsertItem (csTree[0], 1, 1);
	m_TreeCtrl->SetItemState (htItem, TVIS_BOLD, TVIS_BOLD);

	// add children items
	for (int i = 1; i < 9; i++) {
		m_TreeCtrl->InsertItem (csTree[i], 0, 1, htItem, TVI_LAST);
	}

	m_TreeCtrl->Expand (htItem, TVE_EXPAND);
	return 0;
}

BOOL CTreeViewResource::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style |= TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT;
	return CTreeView::PreCreateWindow(cs);
}
