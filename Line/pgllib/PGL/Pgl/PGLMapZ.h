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
// PGLMapZ.h: interface for the CPGLMapZ class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PGLMAPZ_H__9EF2A9DB_774D_4001_99FD_B4C7219CE7F3__INCLUDED_)
#define AFX_PGLMAPZ_H__9EF2A9DB_774D_4001_99FD_B4C7219CE7F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PGLMap.h"
#include "PGLUtility.h"	// Added by ClassView

/*! \brief A height map on evenly spaced lattice.

\ingroup PGLMapGroup
*/
class PGL_EXT_CLASS CPGLMapZ : public CPGLMap  
{
DECLARE_SERIAL(CPGLMapZ);
public:
	/**@name Members*/
	//@{
	CPGLMapZ();
	//! copy constructor
	CPGLMapZ(const CPGLMapZ& l);
	//! assignment constructor
	CPGLMapZ& operator = (const CPGLMapZ& l);
	//i returns a pointer to a copy of the object
	virtual CPGLObject* MakeCopy()
	{	CPGLObject* pCopy=new CPGLMapZ(*this); return pCopy; };
	//! destructor
	~CPGLMapZ();

	//! adds context menu items...
	virtual void AddContextMenuItems(CMenu* pMenu);
	//! adds the line property page to the property sheet dialog.
	virtual void AddPropertyPage(CPropertySheet *pPropSheet);

    /*! \brief plotting function

	Plots the height map using the current colormap.

	\param pDC a valid devied context associated to the current OpenGL context.
	\param pView a valid view
	\param renderToSelect if TRUE, the object ID is loaded in the OpenGL name pile
	  \sa CPGLGraph::Plot
	  \sa PlotToEPS
	  \sa glLoadName
	*/
    /*! \brief export to EPS

	Plots the height map using the current colormap in an open EPS file.

	\param pFile a valid open file (text mode)
	\param pView a valid view
	  \sa CPGLGraph::Plot
	  \sa PlotToEPS
	  \sa glLoadName
	*/
	virtual void PlotGfx(gfxinterface::CGfxInterface& gfx);

	//! sets the array z must be of size $n_x \times n_y$. Memory deallocation is done by PGL
	void SetDatas(double* pZ);
	//! sets the array z must be of size $n_x \times n_y$. It makes it's own copy.
	void SetDatas(const std::vector<double>& pZ);
	//! returns a pointer to the array z
	double* GetDatas()
	{	return m_pZ;};
	//! returns minimum value of Z
	double GetMin() const
	{	return m_dMin;};
	//! returns maximum value of Z
	double GetMax() const
	{	return m_dMax;};
	/*! \brief returns colormap type

	Returns the type of color maps.
	\sa PGL_COLORMAP
	*/
	PGL_COLORMAP GetColorMap() const
	{	return m_eCMap;};
	//! set the type of colormap
	void SetColorMap(PGL_COLORMAP eCMap)
	{	m_eCMap=eCMap;};

	//! Serialize functions
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
	//! an array \f$n_x \times n_y\f$
	double* m_pZ;
	//! color map
	PGL_COLORMAP m_eCMap;
	//@}
private:
    /**@name Private Attributes*/
    //@{ 
	//! \f$\min z(x,y)\f$
	double m_dMin;
	//! \f$\max z(x,y)\f$
	double m_dMax;
	//@}
};

#endif // !defined(AFX_PGLMAPZ_H__9EF2A9DB_774D_4001_99FD_B4C7219CE7F3__INCLUDED_)
