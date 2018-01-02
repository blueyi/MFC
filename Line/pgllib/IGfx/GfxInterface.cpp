// GfxInterface.cpp: implementation of the CGfxInterface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GfxInterface.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace gfxinterface
{

CGfxInterface::CGfxInterface()
{
	m_rCurClip.left=m_rCurClip.top=m_rCurClip.width=m_rCurClip.height=0;
}

CGfxInterface::~CGfxInterface()
{
	ASSERT(m_lClips.empty());
}

void CGfxInterface::BeginPaint()
{
	m_rBoundingBox=m_rMainBoundingBox;

	m_rCurClip=m_rWorldBoundingBox;
}

void CGfxInterface::EndPaint()
{
	m_rBoundingBox = m_rMainBoundingBox;
}

bool CGfxInterface::SetMainBoundingBox(const CRect rect)
{
	m_rMainBoundingBox.left=rect.left;
	m_rMainBoundingBox.top=rect.bottom;
	m_rMainBoundingBox.width=rect.Width();
	m_rMainBoundingBox.height=rect.Height();

	return true;
}

bool CGfxInterface::SetMainBoundingBox(int llx, int lly, int urx, int ury)
{
	if ((llx>=urx) || (lly>=ury))
		return false;

	m_rMainBoundingBox.left=llx;
	m_rMainBoundingBox.top=ury;
	m_rMainBoundingBox.width=urx-llx;
	m_rMainBoundingBox.height=ury-lly;
	ASSERT(m_rMainBoundingBox.width>=0);
	ASSERT(m_rMainBoundingBox.height>=0);

	return SetBoundingBox(llx,lly,urx,ury);
}

bool CGfxInterface::SetBoundingBox(int llx, int lly, int urx, int ury)
{
	if ((llx>=urx) || (lly>=ury))
		return false;

	m_rBoundingBox.left=llx;
	m_rBoundingBox.top=ury;
	m_rBoundingBox.width=urx-llx;
	m_rBoundingBox.height=ury-lly;
	ASSERT(m_rBoundingBox.width>=0);
	ASSERT(m_rBoundingBox.height>=0);

	return true;
}

bool CGfxInterface::SetWorldBoundingBox(double llx, double lly, double urx, double ury)
{
	if ((llx>=urx) || (lly>=ury))
		return false;

	m_rWorldBoundingBox.left=llx;
	m_rWorldBoundingBox.top=ury;
	m_rWorldBoundingBox.width=urx-llx;
	m_rWorldBoundingBox.height=ury-lly;

	return true;
}



void CGfxInterface::GetDefaultLOGFONT(LOGFONT& lf)
{
	lf.lfHeight=8;
	lf.lfWidth=0;
	lf.lfEscapement=0;
	lf.lfOrientation=0;
	lf.lfWeight=FW_NORMAL;
	lf.lfItalic=FALSE;
	lf.lfUnderline=FALSE;
	lf.lfStrikeOut=FALSE;
	lf.lfCharSet=ANSI_CHARSET;
	lf.lfOutPrecision=OUT_TT_PRECIS;
	lf.lfClipPrecision=CLIP_DEFAULT_PRECIS;
	lf.lfQuality=ANTIALIASED_QUALITY;
	lf.lfPitchAndFamily=FF_DONTCARE|DEFAULT_PITCH;
}


};