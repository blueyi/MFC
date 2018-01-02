// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#pragma once

// Change these values to use different versions
#define WINVER		0x0400
//#define _WIN32_WINNT	0x0400
#define _WIN32_IE	0x0400
#define _RICHEDIT_VER	0x0100

#define _WTL_USE_CSTRING
#undef _WTL_NO_WTYPES

#include <atlbase.h>
#include <atlapp.h>

extern CAppModule _Module;

#include <atlctrls.h>
#include <atlmisc.h>

#ifdef _WIN32_WCE

	#include <atlscrl.h>
	#include <atlframe.h>
	#include <atlwince.h>

#else

	#include <atlwin.h>

#endif // _WIN32_WCE
