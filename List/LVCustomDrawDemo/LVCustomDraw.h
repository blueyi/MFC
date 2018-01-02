// LVCustomDraw.h : main header file for the LVCUSTOMDRAW application
//

#if !defined(AFX_LVCUSTOMDRAW_H__4EC7FCA4_25D4_11D3_8D3B_9BE7BCEB1D3D__INCLUDED_)
#define AFX_LVCUSTOMDRAW_H__4EC7FCA4_25D4_11D3_8D3B_9BE7BCEB1D3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLVCustomDrawApp:
// See LVCustomDraw.cpp for the implementation of this class
//

class CLVCustomDrawApp : public CWinApp
{
public:
	CLVCustomDrawApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLVCustomDrawApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLVCustomDrawApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// Global functions

void FillListCtrl ( CListCtrl& list );  

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LVCUSTOMDRAW_H__4EC7FCA4_25D4_11D3_8D3B_9BE7BCEB1D3D__INCLUDED_)
