// LineGL.cpp: implementation of the CPGLLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PGL/PGLLine.h"
#include "PGL/PGLLinePropPage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CPGLLine, CPGLObject,1);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void CPGLLine::Serialize(CArchive &archive)
{
    // call base class function first
    // base class is CObject in this case
    CPGLObject::Serialize( archive );

    // now do the stuff for our specific class
    if( archive.IsStoring() )
        archive << m_iInterpolationType << m_iLineType << m_iPointType 
				<< m_fLineWidth << m_fPointWidth;
    else
        archive >> m_iInterpolationType >> m_iLineType >> m_iPointType
				>> m_fLineWidth		 >> m_fPointWidth;
}

#ifdef _DEBUG
void CPGLLine::Dump( CDumpContext& dc ) const
{
    // call base class function first
    CPGLObject::Dump( dc );

    // now do the stuff for our specific class
	dc << _T("CPGLLine ID ") << GetID() << endl;
    dc << " interpolation type: " << m_iInterpolationType <<
		  " m_iLineType: " << m_iLineType << "line width: " << m_fLineWidth <<
		  " m_iPointType: "<< m_iPointType<< "point width: " << m_fPointWidth << "\n";
}
void CPGLLine::AssertValid() const
{
    // call inherited AssertValid first
    CPGLObject::AssertValid();

    // check members...
	ASSERT(m_fLineWidth>=0);
	ASSERT(m_fPointWidth>=0);
	ASSERT((m_iInterpolationType==PGL_INTERPOLATION_STEP)
		||(m_iInterpolationType==PGL_INTERPOLATION_LINEAR)
		||(m_iInterpolationType==PGL_INTERPOLATION_SEGMENT)
		);										// check m_iInterpolationType
	ASSERT((m_iLineType==PGL_LINE_NONE)
		||(m_iLineType==PGL_LINE_CONT)
		||(m_iLineType==PGL_LINE_BARBAR)
		||(m_iLineType==PGL_LINE_BARPOINT)
		||(m_iLineType==PGL_LINE_POINTPOINT)
		);			// check m_iLineType
	ASSERT((m_iPointType==PGL_POINT_NONE)
		||(m_iPointType==PGL_POINT_SIMPLE)
		||(m_iPointType==PGL_POINT_CONTOUR)
		||(m_iPointType==PGL_POINT_TRIANGLE)
		||(m_iPointType==PGL_POINT_SQUARE)
		);			// check m_iPointType
} 
#endif

CPGLLine::CPGLLine(UINT _iInterpolationType,UINT _iPointType,UINT _iLineType,const CPGLColor& _color)
: CPGLObject(_color)
{
	m_iInterpolationType=_iInterpolationType;
	m_iPointType=_iPointType;
	m_iLineType=_iLineType;
	m_fLineWidth=m_fPointWidth=1.0;
	m_iStripSize = 2;
}


CPGLLine::CPGLLine(const CPGLLine &l)
: CPGLObject(l)
{
	m_iInterpolationType=l.m_iInterpolationType;
	m_iPointType=l.m_iPointType;
	m_iLineType=l.m_iLineType;
	m_fLineWidth=l.m_fLineWidth;
	m_fPointWidth=l.m_fPointWidth;
	m_iStripSize = l.m_iStripSize;
}

CPGLLine& CPGLLine::operator = (const CPGLLine& l)
{
	// prevent self-assignement
	if (&l != this)
	{
		// invoke CPGLObject copy assignement operator
		this->CPGLObject::operator =(l);

		// copy the rest
		m_iInterpolationType=l.m_iInterpolationType;
		m_iPointType=l.m_iPointType;
		m_iLineType=l.m_iLineType;
		m_fLineWidth=l.m_fLineWidth;
		m_fPointWidth=l.m_fPointWidth;
		m_iStripSize = l.m_iStripSize;
	}
	return *this;
}

void CPGLLine::AddContextMenuItems(CMenu* pMenu)
{
	// call base class
	CPGLObject::AddContextMenuItems(pMenu);

	// add own items
}

void CPGLLine::AddPropertyPage(CPropertySheet *pPropSheet)
{
	// call own functions
	CPGLLinePropPage* propPage=new CPGLLinePropPage(this);
	pPropSheet->AddPage(propPage);

	// first call base class function
	CPGLObject::AddPropertyPage(pPropSheet);
}

void CPGLLine::PlotGfx(gfxinterface::CGfxInterface& gfx)
{
	if (!IsVisible())
		return;

	// calling base class plot
	CPGLObject::PlotGfx(gfx);
	
	gfx.AddComment("--- CPGLLine ---");	

	if (GetLineType()!=PGL_LINE_NONE)
	{
		SetDashGfx(gfx);	
		// set line width
		gfx.SetLineWidth(GetLineWidth());	
		PlotLineStripGfx(gfx);
	}

	// Draws points (if necessary)
	if (GetPointType()!=PGL_POINT_NONE)
	{
		PlotPointStripGfx(gfx);
	}

	PlotArrowsGfx(gfx);
}

void CPGLLine::SetDashGfx(gfxinterface::CGfxInterface& gfx)
{
	// set line style
	switch(m_iLineType)
	{
	case PGL_LINE_CONT:
		gfx.SetDash("");
		break;
	case PGL_LINE_BARBAR :
		gfx.SetDash("4 4");
		break;
	case PGL_LINE_BARPOINT:
		gfx.SetDash("4 4 1 4");
		break;		
	case PGL_LINE_POINTPOINT:
		gfx.SetDash("3 1");
		break;		
	}
}
