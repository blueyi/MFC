// SampleStatic.cpp : implementation file
//

#include "stdafx.h"
#include "SampleStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#define SAMPLE_TEXT _T("Sample match text")

/////////////////////////////////////////////////////////////////////////////
// CSampleStatic

BEGIN_MESSAGE_MAP(CSampleStatic, CStatic)
	//{{AFX_MSG_MAP(CSampleStatic)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CSampleStatic::CSampleStatic()
{
	m_rgbBackground = GetSysColor(COLOR_WINDOW);
	m_pBrush = new CBrush(m_rgbBackground);
}

CSampleStatic::~CSampleStatic()
{
	if (m_pBrush)
		delete m_pBrush;
}

/////////////////////////////////////////////////////////////////////////////
// CSampleStatic message handlers

void CSampleStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	dc.SetBkColor(m_rgbBackground);
	dc.SelectObject(m_pBrush);

	// vertical center
#if 0  // -----------------------------------------------------------
	CRect rect;
	GetClientRect(rect); 
	
	dc.DrawText(strText, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
#endif // -----------------------------------------------------------
}

void CSampleStatic::SetBackgroundColor(COLORREF rgb, BOOL bRedraw /*= TRUE*/) 
{ 
	m_rgbBackground = rgb; 
	if (m_pBrush)
		delete m_pBrush;
	m_pBrush = new CBrush(m_rgbBackground);
	if (bRedraw)
		Invalidate(); 
}

BOOL CSampleStatic::OnEraseBkgnd(CDC* pDC) 
{
	CRect cr;
	GetClientRect(cr); 
	pDC->FillRect(&cr, m_pBrush);

	return TRUE; //CStatic::OnEraseBkgnd(pDC);
}
