// Study.cpp : implementation file
//
#include "stdafx.h"
#include <cassert>
#pragma warning (disable:4786)
#include <iostream>
#include <exception>
#include <sstream>
#include <iomanip>
#include <fstream>

#include "Study.h"
#include "Series.h"
#include "Image.h"
#include "PatientManager.h"
#include "StudyProtocol.h"

#include "../BIGlobals/ConfigManager.h"
//#include "../MRIDatabase/DBInterface.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*
    \param patient Patient of the study.
    \param site Site where this study was carried out.
    \param bOwnSite \a true to delete the site and patient information in the 
    destructor. This parameter should be \a true only when an external study
    (a study carried out in another site) is loaded. It should always be 
    \a false if the study is carried out on this site and thus shares site
    and patient information with other studies at this site.
*/
CStudy::CStudy(CPatient& patient, 
			   SiteField& site, 
			   bool bOwnSite)
{
    // clear the parameter field.
    memset(&m_StudyParams, 0, sizeof(m_StudyParams));

	m_StudyParams.Version = 1 << 16 + 0;	// version 1.0
    m_StudyParams.Size = sizeof(StudyField);

	m_pPatient = &patient;
	
    if (m_bOwnSite)
        m_pPatient->AddRef();

	m_pSiteParams = &site;
	m_pCurrentSeries = NULL;
    m_bCompleteStudy = false;
    m_bOwnSite = bOwnSite;
   //Added by Sun Shang for database function at 2002/09/19
	GetSavedRecordNum()=0;
	m_nProcessPACSTran=FALSE;
	//End.

	/** [zhlxu 2007.10.23] 为限制某些操作增加变量 **/
	m_bDoingMIP = false;
	/** [zhlxu 2007.10.23] **/
	
}

/*
    \param patient Patient of the study.
    \param site Site where this study was carried out.
    \param protocol Study protocol used to create this study.
	\param Id of this study.
*/
CStudy::CStudy(CPatient& patient, 
			   SiteField& site, 
			   const CStudyProtocol& protocol, 
			   const std::string& strStudyID)
{
    // clear the parameter field.
    memset(&m_StudyParams, 0, sizeof(m_StudyParams));
    
	m_pPatient = &patient;
    m_pPatient->AddRef();
    m_bOwnSite = false;
    m_bCompleteStudy = false;
	m_pSiteParams = &site;
   //Added by Sun Shang for database function at 2002/09/19
	GetSavedRecordNum()=0;
	//End.

	// copy all study parameters from the protocol.
	// Note: the data time, Operator ID, Radiologist, RefPhy,  of the study is not set.
	m_StudyParams.Version = 1 << 16 + 0;
	m_StudyParams.Size = sizeof (StudyField);
	strcpy(m_StudyParams.Id, strStudyID.c_str());
	strcpy(m_StudyParams.Protocol, 
		std::string(protocol.GetName(), 0, 31).c_str());

	m_StudyParams.ProtocolVersion = 
		protocol.Params().m_usProtocolVersion;
	m_StudyParams.PatPosition = protocol.Params().m_BodyPosition;
	m_StudyParams.PatEntry = protocol.Params().m_BodyEntry;
	m_StudyParams.PatBodyPart = protocol.Params().m_PatBodyPart;
	m_StudyParams.LandmarkPos = protocol.Params().m_LandmarkPos;
	strcpy(m_StudyParams.GradientId, protocol.Params().m_achGradientId);

	CSeries* pSeries = NULL;
	for (CSeriesProtocolConstIter it = protocol.GetSeriesProtocols().begin()
		; it != protocol.GetSeriesProtocols().end(); ++it)
	{
		try
		{
			/** [zhlxu 2008.1.3] [XABW/CX-31-11-0157] 设置默认的频率编码方向参数 **/
			pSeries = new CSeries(*this, *(*it));
			/** [zhlxu 2008.1.17] [] 解决在新建Study时的第一个Series的图象显示方位不正确的问题 **/			
			pSeries->SeriesParams().nPlaneType = pSeries->SeriesParams().Plane;	
			/** [zhlxu 2008.1.17] **/
			pSeries->RestoreFromDefaultOrientationParams();
			/** [zhlxu 2008.1.3] **/
		}
		catch(std::bad_alloc& e)
		{
			std::cerr<< e.what();
			exit(EXIT_FAILURE);
		}
	}
	m_pCurrentSeries = m_Series[0];

	/** [zhlxu 2007.10.23] 为限制某些操作增加变量 **/
	m_bDoingMIP = false;
	/** [zhlxu 2007.10.23] **/
	/*********zyh add 2008.2.1*********/
	m_nProcessPACSTran=FALSE;
	/**********************************************/
}

