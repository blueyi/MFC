// TemplateMFC.h : main header file for the TEMPLATEMFC application
//

#if !defined(AFX_TEMPLATEMFC_H__129DF4F6_5FA5_11D2_BFE7_0020186676FB__INCLUDED_)
#define AFX_TEMPLATEMFC_H__129DF4F6_5FA5_11D2_BFE7_0020186676FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTemplateMFCApp:
// See TemplateMFC.cpp for the implementation of this class
//

class CTemplateMFCApp : public CWinApp
{
public:
	CTemplateMFCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTemplateMFCApp)
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTemplateMFCApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEMPLATEMFC_H__129DF4F6_5FA5_11D2_BFE7_0020186676FB__INCLUDED_)
