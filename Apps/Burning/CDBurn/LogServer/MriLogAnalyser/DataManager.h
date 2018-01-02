// DataManager.h: interface for the CDataManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATAMANAGER_H__72878744_9F4F_4E1A_9E7D_BAC9E6C7CCEC__INCLUDED_)
#define AFX_DATAMANAGER_H__72878744_9F4F_4E1A_9E7D_BAC9E6C7CCEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// -----------------------------------------------------------------------------------------------------------
#pragma warning (disable:4786)
#include <string>
#include <map>
#include <vector>

// -----------------------------------------------------------------------------------------------------------
struct STRUCT_LOG_RECORD
{
	bool bShowBySeqName, bShowByCoilType;

	CString sAlarmLevel;				// 告警级别。A1为一级告警
	CString sDate;						// 年月日。如：20060421
	CString sTime;						// 时分秒。如：121220
	CString sSource;					// 来源子系统和模块。如：SW01,SW－磁共振成像软件系统,01－数据管理模块;          
	CString sRecordType;				// 分类。如：0001    

	CString sStudyID;
	CString sSeriesID;
	CString sCoilType;
	CString sSequenceName;
	
	CString sO1, sTG, sRG, sSF;
//	CString sDescr[64*1024];				// 告警描述。如：STUDYID=22,SERIESID=5,COILTYPE=HEAD,SEQ=FSE2D,O1=-234.56,TG=13.6,RG=0.567
};
// -----------------------------------------------------------------------------------------------------------

	
class CDataManager  
{
public:
	CDataManager();
	virtual ~CDataManager();

	static CDataManager m_Object;
	static CDataManager& GetHandle();

	// 配置信息
public:
	// 配置信息保存在LogServer.ini中
	// *** 通过UI界面进行各选项的配置
	CString					m_sConfigFileName;		// 配置文件全路径名
	CString					m_sWorkDirectory;		// 工作目录
	
	void ReadOptionsFromFile();
	void WriteOptionsToFile();	
	
	// Log记录
public:
	// 查询时间段 
	CString m_sStartDate, m_sStartTime, m_sEndDate, m_sEndTime;
	// 用户名称
	CString m_sNameOfInstitution, m_sSerialNumOfEquip;
	// 扫描参数记录
	std::vector<STRUCT_LOG_RECORD> m_vRecords_ScanParams;
	std::vector<STRUCT_LOG_RECORD*> m_vShownRecords;
	std::map<CString,CString> m_mSequenceName, m_mCoilType;
	
	void ReadLogRecordFromFile();
	bool ReadLogRecord( CString sFileName);
	void ParseLogRecord( CString sRecordStrng );
	void GetShownRecords();
	
};

#endif // !defined(AFX_DATAMANAGER_H__72878744_9F4F_4E1A_9E7D_BAC9E6C7CCEC__INCLUDED_)
