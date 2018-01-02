// PGLLegend.cpp: implementation of the CPGLLegend class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PGL/pgl.h"
#include "PGL/PGLLegend.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CPGLLegend,CPGLText,1);

void CPGLLegend::Serialize(CArchive &archive)
{
    // call base class function first
    // base class is CObject in this case
    CPGLText::Serialize( archive );

    // now do the stuff for our specific class
    if( archive.IsStoring() )
	{
	}
    else
	{
	}
}

#ifdef _DEBUG
void CPGLLegend::Dump( CDumpContext& dc ) const
{
    // call base class function first
    CPGLObject::Dump( dc );

    // now do the stuff for our specific class
	dc << _T("--- CPGLLegend ID ") << GetID() <<_T(" ---\n");
}

void CPGLLegend::AssertValid() const
{
    // call inherited AssertValid first
    CPGLText::AssertValid();
} 
#endif

CPGLLegend::CPGLLegend()
{

}

CPGLLegend::~CPGLLegend()
{

}
