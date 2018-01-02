// GradualChange.h : main header file for the GRADUALCHANGE application
//

#if !defined(AFX_GRADUALCHANGE_H__E1BE1F3C_3404_41DF_8FC3_1E926B20D61A__INCLUDED_)
#define AFX_GRADUALCHANGE_H__E1BE1F3C_3404_41DF_8FC3_1E926B20D61A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGradualChangeApp:
// See GradualChange.cpp for the implementation of this class
//

class CGradualChangeApp : public CWinApp
{
public:
	CGradualChangeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGradualChangeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CGradualChangeApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRADUALCHANGE_H__E1BE1F3C_3404_41DF_8FC3_1E926B20D61A__INCLUDED_)
