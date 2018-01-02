// ListImage.h : main header file for the LISTIMAGE application
//

#if !defined(AFX_LISTIMAGE_H__906394FE_EFA5_430E_A200_2D8E26EFC692__INCLUDED_)
#define AFX_LISTIMAGE_H__906394FE_EFA5_430E_A200_2D8E26EFC692__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CListImageApp:
// See ListImage.cpp for the implementation of this class
//

class CListImageApp : public CWinApp
{
public:
	CListImageApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListImageApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CListImageApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTIMAGE_H__906394FE_EFA5_430E_A200_2D8E26EFC692__INCLUDED_)
