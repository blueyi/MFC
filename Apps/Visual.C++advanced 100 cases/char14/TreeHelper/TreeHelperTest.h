// TreeHelperTest.h : main header file for the TREEHELPERTEST application
//

#if !defined(AFX_TREEHELPERTEST_H__5DD969D5_38CB_11D2_8F85_0060B0ECF89C__INCLUDED_)
#define AFX_TREEHELPERTEST_H__5DD969D5_38CB_11D2_8F85_0060B0ECF89C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTreeHelperTestApp:
// See TreeHelperTest.cpp for the implementation of this class
//

class CTreeHelperTestApp : public CWinApp
{
public:
	CTreeHelperTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeHelperTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTreeHelperTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEHELPERTEST_H__5DD969D5_38CB_11D2_8F85_0060B0ECF89C__INCLUDED_)
