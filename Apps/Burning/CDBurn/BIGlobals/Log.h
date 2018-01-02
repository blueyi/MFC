// Log.h: interface for the CLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOG_H__13CBE8FF_0A06_49BD_BD35_7BE1DDB036DF__INCLUDED_)
#define AFX_LOG_H__13CBE8FF_0A06_49BD_BD35_7BE1DDB036DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS CLog  
{
public:
	CLog();
	virtual ~CLog();

private:
	static CLog m_oLog;
	bool	m_bWriteLogToFile, m_bSendLogToWindow;
	FILE*	m_pFile;
	CString	m_LogDirectory, m_sLogFileName;
	tm*		m_pTime;	

	bool OpenLogFileName();
	CString MakeTimeString( time_t Tm );
	
public:
	static CLog& GetHandle();

	void Write( LPCSTR format, ... );
	
	
};

#endif // !defined(AFX_LOG_H__13CBE8FF_0A06_49BD_BD35_7BE1DDB036DF__INCLUDED_)
