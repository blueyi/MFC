// testMultiColorPlotCtrl.h : main header file for the TESTMULTICOLORPLOTCTRL application
//

#if !defined(AFX_TESTMULTICOLORPLOTCTRL_H__6F85CE9F_E2AF_49ED_BBB0_AF63B53D5E20__INCLUDED_)
#define AFX_TESTMULTICOLORPLOTCTRL_H__6F85CE9F_E2AF_49ED_BBB0_AF63B53D5E20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestMultiColorPlotCtrlApp:
// See testMultiColorPlotCtrl.cpp for the implementation of this class
//

class CTestMultiColorPlotCtrlApp : public CWinApp
{
public:
	CTestMultiColorPlotCtrlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestMultiColorPlotCtrlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestMultiColorPlotCtrlApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTMULTICOLORPLOTCTRL_H__6F85CE9F_E2AF_49ED_BBB0_AF63B53D5E20__INCLUDED_)
