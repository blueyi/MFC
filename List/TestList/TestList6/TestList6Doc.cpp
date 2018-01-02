// TestList6Doc.cpp : implementation of the CTestList6Doc class
//

#include "stdafx.h"
#include "TestList6.h"

#include "TestList6Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestList6Doc

IMPLEMENT_DYNCREATE(CTestList6Doc, CDocument)

BEGIN_MESSAGE_MAP(CTestList6Doc, CDocument)
	//{{AFX_MSG_MAP(CTestList6Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestList6Doc construction/destruction

CTestList6Doc::CTestList6Doc()
{
	// TODO: add one-time construction code here

}

CTestList6Doc::~CTestList6Doc()
{
}

BOOL CTestList6Doc::OnNewDocument()
{
	if(! CDocument::OnNewDocument())return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTestList6Doc serialization

void CTestList6Doc::Serialize(CArchive& ar)
{
	if(ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTestList6Doc diagnostics

#ifdef _DEBUG
void CTestList6Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestList6Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestList6Doc commands
