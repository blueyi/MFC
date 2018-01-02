// StealthDoc.cpp : implementation of the CStealthDoc class
//

#include "stdafx.h"
#include "Stealth.h"

#include "StealthDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStealthDoc

IMPLEMENT_DYNCREATE(CStealthDoc, CDocument)

BEGIN_MESSAGE_MAP(CStealthDoc, CDocument)
	//{{AFX_MSG_MAP(CStealthDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStealthDoc construction/destruction

CStealthDoc::CStealthDoc()
{
	// TODO: add one-time construction code here

}

CStealthDoc::~CStealthDoc()
{
}

BOOL CStealthDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CStealthDoc serialization

void CStealthDoc::Serialize(CArchive& ar)
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
// CStealthDoc diagnostics

#ifdef _DEBUG
void CStealthDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStealthDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStealthDoc commands
