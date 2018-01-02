// SpinnerTBView.cpp : implementation of the CSpinnerTBView class
//

/*##################################################################

  Author:	Masoud Samimi
  Website:	www.geocities.com/samimi73
  Email:	marcello43@hotmail.com

  Program:	Spinner Toolbars
  History:	22.07.2000 (dd.mm.yy)
  
  Purpose: Please visit my website, it is expalined there.
  

Important Notice:

	This Idea and the Application is Copyright(c) Masoud Samimi 1999,2000.
	You can freely use it as long as you credit me for it.

	No guarantee/warantee, expressed or implied is given on this app and I will not be responsible 
	for any damage to you, your property or any other person from using it.
	USE IT ON YOUR OWN RISK.

	Thankyou and have FUNNE =-)

	Masoud Samimi.

##################################################################*/

#include "stdafx.h"
#include "SpinnerTB.h"

#include "SpinnerTBDoc.h"
#include "SpinnerTBView.h"

#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpinnerTBView

IMPLEMENT_DYNCREATE(CSpinnerTBView, CView)

BEGIN_MESSAGE_MAP(CSpinnerTBView, CView)
	//{{AFX_MSG_MAP(CSpinnerTBView)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	ON_COMMAND(ID_COLORS_RED, OnColorsRed)
	ON_COMMAND(ID_COLORS_GREEN, OnColorsGreen)
	ON_COMMAND(ID_COLORS_BLUE, OnColorsBlue)
	ON_COMMAND(ID_COLORS_SPINNERS, OnColorsSpinners)
	ON_EN_CHANGE(ID_EDIT_R, OnUpdateRed)
	ON_EN_CHANGE(ID_EDIT_G, OnUpdateGreen)
	ON_EN_CHANGE(ID_EDIT_B, OnUpdateBlue)
	ON_EN_CHANGE(ID_EDIT_SLD, OnUpdateGradient)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpinnerTBView construction/destruction

CSpinnerTBView::CSpinnerTBView()
{
	// TODO: add construction code here
	
}

CSpinnerTBView::~CSpinnerTBView()
{



}

BOOL CSpinnerTBView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSpinnerTBView drawing

void CSpinnerTBView::OnDraw(CDC* pDC)
{
	
	CSpinnerTBDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


}

/////////////////////////////////////////////////////////////////////////////
// CSpinnerTBView printing

BOOL CSpinnerTBView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSpinnerTBView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSpinnerTBView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSpinnerTBView diagnostics

#ifdef _DEBUG
void CSpinnerTBView::AssertValid() const
{
	CView::AssertValid();
}

void CSpinnerTBView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSpinnerTBDoc* CSpinnerTBView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSpinnerTBDoc)));
	return (CSpinnerTBDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSpinnerTBView message handlers

void CSpinnerTBView::OnPaint() 
{

	CRect rect;
    GetClientRect (&rect);
	rect.OffsetRect (0, 60);

    CPaintDC dc (this);
    DoDrawText (&dc, &rect);

	
}

int CSpinnerTBView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	

	CClientDC dc (this);
    if (dc.GetDeviceCaps (RASTERCAPS) & RC_PALETTE) {
        struct {
            LOGPALETTE lp;
            PALETTEENTRY ape[63];
        } pal;

        LOGPALETTE* pLP = (LOGPALETTE*) &pal;
        pLP->palVersion = 0x300;
        pLP->palNumEntries = 64;

        for (int i=0; i<64; i++) {
            pLP->palPalEntry[i].peRed = 0;
            pLP->palPalEntry[i].peGreen = 0;
            pLP->palPalEntry[i].peBlue = 255 - (i * 4);
            pLP->palPalEntry[i].peFlags = 0;
        }
        m_palette.CreatePalette (pLP);
    }
    return 0;

}

