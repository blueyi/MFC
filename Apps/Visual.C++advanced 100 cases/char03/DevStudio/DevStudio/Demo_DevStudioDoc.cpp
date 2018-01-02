// Demo_DevStudioDoc.cpp : implementation of the CDemo_DevStudioDoc class
//

#include "stdafx.h"
#include "Demo_DevStudio.h"

#include "Demo_DevStudioDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemo_DevStudioDoc

IMPLEMENT_DYNCREATE(CDemo_DevStudioDoc, CDocument)

BEGIN_MESSAGE_MAP(CDemo_DevStudioDoc, CDocument)
	//{{AFX_MSG_MAP(CDemo_DevStudioDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemo_DevStudioDoc construction/destruction

CDemo_DevStudioDoc::CDemo_DevStudioDoc()
{
	// TODO: add one-time construction code here

}

CDemo_DevStudioDoc::~CDemo_DevStudioDoc()
{
}

BOOL CDemo_DevStudioDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDemo_DevStudioDoc serialization

void CDemo_DevStudioDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CDemo_DevStudioDoc diagnostics

#ifdef _DEBUG
void CDemo_DevStudioDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDemo_DevStudioDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemo_DevStudioDoc commands
