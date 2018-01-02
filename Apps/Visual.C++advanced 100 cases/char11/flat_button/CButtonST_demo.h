// CButtonST_demo.h : main header file for the CBUTTONST_DEMO application
//

#if !defined(AFX_CBUTTONST_DEMO_H__E0078DA5_0782_11D2_8E55_9E80D52A2535__INCLUDED_)
#define AFX_CBUTTONST_DEMO_H__E0078DA5_0782_11D2_8E55_9E80D52A2535__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CButtonST_App
//

class CButtonST_App : public CWinApp
{
public:
	CButtonST_App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CButtonST_App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CButtonST_App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CBUTTONST_DEMO_H__E0078DA5_0782_11D2_8E55_9E80D52A2535__INCLUDED_)
