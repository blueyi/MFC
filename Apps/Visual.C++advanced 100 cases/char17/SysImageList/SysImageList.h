// SysImageList.h : main header file for the SYSIMAGELIST application
//

#if !defined(AFX_SYSIMAGELIST_H__A2EB9864_43FA_11D2_8087_00805F7DB281__INCLUDED_)
#define AFX_SYSIMAGELIST_H__A2EB9864_43FA_11D2_8087_00805F7DB281__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSysImageListApp:
// See SysImageList.cpp for the implementation of this class
//

class CSysImageListApp : public CWinApp
{
public:
	CSysImageListApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSysImageListApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSysImageListApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSIMAGELIST_H__A2EB9864_43FA_11D2_8087_00805F7DB281__INCLUDED_)
