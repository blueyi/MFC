// Parameter.cpp: implementation of the CDataBackupInterface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DataBackupInterface.h"
#include <shlwapi.h> 
#include"atlbase.h"
//#include "ciprogressevent.h"
#include <windows.h>
#include <lm.h>
#include <stdio.h>
#include "../ImageHeader/Containers.h"
#include "../ImageHeader/Study.h"
#include "../ImageHeader/Series.h"
#include "../ImageHeader/Image.h"
#include "../Storage/StorageManager.h"
#include "../BCGControlBar/BCGImage.h"
#include "iostream.h"
#include "fstream.h"
#include"string.h"
#include"../BIGlobals/ConfigManager.h"
#include "../ImageDisplay/SeriesViewData.h"
#include "../ImageDisplay/ViewDataManager.h"
#include "../ImageDisplay/ScanViewData.h"
#include "../Filming/FilmingDlg.h"
#include "ExportDataTask.h"
#include "WaitingExportImagesDlg.h"
#include "../StatusWindow/WaitingInterface.h"
#include"../StatusWindow/ProgDlg.h"
CProgressDlg oProgressDlg;
#include "JpegFile.h"





//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDataExportInterface::CDataExportInterface()
{
}

CDataExportInterface::~CDataExportInterface()
{
}

int CDataExportInterface::SetBackupParam()
{
//	CSetBackupParamsDlg oSetBackupParamsDlg;
//	if ( oSetBackupParamsDlg.DoModal() == IDOK )
//	{
//		m_nMoveOrCopy=oSetBackupParamsDlg.m_nMoveOrCopy;
//		m_nStorageMediumType=oSetBackupParamsDlg.m_nMediumType;
//		m_sBackupPath=oSetBackupParamsDlg.m_BackupPath;
//		//传回这个值
//		return oSetBackupParamsDlg.m_nMoveOrCopy;
//	}
	return -1;
}

bool CDataExportInterface::ExecuteBackup( CString sSourcePath, 
										 CString sDatabaseName, std::vector<CString> vStudyId )
{
	//
	//CWaitingDlg
	
	return true;
}

CString CDataExportInterface::SetRestoreParam(CString sLocalPath)
{
	//还要像主类传值
	
	return "";
}

