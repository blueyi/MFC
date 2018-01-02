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
// LineGL.h: interface for the CPGLLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINEGL_H__4DACBB76_9EFC_11D4_8A95_D4B14EEC3D7F__INCLUDED_)
#define AFX_LINEGL_H__4DACBB76_9EFC_11D4_8A95_D4B14EEC3D7F__INCLUDED_

#include "PGLObject.h"
#include "GfxInterface.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*! \defgroup PGLLineGroup Lines and curves
\ingroup PGLObjectGroup
*/

/*! \brief A generic line class. 

\ingroup PGLLineGroup
This is the base class for 2D and 3D curves. It holds all the carateristics of these lines :
<ul>
	<li><b>Point type:</b> There are 1 different shapes of points :
	The corresponding constants are 
	<ul>
		<li> #PGL_POINT_NONE : no point
		<li> #PGL_POINT_SIMPLE : circle
		<li> #PGL_POINT_CONTOUR : a circle
		<li> #PGL_POINT_TRIANGLE : a triangle
		<li> #PGL_POINT_SQUARE : a square
	</ul>
	<li><b>Point width:</b> the point width in pixels
	<li><b>Line type:</b> There are three different patterns, continuous, stippled and dot stippled.
	The corresponding constants are 
	<ul>
		<li> #PGL_LINE_NONE : no line
		<li> #PGL_LINE_CONT : -------
		<li> #PGL_LINE_BARBAR : - - - -
		<li> #PGL_LINE_BARPOINT : -.-.-.
	</ul>
	<li><b>Line width:</b> the line width in pixels
	<li><b>Interpolation type:</b> There are 3 different interpolation methods : piece wize linear or NURBS
	The corresponding constants are 
	<ul>
		<li> #PGL_INTERPOLATION_STEP : steps
		<li> #PGL_INTERPOLATION_LINEAR : linestrip between points
		<li> #PGL_INTERPOLATION_SEGMENT : linesegments
	</ul>	
</ul>
*/
class PGL_EXT_CLASS CPGLLine : public CPGLObject
{
DECLARE_SERIAL(CPGLLine);
public:

	void SetDashGfx(gfxinterface::CGfxInterface& gfx);

	/** \name Class Members*/
	//@{
	//! default constructor
	CPGLLine(UINT _iInterpolationType=PGL_INTERPOLATION_LINEAR,UINT _iPointType=PGL_POINT_NONE,UINT _iLineType=PGL_LINE_CONT,const CPGLColor& _color=CPGLColor());
	//! copy constructor
	CPGLLine(const CPGLLine& l);
	//! assignment constructor
	CPGLLine& operator = (const CPGLLine& l);
	//! returns a pointer to a copy of the object
	virtual CPGLObject* MakeCopy()
	{	CPGLObject* pCopy=new CPGLLine(*this); return pCopy; };
	//! destructor
	virtual ~CPGLLine() {};

	//! adds context menu items...
	virtual void AddContextMenuItems(CMenu* pMenu);
	//! adds the line property page to the property sheet dialog.
	virtual void AddPropertyPage(CPropertySheet *pPropSheet);

	//! returns the interpolation type
	UINT GetInterpolationType() const	{ return m_iInterpolationType;};
	//! returns the point type
	UINT GetPointType()  const			{ return m_iPointType;};
	//! returns the Line type 
	UINT GetLineType() const			{ return m_iLineType;};
	//! returns the point width
	float GetPointWidth() const { return m_fPointWidth;};
	//! returns the line width 
	float GetLineWidth() const { return m_fLineWidth;};
	//! returns number of points in multiple line strip
	UINT GetStripSize() const {	return m_iStripSize;};
	//! Sets the strip size for multiple strip mode
	void SetStripSize(UINT size) {	m_iStripSize = __max(2, size);};


	/*! \brief sets the interpolation type

	\a _iInterpolationType must be one of the following constants :
	<ul>
		<li> #PGL_INTERPOLATION_STEP : steps
		<li> #PGL_INTERPOLATION_LINEAR : lines between points
		<li> #PGL_INTERPOLATION_SEGMENT : multiple line strip
	</ul>	
	@see GetInterpolationType
	*/
	inline void SetInterpolationType(UINT _iInterpolationType);