//Added by Tom, --2008.07.10
CStudy::CStudy(CPatient *pPatient, 
			   SiteField& site, 
			   bool bOwnSite)
{
    // clear the parameter field.
    memset(&m_StudyParams, 0, sizeof(m_StudyParams));

	m_StudyParams.Version = 1 << 16 + 0;	// version 1.0
    m_StudyParams.Size = sizeof(StudyField);

	m_pPatient = pPatient;
	
    if (m_bOwnSite)
        m_pPatient->AddRef();

	m_pSiteParams = &site;
	m_pCurrentSeries = NULL;
    m_bCompleteStudy = false;
    m_bOwnSite = bOwnSite;
   //Added by Sun Shang for database function at 2002/09/19
	GetSavedRecordNum()=0;
	//End.

}

CStudy::~CStudy()
{
    for (CSeriesIter it = m_Series.begin(); it != m_Series.end(); ++it)
    {
        delete (*it);
    }
    if (m_bOwnSite)
    {
        delete m_pSiteParams;
        delete m_pPatient; 
    }
    else
    {
        m_pPatient->Release();
    }
}

/*
    A study loaded from the disk is always a completed one. Also, once a 
    new study begins to scan, the last scanned study will become completed
    automatically. More strictly, once a series in a new study is marked as 
    ready, the last study should be set to complete. In that sense, while
    a scan is in process, you cannot set a series in a new study to "ready".
    In fact, you have to let the patient in before "ready", so this kind of
    behavior is quite acceptable.
*/
bool CStudy::IsCompleted() const
{
    if (m_bCompleteStudy == true)
        return true;

    for (CSeriesConstIter it = m_Series.begin(); it != m_Series.end(); ++it)
    {
        if ((*it)->GetState() != CSeries::ssComplete)
            return false;
    }
    return true;
}

/*
	If a study contains a scan in scanning progress ('ready' checked till 
	stopped), then it cannot be finished, which means you cannot make a series 
	in next study 'ready'. 
*/
bool CStudy::CanFinish()
{
	if (m_bCompleteStudy)
		return true;

    for (CSeriesConstIter it = m_Series.begin(); it != m_Series.end(); ++it)
    {
        if ((*it)->GetState() != CSeries::ssSetup &&
			(*it)->GetState() != CSeries::ssStopped &&
			(*it)->GetState() != CSeries::ssComplete)
            return false;
    }
    return true;
}

/*
    Once the study is complete, call this function to set a flag. Generally,
    a study is considered to be completed once all its series have been carried
    out and a series in another study is set to "ready to scan".
*/
void CStudy::SetComplete()
{
    m_bCompleteStudy = true;
}

bool CStudy::CreateFolder()
{
    CString strDir = 
        CConfigManager::GetHandle().GetImageRootDirectory().c_str();
    strDir = strDir + StudyParams().Id;

    CFileFind finder;
    if (finder.FindFile(strDir))
    {
		if (finder.FindNextFile())
			{
			if (finder.IsDirectory()) // found, already exist
			{
				finder.Close();
				return true;
			}
			// it can only be directory.
			ASSERT(0);
		}
    }

    return (::CreateDirectory(strDir, NULL) != 0);
}

