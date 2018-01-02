// TreeViewClass.cpp : implementation file
//

#include "stdafx.h"
#include "Demo_DevStudio.h"
#include "TreeViewClass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeViewClass

IMPLEMENT_DYNCREATE(CTreeViewClass, CTreeView)

CTreeViewClass::CTreeViewClass()
{
}

CTreeViewClass::~CTreeViewClass()
{
}


BEGIN_MESSAGE_MAP(CTreeViewClass, CTreeView)
	//{{AFX_MSG_MAP(CTreeViewClass)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemexpanding)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeViewClass drawing

void CTreeViewClass::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
/*	// create a memory dc compatible with the paint dc
	CDC memdc;
	memdc->CreateCompatibleDC( pDC );

	CRect rcclip, rcclient;
	pDC->GetClipBox( &rcclip );
	getClientRect(&rcclient);

	// select a compatible bitmap into the memory dc
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap ( &dc, rcclient.width(), rcclient.height() );
	memdc->SelectObject( &bitmap );
	
	// set clip region to be same as that in paint dc
	CRgn rgn;
	rgn.CreateRectRgnIndirect( &rcclip );
	mempDC->SelectClipRgn(&rgn);
	rgn.DeleteObject();
	
	// first let the control do its default drawing.
	CWnd::DefWindowProc( WM_PAINT, (wparam)mempDC->m_hdc, 0 );


	// now create a mask
	CDC maskdc;
	maskdc->CreateCompatibleDC(&dc);
	CBitmap maskbitmap;

	// create monochrome bitmap for the mask
	maskbitmap.CreateBitmap( rcclip.Width(), rcclip.Height(), 1, 1, null );
	maskdc->SelectObject( &maskbitmap );
	memdc->SetBkColor( ::getsyscolor( color_window ) );

	// create the mask from the memory dc
	maskdc->BitBlt( 0, 0, rcclip.Width(), rcclip.Height(), &memdc, 
				rcclip.left, rcclip.top, srccopy );

	// fill the background../di2001.jpgh custom color
	// use a protected member variable to save the color
	// rather than hard coding it.
	pDC->FillRect(rcclip, &CBrush(RGB(255,255,192)) );
	
	// copy the image in memdc transparently

	// maskblt works in nt only - so we use another method
	//	pDC->maskblt( rcclip.left, rcclip.top, rcclip.width(), rcclip.height(), &memdc, 
	//			rcclip.left, rcclip.top, maskbitmap, 0, 0, 
	//			makerop4(srcand,srccopy) );


	// set the background../di2001.jpgn memdc to black. using srcpaint with black and any other
	// color results in the other color, thus making black the transparent color
	memdc->SetBkColor(RGB(0,0,0));          
	memdc->SetTextColor(RGB(255,255,255));  
	memdc->BitBlt(rcclip.left, rcclip.top, rcclip.Width(), rcclip.Height(), &maskdc, rcclip.left, rcclip.top, srcand);

	// set the foreground to black. see comment above.
	pDC->SetBkColor(rgb(255,255,255));
	pDC->SetTextColor(rgb(0,0,0));
	pDC->BitBlt(rcclip.left, rcclip.top, rcclip.Width(), rcclip.Height(), &maskdc, rcclip.left, rcclip.top, srcand);
	
	// combine the foreground with the background../di2001.jpgd
	pDC->BitBlt(rcclip.left, rcclip.top, rcclip.Width(), rcclip.Height(), &memdc, 
					rcclip.left, rcclip.top,srcpaint);
*/
}

/////////////////////////////////////////////////////////////////////////////
// CTreeViewClass diagnostics

#ifdef _DEBUG
void CTreeViewClass::AssertValid() const
{
	CTreeView::AssertValid();
}

void CTreeViewClass::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTreeViewClass message handlers

void CTreeViewClass::OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CTreeViewClass::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

static CString csTree[] =
{
	_T("Demo classes"),
	_T("CClassName"),
	_T("Globals")
};

int CTreeViewClass::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_TreeCtrl = &GetTreeCtrl();

	// Create the image list for the tree control
	m_ImageList.Create (IDB_IL_CLASS, 16, 1, RGB(0,255,0));
	m_TreeCtrl->SetImageList (&m_ImageList, TVSIL_NORMAL);

	// Add the parent item
	HTREEITEM htItem = m_TreeCtrl->InsertItem(csTree[0]);
	m_TreeCtrl->SetItemState( htItem, TVIS_BOLD, TVIS_BOLD );

	// Add children
	for( int i = 1; i < 8; i++ ) {
		m_TreeCtrl->InsertItem (csTree[1], 1, 1, htItem, TVI_LAST);
	}

	// Add children
	m_TreeCtrl->InsertItem (csTree[2], 2, 3, htItem, TVI_LAST);
	m_TreeCtrl->Expand(htItem, TVE_EXPAND);

	return 0;
}

BOOL CTreeViewClass::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style |= TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT;
	return CTreeView::PreCreateWindow(cs);
}

