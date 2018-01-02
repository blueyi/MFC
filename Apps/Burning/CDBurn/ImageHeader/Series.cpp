// Series.cpp
//

#include "stdafx.h"

#include <iostream>
#include <cassert>

#include "Scan.h"
#include "Image.h"
#include "SeriesProtocol.h"
#include "CDLManager.h"

#include "../CDLParser/CDL.h"
#include "../BIGlobals/ConfigManager.h"
#include "../MRIDatabase/DBInterface.h"

#include "Series.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// 用此构造函数的Series不参加成像
CSeries::CSeries(LPCSTR lpszCDLName)
{
	ASSERT(lpszCDLName);

	/*********zyh add 2008.1.31*********/
	m_bEnableCuting = FALSE;
	/**********************************************/
	
	/*********zyh add 2007.11.4*********/
	m_bIsSendingToPACS = FALSE;
	/**********************************************/
	m_strCDLFile = lpszCDLName;

	m_pStudy = NULL;

	m_nTimeElapsed = 0;
	m_nTimeEstimated = 0;
    m_pCurrentScan = NULL;
   //Added by Sun Shang for database function at 2002/09/19
	GetSavedRecordNum()=0;
	//End.

    m_State = ssComplete;

    // clear all the series parameter.
	memset(&m_SeriesParams, 0, sizeof (SeriesField)); // in this case, SequenceOptions = 0

	//Added by Tom, --2008.07.10
	m_SeriesParams.nInterval = 5 ;

	bool bIsFirstSeries = m_SeriesParams.Id == 1;
	m_SeriesParams.bAdjustRG = 
		CConfigManager::GetHandle().IsTuning(CConfigManager::GetHandle().GetTuneConfig().m_tmDefaultTuneModeRG, bIsFirstSeries);

	m_SeriesParams.bAdjustTG = 
		CConfigManager::GetHandle().IsTuning(CConfigManager::GetHandle().GetTuneConfig().m_tmDefaultTuneModeTG, bIsFirstSeries);

	m_SeriesParams.bTuningRFCoil = 
		CConfigManager::GetHandle().IsTuning(CConfigManager::GetHandle().GetTuneConfig().m_tmDefaultTuneModeRFRcvCoil, bIsFirstSeries);

	m_SeriesParams.bAuto1stShimming3Chn = 
		CConfigManager::GetHandle().IsTuning(CConfigManager::GetHandle().GetTuneConfig().m_tmDefaultTuneModeAutoShim, bIsFirstSeries);
	
	m_ClusterSet.clear();

	m_fScale = -1.0; // invalid if negative
	/**    [SHCH 26:9:2007   10:52  PURPOSE:]    **/
	m_bReconFinished=TRUE;
	m_nSelMipAxis=0;
	/**    [SHCH END]    **/

	/** [GMWU 070915] 缺省不自动计算TE/TR **/
	m_bAutoMinTE = false;
	m_bAutoMinTR = false;
	/***************************************/

	//Added by Tom, --2008.07.10
	m_nNumOfScan       = 0;
	m_bFinishedPrescan = false;
	m_bPrescanForFSE   = true ;
	m_bPrescanForSSFP  = true;
	m_nScanCount       = 0;
}


/*
	\remarks Use this format of constructor to construct a series which
	is to be loaded from file.
    \param study The study to which this series belongs.
*/
CSeries::CSeries(CStudy& study)
{
	/*********zyh add 2008.1.31*********/
	m_bEnableCuting = FALSE;
	/**********************************************/
	/*********zyh add 2007.11.4*********/
	m_bIsSendingToPACS = FALSE;
	/**********************************************/
	m_pStudy = &study;

	m_nTimeElapsed = 0;
	m_nTimeEstimated = 0;
    m_pCurrentScan = NULL;
   //Added by Sun Shang for database function at 2002/09/19
	GetSavedRecordNum()=0;
	//End.

    m_State = ssComplete;

    // clear all the series parameter.
	memset(&m_SeriesParams, 0, sizeof (SeriesField));

	//Added by Tom, --2008.07.10
	m_SeriesParams.nInterval = 5 ;

	bool bIsFirstSeries = m_SeriesParams.Id == 1;
	m_SeriesParams.bAdjustRG = 
		CConfigManager::GetHandle().IsTuning(CConfigManager::GetHandle().GetTuneConfig().m_tmDefaultTuneModeRG, bIsFirstSeries);

	m_SeriesParams.bAdjustTG = 
		CConfigManager::GetHandle().IsTuning(CConfigManager::GetHandle().GetTuneConfig().m_tmDefaultTuneModeTG, bIsFirstSeries);

	m_SeriesParams.bTuningRFCoil = 
		CConfigManager::GetHandle().IsTuning(CConfigManager::GetHandle().GetTuneConfig().m_tmDefaultTuneModeRFRcvCoil, bIsFirstSeries);

	m_SeriesParams.bAuto1stShimming3Chn = 
		CConfigManager::GetHandle().IsTuning(CConfigManager::GetHandle().GetTuneConfig().m_tmDefaultTuneModeAutoShim, bIsFirstSeries);
	
    // add this series to the parent study.
    study.GetSeries().push_back(this);

	m_ClusterSet.clear();

	/** [GMWU 070915] 缺省不自动计算TE/TR **/
	m_bAutoMinTE = false;
	m_bAutoMinTR = false;
	/***************************************/

	//Added by Tom, --2008.07.10
	m_nNumOfScan       = 0;
	m_bFinishedPrescan = false;
	m_bPrescanForFSE   = true ;
	m_bPrescanForSSFP  = true;
	m_nScanCount       = 0;
}

