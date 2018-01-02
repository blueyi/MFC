#ifndef _MATEXCEPTION_INCLUDED
#define _MATEXCEPTION_INCLUDED


#include <vector>
#include <tchar.h>

// Throw a first exception, without parent exception
#define EXCEP(/*const wchar_t * */ desc, /*const wchar_t * */ from) throw( MATExceptions(__LINE__,  _T(__FILE__), 0, from, desc) );

// Throw an exception with its parents exceptions: chain of exceptions
#define REEXCEP(/*const wchar_t * */ desc, /*const wchar_t * */ from, /*MATExceptions*/ e) e.add(__LINE__,  __FILE__, 0, from, desc); throw(e);


class MATException
{
	long m_line;
	long m_level;
	std::wstring m_file;
	std::wstring m_from;
	std::wstring m_desc;

public:

	MATException(long line, const wchar_t *file, long level, const wchar_t *from, const wchar_t *desc);
	MATException( const MATException &obj );
	MATException& operator=(const MATException &obj);

	long getLine()const{ return m_line; } 
	long getLevel()const{ return m_level; } 
	std::wstring getFile()const{ return m_file; }
	std::wstring getFrom()const{ return m_from; }
	std::wstring getDesc()const{ return m_desc; }	
};

class MATExceptions
{
	std::vector<MATException> m_exceptions;

public:

	MATExceptions();
	MATExceptions(long line, const wchar_t *file, long level, const wchar_t *from, const wchar_t *desc);
	MATExceptions( const MATExceptions &obj );
	MATExceptions& operator=(const MATExceptions &obj );

	void add( long line, const wchar_t *file, long level, const wchar_t *from, const wchar_t *desc);
	void add( const MATExceptions &e );
	int size()const;
	const MATException* getException(int pos)const;
	std::wstring getAllExceptionStr();
};



#endif

