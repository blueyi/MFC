// MDIWindList.h : main header file for the MDIWINDLIST application
//

#if !defined(AFX_MDIWINDLIST_H__C67D4394_F890_11D1_83BA_0000B43382FE__INCLUDED_)
#define AFX_MDIWINDLIST_H__C67D4394_F890_11D1_83BA_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMDIWindListApp:
// See MDIWindList.cpp for the implementation of this class
//

class CMDIWindListApp : public CWinApp
{
public:
	CMDIWindListApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDIWindListApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMDIWindListApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDIWINDLIST_H__C67D4394_F890_11D1_83BA_0000B43382FE__INCLUDED_)
