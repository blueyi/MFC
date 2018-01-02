// IconLBDemo.h : main header file for the ICONLBDEMO application
//

#if !defined(AFX_ICONLBDEMO_H__DA462425_5FCA_11D5_BBEE_0050BAD90EEA__INCLUDED_)
#define AFX_ICONLBDEMO_H__DA462425_5FCA_11D5_BBEE_0050BAD90EEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIconLBDemoApp:
// See IconLBDemo.cpp for the implementation of this class
//

class CIconLBDemoApp : public CWinApp
{
public:
	CIconLBDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIconLBDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIconLBDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ICONLBDEMO_H__DA462425_5FCA_11D5_BBEE_0050BAD90EEA__INCLUDED_)
