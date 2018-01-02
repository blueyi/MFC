// HDDemo.h : main header file for the HDDEMO application
//

#if !defined(AFX_HDDEMO_H__00C54325_702E_11D2_ABF7_CCFAF0973072__INCLUDED_)
#define AFX_HDDEMO_H__00C54325_702E_11D2_ABF7_CCFAF0973072__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHDDemoApp:
// See HDDemo.cpp for the implementation of this class
//

class CHDDemoApp : public CWinApp
{
public:
	CString m_strUserName;
	CString m_strProductId;
	CString m_strProductVer;
	CString m_strCompName;


	CHDDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHDDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CHDDemoApp)
	afx_msg void OnAppAbout();
	afx_msg void OnDemoInputparameters();
	afx_msg void OnDemoNoparameters();
	afx_msg void OnDemoReturnvalues();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HDDEMO_H__00C54325_702E_11D2_ABF7_CCFAF0973072__INCLUDED_)
