// DBBTest.h : main header file for the DBBTEST application
// Download by http://www.codefans.net

#if !defined(AFX_DBBTEST_H__97EADD9C_01FE_4F8F_8AC4_B9278876DC01__INCLUDED_)
#define AFX_DBBTEST_H__97EADD9C_01FE_4F8F_8AC4_B9278876DC01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDBBTestApp:
// See DBBTest.cpp for the implementation of this class
//

class CDBBTestApp : public CWinApp
{
public:
	CDBBTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBBTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDBBTestApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBBTEST_H__97EADD9C_01FE_4F8F_8AC4_B9278876DC01__INCLUDED_)
