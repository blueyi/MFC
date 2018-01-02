// DrawBar.cpp : implementation file
//

#include "stdafx.h"
#include "vgis.h"
#include "DrawBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawBar dialog
extern CView *g_pView;

CDrawBar::CDrawBar()
{
	//{{AFX_DATA_INIT(CDrawBar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDrawBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDrawBar)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDrawBar, CDialogBar)
	//{{AFX_MSG_MAP(CDrawBar)
	ON_BN_CLICKED(IDC_LINE, OnLine)
	ON_BN_CLICKED(IDC_CIRCLE, OnCircle)
	ON_BN_CLICKED(IDC_ARC, OnArc)
	ON_BN_CLICKED(IDC_RGN, OnRgn)
	ON_BN_CLICKED(IDC_MLINE, OnMline)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_INITDIALOG,InitDialog)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawBar message handlers
LRESULT CDrawBar::InitDialog(WPARAM wParam,LPARAM lParam)
{
	if ( !HandleInitDialog(wParam, lParam) || !UpdateData(FALSE))
	{
		TRACE0("Warning: UpdateData failed during dialog init.\n");
		return 0;
	} 

	return 1;
}

void CDrawBar::OnLine() 
{
	// TODO: Add your control notification handler code here
	g_pView->SendMessage(WM_COMMAND,IDM_DRAW_LINE);

}

void CDrawBar::OnCircle() 
{
	// TODO: Add your control notification handler code here
	g_pView->SendMessage(WM_COMMAND,IDM_DRAW_CIRCLE);
}

void CDrawBar::OnArc() 
{
	// TODO: Add your control notification handler code here
	g_pView->SendMessage(WM_COMMAND,IDM_DRAW_ARC);
}

void CDrawBar::OnRgn() 
{
	// TODO: Add your control notification handler code here
	g_pView->SendMessage(WM_COMMAND,IDM_DRAW_RGN);
}

void CDrawBar::OnMline() 
{
	// TODO: Add your control notification handler code here
	g_pView->SendMessage(WM_COMMAND,IDM_DRAW_MLINE);
}




