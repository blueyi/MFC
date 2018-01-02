// BtnTest.h : main header file for the BTNTEST application
//

#if !defined(AFX_BTNTEST_H__CBAD41A5_3245_11D2_8C4F_000000000000__INCLUDED_)
#define AFX_BTNTEST_H__CBAD41A5_3245_11D2_8C4F_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBtnTestApp:
// See BtnTest.cpp for the implementation of this class
//

class CBtnTestApp : public CWinApp
{
public:
	CBtnTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBtnTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBtnTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BTNTEST_H__CBAD41A5_3245_11D2_8C4F_000000000000__INCLUDED_)
