// TreeDemo.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CTreeDemoApp:
// See TreeDemo.cpp for the implementation of this class
//

class CTreeDemoApp : public CWinApp
{
protected:	
	// GDI+ Library...
	Gdiplus::GdiplusStartupInput	m_gdiStartup;
	ULONG_PTR						m_gdiToken;

public:
	CTreeDemoApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CTreeDemoApp theApp;