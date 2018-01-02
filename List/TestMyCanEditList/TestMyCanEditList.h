// TestMyCanEditList.h : main header file for the TESTMYCANEDITLIST application
//

#if !defined(AFX_TESTMYCANEDITLIST_H__A1B42CF3_4F98_46DB_AB23_8E6DF7AFE459__INCLUDED_)
#define AFX_TESTMYCANEDITLIST_H__A1B42CF3_4F98_46DB_AB23_8E6DF7AFE459__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestMyCanEditListApp:
// See TestMyCanEditList.cpp for the implementation of this class
//

class CTestMyCanEditListApp : public CWinApp
{
public:
	CTestMyCanEditListApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestMyCanEditListApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTestMyCanEditListApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTMYCANEDITLIST_H__A1B42CF3_4F98_46DB_AB23_8E6DF7AFE459__INCLUDED_)