	/*! \brief sets the point type

	\a _iPointType must be one of the following constants :
	<ul>
		<li> #PGL_POINT_NONE : no point
		<li> #PGL_POINT_SIMPLE : a filled circle
		<li> #PGL_POINT_CONTOUR: a circle
		<li> #PGL_POINT_TRIANGLE: a triangle
		<li> #PGL_POINT_SQUARE: a square
	</ul>
	@see GetPointType
	*/
	inline void SetPointType(UINT _iPointType);
	/*! \brief sets the line type

	\a _iLineType must be one of the following constants :
	<ul>
		<li> #PGL_LINE_NONE : no line
		<li> #PGL_LINE_CONT : -------
		<li> #PGL_LINE_BARBAR : - - - -
		<li> #PGL_LINE_BARPOINT :-:-:-:
	</ul>
	@see GetLineType
	*/
	inline void SetLineType(UINT _iLineType);
	//! sets the point width (in pixels)
	void SetPointWidth(float _fPointWidth) {m_fPointWidth=(float)__max(0.0,_fPointWidth);}; 
	//! sets the line width (in pixels)
	void SetLineWidth(float _fLineWidth){m_fLineWidth=(float)__max(0.0,_fLineWidth);};


	void SetFilled(BOOL fill = TRUE)
	{	m_bFilled = fill;};
	BOOL IsFilled() const
	{	return m_bFilled;};

	virtual void PlotGfx(gfxinterface::CGfxInterface& gfx);

	//! Serialize functions
	void Serialize(CArchive& archive);

	//! Debuggin functions
	#ifdef _DEBUG
	    virtual void Dump( CDumpContext& dc ) const;
	    virtual void AssertValid() const;   
	#endif
protected:
	virtual void PlotLineStripGfx(gfxinterface::CGfxInterface& gfx) {ASSERT(FALSE);};
	virtual void PlotPointStripGfx(gfxinterface::CGfxInterface& gfx){ASSERT(FALSE);};
	virtual void PlotArrowsGfx(gfxinterface::CGfxInterface& gfx){ASSERT(FALSE);};
	//@}
	/*! \name Class Parameters*/
	//@{
	UINT m_iInterpolationType;
	UINT m_iPointType;
	UINT m_iLineType;
	float m_fLineWidth;
	float m_fPointWidth;
	BOOL m_bFilled;
	UINT m_iStripSize;
	//@}
};

inline void CPGLLine::SetInterpolationType(UINT _iInterpolationType)
{
	// testing if it exist, if so value is changed
	switch(_iInterpolationType)
	{
	case PGL_INTERPOLATION_STEP:
	case PGL_INTERPOLATION_LINEAR:
	case PGL_INTERPOLATION_SEGMENT:
		m_iInterpolationType=_iInterpolationType;
		break;
	}
}

inline void CPGLLine::SetPointType(UINT _iPointType)
{
	// testing if it exist, if so value is changed
	switch(_iPointType)
	{
	case PGL_POINT_NONE:
	case PGL_POINT_SIMPLE:
	case PGL_POINT_CONTOUR:
	case PGL_POINT_TRIANGLE:
	case PGL_POINT_SQUARE:
		m_iPointType=_iPointType;
		break;
	}
}

inline void CPGLLine::SetLineType(UINT _iLineType)
{
	// testing if it exist, if so value is changed
	switch(_iLineType)
	{
	case PGL_LINE_NONE:
	case PGL_LINE_CONT:
	case PGL_LINE_BARBAR:
	case PGL_LINE_BARPOINT:
	case PGL_LINE_POINTPOINT:
		m_iLineType=_iLineType;
		break;
	}
}

#endif // !defined(AFX_LINEGL_H__4DACBB76_9EFC_11D4_8A95_D4B14EEC3D7F__INCLUDED_)
