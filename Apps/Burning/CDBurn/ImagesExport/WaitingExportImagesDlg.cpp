// WaitingExportImagesDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "ImagesExport.h"
#include "WaitingExportImagesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWaitingExportImagesDlg dialog


CWaitingExportImagesDlg::CWaitingExportImagesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWaitingExportImagesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWaitingExportImagesDlg)
		// NOTE: the ClassWizard will add member initialization here
	
	//}}AFX_DATA_INIT
}


void CWaitingExportImagesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDD_PIC_EXPORT_WAITING, m_dynline);
	//{{AFX_DATA_MAP(CWaitingExportImagesDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWaitingExportImagesDlg, CDialog)
	//{{AFX_MSG_MAP(CWaitingExportImagesDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaitingExportImagesDlg message handlers

BOOL CWaitingExportImagesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CenterWindow();
	//GetDlgItem(IDC_IMG)
	
	// TODO: Add extra initialization here
	m_dynline.Start();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CWaitingExportImagesDlg::OnCloseWaitingDlg()
{
	m_dynline.Stop();
	//this->SendMessage(WM_CLOSE);
	return TRUE;

}
