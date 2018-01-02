// TestPageDoc.cpp : implementation of the CTestPageDoc class
//

#include "stdafx.h"
#include "TestPage.h"

#include "TestPageDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestPageDoc

IMPLEMENT_DYNCREATE(CTestPageDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestPageDoc, CDocument)
	//{{AFX_MSG_MAP(CTestPageDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestPageDoc construction/destruction

CTestPageDoc::CTestPageDoc()
{
	// TODO: add one-time construction code here

}

CTestPageDoc::~CTestPageDoc()
{
}

BOOL CTestPageDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTestPageDoc serialization

void CTestPageDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTestPageDoc diagnostics

#ifdef _DEBUG
void CTestPageDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestPageDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestPageDoc commands
