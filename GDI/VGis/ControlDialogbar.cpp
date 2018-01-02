// ControlDialogbar.cpp : implementation file
//

#include "stdafx.h"
#include "vgis.h"
#include "ControlDialogbar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CControlDialogbar dialog
extern CView *g_pView;

CControlDialogbar::CControlDialogbar()
{
	//{{AFX_DATA_INIT(CControlDialogbar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CControlDialogbar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CControlDialogbar)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CControlDialogbar, CDialogBar)
	//{{AFX_MSG_MAP(CControlDialogbar)
	ON_BN_CLICKED(IDC_MOVE, OnMove)
	ON_BN_CLICKED(IDC_BIG, OnBig)
	ON_BN_CLICKED(IDC_ALL, OnAll)
	ON_BN_CLICKED(IDC_RECTBIG, OnRectbig)
	ON_BN_CLICKED(IDC_SMALL, OnSmall)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_INITDIALOG,InitDialog)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CControlDialogbar message handlers

void CControlDialogbar::OnMove() 
{
	// TODO: Add your control notification handler code here
	g_pView->SendMessage(WM_COMMAND,IDM_MOVE);
}

void CControlDialogbar::OnBig() 
{
	// TODO: Add your control notification handler code here
	g_pView->SendMessage(WM_COMMAND,IDM_DRAW_BIG);	
}

void CControlDialogbar::OnAll() 
{
	// TODO: Add your control notification handler code here
	g_pView->SendMessage(WM_COMMAND,IDM_ALL);	
}

void CControlDialogbar::OnRectbig() 
{
	// TODO: Add your control notification handler code here
	g_pView->SendMessage(WM_COMMAND,IDM_RECTBIG);	
}

void CControlDialogbar::OnSmall() 
{
	// TODO: Add your control notification handler code here
	g_pView->SendMessage(WM_COMMAND,IDM_DRAW_SMALL);	
}
LRESULT CControlDialogbar::InitDialog(WPARAM wParam,LPARAM lParam)
{
	if ( !HandleInitDialog(wParam, lParam) || !UpdateData(FALSE))
	{
		TRACE0("Warning: UpdateData failed during dialog init.\n");
		return 0;
	} 

	CButton *pbtn=(CButton *)this->GetDlgItem(IDC_MOVE);
	pbtn->SetIcon(AfxGetApp()->LoadIcon(IDI_MOVE));

	pbtn=(CButton *)this->GetDlgItem(IDC_BIG);
	pbtn->SetIcon(AfxGetApp()->LoadIcon(IDI_ADD));

	pbtn=(CButton *)this->GetDlgItem(IDC_SMALL);
	pbtn->SetIcon(AfxGetApp()->LoadIcon(IDI_DEC));

	pbtn=(CButton *)this->GetDlgItem(IDC_RECTBIG);
	pbtn->SetIcon(AfxGetApp()->LoadIcon(IDI_RECT));
	return 1;
}