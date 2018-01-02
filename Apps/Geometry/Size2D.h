// Size2D.h: interface for the CSize2D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIZE2D_H__166C6290_BA37_4140_88F5_AC269DC46A06__INCLUDED_)
#define AFX_SIZE2D_H__166C6290_BA37_4140_88F5_AC269DC46A06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef GEOMETRY_IMP
   #define CLASS_DECL_GEOMETRY  __declspec(dllexport)
#else
   #define CLASS_DECL_GEOMETRY  __declspec(dllimport)
#endif

namespace Geometry
{
class CPoint2D;

class CLASS_DECL_GEOMETRY CSize2D  
{
public:
	double cx;
	double cy;

	CSize2D();
	CSize2D(double dx, double dy);
    CSize2D(const CPoint2D& point);

#ifdef _AFX	// if MFC is used.
	CSize2D(const CSize& size)
	{
		cx = static_cast<double>(size.cx);
		cy = static_cast<double>(size.cy);
	}
#endif 
	virtual ~CSize2D();
    CSize2D CSize2D::operator * (double d) const{
		return CSize2D( cx * d, cy * d);
	}

protected:
};

inline CSize2D::CSize2D()
: cx (0.0), cy (0.0)
{
}

inline CSize2D::CSize2D(double dx, double dy)
: cx(dx), cy (dy)
{
}

} // end namespace geometry.
#endif // !defined(AFX_SIZE2D_H__166C6290_BA37_4140_88F5_AC269DC46A06__INCLUDED_)
