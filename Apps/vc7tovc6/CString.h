
#pragma once

#include <stdio.h>
#include <string.h>
#include <malloc.h> // for _alloca (allocation on stack)
#include <mbstring.h>

// --------------------------------------------------------------------------------
//
//
//	CString class : exposes the equivalent of the MFC API, without the MFC.
//
//
//
class CString
{
	// Members
protected:
	char *m_str;

	// Constructor/Destructor
public:
	CString() 
	{ 
		m_str = NULL;
	}
	CString( char *szInputSource) 
	{ 
		m_str = NULL;
		if (szInputSource)
			Copy(szInputSource);
	}
	CString(const CString &szInputSource) 
	{ 
		m_str = NULL;
		Copy(szInputSource.GetData());
	}
	~CString()
	{
		Empty();
	}

// Methods
public:
	void Empty()
	{
		if (m_str)
		{
			free( m_str ); 
			m_str = NULL;
		}
	}

	long GetLength() const
	{ 
		return m_str ? strlen(m_str) : 0; 
	}

	bool IsEmpty() const
	{
		return GetLength()==0;
	}

	char *GetData() const
	{
		return (char*) m_str;
	}

	char *GetBuffer(int index)
	{
		return & m_str[index];
	}

	operator char*()
	{
		return GetData();
	}

	char GetAt(long nIndex)
	{
		return nIndex<GetLength() ? m_str[nIndex] : 0;
	}

	char RawGetAt(long nIndex) // no sanity check, use only in performance issues
	{
		return m_str[nIndex];
	}

	char operator[](long nIndex)
	{
		return GetAt(nIndex);
	}

	void SetAt(long nIndex, char ch)
	{
		if (nIndex<GetLength())
			m_str[nIndex] = ch;
	}

	void RawSetAt(long nIndex, char ch) // no sanity check, use only in performance issues
	{
		m_str[nIndex] = ch;
	}

	void Copy(char *szInputSource)
	{
		Empty();

		if (!szInputSource) return;

		long len = strlen(szInputSource);
		if (szInputSource && len>0)
		{
			m_str = (char*) malloc(len+1);
			if (m_str) strcpy(m_str, szInputSource);
		}
	}

	void Copy(const CString &szInputSource)
	{
		Copy( szInputSource.GetData() );
	}

	void operator =(char *szInputSource)
	{
		Copy( szInputSource );
	}

	void operator =(const CString &szInputSource)
	{
		Copy( szInputSource );
	}

	void ToLower()
	{
		if (GetLength()>0)
			strlwr(m_str);
	}

	void ToUpper()
	{
		if (GetLength()>0)
			strupr(m_str);
	}

	bool Compare(const char *szCompareString)
	{
		if (!GetData()) return false;

		return szCompareString ? (strcmp(GetData(),szCompareString)==0) : NULL;
	}

	bool Compare(CString &szCompareString)
	{
		if (!GetData()) return false;

		return strcmp(GetData(),szCompareString.GetData())==0;
	}

	bool CompareNoCase(const char *szCompareString)
	{
		if (!GetData()) return false;

		return szCompareString ? (stricmp(GetData(),szCompareString)==0) : NULL;
	}

	bool CompareNoCase(CString &szCompareString)
	{
		if (!GetData()) return false;

		return stricmp(GetData(),szCompareString.GetData())==0;
	}

	bool operator ==(CString &szCompareString)
	{
		return Compare(szCompareString);
	}

	long Find(long nStartIndex, char *szStringToFind) // find string
	{
		if (szStringToFind && nStartIndex<GetLength())
		{
			char *szResult = strstr(m_str+nStartIndex, szStringToFind);
			return szResult ? (long)(szResult - m_str) : -1;
		}
		else
			return -1;
	}

	long Find(long nStartIndex, char sCharToFind) // find char
	{
		char szTemp[2];
		szTemp[0] = sCharToFind;
		szTemp[1] = '\0';

		return Find(nStartIndex, szTemp);
	}

	long FindNoCase(long nStartIndex, char *szStringToFind) // find string (without case)
	{
		if (!szStringToFind)
			return -1;

		CString szTempLower = GetData();
		szTempLower.ToLower();
		CString szStringToFindLower = szStringToFind;
		szStringToFindLower.ToLower();

		return szTempLower.Find(nStartIndex, szStringToFindLower.GetData());
	}

	long FindNoCase(long nStartIndex, char szCharToFind) // find char (without case)
	{
		char szTemp[2];
		szTemp[0] = szCharToFind;
		szTemp[1] = '\0';

		return FindNoCase(nStartIndex, szTemp);
	}

