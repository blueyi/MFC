// CMyView2.cpp : implementation file
//

#include "stdafx.h"
#include "splitter.h"
#include "MyView2.h"

#include "testSheet.h"
#include "TestDlg1.h"
#include "TestDlg2.h"
#include "TestDlg3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyView2

IMPLEMENT_DYNCREATE(CMyView2, CFormView)
CMyView2::CMyView2()   
	: ZSplitterDlgImpl<CFormView>(CMyView2::IDD)
{
	//{{AFX_DATA_INIT(CMyView2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMyView2::~CMyView2()
{
}

void CMyView2::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyView2)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyView2, ZSplitterDlgImpl<CFormView>)
	//{{AFX_MSG_MAP(CMyView2)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyView2 diagnostics

void CMyView2::OnDraw(CDC* pDC)
{
	CMyView2* pDoc = (CMyView2*)GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

#ifdef _DEBUG
void CMyView2::AssertValid() const
{
	CFormView::AssertValid();
}

void CMyView2::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyView2 message handlers

void CMyView2::OnButton1() 
{

	CTestSheet dlg("Test");
  CTestDlg1 dlg1;
  CTestDlg2 dlg2;
  CTestDlg3 dlg3;
  dlg.AddPage(&dlg1);
  dlg.AddPage(&dlg2);
  dlg.AddPage(&dlg3);
	dlg.DoModal();

}

void CMyView2::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
  addControl(IDC_BUTTON1);
  addControl(IDC_BUTTON2);
  addControl(IDC_BUTTON3);

  init();
	
}
