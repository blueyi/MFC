/********************************************************************
File Name:	ThreeDim.h
Written by: Li Peng, Yang Guang

Copyright(C) XinaoMDT, 2001 -

Purpose:
	This file defines following classes:

History:
	2002/9/5	Extracted from old Point.h, Yang Guang
*********************************************************************/

#ifndef _yg_CThreeDim_h_592002
#define _yg_CThreeDim_h_592002

#include <cfloat>
#include <cmath>

#include "Point.h"

#ifdef GEOMETRY_IMP
   #define CLASS_DECL_GEOMETRY  __declspec(dllexport)
#else
   #define CLASS_DECL_GEOMETRY  __declspec(dllimport)
#endif

namespace Geometry
{
	
	/*! 
		This class represents a abstract point or vector in a three - dimension 
		space, and it also provides some methods.
	*/
	class CLASS_DECL_GEOMETRY CThreeDim
	{
	public:
		double x;
		double y;
		double z;
		
		explicit CThreeDim(double dx = 1, double dy = 0, double dz = 0);

        // \bug I don't think it's valid to convert a CPoint2D object to CThreeDim.
		explicit CThreeDim(const CPoint2D& v);
		CThreeDim(const CThreeDim& v);
		~CThreeDim();
		
		const CThreeDim& operator = (const CThreeDim& rhs);
		const CThreeDim& operator = (const CPoint2D& rhs);
		const CThreeDim& operator *= (double dMultiplicator);
		const CThreeDim& operator /= (double dDivisor);
		const CThreeDim& operator += (const CThreeDim& rhs);
		const CThreeDim& operator -= (const CThreeDim& rhs);
		CThreeDim operator + () const;
		CThreeDim operator - () const;
	    CThreeDim operator * (double dMultiplicator) const;
	    CThreeDim operator + (const CThreeDim& rhs) const;
	    CThreeDim operator / (double dDivisor) const;
	    CThreeDim operator - (const CThreeDim& rhs) const;
	    bool operator == (const CThreeDim& rhs) const;
	    bool operator != (const CThreeDim& rhs) const;

        double Modulus() const;
		bool   Unify();
	};
	
	inline CThreeDim 
	operator * (double lhs, const CThreeDim& rhs)
	{
		return (CThreeDim(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z));
	}
		
	inline CThreeDim::CThreeDim(double dx, double dy, double dz)
		: x(dx), y(dy), z(dz)
	{
	}

	inline CThreeDim::CThreeDim(const CThreeDim& v)
		: x(v.x), y(v.y), z(v.z)
	{
	}

	//! Special constructor, translate a CPoint2D struct to CThreeDim object.
	inline CThreeDim::CThreeDim(const CPoint2D& v)
		: x(v.x), y(v.y), z(0.0)
	{
	}

	//! Destructor
	inline CThreeDim::~CThreeDim()
	{
	}

	//! This function overroads assignment operator.
	/*!
		\param v is the const reference to CThreeDim.
		\return a reference to CThreeDim--*this, it equals the input object v.
	*/
	inline const CThreeDim& 
	CThreeDim::operator=(const CThreeDim &rhs)
	{
		if(this != &rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
		}
		return (*this);
	}

	/*! 
		This function overroads assignment operator, and at the same time it 
		translates a CPoint2D struct to CThreeDim object.
	*/
	inline const CThreeDim& 
	CThreeDim::operator=(const CPoint2D& v)
	{
		x = v.x;
		y = v.y;
		z = 0;
		return (*this);
	}

	//! Overroad *=(multiply-assign) operation.
	/*!
		\param dMultiplicator Const reference to dboule.
		\return the CThreeDim after be multiplied by dMultiplicator.
	*/
	inline const CThreeDim& 
	CThreeDim::operator *= (double dMultiplicator)
	{
		x *= dMultiplicator;
		y *= dMultiplicator;
		z *= dMultiplicator;
		return (*this);
	}

	//! Overroad /=(division-assign) operation.
	/*!
		\param const dDivisor is a reference to double.
		\return the quotient of *this and dDivisor.
	*/
	inline const CThreeDim& 
	CThreeDim::operator /= (double dDivisor)
	{
		// The divisor should not equal zero, otherwise overflow.
		assert(dDivisor != 0);

		x /= dDivisor;
		y /= dDivisor;
		z /= dDivisor;
		return (*this);
	}

