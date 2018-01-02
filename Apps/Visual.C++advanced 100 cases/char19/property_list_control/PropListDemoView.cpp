// PropListDemoView.cpp : implementation of the CPropListDemoView class
//

#include "stdafx.h"
#include "PropListDemo.h"

#include "PropListDemoDoc.h"
#include "PropListDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropListDemoView

IMPLEMENT_DYNCREATE(CPropListDemoView, CView)

BEGIN_MESSAGE_MAP(CPropListDemoView, CView)
	//{{AFX_MSG_MAP(CPropListDemoView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropListDemoView construction/destruction

CPropListDemoView::CPropListDemoView()
{
	// TODO: add construction code here

}

CPropListDemoView::~CPropListDemoView()
{
}

BOOL CPropListDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPropListDemoView drawing

void CPropListDemoView::OnDraw(CDC* pDC)
{
	CPropListDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

}

/////////////////////////////////////////////////////////////////////////////
// CPropListDemoView printing

BOOL CPropListDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPropListDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPropListDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPropListDemoView diagnostics

#ifdef _DEBUG
void CPropListDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CPropListDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPropListDemoDoc* CPropListDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPropListDemoDoc)));
	return (CPropListDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPropListDemoView message handlers

void CPropListDemoView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

	CRect ClientRect;
	GetClientRect(ClientRect);


	m_nPropList.Create(WS_CHILD | WS_VISIBLE | WS_BORDER,
						ClientRect,
						this,
						1001);

	AddItemsToPropList();

	m_nPropList.ShowWindow(TRUE);
	
}

void CPropListDemoView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

	if (IsWindow(m_nPropList.m_hWnd))
		m_nPropList.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOMOVE | SWP_SHOWWINDOW);
	
}

void CPropListDemoView::AddItemsToPropList()
{
	PROPERTYITEMSETUP ItemInfo;

	m_nPropList.AddItem("Name", FPSPROPERTYITEMTYPE_TEXT);

	ItemInfo.strName = "Type";
	ItemInfo.dwType = FPSPROPERTYITEMTYPE_COMBOBOX;
	ItemInfo.bAllowComboEdit = TRUE;
	ItemInfo.ComboBoxList.AddTail("Type 1");
	ItemInfo.ComboBoxList.AddTail("Type 2");
	ItemInfo.ComboBoxList.AddTail("Type 3");
	ItemInfo.ComboBoxList.AddTail("Custom");
	m_nPropList.AddItem(&ItemInfo);

	ItemInfo.strName = "Visible";
	ItemInfo.dwType = FPSPROPERTYITEMTYPE_BOOL;
	ItemInfo.bBoolValue = TRUE;
	m_nPropList.AddItem(&ItemInfo);

	ItemInfo.strName = "Fore Color";
	ItemInfo.dwType = FPSPROPERTYITEMTYPE_COLOR;
	ItemInfo.ColorValue = RGB(0, 0, 0);
	m_nPropList.AddItem(&ItemInfo);
	
	ItemInfo.strName = "Back Color";
	ItemInfo.dwType = FPSPROPERTYITEMTYPE_COLOR;
	ItemInfo.ColorValue = RGB(255, 255, 255);
	m_nPropList.AddItem(&ItemInfo);

	ItemInfo.strName = "Font";
	ItemInfo.dwType = FPSPROPERTYITEMTYPE_FONT;
	m_nPropList.AddItem(&ItemInfo);

	ItemInfo.strName = "File Name";
	ItemInfo.dwType = FPSPROPERTYITEMTYPE_FILE;
	ItemInfo.bFileOpenDialog = TRUE;
	ItemInfo.strFileFilter = "Access Files (*.MDB)|*.mdb|All Files (*.*)|*.*|";
	m_nPropList.AddItem(&ItemInfo);
}
