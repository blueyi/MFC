// CViewGL.cpp: implementation of the CViewGL class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ViewGL.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CViewGL,CObject,1);

#ifdef _DEBUG
void CViewGL::AssertValid() const
{
    // call inherited AssertValid first
    CObject::AssertValid();

    // check CViewGL members...
	m_StateGL.AssertValid();

	ASSERT(m_iTx>=0);
	ASSERT(m_iTy>=0);
	ASSERT(m_iWidth>=0);
	ASSERT(m_iHeight>=0);
}

void CViewGL::Dump( CDumpContext& ch ) const
{
    // call base class function first
    CObject::Dump( ch );

    // now do the stuff for our specific class
	ch<<_T("--- CViewGL Object ---\n");
	ch<<_T("width : ")<<m_iWidth<<_T("  height : ")<<m_iHeight<<_T("  Tx : ")<<m_iTx<<_T("  Ty : ")<<m_iTy<<_T("\n");
	m_StateGL.Dump(ch);
} 
#endif

void CViewGL::Serialize( CArchive& archive )
{
    // call base class function first
    // base class is CObject in this case
    CObject::Serialize( archive );
	
    // now do the stuff for our specific class
    if (archive.IsStoring())
	{
		archive<<m_iTx<<m_iTy<<m_iWidth<<m_iHeight;
	}
    else
	{
		archive>>m_iTx>>m_iTy>>m_iWidth>>m_iHeight;
	}
	// 
	m_StateGL.Serialize(archive);

	// needs viewport info
	PostViewportInfo();
	// we need reshaping...
	m_bPostReshape=TRUE;
}
