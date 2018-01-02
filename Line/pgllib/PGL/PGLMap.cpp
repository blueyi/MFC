// PGLMap.cpp: implementation of the CPGLMap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PGL/PGLMap.h"

#include "PGL/PGLMapPropPage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CPGLMap, CPGLObject,1);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void CPGLMap::Serialize(CArchive &archive)
{
    // call base class function first
    // base class is CObject in this case
    CPGLObject::Serialize( archive );

    // now do the stuff for our specific class
    if( archive.IsStoring() )
	{
        archive << m_iNx
				<< m_iNy
				<< m_dDx
				<< m_dDy
				<< m_dX0
				<< m_dY0;
	}
    else
	{
        archive << m_iNx
				<< m_iNy
				<< m_dDx
				<< m_dDy
				<< m_dX0
				<< m_dY0;
	}
}

#ifdef _DEBUG
void CPGLMap::Dump( CDumpContext& dc ) const
{
    // call base class function first
    CPGLObject::Dump( dc );

    // now do the stuff for our specific class
	dc << _T("CPGLMap ID ") << GetID() << endl;
	dc	<< " nx : "<< m_iNx
		<< " ny : "<< m_iNy
		<< " dx : "<< m_dDx
		<< " dy : "<< m_dDy
		<< " x0 : "<< m_dX0
		<< " y0 : "<< m_dY0<<"/n";
}
void CPGLMap::AssertValid() const
{
    // call inherited AssertValid first
    CPGLObject::AssertValid();

    // check members...
	ASSERT(m_iNx>=0);
	ASSERT(m_iNy>=0);
} 
#endif

CPGLMap::CPGLMap()
: CPGLObject()
{
	m_iNx=0;
	m_iNy=0;
	m_dDx=m_dDy=1;
	m_dX0=0;
	m_dY0=0;
}


CPGLMap::CPGLMap(const CPGLMap &l)
: CPGLObject(l)
{
	m_iNx=l.m_iNx;
	m_iNy=l.m_iNy;
	m_dDx=l.m_dDx;
	m_dDy=l.m_dDy;
	m_dX0=l.m_dX0;
	m_dY0=l.m_dY0;
}

CPGLMap& CPGLMap::operator = (const CPGLMap& l)
{
	// prevent self-assignement
	if (&l != this)
	{
		// invoke CPGLObject copy assignement operator
		this->CPGLObject::operator =(l);

		// copy the rest
		m_iNx=l.m_iNx;
		m_iNy=l.m_iNy;
		m_dDx=l.m_dDx;
		m_dDy=l.m_dDy;
		m_dX0=l.m_dX0;
		m_dY0=l.m_dY0;

	}
	return *this;
}

void CPGLMap::SetDx(double _dDx)
{
	if  ( _dDx > PGL_EPS)
	{
		m_dDx = _dDx;
		PostUpdateExtent();
	}
}

void CPGLMap::SetDy(double _dDy)
{
	if  ( _dDy > PGL_EPS)
	{
		m_dDy = _dDy;
		PostUpdateExtent();
	}
}

void CPGLMap::AddContextMenuItems(CMenu* pMenu)
{
	// call base class
	CPGLObject::AddContextMenuItems(pMenu);

	// add own items
	
}

void CPGLMap::AddPropertyPage(CPropertySheet *pPropSheet)
{
	// call own functions
	CPGLMapPropPage* propPage=new CPGLMapPropPage(this);
	pPropSheet->AddPage(propPage);

	// first call base class function
	CPGLObject::AddPropertyPage(pPropSheet);
}

void CPGLMap::PlotGfx(gfxinterface::CGfxInterface& gfx)
{
	// calling base class plot
	CPGLObject::PlotGfx(gfx);
	
	gfx.AddComment("--- CPGLMap ID ---");
}

void CPGLMap::SetGrid(int iaxe, int iNPoints, double pos0, double step)
{
	ASSERT(iNPoints>=0);

	switch(iaxe)
	{
	case 0:
		m_iNx=iNPoints;
		m_dDx=step;
		m_dX0=pos0;
		break;
	case 1:
		m_iNy=iNPoints;
		m_dDy=step;
		m_dY0=pos0;
		break;
	}

	PostUpdateExtent();
}

double* CPGLMap::GetExtent(CPGLView* pView)
{
	if (NeedUpdateExtent())
		UpdateExtent(pView);

	return CPGLObject::GetExtent(pView);
}

void CPGLMap::UpdateExtent(CPGLView* pView)
{
	// Calling base class function
	CPGLObject::UpdateExtent(pView);

	m_extent[0]=m_dX0;
	m_extent[1]=m_dX0+(m_iNx-1)*m_dDx;
	m_extent[2]=m_dY0;
	m_extent[3]=m_dY0+(m_iNy-1)*m_dDy;
}
