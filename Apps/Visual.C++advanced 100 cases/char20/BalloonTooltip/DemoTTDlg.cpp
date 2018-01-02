// DemoTTDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DemoToolTip.h"
#include "DemoTTDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoTTDlg dialog


CDemoTTDlg::CDemoTTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoTTDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemoTTDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDemoTTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoTTDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDemoTTDlg, CDialog)
	//{{AFX_MSG_MAP(CDemoTTDlg)
	ON_CBN_DROPDOWN(IDC_COMBO, OnDropdownCombo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoTTDlg message handlers

BOOL CDemoTTDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_bttWnd.RelayEvent(pMsg);
	
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CDemoTTDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_bttWnd.Create(this);
	m_bttWnd.SetWidth(200);
	m_bttWnd.SetBkColor(RGB(213,253,224)); //RGB(210,210,255) violet
	m_bttWnd.SetFrameColor(RGB(0,106,53));

	m_bttWnd.AddTool(GetDlgItem(IDC_EDIT), "Edit Box");
	m_bttWnd.AddTool(GetDlgItem(IDC_COMBO), "Not Stuck");

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDemoTTDlg::OnDropdownCombo() 
{
	// TODO: Add your control notification handler code here
	
}
