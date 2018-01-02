// ScrollbarSample.h : main header file for the SCROLLBARSAMPLE application
//

#if !defined(AFX_SCROLLBARSAMPLE_H__76DC4380_D228_4456_A487_5A6AB8C50596__INCLUDED_)
#define AFX_SCROLLBARSAMPLE_H__76DC4380_D228_4456_A487_5A6AB8C50596__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CScrollbarSampleApp:
// See ScrollbarSample.cpp for the implementation of this class
//

class CScrollbarSampleApp : public CWinApp
{
public:
	CScrollbarSampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScrollbarSampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CScrollbarSampleApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCROLLBARSAMPLE_H__76DC4380_D228_4456_A487_5A6AB8C50596__INCLUDED_)
