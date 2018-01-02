// LineTrackApp.h : main header file for the LINETRACKAPP application
//

#if !defined(AFX_LINETRACKAPP_H__33002A94_6D12_4158_8921_F851BBFA6F9E__INCLUDED_)
#define AFX_LINETRACKAPP_H__33002A94_6D12_4158_8921_F851BBFA6F9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLineTrackAppApp:
// See LineTrackApp.cpp for the implementation of this class
//

class CLineTrackAppApp : public CWinApp
{
public:
	CLineTrackAppApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLineTrackAppApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLineTrackAppApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINETRACKAPP_H__33002A94_6D12_4158_8921_F851BBFA6F9E__INCLUDED_)
