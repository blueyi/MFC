// membmtst2.h : main header file for the MEMBMTST2 application
//

#if !defined(AFX_MEMBMTST2_H__2F4B85CB_3229_4A42_919A_84FA9FF07D92__INCLUDED_)
#define AFX_MEMBMTST2_H__2F4B85CB_3229_4A42_919A_84FA9FF07D92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTstApp:
// See membmtst2.cpp for the implementation of this class
//

class CTstApp : public CWinApp
{
public:
	CTstApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTstApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTstApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEMBMTST2_H__2F4B85CB_3229_4A42_919A_84FA9FF07D92__INCLUDED_)
