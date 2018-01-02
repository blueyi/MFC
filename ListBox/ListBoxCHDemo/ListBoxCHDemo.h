// ListBoxCHDemo.h : main header file for the LISTBOXCHDEMO application
//

#if !defined(AFX_LISTBOXCHDEMO_H__ED804CA5_C5B1_11D6_8D12_004033579553__INCLUDED_)
#define AFX_LISTBOXCHDEMO_H__ED804CA5_C5B1_11D6_8D12_004033579553__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CListBoxCHDemoApp:
// See ListBoxCHDemo.cpp for the implementation of this class
//

class CListBoxCHDemoApp : public CWinApp
{
public:
	CListBoxCHDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListBoxCHDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CListBoxCHDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTBOXCHDEMO_H__ED804CA5_C5B1_11D6_8D12_004033579553__INCLUDED_)
