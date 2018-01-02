// HeaderCtrlExView.cpp : implementation of the CHeaderCtrlExView class
//

#include "stdafx.h"
#include "HeaderCtrlEx.h"

#include "HeaderCtrlExDoc.h"
#include "HeaderCtrlExView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// data for the list view control

#define NUM_COLUMNS 8
#define NUM_ITEMS   7

static _TCHAR *_gszColumnLabel[NUM_COLUMNS] =
{
	_T("Color\nName"), _T("Red\nColor"), _T("Green\nColor"), _T("Blue\nColor"),
	_T("Hue\nValue"), _T("Sat\nValue"), _T("Lum\nValue"), _T("Type\nOf Color")
};

static int _gnColumnFmt[NUM_COLUMNS] =
{
	LVCFMT_LEFT, LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_RIGHT,
		LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_CENTER
};

static int _gnColumnWidth[NUM_COLUMNS] =
{
	150, 50, 50, 50, 100, 50, 50, 150
};

static _TCHAR *_gszItem[NUM_ITEMS][NUM_COLUMNS] =
{
	_T("Yellow"),  _T("255"), _T("255"), _T("0"),   _T("40"),  _T("240"), _T("120"), _T("Neutral"),
	_T("Red"),     _T("255"), _T("0"),   _T("0"),   _T("0"),   _T("240"), _T("120"), _T("Warm"),
	_T("Green"),   _T("0"),   _T("255"), _T("0"),   _T("80"),  _T("240"), _T("120"), _T("Cool"),
	_T("Magenta"), _T("255"), _T("0"),   _T("255"), _T("200"), _T("240"), _T("120"), _T("Warm"),
	_T("Cyan"),    _T("0"),   _T("255"), _T("255"), _T("120"), _T("240"), _T("120"), _T("Cool"),
	_T("Blue"),    _T("0"),   _T("0"),   _T("255"), _T("160"), _T("240"), _T("120"), _T("Cool"),
	_T("Gray"),    _T("192"), _T("192"), _T("192"), _T("160"), _T("0"),   _T("181"), _T("Neutral")
};

/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlExView

IMPLEMENT_DYNCREATE(CHeaderCtrlExView, CListView)

BEGIN_MESSAGE_MAP(CHeaderCtrlExView, CListView)
	//{{AFX_MSG_MAP(CHeaderCtrlExView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlExView construction/destruction

CHeaderCtrlExView::CHeaderCtrlExView()
{
	
}

CHeaderCtrlExView::~CHeaderCtrlExView()
{
}

BOOL CHeaderCtrlExView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= LVS_SHOWSELALWAYS | LVS_REPORT;
	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlExView drawing

void CHeaderCtrlExView::OnDraw(CDC* pDC)
{
	CHeaderCtrlExDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CHeaderCtrlExView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	CListCtrl& ListCtrl = GetListCtrl();
// insert columns

	int i, j;
	LV_COLUMN lvc;

	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	for(i = 0; i<NUM_COLUMNS; i++)
	{
		lvc.iSubItem = i;
		lvc.pszText = _gszColumnLabel[i];
		lvc.cx = _gnColumnWidth[i];
		lvc.fmt = _gnColumnFmt[i];
		ListCtrl.InsertColumn(i,&lvc);
	}

// insert items

	LV_ITEM lvi;

	for(i = 0; i < NUM_ITEMS; i++)
	{
		lvi.mask = LVIF_TEXT;
		lvi.iItem = i;
		lvi.iSubItem = 0;
		lvi.pszText = _gszItem[i][0];
		ListCtrl.InsertItem(&lvi);
	}

// set item text for additional columns

	for(i = 0; i<NUM_ITEMS; i++)
	{
		for(j = 1; j<NUM_COLUMNS; j++)
		{
			ListCtrl.SetItemText(i,j,_gszItem[i][j]);
		}
	}
///////////////////////SET UP THE MULTILINE HEADER CONTROL
	m_NewHeaderFont.CreatePointFont(190,"MS Serif");

	CHeaderCtrl* pHeader = NULL;
	pHeader=ListCtrl.GetHeaderCtrl();

	if(pHeader==NULL)
		return;
	
	VERIFY(m_HeaderCtrl.SubclassWindow(pHeader->m_hWnd));	

	//A BIGGER FONT MAKES THE CONTROL BIGGER
	m_HeaderCtrl.SetFont(&m_NewHeaderFont);

	HDITEM hdItem;

	hdItem.mask = HDI_FORMAT;

	for(i=0; i<m_HeaderCtrl.GetItemCount(); i++)
	{
		m_HeaderCtrl.GetItem(i,&hdItem);

		hdItem.fmt|= HDF_OWNERDRAW;
		
		m_HeaderCtrl.SetItem(i,&hdItem);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlExView diagnostics

#ifdef _DEBUG
void CHeaderCtrlExView::AssertValid() const
{
	CListView::AssertValid();
}

void CHeaderCtrlExView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CHeaderCtrlExDoc* CHeaderCtrlExView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHeaderCtrlExDoc)));
	return (CHeaderCtrlExDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlExView message handlers
