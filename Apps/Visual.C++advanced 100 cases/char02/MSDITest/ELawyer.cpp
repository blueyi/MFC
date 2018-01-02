// ELawyer.cpp : implementation file
//

#include "stdafx.h"
#include "MSDITest.h"
#include "ELawyer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CELawyer

IMPLEMENT_DYNCREATE(CELawyer, CFormView)

CELawyer::CELawyer()
	: CFormView(CELawyer::IDD)
{
	//{{AFX_DATA_INIT(CELawyer)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CELawyer::~CELawyer()
{
}

void CELawyer::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CELawyer)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CELawyer, CFormView)
	//{{AFX_MSG_MAP(CELawyer)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CELawyer diagnostics

#ifdef _DEBUG
void CELawyer::AssertValid() const
{
	CFormView::AssertValid();
}

void CELawyer::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CELawyer message handlers

void CELawyer::OnChangeEdit2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}
