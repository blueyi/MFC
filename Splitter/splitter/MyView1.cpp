// CMyView1.cpp : implementation file
//

#include "stdafx.h"
#include "splitter.h"
#include "MyView1.h"

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
// CMyView1

IMPLEMENT_DYNCREATE(CMyView1, CView)
CMyView1::CMyView1()   
	  : ZSplitterDlgImpl<CView,MyZSplitter>()

{
	//{{AFX_DATA_INIT(CMyView1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMyView1::~CMyView1()
{
}

void CMyView1::DoDataExchange(CDataExchange* pDX)
{
	CView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyView1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

typedef ZSplitterDlgImpl<CView,MyZSplitter>  ZSplitterDlgImpl_CView_MyZSplitter;

BEGIN_MESSAGE_MAP(CMyView1,ZSplitterDlgImpl_CView_MyZSplitter)
	//{{AFX_MSG_MAP(CMyView1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyView1 diagnostics

void CMyView1::OnDraw(CDC* pDC)
{
	CMyView1* pDoc = (CMyView1*)GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

#ifdef _DEBUG
void CMyView1::AssertValid() const
{
	CView::AssertValid();
}

void CMyView1::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyView1 message handlers

#define ID_MY_WND1  45701
#define ID_MY_WND2  45702

void CMyView1::OnInitialUpdate() 
{
	CView::OnInitialUpdate();


  CRect rect1(100,100,200,150);
  CRect rect2(100,200,200,220);
  wnd1.Create("Do Nothing",WS_CHILD|WS_VISIBLE,rect1, this, ID_MY_WND1);
  wnd2.Create("Do Nothing",WS_CHILD|WS_VISIBLE,rect2, this, ID_MY_WND2);
	
  addControl(ID_MY_WND1);
  addControl(ID_MY_WND2);

	init();
	
}
