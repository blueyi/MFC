// MyMeter.h : main header file for the MYMETER application
//

#if !defined(AFX_MYMETER_H__28562282_31F4_4304_BBDE_B4A489659332__INCLUDED_)
#define AFX_MYMETER_H__28562282_31F4_4304_BBDE_B4A489659332__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyMeterApp:
// See MyMeter.cpp for the implementation of this class
//

class CMyMeterApp : public CWinApp
{
public:
	CMyMeterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyMeterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyMeterApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYMETER_H__28562282_31F4_4304_BBDE_B4A489659332__INCLUDED_)
