// LogFileAccess.h: interface for the CLogFileAccess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGFILEACCESS_H__622EBFFC_CEF8_4691_A841_B1F1E946F807__INCLUDED_)
#define AFX_LOGFILEACCESS_H__622EBFFC_CEF8_4691_A841_B1F1E946F807__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CommonDefine.h"

class CLogFileAccess  
{
public:
	CLogFileAccess();
	virtual ~CLogFileAccess();

private:
	CString m_sAppPath, m_sPathOfLogFile, m_sNameOfLogFile;
	tm*		m_pTime;
	FILE*	m_pFile;
	bool OpenLogFileName();
	void ReadHederInfoFromCfgFile( CString& sSerialNumOfEquip, CString& sNameOfInstitution );
	
public:
	void SaveToFile( PVOID pData );

};

#endif // !defined(AFX_LOGFILEACCESS_H__622EBFFC_CEF8_4691_A841_B1F1E946F807__INCLUDED_)
