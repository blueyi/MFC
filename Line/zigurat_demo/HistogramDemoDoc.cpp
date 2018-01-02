// HistogramDemoDoc.cpp : implementation of the CHistogramDemoDoc class
//

#include "stdafx.h"
#include "HistogramDemo.h"

#include "HistogramDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHistogramDemoDoc

IMPLEMENT_DYNCREATE(CHistogramDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CHistogramDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CHistogramDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHistogramDemoDoc construction/destruction

CHistogramDemoDoc::CHistogramDemoDoc()
{
	// TODO: add one-time construction code here

}

CHistogramDemoDoc::~CHistogramDemoDoc()
{
}

BOOL CHistogramDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CHistogramDemoDoc serialization

void CHistogramDemoDoc::Serialize(CArchive& ar)
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
// CHistogramDemoDoc diagnostics

#ifdef _DEBUG
void CHistogramDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHistogramDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHistogramDemoDoc commands
