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
// viewGL2D.h: interface for the CPGLView2D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PGLVIEW2D_H__338966CB_1C93_11D4_8D89_00409503B978__INCLUDED_)
#define AFX_PGLVIEW2D_H__338966CB_1C93_11D4_8D89_00409503B978__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PGLView.h"

/*! \brief A 2D view.

\ingroup PGLViewGroup
  This type of view is used for 2D graphs or drawings. 
It can handle basic mouse
events, such as zooming and panning
*/
class PGL_EXT_CLASS CPGLView2D : public CPGLView
{
DECLARE_SERIAL(CPGLView2D);

public:
    /**@name Class Members*/
    //@{
    /// default constructor
    CPGLView2D(double _m_dLeft=0.0,double _right=1.0,double _top=1.0,double _bottom=0.0);
    /// copy constructor
    CPGLView2D(const CPGLView2D& v2D);
    /// assignement constructor
    CPGLView2D& operator = (const CPGLView2D& v2D);
    /// destructor
    virtual ~CPGLView2D()
    {};

    /// init all the OpenGL states (blending, culling, smoothing, stipple, etc...)
    void InitGLState();
    /** reconstruct the projection matrice and model matrice
    The new viewport is defined by \_tx, \_tx, \_width et \_height
    */  
    void Reshape();
    /// pans the view of x (resp. y) pixels horizontaly (resp. verticaly)
    void Pan(int x,int y);
    /// zooms in of 25\%
    void ZoomIn();
    /// zooms out of 25\%
    void ZoomOut();
    /// zooms the box defined by the 2 points $(xStart, yStart, xEnd, yEnd)$
    void ZoomBox(int xStart,int yStart,int xEnd,int yEnd);
  //  void DrawBackground(){glRectf((GLfloat)m_dLeft, (GLfloat)m_dBottom, (GLfloat)m_dRight, (GLfloat)m_dTop);};
    /// change the project plane to \_left, \_right, \_top and \_bottom
	void ZoomAll(double _dLeft,double _dRight, double _dBottom, double _dTop);
	/// Plot to Encapsulated postscript
    void PlotGfx(gfxinterface::CGfxInterface& gfx);

	/// coordinate transformation
    double PixelToWorld(int iaxe, int pix);
    double PixelToWorldCoord(int iaxe, int pix);
    double PixelToWorld(int iaxe, double pix);
    double PixelToWorldCoord(int iaxe, double pix);

	double GetLeft() const
	{	return m_dLeft;}
	double GetRight() const
	{	return m_dRight;}
	double GetBottom() const
	{	return m_dBottom;}
	double GetTop() const
	{	return m_dTop;}

    /// Serialization
    void Serialize( CArchive& archive );

    /// Debuggin functions
#ifdef _DEBUG
    virtual void Dump( CDumpContext& dc ) const;
    virtual void AssertValid() const;    // Override
#endif
    //@}
protected:
    /**@name Class Parameter*/
    //@{
    /// left limit of the viewport
    double m_dLeft;
    /// right limit of the viewport
    double m_dRight;
    /// top limit of the viewport
    double m_dTop;
    /// bottom limit of the viewport
    double m_dBottom;
    //@}
};

#endif // !defined(AFX_VIEW2DCLASS1_H__338966CB_1C93_11D4_8D89_00409503B978__INCLUDED_)
