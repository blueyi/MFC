// Demo_OutlookDoc.cpp : implementation of the CDemo_OutlookDoc class
//

#include "stdafx.h"
#include "Demo_Outlook.h"

#include "Demo_OutlookDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemo_OutlookDoc

IMPLEMENT_DYNCREATE(CDemo_OutlookDoc, CDocument)

BEGIN_MESSAGE_MAP(CDemo_OutlookDoc, CDocument)
	//{{AFX_MSG_MAP(CDemo_OutlookDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemo_OutlookDoc construction/destruction

CDemo_OutlookDoc::CDemo_OutlookDoc()
{
	// TODO: add one-time construction code here

}

CDemo_OutlookDoc::~CDemo_OutlookDoc()
{
}

BOOL CDemo_OutlookDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDemo_OutlookDoc serialization

void CDemo_OutlookDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CDemo_OutlookDoc diagnostics

#ifdef _DEBUG
void CDemo_OutlookDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDemo_OutlookDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemo_OutlookDoc commands
