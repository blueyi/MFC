/********************************************************************
File Name:	StudyProtocol.cpp
Written by: Yang Guang

Copyright(C) XinaoMDT, 2001 -

Purpose:
	This file defines following classes:

History:
	2002/3/28	Created.
*********************************************************************/

#include "stdafx.h"
#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>

#include "StudyProtocol.h"
#include "SeriesProtocol.h"

#include "../BIGlobals/ConfigManager.h"

std::string CStudyProtocol::s_strRoot = "";

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStudyProtocol::CStudyProtocol()
{
	s_strRoot = CConfigManager::GetHandle().GetProtocolDirectory();

    memset(&m_Parameters, 0, sizeof(CStudyProtocolField));

    strcpy(m_Parameters.m_achTag, "BIP");
    m_Parameters.m_uFormatVersion = 1 << 16;    // version 1.0
    m_Parameters.m_uSize = sizeof (CStudyProtocolField);
    m_Parameters.m_usProtocolVersion = 1 << 8;       // version 1.0
    m_Type = ptUnknown;
}

CStudyProtocol::~CStudyProtocol()
{
    for (CSeriesProtocolIter it = m_SeriesProtocols.begin(); it !=
        m_SeriesProtocols.end(); ++it)
    {
        delete (*it);
    }
}

CStudyProtocol::CStudyProtocol(const CStudy& study, 
                               std::string strName)
{
	s_strRoot = CConfigManager::GetHandle().GetProtocolDirectory();

    memset(&m_Parameters, 0, sizeof(CStudyProtocolField));
    strcpy(m_Parameters.m_achTag, "BIP");
    // high word - major version, lower word - minor version
    m_Parameters.m_uFormatVersion = 1 << 16;    // version 1.0
    m_Parameters.m_uSize = sizeof (CStudyProtocolField);
    // high byte - major version, lower byte - minor version
    m_Parameters.m_usProtocolVersion = 1 << 8;       // version 1.0
    m_Type = ptUnknown;

    m_Parameters.m_uSize = sizeof (CStudyProtocolField);		    
    m_Parameters.m_ucNumSeries = study.GetSeries().size();

    strcpy(m_Parameters.m_achCreator, study.StudyParams().OperatorID);   

    m_Parameters.m_BodyPosition = 
        static_cast<EBodyPosition>(study.StudyParams().PatPosition);     
    m_Parameters.m_BodyEntry = 
        static_cast<EBodyEntry>(study.StudyParams().PatEntry);        
    m_Parameters.m_PatBodyPart = 
        static_cast<EBodyPart>(study.StudyParams().PatBodyPart);
    m_Parameters.m_LandmarkPos = 
        static_cast<ELandmarkPosition>(study.StudyParams().LandmarkPos);

    strcpy(m_Parameters.m_achGradientId, study.StudyParams().GradientId);

    COleDateTime dateTime = COleDateTime::GetCurrentTime();
    m_Parameters.m_timeCreated.day = dateTime.GetDay();
    m_Parameters.m_timeCreated.month = dateTime.GetMonth();
    m_Parameters.m_timeCreated.year = dateTime.GetYear();
    m_Parameters.m_timeCreated.second = dateTime.GetSecond();
    m_Parameters.m_timeCreated.minute = dateTime.GetMinute();
    m_Parameters.m_timeCreated .hour = dateTime.GetHour();

    strcpy(m_Parameters.m_achDesc, study.StudyParams().Desc);

    m_strName = strName;

	CSeriesProtocol* pSeriesProtocol = NULL;
	for (CSeriesConstIter it = study.GetSeries().begin()
		; it != study.GetSeries().end(); ++it)
	{
		try 
		{
			pSeriesProtocol = new CSeriesProtocol(*this, *(*it));
		}
		catch(std::bad_alloc& e)
		{
			std::cerr << e.what();
			exit(EXIT_FAILURE);
		}
		m_SeriesProtocols.push_back(pSeriesProtocol);
	}
}

