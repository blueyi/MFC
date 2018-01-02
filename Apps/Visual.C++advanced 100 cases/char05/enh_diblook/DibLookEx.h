// DibLookEx.h : main header file for the DIBLOOKEX application
//

#if !defined(AFX_DIBLOOKEX_H__A2E75B35_086D_11D2_8A46_0000E81D3D27__INCLUDED_)
#define AFX_DIBLOOKEX_H__A2E75B35_086D_11D2_8A46_0000E81D3D27__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDibLookExApp:
// See DibLookEx.cpp for the implementation of this class
//

class CDibLookExApp : public CWinApp
{
public:
	CDibLookExApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDibLookExApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDibLookExApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIBLOOKEX_H__A2E75B35_086D_11D2_8A46_0000E81D3D27__INCLUDED_)
