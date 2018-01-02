#include "MATException.h"


/***************************************************
*** MATException */

MATException::MATException(long line, const wchar_t *file, long level, const wchar_t *from, const wchar_t *desc)
{
	m_line = line;
	m_file = file;
	m_level = level;
	m_from = from;
	m_desc = desc;	
}

MATException::MATException( const MATException &obj )
{
	operator=(obj);
}


MATException& MATException::operator=(const MATException &obj)
{
	m_line = obj.getLine();
	m_file = obj.getFile();
	m_level = obj.getLevel();
	m_from = obj.getFrom();
	m_desc = obj.getDesc();

	return *this;
}

/***************************************************
*** MATExceptions */


MATExceptions::MATExceptions()
{


}

MATExceptions::MATExceptions(long line, const wchar_t *file, long level, const wchar_t *from, const wchar_t *desc)
{
	add(line, file, level, from, desc);
}

MATExceptions::MATExceptions( const MATExceptions &obj )
{	
	operator=(obj);
}

MATExceptions& MATExceptions::operator=(const MATExceptions &obj )
{
	m_exceptions = obj.m_exceptions;
	return *this;
}

void MATExceptions::add( long line, const wchar_t *file, long level, const wchar_t *from, const wchar_t *desc)
{
	MATException excep(line, file, level, from, desc);
	// on insère au début pour avoir l'ordre du plus récent au plus ancien
	m_exceptions.insert(m_exceptions.begin(), excep);	
}

void MATExceptions::add( const MATExceptions &e )
{
	long size = e.size();

	for( long t=0; t<size; t++ )
	{
		MATException excep(*e.getException(t));		

		m_exceptions.insert(m_exceptions.begin(), excep);
	}

}

int MATExceptions::size()const
{
	return m_exceptions.size();
}
const MATException* MATExceptions::getException(int pos)const
{
	return &m_exceptions[pos];
}

/*****************************************

  Retourne une string contenant la description de
  toutes les exceptions

*****************************************/
std::wstring MATExceptions::getAllExceptionStr()
{
	int nbExeptions = size();
	std::wstring str;

	for( int t=0; t<nbExeptions; t++ )
	{
		str += getException(t)->getDesc();
		str += _T("> ");	
	}

	return str;
}
