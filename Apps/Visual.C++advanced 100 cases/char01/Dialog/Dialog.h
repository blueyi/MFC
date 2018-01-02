// Dialog.h : main header file for the DIALOG application
//

#if !defined(AFX_DIALOG_H__32913E15_6D4A_11D0_B063_E8509A000000__INCLUDED_)
#define AFX_DIALOG_H__32913E15_6D4A_11D0_B063_E8509A000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDialogApp:
// See Dialog.cpp for the implementation of this class
//

class CDialogApp : public CWinApp
{
public:
	CDialogApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDialogApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_H__32913E15_6D4A_11D0_B063_E8509A000000__INCLUDED_)
