// DataManager.cpp: implementation of the CDataManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DataManager.h"
#pragma warning (disable:4786)
#include <fstream>
#include <sstream>
#include <iomanip>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------------------------------
CDataManager CDataManager::m_Object;

// -----------------------------------------------------------------------------------------------------------

CDataManager::CDataManager()
{
	// 获取配置文件名
	CString sAppPath, sPathFile;
	::GetCurrentDirectory( 255, sAppPath.GetBuffer(255) );
	m_sConfigFileName.Format( "%s\\LogServer.ini", sAppPath );

	// 读取配置信息
	ReadOptionsFromFile();
}

CDataManager::~CDataManager()
{

}

CDataManager& CDataManager::GetHandle()
{
	return m_Object;
}

void CDataManager::ReadOptionsFromFile()
{
	char sVal[255];
	
	GetPrivateProfileString( "Options", "WorkDirectory", "C:\\Program Files\\XinAoMDTMRI\\Prospect\\bin\\", 
		sVal, 255, m_sConfigFileName );
	m_sWorkDirectory = sVal;

	GetPrivateProfileString( "Options", "StartDate", "20080101", sVal, 255, m_sConfigFileName );
	m_sStartDate = sVal;
	GetPrivateProfileString( "Options", "StartTime", "000000", sVal, 255, m_sConfigFileName );
	m_sStartTime = sVal;
	GetPrivateProfileString( "Options", "EndDate", "20080301", sVal, 255, m_sConfigFileName );
	m_sEndDate = sVal;
	GetPrivateProfileString( "Options", "EndTime", "235959", sVal, 255, m_sConfigFileName );
	m_sEndTime = sVal;
}

void CDataManager::WriteOptionsToFile()
{
	WritePrivateProfileString( "Options", "WorkDirectory", m_sWorkDirectory, m_sConfigFileName );

	WritePrivateProfileString( "Options", "StartDate", m_sStartDate, m_sConfigFileName );
	WritePrivateProfileString( "Options", "StartTime", m_sStartTime, m_sConfigFileName );
	WritePrivateProfileString( "Options", "EndDate", m_sEndDate, m_sConfigFileName );
	WritePrivateProfileString( "Options", "EndTime", m_sEndTime, m_sConfigFileName );
}

/*
void CDataManager::FindLogFile()
{
	std::vector<CString> m_vLogFilesName;
	
	m_vLogFilesName.clear();

	CString sStartFileName, sEndFileName;
	m_sStartDate.TrimLeft();
	m_sStartDate.TrimRight();
	sStartFileName.Format( "XABW_MRI_%s.txt", m_sStartDate );
	m_sEndDate.TrimLeft();
	m_sEndDate.TrimRight();
	sEndFileName.Format( "XABW_MRI_%s.txt", m_sEndDate );
	
	CString sFile = m_sWorkDirectory;
	sFile += "\\*.txt";
	
	CFileFind oFileFinder;
	BOOL IsFinded=(BOOL)oFileFinder.FindFile( sFile );
	while( IsFinded )
	{
		IsFinded = (BOOL)oFileFinder.FindNextFile();
		
		if(!oFileFinder.IsDots())
		{
			CString sFoundFileName = oFileFinder.GetFileName().GetBuffer(_MAX_PATH);
			if ( sFoundFileName >= sStartFileName && sFoundFileName <= sEndFileName )
			{
				CString sTemp;
				sTemp.Format( "%s\\%s",m_sWorkDirectory, oFileFinder.GetFileName().GetBuffer(_MAX_PATH) );
				m_vLogFilesName.push_back( sTemp );
			}
		}
	}
	
	oFileFinder.Close();
}
*/

void CDataManager::ReadLogRecordFromFile()
{
	int iStartDate = atoi( m_sStartDate );
	int iEndDate = atoi( m_sEndDate );
	CString sFileName;
	
	m_mSequenceName.clear();
	m_mSequenceName["All"] = "All";
	m_mCoilType.clear();	
	m_mCoilType["All"] = "All";

	m_vRecords_ScanParams.clear();
	
	for ( int i= iStartDate; i<= iEndDate; i++ )
	{
		sFileName.Format( "%s\\XABW_MRI_%d.txt", m_sWorkDirectory, i );
		ReadLogRecord( sFileName );
	}

	GetShownRecords();
}

bool CDataManager::ReadLogRecord( CString sFileName)
{
	CFile oIniFile;
	if( oIniFile.Open( sFileName, CFile::modeRead ) == FALSE )
	{
		return false;
	}
	
	CArchive ar(&oIniFile, CArchive::load);
	CString sLine = "";
	CString skey, sData;
	int iSplitIndex;
	
	do
	{
		if(sLine.GetLength() == 0)
		{
			continue;
		}
				
		// 解析Log记录
		iSplitIndex = sLine.Find(";");			
		
		skey = sLine.Left( iSplitIndex );
		skey.TrimLeft();
		skey.TrimRight();
		if ( skey == "" ) 
		{
			continue;
		}
				
		if ( skey == "0101")
		{
			sData = sLine.Mid( iSplitIndex + 1 );
			sData.TrimLeft();
			sData.TrimRight();

			iSplitIndex = sData.Find(";");
			m_sSerialNumOfEquip = sData.Left( iSplitIndex );
			sData = sData.Mid( iSplitIndex + 1 );
			m_sNameOfInstitution = sData;
		}
		else
		{
			ParseLogRecord( sLine );
		}
				
	} while(ar.ReadString(sLine));
	
	ar.Close();
	oIniFile.Close();
	
	return true;
}

