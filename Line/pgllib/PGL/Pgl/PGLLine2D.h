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
// Line2DGL.h: interface for the CPGLLine2D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINE2DGL_H__4DACBB78_9EFC_11D4_8A95_D4B14EEC3D7F__INCLUDED_)
#define AFX_LINE2DGL_H__4DACBB78_9EFC_11D4_8A95_D4B14EEC3D7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PGLLine.h"

/*! \brief A 2D curve class.

\ingroup PGLLineGroup
The curve is represented by a points, wich are given by the user.
All the memory handling is taken care of by PGL.

\b Example: How to plot a function f(x) ?
<ol>
<li>Generate pair of points (x,f(x))
\code
int nPoints; // number of poitns
double* pX=new double[nPoints];
double* pY=new double[nPoints];

// Generating data
for (int i=0;i<nPoints;i++)
{
    pX[i]= // put your function here
    pY[i]= // put your function here
}
\endcode
<li> Create line CPGLLine2D object and assign data to it.
\code
	CPGLLine2D* pLine2D=new CPGLLine2D();
	pLine2D->SetDatas(nPoints, pX,pY);
\endcode
<li>Change characteristics of the line (for example change linewidth):
\code 
	pLine2D->SetLineWidth(2.0f);
\endcode
<li>Add this line a CPGLGraph object.
	CPGLGraph* pGraph;
	...
	pGraph->AddObject(pLine2D);
</ol>


\sa CPGLLine
\sa CPGLGraph
*/
class PGL_EXT_CLASS CPGLLine2D : public CPGLLine  
{
public:
    DECLARE_SERIAL(CPGLLine2D);
    /*! \name Class Members*/
    //@{
    //! default constructor
    CPGLLine2D();
    //! copy constructor
    CPGLLine2D(const CPGLLine2D& l);

    //! assignement constructor
    CPGLLine2D& operator=(const CPGLLine2D& l);

    //! returns a pointer to a copy of the object
    virtual CPGLObject* MakeCopy()
    {   CPGLObject* pCopy=new CPGLLine2D(*this); return pCopy; };

    //! desctructor
	virtual ~CPGLLine2D();

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

    //! adds context menu items...
    virtual void AddContextMenuItems(CMenu* pMenu);
    //! adds the Line2D property page to the property dialog
    virtual void AddPropertyPage(CPropertySheet* pPropSheet);

	//! TRUE if there is an arrow at the beginning of the line
	BOOL IsStartArrow() const
	{	return m_spHeadShow[0];};
	//! TRUE if there is an arrow at the end of the line
	BOOL IsEndArrow() const
	{	return m_spHeadShow[1];};
	//! shows start arrow (default is yes)
	void ShowStartArrow(BOOL show=TRUE)
	{	m_spHeadShow[0]=show;};
	//! shows end arrow (default is yes)
	void ShowEndArrow(BOOL show=TRUE)
	{	m_spHeadShow[1]=show;};
	/*! \brief Get start arrow length

	Returns the start arrow length in pixels.
	\sa GetEndArrowLength
	\sa SetStartArrowLength
	\sa SetEndArrowLength
	\sa IsStartArrow
	\sa IsEndArrow
	*/
	double GetStartArrowLength() const
	{	return m_spHeadLength[0];};
	/*! \brief Get end arrow length

	Returns the end arrow length in pixels.
	\sa GetStartArrowLength
	\sa SetStartArrowLength
	\sa SetEndArrowLength
	\sa IsStartArrow
	\sa IsEndArrow
	*/
	double GetEndArrowLength() const
	{	return m_spHeadLength[1];};
	double GetStartArrowThick() const
	{	return m_spHeadThick[0];};
	double GetEndArrowThick() const
	{	return m_spHeadThick[1];};
	void SetStartArrowLength(double length)
	{	m_spHeadLength[0]=__max(0,length);};
	void SetEndArrowLength(double length)
	{	m_spHeadLength[1]=__max(0,length);};
	void SetStartArrowThick(double thick)
	{	m_spHeadThick[0]=__max(0,thick);};
	void SetEndArrowThick(double thick)
	{	m_spHeadThick[1]=__max(0,thick);};


    //! returns $x(i)$
    double GetXi(int i) const { ASSERT(i>=0 && i<m_iNPoints); return m_pX[i];};
    //! returns $y(i)$
    double GetYi(int i) const { ASSERT(i>=0 && i<m_iNPoints); return m_pY[i];};
    //! returns the number of points
    int GetNPoints() { return m_iNPoints;};
    //! returns a pointer to $x$ array
    double* GetX()
    {   return m_pX;};
    //! returns a pointer to $y$ array
    double* GetY()
    {   return m_pY;};

    //! sets $x(i)$
    void SetXi(int i,double xi) { ASSERT(i>=0 && i<m_iNPoints); m_pX[i]=xi; PostUpdateExtent();};
    //! sets $y(i)$
    void SetYi(int i,double yi) { ASSERT(i>=0 && i<m_iNPoints); m_pY[i]=yi; PostUpdateExtent();};

    /** sets the datas
    It just takes the pointer to the datas so the user can play with it...(use dynamic 
    memory (new))
    Memory cleaning is handled by PGL
    @param \_nPoints number of points
    @param x array of \_nPoints double where m\_pX[i]=$x(i)$
    @param y array of \_nPoints double where m\_pY[i]=$y(i)$
    */
    virtual void SetDatas(int _nPoints,double* _x, double* _y);

    /** sets the datas (makes own copy)
	It makes own copy of the data...
    */
    virtual void SetDatas(const std::vector<double>& vx, const std::vector<double>& vy);

    //! Serialize functions
    void Serialize(CArchive& archive);

    //! Debuggin functions
    #ifdef _DEBUG
        virtual void Dump( CDumpContext& dc ) const;
        virtual void AssertValid() const;    // Override
    #endif
    //@}
protected:

	virtual void PlotArrowsGfx(gfxinterface::CGfxInterface& gfx);
	virtual void PlotLineStripGfx(gfxinterface::CGfxInterface& gfx);
	virtual void PlotPointStripGfx(gfxinterface::CGfxInterface& gfx);

protected:
    /*! \name Attributes*/
    //@{
    //! number of points
    int m_iNPoints;
    //! array of $x(i)$
    double *m_pX;
    //! array of $y(i)$
    double *m_pY;
	//! TRUE if there is a head
	BOOL m_spHeadShow[2];
	//! Head arrow thickness (in pixels)
	double m_spHeadThick[2];
	//! Head arrow length (in pixels)
	double m_spHeadLength[2];
    //@}
};



#endif // !defined(AFX_LINE2DGL_H__4DACBB78_9EFC_11D4_8A95_D4B14EEC3D7F__INCLUDED_)
