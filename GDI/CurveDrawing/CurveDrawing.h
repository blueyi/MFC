// CurveDrawing.h : main header file for the CURVEDRAWING application
//

#if !defined(AFX_CURVEDRAWING_H__34B31B62_E764_4DB4_879D_CDD3BF87AF2D__INCLUDED_)
#define AFX_CURVEDRAWING_H__34B31B62_E764_4DB4_879D_CDD3BF87AF2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCurveDrawingApp:
// See CurveDrawing.cpp for the implementation of this class
//

class CCurveDrawingApp : public CWinApp
{
public:
	CCurveDrawingApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurveDrawingApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCurveDrawingApp)
	//afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURVEDRAWING_H__34B31B62_E764_4DB4_879D_CDD3BF87AF2D__INCLUDED_)
