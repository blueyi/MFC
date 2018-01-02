// ButtonSub.h : main header file for the BUTTONSUB application
//

#if !defined(AFX_BUTTONSUB_H__D6FA7DDB_967D_4A51_B9C2_53F831C90970__INCLUDED_)
#define AFX_BUTTONSUB_H__D6FA7DDB_967D_4A51_B9C2_53F831C90970__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CButtonSubApp:
// See ButtonSub.cpp for the implementation of this class
//

class CButtonSubApp : public CWinApp
{
public:
	CButtonSubApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CButtonSubApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CButtonSubApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTTONSUB_H__D6FA7DDB_967D_4A51_B9C2_53F831C90970__INCLUDED_)
