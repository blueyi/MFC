// WellDemo.h : main header file for the WELLDEMO application
//

#if !defined(AFX_WELLDEMO_H__52C34ECB_C197_4D38_B441_68EB7E2E17CF__INCLUDED_)
#define AFX_WELLDEMO_H__52C34ECB_C197_4D38_B441_68EB7E2E17CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWellDemoApp:
// See WellDemo.cpp for the implementation of this class
//

class CWellDemoApp : public CWinApp
{
public:
	CWellDemoApp();
	ULONG_PTR m_gdiplusToken;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWellDemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWellDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WELLDEMO_H__52C34ECB_C197_4D38_B441_68EB7E2E17CF__INCLUDED_)
