/*
Plot Graphic Library,
a C++/MFC charting library.

  Copyright (C) 2001  de Halleux Jonathan

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

Contact: de Halleux Jonathan, pglinfo@patabelgos.org
*/
// PGLFont.h: interface for the CPGLFont class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PGLFONT_H__83FE3C8D_06FC_4687_9D23_328F0EB68859__INCLUDED_)
#define AFX_PGLFONT_H__83FE3C8D_06FC_4687_9D23_328F0EB68859__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*! \brief A font.

\ingroup PGLTextGroup
A font with OpenGL and EPS connections... bitmap or outline.
You must choose when creating the font bitmap or glyph.
\sa CPGLFontManager
\sa CPGLText
*/
class PGL_EXT_CLASS CPGLFont : public CFont  
{
DECLARE_SERIAL(CPGLFont);

public:
	const LOGFONT& GetLOGFONT() const	{	return m_lf;};
	void SetLOGFONT(const LOGFONT& lf)	{	m_lf=lf;};
	// default constructor, TRUE for bitmap font, FALSE, for glyph font
	CPGLFont();
	virtual ~CPGLFont();

	/// returns the extent the text in screen coorinate
	POINTFLOAT GetTextExtent(const CString& string);
	/// loads the font in the eps file.
	void SetFontGfx(gfxinterface::CGfxInterface& gfx);

	LONG GetHeight() const {	return abs(m_lf.lfHeight);};

	/// Serialize functions
	void Serialize(CArchive& archive);

	/// Debuggin functions
	#ifdef _DEBUG
	    virtual void Dump( CDumpContext& dc ) const;
	    virtual void AssertValid() const;    // Override
	#endif

protected:
	LOGFONT m_lf;
};

#endif // !defined(AFX_PGLFONT_H__83FE3C8D_06FC_4687_9D23_328F0EB68859__INCLUDED_)
