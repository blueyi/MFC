// MyInterface.h : main header file for the MYINTERFACE application
//

#if !defined(AFX_MYINTERFACE_H__E1B4C9C5_DF44_11D4_AF84_18E6A0000000__INCLUDED_)
#define AFX_MYINTERFACE_H__E1B4C9C5_DF44_11D4_AF84_18E6A0000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyInterfaceApp:
// See MyInterface.cpp for the implementation of this class
//

class CMyInterfaceApp : public CWinApp
{
public:
	CMyInterfaceApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyInterfaceApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMyInterfaceApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYINTERFACE_H__E1B4C9C5_DF44_11D4_AF84_18E6A0000000__INCLUDED_)
