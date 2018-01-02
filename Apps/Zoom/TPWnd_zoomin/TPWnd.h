// TPWnd.h : main header file for the TPWND application
//

#if !defined(AFX_TPWND_H__A016D035_AC10_46DB_A34F_FB5EBB189BD7__INCLUDED_)
#define AFX_TPWND_H__A016D035_AC10_46DB_A34F_FB5EBB189BD7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTPWndApp:
// See TPWnd.cpp for the implementation of this class
//

class CTPWndApp : public CWinApp
{
public:
	CTPWndApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPWndApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTPWndApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TPWND_H__A016D035_AC10_46DB_A34F_FB5EBB189BD7__INCLUDED_)
