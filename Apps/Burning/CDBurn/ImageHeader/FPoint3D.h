#ifndef __FPOINT3D_H__
#define __FPOINT3D_H__

#include "../Geometry/ThreeDim.h"
using namespace Geometry;

#ifdef IMAGEHEADER_IMP
   #define CLASS_DECL_IMAGEHEADER __declspec(dllexport)
#else
   #define CLASS_DECL_IMAGEHEADER __declspec(dllimport)
#endif


#include "../BIGlobals/FitHeader.h"

class CFPoint3D;
typedef CFPoint3D		CFVector3D;
class CLASS_DECL_IMAGEHEADER CFPoint3D
{
public:
	CFPoint3D() { m_fx = m_fy = m_fz = 0.0; }
	CFPoint3D(double fx, double fy, double fz) { m_fx = fx, m_fy = fy, m_fz = fz; }
	CFPoint3D(const CThreeDim& pt3D) { m_fx = pt3D.x, m_fy = pt3D.y, m_fz = pt3D.z; }

public:
	void Set(double fx, double fy, double fz) { m_fx = fx, m_fy = fy, m_fz = fz; }
	void SetX(double fx) { m_fx = fx; }
	void SetY(double fy) { m_fy = fy; }
	void SetZ(double fz) { m_fz = fz; }

public:
	CFPoint3D& Move(double dx, double dy, double dz)
	{
		m_fx += dx, m_fy += dy, m_fz += dz;
		return *this;
	}

public: // CFVector3D
	BOOL IsZeroVector() { return IsZero(m_fx) &&  IsZero(m_fy) && IsZero(m_fz); }
	double Module() { return sqrt(m_fx*m_fx + m_fy*m_fy + m_fz*m_fz); }
	void Normalize()
	{
		double r = Module();
		if(r > cnstEpsilon_large)
			m_fx /= r, m_fy /= r, m_fz /= r;
		else
			m_fx = m_fy = m_fz = 0.0;
	}

	void Invert()
	{
		m_fx = -m_fx, m_fy = -m_fy, m_fz = -m_fz;
	}

	void Positize()
	{
		double fAbsMax = m_fx;

		if( fabs(fAbsMax) < fabs(m_fy) )
			fAbsMax = m_fy;

		if( fabs(fAbsMax) < fabs(m_fz) )
			fAbsMax = m_fz;

		if(fAbsMax < 0)
			Invert();
	}


public:
	void operator += (const CFPoint3D& pt)
	{
		m_fx += pt.m_fx, m_fy += pt.m_fy, m_fz += pt.m_fz;
	}
	void operator -= (const CFPoint3D& pt)
	{
		m_fx -= pt.m_fx, m_fy -= pt.m_fy, m_fz -= pt.m_fz;
	}
	void operator *= (const double f)
	{
		m_fx *= f, m_fy *= f, m_fz *= f;
	}

public:
	CFPoint3D operator * (const double f)
	{
		return CFPoint3D(f * m_fx, f * m_fy, f * m_fz);
	}

public:
	CFVector3D ForkMulWith(const CFVector3D& v1) const
	{
		CFVector3D v2;
		v2.m_fx = m_fy * v1.m_fz - m_fz * v1.m_fy;
		v2.m_fy = m_fz * v1.m_fx - m_fx * v1.m_fz;
		v2.m_fz = m_fx * v1.m_fy - m_fy * v1.m_fx;
		return v2;
	}

	double DotMul(const CFVector3D& v1) const
	{
		return m_fx*v1.m_fx + m_fy*v1.m_fy + m_fz*v1.m_fz;
	}
	
public:
	double m_fx;
	double m_fy;
	double m_fz;
};

inline
CFPoint3D operator * (const double f, const CFPoint3D& pt)
{
	return CFPoint3D(f * pt.m_fx, f * pt.m_fy, f * pt.m_fz);
}

inline
CFPoint3D operator - (const CFPoint3D& p0, const CFPoint3D& p1)
{
	return CFPoint3D(p0.m_fx - p1.m_fx, p0.m_fy - p1.m_fy, p0.m_fz - p1.m_fz);
}

inline
CFPoint3D operator + (const CFPoint3D& p0, const CFPoint3D& p1)
{
	return CFPoint3D(p0.m_fx + p1.m_fx, p0.m_fy + p1.m_fy, p0.m_fz + p1.m_fz);
}

inline
BOOL operator == (const CFPoint3D& p0, const CFPoint3D& p1)
{
	return IsEqual(p0.m_fx, p1.m_fx) && IsEqual(p0.m_fy, p1.m_fy) && IsEqual(p0.m_fz, p1.m_fz);
}

inline
BOOL operator != (const CFPoint3D& p0, const CFPoint3D& p1)
{
	return ! IsEqual(p0.m_fx, p1.m_fx) || ! IsEqual(p0.m_fy, p1.m_fy) || ! IsEqual(p0.m_fz, p1.m_fz);
}

inline
CFVector3D ForkMul(const CFVector3D& v0, const CFVector3D& v1)
{
	CFVector3D v2;
	v2.m_fx = v0.m_fy * v1.m_fz - v0.m_fz * v1.m_fy;
	v2.m_fy = v0.m_fz * v1.m_fx - v0.m_fx * v1.m_fz;
	v2.m_fz = v0.m_fx * v1.m_fy - v0.m_fy * v1.m_fx;
	return v2;
}

inline
double DotMul(const CFVector3D& v0, const CFVector3D& v1)
{
	return v0.m_fx*v1.m_fx + v0.m_fy*v1.m_fy + v0.m_fz*v1.m_fz;
}

#endif // __FPOINT3D_H__
