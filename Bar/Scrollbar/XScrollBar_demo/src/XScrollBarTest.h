// XScrollBarTest.h : main header file for the XSCROLLBARTEST application
//

#ifndef XSCROLLBARTEST_H
#define XSCROLLBARTEST_H

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CXScrollBarTestApp:
// See XScrollBarTest.cpp for the implementation of this class
//

class CXScrollBarTestApp : public CWinApp
{
public:
	CXScrollBarTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXScrollBarTestApp)
public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CXScrollBarTestApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //XSCROLLBARTEST_H