/*
    \remarks instead of delete the folder directly, we move it to a recycle bin.
*/
bool CStudy::DeleteFolder()
{
    SHFILEOPSTRUCT fileOp;
    CString strDir = 
        CConfigManager::GetHandle().GetImageRootDirectory().c_str();
    strDir = strDir + StudyParams().Id;

    // pFrom field of SHFILEOPSTRUCT requires a double NULL ended string.
    TCHAR* pchFrom = new TCHAR[strDir.GetLength() + 2];
    strcpy (pchFrom, strDir);
    pchFrom[strDir.GetLength() + 1] = '\0';

    CString strDestDir 
        = CConfigManager::GetHandle().GetRecycleDirectory().c_str();
    strDestDir = strDestDir + "Studies\\";

    // pTo field of SHFILEOPSTRUCT requires a double NULL ended string.
    TCHAR* pchTo = new TCHAR[strDestDir.GetLength() + 2];
    strcpy(pchTo, strDestDir);
    pchTo[strDestDir.GetLength() + 1] = '\0';

    fileOp.hwnd = NULL;
    fileOp.wFunc = FO_MOVE;
    fileOp.pFrom = pchFrom;
    fileOp.pTo = pchTo;
    fileOp.fFlags = FOF_NOCONFIRMMKDIR | FOF_NOCONFIRMATION | FOF_SILENT;
    fileOp.hNameMappings = NULL;
    fileOp.lpszProgressTitle = NULL;

    bool bResult =  (::SHFileOperation(&fileOp) == 0);

    delete []pchFrom;
    delete []pchTo;

    return bResult;
}

/*
    This function loads a study from the disk. It assumes the study is stored
    in the default directory, that is (imageroot)\studyID.
*/
/*
    This function loads a study from the disk. It assumes the study is stored
    in the default directory, that is (imageroot)\studyID.
*/