/*
    \param pStudy The study to which this series belongs.
    \param bComplete Set this parameter to \a true if you are creating a series
    so that a series on the storage can be loaded into, set to \a false if you
    are creating a new series from a series protocol.
*/
CSeries::CSeries(CStudy& study, const CSeriesProtocol& protocol, bool bCopy)
{
	/*********zyh add 2008.1.31*********/
	m_bEnableCuting = FALSE;
	/**********************************************/
	/*********zyh add 2007.11.4*********/
	m_bIsSendingToPACS = FALSE;
	/**********************************************/
	m_pStudy = &study;

	m_nTimeElapsed = 0;
	m_nTimeEstimated = 0;
    m_pCurrentScan = NULL;
   //Added by Sun Shang for database function at 2002/09/19
	GetSavedRecordNum()=0;
	//End.

	study.GetSeries().push_back(this);
    m_State = ssSetup;

    // Set parameters according to the protocol.
	m_SeriesParams = protocol.Params();
    m_SeriesParams.Id = study.GetSeries().size();
	m_strCDLFile = CCDLManager::GetHandle().GetCDLName(this);

	//Added by Tom, --2008.07.10
	m_SeriesParams.nInterval = 5 ;

	/** [GMWU 070915] 缺省不自动计算TE/TR **/
	m_bAutoMinTE = false;
	m_bAutoMinTR = false;
	/***************************************/

    // Create sub scans.
	CScan *pScan = NULL;

	try
	{
		if (protocol.Scans().size() != 0)
		{
			// Create scans according to the scans stored in the protocol.
			for (CScanFieldConstIter it = protocol.Scans().begin(); it !=
				protocol.Scans().end(); ++it)
			{
				pScan = new CScan(this, false, bCopy);
				pScan->ScanParams() = *(*it);
				pScan->UpdateHBCOffset();
				
				/** [zhlxu 2008.4.17] [XABW/CX-31-11-0084] 解决新建或复制SSFP3D序列时相对SNR显示错误 **/
				pScan->ScanParams().DefRelSNR = 0.0;
				/** [zhlxu 2008.4.17] **/
								
				pScan->UpdateParams(false);
				//VERIFY(pScan->CDL()->RunScript("calculate_all"));
			}
		}
		else
		{
			// If there is no scan in the protocol, produce a default one.
			pScan = new CScan(this, false);
			// bug ? what if the series protocol contains no scan?
			// Maybe we should prohibit this to happen?
			ASSERT(0);
		}
	}
    catch (std::bad_alloc& e)
    {
		std::cerr << e.what();
        exit(EXIT_FAILURE);
    }

    m_pCurrentScan = m_Scans[0];

	bool bIsFirstSeries = m_SeriesParams.Id == 1;
	m_SeriesParams.bAdjustRG = 
		CConfigManager::GetHandle().IsTuning(CConfigManager::GetHandle().GetTuneConfig().m_tmDefaultTuneModeRG, bIsFirstSeries);

	m_SeriesParams.bAdjustTG = 
		CConfigManager::GetHandle().IsTuning(CConfigManager::GetHandle().GetTuneConfig().m_tmDefaultTuneModeTG, bIsFirstSeries);

	m_SeriesParams.bTuningRFCoil = 
		CConfigManager::GetHandle().IsTuning(CConfigManager::GetHandle().GetTuneConfig().m_tmDefaultTuneModeRFRcvCoil, bIsFirstSeries);

	m_SeriesParams.bAuto1stShimming3Chn = 
		CConfigManager::GetHandle().IsTuning(CConfigManager::GetHandle().GetTuneConfig().m_tmDefaultTuneModeAutoShim, bIsFirstSeries);

	m_ClusterSet.clear();

	/** [zhlxu 2007.12.17] [XABW/CX-31-11-0068,XABW/CX-31-11-0069,XABW/CX-31-11-0071] 添加序列功能选项的界面限制 **/
	if( !pScan->CDL()->GetParamValue("bSupportMT", m_bSupportMT) )
	{
		m_bSupportMT = false;
	}
	if( !pScan->CDL()->GetParamValue("bSupportNoPhaseWrap", m_bSupportNoPhaseWrap) )
	{
		m_bSupportNoPhaseWrap = true;
	}
	if( !pScan->CDL()->GetParamValue("bSupportOverSampling", m_bSupportOverSampling) )
	{
		m_bSupportOverSampling = true;
	}
	if( !pScan->CDL()->GetParamValue("bSupportFC", m_bSupportFC) )
	{
		m_bSupportFC = false;
	}	
	/** [zhlxu 2007.12.17] **/

	/*********zyh add 2008.4.28*********/
	if( !pScan->CDL()->GetParamValue("bSupportSAT", m_bSupportSAT) )
	{
		m_bSupportSAT = false;
	}
	/**********************************************/
	
	//Added by Tom, --2008.07.10
	m_nNumOfScan       = 0;
	m_bFinishedPrescan = false;
	m_bPrescanForFSE   = true ;
	m_bPrescanForSSFP  = true;
	m_nScanCount       = 0;
}