const CStudyProtocol& 
CStudyProtocol::operator= (const CStudy& study)
{
    strcpy(m_Parameters.m_achTag, "BIP");

    m_Parameters.m_uSize = sizeof (CStudyProtocolField);		    
    m_Parameters.m_ucNumSeries = study.GetSeries().size();

    strcpy(m_Parameters.m_achCreator, study.StudyParams().OperatorID);   

    m_Parameters.m_BodyPosition = 
        static_cast<EBodyPosition>(study.StudyParams().PatPosition);     
    m_Parameters.m_BodyEntry = 
        static_cast<EBodyEntry>(study.StudyParams().PatEntry);        
    m_Parameters.m_PatBodyPart = 
        static_cast<EBodyPart>(study.StudyParams().PatBodyPart);
    m_Parameters.m_LandmarkPos = 
        static_cast<ELandmarkPosition>(study.StudyParams().LandmarkPos);

    strcpy(m_Parameters.m_achGradientId, study.StudyParams().GradientId);

    COleDateTime dateTime = COleDateTime::GetCurrentTime();
    m_Parameters.m_timeCreated.day = dateTime.GetDay();
    m_Parameters.m_timeCreated.month = dateTime.GetMonth();
    m_Parameters.m_timeCreated.year = dateTime.GetYear();
    m_Parameters.m_timeCreated.second = dateTime.GetSecond();
    m_Parameters.m_timeCreated.minute = dateTime.GetMinute();
    m_Parameters.m_timeCreated .hour = dateTime.GetHour();

    strcpy(m_Parameters.m_achDesc, study.StudyParams().Desc);

    // create the series protocol as necessary.
	CSeriesProtocol* pSeriesProtocol = NULL;
	for (CSeriesConstIter it = study.GetSeries().begin()
		; it != study.GetSeries().end(); ++it)
	{
		try 
		{
			pSeriesProtocol = new CSeriesProtocol(*this, *(*it));
		}
		catch(std::bad_alloc& e)
		{
			std::cerr << e.what();
			exit(EXIT_FAILURE);
		}
		m_SeriesProtocols.push_back(pSeriesProtocol);
	}

    return (*this);
};

bool CStudyProtocol::Save(EProtocolType type)
{
    std::string strPath = s_strRoot;

    assert(strPath[strPath.size() - 1] == '\\'); 

    strPath += GetProtocolSubDirectory(type);
    
    // Protocol parameters are saved in the file named 
    // <protocol_name>.<version_highbyte>.<version_lowbyte>
    std::stringstream outStream;
    outStream << std::setfill('0') << std::setw(3) 
        << (m_Parameters.m_usProtocolVersion >> 8)
        << '.'
        << std::setfill('0') << std::setw(3) 
        << (m_Parameters.m_usProtocolVersion & 255);

    std::string strFileName = strPath + outStream.str();
    std::ofstream outFile(strFileName.c_str(), 
        std::ios::out | std::ios::binary);

    outFile.write(reinterpret_cast<char*>(&m_Parameters), sizeof(m_Parameters));

    // save the series protocols.

    // number of series protocols.
    int nSeries = m_SeriesProtocols.size();
    outFile.write(reinterpret_cast<char*>(&nSeries), sizeof (int));
    for (int i = 0; i < nSeries; i++)
    {
        m_SeriesProtocols[i]->Save(outFile);
    }

    return true;
}

/************************************************************************/
/* begin dolphin                                                                     */
/************************************************************************/
bool CStudyProtocol::Save(CIniFile& inifile,EProtocolType type)
{
	 std::string strPath = s_strRoot;

    assert(strPath[strPath.size() - 1] == '\\'); 

    strPath += GetProtocolSubDirectory(type);
	    std::stringstream outStream;
    outStream << std::setfill('0') << std::setw(3) 
        << (m_Parameters.m_usProtocolVersion >> 8)
        << '.'
        << std::setfill('0') << std::setw(3) 
        << (m_Parameters.m_usProtocolVersion & 255);

    std::string strFileName = strPath + outStream.str();

	return true;
}

