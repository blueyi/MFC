// ExToolBar.h : main header file for the EXTOOLBAR application
//

#if !defined(AFX_EXTOOLBAR_H__298735F8_FF1C_11D1_8A9F_000000000000__INCLUDED_)
#define AFX_EXTOOLBAR_H__298735F8_FF1C_11D1_8A9F_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CExToolBarApp:
// See ExToolBar.cpp for the implementation of this class
//

class CExToolBarApp : public CWinApp
{
public:
	CExToolBarApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExToolBarApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation

	//{{AFX_MSG(CExToolBarApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTOOLBAR_H__298735F8_FF1C_11D1_8A9F_000000000000__INCLUDED_)
