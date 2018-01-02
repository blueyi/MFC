// PGLLine2DLOD.cpp: implementation of the CPGLLine2DLOD class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PGL/PGLLine2DLOD.h"
#include "PGL/PGLLine2DLODPropPage.h"

IMPLEMENT_SERIAL(CPGLLine2DLOD, CPGLLine2D,1);

void CPGLLine2DLOD::Serialize(CArchive &archive)
{
    // call base class function first
    // base class is CObject in this case
    CPGLLine2D::Serialize( archive );

    // now do the stuff for our specific class
    if( archive.IsStoring() )
	{
	}
    else
	{
	}
}

#ifdef _DEBUG
void CPGLLine2DLOD::Dump( CDumpContext& dc ) const
{
    // call base class function first
    CPGLLine2D::Dump( dc );

    // now do the stuff for our specific class
	dc << _T("CPGLLine2DLOD ID ") << GetID() << endl;
	dc <<"Tol : "<<m_hull.GetTol()<<endl;
}
void CPGLLine2DLOD::AssertValid() const
{
    // call inherited AssertValid first
    CPGLLine2D::AssertValid();

} 
#endif


CPGLLine2DLOD::CPGLLine2DLOD()
: CPGLLine2D()
{
	LoadBitmap(IDB_PGL_LINE2DLOD_BITMAP);
}

CPGLLine2DLOD::CPGLLine2DLOD(const CPGLLine2DLOD &l)
: CPGLLine2D(l)
{
	using namespace hull;
	// Copying tol...
	m_hull.SetTol(l.m_hull.GetTol());
	
	// setting curve
	LODLine::PointContainer& pc=m_hull.GetPoints();
	pc.resize(m_iNPoints);

	// filling structure
	for (int i=0;i<m_iNPoints;i++)
	{
		pc[i].x=m_pX[i];
		pc[i].y=m_pY[i];
	}
	
	m_hull.ComputeBoundingBox();

	// Approximating
	m_hull.Simplify();

	LoadBitmap(IDB_PGL_LINE2DLOD_BITMAP);
}

void CPGLLine2DLOD::AddContextMenuItems(CMenu* pMenu)
{
	ASSERT_VALID(pMenu);
	// first call base class function
	CPGLLine2D::AddContextMenuItems(pMenu);

	// add separator
	// add own entries...
//	pMenu->AppendMenu(MF_ENABLED | MF_STRING, ,"Test Line2D");	
}

void CPGLLine2DLOD::AddPropertyPage(CPropertySheet* pPropSheet)
{
	ASSERT_VALID(pPropSheet);
	// call own functions
	CPGLLine2DLODPropPage* propPage=new CPGLLine2DLODPropPage(this);
	pPropSheet->AddPage(propPage);

	// first call base class function
	CPGLLine2D::AddPropertyPage(pPropSheet);
}

CPGLLine2DLOD::~CPGLLine2DLOD()
{
}

/// plotting to EPS file
void CPGLLine2DLOD::PlotGfx(gfxinterface::CGfxInterface& gfx)
{
	// first if it is visible
	if (!IsVisible())
		return;

	gfx.AddComment("--- CPGLLine2DLOD ---");

	// calling base class plot
	CPGLLine2D::PlotGfx(gfx);
}

void CPGLLine2DLOD::SetDatas(int _nPoints, double *_x, double *_y)
{
	CPGLLine2D::SetDatas(_nPoints, _x, _y);

	// setting curve
	LODLine::PointContainer& pc=m_hull.GetPoints();
	pc.resize(_nPoints);
	m_iNPoints = _nPoints;

	// filling structure
	for (int i=0;i<m_iNPoints;i++)
	{
		pc[i].x=m_pX[i];
		pc[i].y=m_pY[i];
	}
	
	m_hull.ComputeBoundingBox();

	// Approximating
	m_hull.Simplify();
}

void CPGLLine2DLOD::SetDatas(const std::vector<double>& vx, const std::vector<double>& vy)
{
	CPGLLine2D::SetDatas(vx, vy);

	m_hull.SetPoints(vx,vy);

	// Approximating
	m_hull.Simplify();
}

void CPGLLine2DLOD::UpdateExtent(CPGLView* pView)
{
	// Calling base class function
	CPGLLine2D::UpdateExtent(pView);

	// recomputing hull
	m_hull.Simplify();
}

void CPGLLine2DLOD::SetTol(double tol)
{
	m_hull.SetTol(tol);

	// recompute hull
	m_hull.Simplify();
}

void CPGLLine2DLOD::PlotLineStripGfx(gfxinterface::CGfxInterface& gfx)
{
	const LODLine::KeyContainer& kc= m_hull.GetKeys();
	LODLine::KeyContainer::const_iterator it;
	UINT i;
	double* pX=new double[kc.size()];
	double* pY=new double[kc.size()];
	for (it=kc.begin(), i=0; it!=kc.end();it++, i++)
	{
		pX[i] = (*it)->x;
		pY[i] = (*it)->y;
	}

	if (m_bFilled)
	{
		gfx.PushState();
		gfx.SetFillColor(GetColor().GetRed(), GetColor().GetGreen(), GetColor().GetBlue(), GetColor().GetAlpha());
		gfx.SetColor(0,0,0);
		switch (GetInterpolationType())
		{
		case PGL_INTERPOLATION_STEP:
			gfx.DrawStepStrip(kc.size(),pX,pY, false, true);
			break;
		case PGL_INTERPOLATION_LINEAR:
			gfx.DrawLineStrip(kc.size(),pX,pY, false, true);
			break;
		case PGL_INTERPOLATION_SEGMENT:
			gfx.DrawMultipleLineStrip(kc.size(),m_iStripSize,pX,pY, false, true);
			break;
		}
		gfx.PopState();
	}
	else
	{
		switch (GetInterpolationType())
		{
		case PGL_INTERPOLATION_STEP:
			gfx.DrawStepStrip(kc.size(),pX,pY);
			break;
		case PGL_INTERPOLATION_LINEAR:
			gfx.DrawLineStrip(kc.size(),pX,pY);
			break;
		case PGL_INTERPOLATION_SEGMENT:
			gfx.DrawMultipleLineStrip(kc.size(),m_iStripSize, pX, pY);
			break;
		}
	}


	delete[] pX;
	delete[] pY;
}

void CPGLLine2DLOD::PlotPointStripGfx(gfxinterface::CGfxInterface& gfx)
{
	const LODLine::KeyContainer& kc= m_hull.GetKeys();
	LODLine::KeyContainer::const_iterator it;
	UINT i;
	double* pX=new double[kc.size()];
	double* pY=new double[kc.size()];
	for (it=kc.begin(), i=0; it!=kc.end();it++, i++)
	{
		pX[i] = (*it)->x;
		pY[i] = (*it)->y;
	}

	// choose type of interpolation between points
	switch(GetPointType())
	{
	case PGL_POINT_SIMPLE:
		gfx.DrawCircleStrip(kc.size(), pX, pY, GetPointWidth(), true);
		break;
	case PGL_POINT_CONTOUR:
		gfx.DrawCircleStrip(kc.size(), pX, pY, GetPointWidth());
		break;
	case PGL_POINT_TRIANGLE:
		gfx.DrawTriangleStrip(kc.size(), pX, pY, GetPointWidth());
		break;
	case PGL_POINT_SQUARE:
		gfx.DrawSquareStrip(kc.size(), pX, pY, GetPointWidth());
		break;
	}

	delete[] pX;
	delete[] pY;
}
