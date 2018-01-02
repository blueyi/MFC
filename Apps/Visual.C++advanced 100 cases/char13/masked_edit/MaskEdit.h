// MaskEdit.h : main header file for the MASKEDIT application
//

#if !defined(AFX_MASKEDIT_H__8F2BD4D4_6425_11D2_96B4_00105A08E437__INCLUDED_)
#define AFX_MASKEDIT_H__8F2BD4D4_6425_11D2_96B4_00105A08E437__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMaskEditApp:
// See MaskEdit.cpp for the implementation of this class
//

class CMaskEditApp : public CWinApp
{
public:
	CMaskEditApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMaskEditApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMaskEditApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MASKEDIT_H__8F2BD4D4_6425_11D2_96B4_00105A08E437__INCLUDED_)
