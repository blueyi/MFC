#ifndef __SMARTSTRING_H__
#define __SMARTSTRING_H__

#include <stdlib.h>

class CSmartString
{
	char *m_pchString;
	int m_iLength;
	int m_iSize;
	bool m_bIsStringStatic;
	
public:
	CSmartString();

	~CSmartString();

	void operator = (CSmartString &NewString);
	void operator = ( const char* szText );

	bool operator == (CSmartString &CmpString);
	bool operator == (const char *pszCmpString);
	operator const char* ();

	bool Reference(CSmartString &ReferenceString);
	bool Construct(int iStringPoolSize, void *pvStringPool = NULL);
	void Destruct();

	bool SetString(const char *pchNewString, int iNewStringLength = -1);
	const char* GetString();
	int GetLength();
	bool IsEmpty();
	void Empty();
	bool AddChar(char chChar);
	bool Compare(const char *pchCmpString, int iCmpStringLength = -1);
	bool Reallocate(int iNewStringSize);

private:
	CSmartString(CSmartString&);

};

#endif
