// SliderClrDemoDoc.cpp : implementation of the CSliderClrDemoDoc class
//

#include "stdafx.h"
#include "SliderClrDemo.h"

#include "SliderClrDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSliderClrDemoDoc

IMPLEMENT_DYNCREATE(CSliderClrDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CSliderClrDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CSliderClrDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSliderClrDemoDoc construction/destruction

CSliderClrDemoDoc::CSliderClrDemoDoc()
{
	// TODO: add one-time construction code here

}

CSliderClrDemoDoc::~CSliderClrDemoDoc()
{
}

BOOL CSliderClrDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSliderClrDemoDoc serialization

void CSliderClrDemoDoc::Serialize(CArchive& ar)
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
// CSliderClrDemoDoc diagnostics

#ifdef _DEBUG
void CSliderClrDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSliderClrDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSliderClrDemoDoc commands
