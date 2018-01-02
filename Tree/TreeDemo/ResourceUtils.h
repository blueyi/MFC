#pragma once

/////////////////////////////////////////////////////////////////////
// CResourceUtils, first version (Aug 07)
// Written by Paul Roberts, http://www.tlhouse.co.uk
//
// Use it freely, but please leave this header intact
//

class CResourceUtils
{
public:
	CResourceUtils(void) {}
	virtual ~CResourceUtils(void) {}
	
	static void		UnpackResToFile( UINT nIDResource, LPCTSTR szResType, LPCTSTR lpszPath );
	static CString	UnpackResToTempFile( UINT nIDResource, LPCTSTR szResType );
	static CString	GetTempFileName( LPCTSTR lpszPrefix = _T("TMP") );
};
