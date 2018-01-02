// thumbnail.h : main header file for the THUMBNAIL application
//

#if !defined(AFX_THUMBNAIL_H__7391EF13_72DA_47D8_B396_F5472A0D9F56__INCLUDED_)
#define AFX_THUMBNAIL_H__7391EF13_72DA_47D8_B396_F5472A0D9F56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CThumbnailApp:
// See thumbnail.cpp for the implementation of this class
//

class CThumbnailApp : public CWinApp
{
public:
	CThumbnailApp();

	ULONG_PTR	m_gdiplusToken;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThumbnailApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CThumbnailApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THUMBNAIL_H__7391EF13_72DA_47D8_B396_F5472A0D9F56__INCLUDED_)
