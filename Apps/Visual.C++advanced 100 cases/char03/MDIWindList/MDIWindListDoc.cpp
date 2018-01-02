// MDIWindListDoc.cpp : implementation of the CMDIWindListDoc class
//

#include "stdafx.h"
#include "MDIWindList.h"

#include "MDIWindListDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMDIWindListDoc

IMPLEMENT_DYNCREATE(CMDIWindListDoc, CDocument)

BEGIN_MESSAGE_MAP(CMDIWindListDoc, CDocument)
	//{{AFX_MSG_MAP(CMDIWindListDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMDIWindListDoc construction/destruction

CMDIWindListDoc::CMDIWindListDoc()
{
	// TODO: add one-time construction code here

}

CMDIWindListDoc::~CMDIWindListDoc()
{
}

BOOL CMDIWindListDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMDIWindListDoc serialization

void CMDIWindListDoc::Serialize(CArchive& ar)
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
// CMDIWindListDoc diagnostics

#ifdef _DEBUG
void CMDIWindListDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMDIWindListDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMDIWindListDoc commands