	//! Overroad +(addition) operation.
	/*!
		\param v Const reference to CThreeDim.
		\return the CThreeDim after be added by v.
	*/
	inline const CThreeDim& 
	CThreeDim::operator+=(const CThreeDim& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return (*this);
	}

	//! Overroad binary -(subtraction) operation.
	/*!
		\param v Const reference to CThreeDim.
		\return the CThreeDim after be subtracted by v.
	*/
	inline const CThreeDim& 
	CThreeDim::operator-=(const CThreeDim& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return (*this);
	}

	//! This function overroads unary +(Addition) operator.
	/*!
		\return return a CThreeDim object without changed.
	*/
	inline CThreeDim CThreeDim::operator+() const
	{
		return (*this);
	}

	//! This function overroads unary -(subtraction) operator.
	/*!
		\return return a negative CThreeDim.
	*/
	inline CThreeDim CThreeDim::operator-() const
	{
		return (CThreeDim(-x, -y, -z));
	}

	//! This function get the modulus of CThreeDim.
	/*!
		\return The modulus of CThreeDim.
	*/
	inline double CThreeDim::Modulus() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	/*! 
		This function is used to unify the CThreeDim object, let its modulus equal
		one.
	*/
	/*!
		\return \a true if it can be unified, \a false otherwise.
	*/
	inline bool CThreeDim::Unify()
	{
		double modular = this->Modulus();
		if(fabs(modular) <= FLT_EPSILON)
		{
			x = y = z = 0.0;
			return false;
		}
		else 
		{
			x /= modular;
			y /= modular;
			z /= modular;
			return true;
		}
	}

	//! Friend function, overroad *(multiply) operator.
	/*!
		\param dMultiplicator Value used to multiply the CThreeDim object.
		\return w is the product of v and dMuliplicator.
	*/
	inline CThreeDim 
	CThreeDim::operator * (double rhs) const
	{
		return (CThreeDim(x * rhs, y * rhs, z * rhs));
	}

	//! Friend function, overroad +(addition) operator.
	/*!
		\param const u is a reference to CThreeDim.
		\param const v is a reference to CThreeDim.
		\return w is the sum of u and v.
	*/
	inline CThreeDim 
	CThreeDim::operator + (const CThreeDim& rhs) const
	{
		return (CThreeDim(x + rhs.x, y + rhs.y, z + rhs.z));
	}

	//! Friend function, overroad -(subtraction) operator.
	/*!
		\param const u is a reference to CThreeDim.
		\param const v is a reference to CThreeDim.
		\return w is the minus of u and v.
	*/
	inline CThreeDim 
	CThreeDim::operator-(const CThreeDim& rhs) const
	{
		return (CThreeDim(x - rhs.x, y - rhs.y, z - rhs.z));
	}

	//! Friend function, overroad /(divison) operator.
	/*!
		\param const v is a reference to CThreeDim.
		\param const dDivisor is a reference to double.
		\return w is the quotient of v and dDivisor.
	*/
	inline CThreeDim 
	CThreeDim::operator/(double dDivisor) const
	{
		// The divisor should not equal zero, otherwise overflow.
		assert(dDivisor != 0);
		return (CThreeDim(x / dDivisor, y / dDivisor, z / dDivisor));
	}

	//! Overloaded == operator to compare two CThreeDim objects.
	/*!
		\param rhs CThreeDim object to be compared with this.
		\return \a true if \a rhs equals this, \a false otherwise.
	*/
	inline bool 
	CThreeDim::operator==(const CThreeDim& rhs) const
	{
		return ((fabs(rhs.x - x) < FLT_EPSILON) && 
			(fabs(rhs.y - y) < FLT_EPSILON) && 
			(fabs(rhs.z - z) < FLT_EPSILON));
	}

	//! Overloaded != operator to compare two CThreeDim objects.
	/*!
		\param rhs CThreeDim object to be compared with this.
		\return \a false if \a rhs equals this, \a true otherwise.
	*/
	inline bool 
	CThreeDim::operator!=(const CThreeDim& rhs) const 
	{
		return !((*this) == rhs);
	}

}   // namespace Geometry
#endif
