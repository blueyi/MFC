/* Plot Graphic Library

	Copyright (C) 2002 Pelikhan, Inc. All rights reserved
	Go to http://eauminerale.syldavie.csam.ucl.ac.be/peli/pgl/pgl.html for the latest PGL binaries
	This software is NOT freeware.

	This software is provided "as is", with no warranty.
	Read the license agreement provided with the files

	This software, and all accompanying files, data and materials, are distributed "AS IS" and with no warranties of any kind, 
	whether express or implied.  his disclaimer of warranty constitutes an essential part of the agreement.  
	In no event shall Pelikhan, or its principals, shareholders, officers, employees, affiliates, contractors, subsidiaries, 
	or parent organizations, be liable for any incidental, consequential, or punitive damages whatsoever relating to the use of PGL, 
	or your relationship with Pelikhan.

	Author: Jonathan de Halleux, dehalleux@auto.ucl.ac.be
*/
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

/*! Line approximation algorithms
\ingroup LAGroup 
*/
namespace hull
{

template<class T>
class TLine
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
		T GetCenterX()	{	return (T)((dMaxX+dMinX)/2.0);};
		T GetCenterY()	{	return (T)((dMaxY+dMinY)/2.0);};
		T GetWidth()	{	return (T)(dMaxX-dMinX);};
		T GetHeight()	{	return (T)(dMaxY-dMinY);};
	};

	//! points container
	typedef std::vector<SPoint> PointContainer;
	//! Key containers
	typedef std::list<PointContainer::iterator> KeyContainer;
	//! T container
	typedef std::vector<T> TVector;
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
protected:
	//! return keys
	KeyContainer& GetKeys()					{	return m_cKeys;};
public:
	//! return keys, const
	const KeyContainer& GetKeys() const		{	return m_cKeys;};
	//@}

	//! \name Bounding box
	//@{
	//! compute the bounding box
	void ComputeBoundingBox();
	//! return the point bounding box
	const SLimits& GetBoundingBox() const		{	return m_limits;};
	//@}

	//! \name Normalization
	//@{
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
	virtual void ExportKeys() = 0;

	PointContainer m_cPoints;
	KeyContainer m_cKeys;
	SLimits m_limits;
};


template <class T>
void TLine<T>::ComputeBoundingBox()
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
void TLine<T>::NormalizePoints()
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
void TLine<T>::DeNormalizePoints()
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
class TLineApproximator : virtual public TLine<T>
{
public:

	//! \name Constructor
	//@{
	TLineApproximator(): m_dTol(0), m_bNormalization(true), m_bExport(false)
	{m_limits.dMinX=m_limits.dMinY=0;m_limits.dMaxX=m_limits.dMaxY=1;};
	~TLineApproximator(){};
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
	//! enable/disable exporting
	void SetExport(bool bEnabled= true) const		{	m_bExport=bEnabled;};
	//! enable/disable exporting
	bool IsExport() const							{	return m_bExport;};
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
	\param eTolRight [optional] first estimate on right tolerance
	\param nMaxIter [optional] maximum number of iterations, default is 250
	\return number of estimations
	*/
	UINT ShrinkNorm( T dScale, T dScaleTol = 0.05, T eTolRight = -1, UINT nMaxIter = 250);

	/*! Shrink to a specified number of points
	
	\param n desired number of points in the approximate curve
	\param nTol [optional] tolerance with respect to n, default is 10
	\param eTolRight [optional] first estimate on right tolerance
	\param nMaxIter [optional] maximum number of iterations, default is 250
	\return number of estimations
	*/
	UINT Shrink( UINT nDesiredPoints, UINT nTol = 10, T eTolRight = -1, UINT nMaxIter = 250);
	//@}

protected:
	//! \name Virtual functions
	//@{
	virtual void ComputeKeys()		{	ClearKeys();};
	//@}

private:
	T m_dTol;
	bool m_bNormalization;
	bool m_bExport;
};


template <class T>
UINT TLineApproximator<T>::ShrinkNorm( T dScale, T dScaleTol, T eTolRight ,UINT nMaxIter)
{
	// number of points wanted...
	UINT uWantedPoints= __min(m_cPoints.size(), __max(2, (UINT)floor(m_cPoints.size()*dScale)));
	UINT uTol = __min(m_cPoints.size(), __max(0, (UINT)floor(m_cPoints.size()*dScaleTol) ));

	return Shrink( uWantedPoints, uTol, eTolRight, nMaxIter);
}

template<class T,class TKeyExporter>
UINT TLineApproximator<T>::Shrink( UINT nDesiredPoints, UINT nTol, T eTolRight, UINT nMaxIter)
{
	static const T tEpsilon=std::numeric_limits<T>::epsilon();
	if (m_cPoints.size()<2)
		return 0;
	
	// number of points wanted...
	T dWantedPoints= __min(m_cPoints.size(), __max(2, nDesiredPoints));
	T uMinWantedPoints = __min(m_cPoints.size(), __max(2, nDesiredPoints-nTol ));
	T uMaxWantedPoints = __min(m_cPoints.size(), __max(2, nDesiredPoints+nTol ));

	T eLeft, eRight, eMiddle;
	T dResultLeft, dResultRight;
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
	if ( (m_cKeys.size()<=uMaxWantedPoints) && (m_cKeys.size() >= uMinWantedPoints)  )
		goto PostProcess;

	// second estimation
	if (eTolRight<=0)
		eRight=__max( m_limits.GetWidth(), m_limits.GetHeight()); 
	else
		eRight=eTolRight;
	SetTol(eRight);

	ComputeKeys();

	dResultRight =  m_cKeys.size();

	// test if optimization possible
	if (dResultLeft<uMinWantedPoints ||  dResultRight>uMaxWantedPoints)
		throw _T("TLineApproximator<T>::Shrink failed: Desired compression ratio not possible in the tolerance domain.");

	iter++;
	// test if success
	if ( ((m_cKeys.size()<=uMaxWantedPoints) && (m_cKeys.size() >= uMinWantedPoints)) || (dResultLeft == dResultRight) )
		goto PostProcess;

	// main loop, dichotomy
	do
	{ 
		// test middle
		eMiddle=(eLeft +eRight)/2;
		SetTol(eMiddle);

		// computing new DP...
		ComputeKeys();
		
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
		&& (eRight - eLeft)/eRight > tEpsilon /* interval is non empty */
		&& (dResultRight != dResultLeft)
		&& iter<nMaxIter /* checking for maximum number of iterations */);

PostProcess:
	if (m_bNormalization)
		DeNormalizePoints();

	ExportKeys();

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
	KeyIteratorToVector();
}

template<class T,class TKeyExporter>
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


}; // namespace hull

#endif // !defined(AFX_LINEAPPROXIMATOR_H__F5E6E8DC_1185_4AC0_A061_7B3309700E9D__INCLUDED_)
