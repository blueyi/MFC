// check.h : main header file for the CHECK application
//

#if !defined(AFX_CHECK_H__41BE689B_D11A_420D_B91F_23E0C4DDA596__INCLUDED_)
#define AFX_CHECK_H__41BE689B_D11A_420D_B91F_23E0C4DDA596__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCheckApp:
// See check.cpp for the implementation of this class
//

class CCheckApp : public CWinApp
{
public:
	CCheckApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCheckApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECK_H__41BE689B_D11A_420D_B91F_23E0C4DDA596__INCLUDED_)
