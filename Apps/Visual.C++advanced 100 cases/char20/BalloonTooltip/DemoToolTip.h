// DemoToolTip.h : main header file for the DEMOTOOLTIP application
//

#if !defined(AFX_DEMOTOOLTIP_H__46F5810C_3EEB_11D2_8FDB_000000000000__INCLUDED_)
#define AFX_DEMOTOOLTIP_H__46F5810C_3EEB_11D2_8FDB_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDemoToolTipApp:
// See DemoToolTip.cpp for the implementation of this class
//

class CDemoToolTipApp : public CWinApp
{
public:
	CDemoToolTipApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoToolTipApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDemoToolTipApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOTOOLTIP_H__46F5810C_3EEB_11D2_8FDB_000000000000__INCLUDED_)
