// FontTest.h : main header file for the FONTTEST application
//

#if !defined(AFX_FONTTEST_H__1B527CD5_544F_11D2_84C8_0060970C2D45__INCLUDED_)
#define AFX_FONTTEST_H__1B527CD5_544F_11D2_84C8_0060970C2D45__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFontTestApp:
// See FontTest.cpp for the implementation of this class
//

class CFontTestApp : public CWinApp
{
public:
	CFontTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFontTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFontTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FONTTEST_H__1B527CD5_544F_11D2_84C8_0060970C2D45__INCLUDED_)
