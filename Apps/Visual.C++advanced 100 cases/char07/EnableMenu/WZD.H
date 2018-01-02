// Wzd.h : main header file for the WZD application
//

#if !defined(AFX_WZD_H__CB8C416D_B204_11D1_9B3E_00AA003D8695__INCLUDED_)
#define AFX_WZD_H__CB8C416D_B204_11D1_9B3E_00AA003D8695__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CWzdApp:
// See Wzd.cpp for the implementation of this class
//

class CWzdApp : public CWinApp
{
public:
	CWzdApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWzdApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWzdApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WZD_H__CB8C416D_B204_11D1_9B3E_00AA003D8695__INCLUDED_)
