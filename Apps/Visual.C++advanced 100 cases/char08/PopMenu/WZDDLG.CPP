// WzdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "wzd.h"
#include "WzdDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWzdDialog dialog


CWzdDialog::CWzdDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CWzdDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWzdDialog)
	//}}AFX_DATA_INIT
}


void CWzdDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWzdDialog)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWzdDialog, CDialog)
	//{{AFX_MSG_MAP(CWzdDialog)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWzdDialog message handlers

BOOL CWzdDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// position where mouse button was clicked
	CPoint pt;
	GetCursorPos(&pt); 
	SetWindowPos(NULL,pt.x,pt.y,0,0,SWP_NOSIZE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWzdDialog::OnPaint() 
{
	CDialog::OnPaint();

	// load up menu
	CMenu menu;
	menu.LoadMenu(IDR_WZD_MENU);
	CMenu* pPopup = menu.GetSubMenu(0);

	// get location of static control and display popup menu there
	CRect rect;
	GetDlgItem(IDC_MENU_STATIC)->GetWindowRect(&rect);
	int nLeft=rect.right+2;
	GetWindowRect(&rect);
	pPopup->TrackPopupMenu(TPM_RIGHTBUTTON, nLeft, rect.top, GetParent());

	// cancel this dialog
	PostMessage(WM_CLOSE);
}
