// Numeric.cpp
#include "stdafx.h"
#include "BIGlobals.h"

///////////////////////////////////////////////////////////////////////////
// Globals common operators
int GetFFTPoints(int nDataPoints)
{
    int nResult = 2;
    while(nDataPoints > nResult)
        nResult *= 2;
    return nResult;
}

float Modulus(float fReal, float fImag)
{
	return MODULUS(fReal, fImag);
}
