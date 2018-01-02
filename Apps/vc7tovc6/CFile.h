
#pragma once

#include <fcntl.h> // filecontrol : _O_RDONLY symbol and other stuff
#include <tchar.h> // _fgetts ==> fgets
#include <stdio.h>
#include <io.h>
#include <windows.h>
#include "CString.h"



class CFile
{
	// Members
protected:
	UINT		m_hFile; // handle to actual file (created by ::CreateFile WIN32 API)
	BOOL		m_bCloseOnDelete;
	CString		m_strFileName;


public:
// Flag values
	enum OpenFlags {
		modeRead =          0x0000,
		modeWrite =         0x0001,
		modeReadWrite =     0x0002,
		shareCompat =       0x0000,
		shareExclusive =    0x0010,
		shareDenyWrite =    0x0020,
		shareDenyRead =     0x0030,
		shareDenyNone =     0x0040,
		modeNoInherit =     0x0080,
		modeCreate =        0x1000,
		modeNoTruncate =    0x2000,
		typeText =          0x4000, // typeText and typeBinary are used in
		typeBinary =   (int)0x8000 // derived classes only
		};

	enum SeekPosition { 
		begin = 0x0, 
		current = 0x1, 
		end = 0x2 };

	enum { hFileNull = -1 };

	// Constructor/Destructor
public:
	CFile()
	{
		m_hFile = (UINT) hFileNull;
		m_bCloseOnDelete = FALSE;
	}
	~CFile()
	{
		if (m_hFile != (UINT)hFileNull && m_bCloseOnDelete)
			Close();
	}

	// Methods
public:
	BOOL Open(LPCTSTR lpszFileName, UINT nOpenFlags)
	{
		// CFile objects are always binary and CreateFile does not need flag
		nOpenFlags &= ~(UINT)typeBinary;

		m_bCloseOnDelete = FALSE;
		m_hFile = (UINT)hFileNull;
		m_strFileName.Empty();

		// map read/write mode
		DWORD dwAccess = 0;
		switch (nOpenFlags & 3)
		{
			case modeRead:
				dwAccess = GENERIC_READ;
				break;
			case modeWrite:
				dwAccess = GENERIC_WRITE;
				break;
			case modeReadWrite:
				dwAccess = GENERIC_READ|GENERIC_WRITE;
				break;
			default:
				;  // invalid share mode
		}

		// map share mode
		DWORD dwShareMode = 0;
		switch (nOpenFlags & 0x70)    // map compatibility mode to exclusive
		{
			default:
				;  // invalid share mode?
			case shareCompat:
			case shareExclusive:
				dwShareMode = 0;
				break;
			case shareDenyWrite:
				dwShareMode = FILE_SHARE_READ;
				break;
			case shareDenyRead:
				dwShareMode = FILE_SHARE_WRITE;
				break;
			case shareDenyNone:
				dwShareMode = FILE_SHARE_WRITE|FILE_SHARE_READ;
				break;
		}

		// map modeNoInherit flag
		SECURITY_ATTRIBUTES sa;
		sa.nLength = sizeof(sa);
		sa.lpSecurityDescriptor = NULL;
		sa.bInheritHandle = (nOpenFlags & modeNoInherit) == 0;

		// map creation flags
		DWORD dwCreateFlag;
		if (nOpenFlags & modeCreate)
		{
			if (nOpenFlags & modeNoTruncate)
				dwCreateFlag = OPEN_ALWAYS;
			else
				dwCreateFlag = CREATE_ALWAYS;
		}
		else
			dwCreateFlag = OPEN_EXISTING;

		// attempt file creation
		HANDLE hFile = ::CreateFile(lpszFileName, dwAccess, dwShareMode, &sa,
			dwCreateFlag, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
			return FALSE;

		m_hFile = (HFILE)hFile;
		m_bCloseOnDelete = TRUE;

		return TRUE;
	}

	LONG Seek( LONG lOff, UINT nFrom )
	{
		if (m_hFile == (UINT)hFileNull)	return 0;

		return 	::SetFilePointer((HANDLE)m_hFile, lOff, NULL, (DWORD)nFrom);
	}

	DWORD SeekToEnd()
	{
		return Seek(0, CFile::end);
	}


	UINT Read(void* lpBuf, UINT nCount)
	{
		if (nCount == 0) return 0;   // avoid Win32 "null-read"

		DWORD dwRead = 0;
		
		::ReadFile((HANDLE)m_hFile, lpBuf, nCount, &dwRead, NULL);

		return (UINT)dwRead;
	}

	BOOL ReadEntireFile(/*out*/CString &szContent)
	{
		szContent.Empty();

		char buf[4096+1];
		UINT nRead;
		while ( (nRead=Read(buf,4096))>0 )
		{
			buf[nRead]='\0'; // force EOL
			szContent += buf;
		}

		return szContent.GetLength()>0;
	}

	void Write( const void* lpBuf, UINT nCount )
	{
		if (m_hFile == (UINT)hFileNull)	return;

		if (nCount == 0)
			return;     // avoid Win32 "null-write" option

		DWORD nWritten;
	    ::WriteFile((HANDLE)m_hFile, lpBuf, nCount, &nWritten, NULL);
	}

	void Write(CString &s)
	{
		if (!s.IsEmpty())
			Write(s.GetData(), s.GetLength());
	}

	void Flush()
	{
		if (m_hFile == (UINT)hFileNull)	return;

		::FlushFileBuffers((HANDLE)m_hFile);
	}

	void Close()
	{
		if (m_hFile != (UINT)hFileNull)
			::CloseHandle((HANDLE)m_hFile);

		m_hFile = (UINT) hFileNull;
		m_bCloseOnDelete = FALSE;
		m_strFileName.Empty();
	}


};




class CStdioFile : public CFile
{
	// Members
protected:
	FILE*		m_pStream;

