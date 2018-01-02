// RTDemo.h : main header file for the RTDemo application
//

#if !defined(AFX_RTDemo_H__12551279_E7E7_11D3_85BC_0008C777FFEE__INCLUDED_)
#define AFX_RTDemo_H__12551279_E7E7_11D3_85BC_0008C777FFEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRTDemoApp:
// See RTDemo.cpp for the implementation of this class
//

class CRTDemoApp : public CWinApp
{
public:
	CRTDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRTDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CRTDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RTDemo_H__12551279_E7E7_11D3_85BC_0008C777FFEE__INCLUDED_)
