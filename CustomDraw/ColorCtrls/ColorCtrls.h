// ColorCtrls.h : main header file for the COLORCTRLS application
//

#if !defined(AFX_COLORCTRLS_H__D39DF790_CA36_11D5_831E_0002A5AA1506__INCLUDED_)
#define AFX_COLORCTRLS_H__D39DF790_CA36_11D5_831E_0002A5AA1506__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CColorCtrlsApp:
// See ColorCtrls.cpp for the implementation of this class
//

class CColorCtrlsApp : public CWinApp
{
public:
	CColorCtrlsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorCtrlsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CColorCtrlsApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORCTRLS_H__D39DF790_CA36_11D5_831E_0002A5AA1506__INCLUDED_)
