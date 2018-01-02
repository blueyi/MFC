// demo_ui_explorerDoc.cpp : implementation of the CDemo_ui_explorerDoc class
//

#include "stdafx.h"
#include "demo_ui_explorer.h"

#include "demo_ui_explorerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemo_ui_explorerDoc

IMPLEMENT_DYNCREATE(CDemo_ui_explorerDoc, CDocument)

BEGIN_MESSAGE_MAP(CDemo_ui_explorerDoc, CDocument)
	//{{AFX_MSG_MAP(CDemo_ui_explorerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemo_ui_explorerDoc construction/destruction

CDemo_ui_explorerDoc::CDemo_ui_explorerDoc()
{
	// TODO: add one-time construction code here

}

CDemo_ui_explorerDoc::~CDemo_ui_explorerDoc()
{
}

BOOL CDemo_ui_explorerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDemo_ui_explorerDoc serialization

void CDemo_ui_explorerDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CDemo_ui_explorerDoc diagnostics

#ifdef _DEBUG
void CDemo_ui_explorerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDemo_ui_explorerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemo_ui_explorerDoc commands
