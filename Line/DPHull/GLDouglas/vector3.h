// vector3.h: interface for the CVector3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTORCLASS_H__EE946E20_1D6E_11D4_8D89_00409503B978__INCLUDED_)
#define AFX_VECTORCLASS_H__EE946E20_1D6E_11D4_8D89_00409503B978__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdAfx.h"

/** A vector in 3D.
A little class that implements some basic math operations
on vectors. A vector is the vector from the origin (0,0,0) to
the point (x,y,z)*/
class CVector3  
{
public:
	float x,y,z;

	/// a rectangular coordiantes constructor
	CVector3(float _x=0.0,float _y=0.0, float _z=0.0)
	{ x=_x; y=_y; z=_z;};
	/** a spherical coordinates constructor. \\
	\begin{description}
		\item $x=r*\sin(\phi)*\cos(\theta)$
		\item $y=r*\sin(\phi)*\sin(\theta)$
		\item $z=r*\cos(\phi)$
	\end{description};
	theta and phi are in radians.
	*/
	void createSpherical(float theta, float phi, float r)
	{ x=(float)(r*sin(theta)*cos(phi)); y=(float)(r*cos(theta)*cos(phi)); z=(float)(r*sin(phi));};	

	CVector3(const CVector3& vc)
	{ x=vc.x; y=vc.y; z=vc.z;};
	CVector3& operator = (const CVector3& vc)
	{ x=vc.x; y=vc.y; z=vc.z; return *this;};
	/// the destructor
	~CVector3()
	{};

	/// the cross product between v1 and v2, stored in cross
	friend CVector3 crossProduct(const CVector3& v1,const CVector3& v2)
	{ return CVector3(v1.y*v2.z-v1.z*v2.y, v1.z*v2.x-v1.x*v2.z, v1.x*v2.y-v1.y*v2.x);};
	friend CVector3 crossProductWithX(const CVector3& v2)
	{ return CVector3(0.0,-v2.z, v2.y);};
	friend CVector3 crossProductWithY(const CVector3& v2)
	{ return CVector3(v2.z,0.0,-v2.x);};
	friend CVector3 crossProductWithZ(const CVector3& v2)
	{ return CVector3(-v2.y,v2.x,0.0);};
	/// the dot product between v1 and v2, stored in dot
	friend float dotProduct(const CVector3& v1, const CVector3& v2)
		{ return v1.x*v2.x+v1.y*v2.y+v1.z*v2.z;};
	/// computes the euclidian norm of the vector
	double norm()
		{ return sqrt(x*x+y*y+z*z);};
	/// normalizes the vector
	void normalize()
	{ float n=(float)sqrt(x*x+y*y+z*z); if (n==0) {x=y=z=0.0;} else {x/=n; y/=n; z/=n;}};

	// operators
	/// vector + vector operator
	friend CVector3 operator + (const CVector3& v1,const CVector3& v2)
		{ return CVector3(v1.x+v2.x,v1.y+v2.y,v1.z+v2.z);};
	/// vector - vector operator
	friend CVector3 operator - (const CVector3& v1,const CVector3& v2)
		{ return CVector3(v1.x-v2.x,v1.y-v2.y,v1.z-v2.z);};
	/// float * vector operator
	friend CVector3 operator * (const float a,const CVector3& v1)
		{ return CVector3(a*v1.x,a*v1.y,a*v1.z);};
	/// vector * float operator
	friend CVector3 operator * (const CVector3& v1,const float a)
		{ return CVector3(a*v1.x,a*v1.y,a*v1.z);};
	/// vector / float operator
	friend CVector3 operator / (const CVector3& v1,const float a)
		{ return CVector3(v1.x/a,v1.y/a,v1.z/a);};
	/// vector += vector operator
	CVector3& operator += (const CVector3& v)
		{ x+=v.x; y+=v.y; z+=v.z; return *this;};
	/// vector -= vector operator
	CVector3& operator -= (const CVector3& v)
		{ x-=v.x; y-=v.y; z-=v.z; return *this;};
	/// vector *= float operator
	CVector3& operator *= (const float a)
		{ x*=a; y*=a; z*=a; return *this;};
	/// vector *= float operator
	CVector3& operator /= (const float a)
		{ x/=a; y/=a; z/=a; return *this;};
	/// unary operator -
	friend CVector3 operator - (const CVector3& v)
		{ return CVector3(-v.x,-v.y,-v.z);};

	void rotateAroundY(float theta)
	{
		float tempx=x;
		float tempz=z;
		float ct=(float)cos(theta);
		float st=(float)sin(theta);

		x=tempx*ct-tempz*st;
		z=tempx*st+tempz*ct;
	}

	friend CArchive& operator << (CArchive& out, const CVector3& vc);
	friend CArchive& operator >> (CArchive& in,CVector3& vc);

#ifdef _DEBUG
	friend CDumpContext& operator << (CDumpContext& out, const CVector3& vc);
#endif
};

#endif // !defined(AFX_VECTORCLASS_H__EE946E20_1D6E_11D4_8D89_00409503B978__INCLUDED_)
