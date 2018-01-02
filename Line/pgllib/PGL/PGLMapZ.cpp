// PGLMapZ.cpp: implementation of the CPGLMapZ class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PGL/PGLMapZ.h"
#include "PGL/PGLMapZPropPage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


IMPLEMENT_SERIAL(CPGLMapZ, CPGLMap,1);

void CPGLMapZ::Serialize(CArchive &archive)
{
	int i;
    // call base class function first
    // base class is CObject in this case
    CPGLMap::Serialize( archive );

    // now do the stuff for our specific class
	int iCMap;
    if( archive.IsStoring() )
	{
		iCMap=(int)m_eCMap;
		archive << iCMap;
		archive <<m_dMin << m_dMax;
		for (i=0;i<m_iNx*m_iNy;i++)
		{
			archive << m_pZ[i];
		}
	}
    else
	{
		// reallocation memory
		if (m_pZ)
			delete[] m_pZ; 
		m_pZ=new double[m_iNx*m_iNy];

		archive>>iCMap;
		archive>>m_dMin >> m_dMax;
		m_eCMap=(PGL_COLORMAP)iCMap;
		for (i=0;i<m_iNx*m_iNy;i++)
		{
			archive >> m_pZ[i];
		}
	}
}

#ifdef _DEBUG
void CPGLMapZ::Dump( CDumpContext& dc ) const
{
    // call base class function first
    CPGLMap::Dump( dc );

    // now do the stuff for our specific class
	dc << _T("CPGLMapZ ID ") << GetID() << endl;
}
void CPGLMapZ::AssertValid() const
{
    // call inherited AssertValid first
    CPGLMap::AssertValid();
} 
#endif


CPGLMapZ::CPGLMapZ()
: CPGLMap()
{
	m_pZ=NULL;
	m_eCMap=pglCmHsv;
	m_dMin=0;
	m_dMax=1;

	LoadBitmap(IDB_PGL_MAPZ_BITMAP);
}

CPGLMapZ::CPGLMapZ(const CPGLMapZ &l)
: CPGLMap(l)
{
	m_eCMap=l.m_eCMap;
	m_dMin=l.m_dMin;
	m_dMax=l.m_dMax;
	m_pZ=new double[m_iNx*m_iNy];
	for (int i=0;i<m_iNx*m_iNy;i++)
	{
		m_pZ[i]=l.m_pZ[i];
	}
	LoadBitmap(IDB_PGL_MAPZ_BITMAP);

}

CPGLMapZ& CPGLMapZ::operator = (const CPGLMapZ& l)
{
	// prevent self copy
	if (&l != this)
	{
		// invoke CPGLMap copy assignement operator
		this->CPGLMap::operator=(l);

		m_eCMap=l.m_eCMap;
		m_dMin=l.m_dMin;
		m_dMax=l.m_dMax;

		// deallocate
		if (m_pZ)
			delete[] m_pZ;
		// reallocation memory
		m_pZ=new double[m_iNx*m_iNy];

		for (int i=0;i<m_iNx*m_iNy;i++)
		{
			m_pZ[i]=l.m_pZ[i];
		}	
	}
	return *this;
}

CPGLMapZ::~CPGLMapZ() 
{
	if (m_pZ)
		delete[] m_pZ; 
};

void CPGLMapZ::AddContextMenuItems(CMenu* pMenu)
{
	ASSERT_VALID(pMenu);
	// first call base class function
	CPGLMap::AddContextMenuItems(pMenu);

	// add separator
	// add own entries...
}

void CPGLMapZ::AddPropertyPage(CPropertySheet* pPropSheet)
{
	ASSERT_VALID(pPropSheet);
	// call own functions
	CPGLMapZPropPage* propPage=new CPGLMapZPropPage(this);
	pPropSheet->AddPage(propPage);

	// first call base class function
	CPGLMap::AddPropertyPage(pPropSheet);
}

/// plotting to EPS file
void CPGLMapZ::PlotGfx(gfxinterface::CGfxInterface& gfx)
{
	// first if it is visible
	if (!IsVisible())
		return;

	int i,j,k;
	double xCur,yCur;
	double alpha;
	CPGLColor col;

	// calling base class plot
	CPGLMap::PlotGfx(gfx);

	gfx.AddComment("--- CPGLMapZ ---");
	// generating colors
	double* pColor = new double[3*m_iNx*m_iNy];
	ASSERT(pColor);
	// sending points by rows
	yCur=m_dY0+(m_iNy-1)*m_dDy;
	k=0;
	for (i=0;i<m_iNy;i++)
	{
		xCur=m_dX0;
		for (j=0;j<m_iNx;j++)
		{
			// computing alpha
			alpha=(m_pZ[i*m_iNx+j]-m_dMin)/(m_dMax-m_dMin);
			// setting color
			CPGLUtility::ColorMap(m_eCMap,alpha,col);
			pColor[3*k]=col.GetRed();
			pColor[3*k+1]=col.GetGreen();
			pColor[3*k+2]=col.GetBlue();

			// updating xCur
			xCur+=m_dDx;
			k++;
		}
		// updating y
		yCur-=m_dDy;
	}
	// stroking
	gfx.DrawSurf(m_iNx, m_iNy, m_dX0, m_dY0, m_dDx, m_dDy, pColor);
	delete[] pColor;
}

void CPGLMapZ::SetDatas(double *pZ)
{
	int i;

	// cleaning if needed
	if (m_pZ)
	{
		delete[] m_pZ;
		m_pZ=NULL;
	}

	m_pZ=pZ;

	if ((pZ==NULL) || (m_iNx==0) || (m_iNy==0))
	{
		m_dMin=0;
		m_dMax=1;
		return;
	}

	// finding min and max
	// init loop
	m_dMin=m_pZ[0];
	m_dMax=m_pZ[0];
	for (i=0;i<m_iNx*m_iNy;i++)
	{
		m_dMin=__min(m_dMin,m_pZ[i]);
		m_dMax=__max(m_dMax,m_pZ[i]);
	}

	PostUpdateExtent();
}

void CPGLMapZ::SetDatas(const std::vector<double>& pZ)
{
	ASSERT(pZ.size() == m_iNx*m_iNy);

	UINT i;
	if ((pZ.size()==0) || (m_iNx==0) || (m_iNy==0))
	{
		m_dMin=0;
		m_dMax=1;
		return;
	}

	// cleaning if needed
	if (m_pZ)
	{
		delete[] m_pZ;
		m_pZ=NULL;
	}
	// allocating memory
	m_pZ=new double[m_iNx*m_iNy];

	// finding min and max and copying
	// init loop
	m_dMin=m_dMax=m_pZ[0]=pZ[0];
	for (i=0;i<m_iNx*m_iNy;i++)
	{
		m_pZ[i]=pZ[i];
		m_dMin=__min(m_dMin,m_pZ[i]);
		m_dMax=__max(m_dMax,m_pZ[i]);
	}

	PostUpdateExtent();
}