	long ReverseFind(long nStartIndex, char ch)
	{
		if (nStartIndex<GetLength())
		{
			char *szResult =(char*) _mbsrchr (((const unsigned char *)(m_str+nStartIndex)), ch);
			return szResult ? (long)(szResult - m_str) : -1;
		}
		else
			return -1;
	}

	CString Left(long nCount)
	{
		CString temp;
		char *szTemp=(char*) malloc(nCount+1);
		szTemp[0]='\0';
		if (nCount>0 && GetLength()>0)
		{
			strncat(szTemp, m_str, nCount>GetLength() ? GetLength() : nCount);
			strcat(szTemp, "\0");
		}
		temp = szTemp;
		free(szTemp);
		return temp;
	}

	CString ExcludeLeft(long nCount) // remove first nCount chars
	{
		return Right(GetLength()-nCount);
	}

	CString Mid(long nIndex, long nCount)
	{
		CString temp;
		char *szTemp=(char*) malloc(nCount+1);
		szTemp[0]='\0';
		if (nIndex>=0 && nCount>0 && GetLength()>0)
		{
			strncat(szTemp, m_str+nIndex, (nCount+nIndex)>GetLength() ? GetLength()-nIndex : nCount);
			strcat(szTemp, "\0");
		}
		temp = szTemp;
		free(szTemp);
		return temp;
	}

	CString Right(long nCount)
	{
		return Mid(GetLength()-nCount, nCount);
	}

	void InternalLeft(long nCount) //  applies to *this* object
	{
		CString t;
		t = Left(nCount);
		*this = t;
	}

	void InternalExcludeLeft(long nCount) // remove first nCount chars,  applies to *this* object
	{
		InternalRight(GetLength()-nCount);
	}

	void InternalMid(long nIndex, long nCount) //  applies to *this* object
	{
		CString t;
		t = Mid(nIndex,nCount);
		*this = t;
	}

	void InternalRight(long nCount) //  applies to *this* object
	{
		InternalMid(GetLength()-nCount, nCount);
	}


//CString st = sParams.Tokenize(",",iStart);

	CString Tokenize(char *szTokens, long &nStartIndex)
	{
		CString s;
		if (nStartIndex<0 || nStartIndex>=GetLength())
			return s;

		if (strlen(szTokens)==0)
			return s;

		char c = szTokens[0];
		// long Find(long nStartIndex, char *szStringToFind) // find string
		long nIndex = Find(nStartIndex, c);
		if (nIndex<0)
		{
			s = ExcludeLeft(nStartIndex); // copy current string
			nStartIndex = GetLength();
		}
		else
		{
			s = Mid(nStartIndex,nIndex-nStartIndex);
			nStartIndex = nIndex+1;
		}

		return s;
	}

	void Append(char *szAdditionalString)
	{
		if (!m_str)
			Copy(szAdditionalString);
		else
		{
			long n = strlen(szAdditionalString);
			if (n>0)
			{
				long nCurLength = GetLength();
				char *tempbuf = (char*) _alloca( nCurLength );
				memcpy(tempbuf, m_str, nCurLength);
				m_str = (char*) realloc (m_str, nCurLength+n+1 );
				memcpy(m_str, tempbuf, nCurLength);
				m_str[nCurLength]='\0'; // force EOL
				strcat(GetData(),szAdditionalString);
			}
		}
	}

	void Append(CString &szAdditionalString)
	{
		if (!szAdditionalString.IsEmpty())
			Append( szAdditionalString.GetData() );
	}

	void Append(char sAdditionalChar)
	{
		char szAdditionalString[2];
		szAdditionalString[0] = sAdditionalChar;
		szAdditionalString[1] = '\0';
		Append(szAdditionalString);
	}

	void operator +=(CString &szAdditionalString)
	{
		Append(szAdditionalString);
	}

	void operator +=(char *szAdditionalString)
	{
		Append(szAdditionalString);
	}

	void operator +=(char sAdditionalChar)
	{
		Append(sAdditionalChar);
	}

	CString operator +(CString &szAdditionalString)
	{
		CString szTemp = *this;
		szTemp.Append(szAdditionalString);
		return szTemp;
	}

	CString operator +(char *szAdditionalString)
	{
		CString szTemp = *this;
		szTemp.Append(szAdditionalString);
		return szTemp;
	}

