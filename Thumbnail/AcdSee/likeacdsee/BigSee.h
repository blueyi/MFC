// BigSee.h : main header file for the BIGSEE application
//

#if !defined(AFX_BIGSEE_H__65FC3345_C244_11D6_AFCA_001088A02FAC__INCLUDED_)
#define AFX_BIGSEE_H__65FC3345_C244_11D6_AFCA_001088A02FAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBigSeeApp:
// See BigSee.cpp for the implementation of this class
//

class CBigSeeApp : public CWinApp
{
public:
	CBigSeeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBigSeeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBigSeeApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BIGSEE_H__65FC3345_C244_11D6_AFCA_001088A02FAC__INCLUDED_)
