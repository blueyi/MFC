// CxShadeButtonDemo.h : main header file for the CXSHADEBUTTONDEMO application
//

#if !defined(AFX_CXSHADEBUTTONDEMO_H__165779A6_46C9_11D5_B6C0_00E07D8144D0__INCLUDED_)
#define AFX_CXSHADEBUTTONDEMO_H__165779A6_46C9_11D5_B6C0_00E07D8144D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCxShadeButtonDemoApp:
// See CxShadeButtonDemo.cpp for the implementation of this class
//

class CCxShadeButtonDemoApp : public CWinApp
{
public:
	CCxShadeButtonDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCxShadeButtonDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCxShadeButtonDemoApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CXSHADEBUTTONDEMO_H__165779A6_46C9_11D5_B6C0_00E07D8144D0__INCLUDED_)
