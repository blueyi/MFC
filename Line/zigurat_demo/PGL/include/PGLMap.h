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
// PGLMap.h: interface for the CPGLMap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PGLMAP_H__8D63690A_E25F_4D15_B3C4_F7BFBDA15B34__INCLUDED_)
#define AFX_PGLMAP_H__8D63690A_E25F_4D15_B3C4_F7BFBDA15B34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PGLObject.h"

/*!
	\defgroup PGLMapGroup Maps, surfaces and vector fields.
	\ingroup PGLObjectGroup
*/

/*! \brief A 2D Map with regular base lattice.

\ingroup PGLMapGroup

\image html map.png "Grid description"
\image latex map.eps "Grid description"

*/
class PGL_EXT_CLASS CPGLMap : public CPGLObject  
{
DECLARE_SERIAL(CPGLMap);
public:
	void SetGrid(int iaxe, int iNPoints, double pos0, double step);
	/**@name Members*/
	//@{
	CPGLMap();
	CPGLMap(const CPGLMap& l);
	/// assignment constructor
	CPGLMap& operator = (const CPGLMap& l);
	/// returns a pointer to a copy of the object
	virtual CPGLObject* MakeCopy()
	{	CPGLObject* pCopy=new CPGLMap(*this); return pCopy; };
	/// destructor
	virtual ~CPGLMap() {};

    /** returns the extent of the datas
    The array extent is filled like this :
    <ul>
        <li> extent[0] : min(x)
        <li> extent[1] : __max(x)
        <li> extent[2] : min(y)
        <li> extent[3] : __max(y)
    </ul>
    */
    virtual double* GetExtent(CPGLView* pView);
    ///virtual function to override in derived classes
    virtual void UpdateExtent(CPGLView* pView);

	/// adds context menu items...
	virtual void AddContextMenuItems(CMenu* pMenu);
	/// adds the line property page to the property sheet dialog.
	virtual void AddPropertyPage(CPropertySheet *pPropSheet);
	/// plot to eps
	virtual void PlotGfx(gfxinterface::CGfxInterface& gfx);

	//! returns $n_x$
	int GetNx() const
	{	return m_iNx;};
	//! returns $n_y$
	int GetNy() const
	{	return m_iNy;};

	//! returns $d_x$
	double GetDx() const
	{	return m_dDx;};
	//! returns $d_y$
	double GetDy() const
	{	return m_dDy;};
	//! returns $x_0$
	double GetX0() const
	{	return m_dX0;};
	//! returns $y_0$
	double GetY0() const
	{	return m_dY0;};
	
	void SetDx(double _dDx);
	void SetDy(double _dDy);
	void SetX0(double _dX0)
	{	m_dX0 = _dX0;  PostUpdateExtent();};
	void SetY0(double _dY0)
	{	m_dY0 = _dY0;	PostUpdateExtent();};

	/// Serialize functions
	void Serialize(CArchive& archive);

	/// Debuggin functions
	#ifdef _DEBUG
	    virtual void Dump( CDumpContext& dc ) const;
	    virtual void AssertValid() const;   
	#endif
	//@}
protected:
	/**@name Attributes*/
	//@{
	/// number of points in y direction
	int m_iNx;
	/// number of points in x direction
	int m_iNy;
	/// spatial step in x direction
	double m_dDx;
	/// spatial step in y direction
	double m_dDy;
	/// left position
	double m_dX0;
	/// bottom position
	double m_dY0;
	//@}
};

#endif // !defined(AFX_PGLMAP_H__8D63690A_E25F_4D15_B3C4_F7BFBDA15B34__INCLUDED_)
