// CViewGL2D1.cpp: implementation of the CViewGL2D class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "ViewGL2D.h"


IMPLEMENT_SERIAL(CViewGL2D,CViewGL,1);

#ifdef _DEBUG
void CViewGL2D::AssertValid() const
{
    // call inherited AssertValid first
    CViewGL::AssertValid();

    // check CViewGL2D members...
}

void CViewGL2D::Dump( CDumpContext& ch ) const
{
    // call base class function first
    CViewGL::Dump( ch );

    // now do the stuff for our specific class
	ch<<_T("--- CViewGL2D Object ---\n");
} 
#endif

void CViewGL2D::Serialize( CArchive& archive )
{
    // call base class function first
    // base class is CObject in this case
    CViewGL::Serialize( archive );
	
    // now do the stuff for our specific class
    if (archive.IsStoring())
	{
		archive<<m_dLeft<<m_dRight<<m_dTop<<m_dBottom;
	}
    else
	{
		archive>>m_dLeft>>m_dRight>>m_dTop>>m_dBottom;
	}
}

CViewGL2D::CViewGL2D(GLdouble _dLeft,GLdouble _dRight, GLdouble _dTop,GLdouble _dBottom)
: CViewGL()
{
	m_dLeft=_dLeft;
	m_dRight=_dRight;
	m_dTop=_dTop;
	m_dBottom=_dBottom;

	// setting standard state
	m_StateGL.SetAntialias(TRUE);
	m_StateGL.SetBlending(TRUE);
	m_StateGL.SetBackFaceCulling(FALSE);
	m_StateGL.SetBkgColor(CVector3(1.0f,1.0f,1.0f));
	m_StateGL.SetDepthTest(FALSE);
	m_StateGL.SetStencilTest(FALSE);
	m_StateGL.SetLighting(FALSE);
	m_StateGL.SetPolygonMode(GL_LINE);
	m_StateGL.SetGouraud(TRUE);
	m_StateGL.SetLineStipple(FALSE);
}


CViewGL2D::CViewGL2D(const CViewGL2D &v2D)
: CViewGL(v2D)
{
	m_dLeft=v2D.m_dLeft;
	m_dRight=v2D.m_dRight;
	m_dTop=v2D.m_dTop;
	m_dBottom=v2D.m_dBottom;
}

CViewGL2D& CViewGL2D::operator =(const CViewGL2D &v2D)
{
	// preventing self copying
	if (&v2D!=this)
	{
		// invoke CPGLSurface copy assignement operator
		this->CViewGL::operator=(v2D);

		m_dLeft=v2D.m_dLeft;
		m_dRight=v2D.m_dRight;
		m_dTop=v2D.m_dTop;
		m_dBottom=v2D.m_dBottom;
	}

	return *this;
}

void CViewGL2D::Reshape()
{
	// stop if the view don't need reshaping...
	if (!NeedReshape())
		return;

	// intialize projection and model matrices
	glViewport(m_iTx,m_iTy,m_iWidth,m_iHeight);
 	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(m_dLeft,m_dRight,m_dBottom,m_dTop,-1,1);
	glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

	// Calling base class function
	CViewGL::Reshape();

	// flushing instructions
	glFinish();
}


void CViewGL2D::InitGLState()
{
	if (!m_StateGL.NeedSetState())
		return;
	
	CViewGL::InitGLState();

	glDisable(GL_POLYGON_OFFSET_FILL);	
	glDisable(GL_POLYGON_OFFSET_LINE);	

	glDisable(GL_NORMALIZE);

	glFinish();
}
