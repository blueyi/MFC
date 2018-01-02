// HLinkTest.h : main header file for the HLINKTEST application
//

#if !defined(AFX_HLINKTEST_H__DE0F2CC7_ACE4_11D3_AEDD_0050BABF4197__INCLUDED_)
#define AFX_HLINKTEST_H__DE0F2CC7_ACE4_11D3_AEDD_0050BABF4197__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHLinkTestApp:
// See HLinkTest.cpp for the implementation of this class
//

class CHLinkTestApp : public CWinApp
{
public:
	CHLinkTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHLinkTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHLinkTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HLINKTEST_H__DE0F2CC7_ACE4_11D3_AEDD_0050BABF4197__INCLUDED_)
