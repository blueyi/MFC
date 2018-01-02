// PGLGraphDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PGL/pgl.h"
#include "PGL/PGLGraphDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPGLGraphDlg dialog
void CPGLGraphDlg::Serialize(CArchive &archive)
{
	ASSERT_VALID(m_pGraph);

	if (archive.IsStoring())
	{
		// the mouse stuff
		archive << m_iMouseMode;
	}
	else
	{
		// the mouse stuff
		archive >> m_iMouseMode;
		m_mouse=CPGLMouse();
	}

	// serializing the graph
	m_pGraph->Serialize(archive);

	// updating graph if loading...
	if (archive.IsLoading())
	{
		// updating viewport dimensions...
		CPGLView* pView=m_pGraph->GetView();
		// redimensionning window
		CRect rect;
		GetWindowRect(&rect);
		MoveWindow(rect.left,rect.top,pView->GetWidth(), pView->GetHeight());
		InvalidateRect(NULL,FALSE);
	}
}


CPGLGraphDlg::CPGLGraphDlg(CWnd* pParent /*=NULL*/, CPGLGraph* _pGraph)
	: CDialog(CPGLGraphDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPGLGraphDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pGraph=_pGraph;
	m_iMouseMode=PGL_MODE_TOOLS_SELECTION;
}


CPGLGraphDlg::~CPGLGraphDlg()
{
    if (m_pGraph)
		delete m_pGraph;
}

void CPGLGraphDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPGLGraphDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPGLGraphDlg, CDialog)
	//{{AFX_MSG_MAP(CPGLGraphDlg)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPGLGraphDlg message handlers

void CPGLGraphDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	if (m_pGraph)
		m_pGraph->Delete();
	
}
