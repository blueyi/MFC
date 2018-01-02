// XPBtn_Scroll.h : main header file for the XPBTN_SCROLL application
//

#if !defined(AFX_XPBTN_SCROLL_H__0655EDE1_E3B5_4C44_9A71_54525F867D79__INCLUDED_)
#define AFX_XPBTN_SCROLL_H__0655EDE1_E3B5_4C44_9A71_54525F867D79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CXPBtn_ScrollApp:
// See XPBtn_Scroll.cpp for the implementation of this class
//

class CXPBtn_ScrollApp : public CWinApp
{
public:
		CXPBtn_ScrollApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXPBtn_ScrollApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CXPBtn_ScrollApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XPBTN_SCROLL_H__0655EDE1_E3B5_4C44_9A71_54525F867D79__INCLUDED_)