CSeries::~CSeries()
{
	try
	{
		for (CScanIter it = m_Scans.begin(); it != m_Scans.end(); ++it)
		{
			delete (*it);
		}
		for (CImageIter it2 = m_Images.begin(); it2 != m_Images.end(); ++it2)
		{
			CImage* pImage = *it2;
			// \bug assert error.
			delete (*it2);
		}

		m_ClusterSet.clear();
	}
	catch(...)
	{
		
	}
}

bool CSeries::UpdateCDL(std::string& strCDL)
{
	if (strCDL != "")
	{
		m_strCDLFile = strCDL;

		for (CScanIter itScan = Scans().begin(); itScan != Scans().end(); ++itScan)
		{
			VERIFY((*itScan)->CDL()->LoadCDLFile(CConfigManager::GetHandle().GetCDLDirectory() + strCDL,true));
			(*itScan)->UpdateParams(false);
			// (*itScan)->CDL()->RunScript(_T("calculate_all"));
		}
	}
	else
	{
		ASSERT(0);
	}

	return true;
}

/*
    \param The scan that the image belongs to.
    \param The sequence number of the image in scan.
    \return The sequence number of the image in the sereis.
    \remarks MRI experiments are done on scan basis, however, the images
    are stored in a series. You can use this function to find out the position
    of a specified image in a specified scan in a series of images.
*/
int CSeries::GetImageIndex(CScan* pScan, int nIndexInScan) const
{
    int nIndex = 0;
    for(CScanConstIter it = Scans().begin(); it != Scans().end(); ++it)
    {
        if (*it != pScan)
            nIndex += (*it)->Images().size();
        else
        {
            nIndex += nIndexInScan;
            break;
        }
    }
    return nIndex;
}

void CSeries::AddImage(CImage* pImage)
{
	CImageIter it;
    for (it = m_Images.begin(); it != m_Images.end(); ++it)
	{
		if ((*it)->ScanParams().Id > pImage->ScanParams().Id)
			break;
		else if ((*it)->ScanParams().Id == pImage->ScanParams().Id &&
			     (*it)->ImageParams().Id > pImage->ImageParams().Id)
			break;
	}
	if(pImage->ImageParams().Id == 0 )
		it = m_Images.end();

	m_Images.insert(it, pImage);
    TRACE("Size of the image container in series: %d\n", m_Images.size());
}

std::string CSeries::GetPath() const
{
	std::ostringstream os;
	os << int (SeriesParams().Id);
	return (m_pStudy->GetPath() + os.str() + "\\");
}

bool CSeries::CreateFolder()
{
    CString strDir = CConfigManager::GetHandle().GetImageRootDirectory().c_str();
	
	strDir.Format(strDir + StudyParams().Id + "\\%d\\", SeriesParams().Id);
    CFileFind finder;
    if (finder.FindFile(strDir))
    {
        if (finder.IsDirectory()) 
        {
            finder.Close();
            return true;
        }
        ASSERT(0);
    }
    GetStudy()->CreateFolder();
    return (::CreateDirectory(strDir, NULL) != 0);
}

// Returns the estimated time in seconds that the series will take.
/*
	\bug Hard coding estimated time for prescan and reconstruction.
*/
int CSeries::GetTimeEstimated()
{
	if (m_Scans.size() == 0)
		return 0;

	// 10 seconds for prescan, 10 seconds for recon, hardcoding.
	// return (m_Scans.size() * m_Scans[0]->ScanParams().ACQ + 10 + 10);
	m_nTimeEstimated = 1000 * (GetACQ() + 10 + 10); // ms
	return m_nTimeEstimated; // Rodger 16:02 2004-10-25
}

