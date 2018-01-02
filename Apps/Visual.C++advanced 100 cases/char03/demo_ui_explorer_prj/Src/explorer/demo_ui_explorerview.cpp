// demo_ui_explorerView.cpp : implementation of the CDemo_ui_explorerView class
//

#include "stdafx.h"
#include "demo_ui_explorer.h"

#include "demo_ui_explorerDoc.h"
#include "demo_ui_explorerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemo_ui_explorerView

IMPLEMENT_DYNCREATE(CDemo_ui_explorerView, CEditView)

BEGIN_MESSAGE_MAP(CDemo_ui_explorerView, CEditView)
	//{{AFX_MSG_MAP(CDemo_ui_explorerView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemo_ui_explorerView construction/destruction

CDemo_ui_explorerView::CDemo_ui_explorerView()
{
	// TODO: add construction code here

}

CDemo_ui_explorerView::~CDemo_ui_explorerView()
{
}

BOOL CDemo_ui_explorerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CDemo_ui_explorerView drawing

void CDemo_ui_explorerView::OnDraw(CDC* pDC)
{
	CDemo_ui_explorerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDemo_ui_explorerView printing

BOOL CDemo_ui_explorerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CDemo_ui_explorerView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CDemo_ui_explorerView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CDemo_ui_explorerView diagnostics

#ifdef _DEBUG
void CDemo_ui_explorerView::AssertValid() const
{
	CEditView::AssertValid();
}

void CDemo_ui_explorerView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CDemo_ui_explorerDoc* CDemo_ui_explorerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemo_ui_explorerDoc)));
	return (CDemo_ui_explorerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemo_ui_explorerView message handlers
