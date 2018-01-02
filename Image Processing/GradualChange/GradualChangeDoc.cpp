// GradualChangeDoc.cpp : implementation of the CGradualChangeDoc class
// Download by http://www.codefans.net

#include "stdafx.h"
#include "GradualChange.h"

#include "GradualChangeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGradualChangeDoc

IMPLEMENT_DYNCREATE(CGradualChangeDoc, CDocument)

BEGIN_MESSAGE_MAP(CGradualChangeDoc, CDocument)
	//{{AFX_MSG_MAP(CGradualChangeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGradualChangeDoc construction/destruction

CGradualChangeDoc::CGradualChangeDoc()
{
	// TODO: add one-time construction code here

}

CGradualChangeDoc::~CGradualChangeDoc()
{
}

BOOL CGradualChangeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGradualChangeDoc serialization

void CGradualChangeDoc::Serialize(CArchive& ar)
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
// CGradualChangeDoc diagnostics

#ifdef _DEBUG
void CGradualChangeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGradualChangeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGradualChangeDoc commands
