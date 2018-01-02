// CPGLView.cpp: implementation of the CPGLView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PGL/PGLView.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CPGLView, CObject, 1);

void CPGLView::Serialize(CArchive &archive)
{
    // call base class function first
    // base class is CObject in this case
    CObject::Serialize( archive );

    // now do the stuff for our specific class
    if( archive.IsStoring() )
	{
		archive<<m_iTx<<m_iTy<<m_iWidth<<m_iHeight;
	}
    else
	{
		archive>>m_iTx>>m_iTy>>m_iWidth>>m_iHeight;
	}
}

#ifdef _DEBUG
void CPGLView::Dump( CDumpContext& dc ) const
{
    // call base class function first
    CObject::Dump( dc );

    // now do the stuff for our specific class
	// now dumping
	dc <<_T("--- CPGLView ---") << endl;
}

void CPGLView::AssertValid() const
{
    // call inherited AssertValid first
    CObject::AssertValid();

    // check CPGLView members...
	ASSERT(m_iTx>=0);
	ASSERT(m_iTy>=0);
	ASSERT(m_iWidth>=0);
	ASSERT(m_iHeight>=0);
} 

#endif

CPGLView::CPGLView(int _iTx,int _iTy,int _iWidth,int _iHeight)
{	
	m_iTx=_iTx; 
	m_iTy=_iTy; 
	m_iWidth=_iWidth; 
	m_iHeight=_iHeight; 
};
	
CPGLView::CPGLView(const CPGLView& v)
{
	m_iTx=v.m_iTx; 
	m_iTy=v.m_iTy; 
	m_iWidth=v.m_iWidth; 
	m_iHeight=v.m_iHeight; 
}
	
CPGLView& CPGLView::operator= (const CPGLView& v)
{
	if (this!=&v)
	{
		m_iTx=v.m_iTx; 
		m_iTy=v.m_iTy; 
		m_iWidth=v.m_iWidth; 
		m_iHeight=v.m_iHeight; 
	}
	return *this;
}

void CPGLView::PlotGfx(gfxinterface::CGfxInterface& gfx)
{
	gfx.SetBoundingBox(m_iTx, m_iTy,m_iTx+m_iWidth,m_iTy+m_iHeight);
}
