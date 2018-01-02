// CustDlg.h : main header file for the CUSTDLG application
//

#if !defined(AFX_CUSTDLG_H__5B874566_F463_43F8_AE0C_8079B72E18E5__INCLUDED_)
#define AFX_CUSTDLG_H__5B874566_F463_43F8_AE0C_8079B72E18E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCustDlgApp:
// See CustDlg.cpp for the implementation of this class
//

class CCustDlgApp : public CWinApp
{
public:
	CCustDlgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustDlgApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCustDlgApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTDLG_H__5B874566_F463_43F8_AE0C_8079B72E18E5__INCLUDED_)
