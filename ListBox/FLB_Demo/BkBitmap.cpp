// BkBitmap.cpp : implementation file
//

#include "stdafx.h"
#include "demoflb.h"
#include "BkBitmap.h"
#include <Transparency.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBkBitmap

CBkBitmap::CBkBitmap()
{
	m_bBkModified = TRUE;
}

CBkBitmap::~CBkBitmap()
{
}


BEGIN_MESSAGE_MAP(CBkBitmap, CStatic)
	//{{AFX_MSG_MAP(CBkBitmap)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBkBitmap message handlers

void CBkBitmap::OnPaint() 
{
	CStatic::OnPaint();
	CDC* pDC;
	if (m_bBkModified == TRUE)
	{
		pDC = GetParent()->GetDC();
		GetParent()->UpdateChildrenBackground(pDC, TRUE);
		GetParent()->ReleaseDC(pDC);
		m_bBkModified = FALSE;
	}
}

HBITMAP CBkBitmap::SetBitmap(HBITMAP hBitmap)
{
	m_bBkModified = TRUE;
	return CStatic::SetBitmap(hBitmap);
}