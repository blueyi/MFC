// FileGfxInterface.h: interface for the CFileGfxInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEGFXINTERFACE_H__1610038E_5F25_4B52_BD4E_6A7F372002B0__INCLUDED_)
#define AFX_FILEGFXINTERFACE_H__1610038E_5F25_4B52_BD4E_6A7F372002B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GfxInterface.h"

namespace gfxinterface
{


/* \brief

  \ingroup IGfxGroup

  Intermidate class for Graphic format based on files (such as eps, or svg)
*/
class CFileGfxInterface : public CGfxInterface  
{
public:
	CFileGfxInterface(const char* sFileName = "untitled");
	virtual ~CFileGfxInterface();

	virtual bool Open(const char* filename = NULL);
	virtual void Close();

	//! Sets the creator name in file header
	void SetCreator(const char* str);
	//! Sets image title
	void SetTitle(const char* str);
	//! Sets creation date
	void SetCreationDate(const char* str);

protected:
	std::string m_sFileName;
	std::string m_sCreator;
	std::string m_sTitle;
	std::string m_sCreationDate;
	std::ofstream m_file;
};

}
#endif // !defined(AFX_FILEGFXINTERFACE_H__1610038E_5F25_4B52_BD4E_6A7F372002B0__INCLUDED_)
