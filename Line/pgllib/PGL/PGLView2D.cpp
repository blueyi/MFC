// CPGLView2D1.cpp: implementation of the CPGLView2D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PGL/PGLView2D.h"

IMPLEMENT_SERIAL(CPGLView2D, CPGLView, 1);

void CPGLView2D::Serialize(CArchive &archive)
{
    // call base class function first
    // base class is CObject in this case
    CPGLView::Serialize( archive );

    // now do the stuff for our specific class
    if( archive.IsStoring() )
	{
		archive<<m_dLeft<<m_dRight<<m_dTop<<m_dBottom;
	}
    else
	{
		archive>>m_dLeft>>m_dRight>>m_dTop>>m_dBottom;
	}
}

#ifdef _DEBUG
void CPGLView2D::Dump( CDumpContext& dc ) const
{
    // call base class function first
    CPGLView::Dump( dc );

    // now do the stuff for our specific class
	// now dumping
	dc <<_T("--- CPGLView2D ---") << endl;
	dc <<_T("left: ")<<m_dLeft<<
		_T(" right: ")<<m_dRight<<
		_T(" top: ")<<m_dTop<<
		_T(" bottom: ")<<m_dBottom<<endl;
}

void CPGLView2D::AssertValid() const
{
    // call inherited AssertValid first
    CPGLView::AssertValid();

    // check CPGLView members...
	ASSERT(m_dLeft<m_dRight);
	ASSERT(m_dBottom<m_dTop);
} 

#endif

CPGLView2D::CPGLView2D(double _dLeft,double _dRight, double _dTop,double _dBottom)
: CPGLView()
{
	ASSERT(_dLeft<_dRight);
	ASSERT(_dBottom<_dTop);

	m_dLeft=_dLeft;
	m_dRight=_dRight;
	m_dTop=_dTop;
	m_dBottom=_dBottom;
	if (fabs(m_dBottom-m_dTop)<PGL_EPS)
	{
		m_dTop+=PGL_EPS;
	}
	if (fabs(m_dLeft-m_dRight)<PGL_EPS)
	{
		m_dRight+=PGL_EPS;
	}
}

CPGLView2D& CPGLView2D::operator =(const CPGLView2D &v2D)
{
	if (this!=&v2D)
	{
		this->CPGLView::operator=(v2D);
	
		m_dLeft=v2D.m_dLeft;
		m_dRight=v2D.m_dRight;
		m_dTop=v2D.m_dTop;
		m_dBottom=v2D.m_dBottom;
	}
	return *this;
}

CPGLView2D::CPGLView2D(const CPGLView2D &v2D)
:CPGLView(v2D)
{
	m_dLeft=v2D.m_dLeft;
	m_dRight=v2D.m_dRight;
	m_dTop=v2D.m_dTop;
	m_dBottom=v2D.m_dBottom;
}


void CPGLView2D::Pan(int x,int y)
{
	double dx=(double)x/m_iWidth*(m_dRight-m_dLeft);
	double dy=(double)y/m_iHeight*(m_dTop-m_dBottom);

	m_dLeft+=dx;
	m_dRight+=dx;
	m_dTop+=dy;
	m_dBottom+=dy;
}

void CPGLView2D::ZoomBox(int xStart,int yStart,int xEnd,int yEnd)
{
	double temp;

	// points orientation
	int xLeft=__min(xStart,xEnd);
	int yUp=__min(yStart,yEnd);
	int dx=abs(xStart - xEnd);
	int dy=abs(yEnd - yStart);
	
	dx=__max(1,dx);
	dy=__max(1,dy);

	temp=(double)(m_dRight-m_dLeft);
	m_dLeft+=temp*(xLeft-m_iTx)/(double)m_iWidth;
	m_dRight=m_dLeft+temp*dx/(double)m_iWidth;
	temp=(double)(m_dTop-m_dBottom);
	m_dTop-=temp*yUp/(double)m_iHeight;
	m_dBottom=m_dTop-temp*dy/(double)m_iHeight;
}

void CPGLView2D::ZoomAll(double _dLeft,double _dRight, double _dBottom, double _dTop)
{
	ASSERT(_dLeft<=_dRight);
	ASSERT(_dBottom<=_dTop);
	
	m_dLeft=_dLeft;
	m_dRight=_dRight;
	m_dTop=_dTop;
	m_dBottom=_dBottom;

}
	
void CPGLView2D::ZoomOut()
{
	double w=m_dRight-m_dLeft;
	double h=m_dTop-m_dBottom;

	m_dLeft-=w/4.0;
	m_dRight+=w/4.0;
	m_dTop+=h/4.0;
	m_dBottom-=h/4.0;

}

void CPGLView2D::ZoomIn()
{
	double w=m_dRight-m_dLeft;
	double h=m_dTop-m_dBottom;

	m_dLeft+=w/4.0;
	m_dRight-=w/4.0;
	m_dTop-=h/4.0;
	m_dBottom+=h/4.0;

}

void CPGLView2D::PlotGfx(gfxinterface::CGfxInterface& gfx)
{
	// calling base class
	CPGLView::PlotGfx(gfx);
	gfx.SetWorldBoundingBox(m_dLeft, m_dBottom, m_dRight, m_dTop);
}

double CPGLView2D::PixelToWorld(int iaxe, int pix)
{
	switch(iaxe)
	{
	case 0:
		ASSERT(m_iWidth > 0);
		return pix*(m_dRight-m_dLeft)/m_iWidth;
		break;
	case 1:
		ASSERT(m_iHeight > 0);
		return pix*(m_dTop-m_dBottom)/m_iHeight;
		break;
	default:
		return 0;
	}
}

double CPGLView2D::PixelToWorldCoord(int iaxe, int pix)
{
	switch(iaxe)
	{
	case 0:
		ASSERT(m_iWidth > 0);
		return m_dLeft+pix*(m_dRight-m_dLeft)/m_iWidth;
		break;
	case 1:
		ASSERT(m_iHeight > 0);
		return m_dTop-pix*(m_dTop-m_dBottom)/m_iHeight;
		break;
	default:
		return 0;
	}
}

double CPGLView2D::PixelToWorld(int iaxe, double pix)
{
	switch(iaxe)
	{
	case 0:
		ASSERT(m_iWidth > 0);
		return pix*(m_dRight-m_dLeft)/m_iWidth;
		break;
	case 1:
		ASSERT(m_iHeight > 0);
		return pix*(m_dTop-m_dBottom)/m_iHeight;
		break;
	default:
		return 0;
	}
}

double CPGLView2D::PixelToWorldCoord(int iaxe, double pix)
{
	switch(iaxe)
	{
	case 0:
		ASSERT(m_iWidth > 0);
		return m_dLeft+pix*(m_dRight-m_dLeft)/m_iWidth;
		break;
	case 1:
		ASSERT(m_iHeight > 0);
		return m_dTop-pix*(m_dTop-m_dBottom)/m_iHeight;
		break;
	default:
		return 0;
	}
}
