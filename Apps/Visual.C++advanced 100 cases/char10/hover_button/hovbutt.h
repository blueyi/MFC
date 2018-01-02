// hovbutt.h : main header file for the HOVBUTT application
//

#if !defined(AFX_HOVBUTT_H__11557374_628E_11D2_81B5_0020AFC24C58__INCLUDED_)
#define AFX_HOVBUTT_H__11557374_628E_11D2_81B5_0020AFC24C58__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHovbuttApp:
// See hovbutt.cpp for the implementation of this class
//

class CHovbuttApp : public CWinApp
{
public:
	CHovbuttApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHovbuttApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHovbuttApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOVBUTT_H__11557374_628E_11D2_81B5_0020AFC24C58__INCLUDED_)
