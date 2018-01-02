// fontsTest.h : main header file for the FONTSTEST application
//

#if !defined(AFX_FONTSTEST_H__8D233C17_8B2A_11D1_92BB_006097AEFD47__INCLUDED_)
#define AFX_FONTSTEST_H__8D233C17_8B2A_11D1_92BB_006097AEFD47__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFontsTestApp:
// See fontsTest.cpp for the implementation of this class
//

class CFontsTestApp : public CWinApp
{
public:
	CFontsTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFontsTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFontsTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FONTSTEST_H__8D233C17_8B2A_11D1_92BB_006097AEFD47__INCLUDED_)
