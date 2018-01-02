// InPlaneMapper.cpp: implementation of the CInPlaneMapper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <cassert>
#include <cmath>
#include <cfloat>

#include "Point.h"
#include "InPlaneMapper.h"
#include "algorithm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace Geometry;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInPlaneMapper::CInPlaneMapper()
{
	m_bUpdated = false;
}

CInPlaneMapper::~CInPlaneMapper()
{

}

/*!
	\param ptROI1 Coordinates of the first point in ROI Coordinate System.
	\param ptOrg It means the physical coordinate value of the ptROI1.
	\param ptROI2 Const reference to CPoint2D, it means the second point in 
	ROI Coordinate System.
	\param ptX Const reference to CPoint2D, it means the physical
	coordinate value of the ptROI2.
	\param ptROI3 Const reference to CPoint2D, it means the third point in 
	ROI Coordinate System.
	\param ptY Const reference to CPoint2D, it means the physical
	coordinate value of the ptROI3.
	\remarks 
	Use three points(not in one line), we can define two linear functions:
		CPoint2D ROIToPhysical(const CPoint2D& ptROI)
		-----Transform the point in the ROI Coordinate System to the point in
		the Physical Coordinate System.
	and 
		CPoint2D PhysicalToROI(const CPoint2D& ptPhysical)
		-----Transform the point in the Physical Coordinate System to the point
		in the ROI Coordinate System.
	For the efficiency being, 
	let ptROI1 = (0, 0)-----the original point,
	let ptROI2 = (Px, 0)----the point in X axis,
	let ptROI3 = (0, Py)----the point in Y axis.
	otherwise we must solve two 3 by 3 determinants.
*/
void CInPlaneMapper::Update(const CPoint2D& ptROI1, 
							 const CPoint2D& ptOrg,
							 const CPoint2D& ptROI2, 
							 const CPoint2D& ptX,
							 const CPoint2D& ptROI3, 
							 const CPoint2D& ptY)
{
	// the first point in ROI Coordinate System must be the original point.
	assert((fabs(ptROI1.x) < FLT_EPSILON) && (fabs(ptROI1.y) < FLT_EPSILON));

	// the second point in ROI Coordinate System must be the point in X axis. 
	assert((fabs(ptROI2.x) > FLT_EPSILON) && (fabs(ptROI2.y) < FLT_EPSILON));

	// the third point in ROI Coordinate System must be the point in Y axis. 
	assert((fabs(ptROI3.x) < FLT_EPSILON) && (fabs(ptROI3.y) > FLT_EPSILON));

	m_dC1RP = ptOrg.x;
	m_dC2RP = ptOrg.y;
	m_dA1RP = (ptX.x - m_dC1RP) / ptROI2.x;
	m_dA2RP = (ptX.y - m_dC2RP) / ptROI2.x;
	m_dB1RP = (ptY.x - m_dC1RP) / ptROI3.y;
	m_dB2RP = (ptY.y - m_dC2RP) / ptROI3.y;
	
	double MatrixValue = m_dA1RP * m_dB2RP - m_dA2RP * m_dB1RP;

	// This value must not be zero, if the transformation is linear conversion.
	assert(fabs(MatrixValue) > FLT_EPSILON);

	m_dA1PR = m_dB2RP / MatrixValue;
	m_dB1PR = -m_dB1RP / MatrixValue;
	m_dA2PR = -m_dA2RP / MatrixValue;
	m_dB2PR = m_dA1RP / MatrixValue;
	m_dC1PR = -(m_dA1PR * m_dC1RP + m_dB1PR * m_dC2RP);
	m_dC2PR = -(m_dA2PR * m_dC1RP + m_dB2PR * m_dC2RP);
	
	m_bUpdated = true;
}

