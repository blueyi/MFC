// Demo_DevStudio.h : main header file for the DEMO_DEVSTUDIO application
//

#if !defined(AFX_DEMO_DEVSTUDIO_H__AC8E7207_6379_11D2_9582_0040053E0F5B__INCLUDED_)
#define AFX_DEMO_DEVSTUDIO_H__AC8E7207_6379_11D2_9582_0040053E0F5B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDemo_DevStudioApp:
// See Demo_DevStudio.cpp for the implementation of this class
//

class CDemo_DevStudioApp : public CWinApp
{
public:
	CDemo_DevStudioApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemo_DevStudioApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDemo_DevStudioApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMO_DEVSTUDIO_H__AC8E7207_6379_11D2_9582_0040053E0F5B__INCLUDED_)
