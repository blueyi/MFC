// HistogramDemo.h : main header file for the HISTOGRAMDEMO application
//

#if !defined(AFX_HISTOGRAMDEMO_H__F118834B_7510_416F_A7C8_BC5ABAC9A957__INCLUDED_)
#define AFX_HISTOGRAMDEMO_H__F118834B_7510_416F_A7C8_BC5ABAC9A957__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHistogramDemoApp:
// See HistogramDemo.cpp for the implementation of this class
//

class CHistogramDemoApp : public CWinApp
{
public:
	CHistogramDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistogramDemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CHistogramDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	ULONG_PTR m_ulGdiplusToken;		//	ULONG_PTR is typedef'd to ULONG, hmmm.
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTOGRAMDEMO_H__F118834B_7510_416F_A7C8_BC5ABAC9A957__INCLUDED_)
