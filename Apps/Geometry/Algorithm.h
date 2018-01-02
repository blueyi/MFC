/********************************************************************
File Name:	Algorithm.h
Written by: Li Peng, Yang Guang

Copyright(C) XinaoMDT, 2001 -

Purpose:
	This file defines following classes:

History:
	2002/8/30	Move some algorithms from Point.h here.
*********************************************************************/

#ifndef _yg_Algorithm_h_3082002
#define _yg_Algorithm_h_3082002

#include "ThreeDim.h"

#ifdef GEOMETRY_IMP
   #define CLASS_DECL_GEOMETRY  __declspec(dllexport)
#else
   #define CLASS_DECL_GEOMETRY  __declspec(dllimport)
#endif

/*!
	Here we keep a set of global functions related to frequently
	
*/
namespace Geometry
{
    class CPoint2D;

    //! Returns angle in arc or degree.
    CLASS_DECL_GEOMETRY double CrossAngle(const Geometry::CPoint2D& ptEndPoint1, 
        const Geometry::CPoint2D& ptVertex, 
        const Geometry::CPoint2D& ptEndPoint2, bool bInArc = true);

    //! This function calculates the distance between two points.
    CLASS_DECL_GEOMETRY double Distance(const Geometry::CPoint2D& pt1, 
        const Geometry::CPoint2D& pt2);

	//! Calculate the crossing point between two lines.
	CLASS_DECL_GEOMETRY bool CrossPoint(const CPoint2D& pt1L1, const CPoint2D& pt2L1,
		const CPoint2D& pt1L2, const CPoint2D& pt2L2,
		CPoint2D& ptCross);
	
	//! 
	CLASS_DECL_GEOMETRY CPoint2D VertexMoving(const CPoint2D& ptLock, const CPoint2D& ptPassive,
		const CPoint2D& ptDynamic, const CPoint2D& ptTerminal);
	
	//! Calculate the distance between a point and a line.
	CLASS_DECL_GEOMETRY double DistanceToLine(const CPoint2D& pt, const CPoint2D& pt1, 
		const CPoint2D& pt2);
	
	//! To judge if a point is within a segment of line.
	CLASS_DECL_GEOMETRY bool PtWithinLine(const CPoint2D& pt, const CPoint2D& pt1L,
		const CPoint2D& pt2L);

	//! Check to see if a given point is on the line segment.
	CLASS_DECL_GEOMETRY bool PointOnLine(const Geometry::CPoint2D& point, 
		const Geometry::CPoint2D& ptEnd1, const Geometry::CPoint2D& ptEnd2,
		double dAdjacent);
	
	//! To judeg if two lines are crossing.
	CLASS_DECL_GEOMETRY bool IsCrossing(const CPoint2D& point1, const CPoint2D& point2,
		const CPoint2D& point3, const CPoint2D& point4);
	
	//! To judge if two segment lines are crossing.
	CLASS_DECL_GEOMETRY bool IsSegmentsCrossing(const CPoint2D& point1, const CPoint2D& point2,
		const CPoint2D& point3, const CPoint2D& point4);
	
	CLASS_DECL_GEOMETRY double  InnerProduct(const CThreeDim &u, const CThreeDim& v);
	CLASS_DECL_GEOMETRY CThreeDim OuterProduct(const CThreeDim &u, const CThreeDim& v);
	CLASS_DECL_GEOMETRY double CalcCrossAngle(const CPoint2D& FormerPoint,
		const CPoint2D& LatterPoint,
		const CPoint2D& CenterPoint);

	//! this function calculates the area of a polygon.
	CLASS_DECL_GEOMETRY double Area(const CPoint2D* pPoints, int nSize);

}
#endif
