// sdiDoc.cpp : implementation of the CSdiDoc class
//

#include "stdafx.h"
#include "sdi.h"

#include "sdiDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSdiDoc

IMPLEMENT_DYNCREATE(CSdiDoc, CDocument)

BEGIN_MESSAGE_MAP(CSdiDoc, CDocument)
	//{{AFX_MSG_MAP(CSdiDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSdiDoc construction/destruction

CSdiDoc::CSdiDoc()
{
	// TODO: add one-time construction code here
	m_chart.SetBorderColor( PIECOLOR_RED );
	m_chart.SetTextColor( PIECOLOR_GRAY );
	m_chart.SetAutoDelete( TRUE );
	m_chart.SetTitle( _T("IT outsourcing (2003)") );

	CPieSlice* sl = new CPieSlice();
	sl->SetColor( PIECOLOR_BLUE );
	sl->SetDescription( _T("India") );
	sl->SetPercentage( 82 );
	m_chart.AddSlice( *sl );

	sl = new CPieSlice();
	sl->SetColor( PIECOLOR_GREEN );
	sl->SetDescription( _T("USA") );
	sl->SetPercentage( 6 );
	m_chart.AddSlice( *sl );

	sl = new CPieSlice();
	sl->SetColor( PIECOLOR_YELLOW );
	sl->SetDescription( _T("Germany") );
	sl->SetPercentage( 3 );
	m_chart.AddSlice( *sl );

	sl = new CPieSlice();
	sl->SetColor( PIECOLOR_RED );
	sl->SetDescription( _T("Great Britain") );
	sl->SetPercentage( 2 );
	m_chart.AddSlice( *sl );

	sl = new CPieSlice();
	sl->SetColor( PIECOLOR_WHITE );
	sl->SetDescription( _T("China") );
	sl->SetPercentage( 2 );
	m_chart.AddSlice( *sl );

	sl = new CPieSlice();;
	sl->SetColor( PIECOLOR_PURPLE );
	sl->SetDescription( _T("Mexico") );
	sl->SetPercentage( 2 );
	m_chart.AddSlice( *sl );

	sl = new CPieSlice();
	sl->SetColor( PIECOLOR_CYAN );
	sl->SetDescription( _T("South America") );
	sl->SetPercentage( 2 );
	m_chart.AddSlice( *sl );

	sl = new CPieSlice();
	sl->SetColor( PIECOLOR_GRAY );
	sl->SetDescription( _T("Africa") );
	sl->SetPercentage( 1 );
	m_chart.AddSlice( *sl );
}

CSdiDoc::~CSdiDoc()
{
}

BOOL CSdiDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSdiDoc serialization

void CSdiDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	m_chart.Serialize( ar );
}

/////////////////////////////////////////////////////////////////////////////
// CSdiDoc diagnostics

#ifdef _DEBUG
void CSdiDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSdiDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSdiDoc commands
