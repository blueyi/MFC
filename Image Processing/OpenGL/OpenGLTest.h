// OpenGLTest.h : main header file for the OPENGLTEST application
//

#if !defined(AFX_OPENGLTEST_H__412EF9D9_29DD_485C_8E8E_12B7D9F00B78__INCLUDED_)
#define AFX_OPENGLTEST_H__412EF9D9_29DD_485C_8E8E_12B7D9F00B78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// COpenGLTestApp:
// See OpenGLTest.cpp for the implementation of this class
//

class COpenGLTestApp : public CWinApp
{
public:
	COpenGLTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenGLTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(COpenGLTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENGLTEST_H__412EF9D9_29DD_485C_8E8E_12B7D9F00B78__INCLUDED_)
