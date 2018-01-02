// LineApproximator.h: interface for the CLineApproximator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINEAPPROXIMATOR_H__F5E6E8DC_1185_4AC0_A061_7B3309700E9D__INCLUDED_)
#define AFX_LINEAPPROXIMATOR_H__F5E6E8DC_1185_4AC0_A061_7B3309700E9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef UINT
	#define UINT unsigned int
#endif

#ifndef ASSERT
	#ifdef _DEBUG
		#define ASSERT(a)	if(!(a)) exit(-1);
	#else
		#define ASSERT(a)
	#endif
#endif

#include <iostream>
#include <vector>
#include <list>
#include <limits>

namespace hull
{

/*! \brief Base class for line approximators

\par Notations:

  - points : data to interpolate
  - keys : selected points from available set that interpolate within the desired tolerance

\par 2D (homogenous) coordinates

Two internal structures are used to do simple computations on 2D points:
	-  SPoint, 2D point, contains classical vectorial functions such as dot product, cross product, etc...
	- SHomog, 2D point + homogenous data

\par Containers:

  - Points are stored in a #PointContainer. #PointContainer is a STL container of SPoint (actually implemented as vector)
  - Keys are stored in a #KeyContainer. #KeyContainer is a STL container of PointContainer::const_iterator 

\par Data normalization:

  To avoid numerical instability when computing cross product and so, data is normalized ( see #NormalizePoints ).
  To enable/disable normalization, use #SetNormalization.
*/
template <class T>
class TLineApproximator  
{
public:
	//! \name Structures and typedefs
	//@{
	//! 2D homogenous point
	struct SHomog
	{
	public:
		SHomog(T _x=0, T _y=0, T _w=1)	{ x=_x; y=_y; w=_w;};	
		T x;
		T y;
		T w;
	};

	//! 2D point
	struct SPoint
	{
	public:
		SPoint(T _x=0, T _y=0)	{	x=_x; y=_y;};	
		static void CrossProduct( const SPoint& p, const SPoint& q, SHomog& r)
		{
			r.w = p.x * q.y - p.y * q.x;
			r.x = - q.y + p.y;
			r.y = q.x - p.x;
		};
		
		static T DotProduct( const SPoint& p, const SHomog& q)
		{
			return q.w + p.x*q.x + p.y*q.y;
		};
	
		static T DotProduct( const SPoint& p, const SPoint& q)
		{
			return p.x*q.x + p.y*q.y;
		};
	
		static void LinComb( T a, const SPoint& p, T b, const SPoint& q, SPoint& r)
		{
			r.x = a * p.x + b * q.x;
			r.y = a * p.y + b * q.y;
		};
	
		T x;
		T y;
	};

	//! Internal limit structure
	struct SLimits
	{
		T dMinX;
		T dMaxX;
		T dMinY;
		T dMaxY;
		T GetCenterX()	{	return (dMaxX+dMinX)/2.0;};
		T GetCenterY()	{	return (dMaxX+dMinX)/2.0;};
		T GetWidth()	{	return dMaxX-dMinX;};
		T GetHeight()	{	return dMaxY-dMinY;};
	};

	//! points container
	typedef std::vector<SPoint> PointContainer;
	//! Key containers
	typedef std::list<PointContainer::const_iterator> KeyContainer;
	//@}

	//! \name Constructor
	//@{
	TLineApproximator(): m_dTol(0), m_bNormalization(true)
	{m_limits.dMinX=m_limits.dMinY=0;m_limits.dMaxX=m_limits.dMaxY=1;};
	~TLineApproximator(){};
	//@}
		
	//! \name Point handling
	//@{
	//! returns number of points
	UINT GetPointSize() const				{	return m_cPoints.size();};
	//! sets the points as copy of the vectors
	void SetPoints( const std::vector<T>& vX, const std::vector<T>& vY);
	//! return vector of points
	PointContainer& GetPoints()				{	return m_cPoints;};
	//! return vector of points, const
	const PointContainer& GetPoints() const	{	return m_cPoints;};
	//@}

	//! \name Key handling
	//@{
	//! returns number of keys
	UINT GetKeySize() const					{	return m_cKeys.size();};
	//! return keys
	KeyContainer& GetKeys()					{	return m_cKeys;};
	//! return keys, const
	const KeyContainer& GetKeys() const		{	return m_cKeys;};
	//! fill vectors with keys
	void GetKeys( std::vector<T>& vX, std::vector<T>& vY);
	//@}

