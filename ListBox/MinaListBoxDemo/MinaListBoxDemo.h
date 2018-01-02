// MinaListBoxDemo.h : main header file for the MINALISTBOXDEMO application
//

#if !defined(AFX_MINALISTBOXDEMO_H__7FF84776_B267_4CF1_B5A7_7E3DE7981D92__INCLUDED_)
#define AFX_MINALISTBOXDEMO_H__7FF84776_B267_4CF1_B5A7_7E3DE7981D92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMinaListBoxDemoApp:
// See MinaListBoxDemo.cpp for the implementation of this class
//

class CMinaListBoxDemoApp : public CWinApp
{
public:
	CMinaListBoxDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMinaListBoxDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMinaListBoxDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MINALISTBOXDEMO_H__7FF84776_B267_4CF1_B5A7_7E3DE7981D92__INCLUDED_)
