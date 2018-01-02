// View4.cpp : implementation file
//

#include "stdafx.h"
#include "MultiScreen.h"
#include "View4.h"
#include "resource.h"
#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CView4

IMPLEMENT_DYNCREATE(CView4, CFormView)

CView4::CView4()
	: CFormView(CView4::IDD)
{
	//{{AFX_DATA_INIT(CView4)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CView4::~CView4()
{
}

void CView4::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CView4)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CView4, CFormView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CView4)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CView4 diagnostics

#ifdef _DEBUG
void CView4::AssertValid() const
{
	CFormView::AssertValid();
}

void CView4::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CView4 message handlers

void CView4::OnContextMenu(CWnd*, CPoint point)
{

	// CG: This block was added by the Pop-up Menu component
	{
		if (point.x == -1 && point.y == -1){
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_VIEW4));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}


void CView4::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CMainFrame* pFrame=(CMainFrame*) AfxGetMainWnd();	
	pFrame->SetWindowText("View 4");
}