CStudy* CStudy::Load(const CString& strStudyID)
{
    CString strPath  = 
        CConfigManager::GetHandle().GetImageRootDirectory().c_str();
    strPath += strStudyID + "\\";

    bool bFirstImageInStudy = true;
    bool bFirstImageInScan = true;

    CStudy* pStudy = NULL;
    CSeries* pCurrentSeries = NULL;
    CScan* pCurrentScan = NULL;
    CPatient* pPatient = NULL;

    CFileFind seriesFinder;
    BOOL bSeriesAvailable = seriesFinder.FindFile(strPath + "*.*");

    // loop for all series in the study.
    while (bSeriesAvailable)
    {
        bSeriesAvailable = seriesFinder.FindNextFile();

        // for each series, initialize this to null, this should be set 
        // according to the series field data in the first image in the series.
        pCurrentSeries = NULL;
        pCurrentScan = NULL;

        // skip . and .. files
        if (seriesFinder.IsDots())
            continue;

        if (!seriesFinder.IsDirectory())
        {
            // file in the study, maybe we should save a parameter file in 
            // the study folder to acclerate the loading of the study.
            continue;
        }

        CString strSeriesPath = seriesFinder.GetFilePath();

        // for every series, read in every image file.
        CFileFind imageFinder;
        BOOL bImageAvailable = 
            imageFinder.FindFile(strSeriesPath + "\\*.img");

        // loop for all images in the series.
        while (bImageAvailable)
        {
            bImageAvailable = imageFinder.FindNextFile();

            // read in the image file
            CBIImageHeader imageHeader;
            short* pBuffer = CImage::ReadImageFile (
                std::string(imageFinder.GetFilePath()), imageHeader);

            if (pBuffer == NULL)
            {
                // there is an error openning the file
                // note: file sharing error may also cause this
                return NULL;
            }

            if (bFirstImageInStudy)
            {
                // if this is the fist image in the study, we should load
                // study information, site information, patient information
                // from it.

                // check to see if the study comes from this site.
                // create an appropriate study accordingly.
                if (strcmp(imageHeader.siteField.Id,
                    CConfigManager::GetHandle().GetSiteField().Id) != 0)
                {
                    SiteField* pSite = NULL;
                    CPatient* pPatient = NULL;

                    try
                    {
                        pSite = new SiteField;
                        *pSite = imageHeader.siteField;

                        pStudy = new CStudy(*pPatient, *pSite, true);
                        // set the study field parameters.
                        pStudy->StudyParams() = imageHeader.studyField;
                    }
                    catch(std::bad_alloc& e)
                    {
                        std::cerr << e.what();
                        exit(EXIT_FAILURE);
                    }

                }
                else    // study comes from this site
                {
                    CPatient* pPatient = CPatientManager::GetHandle().
                        FindPatient(std::string(imageHeader.patientField.Id));
                    if (pPatient == NULL)
                    {
                        // the patient is not open yet, so create one and add
                        // to the patient manager.
                        try
                        {
                            pPatient = new CPatient(imageHeader.patientField);
                        }
                        catch(std::bad_alloc& e)
                        {
                            std::cerr << e.what();
                            exit(EXIT_FAILURE);
                        }
                        CPatientManager::GetHandle().AddPatient(pPatient);
                    }

                    SiteField* pSite = 
                        &(CConfigManager::GetHandle().GetSiteField());

                    try
                    {
                        pStudy = new CStudy(*pPatient, *pSite, false);
                    }
                    catch(std::bad_alloc& e)
                    {
                        std::cerr << e.what();
                        exit(EXIT_FAILURE);
                    }
                    pStudy->StudyParams() = imageHeader.studyField;
                }

                bFirstImageInStudy = false;
            }   // end if (bFirstImageInStudy)

            // if this is the first series in the study.
            if (pCurrentSeries == NULL) 
            {
                // this is the first image in series, so we need to create
                // a new series.
                try
                {
                    pCurrentSeries = new CSeries(*pStudy);
                    // a series load from file is always a complete one.
                    pCurrentSeries->SetState(CSeries::ssComplete);
					/**BEGIN    [SHCH 26:9:2007   8:29]*********************************/
					pCurrentSeries->SetReconStatus(TRUE);
					/*****END    [SHCH PURPOSE:    ]  ************************************/
					
                    // set the first series as the current series of the study.
                    pStudy->SetCurrentSeries(pCurrentSeries);
                }
                catch(std::bad_alloc& e)
                {
                    std::cerr << e.what();
                    exit(EXIT_FAILURE);
                }
                
                pCurrentSeries->SeriesParams() = imageHeader.seriesField;
            }

            bFirstImageInScan = (pCurrentScan == NULL) ? true :
                pCurrentScan->ScanParams().Id != imageHeader.scanField.Id;

            // if this is the first image in the scan, create a new scan and
            // and it to the series.
            if (bFirstImageInScan)
            {
                try
                {
                    pCurrentScan = new CScan(pCurrentSeries, 
                        true );

					// set the current scan of the series to the first scan.
					if (pCurrentScan->GetSeries()->GetCurrentScan() == NULL)
					{
						pCurrentScan->GetSeries()->SetCurrentScan(pCurrentScan);
					}
                }
                catch(std::bad_alloc& e)
                {
                    std::cerr << e.what();
                    exit(EXIT_FAILURE);
                }
                pCurrentScan->ScanParams() = imageHeader.scanField;
            }
            
            // create a new CImage object and put it to scans and series.
            CImage* pImage = NULL;
            try
            {
                pImage = new CImage(pCurrentScan, imageHeader.imageField.Id);
            }
            catch (std::bad_alloc& e)
            {
                std::cerr << e.what();
                exit(EXIT_FAILURE);
            }
            pImage->ImageParams() = imageHeader.imageField;
            pImage->SetBuffer(pBuffer);

			//Added by Tom, --2008.07.10
 			pImage->m_sImageHeader = imageHeader ;
        } // end while (bImageAvailable)
    }

    return pStudy;    
}


