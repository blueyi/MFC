// RTDemoDoc.cpp : implementation of the CRTDemoDoc class
//

#include "stdafx.h"
#include "RTDemo.h"

#include "RTDemoDoc.h"
#include "RTDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRTDemoDoc

IMPLEMENT_DYNCREATE(CRTDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CRTDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CRTDemoDoc)
	ON_COMMAND(ID_TYPE_GRID, OnTypeGrid)
	ON_UPDATE_COMMAND_UI(ID_TYPE_GRID, OnUpdateTypeGrid)
	ON_COMMAND(ID_TYPE_BOUNDARY, OnTypeBoundary)
	ON_UPDATE_COMMAND_UI(ID_TYPE_BOUNDARY, OnUpdateTypeBoundary)
	ON_COMMAND(ID_TYPE_BACKCOLOR, OnTypeBackcolor)
	ON_UPDATE_COMMAND_UI(ID_TYPE_BACKCOLOR, OnUpdateTypeBackcolor)
	ON_COMMAND(ID_TYPE_TITLE, OnTypeTitle)
	ON_UPDATE_COMMAND_UI(ID_TYPE_TITLE, OnUpdateTypeTitle)
	ON_COMMAND(ID_TYPE_MEMORYDRAW, OnTypeMemorydraw)
	ON_UPDATE_COMMAND_UI(ID_TYPE_MEMORYDRAW, OnUpdateTypeMemorydraw)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRTDemoDoc construction/destruction

CRTDemoDoc::CRTDemoDoc()
{
	m_bMemDraw	 = true;
	m_bTitle	 = true;
	m_bBoundary	 = false;
	m_bGrid		 = true;
	m_bVertical  = true;
	m_nBkColor   = RGB(255, 255, 255);

	pView		 = NULL;
}

CRTDemoDoc::~CRTDemoDoc()
{
}

BOOL CRTDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CRTDemoDoc serialization

void CRTDemoDoc::Serialize(CArchive& ar)
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
// CRTDemoDoc diagnostics

#ifdef _DEBUG
void CRTDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRTDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRTDemoDoc commands

void CRTDemoDoc::OnTypeGrid() 
{
	m_bGrid = !m_bGrid;
	pView->Redraw();
}

void CRTDemoDoc::OnUpdateTypeGrid(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bGrid);
}

void CRTDemoDoc::OnTypeBoundary() 
{
	m_bBoundary = !m_bBoundary;
	pView->Redraw();
}

void CRTDemoDoc::OnUpdateTypeBoundary(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bBoundary);
}

void CRTDemoDoc::OnTypeBackcolor() 
{
	CColorDialog cDlg(m_nBkColor, CC_FULLOPEN | CC_ANYCOLOR);
	if (cDlg.DoModal() == IDOK)
	{
		m_nBkColor = cDlg.GetColor();
		pView->Redraw();
	}
}

void CRTDemoDoc::OnUpdateTypeBackcolor(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CRTDemoDoc::OnTypeTitle() 
{
	m_bTitle = !m_bTitle;
	pView->Redraw();
}

void CRTDemoDoc::OnUpdateTypeTitle(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bTitle);
}

void CRTDemoDoc::OnTypeMemorydraw() 
{
	m_bMemDraw = !m_bMemDraw;
	pView->Redraw();
}

void CRTDemoDoc::OnUpdateTypeMemorydraw(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bMemDraw);
}
