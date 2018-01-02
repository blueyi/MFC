// HDDemoDoc.cpp : implementation of the CHDDemoDoc class
//

#include "stdafx.h"
#include "HDDemo.h"

#include "HDDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHDDemoDoc

IMPLEMENT_DYNCREATE(CHDDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CHDDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CHDDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHDDemoDoc construction/destruction

CHDDemoDoc::CHDDemoDoc()
{
	// TODO: add one-time construction code here

}

CHDDemoDoc::~CHDDemoDoc()
{
}

BOOL CHDDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CHDDemoDoc serialization

void CHDDemoDoc::Serialize(CArchive& ar)
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
// CHDDemoDoc diagnostics

#ifdef _DEBUG
void CHDDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHDDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHDDemoDoc commands
