// PropListDemoDoc.cpp : implementation of the CPropListDemoDoc class
//

#include "stdafx.h"
#include "PropListDemo.h"

#include "PropListDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropListDemoDoc

IMPLEMENT_DYNCREATE(CPropListDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CPropListDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CPropListDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropListDemoDoc construction/destruction

CPropListDemoDoc::CPropListDemoDoc()
{
	// TODO: add one-time construction code here

}

CPropListDemoDoc::~CPropListDemoDoc()
{
}

BOOL CPropListDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPropListDemoDoc serialization

void CPropListDemoDoc::Serialize(CArchive& ar)
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
// CPropListDemoDoc diagnostics

#ifdef _DEBUG
void CPropListDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPropListDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPropListDemoDoc commands