BOOL CSpinnerTBView::OnEraseBkgnd(CDC* pDC) 
{
	 
	CRect rect;
    GetClientRect (&rect);

    CPalette* pOldPalette;
    if ((HPALETTE) m_palette != NULL) {
        pOldPalette = pDC->SelectPalette (&m_palette, FALSE);
        pDC->RealizePalette ();
    }

    DoGradientFill (pDC, &rect);

    if ((HPALETTE) m_palette != NULL)
        pDC->SelectPalette (pOldPalette, FALSE);
    
	return TRUE;
	
	
}


BOOL CSpinnerTBView::OnQueryNewPalette ()
{
    if ((HPALETTE) m_palette == NULL)   // Shouldn't happen, but
        return 0;                       // let's be sure.

    CClientDC dc (this);
    CPalette* pOldPalette = dc.SelectPalette (&m_palette, FALSE);

    UINT nCount;
    if (nCount = dc.RealizePalette ())
        Invalidate ();

    dc.SelectPalette (pOldPalette, FALSE);
    return nCount;
}

void CSpinnerTBView::OnPaletteChanged (CWnd* pFocusWnd)
{
    if ((HPALETTE) m_palette == NULL)   // Shouldn't happen, but
        return;                         // let's be sure.

    if (pFocusWnd != this) {
        CClientDC dc (this);
        CPalette* pOldPalette = dc.SelectPalette (&m_palette, FALSE);
        if (dc.RealizePalette ())
            Invalidate ();
        dc.SelectPalette (pOldPalette, FALSE);
    }
}

void CSpinnerTBView::DoGradientFill (CDC* pDC, LPRECT pRect)
{
	
	CSpinnerTBDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);

    CBrush* pBrush[64];
    for (int i=0; i<64; i++)
      pBrush[i] = new CBrush (PALETTERGB (pDoc->m_nGradValue,
		pDoc->m_nGradValue,
		pDoc->m_nGradValue - (i * 4)));

    int nWidth = pRect->right - pRect->left;
    int nHeight = pRect->bottom - pRect->top;
    CRect rect;

    for (i=0; i<nHeight; i++) {
        rect.SetRect (0, i, nWidth, i + 1);
        pDC->FillRect (&rect, pBrush[(i * 63) / nHeight]);
    }

	AfxGetMainWnd ()->SendMessage (WM_USER_UPDATE_GRADIENT, 0,
	        (LPARAM) (UINT) pDoc->m_nGradValue);

	m_strRGB.Format("Gradient Value: %d ",pDoc->m_nGradValue);
	AfxGetMainWnd ()->SendMessage (WM_USER_UPDATE_GRADIENT_STATUS, 0,
	        (LPARAM) (LPCTSTR) m_strRGB);

    for (i=0; i<64; i++)
        delete pBrush[i];

	
}

void CSpinnerTBView::DoDrawText (CDC* pDC, LPRECT pRect)
{
		
	CSpinnerTBDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 		
	CFont font;
    font.CreatePointFont (120,
		_T ("Comic Sans MS"));
   
    CFont* pOldFont = pDC->SelectObject (&font);

	pDC->SetBkMode (TRANSPARENT);   
	pDC->SetTextColor(pDoc->m_clrTextClr);
	pDC->DrawText (pDoc->m_strText, -1, pRect, 
				DT_CENTER | DT_VCENTER);

    pDC->SelectObject (pOldFont);

	m_strRGB.Format("Text: Red=%d, Green=%d, Blue=%d.", pDoc->m_nRed, pDoc->m_nGreen, pDoc->m_nBlue);
	
	AfxGetMainWnd ()->SendMessage (WM_USER_UPDATE_COLOR, 0,
	        (LPARAM) (LPCTSTR) m_strRGB);

	AfxGetMainWnd ()->SendMessage (WM_USER_UPDATE_SPINNER_RED, 0,
	        (LPARAM) (UINT) pDoc->m_nRed);
	AfxGetMainWnd ()->SendMessage (WM_USER_UPDATE_SPINNER_GREEN, 0,
	        (LPARAM) (UINT) pDoc->m_nGreen);
	AfxGetMainWnd ()->SendMessage (WM_USER_UPDATE_SPINNER_BLUE, 0,
	        (LPARAM) (UINT) pDoc->m_nBlue);


}

