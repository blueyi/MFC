// TestMyCanEditListDoc.cpp : implementation of the CTestMyCanEditListDoc class
//

#include "stdafx.h"
#include "TestMyCanEditList.h"

#include "TestMyCanEditListDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestMyCanEditListDoc

IMPLEMENT_DYNCREATE(CTestMyCanEditListDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestMyCanEditListDoc, CDocument)
	//{{AFX_MSG_MAP(CTestMyCanEditListDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestMyCanEditListDoc construction/destruction

CTestMyCanEditListDoc::CTestMyCanEditListDoc()
{
	// TODO: add one-time construction code here

}

CTestMyCanEditListDoc::~CTestMyCanEditListDoc()
{
}

BOOL CTestMyCanEditListDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTestMyCanEditListDoc serialization

void CTestMyCanEditListDoc::Serialize(CArchive& ar)
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
// CTestMyCanEditListDoc diagnostics

#ifdef _DEBUG
void CTestMyCanEditListDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestMyCanEditListDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestMyCanEditListDoc commands
