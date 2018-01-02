// EasyFavorite.h : main header file for the EASYFAVORITE application
//

#if !defined(AFX_EASYFAVORITE_H__CA4304C1_2082_4D67_9C43_35F1B8F1D040__INCLUDED_)
#define AFX_EASYFAVORITE_H__CA4304C1_2082_4D67_9C43_35F1B8F1D040__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEasyFavoriteApp:
// See EasyFavorite.cpp for the implementation of this class
//

class CEasyFavoriteApp : public CWinApp
{
public:
	CEasyFavoriteApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEasyFavoriteApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEasyFavoriteApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EASYFAVORITE_H__CA4304C1_2082_4D67_9C43_35F1B8F1D040__INCLUDED_)