	//! \name Tolerance
	//@{
	//! sets the tolerance
	void SetTol( double dTol)				{	m_dTol = __max( dTol, 0);};
	//! return current tolerance
	double GetTol() const					{	return m_dTol;};
	//@}

	//! \name Normalization
	//@{
	//! enabled, disable normalization
	void SetNormalization( bool bEnabled = true)	{	m_bNormalization = true;};
	//! returns true if normalizing
	bool IsNormalization() const					{	return m_bNormalization;};
	//@}

	//! \name Simplification functions
	//@{
	//! Initialize simplification
	void ClearKeys()								{	m_cKeys.clear();};
	//! Compute the keys
	void Simplify();
	/*! Shrink to compression level 
	
	\param dScale scaling to apply [0...1]
	\param dScaleTol [optional] tolerance with respect to dScale, default is 0.05
	\param nMaxIter [optional] maximum number of iterations, default is 250
	\return number of estimations
	*/
	UINT ShrinkNorm( double dScale, double dScaleTol = 0.05, UINT nMaxIter = 250);

	/*! Shrink to a specified number of points
	
	\param n desired number of points in the approximate curve
	\param nTol [optional] tolerance with respect to n, default is 10
	\param nMaxIter [optional] maximum number of iterations, default is 250
	\return number of estimations
	*/
	UINT Shrink( UINT nDesiredPoints, UINT nTol = 10, UINT nMaxIter = 250);
	//@}

	//! \name Helper functions
	//@{
	//! compute the bounding box
	void ComputeBoundingBox();

	//! return the point bounding box
	const SLimits& GetBoundingBox() const		{	return m_limits;};

	/*! Point normalization
	
	 Let $(x_i,y_i)$, the original points and $(\hat x_x, \hat y_i)$ the normalized points:
	 \[
	 \hat x_i = \frac{x_i - \bar x]}{\max_i (x_i-x_j)}
	 \]
	where $\bar x, \bar y$ denote respectively the mean value of the $x_i$ and $y_i$.

	\sa DeNormalizePoints
	*/
	void NormalizePoints();

