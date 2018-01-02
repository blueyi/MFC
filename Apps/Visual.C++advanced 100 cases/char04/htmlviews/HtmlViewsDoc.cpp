// HtmlViewsDoc.cpp : implementation of the CHtmlViewsDoc class
//

#include "stdafx.h"
#include "HtmlViews.h"

#include "HtmlViewsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHtmlViewsDoc

IMPLEMENT_DYNCREATE(CHtmlViewsDoc, CDocument)

BEGIN_MESSAGE_MAP(CHtmlViewsDoc, CDocument)
	//{{AFX_MSG_MAP(CHtmlViewsDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHtmlViewsDoc construction/destruction

CHtmlViewsDoc::CHtmlViewsDoc()
{
	// TODO: add one-time construction code here

}

CHtmlViewsDoc::~CHtmlViewsDoc()
{
}

BOOL CHtmlViewsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CHtmlViewsDoc serialization

void CHtmlViewsDoc::Serialize(CArchive& ar)
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
// CHtmlViewsDoc diagnostics

#ifdef _DEBUG
void CHtmlViewsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHtmlViewsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHtmlViewsDoc commands
