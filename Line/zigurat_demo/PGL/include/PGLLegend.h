// PGLLegend.h: interface for the CPGLLegend class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PGLLEGEND_H__D9B6DFE3_F601_4CCC_B09A_518A7AE5CAE4__INCLUDED_)
#define AFX_PGLLEGEND_H__D9B6DFE3_F601_4CCC_B09A_518A7AE5CAE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PGLText.h"

class CPGLLegend : public CPGLText  
{
DECLARE_SERIAL(CPGLLegend);
public:
	CPGLLegend();
	virtual ~CPGLLegend();

	// Serialize functions
	void Serialize(CArchive& archive);

	// Debuggin functions
	#ifdef _DEBUG
	    virtual void Dump( CDumpContext& dc ) const;
	    virtual void AssertValid() const;    // Override
	#endif
};

#endif // !defined(AFX_PGLLEGEND_H__D9B6DFE3_F601_4CCC_B09A_518A7AE5CAE4__INCLUDED_)
