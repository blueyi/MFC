// Form1.cpp : implementation file
//

#include "stdafx.h"
#include "splittst.h"
#include "Form1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CForm1

IMPLEMENT_DYNCREATE(CForm1, CFormView)

CForm1::CForm1()
	: CFormView(CForm1::IDD)
{
	//{{AFX_DATA_INIT(CForm1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CForm1::~CForm1()
{
}

void CForm1::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CForm1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CForm1, CFormView)
	//{{AFX_MSG_MAP(CForm1)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CForm1 diagnostics

#ifdef _DEBUG
void CForm1::AssertValid() const
{
	CFormView::AssertValid();
}

void CForm1::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CForm1 message handlers
