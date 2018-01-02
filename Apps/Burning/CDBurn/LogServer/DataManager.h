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
#include "CommonDefine.h"

// -----------------------------------------------------------------------------------------------------------

class CDataManager  
{
public:
	CDataManager();
	virtual ~CDataManager();

	static CDataManager m_Object;
	static CDataManager& GetHandle();
	
public:
	// Log记录
	std::vector<STRUCT_PACKET_FAULT_DIAGNOSIS> m_vRecords;
	
	// 配置信息
	// 配置信息保存在LogServer.ini中
	// *** 通过UI界面进行各选项的配置
	CString					m_sConfigFileName;		// 配置文件全路径名
	CString					m_sWorkDirectory;		// 工作目录
	std::map<CString,bool>	m_mSaveRecordFlag;		// Log记录内容过滤配置
	unsigned int			m_iPermittedLogFileNum;	// 允许保存的最大Log文件个数

	void ReadOptionsFromFile();
	void WriteOptionsToFile();

	CString GetExeDirectory();

	// 文件个数维护
	std::vector<CString> m_vLogFilesName;	
	void FindLogFiles();
	void DeleteRedundanceFiles();
};

#endif // !defined(AFX_DATAMANAGER_H__72878744_9F4F_4E1A_9E7D_BAC9E6C7CCEC__INCLUDED_)
