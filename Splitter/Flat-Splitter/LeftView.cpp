// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "FlatSplitter_Demo.h"

#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CView)

BEGIN_MESSAGE_MAP(CLeftView, CView)
	//{{AFX_MSG_MAP(CLeftView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView construction/destruction

CLeftView::CLeftView()
{
}

CLeftView::~CLeftView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

void CLeftView::OnDraw(CDC* pDC)
{
	CRect rect,rcClient;
	GetClientRect(rcClient);

//	pDC->FillSolidRect(rcClient,233+233*256+233*256*256);

//	return;
	COLORREF crLight = GetSysColor(COLOR_BTNHIGHLIGHT);
	COLORREF crShadow = GetSysColor(COLOR_BTNSHADOW);
	COLORREF crBtnFace = GetSysColor(COLOR_BTNFACE);

	pDC->SetBkMode(TRANSPARENT);
	CGdiObject *pOldFont = pDC->SelectStockObject(ANSI_VAR_FONT);

	rect = rcClient;

	// 1st rect
	rect.bottom = rect.top + 22;
	pDC->FillSolidRect(rect,crBtnFace);
	pDC->Draw3dRect(rect,crLight,crShadow);
	pDC->DrawText("   Some Title",rect,DT_SINGLELINE|DT_VCENTER);

	// 2nd rect
	rect.OffsetRect(0,22);
	pDC->FillSolidRect(rect,crBtnFace);
	pDC->Draw3dRect(rect,crLight,crShadow);
	pDC->DrawText("<===o===>",rect,DT_SINGLELINE|DT_VCENTER|DT_CENTER);

	// White rect
	rect.top = rect.bottom;
	rect.bottom = rcClient.bottom;
	pDC->FillSolidRect(rect,RGB(255,255,255));
	pDC->Draw3dRect(rect,crLight,crShadow);

	pDC->SelectObject(pOldFont);
}