// SCBDemoDoc.cpp : implementation of the CSCBDemoDoc class
//

#include "stdafx.h"
#include "SCBDemo.h"

#include "SCBDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSCBDemoDoc

IMPLEMENT_DYNCREATE(CSCBDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CSCBDemoDoc, CDocument)
    //{{AFX_MSG_MAP(CSCBDemoDoc)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSCBDemoDoc construction/destruction

CSCBDemoDoc::CSCBDemoDoc()
{
    // TODO: add one-time construction code here

}

CSCBDemoDoc::~CSCBDemoDoc()
{
}

BOOL CSCBDemoDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    // TODO: add reinitialization code here
    // (SDI documents will reuse this document)

    return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSCBDemoDoc serialization

void CSCBDemoDoc::Serialize(CArchive& ar)
{
    // CEditView contains an edit control which handles all serialization
    ((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CSCBDemoDoc diagnostics

#ifdef _DEBUG
void CSCBDemoDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CSCBDemoDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSCBDemoDoc commands
