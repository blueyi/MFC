// DBBTestDoc.cpp : implementation of the CDBBTestDoc class
// Download by http://www.codefans.net

#include "stdafx.h"
#include "DBBTest.h"

#include "DBBTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBBTestDoc

IMPLEMENT_DYNCREATE(CDBBTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CDBBTestDoc, CDocument)
	//{{AFX_MSG_MAP(CDBBTestDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBBTestDoc construction/destruction

CDBBTestDoc::CDBBTestDoc()
{
	// TODO: add one-time construction code here

}

CDBBTestDoc::~CDBBTestDoc()
{
}

BOOL CDBBTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDBBTestDoc serialization

void CDBBTestDoc::Serialize(CArchive& ar)
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
// CDBBTestDoc diagnostics

#ifdef _DEBUG
void CDBBTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDBBTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDBBTestDoc commands
