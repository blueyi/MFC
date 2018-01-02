// StdioFileTest.h : main header file for the STDIOFILETEST application
//

#if !defined(AFX_STDIOFILETEST_H__A233A561_344D_4F46_876C_DBF422EBE8CA__INCLUDED_)
#define AFX_STDIOFILETEST_H__A233A561_344D_4F46_876C_DBF422EBE8CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CStdioFileTestApp:
// See StdioFileTest.cpp for the implementation of this class
//

class CStdioFileTestApp : public CWinApp
{
public:
	CStdioFileTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStdioFileTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CStdioFileTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDIOFILETEST_H__A233A561_344D_4F46_876C_DBF422EBE8CA__INCLUDED_)
