// OSDetectDoc.cpp : implementation of the COSDetectDoc class
//

#include "stdafx.h"
#include "OSDetect.h"

#include "OSDetectDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COSDetectDoc

IMPLEMENT_DYNCREATE(COSDetectDoc, CDocument)

BEGIN_MESSAGE_MAP(COSDetectDoc, CDocument)
	//{{AFX_MSG_MAP(COSDetectDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COSDetectDoc construction/destruction

COSDetectDoc::COSDetectDoc()
{
	// TODO: add one-time construction code here

}

COSDetectDoc::~COSDetectDoc()
{
}

BOOL COSDetectDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COSDetectDoc serialization

void COSDetectDoc::Serialize(CArchive& ar)
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
// COSDetectDoc diagnostics

#ifdef _DEBUG
void COSDetectDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COSDetectDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COSDetectDoc commands
