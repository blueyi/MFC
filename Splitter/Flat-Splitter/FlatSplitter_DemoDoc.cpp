// FlatSplitter_DemoDoc.cpp : implementation of the CFlatSplitter_DemoDoc class
//

#include "stdafx.h"
#include "FlatSplitter_Demo.h"

#include "FlatSplitter_DemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlatSplitter_DemoDoc

IMPLEMENT_DYNCREATE(CFlatSplitter_DemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CFlatSplitter_DemoDoc, CDocument)
	//{{AFX_MSG_MAP(CFlatSplitter_DemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlatSplitter_DemoDoc construction/destruction

CFlatSplitter_DemoDoc::CFlatSplitter_DemoDoc()
{
	// TODO: add one-time construction code here

}

CFlatSplitter_DemoDoc::~CFlatSplitter_DemoDoc()
{
}

BOOL CFlatSplitter_DemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFlatSplitter_DemoDoc serialization

void CFlatSplitter_DemoDoc::Serialize(CArchive& ar)
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
// CFlatSplitter_DemoDoc diagnostics

#ifdef _DEBUG
void CFlatSplitter_DemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFlatSplitter_DemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFlatSplitter_DemoDoc commands
