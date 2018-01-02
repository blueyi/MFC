/////////////////////////////////////////////////////////////////////////////
// MainView.cpp : implementation of the CMainView class
/////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "Main.h"
#include "MainDoc.h"
#include "MainView.h"

#ifdef _DEBUG
	#define new DEBUG_NEW
#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainView
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CMainView, CFormView)

BEGIN_MESSAGE_MAP(CMainView, CFormView)
	ON_WM_CREATE()
	//{{AFX_MSG_MAP(CMainView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainView construction
/////////////////////////////////////////////////////////////////////////////
CMainView::CMainView() : CFormView(CMainView::IDD) {
}

/////////////////////////////////////////////////////////////////////////////
// CMainView destruction
/////////////////////////////////////////////////////////////////////////////
CMainView::~CMainView() {
}

/////////////////////////////////////////////////////////////////////////////
// OnCreate
/////////////////////////////////////////////////////////////////////////////
int CMainView::OnCreate(LPCREATESTRUCT pCS) {
	if(CFormView::OnCreate(pCS) == -1)
			return -1;

	//*** Table style
	DWORD dwStyle =	0;

	//*** Calls WM_DRAWITEM messages into CListCtrlEx and CHeaderCtrlEx 
	// and WM_MEASUREITEM message into CListCtrlEx
	dwStyle |= LVS_OWNERDRAWFIXED;

	dwStyle |= LVS_REPORT;  // Sets the Report mode (base style)
	dwStyle |= LVS_OWNERDATA;  // Sets the Virtual mode
	dwStyle |= WS_CHILD;  // Creates a child window
	dwStyle |= WS_BORDER;  // Creates a window that has a border
	dwStyle |= WS_VISIBLE;  // Make visible (to don't use ShowWindow)
	
	//*** Extension table style
	DWORD dwExStyle = 0;

	dwExStyle |= LVS_EX_GRIDLINES;  // It draws grid lines

	//*** The view rectangle
	RECT ViewRect = {0, 25, 689, 400};

	//*** Create table
	CListCtrlEx *pTable = new CListCtrlEx;
	
	if(!pTable) {
		_M("Empty a CListCtrlEx object!");
		return -1;
	}

	//*** CListCtrl initialization
	if(!pTable->Create(dwStyle, ViewRect, this, IDC_LISTCTRL)) {
		_M("Failed to create a CListCtrl object!");
		return - 1;
	}

	//*** To set extended table style
	pTable->SetExtendedStyle(dwExStyle);

	//*** Creates a table header
	CHeaderCtrlEx *pHeader = new CHeaderCtrlEx;
	
	if(!pHeader) {
		_M("Empty CHeaderCtrlEx object!");
		return -1;
	}
	
	//*** The CHeaderCtrlEx handle
	HWND hHeader = pHeader->m_hWnd;
	//HWND hHeader = pHeader->GetSafeHwnd();

	CHeaderCtrl *pOldHeader = pTable->GetHeaderCtrl();

	if(!pOldHeader) {
		_M("Empty CHeaderCtrl object!");
		return -1;
	}
	
	//*** The CHeaderCtrl handle
	HWND hOldHeader = pOldHeader->m_hWnd; 
	//HWND hOldHeader = pOldHeader->GetSafeHwnd();

	//*** The table header subclassing
	if(!pHeader->SubclassWindow(hOldHeader)) {
		_M("Failed to Subclass a table header!");
		return -1;
	}

	//*** Table columns array
	META_HEADER aMetaHeader[] = {
		{_T("Ind. No"),		 LVCFMT_RIGHT,		 50},
		{_T("Empl. Id"),	 LVCFMT_RIGHT,		 57},
		{_T("Title"),			 LVCFMT_LEFT,			225},
		{_T("Name"),			 LVCFMT_LEFT,			150},
		{_T("Birthday"),	 LVCFMT_CENTER,		 85},
		{_T("Work Phone"), LVCFMT_CENTER,		105}
	};

	//*** The table columns count
	// Must be m_nColCount = nColCount in CListCtrlEx::CListCtrlEx
	UINT nColCount = sizeof(aMetaHeader) / sizeof(aMetaHeader[0]);  // = 6
		
	//*** The structure of a table header cell
	HDITEM HDItem = {0};

	HDItem.mask |= HDI_FORMAT;  // The fmt member is valid
	HDItem.mask |= HDI_TEXT;  // The pszText and cchTextMax members are valid
	HDItem.mask |= HDI_WIDTH;  // The cxy member is valid and specifies the item's width

	HDItem.cchTextMax = MAXITEMTEXT;

	//*** Creates table columns
	for(UINT i = 0; i < nColCount; i++) {
		HDItem.pszText = (LPTSTR) aMetaHeader[i].szHdrName;
		HDItem.fmt = aMetaHeader[i].nAdjust;
		HDItem.cxy = aMetaHeader[i].nWidth;
		
		//*** Calls CHeaderCtrlEx::DrawItem
		HDItem.fmt |= HDF_OWNERDRAW;
		
		//*** Sends too message HDM_LAYOUT
		pTable->InsertColumn(
				i, 
				HDItem.pszText,	
				HDItem.fmt, 
				HDItem.cxy
		);
	
		//*** Reset the first column
		if(i == 0)
				pHeader->SetItem(i, &HDItem);
	}

	//*** Sets the table rows count in the virtual mode (LVS_OWNERDATA)
	//*** Send messages LVN_GETDISPINFOW & HDM_LAYOUT
	//*** Cals the CListCtrlEx::DrawItem
	pTable->SetItemCount(12);

	return 0;
}  // OnCreate

/////////////////////////////////////////////////////////////////////////////
// CMainView diagnostics
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
	/////////////////////////////////////////////////////////////////////////////
	// AssertValid
	/////////////////////////////////////////////////////////////////////////////
	void CMainView::AssertValid() const {
		CFormView::AssertValid();
	}  // AssertValid

	/////////////////////////////////////////////////////////////////////////////
	// Dump
	/////////////////////////////////////////////////////////////////////////////
	void CMainView::Dump(CDumpContext &dc) const {
		CFormView::Dump(dc);
	}  // Dump
	/*
	/////////////////////////////////////////////////////////////////////////////
	// GetDocument : Non-debug version is inline
	/////////////////////////////////////////////////////////////////////////////
	CMainDoc *CMainView::GetDocument() {
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMainDoc)));

		return (CMainDoc *) m_pDocument;
	}  // GetDocument
	*/
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
