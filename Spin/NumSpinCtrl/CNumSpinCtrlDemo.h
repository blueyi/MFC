// CNumSpinCtrlDemo.h : main header file for the CNUMSPINCTRLDEMO application
//

#if !defined(AFX_CNUMSPINCTRLDEMO_H__22186F9B_BDA5_41B9_8620_48985781AC59__INCLUDED_)
#define AFX_CNUMSPINCTRLDEMO_H__22186F9B_BDA5_41B9_8620_48985781AC59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCNumSpinCtrlDemoApp:
// See CNumSpinCtrlDemo.cpp for the implementation of this class
//

class CCNumSpinCtrlDemoApp : public CWinApp
{
public:
	CCNumSpinCtrlDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCNumSpinCtrlDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCNumSpinCtrlDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNUMSPINCTRLDEMO_H__22186F9B_BDA5_41B9_8620_48985781AC59__INCLUDED_)
