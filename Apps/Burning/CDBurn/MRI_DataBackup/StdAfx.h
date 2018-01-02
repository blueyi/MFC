// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__53E82187_8878_4ADD_B3E5_4512CC29B998__INCLUDED_)
#define AFX_STDAFX_H__53E82187_8878_4ADD_B3E5_4512CC29B998__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//0-None,1-Copy,2-Move
#define _FILE_MOVE_ 2
#define _FILE_COPY_ 1
#define _FILE_NONE_ 0
//0-None; 1-Hard Disk; 2-CD; 3-DVD
#define _DISK_NONE_ 0
#define _DISK_DISK_ 1
#define _DISK_CD_ 2
#define _DISK_DVD_ 3
#define _MAX_DVD_ (4*1024*1024*1024)
#define _MAX_CD_ (600*1024*1024)
#define _DWORD_LENGTH_ 32


#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__53E82187_8878_4ADD_B3E5_4512CC29B998__INCLUDED_)
