#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

class CCGdiPlusBitmapTestApp : public CWinApp
{
public:
	CCGdiPlusBitmapTestApp();

	ULONG_PTR m_gdiplusToken;

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CCGdiPlusBitmapTestApp theApp;
