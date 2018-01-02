// BigSeeDoc.cpp : implementation of the CBigSeeDoc class
//

#include "stdafx.h"
#include "BigSee.h"

#include "BigSeeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBigSeeDoc

IMPLEMENT_DYNCREATE(CBigSeeDoc, CDocument)

BEGIN_MESSAGE_MAP(CBigSeeDoc, CDocument)
	//{{AFX_MSG_MAP(CBigSeeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBigSeeDoc construction/destruction

CBigSeeDoc::CBigSeeDoc()
{
	// TODO: add one-time construction code here

}

CBigSeeDoc::~CBigSeeDoc()
{
}

BOOL CBigSeeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBigSeeDoc serialization

void CBigSeeDoc::Serialize(CArchive& ar)
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
// CBigSeeDoc diagnostics

#ifdef _DEBUG
void CBigSeeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBigSeeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBigSeeDoc commands
