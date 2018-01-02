// PGLMapVector.cpp: implementation of the CPGLMapVector class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PGL/PGLMapVector.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



IMPLEMENT_SERIAL(CPGLMapVector, CPGLMap,1);

void CPGLMapVector::Serialize(CArchive &archive)
{
	int i;
    // call base class function first
    // base class is CObject in this case
    CPGLMap::Serialize( archive );

    // now do the stuff for our specific class
	archive << m_dNormMin << m_dNormMax << m_fLineWidth;
    if( archive.IsStoring() )
	{
		for (i=0;i<m_iNx*m_iNy;i++)
		{
			archive << m_pVx[i] <<m_pVy[i];
		}
	}
    else
	{
		archive >> m_dNormMin >> m_dNormMax >> m_fLineWidth;
		// reallocation memory
		if (m_pVx)
			delete[] m_pVx; 
		if (m_pVy)
			delete[] m_pVy; 
		m_pVx=new double[m_iNx*m_iNy];
		m_pVy=new double[m_iNx*m_iNy];

		for (i=0;i<m_iNx*m_iNy;i++)
		{
			archive >> m_pVx[i] >> m_pVy[i];
		}
	}
}

#ifdef _DEBUG
void CPGLMapVector::Dump( CDumpContext& dc ) const
{
    // call base class function first
    CPGLMap::Dump( dc );

    // now do the stuff for our specific class
	dc << _T("CPGLMapVector ID ") << GetID() << endl;
}

void CPGLMapVector::AssertValid() const
{
    // call inherited AssertValid first
    CPGLMap::AssertValid();
} 
#endif


CPGLMapVector::CPGLMapVector()
: CPGLMap()
{
	m_pVx=NULL;
	m_pVy=NULL;
	m_dNormMin=0;
	m_dNormMax=1;
	m_fLineWidth=1;

	LoadBitmap(IDB_PGL_MAPVECTOR_BITMAP);
}

CPGLMapVector::CPGLMapVector(const CPGLMapVector &l)
: CPGLMap(l)
{
	m_pVx=new double[m_iNx*m_iNy];
	m_pVy=new double[m_iNx*m_iNy];
	for (int i=0;i<m_iNx*m_iNy;i++)
	{
		m_pVx[i]=l.m_pVx[i];
		m_pVy[i]=l.m_pVy[i];
	}	
	m_dNormMin=l.m_dNormMin;
	m_dNormMax=l.m_dNormMax;
	m_fLineWidth=l.m_fLineWidth;
	LoadBitmap(IDB_PGL_MAPVECTOR_BITMAP);

}

CPGLMapVector& CPGLMapVector::operator = (const CPGLMapVector& l)
{
	// prevent self copy
	if (&l != this)
	{
		// invoke CPGLMap copy assignement operator
		this->CPGLMap::operator=(l);

		m_dNormMin=l.m_dNormMin;
		m_dNormMax=l.m_dNormMax;
		m_fLineWidth=l.m_fLineWidth;
		// deallocate
		if (m_pVx)
			delete[] m_pVx;
		if (m_pVy)
			delete[] m_pVy;
		// reallocation memory
		m_pVx=new double[m_iNx*m_iNy];
		m_pVy=new double[m_iNx*m_iNy];

		for (int i=0;i<m_iNx*m_iNy;i++)
		{
			m_pVx[i]=l.m_pVx[i];
			m_pVy[i]=l.m_pVy[i];
		}	
	}
	return *this;
}

CPGLMapVector::~CPGLMapVector() 
{
	if (m_pVx)
		delete[] m_pVx;
	if (m_pVy)
		delete[] m_pVy;
};

void CPGLMapVector::AddContextMenuItems(CMenu* pMenu)
{
	ASSERT_VALID(pMenu);
	// first call base class function
	CPGLMap::AddContextMenuItems(pMenu);

	// add separator
	// add own entries...
}

void CPGLMapVector::AddPropertyPage(CPropertySheet* pPropSheet)
{
	ASSERT_VALID(pPropSheet);
	// call own functions
	CPGLMapVectorPropPage* propPage=new CPGLMapVectorPropPage(this);
	pPropSheet->AddPage(propPage);

	// first call base class function
	CPGLMap::AddPropertyPage(pPropSheet);
}

