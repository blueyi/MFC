// MultiWindow.h : main header file for the MULTIWINDOW application
//

#if !defined(AFX_MULTIWINDOW_H__32913E23_6D4A_11D0_B063_E8509A000000__INCLUDED_)
#define AFX_MULTIWINDOW_H__32913E23_6D4A_11D0_B063_E8509A000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMultiWindowApp:
// See MultiWindow.cpp for the implementation of this class
//

class CMultiWindowApp : public CWinApp
{
public:
	CMultiWindowApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiWindowApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMultiWindowApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTIWINDOW_H__32913E23_6D4A_11D0_B063_E8509A000000__INCLUDED_)
