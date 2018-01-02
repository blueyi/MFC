// EditTest.h : main header file for the EDITTEST application
//

#if !defined(AFX_EDITTEST_H__BBD07297_DB6B_440A_9972_976C2AADD7EE__INCLUDED_)
#define AFX_EDITTEST_H__BBD07297_DB6B_440A_9972_976C2AADD7EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEditTestApp:
// See EditTest.cpp for the implementation of this class
//

class CEditTestApp : public CWinApp
{
public:
	CEditTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEditTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITTEST_H__BBD07297_DB6B_440A_9972_976C2AADD7EE__INCLUDED_)
