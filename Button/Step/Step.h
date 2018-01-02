// Step.h : main header file for the STEP application
//

#if !defined(AFX_STEP_H__11E86684_263F_11DB_ACFE_0050BA012D9B__INCLUDED_)
#define AFX_STEP_H__11E86684_263F_11DB_ACFE_0050BA012D9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// ZApp:
// See Step.cpp for the implementation of this class
//

class ZApp : public CWinApp
{
public:
	ZApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(ZApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STEP_H__11E86684_263F_11DB_ACFE_0050BA012D9B__INCLUDED_)
