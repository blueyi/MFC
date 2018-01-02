// Line.h: interface for the CLineSegment class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINE_H__27282854_EDE4_43F7_B5FB_D0E6E2172044__INCLUDED_)
#define AFX_LINE_H__27282854_EDE4_43F7_B5FB_D0E6E2172044__INCLUDED_

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

class CLASS_DECL_GEOMETRY CLineSegment  
{
public:
	CLineSegment();
	CLineSegment(const CPoint2D& point1, const CPoint2D& point2);
	virtual ~CLineSegment();

protected:
	CPoint2D m_pt2dEnd1;
	CPoint2D m_pt2dEnd2;
};

inline CLineSegment::CLineSegment()
 : m_pt2dEnd1(0.0, 0.0), m_pt2dEnd2(0.0, 0.0)
{
}

inline CLineSegment::CLineSegment(const CPoint2D& point1, const CPoint2D& point2)
{
	m_pt2dEnd1 = point1;
	m_pt2dEnd2 = point2;
}

double CrossAngle(const CPoint2D& ptEndPoint1, const CPoint2D& ptVertex, 
				  const CPoint2D& ptEndPoint2);

// end Geometry 
}

#endif // !defined(AFX_LINE_H__27282854_EDE4_43F7_B5FB_D0E6E2172044__INCLUDED_)
