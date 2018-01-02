// MainView.cpp : implementation of the CMainView class
//

#include "stdafx.h"
#include "MultiScreen.h"
#include "mainfrm.h"
#include "Doc.h"
#include "MainView.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainView

IMPLEMENT_DYNCREATE(CMainView, CFormView)

BEGIN_MESSAGE_MAP(CMainView, CFormView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CMainView)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainView construction/destruction

CMainView::CMainView()
	: CFormView(CMainView::IDD)
{
	//{{AFX_DATA_INIT(CMainView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CMainView::~CMainView()
{
}

void CMainView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CMainView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainView printing

BOOL CMainView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMainView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMainView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMainView::OnPrint(CDC* pDC, CPrintInfo*)
{
	// TODO: add code to print the controls
}

/////////////////////////////////////////////////////////////////////////////
// CMainView diagnostics

#ifdef _DEBUG
void CMainView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMainView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CDoc* CMainView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDoc)));
	return (CDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainView message handlers

//---------------------------------------------------------------
//	Desc:
//	Params:
//	returns:
//---------------------------------------------------------------
void CMainView::OnInitialUpdate() 
{
	static	int FirstTime=true;
	CMainFrame* pFrame;
	CRect rectFrame,rectView;
	CFormView::OnInitialUpdate();
	if(FirstTime)
	{
		FirstTime=false;
		// Resize parent to fit dialog template exactly    
		// while not resizing beyond size of screen
		VERIFY( pFrame = (CMainFrame*)GetParentFrame() );
		pFrame->GetClientRect( rectFrame );
		GetClientRect( rectView );
		if ( rectFrame.Width() < rectView.Width()
			 || rectFrame.Height() > rectView.Height() )
		{        
			// Resize so can be refit to any template that fits the screen
			pFrame->MoveWindow( 0, 0, GetSystemMetrics(SM_CXSCREEN), 
							GetSystemMetrics(SM_CYSCREEN), FALSE ); 
		}
		pFrame->RecalcLayout();
		ResizeParentToFit(TRUE);    // Shrink to fit template
		pFrame->CenterWindow();
	}
	
}

//---------------------------------------------------------------
//	Desc:
//	Params:
//	returns:
//---------------------------------------------------------------
void CMainView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CMainFrame* pFrame=(CMainFrame*) AfxGetMainWnd();	
	pFrame->SetWindowText("Main View");
}

//---------------------------------------------------------------
//	Desc:
//	Params:
//	returns:
//---------------------------------------------------------------
void CMainView::OnContextMenu(CWnd*, CPoint point)
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
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_MAIN_VIEW));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

