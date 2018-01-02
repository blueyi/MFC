// TextInStatus.h : main header file for the TEXTINSTATUS application
//

#if !defined(AFX_TEXTINSTATUS_H__9E913155_E950_11D4_AFB3_0050BABF4197__INCLUDED_)
#define AFX_TEXTINSTATUS_H__9E913155_E950_11D4_AFB3_0050BABF4197__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTextInStatusApp:
// See TextInStatus.cpp for the implementation of this class
//

class CTextInStatusApp : public CWinApp
{
public:
	CTextInStatusApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextInStatusApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTextInStatusApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTINSTATUS_H__9E913155_E950_11D4_AFB3_0050BABF4197__INCLUDED_)
