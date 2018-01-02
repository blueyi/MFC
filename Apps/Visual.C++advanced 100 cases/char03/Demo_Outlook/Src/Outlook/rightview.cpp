// RightView.cpp : implementation file
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RightView.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRightView

IMPLEMENT_DYNCREATE(CRightView, CListView)

CRightView::CRightView()
{
}

CRightView::~CRightView()
{
}


BEGIN_MESSAGE_MAP(CRightView, CListView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CRightView)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_DETAILS, OnViewDetails)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DETAILS, OnUpdateViewDetails)
	ON_COMMAND(ID_VIEW_LIST, OnViewList)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LIST, OnUpdateViewList)
	ON_COMMAND(ID_VIEW_SMALL, OnViewSmall)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SMALL, OnUpdateViewSmall)
	ON_COMMAND(ID_VIEW_LARGE, OnViewLarge)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LARGE, OnUpdateViewLarge)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRightView drawing

void CRightView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CRightView diagnostics

#ifdef _DEBUG
void CRightView::AssertValid() const
{
	CListView::AssertValid();
}

void CRightView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRightView message handlers

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

static UINT nHeaderBmps[] =
{
	IDB_HEADER_0,
	IDB_HEADER_1,
	IDB_HEADER_2,
	IDB_HEADER_3
};

int CRightView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_ListCtrl = &GetListCtrl();
	m_ListCtrl->ModifyStyle (0, LVS_REPORT);

	// Create the large and small image lists
	m_ImageList.Create (16, 16, true, 2, 1);
	m_ImageListNormal.Create (32, 32, true, 2, 1);
	HICON hIcon;
	
	for (int i =0; i < 12; ++i) {
		hIcon= AfxGetApp()->LoadIcon (nImages[i]);
		m_ImageList.Add (hIcon);
		m_ImageListNormal.Add (hIcon);
	}

	m_ListCtrl->SetImageList (&m_ImageList, LVSIL_SMALL);
	m_ListCtrl->SetImageList (&m_ImageListNormal, LVSIL_NORMAL);
	m_ListCtrl->SetTextColor (RGB(0,0,255));

	m_Font.CreatePointFont (85, _T("Tahoma"));
    m_ListCtrl->SetFont (&m_Font);

	BuildColumns();
	PopulateList();
	
	return 0;
}

static int _gnCols = 5;

static int _gnColSize[] =
{
	18,21,22,18,380
};

static CString _gcsColLabel[] =
{
	_T("x"),
	_T("x"),
	_T("x"),
	_T("x"),
	_T("Description:")
};

void CRightView::BuildColumns()
{
	// Insert the columns into the list control
	LV_COLUMN lvCol;

	lvCol.mask = LVCF_FMT|LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM;
	for (int i = 0; i < _gnCols; ++i)
	{
		lvCol.iSubItem = i;
		lvCol.pszText = (char*)(LPCTSTR)_gcsColLabel[i];
		lvCol.cx = _gnColSize[i];
		lvCol.fmt = LVCFMT_LEFT;
		m_ListCtrl->InsertColumn(i, &lvCol);
	}

	for (int x = 0; x < _gnCols-1; x++)
		SetHeaderBitmap(x, nHeaderBmps[x], HDF_STRING);
}

void CRightView::PopulateList(CString* cs)
{
	int			nI = m_ListCtrl->GetItemCount();
	LV_ITEM		lvi;

	if (cs)
	{
		CString cstr;
		cstr.Format("Tree Index: %s", cs[0]);

		lvi.mask = LVIF_TEXT|LVIF_IMAGE|LVIF_STATE;
		lvi.iItem = nI;
		lvi.iSubItem = 0;
		lvi.iImage = atoi((char*)(LPCTSTR)cs[0]);
		lvi.stateMask = LVIS_STATEIMAGEMASK;
		lvi.state = INDEXTOSTATEIMAGEMASK(1);
		lvi.pszText = (char*)(LPCTSTR)cstr;

		if (m_ListCtrl->InsertItem(&lvi) != -1) {
			m_ListCtrl->SetItemText(nI, 4, cs[1]);
		}
	}
}

void CRightView::OnContextMenu(CWnd*, CPoint point)
{
	// CG: This block was added by the Pop-up Menu component
	{
		if (point.x == -1 && point.y == -1){
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenu(POPUP_RIGHT_VIEW));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

typedef enum enumListView {
	Details = LVS_REPORT,
	List	= LVS_LIST,
	Small	= LVS_SMALLICON,
	Large	= LVS_ICON
};

enumListView ListView = Details;

void CRightView::OnViewDetails() 
{
	m_ListCtrl->ModifyStyle (ListView, LVS_REPORT);
	ListView = Details;
}

void CRightView::OnUpdateViewDetails(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(ListView == Details);
}

void CRightView::OnViewList() 
{
	m_ListCtrl->ModifyStyle (ListView, LVS_LIST);
	ListView = List;
}

void CRightView::OnUpdateViewList(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(ListView == List);
}

void CRightView::OnViewSmall() 
{
	m_ListCtrl->ModifyStyle (ListView, LVS_SMALLICON);
	ListView = Small;
}

void CRightView::OnUpdateViewSmall(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(ListView == Small);
}

void CRightView::OnViewLarge() 
{
	m_ListCtrl->ModifyStyle (ListView, LVS_ICON);
	ListView = Large;
}

void CRightView::OnUpdateViewLarge(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(ListView == Large);
}

void CRightView::SetHeaderBitmap(int nCol, int nBitmap, DWORD dwRemove)
{
	CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);

	HD_ITEM hdi;
	hdi.mask = HDI_FORMAT;
	pHeader->GetItem (nCol, &hdi);
	hdi.mask = HDI_BITMAP | HDI_FORMAT;
	hdi.fmt  |= HDF_BITMAP;
	hdi.hbm = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(nBitmap),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS);

	if (dwRemove)
		hdi.fmt &= ~dwRemove;

	pHeader->SetItem (nCol, &hdi);
}
