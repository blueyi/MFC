// TestPageView.cpp : implementation of the CTestPageView class
//

#include "stdafx.h"
#include "TestPage.h"

#include "TestPageDoc.h"
#include "TestPageView.h"

#include "PageWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CPageWnd* ClientPagePtr;  //pointer on CPageWnd 

/////////////////////////////////////////////////////////////////////////////
// CTestPageView

IMPLEMENT_DYNCREATE(CTestPageView, CView)

BEGIN_MESSAGE_MAP(CTestPageView, CView)
	//{{AFX_MSG_MAP(CTestPageView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestPageView construction/destruction

CTestPageView::CTestPageView()
{
  //creating CPageWnd object
  try 
  {
    int nrows = 32;
    int ncols = 16;
    ClientPagePtr = new CPageWnd(nrows, ncols);
  }
  catch(...)
  {
    TRACE("new CPageWnd(18, 32) failed");
    ClientPagePtr = 0;
  }

}

CTestPageView::~CTestPageView()
{
  //deleteing CPageWnd object
  if(ClientPagePtr)
    delete ClientPagePtr;
}

BOOL CTestPageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestPageView drawing

void CTestPageView::OnDraw(CDC* pDC)
{
	CTestPageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTestPageView printing

BOOL CTestPageView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestPageView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestPageView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTestPageView diagnostics

#ifdef _DEBUG
void CTestPageView::AssertValid() const
{
	CView::AssertValid();
}

void CTestPageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestPageDoc* CTestPageView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestPageDoc)));
	return (CTestPageDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestPageView message handlers

void CTestPageView::OnInitialUpdate() 
{
  CView::OnInitialUpdate();
  
  //creating CPageWnd windows object

  if(ClientPagePtr == 0) {
      TRACE("ClientPagePtr = 0 in CTestPageView::OnInitialUpdate");
      return;
  }

  if(ClientPagePtr->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, 
	  CRect(0, 0, 0, 0), this, 201, NULL)) {
	  
	  //example of setting text in CPageWnd (see  PageWnd.h for color, alignment and font etc.)
    char text[16];

    int nrows = ClientPagePtr->GetRowCount();
    int ncols = ClientPagePtr->GetColCount();

	  for(int row = 0; row < nrows; row++)  {
  		sprintf(text, "%d", row);
	  	ClientPagePtr->SetCellText(row, 0, text);
	  }

	  for(int col = 1; col < ncols; col++)  {
		  sprintf(text, "%c", 'A' + col - 1);
		  ClientPagePtr->SetCellText(0, col, text);
	  }	  
  }
  
}

void CTestPageView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
  //resizing CPageWnd object
	if(ClientPagePtr && IsWindow(ClientPagePtr->m_hWnd))
    ClientPagePtr->MoveWindow(0, 0, cx, cy, true);
	
}
