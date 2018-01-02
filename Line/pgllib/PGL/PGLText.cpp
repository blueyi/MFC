// TextGL.cpp: implementation of the CPGLText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PGL/PGLText.h"
#include "PGL/PGLTextPropPage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CPGLText,CPGLObject,1);

void CPGLText::Serialize(CArchive &archive)
{
    // call base class function first
    // base class is CObject in this case
    CPGLObject::Serialize( archive );

    // now do the stuff for our specific class
    if( archive.IsStoring() )
	{
        archive		<< m_sText
					<< m_pPosition[0] << m_pPosition[1]
					<< m_iAlign << m_fAngle;
	}
    else
	{
        archive		>> m_sText
					>> m_pPosition[0] >> m_pPosition[1]
					>> m_iAlign >> m_fAngle;
	}
}

#ifdef _DEBUG
void CPGLText::Dump( CDumpContext& dc ) const
{
    // call base class function first
    CPGLObject::Dump( dc );

    // now do the stuff for our specific class
	dc << _T("--- CPGLText ID ") << GetID() <<_T(" ---\n");
}

void CPGLText::AssertValid() const
{
    // call inherited AssertValid first
    CPGLObject::AssertValid();

	ASSERT( (m_iAlign==PGL_TEXT_ALIGN_LEFT)
		|| (m_iAlign==PGL_TEXT_ALIGN_RIGHT)
		|| (m_iAlign==PGL_TEXT_ALIGN_CENTER));
} 
#endif

CPGLText::CPGLText(const CString& _sText, int _fontID)
:CPGLObject()
{ 
	m_sText=_sText; 
	m_iAlign=PGL_TEXT_ALIGN_LEFT;
	m_pPosition=new float[2];
	m_pPosition[0]=0.5f;
	m_pPosition[1]=0.5f;
	m_fAngle=0;

	// setting to black
	SetColor(0.0,0.0,0.0,1.0f);

	LoadBitmap(IDB_PGL_TEXT_BITMAP);
};

CPGLText::CPGLText(const CPGLText& t)
: CPGLObject(t)
{
	m_sText=t.m_sText;
	m_iAlign=t.m_iAlign;
	m_pPosition=new float[2];
	m_pPosition[0]=t.m_pPosition[0];
	m_pPosition[1]=t.m_pPosition[1];
	m_fAngle=t.m_fAngle;

	LoadBitmap(IDB_PGL_TEXT_BITMAP);

}

CPGLText& CPGLText::operator=(const CPGLText& t)
{
	if (&t!=this)
	{
		// invoke CPGLObject copy assignement operator
		this->CPGLObject::operator=(t);

		m_iAlign=t.m_iAlign;
		m_sText=t.m_sText; 
		m_fAngle=t.m_fAngle;
		if (m_pPosition)
			delete[] m_pPosition;
		m_pPosition=new float[2];
		m_pPosition[0]=t.m_pPosition[0];
		m_pPosition[1]=t.m_pPosition[1];
	}
	return *this;
}

double* CPGLText::GetExtent(CPGLView* pView)
{
	if (NeedUpdateExtent())
		UpdateExtent(pView);

	return CPGLObject::GetExtent(pView);
}

///virtual function to override in derived classes
void CPGLText::UpdateExtent(CPGLView* pView)
{
	// Calling base class first
	CPGLObject::UpdateExtent(pView);

	// SIZE structure
	POINTFLOAT pf;

	pf.x=0;
	pf.y=0;
/*	LOGFONT logFont;
	m_font.GetLogFont(&logFont);
	// getting text extent
	pf=m_font.GetTextExtent(m_sText);
	pf.x*= pView->PixelToWorld(0,abs(logFont.lfHeight));
	pf.y*= pView->PixelToWorld(1,abs(logFont.lfHeight));
*/
	// rotating if necessary
	if (m_fAngle)
	{
		double norm = sqrt(pf.x*pf.x+pf.y*pf.y);
		pf.x = norm * cos( m_fAngle / 180.0 * PGL_PI); 
		pf.y = norm * sin( m_fAngle / 180.0 * PGL_PI); 
	}

	// updating extent...
	switch(m_iAlign)
	{
	case PGL_TEXT_ALIGN_LEFT:
		m_extent[0]=m_pPosition[0];
		m_extent[1]=m_pPosition[0]+pf.x;
		break;
	case PGL_TEXT_ALIGN_RIGHT:
		m_extent[0]=m_pPosition[0]-pf.x;
		m_extent[1]=m_pPosition[0];
		break;
	case PGL_TEXT_ALIGN_CENTER:
		m_extent[0]=m_pPosition[0]-pf.x/2;
		m_extent[1]=m_pPosition[0]+pf.x/2;
		break;
	}

	m_extent[2]=m_pPosition[1];
	m_extent[3]=m_pPosition[1]+pf.y;
}

void CPGLText::SetAlign(int iAlign)
{
	ASSERT( (iAlign==PGL_TEXT_ALIGN_LEFT)
		|| (iAlign==PGL_TEXT_ALIGN_RIGHT)
		|| (iAlign==PGL_TEXT_ALIGN_CENTER));
	m_iAlign=iAlign;
}

void CPGLText::PlotGfx(gfxinterface::CGfxInterface& gfx)
{
	if (!IsVisible())
		return;

	// calling base class plot
	CPGLObject::PlotGfx(gfx);

	gfx.AddComment("--- CPGLText ---");	

	// setting font...
	m_font.SetFontGfx(gfx);

	// writing down text...
	// text
	switch(m_iAlign)
	{
	case PGL_TEXT_ALIGN_LEFT:
		gfx.DrawTextLeft(m_pPosition[0],m_pPosition[1],(LPCSTR)m_sText,m_fAngle);
		break;
	case PGL_TEXT_ALIGN_RIGHT:
		gfx.DrawTextRight(m_pPosition[0],m_pPosition[1],(LPCSTR)m_sText,m_fAngle);
		break;
	case PGL_TEXT_ALIGN_CENTER:
		gfx.DrawTextCenter(m_pPosition[0],m_pPosition[1],(LPCSTR)m_sText,m_fAngle);
		break;
	}
}

void CPGLText::AddPropertyPage(CPropertySheet* pPropSheet)
{
	ASSERT_VALID(pPropSheet);
	// call own functions
	CPGLTextPropPage* propPage=new CPGLTextPropPage(this);
	pPropSheet->AddPage(propPage);

	// first call base class function
	CPGLObject::AddPropertyPage(pPropSheet);
}
