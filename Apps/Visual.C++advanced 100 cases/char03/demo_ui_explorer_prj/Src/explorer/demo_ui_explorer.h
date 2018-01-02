// demo_ui_explorer.h : main header file for the DEMO_UI_EXPLORER application
//

#if !defined(AFX_DEMO_UI_EXPLORER_H__7BB52B7D_0704_11D2_AB9F_441100C10000__INCLUDED_)
#define AFX_DEMO_UI_EXPLORER_H__7BB52B7D_0704_11D2_AB9F_441100C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDemo_ui_explorerApp:
// See demo_ui_explorer.cpp for the implementation of this class
//

class CDemo_ui_explorerApp : public CWinApp
{
public:
	CDemo_ui_explorerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemo_ui_explorerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDemo_ui_explorerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMO_UI_EXPLORER_H__7BB52B7D_0704_11D2_AB9F_441100C10000__INCLUDED_)
