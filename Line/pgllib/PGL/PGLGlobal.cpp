// PGLGlobal.cpp: implementation of the CPGLGlobal class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "pgl/PGLGlobal.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


HMODULE CPGLGlobal::GetInstance()
{
	HMODULE hInst=NULL;
// getting module handle
#ifdef _MFC_7
	#ifndef _UNICODE
		#ifdef _DEBUG
			hInst=GetModuleHandle(_T("PGL7d.dll"));
		#else
			hInst=GetModuleHandle(_T("PGL7.dll"));
		#endif
	#else
		#ifdef _DEBUG
			hInst=GetModuleHandle(_T("PGL7ud.dll"));
		#else
			hInst=GetModuleHandle(_T("PGL7u.dll"));
		#endif
	#endif
#else
	#ifndef _UNICODE
		#ifdef _DEBUG
			hInst=GetModuleHandle(_T("PGLd.dll"));
		#else
			hInst=GetModuleHandle(_T("PGL.dll"));
		#endif
	#else
		#ifdef _DEBUG
			hInst=GetModuleHandle(_T("PGLud.dll"));
		#else
			hInst=GetModuleHandle(_T("PGLu.dll"));
		#endif
	#endif
#endif
	return hInst;
}