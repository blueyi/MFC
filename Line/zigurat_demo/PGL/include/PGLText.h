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
// TextGL.h: interface for the CPGLText class.
//
////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTGL_H__4DACBB86_9EFC_11D4_8A95_D4B14EEC3D7F__INCLUDED_)
#define AFX_TEXTGL_H__4DACBB86_9EFC_11D4_8A95_D4B14EEC3D7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PGLObject.h"

/*! 
	\defgroup PGLTextGroup Texts, axes.
	\ingroup PGLObjectGroup
*/

/*! \brief A text object.

\ingroup PGLTextGroup
A text associated to a font.
*/
class PGL_EXT_CLASS CPGLText : public CPGLObject  
{
	DECLARE_SERIAL(CPGLText);
public:

	//!  default constructor
	CPGLText(const CString& _text=CString(),int _fontID=-1);
	//!  copy constructor
	CPGLText(const CPGLText& t);
	// assignement contructor
	CPGLText& operator=(const CPGLText& t);
	//!  returns a pointer to a copy of the object
	virtual CPGLObject* MakeCopy()
	{	CPGLObject* pCopy=new CPGLText(*this); return pCopy; };
	//!  destructor
	virtual ~CPGLText(){ delete[] m_pPosition;};

	/*! \brief returns the bounding box

	\param pDC pointer to current DC
	\param pView pointer to current view
	\retval min(x), __max(x), min(y), __max(y)
	\sa CPGLObject::GetExtent
	*/
	virtual double* GetExtent(CPGLView* pView);
	/*! Computes bounding box */
	virtual void UpdateExtent(CPGLView* pView);

	// properties
	virtual void AddPropertyPage(CPropertySheet* pPropSheet);

	//! return the font pointer
	CPGLFont& GetFont() {	return m_font;};
	const CPGLFont& GetFont() const {	return m_font;};

	// accessing attributes
	void SetString(const CString& _text){m_sText=_text;};
	void SetPosition(const float* _position){m_pPosition[0]=_position[0]; m_pPosition[1]=_position[1];};
	const CString& GetString() const { return m_sText;};
	float* GetPosition() const { return m_pPosition;};
	void SetAngle( float angle)
	{	m_fAngle = angle - ((int)floor(angle/360) )*360;};
	float GetAngle() const
	{	return m_fAngle;};

	int GetAlign() const
	{	return m_iAlign;};
	void SetAlign(int iAlign);
	// plotting
	virtual void PlotGfx(gfxinterface::CGfxInterface& gfx);

	void GetTextExtent(double& width, double& height)
	{	width=m_extent[1]-m_extent[0]; height=m_extent[4]-m_extent[3];};

	// Serialize functions
	void Serialize(CArchive& archive);

	// Debuggin functions
	#ifdef _DEBUG
	    virtual void Dump( CDumpContext& dc ) const;
	    virtual void AssertValid() const;    // Override
	#endif

protected:
	//!  pointer to font
	CPGLFont m_font;
	//! align type : left, center, right
	int m_iAlign;
	//! text
	CString m_sText;
	//! position
	float* m_pPosition;
	//! Angle ( counter clock-wize starting at 0 = horizontal) in DEGRES !
	float m_fAngle;
};

#endif // !defined(AFX_TEXTGL_H__4DACBB86_9EFC_11D4_8A95_D4B14EEC3D7F__INCLUDED_)
