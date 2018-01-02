// BmpStyleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "ShowStyleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowStyleDlg dialog

CShowStyleDlg::CShowStyleDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CShowStyleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShowStyleDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CShowStyleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowStyleDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShowStyleDlg, CMyDialog)
	//{{AFX_MSG_MAP(CShowStyleDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowStyleDlg message handlers

BOOL CShowStyleDlg::OnInitDialog() 
{
	CMyDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_useStatic.SubclassDlgItem(IDC_USE_MYSTATIC,this);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
