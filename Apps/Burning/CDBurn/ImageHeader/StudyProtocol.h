/********************************************************************
File Name:	StudyProtocol.h
Written by: Yang Guang

Copyright(C) XinaoMDT, 2001 -

Purpose:
	This file defines following classes:

History:
	2002/3/28	Created.
*********************************************************************/

#if !defined(AFX_STUDYPROTOCOL_H__AF2BC97A_CFBC_4CF9_91F0_811CA37AA9D3__INCLUDED_)
#define AFX_STUDYPROTOCOL_H__AF2BC97A_CFBC_4CF9_91F0_811CA37AA9D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning (disable:4786)
#include <vector>
#include "BI_Constants.h"
#include "../BIGlobals/BI_ImageHeader.h"
#include "Study.h"
#include "../BIGlobals/inifile.h"

class CSeriesProtocol;
typedef std::vector<CSeriesProtocol*> CSeriesProtocolContainer;
typedef CSeriesProtocolContainer::iterator CSeriesProtocolIter;
typedef CSeriesProtocolContainer::const_iterator CSeriesProtocolConstIter;

#ifdef IMAGEHEADER_IMP
   #define CLASS_DECL_IMAGEHEADER __declspec(dllexport)
#else
   #define CLASS_DECL_IMAGEHEADER __declspec(dllimport)
#endif

struct CStudyProtocolField
{
    char m_achTag[4];                       //!< "BIP\0"
    //! Version of the field format: (major_version << 16) + lower_version.
    unsigned int    m_uFormatVersion;	
    unsigned int    m_uSize;		        //!< Size of this field.
    unsigned char   m_ucNumSeries;          //!< Number of series.
    char            m_achDesc[128];	        //!< Description of protocol
    unsigned short	m_usProtocolVersion;	//!< Version of protocol used.
    BIDateTime	    m_timeCreated;          //!< Date/time of creation.
    char 	        m_achCreator[16];       //!< ID of the protocol creator.
    EBodyPosition   m_BodyPosition;         //!< Position of the patient.
    EBodyEntry      m_BodyEntry;            //!< Entry of the patient.
    EBodyPart       m_PatBodyPart;          //!< Part of body examined.
    ELandmarkPosition m_LandmarkPos;        //!< Scan landmark position reference. 
    char            m_achGradientId[32];	//!< ID of Gradient coil.
};

//! This class is used to store a study protocol.
/*!
	A study protocol is simply a template for generating study
*/
class CLASS_DECL_IMAGEHEADER CStudyProtocol  
{
public:
    enum EProtocolType
    {
        ptUnknown,
        ptSystem,
        ptUser,
        ptUnsorted,
    };

    //! Container used to hold series protocols.
	CSeriesProtocolContainer m_SeriesProtocols;
public:
	//! \name Constructors and destructor
	//@{
	//! Constructor.
	CStudyProtocol();
    explicit CStudyProtocol(const CStudy& study, std::string strName = "");
	//! Destructor.
	virtual ~CStudyProtocol();
	//@}

    const CStudyProtocol& operator= (const CStudy& study);

	//! Returns pointer to the series protocol container.
    CSeriesProtocolContainer& GetSeriesProtocols()
    {
        return m_SeriesProtocols;
    }
	//! Returns pointer to the series protocol container.
    const CSeriesProtocolContainer& GetSeriesProtocols() const
    {
        return m_SeriesProtocols;
    }

    //! Save the protocol to file.
    bool Save(EProtocolType type);

    //! Load the protocol from file.
    bool Load(EProtocolType type, std::string strName = "",
        unsigned short usVersion = 256 /* version 1.0 */);
	//begin dolphin
	bool Save(CIniFile& inifile,EProtocolType type);

    bool Load(CIniFile& inifile,EProtocolType type, std::string strName = "",
        unsigned short usVersion = 256 /* version 1.0 */);
	//end
	CStudyProtocolField& Params()
	{
		return m_Parameters;
	}
	const CStudyProtocolField& Params() const
	{
		return m_Parameters;
	}
	std::string& GetName()
	{
		return m_strName;
	}
	const std::string& GetName() const
	{
		return m_strName;
	}
	void SetName(const std::string& strName)
	{
		m_strName = strName;
	}
    //! Create a new study based on this protocol.
    CStudy* CreateStudy() const;

protected:
    CStudyProtocolField m_Parameters;
    std::string GetProtocolSubDirectory(EProtocolType type);
    static bool SetRootDirectory(const std::string& strRoot);

    EProtocolType       m_Type;
    std::string         m_strName;
    static std::string  s_strRoot;
};

#endif // !defined(AFX_STUDYPROTOCOL_H__AF2BC97A_CFBC_4CF9_91F0_811CA37AA9D3__INCLUDED_)
