// MriLogAnalyserDoc.cpp : implementation of the CMriLogAnalyserDoc class
//

#include "stdafx.h"
#include "MriLogAnalyser.h"

#include "MriLogAnalyserDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMriLogAnalyserDoc

IMPLEMENT_DYNCREATE(CMriLogAnalyserDoc, CDocument)

BEGIN_MESSAGE_MAP(CMriLogAnalyserDoc, CDocument)
	//{{AFX_MSG_MAP(CMriLogAnalyserDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMriLogAnalyserDoc construction/destruction

CMriLogAnalyserDoc::CMriLogAnalyserDoc()
{
	// TODO: add one-time construction code here

}

CMriLogAnalyserDoc::~CMriLogAnalyserDoc()
{
}

BOOL CMriLogAnalyserDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMriLogAnalyserDoc serialization

void CMriLogAnalyserDoc::Serialize(CArchive& ar)
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
// CMriLogAnalyserDoc diagnostics

#ifdef _DEBUG
void CMriLogAnalyserDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMriLogAnalyserDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMriLogAnalyserDoc commands
