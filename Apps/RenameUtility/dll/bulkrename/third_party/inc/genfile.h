#ifndef	__FILE_GEN_H__
#define	__FILE_GEN_H__

#include "Typedefs.h"
#include "stdio.h"

//winbase.h
#define CREATE_ALWAYS       2
#define OPEN_EXISTING       3
#define OPEN_ALWAYS         4

class CGenFile
{
public:
	CGenFile();
	~CGenFile();
	
	FILE* m_fFile;
	char* m_szFileName;
	//Open Flag values.
	bool Open( char* szFileName, const char *mode );
	int Read( void* pBuf, uint* pCount );
	int Write(const void* pBuf, uint nCount );
	bool Seek( long lOffset );
	uint GetPosition();
	void Close();
	uint GetLength();
	static bool IsFile( char* szFile );
	operator FILE*();
	//Reads data from the file to szStr till '\n' is encountered.
	bool ReadLine( char* szStr, uint* pMaxSize );
	//Writes szStr and then writes '\n' to the file.
	bool WriteLine( const char* szStr, int iSize=-1 );
};

#endif	//__FILE_GEN_H__
