// PGLPie.cpp: implementation of the CPGLMap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PGL/PGLPie.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CPGLPie, CPGLObject,1);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void CPGLPie::Serialize(CArchive &archive)
{
    // call base class function first
    // base class is CObject in this case
    CPGLObject::Serialize( archive );

    // now do the stuff for our specific class
    if( archive.IsStoring() )
	{
	}
    else
	{
	}
}

#ifdef _DEBUG
void CPGLPie::Dump( CDumpContext& dc ) const
{
    // call base class function first
    CPGLObject::Dump( dc );

    // now do the stuff for our specific class
	dc << _T("CPGLPie ID ") << GetID() << endl;
}
void CPGLPie::AssertValid() const
{
    // call inherited AssertValid first
    CPGLObject::AssertValid();

    // check members...
} 
#endif

CPGLPie::CPGLPie()
: CPGLObject()
{
}


CPGLPie::CPGLPie(const CPGLPie &r)
: CPGLObject(r)
{
}

CPGLPie& CPGLPie::operator = (const CPGLPie& l)
{
	// prevent self-assignement
	if (&l != this)
	{
		// invoke CPGLObject copy assignement operator
		this->CPGLObject::operator =(l);

		// copy the rest
	}
	return *this;
}

void CPGLPie::PlotGfx(gfxinterface::CGfxInterface& gfx)
{
	// calling base class plot
	CPGLObject::PlotGfx(gfx);
		
}

double* CPGLPie::GetExtent(CPGLView* pView)
{
	if (NeedUpdateExtent())
		UpdateExtent(pView);

	return CPGLObject::GetExtent(pView);
}

void CPGLPie::UpdateExtent(CPGLView* pView)
{
	// Calling base class function
	CPGLObject::UpdateExtent(pView);

	m_extent[0]=-1.0f;
	m_extent[1]= 1.0f;
	m_extent[2]=-1.0f;
	m_extent[3]= 1.0f;
}

#define PI 3.1415926535897f 
#define X .525731112119133606f 
#define Z .850650808352039932f