bool CDataExportInterface::ExecuteRestore( CString sDestPath, 
										  std::vector<CString> vStudyId )
{
	

	return true;
}
long CDataExportInterface::GetFolderSize(CString sFolderPath)
{
	m_CurFolderSize=0;
	CalculateFolderSize(sFolderPath);
	return m_CurFolderSize;

}
bool CDataExportInterface::CreateEqualFolders(CString csDirPath, CString csDesPath,int dMorC,bool bMdb)
{
	WIN32_FIND_DATA wfd;
	HANDLE hFind;
	CString csText = _T("");
	
	// Check if the last char is a back-slash
	// (If not, put it there)
	if (csDirPath.Right(1) != "\\")
		csDirPath += _T("\\");
	if (csDesPath.Right(1) != "\\")
		csDesPath += _T("\\");
	
	// set the variable and add an astrix for 
	// the beginning of the directory search.
	csText = csDirPath + _T("*");
	
	// Iterate through dirs
	hFind = FindFirstFile(csText, &wfd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			
			// Check if "." or "..", if not...
			// Check if its a directory.
			if ((strcmp(wfd.cFileName,_T("."))) && (strcmp(wfd.cFileName,_T(".."))) && 
				(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				
				CString csDirIn = _T("");
				CString csDirOut = _T("");
				
				// Set to the directory found.
				csDirIn = csDirPath + wfd.cFileName;
				csDirOut=csDesPath+wfd.cFileName;
				bool bRoot = (PathFileExists(csDirOut) != 0) ;   //Modified by Tom, --2008.07.10
				//不存在建立新的
				if(bRoot==FALSE)
				{
					::CreateDirectory(csDirOut,NULL);
				}


				
				// Call this function again.
				CreateEqualFolders(csDirIn, csDirOut,dMorC,bMdb);
			}
		} while (FindNextFile(hFind, &wfd));
		
		// This is a MUST
		FindClose(hFind);
	}
	
	// Iterate through files
	//
	// set the variable and add an astrix-dot-astrix "*.*"
	// for the beginning of the file search.
	csText = csDirPath + _T("*.*");
	hFind = FindFirstFile(csText, &wfd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			
			// If NOT a directory...
			if ((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
				
				CString csIn = _T("");
				CString csOut = _T("");
				
				// Set to the file found.
				csIn = csDirPath + wfd.cFileName;
				csOut=csDesPath+wfd.cFileName;
				bool bPathExist = (PathFileExists(csOut) != 0) ;   //Modified by Tom, --2008.07.10
				CString szExt=csIn.Right(3);
				szExt.MakeLower();
				if(bMdb==FALSE)
				{
					if(szExt=="mdb")
					{
						continue;
					}
				}
				
				if(dMorC==_FILE_MOVE_)
				{
					MoveFileEx(csIn,csOut,MOVEFILE_REPLACE_EXISTING);
				}
				else if(dMorC==_FILE_COPY_)
				{
					CopyFile(csIn,csOut,FALSE);

				}
				

				// Now, add the filename into the Array.
				
			}
		} while (FindNextFile(hFind, &wfd));
		
		// This is a MUST
		FindClose(hFind);
		
	}
	
	return TRUE;
}
void CDataExportInterface::CalculateFolderSize(CString csDirPath)
{
	WIN32_FIND_DATA wfd;
	HANDLE hFind;
	CString csText = _T("");
	
	// Check if the last char is a back-slash
	// (If not, put it there)
	if (csDirPath.Right(1) != "\\")
		csDirPath += _T("\\");
	
	// set the variable and add an astrix for 
	// the beginning of the directory search.
	csText = csDirPath + _T("*");
	
	// Iterate through dirs
	hFind = FindFirstFile(csText, &wfd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			
			// Check if "." or "..", if not...
			// Check if its a directory.
			if ((strcmp(wfd.cFileName,_T("."))) && (strcmp(wfd.cFileName,_T(".."))) && 
				(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				
				CString csDirIn = _T("");
				
				// Set to the directory found.
				csDirIn = csDirPath + wfd.cFileName;
				
				// Call this function again.
				CalculateFolderSize(csDirIn);
			}
		} while (FindNextFile(hFind, &wfd));
		
		// This is a MUST
		FindClose(hFind);
	}
	
	// Iterate through files
	//
	// set the variable and add an astrix-dot-astrix "*.*"
	// for the beginning of the file search.
	csText = csDirPath + _T("*.*");
	hFind = FindFirstFile(csText, &wfd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			
			// If NOT a directory...
			if ((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
				
				CString csIn = _T("");
				CString csOut = _T("");
				
				// Set to the file found.
				csIn = csDirPath + wfd.cFileName;
				
				//Modified by Tom, --2008.07.10
				m_CurFolderSize += wfd.nFileSizeLow + (wfd.nFileSizeHigh<<_DWORD_LENGTH_);
			}
		} while (FindNextFile(hFind, &wfd));
		
		// This is a MUST
		FindClose(hFind);
		
	}
	

}
bool CDataExportInterface::DeleteFolderFiles(CString csDirPath)
{
	WIN32_FIND_DATA wfd;
	HANDLE hFind;
	CString csText = _T("");
	
	// Check if the last char is a back-slash
	// (If not, put it there)
	if (csDirPath.Right(1) != "\\")
		csDirPath += _T("\\");
	
	// set the variable and add an astrix for 
	// the beginning of the directory search.
	csText = csDirPath + _T("*");
	
	// Iterate through dirs
	hFind = FindFirstFile(csText, &wfd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			
			// Check if "." or "..", if not...
			// Check if its a directory.
			if ((strcmp(wfd.cFileName,_T("."))) && (strcmp(wfd.cFileName,_T(".."))) && 
				(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				
				CString csDirIn = _T("");
				
				// Set to the directory found.
				csDirIn = csDirPath + wfd.cFileName;
				
				// Call this function again.
				DeleteFolderFiles(csDirIn);
			}
		} while (FindNextFile(hFind, &wfd));
		
		// This is a MUST
		FindClose(hFind);
	}
	
	// Iterate through files
	//
	// set the variable and add an astrix-dot-astrix "*.*"
	// for the beginning of the file search.
	csText = csDirPath + _T("*.*");
	hFind = FindFirstFile(csText, &wfd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			
			// If NOT a directory...
			if ((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
				
				CString csIn = _T("");
				CString csOut = _T("");
				
				// Set to the file found.
				csIn = csDirPath + wfd.cFileName;
				//设置文件属性为无
                //Modified by Tom, --2008.07.10
				bool bFileReadOnly = (SetFileAttributes(csIn,FILE_ATTRIBUTE_ARCHIVE) != 0);
				if(bFileReadOnly==TRUE)
					DeleteFile(csIn);
				
				//m_CurFolderSize+=wfd.nFileSizeLow+wfd.nFileSizeHigh<<_DWORD_LENGTH_;
			}
		} while (FindNextFile(hFind, &wfd));
		
		// This is a MUST
		FindClose(hFind);
		
	}
	return TRUE;
}
bool CDataExportInterface::DeleteImageFile( CString sLocalPath, std::vector<CString> vStudyId )
{
	if (sLocalPath.Right(1) != "\\")
		sLocalPath += _T("\\");

	int dSize=vStudyId.size();
	int t=0;
	while(t<dSize)
	{
		CString sStudyId=vStudyId.back();
		DeleteDirAndFiles(sLocalPath+sStudyId);
		vStudyId.pop_back();
		t++;

	}
	return TRUE;

}
BOOL CDataExportInterface::DeleteDirectory(char *DirName)
{
    CFileFind tempFind;
    char tempFileFind[200];
    sprintf(tempFileFind,"%s\\*.*",DirName);
    BOOL IsFinded=(BOOL)tempFind.FindFile(tempFileFind);
    while(IsFinded)
	{
		IsFinded=(BOOL)tempFind.FindNextFile();
		if(!tempFind.IsDots())
		{
			char foundFileName[200];
			strcpy(foundFileName,tempFind.GetFileName().GetBuffer(200));
			if(tempFind.IsDirectory())
			{
				char tempDir[200];
				sprintf(tempDir,"%s\\%s",DirName,foundFileName);
				DeleteDirectory(tempDir);
			}
			else
			{
				char tempFileName[200];
				sprintf(tempFileName,"%s\\%s",DirName,foundFileName);
				DeleteFile(tempFileName);
			}
		}
	}
	tempFind.Close();
	if(!RemoveDirectory(DirName))
	{
		//MessageBox(0,"删除目录失败！","警告信息",MB_OK);
		return FALSE;
	}
	return TRUE;
}
bool CDataExportInterface::DeleteDirAndFiles(CString csFilePath)
{
	char*pName;
	int dlen=csFilePath.GetLength();
	pName=(char*)malloc(dlen+1);
	memset(pName,0,dlen+1);
	memcpy(pName,csFilePath,dlen);
	pName[dlen]='\0';
	DeleteDirectory(pName);
	free(pName);
	return TRUE;
	
}

