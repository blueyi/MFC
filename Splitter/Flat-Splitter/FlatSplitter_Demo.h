// FlatSplitter_Demo.h : main header file for the FLATSPLITTER_DEMO application
//

#if !defined(AFX_FLATSPLITTER_DEMO_H__AC99D6F6_3033_4D5A_A761_59F268167218__INCLUDED_)
#define AFX_FLATSPLITTER_DEMO_H__AC99D6F6_3033_4D5A_A761_59F268167218__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFlatSplitter_DemoApp:
// See FlatSplitter_Demo.cpp for the implementation of this class
//

class CFlatSplitter_DemoApp : public CWinApp
{
public:
	CFlatSplitter_DemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlatSplitter_DemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CFlatSplitter_DemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLATSPLITTER_DEMO_H__AC99D6F6_3033_4D5A_A761_59F268167218__INCLUDED_)
