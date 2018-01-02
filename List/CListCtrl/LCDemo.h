// LCDemo.h : main header file for the LCDEMO application
//

#if !defined(AFX_LCDEMO_H__7C7E6147_1A6A_4107_B475_679B1AB2CD70__INCLUDED_)
#define AFX_LCDEMO_H__7C7E6147_1A6A_4107_B475_679B1AB2CD70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLCDemoApp:
// See LCDemo.cpp for the implementation of this class
//

class CLCDemoApp : public CWinApp
{
public:
	CLCDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLCDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLCDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LCDEMO_H__7C7E6147_1A6A_4107_B475_679B1AB2CD70__INCLUDED_)
