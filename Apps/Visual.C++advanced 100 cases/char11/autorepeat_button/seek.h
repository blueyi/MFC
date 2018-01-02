// seek.h : main header file for the SEEK application
//

#if !defined(AFX_SEEK_H__E5CF1A05_0910_11D2_A171_000000000000__INCLUDED_)
#define AFX_SEEK_H__E5CF1A05_0910_11D2_A171_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSeekApp:
// See seek.cpp for the implementation of this class
//

class CSeekApp : public CWinApp
{
public:
	CSeekApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeekApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSeekApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEEK_H__E5CF1A05_0910_11D2_A171_000000000000__INCLUDED_)