// nIndex: Index of the reference image to retrieve. Can be 0 or 1.
CImage* CSeries::GetReferenceImage(int nIndex) const
{
    // Now only two reference image can be used in the system.
    assert(0 == nIndex || 1 == nIndex);
    int nSeriesID = 
        (0 == nIndex) ? SeriesParams().RefSeries1 : SeriesParams().RefSeries2;
    int nImageID = 
        (0 == nIndex) ? SeriesParams().RefImage1 : SeriesParams().RefImage2;

    // if the reference series ID is set to 0, no reference image is used,
	// for series ID starts from 1.
	if ( nSeriesID == -1 || nSeriesID == 0 ) return NULL;

    // The id of the reference series and image must be in the valid range.
	const CSeriesContainer& SeriesSet = GetStudy()->GetSeries();
	int nSize = SeriesSet.size();
	if(nSeriesID > nSize)	//if(nSeriesID >= nSize)
	{
		ASSERT(0);	// something wrong
		return NULL;
	}

	CSeries* pRefSeries = SeriesSet[nSeriesID];
	for(CSeriesConstIter it = SeriesSet.begin(); it != SeriesSet.end(); ++it)
	{
		if((*it)->SeriesParams().Id == nSeriesID)
		{
			pRefSeries = (*it);
			break;
		}
	}

	int nImageNum = pRefSeries->Images().size();
	if(nImageNum <= 0)
		return NULL;
	else if(0 > nImageID || nImageID >= nImageNum)
		return NULL;

	// assert (0 <= nImageID && nImageID < nImageNum);

    // return (GetStudy()->GetSeries()[nSeriesID]->Images()[nImageID]);
	return pRefSeries->Images()[nImageID];
}

// return Total acquisition time of the series in seconds.
int CSeries::GetACQ() const
{
    int nACQ = 0;
    for (int i = 0; i < Scans().size(); i++)
    {
        nACQ += m_Scans[i]->ScanParams().ACQ;
    }
    return nACQ;
}

//20070718.liuxuan.for RelSNR
float CSeries::GetSNR() const
{
    float fSNR = 0;
	for (int i = 0; i < Scans().size(); i++)
    {
        fSNR = m_Scans[i]->ScanParams().RelSNR;
    }
    return fSNR;
}

/*
    \param nScanID Id of the scan.
    \return The scan with given scan ID.
    \remarks The scan id is a sequential number used to identify a scan in
    a series. We don't assume the scan ids are continuous numbers.

*/
CScan* CSeries::GetScan(int nScanId)
{
    for (int i = 0; i < m_Scans.size(); i++)
    {
        if (m_Scans[i]->ScanParams().Id == nScanId)
        {
            return (m_Scans[i]);
        }
    }

    return NULL;
}

/*
    \param nScanID Id of the scan.
    \return The scan with given scan ID.
    \remarks The scan id is a sequential number used to identify a scan in
    a series. We don't assume the scan ids are continuous numbers.
*/
const CScan* CSeries::GetScan(int nScanId) const
{
    for (int i = 0; i < m_Scans.size(); i++)
    {
        if (m_Scans[i]->ScanParams().Id == nScanId)
        {
            return (m_Scans[i]);
        }
    }

    return NULL;
}

/*
    \param nImageId Id of the image.
    \return The image with given id.
    \note The image id should be a sequential number which is unique in a 
    series, because all images in a series is displayed in the same layout 
    window at the same time. However, due to a bug in the current design, the 
    image id is unique in scan. This will bring us trouble when we try to do
    series containing more than one scans. This function is designed to be used
    after we have modifed the existing code so that the image ids are unique in
    the series.
    \bug Need to change the definition of the image id so that the image id is
    unique in the series. 
    \todo Using a more effective way to find the given image if necessary.
*/
CImage* CSeries::GetImage(int nImageId)
{
    for (int i = 0; i < m_Images.size(); i++)
    {
		int nThisID = m_Images[i]->ImageParams().Id;
        if (nThisID == nImageId)
        {
            return (m_Images[i]);
        }
    }

    return NULL;
}

/*
    \param nImageId Id of the image.
    \return The image with given id.
*/
const CImage* CSeries::GetImage(int nImageId) const
{
    for (int i = 0; i < m_Images.size(); i++)
    {
        if (m_Images[i]->ImageParams().Id == nImageId)
        {
            return (m_Images[i]);
        }
    }

    return NULL;
}

STRUCT_SLICE_PLANE_INFO* CSeries::GetCenterPoint( int nNoOfSlice )
{
	if ( nNoOfSlice < 1 || nNoOfSlice > m_nTotalNumOfSlices || nNoOfSlice >= MAX_NUM_OF_SLICES_IN_ALL_SLABS )
	{
		return NULL;
	}
	else
	{
		return &m_oCenterPointOfSlices[nNoOfSlice];
	}
}

