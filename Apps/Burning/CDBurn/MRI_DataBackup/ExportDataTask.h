// ExportDataTask.h: interface for the CExportDataTask class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXPORTDATATASK_H__F9C8894E_DFE2_4D97_A39F_44D3A521E345__INCLUDED_)
#define AFX_EXPORTDATATASK_H__F9C8894E_DFE2_4D97_A39F_44D3A521E345__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//////////////////////////////////////
 #include"vector"
// #include "../ImageHeader/Image.h"
// #include "../ImageHeader/Series.h"
// #ifndef _CHEN_SHI_
// #define _CHEN_SHI_
// #endif// 
// #ifdef _CHEN_SHI_
// 	#define _OPEN_STUDY_ 0
// 	#define _SELECT_PATIENT_ 1
// 	#define _PATIENT_INFO_EDIT_ 2
// 	#define _BACKUP_DATA 3
// 	#define _RESTORE_DATA_ 4
// 	#define _EXPORT_DATA_ 5
 	#define _MAX_STRING_LENGHT_  256
// #ifndef _EXPORT_BLOCK_ 
// #define _EXPORT_BLOCK_
// //typedef _EXPORT_STRUCT_
typedef struct
{
	char	m_pStydyID[_MAX_STRING_LENGHT_];
	int		m_nSeriesIndex;
	std::vector<CString>m_szExportStudyID;
	BOOL	m_bShowStudy;
	std::vector<CBitmap*>m_pImageDataContainer;
	CString m_pFileType;
	CString m_pDesPosition;
	BOOL	m_bSaveType;
	CString m_szImageRootPath;
	
}_EXPORT_STRUCT_;
#define _DCM_TYPE_ 0
#define _BMP_TYPE_ 1
#define _JPEG_TYPE_ 2
// 
// 
// #endif
// 
// #endif
//class CProgressAndTipDlg;
class CExportDataTask  
{
 public:
// 	BOOL ExportStudyToJPEG(CString szImageRootPath,CString szStudyID,CString strDestFilePathName,BOOL nSaveMed);
// public:
// 
// 	/*static*/ bool ReadImageFileHeader(const std::string& strFilename, CBIImageHeader& imageHeader);
// 	bool SaveImageDataToBmp(unsigned char *pDest,
// 					int w,
// 					int h,
// 					int format,
// 					char *pFileName);
// 	BOOL ExportStudyToBMP(CString szImageRootPath,CString szStudyID,CString strDestFilePathName,BOOL nSaveMed);
// //校验Path
// 	/*static*/ BOOL CheckAndCreateDir(CString szDir);
// 
// 	//Modified by Tom, --2008.07.10
// //校验磁盘空间
// 	/*static*/ int CheckDiskSpaceAndEnWrite(CString szPath, int nTotalImage);
// //导出程序入口
 	/*static*/ long ExportStudyToDicom(CString szImageRootPath,CString szStudyID,CString strDestFilePathName,BOOL nSaveMed,BOOL bSaveInfo, BOOL bCreateDicomDir = FALSE);
// //导出过程,按照导出的数据结构进行图像导出
// 	BOOL ExportSelectStudy(void *pExportBlockX);
// 	/*********zyh add 2008.2.27*********/
 	BOOL ExportSelectStudy2(void *pExportBlockX, CProgressCtrl *pProcess);
// 	/**********************************************/
// 	
// public:
// 	/*********zyh add 2008.3.7*********/
// 	//from cs code copy
// 	CProgressAndTipDlg * pProgDlg;
// 	BOOL SendDICOMImageFileToPACS(CString szPathFileName,CString szFileName);
// 	long ExportAllSelStudyToTempDICOM(void *pExportBlockX);
// 	bool DeleteDirAndFiles(CString csFilePath);
// 	BOOL DeleteDirectory(char *DirName);
// 	/**********************************************/
// 	/*********zyh add 2008.2.27*********/
// 	//增加生成dicomdir功能,增加参数u。
// 	/*static*/ long ExportSeriesToDICOM(CSeries*pSeries,CString szImgRootPath, CString strDestFilePathName, BOOL nSaveMed, BOOL bCreateDicomDir = FALSE);
// 	/**********************************************/
	
	
	CExportDataTask();
	virtual ~CExportDataTask();

};

#endif // !defined(AFX_EXPORTDATATASK_H__F9C8894E_DFE2_4D97_A39F_44D3A521E345__INCLUDED_)