void CDataManager::ParseLogRecord( CString sRecordStrng )
{
	CString sData;
	int iSplitIndex;
	CString sTempString;

	STRUCT_LOG_RECORD oRecord;

	// 告警级别 
	iSplitIndex = sRecordStrng.Find(";");
	oRecord.sAlarmLevel = sRecordStrng.Left( iSplitIndex );
	
	// Date
	sRecordStrng = sRecordStrng.Mid( iSplitIndex + 1 );
	iSplitIndex = sRecordStrng.Find(";");
	oRecord.sDate = sRecordStrng.Left( iSplitIndex );
	
	// Time
	sRecordStrng = sRecordStrng.Mid( iSplitIndex + 1 );
	iSplitIndex = sRecordStrng.Find(";");
	oRecord.sTime = sRecordStrng.Left( iSplitIndex );

	// 来源子系统和模块
	sRecordStrng = sRecordStrng.Mid( iSplitIndex + 1 );
	iSplitIndex = sRecordStrng.Find(";");
	oRecord.sSource = sRecordStrng.Left( iSplitIndex );
	
	// 分类
	sRecordStrng = sRecordStrng.Mid( iSplitIndex + 1 );
	iSplitIndex = sRecordStrng.Find(";");
	oRecord.sRecordType = sRecordStrng.Left( iSplitIndex );
	
	// 数据体
	sData = sRecordStrng.Mid( iSplitIndex + 1 );
	if ( oRecord.sSource == "SW02" && oRecord.sRecordType == "0001" )
	{
		// Study ID
		iSplitIndex = sData.Find(",");
		oRecord.sStudyID = sData.Left( iSplitIndex );

		// Series ID
		sData = sData.Mid( iSplitIndex + 1 );
		iSplitIndex = sData.Find(",");
		oRecord.sSeriesID = sData.Left( iSplitIndex );

		// CoilType
		sData = sData.Mid( iSplitIndex + 1 );
		iSplitIndex = sData.Find(",");
		oRecord.sCoilType = sData.Left( iSplitIndex );
		
		// Sequence Name
		sData = sData.Mid( iSplitIndex + 1 );
		iSplitIndex = sData.Find(",");
		oRecord.sSequenceName = sData.Left( iSplitIndex );
		
		// O1
		sData = sData.Mid( iSplitIndex + 1 );
		iSplitIndex = sData.Find(",");
		oRecord.sO1 = sData.Left( iSplitIndex );
		
		// TG
		sData = sData.Mid( iSplitIndex + 1 );
		iSplitIndex = sData.Find(",");
		oRecord.sTG = sData.Left( iSplitIndex );
		
		// RG
		sData = sData.Mid( iSplitIndex + 1 );
		iSplitIndex = sData.Find(",");
		if ( iSplitIndex != -1 )
		{
			oRecord.sRG = sData.Left( iSplitIndex );
		}
		else
		{
			oRecord.sRG = sData;
		}
		
		// SF
		if ( iSplitIndex != -1 )
		{
			sData = sData.Mid( iSplitIndex + 1 );
			oRecord.sSF = sData;
		}
		else
		{
			oRecord.sSF = "SF=0.0";
		}
		
		
		// 进一步整理数据
		iSplitIndex = oRecord.sStudyID.Find("=");
		oRecord.sStudyID = oRecord.sStudyID.Right( oRecord.sStudyID.GetLength() - iSplitIndex - 1 );
		
		iSplitIndex = oRecord.sSeriesID.Find("=");
		oRecord.sSeriesID = oRecord.sSeriesID.Right( oRecord.sSeriesID.GetLength() - iSplitIndex - 1 );

		iSplitIndex = oRecord.sCoilType.Find("=");
		oRecord.sCoilType = oRecord.sCoilType.Right( oRecord.sCoilType.GetLength() - iSplitIndex - 1 );

		iSplitIndex = oRecord.sSequenceName.Find("=");
		oRecord.sSequenceName = oRecord.sSequenceName.Right( oRecord.sSequenceName.GetLength() - iSplitIndex - 1 );

		iSplitIndex = oRecord.sO1.Find("=");
		oRecord.sO1 = oRecord.sO1.Right( oRecord.sO1.GetLength() - iSplitIndex - 1 );

		iSplitIndex = oRecord.sTG.Find("=");
		oRecord.sTG = oRecord.sTG.Right( oRecord.sTG.GetLength() - iSplitIndex - 1 );

		iSplitIndex = oRecord.sRG.Find("=");
		oRecord.sRG = oRecord.sRG.Right( oRecord.sRG.GetLength() - iSplitIndex - 1 );

		iSplitIndex = oRecord.sSF.Find("=");
		oRecord.sSF = oRecord.sSF.Right( oRecord.sSF.GetLength() - iSplitIndex - 1 );

		oRecord.bShowBySeqName = true;
		oRecord.bShowByCoilType = true;

		m_vRecords_ScanParams.push_back( oRecord );
//		m_vShownRecords.push_back( &m_vRecords_ScanParams[m_vRecords_ScanParams.size()-1] );

		m_mSequenceName[ oRecord.sSequenceName ] = oRecord.sSequenceName;
		m_mCoilType[ oRecord.sCoilType ] = oRecord.sCoilType;
	}
}

void CDataManager::GetShownRecords()
{
	m_vShownRecords.clear();

	for ( int i=0; i< m_vRecords_ScanParams.size(); i++ )
	{
		if ( m_vRecords_ScanParams[i].bShowBySeqName && m_vRecords_ScanParams[i].bShowByCoilType )
		{
			m_vShownRecords.push_back( &m_vRecords_ScanParams[i] );
		}
	}
}