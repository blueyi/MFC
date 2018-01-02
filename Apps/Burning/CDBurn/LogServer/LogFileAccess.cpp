// LogFileAccess.cpp: implementation of the CLogFileAccess class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LogServer.h"
#include "LogFileAccess.h"
#include "CommonDefineFunc.h"
#include "DataManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogFileAccess::CLogFileAccess()
{
	m_pFile = NULL;
	m_sNameOfLogFile = "";

	char sAppPath[255];
	::GetCurrentDirectory( 255, sAppPath );
	m_sAppPath = sAppPath;
	m_sPathOfLogFile.Format( "%s\\Log", sAppPath );
	::CreateDirectory( m_sPathOfLogFile, NULL );
	
	m_pTime = new tm();
	memset( m_pTime, 0, sizeof(tm) );
	
	OpenLogFileName();
}

CLogFileAccess::~CLogFileAccess()
{
	delete m_pTime;
	
	if ( m_pFile )
	{
		fclose( m_pFile );
	}
}

void CLogFileAccess::ReadHederInfoFromCfgFile( CString& sSerialNumOfEquip, CString& sNameOfInstitution )
{
	CString sCfgFile;
	sCfgFile.Format( "%s\\xbmri.ini", m_sAppPath );
	CFileFind oFileFinder;
	BOOL bExist = oFileFinder.FindFile( sCfgFile );
	if ( !bExist )
	{
		CString sMsg;
		sMsg.Format( "Can't find config file: %s", sCfgFile );
		AfxMessageBox( sMsg );
	}
	
	GetPrivateProfileString( "SYSTEM_BIMRI_CONFIG_DIRECTORY", "institution_name", "XinAoMDT MRI Lab", sNameOfInstitution.GetBuffer(64), 32, sCfgFile );
	GetPrivateProfileString( "SYSTEM_BIMRI_CONFIG_DIRECTORY", "SerialNumOfEquipment", "XABW_MRI_00001", sSerialNumOfEquip.GetBuffer(64), 32, sCfgFile );
}

bool CLogFileAccess::OpenLogFileName()
{
	time_t nDateTime = mktime( CTime::GetCurrentTime().GetLocalTm() );	
	tm * pTm = localtime( &nDateTime );
	
	// 若时间不符，则按当前系统时间产生新的文件名
	if ( m_pTime->tm_year != pTm->tm_year 
		|| m_pTime->tm_mon + 1 != pTm->tm_mon + 1 
		|| m_pTime->tm_mday != pTm->tm_mday )
	{
		memcpy( m_pTime, pTm, sizeof(tm) );
		m_sNameOfLogFile.Format( "%s\\XABW_MRI_%04d%02d%02d.txt", 
			m_sPathOfLogFile, 
			pTm->tm_year + 1900, pTm->tm_mon + 1, pTm->tm_mday );
		
		if ( m_pFile )
		{
			fclose( m_pFile );
		}
		
		CFileFind oFileFinder;
		BOOL bExist = oFileFinder.FindFile( m_sNameOfLogFile );
		
		m_pFile = fopen( m_sNameOfLogFile, "a+t" );
		if ( !m_pFile )
		{
			return false;
		}
		else
		{
			// 写文件头到新的文件
			if ( !bExist )
			{
				CString sSerialNumOfEquip, sNameOfInstitution;
				ReadHederInfoFromCfgFile( sSerialNumOfEquip, sNameOfInstitution );
				fprintf( m_pFile, "0101;%s;%s\n", sSerialNumOfEquip.GetBuffer(64), sNameOfInstitution.GetBuffer(64) );			
				fflush( m_pFile );
			}
		}
	}
	
	if ( !m_pFile )
	{
		return false;
	}
	
	return true;
}

void CLogFileAccess::SaveToFile( PVOID pData )
{
	// 删除冗余的Log文件
	CDataManager::GetHandle().FindLogFiles();
	CDataManager::GetHandle().DeleteRedundanceFiles();
	
	
	if ( !OpenLogFileName() )
	{
		return;
	}

	char* pcData = (char*)pData;
	STRUCT_PACKET_FAULT_DIAGNOSIS oRecord;
	memcpy ( &oRecord, pcData, sizeof(STRUCT_PACKET_FAULT_DIAGNOSIS) );
	
	// 过滤Log记录内容
	CString sLogSource = oRecord.sSource;
	sLogSource.MakeUpper();
	if ( CDataManager::GetHandle().m_mSaveRecordFlag[ sLogSource ] )
	{
		// 数据包类型STRUCT_PACKET_TYPE部分仅用于通信，不保存到文件
		// 字段顺序和分隔符为：A1;20060421;121220;SW01;0001;STUDYID=22,SERIESID=5,COILTYPE=HEAD,SEQ=FSE2D,O1=-234.56,TG=13.6,RG=0.567
		fprintf( m_pFile, "%s;%s;%s;%s;%s;%s\n", 
			oRecord.sTypeOfFault, 
			oRecord.sDate, 
			oRecord.sTime, 
			oRecord.sSource, 
			oRecord.sTypeOfRecord,
			oRecord.sDescr );
		fflush( m_pFile );
	}
}