// TestMyCanEditListView.cpp : implementation of the CTestMyCanEditListView class
//

#include "stdafx.h"
#include "TestMyCanEditList.h"

#include "TestMyCanEditListDoc.h"
#include "TestMyCanEditListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

# define IDC_LISTCTRL_CONDITION 2000
/////////////////////////////////////////////////////////////////////////////
// CTestMyCanEditListView

IMPLEMENT_DYNCREATE(CTestMyCanEditListView, CView)

BEGIN_MESSAGE_MAP(CTestMyCanEditListView, CView)
	//{{AFX_MSG_MAP(CTestMyCanEditListView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestMyCanEditListView construction/destruction

CTestMyCanEditListView::CTestMyCanEditListView()
{
	// TODO: add construction code here

}

CTestMyCanEditListView::~CTestMyCanEditListView()
{
}

BOOL CTestMyCanEditListView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestMyCanEditListView drawing

void CTestMyCanEditListView::OnDraw(CDC* pDC)
{
	CTestMyCanEditListDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTestMyCanEditListView printing

BOOL CTestMyCanEditListView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestMyCanEditListView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestMyCanEditListView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTestMyCanEditListView diagnostics

#ifdef _DEBUG
void CTestMyCanEditListView::AssertValid() const
{
	CView::AssertValid();
}

void CTestMyCanEditListView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestMyCanEditListDoc* CTestMyCanEditListView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestMyCanEditListDoc)));
	return (CTestMyCanEditListDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestMyCanEditListView message handlers

int CTestMyCanEditListView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	if(!m_wndConditionList.Create(WS_VISIBLE|WS_CHILD|LVS_REPORT ,CRect(0,0,0,0),this,IDC_LISTCTRL_CONDITION))
	{
		AfxMessageBox("创建m_wndConditionList控件时出错!");
		return -1;
	}
	//m_wndConditionList.SetBkColor(RGB(236,233,216));
	m_wndConditionList.SetTextBkColor(RGB(222,222,222));


	m_wndConditionList.InitListCtrl();
    //m_wndConditionList.Invalidate(TRUE);

	m_wndConditionList.SetExtendedStyle( LVS_EX_FULLROWSELECT 	//允许整行选中
		//| LVS_EX_HEADERDRAGDROP 		//允许整列拖动
		| LVS_EX_GRIDLINES 	//画出网格线
		//| LVS_EX_FLATSB				//扁平风格的滚动条	
		);

	m_wndConditionList.InsertItem(0,"1");
	m_wndConditionList.InsertItem(1,"2");
	m_wndConditionList.InsertItem(2,"3");
	m_wndConditionList.InsertItem(3,"4");
	m_wndConditionList.InsertItem(4,"5");
	m_wndConditionList.InsertItem(5,"6");

	return 0;
}

void CTestMyCanEditListView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(this->m_wndConditionList.m_hWnd)
	{
		CRect rect;
		this->GetClientRect(rect);
		this->m_wndConditionList.MoveWindow(rect,TRUE);
	}

}
