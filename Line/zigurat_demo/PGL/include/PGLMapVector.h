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
// PGLMapVector.h: interface for the CPGLMapVector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PGLMAPVECTOR_H__70867AFB_7D0F_4F2B_8187_6103E59B8EAA__INCLUDED_)
#define AFX_PGLMAPVECTOR_H__70867AFB_7D0F_4F2B_8187_6103E59B8EAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PGLMap.h"

/*! \brief A vector filed on evenly spaced lattice.

\ingroup PGLMapGroup
This objects implement a vector field.

\image html vectorf.png "A vector field"
\image latex vectorf.eps "A vector filed"
*/
class PGL_EXT_CLASS CPGLMapVector : public CPGLMap  
{
DECLARE_SERIAL(CPGLMapVector);
public:
	/**@name Members*/
	//@{
	CPGLMapVector();
	CPGLMapVector(const CPGLMapVector& l);
	/// assignment constructor
	CPGLMapVector& operator = (const CPGLMapVector& l);
	/// returns a pointer to a copy of the object
	CPGLObject* MakeCopy()
	{	CPGLObject* pCopy=new CPGLMapVector(*this); return pCopy; };
	/// destructor
	~CPGLMapVector();

	/// adds context menu items...
	virtual void AddContextMenuItems(CMenu* pMenu);
	/// adds the line property page to the property sheet dialog.
	virtual void AddPropertyPage(CPropertySheet *pPropSheet);

    /// plotting function. @see CPGLGraph::plot
	/// plot to eps
	virtual void PlotGfx(gfxinterface::CGfxInterface& gfx);

	/// sets the array $V_x$ must be of size $n_x \times n_y$. Memory deallocation is done by PGL
	void SetDatas(double* pVx, double* pVy);
	/// sets the array $V_x$ must be of size $n_x \times n_y$. PGL makes own copy of data.
	void SetDatas(const std::vector<double>& pVx, const std::vector<double>&  pVy);
	/// sets the linewidth
	void SetLineWidth(float lw)
	{	m_fLineWidth=__max(0.5f,lw);};

	/// returns a pointer to the array $V_x$
	double* GetVx()
	{	return m_pVx;};
	/// returns a pointer to the array $V_y$
	double* GetVy()
	{	return m_pVy;};
	/// returns minimum value of Z
	double GetNormMin() const
	{	return m_dNormMin;};
	/// returns maximum value of Z
	double GetNormMax() const
	{	return m_dNormMax;};
	float GetLineWidth() const
	{	return m_fLineWidth;};

	/// Serialize functions
	void Serialize(CArchive& archive);

	/// Debuggin functions
	#ifdef _DEBUG
	    virtual void Dump( CDumpContext& dc ) const;
	    virtual void AssertValid() const;   
	#endif
	//@}
protected:
	float m_fLineWidth;
    /**@name Attributes*/
    //@{
	/// $v_x$, array of $n_x \times n_y$
	double* m_pVx;
	/// $v_y$, array of $n_x \times n_y$
	double* m_pVy;
	//@}
private:
    /**@name Private Attributes*/
    //@{ 
	/// minimum of $\|(x,y)\|_2$
	double m_dNormMin;
	/// maximum of $\|(x,y)\|_2$
	double m_dNormMax;
	//@}
};

#endif // !defined(AFX_PGLMAPVECTOR_H__70867AFB_7D0F_4F2B_8187_6103E59B8EAA__INCLUDED_)
