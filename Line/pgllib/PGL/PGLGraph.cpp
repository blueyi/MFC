// GraphGL.cpp: implementation of the CPGLColor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PGL/PGLGraph.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
	
IMPLEMENT_SERIAL(CPGLGraph,CPGLRegion,1);

CPGLObjectManager* CPGLGraph::sm_mClipboard=NULL;

void CPGLGraph::Serialize(CArchive &archive)
{
    // call base class function first
    // base class is CPGLObject in this case
    CPGLRegion::Serialize( archive );

	m_axe.Serialize(archive);
	m_mObjects.Serialize(archive);

	if (archive.IsLoading())
	{
		// setting view...
		m_axe.SetView(&m_view);
		// calling updating graph
		PostUpdateGraph();
	}
}

#ifdef _DEBUG
void CPGLGraph::Dump( CDumpContext& dc ) const
{
    // call base class function first
    CPGLRegion::Dump( dc );

    // now do the stuff for our specific class
	// now dumping..
	dc << _T("--- CPGLGraph ---\n")<< endl;
    dc << m_background<<m_view<<m_axe<<m_mObjects<<"\n";
}
void CPGLGraph::AssertValid() const
{
    // call inherited AssertValid first
    CPGLRegion::AssertValid();

} 
#endif

CPGLGraph::CPGLGraph()
{
	m_view.SetViewport(0,0,1,1);
}

CPGLGraph::CPGLGraph(const CPGLGraph& g)
: CPGLRegion(g)
{	
	LoadBitmap(IDB_PGL_GRAPH_BITMAP);
}

CPGLGraph& CPGLGraph::operator =(const CPGLGraph& g)
{
	if (&g!=this)
	{
		this->CPGLRegion::operator =(g);
	
	}
	return *this;
}

CPGLGraph::~CPGLGraph()
{
}


/// adds context menu items...
void CPGLGraph::AddContextMenuItems(CMenu* pMenu)
{
/*	//filling menu items...
	// check selection state
	CString str;

	if (IsSelectionEmpty())
	{
		pMenu->AppendMenu(MF_GRAYED | MF_STRING, ID_PGL_EDIT_CUT, "Cut");
		pMenu->AppendMenu(MF_GRAYED | MF_STRING, ID_PGL_EDIT_COPY, "Copy");
	}
	else
	{
		pMenu->AppendMenu(MF_ENABLED | MF_STRING, ID_PGL_EDIT_CUT, "Cut");
		pMenu->AppendMenu(MF_ENABLED | MF_STRING, ID_PGL_EDIT_COPY, "Copy");
	}

	// check clipboard state
	if (IsClipBoardEmpty())
	{
		pMenu->AppendMenu(MF_GRAYED | MF_STRING, ID_PGL_EDIT_PASTE, "Paste");
	}
	else
	{
		pMenu->AppendMenu(MF_ENABLED | MF_STRING, ID_PGL_EDIT_PASTE, "Paste");
	}

	pMenu->AppendMenu(MF_SEPARATOR);

	if (IsSelectionEmpty())
		pMenu->AppendMenu(MF_GRAYED | MF_STRING, ID_PGL_EDIT_DELETE, "Delete");
	else
		pMenu->AppendMenu(MF_ENABLED | MF_STRING, ID_PGL_EDIT_DELETE, "Delete");
*/
}

//DEL void CPGLGraph::Plot(BOOL renderToSelect)
//DEL {
//DEL 	// set clearing color...
//DEL 	MakeBackgroundCurrent();
//DEL 	//clear buffer
//DEL 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//DEL 	PGL_TRACE("PGL-Graph: Plot : GL buffer cleared\n");
//DEL 
//DEL 	CPGLRegion::Plot(renderToSelect);
//DEL };


void CPGLGraph::PlotGfx(gfxinterface::CGfxInterface& gfx)
{
	// defining some operator...
	gfx.PushState();
	CPGLRegion::PlotGfx(gfx);
	gfx.PopState();
}



void CPGLGraph::FormatSelectedText()
{
	// check if single or multiple selection
	// and choose new text format...
/*	CPGLFont* pFont=m_mFonts.ChooseFontFromDialog();

	if (pFont!=NULL)
	{
		// set font to selected text objects...
		CPGLObject* pObject;
		CPGLObjectManager* pTextSelection=m_mObjects.GetTextSelection();
		POSITION pos=pTextSelection->GetHeadPosition();
		while (pos!=NULL)
		{
			pObject=pTextSelection->GetNext(pos);
			ASSERT( pObject->IsKindOf(RUNTIME_CLASS(CPGLText)));
			m_mFonts.ChangeFont((CPGLText*)pObject, pFont->GetID());
		}

		// cleaning
		delete pTextSelection;
	}
*/
}

