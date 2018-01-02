/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// ShowWnd.cpp : implementation of the CShowWnd class                      //
//                                     CColorWnd class                     //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ArrayCtrlDemo.h"
#include "ObjInfo.h"
#include "ShowWnd.h"
#include "SfxApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void	SfxTextOut	(CPaintDC* pDC, CPoint* pStart, LPTSTR lpText, COLORREF crColor, CFont* pFont);

extern	HICON	hSmile, hFrown, hUnimpr;


/////////////////////////////////////////////////////////////////////////////
// CShowWnd

CShowWnd::CShowWnd()
{
}

CShowWnd::~CShowWnd()
{
}


BEGIN_MESSAGE_MAP(CShowWnd,CWnd )
	//{{AFX_MSG_MAP(CShowWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CShowWnd message handlers

BOOL CShowWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
	if( !CWnd::PreCreateWindow(cs) ) return FALSE;
	return TRUE;
}

int CShowWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if( CWnd ::OnCreate(lpCreateStruct) == -1 ) return -1;
	
	// TODO: Add your specialized creation code here
	m_pImage = (CBitmap*)(lpCreateStruct->lpCreateParams);
	return 0;
}

void CShowWnd::OnPaint() 
{
	CPaintDC	dc(this);
	CRect		rc;

	// TODO: Add your message handler code here
	GetClientRect(&rc);
	::SfxDrawImage(&dc, 0, 0, rc.Width(), rc.Height(), m_pImage, 0);
	
	// Do not call CWnd::OnPaint() for painting messages
}

void CShowWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	DestroyWindow();
}

void CShowWnd::OnDestroy() 
{
	CWnd::OnDestroy();
	
	// TODO: Add your message handler code here
	::DeleteObject(m_pImage->Detach());
	delete m_pImage;
}

// CShowWnd end
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CColorWnd

CColorWnd::CColorWnd()
{
}

CColorWnd::~CColorWnd()
{
}


BEGIN_MESSAGE_MAP(CColorWnd,CWnd )
	//{{AFX_MSG_MAP(CColorWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CColorWnd message handlers

BOOL CColorWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
	if( !CWnd::PreCreateWindow(cs) ) return FALSE;
	return TRUE;
}

int CColorWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	CClrInfo*	pClrInfo;
	int			nLum, nLum1, nLum2;

	if( CWnd ::OnCreate(lpCreateStruct) == -1 ) return -1;
	
	// TODO: Add your specialized creation code here
	pClrInfo = (CClrInfo*)(lpCreateStruct->lpCreateParams);
	m_dwRGB = pClrInfo->GetRGBColor();
	m_dwHSB = pClrInfo->GetHSBColor();
	m_dwContrast1 = ::SfxContrastColor(m_dwRGB);
	m_dwContrast2 = ::SfxComplementColor(m_dwRGB, 40);
	m_pFont = ::SfxCreateFont(_T("Arial"), 8, 0, 0, 0);
	nLum = ::SfxGetLuminance(m_dwRGB);
	nLum1 = ::SfxGetLuminance(m_dwContrast1);
	nLum2 = ::SfxGetLuminance(m_dwContrast2);
	nLum1 = abs(nLum - nLum1);
	nLum2 = abs(nLum - nLum2);
	if( nLum1 < 30 ) m_hIcon1 = hFrown;
	else if( nLum1 < 40 ) m_hIcon1 = hUnimpr;
	else m_hIcon1 = hSmile;
	if( nLum2 < 30 ) m_hIcon2 = hFrown;
	else if( nLum2 < 40 ) m_hIcon2 = hUnimpr;
	else m_hIcon2 = hSmile;
	return 0;
}

void CColorWnd::OnPaint() 
{
	CPaintDC	dc(this);
	int			nW, nH;
	CRect		rcClient, rcCol;
	CBrush		brBack, brCol1, brCol2;
	CPoint		Start;
	COLORREF	crTxt;
	TCHAR		szBuffer[MAX_PATH];

	// TODO: Add your message handler code here
	GetClientRect(&rcClient);
	nW = rcClient.Width()/6;
	nH = rcClient.Height()/3;

	brBack.CreateSolidBrush(m_dwRGB);
	dc.FillRect(&rcClient, &brBack);
	::SfxGetColorInfo(m_dwRGB, m_dwHSB, TPTR(szBuffer), _T(" "));
	Start.x = 4;
	Start.y = 4;
	crTxt = RGB(0,0,0);
	if( ::SfxGetLuminance(m_dwRGB) < 50 ) crTxt = RGB(255,255,255);
	::SfxTextOut(&dc, &Start, TPTR(szBuffer), crTxt, m_pFont); 

	rcCol.SetRect(nW*2, nH, nW*3, nH*2);
	brCol1.CreateSolidBrush(m_dwContrast1);
	dc.FillRect(&rcCol, &brCol1);
	::SfxGetColorInfo(m_dwContrast1, CLR_NONE, TPTR(szBuffer), _T("\n"));
	Start.x = 4;
	Start.y = nH;
	::SfxTextOut(&dc, &Start, TPTR(szBuffer), m_dwContrast1, m_pFont); 
	::DrawIconEx(dc.GetSafeHdc(), nW*2, nH*2+8, m_hIcon1, 0, 0, 0, NULL, DI_NORMAL);

	rcCol.SetRect(nW*3, nH, nW*4, nH*2);
	brCol2.CreateSolidBrush(m_dwContrast2);
	dc.FillRect(&rcCol, &brCol2);
	::SfxGetColorInfo(m_dwContrast2, CLR_NONE, TPTR(szBuffer), _T("\n"));
	Start.x = nW*4 + 4;
	Start.y = nH;
	::SfxTextOut(&dc, &Start, TPTR(szBuffer), m_dwContrast2, m_pFont); 
	::DrawIconEx(dc.GetSafeHdc(), nW*4-16, nH*2+8, m_hIcon2, 0, 0, 0, NULL, DI_NORMAL);

	// Do not call CWnd::OnPaint() for painting messages
}

void CColorWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	DestroyWindow();
}

void CColorWnd::OnDestroy() 
{
	CWnd::OnDestroy();
	
	// TODO: Add your message handler code here
}

// CColorWnd end
/////////////////////////////////////////////////////////////////////////////

void SfxTextOut(CPaintDC* pDC, CPoint* pStart, LPTSTR lpText, COLORREF crColor, CFont* pFont)
{
	CFont*		pOrigFont;
	CSize		Size;
	LPTSTR		pSubStr;
	int			nLen, x, y;

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(crColor);
	if( pFont ) pOrigFont = pDC->SelectObject(pFont);

	x = pStart->x;
	y = pStart->y;
	pSubStr = _tcstok(lpText, _T("\n"));
	while( pSubStr )
	{
		nLen = lstrlen(pSubStr);
		Size = pDC->GetTextExtent(pSubStr, nLen);
		pDC->TextOut(x, y, pSubStr, nLen);
		y += Size.cy;
		pSubStr = _tcstok(NULL, _T("\n"));
	}
	if( pFont ) pDC->SelectObject(pOrigFont);
	pStart->y = y;
	pStart->x += Size.cx; 
}

