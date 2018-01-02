// WzdSplsh.cpp : implementation file
//

#include "stdafx.h"
#include "WzdSplsh.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWzdSplash

CWzdSplash::CWzdSplash()
{
}

CWzdSplash::~CWzdSplash()
{
}


BEGIN_MESSAGE_MAP(CWzdSplash, CWnd)
	//{{AFX_MSG_MAP(CWzdSplash)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWzdSplash message handlers

void CWzdSplash::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	// get bitmap colors
	CPalette *pOldPal = dc.SelectPalette(m_bitmap.GetPalette(),FALSE);
	dc.RealizePalette();

	// get device context to select bitmap into
	CDC dcComp;
	dcComp.CreateCompatibleDC(&dc);
	dcComp.SelectObject(&m_bitmap);

	// draw bitmap
	dc.BitBlt(0,0,m_bitmap.m_Width,m_bitmap.m_Height, &dcComp, 0,0,SRCCOPY);

	// reselect old palette
	dc.SelectPalette(pOldPal,FALSE);
}

void CWzdSplash::Create( UINT nID )
{
	m_bitmap.LoadBitmapEx(nID,FALSE);

	int x = (::GetSystemMetrics (SM_CXSCREEN)-m_bitmap.m_Width)/2;
	int y = (::GetSystemMetrics (SM_CYSCREEN)-m_bitmap.m_Height)/2;
	CRect rect(x,y,x+m_bitmap.m_Width,y+m_bitmap.m_Height);
	CreateEx(0,AfxRegisterWndClass(0),"",WS_POPUP|WS_VISIBLE|WS_BORDER,rect,NULL,0);
}
