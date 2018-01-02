/********************************************************************
File Name:	Algorithm.h
Written by: Li Peng, Yang Guang

Copyright(C) XinaoMDT, 2001 -

Purpose:
	This file defines following classes:

History:
	2002/8/30	Move some algorithms from Point.h here.
*********************************************************************/
#include "stdafx.h"		// required by MFC for precomiled header.

#pragma warning (disable:4786)

#include <cassert>
#include <cmath>
#include <cfloat>
#include <iostream>

#include "algorithm.h"
#include "point.h"
#include "ThreeDim.h"
#include "Triangle2.h"
#include "GenericRect.h"

using namespace Geometry;

#define PI 3.14159265


/*!
	\param u const referece to CPoint2D
	\param v const referece to CPoint2D
	\return the distance of the previous point in a plane.
*/
double Geometry::Distance(const CPoint2D& pt1, const CPoint2D& pt2)
{
	double dx = pt1.x - pt2.x;
	double dy = pt1.y - pt2.y;
	return sqrt(dx * dx + dy * dy);
}

/*!
	\param pt1L1 Const referece to CPoint2D. The first point of the first line.
	\param pt2L1 Const referece to CPoint2D. The second point of the first
	line.
	\param pt1L2 Const referece to CPoint2D. The first point of the second
	line.
	\param pt2L2 Const referece to CPoint2D. The second point of the seond
	line.
	\return the crossing point of the two lines.
	\remarks
	//////////////////////Algorithm Schema////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	Define two lines by the four points.
	L1: k1 * x + (-1) * y = k1 * pt1L1.x - pt1L1.y;
	L2: k2 * x + (-1) * y = k2 * pt1L2.x - pt1L2.y;
	k1 = (pt2L1.y - pt1L1.y) / (pt2L1.x - pt1L1.x);
	k2 = (pt2L2.y - pt1L2.y) / (pt2L2.x - pt1L2.x);

	So:
	L1: (pt2L1.y - pt1L1.y) * x + (-1) * (pt2L1.x - pt1L1.x) * y
		= (pt2L1.y - pt1L1.y) * pt1L1.x - (pt2L1.x - pt1L1.x) * pt1L1.y;
	L2: (pt2L2.y - pt1L2.y) * x + (-1) * (pt2L2.x - pt1L2.x) * y
		= (pt2L2.y - pt1L2.y) * pt1L2.x - (pt2L2.x - pt1L2.x) * pt1L2.y;

	Being two equations:
	Eq1: a1 * x + b1 * y = c1;
	Eq2: a2 * x + b2 * y = c2;
	Their solution is:
	x = (b2 * c1 - b1 * c2) / Delta;
	y = (a1 * c2 - a2 * c1) / Delta;
	Delta = a1 * b2 - a2 * b1;
	(if Delta equals zero, it means L1 and L2 are in parallel.)
	So the crossing point of the L1 and L2 is:
	(x, y);
	a1 = pt2L1.y - pt1L1.y, b1 = (-1) * (pt2L1.x - pt1L1.x)
	a2 = pt2L2.y - pt1L2.y, b2 = (-1) * (pt2L2.x - pt1L2.x), 
	c1 = (pt2L1.y - pt1L1.y) * pt1L1.x - (pt2L1.x - pt1L1.x) * pt1L1.y;
	c2 = (pt2L2.y - pt1L2.y) * pt1L2.x - (pt2L2.x - pt1L2.x) * pt1L2.y;    
	//////////////////////////////////////////////////////////////////////
*/
bool Geometry::CrossPoint(const CPoint2D& pt1L1, const CPoint2D& pt2L1,
				const CPoint2D& pt1L2, const CPoint2D& pt2L2,
				CPoint2D& ptCross)
{
	double a1, b1, c1, a2, b2, c2;
	a1 = (pt2L1.y - pt1L1.y);
	b1 = pt1L1.x - pt2L1.x;
	a2 = pt2L2.y - pt1L2.y;
	b2 = pt1L2.x - pt2L2.x;
	c1 = a1 * pt1L1.x + b1 * pt1L1.y;
	c2 = a2 * pt1L2.x + b2 * pt1L2.y;

	double delta = a1 * b2 - a2 * b1;
	if(fabs(delta) < FLT_EPSILON)
	{
		return false;
	}
	ptCross.x = (b2 * c1 - b1 * c2) / delta;
	ptCross.y = (a1 * c2 - a2 * c1) / delta;
	return true;
}

