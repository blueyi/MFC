// TestCurve.h : main header file for the TESTCURVE application
//

#if !defined(AFX_TESTCURVE_H__B2CD3D9C_70FD_40A1_A778_8877DC4BD6F8__INCLUDED_)
#define AFX_TESTCURVE_H__B2CD3D9C_70FD_40A1_A778_8877DC4BD6F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestCurveApp:
// See TestCurve.cpp for the implementation of this class
//

class CTestCurveApp : public CWinApp
{
public:
	CTestCurveApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestCurveApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestCurveApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCURVE_H__B2CD3D9C_70FD_40A1_A778_8877DC4BD6F8__INCLUDED_)
