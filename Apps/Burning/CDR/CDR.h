// CDR.h : main header file for the CDR application
//

#if !defined(AFX_CDR_H__566B7080_8576_4C54_B78E_100315BE49C3__INCLUDED_)
#define AFX_CDR_H__566B7080_8576_4C54_B78E_100315BE49C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCDRApp:
// See CDR.cpp for the implementation of this class
//

class CCDRApp : public CWinApp
{
public:
	CCDRApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCDRApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCDRApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDR_H__566B7080_8576_4C54_B78E_100315BE49C3__INCLUDED_)
