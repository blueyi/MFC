// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//avoid VS 2005 CRT deprecation messages
#define _CRT_SECURE_NO_DEPRECATE

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Win 98 or later
#define _WIN32_WINDOWS 0x0410
#endif

#include <assert.h>
#ifndef NDEBUG
	#define M_ASSERT(x)	assert(x)
#else
	#define M_ASSERT(x)
#endif

// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <math.h>

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

// Local Header Files

// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#if defined(_WIN32_WCE) && !defined(UNDER_CE)
	#define UNDER_CE _WIN32_WCE
#endif

#ifdef UNDER_CE
#if _WIN32_WCE < 0x500 && _MSC_VER > 1220 
// only needed for WM2003 builds under VS2005 
#pragma comment(lib, "ccrtrtti.lib") 
#endif
#endif

//undefine to use DDB functionality instead of DIB section
//#define MCH_USE_DDB

//define stubs for MChart - specific types to compile standalone
#define MByteString	std::string
#define M_NUMBER_OF_ARRAY_ELEMENTS(a)	(sizeof(a)/sizeof(a[0]))
#define M_L(x)	_T(x)
//stringer macro
#define MCH_TO_STRING_(x)			# x
#define MCH_TO_STRING(x)	MCH_TO_STRING_(x)

struct MException
{
public:
	MException( LPCTSTR strMsg ) : m_strMsg(strMsg) {}
	static void Throw( LPCTSTR strMsg ) { throw MException( strMsg ); }

	LPCTSTR GetMsg() const { return m_strMsg.c_str(); }

protected:
	typedef std::basic_string<TCHAR> StdStringT;
	StdStringT m_strMsg;
};

class MChNonCopyableConcept
{
protected:
	MChNonCopyableConcept() {}
	~MChNonCopyableConcept() {}

private:  
	MChNonCopyableConcept( const MChNonCopyableConcept& );
	const MChNonCopyableConcept& operator=( const MChNonCopyableConcept& );
};

//gdi wrappers
#include "MChGDIWrappers.h"
//membm
#include "MChMemBm.h"

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
