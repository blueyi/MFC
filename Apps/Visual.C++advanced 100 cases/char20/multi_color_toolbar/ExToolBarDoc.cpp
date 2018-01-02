// ExToolBarDoc.cpp : implementation of the CExToolBarDoc class
//

#include "stdafx.h"
#include "ExToolBar.h"

#include "ExToolBarDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExToolBarDoc

IMPLEMENT_DYNCREATE(CExToolBarDoc, CDocument)

BEGIN_MESSAGE_MAP(CExToolBarDoc, CDocument)
	//{{AFX_MSG_MAP(CExToolBarDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CExToolBarDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CExToolBarDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IExToolBar to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {298735F5-FF1C-11D1-8A9F-000000000000}
static const IID IID_IExToolBar =
{ 0x298735f5, 0xff1c, 0x11d1, { 0x8a, 0x9f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } };

BEGIN_INTERFACE_MAP(CExToolBarDoc, CDocument)
	INTERFACE_PART(CExToolBarDoc, IID_IExToolBar, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExToolBarDoc construction/destruction

CExToolBarDoc::CExToolBarDoc()
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CExToolBarDoc::~CExToolBarDoc()
{
	AfxOleUnlockApp();
}

BOOL CExToolBarDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CExToolBarDoc serialization

void CExToolBarDoc::Serialize(CArchive& ar)
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
// CExToolBarDoc diagnostics

#ifdef _DEBUG
void CExToolBarDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CExToolBarDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExToolBarDoc commands
