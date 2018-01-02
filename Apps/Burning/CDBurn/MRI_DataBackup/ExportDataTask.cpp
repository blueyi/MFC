// ExportDataTask.cpp: implementation of the CExportDataTask class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "ImagesExport.h"
#include "ExportDataTask.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
// #include "../ImageHeader/Containers.h"
#include "../ImageHeader/Study.h"
// #include "../ImageHeader/Series.h"
// #include "../ImageHeader/Image.h"
// //#include "../Storage/StorageManager.h"
// //#include "../BCGControlBar/BCGImage.h"
// #include "fstream.h"
// #include "iostream.h"
// #include"istream"
// 
// #include"string.h"
// #include"../BIGlobals/ConfigManager.h"
//#include "../ImageDisplay/SeriesViewData.h"
//#include "../ImageDisplay/ViewDataManager.h"
//#include "../ImageDisplay/ScanViewData.h"
//#include "../Filming/FilmingDlg.h"


//#include "../ImageDisplay/SeriesViewData.h"
//#include "../ImageDisplay/ViewDataManager.h"
//#include "../ImageDisplay/ScanViewData.h"
//#include "../ImageDisplay/LayoutWnd.h"
//#include "../MRIDatabase/DBInterface.h"
//#include "../Storage/StorageManager.h"

//#include "../ParamsPages/SeriesParamsDialog.h"

//#include "../DataProcessing/TOF3DReconTask.h"
//#include "../Filming/FilmingDlg.h"
//#include "../Filming/WaitingDlg.h"
//#include"../StatusWindow/ProgDlg.h"
// #include <shlwapi.h> 

//#include "ProgressAndTipDlg.h"
// #ifdef _CHEN_SHI_
// #define _MAX_BUFFER_  3*1024*1024
// #endif
//#include "JpegFile.h"




//extern CProgressDlg oProgressDlg;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// bool ConvertXB2Dicom(CBIImageHeader imageHeader,double nAngle,BOOL nVerFlip,BOOL nHorFlip,
// 					 short* psImageData,
// 					 char* pcDicomData,
// 					 int& nDicomDataLen);
// 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CExportDataTask::CExportDataTask()
{

}

CExportDataTask::~CExportDataTask()
{

}
/********************************************
函数名称: 
描    述: 
输    入: 无
输    出: 无
返    回: 无
其    它: 无
修改历史:
       <修改人> <时间>     <版本 >   <描述>
    1. 朱映华    2008.2.27 v1.0 
*********************************************/
BOOL CExportDataTask::ExportSelectStudy2(void *pExportBlockX, CProgressCtrl *pProcess)
{
	_EXPORT_STRUCT_ *pExportBlock=(_EXPORT_STRUCT_ *)pExportBlockX;
	int nCountOfStudy=pExportBlock->m_szExportStudyID.size();
	pProcess->SetRange(0, nCountOfStudy);
	pProcess->SetStep(1);
	pProcess->SetPos(0);
	if(nCountOfStudy==0)
	{
		return FALSE;
	}
	pExportBlock->m_pFileType.MakeUpper();


	BOOL bSaveInfo=pExportBlock->m_bSaveType;
	
	for(int i=0;i<nCountOfStudy;i++)
	{
		CString szSelectStudy=pExportBlock->m_szExportStudyID[i];
		CString szOnShowStudy=pExportBlock->m_pStydyID;
		int nOnShowSeries=pExportBlock->m_nSeriesIndex;
		
		BOOL nRet=ExportStudyToDicom(pExportBlock->m_szImageRootPath, szSelectStudy,
			pExportBlock->m_pDesPosition, _DCM_TYPE_, bSaveInfo, TRUE);
		pProcess->StepIt();
		
	}
	return TRUE;
}
// BOOL CExportDataTask::ExportSelectStudy(void *pExportBlockX)
// {
// 	_EXPORT_STRUCT_ *pExportBlock=(_EXPORT_STRUCT_ *)pExportBlockX;
// 	int nCountOfStudy=pExportBlock->m_szExportStudyID.size();
// 	if(nCountOfStudy==0)
// 	{
// 		return 0;
// 	}
// 	int nConvType=-1;
// 	pExportBlock->m_pFileType.MakeUpper();
// 	if(pExportBlock->m_pFileType=="DCM")
// 	{
// 		nConvType=_DCM_TYPE_;
// 	}
// 	else if(pExportBlock->m_pFileType=="BMP")
// 	{
// 		nConvType=_BMP_TYPE_;
// 	}
// 	else if(pExportBlock->m_pFileType=="JPEG")
// 	{
// 		nConvType=_JPEG_TYPE_;
// 
// 	}
// 	BOOL bSaveInfo=pExportBlock->m_bSaveType;
// 	
// 	for(int i=0;i<nCountOfStudy;i++)
// 	{
// 		CString szSelectStudy=pExportBlock->m_szExportStudyID[i];
// 		CString szOnShowStudy=pExportBlock->m_pStydyID;
// 		int nOnShowSeries=pExportBlock->m_nSeriesIndex;
// 		int nPos=oProgressDlg.m_Progress.GetPos();
// 		if(nPos<80)
// 		{
// 			oProgressDlg.StepIt();
// 
// 		}
// 		if(nConvType==_DCM_TYPE_)
// 		{
// 			BOOL nRet=ExportStudyToDicom(pExportBlock->m_szImageRootPath,szSelectStudy,
// 			pExportBlock->m_pDesPosition,nConvType,bSaveInfo);
// 
// 		}
// 		else if(nConvType==_BMP_TYPE_)
// 		{
// 			BOOL nRet=ExportStudyToBMP(pExportBlock->m_szImageRootPath,szSelectStudy,
// 			pExportBlock->m_pDesPosition,bSaveInfo);
// 		}
// 		else if(nConvType==_JPEG_TYPE_)
// 		{
// 			BOOL nRet=ExportStudyToJPEG(pExportBlock->m_szImageRootPath,szSelectStudy,
// 			pExportBlock->m_pDesPosition,bSaveInfo);
// 		}
// 	}
// 	return TRUE;
// }

//界面上不存在的部分
//nConvType 0 DICOM ; 1 BMP ...
/********************************************
函数名称: 
描    述: 
输    入: 无
输    出: 无
返    回: 无
其    它: 无
修改历史:
       <修改人> <时间>     <版本 >   <描述>
    1. 朱映华    2008.2.27 v1.0      调整函数并增加bCreateDicomdir参数
*********************************************/
long CExportDataTask::ExportStudyToDicom(CString szImageRootPath,CString szStudyID,CString strDestFilePathName,BOOL nSaveMed,BOOL bSaveInfo, BOOL bCreateDicomDir /*=FALSE*/)
{
	int nCount = 0;
	if(strDestFilePathName.Right(1)=="\\")
	{
		strDestFilePathName=strDestFilePathName.Left(strDestFilePathName.GetLength()-1);
	}
	/*BOOL bF=CheckDiskSpaceAndEnWrite(strDestFilePathName,50);
	if(bF==FALSE)
	{
		CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("IMAGE_EXPORT_MSG_DISK_ERROR"));
		return nCount;
	}*/
    //当前的Study ID
	std::string pStrData=(char*)szStudyID.operator LPCTSTR();
	
// 	CStudy* pStudy = CStorageManager::GetHandle().GetStudy(pStrData/*,TRUE*/);
// 	BOOL bCanClose = FALSE;
// 	if(NULL == pStudy)
// 	{
// 		pStudy = CStorageManager::GetHandle().GetStudy(pStrData,TRUE);
// 		if(!pStudy)
// 			return nCount;
// 		bCanClose = TRUE;
// 	}


// 	int nCountOfSeries=pStudy->GetCountOfSeries();
// 	int nIndex=1;
// 	for(int i=0;i<nCountOfSeries;nIndex++)
// 	{
// 		CSeries*pSeries=pStudy->GetSeries(nIndex);
// 		if(!pSeries)
// 			continue;
// 		
// 		int nCount1 = ExportSeriesToDICOM(pSeries,szImageRootPath,strDestFilePathName,bSaveInfo,bCreateDicomDir);
// 		nCount += nCount1 ;
// 		i++;
// 		if(FALSE == bCreateDicomDir && nCount1>0)
// 		{
// 			int nPos=oProgressDlg.m_Progress.GetPos();
// 			if(nPos<80)
// 				oProgressDlg.StepIt();
// 		}
// 	}
// 	if(bCanClose)
// 	{
// 		CViewDataManager::GetHandle().DeleteStudyData(pStudy);
// 		CStorageManager::GetHandle().CloseStudy(pStudy);
// 	}
// 	return nCount;
	return 0;
}

//Modified by Tom, --2008.07.10
/*
return value:
    -1: Path error;
	-2: Disk space not enough
	-3: Disk write error:cannot create file
	-4: Disk writing error:cannot delete file
*/
// int CExportDataTask::CheckDiskSpaceAndEnWrite(CString szPath, int nTotalImage)
// {
// 	if(szPath=="")
// 	{
// 		return -1;
// 	}
// 	BOOL bRes=PathFileExists(szPath);
// 	if(bRes==FALSE)
// 	{
// 		return -1;
// 	}
// 
// 	unsigned long nImgSize=512*1024*nTotalImage;
// 	ULARGE_INTEGER h1;
//     ULARGE_INTEGER h2;
//     ULARGE_INTEGER h3;
// 	if(szPath.GetLength()<2)
// 	{
// 		//AfxMessageBox("Path can't be recognized");
// //		CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("IMAGE_EXPORT_MSG_PATH_CANNOT_REC"));
// 		return -1;
// 	}
// 	CString szDiskName=szPath.Left(2);
// 	if(szDiskName.Right(1)!=":")
// 	{
// 		//AfxMessageBox("Path can't be recognized");
// //		CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("IMAGE_EXPORT_MSG_PATH_CANNOT_REC"));
// 		return -1;
// 	}
//     GetDiskFreeSpaceEx(szDiskName,&h1,&h2,&h3);
// 	
// 	unsigned long nDiskFreeSizeHigh=h1.u.HighPart;
// 	unsigned long nDiskFreeSizeLow=h1.u.LowPart;
// 	if(nDiskFreeSizeHigh==0 && nDiskFreeSizeLow<nImgSize)
// 	{
// 		//AfxMessageBox("Can't get enough space!");
// //		CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("IMAGE_EXPORT_MSG_CANNOT_GET_ENOUGH_SPACE"));
// 		return -2;
// 
// 	}
// 
// 
// 	HANDLE hFile; 
// 	
// 	hFile = CreateFile(szPath+"MYFILE.TXT",           // create MYFILE.TXT 
// 		GENERIC_WRITE,                // open for writing 
// 		0,                            // do not share 
// 		NULL,                         // no security 
// 		CREATE_ALWAYS,                // overwrite existing 
// 		FILE_ATTRIBUTE_NORMAL |       // normal file 
// 		FILE_FLAG_OVERLAPPED,         // asynchronous I/O 
// 		NULL);                        // no attr. template 
// 	
// 	if (hFile == INVALID_HANDLE_VALUE) 
// 	{ 
// 		CloseHandle(hFile);
// 		//AfxMessageBox("Could not write file.");  // process error
// 		return -3;
// 		
// 	}
// 	else
// 	{
// 		CloseHandle(hFile);
// 		BOOL bRes=DeleteFile(szPath+"MYFILE.TXT");
// 		if(bRes==FALSE)
// 		{
// 			return -4;
// 		}
// 	}
// 	return 0;
// 
// }
// BOOL CExportDataTask::CheckAndCreateDir(CString szDir)
// {
// 	if(szDir.Right(1)!="\\")
// 	{
// 		szDir+="\\";
// 	}
// 	//MakeSureDirectoryPathExists()
// 	BOOL bReturn=PathFileExists(szDir);
// 	if(bReturn==TRUE)
// 	{
// 		return TRUE;
// 	}
// 	CString szPathDir=szDir;
// 	CString szLeftStr;
// 	
// 	CString szRemainStr;
// 	int nPos=-1;
// 	do 
// 	{
// 		nPos=szPathDir.Find("\\",0);
// 		if(nPos>0)
// 		{
// 			szRemainStr+=szPathDir.Left(nPos);
// 			if(szRemainStr.Right(1)!="\\")
// 			{
// 				szRemainStr+="\\";
// 				
// 			}
// 			bReturn=PathFileExists(szRemainStr);
// 			if(bReturn==TRUE)
// 			{
// 				
// 			}
// 			else if(bReturn==FALSE)
// 			{
// 				BOOL nRes=CreateDirectory(szRemainStr,NULL);
// 				if(nRes==FALSE)
// 				{
// 					return FALSE;
// 				}
// 				
// 				
// 			}
// 			szPathDir=szPathDir.Right(szPathDir.GetLength()-nPos-1);
// 		}
// 		
// 	} while(nPos>0);
// 	return TRUE;
// }
// //Global Function
// const char gszOrgRoot[] = "1.2.840.1009";
// void CreateUID(char UID[], char szTerm[10][20], int nNum)
// {
// 	strcpy(UID, gszOrgRoot);
// 	for(int i=0; i<nNum; i++)
// 	{
// 		if(szTerm[i][0] == '0')
// 		{
// 			long nTemp;
// 			nTemp = atol(szTerm[i]);
// 			_ltoa(nTemp,szTerm[i],10);
// 		}
// 		strcat(UID,".");
// 		strcat(UID,szTerm[i]);
// 	}
// }
// 
// void CreateImgUID(CBIImageHeader imageHeader, char szImgUID[])
// {
// 	char    cT1[32];
// 	strcpy(szImgUID, gszOrgRoot);
// 
// 	strcat(szImgUID,".");
// 	CString csStationNo = CConfigManager::GetHandle().GetSiteField().InstName;
// //	strcat(szSeriesUID,".");
// 	strcat(szImgUID,csStationNo.GetBuffer(10));
// 
// 	//Study ID
// 	strcat(szImgUID,".");
// 	strcat(szImgUID,imageHeader.studyField.Id);
// 
// 	//Series ID
// 	strcat(szImgUID,".");
// 	itoa(imageHeader.seriesField.Id,cT1,10);
// 	strcat(szImgUID,cT1);
// //    strcat(szImgUID,".");
// 
// 	strcat(szImgUID,".");
// 	if (imageHeader.imageField.DateTime.year > 2000)
// 	{
// 		//link year
// 		itoa(imageHeader.imageField.DateTime.year,cT1,10);
// 		strcat(szImgUID,cT1);
// 
// 		//link month
// 		itoa(imageHeader.imageField.DateTime.month,cT1,10);
// 		if (imageHeader.imageField.DateTime.month >= 10)
// 		{
// 		    strcat(szImgUID,cT1);
// 		}
// 		else
// 		{
// 			strcat(szImgUID,"0");
// 			strcat(szImgUID,cT1);
// 		}
// 
// 		//link day
// 		itoa(imageHeader.imageField.DateTime.day,cT1,10);
// 		if (imageHeader.imageField.DateTime.day >= 10)
// 		{
// 			strcat(szImgUID,cT1);
// 		}
// 		else
// 		{
// 			strcat(szImgUID,"0");
// 			strcat(szImgUID,cT1);
// 		}
// 
// 		//link hour
// 		itoa(imageHeader.imageField.DateTime.hour,cT1,10);
// 		if (imageHeader.imageField.DateTime.hour >= 10)
// 		{
// 			strcat(szImgUID,cT1);
// 		}
// 		else
// 		{
// 			strcat(szImgUID,"0");
// 			strcat(szImgUID,cT1);
// 		}
// 
// 		//link minute
// 		itoa(imageHeader.imageField.DateTime.minute,cT1,10);
// 		if (imageHeader.imageField.DateTime.minute >= 10)
// 		{
// 		    strcat(szImgUID,cT1);
// 		}
// 		else
// 		{
// 			strcat(szImgUID,"0");
// 			strcat(szImgUID,cT1);
// 		}
// 
// 		//link second
// 		itoa(imageHeader.imageField.DateTime.second,cT1,10);
// 		if (imageHeader.imageField.DateTime.second >= 0)
// 		{
// 			strcat(szImgUID,cT1);
// 		}
// 		else
// 		{
// 			strcat(szImgUID,"0");
// 		    strcat(szImgUID,cT1);
// 		}
// 	}
// 	else
// 	{
// 		//link year
// 		itoa(imageHeader.studyField.Time.year,cT1,10);
// 		strcat(szImgUID,cT1);
// 
// 		//link month
// 		itoa(imageHeader.studyField.Time.month,cT1,10);
// 		if (imageHeader.studyField.Time.month >= 10)
// 		{
// 		    strcat(szImgUID,cT1);
// 		}
// 		else
// 		{
// 			strcat(szImgUID,"0");
// 			strcat(szImgUID,cT1);
// 		}
// 
// 		//link day
// 		itoa(imageHeader.studyField.Time.day,cT1,10);
// 		if (imageHeader.studyField.Time.day >= 10)
// 		{
// 		    strcat(szImgUID,cT1);
// 		}
// 		else
// 		{
// 			strcat(szImgUID,"0");
// 			strcat(szImgUID,cT1);
// 		}
// 
// 		//link hour
// 		itoa(imageHeader.studyField.Time.hour,cT1,10);
// 		if (imageHeader.studyField.Time.hour >= 0)
// 		{
// 		    strcat(szImgUID,cT1);
// 		}
// 		else
// 		{
// 			strcat(szImgUID,"0");
// 			strcat(szImgUID,cT1);
// 		}
// 
// 		//link minute
// 		itoa(imageHeader.studyField.Time.minute,cT1,10);
// 		if (imageHeader.studyField.Time.minute >= 10)
// 		{
// 		    strcat(szImgUID,cT1);
// 		}
// 		else
// 		{
// 			strcat(szImgUID,"0");
// 			strcat(szImgUID,cT1);
// 		}
// 
// 		//link second
// 		itoa(imageHeader.studyField.Time.second,cT1,10);
// 		if (imageHeader.studyField.Time.second >= 0)
// 		{
// 		    strcat(szImgUID,cT1);
// 		}
// 		else
// 		{
// 			strcat(szImgUID,"0");
// 			strcat(szImgUID,cT1);
// 		}
// 	}
//     strcat(szImgUID,".");
// 	itoa(imageHeader.imageField.Id,cT1,10);
// 	strcat(szImgUID,cT1);
//	CString csStationNo = CConfigManager::GetHandle().GetStationNo();
//	strcat(szImgUID,".");
//	strcat(szImgUID,csStationNo.GetBuffer(10));
// }
// 
// void CreateSeriesUID(CBIImageHeader imageHeader, char szSeriesUID[])
// {
// 	char    cT1[32];
// 
// 	strcpy(szSeriesUID, gszOrgRoot);
// 	//Modality ID
// 	strcat(szSeriesUID,".");
// 	CString csStationNo = CConfigManager::GetHandle().GetSiteField().InstName;
// //	strcat(szSeriesUID,".");
// 	strcat(szSeriesUID,csStationNo.GetBuffer(10));
// 
// 	//Study ID
// 	strcat(szSeriesUID,".");
// 	strcat(szSeriesUID,imageHeader.studyField.Id);
// 
// 	//Series ID
// 	strcat(szSeriesUID,".");
// 	itoa(imageHeader.seriesField.Id,cT1,10);
// 	strcat(szSeriesUID,cT1);
//     strcat(szSeriesUID,".");
// 
// 	if (imageHeader.seriesField.DateTime.year > 2000)
// 	{
// 		//link year
// 		itoa(imageHeader.seriesField.DateTime.year,cT1,10);
// 		strcat(szSeriesUID,cT1);
// 
// 		//link month
// 		itoa(imageHeader.seriesField.DateTime.month,cT1,10);
// 		if (imageHeader.seriesField.DateTime.month >= 10)
// 		{
// 		    strcat(szSeriesUID,cT1);
// 		}
// 		else
// 		{
// 			strcat(szSeriesUID,"0");
// 			strcat(szSeriesUID,cT1);
// 		}
// 
// 		//link day
// 		itoa(imageHeader.seriesField.DateTime.day,cT1,10);
// 		if (imageHeader.seriesField.DateTime.day >= 10)
// 		{
// 			strcat(szSeriesUID,cT1);
// 		}
// 		else
// 		{
// 			strcat(szSeriesUID,"0");
// 			strcat(szSeriesUID,cT1);
// 		}
// 
// 		//link hour
// 		itoa(imageHeader.seriesField.DateTime.hour,cT1,10);
// 		if (imageHeader.seriesField.DateTime.hour >= 10)
// 		{
// 			strcat(szSeriesUID,cT1);
// 		}
// 		else
// 		{
// 			strcat(szSeriesUID,"0");
// 			strcat(szSeriesUID,cT1);
// 		}
// 
// 		//link minute
// 		itoa(imageHeader.seriesField.DateTime.minute,cT1,10);
// 		if (imageHeader.seriesField.DateTime.minute >= 10)
// 		{
// 		    strcat(szSeriesUID,cT1);
// 		}
// 		else
// 		{
// 			strcat(szSeriesUID,"0");
// 			strcat(szSeriesUID,cT1);
// 		}
// 
// 		//link second
// 		itoa(imageHeader.seriesField.DateTime.second,cT1,10);
// 		if (imageHeader.seriesField.DateTime.second >= 0)
// 		{
// 			strcat(szSeriesUID,cT1);
// 		}
// 		else
// 		{
// 			strcat(szSeriesUID,"0");
// 		    strcat(szSeriesUID,cT1);
// 		}
// 	}
// 	else
// 	{
// 		//link year
// 		itoa(imageHeader.studyField.Time.year,cT1,10);
// 		strcat(szSeriesUID,cT1);
// 
// 		//link month
// 		itoa(imageHeader.studyField.Time.month,cT1,10);
// 		if (imageHeader.studyField.Time.month >= 10)
// 		{
// 		    strcat(szSeriesUID,cT1);
// 		}
// 		else
// 		{
// 			strcat(szSeriesUID,"0");
// 			strcat(szSeriesUID,cT1);
// 		}
// 
// 		//link day
// 		itoa(imageHeader.studyField.Time.day,cT1,10);
// 		if (imageHeader.studyField.Time.day >= 10)
// 		{
// 		    strcat(szSeriesUID,cT1);
// 		}
// 		else
// 		{
// 			strcat(szSeriesUID,"0");
// 			strcat(szSeriesUID,cT1);
// 		}
// 
// 		//link hour
// 		itoa(imageHeader.studyField.Time.hour,cT1,10);
// 		if (imageHeader.studyField.Time.hour >= 0)
// 		{
// 		    strcat(szSeriesUID,cT1);
// 		}
// 		else
// 		{
// 			strcat(szSeriesUID,"0");
// 			strcat(szSeriesUID,cT1);
// 		}
// 
// 		//link minute
// 		itoa(imageHeader.studyField.Time.minute,cT1,10);
// 		if (imageHeader.studyField.Time.minute >= 10)
// 		{
// 		    strcat(szSeriesUID,cT1);
// 		}
// 		else
// 		{
// 			strcat(szSeriesUID,"0");
// 			strcat(szSeriesUID,cT1);
// 		}
// 
// 		//link second
// 		itoa(imageHeader.studyField.Time.second,cT1,10);
// 		if (imageHeader.studyField.Time.second >= 0)
// 		{
// 		    strcat(szSeriesUID,cT1);
// 		}
// 		else
// 		{
// 			strcat(szSeriesUID,"0");
// 			strcat(szSeriesUID,cT1);
// 		}
// 	}
// }
// 
// void CreateStudyUID(CBIImageHeader imageHeader, char szStudyUID[])
// {
// 	char    cT1[32];
// 
// 	strcpy(szStudyUID, gszOrgRoot);
// 	//Modality ID
// 	strcat(szStudyUID,".");
// 	CString csStationNo = CConfigManager::GetHandle().GetSiteField().InstName;
// 	strcat(szStudyUID,csStationNo.GetBuffer(10));
// 
// 	//Study ID
// //	strcat(szStudyUID,".");
// 	strcat(szStudyUID,imageHeader.studyField.Id);
//     strcat(szStudyUID,".");
// 
// 	//link year
// 	itoa(imageHeader.studyField.Time.year,cT1,10);
// 	strcat(szStudyUID,cT1);
// 
// 	//link month
// 	itoa(imageHeader.studyField.Time.month,cT1,10);
// 	if (imageHeader.studyField.Time.month >= 10)
// 	{
// 		strcat(szStudyUID,cT1);
// 	}
// 	else
// 	{
// 		strcat(szStudyUID,"0");
// 		strcat(szStudyUID,cT1);
// 	}
// 
// 	//link day
// 	itoa(imageHeader.studyField.Time.day,cT1,10);
// 	if (imageHeader.studyField.Time.day >= 10)
// 	{
// 		strcat(szStudyUID,cT1);
// 	}
// 	else
// 	{
// 		strcat(szStudyUID,"0");
// 		strcat(szStudyUID,cT1);
// 	}
// 
// 	//link hour
// 	itoa(imageHeader.studyField.Time.hour,cT1,10);
// 	if (imageHeader.studyField.Time.hour >= 0)
// 	{
// 		strcat(szStudyUID,cT1);
// 	}
// 	else
// 	{
// 		strcat(szStudyUID,"0");
// 		strcat(szStudyUID,cT1);
// 	}
// 
// 	//link minute
// 	itoa(imageHeader.studyField.Time.minute,cT1,10);
// 	if (imageHeader.studyField.Time.minute >= 10)
// 	{
// 		strcat(szStudyUID,cT1);
// 	}
// 	else
// 	{
// 		strcat(szStudyUID,"0");
// 		strcat(szStudyUID,cT1);
// 	}
// 
// 	//link second
// 	itoa(imageHeader.studyField.Time.second,cT1,10);
// 	if (imageHeader.studyField.Time.second >= 0)
// 	{
// 		strcat(szStudyUID,cT1);
// 	}
// 	else
// 	{
// 		strcat(szStudyUID,"0");
// 		strcat(szStudyUID,cT1);
// 	}
// }
// 
// void WriteString(char* pcDest, char* pcScr, int nCharNum)
// {
// 	memcpy((void*)pcDest,(void*)pcScr,nCharNum);
// }
// 
// bool WriteDataElementChar(char* &pcData, int nGroupnum,int nElementnum, char vr[],long nVlength,char value[])
// {
// 	*pcData = nGroupnum&0x00FF;
// 	pcData++;
// 	*pcData = (nGroupnum&0xFF00)>>8;
// 	pcData++;
// 	*pcData = nElementnum&0x00FF;
// 	pcData++;
// 	*pcData = (nElementnum&0xFF00)>>8;
// 	pcData++;
// 	*pcData = vr[0];
// 	pcData++;
// 	*pcData = vr[1];
// 	pcData++;
// 	if(vr=="OB"||vr=="OW"||vr=="SQ"||vr=="UN")
// 	{
// 		*pcData = 0x00;
// 		pcData++;
// 		*pcData = 0x00;
// 		pcData++;
// 		*pcData = nVlength&0x000000FF;
// 		pcData++;
// 		*pcData = (nVlength&0x0000FF00)>>8;
// 		pcData++;
// 		*pcData = (nVlength&0x00FF0000)>>16;
// 		pcData++;
// 		*pcData = (nVlength&0xFF000000)>>24;
// 		pcData++;
// 	}
// 	else
// 	{
// 		*pcData = nVlength&0x00FF;
// 		pcData++;
// 		*pcData = (nVlength&0xFF00)>>8;
// 		pcData++;
// 	}
// 	
// 	int i=0;
// 
// 	if(vr=="OB")
// 	{
// 		for( ; i<nVlength; i++)
// 		{
// 			*pcData = value[i];
// 			pcData++;
// 		}
// 	}
// 	else
// 	{
// 		while(value[i]!='\0')
// 		{
// 				*pcData = value[i];
// 				pcData++;
// 				i++;
// 		}
// 
// 	}
// 
// 	for( ; i<nVlength; i++)//padding with space
// 	{
// 		if(vr=="UI")
// 		{
// 			*pcData = 0x00;
// 		}
// 		else
// 		{
// 			*pcData = 0x20;
// 		}
// 		pcData++;
// 		
// 	}
// 	return true;
// }
// 
// template<class T>
// bool WriteDataElementChar(char* &pcData, int nGroupNum,int nElementNum, char vr[],long nVlength,T value[])
// {
// 	int nPaddingflag = 0;
// 
// 	if(sizeof(T)*nVlength%2 == 1)
// 	{
// 		nPaddingflag = 1;
// 	}
// 	*pcData = nGroupNum&0x00FF;
// 	pcData++;
// 	*pcData = (nGroupNum&0xFF00)>>8;
// 	pcData++;
// 	*pcData = nElementNum&0x00FF;
// 	pcData++;
// 	*pcData = (nElementNum&0xFF00)>>8;
// 	pcData++;
// 	*pcData = vr[0];
// 	pcData++;
// 	*pcData = vr[1];
// 	pcData++;
// 	if(vr=="OB"||vr=="OW"||vr=="SQ"||vr=="UN")
// 	{
// 		*pcData = 0x00;
// 		pcData++;
// 		*pcData = 0x00;
// 		pcData++;
// 		*pcData = nVlength*sizeof(T) + nPaddingflag&0x000000FF;
// 		pcData++;
// 		*pcData = (nVlength*sizeof(T) + nPaddingflag&0x0000FF00)>>8;
// 		pcData++;
// 		*pcData = (nVlength*sizeof(T) + nPaddingflag&0x00FF0000)>>16;
// 		pcData++;
// 		*pcData = (nVlength*sizeof(T) + nPaddingflag&0xFF000000)>>24;
// 		pcData++;
// 	}
// 	else
// 	{
// 		*pcData=(nVlength*sizeof(T) + nPaddingflag)&0x00FF;
// 		pcData++;
// 		*pcData=((nVlength*sizeof(T) + nPaddingflag)&0xFF00)>>8;
// 		pcData++;
// 	}
// 	
// 	int i=0;
// 	if(vr=="OW"||vr=="OB"||vr=="UN")
// 	{
// 		for(i=0; i<nVlength; i++)
// 		{
// 			*((T*)pcData) = value[i];
// 			pcData += sizeof(T);
// 		}
// 	}
// 	else
// 	{
// 	}
// 
// 	if(nPaddingflag)
// 	{
// 		*pcData = 0x00;
// 		pcData++;
// 	}
// 	return true;
// }
// 
// int StringRealSize(char string[])
// {
// 	int i = 0;
// 	while(1)
// 	{
// 		if(string[i] == 0)
// 			break;
// 		else
// 			i++;
// 	}
// 	return i;
// }

