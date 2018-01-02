// DPHullGL.cpp: implementation of the CDPHullGL class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DPHullGL.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDPHullGL::CDPHullGL()
{
	m_bHull=true;
}

CDPHullGL::~CDPHullGL()
{

}

void CDPHullGL::PlotPoints()
{
	int i;
	glBegin(GL_LINE_STRIP);
	PointContainer& pc = m_dpHull.GetPoints();
	for (i=0;i<pc.size();i++)
	{
		glVertex2f((GLfloat)pc[i].x,(GLfloat)pc[i].y);
	}
	glEnd();
}

void CDPHullGL::PlotKeys(CWGL& wgl)
{
	CString str;

	if (m_bHull)
	{
		glColor3f(1,0,0);
		PlotKeyMethod(m_dpHull);
	}

}

void CDPHullGL::PlotKeyMethod( const TLineApproximator<float, PointContainer, KeyContainer>& l)
{
	TLineApproximator<float, PointContainer, KeyContainer>& la = const_cast<TLineApproximator<float, PointContainer, KeyContainer>&> (l);

	const KeyContainer& kc = la.GetKeys();
	KeyContainer::const_iterator it;

	glBegin(GL_LINE_STRIP);
	for (it=kc.begin();it!=kc.end();it++)
	{
		glVertex2f((GLfloat)(*it)->x,(GLfloat)(*it)->y);
	}
	glEnd();
}

void CDPHullGL::SetTol( double dTol)
{
	m_dpHull.SetTol(dTol);
}

void CDPHullGL::ResizePoints(UINT nPoints)
{
	if (nPoints < 2)
		return;

	m_dpHull.GetPoints().resize(nPoints);
}

void CDPHullGL::SetPoint( UINT i, double x, double y)
{
	using namespace hull;
	ASSERT(i<GetPointSize());

	m_dpHull.GetPoints()[i]=hull::TPoint<float>(x,y);
}

void CDPHullGL::ComputeBoundingBox()
{
	m_dpHull.ComputeBoundingBox();
}

void CDPHullGL::Simplify()
{
	if (m_bHull)
		m_dpHull.Simplify();
}

UINT CDPHullGL::ShrinkNorm(double dScale, double dScaleTol, double eTolRight, UINT nMaxIter)
{
	return m_iterHull=m_dpHull.ShrinkNorm(dScale, dScaleTol, eTolRight,nMaxIter);
}
