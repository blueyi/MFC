// HistogramMatlab.h : main header file for the HISTOGRAMMATLAB application
//

#if !defined(AFX_HISTOGRAMMATLAB_H__64BC7337_E75F_4149_8008_15BB744D1051__INCLUDED_)
#define AFX_HISTOGRAMMATLAB_H__64BC7337_E75F_4149_8008_15BB744D1051__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHistogramMatlabApp:
// See HistogramMatlab.cpp for the implementation of this class
//

class CHistogramMatlabApp : public CWinApp
{
public:
	CHistogramMatlabApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistogramMatlabApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	IDispatch* GetMatlabEngine()	{	return m_pMtlbDispApp;};

	//{{AFX_MSG(CHistogramMatlabApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	void DeInitMatlab();
	void InitMatlab();
	
	// Matlab Application Dispatch Interface object
	IDispatch* m_pMtlbDispApp;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTOGRAMMATLAB_H__64BC7337_E75F_4149_8008_15BB744D1051__INCLUDED_)
