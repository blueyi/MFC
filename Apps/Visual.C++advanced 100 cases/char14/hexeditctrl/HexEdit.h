// HexEdit.h : main header file for the HEXEDIT application
//

#if !defined(AFX_HEXEDIT_H__CF147E4E_214B_11D2_B9F9_0000E829B15A__INCLUDED_)
#define AFX_HEXEDIT_H__CF147E4E_214B_11D2_B9F9_0000E829B15A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHexEditApp:
// See HexEdit.cpp for the implementation of this class
//

class CHexEditApp : public CWinApp
{
public:
	CHexEditApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHexEditApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHexEditApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEXEDIT_H__CF147E4E_214B_11D2_B9F9_0000E829B15A__INCLUDED_)
