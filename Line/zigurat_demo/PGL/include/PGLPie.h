/*
Plot Graphic Library,
a C++/MFC charting library.

  Copyright (C) 2001  Jens Scheidtmann

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

Contact: Jens Scheidtmann <grimaldi@users.sourceforge.net>
*/
// PGLPie.h: interface for the CPGLPie class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PGLPIE_H__8D63690A_E25F_4D15_B3C4_F7BFBDA15B34__INCLUDED_)
#define AFX_PGLPIE_H__8D63690A_E25F_4D15_B3C4_F7BFBDA15B34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PGLObject.h"

/*!
	\ingroup PGLObjectGroup
*/

/*! \brief A Pie plot Object.

*/
class PGL_EXT_CLASS CPGLPie : public CPGLObject  
{
DECLARE_SERIAL(CPGLPie);
public:
	/**@name Members*/
	//@{
	CPGLPie();
	CPGLPie(const CPGLPie& r);
	/// assignment constructor
	CPGLPie& operator = (const CPGLPie& r);
	/// returns a pointer to a copy of the object
	virtual CPGLObject* MakeCopy()
	{	CPGLObject* pCopy=new CPGLPie(*this); return pCopy; };
	/// destructor
	virtual ~CPGLPie() {};

    /** returns the extent of the datas
    The array extent is filled like this :
    \begin{itemize}
        \item extent[0] : min(x)
        \item extent[1] : __max(x)
        \item extent[2] : min(y)
        \item extent[3] : __max(y)
    \end{itemize}
    */
    virtual double* GetExtent(CPGLView* pView);
    ///virtual function to override in derived classes
    virtual void UpdateExtent(CPGLView* pView);

	/// plot using OpenGL

	/// adds context menu items...
	//virtual void AddContextMenuItems(CMenu* pMenu);
	/// adds the line property page to the property sheet dialog.
	//virtual void AddPropertyPage(CPropertySheet *pPropSheet);
	/// plot to eps
	virtual void PlotGfx(gfxinterface::CGfxInterface& gfx);

	/// Serialize functions
	void Serialize(CArchive& archive);

	/// Debuggin functions
	#ifdef _DEBUG
	    virtual void Dump( CDumpContext& dc ) const;
	    virtual void AssertValid() const;   
	#endif
	//@}
protected:
};

#endif // !defined(AFX_PGLPIE_H__8D63690A_E25F_4D15_B3C4_F7BFBDA15B34__INCLUDED_)