void CSpinnerTBView::OnColorsRed() 
{
		
	// Get a pointer to our Main Frame
//	CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
//	ASSERT_VALID(pFrame);

	CSpinnerTBDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 		
	pDoc->m_nRed = 255;
	pDoc->m_nGreen = 0;
	pDoc->m_nBlue = 0;
	pDoc->m_clrTextClr = RGB(pDoc->m_nRed, pDoc->m_nGreen, pDoc->m_nBlue);
	pDoc->UpdateAllViews(0);
	pDoc->SetModifiedFlag();
	
	m_strRGB.Format("Text: Red=%d, Green=%d, Blue=%d.", pDoc->m_nRed, pDoc->m_nGreen, pDoc->m_nBlue);
	AfxGetMainWnd ()->SendMessage (WM_USER_UPDATE_COLOR, 0,
	        (LPARAM) (LPCTSTR) m_strRGB);


	AfxGetMainWnd ()->SendMessage (WM_USER_UPDATE_SPINNER_RED, 0,
	        (LPARAM) (UINT) pDoc->m_nRed);
	AfxGetMainWnd ()->SendMessage (WM_USER_UPDATE_SPINNER_GREEN, 0,
	        (LPARAM) (UINT) pDoc->m_nGreen);
	AfxGetMainWnd ()->SendMessage (WM_USER_UPDATE_SPINNER_BLUE, 0,
	        (LPARAM) (UINT) pDoc->m_nBlue);

}


void CSpinnerTBView::OnColorsGreen() 
{
	
	// Get a pointer to our Main Frame
//	CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
//	ASSERT_VALID(pFrame);
	
	CSpinnerTBDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 		
	pDoc->m_nRed = 0;
	pDoc->m_nGreen = 255;
	pDoc->m_nBlue = 0;
	pDoc->m_clrTextClr = RGB(pDoc->m_nRed, pDoc->m_nGreen, pDoc->m_nBlue);
	pDoc->UpdateAllViews(0);
	pDoc->SetModifiedFlag();

	m_strRGB.Format("Text: Red=%d, Green=%d, Blue=%d.", pDoc->m_nRed, pDoc->m_nGreen, pDoc->m_nBlue);
	AfxGetMainWnd ()->SendMessage (WM_USER_UPDATE_COLOR, 0,
	        (LPARAM) (LPCTSTR) m_strRGB);

	AfxGetMainWnd ()->SendMessage (WM_USER_UPDATE_SPINNER_RED, 0,
	        (LPARAM) (UINT) pDoc->m_nRed);
	AfxGetMainWnd ()->SendMessage (WM_USER_UPDATE_SPINNER_GREEN, 0,
	        (LPARAM) (UINT) pDoc->m_nGreen);
	AfxGetMainWnd ()->SendMessage (WM_USER_UPDATE_SPINNER_BLUE, 0,
	        (LPARAM) (UINT) pDoc->m_nBlue);


}



void CSpinnerTBView::OnColorsBlue() 
{
	
	// Get a pointer to our Main Frame
//	CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
//	ASSERT_VALID(pFrame);

	CSpinnerTBDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 		
	pDoc->m_nRed = 0;
	pDoc->m_nGreen = 0;
	pDoc->m_nBlue = 255;
	pDoc->m_clrTextClr = RGB(pDoc->m_nRed, pDoc->m_nGreen, pDoc->m_nBlue);
	pDoc->UpdateAllViews(0);
	pDoc->SetModifiedFlag();
	
	m_strRGB.Format("Text: Red=%d, Green=%d, Blue=%d.", pDoc->m_nRed, pDoc->m_nGreen, pDoc->m_nBlue);
	AfxGetMainWnd ()->SendMessage (WM_USER_UPDATE_COLOR, 0,
	        (LPARAM) (LPCTSTR) m_strRGB);

	AfxGetMainWnd ()->SendMessage (WM_USER_UPDATE_SPINNER_RED, 0,
	        (LPARAM) (UINT) pDoc->m_nRed);
	AfxGetMainWnd ()->SendMessage (WM_USER_UPDATE_SPINNER_GREEN, 0,
	        (LPARAM) (UINT) pDoc->m_nGreen);
	AfxGetMainWnd ()->SendMessage (WM_USER_UPDATE_SPINNER_BLUE, 0,
	        (LPARAM) (UINT) pDoc->m_nBlue);

}

