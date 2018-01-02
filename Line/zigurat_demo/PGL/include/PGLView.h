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
// viewGL.h: interface for the CPGLView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PGLVIEW_H__338966C8_1C93_11D4_8D89_00409503B978__INCLUDED_)
#define AFX_PGLVIEW_H__338966C8_1C93_11D4_8D89_00409503B978__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*!
	\defgroup PGLViewGroup Views : 2D view, 3D view.
	\ingroup PGLGroup
*/

/*! \brief A class that defines a view.

\ingroup PGLViewGroup
This class is used as a base to build 2D and 3D views. These
views will be used with OpenGL.
*/
class PGL_EXT_CLASS CPGLView : public CObject
{
DECLARE_SERIAL(CPGLView);

public:

    CPGLView(int _iTx=0,int _iTy=0,int _iWidth=1,int _iHeight=1);
    CPGLView(const CPGLView& v);
    CPGLView& operator= (const CPGLView& v);

    ~CPGLView(){};
    /**@name Class Members*/
    //@{
    /// sets the viewport characteristics
    virtual void SetViewport(int _iTx,int _iTy,int _iWidth,int _iHeight)
    {   m_iTx=_iTx; m_iTy=_iTy; m_iWidth=_iWidth; m_iHeight=_iHeight;};

    /// pan the view of $x$ pixels horizontaly and $y$ pixels verticaly
    virtual void Pan(int x,int y){};
    /// zooms in
    virtual void ZoomIn(){};
    /// zooms out
    virtual void ZoomOut(){};
    /// zooming extent of view
    virtual void ZoomAll(double _left, double _right, double _bottom, double _top){};
    /// zoom the region of the screen describe by the 2 points $(xStart, yStart, xEnd, yEnd)$
    virtual void ZoomBox(int xStart,int yStart,int xEnd,int yEnd){};
    /// draws a white rectangle whose opposite corner are $(x_1,y_1)$ and $(x_2,y_2)$
    virtual void DrawBox(int x1,int y1, int x2, int y2){};
    virtual void DrawBackground(){};
    /// returns the height of the viewport
    int GetHeight() const
    { return m_iHeight;};
    /// returns the width of the viewport
    int GetWidth() const
    { return m_iWidth;};
    /// returns the lower left corner x-coordinate of the viewport
    int GetTx() const
    { return m_iTx;};
    /// returns the lower left corner y-coordinate of the viewport
    int GetTy() const
    { return m_iTy;};

    virtual void PlotGfx(gfxinterface::CGfxInterface& gfx);

    virtual double PixelToWorld(int iaxe, int pix)
    {   return 0.0;};
    virtual double PixelToWorldCoord(int iaxe, int pix)
    {   return 0.0;};
    virtual double PixelToWorld(int iaxe, double pix)
    {   return 0.0;};
    virtual double PixelToWorldCoord(int iaxe, double pix)
    {   return 0.0;};

    /// Serialization
    void Serialize( CArchive& archive );

    /// Debuggin functions
#ifdef _DEBUG
    virtual void Dump( CDumpContext& dc ) const;
    virtual void AssertValid() const;    // Override
#endif

    //@}
protected:
    /**@name Class Parameters*/
    //@{
    /// lower left corner x-coordinate of the viewport
    int m_iTx;
    /// lower left corner y-coordinate of the viewport
    int m_iTy;
    /// width of the viewport (in pixels)
    int m_iWidth;
    /// height of the viewport (in pixels)
    int m_iHeight;
    //@}
};

#endif // !defined(AFX_VIEWCLASS_H__338966C8_1C93_11D4_8D89_00409503B978__INCLUDED_)
