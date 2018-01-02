// StateGL.cpp: implementation of the CStateGL class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StateGL.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


IMPLEMENT_SERIAL(CStateGL,CObject,1);

#ifdef _DEBUG
void CStateGL::AssertValid() const
{
    // call inherited AssertValid first
    CObject::AssertValid();

    // check CStateGL members...
	ASSERT((m_iPolygonMode==GL_POINT) ||
		(m_iPolygonMode==GL_LINE) ||
		(m_iPolygonMode==GL_FILL));
}

void CStateGL::Dump( CDumpContext& ch ) const
{
    // call base class function first
    CObject::Dump( ch );

    // now do the stuff for our specific class
	ch<<_T("--- CStateGL Object ---\n");
} 
#endif

void CStateGL::Serialize( CArchive& archive )
{
    // call base class function first
    // base class is CObject in this case
    CObject::Serialize( archive );
	
    // now do the stuff for our specific class
    if (archive.IsStoring())
	{
		archive<<m_bAntialias
			<<m_bBackFaceCulling
			<<m_bBlending
			<<m_bGouraud
			<<m_bLighting
			<<m_bLineStipple
			<<m_bDepthTest
			<<m_bStencilTest
			<<m_cBkgColor
			<<m_fLineWidth
			<<m_iPolygonMode;
	}
    else
	{
		archive>>m_bAntialias
			>>m_bBackFaceCulling
			>>m_bBlending
			>>m_bGouraud
			>>m_bLighting
			>>m_bLineStipple
			>>m_bDepthTest
			>>m_bStencilTest
			>>m_cBkgColor
			>>m_fLineWidth
			>>m_iPolygonMode;
	}

	// state need resetting
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStateGL::CStateGL()
{
	m_bPostSetState=TRUE;

	m_bAntialias=TRUE;
	m_bBackFaceCulling=TRUE;
	m_bBlending=TRUE;
	m_bDepthTest=TRUE;
	m_bStencilTest=FALSE;
	m_bLighting=TRUE;
	m_bLineStipple=FALSE;
	m_bGouraud=TRUE;
	m_fLineWidth=2;
	m_iPolygonMode=GL_FILL;
	m_cBkgColor=CVector3(1.0f,1.0f,1.0f);
}

CStateGL::CStateGL(const CStateGL &sgl)
{
	m_bPostSetState=TRUE;

	m_bAntialias=sgl.m_bAntialias;
	m_bBackFaceCulling=sgl.m_bBackFaceCulling;
	m_bBlending=sgl.m_bBlending;
	m_bDepthTest=sgl.m_bDepthTest;
	m_bStencilTest=sgl.m_bStencilTest;
	m_bLighting=sgl.m_bLighting;
	m_bLineStipple=sgl.m_bLineStipple;
	m_bGouraud=sgl.m_bGouraud;
	m_fLineWidth=sgl.m_fLineWidth;
	m_iPolygonMode=sgl.m_iPolygonMode;
	m_cBkgColor=sgl.m_cBkgColor;
}

CStateGL& CStateGL::operator =(const CStateGL &sgl)
{
	if (&sgl!=this)
	{
		m_bPostSetState=TRUE;

		m_bAntialias=sgl.m_bAntialias;
		m_bBackFaceCulling=sgl.m_bBackFaceCulling;
		m_bBlending=sgl.m_bBlending;
		m_bDepthTest=sgl.m_bDepthTest;
		m_bStencilTest=sgl.m_bStencilTest;
		m_bLighting=sgl.m_bLighting;
		m_bLineStipple=sgl.m_bLineStipple;
		m_bGouraud=sgl.m_bGouraud;
		m_iPolygonMode=sgl.m_iPolygonMode;
		m_cBkgColor=sgl.m_cBkgColor;
	}
	return *this;
}

CStateGL::~CStateGL()
{

}

BOOL CStateGL::GetStateFromDC()
{
	return TRUE;
}

void CStateGL::SetStateGL()
{
	if (!m_bPostSetState)
		return;
	m_bPostSetState=FALSE;

	// ok setting state
	glPolygonMode(GL_FRONT_AND_BACK, m_iPolygonMode);

	// Culling
	glDrawBuffer(GL_BACK);

	if (m_bBackFaceCulling)
	{
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
	}
	else
		glDisable(GL_CULL_FACE);

	// lighing
	if (m_bLighting)
		glEnable(GL_LIGHTING);
	else
		glDisable(GL_LIGHTING);

	// gouraud
	if (m_bGouraud)
		glShadeModel(GL_SMOOTH);
	else
		glShadeModel(GL_FLAT);

	// background color
	glClearColor(m_cBkgColor.x, m_cBkgColor.y, m_cBkgColor.z, 0.0f);

	// depth test
	if (m_bDepthTest)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	// antialiasing
	if (m_bAntialias)
	{
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
//		glEnable(GL_POLYGON_SMOOTH);
//		glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
	}
	else
	{
		glDisable(GL_LINE_SMOOTH);
//		glDisable(GL_POLYGON_SMOOTH);
	}

	// blending
	if (m_bBlending)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	}
	else
	{
		glDisable(GL_BLEND);
	}

	glLineWidth(m_fLineWidth);
	// line stipple
	glLineStipple(2,0x9999);

	if (m_bLineStipple)
		glEnable(GL_LINE_STIPPLE);	
	else
		glDisable(GL_LINE_STIPPLE);	
}
