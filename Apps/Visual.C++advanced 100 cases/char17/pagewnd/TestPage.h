// TestPage.h : main header file for the TESTPAGE application
//

#if !defined(AFX_TESTPAGE_H__A2438D35_1B15_11D2_880E_00C0DFA97DA3__INCLUDED_)
#define AFX_TESTPAGE_H__A2438D35_1B15_11D2_880E_00C0DFA97DA3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestPageApp:
// See TestPage.cpp for the implementation of this class
//

class CTestPageApp : public CWinApp
{
public:
	CTestPageApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestPageApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestPageApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTPAGE_H__A2438D35_1B15_11D2_880E_00C0DFA97DA3__INCLUDED_)
