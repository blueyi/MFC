// PGLLine2DLOD.h: interface for the CPGLLine2DLOD class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PGLLINE2DLOD_H__56F09710_E27C_452B_A49B_78D72EAA6CB2__INCLUDED_)
#define AFX_PGLLINE2DLOD_H__56F09710_E27C_452B_A49B_78D72EAA6CB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PGLLine2D.h"

/*! \brief A 2D curve class with Level of Detail capabilities

\ingroup PGLLineGroup

 The curve is represented by a serie of points, wich are given by the user.
All the memory handling is taken care of by PGL.

The user sets a tolerance parameter for the approximated curve. The apprimation
algorithm is based on Douglas-Peukler algorithm. The DP line simplification algorithm was originaly proposed in [1]. 
John Hershberger and Jack Snoeyink have implemented it in C in [2] as a package named DPSimp:

<em>DPsimp is a Douglas-Peucker line simplification alogorithm implementation 
by John Hershberger and Jack Snoeyink. They analyze the line simplification 
algorithm reported by Douglas and Peucker and show that its worst case is quadratic in n, the number of input points. The algorithm is based on path hulls, that uses the geometric structure of the problem to attain a worst-case running time proportional to nlog_2(n), which is the best case of the Douglas algorithm.
</em>

\b Example: How to plot a function f(x) ?
<ol>
<li>Generate pair of points (x,f(x))
\code
int nPoints= // number of poitns
double* pX=new double[nPoints];
double* pY=new double[nPoints];

// Generating data
for (int i=0;i<nPoints;i++)
{
    pX[i]= // put your function here
    pY[i]= // put your function here
}
\endcode
<li> Create line CPGLLine2DLOD object and assign data to it.
\code
	CPGLLine2DLOD* pLine2DLOD=new CPGLLine2DLOD();
	pLine2D->SetDatas(nPoints, pX,pY);
\endcode
<li>Change tolerance parameter:
\code 
	pLine2DLOD->SetTol(0.0001);
\endcode
<li>Add this line a CPGLGraph object.
	CPGLGraph* pGraph;
	...
	pGraph->AddObject(pLine2DLOD);
</ol>

\b Reference:
<ul>
<li>[1] D. H. Douglas and T. K. Peucker. Algorithms for the reduction of the number of points required to represent a line or its caricature. The Canadian Cartographer, 10(2):112--122, 1973.
<li>[2] J. Hershberger and J. Snoeyink. Speeding up the Douglas-Peucker line simplification algorithm. In Proc. 5th Intl. Symp. Spatial Data Handling. IGU Commission on GIS, pages 134--143, 1992. (home page)
</ul>
\sa CPGLLine2D
\sa CPGLLine
\sa CPGLGraph
*/
class PGL_EXT_CLASS CPGLLine2DLOD : public CPGLLine2D  
{
public:
	DECLARE_SERIAL(CPGLLine2DLOD);

    /*! \name Class Members*/
    //@{
    //! default constructor
    CPGLLine2DLOD();
    //! copy constructor
    CPGLLine2DLOD(const CPGLLine2DLOD& l);
    //! assignement constructor
    CPGLLine2DLOD& operator=(const CPGLLine2DLOD& l);
    //! returns a pointer to a copy of the object
    virtual CPGLObject* MakeCopy()
    {   CPGLObject* pCopy=new CPGLLine2DLOD(*this); return pCopy; };
    //! desctructor
	virtual ~CPGLLine2DLOD();

	/// returns a pointer to the hull object
	CDPHull* GetHull()
	{	return &m_hull;};
	/// Sets the tolerance of approximation
	void SetTol(double tol);
	/// return tolerance of approximation
	double GetTol() const
	{	return m_hull.GetTol();};

    //! adds context menu items...
    virtual void AddContextMenuItems(CMenu* pMenu);
    //! adds the Line2D property page to the property dialog
    virtual void AddPropertyPage(CPropertySheet* pPropSheet);

	virtual void SetDatas(int _nPoints, double *_x, double *_y);
	virtual void SetDatas(const std::vector<double>& vx, const std::vector<double>& vy);

    //! plotting to EPS file
    virtual void PlotGfx(gfxinterface::CGfxInterface& gfx);

   virtual void UpdateExtent(CPGLView* pView);

    //! Serialize functions
    void Serialize(CArchive& archive);

    //! Debuggin functions
    #ifdef _DEBUG
        virtual void Dump( CDumpContext& dc ) const;
        virtual void AssertValid() const;    // Override
    #endif
protected:
	virtual void PlotLineStripGfx(gfxinterface::CGfxInterface& gfx);
	virtual void PlotPointStripGfx(gfxinterface::CGfxInterface& gfx);
    //@}
protected:
	CDPHull m_hull;

};

#endif // !defined(AFX_PGLLINE2DLOD_H__56F09710_E27C_452B_A49B_78D72EAA6CB2__INCLUDED_)