/*!
	\param ptLock Const reference to CPoint2D, this point is a fixed-point.
	\param ptLock Const reference to CPoint2D, this point will be changed by
	the changing of ptDynamic.
	\param ptLock Const reference to CPoint2D, this point is a changeable
	point, it will be changed by the user directly.
	\param ptLock Const reference to CPoint2D, this point is the result of
	ptDynamic.
	\remarks A triangle is defined by three point: 
	ptLock, ptPassive and ptDynamic.
	ptLock is a fixed-point, ptDynamic is a point that is moved in real-time.
	ptPassive is a point which is changed by ptLock and ptDynamic.
	//////////////////////Algorithm Schema////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	1) Define the first line------L1 by two points: ptLock and ptTerminal.
	   Define the second line-----L2 by two points: ptPassive and ptDynamic.
	   Caculate the crossing point----ptCross of the two lines.
	   if L1 and L2 are in parallel, ptResult equals ptLock.
	2) Use the follow formula to caculate the later position of ptPassive 
	   ----ptResult.
	   ptCross    - ptLock		       ptPassive - ptLock
	   ---------------------     =   ---------------------
	   ptTerminal - ptLock		       ptResult  - ptLock
	   Than the value of ptResult can be caculated.
	//////////////////////////////////////////////////////////////////////
*/
Geometry::CPoint2D 
Geometry::VertexMoving(const CPoint2D& ptLock, 
                       const CPoint2D& ptPassive,
                       const CPoint2D& ptDynamic,
                       const CPoint2D& ptTerminal)
{
	CPoint2D ptCross;
	if(!CrossPoint(ptLock, ptTerminal, ptPassive, ptDynamic, ptCross))
	{
		return ptLock;
	}
	else
	{
		// if the ptCross is very near to ptLock, it means all the area is very
		// small.
		if (ptCross == ptLock)
			return ptLock;

		CPoint2D ptResult;
		if(fabs(ptCross.x - ptLock.x) < FLT_EPSILON)
		{
			ptResult.x = ptDynamic.x;
		}
		else
		{
			ptResult.x = ptLock.x + (ptPassive.x - ptLock.x) 
				/ (ptCross.x - ptLock.x) * (ptTerminal.x - ptLock.x);
		}

		if(fabs(ptCross.y - ptLock.y) < FLT_EPSILON)
		{
			ptResult.y = ptDynamic.y;
		}
		else
		{
			ptResult.y = ptLock.y + (ptPassive.y - ptLock.y) 
				/ (ptCross.y - ptLock.y) * (ptTerminal.y - ptLock.y);
		}
		return ptResult;
	}
}

/*!
    \param pt Point whose distance to the line is calculated.
    \param pt1 One end point of the line.
    \param pt2 Another end point of the line.
    \return Calculated distance.
*/
double 
Geometry::DistanceToLine(const Geometry::CPoint2D& pt, 
                     const Geometry::CPoint2D& pt1, 
                     const Geometry::CPoint2D& pt2)
{
	if (pt1 == pt2)
		return Distance(pt, pt1);
	else
	{
		double a;
		double b;
		a = fabs(-pt2.y * pt1.x + pt2.x * pt1.y +
			pt2.y * pt.x - pt.x * pt1.y - pt2.x * pt.y + pt.y * pt1.x);
		b = Distance(pt1, pt2);
		return (a / b);
	}
}

/*!
	\param pt Const reference to CPoint2D, a point to be judged.
	\param pt1L Const reference to CPoint2D, one point of the segment of line.
	\param pt2L Const reference to CPoint2D, one point of the segment of line.
	\return \a true if the point is within the segment of line, \a false 
	otherwise.
*/
bool 
Geometry::PtWithinLine(const Geometry::CPoint2D& pt, 
                       const Geometry::CPoint2D& pt1L,
                       const Geometry::CPoint2D& pt2L)
{
	double dDist1 = Distance(pt, pt1L);
	if(dDist1 < FLT_EPSILON) // if pt is very near to pt1L
		return true;

	double dDist2 = Distance(pt, pt2L);
	if(dDist2 < FLT_EPSILON) // if pt is very near to pt2L
		return true;

	double dDist  = Distance(pt1L, pt2L);
	if(fabs(dDist1 + dDist2 - dDist) < FLT_EPSILON)
		return true;
	return false;
}

