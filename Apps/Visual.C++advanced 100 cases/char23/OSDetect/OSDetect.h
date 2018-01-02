// OSDetect.h : main header file for the OSDETECT application
//

#if !defined(AFX_OSDETECT_H__EBEB9576_3821_11D2_8B51_000000000000__INCLUDED_)
#define AFX_OSDETECT_H__EBEB9576_3821_11D2_8B51_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// COSDetectApp:
// See OSDetect.cpp for the implementation of this class
//

class COSDetectApp : public CWinApp
{
public:
	COSDetectApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COSDetectApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(COSDetectApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OSDETECT_H__EBEB9576_3821_11D2_8B51_000000000000__INCLUDED_)
