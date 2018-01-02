// FileFind.cpp: implementation of the CFileFind class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileFind.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileFind::CFileFind(const std::vector<std::string>&filter)
{
	m_filter=filter;
	if(m_filter.size)
		m_end=false;
	else
		m_end=true;
	
}

CFileFind::~CFileFind()
{

}

CFileFind& CFileFind::end()
{
	CFileFind end(const std::vector<std::string>());
	return end;

}
bool CFileFind::operator!=(CFileFind&right)
{
	return !m_end;
}
std::string CFileFind::operator * ()
{
	return std::string ();
}

void CFileFind::NextFit()
{

}

CFileFind CFileFind::begin()
{
return *this;
}