/** [zhlxu 2007.10.9] 获得总层数及图形定位可视SLAB数目 **/
unsigned int CSeries::GetTotalNumofSlices()
{
	return SeriesParams().ResolutionZ * max( m_ClusterSet.size(), 1 );
}

unsigned int CSeries::GetNumofSlicesPerSlab()
{
	return SeriesParams().ResolutionZ;
}

unsigned int CSeries::GetNumofSlabs()
{
	return max( m_ClusterSet.size(), 1 );
}
/** [zhlxu 2007.10.9] **/

/***********************************************************************
函数名称: ValidateTotalSlabNum
描述: 根据序列类型，验证Slabs个数是否有效
输入: 
输出: 
返回: true－有效；false－无效
其它: MRA 3D TOF的SeriesParams().NumSlab在InPlaneParamsDialog.cpp的函数OnKillfocusEditNumSlabs和OnKillfocusEditPointsPerSlab中作特殊处理
修改历史:
       <修改人> <时间>     <版本 >   <描述>
    1. zhlxu    2007.11.22 v3.5.5.01 创建函数
    2. 
***********************************************************************/

bool CSeries::ValidateTotalSlabNum()
{
	bool bValidNum = false;
	unsigned int iTotalSlabNum = GetNumofSlabs();
	unsigned int iMinTotalSlabNum, iMaxTotalSlabNum;	
	CString sErrorMsg, sErrorMsg0 = CLang::GetHandle().GetCharRes("MSG___TOTAL_NUM_OF_SLAB__5");
	
	int iSeqType = SeriesParams().SequenceOptions & cnstBasicSequenceTypeMask;
	switch ( iSeqType )
	{
		case cnstSE:
		case cnstGRE:
		case cnstFSE:
		case cnstSTIR:
		case cnstIRSE:
		case cnstSPGR2D:
		case cnstWFI:
			iMinTotalSlabNum = 1;
			iMaxTotalSlabNum = 12;
			( iMinTotalSlabNum <= iTotalSlabNum && iTotalSlabNum <= iMaxTotalSlabNum ) ? 
				bValidNum = true : bValidNum = false;
			break;

		case cnstSPGR:
		case cnstTOF2D:
		case cnstEPDWI:
		case cnstEPDWI1B:
		case cnstSPGR2DBH:
		case cnstLSDI:
		case cnstLSDI1B:
		case cnstSSFSE3D:
		case cnstDeGhost:
		case cnstFLAIR:
		case cnstSSFSE:
		/** [zhlxu 2008.5.8] [XABW/CX-31-11-0083] 添加Slab限制 **/
		case cnstSSFP3D:
		/** [zhlxu 2008.5.8] **/
			iMinTotalSlabNum = 1;
			iMaxTotalSlabNum = 1;
			( iMinTotalSlabNum <= iTotalSlabNum && iTotalSlabNum <= iMaxTotalSlabNum ) ? 
				bValidNum = true : bValidNum = false;
			break;
			
		case cnstTOF3D:
			// Cluster
			iMinTotalSlabNum = 1;
			iMaxTotalSlabNum = 1;			
			( iMinTotalSlabNum <= iTotalSlabNum && iTotalSlabNum <= iMaxTotalSlabNum ) ?
				bValidNum = true : bValidNum = false; 
			break;

			/** [zhlxu 2008.5.9] [XABW/CX-31-11-0085] 更改Slab个数限制为4 **/
		case cnstSSFP:
			iMinTotalSlabNum = 1;
			iMaxTotalSlabNum = 4;
			( iMinTotalSlabNum <= iTotalSlabNum && iTotalSlabNum <= iMaxTotalSlabNum ) ? 
				bValidNum = true : bValidNum = false;
			break;
			/** [zhlxu 2008.5.9] **/
			
			
		default:
			bValidNum = true;
			break;
	}

	if ( !bValidNum )
	{
		if ( iMinTotalSlabNum == iMaxTotalSlabNum )
		{
			sErrorMsg.Format( "%s(%d).", sErrorMsg0, iMaxTotalSlabNum );
		}
		else
		{
			sErrorMsg.Format( "%s(%d-%d).", sErrorMsg0, iMinTotalSlabNum, iMaxTotalSlabNum );
		}

		CLang::GetHandle().ShowMessage( sErrorMsg );
	}
	
	return bValidNum;
}

