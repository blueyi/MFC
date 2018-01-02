// PGLLineVer.cpp: implementation of the CPGLLineVer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PGL/pgl.h"
#include "PGL/PGLLineVer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



IMPLEMENT_SERIAL(CPGLLineVer, CPGLLine,1);

void CPGLLineVer::Serialize(CArchive &archive)
{
    // call base class function first
    // base class is CObject in this case
    CPGLLine::Serialize( archive );

    // now do the stuff for our specific class
    if( archive.IsStoring() )
	{
		archive>>m_dX;
	}
    else
	{
		archive>>m_dX;
	}
}

#ifdef _DEBUG
void CPGLLineVer::Dump( CDumpContext& dc ) const
{
    // call base class function first
    CPGLLine::Dump( dc );
}
void CPGLLineVer::AssertValid() const
{
    // call inherited AssertValid first
    CPGLLine::AssertValid();

} 
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPGLLineVer::CPGLLineVer()
: CPGLLine()
{
	m_dX = 0;
	m_tCaption.SetAngle(90);
}

CPGLLineVer::CPGLLineVer(const CPGLLineVer& lv)
: CPGLLine(lv)
{
	m_dX = lv.m_dX;
	m_tCaption = lv.m_tCaption;
}

CPGLLineVer& CPGLLineVer::operator =(const CPGLLineVer& lv)
{
	if (this != &lv)
	{
		this->CPGLLineVer::operator =(lv);
		m_dX = lv.m_dX;
	}
	return *this;
}

CPGLLineVer::~CPGLLineVer()
{
}

double* CPGLLineVer::GetExtent(CPGLView* pView)
{
	if (NeedUpdateExtent())
		UpdateExtent(pView);

	return CPGLLine::GetExtent(pView);
}

void CPGLLineVer::UpdateExtent(CPGLView* pView)
{
	// Calling base class function
	CPGLLine::UpdateExtent(pView);

	m_extent[0]=m_extent[1]=m_dX;
	m_extent[2]=m_extent[3]=0;
}


void CPGLLineVer::PlotGfx(gfxinterface::CGfxInterface& gfx)
{
	if (!IsVisible())
		return;

	// calling base class plot
	CPGLObject::PlotGfx(gfx);
	
	gfx.AddComment("--- CPGLLineVer ---");	

	// Sets dash...
	SetDashGfx(gfx);	
	// set line width
	gfx.SetLineWidth(GetLineWidth());	
	gfx.DrawLine(m_dX, gfx.GetWorldBottom(), m_dX, gfx.GetWorldTop());

	// setting caption position
	float pos[2];
	pos[0]=m_dX+gfx.BBToWorldAbsx(GetLineWidth()+5);
	pos[1]=gfx.GetWorldClipTop();
	pos[1]+=gfx.BBToWorldAbsy(5);
	m_tCaption.SetPosition(pos);
	m_tCaption.PlotGfx(gfx);
}