	CString operator +(char sAdditionalChar)
	{
		CString szTemp = *this;
		szTemp.Append(sAdditionalChar);
		return szTemp;
	}

// binary + operator (global, with const parameters)
	friend CString operator+(const CString &sz1, const CString &sz2)
	{
		CString s = sz1;
		s += (CString&)sz2;
		return s;
	}

	friend CString operator+(CString &sz1, const char *sz2)
	{
		CString s = sz1;
		s += (char*)sz2;
		return s;
	}

	friend CString operator+(const char *sz1, CString &sz2)
	{
		CString s = (char*)sz1;
		s += sz2;
		return s;
	}


	void TrimLeft(char ch=' ')
	{
		if (IsEmpty())
			return;
		
		long nSize = GetLength();
		long nAmount = 0;
		bool bContinue = true;
		for (long i=0; i<nSize && bContinue; i++)
		{
			if (RawGetAt(i)==ch)
				nAmount++;
			else
				bContinue = false;
		}

		if (!bContinue || nAmount>0)
			InternalExcludeLeft( nAmount );
	}

	void TrimRight(char ch=' ')
	{
		if (IsEmpty())
			return;
		
		long nSize = GetLength();
		long nAmount = 0;
		bool bContinue = true;
		for (long i=0; i<nSize && bContinue; i++)
		{
			if (RawGetAt(nSize-1-i)==ch)
				nAmount++;
			else
				bContinue = false;
		}

		if (!bContinue || nAmount>0)
			InternalLeft( GetLength()-nAmount );
	}

	void Trim(char ch=' ')
	{
		TrimLeft(ch);
		TrimRight(ch);
	}

	long GetNumber()
	{
		if (IsEmpty())
			return 0L;

		long longValue = 0;
		char *c = strpbrk(GetData(), "0123456789.,-+");
		if (c) sscanf(c, "%ld", &longValue); 
		return longValue;
	}

	float GetFloat()
	{
		if (IsEmpty())
			return 0.0f;

		float floatValue = 0;
		char *c = strpbrk(GetData(), "0123456789.,-+");
		if (c) sscanf(c, "%f", &floatValue); 
		return floatValue;
	}


	void ReplaceChar(char ch, char sReplacementChar)
	{
		if (IsEmpty())
			return;

		long nSize = GetLength();
		long nIndex=0;
		long nIndex2;
		while ( nIndex<nSize && (nIndex2=Find(nIndex,ch))>-1 )
		{
			RawSetAt( nIndex2, sReplacementChar);

			nIndex = ++nIndex2; // ensure no infinite loop trap
			
			// loop
		}
	}

	void ReplaceCharWithString(char ch, char *szReplacementString) // szReplacementString==NULL allowed
	{
		if (IsEmpty())
			return;

		CString szTemp;
		long nSize = GetLength();
		long nIndex=0;
		long nIndex2;
		while ( nIndex<nSize && (nIndex2=Find(nIndex,ch))>-1 )
		{
			// copy first portion of string
			if (nIndex2>nIndex)
			{
				szTemp += Mid(nIndex, nIndex2-nIndex);
			}

			// then copy replacement string
			if (szReplacementString)
			{
				szTemp += szReplacementString;
			}

			nIndex = ++nIndex2; // ensure no infinite loop trap
			
			// loop
		}

		// don't forget to copy the remainder of the input string, if any
		if (nIndex<nSize)
			szTemp += ExcludeLeft(nIndex);

		*this = szTemp;
	}

	void ReplaceCharWithString(char ch, CString &szReplacementString)
	{
		ReplaceCharWithString(ch, szReplacementString.GetData() );
	}


	void Format(LPSTR pszFormat, ...) // do not use, m_str does not have the right buffer allocated
	{ // missing here is a preliminary loop that sums the amount of bytes required to expand pszFormat according to argList %s, %d, ...
		va_list argList;
		va_start(argList, pszFormat);
		vsprintf(m_str, pszFormat, argList ); 
		va_end(argList);
	}

	BSTR AllocSysString() const
	{
#if defined(_UNICODE) || defined(OLE2ANSI)
		BSTR bstr = ::SysAllocStringLen(m_str, GetLength());
#else
		int nLen = ::MultiByteToWideChar(CP_ACP, 0, m_str, GetLength(), NULL, NULL);
		BSTR bstr = ::SysAllocStringLen(NULL, nLen);
		::MultiByteToWideChar(CP_ACP, 0, m_str, GetLength(), bstr, nLen);
#endif

		return bstr;
	}



}; 

typedef CString &RString;



