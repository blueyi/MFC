#include "stdafx.h"
#include "ColorCtrls.h"
#include "ColorStatic.h"

CColorStatic::CColorStatic()
{
}

CColorStatic::~CColorStatic()
{
}

BEGIN_MESSAGE_MAP(CColorStatic, CStatic)
	//{{AFX_MSG_MAP(CColorStatic)
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

HBRUSH CColorStatic::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	HBRUSH hbr;
        pDC->SetTextColor(m_crFg);
        pDC->SetBkColor(m_crBg);
        hbr = *m_pBrush;
	return hbr;	
}
