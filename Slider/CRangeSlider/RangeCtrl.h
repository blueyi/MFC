// RangeCtrl.h : main header file for the RANGECTRL application
//

#if !defined(AFX_RANGECTRL_H__25E884C6_14DD_43E8_9DF2_D91186907E56__INCLUDED_)
#define AFX_RANGECTRL_H__25E884C6_14DD_43E8_9DF2_D91186907E56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRangeCtrlApp:
// See RangeCtrl.cpp for the implementation of this class
//

class CRangeCtrlApp : public CWinApp
{
public:
	CRangeCtrlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRangeCtrlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRangeCtrlApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RANGECTRL_H__25E884C6_14DD_43E8_9DF2_D91186907E56__INCLUDED_)
