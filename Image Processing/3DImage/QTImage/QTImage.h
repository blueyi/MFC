// QTImage.h : main header file for the QTIMAGE application
//

#if !defined(AFX_QTIMAGE_H__0B1D5998_046D_4B9C_9839_5B207BC5339D__INCLUDED_)
#define AFX_QTIMAGE_H__0B1D5998_046D_4B9C_9839_5B207BC5339D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CQTImageApp:
// See QTImage.cpp for the implementation of this class
//

class CQTImageApp : public CWinApp
{
public:
	CQTImageApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQTImageApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CQTImageApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QTIMAGE_H__0B1D5998_046D_4B9C_9839_5B207BC5339D__INCLUDED_)