void CSpinnerTBView::OnColorsSpinners() 
{
		
	// Get a pointer to our Main Frame
	CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pFrame);

	// Document pointer
	CSpinnerTBDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);
 		
	pDoc->m_nRed = pFrame->m_wndSpinBar.m_nRed;
	pDoc->m_nGreen = pFrame->m_wndSpinBar.m_nGreen;
	pDoc->m_nBlue = pFrame->m_wndSpinBar.m_nBlue;
	pDoc->m_clrTextClr = RGB(pDoc->m_nRed, pDoc->m_nGreen, pDoc->m_nBlue);
	
	m_strRGB.Format("Spinners: Red=%d, Green=%d, Blue=%d.", pDoc->m_nRed, pDoc->m_nGreen, pDoc->m_nBlue);
	MessageBox(_T(m_strRGB), _T("Spinners Values Report"));
	

}



void CSpinnerTBView::OnUpdateRed() 
{

	// Get a pointer to our Main Frame
	CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pFrame);

	// Document pointer
	CSpinnerTBDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);

	pFrame->m_wndSpinBar.m_nRed = pFrame->m_wndSpinBar.m_wndSpin_r.GetPos();
	pDoc->m_nRed = pFrame->m_wndSpinBar.m_nRed;
	pDoc->m_clrTextClr = RGB(pDoc->m_nRed, pDoc->m_nGreen, pDoc->m_nBlue);
	pDoc->UpdateAllViews(NULL);
	pDoc->SetModifiedFlag(); 
	

}


void CSpinnerTBView::OnUpdateGreen() 
{
	
	// Get a pointer to our Main Frame
	CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pFrame);

	// Document pointer
	CSpinnerTBDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);

	pFrame->m_wndSpinBar.m_nGreen = pFrame->m_wndSpinBar.m_wndSpin_g.GetPos();
	pDoc->m_nGreen = pFrame->m_wndSpinBar.m_nGreen;
	pDoc->m_clrTextClr = RGB(pDoc->m_nRed, pDoc->m_nGreen, pDoc->m_nBlue);
	pDoc->UpdateAllViews(0);
	pDoc->SetModifiedFlag(); 


}


void CSpinnerTBView::OnUpdateBlue() 
{

	// Get a pointer to our Main Frame
	CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pFrame);

	// Document pointer
	CSpinnerTBDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);

	pFrame->m_wndSpinBar.m_nBlue = pFrame->m_wndSpinBar.m_wndSpin_b.GetPos();
	pDoc->m_nBlue = pFrame->m_wndSpinBar.m_nBlue;
	pDoc->m_clrTextClr = RGB(pDoc->m_nRed, pDoc->m_nGreen, pDoc->m_nBlue);
	pDoc->UpdateAllViews(0);
	pDoc->SetModifiedFlag();
	

}


void CSpinnerTBView::OnUpdateGradient() 
{

	// Get a pointer to our Main Frame
	CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_VALID(pFrame);

	// Document pointer
	CSpinnerTBDoc* pDoc = GetDocument();
 	ASSERT_VALID(pDoc);

	pFrame->m_wndSpinBar.m_nGradValue  = pFrame->m_wndSpinBar.m_wndSlider.GetPos();
	pDoc->m_nGradValue = pFrame->m_wndSpinBar.m_nGradValue; 
	pDoc->UpdateAllViews(0);
	pDoc->SetModifiedFlag();

//	AfxMessageBox("Test");
	
}