/// plotting to EPS file
void CPGLMapVector::PlotGfx(gfxinterface::CGfxInterface& gfx)
{
	// first if it is visible
	if (!IsVisible())
		return;

	int i,j,k;
	double xCur,yCur;
	double vx,vy,norm,length;
	CPGLColor col;

	// calling base class plot
	CPGLMap::PlotGfx(gfx);

	gfx.AddComment("--- CPGLMapVector ---");	
	gfx.PushState();
	gfx.SetFillColor(GetColor().GetRed(), GetColor().GetGreen(), GetColor().GetBlue(), GetColor().GetAlpha());
	gfx.SetColor(GetColor().GetRed(), GetColor().GetGreen(), GetColor().GetBlue(), GetColor().GetAlpha());
	gfx.SetDash("");
	length=__min(m_dDx,m_dDy);

	// let's go for the fun
	double* pV= new double [2*m_iNx*m_iNy];
	ASSERT(pV);
	// sending points by rows
	yCur=m_dY0+(m_iNy-1)*m_dDy;
	k=0;
	for (i=0;i<m_iNy;i++)
	{
		xCur=m_dX0;
		for (j=0;j<m_iNx;j++)
		{
			vx=m_pVx[i*m_iNx+j];
			vy=m_pVy[i*m_iNx+j];
			norm=sqrt(vx*vx+vy*vy);
			vx*=length/(norm);
			vy*=length/(norm);

			pV[2*k]=vx;
			pV[2*k+1]=vy;
			// updating x
			xCur+=m_dDx;
			k++;
		}
		yCur-=m_dDy;
	}
	gfx.DrawVectorField(m_iNx, m_iNy, m_dX0, m_dY0, m_dDx, m_dDy, pV, GetLineWidth());
	gfx.PopState();
	delete[] pV;
}

void CPGLMapVector::SetDatas(double *pVx, double* pVy)
{
	int i;
	double norm;

	// cleaning if needed
	if (m_pVx)
	{
		delete[] m_pVx;
		m_pVx=NULL;
	}
	if (m_pVy)
	{
		delete[] m_pVy;
		m_pVy=NULL;
	}

	// getting address of buffers
	m_pVx=pVx;
	m_pVy=pVy;

	if ((m_pVx==NULL) || (m_pVy==NULL) || (m_iNx==0) || (m_iNy==0))
	{
		m_dNormMin=0;
		m_dNormMax=1;
		return;
	}

	// finding min and max
	// init loop
	m_dNormMin=m_dNormMax=sqrt(m_pVx[0]*m_pVx[0]+m_pVy[0]*m_pVy[0]);
	for (i=0;i<m_iNx*m_iNy;i++)
	{
		norm=sqrt(m_pVx[i]*m_pVx[i]+m_pVy[i]*m_pVy[i]);
		m_dNormMin=__min(m_dNormMin,norm);
		m_dNormMax=__max(m_dNormMax,norm);
	}

	PostUpdateExtent();
}

void CPGLMapVector::SetDatas(const std::vector<double>& pVx, const std::vector<double>&  pVy)
{
	ASSERT(pVx.size() == m_iNx);
	ASSERT(pVy.size() == m_iNy);
	UINT i;
	double norm;

	// cleaning if needed
	if (m_pVx)
	{
		delete[] m_pVx;
		m_pVx=NULL;
	}
	if (m_pVy)
	{
		delete[] m_pVy;
		m_pVy=NULL;
	}

	// getting address of buffers
	if ((pVx.size()==0) || (pVy.size()==0) || (m_iNx==0) || (m_iNy==0))
	{
		m_dNormMin=0;
		m_dNormMax=1;
		return;
	}

	// allocating memory
	m_pVx=new double[m_iNx];
	m_pVy=new double[m_iNx];

	// finding min and max
	// init loop
	m_dNormMin=m_dNormMax=sqrt(m_pVx[0]*m_pVx[0]+m_pVy[0]*m_pVy[0]);
	for (i=0;i<m_iNx*m_iNy;i++)
	{
		norm=sqrt(m_pVx[i]*m_pVx[i]+m_pVy[i]*m_pVy[i]);
		m_dNormMin=__min(m_dNormMin,norm);
		m_dNormMax=__max(m_dNormMax,norm);
	}

	PostUpdateExtent();
}
