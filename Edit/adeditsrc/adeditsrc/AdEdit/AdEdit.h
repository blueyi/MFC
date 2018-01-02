// AdEdit.h : main header file for the ADEDIT application
//

#if !defined(AFX_ADEDIT_H__0370AAEE_2768_47F1_B62A_24A2D3311062__INCLUDED_)
#define AFX_ADEDIT_H__0370AAEE_2768_47F1_B62A_24A2D3311062__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAdEditApp:
// See AdEdit.cpp for the implementation of this class
//

class CAdEditApp : public CWinApp
{
public:
	CAdEditApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdEditApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAdEditApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADEDIT_H__0370AAEE_2768_47F1_B62A_24A2D3311062__INCLUDED_)