bool CDataExportInterface::CreateDirectoryMulty(CString csPathDir)
{
	CString szDir;
	CString szName;
	
	//if(csPathDir)
	//	{
	//		return FALSE;
	//	}
	
	CString tTemp=csPathDir;
	if(tTemp.Right(1)=="\\")
	{
		tTemp=tTemp.Left(tTemp.GetLength()-1);
		
	}
	int dPos=tTemp.Find("\\",0);
	while(dPos>=0)
	{
		
		szName=tTemp.Left(dPos);
		
		szDir+=szName+"\\";
		tTemp=tTemp.Right(tTemp.GetLength()-dPos-1);
		bool bRes = (PathFileExists(szDir) != 0);    //Modified by Tom, --2008.07.10
		
		if(bRes==FALSE)
		{
			CreateDirectory(szDir,NULL);
		}
		dPos=tTemp.Find("\\",0);
		
		
		
	}
	//szName=tTemp.Left(dPos);
	szDir+=tTemp;
	tTemp=tTemp.Right(tTemp.GetLength()-dPos-1);
	bool bRes = (PathFileExists(szDir) != 0);   //Modified by Tom, --2008.07.10
	
	if(bRes==FALSE)
	{
		CreateDirectory(szDir,NULL);
	}
	return TRUE;
	
	
	
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
BOOL CDataExportInterface::ExportSelectStudy2(void *pExportBlockX, 
											 CProgressCtrl *pProcess)
{
	CExportDataTask exortDataTask;
	return exortDataTask.ExportSelectStudy2(pExportBlockX, pProcess);
}

//UINT ExportSelectStudy(LPVOID pExportBlockX)
BOOL CDataExportInterface::ExportSelectStudy(void *pExportBlockX)
{
	//int p=sizeof(double);
	//ThreadExportStudy(pExportBlockX);
	AfxBeginThread(ThreadExportStudy,(LPVOID)pExportBlockX);
	return TRUE;
	
}
UINT CDataExportInterface::ThreadExportStudy(LPVOID pVoid)
{
//	CWaitingExportImagesDlg *dlg;
//	dlg=new CWaitingExportImagesDlg;
//	if(dlg)
//	{
//		BOOL nRet=dlg->Create(CWaitingExportImagesDlg::IDD);
//		if(nRet==TRUE)
//		{
//			dlg->ShowWindow(SW_SHOW);
//
//		}
//
//	}
	//#include "WaitingInterface.h"
//	CWaitInterface*dlg;
//	dlg=new CWaitInterface;
//	dlg->Create();
//	if(dlg)
//	{
//		dlg->ShowWindow(SW_SHOW);
//	}
	//AfxMessageBox("");
//	CWaitInterface*dlga;
//	dlga=new CWaitInterface;
//	if(dlga)
//	{
//		dlga->Create();
//		dlga->Show();
//		//dlga->ShowWindow(SW_SHOW);
//		//dlga->SetRedraw();
//	}
	//AfxMessageBox("");
	//Sleep(100000);
	//
	oProgressDlg.Create();
	oProgressDlg.SetRange(0,100);
	oProgressDlg.SetStep( 100/10 );
	CString szTitleMsg=CLang::GetHandle().GetCharRes("MRI_PROGRESS_CAPTION");
	oProgressDlg.SetStatus( szTitleMsg/*"正在打开网络图层，请等待 ..."*/ );
	 //oProgressDlg.SetStatus( "正在打开网络图层，请等待 ..." );
	

	CExportDataTask *m_pExortDataTask=new CExportDataTask;
	m_pExortDataTask->ExportSelectStudy(pVoid);
//	if(dlg)
//	{
//		dlg->SendMessage(WM_CLOSE);
//
//	}
//	dlga->SendMessage(WM_CLOSE);
//	if(dlg)
//	{
//		dlg->OnCloseWaitingDlg();
//		dlg->SendMessage(WM_CLOSE);
//
//		if(dlg)
//		{
//			delete dlg;
//
//		}
//		
//
//	}
	oProgressDlg.DestroyWindow();
	CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("MRI_EXPORT_STUDY")/*"Export task complete!"*/);
	
	return TRUE;

}
//界面上不存在的部分
//nConvType 0 DICOM ; 1 BMP ...
bool CDataExportInterface::ExportStudyToDicom(CString szImageRootPath,CString szStudyID,CString strDestFilePathName,BOOL nSaveMed)
{
	//////////////////////////////////////////////////////////////////////////
	//设置序列图像保存的文件参数;
	//Modified by lwz;
//	if(strDestFilePathName.Right(1)=="\\")
//	{
//		strDestFilePathName=strDestFilePathName.Left(strDestFilePathName.GetLength()-1);
//
//	}
//	BOOL bF=CheckDiskSpaceAndEnWrite(strDestFilePathName,50);
//	if(bF==FALSE)
//	{
//		AfxMessageBox("Disk Error!\nCan't export series!");
//		return FALSE;
//	}
//    //当前的Study ID
//	std::string pStrData=(char*)szStudyID.operator LPCTSTR();
//	int      nFileCount = 0;
//	char    *pcDicomData   = NULL;
//	int      nDicomDataLen = 0;
//	//HMODULE  hPushDll ;
//	pcDicomData = new char[3*1024*1024];
//	
//	CStudy* pStudy = CStorageManager::GetHandle().GetStudy(pStrData);
//	int nCountOfSeries=pStudy->GetCountOfSeries();
//	for(int i=1;i<nCountOfSeries+1;i++)
//	{
//		CSeries*pSeries=pStudy->GetSeries(i);
//		if(!pSeries)
//		{
//			continue;
//		}
//		int nCountOfImage=pSeries->GetCountOfImage();
//		for(int j=0;j<nCountOfImage;j++)
//		{
//			CImage *pImage=pSeries->GetImage(j);
//			if(!pImage)
//			{
//				continue;
//			}
//			//转化
//			short*p12BitData=pImage->GetBuffer();
//			int nW=pImage->GetWidth();
//			int nH=pImage->GetHeight();
//			CString szImagePath;
//			szImagePath.Format("%s%s\\%d\\%d.img",szImageRootPath,szStudyID,i,j);
//			CBIImageHeader imageHeader;
//			short*pShortData=CImage::ReadImageFile((char*)szImagePath.operator LPCTSTR(),imageHeader);
//			if(!pShortData)
//			{
//				continue;
//
//			}
//			
//			if (!ConvertXB2Dicom(imageHeader,p12BitData,pcDicomData,nDicomDataLen))
//			{
//				delete[] pcDicomData;
//				return FALSE ;
//			}
//			CString szSaveName;
//			if(nSaveMed==FALSE)
//			{
//				szSaveName.Format("%s\\%s_%d_%d.dcm",strDestFilePathName,szStudyID,i,j);
//			}
//			else if(nSaveMed==TRUE)
//			{
//				szSaveName.Format("%s\\%s\\%d\\%d.bmp",strDestFilePathName,szStudyID,i,j);
//				CString szPath;
//				szPath.Format("%s\\%s\\%d\\",strDestFilePathName,szStudyID,i);
//				BOOL nRef=CheckAndCreateDir(szPath);
//				if(nRef==FALSE)
//				{
//					continue;
//				}
//
//			}
//			CFile file;
//			file.Open(szSaveName,CFile::modeCreate | CFile::modeWrite);
//			file.WriteHuge(pcDicomData,nDicomDataLen) ;
//			
//			nDicomDataLen = 0 ;
//			file.Close();
////			///////////////////////////////////////////////
//		}
//	}
	return true ;

}
BOOL CDataExportInterface::CheckDiskSpaceAndEnWrite(CString szPath, int nTotalImage)
{
	if(szPath=="")
	{
		return FALSE;
	}
	BOOL bRes=PathFileExists(szPath);
	if(bRes==FALSE)
	{
		return FALSE;

	}
	unsigned long nImgSize=512*1024*nTotalImage;
	ULARGE_INTEGER h1;
    ULARGE_INTEGER h2;
    ULARGE_INTEGER h3;
	if(szPath.GetLength()<2)
	{
		//AfxMessageBox("Path can't be recognized");
		//CLang::GetHandle().ShowMessage("");
		CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("IMAGE_EXPORT_MSG_PATH_CANNOT_REC"));
		return FALSE;
	}
	CString szDiskName=szPath.Left(2);
	if(szDiskName.Right(1)!=":")
	{
		//AfxMessageBox("Path can't be recognized");
		//CLang::GetHandle().ShowMessage("");
		CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("IMAGE_EXPORT_MSG_PATH_CANNOT_REC"));
		
		return FALSE;
	}
    GetDiskFreeSpaceEx(szDiskName,&h1,&h2,&h3);
	
	unsigned long nDiskFreeSizeHigh=h1.u.HighPart;
	unsigned long nDiskFreeSizeLow=h1.u.LowPart;
	if(nDiskFreeSizeHigh==0 && nDiskFreeSizeLow<nImgSize)
	{
		//AfxMessageBox("Can't get enough space!");
		//CLang::GetHandle().ShowMessage("");
		CLang::GetHandle().ShowMessage(CLang::GetHandle().GetCharRes("IMAGE_EXPORT_MSG_CANNOT_GET_ENOUGH_SPACE"));
		return FALSE;

	}


	HANDLE hFile; 
	
	hFile = CreateFile(szPath+"MYFILE.TXT",           // create MYFILE.TXT 
		GENERIC_WRITE,                // open for writing 
		0,                            // do not share 
		NULL,                         // no security 
		CREATE_ALWAYS,                // overwrite existing 
		FILE_ATTRIBUTE_NORMAL |       // normal file 
		FILE_FLAG_OVERLAPPED,         // asynchronous I/O 
		NULL);                        // no attr. template 
	
	if (hFile == INVALID_HANDLE_VALUE) 
	{ 
		CloseHandle(hFile);
	//	AfxMessageBox("Could not write file.");  // process error
		return FALSE;
		
	}
	else
	{
		CloseHandle(hFile);
		BOOL bRes=DeleteFile(szPath+"MYFILE.TXT");
		if(bRes==FALSE)
		{
			return FALSE;
			
		}
	}
	return TRUE;

}
BOOL CDataExportInterface::CheckAndCreateDir(CString szDir)
{
	if(szDir.Right(1)!="\\")
	{
		szDir+="\\";
	}
	//MakeSureDirectoryPathExists()
	BOOL bReturn=PathFileExists(szDir);
	if(bReturn==TRUE)
	{
		return TRUE;
	}
	CString szPathDir=szDir;
	CString szLeftStr;
	
	CString szRemainStr;
	int nPos=-1;
	do 
	{
		nPos=szPathDir.Find("\\",0);
		if(nPos>0)
		{
			szRemainStr+=szPathDir.Left(nPos);
			if(szRemainStr.Right(1)!="\\")
			{
				szRemainStr+="\\";
				
			}
			bReturn=PathFileExists(szRemainStr);
			if(bReturn==TRUE)
			{
				
			}
			else if(bReturn==FALSE)
			{
				BOOL nRes=CreateDirectory(szRemainStr,NULL);
				if(nRes==FALSE)
				{
					return FALSE;
				}
				
				
			}
			szPathDir=szPathDir.Right(szPathDir.GetLength()-nPos-1);
		}
		
	} while(nPos>0);
	return TRUE;
}
//Global Function








