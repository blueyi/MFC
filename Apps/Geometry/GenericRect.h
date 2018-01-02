/********************************************************************
File Name:	GenericRect.h
Written by: Yang Guang

Copyright(C) XinaoMDT, 2001 -

Purpose:
	This file defines following classes:
    CGenericRect

History:
	2002/8/15	Created.
*********************************************************************/

#if !defined(AFX_GENERICRECT_H__C54747AE_2A76_4514_B853_ABE6B55065E1__INCLUDED_)
#define AFX_GENERICRECT_H__C54747AE_2A76_4514_B853_ABE6B55065E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Point.h"

#ifdef GEOMETRY_IMP
   #define CLASS_DECL_GEOMETRY  __declspec(dllexport)
#else
   #define CLASS_DECL_GEOMETRY  __declspec(dllimport)
#endif

namespace Geometry
{

/*!
    This class is the same in the meaning with the MFC CRect class, but all
    coordinates are stored in double, so it can be used to store a real world
    rectangle.
*/
class CLASS_DECL_GEOMETRY CGenericRect  
{
public:
    CGenericRect();
	CGenericRect(double left, double top, double right, double bottom);
	CGenericRect(const CPoint2D& point, const CSize2D& size);
    virtual ~CGenericRect(){};

#ifdef _AFX	// if MFC is used.
    CGenericRect(const CRect& rc);
    operator CRect();
#endif

    bool PtInRect(const CPoint2D& pt);
    void NormalizeRect();
    void InflateRect(double dDeltaX, double dDeltaY);

    double m_dLeft;
    double m_dRight;
    double m_dTop;
    double m_dBottom;
};

/*!
    Default constructor. All members initialized to zero.
*/
inline CGenericRect::CGenericRect()
{
    m_dLeft = m_dRight = m_dTop = m_dBottom = 0.0;
}

/*!
    Constructs an object from the four side of the rectangle.
*/
inline CGenericRect::CGenericRect(double left, 
                                  double top, 
                                  double right, 
                                  double bottom)
{
    m_dLeft = left;
    m_dRight = right;
    m_dTop = top;
    m_dBottom = bottom;
}

#ifdef _AFX
/*!
    Constructs an object from an MFC CRect object.
*/
inline CGenericRect::CGenericRect(const CRect& rc)
{
    m_dLeft = static_cast<double>(rc.left);
    m_dTop = static_cast<double>(rc.top);
    m_dRight = static_cast<double>(rc.right);
    m_dBottom = static_cast<double>(rc.bottom);
}

/*!
    Automatic type conversion operator used to convert a CGenericRect object
    to MFC CRect.
*/
inline CGenericRect::operator CRect()
{
    return CRect(static_cast<int>(m_dLeft + (m_dLeft > 0 ? 0.5 : -0.5)),
        static_cast<int>(m_dTop + (m_dTop > 0 ? 0.5 : -0.5)),
        static_cast<int>(m_dRight + (m_dRight > 0 ? 0.5 : -0.5)),
        static_cast<int>(m_dBottom + (m_dBottom > 0 ? 0.5 : -0.5)));
}
#endif 

/*!
    Normalize the rectangle, that is, to make sure the left side of rectangle
    is less than the right and the top is less than the bottom.
*/
inline void CGenericRect::NormalizeRect()
{
    double d;
    if (m_dLeft > m_dRight)
    {
        d = m_dLeft;
        m_dLeft = m_dRight;
        m_dRight = d;
    }
    if (m_dTop > m_dBottom)
    {
        d = m_dTop;
        m_dTop = m_dBottom;
        m_dBottom = d;
    }
}

/*!
    Check to see if a given point is in the rectangle.
    \param pt Point to test.
    \pre The rectangle must be normalized before calling this function.
    You can call NormallizeRect() to normalize the rectangle.
*/
inline bool CGenericRect::PtInRect(const CPoint2D& pt)
{
    // the rectangle must be normalized before calling this function.
    ASSERT((m_dLeft <= m_dRight) && (m_dTop <= m_dBottom));

    if (pt.x >= m_dLeft && pt.x < m_dRight && 
        pt.y >= m_dTop && pt.y < m_dBottom)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*!
    Inflate the rectangle by the given value.
    \param dDeltaX Amount to inflate on left and right side.
    \param dDeltaY Amount to inflate on top and bottom side.
    \pre The rectangle must be normalized before calling this function.
*/
inline void CGenericRect::InflateRect(double dDeltaX, double dDeltaY)
{
    // the rectangle must be normalized before calling this function.
    ASSERT((m_dLeft <= m_dRight) && (m_dTop <= m_dBottom));

    m_dLeft -= dDeltaX;
    m_dRight += dDeltaX;
    m_dTop -= dDeltaY;
    m_dBottom += dDeltaY;
}

//! Constructor.
/*!
	This function constructs a CGenericRect from its top left corner and size.
	\param point Coordinate ot the top left corner of the rectangle.
	\param size Size of the rectangle.
*/
inline CGenericRect::CGenericRect(const CPoint2D& point, const CSize2D& size)
{
	m_dLeft = point.x;
	m_dRight = point.x + size.cx;
	m_dTop = point.y;
	m_dRight = point.y + size.cy;
}


}	// End namespace Geometry.

#endif // !defined(AFX_GENERICRECT_H__C54747AE_2A76_4514_B853_ABE6B55065E1__INCLUDED_)
