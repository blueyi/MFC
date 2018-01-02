// Line2DGL.cpp: implementation of the CPGLLine2D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PGL/PGLLine2D.h"
#include "PGL/PGLLine2DPropPage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CPGLLine2D, CPGLLine,1);

void CPGLLine2D::Serialize(CArchive &archive)
{
	int i;
    // call base class function first
    // base class is CObject in this case
    CPGLLine::Serialize( archive );

    // now do the stuff for our specific class
    if( archive.IsStoring() )
	{
		archive<< m_bFilled;
        archive << m_iNPoints;
		for (i=0;i<2;i++)
		{
			archive <<m_spHeadShow[i] << m_spHeadThick[i] << m_spHeadLength[i];
		}
		for (i=0;i<m_iNPoints;i++)
		{
			archive << m_pX[i] << m_pY[i];
		}
	}
    else
	{
		archive>> m_bFilled;
        archive >>	m_iNPoints;
		for (i=0;i<2;i++)
		{
			archive >>m_spHeadShow[i] >> m_spHeadThick[i] >> m_spHeadLength[i];
		}

		// reallocation memory
		if (m_pX)
			delete[] m_pX; 
		if (m_pY)
			delete[] m_pY; 
		m_pX=new double[m_iNPoints];
		m_pY=new double[m_iNPoints];

		for (i=0;i<m_iNPoints;i++)
		{
			archive >> m_pX[i] >> m_pY[i];
		}
	}
}

#ifdef _DEBUG
void CPGLLine2D::Dump( CDumpContext& dc ) const
{
    // call base class function first
    CPGLLine::Dump( dc );

    // now do the stuff for our specific class
	dc << _T("CPGLLine2D ID ") << GetID() << endl;
    dc << _T("nb points: ") << m_iNPoints << endl;
}
void CPGLLine2D::AssertValid() const
{
    // call inherited AssertValid first
    CPGLLine::AssertValid();

    // check members...
	ASSERT(m_iNPoints>0);

} 
#endif


CPGLLine2D::CPGLLine2D()
: CPGLLine()
{
	m_spHeadShow[0]=m_spHeadShow[1]=FALSE;
	m_spHeadThick[0]=m_spHeadThick[1]=12;
	m_spHeadLength[0]=m_spHeadLength[1]=16;
	m_iNPoints=0;
	m_pX=NULL;
	m_pY=NULL;
	m_bFilled=FALSE;

	LoadBitmap(IDB_PGL_LINE2D_BITMAP);
}

CPGLLine2D::CPGLLine2D(const CPGLLine2D &l)
: CPGLLine(l)
{
	int i;

	m_bFilled = l.m_bFilled;
	m_iNPoints=l.m_iNPoints;
	for (i=0;i<2;i++)
	{
		m_spHeadShow[i]=l.m_spHeadShow[i];
		m_spHeadThick[i]=l.m_spHeadThick[i];
		m_spHeadLength[i]=l.m_spHeadLength[i];
	}

	m_pX=new double[m_iNPoints];
	m_pY=new double[m_iNPoints];

	for (i=0;i<m_iNPoints;i++)
	{
		m_pX[i]=l.m_pX[i];
		m_pY[i]=l.m_pY[i];
	}	

	LoadBitmap(IDB_PGL_LINE2D_BITMAP);
}

CPGLLine2D& CPGLLine2D::operator = (const CPGLLine2D& l)
{
	int i;

	// prevent self copy
	if (&l != this)
	{
		// invoke CPGLLine copy assignement operator
		this->CPGLLine::operator=(l);

		for (i=0;i<2;i++)
		{
			m_spHeadShow[i]=l.m_spHeadShow[i];
			m_spHeadThick[i]=l.m_spHeadThick[i];
			m_spHeadLength[i]=l.m_spHeadLength[i];
		}

		m_bFilled = l.m_bFilled;
		// copy the operand
		if (m_iNPoints!=l.m_iNPoints)
		{
			// reallocation memory
			m_iNPoints=l.m_iNPoints;
			if (m_pX)
				delete[] m_pX; 
			m_pX=new double[m_iNPoints];
			if (m_pY)
				delete[] m_pY; 
			m_pY=new double[m_iNPoints];
		}
		for (i=0;i<m_iNPoints;i++)
		{
			m_pX[i]=l.m_pX[i];
			m_pY[i]=l.m_pY[i];
		}	
	}
	return *this;
}

CPGLLine2D::~CPGLLine2D() 
{
	if (m_pX)
		delete[] m_pX; 
	if (m_pY)
		delete[] m_pY;
};

void CPGLLine2D::AddContextMenuItems(CMenu* pMenu)
{
	ASSERT_VALID(pMenu);
	// first call base class function
	CPGLLine::AddContextMenuItems(pMenu);

	// add separator
	// add own entries...
//	pMenu->AppendMenu(MF_ENABLED | MF_STRING, ,"Test Line2D");	
}

void CPGLLine2D::AddPropertyPage(CPropertySheet* pPropSheet)
{
	ASSERT_VALID(pPropSheet);
	// call own functions
	CPGLLine2DPropPage* propPage=new CPGLLine2DPropPage(this);
	pPropSheet->AddPage(propPage);

	// first call base class function
	CPGLLine::AddPropertyPage(pPropSheet);
}

void CPGLLine2D::SetDatas(int _nPoints, double *_x, double *_y)
{
	// cleaning old datas.
	if (m_pX)
		delete[] m_pX;
	if (m_pY)
		delete[] m_pY;
	// storing pointers...
	m_iNPoints=_nPoints;
	m_pX=_x;
	m_pY=_y;

	PostUpdateExtent();
}

