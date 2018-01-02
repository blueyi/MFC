// LBSpinDemo.h : main header file for the LBSPINDEMO application
//

#if !defined(AFX_LBSPINDEMO_H__16B8B6E5_C905_11D3_AA40_008048EAE3F5__INCLUDED_)
#define AFX_LBSPINDEMO_H__16B8B6E5_C905_11D3_AA40_008048EAE3F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLBSpinDemoApp:
// See LBSpinDemo.cpp for the implementation of this class
//

class CLBSpinDemoApp : public CWinApp
{
public:
	CLBSpinDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLBSpinDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLBSpinDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LBSPINDEMO_H__16B8B6E5_C905_11D3_AA40_008048EAE3F5__INCLUDED_)
