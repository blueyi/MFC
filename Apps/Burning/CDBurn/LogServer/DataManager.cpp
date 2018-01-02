// DataManager.cpp: implementation of the CDataManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LogServer.h"
#include "DataManager.h"
#include "CommonDefineFunc.h"

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
	
	m_sWorkDirectory = GetExeDirectory();
	m_sWorkDirectory += "\\Log";

//	m_sWorkDirectory = "..\\XinAoMDTMRI\\Prospect\\bin\\Log";

	m_iPermittedLogFileNum = GetPrivateProfileInt( "Options", "PermittedLogFileNum", 50, m_sConfigFileName );

	//	SW02,PROSPECT软件扫描参数
	//	MS01,磁体温控器
	//	RS01,射频放大器
	//	GS01,梯度放大器
	//	GS02,梯度电源
	//	GS03,匀场放大器
	//	SP01,谱仪
	//	OS01,SIU
	//	OS02,门控
	//	OS03,电动病床
	//	I000,信息类
	//	UNNO,unknown
	m_mSaveRecordFlag["SW02"] = GetPrivateProfileInt( "Options", "SW02", true, m_sConfigFileName );
	m_mSaveRecordFlag["MS01"] = GetPrivateProfileInt( "Options", "MS01", true, m_sConfigFileName );
	m_mSaveRecordFlag["RS01"] = GetPrivateProfileInt( "Options", "RS01", true, m_sConfigFileName );
	m_mSaveRecordFlag["GS01"] = GetPrivateProfileInt( "Options", "GS01", true, m_sConfigFileName );
	m_mSaveRecordFlag["GS02"] = GetPrivateProfileInt( "Options", "GS02", true, m_sConfigFileName );
	m_mSaveRecordFlag["GS03"] = GetPrivateProfileInt( "Options", "GS03", true, m_sConfigFileName );
	m_mSaveRecordFlag["SP01"] = GetPrivateProfileInt( "Options", "SP01", true, m_sConfigFileName );
	m_mSaveRecordFlag["OS01"] = GetPrivateProfileInt( "Options", "OS01", true, m_sConfigFileName );
	m_mSaveRecordFlag["OS02"] = GetPrivateProfileInt( "Options", "OS02", true, m_sConfigFileName );
	m_mSaveRecordFlag["OS03"] = GetPrivateProfileInt( "Options", "OS03", true, m_sConfigFileName );
	m_mSaveRecordFlag["I000"] = GetPrivateProfileInt( "Options", "I000", true, m_sConfigFileName );
}

void CDataManager::WriteOptionsToFile()
{
	char sVal[255];

	sprintf( sVal, "%d", m_iPermittedLogFileNum );
	WritePrivateProfileString( "Options", "PermittedLogFileNum", sVal, m_sConfigFileName );

	sprintf( sVal, "%d", m_mSaveRecordFlag["SW02"] );
	WritePrivateProfileString( "Options", "SW02", sVal, m_sConfigFileName );
	sprintf( sVal, "%d", m_mSaveRecordFlag["MS01"] );
	WritePrivateProfileString( "Options", "MS01", sVal, m_sConfigFileName );
	sprintf( sVal, "%d", m_mSaveRecordFlag["RS01"] );
	WritePrivateProfileString( "Options", "RS01", sVal, m_sConfigFileName );
	sprintf( sVal, "%d", m_mSaveRecordFlag["GS01"] );
	WritePrivateProfileString( "Options", "GS01", sVal, m_sConfigFileName );
	sprintf( sVal, "%d", m_mSaveRecordFlag["GS02"] );
	WritePrivateProfileString( "Options", "GS02", sVal, m_sConfigFileName );
	sprintf( sVal, "%d", m_mSaveRecordFlag["GS03"] );
	WritePrivateProfileString( "Options", "GS03", sVal, m_sConfigFileName );
	sprintf( sVal, "%d", m_mSaveRecordFlag["SP01"] );
	WritePrivateProfileString( "Options", "SP01", sVal, m_sConfigFileName );
	sprintf( sVal, "%d", m_mSaveRecordFlag["OS01"] );
	WritePrivateProfileString( "Options", "OS01", sVal, m_sConfigFileName );
	sprintf( sVal, "%d", m_mSaveRecordFlag["OS02"] );
	WritePrivateProfileString( "Options", "OS02", sVal, m_sConfigFileName );
	sprintf( sVal, "%d", m_mSaveRecordFlag["OS03"] );
	WritePrivateProfileString( "Options", "OS03", sVal, m_sConfigFileName );
	sprintf( sVal, "%d", m_mSaveRecordFlag["I000"] );
	WritePrivateProfileString( "Options", "I000", sVal, m_sConfigFileName );
}

CString CDataManager::GetExeDirectory()
{
	// 去掉倒数反斜扛,获取目录名
	CString sExePath;
	char tmp[ MAX_PATH ];
	::GetModuleFileName( NULL, tmp, MAX_PATH );
	size_t i;
	for ( i = strlen(tmp)-1; i>0 && tmp[i] != '\\'; i-- );
	tmp[ i ]='\0';
	sExePath = tmp;
	
	return sExePath;
}


void CDataManager::FindLogFiles()
{	
	m_vLogFilesName.clear();
	
	CString sLogFile = m_sWorkDirectory;
	sLogFile += "\\XABW_MRI_*.txt";
	
	CFileFind oFileFinder;
	BOOL IsFinded=(BOOL)oFileFinder.FindFile( sLogFile );
	while( IsFinded )
	{
		IsFinded = (BOOL)oFileFinder.FindNextFile();
		
		if(!oFileFinder.IsDots())
		{
			CString sFoundFileName = oFileFinder.GetFileName().GetBuffer(_MAX_PATH);
				CString sTemp;
				sTemp.Format( "%s\\%s",m_sWorkDirectory, oFileFinder.GetFileName().GetBuffer(_MAX_PATH) );
				m_vLogFilesName.push_back( sTemp );
		}
	}
	
	oFileFinder.Close();
}


void CDataManager::DeleteRedundanceFiles()
{
	if ( m_vLogFilesName.size() > m_iPermittedLogFileNum )
	{
		for ( int i= m_iPermittedLogFileNum; i< m_vLogFilesName.size(); i++ )
		{
			DeleteFile( m_vLogFilesName[i] );
		}
	}
}