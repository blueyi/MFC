#include "StdAfx.h"
#include ".\resourceutils.h"

void CResourceUtils::UnpackResToFile( UINT nIDResource, LPCTSTR szResType, LPCTSTR lpszPath )
// Unpacks a (custom?) resource to a given file.
// If anything goes wrong an MFC exception is thrown.
{
	HINSTANCE		hInst = ::AfxGetResourceHandle();
	HRSRC			hResInfo = NULL;
	HGLOBAL			hRes = NULL;
	LPVOID			pResData = NULL;
	DWORD			dwResSize = 0;
	CFile			targetFile;
	CFileException	fe;
	//

	try
	{
		// Locate and load the user-defined resource.
		hResInfo = ::FindResource( hInst, MAKEINTRESOURCE((WORD)nIDResource), szResType );
		hRes = ::LoadResource( hInst, hResInfo );

		// Throw an exception if we didn't get the resource!
		if ( NULL == hRes )
			AfxThrowResourceException();
			
		// Lock down the resource - throw an exception if this fails!
		if ( (pResData = ::LockResource(hRes)) == NULL )
			AfxThrowResourceException();

		// Get the target file ready for writing...
		if ( !targetFile.Open(lpszPath, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite, &fe) )
			::AfxThrowFileException( fe.m_cause, fe.m_lOsError, lpszPath );

		// Write the resource data into the file...
		dwResSize = ::SizeofResource( hInst, hResInfo );
		targetFile.Write( pResData, dwResSize );
		targetFile.Close();
	}
	catch ( CException* )
	{
		// Make sure the file is closed
		targetFile.Abort();
	
		// Rethrow the exception
		throw;
	}
}

CString CResourceUtils::UnpackResToTempFile( UINT nIDResource, LPCTSTR szResType )
// Unpacks the given resource to a temporary file, and returns the full path
// of that file. 
//
// If an error occurs, the resulting string will be empty.
{
	CString	strTemp;
	//

	try
	{
		strTemp = CResourceUtils::GetTempFileName();
		CResourceUtils::UnpackResToFile( nIDResource, szResType, strTemp );
	}
	catch ( CException* e )
	{
		// Suppress the exception
		TRACE( _T("Exception in CResourceUtils::UnpackResToTempFile!\n") );
		e->Delete();
		
		// Ditch the file if any
		::DeleteFile( strTemp );
		strTemp.Empty();
	}
	
	return strTemp;
}

CString CResourceUtils::GetTempFileName( LPCTSTR lpszPrefix /*= _T("TMP")*/ )
// Generates a unique filename in the system temporary directory.
// If supplied, the first three characters are used at the start
// of the filename. 
{
	TCHAR	szTempDir[_MAX_PATH];
	TCHAR	szTempFile[_MAX_PATH];
	DWORD	dwResult = 0;
	//

	// Get hold of the system temporary directory. Throw an
	// exception on failure...
	dwResult = ::GetTempPath( sizeof(szTempDir), szTempDir );
	if ( 0 == dwResult )
		CFileException::ThrowOsError( ::GetLastError() );

	// Generate a temporary filename, using the given prefix string.
	// Throw an exception on failure...
	dwResult = ::GetTempFileName( szTempDir, lpszPrefix, 0, szTempFile );
	if ( 0 == dwResult )
		CFileException::ThrowOsError( ::GetLastError() );

	// If we're still here...
	return (szTempFile);
}
