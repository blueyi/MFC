// DemoToolTipDoc.cpp : implementation of the CDemoToolTipDoc class
//

#include "stdafx.h"
#include "DemoToolTip.h"

#include "DemoToolTipDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoToolTipDoc

IMPLEMENT_DYNCREATE(CDemoToolTipDoc, CDocument)

BEGIN_MESSAGE_MAP(CDemoToolTipDoc, CDocument)
	//{{AFX_MSG_MAP(CDemoToolTipDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoToolTipDoc construction/destruction

CDemoToolTipDoc::CDemoToolTipDoc()
{
	// TODO: add one-time construction code here

}

CDemoToolTipDoc::~CDemoToolTipDoc()
{
}

BOOL CDemoToolTipDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDemoToolTipDoc serialization

void CDemoToolTipDoc::Serialize(CArchive& ar)
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
// CDemoToolTipDoc diagnostics

#ifdef _DEBUG
void CDemoToolTipDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDemoToolTipDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemoToolTipDoc commands
