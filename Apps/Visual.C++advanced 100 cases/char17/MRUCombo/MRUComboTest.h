// MRUComboTest.h : main header file for the MRUCOMBOTEST application
//

#if !defined(AFX_MRUCOMBOTEST_H__BDE24F07_4632_11D2_9505_D07F50C10000__INCLUDED_)
#define AFX_MRUCOMBOTEST_H__BDE24F07_4632_11D2_9505_D07F50C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMRUComboTestApp:
// See MRUComboTest.cpp for the implementation of this class
//

class CMRUComboTestApp : public CWinApp
{
public:
	CMRUComboTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMRUComboTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMRUComboTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MRUCOMBOTEST_H__BDE24F07_4632_11D2_9505_D07F50C10000__INCLUDED_)
