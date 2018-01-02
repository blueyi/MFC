/*************************************************************************************
 *************************************************************************************
 **																					**
 ** File name:		GenFile.cpp.													**
 **																					**
 ** Description:	Implementation file of class CGenFile.							**
 **																					**
 ** Created on:		Nov 2002.													**
 **																					**
 ** Author:			Stas Desyatnikov.												**
 **																					**
 ** FileX Copyright (C) 2002. All rights reserved.									**
 **																					**
 *************************************************************************************
 *************************************************************************************/

#include <string.h>
#include "GenFile.h"

CGenFile::CGenFile()
{
	m_fFile = 0;
}

CGenFile::~CGenFile()
{
	if (m_fFile != 0)
		Close();
}

bool CGenFile::Open(char* szFileName, const char *mode)
{
	// attempt file creation
	FILE* fFile = fopen(szFileName, mode);
	m_fFile = fFile;

	return ( m_fFile != NULL);
}

int CGenFile::Read(void* pBuf, uint* pCount)
{
	return fread( pBuf, sizeof(char), *pCount, m_fFile );
}

bool CGenFile::ReadLine(char* szStr, uint* pMaxCount)
{
	return ( NULL != fgets( szStr, *pMaxCount, m_fFile ) );
}

int CGenFile::Write(const void* pBuf, uint nCount)
{
	return fwrite( pBuf, sizeof(char), nCount, m_fFile );
}

bool CGenFile::WriteLine( const char* szStr, int iSize )
{
	if ( iSize == -1 )
		iSize = strlen( szStr );

	int iRet = Write( szStr, iSize );
	if ( iRet < iSize )
		return false;

	iRet = strlen("\n");
	return ( iRet == Write( "\n", iRet ) );
}

bool CGenFile::Seek( long lOffset )
{
	int iRet = fseek( m_fFile, lOffset, SEEK_SET );
	return ( iRet == 0 );
}

uint CGenFile::GetPosition()
{
	return ftell(m_fFile);
}

void CGenFile::Close()
{
	if ( m_fFile )
	{
		fclose( m_fFile );
		m_fFile = NULL;
	}
}

uint CGenFile::GetLength()
{
	int StreamLength;
	long CurrStreamPosition;
	
	//Get current position
	CurrStreamPosition = ftell(m_fFile);
	//seek to the end of file
	fseek(m_fFile, 0, SEEK_END);
	StreamLength = ftell(m_fFile);
	//Get back to the stored position
	fseek(m_fFile, CurrStreamPosition, SEEK_SET);

	return StreamLength;
}

bool CGenFile::IsFile( char* szFile )
{
	FILE* fFile = fopen( szFile, "r" );
	if ( fFile )
	{
		fclose( fFile );
		return true;
	}
	else
	{
		return false;
	}
}

CGenFile::operator FILE*()
{
	return m_fFile;
}
