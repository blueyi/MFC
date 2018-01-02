// TDS_chart.h : main header file for the TDS_CHART application
//

#if !defined(AFX_TDS_CHART_H__E1EAE37B_A2F0_4806_8396_7BA57E0A329D__INCLUDED_)
#define AFX_TDS_CHART_H__E1EAE37B_A2F0_4806_8396_7BA57E0A329D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTDS_chartApp:
// See TDS_chart.cpp for the implementation of this class
//

class CTDS_chartApp : public CWinApp
{
public:
	CTDS_chartApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTDS_chartApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTDS_chartApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TDS_CHART_H__E1EAE37B_A2F0_4806_8396_7BA57E0A329D__INCLUDED_)