bool 
Geometry::IsCrossing(const Geometry::CPoint2D& point1, 
                     const Geometry::CPoint2D& point2,
                     const Geometry::CPoint2D& point3, 
                     const Geometry::CPoint2D& point4)
{
	double a1, b1, c1, a2, b2, c2;
	a1 = (point2.y - point1.y);
	b1 = point1.x - point2.x;
	a2 = point4.y - point3.y;
	b2 = point3.x - point4.x;
	c1 = a1 * point1.x + b1 * point1.y;
	c2 = a2 * point3.x + b2 * point3.y;

	double delta = a1 * b2 - a2 * b1;
	if(fabs(delta) < FLT_EPSILON)
	{
		return false;
	}
	return true;
}


//! This function implement inner product operation between two vectors.
/*!
	\param u Const reference to the input vector.
	\param v Const reference to the input vector.
	\return the value of two vectors' inner product.
*/
double Geometry::InnerProduct(const CThreeDim &u, const CThreeDim &v)
{
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

//! This function implement outer product operation between two vectors.
/*!
	\param u Const reference to the input vector.
	\param v Const reference to the input vector.
	\return the vector of two vectors' outer product.
*/
CThreeDim Geometry::OuterProduct(const CThreeDim & u,const CThreeDim &v)
{
	CThreeDim w;
	w.x = u.y * v.z - u.z * v.y;
	w.y = u.z * v.x - u.x * v.z;
	w.z = u.x * v.y - u.y * v.x;
	return w;
}

/*! 
	This function calculate the crossing angle of two vector, it also 
	distinguish rotation angle between anti-clockwise or clockwise.
*/
/*!
	\param FormerPoint is a const reference to CPoint2D, it is the original end 
	point of the vector	in the plane---here, the plane is the referene image.
	\param LatterPoint is a const reference to CPoint2D, it is the end point of
	vector that after rotation in the plane.
	\param CenterPoint is a const reference to CPoint2D, it is the starting
	point of the vector that be rotated.
	\return the rotation angle that describe anti-clockwise or clock.
	\remarks In this function we assume the rotation angle's absolute value
	(identical to the crossing angle between the two vector) is within the
	interval [0, PI).
	Vector A become B after rotating: now the question is
	"How to judge a rotation process is anti-clockwise or clockwise?"
	1) Calculate the crossing angle
	     delta = inner-product(A,B)/[module(A)*module(B)];
	2) Create a rotation matrix
                       _                        _
			          |  cos(delta) -sin(delta)  |	  
		   R(delta) = |_ sin(delta)  sin(delta) _|
	3) Create a vector A' = R(delta) * A, A' equals A after rotating angle 
	   delta in anti-clockwise.
	4) Let v  = out-product(A,B)/[module(A)*module(B)] and
	   let v' = out-product(A,A')/[module(A)*module(A')]
	   if  v == v', the rotation process is anti-clockwise;
	   else the rotation process is clockwise.(In this case, v == -v').	       
*/
double Geometry::CalcCrossAngle(const CPoint2D& FormerPoint,
							    const CPoint2D& LatterPoint,
							    const CPoint2D& CenterPoint)
{
	CThreeDim FormerPoint3D(FormerPoint);
	CThreeDim LatterPoint3D(LatterPoint);
	CThreeDim CenterPoint3D(CenterPoint);

	CThreeDim OrigVector = FormerPoint3D - CenterPoint3D;
	CThreeDim DestVector = LatterPoint3D - CenterPoint3D;
	
	OrigVector.Unify();
	DestVector.Unify();
	// The first item means the crossing angle is very small or zero.
    // The second and third one means these two vector is zero vector.
	if((OrigVector == DestVector) || 
		(OrigVector == CThreeDim(0, 0, 0)) || 
		(DestVector == CThreeDim(0, 0, 0)))
	{
		return 0;             
	}

	double CosineValue = Geometry::InnerProduct(OrigVector, DestVector)
		/(sqrt(Geometry::InnerProduct(OrigVector, OrigVector)) 
		* sqrt(Geometry::InnerProduct(DestVector, DestVector)));

	double CrossingAngle = acos(CosineValue);
	// AssitVector is a vector that anti-clockwise by CrossingAngle from 
	// OrigVector.
	CThreeDim AssitVector;  
	AssitVector.x = OrigVector.x * CosineValue - OrigVector.y 
					* sin(CrossingAngle);
	AssitVector.y = OrigVector.x * sin(CrossingAngle) + OrigVector.y 
					* CosineValue; 
	
	if(AssitVector != DestVector)
		CrossingAngle = - CrossingAngle;
	return CrossingAngle;
}

bool Geometry::IsSegmentsCrossing(const CPoint2D& point1, 
                        const CPoint2D& point2,
                        const CPoint2D& point3, 
                        const CPoint2D& point4)
{
    CPoint2D ptCross;

	if(CrossPoint(point1, point2, point3, point4, ptCross))
	{
		if(PtWithinLine(ptCross, point1, point2)
			&& PtWithinLine(ptCross, point3, point4))
			return true;
	}
    
    return false;
}

/*!
	\a CrossAngle function calculates the angle (in arc) determined by three
	points. 
	\param pt1 End point of one of the line segment.
	\param ptVertex Cross point of two line segments.
	\param pt2 End point of another line segment.
	\param bInArc \a true if the angle is expressed in arc, \a false if 
	expressed in degree.
	\return Angle in arc.
*/
double Geometry::CrossAngle(const CPoint2D& pt1, 
				  const CPoint2D& ptVertex, 
				  const CPoint2D& pt2, 
				  bool bInArc)
{
	double dx1 = pt1.x - ptVertex.x;
	double dy1 = pt1.y - ptVertex.y;
	double dx2 = pt2.x - ptVertex.x;
	double dy2 = pt2.y - ptVertex.y;

	double d = (dx1 * dx1 + dy1 * dy1) * (dx2 * dx2 + dy2 * dy2);	
	if ( d != 0.0 )
	{
		d = acos((dx1 * dx2 + dy1 * dy2) / sqrt(d));
	}
	else
	{
		d = 0.0;
	}

	return (bInArc ? d : d / PI * 180.0);
}

/*!
	\param pt1 First point.
	\param pt2 Second point.
	\return The distance between two points.
*/
double Geometry::Distance(const CPoint2D& pt1, const CPoint2D& pt2)
{
	double dx = pt1.x - pt2.x;
	double dy = pt1.y - pt2.y;
	return sqrt(dx * dx + dy * dy);
}

/*! 
 	This function checks to see if a given point \a pt is on the line segment
	determined by \a pt1 and \a pt2. If the distance from \a pt to the line 
	segment is no more than \a dAdjacent, it is regarded to be on the line.
	\param pt Point to test.
	\param pt1 First end point of the line segment.
	\param pt2 Second end point of the line segment.
	\param dAdjacent If the distance from the point to the line is less than 
	this value, it is regarded to be on the line.
	\return \a true if the point \a pt is on the line segment, \a false otherwise.
 */
bool Geometry::PointOnLine(const CPoint2D& pt,
						const CPoint2D& pt1,
						const CPoint2D& pt2,
						double dAdjacent)
{						
	CGenericRect rc(pt1.x, pt1.y, pt2.x, pt2.y);
	rc.NormalizeRect();

    // \bug 
	rc.InflateRect(dAdjacent, dAdjacent);

	if (!rc.PtInRect(pt))
		return false;

	if (DistanceToLine (pt, pt1, pt2) <= dAdjacent)
		return true;
	else
		return false;
}

/*!
	This function calculates the area of the polygon.
	\param points Array holding the vertexes of the polygon.
	\param nSize Number of vertexes of the polygon.
	\remarks This function uses triangulate method to calculate the area of 
	a polygon, the algorithm can be optimized if necessary.
*/
double Geometry::Area(const CPoint2D* pPoints, int nSize)
{
	assert (nSize >= 3);
    CPolyTri triangle;

	if (nSize != 3)
	{
		Vector3F* pVertexVecs = NULL;
		try
		{
			pVertexVecs = new Vector3F[nSize];
		}
		catch(std::bad_alloc& e)
		{
			std::cerr << e.what();
			exit(EXIT_FAILURE);
		}

		for( int i=0 ; i < nSize ; i++ )
		{
			 pVertexVecs[i][0]   = pPoints[i].x;
			 pVertexVecs[i][1]   = pPoints[i].y;
			 pVertexVecs[i][2]   = 0.0f;
		}
		Vector3F normal;
		triangle.ComputeNormal(pVertexVecs, nSize, normal);
		triangle.Triangulate(pVertexVecs, normal, nSize);
		delete []pVertexVecs;
		return (triangle.GetArea());
	}
	else
	{
		CThreeDim edge1(CThreeDim(pPoints[0]) - CThreeDim(pPoints[1]));
		CThreeDim edge2(CThreeDim(pPoints[0]) - CThreeDim(pPoints[2]));
		CThreeDim doubleArea = OuterProduct(edge1, edge2);
		return (doubleArea.Modulus() / 2.0);
	}
}
