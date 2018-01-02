// CVector3.cpp: implementation of the CVector3 class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "vector3.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CArchive& operator << (CArchive& out, const CVector3& vc)
{
	out<<vc.x<<vc.y<<vc.z;
	return out;
}
CArchive& operator >> (CArchive& in,CVector3& vc)
{
	in>>vc.x>>vc.y>>vc.z;
	return in;
}

#ifdef _DEBUG

CDumpContext& operator << (CDumpContext& out, const CVector3& vc)
{
	out<<vc.x<<" "<<vc.y<<" "<<vc.z;
	return out;
}

#endif