	/*! \brief Roll back normalization

	\sa NormalizePoints
	*/
	void DeNormalizePoints();
	//@}

protected:
	//! \name Virtual functions
	//@{
	virtual void ComputeKeys()		{	ClearKeys();};
	//@}

private:
	double m_dTol;
	bool m_bNormalization;
	PointContainer m_cPoints;
	KeyContainer m_cKeys;
	SLimits m_limits;
};


template <class T>
void TLineApproximator<T>::ComputeBoundingBox()
{
	if (m_cPoints.size() < 2)
		return;

	PointContainer::const_iterator it = m_cPoints.begin();
	//finding minimum and maximum...
	m_limits.dMinX=m_limits.dMaxY=it->x;
	m_limits.dMinY=m_limits.dMaxY=it->y;
	it++;
	for (;it!=m_cPoints.end();it++)
	{
		m_limits.dMaxX=__max( it->x, m_limits.dMaxX);
		m_limits.dMaxY=__max( it->y, m_limits.dMaxY);
		m_limits.dMinX=__min( it->x, m_limits.dMinX);
		m_limits.dMinY=__min( it->y, m_limits.dMinY);
	}

	if ( fabs( m_limits.GetWidth() ) < std::numeric_limits<T>::epsilon() )
	{
		m_limits.dMaxX = m_limits.dMinX+1;
	}
	if ( fabs( m_limits.GetHeight() ) < std::numeric_limits<T>::epsilon() )
	{
		m_limits.dMaxY = m_limits.dMinY+1;
	}
}

template <class T>
void TLineApproximator<T>::NormalizePoints()
{
	T xm,ym,dx,dy;
	// normalizing...
	xm=m_limits.GetCenterX();
	ym=m_limits.GetCenterY();
	dx=m_limits.GetWidth();
	dy=m_limits.GetHeight();

	// normalizing
	PointContainer::iterator it;
	for (it = m_cPoints.begin();it!=m_cPoints.end();it++)
	{
		it->x=(it->x-xm)/dx;
		it->y=(it->y-ym)/dy;
	}
}

template <class T>
void TLineApproximator<T>::DeNormalizePoints()
{
	T xm,ym,dx,dy;
	// normalizing...
	xm=m_limits.GetCenterX();
	ym=m_limits.GetCenterY();
	dx=m_limits.GetWidth();
	dy=m_limits.GetHeight();

	// denormalizing
	PointContainer::iterator it;
	for (it = m_cPoints.begin();it!=m_cPoints.end();it++)
	{
		it->x=xm+it->x*dx;
		it->y=ym+it->y*dy;
	}
}


template <class T>
UINT TLineApproximator<T>::ShrinkNorm( double dScale, double dScaleTol, UINT nMaxIter)
{
	// number of points wanted...
	UINT uWantedPoints= __min(m_cPoints.size(), __max(2, (UINT)floor(m_cPoints.size()*dScale)));
	UINT uTol = __min(m_cPoints.size(), __max(0, (UINT)floor(m_cPoints.size()*dScaleTol) ));

	return Shrink( uWantedPoints, uTol, nMaxIter);
}

template<class T>
UINT TLineApproximator<T>::Shrink( UINT nDesiredPoints, UINT nTol, UINT nMaxIter)
{
	if (m_cPoints.size()<2)
		return 0;
	
	// number of points wanted...
	double dWantedPoints= __min(m_cPoints.size(), __max(2, nDesiredPoints));
	double uMinWantedPoints = __min(m_cPoints.size(), __max(2, nDesiredPoints-nTol ));
	double uMaxWantedPoints = __min(m_cPoints.size(), __max(2, nDesiredPoints+nTol ));

	double eLeft, eRight, eMiddle;
	double dResultLeft, dResultRight;
	UINT iter=0;

	// normalize if needed
	if (m_bNormalization)
		NormalizePoints();


	// first estimation
	eLeft = 0;
	SetTol(eLeft);

	ComputeKeys();

	dResultLeft =  m_cKeys.size();
	iter++;
	// test if success
	if ( (m_cKeys.size()<=uMaxWantedPoints) && (m_cKeys.size() >= uMinWantedPoints) )
		goto PostProcess;

	// second estimation
	eRight=__max( m_limits.GetHeight(), m_limits.GetWidth() );
	SetTol(eRight);

	ComputeKeys();

	dResultRight =  m_cKeys.size();
	iter++;
	// test if success
	if ( (m_cKeys.size()<=uMaxWantedPoints) && (m_cKeys.size() >= uMinWantedPoints) )
		goto PostProcess;

	// main loop, dichotomy
	do
	{ 
		// test middle
		eMiddle=(eLeft +eRight)/2;
		SetTol(eMiddle);

		// computing new DP...
		ComputeKeys();
		
		std::cout<<"Iter: "<<iter<<", Wanted Keys "<<dWantedPoints<<", Current Keys "<<m_cKeys.size()<<", Tol (left, middle, right): ("
			<<eLeft<<", "<<eMiddle<<", "<<eRight<<")\n";

		// updating...
		if ( (m_cKeys.size()-dWantedPoints)*( dResultLeft-dResultRight) < 0 )
		{
			eRight=eMiddle;
			dResultRight=m_cKeys.size();
		}
		else 
		{
			eLeft=eMiddle;
			dResultLeft=m_cKeys.size();
		}

		iter++;
	} while ( ((m_cKeys.size()>uMaxWantedPoints) || (m_cKeys.size() < uMinWantedPoints)) /* checking that we are in the acceptable compression */
		&& (eRight - eLeft) > std::numeric_limits<T>::epsilon() /* interval is non empty */
		&& iter<nMaxIter /* checking for maximum number of iterations */);

PostProcess:
	if (m_bNormalization)
		DeNormalizePoints();

	return iter;
}


template <class T>
void TLineApproximator<T>::Simplify()
{
	if (m_cPoints.size()<2)
		return;
	
	// preprocess...
	if (m_bNormalization)
		NormalizePoints();

	ComputeKeys();

	if (m_bNormalization)
		DeNormalizePoints();
}

template<class T>
void TLineApproximator<T>::SetPoints( const std::vector<T>& vX, const std::vector<T>& vY)
{
	ClearKeys();
	UINT n = __min(vX.size(), vY.size());
	m_cPoints.resize(n);
	for (UINT i=0;i<n;i++)
	{
		m_cPoints[i].x=vX[i];
		m_cPoints[i].y=vY[i];
	}

	ComputeBoundingBox();
}

template<class T>
void TLineApproximator<T>::GetKeys( std::vector<T>& vX, std::vector<T>& vY)
{
	KeyContainer::const_iterator it;
	UINT i;

	vX.resize(m_cKeys.size());
	VY.reisze(m_cKeys.size());
	for (it = m_cKeys.begin(), i=0; it != m_cKeys.end(); it++, i++)
	{
		vX[i]=(*it)->x;
		vY[i]=(*it)->y;
	}
}


}; // namespace hull

#endif // !defined(AFX_LINEAPPROXIMATOR_H__F5E6E8DC_1185_4AC0_A061_7B3309700E9D__INCLUDED_)
