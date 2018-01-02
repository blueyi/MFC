// VGisDoc.cpp : implementation of the CVGisDoc class
//

#include "stdafx.h"
#include "VGis.h"

#include "VGisDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVGisDoc

IMPLEMENT_DYNCREATE(CVGisDoc, CDocument)

BEGIN_MESSAGE_MAP(CVGisDoc, CDocument)
	//{{AFX_MSG_MAP(CVGisDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVGisDoc construction/destruction

CVGisDoc::CVGisDoc()
{
	// TODO: add one-time construction code here

}

CVGisDoc::~CVGisDoc()
{
}

BOOL CVGisDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CVGisDoc serialization
extern CView  *g_pView;
void CVGisDoc::Serialize(CArchive& ar)
{
	g_pView->Serialize(ar);
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
// CVGisDoc diagnostics

#ifdef _DEBUG
void CVGisDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVGisDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVGisDoc commands