bool CStudyProtocol::Load(CIniFile& inifile,EProtocolType type, std::string strName /* = "" */, unsigned short usVersion /* = 256  */)
{
	return true;
}
/************************************************************************/
/* end                                                                     */
/************************************************************************/             
bool CStudyProtocol::Load(EProtocolType type, 
                          std::string strName, 
                          unsigned short usProtocolVersion)
{
    std::string strPath = s_strRoot;

    assert(strPath[strPath.size() - 1] == '\\'); 

    strPath += GetProtocolSubDirectory(type);
    
    // Protocol parameters are saved in the file named 
    // <protocol_name>.<version_highbyte>.<version_lowbyte>
    std::stringstream outStream;
    outStream << std::setfill('0') << std::setw(3) 
        << (usProtocolVersion >> 8)
        << '.'
        << std::setfill('0') << std::setw(3) 
        << (usProtocolVersion & 255);

    std::string strFileName = strPath + outStream.str();
    std::ifstream inFile(strFileName.c_str(), 
        std::ios::in | std::ios::binary);

    inFile.read(reinterpret_cast<char*>(&m_Parameters), sizeof(m_Parameters));

    // Load series protocols.
    // number of series protocols.

    int nSeries = 0;
    inFile.read(reinterpret_cast<char*>(&nSeries), sizeof (int));
    for (int i = 0; i < nSeries; i++)
    {
        CSeriesProtocol* pSeries = NULL;
        try
        {
            pSeries = new CSeriesProtocol(*this);
        }
		catch(std::bad_alloc& e)
		{
			std::cerr << e.what();
			exit(EXIT_FAILURE);
		}

        m_SeriesProtocols[i]->Load(inFile);
		
    }

    return true;
}

// ! Create a new study based on this protocol.
CStudy* CStudyProtocol::CreateStudy() const
{
	ASSERT(0);
    return NULL;
}

/*!
    This function is used to determine the subdirectory in which the protocol
    is stored. To get the full path of the protocol, you should add 
    "<protocol_root>" before it.
    \note The directory returned by this function is with the trailing '\'
    and without the leading '\'.
*/
std::string 
CStudyProtocol::GetProtocolSubDirectory(EProtocolType type)
{
    std::string strPath;

    switch (type)
    {
    case ptSystem:
        strPath = "system\\";
        break;
    case ptUser:
        strPath = "user\\";
        break;
    case ptUnsorted:
        strPath = "unsorted\\";
        return (strPath + m_strName + "\\");
        break;
    default:
        ASSERT(0);
    }
    
    // For system protocols and user protocols...
    // Use switch instead of string array in case the enumeration values
    // is changed (or new values added) in the future.
    switch(this->m_Parameters.m_PatBodyPart)
    {
	    case bpHead: 
            strPath += "head\\";
            break;
        case bpNeck: 
            strPath += "neck\\"; 
            break;
        case bpShoulder: 
            strPath += "shoulder\\"; 
            break; 
        case bpCervicalSpine: 
            strPath += "cervical_spine\\"; 
            break;
        case bpThoracicSpine: 
            strPath += "thoracic_spine\\"; 
            break; 
		case bpSpine:
			strPath += "spine\\";
        case bpLumberSpine: 
            strPath += "lumber_spine\\"; 
            break;
        case bpChest: 
            strPath += "chest\\"; 
            break;
        case bpBreast: 
            strPath += "breast\\"; 
            break; 
        case bpAbdomen: 
            strPath += "abdomen\\"; 
            break; 
        case bpPelvis: 
            strPath += "pelvis\\"; 
            break; 
        case bpHip: 
            strPath += "hip\\"; 
            break; 
        case bpElbow: 
            strPath += "elbow\\"; 
            break; 
        case bpWrist: 
            strPath += "wrist\\"; 
            break;
        case bpArm: 
            strPath += "arm\\"; 
            break;
        case bpHand: 
            strPath += "hand\\"; 
            break;
        case bpKnee: strPath += "knee\\"; 
            break;
        case bpLeg: strPath += "leg\\"; 
            break;
        case bpAnkle: strPath += "ankle\\"; 
            break;
        case bpFoot: strPath += "foot\\"; 
            break;
        case bpHeart: strPath += "heart\\"; 
            break;
        case bpVascularHead: strPath += "vascular_head\\"; 
            break;
        case bpVascularNeck: 
            strPath += "vascular_neck\\"; 
            break;
        case bpVascularBody: 
            strPath += "vascular_body\\"; 
            break;
        case bpVascularPeripheral: 
            strPath += "vascular_peripheral\\"; 
            break;
		//Added by Tom, --2008.07.10
		case bpLung:
			strPath += "chest\\"; 
			break;
		case bpLiver:
		case bpKidney:
			strPath += "abdomen\\"; 
            break; 
        default:
            ASSERT(0);

    }
    return (strPath + m_strName + ".");
}

bool CStudyProtocol::SetRootDirectory(const std::string& strRoot)
{
    s_strRoot = strRoot;
    if (s_strRoot[s_strRoot.size() - 1] != '\\')
        s_strRoot += "\\";

    return true;
}
