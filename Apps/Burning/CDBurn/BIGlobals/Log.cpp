// Log.cpp: implementation of the CLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Log.h"
#include "ConfigManager.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AFX_EXT_CLASS CLog CLog::m_oLog;

CLog::CLog()
{
	m_pFile = NULL;
	m_sLogFileName = "";
	
	CString sIniFile = CConfigManager::GetHandle().m_strConfigIniFile.c_str();

	//Modified by Tom, --2008.07.10
	m_bWriteLogToFile  = (GetPrivateProfileInt( "LOG", "WriteToFile", 1, sIniFile )>0?true:false);
	m_bSendLogToWindow = (GetPrivateProfileInt( "LOG", "SendToWindow", 1, sIniFile )>0?true:false);
/*
	m_LogDirectory = CConfigManager::GetHandle().m_strHomePath;
	m_LogDirectory += "Log";
*/
	char sAppPath[255];
	::GetCurrentDirectory( 255, sAppPath );
		m_LogDirectory.Format( "%s\\Log", sAppPath );
	::CreateDirectory( m_LogDirectory, NULL );

	m_pTime = new tm();
	memset( m_pTime, 0, sizeof(tm) );

	OpenLogFileName();
}

CLog::~CLog()
{
	delete m_pTime;
	
	if ( m_pFile )
	{
		fclose( m_pFile );
	}
}

CLog& CLog::GetHandle()
{
	return m_oLog;
}

bool CLog::OpenLogFileName()
{
	time_t nDateTime = mktime( CTime::GetCurrentTime().GetLocalTm() );	
	tm * pTm = localtime( &nDateTime );
	
	if ( m_pTime->tm_year != pTm->tm_year 
		|| m_pTime->tm_mon + 1 != pTm->tm_mon + 1 
		|| m_pTime->tm_mday != pTm->tm_mday )
	{
		memcpy( m_pTime, pTm, sizeof(tm) );
		m_sLogFileName.Format( "%s\\Trace%04d-%02d-%02d.log", 
			m_LogDirectory, 
			pTm->tm_year + 1900, pTm->tm_mon + 1, pTm->tm_mday );

		if ( m_pFile )
		{
			fclose( m_pFile );
		}

		m_pFile = fopen( m_sLogFileName, "a+t" );
		if ( !m_pFile )
		{
			CString sCharRes = CLang::GetHandle().GetCharRes("MSG___FAIL_TO_OPEN_LOG_FILE");
			CString sMsg;
			sMsg.Format( sCharRes, m_sLogFileName );
			CLang::GetHandle().ShowMessage( sMsg );
			return false;
		}
	}

	if ( !m_pFile )
	{
		return false;
	}

	return true;
}

CString CLog::MakeTimeString( time_t Tm )
{
	if ( Tm <= 0 ) return "无效时间";
	
	CString tmpbuf;
	
	tm * pTm = localtime( &Tm );
	tmpbuf.Format( "%04d-%02d-%02d %02d:%02d:%02d", 
		pTm->tm_year + 1900, pTm->tm_mon + 1, pTm->tm_mday,
		pTm->tm_hour, pTm->tm_min, pTm->tm_sec );
	
	return tmpbuf;
}

void CLog::Write( LPCSTR format, ... )
{
	va_list arglist; 
	char buffer[2048]; 
	
	va_start (arglist,format); 
	vsprintf(buffer, format, arglist); 
	va_end (arglist); 
	
	if ( m_bSendLogToWindow )
	{
		HWND hReceiver = ::FindWindow(NULL, _T("Analyser"));
		if (hReceiver)
		{
			COPYDATASTRUCT cds;
			ZeroMemory(&cds, sizeof(COPYDATASTRUCT));
			cds.dwData = 0x00031337;
			cds.cbData = _tcslen(buffer) + sizeof(TCHAR);
			cds.lpData = buffer;
			::SendMessage(hReceiver, WM_COPYDATA, NULL, (LPARAM) &cds);
		}
	}
	 
	if ( m_bWriteLogToFile )
	{
		if ( OpenLogFileName() )
		{
			time_t nDateTime = mktime( CTime::GetCurrentTime().GetLocalTm() );			
			CString sDateTime = MakeTimeString( nDateTime );
			CString sLogText = "[";
			sLogText += sDateTime + "] ";
			sLogText += buffer;
			sLogText += "\n";
			
			fprintf( m_pFile, sLogText );
			fflush( m_pFile );
		}
	}
}