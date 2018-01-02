// FileGfxInterface.cpp: implementation of the CFileGfxInterface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileGfxInterface.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace gfxinterface
{

CFileGfxInterface::CFileGfxInterface(const char* sFileName)
: CGfxInterface()
{
	m_sFileName = sFileName;
}

CFileGfxInterface::~CFileGfxInterface()
{

}

void CFileGfxInterface::SetCreator(const char *str)
{
	_ASSERT(str);
	m_sCreator=str;
}

void CFileGfxInterface::SetTitle(const char *str)
{
	_ASSERT(str);
	m_sTitle=str;
}

void CFileGfxInterface::SetCreationDate(const char *str)
{
	_ASSERT(str);
	m_sCreationDate=str;
}

bool CFileGfxInterface::Open(const char* filename)
{
	if (filename)
		m_sFileName=filename;

	m_file.open(m_sFileName.c_str());
	return !m_file.fail() ;
}

void CFileGfxInterface::Close()
{
	m_file.close();
}

}
