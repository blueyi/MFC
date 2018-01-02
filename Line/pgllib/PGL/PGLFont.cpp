// PGLFont.cpp: implementation of the CPGLFont class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "PGL/PGL.h"
#include "PGL/PGLFont.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CPGLFont,CObject,1);

void CPGLFont::Serialize(CArchive &archive)
{
    // call base class function first
    // base class is CFont in this case
    CObject::Serialize( archive );

	if( archive.IsStoring() )
	{
	}
	else
	{
	}	
}

#ifdef _DEBUG
void CPGLFont::Dump( CDumpContext& dc ) const
{
    // call base class function first
    CObject::Dump( dc );

	// now dumping..
	dc << _T("--- CPGLFont ---") <<endl;
}

void CPGLFont::AssertValid() const
{
    // call inherited AssertValid first
    CObject::AssertValid();
} 
#endif


CPGLFont::CPGLFont()
{
	m_lf.lfHeight=8;
	m_lf.lfWidth=0;
	m_lf.lfEscapement=0;
	m_lf.lfOrientation=0;
	m_lf.lfWeight=FW_NORMAL;
	m_lf.lfItalic=FALSE;
	m_lf.lfUnderline=FALSE;
	m_lf.lfStrikeOut=FALSE;
	m_lf.lfCharSet=ANSI_CHARSET;
	m_lf.lfOutPrecision=OUT_TT_PRECIS;
	m_lf.lfClipPrecision=CLIP_DEFAULT_PRECIS;
	m_lf.lfQuality=ANTIALIASED_QUALITY;
	m_lf.lfPitchAndFamily=FF_DONTCARE|DEFAULT_PITCH;
}

CPGLFont::~CPGLFont()
{
}

void CPGLFont::SetFontGfx(gfxinterface::CGfxInterface& gfx)
{
	// getting information on font
	gfx.SetFont(abs(m_lf.lfHeight));
}

POINTFLOAT CPGLFont::GetTextExtent(const CString &string)
{
	POINTFLOAT pf;

	pf.x=0;
	pf.y=0;
	return pf;
}
