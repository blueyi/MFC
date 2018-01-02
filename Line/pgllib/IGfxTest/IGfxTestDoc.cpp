// IGfxTestDoc.cpp : implementation of the CIGfxTestDoc class
//

#include "stdafx.h"
#include "IGfxTest.h"

#include "IGfxTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIGfxTestDoc

IMPLEMENT_DYNCREATE(CIGfxTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CIGfxTestDoc, CDocument)
	//{{AFX_MSG_MAP(CIGfxTestDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CIGfxTestDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CIGfxTestDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IIGfxTest to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {B4F0F0E1-F5FF-42B8-B0C4-95A0A72161D4}
static const IID IID_IIGfxTest =
{ 0xb4f0f0e1, 0xf5ff, 0x42b8, { 0xb0, 0xc4, 0x95, 0xa0, 0xa7, 0x21, 0x61, 0xd4 } };

BEGIN_INTERFACE_MAP(CIGfxTestDoc, CDocument)
	INTERFACE_PART(CIGfxTestDoc, IID_IIGfxTest, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIGfxTestDoc construction/destruction

CIGfxTestDoc::CIGfxTestDoc()
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CIGfxTestDoc::~CIGfxTestDoc()
{
	AfxOleUnlockApp();
}

BOOL CIGfxTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CIGfxTestDoc serialization

void CIGfxTestDoc::Serialize(CArchive& ar)
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
// CIGfxTestDoc diagnostics

#ifdef _DEBUG
void CIGfxTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CIGfxTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIGfxTestDoc commands
