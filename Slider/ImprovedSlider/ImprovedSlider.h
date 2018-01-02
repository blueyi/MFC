// ImprovedSlider.h : main header file for the IMPROVEDSLIDER application
//

#if !defined(IMPROVED_SLIDER_H)
#define IMPROVED_SLIDER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CImprovedSliderApp:
// See ImprovedSlider.cpp for the implementation of this class
//

class CImprovedSliderApp : public CWinApp
{
public:
	CImprovedSliderApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImprovedSliderApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CImprovedSliderApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(IMPROVED_SLIDER_H)
