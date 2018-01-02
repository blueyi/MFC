// Size2D.cpp: implementation of the CSize2D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Size2D.h"
#include "Point.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Geometry::CSize2D::~CSize2D()
{

}

Geometry::CSize2D::CSize2D(const CPoint2D& point)
{
    cx = point.x;
    cy = point.y;
}
