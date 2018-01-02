// SCBDemoView.cpp : implementation of the CSCBDemoView class
//

#include "stdafx.h"
#include "SCBDemo.h"

#include "SCBDemoDoc.h"
#include "SCBDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSCBDemoView

IMPLEMENT_DYNCREATE(CSCBDemoView, CEditView)

BEGIN_MESSAGE_MAP(CSCBDemoView, CEditView)
    //{{AFX_MSG_MAP(CSCBDemoView)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
    // Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSCBDemoView construction/destruction

CSCBDemoView::CSCBDemoView()
{
    // TODO: add construction code here

}

CSCBDemoView::~CSCBDemoView()
{
}

BOOL CSCBDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    BOOL bPreCreated = CEditView::PreCreateWindow(cs);
    cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);   // Enable word-wrapping

    return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CSCBDemoView drawing

void CSCBDemoView::OnDraw(CDC* pDC)
{
    CSCBDemoDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

    // TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSCBDemoView printing

BOOL CSCBDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // default CEditView preparation
    return CEditView::OnPreparePrinting(pInfo);
}

void CSCBDemoView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
    // Default CEditView begin printing.
    CEditView::OnBeginPrinting(pDC, pInfo);
}

void CSCBDemoView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
    // Default CEditView end printing
    CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CSCBDemoView diagnostics

#ifdef _DEBUG
void CSCBDemoView::AssertValid() const
{
    CEditView::AssertValid();
}

void CSCBDemoView::Dump(CDumpContext& dc) const
{
    CEditView::Dump(dc);
}

CSCBDemoDoc* CSCBDemoView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSCBDemoDoc)));
    return (CSCBDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSCBDemoView message handlers
