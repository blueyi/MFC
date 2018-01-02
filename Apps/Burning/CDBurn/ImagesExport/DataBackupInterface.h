// Parameter.h: interface for the CDataBackupInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DataExportInterface__INCLUDED_)
#define _DataExportInterface__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include"stdafx.h"

// -----------------------------------------------------------------------------------------------------------
#pragma warning (disable : 4786)
#include <vector>

//extern "C" _declspec(dllexport) int Test();
/*

*/
// -----------------------------------------------------------------------------------------------------------

#ifndef _CHEN_SHI_
#define _CHEN_SHI_
#endif// 


class /*AFX_EXT_CLASS*/ CDataExportInterface  
{
public:
	CDataExportInterface();
	virtual ~CDataExportInterface();

private:

	int m_nStorageMediumType;	// 0-None; 1-Hard Disk; 2-CD; 3-DVD
	int m_nMoveOrCopy;			// 0-None; 1-Copy; 2-Move
	CString m_sLocalPath, m_sBackupPath;
	long m_CurFolderSize;//统计文件夹大小
	//需要一个中间的数据库 没有只读属性
	CString m_BackDbPath;

public:
	bool SaveImageDataToBmp(unsigned char *pDest,
						int w,
						int h,
						int format,
						char *pFileName);
	
	BOOL ExportStudyToBMP(CString szImageRootPath,CString szStudyID,CString strDestFilePathName,BOOL nSaveMed);
	//校验Path
	static BOOL CheckAndCreateDir(CString szDir);
//校验磁盘空间
	static BOOL CheckDiskSpaceAndEnWrite(CString szPath, int nTotalImage);
//导出程序入口
	static bool ExportStudyToDicom(CString szImageRootPath,CString szStudyID,CString strDestFilePathName,BOOL nSaveMed);

//导出过程,按照导出的数据结构进行图像导出
	/*********zyh add 2008.3.7 from cs*********/
	static long ExportAllSelStudyToTempDICOM(void *pExportBlockX);
	static long ThreadExportStudySendToPacs(LPVOID pVoid);
	/**********************************************/
	
	

	static BOOL ExportSelectStudy(void* pExportBlockX);
	/*********zyh add 2008.2.27*********/
	static BOOL ExportSelectStudy2(void *pExportBlockX, CProgressCtrl *pProcess);
	/**********************************************/
	
	static UINT ThreadExportStudy(LPVOID pVoid);
	int SetBackupParam();
	// 执行备份
	// vStudyId—输入所有要备份的Study的目录名
	bool ExecuteBackup( CString sLocalPath, CString sDatabaseName, std::vector<CString> vStudyId );
	// 设置数据恢复参数
	// 返回：备份数据的路径
	CString SetRestoreParam(CString sLocalPath);
	// 执行数据恢复
	// vStudyId—输入所有要恢复的备份Study的目录名
	// 注意：不能copy数据库到本地
	bool ExecuteRestore( CString sLocalPath, std::vector<CString> vStudyId );
	// 删除本地的图像文件
	bool DeleteImageFile( CString sLocalPath, std::vector<CString> vStudyId );
	////////////////////////////////////////////////////////////////////////////
	//下面的是动态库那不的方法，无法从外部调用。
	bool CreateEqualFolders(CString csDirPath, CString csDesPath,int dMorC,bool bMdb);
	long GetFolderSize(CString sFolderPath);
	void CalculateFolderSize(CString csDirPath);
	bool DeleteFolderFiles(CString csDirPath);
	BOOL DeleteDirectory(char *DirName);
	bool DeleteDirAndFiles(CString csFilePath);
	bool CreateDirectoryMulty(CString csPathDir);
		
	
};

#endif // !defined(_DataBackupInterface__INCLUDED_)
