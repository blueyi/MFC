// testpglDoc.cpp : implementation of the CTestpglDoc class
//

#include "stdafx.h"
#include "testpgl.h"

#include "testpglDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestpglDoc

IMPLEMENT_DYNCREATE(CTestpglDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestpglDoc, CDocument)
	//{{AFX_MSG_MAP(CTestpglDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestpglDoc construction/destruction

CTestpglDoc::CTestpglDoc()
{
	// TODO: add one-time construction code here

}

CTestpglDoc::~CTestpglDoc()
{
}

BOOL CTestpglDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTestpglDoc serialization

void CTestpglDoc::Serialize(CArchive& ar)
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
// CTestpglDoc diagnostics

#ifdef _DEBUG
void CTestpglDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestpglDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestpglDoc commands
