// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__D8FEDCE7_5D82_11D4_BEC3_FE8979D1AC45__INCLUDED_)
#define AFX_STDAFX_H__D8FEDCE7_5D82_11D4_BEC3_FE8979D1AC45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

// Custom user messages
#define WM_USER_UPDATE_COLOR		WM_USER+0x100
#define WM_USER_UPDATE_SPINNER_RED	WM_USER+0x101
#define WM_USER_UPDATE_SPINNER_GREEN	WM_USER+0x102
#define WM_USER_UPDATE_SPINNER_BLUE	WM_USER+0x103
#define WM_USER_UPDATE_GRADIENT		WM_USER+0x104
#define WM_USER_UPDATE_GRADIENT_STATUS	WM_USER+0x105

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__D8FEDCE7_5D82_11D4_BEC3_FE8979D1AC45__INCLUDED_)
