// TestList6.h : main header file for the TESTLIST6 application
//

#if !defined(AFX_TESTLIST6_H__D33CF0BB_A213_11E0_9065_0050BF29759A__INCLUDED_)
#define AFX_TESTLIST6_H__D33CF0BB_A213_11E0_9065_0050BF29759A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestList6App:
// See TestList6.cpp for the implementation of this class
//

class CTestList6App : public CWinApp
{
public:
	CTestList6App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestList6App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTestList6App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTLIST6_H__D33CF0BB_A213_11E0_9065_0050BF29759A__INCLUDED_)
