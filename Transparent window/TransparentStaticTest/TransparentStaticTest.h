// TransparentStaticTest.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CTransparentStaticTestApp:
// See TransparentStaticTest.cpp for the implementation of this class
//

class CTransparentStaticTestApp : public CWinApp
{
public:
	CTransparentStaticTestApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CTransparentStaticTestApp theApp;