// template<class T>
// bool WriteDataElementNum(char* &pcData, int nGroupNum,int nElementnum, char vr[], long nVlength,T value)
// {
// 	*pcData = nGroupNum&0x00FF;
// 	pcData++;
// 	*pcData = (nGroupNum&0xFF00)>>8;
// 	pcData++;
// 	*pcData = nElementnum&0x00FF;
// 	pcData++;
// 	*pcData = (nElementnum&0xFF00)>>8;
// 	pcData++;
// 	*pcData = vr[0];
// 	pcData++;
// 	*pcData = vr[1];
// 	pcData++;
// 	if(vr=="OB"||vr=="OW"||vr=="SQ"||vr=="OR"||vr=="UN")
// 	{
// 		*pcData = 0x00;
// 		pcData++;
// 		*pcData = 0x00;
// 		pcData++;
// 		*pcData = nVlength&0x000000FF;
// 		pcData++;
// 		*pcData = (nVlength&0x0000FF00)>>8;
// 		pcData++;
// 		*pcData = (nVlength&0x00FF0000)>>16;
// 		pcData++;
// 		*pcData = (nVlength&0xFF000000)>>24;
// 		pcData++;
// 	}
// 	else
// 	{
// 		*pcData = nVlength&0x00FF;
// 		pcData++;
// 		*pcData = (nVlength&0xFF00)>>8;
// 		pcData++;
// 	}
// 	*((T *)pcData) = value;
// 	pcData += sizeof(T);
// 
// 	return true;
// }
// 
// template<class T>
// bool WriteImageData(char* &pcData, char vr[], long nVlength,T imagedata[])
// {
// 	int nPaddingflag = 0;
// 
// 	if (sizeof(T)*nVlength%2 == 1)
// 	{
// 		nPaddingflag = 1;
// 	}
// 	*pcData = (char)0xE0;
// 	pcData++;
// 	*pcData = (char)0x7F;
// 	pcData++;
// 	*pcData = (char)0x10;
// 	pcData++;
// 	*pcData = 0x00;
// 	pcData++;
// 	*pcData = vr[0];
// 	pcData++;
// 	*pcData = vr[1];
// 	pcData++;
// 	*pcData = 0x00;
// 	pcData++;
// 	*pcData = 0x00;
// 	pcData++;
// 	*pcData = nVlength*sizeof(T) + nPaddingflag&0x000000FF;
// 	pcData++;
// 	*pcData = (nVlength*sizeof(T) + nPaddingflag&0x0000FF00)>>8;
// 	pcData++;
// 	*pcData = (nVlength*sizeof(T) + nPaddingflag&0x00FF0000)>>16;
// 	pcData++;
// 	*pcData = (nVlength*sizeof(T) + nPaddingflag&0xFF000000)>>24;
// 	pcData++;
// 	
// 	for(int i=0; i<nVlength; i++)
// 	{
// 		*((T*)pcData) = imagedata[i];
// 		pcData+=sizeof(T);
// 	}
// 	return true;
// }
// 
// void TimeConvert(BIDateTime datetime,std::string& strDate, std::string& strTime)
// {
// 	char year[5],mon[3],day[3],hour[3],min[3],sec[3];
// 
// 	_ultoa((int)datetime.year,year,10);
// 	_ultoa((int)datetime.month,mon,10);
// 	if(datetime.month<10)
// 	{
// 		mon[1] = mon[0];
// 		mon[0] = '0';
// 		mon[2] = 0;
// 	}
// 	_ultoa((int)datetime.day,day,10);
// 	if(datetime.day<10)
// 	{
// 		day[1] = day[0];
// 		day[0] = '0';
// 		day[2] = 0;
// 	}
// 	_ultoa((int)datetime.hour,hour,10);
// 	if(datetime.hour<10)
// 	{
// 		hour[1] = hour[0];
// 		hour[0] = '0';
// 		hour[2] = 0;
// 	}
// 	_ultoa((int)datetime.minute,min,10);
// 	if(datetime.minute<10)
// 	{
// 		min[1] = min[0];
// 		min[0] = '0';
// 		min[2] = 0;
// 	}
// 	_ultoa((int)datetime.second,sec,10);
// 	if(datetime.second<10)
// 	{
// 		sec[1] = sec[0];
// 		sec[0] = '0';
// 		sec[2] = 0;
// 	}
// 	strDate = year ;
// 	strDate += mon;
//     strDate += day;
// 	strTime = hour;
// 	strTime += min;
// 	strTime += sec;
// }
// 
// void NameConvert(char BIname[], char DIname[])
// {
// 	int i=0;
// 	while(BIname[i]!=0x20&&BIname[i]!=0x00)
// 	{
// 		DIname[i]=BIname[i];
// 		i++;
// 	}
// 	if(BIname[i]!=0x00)
// 	{
// 		DIname[i]='^';
// 		i++;
// 	}
// 	while(BIname[i]!=0x00)
// 	{
// 		DIname[i]=BIname[i];
// 		i++;
// 	}
// 	DIname[i]=0;
// }
// 
// void AgeConvert(char DIage[], unsigned char BIage)
// {
// 	char age[3];
// 	_ultoa(BIage,age,10);
// 	if(BIage<10)
// 	{
// 		DIage[0]='0';
// 		DIage[1]='0';
// 		DIage[2]=age[0];
// 	}
// 	else if(BIage<100)
// 	{
// 		DIage[0]='0';
// 		DIage[1]=age[0];
// 		DIage[2]=age[1];
// 	}
// 	else
// 	{
// 		DIage[0]=age[0];
// 		DIage[1]=age[1];
// 		DIage[2]=age[2];
// 	}
// }
// bool ConvertXB2Dicom(CBIImageHeader imageHeader,double nAngle,BOOL nVerFlip,BOOL nHorFlip,
// 					 short* psImageData,
// 					 char* pcDicomData,
// 					 int& nDicomDataLen)
// {
// /*
// 	if ( imageHeader.imageField.Id != 0 )
// 	{
// 		return false;
// 	}
// */
// 
// 	// 计算DICOM所需的方位参数
// 	float fTopLeftX, fTopLeftY, fTopLeftZ;
// 	float fRowCosineWithZ, fRowCosineWithX, fRowCosineWithY;
// 	float fColCosineWithZ, fColCosineWithX, fColCosineWithY;
// 
// 	CString sDesc = imageHeader.seriesField.Desc;
// 	
// 	if ( sDesc.Find( "MIP", 0 ) == -1 )
// 	{
// 		//RFInhomoCorrection( pTask->m_pScan );
// 		//GradientCorrection( pTask->m_pScan );
// // 		CDirectionCalculator::GetHandle().GetActiveDirForDicom( imageHeader, nAngle,nVerFlip,nHorFlip,
// // 		fTopLeftX, fTopLeftY, fTopLeftZ,
// // 		fRowCosineWithZ, fRowCosineWithX, fRowCosineWithY,
// // 		fColCosineWithZ, fColCosineWithX, fColCosineWithY );
// 	}
// 	else
// 	{
// 		//Modified by Tom, --2008.07.10
// 		float fReadModule=(float)sqrt(pow(imageHeader.imageField.fFreqDirZ,2)+
// 									  pow(imageHeader.imageField.fFreqDirX,2)+
// 									  pow(imageHeader.imageField.fFreqDirY,2));
// 		float fPhaseModule=(float)sqrt(pow(imageHeader.imageField.fPhaseDirZ,2)+
// 									   pow(imageHeader.imageField.fPhaseDirX,2)+
// 									   pow(imageHeader.imageField.fPhaseDirY,2));
// 
// // 		CDirectionCalculator::GetHandle().GetMIPActiveDirForDicom( imageHeader,
// // 		fTopLeftX, fTopLeftY, fTopLeftZ,
// // 		fRowCosineWithZ, fRowCosineWithX, fRowCosineWithY,
// // 		fColCosineWithZ, fColCosineWithX, fColCosineWithY );
// 		
// 
// 
// 	}
// 
// 
// 	// 产生DICOM文件内容
// 	char *pcCurrent  = pcDicomData ;
// 	char szName[32]  = " ";
// 	char szTemp[64]  = "0";
// 	char szTerm[10][20];
// 	char szAge[5]    = "000Y";
// 	char szSex[2]    = "M"  ;
// 	char szImgUID[64];
// 	char szSeriesUID[64];
// 	char szStudyUID[64];
// 	int  nStrLen    ;
// 	int  i;
// 
// 	//Start Convert
// 	//File Preamble
// 	memset((void*)pcDicomData,0x00,128) ;
// 	pcCurrent += 128 ;
// 	//DICOM Prefix
// 	WriteString(pcCurrent,"DICM",0x04);
// 	pcCurrent += 4 ;
// 
// 	//Write Group {0x00}
// 	//Group Length Mark
// 	char *pcMark = pcCurrent;
// 	pcCurrent += 12;
// 	//Meta Info Version
// 	char metav[2]={0x00,0x01};
// 	if(!WriteDataElementChar(pcCurrent,0x0002,0x0001,"OB",0x02,metav))
// 	{
// 		return false;
// 	}
// 	//Media Storage SOP Class UID	
// 	if(!WriteDataElementChar(pcCurrent,0x0002,0x0002,"UI",0x001A,"1.2.840.10008.5.1.4.1.1.4"))
// 	{
// 		return false;
// 	}
// 	//Media Storage SOP Instance UID
// 	CreateImgUID(imageHeader, szImgUID);
// 	nStrLen = StringRealSize(szImgUID)%2 + StringRealSize(szImgUID);
// //	strcat(szTemp,".1.1");
// //	nStrLen = StringRealSize(szTemp)%2 + StringRealSize(szTemp);
// 	if(!WriteDataElementChar(pcCurrent,0x0002,0x0003,"UI",nStrLen,szImgUID))
// 	{
// 		return false;
// 	}
// 	//Transfer Syntax UID
// 	if(!WriteDataElementChar(pcCurrent,0x0002,0x0010,"UI",0x0014,"1.2.840.10008.1.2.1"))
// 	{
// 		return false;
// 	}
// 	//Implementation Class UID
// //	CreateImgUID(imageHeader, szImgUID);
// 	strcpy(szTemp,gszOrgRoot);
// 	strcat(szTemp,".2.1.1");
// 	nStrLen = StringRealSize(szTemp)%2 + StringRealSize(szTemp);
// 	if(!WriteDataElementChar(pcCurrent,0x0002,0x0012,"UI",nStrLen,szTemp))
// 	{
// 		return false;
// 	}
// 	//Implementation Version Name
// 	//Source Application Entity Title
// 	nStrLen = StringRealSize(imageHeader.headInfo.BITitle)%2 + StringRealSize(imageHeader.headInfo.BITitle);
// 	if(!WriteDataElementChar(pcCurrent,0x0002,0x0016,"AE",nStrLen,imageHeader.headInfo.BITitle))
// 	{
// 		return false;
// 	}
// 	//Private Information Creator UID
// 	//Private Information
// 	///////////////////////////////////////////////////////////////////////////////////////////////
// 	//增加一个字段，保留13三个变量，每个变量占16字节空格部分填充字符0，即0x30
// 	//1.imageHeader.imageField.nPlaneType
// 	//2~13.imageHeader.imageField.fCenterPointX, imageHeader.imageField.fCenterPointY, imageHeader.imageField.fCenterPointZ,
// 	//	imageHeader.imageField.fFreqDirX, imageHeader.imageField.fFreqDirY,imageHeader.imageField.fFreqDirZ,
// 	//	imageHeader.imageField.fPhaseDirX,imageHeader.imageField.fPhaseDirY,imageHeader.imageField.fPhaseDirZ,
// 	//	imageHeader.imageField.fSliceDirX,imageHeader.imageField.fSliceDirY,imageHeader.imageField.fSliceDirZ
// 	CString szBWUsingParam;
// 	szBWUsingParam.Format("%016d%016f%016f%016f%016f%016f%016f%016f%016f%016f%016f%016f%016f",imageHeader.imageField.nPlaneType,
// 		imageHeader.imageField.fCenterPointX, imageHeader.imageField.fCenterPointY, imageHeader.imageField.fCenterPointZ,
// 		imageHeader.imageField.fFreqDirX, imageHeader.imageField.fFreqDirY,imageHeader.imageField.fFreqDirZ,
// 		imageHeader.imageField.fPhaseDirX,imageHeader.imageField.fPhaseDirY,imageHeader.imageField.fPhaseDirZ,
// 		imageHeader.imageField.fSliceDirX,imageHeader.imageField.fSliceDirY,imageHeader.imageField.fSliceDirZ);
// 	char*pBWUsingParam=(char*)szBWUsingParam.operator LPCTSTR();
// 	if(!WriteDataElementChar(pcCurrent,0x0002,0x07ff,"DS",/*"\0"*/szBWUsingParam.GetLength(),pBWUsingParam))
// 	{
// 		return false;
// 	}
// 	//Write Group Length
// 	if(!WriteDataElementNum(pcMark,0x0002,0x0000,"UL",0x04,pcCurrent-pcMark-12))
// 	{
// 		return false;
// 	}
// 
// //////////////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////		Standard Attributes		//////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////////
// 
// 	///////////////////////////////////////////////////////////////////////////////
// 	//????(0008,xxxx)
// 
// 	//Group Length Mark
// 	pcMark = pcCurrent;
// 	pcCurrent += 12;
// 	//*Image_Type			(0008,0008) Image Type CS 1-n		//?????,???????
// 	switch(imageHeader.imageField.Type)
// 	{
// 		
// 		case itMPR:
// 			strcpy(szTemp,"ORIGINAL\\PRIMARY\\MPR");
// 			break;
// 		case itProjection:
// 			strcpy(szTemp,"ORIGINAL\\PRIMARY\\PROJECTION IMAGE ");
// 			break;
// 		case itImage:
// 			strcpy(szTemp,"ORIGINAL\\PRIMARY\\IMAGE");
// 			break;		//NO
// 		case itT1Map:
// 			strcpy(szTemp,"ORIGINAL\\PRIMARY\\T1 MAP");
// 			break;
// 		case itT2Map:
// 			strcpy(szTemp,"ORIGINAL\\PRIMARY\\T2 MAP");
// 			break;
// 		case itDiffusionMap:
// 			strcpy(szTemp,"ORIGINAL\\PRIMARY\\DIFFUSION MAP");
// 			break;
// 		case itDensityMap:
// 			strcpy(szTemp,"ORIGINAL\\PRIMARY\\DENSITY MAP");
// 			break;
// 		case itPhaseMap:
// 			strcpy(szTemp,"ORIGINAL\\PRIMARY\\PHASE MAP");
// 			break;
// 		case itVelocityMap:
// 			strcpy(szTemp,"ORIGINAL\\PRIMARY\\VELOCITY MAP");
// 			break;
// 		case itImageAddition:
// 			strcpy(szTemp,"ORIGINAL\\PRIMARY\\IMAGE ADDITION");
// 			break;
// 		case itPhaseSubtract:
// 			strcpy(szTemp,"ORIGINAL\\PRIMARY\\PHASE SUBTRACT");
// 			break;
// 		case itModulusSubtract:
// 			strcpy(szTemp,"ORIGINAL\\PRIMARY\\MODULUS SUBTRACT");
// 			break;
// 		case itOther:
// 			strcpy(szTemp,"ORIGINAL\\PRIMARY\\OTHER");
// 			break;
// 	}
// 
// 	nStrLen = StringRealSize(szTemp)%2 + StringRealSize(szTemp);
// 	if(!WriteDataElementChar(pcCurrent,0x0008,0x0008,"CS",nStrLen,szTemp))
// 	{
// 		return false;
// 	}
// 	//SOP Class UID (0008,0016)
// 	if(!WriteDataElementChar(pcCurrent,0x0008,0x0016,"UI",0x001A,"1.2.840.10008.5.1.4.1.1.4"))
// 	{
// 		return 0;
// 	}
// 	
// 	//SOP Instance UID (0008,0018)
//     CreateImgUID(imageHeader, szImgUID);
// 	nStrLen = StringRealSize(szImgUID)%2 + StringRealSize(szImgUID);
// 	if(!WriteDataElementChar(pcCurrent,0x0008,0x0018,"UI",nStrLen,szImgUID))
// 	{
// 		return 0;
// 	}
// 
// 	//*Study_Time			(0008,0020) Study Date DA 1	
// 	//*						(0008,0030) Study Time TM 1
// 
//     std::string strDate,strTime; 
// 	TimeConvert(imageHeader.studyField.Time,strDate,strTime);
// 	if(!WriteDataElementChar(pcCurrent,0x0008,0x0020,"DA",8,const_cast<char*>(strDate.c_str()))) //pcDateTime))
// 	{
// 		return 0;
// 	}
// 	if(!WriteDataElementChar(pcCurrent,0x0008,0x0030,"TM",6,const_cast<char*>(strTime.c_str())))
// 	{
// 		return 0;
// 	}
// 	//*						(0008,0050) Accession Number SH 1	//RIS
// 	if(!WriteDataElementChar(pcCurrent,0x0008,0x0050,"SH",0,"\0"))
// 	{
// 		return 0;
// 	}
// 	//*						(0008,0060) Modality CS 1
// 	if(!WriteDataElementChar(pcCurrent,0x0008,0x0060,"CS",2,"MR"))
// 	{
// 		return 0;
// 	}
// 	//*						(0008,0070)	Manufacturer LO 1			//????
// 	if(!WriteDataElementChar(pcCurrent,0x0008,0x0070,"LO",6,"BIMRI"))
// 	{
// 		return 0;
// 	}
// 	//*Site_InstName		(0008,0080) Institution Name LO 1
// 	nStrLen = StringRealSize(imageHeader.siteField.InstName)%2 
// 		    + StringRealSize(imageHeader.siteField.InstName);
// 	if(!WriteDataElementChar(pcCurrent,0x0008,0x0080,"LO",nStrLen,imageHeader.siteField.InstName))
// 	{
// 		return false;
// 	}
// 	//*Study_RefPhy			(0008,0090) Referring Physician'sName PN 1
// 	NameConvert(imageHeader.studyField.RefPhy, szName);
// 	nStrLen = StringRealSize(szName)%2 + StringRealSize(szName);
// 	if(!WriteDataElementChar(pcCurrent,0x0008,0x0090,"PN",nStrLen,szName))
// 	{
// 		return false;
// 	}
// 	//*Site_StationName		(0008,1010) Station Name SH 1
// 	nStrLen = StringRealSize(imageHeader.siteField.StationName)%2
// 		    + StringRealSize(imageHeader.siteField.StationName);
// 	if(!WriteDataElementChar(pcCurrent,0x0008,0x1010,"SH",nStrLen,imageHeader.siteField.StationName))
// 	{
// 		return false;
// 	}
// 	//*Study_Desc			(0008,1030) Study Description LO 1			//DICOM?????
// 	nStrLen =StringRealSize(imageHeader.studyField.Desc)%2+StringRealSize(imageHeader.studyField.Desc);
// 	if(nStrLen > 64)
// 	{
// 		nStrLen = 64;
// 	}
// 	if(!WriteDataElementChar(pcCurrent,0x0008,0x1030,"LO",nStrLen,imageHeader.studyField.Desc))
// 	{
// 		return false;
// 	}
// 	//*Series_Desc			(0008,103E) Series Description LO 1
// 	nStrLen = StringRealSize(imageHeader.seriesField.Desc)%2
// 		    + StringRealSize(imageHeader.seriesField.Desc);
// 	if(!WriteDataElementChar(pcCurrent,0x0008,0x103E,"LO",nStrLen,imageHeader.seriesField.Desc))
// 	{
// 		return false;
// 	}
// 	//*Site_InstDeptName		(0008,1040) Institutional Department Name LO 1
// 	nStrLen = StringRealSize(imageHeader.siteField.InstDeptName)%2
// 		    + StringRealSize(imageHeader.siteField.InstDeptName);
// 	if(!WriteDataElementChar(pcCurrent,0x0008,0x1040,"LO",nStrLen,imageHeader.siteField.InstDeptName))
// 	{
// 		return false;
// 	}
// 	//*Study_Radiologist		(0008,1050) Performing Physician's Name PN 1-n
// 	NameConvert(imageHeader.studyField.Radiologist,szName);
// 	nStrLen = StringRealSize(szName)%2 + StringRealSize(szName);
// 	if(!WriteDataElementChar(pcCurrent,0x0008,0x1050,"PN",nStrLen,szName))
// 	{
// 		return false;
// 	}
// 	//Write Group Length
// 	if(!WriteDataElementNum(pcMark,0x0008,0x0000,"UL",0x04,pcCurrent-pcMark-12))
// 	{
// 		return false;
// 	}
// 
// 	///////////////////////////////////////////////////////////////////////////////
// 	//(0009,xxxx)
// 
// 	//Group Length Mark
// 	pcMark = pcCurrent;
// 	pcCurrent += 12;
// 	//							(0009,0010) Private Creator ID LO 1
// 	if(!WriteDataElementChar(pcCurrent,0x0009,0x0010,"LO",14,"BIMRI_PATI_01"))
// 	{
// 		return false;
// 	}
// 	//Site_Id(machine id)		*(0009,1001) Machine ID LO 1
// 	nStrLen = StringRealSize(imageHeader.siteField.Id)%2 + StringRealSize(imageHeader.siteField.Id);
// 	if(!WriteDataElementChar(pcCurrent,0x0009,0x1001,"LO",nStrLen,imageHeader.siteField.Id))
// 	{
// 		return false;
// 	}
// 	//Study_OperatorID			*(0009,1002) OperatorsID CS 1
// 	nStrLen = StringRealSize(imageHeader.studyField.OperatorID)%2 
// 		    + StringRealSize(imageHeader.studyField.OperatorID);
// 	if(!WriteDataElementChar(pcCurrent,0x0009,0x1002,"CS",nStrLen,imageHeader.studyField.OperatorID))
// 	{
// 		return false;
// 	}
// 	//Series_DataType			*(0009,1004) Data Type US 1
// 	if(!WriteDataElementNum(pcCurrent,0x0009,0x1004,"US",0x02,(short)imageHeader.seriesField.DataType))
// 	{
// 		return false;
// 	}
// 	//Series_ReadPoints			*(0009,1005) Read Points US 1
// 	if(!WriteDataElementNum(pcCurrent,0x0009,0x1005,"US",0x02,imageHeader.seriesField.ReadPoints))
// 	{
// 		return false;
// 	}
// 	//*Study_Desc			*(0009,1006) Study Description LT 1			//DICOM?????
// 	nStrLen = StringRealSize(imageHeader.studyField.Desc)%2 
// 		    + StringRealSize(imageHeader.studyField.Desc);
// 	if(!WriteDataElementChar(pcCurrent,0x0009,0x1006,"LT",nStrLen,imageHeader.studyField.Desc))
// 	{
// 		return false;
// 	}
// 
// 	//Header File Version		*(0009,100F)	SL	1
// 	if(!WriteDataElementNum(pcCurrent,0x0009,0x100F,"SL",0x04,imageHeader.headInfo.Version))
// 	{
// 		return false;
// 	}
// 	//Header File Size			*(0009,1010)	US	1
// 	if(!WriteDataElementNum(pcCurrent,0x0009,0x1010,"US",0x02,imageHeader.headInfo.Size))
// 	{
// 		return false;
// 	}
// 	//SiteField Version			*(0009,1011)	SL	1
// 	if(!WriteDataElementNum(pcCurrent,0x0009,0x1011,"SL",0x04,imageHeader.siteField.Version))
// 	{
// 		return false;
// 	}
// 	//SiteField Size			*(0009,1012)	US	1
// 	if(!WriteDataElementNum(pcCurrent,0x0009,0x1012,"US",0x02,imageHeader.siteField.Size))
// 	{
// 		return false;
// 	}
// 	//PatientField Version		*(0009,1013)	SL	1
// 	if(!WriteDataElementNum(pcCurrent,0x0009,0x1013,"SL",0x04,imageHeader.patientField.Version))
// 	{
// 		return false;
// 	}
// 	//PatientField Size			*(0009,1014)	US	1
// 	if(!WriteDataElementNum(pcCurrent,0x0009,0x1014,"US",0x02,imageHeader.patientField.Size))
// 	{
// 		return false;
// 	}
// 	//StudyField Version		*(0009,1015)	SL	1
// 	if(!WriteDataElementNum(pcCurrent,0x0009,0x1015,"SL",0x04,imageHeader.studyField.Version))
// 	{
// 		return false;
// 	}
// 	//StudyField Size			*(0009,1016)	US	1
// 	if(!WriteDataElementNum(pcCurrent,0x0009,0x1016,"US",0x02,imageHeader.studyField.Size))
// 	{
// 		return false;
// 	}
// 	//SeriesField Version		*(0009,1017)	SL	1
// 	if(!WriteDataElementNum(pcCurrent,0x0009,0x1017,"SL",0x04,imageHeader.seriesField.Version))
// 	{	
// 		return false;
// 	}
// 	//SeriesField Size			*(0009,1018)	US	1
// 	if(!WriteDataElementNum(pcCurrent,0x0009,0x1018,"US",0x02,imageHeader.seriesField.Size))
// 	{
// 		return false;
// 	}
// 	//ScanField Version			*(0009,1019)	SL	1
// 	if(!WriteDataElementNum(pcCurrent,0x0009,0x1019,"SL",0x04,imageHeader.scanField.Version))
// 	{
// 		return false;
// 	}
// 	//ScanField Size			*(0009,101A)	US	1
// 	if(!WriteDataElementNum(pcCurrent,0x0009,0x101A,"US",0x02,imageHeader.scanField.Size))
// 	{
// 		return false;
// 	}
// 	//ImageField Version		*(0009,101B)	SL	1
// 	if(!WriteDataElementNum(pcCurrent,0x0009,0x101B,"SL",0x04,imageHeader.imageField.Version))
// 	{
// 		return false;
// 	}
// 	//ImageField Size			*(0009,101C)	US	1
// 	if(!WriteDataElementNum(pcCurrent,0x0009,0x101C,"US",0x02,imageHeader.imageField.Size))
// 	{
// 		return false;
// 	}
// 	//NumHdrFields				*(0009,1020)	US	1
// 	if(!WriteDataElementNum(pcCurrent,0x0009,0x1020,"US",0x02,(short)imageHeader.headInfo.NumHdrFields))
// 	{
// 		return false;
// 	}
// 	//HeaderSize				*(0009,1021)	US	1
// 	if(!WriteDataElementNum(pcCurrent,0x0009,0x1021,"US",0x02,imageHeader.headInfo.HeaderSize))
// 	{
// 		return false;
// 	}
// 	//DataMatrixSize			*(0009,1022)	UL	1
// //	if(!WriteDataElementNum(pcCurrent,0x0009,0x1022,"UL",0x04,imageHeader.headInfo.DataMatrixSize);
// 	
// 	//Series_RefSeries1			*(0009,1030)	US	1
// 	if(!WriteDataElementNum(pcCurrent,0x0009,0x1030,"US",0x02,(short)imageHeader.seriesField.RefSeries1))
// 	{
// 		return false;
// 	}
// 	//Series_RefSeries2			*(0009,1031)	US	1
// 	if(!WriteDataElementNum(pcCurrent,0x0009,0x1031,"US",0x02,(short)imageHeader.seriesField.RefSeries2))
// 	{
// 		return false;
// 	}
// 	//Series_RefImage1			*(0009,1032)	US	1
// 	if(!WriteDataElementNum(pcCurrent,0x0009,0x1032,"US",0x02,(short)imageHeader.seriesField.RefImage1))
// 	{
// 		return false;
// 	}
// 	//Series_RefImage2			*(0009,1033)	US	1
// 	if(!WriteDataElementNum(pcCurrent,0x0009,0x1033,"US",0x02,(short)imageHeader.seriesField.RefImage2))
// 	{
// 		return false;
// 	}
// 
// 	//Write Group Length
// 	if(!WriteDataElementNum(pcMark,0x0009,0x0000,"UL",0x04,pcCurrent-pcMark-12))
// 	{
// 		return false;
// 	}
// 
// 
// 	///////////////////////////////////////////////////////////////////////////////
// 	//????(0010,xxxx)
// 	
// 	//Group Length Mark
// 	pcMark = pcCurrent;
// 	pcCurrent += 12;
// 	//*Patient_Name			(0010,0010) Patient's Name PN 1
// 	NameConvert(imageHeader.patientField.Name, szName);
// 	nStrLen=StringRealSize(szName)%2 + StringRealSize(szName);
// 	if(!WriteDataElementChar(pcCurrent,0x0010,0x0010,"PN",nStrLen,szName))
// 	{
// 		return false;
// 	}
// 	//*Patient_Id			(0010,0020) Patient ID LO 1
// 	nStrLen = StringRealSize(imageHeader.patientField.Id)%2 
// 		    + StringRealSize(imageHeader.patientField.Id);
// 	if(!WriteDataElementChar(pcCurrent,0x0010,0x0020,"LO",nStrLen,imageHeader.patientField.Id))
// 	{
// 		return false;
// 	}
// 	//*Patient_BirthDate	(0010,0030) Patient's Birth Date DA 1	
// 	//						(0010,0032) Patient's Birth Time TM 1
// 	/*
// 		日期：2007-09-15
// 		作者：陈实
// 		目的：DICOM传输时0x0010,0x0032标志内容不合法
// 	*/
// 	imageHeader.patientField.BirthDate.hour=0;
// 	imageHeader.patientField.BirthDate.minute=0;
// 	imageHeader.patientField.BirthDate.second=0;
// 	TimeConvert(imageHeader.patientField.BirthDate,strDate,strTime);
// 	if(!WriteDataElementChar(pcCurrent,0x0010,0x0030,"DA",8,const_cast<char*>(strDate.c_str())))
// 	{
// 		return false;
// 	}
// 	if(!WriteDataElementChar(pcCurrent,0x0010,0x0032,"TM",6,const_cast<char*>(strTime.c_str())))
// 	{
// 		return false;
// 	}
// 	//*Patient_Sex			(0010,0040) Patient's Sex CS 1
// 	if(imageHeader.patientField.Sex=='U')
// 	{
// 		imageHeader.patientField.Sex = 'O';
// 	}
// 	szSex[0] = imageHeader.patientField.Sex;
// 	if(!WriteDataElementChar(pcCurrent,0x0010,0x0040,"CS",2,szSex))
// 	{
// 		return false;
// 	}
// 	//*Patient_Age			(0010,1010) Patient's Age AS 1
// 	AgeConvert(szAge, imageHeader.patientField.Age);
// 	if(!WriteDataElementChar(pcCurrent,0x0010,0x1010,"AS",4,szAge))
// 	{
// 		return false;
// 	}
// 	//*Patient_Weight		(0010,1030) Patient's Weight DS 1
// 	_ultoa(imageHeader.patientField.Weight,szTemp,10);
// 	nStrLen = StringRealSize(szTemp)%2 + StringRealSize(szTemp);
// 	if(!WriteDataElementChar(pcCurrent,0x0010,0x1030,"DS",nStrLen,szTemp))
// 	{
// 		return false;
// 	}
// 	//*Patient_Desc			(0010,21B0) Additional Patient History LT 1
// 	nStrLen = StringRealSize(imageHeader.patientField.Desc)%2 
// 		    + StringRealSize(imageHeader.patientField.Desc);
// 	if(!WriteDataElementChar(pcCurrent,0x0010,0x21B0,"LT",nStrLen,imageHeader.patientField.Desc))
// 	{
// 		return false;
// 	}
// 	//Write Group Length
// 	if(!WriteDataElementNum(pcMark,0x0010,0x0000,"UL",0x04,pcCurrent-pcMark-12))
// 	{
// 		return false;
// 	}
// 
// 	///////////////////////////////////////////////////////////////////////////////
// 	//????(0018,xxxx)
// 
// 	//Group Length Mark
// 	pcMark = pcCurrent;
// 	pcCurrent += 12;
// 	//*PatBodyPart		(0018,0015) Body Part Examined CS 1
// 	switch(imageHeader.studyField.PatBodyPart)
// 	{
// 		case bpHead:
// 			strcpy(szTemp,"SKULL");
// 			break;
// 		case bpNeck:
// 			strcpy(szTemp,"NECK");
// 			break;		//No
// 		case bpShoulder:
// 			strcpy(szTemp,"SHOULDER");
// 			break;
// 		case bpCervicalSpine:
// 			strcpy(szTemp,"CSPINE");
// 			break;
// 		case bpThoracicSpine:
// 			strcpy(szTemp,"TSPINE");
// 			break;
// 		case bpLumberSpine:
// 			strcpy(szTemp,"LSPINE");
// 			break;
// 		case bpChest:
// 			strcpy(szTemp,"CHEST");
// 			break;
// 		case bpBreast:
// 			strcpy(szTemp,"BREAST");
// 			break;
// 		case bpAbdomen:
// 			strcpy(szTemp,"ABODOMEN");
// 			break;
// 		case bpPelvis:
// 			strcpy(szTemp,"PELVIS");
// 			break;
// 		case bpHip:
// 			strcpy(szTemp,"HIP");
// 			break;
// 		case bpElbow:
// 			strcpy(szTemp,"ELBOW");
// 			break;
// 		case bpWrist:
// 			strcpy(szTemp,"WRIST");
// 			break;		//No
// 		case bpArm:
// 			strcpy(szTemp,"ARM");
// 			break;		//No
// 		case bpHand:
// 			strcpy(szTemp,"HAND");
// 			break;
// 		case bpKnee:
// 			strcpy(szTemp,"KNEE");
// 			break;
// 		case bpLeg:
// 			strcpy(szTemp,"LEG");
// 			break;		//No
// 		case bpAnkle:
// 			strcpy(szTemp,"ANKLE");
// 			break;
// 		case bpFoot:
// 			strcpy(szTemp,"FOOT");
// 			break;
// 		case bpHeart:
// 			strcpy(szTemp,"HEART");
// 			break;		//No
// 		case bpVascularHead:
// 			strcpy(szTemp,"VASCULARHEAD");
// 			break;	//No
// 		case bpVascularNeck:
// 			strcpy(szTemp,"VASCULARNECK");
// 			break;	//No
// 		case bpVascularBody:
// 			strcpy(szTemp,"VASCULARBODY");
// 			break;	//No
// 		case bpVascularPeripheral:
// 			strcpy(szTemp,"VASCULARPER");
// 			break;	//No
//         //Added by Tom, --2008.07.10
// 		case bpLung:
// 			strcpy(szTemp,"LUNG");
// 			break;
// 		case bpLiver:
// 			strcpy(szTemp,"LIVER");
// 			break;
// 		case bpKidney:
// 			strcpy(szTemp,"KIDNEY");
//             break; 
// 	}
// 	nStrLen = StringRealSize(szTemp)%2 + StringRealSize(szTemp);
// 	if(!WriteDataElementChar(pcCurrent,0x0018,0x0015,"CS",nStrLen,szTemp))
// 	{
// 		return false;
// 	}
// 	//*						(0018,0020) Scanning Sequence CS 1-n
// 	//*						(0018,0021) Sequence Variant CS 1-n
// 	//*						(0018,0022) Scan Options CS 1-n
// 	/***********************Begin**********************/
// 	switch(imageHeader.seriesField.SequenceOptions&255)
// 	{
// 		case cnstSE:
// 			{
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0020,"CS",2,"SE"))
// 				{
// 					return false;
// 				}
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0021,"CS",4,"NONE"))
// 				{
// 					return false;
// 				}
// 			}break;
// 		case cnstSEDWI:
// 			{
// 				/*
// 				时间：2007-09-18
// 				作者：陈实
// 				目的：DICOM无法传输
// 				*/
// 				/*********************Begin************************/
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0020,"CS",6,"SEDWI "))
// 				{
// 					return false;
// 				}
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0021,"CS",4,"NONE"))
// 				{
// 					return false;
// 				}
// 			}break;
// 		case cnstIRSE:
// 			{
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0020,"CS",4,"IRSE"))
// 				{
// 					return false;
// 				}
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0021,"CS",4,"NONE"))
// 				{
// 					return false;
// 				}
// 			}break;
// 		case cnstFSE:
// 			{
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0020,"CS",4,"FSE "))
// 				{
// 					return false;
// 				}
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0021,"CS",4,"NONE"))
// 				{
// 					return false;
// 				}
// 			}
// 			break;
// 		case cnstSTIR:
// 			{
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0020,"CS",4,"STIR"))
// 				{
// 					return false;
// 				}
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0021,"CS",4,"NONE"))
// 				{
// 					return false;
// 				}
// 			}
// 			break;
// 		case cnstFLAIR:
// 			{
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0020,"CS",6,"FLAIR"))
// 				{
// 					return false;
// 				}
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0021,"CS",4,"NONE"))
// 				{
// 					return false;
// 				}
// 			}
// 			break;
// 		case cnstGRE:
// 			{
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0020,"CS",4,"GRE"))
// 				{
// 					return false;
// 				}
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0021,"CS",4,"NONE"))
// 				{
// 					return false;
// 				}
// 			}
// 			break;
// 		case cnstSPGR:
// 			{
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0020,"CS",4,"SPGR"))
// 				{
// 					return false;
// 				}
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0021,"CS",4,"NONE"))
// 				{
// 					return false;
// 				}
// 			}
// 			break;
// 		case cnstTOF3D:
// 			{
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0020,"CS",4,"TOF "))
// 				{
// 					return false;
// 				}
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0021,"CS",4,"NONE"))
// 				{
// 					return false;
// 				}
// 			}
// 			break;
// 		case cnstLSDI:
// 		case cnstLSDI1B:
// 			{
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0020,"CS",4,"LSDI"))
// 				{
// 					return false;
// 				}
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0021,"CS",4,"NONE"))
// 				{
// 					return false;
// 				}
// 			}
// 			break;
// 			
// 		case cnstEPDWI:
// 		case cnstEPDWI1B:
// 			{
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0020,"CS",6,"EPDWI"))
// 				{
// 					return false;
// 				}
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0021,"CS",4,"NONE"))
// 				{
// 					return false;
// 				}
// 			}
// 			break;
// 		case cnstShimming:
// 			{
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0020,"CS",2," "))
// 				{
// 					return false;
// 				}
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0021,"CS",4,"NONE"))
// 				{
// 					return false;
// 				}
// 			}
// 			break;
// 	}
// 	/***********************End**********************/
// 
// 	switch(imageHeader.seriesField.SequenceOptions&0xFFFFFF00)
// 	{
// 		case cnstRespiratoryTriggering:
// 			{
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0022,"CS",2,"RG"))return false;
// 			}
// 			break;
// 		case cnstECGGating:
// 			{
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0022,"CS",2,"CG"))return false;
// 			}
// 			break;
// 		case cnstPeripheralGating:
// 			{
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0022,"CS",4,"PPG"))return false;
// 			}
// 			break;
// 		case cnstMTC:
// 			{
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0022,"CS",2,"MT"))return false;
// 			}
// 			break;
// 		case cnstIRPreparation:
// 			{
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0022,"CS",2," "))return false;
// 			}
// 			break;
// 		case cnstDEPreparation:
// 			{
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0022,"CS",2," "))return false;
// 			}
// 			break;
// 		case cnstPOMP:
// 			{
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0022,"CS",2," "))return false;
// 			}
// 			break;
// 		case cnstChop:
// 			{
// 				if(!WriteDataElementChar(pcCurrent,0x0018,0x0022,"CS",4,"CHOP"))return false;
// 			}
// 			break;
// 	}
// 	//*Series_Mode			(0018,0023) MR Acquisition Type CS 1-n
// 	switch(imageHeader.seriesField.Mode)
// 	{
// 		case im2D:
// 			strcpy(szTemp,"2D");
// 			break;
// 		case im3D:
// 			strcpy(szTemp,"3D");
// 			break;
// 		default:
// 			szTemp[0]=0x00;
// 			break;
// 	}
// 	nStrLen = StringRealSize(szTemp)%2 + StringRealSize(szTemp);
// 	if(!WriteDataElementChar(pcCurrent,0x0018,0x0023,"CS",nStrLen,szTemp))
// 	{
// 		return false;
// 	}
// 	//						(0018,0024) Sequence Name SH 1
// 	nStrLen = StringRealSize(imageHeader.seriesField.PulseSeqName)%2 
// 		    + StringRealSize(imageHeader.seriesField.PulseSeqName);
// 	if(nStrLen>16)
// 	{
// 		nStrLen=16;
// 	}
// 	if(!WriteDataElementChar(pcCurrent,0x0018,0x0024,"SH",nStrLen,imageHeader.seriesField.PulseSeqName))
// 	{
// 		return false;
// 	}
// 	//*Series_Protocol Name	(0018,0030) Protocol Name LO 1
// 	char sPlaneAndProtocol[64], sPlaneType[16];
// 	if ( imageHeader.imageField.nPlaneType == ipAxial )
// 	{
// 		sprintf( sPlaneType, "Axi." );
// 	}
// 	else if ( imageHeader.imageField.nPlaneType == ipSagittal )
// 	{
// 		sprintf( sPlaneType, "Sag." );
// 	}
// 	else if ( imageHeader.imageField.nPlaneType == ipCoronal )
// 	{
// 		sprintf( sPlaneType, "Cor." );
// 	}
// 	else
// 	{
// 		sprintf( sPlaneType, "Obl." );
// 	}
// 	sprintf( sPlaneAndProtocol, "%s %s\0", sPlaneType, imageHeader.seriesField.Protocol );
// 
// 	nStrLen = StringRealSize(sPlaneAndProtocol/*imageHeader.seriesField.Protocol*/)%2
// 		    + StringRealSize(sPlaneAndProtocol/*imageHeader.seriesField.Protocol*/);
// 	if(!WriteDataElementChar(pcCurrent,0x0018,0x0030,"LO",nStrLen,sPlaneAndProtocol/*imageHeader.seriesField.Protocol*/))
// 	{
// 		return false;
// 	}
// 	//*SliceThickness		(0018,0050) Slice Thickness DS 1
// 	_gcvt(imageHeader.seriesField.SliceThickness,7,szTemp);
// 	nStrLen = StringRealSize(szTemp)%2 + StringRealSize(szTemp);
// 	if(!WriteDataElementChar(pcCurrent,0x0018,0x0050,"DS",nStrLen,szTemp))
// 	{
// 		return false;
// 	}
// 	//*Series_RepTime			(0018,0080) Repetition Time DS 1
// 	_ultoa(imageHeader.seriesField.RepTime,szTemp,10);
// 	nStrLen=StringRealSize(szTemp)%2 + StringRealSize(szTemp);
// 	if(!WriteDataElementChar(pcCurrent,0x0018,0x0080,"DS",nStrLen,szTemp))
// 	{
// 		return false;
// 	}
// 	//*Series_EchoTime			(0018,0081) Echo Time DS 1
// 	_ultoa(imageHeader.seriesField.EchoTime,szTemp,10);
// 	nStrLen = StringRealSize(szTemp)%2 + StringRealSize(szTemp);
// 	if(!WriteDataElementChar(pcCurrent,0x0018,0x0081,"DS",nStrLen,szTemp))
// 	{
// 		return false;
// 	}
// 	//Series_TI					(0018,0082) Inversion Time DS 1		
// 	_itoa(imageHeader.seriesField.TI,szTemp,10);
// 	nStrLen = StringRealSize(szTemp)%2 + StringRealSize(szTemp);
// 	if(!WriteDataElementChar(pcCurrent,0x0018,0x0082,"DS",nStrLen,szTemp))
// 	{
// 		return false;
// 	}
// 	//*Series_NumAvg				(0018,0083) Number of Averages DS 1
// 	_itoa(imageHeader.seriesField.NumAvg,szTemp,10);
// 	nStrLen = StringRealSize(szTemp)%2 + StringRealSize(szTemp);
// 	if(!WriteDataElementChar(pcCurrent,0x0018,0x0083,"DS",nStrLen,szTemp))
// 	{
// 		return false;
// 	}
// 	//*Series_NucType			(0018,0085) Imaged Nucleus SH 1
// 	switch(imageHeader.seriesField.NucType)
// 	{
// 		case ntH1:
// 			strcpy(szTemp,"1H");
// 			break;
// 		case ntHe3:
// 			strcpy(szTemp,"3He");
// 			break;	
// 		case ntC13:
// 			strcpy(szTemp,"13C");
// 			break;
// 		case ntF19:
// 			strcpy(szTemp,"19F");
// 			break;
// 		case ntNa23:
// 			strcpy(szTemp,"23Na");
// 			break;
// 		case ntP31:
// 			strcpy(szTemp,"31P");
// 			break;
// 		case ntK39:
// 			strcpy(szTemp,"39K");
// 			break;
// 		case ntXe129:
// 			strcpy(szTemp,"129Xe");
// 			break;
// 	}
// 	nStrLen = StringRealSize(szTemp)%2 + StringRealSize(szTemp);
// 	if(!WriteDataElementChar(pcCurrent,0x0018,0x0085,"SH",nStrLen,szTemp))
// 	{
// 		return false;
// 	}
// 	//*Image_EchoNum			(0018,0086) Echo Number(s) IS 1-n
// 	_ultoa(imageHeader.imageField.EchoNum, szTemp, 10);
// 	nStrLen = StringRealSize(szTemp)%2 + StringRealSize(szTemp);
// 	if(!WriteDataElementChar(pcCurrent,0x0018,0x0086,"IS",nStrLen,szTemp))
// 	{
// 		return false;
// 	}
// 	//*							(0018,0087) Magnetic Field Strength DS 1
// 	if(!WriteDataElementChar(pcCurrent,0x0018,0x0087,"DS",4,"0.3"))
// 	{
// 		return false;
// 	}
// 	//*Series_SliceGap			(0018,0088) Spacing Between Slices DS 1
// 	_ultoa(imageHeader.seriesField.SliceGap,szTemp,10);
// 	nStrLen=StringRealSize(szTemp)%2+StringRealSize(szTemp);
// 	if(!WriteDataElementChar(pcCurrent,0x0018,0x0088,"DS",nStrLen,szTemp))
// 	{
// 		return false;
// 	}
// 	//*Series_PhasePoint		(0018,0089) Number of Phase Encoding Steps IS 1
// 	_ultoa(imageHeader.seriesField.PhasePoints,szTemp,10);
// 	nStrLen=StringRealSize(szTemp)%2+StringRealSize(szTemp);
// 	if(!WriteDataElementChar(pcCurrent,0x0018,0x0089,"IS",nStrLen,szTemp))
// 	{
// 		return false;
// 	}
// 	//*Series_EchoTrainLength	(0018,0091) Echo Train Length IS 1
// 	_ultoa(imageHeader.seriesField.EchoTrainLength,szTemp,10);
// 	nStrLen=StringRealSize(szTemp)%2+StringRealSize(szTemp);
// 	if(!WriteDataElementChar(pcCurrent,0x0018,0x0091,"IS",nStrLen,szTemp))
// 	{
// 		return false;
// 	}
// 	//*					(0018,0094) Percent Phase Field of View DS 1
// 	_gcvt(imageHeader.seriesField.FovY/imageHeader.seriesField.FovX,7,szTemp);
// 	nStrLen=StringRealSize(szTemp)%2+StringRealSize(szTemp);
// 	if(!WriteDataElementChar(pcCurrent,0x0018,0x0094,"DS",nStrLen,szTemp))
// 	{
// 		return false;
// 	}
// 	//*Series_AcqBandWitch	(0018,0095) Pixel Bandwidth DS 1
// 	_gcvt(imageHeader.seriesField.AcqBandwidth,7,szTemp);
// 	nStrLen=StringRealSize(szTemp)%2+StringRealSize(szTemp);
// 	if(!WriteDataElementChar(pcCurrent,0x0018,0x0095,"DS",nStrLen,szTemp))
// 	{
// 		return false;
// 	}
// 	//*BISerialNum		(0018,1000) Device Serial Number LO 1
// 	nStrLen = StringRealSize(imageHeader.siteField.BISerialNum)%2
// 		    + StringRealSize(imageHeader.siteField.BISerialNum);
// 	if(!WriteDataElementChar(pcCurrent,0x0018,0x1000,"LO",nStrLen,imageHeader.siteField.BISerialNum))
// 	{
// 		return false;
// 	}
// 	//*Series_CardiacGating_TDT		(0018,1060) Trigger Time DS 1
// //	ultoa(imageHeader.seriesField.CardiacGating.m_usTriggerDelayTime,szTemp,10);
// //	nStrLen = StringRealSize(szTemp)%2 + StringRealSize(szTemp);
// //	if(!WriteDataElementChar(pcCurrent,0x0018,0x1060,"DS",nStrLen,szTemp))
// //	{
// //		return false;
// //	}
// 	//*Series_CardiacGating_SB		(0018,1086) Skip Beats IS 1
// //	ultoa(imageHeader.seriesField.CardiacGating.m_ucSkipBeat,szTemp,10);
// //	nStrLen = StringRealSize(szTemp)%2 + StringRealSize(szTemp);
// //	if(!WriteDataElementChar(pcCurrent,0x0018,0x1086,"IS",nStrLen,szTemp))
// //	{
// //		return false;
// //	}
// 	//*Series_CardiacGating_Rate		(0018,1088) Heart Rate IS 1
// //	ultoa(imageHeader.seriesField.CardiacGating.m_usRate, szTemp, 10);
// //	nStrLen = StringRealSize(szTemp)%2 + StringRealSize(szTemp);
// //	if(!WriteDataElementChar(pcCurrent,0x0018,0x1088,"IS",nStrLen,szTemp))
// //	{
// //		return false;
// //	}
// 	//*Series_CardiacGating_NOI		(0018,1090) Cardiac Number of Images IS 1
// //	ultoa(imageHeader.seriesField.CardiacGating.m_usNumOfImages,szTemp,10);
// //	nStrLen = StringRealSize(szTemp)%2+StringRealSize(szTemp);
// //	if(!WriteDataElementChar(pcCurrent,0x0018,0x1090,"IS",nStrLen,szTemp))
// //	{
// //		return false;
// //	}
// 	//*Series_CardiacGating_TW		(0018,1094) Trigger Window IS 1
// //	ultoa(imageHeader.seriesField.CardiacGating.m_usTriggerWin,szTemp,10);
// //	nStrLen = StringRealSize(szTemp)%2 + StringRealSize(szTemp);
// //	if(!WriteDataElementChar(pcCurrent,0x0018,0x1094,"IS",nStrLen,szTemp))
// //	{
// //		return false;
// //	}
// 	//*LastCalib		(0018,1200) Date of Last Calibration DA 1-n	
// 	//*					(0018,1201) Time of Last Calibration TM 1-n
// 	TimeConvert(imageHeader.studyField.Time,strDate,strTime);
// 	if(!WriteDataElementChar(pcCurrent,0x0018,0x1200,"DA",8,const_cast<char*>(strDate.c_str())))
// 	{
// 		return false;
// 	}
// 	if(!WriteDataElementChar(pcCurrent,0x0018,0x1201,"TM",6,const_cast<char*>(strTime.c_str())))
// 	{
// 		return false;
// 	}
// 	//*RcvCoil				(0018,1250) Receiving Coil SH 1
// 	switch(imageHeader.seriesField.RcvCoil)
// 	{
// 		case ctSystemCoil:
// 			strcpy(szTemp,"SYSTEMCOIL");
// 			break;
// 		case ctHeadSolonoid:
// 			strcpy(szTemp,"HEADSOLONOID");
// 			break;
// 		case ctBodySolonoidL:
// 			strcpy(szTemp,"BODYSOLONOIDL");
// 			break;
// 		case ctBodySolonoidM:
// 			strcpy(szTemp,"BODYSOLONOIDM");
// 			break;
// 		case ctBodySolonoidS:
// 			strcpy(szTemp,"BODYSOLONOIDS");
// 			break;
// 		case ctNeckSolonoid:
// 			strcpy(szTemp,"NECKSOLONOID");
// 			break;
// 		case ctHeadQD:
// 			strcpy(szTemp,"HEADQD");
// 			break;
// 		case ctKneeQD:
// 			strcpy(szTemp,"KNEEQD");
// 			break;
// 		case ctBodyQDL:
// 			strcpy(szTemp,"BODYQDL");
// 			break;
// 		case ctBodyQDM:
// 			strcpy(szTemp,"BODYQDM");
// 			break;
// 		case ctBodyQDS:
// 			strcpy(szTemp,"BODYQDS");
// 			break;
// 		case ctSurfaceNeck:
// 			strcpy(szTemp,"SURFACENECK");
// 			break;
// 		case ctSurfaceElbow:
// 			strcpy(szTemp,"SURFACEELBOW");
// 			break;
// 		case ctSurfaceShoulder:
// 			strcpy(szTemp,"SURFACESHOULDER");
// 			break;
// 		case ctPhaseArraySpine:
// 			strcpy(szTemp,"PHASEARRAYSPINE");
// 			break;
// 		case ctPhaseArrayCardiac:
// 			strcpy(szTemp,"PHASEARRAYCARD");
// 			break;
// 	}
// 	nStrLen=StringRealSize(szTemp)%2+StringRealSize(szTemp);
// 	if(!WriteDataElementChar(pcCurrent,0x0018,0x1250,"SH",nStrLen,szTemp))
// 	{
// 		return false;
// 	}
// 	//*TXCoil				(0018,1251) Transmitting Coil SH 1
// 	switch(imageHeader.seriesField.TXCoil)
// 	{
// 		case ctSystemCoil:
// 			strcpy(szTemp,"SYSTEMCOIL");
// 			break;
// 		case ctHeadSolonoid:
// 			strcpy(szTemp,"HEADSOLONOID");
// 			break;
// 		case ctBodySolonoidL:
// 			strcpy(szTemp,"BODYSOLONOIDL");
// 			break;
// 		case ctBodySolonoidM:
// 			strcpy(szTemp,"BODYSOLONOIDM");
// 			break;
// 		case ctBodySolonoidS:
// 			strcpy(szTemp,"BODYSOLONOIDS");
// 			break;
// 		case ctNeckSolonoid:
// 			strcpy(szTemp,"NECKSOLONOID");
// 			break;
// 		case ctHeadQD:
// 			strcpy(szTemp,"HEADQD");
// 			break;
// 		case ctKneeQD:
// 			strcpy(szTemp,"KNEEQD");
// 			break;
// 		case ctBodyQDL:
// 			strcpy(szTemp,"BODYQDL");
// 			break;
// 		case ctBodyQDM:
// 			strcpy(szTemp,"BODYQDM");
// 			break;
// 		case ctBodyQDS:
// 			strcpy(szTemp,"BODYQDS");
// 			break;
// 		case ctSurfaceNeck:
// 			strcpy(szTemp,"SURFACENECK");
// 			break;
// 		case ctSurfaceElbow:
// 			strcpy(szTemp,"SURFACEELBOW");
// 			break;
// 		case ctSurfaceShoulder:
// 			strcpy(szTemp,"SURFACESHOULDER");
// 			break;
// 		case ctPhaseArraySpine:
// 			strcpy(szTemp,"PHASEARRAYSPINE");
// 			break;
// 		case ctPhaseArrayCardiac:
// 			strcpy(szTemp,"PHASEARRAYCARD");
// 			break;
// 	}
// 	nStrLen=StringRealSize(szTemp)%2+StringRealSize(szTemp);
// 	if(!WriteDataElementChar(pcCurrent,0x0018,0x1251,"SH",nStrLen,szTemp))
// 	{
// 		return false;
// 	}
// 	//						(0018,1310) Acquisition Matrix US 4
// 	//						(0018,1312) Phase Encoding Direction CS 1
// 	if(imageHeader.seriesField.OtherOptions&cnstDefaultFrequencyDir==0)
// 	{
// 		if(!WriteDataElementChar(pcCurrent,0x0018,0x1312,"CS",4,"COL"))
// 		{
// 			return false;
// 		}
// 	}
// 	else
// 	{
// 		if(!WriteDataElementChar(pcCurrent,0x0018,0x1312,"CS",4,"ROW"))
// 		{
// 			return false;
// 		}
// 	}
// 	//*Series_FlipAngle		(0018,1314) Flip Angle DS 1
// 	_gcvt(imageHeader.seriesField.FlipAngle,7,szTemp);
// 	nStrLen=StringRealSize(szTemp)%2+StringRealSize(szTemp);
// 	if(!WriteDataElementChar(pcCurrent,0x0018,0x1314,"DS",nStrLen,szTemp))
// 	{
// 		return false;
// 	}
// 	//*Series_SARAvg			(0018,1316) SAR DS 1
// 	_ultoa(imageHeader.seriesField.SARAvg,szTemp,10);
// 	nStrLen=StringRealSize(szTemp)%2+StringRealSize(szTemp);
// 	if(!WriteDataElementChar(pcCurrent,0x0018,0x1316,"DS",nStrLen,szTemp))
// 	{
// 		return false;
// 	}
// 	//*Study_PatPosition	(0018,5100) Patient Position CS 1
// 	//*Study_PatEntry
// 	if(imageHeader.studyField.PatEntry==beHeadFirst)
// 	{
// 		szTemp[0] = 'H';
// 	}
// 	else
// 	{
// 		szTemp[0] = 'F';
// 	}
// 
// 	szTemp[1]='F';
// 	switch(imageHeader.studyField.PatPosition)
// 	{
// 		case bpSupine:
// 			szTemp[2] = 'S';
// 			szTemp[3] = '\0';
// 			break;
// 		case bpProne:
// 			szTemp[2] = 'P';
// 			szTemp[3] = '\0';
// 			break;
// 		case bpDecubitusRight:
// 			szTemp[2] = 'D';
// 			szTemp[3] = 'R';
// 			szTemp[4] = '\0';
// 			break;
// 		case bpDecubitusLeft:
// 			szTemp[2] = 'D';
// 			szTemp[3] = 'L';
// 			szTemp[4] = '\0';
// 			break;
// 	}
// 	nStrLen=StringRealSize(szTemp)%2+StringRealSize(szTemp);
// 	if(!WriteDataElementChar(pcCurrent,0x0018,0x5100,"CS",nStrLen,szTemp))
// 	{
// 		return false;
// 	}
// 
// 	//Write Group Length
// 	if(!WriteDataElementNum(pcMark,0x0018,0x0000,"UL",0x04,pcCurrent-pcMark-12))
// 	{
// 		return false;
// 	}
// 
// 	///////////////////////////////////////////////////////////////////////////////
// 	//(0019,xxxx)
// 	
// 	//Group Length Mark
// 	pcMark = pcCurrent;
// 	pcCurrent += 12;
// 	//							(0019,0010) Private Creator ID LO 1
// 	if(!WriteDataElementChar(pcCurrent,0x0019,0x0010,"LO",14,"BIMRI_ACQU_01"))
// 	{
// 		return false;
// 	}
// 
// 	//Site_MagCalibStrength				*(0019,1001) MagCalibStrength FL 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1001,"FL",0x04,imageHeader.siteField.MagCalibStrength))
// 	{
// 		return false;
// 	}
// 	//Site_GradientStrengthX			*(0019,1002) GradientStrengthX FL
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1002,"FL",0x04,imageHeader.siteField.GradientStrengthX))
// 	{
// 		return false;
// 	}
// 	//Site_GradientStrengthY			*(0019,1003) GradientStrengthY FL
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1003,"FL",0x04,imageHeader.siteField.GradientStrengthY))
// 	{
// 		return false;
// 	}
// 	//Site_GradientStrengthZ			*(0019,1004) GradientStrengthZ FL
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1004,"FL",0x04,imageHeader.siteField.GradientStrengthZ))
// 	{
// 		return false;
// 	}
// 	//Site_SF							*(0019,1005) Spectrometer Freguency FL
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1005,"FL",0x04,imageHeader.siteField.SF))
// 	{
// 		return false;
// 	}
// 
// 	//???Study_Protocol					*(0019,1006) Study Protocol LO 1
// 	if ( imageHeader.imageField.nPlaneType == ipAxial )
// 	{
// 		sprintf( sPlaneType, "Axi." );
// 	}
// 	else if ( imageHeader.imageField.nPlaneType == ipSagittal )
// 	{
// 		sprintf( sPlaneType, "Sag." );
// 	}
// 	else if ( imageHeader.imageField.nPlaneType == ipCoronal )
// 	{
// 		sprintf( sPlaneType, "Cor." );
// 	}
// 	else
// 	{
// 		sprintf( sPlaneType, "Obl." );
// 	}
// 	sprintf( sPlaneAndProtocol, "%s %s\0", sPlaneType, imageHeader.studyField.Protocol );
// 	
// 	nStrLen = StringRealSize(sPlaneAndProtocol/*imageHeader.seriesField.Protocol*/)%2
// 		+ StringRealSize(sPlaneAndProtocol/*imageHeader.seriesField.Protocol*/);
// 	
// /*
// 	nStrLen = StringRealSize(imageHeader.studyField.Protocol)%2
// 		    + StringRealSize(imageHeader.studyField.Protocol);
// */
// 	if(!WriteDataElementChar(pcCurrent,0x0019,0x1006,"LO",nStrLen,sPlaneAndProtocol/*imageHeader.studyField.Protocol*/))
// 	{
// 		return false;
// 	}
// 	//???Study_ProtocolVersion			*(0019,1007) Study Protocol Version US 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1007,"US",0x02,imageHeader.studyField.ProtocolVersion))
// 	{
// 		return false;
// 	}
// 
// 	//Study_LandmarkPos		*(0019,1008) Land Mark Position US 1		//enum->char[]
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1008,"US",0x02,(short)imageHeader.studyField.LandmarkPos))
// 	{
// 		return false;
// 	}
// 	//Study_GradientId		*(0019,1009) Gradient ID LO 1
// 	nStrLen = StringRealSize(imageHeader.studyField.GradientId)%2
// 		    + StringRealSize(imageHeader.studyField.GradientId);
// 	if(!WriteDataElementChar(pcCurrent,0x0019,0x1009,"LO",nStrLen,imageHeader.studyField.GradientId))
// 	{
// 		return false;
// 	}
// 	//Scan_Id				(0019,100A) Scanning ID LO 1
// 	_ultoa(imageHeader.scanField.Id,szTemp,10);
// 	nStrLen=StringRealSize(szTemp)%2+StringRealSize(szTemp);
// 	if(!WriteDataElementChar(pcCurrent,0x0019,0x100A,"LO",nStrLen,szTemp))
// 	{
// 		return false;
// 	}
// 	//Series_GRR			*(0019,1011) GRR SL 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1011,"SL",0x04,imageHeader.seriesField.GRR))
// 	{
// 		return false;
// 	}
// 	//Series_UserTxCoilDesc	*(0019,1012) User TXCoil Desecription LO 1
// 	nStrLen = StringRealSize(imageHeader.seriesField.UserTxCoilDesc)%2
// 		    + StringRealSize(imageHeader.seriesField.UserTxCoilDesc);
// 	if(!WriteDataElementChar(pcCurrent,0x0019,0x1012,"LO",nStrLen,imageHeader.seriesField.UserTxCoilDesc))
// 	{
// 		return false;
// 	}
// 	//Series_UserRcvCoilDesc*(0019,1013) User RcvCoil Desecription LO 1
// 	nStrLen = StringRealSize(imageHeader.seriesField.UserRcvCoilDesc)%2
// 		    + StringRealSize(imageHeader.seriesField.UserRcvCoilDesc);
// 	if(!WriteDataElementChar(pcCurrent,0x0019,0x1013,"LO",nStrLen,imageHeader.seriesField.UserRcvCoilDesc))
// 	{
// 		return false;
// 	}
// 	//Series_PulseSeqName	*(0019,1014) Pulse Sequence Name LO 1		//(0018,0024)Dicom?????
// 	nStrLen = StringRealSize(imageHeader.seriesField.PulseSeqName)%2
// 		    + StringRealSize(imageHeader.seriesField.PulseSeqName);
// 	if(!WriteDataElementChar(pcCurrent,0x0019,0x1014,"LO",nStrLen,imageHeader.seriesField.PulseSeqName))
// 	{
// 		return false;
// 	}
// 	//Series_SequenceOptions	*(0019,1015) Sequence Options SL 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1015,"SL",0x04,imageHeader.seriesField.SequenceOptions))
// 	{
// 		return false;
// 	}
// 	//Series_OtherOptions		*(0019,1016) Other Options SL 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1016,"SL",0x04,imageHeader.seriesField.OtherOptions))
// 	{
// 		return false;
// 	}
// 
// 	//???Series_Mode			*(0019,1020) Image Mode US 1			//DICOM??2D,3D
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1020,"US",0x02,(short)imageHeader.seriesField.Mode))
// 	{
// 		return false;
// 	}
// 	//Series_FovX			*(0019,1021) Field Of View X US 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1021,"US",0x02,imageHeader.seriesField.FovX))
// 	{
// 		return false;
// 	}
// 	//Series_FovY			*(0019,1022) Field Of View Y US 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1022,"US",0x02,imageHeader.seriesField.FovY))
// 	{
// 		return false;
// 	}
// 	//Series_FovZ			*(0019,1023) Field Of View Z US 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1023,"US",0x02,imageHeader.seriesField.FovZ))
// 	{
// 		return false;
// 	}
// 	//Series_ResolutionX		*(0019,1024) Resolution X US 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1024,"US",0x02,imageHeader.seriesField.ResolutionX))
// 	{
// 		return false;	
// 	}
// 	//Series_ResolutionY		*(0019,1025) Resolution Y US 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1025,"US",0x02,imageHeader.seriesField.ResolutionY))
// 	{
// 		return false;
// 	}
// 	//Series_ResolutionZ		*(0019,1026) Resolution Z US 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1026,"US",0x02,imageHeader.seriesField.ResolutionZ))
// 	{
// 		return false;
// 	}
// 	//Series_SlabOrder			*(0019,1027) Slab Order US 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1027,"US",0x02,(short)imageHeader.seriesField.SlabOrder))
// 	{
// 		return false;
// 	}
// 	//Series_NumPntsPerSlab	*(0019,1028) Num of Points Per Slab US 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1028,"US",0x02,imageHeader.seriesField.NumPntsPerSlab))
// 	{
// 		return false;
// 	}
// 	//Series_SlabOverlap		*(0019,1029) Slab Overlapped US 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1029,"US",0x02,imageHeader.seriesField.SlabOverlap))
// 	{
// 		return false;
// 	}
// 	//Series_Echo2Time			*(0019,1030) Echo2 Time DS 1
// 	_ultoa(imageHeader.seriesField.Echo2Time,szTemp,10);
// 	nStrLen=StringRealSize(szTemp)%2+StringRealSize(szTemp);
// 	if(!WriteDataElementChar(pcCurrent,0x0019,0x1030,"DS",nStrLen,szTemp))
// 	{
// 		return false;
// 	}
// 	//Series_EchoSpacing		*(0019,1031) Echo Spacing UL 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1031,"UL",0x04,imageHeader.seriesField.EchoSpacing))
// 	{
// 		return false;
// 	}
// 	//Series_NumEchoImages		*(0019,1032) NumEchoImages US 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1032,"US",0x02,imageHeader.seriesField.NumEchoImages))
// 	{
// 		return false;
// 	}
// 	//Series_AcqBandwidth		*(0019,1033) AcqBandwidth FL 1
// //	if(!WriteDataElementNum(q,0x0019,0x1033,"FL",0x04,imageHeader.seriesField.AcqBandwidth))return 0;
// 	//Series_AcqBandwidth2		*(0019,1034) AcqBandwidth2 FL 1
// 	_gcvt(imageHeader.seriesField.AcqBandwidth2,7,szTemp);
// 	nStrLen = StringRealSize(szTemp)%2 + StringRealSize(szTemp);
// 	if(!WriteDataElementChar(pcCurrent,0x0019,0x1034,"DS",nStrLen,szTemp))
// 	{
// 		return false;
// 	}
// 	//Series_NumSlab			(0019,1035) Number of Slices US 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1035,"US",0x02,imageHeader.seriesField.NumSlab))
// 	{
// 		return false;
// 	}
// 	//Series_SARPeak			*(0019,1040) SAR Peak DS 1
// 	_ultoa(imageHeader.seriesField.SARPeak,szTemp,10);
// 	nStrLen = StringRealSize(szTemp)%2 + StringRealSize(szTemp);
// 	if(!WriteDataElementChar(pcCurrent,0x0019,0x1040,"DS",nStrLen,szTemp))
// 	{
// 		return false;
// 	}
// 	//Series_PresaturationRegions[6]	*(0019,1041) Presaturation Regions UN 3
// 	if(!WriteDataElementChar(pcCurrent,0x0019,0x1041,"UN",0x06,imageHeader.seriesField.PresaturationRegions))
// 	{
// 		return false;
// 	}
// //	//Series_CardiacGating_PPS				*(0019,1042) Cardiac Gating US 2
// //	if(!WriteDataElementNum(pcCurrent,0x0019,0x1042,"US",0x02,
// //		(short)imageHeader.seriesField.CardiacGating.m_ucPhasesPerSegment))
// //	{
// //		return false;
// //	}
// 	//Scan_CardDelayTime	*(0019,1043) Card Delay Time SL 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1043,"SL",0x04,imageHeader.imageField.CardDelayTime))
// 	{
// 		return false;
// 	}
// 
// 	//Series_ContrastFlag		*(0019,1050) Contrast Flag US 1			//DICOM??Contrast Agent
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1050,"US",0x02,(short)imageHeader.seriesField.ContrastFlag))
// 	{
// 		return false;
// 	}
// 	//Series_IVContrast[32]		*(0019,1051) IVContrast LO 1
// 	nStrLen = StringRealSize(imageHeader.seriesField.IVContrast)%2
// 		    + StringRealSize(imageHeader.seriesField.IVContrast);
// 	if(!WriteDataElementChar(pcCurrent,0x0019,0x1051,"LO",nStrLen,imageHeader.seriesField.IVContrast))
// 	{
// 		return false;
// 	}
// 	//Series_OralContrast[32]	*(0019,1052) OralContrast LO 1
// 	nStrLen = StringRealSize(imageHeader.seriesField.OralContrast)%2
// 		    + StringRealSize(imageHeader.seriesField.OralContrast);
// 	if(!WriteDataElementChar(pcCurrent,0x0019,0x1052,"LO",nStrLen,imageHeader.seriesField.OralContrast))
// 	{
// 		return false;
// 	}
// 	//Series_ContrastAmount		*(0019,1053) Contrast Amount FL 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1053,"FL",0x04,imageHeader.seriesField.ContrastAmount))
// 	{
// 		return false;
// 	}
// 
// 	//Series_PauseTime		*(0019,1060) Pause Time FL 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1060,"FL",0x04,imageHeader.seriesField.PauseTime))
// 	{
// 		return false;
// 	}
// 	//Series_NumAvg			*(0019,1061) Number Of Scans SS 1
// //	if(!WriteDataElementNum(pcCurrent,0x0019,0x1061,"SS",0x02,imageHeader.seriesField.NumAvg);
// 	//Series_PhEncOrder		*(0019,1062) Phase Encoding Order SS 1 		//enum->char[]
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1062,"SS",0x02,imageHeader.seriesField.PhEncOrder))
// 	{
// 		return false;
// 	}
// 	//Series_Saturation		*(0019,1063) Saturation SS 1				//enum->char[]
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1063,"SS",0x02,imageHeader.seriesField.Saturation))
// 	{
// 		return false;
// 	}
// 	//Series_PhasePoints	*(0019,1065) Phase Points US 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1065,"US",0x02,imageHeader.seriesField.PhasePoints))
// 	{
// 		return false;
// 	}
// 	//Series_EchoRatio		*(0019,1066) EchoRatio FL 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1066,"FL",0x04,imageHeader.seriesField.EchoRatio))
// 	{
// 		return false;
// 	}
// 	//Scan_RFTxLev			*(0019,1090) Hardware RF Transmitter Power Level FL 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1090,"FL",0x04,imageHeader.scanField.RFTxLev))
// 	{
// 		return false;
// 	}
// 	//Scan_AnaRCGain		*(0019,1091) Analog Gain FL 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1091,"FL",0x04,imageHeader.scanField.AnaRCGain))
// 	{
// 		return false;
// 	}
// 	//Scan_DigRCGain		*(0019,1092) Digital Gain FL 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1092,"FL",0x04,imageHeader.scanField.DigRCGain))
// 	{
// 		return false;
// 	}
// 	//Scan_O1				*(0019,1093) Transmitter Center FrepcCurrentuency Offset FL 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1093,"FL",0x04,imageHeader.scanField.O1))
// 	{
// 		return false;
// 	}
// 	//Scan_ACQ				*(0019,1094) ACQ Time Of Scan US 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x1094,"US",0x02,imageHeader.scanField.ACQ))
// 	{
// 		return false;
// 	}
// 	
// 	//Scan_FreqDir			*(0019,10A0) FreqDir US 1	
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x10A0,"US",0x02,(short)imageHeader.scanField.FreqDir))
// 	{
// 		return false;
// 	}
// 	//Scan_FreqDirX			*(0019,10A1) FreqDirX FL 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x10A1,"FL",0x04,imageHeader.scanField.FreqDirX))
// 	{
// 		return false;
// 	}
// 	//Scan_FreqDirY			*(0019,10A2) FreqDirY FL 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x10A2,"FL",0x04,imageHeader.scanField.FreqDirY))
// 	{
// 		return false;
// 	}
// 	//Scan_FreqDirZ			*(0019,10A3) FreqDirZ FL 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x10A3,"FL",0x04,imageHeader.scanField.FreqDirZ))
// 	{
// 		return false;
// 	}
// 	//Scan_PhaseDirX		*(0019,10A4) PhaseDirX FL 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x10A4,"FL",0x04,imageHeader.scanField.PhaseDirX))
// 	{
// 		return false;
// 	}
// 	//Scan_PhaseDirY		*(0019,10A5) PhaseDirY FL 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x10A5,"FL",0x04,imageHeader.scanField.PhaseDirY))
// 	{
// 		return false;
// 	}
// 	//Scan_PhaseDirZ		*(0019,10A6) PhaseDirZ FL 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x10A6,"FL",0x04,imageHeader.scanField.PhaseDirZ))
// 	{
// 		return false;
// 	}
// 	//Scan_SliceDirX		*(0019,10A7) SliceDirX FL 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x10A7,"FL",0x04,imageHeader.scanField.SliceDirX))
// 	{
// 		return false;
// 	}
// 	//Scan_SliceDirY		*(0019,10A8) SliceDirY FL 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x10A8,"FL",0x04,imageHeader.scanField.SliceDirY))
// 	{
// 		return false;
// 	}
// 	//Scan_SliceDirZ		*(0019,10A9) SliceDirZ FL 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x10A9,"FL",0x04,imageHeader.scanField.SliceDirZ))
// 	{
// 		return false;
// 	}
// 	//Scan_ReadOffset		*(0019,10AA) ReadOffset FL 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x10AA,"FL",0x04,imageHeader.scanField.ReadOffset))
// 	{
// 		return false;
// 	}
// 	//Scan_PhaseOffset		*(0019,10AB) PhaseOffset FL 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x10AB,"FL",0x04,imageHeader.scanField.PhaseOffset))
// 	{
// 		return false;
// 	}
// 	//Scan_SliceOffset		*(0019,10AC) SliceOffset FL 1
// 	if(!WriteDataElementNum(pcCurrent,0x0019,0x10AC,"FL",0x04,imageHeader.scanField.SliceOffset))
// 	{
// 		return false;
// 	}
// 
// 	//Write Group Length
// 	if(!WriteDataElementNum(pcMark,0x0019,0x0000,"UL",0x04,pcCurrent-pcMark-12))
// 	{
// 		return false;
// 	}
// 
// 
// 	///////////////////////////////////////////////////////////////////////////////
// 	//???????????(0020,xxxx)
// 	
// 	//Group Length Mark
// 	pcMark = pcCurrent;
// 	pcCurrent += 12;
// 	//*						(0020,000D) Study Instance UID	UI 1
// 	//<root org>.1.siteserialnum.studyid.datetimestamp
// 	strcpy(szTerm[0],"1");
// 	char *serial = imageHeader.siteField.BISerialNum + 10;
// 	strcpy(szTerm[1],serial);
// 	strcpy(szTerm[2],imageHeader.studyField.Id);
// 	_itoa(imageHeader.studyField.Time.year,szTerm[3],10);
// 	//Date Time Stamp
// 	char addition[4];
// 	_itoa(imageHeader.studyField.Time.month,addition,10);
// 	strcat(szTerm[3],addition);
// 	_itoa(imageHeader.studyField.Time.day,addition,10);
// 	strcat(szTerm[3],addition);
// 	_itoa(imageHeader.studyField.Time.hour,addition,10);
// 	strcat(szTerm[3],addition);
// 	_itoa(imageHeader.studyField.Time.minute,addition,10);
// 	strcat(szTerm[3],addition);
//     CreateStudyUID(imageHeader,szStudyUID);
// 	nStrLen = StringRealSize(szStudyUID)%2 + StringRealSize(szStudyUID);
// 	if(!WriteDataElementChar(pcCurrent,0x0020,0x000D,"UI",nStrLen,szStudyUID))
// 	{
// 		return false;
// 	}
// 
// 	//*						(0020,000E) Series Instance UID UI 1
// 	//<root org>.1.siteserialnum.studyid.seriesid.datetimestamp
// 	strcpy(szTerm[0],"1");
// 	serial=imageHeader.siteField.BISerialNum+10;
// 	strcpy(szTerm[1],serial);
// 	strcpy(szTerm[2],imageHeader.studyField.Id);
// 	_itoa(imageHeader.studyField.Time.year,szTerm[4],10);
// 	_itoa(imageHeader.seriesField.Id,szTerm[3],10);
// 	_itoa(imageHeader.studyField.Time.year,szTerm[4],10);
// 	//Date Time Stamp
// 	addition[4];
// 	_itoa(imageHeader.studyField.Time.month,addition,10);
// 	strcat(szTerm[4],addition);
// 	_itoa(imageHeader.studyField.Time.day,addition,10);
// 	strcat(szTerm[4],addition);
// 	_itoa(imageHeader.studyField.Time.hour,addition,10);
// 	strcat(szTerm[4],addition);
// 	_itoa(imageHeader.studyField.Time.minute,addition,10);
// 	strcat(szTerm[4],addition);
// 	CreateSeriesUID(imageHeader, szSeriesUID);
// 	nStrLen = StringRealSize(szSeriesUID)%2 + StringRealSize(szSeriesUID);
// 	if(!WriteDataElementChar(pcCurrent,0x0020,0x000E,"UI",nStrLen,szSeriesUID))
// 	{
// 		return false;
// 	}
// 
// 	//*Study_Id				(0020,0010) Study ID SH 1
// 	nStrLen = StringRealSize(imageHeader.studyField.Id)%2
// 		    + StringRealSize(imageHeader.studyField.Id);
// 	if(!WriteDataElementChar(pcCurrent,0x0020,0x0010,"SH",nStrLen,imageHeader.studyField.Id))
// 	{
// 		return false;
// 	}
// 	//*Series_Id			(0020,0011) Series Number IS 1
// 	_ultoa(imageHeader.seriesField.Id,szTemp,10);
// 	nStrLen = StringRealSize(szTemp)%2 + StringRealSize(szTemp);
// 	if(!WriteDataElementChar(pcCurrent,0x0020,0x0011,"IS",nStrLen,szTemp))
// 	{
// 		return false;
// 	}
// 	//*Image_Id				(0020,0013) Instance Number IS 1
// 	_ultoa(imageHeader.imageField.Id,szTemp,10);
// 	nStrLen = StringRealSize(szTemp)%2 + StringRealSize(szTemp);
// 	if(!WriteDataElementChar(pcCurrent,0x0020,0x0013,"IS",nStrLen,szTemp))
// 	{
// 		return false;
// 	}
// 	///////////////////////////////////////////////////////////////////////////
// 	//add chenshi (0x0020,0x0020) 直接传递标注的字符
// //	char pOrientation[2];
// //	memset(pOrientation,0,sizeof(char));
// //	int nLenOre=4;
// //	char *p1="PF";
// //	memcpy(pOrientation,p1,2);
// //	pOrientation[0]='L';
// //	pOrientation[1]='\';
// //	if(!WriteDataElementChar(pcCurrent,0x0020,0x0020,"CS",nLenOre,pOrientation))
// //	{
// //		return false;
// //	}
// 	////////////////////////////////////////////////////////////////////////////
// 
// 	//add chenshi (0x0020,0x0032) 图像的起始位置3*16
// 
// 	CString szPos;
// 	szPos.Format("%f\\%f\\%f",fTopLeftX,fTopLeftY,fTopLeftZ);
// 	int nLength=szPos.GetLength();
// 	if(nLength%2==1)
// 	{
// 		nLength++;
// 
// 
// 	}
// 	char*pPos=(char*)szPos.operator LPCTSTR();
// 	
// 	if(!WriteDataElementChar(pcCurrent,0x0020,0x0032,"DS",nLength,pPos))
// 	{
// 		return false;
// 	}
// 	//add chenshi 0x0020,0x0037
// 	CString szPosRotate;
// 	szPosRotate.Format("%f\\%f\\%f\\%f\\%f\\%f",
// 		fRowCosineWithX, fRowCosineWithY, fRowCosineWithZ,
// 		fColCosineWithX, fColCosineWithY,fColCosineWithZ);
// 	int nLen=szPosRotate.GetLength();
// 	nLen=nLen%2+nLen;
// 	char*pRotate=(char*)szPosRotate.operator LPCTSTR();
// 	if(!WriteDataElementChar(pcCurrent,0x0020,0x0037,"DS",nLen,pRotate))
// 	{
// 		return false;
// 	}
// 	////////////////////////////////////////////////////////////////////////
// 	//*						(0020,0060) Laterality CS 1
// 	if(!WriteDataElementChar(pcCurrent,0x0020,0x0060,"CS",0,"\0"))
// 	{
// 		return false;
// 	}
// 	//*						(0020,1040) Position Reference Indicator LO 1
// 	if(!WriteDataElementChar(pcCurrent,0x0020,0x1040,"LO",0,"\0"))
// 	{
// 		return false;
// 	}
// 
// 	//Write Group Length
// 	if(!WriteDataElementNum(pcMark,0x0020,0x0000,"UL",0x04,pcCurrent-pcMark-12))
// 	{
// 		return false;
// 	}
// 
// 	///////////////////////////////////////////////////////////////////////////////
// 	//(0021,xxxx)
// 
// 	//Group Length Mark
// 	pcMark = pcCurrent;
// 	pcCurrent += 12;
// 	//							(0021,0010) Private Creator ID LO 1
// 	if(!WriteDataElementChar(pcCurrent,0x0021,0x0010,"LO",14,"BIMRI_RELA_01"))
// 	{
// 		return false;
// 	}
// 
// 	//??Image_OffsetSI		*(0021,1001) OffsetSI SS 1					//DICOM???????????
// 	if(!WriteDataElementNum(pcCurrent,0x0021,0x1001,"SS",0x02,imageHeader.imageField.OffsetSI))
// 	{
// 		return false;
// 	}
// 	//??Image_OffsetAP		*(0021,1002) OffsetAP SS 1
// 	if(!WriteDataElementNum(pcCurrent,0x0021,0x1002,"SS",0x02,imageHeader.imageField.OffsetAP))
// 	{
// 		return false;
// 	}
// 	//??Image_OffsetLR		*(0021,1003) OffsetLR SS 1
// 	if(!WriteDataElementNum(pcCurrent,0x0021,0x1003,"SS",0x02,imageHeader.imageField.OffsetLR))
// 	{
// 		return false;
// 	}
// 	//Series_Plane			*(0021,1004) Scan Plane US 1
// 	if(!WriteDataElementNum(pcCurrent,0x0021,0x1004,"US",0x02,(short)imageHeader.seriesField.Plane))
// 	{
// 		return false;	
// 	}
// 
// 	//Write Group Length
// 	if(!WriteDataElementNum(pcMark,0x0021,0x0000,"UL",0x04,pcCurrent-pcMark-12))
// 	{
// 		return false;
// 	}
// 
// 	///////////////////////////////////////////////////////////////////////////////
// 	//Pixel(0028,xxxx)
// 
// 	//Group Length Mark
// 	pcMark = pcCurrent;
// 	pcCurrent += 12;
// 	//*					(0028,0002) Samples per Pixel US 1
// 	short ss = 0x01;
// 	if(!WriteDataElementNum(pcCurrent,0x0028,0x0002,"US",0x02,ss))
// 	{
// 		return false;
// 	}
// 	//*					(0028,0004) Photometric Interpretation CS 1
// 	if(!WriteDataElementChar(pcCurrent,0x0028,0x0004,"CS",12,"MONOCHROME2"))
// 	{
// 		return false;
// 	}
// 	//*					(0028,0010) Rows US 1
// 	if(!WriteDataElementNum(pcCurrent,0x0028,0x0010,"US",0x02,imageHeader.seriesField.ResolutionY))
// 	{
// 		return false;
// 	}
// 	//*					(0028,0011) Columns US 1
// 	if(!WriteDataElementNum(pcCurrent,0x0028,0x0011,"US",0x02,imageHeader.seriesField.ResolutionX))
// 	{
// 		return false;
// 	}
// 	//*                 (0028,0030) Pixel Spacing
// 	/************************************************************************/
// 	/*
// 	日期：2007-09-24
// 	作者：陈实
// 	目的：修改FOVRadio的问题
// 	*/
// 	double dXSpacing = (double)imageHeader.seriesField.FovX/(imageHeader.seriesField.ResolutionX-1) ;
// 	double dYSpacing = (double)imageHeader.seriesField.FovX/(imageHeader.seriesField.ResolutionY-1) ;
// 	/************************************************************************/
// 	
// 	
// 	CString csSpacing;
// 	csSpacing.Format("%10.8f\\%10.8f",dXSpacing,dYSpacing);
//     nStrLen = csSpacing.GetLength() ;
// 	nStrLen += nStrLen%2 ;
// 	if(!WriteDataElementChar(pcCurrent,0x0028,0x0030,"DS",nStrLen,csSpacing.GetBuffer(nStrLen)))
// 	{
// 		return false;
// 	}
// 
// 	//*					(0028,0100) Bits Allocated US 1
// 	ss=0x10;
// 	if(!WriteDataElementNum(pcCurrent,0x0028,0x0100,"US",0x02,ss))
// 	{
// 		return false;
// 	}
// 	//*					(0028,0101) Bits Stored US 1
// 	ss = 0x0c;
// 	if(!WriteDataElementNum(pcCurrent,0x0028,0x0101,"US",0x02,ss))
// 	{
// 		return false;
// 	}
// 	//*					(002s8,0102) High Bit US 1
// 	ss = 0x0B;
// 	if(!WriteDataElementNum(pcCurrent,0x0028,0x0102,"US",0x02,ss))
// 	{
// 		return false;
// 	}
// 	//*					(0028,0103) Pixel Representation US 1
// 	ss = 0x00;
// 	if(!WriteDataElementNum(pcCurrent,0x0028,0x0103,"US",0x02,ss))
// 	{
// 		return false;
// 	}
// 	CString szWindowLevel;
// 	szWindowLevel.Format("%04d",imageHeader.imageField.WindowLevel);
// 	int nCountOfValue=szWindowLevel.GetLength();
// 	if(nCountOfValue%2==1)
// 	{
// 		nCountOfValue+=1;
// 	}
// 	//char*pWW=szWindowLevel.
// 	if(!WriteDataElementChar(pcCurrent,0x0028,0x1050,"DS",nCountOfValue,(char*)szWindowLevel.operator LPCTSTR()))
// 	{
// 		return false;
// 	}
// 	CString szWindowWidth;
// 	szWindowWidth.Format("%04d",imageHeader.imageField.WindowWidth);
// 	nCountOfValue=szWindowWidth.GetLength();
// 	if(nCountOfValue%2==1)
// 	{
// 		nCountOfValue+=1;
// 	}
// 	/*********zyh add 2008.2.27*********/
// 	if(!WriteDataElementChar(pcCurrent,0x0028,0x1051,"DS",nCountOfValue,(char*)szWindowWidth.operator LPCTSTR()))
// 	{
// 		return false;
// 	}
// 	/**********************************************/
// 
// 	//Write Group Length
// 	if(!WriteDataElementNum(pcMark,0x0028,0x0000,"UL",0x04,pcCurrent-pcMark-12))
// 	{
// 		return false;
// 	}
// 
// 	///////////////////////////////////////////////////////////////////////////////
// 	//(0029,xxxx)
// 
// 	//Group Length Mark
// 	pcMark = pcCurrent;
// 	pcCurrent += 12;
// 	//							(0029,0010) Private Creator ID LO 1
// 	if(!WriteDataElementChar(pcCurrent,0x0029,0x0010,"LO",14,"BIMRI_IMPS_01"))
// 	{
// 		return false;
// 	}
// 	//Image_IntensityMean		*(0029,1001) Mean Intensity Of Image SS 1
// 	if(!WriteDataElementNum(pcCurrent,0x0029,0x1001,"SS",0x02,imageHeader.imageField.IntensityMean))
// 	{
// 		return false;
// 	}
// 	//Image_IntensityDev		*(0029,1002) Standard Deviation of Intensity Of Image SS1
// 	if(!WriteDataElementNum(pcCurrent,0x0029,0x1002,"SS",0x02,imageHeader.imageField.IntensityDev))
// 	{
// 		return false;
// 	}
// 	
// 	//Write Group Length
// 	if(!WriteDataElementNum(pcMark,0x0029,0x0000,"UL",0x04,pcCurrent-pcMark-12))
// 	{
// 		return false;
// 	}
// 
// 	///////////////////////////////////////////////////////////////////////////////
// 	//(0043,xxxx)
// 
// 	//Group Length Mark
// 	pcMark = pcCurrent;
// 	pcCurrent += 12;
// 	//							(0043,0010) Private Creator ID LO 1
// 	if(!WriteDataElementChar(pcCurrent,0x0043,0x0010,"LO",14,"BIMRI_PARM_01"))
// 	{
// 		return false;
// 	}
// 
// 	//Series_GradientShimX		*(0043,1001) GradientShimX SL 1
// 	if(!WriteDataElementNum(pcCurrent,0x0043,0x1001,"SL",0x04,imageHeader.seriesField.GradientShimX))
// 	{
// 		return false;
// 	}
// 	//Series_GradientShimY		*(0043,1002) GradientShimY SL 1
// 	if(!WriteDataElementNum(pcCurrent,0x0043,0x1002,"SL",0x04,imageHeader.seriesField.GradientShimY))
// 	{
// 		return false;
// 	}
// 	//Series_GradientShimZ		*(0043,1003) GradientShimZ SL 1
// 	if(!WriteDataElementNum(pcCurrent,0x0043,0x1003,"SL",0x04,imageHeader.seriesField.GradientShimZ))
// 	{
// 		return false;
// 	}
// 	
// 	//Series_DigFilterType		*(0043,1010) Digital Filter Type SS 1
// 	if(!WriteDataElementNum(pcCurrent,0x0043,0x1010,"SS",0x02,imageHeader.seriesField.DigFilterType))
// 	{
// 		return false;
// 	}
// 	//Series_DigFilterPar[8]	*(0043,1011) Digital Filter Parameters 	UN 1 ??float[8]
// 	if(!WriteDataElementChar(pcCurrent,0x0043,0x1011,"UN",0x08,imageHeader.seriesField.DigFilterPar))
// 	{
// 		return false;
// 	}
// 	//Series_WindowLevel		*(0043,1012) Window Level SS 1
// 	if(!WriteDataElementNum(pcCurrent,0x0043,0x1012,"SS",0x02,imageHeader.seriesField.WindowLevel))
// 	{
// 		return false;
// 	}
// 	//Series_WindowWidth		*(0043,1013) Window Width SS 1	
// 	if(!WriteDataElementNum(pcCurrent,0x0043,0x1013,"SS",0x02,imageHeader.seriesField.WindowWidth))
// 	{
// 		return false;
// 	}
// 	//image_WindowLevel		*(0043,1014) Window Level SS 1
// 	if(!WriteDataElementNum(pcCurrent,0x0043,0x1014,"SS",0x02,imageHeader.imageField.WindowLevel))
// 	{
// 		return false;
// 	}
// 	//image_WindowWidth		*(0043,1015) Window Width SS 1	
// 	if(!WriteDataElementNum(pcCurrent,0x0043,0x1015,"SS",0x02,imageHeader.imageField.WindowWidth))
// 	{
// 		return false;
// 	}
// 	
// 	//Series_FlowCompensation	*(0043,1020) Flow Compensation SS 1
// 	if(!WriteDataElementNum(pcCurrent,0x0043,0x1020,"SS",0x02,(short)imageHeader.seriesField.FlowCompensation))
// 	{
// 		return false;
// 	}
// 	//RespiratoryTrigger	*(0043,1021) Respiratory Trigger UN 1
// //	if(!WriteDataElementNum(pcCurrent,0x0043,0x1021,"UN",
// //		sizeof(imageHeader.seriesField.RespiratoryTrigger),
// //		imageHeader.seriesField.RespiratoryTrigger))
// //	{
// //		return false;
// //	}
// 	//Series_PompNumber		*(0043,1022) Pomp Number US 1
// 	if(!WriteDataElementNum(pcCurrent,0x0043,0x1022,"US",0x02,(short)imageHeader.seriesField.PompNumber))
// 	{
// 		return false;
// 	}
// 	//Series_NumOfAngioImages	*(0043,1023) Num Of Angio Images US 1
// 	if(!WriteDataElementNum(pcCurrent,0x0043,0x1023,"US",0x02,(short)imageHeader.seriesField.NumOfAngioImages))
// 	{
// 		return false;
// 	}
// 	//Series_HalfKSpaceRatio		*(0043,1024) Ratio Of Half Fourier Imaging FL 1 
// 	if(!WriteDataElementNum(pcCurrent,0x0043,0x1024,"FL",0x04,imageHeader.seriesField.HalfKSpaceRatio))
// 	{
// 		return false;
// 	}
// 
// 	//Write Group Length
// 	if(!WriteDataElementNum(pcMark,0x0043,0x0000,"UL",0x04,pcCurrent-pcMark-12))
// 	{
// 		return false;
// 	}
// 
// 	////////////////////////////////////////////////////////////////////////////////
// 	//(7FE0,xxxx)
// 	//Group Length Mark
// 	pcMark = pcCurrent;
// 	pcCurrent += 12;
// 	int nXRes = imageHeader.seriesField.ResolutionX ;
// 	int nYRes = imageHeader.seriesField.ResolutionY ;
// 	//*					(7FE0,0010) Pixel Data OW or OB 1
// 	imageHeader.headInfo.DataMatrixSize=nXRes*nYRes*sizeof(WORD);
// 	WORD *buffertemp = new WORD[/*imageHeader.headInfo.DataMatrixSize/2*/nXRes*nYRes];
// 	if(buffertemp == NULL)
// 	{
// 		return false;
// 	}
// 	WORD *imagedata = buffertemp;
// 	
// 	/*imageHeader.seriesField.*/
// /*
// 	for(i=0; i<nXRes; i++)
// 	{
// 		for(int j=0; j<nYRes; j++)
// 		{
// 			// *imagedata=BIImageData[j*imageHeader.seriesField.ResolutionX+i];
// 			// *imagedata=BIImageData[j*imageHeader.seriesField.ResolutionX+i];
// 			*imagedata = psImageData[(nYRes-j-1)*nXRes + nXRes-i-1];  // Rodger: remove the transposition
// 			// *imagedata = psImageData[(nYRes-j-1)*nXRes + nXRes];		// lwz: remove the transposition
// 			imagedata++;
// 		}
// 	}
// */
// 	for(i=0; i<nYRes; i++)
// 	{
// 		for(int j=0; j<nXRes; j++)
// 		{
// 			*imagedata=psImageData[i*nXRes+j];
// 			// *imagedata=BIImageData[j*imageHeader.seriesField.ResolutionX+i];
// 			//Cur//*imagedata = psImageData[(nYRes-j-1)*nXRes + nXRes-i-1];  // Rodger: remove the transposition
// 			//*imagedata = psImageData[(nYRes-j-1)*nXRes + nXRes];		// lwz: remove the transposition
// 			imagedata++;
// 		}
// 	}
// 	imagedata = buffertemp;
// 	WriteImageData(pcCurrent,"OW",imageHeader.headInfo.DataMatrixSize/2,imagedata);
// 	delete[] buffertemp;
// 
// 	//Write Group Length
// 	if(!WriteDataElementNum(pcMark,0x7FE0,0x0000,"UL",0x04,pcCurrent-pcMark-12))
// 	{
// 		return false;
// 	}
// 
// 	nDicomDataLen = pcCurrent - pcDicomData; 
// 	return true;
// }
// BOOL CExportDataTask::ExportStudyToBMP(CString szImageRootPath, CString szStudyID, CString strDestFilePathName, BOOL nSaveMed)
// {
// 	if(strDestFilePathName.Right(1)=="\\")
// 	{
// 		strDestFilePathName=strDestFilePathName.Left(strDestFilePathName.GetLength()-1);
// 
// 	}
// 
// 	//Modified by Tom, --2008.07.10
// 	int  nF = CheckDiskSpaceAndEnWrite(strDestFilePathName,50);
// 	if(nF != 0)
// 	{
// 		//AfxMessageBox("Disk Error!\nCan't export series!");
// 		//CLang::GetHandle().ShowMessage("");
// 		switch (nF)
// 		{
// 		case -1:
// 			CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("IMAGE_EXPORT_MSG_PATH_CANNOT_REC"));
// 			break ;
// 		case -2:
// 			CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("IMAGE_EXPORT_MSG_CANNOT_GET_ENOUGH_SPACE"));
// 			break ;
// 		case -3:
// 		case -4:
// 		default:
// 			CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("IMAGE_EXPORT_MSG_DISK_ERROR"));
// 			break ;
// 		}
// //		CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("IMAGE_EXPORT_MSG_DISK_ERROR"));
// 		return FALSE;
// 	}
//     //当前的Study ID
// 	std::string pStrData=(char*)szStudyID.operator LPCTSTR();
// 	
// //	CStudy* pStudy = CStorageManager::GetHandle().GetStudy(pStrData,TRUE);
// //	if(!pStudy)
// //	{
// //		return FALSE;
// //	}
// // 	CStudy* pStudy = CStorageManager::GetHandle().GetStudy(pStrData/*,TRUE*/);
// // 	BOOL nRet=FALSE;
// // 	if(!pStudy)//pStudy==NULL
// // 	{
// // 		nRet=TRUE;
// // 
// // 	}
// // 	if(nRet==TRUE)
// // 	{
// // 		pStudy = CStorageManager::GetHandle().GetStudy(pStrData,TRUE);
// // 
// // 	}
// // 	if(!pStudy)
// // 	{
// // 		return FALSE;
// // 	}
// // 	int nCountOfSeries=pStudy->GetCountOfSeries();
// // 	int nIndex=0;
// // 	for(int i=0;nIndex<nCountOfSeries;i++)
// // 	{
// // 		CSeries*pSeries=pStudy->GetSeries(i);
// // 		if(!pSeries)
// // 		{
// // 			continue;
// // 		}
// // 		nIndex++;
// // 
// // 		int nCountOfImage=pSeries->GetCountOfImage();
// // 		for(int j=0;j<nCountOfImage;j++)
// // 		{
// // 			CImage *pImage=pSeries->GetImage(j);
// // 			if(!pImage)
// // 			{
// // 				continue;
// // 			}
// // 			//转化
// // 			/////////////////////////////////////////////////////
// // 			CSize nImgSize=pImage->GetSize();
// // 			CImageViewData* pImageViewData = CViewDataManager::GetHandle().GetImageViewData(pImage);
// // 			ASSERT(pImageViewData);
// // 			CProcessParams params = pImageViewData->ProcessParams();
// // 			int nImageSize = CConfigManager::GetHandle().GetFilmingConfig().m_nImageSize;
// // 			int nWidth = nImageSize;//pImageData->GetWidth();
// // 			int nHeight = nImageSize;//pImageData->GetHeight();
// // 			params.m_sizeBitmap.cx = nWidth;
// // 			params.m_sizeBitmap.cy = nHeight;
// // 			CDC dcPrint;
// // 			//memcpy(nSaveCtrlInfo,nControlInfo,4*sizeof(int));
// // 			
// // 			dcPrint.CreateDC("DISPLAY", NULL, NULL, NULL);
// // 			dcPrint.SetMapMode(MM_TEXT);
// // 			BYTE* pData = CFilmingDlg::OnGetPrintDataBYTEPrint(dcPrint, pImage, nWidth, nHeight,FALSE, i);
// // 			if(!pData)
// // 			{
// // 				continue;
// // 			}
// // 			BYTE *pUsingData;
// // 			pUsingData=new BYTE[nHeight*nWidth];
// // 			memset(pUsingData,0,sizeof(BYTE)*nHeight*nWidth);
// // 			int nShortSize=nHeight*nWidth;
// // 			for(int m=0;m<nHeight;m++)
// // 			{
// // 				for(int n=0;n<nWidth;n++)
// // 				{
// // 					int nTemp=pData[(m*nWidth+n)];
// // 					pUsingData[((nHeight-1-m)*nWidth+n)]=(BYTE)nTemp;
// // 					
// // 					
// // 				}
// // 			}
// // 			/////////////////////////////////////////////////////
// // 			////////////////////////////////////////////////////////////////////
// // 			//////////////////////////////////////////////////////////
// // 			CString szImagePath;
// // 			szImagePath.Format("%s\\%s\\%d\\%d.img",szImageRootPath,szStudyID,i,j);
// // 			CString szSaveName;
// // 			if(nSaveMed==FALSE)
// // 			{
// // 				szSaveName.Format("%s\\%s_%d_%d.bmp",strDestFilePathName,szStudyID,i,j);
// // 			}
// // 			else if(nSaveMed==TRUE)
// // 			{
// // 				szSaveName.Format("%s\\%s\\%d\\%d.bmp",strDestFilePathName,szStudyID,i,j);
// // 				CString szPath;
// // 				szPath.Format("%s\\%s\\%d\\",strDestFilePathName,szStudyID,i);
// // 				BOOL nRef=CheckAndCreateDir(szPath);
// // 				if(nRef==FALSE)
// // 				{
// // 					continue;
// // 				}
// // 
// // 			}
// // 			char*pStrBmpName=(char*)szSaveName.operator LPCTSTR();
// // 			SaveImageDataToBmp(pUsingData,nWidth,nHeight,1,pStrBmpName);
// // 			if(pUsingData)
// // 			{
// // 				delete []pUsingData;
// // 
// // 			}
// // 			if(pData)
// // 			{
// // 				delete []pData;
// // 
// // 			}
// // 			///////////////////////////////////////////////
// // 		}
// // 		/** [SHCH-15-12-2007  BUG-TITLE:XABW/CX-31-11-0078] **/
// // 		int nPos=oProgressDlg.m_Progress.GetPos();
// // 		if(nPos<80)
// // 		{
// // 			oProgressDlg.StepIt();
// // 
// // 		}
// // 		/** [SHCH-15-12-2007  BUG-TITLE:XABW/CX-31-11-0078] **/
// // 	}
// // //	BOOL nRet= CStorageManager::GetHandle().CloseStudy(pStudy);
// // //	if(nRet==FALSE)
// // //	{
// // //		return FALSE;
// // //
// // //	}
// // 	if(nRet==TRUE)
// // 	{
// // 		BOOL tRes= CStorageManager::GetHandle().CloseStudy(pStudy);
// // 		if(tRes==FALSE)
// // 		{
// // 			return FALSE;
// // 
// // 		}
// // 
// // 	}
// 
// 	return true ;
// 
// }
// //////////////////////////////////////////////////////////////////////////
// /*
// 函数说明：保存图像数据为BMP图像
// 参数说明：
// 	1) unsigned char *pDest :　[in]图像数据
// 	2) int w				:　[in]图像宽度
// 	3) int h				:  [in]图像高度
// 	4) char *pFileName      :  [in]图象文件名
// 返回值：
// 　　TRUE　保存成功，　FALSE　保存失败；
// //这个存取函数是基于列优先存储的　
// */
// //////////////////////////////////////////////////////////////////////////
// bool CExportDataTask::SaveImageDataToBmp(unsigned char *pDest,
// 						int w,
// 						int h,
// 						int format,
// 						char *pFileName)
// {
// 
// 	bool bResult  = true;
// 	int m_nX = 0;
// 	int m_nY = 0;
// 	m_nX = w;
// 	m_nY = h;
// 	int i = 0;
// 	//////////////////////////////////////////////////////////////////////////
// 	//写bmp文件;
// 	BITMAPFILEHEADER bmfHdr; //定义文件头
// 	BITMAPINFOHEADER bmiHdr; //定义信息头
// 	RGBQUAD rgbQuad[256];    //定义调色板
// 	//对信息头进行赋值
// 	bmiHdr.biSize = sizeof(BITMAPINFOHEADER);
// 	bmiHdr.biWidth = m_nX;
// 	bmiHdr.biHeight = m_nY;
// 	bmiHdr.biPlanes = 1;
// 	if(format == 3)
// 		bmiHdr.biBitCount = 24;
//     else if(format == 1)
//         bmiHdr.biBitCount = 8;
// 	else if(format == 16)
// 		bmiHdr.biBitCount = 16;
// 	else if(format == 4)
// 		bmiHdr.biBitCount = 32;
// 
// 	bmiHdr.biCompression = BI_RGB;
// 	bmiHdr.biSizeImage = m_nX * m_nY * format;
// 	bmiHdr.biXPelsPerMeter = 0;
// 	bmiHdr.biYPelsPerMeter = 0;
// 	bmiHdr.biClrUsed = 0;
// 	bmiHdr.biClrImportant = 0;
// 	//对调色板进行赋值
// 	for(i=0; i<256; i++)
// 	{
// 		rgbQuad[i].rgbBlue = (BYTE)i;
// 		rgbQuad[i].rgbGreen = (BYTE)i;
// 		rgbQuad[i].rgbRed = (BYTE)i;
// 		rgbQuad[i].rgbReserved = 0;
// 	}
// 
// 	
// 	//对文件头进行赋值
// 	bmfHdr.bfType = (WORD)0x4D42;
// 	bmfHdr.bfSize=(DWORD)(sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*256 + m_nX*m_nY*format);
// 	bmfHdr.bfReserved1 = 0;
// 	bmfHdr.bfReserved2 = 0;
// 	bmfHdr.bfOffBits=(DWORD)(sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*256);
// 	
// 	//////////////////////////////////////////////////////////////////////////
// 	//保存文件
// 	CString strBmpFileName;
// 	strBmpFileName.Format("%s",pFileName);
// 	
//     CFile fp;
// 	fp.Open(strBmpFileName,CFile::modeCreate|CFile::modeWrite);
// 	fp.Write((LPSTR)&bmfHdr,sizeof(BITMAPFILEHEADER));				//写文件头
// 	fp.Write((LPSTR)&bmiHdr,sizeof(BITMAPINFOHEADER));				//写信息头
// 	fp.Write((LPSTR)rgbQuad,sizeof(RGBQUAD)*256);					//写调色板
// 	fp.Write(pDest,m_nX*m_nY*format);										//写数据
// 	fp.Close();	
// 	
// 	bResult = true;
//     return bResult;
// }
// bool CExportDataTask::ReadImageFileHeader(const std::string& strFilename, CBIImageHeader& imageHeader)
// {
// 	/*using namespace std;*/
// 
// //	ifstream inFile(strFilename.c_str(), std::ios::in | std::ios::binary);	
// //    if (!inFile)
// //	{
// //        return NULL;
// //	}
// 	//inFile.seekg(0);
// //	inFile.s
// //	
// 	//inFile.seekg(0, std::ios::seek_dir::beg);
// 	//inFile.seekg( 0,std::ios::seekdir::beg);
// 	memset(&imageHeader,0,sizeof(CBIImageHeader));
//     CFile file;
// 	if (!file.Open(strFilename.c_str(),CFile::modeRead))
// 	{
// 		return false;
// 	}
// 	file.Read((void*)&imageHeader,sizeof(CBIImageHeader));
// 	file.Close();
// //
// //	//
// //	LONG nHeahAddr, nGapAddr, nOffsetAddr;
// //	CString sHeadAddr, sGapAddr;
// //	sHeadAddr.Format( "%ld", &imageHeader.seriesField );
// //	nHeahAddr = atoi( sHeadAddr );
// //
// //	sGapAddr.Format( "%ld", &imageHeader.seriesField.SliceGap );
// //	nGapAddr = atoi( sGapAddr );
// //	nOffsetAddr = nGapAddr - nHeahAddr;
// //
// //    inFile.read( (char*)(&imageHeader.seriesField), nOffsetAddr );
// //	
// //	// read SliceGap by image's Version {BEGIN}
// //	int nGapLen = 0;
// //	if ( imageHeader.headInfo.Version == (int(1) << 16 + 0) )
// //	{
// //		U2 SliceGap;
// //		inFile.read((char*)(&SliceGap), sizeof(U2));
// //		imageHeader.seriesField.SliceGap = SliceGap;
// //		nGapLen = sizeof(U2);
// //	}
// //	else if ( imageHeader.headInfo.Version == (int(1) << 16 + 1) )
// //	{
// //		F4 SliceGap;
// //		inFile.read((char*)(&SliceGap), sizeof(F4));
// //		imageHeader.seriesField.SliceGap = SliceGap;
// //		nGapLen = sizeof(F4);
// //	}
// //	else
// //	{
// //		//AfxMessageBox( "Invalid image file !" );
// //		return false;
// //	}
// //	// read SliceGap by image's Version {END}
// //	
// //	if ( imageHeader.headInfo.Version == (int(1) << 16 + 0) )
// //	{
// //		inFile.seekg( 2/*,ios_base::cur*//*, std::ios::seekdir::cur*/ );
// //	}
// //	
// //    inFile.read( (char*)(&imageHeader.seriesField.EchoTime), 
// //		  sizeof(imageHeader.seriesField) - nOffsetAddr - 1/* - nGapLen*/ 
// //		+ sizeof(imageHeader.scanField)
// //		+ sizeof(imageHeader.imageField) );
// //	//int nt1100=200;
// 	return TRUE;
// 	
// }
// /*********zyh add 2008.2.27*********/
// #include "E:\VImage\Include\DCMINT.h"
// /**********************************************/
// 
// /********************************************
// 函数名称: 
// 描    述: 增加生成dicomdir功能
// 输    入: 无
// 输    出: 无
// 返    回: 无
// 其    它: 无
// 修改历史:
//        <修改人> <时间>     <版本 >   <描述>
//     1. 朱映华    2008.2.27 v1.1      增加生成dicomdir功能,并优化函数，修改函数内存泄露问题
// *********************************************/
// /*********zyh add 2008.2.27*********/
// #include "imagehlp.h"
// #pragma   comment(lib,"imagehlp.lib")
// /**********************************************/
// long CExportDataTask::ExportSeriesToDICOM(CSeries *pSeries, CString szImgRootPath, CString strDestFilePathName, BOOL nSaveMed, BOOL bCreateDicomDir/* = FALSE*/)
// {
// 	int nCount = 0;
// 	int nCountOfImage=pSeries->GetCountOfImage();
// 	CStudy *pStudy=pSeries->GetStudy();
// 	CString szStudyID=pStudy->StudyParams().Id;
// 	int      nFileCount = 0;
// 	char    *pcDicomData   = NULL;
// 	int      nDicomDataLen = 0;
// 	char m_pImagePath[256];
// 	pcDicomData=new char[_MAX_BUFFER_];
// 	
// 	if(!pcDicomData)
// 		return nCount;
// 
// 	/*********zyh add 2008.2.27*********/
// 	char szDicomDirFileName[MAX_PATH];
// 	char szTmpPath[MAX_PATH];
// 	if(bCreateDicomDir)
// 		sprintf(szDicomDirFileName, "%s\\DICOMDIR", strDestFilePathName.GetBuffer(strDestFilePathName.GetLength()));
// 	/**********************************************/
// 	
// 	
// // 	for(int j=0;j<nCountOfImage;j++)
// // 	{
// // 		CImage *pImageData=pSeries->GetImage(j);
// // 		if(!pImageData)
// // 			continue;
// // 
// // 		//转化
// // 		short*p12BitData=pImageData->GetBuffer();
// // 		CBIImageHeader imageHeader;
// // 		CString szImagePath;
// // 		szImagePath.Format("%s%s\\%d\\%d.img", szImgRootPath, szStudyID, (int)pSeries->SeriesParams().Id, j);
// // 		
// // 		
// // 		BOOL nRet=PathFileExists(szImagePath);
// // 		if(nRet==FALSE)
// // 		{
// // 			continue;
// // 		}
// // 		memset(m_pImagePath,0,sizeof(char)*256);
// // 		memcpy(m_pImagePath,szImagePath,szImagePath.GetLength());
// // 		//CImage::ReadImageFile();
// // 		ReadImageFileHeader(std::string(m_pImagePath),imageHeader);
// // 		///////////////////////////////////////////////////////////////
// // 		CSize nImgSize=pImageData->GetSize();
// // 		CImageViewData* pImageViewData = CViewDataManager::GetHandle().GetImageViewData(pImageData);
// // 		CSeriesViewData* pSrViewData =  CViewDataManager::GetHandle().GetSeriesViewData(pImageData);
// // 		//CProcessParams params = pSrViewData->m_ProcessParams;
// // 		ASSERT(pImageViewData);
// // 		CProcessParams params = pSrViewData->m_ProcessParams/*pImageViewData->ProcessParams()*/;
// // 		int nImageSize = CConfigManager::GetHandle().GetFilmingConfig().m_nImageSize;
// // 		int nWidth = nImageSize/*pImageData->GetWidth()*/;
// // 		int nHeight = nImageSize/*pImageData->GetHeight()*/;
// // 		params.m_sizeBitmap.cx = nWidth;
// // 		params.m_sizeBitmap.cy = nHeight;
// // 		CImageViewData viewData(pImageData);
// // 
// // 		///////////////////////////////////////////////////////////////////////////////
// // 		CBitmap*pBitmapData=viewData.GetZoomedBitmap(params, false);
// // 		if(!pBitmapData)
// // 		{
// // 			continue;
// // 		}
// // 
// // 		BITMAP nBitmap;
// // 		pBitmapData->GetBitmap(&nBitmap);
// // 		int nH=nBitmap.bmHeight;
// // 		int nW=nBitmap.bmWidth;
// // 		int nF=nBitmap.bmBitsPixel;
// // 		BYTE*pData;
// // 		pData=new BYTE[nH*nW*nF/8];
// // 		memset(pData,0,nH*nW*nF/8);
// // 		pBitmapData->GetBitmapBits(nH*nW*nF/8,pData);
// // 		short *pUsingData;
// // 		pUsingData=new short[nH*nW];
// // 		memset(pUsingData,0,sizeof(short)*nH*nW);
// // 		int nShortSize=nH*nW;
// // 		for(int i=0;i<nShortSize;i++)
// // 		{
// // 			int nTemp=pData[4*i]<<4;
// // 			pUsingData[i]=(short)nTemp;
// // 			
// // 		}
// // 		///////////////////////////////////////////////////////////////////
// // //        imageHeader.seriesField.ResolutionX=pImageData->GetWidth();
// // //		imageHeader.seriesField.ResolutionY=pImageData->GetHeight();
// // //		///////////////////////////////////////////////////////////////
// // //		
// // //		memset(pcDicomData,0,sizeof(char)*_MAX_BUFFER_);
// // 		imageHeader.seriesField.ResolutionX=nW;
// // 		imageHeader.seriesField.ResolutionY=nH;
// // 		int tInfo=imageHeader.headInfo.DataMatrixSize;
// // 		//CLayoutWnd* pLayout = theApp.m_pMriView->m_pdlgImagesPage->GetLayoutWnd();
// // 		double nAngle = params.m_dAngle;
// // 		BOOL nVerFlip=params.m_bVerticalFlip;
// // 		BOOL nHorFilp=params.m_bHorizontalFlip;
// // 		
// // 
// // 		//读取其它信息。
// // 		CScanViewData* pScanData = 
// // 		CViewDataManager::GetHandle().GetScanViewData(pImageData);
// // 
// // 		CString sDesc = pScanData->GetThisScanDecs();
// // 		 
// // 		if ( sDesc.Find( "MIP", 0 ) == -1 )
// // 		{
// // 			//RFInhomoCorrection( pTask->m_pScan );
// // 			//GradientCorrection( pTask->m_pScan );
// // 		}
// // 		else
// // 		{
// // 			pScanData->UpdateMIPImagePlane(pImageData/*,40m_pImage->GetScan()->GetSeries()->GetCountOfImage()*/);
// // 			pScanData->UpdateOrientations();
// // 			if(nCountOfImage!=20)
// // 			{
// // 				nCountOfImage=20;
// // 
// // 			}
// // 			 
// // 			_ORIENTATIONS_VECTOR_ nThisMipOrientation=pScanData->GetImageRealOrientationAndPos(pImageData,nCountOfImage);
// // 			
// // 			//Modified by Tom, --2008.07.10
// // 			imageHeader.imageField.fFreqDirZ = (float)nThisMipOrientation.m_nReadOrientation.z;
// // 			imageHeader.imageField.fFreqDirX = (float)nThisMipOrientation.m_nReadOrientation.x;
// // 			imageHeader.imageField.fFreqDirY = (float)nThisMipOrientation.m_nReadOrientation.y;
// // 			imageHeader.imageField.fPhaseDirZ= (float)nThisMipOrientation.m_nPhaseOrientation.z;
// // 			imageHeader.imageField.fPhaseDirX= (float)nThisMipOrientation.m_nPhaseOrientation.x;
// // 			imageHeader.imageField.fPhaseDirY= (float)nThisMipOrientation.m_nPhaseOrientation.y;
// // 
// // 
// // 		}
// // 		
// // 		
// // 		bool bFlags=ConvertXB2Dicom(imageHeader,nAngle,nVerFlip,nHorFilp,pUsingData,pcDicomData,nDicomDataLen);
// // 		if (!bFlags)
// // 		{
// // 			delete [] pData;
// // 			delete [] pUsingData;
// // 			delete[] pcDicomData;
// // 			return FALSE ;
// // 		}
// // 		CString szSaveName;
// // 		/*********zyh add 2008.2.27*********/
// // 		if(bCreateDicomDir)
// // 		{
// // 			sprintf(szTmpPath, "%s\\%s\\%d\\", strDestFilePathName,szStudyID,(int)pSeries->SeriesParams().Id);
// // 			MakeSureDirectoryPathExists(szTmpPath);
// // 		}
// // 		/**********************************************/
// // 		
// // 		if(nSaveMed==FALSE)
// // 		{
// // 			/*********zyh add 2008.4.18*********/
// // 			//szSaveName.Format("%s\\%s_%d_%d.dcm",strDestFilePathName,szStudyID,(int)pSeries->SeriesParams().Id,j);
// // 			szSaveName.Format("%s\\%s_%02d_%03d.dcm",strDestFilePathName,szStudyID,(int)pSeries->SeriesParams().Id,j + 1);
// // 			/**********************************************/
// // 		}
// // 		else if(nSaveMed==TRUE)
// // 		{
// // 			szSaveName.Format("%s\\%s\\%d\\%d.dcm",strDestFilePathName,szStudyID,(int)pSeries->SeriesParams().Id,j + 1);
// // 			CString szPath;
// // 			szPath.Format("%s\\%s\\%d\\",strDestFilePathName,szStudyID,(int)pSeries->SeriesParams().Id);
// // 			BOOL nRef=CheckAndCreateDir(szPath);
// // 			if(nRef==FALSE)
// // 			{
// // 				continue;
// // 			}
// // 
// // 		}
// // 		CFile file;
// // 		//Added by Tom, --2008.07.10
// // 		if (file.Open(szSaveName,CFile::modeCreate | CFile::modeWrite))
// // 		{
// // 			file.Write(pcDicomData,nDicomDataLen) ;
// // 			nDicomDataLen = 0 ;
// // 			file.Close();
// // 			nCount++;
// // 
// // 			if(bCreateDicomDir)
// // 			{
// // 				try
// // 				{
// // 					AddToDCMDir(szDicomDirFileName, szSaveName.GetBuffer(szSaveName.GetLength()));
// // 				}
// // 				catch (...) 
// // 				{
// // 					;
// // 				}
// // 			}
// // 		}
// // 
// // 		delete [] pData;
// // 		delete [] pUsingData;
// // 		
// // 		//BOOL nRet=ReadImageFileHeader(std::string(m_pImagePath),imageHeader);
// // 	}
// // 	if(pcDicomData)
// // 	{
// // 		delete[] pcDicomData;
// // 	}
// // 	return nCount;
// return 0;
// }
// 
// BOOL CExportDataTask::ExportStudyToJPEG(CString szImageRootPath,CString szStudyID,CString strDestFilePathName,BOOL nSaveMed)
// {
// 	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// // 	if(strDestFilePathName.Right(1)=="\\")
// // 	{
// // 		strDestFilePathName=strDestFilePathName.Left(strDestFilePathName.GetLength()-1);
// // 
// // 	}
// // 
// // 	//Modified by Tom, --2008.07.10
// // 	int  nF = CheckDiskSpaceAndEnWrite(strDestFilePathName,50);
// // 	if(nF != 0)
// // 	{
// // 		//AfxMessageBox("Disk Error!\nCan't export series!");
// // 		//CLang::GetHandle().ShowMessage("");
// // 		switch (nF)
// // 		{
// // 		case -1:
// // 			CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("IMAGE_EXPORT_MSG_PATH_CANNOT_REC"));
// // 			break ;
// // 		case -2:
// // 			CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("IMAGE_EXPORT_MSG_CANNOT_GET_ENOUGH_SPACE"));
// // 			break ;
// // 		case -3:
// // 		case -4:
// // 		default:
// // 			CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("IMAGE_EXPORT_MSG_DISK_ERROR"));
// // 			break ;
// // 		}
// // //		CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("IMAGE_EXPORT_MSG_DISK_ERROR"));
// // 		return FALSE;
// // 	}
// // 
// //     //当前的Study ID
// // 	std::string pStrData=(char*)szStudyID.operator LPCTSTR();
// // 	///////////////////////////////////////////////////////////////////////////////////////////
// // 	CStudy* pStudy = CStorageManager::GetHandle().GetStudy(pStrData/*,TRUE*/);
// // 	BOOL nRet=FALSE;
// // 	if(!pStudy)//pStudy==NULL
// // 	{
// // 		nRet=TRUE;
// // 
// // 	}
// // 	if(nRet==TRUE)
// // 	{
// // 		pStudy = CStorageManager::GetHandle().GetStudy(pStrData,TRUE);
// // 
// // 	}
// // 	if(!pStudy)
// // 	{
// // 		return FALSE;
// // 	}
// // 	int nCountOfSeries=pStudy->GetCountOfSeries();
// // 	int nIndex=0;
// // 	for(int i=0;i<nCountOfSeries+1;i++)
// // 	{
// // 		CSeries*pSeries=pStudy->GetSeries(i);
// // 		if(!pSeries)
// // 		{
// // 			continue;
// // 		}
// // 		int nCountOfImage=pSeries->GetCountOfImage();
// // 		for(int j=0;j<nCountOfImage;j++)
// // 		{
// // 			CImage *pImage=pSeries->GetImage(j);
// // 			if(!pImage)
// // 			{
// // 				continue;
// // 			}
// // 			//转化
// // 			/////////////////////////////////////////////////////
// // 			CSize nImgSize=pImage->GetSize();
// // 			CImageViewData* pImageViewData = CViewDataManager::GetHandle().GetImageViewData(pImage);
// // 			ASSERT(pImageViewData);
// // 			CProcessParams params = pImageViewData->ProcessParams();
// // 			int nImageSize = CConfigManager::GetHandle().GetFilmingConfig().m_nImageSize;
// // 			int nWidth = nImageSize;//pImageData->GetWidth();
// // 			int nHeight = nImageSize;//pImageData->GetHeight();
// // 			params.m_sizeBitmap.cx = nWidth;
// // 			params.m_sizeBitmap.cy = nHeight;
// // 			CDC dcPrint;
// // 			//memcpy(nSaveCtrlInfo,nControlInfo,4*sizeof(int));
// // 			dcPrint.CreateDC("DISPLAY", NULL, NULL, NULL);
// // 			dcPrint.SetMapMode(MM_TEXT);
// // 			BYTE* pData = CFilmingDlg::OnGetPrintDataBYTEPrint(dcPrint, pImage, nWidth, nHeight,FALSE, j);
// // 			if(!pData)
// // 			{
// // 				continue;
// // 			}
// // 			BYTE *pUsingData;
// // 			pUsingData=new BYTE[nHeight*nWidth*3];
// // 			memset(pUsingData,0,sizeof(BYTE)*nHeight*nWidth);
// // 			int nShortSize=nHeight*nWidth;
// // 			for(int m=0;m<nHeight;m++)
// // 			{
// // 				for(int n=0;n<nWidth;n++)
// // 				{
// // 					int nTemp=pData[(m*nWidth+n)];
// // 					int nDesIndex=((nHeight-1-m)*nWidth+n)*3;
// // 					pUsingData[nDesIndex]=(BYTE)nTemp;
// // 					pUsingData[nDesIndex+1]=(BYTE)nTemp;
// // 					pUsingData[nDesIndex+2]=(BYTE)nTemp;
// // 					
// // 					
// // 				}
// // 			}
// // 			/////////////////////////////////////////////////////
// // 			////////////////////////////////////////////////////////////////////
// // 			//////////////////////////////////////////////////////////
// // //			CString szImagePath;
// // //			szImagePath.Format("%s\\%s\\%d\\%d.img",szImageRootPath,szStudyID,i,j);
// // 			CString szSaveName;
// // 			if(nSaveMed==FALSE)
// // 			{
// // 				szSaveName.Format("%s\\%s_%d_%d.jpg",strDestFilePathName,szStudyID,i,j);
// // 			}
// // 			else if(nSaveMed==TRUE)
// // 			{
// // 				szSaveName.Format("%s\\%s\\%d\\%d.jpg",strDestFilePathName,szStudyID,i,j);
// // 				CString szPath;
// // 				szPath.Format("%s\\%s\\%d\\",strDestFilePathName,szStudyID,i);
// // 				BOOL nRef=CheckAndCreateDir(szPath);
// // 				if(nRef==FALSE)
// // 				{
// // 					continue;
// // 				}
// // 
// // 			}
// // 			char*pStrBmpName=(char*)szSaveName.operator LPCTSTR();
// // 			////////////////////////////////////////////////////////////////////////////////
// // 			//存储成JPEG图像
// // 			JpegFile::VertFlipBuf(pUsingData, nWidth*3 , nHeight);
// // 
// // 			// we swap red and blue for display, undo that.
// // 			JpegFile::BGRFromRGB(pUsingData, nWidth, nHeight);
// // 
// // 
// // 			// save RGB packed buffer to JPG
// // 			BOOL ok=JpegFile::RGBToJpegFile(szSaveName, 
// // 											pUsingData,
// // 											nWidth,
// // 											nHeight,
// // 											TRUE, 
// // 											80);			// quality value 1-100.
// // 			////////////////////////////////////////////////////////////////////////////////
// // //			SaveImageDataToBmp(pUsingData,nWidth,nHeight,1,pStrBmpName);
// // 			if(pUsingData)
// // 			{
// // 				delete []pUsingData;
// // 
// // 			}
// // 			if(pData)
// // 			{
// // 				delete []pData;
// // 
// // 			}
// // 			///////////////////////////////////////////////
// // 		}
// // 		/** [SHCH-15-12-2007  BUG-TITLE:XABW/CX-31-11-0078] **/
// // 		int nPos=oProgressDlg.m_Progress.GetPos();
// // 		if(nPos<80)
// // 		{
// // 			oProgressDlg.StepIt();
// // 
// // 		}
// // 		/** [SHCH-15-12-2007  BUG-TITLE:XABW/CX-31-11-0078] **/
// // 	}
// // 	if(nRet==TRUE)
// // 	{
// // 		BOOL tRes= CStorageManager::GetHandle().CloseStudy(pStudy);
// // 		if(tRes==FALSE)
// // 		{
// // 			return FALSE;
// // 
// // 		}
// // 
// // 	}
// // 	////////////////////////////////////////////////////////////////////////////////////////////
// // 	
// // 	
// // 	
//  	return TRUE;
// }
// /********************************************
// 函数名称: 
// 描    述: 
// 输    入: 无
// 输    出: 无
// 返    回: 无
// 其    它: 无
// 修改历史:
//        <修改人> <时间>     <版本 >   <描述>
//     1. 朱映华    2008.3.7 v1.0		from cs code copy
// 	2. 朱映华	 2008.3.27  v1.1    优化cs的代码
// *********************************************/
// long CExportDataTask::ExportAllSelStudyToTempDICOM(void *pExportBlockX)
// {
// // 	long nCount = 0;
// // 	_EXPORT_STRUCT_ *pExportBlock=(_EXPORT_STRUCT_ *)pExportBlockX;
// // 	int nCountOfStudy=pExportBlock->m_szExportStudyID.size();
// // 	
// // 	if(nCountOfStudy==0)
// // 		return nCount;
// // 
// // 	CString szHomePath= CConfigManager::GetHandle().GetHomePath();
// // 	if(szHomePath.Right(2)=="\\\\")
// // 	{
// // 		szHomePath=szHomePath.Left(szHomePath.GetLength()-1);
// // 		
// // 	}
// // 	CString m_DICOMPrinterFilePath=szHomePath+"dicom";
// // 
// // 	if(FALSE == PathFileExists(m_DICOMPrinterFilePath))
// // 	{
// // 		if(!CreateDirectory(m_DICOMPrinterFilePath,NULL))
// // 			return nCount;
// // 	}
// // 	else//清空相关文件夹
// // 	{
// // 		//DeleteDirAndFiles(m_DICOMPrinterFilePath);		//zyh del 2008.3.27 没用的函数！
// // 		DeleteDirectory(m_DICOMPrinterFilePath.GetBuffer(m_DICOMPrinterFilePath.GetLength()));
// // 		//CheckAndCreateDir(m_DICOMPrinterFilePath);		//zyh del 2008.3.27，改为下行语句
// // 		CreateDirectory(m_DICOMPrinterFilePath.GetBuffer(m_DICOMPrinterFilePath.GetLength()), NULL);
// // 	}
// // 
// // 	for(int i=0;i<nCountOfStudy;i++)
// // 	{
// // 		CString szSelectStudy=pExportBlock->m_szExportStudyID[i];
// // 		CString szOnShowStudy=pExportBlock->m_pStydyID;
// // 		int nOnShowSeries=pExportBlock->m_nSeriesIndex;
// // 		int nPos=oProgressDlg.m_Progress.GetPos();
// // 		if(nPos<80)
// // 			oProgressDlg.StepIt();
// // 
// // 		nCount += ExportStudyToDicom(pExportBlock->m_szImageRootPath,szSelectStudy,
// // 			m_DICOMPrinterFilePath,_DCM_TYPE_,FALSE);
// // 	}
// // 	if(oProgressDlg)
// // 		oProgressDlg.DestroyWindow();
// // 	return nCount;
// 	return 0;
// }
// 
// BOOL CExportDataTask::SendDICOMImageFileToPACS(CString szPathName,CString szFileName)
// {
// // 	CString sMsg;
// // 	sMsg.Format( "%s",szFileName	);
// // 	
// // 	CString szTranMsg=CLang::GetHandle().GetCharRes("MSG_FILE_NUM_TITLE");
// // 	CString szTitleAll=szTranMsg+sMsg;
// // 	char*pTitle=(char*)szTitleAll.operator LPCTSTR();
// // 	CString szPathFileName;
// // 	szPathFileName=szPathName+szFileName;
// // 	//theApp.m_pMriView->SendMessage(WM_PROGRESS_SET_TITLE_PACS_TRAN,(DWORD)pTitle,1);
// // 	//////////////////////////////////////////////////////////////////////////////////////
// // 	const char*pSendFileName=(char*)szPathFileName.operator LPCTSTR();
// // 	//REPEAT_SEND_IMAGE_FILE:	
// // 	BOOL bRes=StoreToServer(const_cast<char*>(CConfigManager::GetHandle().GetRemoteAE()),
// // 		const_cast<char*>(CConfigManager::GetHandle().GetRemoteIP()),
// // 		const_cast<char*>(CConfigManager::GetHandle().GetRemotePort()),
// // 		pSendFileName);
// // 	if( pProgDlg && (pProgDlg->m_sProgressCtrl.GetPos()<80))
// // 	{
// // 		pProgDlg->m_sProgressCtrl.StepIt();
// // 		CString szTran="正在传送：";
// // 		pProgDlg->m_sStatic_Ctrl.SetWindowText(szTran+szFileName);
// // 		
// // 	}
// // 	return bRes;
// 	return 0;
// }
// //zyh 对cs 代码做优化，精简函数 2008.3.27
// bool CExportDataTask::DeleteDirAndFiles(CString csFilePath)
// {
// 	DeleteDirectory(csFilePath.GetBuffer(csFilePath.GetLength()));
// 	return TRUE;
// 	
// }
// BOOL CExportDataTask::DeleteDirectory(char *DirName)
// {
//     CFileFind tempFind;
//     char tempFileFind[200];
//     sprintf(tempFileFind,"%s\\*.*",DirName);
//     BOOL IsFinded=(BOOL)tempFind.FindFile(tempFileFind);
//     while(IsFinded)
// 	{
// 		IsFinded=(BOOL)tempFind.FindNextFile();
// 		if(!tempFind.IsDots())
// 		{
// 			char foundFileName[200];
// 			strcpy(foundFileName,tempFind.GetFileName().GetBuffer(200));
// 			if(tempFind.IsDirectory())
// 			{
// 				char tempDir[200];
// 				sprintf(tempDir,"%s\\%s",DirName,foundFileName);
// 				DeleteDirectory(tempDir);
// 			}
// 			else
// 			{
// 				char tempFileName[200];
// 				sprintf(tempFileName,"%s\\%s",DirName,foundFileName);
// 				DeleteFile(tempFileName);
// 			}
// 		}
// 	}
// 	tempFind.Close();
// 	if(!RemoveDirectory(DirName))
// 	{
// 		//MessageBox(0,"删除目录失败！","警告信息",MB_OK);
// 		return FALSE;
// 	}
// 	return TRUE;
// }