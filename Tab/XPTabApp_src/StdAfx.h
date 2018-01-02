/////////////////////////////////////////////////////////////////////////////
// StdAfx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STDAFX_H__B39AA2CE_684D_11D8_97C8_0002A522F13C__INCLUDED_)
#define AFX_STDAFX_H__B39AA2CE_684D_11D8_97C8_0002A522F13C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <AfxWin.h>         // MFC core and standard components
#include <AfxExt.h>         // MFC extensions

#include <AfxDtCtl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <AfxCmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


#define RGB_AVERAGE(a, b)   ( ((((a) ^ (b)) & 0xfffefefeL) >> 1) + ((a) & (b)) )

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_STDAFX_H__B39AA2CE_684D_11D8_97C8_0002A522F13C__INCLUDED_)
