// TestDlg1.cpp : implementation file
//

#include "stdafx.h"
#include "splitter.h"
#include "TestDlg1.h"
#include "DemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestDlg1 dialog


CTestDlg1::CTestDlg1():ZSplitterDlgImpl<CPropertyPage>(CTestDlg1::IDD)
{
	
	//{{AFX_DATA_INIT(CTestDlg1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTestDlg1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlg1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestDlg1, ZSplitterDlgImpl<CPropertyPage>)
	//{{AFX_MSG_MAP(CTestDlg1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTestDlg1 message handlers

BOOL CTestDlg1::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
  addControls(2,false,IDC_LIST6,IDC_LIST7);
  addControls(2,true,IDC_LIST1,IDC_LIST8);
  
  addControl(IDC_LIST9);
  addControl(IDC_LIST2);
  addControl(IDC_LIST3);
  addControl(IDC_LIST4);
  addControl(IDC_LIST5);
  addControl(IDC_BUTTON2);

	init();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTestDlg1::OnButton1() 
{
  CDemoDlg dlg0;
	int nResponse = dlg0.DoModal();
}
