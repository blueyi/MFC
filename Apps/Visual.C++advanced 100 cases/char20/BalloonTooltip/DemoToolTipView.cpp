// DemoToolTipView.cpp : implementation of the CDemoToolTipView class
//

#include "stdafx.h"
#include "DemoToolTip.h"

#include "DemoToolTipDoc.h"
#include "DemoToolTipView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoToolTipView

IMPLEMENT_DYNCREATE(CDemoToolTipView, CFormView)

BEGIN_MESSAGE_MAP(CDemoToolTipView, CFormView)
	//{{AFX_MSG_MAP(CDemoToolTipView)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoToolTipView construction/destruction

CDemoToolTipView::CDemoToolTipView()
	: CFormView(CDemoToolTipView::IDD)
{
	//{{AFX_DATA_INIT(CDemoToolTipView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CDemoToolTipView::~CDemoToolTipView()
{
}

void CDemoToolTipView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoToolTipView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CDemoToolTipView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDemoToolTipView printing

BOOL CDemoToolTipView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDemoToolTipView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDemoToolTipView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CDemoToolTipView::OnPrint(CDC* pDC, CPrintInfo*)
{
	// TODO: add code to print the controls
}

/////////////////////////////////////////////////////////////////////////////
// CDemoToolTipView diagnostics

#ifdef _DEBUG
void CDemoToolTipView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDemoToolTipView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CDemoToolTipDoc* CDemoToolTipView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemoToolTipDoc)));
	return (CDemoToolTipDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemoToolTipView message handlers

void CDemoToolTipView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	CListBox *pList = (CListBox *) GetDlgItem(IDC_LIST1);
	pList->AddString("Item1");
	pList->AddString("Item2");
	pList->AddString("Item3");


	m_BalloonToolWnd.Create(this);
	m_BalloonToolWnd.m_bStuck = true;

	m_BalloonToolWnd.AddTool(GetDlgItem(IDC_EDIT1),"Type your address here", RGB(255,0,0));
	m_BalloonToolWnd.AddTool(GetDlgItem(IDC_EDIT2),"Stuck!!!", RGB(0,0,255));
	m_BalloonToolWnd.AddTool(GetDlgItem(IDC_LIST1),"List Box");	
	m_BalloonToolWnd.AddTool(GetDlgItem(IDC_BUTTON1),"Button1");	
}

BOOL CDemoToolTipView::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_BalloonToolWnd)
		m_BalloonToolWnd.RelayEvent(pMsg);

	return CFormView::PreTranslateMessage(pMsg);
}

void CDemoToolTipView::OnButton1() 
{
	// TODO: Add your control notification handler code here
	AfxMessageBox("Button1");
}
