// IGfxTest.h : main header file for the IGFXTEST application
//

#if !defined(AFX_IGFXTEST_H__237F900A_1744_4BE9_8338_69884DFE112B__INCLUDED_)
#define AFX_IGFXTEST_H__237F900A_1744_4BE9_8338_69884DFE112B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CIGfxTestApp:
// See IGfxTest.cpp for the implementation of this class
//

class CIGfxTestApp : public CWinApp
{
public:
	CIGfxTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIGfxTestApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	//{{AFX_MSG(CIGfxTestApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	ULONG_PTR m_ulGdiplusToken;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IGFXTEST_H__237F900A_1744_4BE9_8338_69884DFE112B__INCLUDED_)
