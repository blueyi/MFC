// CHexEditDemo.h : main header file for the CHEXEDITDEMO application
//

#if !defined(AFX_CHEXEDITDEMO_H__B5833A84_8DEC_410A_BB2D_76D615E1910E__INCLUDED_)
#define AFX_CHEXEDITDEMO_H__B5833A84_8DEC_410A_BB2D_76D615E1910E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCHexEditDemoApp:
// See CHexEditDemo.cpp for the implementation of this class
//

class CCHexEditDemoApp : public CWinApp
{
public:
	CCHexEditDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCHexEditDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCHexEditDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHEXEDITDEMO_H__B5833A84_8DEC_410A_BB2D_76D615E1910E__INCLUDED_)
