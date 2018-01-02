// ExpandDialog.h : main header file for the EXPANDDIALOG application
//

#if !defined(AFX_EXPANDDIALOG_H__866E8705_EBC8_11D4_AFC0_9AFBB6000000__INCLUDED_)
#define AFX_EXPANDDIALOG_H__866E8705_EBC8_11D4_AFC0_9AFBB6000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CExpandDialogApp:
// See ExpandDialog.cpp for the implementation of this class
//

class CExpandDialogApp : public CWinApp
{
public:
	CExpandDialogApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExpandDialogApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CExpandDialogApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPANDDIALOG_H__866E8705_EBC8_11D4_AFC0_9AFBB6000000__INCLUDED_)
