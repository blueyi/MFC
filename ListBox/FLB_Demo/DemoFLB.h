// DemoFLB.h : main header file for the DEMOFLB application
//

#if !defined(AFX_DEMOFLB_H__48BA3D98_EC95_4AD8_B485_B226D661B9E5__INCLUDED_)
#define AFX_DEMOFLB_H__48BA3D98_EC95_4AD8_B485_B226D661B9E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDemoFLBApp:
// See DemoFLB.cpp for the implementation of this class
//

class CDemoFLBApp : public CWinApp
{
public:
	CDemoFLBApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoFLBApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDemoFLBApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOFLB_H__48BA3D98_EC95_4AD8_B485_B226D661B9E5__INCLUDED_)