BOOL CDataExportInterface::ExportStudyToBMP(CString szImageRootPath, CString szStudyID, CString strDestFilePathName, BOOL nSaveMed)
{
	if(strDestFilePathName.Right(1)=="\\")
	{
		strDestFilePathName=strDestFilePathName.Left(strDestFilePathName.GetLength()-1);

	}
	BOOL bF=CheckDiskSpaceAndEnWrite(strDestFilePathName,50);
	if(bF==FALSE)
	{
		AfxMessageBox("Disk Error!\nCan't export series!");
		return FALSE;
	}
    //当前的Study ID
	std::string pStrData=(char*)szStudyID.operator LPCTSTR();
	
	CStudy* pStudy = CStorageManager::GetHandle().GetStudy(pStrData);
	int nCountOfSeries=pStudy->GetCountOfSeries();
	for(int i=0;i<nCountOfSeries;i++)
	{
		CSeries*pSeries=pStudy->GetSeries(i);
		if(!pSeries)
		{
			continue;
		}
		int nCountOfImage=pSeries->GetCountOfImage();
		for(int j=0;j<nCountOfImage;j++)
		{
			CImage *pImage=pSeries->GetImage(j);
			if(!pImage)
			{
				continue;
			}
			//转化
			/////////////////////////////////////////////////////
			CSize nImgSize=pImage->GetSize();
			CImageViewData* pImageViewData = CViewDataManager::GetHandle().GetImageViewData(pImage);
			ASSERT(pImageViewData);
			CProcessParams params = pImageViewData->ProcessParams();
			int nImageSize = CConfigManager::GetHandle().GetFilmingConfig().m_nImageSize;
			int nWidth = nImageSize;//pImageData->GetWidth();
			int nHeight = nImageSize;//pImageData->GetHeight();
			params.m_sizeBitmap.cx = nWidth;
			params.m_sizeBitmap.cy = nHeight;
			CDC dcPrint;
			//memcpy(nSaveCtrlInfo,nControlInfo,4*sizeof(int));
			dcPrint.CreateDC("DISPLAY", NULL, NULL, NULL);
			dcPrint.SetMapMode(MM_TEXT);
			BYTE* pData = CFilmingDlg::OnGetPrintDataBYTEPrint(dcPrint, pImage, nWidth, nHeight,FALSE, j);
			if(!pData)
			{
				continue;
			}
			BYTE *pUsingData;
			pUsingData=new BYTE[nHeight*nWidth];
			memset(pUsingData,0,sizeof(BYTE)*nHeight*nWidth);
			int nShortSize=nHeight*nWidth;
			for(int i=0;i<nHeight;i++)
			{
				for(int j=0;j<nWidth;j++)
				{
					int nTemp=pData[(i*nWidth+j)];
					pUsingData[((nHeight-1-i)*nWidth+j)]=(BYTE)nTemp;
					
					
				}
			}
			/////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////
			CString szImagePath;
			szImagePath.Format("%s\\%s\\%d\\%d.img",szImageRootPath,szStudyID,i,j);
			CString szSaveName;
			if(nSaveMed==FALSE)
			{
				szSaveName.Format("%s\\%s_%d_%d.dcm",strDestFilePathName,szStudyID,i,j);
			}
			else if(nSaveMed==TRUE)
			{
				szSaveName.Format("%s\\%s\\%d\\%d.bmp",strDestFilePathName,szStudyID,i,j);
				CString szPath;
				szPath.Format("%s\\%s\\%d\\",strDestFilePathName,szStudyID,i);
				BOOL nRef=CheckAndCreateDir(szPath);
				if(nRef==FALSE)
				{
					continue;
				}

			}
			char*pStrBmpName=(char*)szSaveName.operator LPCTSTR();
			SaveImageDataToBmp(pUsingData,nWidth,nHeight,1,pStrBmpName);
			if(pUsingData)
			{
				delete []pUsingData;

			}
			if(pData)
			{
				delete []pData;

			}
			///////////////////////////////////////////////
		}
	}
	return true ;

}
//////////////////////////////////////////////////////////////////////////
/*
函数说明：保存图像数据为BMP图像
参数说明：
	1) unsigned char *pDest :　[in]图像数据
	2) int w				:　[in]图像宽度
	3) int h				:  [in]图像高度
	4) char *pFileName      :  [in]图象文件名
返回值：
　　TRUE　保存成功，　FALSE　保存失败；
//这个存取函数是基于列优先存储的　
*/
//////////////////////////////////////////////////////////////////////////
bool CDataExportInterface::SaveImageDataToBmp(unsigned char *pDest,
						int w,
						int h,
						int format,
						char *pFileName)
{

	bool bResult  = true;
	int m_nX = 0;
	int m_nY = 0;
	m_nX = w;
	m_nY = h;
	int i = 0;
	//////////////////////////////////////////////////////////////////////////
	//写bmp文件;
	BITMAPFILEHEADER bmfHdr; //定义文件头
	BITMAPINFOHEADER bmiHdr; //定义信息头
	RGBQUAD rgbQuad[256];    //定义调色板
	//对信息头进行赋值
	bmiHdr.biSize = sizeof(BITMAPINFOHEADER);
	bmiHdr.biWidth = m_nX;
	bmiHdr.biHeight = m_nY;
	bmiHdr.biPlanes = 1;
	if(format == 3)
		bmiHdr.biBitCount = 24;
    else if(format == 1)
        bmiHdr.biBitCount = 8;
	else if(format == 16)
		bmiHdr.biBitCount = 16;
	else if(format == 4)
		bmiHdr.biBitCount = 32;

	bmiHdr.biCompression = BI_RGB;
	bmiHdr.biSizeImage = m_nX * m_nY * format;
	bmiHdr.biXPelsPerMeter = 0;
	bmiHdr.biYPelsPerMeter = 0;
	bmiHdr.biClrUsed = 0;
	bmiHdr.biClrImportant = 0;
	//对调色板进行赋值
	for(i=0; i<256; i++)
	{
		rgbQuad[i].rgbBlue = (BYTE)i;
		rgbQuad[i].rgbGreen = (BYTE)i;
		rgbQuad[i].rgbRed = (BYTE)i;
		rgbQuad[i].rgbReserved = 0;
	}

	
	//对文件头进行赋值
	bmfHdr.bfType = (WORD)0x4D42;
	bmfHdr.bfSize=(DWORD)(sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*256 + m_nX*m_nY*format);
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits=(DWORD)(sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*256);
	
	//////////////////////////////////////////////////////////////////////////
	//保存文件
	CString strBmpFileName;
	strBmpFileName.Format("%s",pFileName);
	
    CFile fp;
	fp.Open(strBmpFileName,CFile::modeCreate|CFile::modeWrite);
	fp.Write((LPSTR)&bmfHdr,sizeof(BITMAPFILEHEADER));				//写文件头
	fp.Write((LPSTR)&bmiHdr,sizeof(BITMAPINFOHEADER));				//写信息头
	fp.Write((LPSTR)rgbQuad,sizeof(RGBQUAD)*256);					//写调色板
	fp.Write(pDest,m_nX*m_nY*format);										//写数据
	fp.Close();	
	
	bResult = true;
    return bResult;
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
    1. 朱映华    2008.3.7 v1.0		  从cs代码拷贝过来
*********************************************/
long CDataExportInterface::ExportAllSelStudyToTempDICOM(void *pExportBlockX)
{
	//	AfxBeginThread(ThreadExportStudySendToPacs,(LPVOID)pExportBlockX);
	
	return ThreadExportStudySendToPacs(pExportBlockX);
	
}
long CDataExportInterface::ThreadExportStudySendToPacs(LPVOID pVoid)
{
	oProgressDlg.Create();
	oProgressDlg.SetRange(0,100);
	oProgressDlg.SetStep( 2 );
	CString szTitleMsg=CLang::GetHandle().GetCharRes("MRI_PROGRESS_CAPTION");
	oProgressDlg.SetStatus( szTitleMsg);
	
	CExportDataTask *pExortDataTask=new CExportDataTask;
	long n = pExortDataTask->ExportAllSelStudyToTempDICOM(pVoid);
	delete pExortDataTask;
	return n;
	
}