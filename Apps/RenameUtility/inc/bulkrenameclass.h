#pragma once
#ifdef __BULKRENAME
#define _EXPORTSBULKRENAMER __declspec(dllexport)
#else
#define _EXPORTSBULKRENAMER __declspec(dllimport)
#endif
#include "StdAfx.h"
#include <afxtempl.h>

class _EXPORTSBULKRENAMER CErrorData : public CObject
{
public:
	CErrorData(void)
	{
		nSno = 0;
		strFilePath = _T("");
		strErrorDesc = _T("");
	}

	~CErrorData(void)
	{
	}

	int		nSno;
	CString strFilePath;
	CString strErrorDesc;
};
class _EXPORTSBULKRENAMER	CRenameOption
{
public:
	CRenameOption(void)
	{
		bRenameSubFolder = FALSE;
	}

	//Path of the parent Folder
	CString m_strPath;

	// str which is to be replaced
	CString m_strFindWhat;

	//new str with which to replace
	CString m_strReplaceWith;

	//str Which willbe used as suffix or prefix
	CString m_strSuff_Pref;

	//enum value for Case Type
	enum enCaseType
	{
		nUpperCase,
		nLowerCase,
		nTitelCase
	};
	enCaseType CaseType;

	// Bool value if set to true folders will also be renamed
	BOOL bRenameSubFolder;

	//enum value for Suffix or Prefix Type
	enum RenameOptions
	{
		nSuffix,
		nPrefix,
		nIncludeExt,
		nExcludeExt,
		nRemoveText
	};
	RenameOptions enRenameOptions;

	//Windows Handle
	HWND hWnd;

	//enum value Identifies the typeof operation to be performed
	enum OperationType
	{
		nChangeCase,
		nReplace,
		nSuff_Pref
	};
	OperationType enOperationType;
};
class _EXPORTSBULKRENAMER	CBulkRename
{
public:
	static volatile int						nFileCurrCount;
	static int								nErrorCount;

	CBulkRename(void);
	~										CBulkRename(void);
	void									GetFileCountinFolder(CString strPath, int &m_nFiles);
	BOOL									FileChangeCase(CString strPath, int nCaseType, BOOL bIncDir,
														   BOOL CALLBACK CancelProc(LPCTSTR strStatus, int nPercent) = NULL);
	CTypedPtrList<CObList, CErrorData *>	*pErrorList;
	BOOL									ErrorReport();
	BOOL									RenameFile(CRenameOption & RenameOption,
													   BOOL CALLBACK CancelProc(LPCTSTR strStatus, int nPercent));
private:
	BOOL	RenameOP(CString strScrFileName, int nCaseType);
	BOOL	RenameOP(CString strScrFilePath, CString strDestFilePath);

	CString TitleCase(CString strFileName);
	CString ConvertStringToTitleCase(CString strOldString);

	CString ErrorDescription(DWORD p_dwError);
	BOOL	ErrorLog(CString strFileName, CString strErrorDesc);
	CString ReplaceRename(CString strSrc, CString strOld, CString strNew, int nCaseType);
	CString AddSuffixPrefix(CString strSrc, CRenameOption &RenameOption);
};