CScan* CStudy::GetReadyScan()
{
	// First round, search for scanning series. If any scan remains ready in 
	// the scanning series, then return pointer to it.
	for (CSeriesIter itSeries = GetSeries().begin()
		; itSeries != GetSeries().end(); ++itSeries)
	{
        if ((*itSeries)->GetState() == CSeries::ssScanning)
        {
            // find the first scan to perform.
            for (CScanIter itScan = (*itSeries)->Scans().begin()
                ; itScan != (*itSeries)->Scans().end(); ++itScan)
            {
                if ((*itScan)->GetScanState() != ssComplete)
                {
                    return *itScan;
                }
            }
        }
	}

	// Second round, search for ready series.
	for (itSeries = GetSeries().begin()
		; itSeries != GetSeries().end(); ++itSeries)
	{
        if ((*itSeries)->GetState() == CSeries::ssReady)
        {
            // find the first scan to perform.
            for (CScanIter itScan = (*itSeries)->Scans().begin()
                ; itScan != (*itSeries)->Scans().end(); ++itScan)
            {
                if ((*itScan)->GetScanState() != ssComplete)
                {
                    return *itScan;
                }
            }
        }
	}

	return NULL;
}

std::string CStudy::GetPath() const
{
	return (CConfigManager::GetHandle().GetImageRootDirectory() 
		+ StudyParams().Id + "\\");
}

CSeries* CStudy::GetSeries(int nSeriesID)
{
    for (int i = 0; i < m_Series.size(); i++)
    {
        if (m_Series[i]->SeriesParams().Id == nSeriesID)
        {
            return (m_Series[i]);
        }
    }

    return NULL;
}

const CSeries* CStudy::GetSeries(int nSeriesID) const
{
    for (int i = 0; i < m_Series.size(); i++)
    {
        if (m_Series[i]->SeriesParams().Id == nSeriesID)
        {
            return (m_Series[i]);
        }
    }

    return NULL;
}


BOOL CStudy::ReorderSeriesByState()
{
	// classify those series in the study into two categories
	CSeries* pSeries = 0;
	CSeriesIter it;
	CSeriesContainer setupSeriesList, otherSeriesList;
	for(it = GetSeries().begin(); it != GetSeries().end(); ++it)
	{
		CSeries* pSeries = (*it);
		if(CSeries::ssSetup == pSeries->GetState())
			setupSeriesList.push_back(pSeries);
		else
			otherSeriesList.push_back(pSeries);
	}

	// clear all
	GetSeries().clear();

	// other part
	for(it = otherSeriesList.begin(); it != otherSeriesList.end(); ++it)
	{
		pSeries = (*it);
		GetSeries().push_back(pSeries);
	}
	otherSeriesList.clear();

	// setup part
	for(it = setupSeriesList.begin(); it != setupSeriesList.end(); ++it)
	{
		pSeries = (*it);
		GetSeries().push_back(pSeries);
	}
	setupSeriesList.clear();


	int ID = 1;
	for(it = GetSeries().begin(); it != GetSeries().end(); ++it)
	{
		pSeries = (*it);
		pSeries->SeriesParams().Id = ID++;
	}

    return TRUE;
}


/*
    Function operator.
    \param pStudy Study whose id is to be compared with the id used to 
    initialize this functor.
*/
bool CompareStudyId::operator()(CStudy* pStudy)
{
    return (pStudy->StudyParams().Id == m_strId);
}

