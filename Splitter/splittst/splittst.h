// splittst.h : main header file for the SPLITTST application
//

#if !defined(AFX_SPLITTST_H__FA98B70B_D0B7_11D3_BC39_00C04F602FEE__INCLUDED_)
#define AFX_SPLITTST_H__FA98B70B_D0B7_11D3_BC39_00C04F602FEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSplittstApp:
// See splittst.cpp for the implementation of this class
//

class CSplittstApp : public CWinApp
{
public:
	CSplittstApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplittstApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSplittstApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLITTST_H__FA98B70B_D0B7_11D3_BC39_00C04F602FEE__INCLUDED_)