/***********************************************************************
函数名称: ValidateTotalSliceNum
描述: 根据序列类型，验证Slices总层数是否有效
输入: 
输出: 
返回: true－有效；false－无效
其它: MRA 3D TOF的总层数在InPlaneParamsDialog.cpp的函数OnKillfocusEditNumSlabs和OnKillfocusEditPointsPerSlab中作特殊处理
修改历史:
       <修改人> <时间>     <版本 >   <描述>
    1. zhlxu    2007.11.22 v3.5.5.01 创建函数
    2. zhlxu	2008.04.30 v3.5.5.02 [XABW/CX-31-11-0094,XABW/CX-31-11-0130,XABW/CX-31-11-0138] 
									   将所有32层更改为30层；将cnstTOF2D的200层更改为140层
***********************************************************************/

bool CSeries::ValidateTotalSliceNum()
{
	bool bValidNum = false;
	unsigned int iTotalSliceNum = GetTotalNumofSlices();
	unsigned int iMinTotalSliceNum, iMaxTotalSliceNum;	
	CString sErrorMsg, sErrorMsg0 = CLang::GetHandle().GetCharRes("MSG___TOTAL_NUM_OF_SLICE__5");
	
	int iSeqType = SeriesParams().SequenceOptions & cnstBasicSequenceTypeMask;
	switch ( iSeqType )
	{
		case cnstSE:
		case cnstGRE:
		case cnstFSE:
		case cnstFLAIR:
		case cnstSTIR:
		case cnstSSFSE:
		case cnstIRSE:
		case cnstEPDWI:
		case cnstEPDWI1B:		
		case cnstSPGR2D:
		case cnstSPGR2DBH:
		//Added by Tom, --2008.07.10
		/**[xd 2008.12.06]增加spgr预饱和 Begin**/
		case cnstSPGR2DSAT:
		/**[xd 2008.12.06]增加spgr预饱和 End**/
		case cnstLSDI:
		case cnstLSDI1B:
		case cnstDeGhost:
		case cnstWFI:
		/** [zhlxu 2008.4.16] [XABW/CX-31-11-0085] 添加SSFP2D的Slabs个数、每个Slab的层数、总层数的限制**/
		case cnstSSFP:
		/** [zhlxu 2008.4.16] **/
			
			iMinTotalSliceNum = 1;
			/** [yhwang 2008.3.28] 更改最大层数限制 **/
			iMaxTotalSliceNum = 30;
			/** [yhwang 2008.3.28] **/
			( iMinTotalSliceNum <= iTotalSliceNum && iTotalSliceNum <= iMaxTotalSliceNum ) ? 
				bValidNum = true : bValidNum = false;
			break;
			
		case cnstSPGR:
		case cnstSSFSE3D:
			iMinTotalSliceNum = 1;
			iMaxTotalSliceNum = 100;
			( iMinTotalSliceNum <= iTotalSliceNum && iTotalSliceNum <= iMaxTotalSliceNum ) ? 
				bValidNum = true : bValidNum = false;
			break;

		case cnstTOF2D:
			iMinTotalSliceNum = 1;
			iMaxTotalSliceNum = 140;
			( iMinTotalSliceNum <= iTotalSliceNum && iTotalSliceNum <= iMaxTotalSliceNum ) ? 
				bValidNum = true : bValidNum = false;
			break;
			
		case cnstTOF3D:
			iMinTotalSliceNum = 1;
			iMaxTotalSliceNum = 100;
			// 仅提示，用户不能在InPlaneParamsDialog界面上更改此参数
			( iMinTotalSliceNum <= iTotalSliceNum && iTotalSliceNum <= iMaxTotalSliceNum ) ? 
				bValidNum = true : bValidNum = false;
			break;
			
		/** [zhlxu 2008.5.8] [XABW/CX-31-11-0083] 添加总层数限制 **/
		case cnstSSFP3D:
			iMinTotalSliceNum = 1;
			iMaxTotalSliceNum = 64;
			( iMinTotalSliceNum <= iTotalSliceNum && iTotalSliceNum <= iMaxTotalSliceNum ) ? 
				bValidNum = true : bValidNum = false;
			break;
		/** [zhlxu 2008.5.8] **/
			
		default:
			bValidNum = true;
			break;
	}
	
	if ( !bValidNum )
	{
		if ( iMinTotalSliceNum == iMaxTotalSliceNum )
		{
			sErrorMsg.Format( "%s(%d).", sErrorMsg0, iMaxTotalSliceNum );
		}
		else
		{
			sErrorMsg.Format( "%s(%d-%d).", sErrorMsg0, iMinTotalSliceNum, iMaxTotalSliceNum );
		}
		
		CLang::GetHandle().ShowMessage( sErrorMsg );
	}
	
	return bValidNum;
}

