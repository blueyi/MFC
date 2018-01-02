// CShut.h : main header file for the CSHUT application
//

#if !defined(AFX_CSHUT_H__361D6609_15D2_4CF4_AC2F_CF1C52C5C7FC__INCLUDED_)
#define AFX_CSHUT_H__361D6609_15D2_4CF4_AC2F_CF1C52C5C7FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCShutApp:
// See CShut.cpp for the implementation of this class
//

class CCShutApp : public CWinApp
{
public:
	CCShutApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCShutApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCShutApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSHUT_H__361D6609_15D2_4CF4_AC2F_CF1C52C5C7FC__INCLUDED_)
