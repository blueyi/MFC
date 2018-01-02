// TextInStatusDoc.cpp : implementation of the CTextInStatusDoc class
//

#include "stdafx.h"
#include "TextInStatus.h"

#include "TextInStatusDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextInStatusDoc

IMPLEMENT_DYNCREATE(CTextInStatusDoc, CDocument)

BEGIN_MESSAGE_MAP(CTextInStatusDoc, CDocument)
	//{{AFX_MSG_MAP(CTextInStatusDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextInStatusDoc construction/destruction

CTextInStatusDoc::CTextInStatusDoc()
{
	// TODO: add one-time construction code here

}

CTextInStatusDoc::~CTextInStatusDoc()
{
}

BOOL CTextInStatusDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTextInStatusDoc serialization

void CTextInStatusDoc::Serialize(CArchive& ar)
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
// CTextInStatusDoc diagnostics

#ifdef _DEBUG
void CTextInStatusDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTextInStatusDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTextInStatusDoc commands
