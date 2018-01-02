// ListSubclass.h : main header file for the LISTSUBCLASS application
//

#if !defined(AFX_LISTSUBCLASS_H__FCAFAD46_796F_11D5_AD86_B1D3CD2E4211__INCLUDED_)
#define AFX_LISTSUBCLASS_H__FCAFAD46_796F_11D5_AD86_B1D3CD2E4211__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CListSubclassApp:
// See ListSubclass.cpp for the implementation of this class
//

class CListSubclassApp : public CWinApp
{
public:
	CListSubclassApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListSubclassApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CListSubclassApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTSUBCLASS_H__FCAFAD46_796F_11D5_AD86_B1D3CD2E4211__INCLUDED_)
