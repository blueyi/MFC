// ListCtrlLinkTest.h : main header file for the LISTCTRLLINKTEST application
//

#if !defined(AFX_LISTCTRLLINKTEST_H__168A7C4A_2634_4D52_8C9F_4F8D8E148B6D__INCLUDED_)
#define AFX_LISTCTRLLINKTEST_H__168A7C4A_2634_4D52_8C9F_4F8D8E148B6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CListCtrlLinkTestApp:
// See ListCtrlLinkTest.cpp for the implementation of this class
//

class CListCtrlLinkTestApp : public CWinApp
{
public:
	CListCtrlLinkTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlLinkTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CListCtrlLinkTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCTRLLINKTEST_H__168A7C4A_2634_4D52_8C9F_4F8D8E148B6D__INCLUDED_)
