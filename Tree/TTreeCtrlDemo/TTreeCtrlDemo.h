// TTreeCtrlDemo.h : main header file for the TTREECTRLDEMO application
//

#if !defined(AFX_TTREECTRLDEMO_H__F5E88A60_2CF8_4AF2_B66D_E2C16A905966__INCLUDED_)
#define AFX_TTREECTRLDEMO_H__F5E88A60_2CF8_4AF2_B66D_E2C16A905966__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTTreeCtrlDemoApp:
// See TTreeCtrlDemo.cpp for the implementation of this class
//

class CTTreeCtrlDemoApp : public CWinApp
{
public:
	CTTreeCtrlDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTTreeCtrlDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTTreeCtrlDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TTREECTRLDEMO_H__F5E88A60_2CF8_4AF2_B66D_E2C16A905966__INCLUDED_)
