#include "bulkrenameclass.h"
#include "Path.h"
#include "Tokenizer.h"
#include "HtmlLogger.h"

volatile int	CBulkRename::nFileCurrCount = 0 ;
int	CBulkRename::nErrorCount = 0 ;


CBulkRename::CBulkRename(void)
{
	CBulkRename::nErrorCount = 0 ;
	pErrorList =  new CTypedPtrList<CObList , CErrorData*>;
}

CBulkRename::~CBulkRename(void)
{
	
}
/*---------------------------------------------------------------------------------------------
Name				:	GetFileCountinFolder(CString strPath, int &m_nFiles)
Purpose				:	<Purpose>
Parameters			:
						CString  strPath - 
						int & m_nFiles - 
Return				:	Void.
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
void CBulkRename::GetFileCountinFolder(CString strPath , int &m_nFiles)
{
	CFileFind ff;
	BOOL bFlag = ff.FindFile(strPath + _T("\\*.*"));

	while(bFlag)
	{
		bFlag = ff.FindNextFile();
		if(ff.IsDots()) continue;

		if(ff.IsDirectory())
		{
			//m_nFolders++; // counts number of folders
			CString subFolderPath=ff.GetFilePath();
			GetFileCountinFolder(subFolderPath,m_nFiles);
		}
		else
		{
			m_nFiles++; // counts number of files
		}

	}
	
	ff.Close();
}
/*---------------------------------------------------------------------------------------------
Name				:	FileChangeCase(CString strPath, int nCaseType, BOOL bIncDir, BOOL (*CancelProc)(LPCTSTR, int) = 0)
Purpose				:	<Purpose>
Parameters			:
						CString  strPath - 
						int  nCaseType - 
						BOOL  bIncDir - 
						BOOL (*)(LPCTSTR, int) CancelProc - 
Return				:	<Return Description>
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
BOOL CBulkRename::FileChangeCase(CString strPath , int nCaseType , BOOL bIncDir ,BOOL CALLBACK CancelProc(LPCTSTR strStatus,int nPercent))
{
	CFileFind FfChangeCase;
	BOOL bFlag = FfChangeCase.FindFile(strPath + _T("\\*.*"));
	while(bFlag)
	{
		bFlag = FfChangeCase.FindNextFile();
		if(FfChangeCase.IsDots()) continue;

		if(FfChangeCase.IsDirectory())
		{
			//m_nFolders++; // counts number of folders
			if(bIncDir)
			{
			   CString strFileName = FfChangeCase.GetFilePath();
			   strFileName = CPath::AddBackSlash( strFileName);
			   if(!RenameOP( strFileName ,nCaseType) )
			   {
				   return FALSE;
			   }
			}
			CString subFolderPath=FfChangeCase.GetFilePath();
			FileChangeCase(subFolderPath,nCaseType, bIncDir ,CancelProc);
		}
		else
		{
			CString strFileName = FfChangeCase.GetFilePath();
			nFileCurrCount++ ;
			if( CancelProc != NULL )
			{
				CString strPath ;
				strPath =   strFileName ;
				int i = 0 ;
				/*if(CRenameUtilityDlg::m_bTotalFileCount !=0)
				{
					i =( (double)nFileCurrCount / CRenameUtilityDlg::m_bTotalFileCount) * 100 ;
				}*/
				if(	CancelProc(	strPath,nFileCurrCount))
				{
				}
			}
			if(!RenameOP( strFileName ,nCaseType))
			{
				return FALSE;
			}
		}

	}
	
	FfChangeCase.Close();
	return TRUE ;
}
/*---------------------------------------------------------------------------------------------
Name				:	RenameOP(CString strScrFileName, int nCaseType)
Purpose				:	<Purpose>
Parameters			:
						CString  strScrFileName - 
						int  nCaseType - 
Return				:	<Return Description>
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
BOOL CBulkRename::RenameOP(CString strScrFileName , int nCaseType )
{
	CString strDestFileName ;
	
	strDestFileName =	 strScrFileName ;
	switch( nCaseType )
	{
	case CRenameOption::enCaseType::nLowerCase: //
		{
			strDestFileName.MakeLower();
		}
	break;
	case CRenameOption::enCaseType::nUpperCase: //
		{
			strDestFileName.MakeUpper();
		}
	break;
	case CRenameOption::enCaseType::nTitelCase: //
		{
			strDestFileName = TitleCase(strDestFileName);
		}
	break;
	}
	int result = 0 ;
	result = _trename(   strScrFileName ,  strDestFileName );
	if(result != 0)
	{
		//return FALSE;
		CString strErrorResult ;
		strErrorResult = ErrorDescription(GetLastError());
		//GetLastError();
		ErrorLog(strScrFileName,strErrorResult);
	}
	return TRUE;
}
/*---------------------------------------------------------------------------------------------
Name				:	RenameOP(CString strScrFilePath, CString strDestFilePath)
Purpose				:	<Purpose>
Parameters			:
						CString  strScrFilePath - 
						CString  strDestFilePath - 
Return				:	<Return Description>
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
BOOL CBulkRename::RenameOP(CString strScrFilePath , CString strDestFilePath )
{
	int result = 0 ;
	result = _trename(   strScrFilePath ,  strDestFilePath );
	if(result != 0)
	{
		//return FALSE;
		CString strErrorResult ;
		strErrorResult = ErrorDescription(GetLastError());
		//GetLastError();
		ErrorLog(strScrFilePath,strErrorResult);
	}
	return TRUE;
}

/*---------------------------------------------------------------------------------------------
Name				:	TitleCase(CString strFileName)
Purpose				:	<Purpose>
Parameters			:
						CString  strFileName - 
Return				:	<Return Description>
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
CString CBulkRename::TitleCase(CString strFilePath )
{
	CPath path1 ;
	CString strFolder,strFileName ;
	path1.SetPath(strFilePath) ;
	if(path1.IsFilePath()  )
	{
		strFolder = path1.GetLocation();
		strFileName = path1.GetFileName() ;
		strFileName = ConvertStringToTitleCase( strFileName) ;
	}
	else
	{
		CPath pathFolder ;
		strFilePath  = pathFolder.RemoveBackSlash(strFilePath);
		pathFolder.SetPath(strFilePath,FALSE) ;
		strFileName = pathFolder.GetFileName() ;
		strFolder = pathFolder.GetLocation();
		strFileName = ConvertStringToTitleCase( strFileName ) ;

	}
	strFolder = strFolder  +  strFileName ;
	return	  strFolder ;

}
/*---------------------------------------------------------------------------------------------
Name				:	ConvertStringToTitleCase(CString strOldString)
Purpose				:	<Purpose>
Parameters			:
						CString  strOldString - 
Return				:	<Return Description>
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
CString CBulkRename::ConvertStringToTitleCase(CString strOldString )
{
	CString strTemp ,cs ;
	CTokenizer tok(	strOldString ,_T(" "));
	while(tok.Next(cs))
	{
		if(cs.GetLength() > 0)
		{
			CString strFirstChar;
			strFirstChar = cs.Left(1);
			cs = cs.Right(cs.GetLength() - 1);
			strFirstChar.MakeUpper();
			cs.MakeLower();
			strTemp =strTemp +  strFirstChar+ cs + _T(" ");
		}
	}
	strTemp.TrimRight(' ');
	return	  strTemp ;
}
/*---------------------------------------------------------------------------------------------
Name				:	ErrorLog(CString strFileName, CString strErrorDesc)
Purpose				:	<Purpose>
Parameters			:
						CString  strFileName - 
						CString  strErrorDesc - 
Return				:	<Return Description>
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
BOOL CBulkRename::ErrorLog(CString strFileName ,CString strErrorDesc )
{
	nErrorCount++;
	CErrorData* pErrorData  = new CErrorData ;
	pErrorData->nSno = nErrorCount ;
	pErrorData->strFilePath = strFileName ;
	pErrorData->strErrorDesc = strErrorDesc ;
	if(pErrorList)
	{
		pErrorList->AddTail(pErrorData);
	}
	return TRUE ;
}
/*---------------------------------------------------------------------------------------------
Name				:	ErrorReport(void)
Purpose				:	<Purpose>
Parameters			:	None.
Return				:	<Return Description>
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
BOOL CBulkRename::ErrorReport( )
{
	if(nErrorCount > 0 )
	{
		CHtmlLogger Log;

		if ( Log.Create( "ErrorLog.htm" ) )
		{
			CErrorData* pErrorData  = NULL ;
			if ( !Log.CreateTable( 3, "Bulk Rename Error Log" ) )
			{
				return FALSE;
			}
			Log.SetColumn( 0, "S.No." );
			Log.SetColumn( 1, "File Path" );
			Log.SetColumn( 2, "Error Desc." );
			Log.AddLine( 0, CHtmlLogger::LT_Header );
			POSITION posit = pErrorList->GetHeadPosition();
			for(int nIndex = 1; nIndex <= pErrorList->GetCount(); nIndex++)
			{
				CErrorData* pErrorData = pErrorList->GetNext(posit);
				if(pErrorData)
				{
					CString strTemp ;
					strTemp.Format(_T("%d"),pErrorData->nSno) ;
					Log.SetColumn( 0, strTemp.GetBuffer() );
					Log.SetColumn( 1,pErrorData->strFilePath.GetBuffer());
					Log.SetColumn( 2, pErrorData->strErrorDesc.GetBuffer() );
					Log.AddLine();
				}
			}
		}
	}
	if(pErrorList !=NULL)
	{
		POSITION pos = pErrorList->GetHeadPosition();

		while (pos!=NULL) {
			delete pErrorList->GetNext(pos);
		}
		pErrorList->RemoveAll();
	}
	delete pErrorList ;
	return TRUE ;
}
// get the description of error
/*---------------------------------------------------------------------------------------------
Name				:	ErrorDescription(DWORD p_dwError)
Purpose				:	<Purpose>
Parameters			:
						DWORD  p_dwError - 
Return				:	<Return Description>
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
CString CBulkRename::ErrorDescription(DWORD p_dwError) 
{
    CString strErrorDesc ;
    HLOCAL hLocal = NULL;
    
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
        NULL, p_dwError, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),(LPTSTR)&hLocal, 
        0, NULL);
    strErrorDesc = (LPCTSTR)LocalLock(hLocal);
    LocalFree(hLocal);
	
	return strErrorDesc ;
}
/*---------------------------------------------------------------------------------------------
Name				:	RenameFile(CRenameOption &RenameOption, BOOL (*CancelProc)(LPCTSTR, int))
Purpose				:	<Purpose>
Parameters			:
						CRenameOption & RenameOption - 
						BOOL (*)(LPCTSTR, int) CancelProc - 
Return				:	<Return Description>
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
BOOL CBulkRename::RenameFile(CRenameOption  &RenameOption  ,BOOL CALLBACK CancelProc(LPCTSTR strStatus,int nPercent))
{
	CFileFind FfRename;
	BOOL bFlag = FfRename.FindFile(RenameOption.m_strPath + _T("\\*.*"));
	while(bFlag)
	{
		bFlag = FfRename.FindNextFile();
		if(FfRename.IsDots()) continue;

		if(FfRename.IsDirectory())
		{
			//m_nFolders++; // counts number of folders
			if(RenameOption.bRenameSubFolder)
			{
				CString strFileName = FfRename.GetFilePath();
				strFileName = CPath::AddBackSlash( strFileName);
				CString strDestPath ;
				//Find Dest Path
				switch( RenameOption.enOperationType )
				{
					case CRenameOption::OperationType::nReplace: //
					{
						strDestPath = ReplaceRename(strFileName ,RenameOption.m_strFindWhat,RenameOption.m_strReplaceWith,RenameOption.enRenameOptions );
						
					}
					break;
					case CRenameOption::OperationType::nSuff_Pref: //
					{
						strDestPath =  AddSuffixPrefix(strFileName,RenameOption );
						
					}
					break;
				}
				
				if(!RenameOP( strFileName ,strDestPath ) )
				{
					return FALSE;
				}
			}
			CString subFolderPath=FfRename.GetFilePath();
			RenameOption.m_strPath =subFolderPath ;
			RenameFile(RenameOption,CancelProc);
		}
		else
		{
			CString strFileName = FfRename.GetFilePath();
			nFileCurrCount++ ;
			if( CancelProc != NULL )
			{
				CString strPath ;
				strPath =   strFileName ;
				int i = 0 ;
				
				if(	CancelProc(	strPath,nFileCurrCount))
				{
				}
			}
			CString strDestPath ;
			//Find Dest Path
			switch( RenameOption.enOperationType )
			{
				case CRenameOption::OperationType::nReplace: //
				{
					strDestPath = ReplaceRename(strFileName ,RenameOption.m_strFindWhat,RenameOption.m_strReplaceWith,RenameOption.enRenameOptions);
					
				}
				break;
				case CRenameOption::OperationType::nSuff_Pref: //
				{
					strDestPath =  AddSuffixPrefix(strFileName,RenameOption );
					
				}
				break;
			}
			
			
			if(!RenameOP( strFileName ,strDestPath))
			{
				return FALSE;
			}
		}
	}
	
	FfRename.Close();
	return TRUE ;
}
/*---------------------------------------------------------------------------------------------
Name				:	ReplaceRename(CString strSrc, CString strOld, CString strNew)
Purpose				:	<Purpose>
Parameters			:
						CString  strSrc - 
						CString  strOld - 
						CString  strNew - 
Return				:	<Return Description>
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
CString CBulkRename::ReplaceRename(CString strSrc,CString strOld ,CString strNew , int nCaseType)
{
	CString strDestPath ;
	switch( nCaseType)
	{
		case CRenameOption::RenameOptions::nIncludeExt: //
		{
			CPath path1 ;
			CString strFolder,strFileName ;
			path1.SetPath(strSrc) ;
			strFolder = path1.GetLocation();
			strFileName = path1.GetFileName() ;
			strOld.MakeUpper();
			strFileName.Replace(strOld,strNew);
			strOld.MakeLower();
			strFileName.Replace(strOld,strNew);

			strDestPath = strFolder +  strFileName ;
		}
		break;
		case CRenameOption::RenameOptions::nExcludeExt: //
		{
			CPath path1 ;
			CString strFolder,strFileName ;
			path1.SetPath(strSrc) ;
			strFolder = path1.GetLocation();
			strFileName = path1.GetFileTitle() ;
			strOld.MakeUpper();
			strFileName.Replace(strOld,strNew);
			strOld.MakeLower();
			strFileName.Replace(strOld,strNew);

			strDestPath = strFolder +  strFileName + path1.GetExtension();
		}
		break;
		case CRenameOption::RenameOptions::nRemoveText: //
		{
			CPath path1 ;
			CString strFolder,strFileName ;
			path1.SetPath(strSrc) ;
			strFolder = path1.GetLocation();
			strFileName = path1.GetFileName() ;
			strOld.MakeUpper();
			strFileName.Replace(strOld,_T(""));
			strOld.MakeLower();
			strFileName.Replace(strOld,_T(""));
			strDestPath = strFolder +  strFileName ;
		}
		break;
		
	}
	return  strDestPath ;
}
/*---------------------------------------------------------------------------------------------
Name				:	AddSuffixPrefix(CString strSrc, CRenameOption &RenameOption)
Purpose				:	<Purpose>
Parameters			:
						CString  strSrc - 
						CRenameOption & RenameOption - 
Return				:	<Return Description>
Globals Modified	:	None.
--------------------------------------------------------------------------------------------*/
CString CBulkRename::AddSuffixPrefix(CString strSrc,CRenameOption  &RenameOption )
{
	CString strDestPath ,strSrcPath;
	CString strFolder,strFileName ;
	CPath path1 ;
	path1.SetPath(strSrc) ;
	if(path1.IsFilePath()  )
	{
		strFolder = path1.GetLocation();
		strFileName = path1.GetFileTitle() ;
		if(RenameOption.enRenameOptions == CRenameOption::RenameOptions::nPrefix)
		{
			strDestPath = strFolder + RenameOption.m_strSuff_Pref + strFileName + path1.GetExtension();
		}
		else if (RenameOption.enRenameOptions == CRenameOption::RenameOptions::nSuffix)
		{
			strDestPath = strFolder + strFileName + RenameOption.m_strSuff_Pref  + path1.GetExtension();
		}

	}
	else
	{
		CPath pathFolder ;
		strSrcPath  = pathFolder.RemoveBackSlash(strSrc);
		pathFolder.SetPath(strSrcPath,FALSE) ;
		strFileName = pathFolder.GetFileName() ;
		strFolder = pathFolder.GetLocation();
		if(RenameOption.enRenameOptions == CRenameOption::RenameOptions::nPrefix)
		{
			strDestPath = strFolder + RenameOption.m_strSuff_Pref + strFileName ;
		}
		else if(RenameOption.enRenameOptions == CRenameOption::RenameOptions::nSuffix)
		{
			strDestPath = strFolder + strFileName + RenameOption.m_strSuff_Pref ;
		}

	}

	return  strDestPath ;
}

