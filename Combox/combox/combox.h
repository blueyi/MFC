// combox.h : main header file for the COMBOX application
//

#if !defined(AFX_COMBOX_H__10F3E167_B2B9_4ACE_B020_B1568A6669EB__INCLUDED_)
#define AFX_COMBOX_H__10F3E167_B2B9_4ACE_B020_B1568A6669EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CComboxApp:
// See combox.cpp for the implementation of this class
//

class CComboxApp : public CWinApp
{
public:
	CComboxApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboxApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CComboxApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOX_H__10F3E167_B2B9_4ACE_B020_B1568A6669EB__INCLUDED_)
