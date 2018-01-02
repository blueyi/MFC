// MenuDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BigSee.h"
#include "MenuDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMenuDlg dialog


CMenuDlg::CMenuDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMenuDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMenuDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMenuDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMenuDlg, CDialog)
	//{{AFX_MSG_MAP(CMenuDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMenuDlg message handlers

BOOL CMenuDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CPoint pt;
	GetCursorPos(&pt);
	SetWindowPos(NULL,pt.x,pt.y,0,0,SWP_NOSIZE);
	          //SWP_NOSIZE flags makes cx and cy useless 
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMenuDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	//load menu
	CMenu menu;
	menu.LoadMenu(IDR_POPUP_MENU);
	CMenu*pPopup=menu.GetSubMenu(0);
    CRect rect;
	GetDlgItem(IDC_MENU_STATIC)->GetWindowRect(&rect);
	int nleft=rect.right-1;
	GetWindowRect(&rect);
	pPopup->TrackPopupMenu(TPM_RIGHTBUTTON,nleft
		                   ,rect.top,GetParent());
	//
	PostMessage(WM_CLOSE);
	// Do not call CDialog::OnPaint() for painting messages
}



