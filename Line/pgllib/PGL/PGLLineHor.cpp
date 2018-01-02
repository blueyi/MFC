// PGLLineHor.cpp: implementation of the CPGLLineHor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PGL/pgl.h"
#include "PGL/PGLLineHor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


IMPLEMENT_SERIAL(CPGLLineHor, CPGLLine,1);

void CPGLLineHor::Serialize(CArchive &archive)
{
    // call base class function first
    // base class is CObject in this case
    CPGLLine::Serialize( archive );

    // now do the stuff for our specific class
    if( archive.IsStoring() )
	{
		archive>>m_dY;
	}
    else
	{
		archive>>m_dY;
	}
}

#ifdef _DEBUG
void CPGLLineHor::Dump( CDumpContext& dc ) const
{
    // call base class function first
    CPGLLine::Dump( dc );
}
void CPGLLineHor::AssertValid() const
{
    // call inherited AssertValid first
    CPGLLine::AssertValid();

} 
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPGLLineHor::CPGLLineHor()
: CPGLLine()
{
	m_dY = 0;
	m_tCaption.SetColor(0,0,0);
}

CPGLLineHor::CPGLLineHor(const CPGLLineHor& lv)
: CPGLLine(lv)
{
	m_dY = lv.m_dY;
	m_tCaption = lv.m_tCaption;
}

CPGLLineHor& CPGLLineHor::operator =(const CPGLLineHor& lv)
{
	if (this != &lv)
	{
		this->CPGLLineHor::operator =(lv);
		m_dY = lv.m_dY;
		m_tCaption = lv.m_tCaption;
	}
	return *this;
}

CPGLLineHor::~CPGLLineHor()
{
}

double* CPGLLineHor::GetExtent(CPGLView* pView)
{
	if (NeedUpdateExtent())
		UpdateExtent(pView);

	return CPGLLine::GetExtent(pView);
}

void CPGLLineHor::UpdateExtent(CPGLView* pView)
{
	// Calling base class function
	CPGLLine::UpdateExtent(pView);

	m_extent[0]=m_extent[1]=m_dY;
	m_extent[2]=m_extent[3]=0;
}



void CPGLLineHor::PlotGfx(gfxinterface::CGfxInterface& gfx)
{
	if (!IsVisible())
		return;

	// calling base class plot
	CPGLObject::PlotGfx(gfx);
	
	gfx.AddComment("--- CPGLLineHor ---");	
	SetDashGfx(gfx);	
	// set line width
	gfx.SetLineWidth(GetLineWidth());	
	gfx.DrawLine(gfx.GetWorldLeft(), m_dY, gfx.GetWorldRight(), m_dY);

	// setting caption position
	float pos[2];

	pos[0]=gfx.GetWorldClipLeft()+gfx.BBToWorldAbsx(5);
	pos[1]=m_dY+gfx.BBToWorldAbsy(GetLineWidth()+5);
	m_tCaption.SetPosition(pos);
	m_tCaption.PlotGfx(gfx);
}