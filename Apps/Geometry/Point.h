/********************************************************************
File Name:	point.h
Written by: Li Peng, Yang Guang

Copyright(C) XinaoMDT, 2001 -

Purpose:
	This file defines following classes:
	CPoint2D
	CThreeDim

History:
	2002/9/4 Added CSize2D related function, CPoint2D reviewed. Yang Guang
	2001/11/28	Created by Li Peng.
*********************************************************************/
#if !defined(AFX_POINT_H__98FBD359_6FEA_429B_8279_A3AF3740EE68__INCLUDED_)
#define AFX_POINT_H__98FBD359_6FEA_429B_8279_A3AF3740EE68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <cassert>

#include "Size2D.h"

#ifdef GEOMETRY_IMP
   #define CLASS_DECL_GEOMETRY  __declspec(dllexport)
#else
   #define CLASS_DECL_GEOMETRY  __declspec(dllimport)
#endif

namespace Geometry
{
	//! This struct represents a point in a two-dimension plane.
	class CLASS_DECL_GEOMETRY CPoint2D
	{
	public:
		double x;
		double y;
		
		CPoint2D();
		CPoint2D(double dx, double dy);
		CPoint2D(const CPoint2D& pt);
        CPoint2D(const CSize2D& size){
            x = size.cx;
            y = size.cy;
        }

#ifdef _AFX	// if MFC is used.
		CPoint2D(const CPoint& pt);
#endif 		
		const CPoint2D& operator = (const CPoint2D& pt);
		const CPoint2D& operator += (const CPoint2D& pt);
		CSize2D operator -= (const CPoint2D& pt);
		const CPoint2D& operator + () const;
		CPoint2D operator - () const;
		CSize2D operator - (const CPoint2D& pt) const;
		const CPoint2D& operator *= (double dMultiplicator);
		const CPoint2D& operator /= (double dDivisor);
		CPoint2D operator * (double dMultiplicator) const;
		CPoint2D operator / (double dDivisor) const;
		
		const CPoint2D& operator += (const CSize2D& size);
		const CPoint2D& operator -= (const CSize2D& size);
		CPoint2D operator +  (const CSize2D& size) const;
		CPoint2D operator -  (const CSize2D& size) const;
		CPoint2D operator + (const CPoint2D& point) const;
		bool operator == (const CPoint2D& rhs) const;
		bool operator != (const CPoint2D& rhs) const;
		
		void Set(const CPoint2D& pt);
		void Set(double dx, double dy);
	};
	
#ifdef _AFX
	inline CPoint2D::CPoint2D(const CPoint& point)
	{
		x = static_cast < double>(point.x);
		y = static_cast < double>(point.y);
	}
#endif
	
	// =================== inline functions ====================
	inline CPoint2D::CPoint2D(): x(0.0), y(0.0)
	{
	}

	inline CPoint2D::CPoint2D(double dx, double dy) : x(dx), y(dy)
	{
	}

	inline CPoint2D::CPoint2D(const CPoint2D& pt) : x(pt.x), y(pt.y)
	{
	}

	inline const CPoint2D& CPoint2D::operator=(const CPoint2D& pt)
	{
		// not necessary to do self assignment test.
		x = pt.x;
		y = pt.y;

		return (*this);
	}

	inline void CPoint2D::Set(const CPoint2D& pt)
	{
		x = pt.x;
		y = pt.y;
	}

	inline void CPoint2D::Set(double dx, double dy)
	{
		x = dx;
		y = dy;
	}

	/*!
		\param pt const reference to CPoint2D
		\return a reference to CPoint2D, which is added by pt.
	*/
	inline const CPoint2D& CPoint2D::operator+=(const CPoint2D& pt)
	{
		x += pt.x;
		y += pt.y;

		return (*this);
	}

	/*!
		\param pt const reference to CPoint2D
		\return a reference to CPoint2D, which is subtracted by pt.
	*/
	inline CSize2D CPoint2D::operator -= (const CPoint2D& pt)
	{
		x -= pt.x;
		y -= pt.y;
		return (*this);
	}

	inline const CPoint2D& CPoint2D::operator+() const
	{
		return (*this);
	}

	inline CPoint2D CPoint2D::operator-() const
	{
		return CPoint2D(-x, -y);
	}

	inline const CPoint2D& CPoint2D::operator*=(double dMultiplicator)
	{
		x *= dMultiplicator;
		y *= dMultiplicator;
		return (*this);
	}

	inline const CPoint2D& CPoint2D::operator/=(double dDivisor)
	{
		assert(dDivisor != 0);
		x /= dDivisor;
		y /= dDivisor;
		return (*this);
	}

	inline CPoint2D CPoint2D::operator * (double dMultiplicator) const
	{
		return CPoint2D( x * dMultiplicator, y * dMultiplicator);
	}

	inline CPoint2D CPoint2D::operator/(double dDivisor) const
	{
		assert(dDivisor != 0);
		return CPoint2D(x / dDivisor, y / dDivisor);
	}

	//! Friend function, overroad +(addition) operator.
	/*!
		\param const pt1 is a reference to CPoint2D.
		\param const pt2 is a reference to CPoint2D.
		\return pt is the sum of pt1 and pt2.
	*/
	inline CPoint2D CPoint2D::operator+(const CPoint2D& point) const
	{
		return CPoint2D(x + point.x, y + point.y);
	}

	//! Friend function, overroad -(subtraction) operator.
	/*!
		\param point Point to substract.
		\return Offset from this point to \a point.
	*/
	inline CSize2D CPoint2D::operator-(const CPoint2D& point) const
	{
		return CSize2D(x - point.x, y - point.y);
	}
	
	inline const CPoint2D& CPoint2D::operator += (const CSize2D& size)
	{
		x += size.cx;
		y += size.cy;
		return (*this);
	}
	
	inline const CPoint2D& CPoint2D::operator -= (const CSize2D& size)
	{
		x -= size.cx;
		y -= size.cy;
		return (*this);
	}
	
	inline CPoint2D CPoint2D::operator + (const CSize2D& size) const
	{
		return CPoint2D(x + size.cx, y + size.cy);
	}

	inline CPoint2D CPoint2D::operator -  (const CSize2D& size) const
	{
		return CPoint2D(x - size.cx, y - size.cy);
	}

	inline bool 
	CPoint2D::operator == (const CPoint2D& rhs) const
	{
		return (x == rhs.x && y == rhs.y);
	}

	inline bool 
	CPoint2D::operator != (const CPoint2D& rhs) const
	{
		return !((*this) == rhs);
	}

} // end namespace Geometry

#endif // !defined(AFX_POINT_H__98FBD359_6FEA_429B_8279_A3AF3740EE68__INCLUDED_)
