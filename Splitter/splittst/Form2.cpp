// Form2.cpp : implementation file
//

#include "stdafx.h"
#include "splittst.h"
#include "Form2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CForm2

IMPLEMENT_DYNCREATE(CForm2, CFormView)

CForm2::CForm2()
	: CFormView(CForm2::IDD)
{
	//{{AFX_DATA_INIT(CForm2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CForm2::~CForm2()
{
}

void CForm2::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CForm2)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CForm2, CFormView)
	//{{AFX_MSG_MAP(CForm2)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CForm2 diagnostics

#ifdef _DEBUG
void CForm2::AssertValid() const
{
	CFormView::AssertValid();
}

void CForm2::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CForm2 message handlers
