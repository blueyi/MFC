// MyInterfaceDoc.cpp : implementation of the CMyInterfaceDoc class
//

#include "stdafx.h"
#include "MyInterface.h"

#include "MyInterfaceDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyInterfaceDoc

IMPLEMENT_DYNCREATE(CMyInterfaceDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyInterfaceDoc, CDocument)
	//{{AFX_MSG_MAP(CMyInterfaceDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyInterfaceDoc construction/destruction

CMyInterfaceDoc::CMyInterfaceDoc()
{
	// TODO: add one-time construction code here

}

CMyInterfaceDoc::~CMyInterfaceDoc()
{
}

BOOL CMyInterfaceDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyInterfaceDoc serialization

void CMyInterfaceDoc::Serialize(CArchive& ar)
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
// CMyInterfaceDoc diagnostics

#ifdef _DEBUG
void CMyInterfaceDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyInterfaceDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyInterfaceDoc commands
