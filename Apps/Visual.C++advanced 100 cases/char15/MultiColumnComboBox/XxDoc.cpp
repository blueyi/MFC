// XxDoc.cpp : implementation of the CXxDoc class
//

#include "stdafx.h"
#include "Xx.h"

#include "XxDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXxDoc

IMPLEMENT_DYNCREATE(CXxDoc, CDocument)

BEGIN_MESSAGE_MAP(CXxDoc, CDocument)
	//{{AFX_MSG_MAP(CXxDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXxDoc construction/destruction

CXxDoc::CXxDoc()
{
	// TODO: add one-time construction code here

}

CXxDoc::~CXxDoc()
{
}

BOOL CXxDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CXxDoc serialization

void CXxDoc::Serialize(CArchive& ar)
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
// CXxDoc diagnostics

#ifdef _DEBUG
void CXxDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CXxDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXxDoc commands