void CInPlaneMapper::Update(const CPoint2D& ptOrg, const CPoint2D& ptX, const CPoint2D& ptY)
{
    CPoint2D pt2X(ptX), pt2Y(ptY);
    // if ptOrg != ptX, calculate ptY from ptOrg and ptX
    // |ptY.y - ptOrg.y|   |0  -1 |   |ptX.y - ptOrg.y|
    // |               | = |      | * |               |
    // |ptY.x - ptOrg.x|   |1   0 |   |ptX.x - ptOrg.x|
    if(ptOrg != ptX)
    {
        pt2Y.y = ptOrg.x - ptX.x + ptOrg.y;
        pt2Y.x = ptX.y - ptOrg.y + ptOrg.x;
        assert(pt2Y != ptOrg);
    }
    // if ptOrg != ptY, calculate ptX from ptOrg and ptY
    // |ptX.y - ptOrg.y|   |0    1 |   |ptY.y - ptOrg.y|
    // |               | = |       | * |               |
    // |ptX.x - ptOrg.x|   |-1   0 |   |ptY.x - ptOrg.x|
    else if (ptOrg != ptY)
    {
        pt2X.y = ptY.x - ptOrg.x + ptOrg.y;
        pt2X.x = ptOrg.y - ptY.y + ptOrg.x;
        assert(pt2X != ptOrg);
    }
    // if ptOrg == ptX == ptY, return
    else
    {
        m_bUpdated = false;
        return;
    }
    
    double dROIX, dROIY;
    dROIX = Distance(ptOrg, pt2X);
    dROIY = Distance(ptOrg, pt2Y);
    
	m_dC1RP = ptOrg.x;
	m_dC2RP = ptOrg.y;
	m_dA1RP = (pt2X.x - m_dC1RP) / dROIX;
	m_dA2RP = (pt2X.y - m_dC2RP) / dROIX;
	m_dB1RP = (pt2Y.x - m_dC1RP) / dROIY;
	m_dB2RP = (pt2Y.y - m_dC2RP) / dROIY;
	
	double MatrixValue = m_dA1RP * m_dB2RP - m_dA2RP * m_dB1RP;

	// This value must not be zero, if the transformation is linear conversion.
	assert(fabs(MatrixValue) > FLT_EPSILON);

	m_dA1PR = m_dB2RP / MatrixValue;
	m_dB1PR = -m_dB1RP / MatrixValue;
	m_dA2PR = -m_dA2RP / MatrixValue;
	m_dB2PR = m_dA1RP / MatrixValue;
	m_dC1PR = -(m_dA1PR * m_dC1RP + m_dB1PR * m_dC2RP);
	m_dC2PR = -(m_dA2PR * m_dC1RP + m_dB2PR * m_dC2RP);
    
    m_bUpdated = true;
}

void CInPlaneMapper::Update(const CPoint2D& ptOrg, double dAngleInArc)
{
   	m_dC1RP = ptOrg.x;
	m_dC2RP = ptOrg.y;
  	m_dA1RP = cos(dAngleInArc);
	m_dA2RP = sin(dAngleInArc);
	m_dB1RP = -m_dA2RP;
	m_dB2RP = m_dA1RP;
    
	double MatrixValue = m_dA1RP * m_dB2RP - m_dA2RP * m_dB1RP;

	// This value must not be zero, if the transformation is linear conversion.
	assert(fabs(MatrixValue) > FLT_EPSILON);

	m_dA1PR = m_dB2RP / MatrixValue;
	m_dB1PR = -m_dB1RP / MatrixValue;
	m_dA2PR = -m_dA2RP / MatrixValue;
	m_dB2PR = m_dA1RP / MatrixValue;
	m_dC1PR = -(m_dA1PR * m_dC1RP + m_dB1PR * m_dC2RP);
	m_dC2PR = -(m_dA2PR * m_dC1RP + m_dB2PR * m_dC2RP);
    
    m_bUpdated = true;
}

CPoint2D CInPlaneMapper::ROIToPhysical(const CPoint2D& ptROI) const
{
	// the converter must be enabled before the coordinate converting.
	assert(m_bUpdated);

	CPoint2D ptPhysical;
	ptPhysical.x = m_dA1RP * ptROI.x + m_dB1RP * ptROI.y + m_dC1RP;
	ptPhysical.y = m_dA2RP * ptROI.x + m_dB2RP * ptROI.y + m_dC2RP;
	return ptPhysical;
}

CPoint2D CInPlaneMapper::PhysicalToROI(const CPoint2D& ptPhysical) const
{
	// the converter must be enabled before the coordinate converting.
	assert(m_bUpdated);

	CPoint2D ptROI;
	ptROI.x = m_dA1PR * ptPhysical.x + m_dB1PR * ptPhysical.y + m_dC1PR;
	ptROI.y = m_dA2PR * ptPhysical.x + m_dB2PR * ptPhysical.y + m_dC2PR;
	return ptROI;
}
