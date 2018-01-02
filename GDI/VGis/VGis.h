// VGis.h : main header file for the VGIS application
//

#if !defined(AFX_VGIS_H__F4D4E80E_E70C_4F6E_B0BB_748A53DA1986__INCLUDED_)
#define AFX_VGIS_H__F4D4E80E_E70C_4F6E_B0BB_748A53DA1986__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CVGisApp:
// See VGis.cpp for the implementation of this class
//

class CVGisApp : public CWinApp
{
public:
	CVGisApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVGisApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CVGisApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VGIS_H__F4D4E80E_E70C_4F6E_B0BB_748A53DA1986__INCLUDED_)
