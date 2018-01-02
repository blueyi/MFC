// ValidatingEditDemo.h : main header file for the VALIDATINGEDITDEMO application
//

#if !defined(AFX_VALIDATINGEDITDEMO_H__47C40B3C_B2C8_11D5_938E_0002A50C1C28__INCLUDED_)
#define AFX_VALIDATINGEDITDEMO_H__47C40B3C_B2C8_11D5_938E_0002A50C1C28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CValidatingEditDemoApp:
// See ValidatingEditDemo.cpp for the implementation of this class
//

class CValidatingEditDemoApp : public CWinApp
{
public:
	CValidatingEditDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CValidatingEditDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CValidatingEditDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VALIDATINGEDITDEMO_H__47C40B3C_B2C8_11D5_938E_0002A50C1C28__INCLUDED_)
