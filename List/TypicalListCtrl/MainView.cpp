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
/*
/////////////////////////////////////////////////////////////////////////////
// DoDataExchange
/////////////////////////////////////////////////////////////////////////////
void CMainView::DoDataExchange(CDataExchange *pDX) {
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}  // DoDataExchange

/////////////////////////////////////////////////////////////////////////////
// PreCreateWindow
/////////////////////////////////////////////////////////////////////////////
BOOL CMainView::PreCreateWindow(CREATESTRUCT& cs) {
	return CFormView::PreCreateWindow(cs);
}  // PreCreateWindow

/////////////////////////////////////////////////////////////////////////////
// OnInitialUpdate
/////////////////////////////////////////////////////////////////////////////
void CMainView::OnInitialUpdate() {
	CFormView::OnInitialUpdate();
	
	ResizeParentToFit();
}  // OnInitialUpdate
*/
/////////////////////////////////////////////////////////////////////////////
// OnCreate
/////////////////////////////////////////////////////////////////////////////
int CMainView::OnCreate(LPCREATESTRUCT pCS) {
	if(CFormView::OnCreate(pCS) == -1)
			return -1;

	//*** Table style
	DWORD dwStyle =	0;

	dwStyle |= LVS_REPORT;  // The Report mode (base style)
	//dwStyle |= WS_CHILD;  // Creates a child window
	dwStyle |= WS_BORDER;  // Creates a window that has a border
	dwStyle |= WS_VISIBLE;  // Make visible (to don't use ShowWindow)
	
	//*** Extension table style
	DWORD dwExStyle = 0;

	dwExStyle |= LVS_EX_GRIDLINES;  // It draws grid lines

	//*** The view rectangle
	RECT ViewRect = {0, 25, 665, 210};

	//*** Table columns array
	META_HEADER aMetaHeader[] = {
		{_T("Ind. No"),		 LVCFMT_RIGHT,		 55},
		{_T("Empl. Id"),	 LVCFMT_RIGHT,		 60},
		{_T("Title"),			 LVCFMT_LEFT,			200},
		{_T("Name"),			 LVCFMT_LEFT,			150},
		{_T("Birthday"),	 LVCFMT_CENTER,		 85},
		{_T("Work Phone"), LVCFMT_CENTER,		120}
	};

	//*** Amount table columns
	UINT nHdrCount = sizeof(aMetaHeader) / sizeof(aMetaHeader[0]);
	
	//*** Table rows array
	TCHAR *apRowText[10][6] = {
		{_T(" 1"),	_T("123"), _T("Sales Representative"),	_T("Andrew Overling"),   _T("01.01.1981"),	_T("555-1111")},
		{_T(" 2"),	_T("321"), _T("Vice President, Sales"), _T("Janet Savolio"),	   _T("02.02.1982"),	_T("555-2222")},
		{_T(" 3"),	_T("444"), _T("Sales Representative"),	_T("Alex Romb"),		     _T("03.03.1983"),	_T("555-3333")},
		{_T(" 4"),	_T("222"), _T("Sales Manager"),					_T("Roy Trix"),				   _T("04.04.1984"),	_T("555-4444")},
		{_T(" 5"),	_T("458"), _T("Sales Representative"),	_T("Steven Puller"),		 _T("05.05.1985"),	_T("555-5555")},
		{_T(" 6"),	_T("753"), _T("Sales Manager"),					_T("Brad Hamer"),				 _T("06.06.1986"),	_T("555-6666")},
		{_T(" 7"),	_T("159"), _T("Sales Manager"),					_T("Margaret Luchanan"), _T("07.07.1987"),	_T("555-7777")},
		{_T(" 8"),	_T("111"), _T("Secretary"),							_T("Nancy Kuller"),			 _T("08.08.1988"),	_T("555-8888")},
		{_T(" 9"),	_T("777"), _T("Sales Analyst"),					_T("Anatoly Suren"),		 _T("09.09.1989"),	_T("555-9999")},
		{_T("10"),	_T("555"), _T("Cleaning Woman"),				_T("Susan Scrub"),			 _T("10.10.1990"),	_T("555-0000")}
	};
	
	//*** Amount table rows
	UINT nRowCount = 10;

	//*** Create table
	CListCtrl *pTable = new CListCtrl;
	
	if(!pTable) {
		_M("Empty a CListCtrl object!");
		return -1;
	}

	//*** CListCtrl initialization.
	if(!pTable->Create(dwStyle, ViewRect, this, 0)) {
		_M("It isn't create a CListCtrl object!");
		return - 1;
	}

	//*** To set extended table style
	pTable->SetExtendedStyle(dwExStyle);

	//*** The structure of a table header cell
	HDITEM HDItem = {0};

	HDItem.mask |= HDI_FORMAT;  // The fmt member is valid
	HDItem.mask |= HDI_TEXT;  // The pszText and cchTextMax members are valid
	HDItem.mask |= HDI_WIDTH;  // The cxy member is valid and specifies the item's width

	HDItem.cchTextMax = MAXITEMTEXT;

	//*** Creates table columns
	for(UINT i = 0; i < nHdrCount; i++) {
		HDItem.pszText = (LPTSTR) aMetaHeader[i].szHdrName;
		HDItem.fmt = aMetaHeader[i].nAdjust;
		HDItem.cxy = aMetaHeader[i].nWidth;
		
		pTable->InsertColumn(
				i, 
				HDItem.pszText,	
				HDItem.fmt, 
				HDItem.cxy
		);
	}

	//*** The structure of a table row cell
	LVITEM lvItem = {0};
	
	lvItem.mask = LVIF_TEXT;

	//*** Creates table rows
	for(UINT j = 0; j < nRowCount; j++) {
		lvItem.iItem = j;
		lvItem.iSubItem = 0;
		lvItem.pszText = apRowText[j][0];
		
		pTable->InsertItem(&lvItem);

		for(i = 1; i < nHdrCount; i++) {
			lvItem.iItem = j;
			lvItem.iSubItem = i;
			lvItem.pszText = apRowText[j][i];
		
			pTable->SetItem(&lvItem);
		}
	}

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
	void CMainView::Dump(CDumpContext& dc) const {
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
