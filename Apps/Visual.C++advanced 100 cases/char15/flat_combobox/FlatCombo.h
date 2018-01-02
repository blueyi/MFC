// FlatCombo.h : main header file for the FLATCOMBO application
//

#if !defined(AFX_FLATCOMBO_H__3422A0B7_4F3A_11D2_957B_0040053E0F5B__INCLUDED_)
#define AFX_FLATCOMBO_H__3422A0B7_4F3A_11D2_957B_0040053E0F5B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFlatComboApp:
// See FlatCombo.cpp for the implementation of this class
//

class CFlatComboApp : public CWinApp
{
public:
	CFlatComboApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlatComboApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFlatComboApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLATCOMBO_H__3422A0B7_4F3A_11D2_957B_0040053E0F5B__INCLUDED_)
