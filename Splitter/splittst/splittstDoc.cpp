// splittstDoc.cpp : implementation of the CSplittstDoc class
//

#include "stdafx.h"
#include "splittst.h"

#include "splittstDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplittstDoc

IMPLEMENT_DYNCREATE(CSplittstDoc, CDocument)

BEGIN_MESSAGE_MAP(CSplittstDoc, CDocument)
	//{{AFX_MSG_MAP(CSplittstDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplittstDoc construction/destruction

CSplittstDoc::CSplittstDoc()
{
	// TODO: add one-time construction code here

}

CSplittstDoc::~CSplittstDoc()
{
}

BOOL CSplittstDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSplittstDoc serialization

void CSplittstDoc::Serialize(CArchive& ar)
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
// CSplittstDoc diagnostics

#ifdef _DEBUG
void CSplittstDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSplittstDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSplittstDoc commands
