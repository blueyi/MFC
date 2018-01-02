// TestDialog.h : main header file for the TESTDIALOG application
//

#if !defined(AFX_TESTDIALOG_H__CCAACD75_1F93_11D2_864F_0040055C08D9__INCLUDED_)
#define AFX_TESTDIALOG_H__CCAACD75_1F93_11D2_864F_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestDialogApp:
// See TestDialog.cpp for the implementation of this class
//

class CTestDialogApp : public CWinApp
{
public:
	CTestDialogApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDialogApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestDialogApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDIALOG_H__CCAACD75_1F93_11D2_864F_0040055C08D9__INCLUDED_)
