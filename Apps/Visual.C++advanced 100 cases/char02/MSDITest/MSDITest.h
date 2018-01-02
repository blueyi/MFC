// MSDITest.h : main header file for the MSDITEST application
//

#if !defined(AFX_MSDITEST_H__58EAB965_E2C7_11D4_AF92_C0ABC2000000__INCLUDED_)
#define AFX_MSDITEST_H__58EAB965_E2C7_11D4_AF92_C0ABC2000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "MSDIApp.h"

/////////////////////////////////////////////////////////////////////////////
// CMSDITestApp:
// See MSDITest.cpp for the implementation of this class
//

class CMSDITestApp : public CMSDIWinApp//wb modify
{
public:
	CMSDITestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMSDITestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMSDITestApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CMSDITestApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSDITEST_H__58EAB965_E2C7_11D4_AF92_C0ABC2000000__INCLUDED_)
