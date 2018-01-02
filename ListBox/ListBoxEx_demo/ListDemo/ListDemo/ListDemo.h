// ListDemo.h : main header file for the LISTDEMO application
//

#if !defined(AFX_LISTDEMO_H__E503C828_836A_11D5_AD87_8686F2D82715__INCLUDED_)
#define AFX_LISTDEMO_H__E503C828_836A_11D5_AD87_8686F2D82715__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CListDemoApp:
// See ListDemo.cpp for the implementation of this class
//

class CListDemoApp : public CWinApp
{
public:
	CListDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CListDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTDEMO_H__E503C828_836A_11D5_AD87_8686F2D82715__INCLUDED_)
