// DibView.cpp : implementation of the CDibView class
//

#include "stdafx.h"
#include "DibLookEx.h"

#include "Dib.h"
#include "DibDoc.h"
#include "MainFrm.h"
#include "DibView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDibView

IMPLEMENT_DYNCREATE(CDibView, CScrollView)

BEGIN_MESSAGE_MAP(CDibView, CScrollView)
	//{{AFX_MSG_MAP(CDibView)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDibView construction/destruction

CDibView::CDibView()
{
	// TODO: add construction code here

}

CDibView::~CDibView()
{
}

BOOL CDibView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDibView drawing

void CDibView::OnDraw(CDC* pDC)
{
	CDibDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->IsValid())
	{
		int cxDIB = (int)pDoc->Width();         // Size of DIB - x
		int cyDIB = (int)pDoc->Height();        // Size of DIB - y
		CRect rcDIB;
		rcDIB.top = rcDIB.left = 0;
		rcDIB.right = cxDIB;
		rcDIB.bottom = cyDIB;
		CRect rcDest;
		if (pDC->IsPrinting())   // printer DC
		{
			// get size of printer page (in pixels)
			int cxPage = pDC->GetDeviceCaps(HORZRES);
			int cyPage = pDC->GetDeviceCaps(VERTRES);
			// get printer pixels per inch
			int cxInch = pDC->GetDeviceCaps(LOGPIXELSX);
			int cyInch = pDC->GetDeviceCaps(LOGPIXELSY);

			//
			// Best Fit case -- create a rectangle which preserves
			// the DIB's aspect ratio, and fills the page horizontally.
			//
			// The formula in the "->bottom" field below calculates the Y
			// position of the printed bitmap, based on the size of the
			// bitmap, the width of the page, and the relative size of
			// a printed pixel (cyInch / cxInch).
			//
			rcDest.top = rcDest.left = 0;
			rcDest.bottom = (int)(((double)cyDIB * cxPage * cyInch)
					/ ((double)cxDIB * cxInch));
			rcDest.right = cxPage;
		}
		else   // not printer DC
		{
			rcDest = rcDIB;
		}
		pDoc->PaintDIB(pDC->m_hDC, &rcDest, &rcDIB);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDibView printing

BOOL CDibView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDibView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDibView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDibView diagnostics

#ifdef _DEBUG
void CDibView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDibView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDibDoc* CDibView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDibDoc)));
	return (CDibDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDibView message handlers

void CDibView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	CScrollView::OnActivateView(bActivate, pActivateView, pDeactiveView);

	if (bActivate) 
	{
		ASSERT(pActivateView==this);
		DoRealizePalette(FALSE);
	}
}

void CDibView::OnInitialUpdate() 
{
	CScrollView::OnInitialUpdate();
	
	CDibDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	SetScrollSizes(MM_TEXT, CSize(pDoc->Width(), pDoc->Height()));
}

void CDibView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetDocument()->IsValid());
}

void CDibView::OnEditCopy() 
{
	CDibDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// Clean clipboard of contents, and copy the DIB.
	if (OpenClipboard())
	{
		BeginWaitCursor();
		EmptyClipboard();
		SetClipboardData (CF_DIB, pDoc->CopyDIBToHandle());
		CloseClipboard();
		EndWaitCursor();
	}
}

void CDibView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(::IsClipboardFormatAvailable(CF_DIB));
}

void CDibView::OnEditPaste() 
{
	CDibDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (OpenClipboard())
	{
		BeginWaitCursor();
		pDoc->ReadDIBFromHandle(::GetClipboardData(CF_DIB));
		CloseClipboard();
		SetScrollSizes(MM_TEXT, CSize(pDoc->Width(), pDoc->Height()));
		DoRealizePalette(FALSE);  // realize the new palette
		EndWaitCursor();
	}
}

BOOL CDibView::OnQueryNewPalette() 
{
	return DoRealizePalette(FALSE);
}

void CDibView::OnPaletteChanged(CWnd* pFocusWnd) 
{
	if (pFocusWnd != this)
		DoRealizePalette(TRUE);
}

int CDibView::DoRealizePalette(BOOL bForceBackground)
{
	CDibDoc* pDoc = GetDocument();
	if (!pDoc->IsValid())
		return 0;  // must be a new document

	CPalette* pPalette = pDoc->GetDocPalette();
	if (pPalette==NULL)
		return 0; // the DIB has no palette

	CMainFrame* pAppFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_KINDOF(CMainFrame, pAppFrame);

	CClientDC appDC(pAppFrame);
	CPalette* oldPalette = appDC.SelectPalette(pPalette, bForceBackground);
	int nColorsChanged = 0;
	if (oldPalette != NULL)
	{
		nColorsChanged = appDC.RealizePalette();
		if (nColorsChanged > 0)
			pDoc->UpdateAllViews(NULL);
		appDC.SelectPalette(oldPalette, TRUE);
	}
	else
	{
		TRACE0("\tSelectPalette failed in CSampleView::DoRealizePalette\n");
	}
	
	return nColorsChanged;
}

