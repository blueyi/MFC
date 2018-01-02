// InfoTipTest.h : main header file for the INFOTIPTEST application
//

#if !defined(AFX_INFOTIPTEST_H__618FB1DA_F154_4CFF_8AAB_A8FF71282B63__INCLUDED_)
#define AFX_INFOTIPTEST_H__618FB1DA_F154_4CFF_8AAB_A8FF71282B63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CInfoTipTestApp:
// See InfoTipTest.cpp for the implementation of this class
//

class CInfoTipTestApp : public CWinApp
{
public:
	CInfoTipTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfoTipTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CInfoTipTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFOTIPTEST_H__618FB1DA_F154_4CFF_8AAB_A8FF71282B63__INCLUDED_)
