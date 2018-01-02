// MSDITestDoc.cpp : implementation of the CMSDITestDoc class
//

#include "stdafx.h"
#include "MSDITest.h"

#include "MSDITestDoc.h"

#include "ELawyer.h"
#include "MSDITestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMSDITestDoc

IMPLEMENT_DYNCREATE(CMSDITestDoc, CDocument)

BEGIN_MESSAGE_MAP(CMSDITestDoc, CDocument)
	//{{AFX_MSG_MAP(CMSDITestDoc)
	ON_COMMAND(ID_WINDOW_CFORMVIEW, OnWindowCformview)
	ON_COMMAND(ID_WINDOW_CVIEW, OnWindowCview)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMSDITestDoc construction/destruction

CMSDITestDoc::CMSDITestDoc()
{
	// TODO: add one-time construction code here

}

CMSDITestDoc::~CMSDITestDoc()
{
}

BOOL CMSDITestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMSDITestDoc serialization

void CMSDITestDoc::Serialize(CArchive& ar)
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
// CMSDITestDoc diagnostics

#ifdef _DEBUG
void CMSDITestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMSDITestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMSDITestDoc commands

void CMSDITestDoc::OnWindowCformview() 
{
	theApp.CreateOrActivateFrame(RUNTIME_CLASS(CELawyer), this);
	
}

void CMSDITestDoc::OnWindowCview() 
{
	theApp.CreateOrActivateFrame(RUNTIME_CLASS(CMSDITestView), this);
	
}
