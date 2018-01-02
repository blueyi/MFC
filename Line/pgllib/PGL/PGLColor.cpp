// ColorGL.cpp: implementation of the CPGLColor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PGL/PGLColor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CPGLColor, CObject,1);


void CPGLColor::Serialize(CArchive &archive)
{
    // call base class function first
    // base class is CObject in this case
    CObject::Serialize( archive );

    // now do the stuff for our specific class
    if( archive.IsStoring() )
        archive << m_c[0] << m_c[1] << m_c[2] << m_c[3] ;
    else
        archive >> m_c[0] >> m_c[1] >> m_c[2] >> m_c[3];
}

#ifdef _DEBUG
void CPGLColor::Dump( CDumpContext& dc ) const
{
    // call base class function first
    CObject::Dump( dc );

    // now do the stuff for our specific class
    dc << "color : "<< m_c[0] <<
				" " << m_c[1] <<
				" " << m_c[2] <<
				" " << m_c[3] << endl;
}
void CPGLColor::AssertValid() const
{
    // call inherited AssertValid first
    CObject::AssertValid();

    // check members...
    ASSERT( m_c[0]>=0 && m_c[0]<=1); // color is in [0,1]
    ASSERT( m_c[1]>=0 && m_c[1]<=1); // color is in [0,1]
    ASSERT( m_c[2]>=0 && m_c[2]<=1); // color is in [0,1]
    ASSERT( m_c[3]>=0 && m_c[3]<=1); // color is in [0,1]
} 
#endif

