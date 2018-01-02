// BmpButton.h : main header file for the BMPBUTTON application
//

#if !defined(AFX_BMPBUTTON_H__8CDDBF07_E0D2_11D4_AF89_FE799D000000__INCLUDED_)
#define AFX_BMPBUTTON_H__8CDDBF07_E0D2_11D4_AF89_FE799D000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBmpButtonApp:
// See BmpButton.cpp for the implementation of this class
//

class CBmpButtonApp : public CWinApp
{
public:
	CBmpButtonApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmpButtonApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBmpButtonApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMPBUTTON_H__8CDDBF07_E0D2_11D4_AF89_FE799D000000__INCLUDED_)
