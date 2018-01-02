// TestDlg2.cpp : implementation file
//

#include "stdafx.h"
#include "splitter.h"
#include "TestDlg2.h"
#include "splitterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestDlg2 property page

IMPLEMENT_DYNCREATE(CTestDlg2, CPropertyPage)

CTestDlg2::CTestDlg2() : CPropertyPage(CTestDlg2::IDD),m_mng(this)
{
	//{{AFX_DATA_INIT(CTestDlg2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CTestDlg2::~CTestDlg2()
{
}

void CTestDlg2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlg2)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestDlg2, CPropertyPage)
	//{{AFX_MSG_MAP(CTestDlg2)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg2 message handlers

void CTestDlg2::OnDestroy() 
{
	CPropertyPage::OnDestroy();
	
	m_mng.onDestroy();
}

BOOL CTestDlg2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
  m_mng.addControl(IDC_LIST1);
  m_mng.addControl(IDC_LIST9);
  m_mng.addControl(IDC_LIST5);
  m_mng.addControl(IDC_LIST6);

  m_mng.init();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTestDlg2::OnButton1() 
{
  CSplitterDlg	dlg;
  dlg.DoModal();
}

void CTestDlg2::OnSize(UINT nType, int cx, int cy) 
{
	CPropertyPage::OnSize(nType, cx, cy);
  m_mng.onSize(nType,cx,cy);
}
