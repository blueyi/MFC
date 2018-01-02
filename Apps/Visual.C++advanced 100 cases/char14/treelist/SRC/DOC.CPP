// Doc.cpp : implementation of the CTreeListDoc class
//

#include "stdafx.h"
#include "TreeList.h"
#include "MainFrm.h"

#include "Doc.h"
#include "ViewList.h"
#include "ViewTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeListDoc

IMPLEMENT_DYNCREATE(CTreeListDoc, CDocument)

BEGIN_MESSAGE_MAP(CTreeListDoc, CDocument)
	//{{AFX_MSG_MAP(CTreeListDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeListDoc construction/destruction

CTreeListDoc::CTreeListDoc()
{
}

CTreeListDoc::~CTreeListDoc()
{
}

BOOL CTreeListDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CTreeListDoc serialization

void CTreeListDoc::Serialize(CArchive& ar)
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
// CTreeListDoc diagnostics

#ifdef _DEBUG
void CTreeListDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTreeListDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTreeListDoc commands

/////////////////////////////////////////////////////////////////////////////

