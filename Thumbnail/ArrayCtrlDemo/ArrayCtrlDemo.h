/////////////////////////////////////////////////////////////////////////////
// ArrayCtrlDemo.h : main header file for the ArrayCtrlDemo application
//

#if !defined(AFX_ARRAYCTRLDEMO_H__0109BE52_65A4_49D5_88C1_65CD52799093__INCLUDED_)
#define AFX_ARRAYCTRLDEMO_H__0109BE52_65A4_49D5_88C1_65CD52799093__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// ArrayCtrlDemoApp:
// See ArrayCtrlDemo.cpp for the implementation of this class
//

class CArrayCtrlDemoApp : public CWinApp
{
public:
	CArrayCtrlDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArrayCtrlDemoApp)
	public:
	virtual BOOL	InitInstance();
	virtual int		ExitInstance();
	//}}AFX_VIRTUAL

// Members
public:

// Implementation
public:

public:
	//{{AFX_MSG(CArrayCtrlDemoApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARRAYCTRLDEMO_H__0109BE52_65A4_49D5_88C1_65CD52799093__INCLUDED_)
