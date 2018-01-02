// GRADPAL.CPP
// Written by chensu


#include <afxwin.h>
#include "gradpal.h"


//*****************************************************************************
//-----------------------------------------------------------------------------
CGradpalApp GradpalApp;
//-----------------------------------------------------------------------------
//*****************************************************************************


//*****************************************************************************
//-----------------------------------------------------------------------------
BOOL CGradpalApp::InitInstance()
{
	CGradpalWnd *pMainFrame = new CGradpalWnd();

	if (!pMainFrame->CreateWnd())
		return FALSE;

	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
	
	m_pMainWnd = pMainFrame;
	
	return TRUE;
}
//-----------------------------------------------------------------------------
//*****************************************************************************


//*****************************************************************************
//-----------------------------------------------------------------------------
CGradpalWnd::CGradpalWnd() :
	m_nPaintSteps(236),		// the number of steps
	m_nPaintDir(GPD_BTOT),	// the direction
	m_nPaintRGB(GPC_BLUE)	// the color
{
	VERIFY(this->CreateGradPalette());
}
//-----------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CGradpalWnd, CFrameWnd)
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	ON_WM_PAINT()
END_MESSAGE_MAP()
//-----------------------------------------------------------------------------
BOOL CGradpalWnd::OnQueryNewPalette()
{
	CClientDC dc(this);
	
	CPalette *pPalOld = dc.SelectPalette(&m_Pal, FALSE);
	
	BOOL bRet = dc.RealizePalette();
	
	dc.SelectPalette(pPalOld, FALSE);
	
	if (bRet)
		// some colors changed
		this->Invalidate();
	
	return bRet;
}
//-----------------------------------------------------------------------------
void CGradpalWnd::OnPaletteChanged(CWnd *pFocusWnd)
{
	if (pFocusWnd != this)
		this->OnQueryNewPalette();
}
//-----------------------------------------------------------------------------
void CGradpalWnd::OnPaint()
{
	CPaintDC dc(this);
	
	CPalette *pPalOld = dc.SelectPalette(&m_Pal, FALSE);
	dc.RealizePalette();
	
	RECT rect;
	this->GetClientRect(&rect);
	
	this->PaintGradiantRect(&dc, rect);
	
	dc.SelectPalette(pPalOld, FALSE);
}
//-----------------------------------------------------------------------------
void CGradpalWnd::PaintGradiantRect(CDC *pDC, const RECT &rect) const
{
	ASSERT(pDC != NULL);
	ASSERT_KINDOF(CDC, pDC);
	
	// initialize
	RECT rectVar = { rect.left, rect.top, rect.left, rect.top };
	int nTotalSize;
	if (m_nPaintDir == GPD_TTOB || m_nPaintDir == GPD_BTOT)
	{
		rectVar.right = rect.right;
		nTotalSize = rect.bottom - rect.top;
	}
	else
	{
		rectVar.bottom = rect.bottom;
		nTotalSize = rect.right - rect.left;
	}
	
	// paint nSteps times
	for (int nIndex = 0; nIndex < m_nPaintSteps; nIndex++)
	{
		// calculate the rectangle
		if (m_nPaintDir == GPD_TTOB || m_nPaintDir == GPD_BTOT)
		{
			rectVar.top = rectVar.bottom;
			rectVar.bottom = rect.top +
							 ::MulDiv(nIndex + 1, nTotalSize, m_nPaintSteps);
		}
		else
		{
			rectVar.left = rectVar.right;
			rectVar.right = rect.left +
							::MulDiv(nIndex + 1, nTotalSize, m_nPaintSteps);
		}
		
		// calculate the color value
		int nColor = ::MulDiv(nIndex, 255, m_nPaintSteps);
		if (m_nPaintDir == GPD_BTOT || m_nPaintDir == GPD_RTOL)
			nColor = 255 - nColor;
		const COLORREF clrBr =
			PALETTERGB((BYTE)(m_nPaintRGB & GPC_RED ? nColor : 0),
					   (BYTE)(m_nPaintRGB & GPC_GREEN ? nColor : 0),
					   (BYTE)(m_nPaintRGB & GPC_BLUE ? nColor : 0));
		
		// paint the rectangle with the brush
		CBrush brush(clrBr);
		pDC->FillRect(&rectVar, &brush);
	}
}
//-----------------------------------------------------------------------------
BOOL CGradpalWnd::CreateGradPalette()
{
	if (m_Pal.GetSafeHandle() != NULL)
		return FALSE;
	
	BOOL bSucc = FALSE;
	
	const int nNumColors = 236;
	
	LPLOGPALETTE lpPal = (LPLOGPALETTE)new BYTE[sizeof(LOGPALETTE) +
												sizeof(PALETTEENTRY) *
												nNumColors];
	
	if (lpPal != NULL)
	{
		lpPal->palVersion = 0x300;
		lpPal->palNumEntries = nNumColors;
		
		PALETTEENTRY *ppe = lpPal->palPalEntry;
		
		for (int nIndex = 0; nIndex < nNumColors; nIndex++)
		{
			const int nColor = ::MulDiv(nIndex, 255, nNumColors);
			
			ppe->peRed = (BYTE)(m_nPaintRGB & GPC_RED ? nColor : 0);
			ppe->peGreen = (BYTE)(m_nPaintRGB & GPC_GREEN ? nColor : 0);
			ppe->peBlue = (BYTE)(m_nPaintRGB & GPC_BLUE ? nColor : 0);
			ppe->peFlags = (BYTE)0;
			
			ppe++;
		}
		
		bSucc = m_Pal.CreatePalette(lpPal);
		
		delete [](PBYTE)lpPal;
	}
	
	return bSucc;
}
//-----------------------------------------------------------------------------
//*****************************************************************************


// End of GRADPAL.CPP
