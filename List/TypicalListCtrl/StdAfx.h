/////////////////////////////////////////////////////////////////////////////
// StdAfx.h : include file for standard system include files
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STDAFX_H__EMERY_EMERALD__INCLUDED_)
	#define AFX_STDAFX_H__EMERY_EMERALD__INCLUDED_

	#if _MSC_VER > 1000
		#pragma once
	#endif // _MSC_VER > 1000

	#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

	#include <afxwin.h>         // MFC core and standard components
	#include <afxext.h>         // MFC extensions
	#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
	#ifndef _AFX_NO_AFXCMN_SUPPORT
	#include <afxcmn.h>			// MFC support for Windows Common Controls
	#endif // _AFX_NO_AFXCMN_SUPPORT

	#define MAXITEMTEXT			256  // The maximum text length

	//*** The table header structure
	typedef struct {
			LPCTSTR szHdrName;  // A column name
			DWORD nAdjust;  // Text formating
			UINT nWidth;  // A column width
	} META_HEADER;

	void _M(int nVal);  // Shows a number
	void _M(CString sStr);  // Shows a CString
	void _M(wchar_t *szStr);  // Shows a Unicode line

	//{{AFX_INSERT_LOCATION}}
	// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_STDAFX_H__EMERY_EMERALD__INCLUDED_)

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