	// Constructor/Destructor
public:

	CStdioFile()
	{
		m_pStream = NULL;
	}

	~CStdioFile()
	{
		if (m_pStream != NULL && m_bCloseOnDelete)
			Close();
	}


	// Methods
public:
	BOOL Open(LPCTSTR lpszFileName, UINT nOpenFlags)
	{
		m_pStream = NULL;

		if (!CFile::Open(lpszFileName, (nOpenFlags & ~typeText)))
			return FALSE;

		char szMode[4]; // C-runtime open string
		int nMode = 0;

		// determine read/write mode depending on CFile mode
		if (nOpenFlags & modeCreate)
		{
			if (nOpenFlags & modeNoTruncate)
				szMode[nMode++] = 'a';
			else
				szMode[nMode++] = 'w';
		}
		else if (nOpenFlags & modeWrite)
			szMode[nMode++] = 'a';
		else
			szMode[nMode++] = 'r';

		// add '+' if necessary (when read/write modes mismatched)
		if (szMode[0] == 'r' && (nOpenFlags & modeReadWrite) ||
			szMode[0] != 'r' && !(nOpenFlags & modeWrite))
		{
			// current szMode mismatched, need to add '+' to fix
			szMode[nMode++] = '+';
		}

		// will be inverted if not necessary
		int nFlags = _O_RDONLY|_O_TEXT;
		if (nOpenFlags & (modeWrite|modeReadWrite))
			nFlags ^= _O_RDONLY;

		if (nOpenFlags & typeBinary)
			szMode[nMode++] = 'b', nFlags ^= _O_TEXT;
		else
			szMode[nMode++] = 't';
		szMode[nMode++] = '\0';

		// open a C-runtime low-level file handle
		int nHandle = _open_osfhandle(m_hFile, nFlags);

		// open a C-runtime stream from that handle
		if (nHandle != -1)
			m_pStream = _fdopen(nHandle, szMode);

		if (m_pStream == NULL)
		{
			return FALSE;
		}

		return TRUE;
	}


	BOOL ReadString(CString& rString)
	{
		rString.Empty();

		const int nMaxSize = 256;
		char lpsz[nMaxSize+1];
		LPTSTR lpszResult;
		int nLen = 0;
		for (;;)
		{
			lpsz[0]='\0';

			lpszResult = _fgetts(lpsz, nMaxSize+1, m_pStream);

			// handle error/eof case
			if (lpszResult == NULL && !feof(m_pStream))
			{
				break;
			}

			nLen = lstrlen(lpsz);
			rString += lpsz;

			// if string is read completely or EOF
			if (lpszResult == NULL ||
				nLen<nMaxSize ||
				lpsz[nLen-1] == '\n')
				break;
			
		}

		// remove '\n' from end of string if present
		nLen = rString.GetLength();
		if (nLen != 0 && rString.GetAt(nLen-1) == '\n')
			rString.SetAt(nLen-1,'\0');

		return (lpszResult != NULL);
	}

	void Close()
	{
		int nErr = 0;

		if (m_pStream != NULL)
			nErr = fclose(m_pStream);

		m_hFile = (UINT) hFileNull;
		m_bCloseOnDelete = FALSE;
		m_pStream = NULL;
	}
	

};