BOOL CStudy::InsertSeriesAfter(CSeries* pSeriesInsert, const CSeries* pSeriesPos /* = NULL */)
{
	if(! pSeriesInsert)
		return FALSE;

	if(FindSeriesIndex(pSeriesInsert) > 0)
	{
		ASSERT(0); // pSeriesInsert一定不在链表中
		return FALSE;
	}

	if(! pSeriesPos)
	{
		GetSeries().push_back(pSeriesInsert);
		pSeriesInsert->SeriesParams().Id = GetSeries().size();
		return TRUE;
	}


	if(FindSeriesIndex(pSeriesPos) <= 0)
	{
		ASSERT(0); // pSeriesPos一定在链表中
		return FALSE;
	}

	// 搜索插入位置
	for(CSeriesIter it = GetSeries().begin(); it != GetSeries().end(); ++it)
	{
		CSeries* pSeries = (*it);
		if(pSeries == pSeriesPos)
		{
			++it;
			break;
		}
	}

	// 插入
	if(it == GetSeries().end())
		GetSeries().push_back(pSeriesInsert);
	else
		GetSeries().insert(it, pSeriesInsert);

	// 对Series的ID进行排序
	return OrderSeriesID();
}

int CStudy::FindSeriesIndex(const CSeries* pSeriesFind)
{
	BOOL bFound = FALSE;
	int nIndex = 0;

	CSeries* pSeries = 0;
	for(CSeriesIter it = GetSeries().begin(); it != GetSeries().end(); ++it)
	{
		nIndex++;
		pSeries = (*it);
		ASSERT(pSeries);
		if(pSeriesFind == pSeries)
		{
			bFound = TRUE;
			ASSERT(nIndex == pSeries->SeriesParams().Id);
			break;
		}
	}

	return bFound? nIndex : 0;
}

BOOL CStudy::OrderSeriesID()
{
	BOOL bChanged = FALSE;
	CSeries* pSeries = 0;
	int nID = 1;
	for(CSeriesIter it = GetSeries().begin(); it != GetSeries().end(); ++it, nID++)
	{
		pSeries = (*it);
		ASSERT(pSeries);
		if(nID != pSeries->SeriesParams().Id)
		{
			bChanged = TRUE;
			pSeries->SeriesParams().Id = nID;
		}
	}

	return bChanged;
}

void CStudy::CheckSeriesID()
{
#ifdef _DEBUG
	CSeries* pSeries = 0;
	int nID = 1;
	for(CSeriesIter it = GetSeries().begin(); it != GetSeries().end(); ++it, nID++)
	{
		pSeries = (*it);
		ASSERT(pSeries);
		ASSERT(nID == pSeries->SeriesParams().Id);
	}
#endif
}

BOOL CStudy::ReorderSeriesByID()
{
	BOOL bChanged = FALSE;

	CSeriesContainer SeriesList;

	CSeries* pSeries = NULL;
	CSeriesIter itMin;
	int nID = -1;
	BOOL bFirst = TRUE;

	while(GetSeries().size() > 0)
	{
		// 1. find the next series with the minimum ID
		nID = -1;
		bFirst = TRUE;

		for(CSeriesIter it = GetSeries().begin(); it != GetSeries().end(); it++)
		{
			pSeries = (*it);
			ASSERT(pSeries);

			if(bFirst)
			{
				bFirst = FALSE;
				nID = pSeries->SeriesParams().Id;
				itMin = it;
			}
			else
			{
				ASSERT(nID != pSeries->SeriesParams().Id); // no duplicate series ID

				if(nID > pSeries->SeriesParams().Id)
				{
					nID = pSeries->SeriesParams().Id;
					itMin = it;
				}
			}
		}

		// 2. insert the series found into the new series list
		if(-1 != nID)
		{
			bChanged = TRUE;

			pSeries = (*itMin);
			ASSERT(pSeries);

			SeriesList.push_back(pSeries);

			m_Series.erase(itMin);
		}
		else
		{
			ASSERT(0); // there must be something wrong somewhere.
		}
	}

	if(bChanged)
	{
		m_Series.clear();

		for(CSeriesIter it = SeriesList.begin(); it != SeriesList.end(); ++it)
		{
			pSeries = (*it);
			ASSERT(pSeries);

			m_Series.push_back(pSeries);
		}
	}

	return bChanged;
}