/***********************************************************************
函数名称: ValidateSliceNumPerSlab
描述: 根据序列类型，验证单个Slab的Slices层数是否有效
输入: 
输出: 
返回: true－有效；false－无效
其它: MRA 3D TOF的SeriesParams().NumPntsPerSlab在InPlaneParamsDialog.cpp的函数OnKillfocusEditNumSlabs和OnKillfocusEditPointsPerSlab中作特殊处理
修改历史:
       <修改人> <时间>     <版本 >   <描述>
    1. zhlxu    2007.11.22 v3.5.5.01 创建函数
    2. zhlxu	2008.04.30 v3.5.5.02 [XABW/CX-31-11-0094,XABW/CX-31-11-0130,XABW/CX-31-11-0138] 
									   将所有32层更改为30层；将cnstTOF2D的200层更改为140层
***********************************************************************/


bool CSeries::ValidateSliceNumPerSlab()
{
	bool bValidNum = false;
	unsigned int iNumofSlicesPerSlab = GetNumofSlicesPerSlab();
	unsigned int iMinNumofSlicesPerSlab, iMaxNumofSlicesPerSlab;
	CString sErrorMsg, sErrorMsg0 = CLang::GetHandle().GetCharRes("MSG___NUM_OF_SLICE_PER_SLAB__5");
	
	int iSeqType = SeriesParams().SequenceOptions & cnstBasicSequenceTypeMask;
	switch ( iSeqType )
	{
		case cnstSE:
		case cnstGRE:
		case cnstFSE:
		case cnstFLAIR:
		case cnstSTIR:
		case cnstSSFSE:
		case cnstIRSE:
		case cnstEPDWI:
		case cnstEPDWI1B:		
		case cnstSPGR2D:
		case cnstSPGR2DBH:
		//Added by Tom, --2008.07.10
		/**[xd 2008.12.06]增加spgr预饱和 Begin**/
		case cnstSPGR2DSAT:
		/**[xd 2008.12.06]增加spgr预饱和 End**/
		case cnstLSDI:
		case cnstLSDI1B:
		case cnstDeGhost:
		case cnstWFI:
		/** [zhlxu 2008.4.16] [XABW/CX-31-11-0085] 添加SSFP2D的Slabs个数、每个Slab的层数、总层数的限制**/
		case cnstSSFP:
		/** [zhlxu 2008.4.16] **/
			
			iMinNumofSlicesPerSlab = 1;
			/** [yhwang 2008.3.28] 更改最大层数限制 **/
			iMaxNumofSlicesPerSlab = 30;
			/** [yhwang 2008.3.28] **/
			( iMinNumofSlicesPerSlab <= iNumofSlicesPerSlab && iNumofSlicesPerSlab <= iMaxNumofSlicesPerSlab ) ? 
				bValidNum = true: bValidNum = false;
			break;
			
		case cnstSPGR:
		case cnstSSFSE3D:
			iMinNumofSlicesPerSlab = 1;
			iMaxNumofSlicesPerSlab = 100;
			( iMinNumofSlicesPerSlab <= iNumofSlicesPerSlab && iNumofSlicesPerSlab <= iMaxNumofSlicesPerSlab ) ? 
				bValidNum = true : bValidNum = false;
			break;
			
		case cnstTOF2D:
			iMinNumofSlicesPerSlab = 1;
			iMaxNumofSlicesPerSlab = 140;
			( iMinNumofSlicesPerSlab <= iNumofSlicesPerSlab && iNumofSlicesPerSlab <= iMaxNumofSlicesPerSlab ) ? 
				bValidNum = true : bValidNum = false;
			break;
			
		case cnstTOF3D:
			iMinNumofSlicesPerSlab = 1;
			iMaxNumofSlicesPerSlab = 100;
			( iMinNumofSlicesPerSlab <= iNumofSlicesPerSlab && iNumofSlicesPerSlab <= iMaxNumofSlicesPerSlab ) ? 
				bValidNum = true : bValidNum = false;
			break;
			
		default:
			bValidNum = true;
			break;
	}

	if ( !bValidNum )
	{
		if ( iMinNumofSlicesPerSlab == iMaxNumofSlicesPerSlab )
		{
			sErrorMsg.Format( "%s(%d).", sErrorMsg0, iMaxNumofSlicesPerSlab );
		}
		else
		{
			sErrorMsg.Format( "%s(%d-%d).", sErrorMsg0, iMinNumofSlicesPerSlab, iMaxNumofSlicesPerSlab );
		}

		CLang::GetHandle().ShowMessage( sErrorMsg );
	}
	
	return bValidNum;
}

/***********************************************************************
函数名称: BackupToDefaultOrientationParams
描述: 备份到默认Freq、Phase方向参数
输入: 
输出: 
返回: 
其它: 在创建Series时，调用。In two cases:
      (1) void CMriView::OnNewSeries()
	  (2) CStudy::CStudy(...)
修改历史:
       <修改人> <时间>     <版本 >   <描述>
    1. zhlxu    2008.01.03 v3.5.5.01 创建函数
    2. 
***********************************************************************/

