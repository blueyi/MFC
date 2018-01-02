// ThumbNail.h : main header file for the THUMBNAIL application
//

#if !defined(AFX_THUMBNAIL_H__C6E7299E_9632_47CD_BC8C_8B374FEF0E26__INCLUDED_)
#define AFX_THUMBNAIL_H__C6E7299E_9632_47CD_BC8C_8B374FEF0E26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CThumbNailApp:
// See ThumbNail.cpp for the implementation of this class
//

class CThumbNailApp : public CWinApp
{
public:
	CThumbNailApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThumbNailApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CThumbNailApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THUMBNAIL_H__C6E7299E_9632_47CD_BC8C_8B374FEF0E26__INCLUDED_)
