// TestDlg1.cpp : implementation file
//

#include "stdafx.h"
#include "splitter.h"
#include "TestDlg3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestDlg3 dialog


CTestDlg3::CTestDlg3() : CPropertyPage(CTestDlg3::IDD)
{
	//{{AFX_DATA_INIT(CTestDlg3)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTestDlg3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlg3)
		// NOTE: the ClassWizard will add DDX and DDV calls here
  DDX_Control(pDX, IDC_SPLIT_MID, m_spliter);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestDlg3, CPropertyPage)
	//{{AFX_MSG_MAP(CTestDlg3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg3 message handlers

BOOL CTestDlg3::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
  m_spliter.addWindow(IDC_LIST1,sp_StyleRight|sp_StyleBottom);
  m_spliter.addWindow(IDC_LIST9,sp_StyleRight|sp_StyleTop);
  m_spliter.addWindow(IDC_LIST6,sp_StyleLeft|sp_StyleTop);
  m_spliter.addWindow(IDC_LIST5,sp_StyleLeft|sp_StyleBottom);
  m_spliter.setStyle(sp_StyleRect);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
