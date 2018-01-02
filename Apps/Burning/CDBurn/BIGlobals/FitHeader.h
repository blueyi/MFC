#ifndef __FITHEADER_H__
#define __FITHEADER_H__

#include <math.h>

// Numerics
const double PI = 3.1415926535898; // 3.1415926535897932384626

#define clip(v, a, b)			( (v) < (a)? (v) = (a) : ( (v) > (b)? (v) = (b) : (v) ) )

#define FLOAT_ZERO			1.0e-30

const double cnstEpsilon_large	= 1e-8;
const double cnstEpsilon		= 1e-10; // 1e-8;
const double cnstEpsilon_small	= 1e-15;

#define IsEqual(f1, f2)		(fabs( (f1) - (f2) ) < cnstEpsilon)
#define IsZero(a)			(fabs(a) < cnstEpsilon)


#define ROUND(v)		((v) > 0? (int)((v) + 0.5) : (int)((v) - 0.5))

template <class T> SWAP (T& a, T& b)
{
	T t;
	t = a;
	a = b;
	b = t;
}


typedef struct {
	float real;
	float image;
} COMPLEX;

#define SwapComplex(C1, C2)		(SWAP(C1.real, C2.real), SWAP(C1.image, C2.image))

#define MODULUS(fRe, fIm)		sqrt((fRe)*(fRe) + (fIm)*(fIm))
float AFX_EXT_API Modulus(float fReal, float fImag); // calculate the modulus of a complex data
int AFX_EXT_API GetFFTPoints(int nDataPoints);


#endif // __FITHEADER_H__
