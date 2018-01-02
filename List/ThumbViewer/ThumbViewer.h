// ThumbViewer.h : main header file for the THUMBVIEWER application
//

#if !defined(AFX_THUMBVIEWER_H__71E2C240_CCFB_4DFD_836E_EECD986C32A8__INCLUDED_)
#define AFX_THUMBVIEWER_H__71E2C240_CCFB_4DFD_836E_EECD986C32A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CThumbViewerApp:
// See ThumbViewer.cpp for the implementation of this class
//

class CThumbViewerApp : public CWinApp
{
public:
	CThumbViewerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThumbViewerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CThumbViewerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THUMBVIEWER_H__71E2C240_CCFB_4DFD_836E_EECD986C32A8__INCLUDED_)
