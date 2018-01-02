// WzdTlBar.cpp : implementation file
//

#include "stdafx.h"
#include "wzd.h"
#include "WzdTlBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWzdToolBar

CWzdToolBar::CWzdToolBar()
{
}

CWzdToolBar::~CWzdToolBar()
{
}


BEGIN_MESSAGE_MAP(CWzdToolBar, CToolBar)
	//{{AFX_MSG_MAP(CWzdToolBar)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWzdToolBar message handlers

BOOL CWzdToolBar::LoadToolBarEx(UINT id)
{
	// load toolbar info
	BOOL bRet;
	if (bRet=CToolBar::LoadToolBar(id))
	{
		// make flat buttons
		ModifyStyle(0, TBSTYLE_FLAT);
	}

	return bRet;
}



void CWzdToolBar::OnPaint() 
{
	CToolBar::OnPaint();

	// if floating, no grabber bar
	if (IsFloating())
		return;

	// draw to whole window!
	CWindowDC dc(this);

	// draw horizontal or vertical grabber bar
	CRect rect;
	GetClientRect(&rect);

	CPen penHL(PS_SOLID,2,::GetSysColor(COLOR_3DHIGHLIGHT));
	CPen penSH(PS_SOLID,3,::GetSysColor(COLOR_3DSHADOW));

	CPen *pPen=dc.SelectObject(&penSH);
	if (GetBarStyle()&CBRS_ORIENT_HORZ)
	{
		// draw shadow lines
		rect.OffsetRect(4,4);
		dc.MoveTo(rect.left,rect.top);
		dc.LineTo(rect.left,rect.bottom);
		dc.MoveTo(rect.left+4,rect.top);
		dc.LineTo(rect.left+4,rect.bottom);

		// draw highlight lines
		dc.SelectObject(&penHL);
		dc.MoveTo(rect.left,rect.top);
		dc.LineTo(rect.left,rect.bottom-1);
		dc.MoveTo(rect.left+4,rect.top);
		dc.LineTo(rect.left+4,rect.bottom-1);
	}
	else
	{
		// draw shadow lines
		rect.OffsetRect(4,2);
		dc.MoveTo(rect.left,rect.top);
		dc.LineTo(rect.right,rect.top);
		dc.MoveTo(rect.left,rect.top+4);
		dc.LineTo(rect.right,rect.top+4);

		// draw highlight lines
		dc.SelectObject(&penHL);
		dc.MoveTo(rect.left,rect.top);
		dc.LineTo(rect.right-1,rect.top);
		dc.MoveTo(rect.left,rect.top+4);
		dc.LineTo(rect.right-1,rect.top+4);
	}

	dc.SelectObject(pPen);
}