void CSeries::BackupToDefaultOrientationParams()
{
	ScanField& scanParams = GetScan(1)->ScanParams();

	SeriesParams().nPlaneType = SeriesParams().Plane;

	bool bDefaultFrequencyDir = ((SeriesParams().OtherOptions & cnstDefaultFrequencyDir) != 0);
	
	if ( bDefaultFrequencyDir )
	{
		scanParams.DefaultFreqDirX = scanParams.FreqDirX;	
		scanParams.DefaultFreqDirY = scanParams.FreqDirY;	
		scanParams.DefaultFreqDirZ = scanParams.FreqDirZ;	
		
		scanParams.DefaultPhaseDirX = scanParams.PhaseDirX;	
		scanParams.DefaultPhaseDirY = scanParams.PhaseDirY;	
		scanParams.DefaultPhaseDirZ = scanParams.PhaseDirZ;	
		
		scanParams.DefaultReadOffset = scanParams.ReadOffset;	
		scanParams.DefaultPhaseOffset = scanParams.PhaseOffset;	
	}
	else
	{
		scanParams.DefaultFreqDirX = scanParams.PhaseDirX;	
		scanParams.DefaultFreqDirY = scanParams.PhaseDirY;	
		scanParams.DefaultFreqDirZ = scanParams.PhaseDirZ;	
		
		scanParams.DefaultPhaseDirX = scanParams.FreqDirX;	
		scanParams.DefaultPhaseDirY = scanParams.FreqDirY;	
		scanParams.DefaultPhaseDirZ = scanParams.FreqDirZ;	
		
		scanParams.DefaultReadOffset = scanParams.PhaseOffset;	
		scanParams.DefaultPhaseOffset = scanParams.ReadOffset;	
	}
	
	scanParams.DefaultSliceDirX = scanParams.SliceDirX;	
	scanParams.DefaultSliceDirY = scanParams.SliceDirY;	
	scanParams.DefaultSliceDirZ = scanParams.SliceDirZ;	
		
	scanParams.DefaultSliceOffset = scanParams.SliceOffset;	
	
	scanParams.bDefaultFreqDir = bDefaultFrequencyDir;	
}

/***********************************************************************
函数名称: RestoreFromDefaultOrientationParams
描述: 恢复为默认Freq、Phase方向参数
输入: 
输出: 
返回: 
其它: 在创建Series时，调用。In three cases:
      (1) CScanParametersPage::OnButtonClearSelSlab()
	  (2) CScanParametersPage::OnClearGL()
	  (3) CScanParametersPage::OnClearSlab()
修改历史:
       <修改人> <时间>     <版本 >   <描述>
    1. zhlxu    2008.01.03 v3.5.5.01 创建函数
    2. 
***********************************************************************/

void CSeries::RestoreFromDefaultOrientationParams()
{
	ScanField& scanParams = GetScan(1)->ScanParams();

	SeriesParams().Plane = SeriesParams().nPlaneType;

	bool bDefaultFrequencyDir = ((SeriesParams().OtherOptions & cnstDefaultFrequencyDir) != 0);
	
	if ( bDefaultFrequencyDir )
	{
		scanParams.FreqDirX = scanParams.DefaultFreqDirX;	
		scanParams.FreqDirY = scanParams.DefaultFreqDirY;	
		scanParams.FreqDirZ = scanParams.DefaultFreqDirZ;	

		scanParams.PhaseDirX = scanParams.DefaultPhaseDirX;	
		scanParams.PhaseDirY = scanParams.DefaultPhaseDirY;	
		scanParams.PhaseDirZ = scanParams.DefaultPhaseDirZ;	
				
		scanParams.ReadOffset = scanParams.DefaultReadOffset;	
		scanParams.PhaseOffset = scanParams.DefaultPhaseOffset;	
	}
	else
	{
		scanParams.FreqDirX = scanParams.DefaultPhaseDirX;	
		scanParams.FreqDirY = scanParams.DefaultPhaseDirY;	
		scanParams.FreqDirZ = scanParams.DefaultPhaseDirZ;		
		
		scanParams.PhaseDirX = scanParams.DefaultFreqDirX;	
		scanParams.PhaseDirY = scanParams.DefaultFreqDirY;	
		scanParams.PhaseDirZ = scanParams.DefaultFreqDirZ;	
		
		scanParams.ReadOffset = scanParams.DefaultPhaseOffset;	
		scanParams.PhaseOffset = scanParams.DefaultReadOffset;	
	}

	scanParams.SliceDirX = scanParams.DefaultSliceDirX;	
	scanParams.SliceDirY = scanParams.DefaultSliceDirY;	
	scanParams.SliceDirZ = scanParams.DefaultSliceDirZ;	
	
	scanParams.SliceOffset = scanParams.DefaultSliceOffset;	
	
	scanParams.bDefaultFreqDir = bDefaultFrequencyDir;	
}