void CPGLLine2D::SetDatas(const std::vector<double>& vx, const std::vector<double>& vy)
{
	// cleaning old datas.
	if (m_pX)
	{
		delete[] m_pX;
		m_pX=NULL;
	}
	if (m_pY)
	{
		delete[] m_pY;
		m_pY=NULL;
	}

	// storing pointers...
	m_iNPoints=__min(vx.size(),vy.size());
	m_pX=new double [m_iNPoints];
	m_pY=new double [m_iNPoints];
	for (UINT i=0;i<m_iNPoints;i++)
	{
		m_pX[i]=vx[i];
		m_pY[i]=vy[i];
	}

	PostUpdateExtent();
}

double* CPGLLine2D::GetExtent(CPGLView* pView)
{
	if (NeedUpdateExtent())
		UpdateExtent(pView);

	return CPGLLine::GetExtent(pView);
}

void CPGLLine2D::UpdateExtent(CPGLView* pView)
{
	// Calling base class function
	CPGLLine::UpdateExtent(pView);

	int i;
	// init extent :
	if (m_iNPoints>0)
	{
		m_extent[0]=m_extent[1]=m_pX[0];
		m_extent[2]=m_extent[3]=m_pY[0];
	}

	for (i=1;i<m_iNPoints;i++)
	{
		// testing left and right
		m_extent[0]=__min(m_extent[0],m_pX[i]);
		m_extent[1]=__max(m_extent[1],m_pX[i]);
		// testing bottom and up
		m_extent[2]=__min(m_extent[2],m_pY[i]);
		m_extent[3]=__max(m_extent[3],m_pY[i]);
	}
}

void CPGLLine2D::PlotLineStripGfx(gfxinterface::CGfxInterface& gfx)
{
	if (m_bFilled)
	{
		gfx.PushState();
		gfx.SetFillColor(GetColor().GetRed(), GetColor().GetGreen(), GetColor().GetBlue(), GetColor().GetAlpha());
		gfx.SetColor(0,0,0);
		switch (GetInterpolationType())
		{
		case PGL_INTERPOLATION_STEP:
			gfx.DrawStepStrip(m_iNPoints,m_pX,m_pY, false, true);
			break;
		case PGL_INTERPOLATION_LINEAR:
			gfx.DrawLineStrip(m_iNPoints,m_pX,m_pY, false, true);
			break;
		case PGL_INTERPOLATION_SEGMENT:
			gfx.DrawMultipleLineStrip(m_iNPoints,m_iStripSize,m_pX,m_pY, false, true);
			break;
		}
		gfx.PopState();
	}
	else
	{
		switch (GetInterpolationType())
		{
		case PGL_INTERPOLATION_STEP:
			gfx.DrawStepStrip(m_iNPoints,m_pX,m_pY);
			break;
		case PGL_INTERPOLATION_LINEAR:
			gfx.DrawLineStrip(m_iNPoints,m_pX,m_pY);
			break;
		case PGL_INTERPOLATION_SEGMENT:
			gfx.DrawMultipleLineStrip(m_iNPoints,m_iStripSize, m_pX, m_pY);
			break;
		}
	}
}

void CPGLLine2D::PlotPointStripGfx(gfxinterface::CGfxInterface& gfx)
{
	// choose type of interpolation between points
	gfx.SetFillColor(GetColor().GetRed(), GetColor().GetGreen(), GetColor().GetBlue(), GetColor().GetAlpha());
	switch(GetPointType())
	{
	case PGL_POINT_SIMPLE:
		gfx.DrawCircleStrip(m_iNPoints, m_pX, m_pY, GetPointWidth(), true);
		break;
	case PGL_POINT_CONTOUR:
		gfx.DrawCircleStrip(m_iNPoints, m_pX, m_pY, GetPointWidth());
		break;
	case PGL_POINT_TRIANGLE:
		gfx.DrawTriangleStrip(m_iNPoints, m_pX, m_pY, GetPointWidth());
		break;
	case PGL_POINT_SQUARE:
		gfx.DrawSquareStrip(m_iNPoints, m_pX, m_pY, GetPointWidth());
		break;
	}
}


void CPGLLine2D::PlotArrowsGfx(gfxinterface::CGfxInterface& gfx)
{
	double x,y,vx,vy,norm;
	int i;

	// drawing arrows if needed
	if (GetNPoints()<=1)
		return;

	for (i=0;i<2;i++)
	{
		// start arrow
		if (!m_spHeadShow[i])
			continue;

		if (i==0)
		{
			x=GetXi(0);
			y=GetYi(0);
			vx=GetXi(0)-GetXi(1);
			vy=GetYi(0)-GetYi(1);
		}
		else
		{
			x=GetXi(GetNPoints()-1);
			y=GetYi(GetNPoints()-1);
			vx=GetXi(GetNPoints()-1)-GetXi(GetNPoints()-2);
			vy=GetYi(GetNPoints()-1)-GetYi(GetNPoints()-2);
		}

		norm=sqrt(vx*vx+vy*vy);
		if (norm <PGL_EPS)
			continue;

		vx*=m_spHeadLength[i]/(norm);
		vy*=m_spHeadLength[i]/(norm);
		// starting path
		// sending points to eps
		gfx.DrawArrowAbs(x, y, vx, vy, GetLineWidth()-1.0, m_spHeadThick[i], m_spHeadLength[i]);
	}
}
