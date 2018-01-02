// CurveDrawingDoc.cpp : implementation of the CCurveDrawingDoc class
//

#include "stdafx.h"
#include "CurveDrawing.h"

#include "CurveDrawingDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurveDrawingDoc

IMPLEMENT_DYNCREATE(CCurveDrawingDoc, CDocument)

BEGIN_MESSAGE_MAP(CCurveDrawingDoc, CDocument)
	//{{AFX_MSG_MAP(CCurveDrawingDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurveDrawingDoc construction/destruction

CCurveDrawingDoc::CCurveDrawingDoc()
{
	// TODO: add one-time construction code here
//	str("guagua")
	li=1;
	ifdrawcurve=FALSE;
	
}

CCurveDrawingDoc::~CCurveDrawingDoc()
{
}

BOOL CCurveDrawingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCurveDrawingDoc serialization

void CCurveDrawingDoc::Serialize(CArchive& ar)
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
// CCurveDrawingDoc diagnostics

#ifdef _DEBUG
void CCurveDrawingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCurveDrawingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCurveDrawingDoc commands
