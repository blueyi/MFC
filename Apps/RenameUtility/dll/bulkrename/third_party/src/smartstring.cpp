#include "SmartString.h"
#include <string.h>

CSmartString::CSmartString()
{
	m_pchString = NULL;
	m_iSize = 0;
	m_iLength = 0;
	m_bIsStringStatic = false;
}

CSmartString::~CSmartString()
{
	Destruct();
}

void CSmartString::operator = (CSmartString &NewString)
{
	SetString(NewString.m_pchString, NewString.m_iLength);
}

void CSmartString::operator = ( const char* szText )
{
	SetString( szText );
}

bool CSmartString::operator == (CSmartString &CmpString)
{
	return Compare(CmpString.m_pchString, CmpString.m_iLength);
}

bool CSmartString::operator == (const char *pszCmpString)
{
	return Compare(pszCmpString);
}

CSmartString::operator const char* ()
{
	return GetString();
}

bool CSmartString::Reference(CSmartString &ReferenceString)
{
	if ( !Construct(ReferenceString.m_iLength, ReferenceString.m_pchString) )
		return false;

	m_iLength = ReferenceString.m_iLength;

	return true;
}

bool CSmartString::Construct(int iStringPoolSize, void *pvStringPool /* = NULL */)
{
	Destruct();

	if ( iStringPoolSize - 1 > 0 && pvStringPool != NULL )
	{
		m_pchString = (char *)pvStringPool;
		m_iSize = iStringPoolSize;
		m_bIsStringStatic = true;
		return true;
	}

	if ( Reallocate(iStringPoolSize) )
		return true;

	return false;
}

void CSmartString::Destruct()
{
	if ( !m_bIsStringStatic )
		delete m_pchString;

	m_pchString = NULL;
	m_iSize = 0;
	m_iLength = 0;
	m_bIsStringStatic = false;
}

bool CSmartString::SetString(const char *pchNewString, int iNewStringLength /* = -1 */)
{
	if ( iNewStringLength == -1 )
		iNewStringLength = strlen(pchNewString);
	if ( iNewStringLength >= m_iSize )
	{
		if ( !Reallocate(iNewStringLength + 1) )
			return false;
	}
	memcpy(m_pchString, pchNewString, iNewStringLength);
	m_iLength = iNewStringLength;

	return true;
}

const char* CSmartString::GetString()
{
	m_pchString[m_iLength] = '\0';
	return m_pchString;
}

int CSmartString::GetLength()
{
	return m_iLength;
}

bool CSmartString::IsEmpty()
{
	return ( m_iLength == 0 );
}

void CSmartString::Empty()
{
	m_iLength = 0;
}

bool CSmartString::AddChar(char chChar)
{
	if ( m_iLength >= m_iSize - 1 )
		return false;
	m_pchString[m_iLength++] = chChar;
	return true;
}

bool CSmartString::Compare(const char *pchCmpString, int iCmpStringLength /* = -1 */)
{
	if ( iCmpStringLength == -1 )
		iCmpStringLength = strlen(pchCmpString);

	if ( m_iLength != iCmpStringLength )
		return false;
	if ( memcmp(m_pchString, pchCmpString, m_iLength) != 0 )
		return false;

	return true;
}

bool CSmartString::Reallocate(int iNewStringSize)
{
	if ( m_bIsStringStatic )
		return false;
	Destruct();
	if ( iNewStringSize > 0 )
	{
		m_pchString = new char[iNewStringSize];
		if ( m_pchString == NULL )
			return false;
		m_iSize = iNewStringSize;
	}
	return true;
}
