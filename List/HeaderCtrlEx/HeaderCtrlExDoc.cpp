// HeaderCtrlExDoc.cpp : implementation of the CHeaderCtrlExDoc class
//

#include "stdafx.h"
#include "HeaderCtrlEx.h"

#include "HeaderCtrlExDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlExDoc

IMPLEMENT_DYNCREATE(CHeaderCtrlExDoc, CDocument)

BEGIN_MESSAGE_MAP(CHeaderCtrlExDoc, CDocument)
	//{{AFX_MSG_MAP(CHeaderCtrlExDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlExDoc construction/destruction

CHeaderCtrlExDoc::CHeaderCtrlExDoc()
{
	// TODO: add one-time construction code here

}

CHeaderCtrlExDoc::~CHeaderCtrlExDoc()
{
}

BOOL CHeaderCtrlExDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlExDoc serialization

void CHeaderCtrlExDoc::Serialize(CArchive& ar)
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
// CHeaderCtrlExDoc diagnostics

#ifdef _DEBUG
void CHeaderCtrlExDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHeaderCtrlExDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlExDoc commands
