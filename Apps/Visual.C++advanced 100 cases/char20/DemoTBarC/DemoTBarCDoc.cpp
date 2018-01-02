// DemoTBarCDoc.cpp : implementation of the CDemoTBarCDoc class
//

#include "stdafx.h"
#include "DemoTBarC.h"

#include "DemoTBarCDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoTBarCDoc

IMPLEMENT_DYNCREATE(CDemoTBarCDoc, CDocument)

BEGIN_MESSAGE_MAP(CDemoTBarCDoc, CDocument)
	//{{AFX_MSG_MAP(CDemoTBarCDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoTBarCDoc construction/destruction

CDemoTBarCDoc::CDemoTBarCDoc()
{
	// TODO: add one-time construction code here

}

CDemoTBarCDoc::~CDemoTBarCDoc()
{
}

BOOL CDemoTBarCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDemoTBarCDoc serialization

void CDemoTBarCDoc::Serialize(CArchive& ar)
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
// CDemoTBarCDoc diagnostics

#ifdef _DEBUG
void CDemoTBarCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDemoTBarCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemoTBarCDoc commands
