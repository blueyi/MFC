// SeriesProtocol.cpp: implementation of the CSeriesProtocol class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <iostream>
#include "SeriesProtocol.h"
#include "ProtocolExample.h"
#include "../BIGlobals/ConfigManager.h"
#include "..\\SystemSettings\\SystemSettingInterface.h"

#include "Series.h"
#include "Scan.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSeriesProtocol::CSeriesProtocol()
{
    m_pStudyProtocol = NULL;
    memset(reinterpret_cast<char*>(&m_SeriesParams), 0, sizeof (SeriesField));
    m_strProtocolName  = "";

	// no scan in the series protocol for now
}

void CSeriesProtocol::ClearAllScans()
{
	for(CScanFieldIter it = m_Scans.begin(); it != m_Scans.end(); ++it)
	{
		ScanField* pScanField = (*it);
		if(pScanField)
			delete pScanField;
	}
	m_Scans.clear();
}

void CSeriesProtocol::CopyParametersFrom(const CSeriesProtocol& SeriesProtocol)
{
//	m_pStudyProtocol = SeriesProtocol.GetParentStudyProtocol();
    memcpy(&m_SeriesParams, &SeriesProtocol.Params(), sizeof (SeriesField));

	// clear reference images
	m_SeriesParams.RefSeries1 = m_SeriesParams.RefSeries2 = 0;
	m_SeriesParams.RefImage1 = m_SeriesParams.RefImage2 = 0;

    m_strProtocolName  = SeriesProtocol.GetName();

//	if(m_pStudyProtocol)
//		m_pStudyProtocol->m_SeriesProtocols.push_back(this);

	ClearAllScans();

	// add a default scan to the series protocol.
	CScanFieldContainer ScanList = SeriesProtocol.Scans();
	for(CScanFieldIter it = ScanList.begin(); it != ScanList.end(); ++it)
	{
		ScanField* pScanFieldSrc = (*it);
		ScanField* pScanField = new ScanField;
		memcpy(pScanField, pScanFieldSrc, sizeof (ScanField));
		m_Scans.push_back(pScanField);
	}
}

void CSeriesProtocol::CopyParametersFrom(const CSeries& series)
{
    m_pStudyProtocol = NULL;
    m_SeriesParams = series.SeriesParams();

	// clear reference images
	m_SeriesParams.RefSeries1 = m_SeriesParams.RefSeries2 = 0;
	m_SeriesParams.RefImage1 = m_SeriesParams.RefImage2 = 0;

    m_strProtocolName = "";

    for (CScanConstIter it = series.Scans().begin(); it != series.Scans().end(); ++it)
    {
        ScanField * pScanParams;
        try
        {
            pScanParams = new ScanField;
        }
        catch(std::bad_alloc& e)
        {
            std::cerr << e.what();
            exit(EXIT_FAILURE);
        }
        *pScanParams = (*it)->ScanParams();
        m_Scans.push_back(pScanParams);
    }

}


/////////////////////////////////////////////////////////////////////////////////////
//
CSeriesProtocol::CSeriesProtocol(CStudyProtocol& studyProtocol)
{
    m_pStudyProtocol = &studyProtocol;
    memset(reinterpret_cast<char*>(&m_SeriesParams), 0, sizeof (SeriesField));
    m_strProtocolName  = "";
    studyProtocol.m_SeriesProtocols.push_back(this);

	// add a default scan to the series protocol.
	ScanField* pScanField = new ScanField;
	memset(pScanField, 0, sizeof (ScanField));
	pScanField->Id = 1;
	m_Scans.push_back(pScanField);
}

/*!
    Constructs a CSeriesProtocol object from a given series.
*/
CSeriesProtocol::CSeriesProtocol(CStudyProtocol& studyProtocol, 
                                 const CSeries& series)
{
    m_pStudyProtocol = &studyProtocol;
    m_SeriesParams = series.SeriesParams();
    m_strProtocolName = "";
    studyProtocol.m_SeriesProtocols.push_back(this);

    for (CScanConstIter it = series.Scans().begin(); 
		it != series.Scans().end(); ++it)
    {
        ScanField * pScanParams;
        try
        {
            pScanParams = new ScanField;
        }
        catch(std::bad_alloc& e)
        {
            std::cerr << e.what();
            exit(EXIT_FAILURE);
        }
        *pScanParams = (*it)->ScanParams();
        m_Scans.push_back(pScanParams);
    }

}

CSeriesProtocol::~CSeriesProtocol()
{
    for (CScanFieldIter it = m_Scans.begin(); it != m_Scans.end(); ++it)
    {
        delete (*it);
    }
}

/*!
    Save the series protocol into an output stream. Called from within the 
    CStudyProtocol::Save().
    \param outStream Output stream into which the protocol should be saved.
    \return \a true if successful, \a false otherwise.
*/
bool CSeriesProtocol::Save(std::ostream& outStream)
{
    if (!outStream)
        return false;

    // Save the protocol name first, fixed length 32 chars.
    char pchBuf[32] = {0};
    memcpy(pchBuf, m_strProtocolName.c_str(), 
        min(m_strProtocolName.length(), 31));

    outStream.write(pchBuf, 32);

    // Series parameters.
    outStream.write(reinterpret_cast<char*>(&m_SeriesParams),
        sizeof (m_SeriesParams));
    // Scans.
    int nNumScans = m_Scans.size();
    outStream.write(reinterpret_cast<char*>(&nNumScans), sizeof (int));

    for (CScanFieldIter it = m_Scans.begin(); it != m_Scans.end(); ++it)
    {
        outStream.write(reinterpret_cast<char*>(*it), sizeof (ScanField));
    }

    return true;
}

bool CSeriesProtocol::Save(CArchive& ar)
{
    if (!ar.IsStoring())
        return false;

    // Save the protocol name first, fixed length 32 chars.
    char pchBuf[32] = {0};
    memcpy(pchBuf, m_strProtocolName.c_str(), 
        min(m_strProtocolName.length(), 31));

	ar.Write(pchBuf, 32);

    // Series parameters.
    ar.Write(reinterpret_cast<char*>(&m_SeriesParams), sizeof (m_SeriesParams));

    // Scans.
    int nNumScans = m_Scans.size();
    ar.Write(reinterpret_cast<char*>(&nNumScans), sizeof (int));

    for (CScanFieldIter it = m_Scans.begin(); it != m_Scans.end(); ++it)
    {
        ar.Write(reinterpret_cast<char*>(*it), sizeof (ScanField));
    }

    return true;
}
/************************************************************************/
/* beging //dolphin                                                                     */
/************************************************************************/

bool CSeriesProtocol::Save(CIniFile& iniFile,CString strSectionPrefix,int index)
{
	CString strSeriesProtocolSection = "SERIES_PROTOCOL_";
	strSeriesProtocolSection.Format(strSectionPrefix+"."+strSeriesProtocolSection+"%d",index);
	CString strSeriesFieldSection = "SERIES_FIELD";
	strSeriesFieldSection.Format(strSeriesProtocolSection+"."+strSeriesFieldSection);
	
	CString presaturation_region_Section = "PRESATURATION_REGION";
	presaturation_region_Section.Format(strSeriesProtocolSection+".SERIES_FIELD."+presaturation_region_Section);
	CString strGatingTriggerSection = "GATINGTRIGGER";
	strGatingTriggerSection.Format(strSeriesProtocolSection+".SERIES_FIELD."+strGatingTriggerSection);
	CString bidate_time_Section = "BIDATE_TIME";
	bidate_time_Section.Format(strSeriesProtocolSection+".SERIES_FIELD."+bidate_time_Section);

	CString scan_field_Section = "SCAN_FIELD_";
	scan_field_Section.Format(strSeriesProtocolSection+"."+scan_field_Section);
	
/*	iniFile.AddSection(strSeriesProtocolSection);
	iniFile.AddKey(strSeriesProtocolSection,"series_protocol_name");
	iniFile.AddKey(strSeriesProtocolSection,"n_scan_fields");*/
	char pchBuf[32] = {0};
    memcpy(pchBuf, m_strProtocolName.c_str(), 
        min(m_strProtocolName.length(), 31));
	
	iniFile.SetKeyValue(strSeriesProtocolSection,CString("series_protocol_name"),CString(pchBuf));
	itoa(m_Scans.size(),pchBuf,10);
	iniFile.SetKeyValue(strSeriesProtocolSection,CString("n_scan_fields"),CString(pchBuf));

	
/*	iniFile.AddSection(strSeriesFieldSection);
	iniFile.AddKey(strSeriesFieldSection,"Version"			);
	iniFile.AddKey(strSeriesFieldSection,"Size"				);
	iniFile.AddKey(strSeriesFieldSection,"Id"					  );
	iniFile.AddKey(strSeriesFieldSection,"Desc"		); //(128位)
	iniFile.AddKey(strSeriesFieldSection,"Protocol"       );//(32位)
	iniFile.AddKey(strSeriesFieldSection,"NucType"	    	);
	iniFile.AddKey(strSeriesFieldSection,"GRR"				);
	iniFile.AddKey(strSeriesFieldSection,"TXCoil"			 	);
	iniFile.AddKey(strSeriesFieldSection,"UserTxCoilDesc");//(32位)
	iniFile.AddKey(strSeriesFieldSection,"RcvCoil"			);
	iniFile.AddKey(strSeriesFieldSection,"UserRcvCoilDesc");//(32位)
	iniFile.AddKey(strSeriesFieldSection,"PulseSeqName"	);//(64位)
	iniFile.AddKey(strSeriesFieldSection,"SequenceOptions"   );
	iniFile.AddKey(strSeriesFieldSection,"OtherOptions"      );
	iniFile.AddKey(strSeriesFieldSection,"RefSeries1"			  );
	iniFile.AddKey(strSeriesFieldSection,"RefImage1"			);
	iniFile.AddKey(strSeriesFieldSection,"RefSeries2"			);
	iniFile.AddKey(strSeriesFieldSection,"RefImage2"			);
	iniFile.AddKey(strSeriesFieldSection,"Plane"            	);
	iniFile.AddKey(strSeriesFieldSection,"Mode"				);
	iniFile.AddKey(strSeriesFieldSection,"FovX"				);
	iniFile.AddKey(strSeriesFieldSection,"FovY"				);
	iniFile.AddKey(strSeriesFieldSection,"FovZ"				);
	iniFile.AddKey(strSeriesFieldSection,"ResolutionX"		);
	iniFile.AddKey(strSeriesFieldSection,"ResolutionY"		);
	iniFile.AddKey(strSeriesFieldSection,"ResolutionZ"		);
	iniFile.AddKey(strSeriesFieldSection,"SliceThickness"	);
	iniFile.AddKey(strSeriesFieldSection,"NumSlab"		);
	iniFile.AddKey(strSeriesFieldSection,"SlabOrder"		);
	iniFile.AddKey(strSeriesFieldSection,"NumPntsPerSlab");
	iniFile.AddKey(strSeriesFieldSection,"SlabOverlap"		);
	iniFile.AddKey(strSeriesFieldSection,"SliceGap"			);
	iniFile.AddKey(strSeriesFieldSection,"EchoTime"		);
	iniFile.AddKey(strSeriesFieldSection,"Echo2Time"			);
	iniFile.AddKey(strSeriesFieldSection,"EchoSpacing"     );
	iniFile.AddKey(strSeriesFieldSection,"RepTime"		);
	iniFile.AddKey(strSeriesFieldSection,"NumEchoImages"		);
	iniFile.AddKey(strSeriesFieldSection,"AcqBandwidth"		);
	iniFile.AddKey(strSeriesFieldSection,"AcqBandwidth2"		);
	iniFile.AddKey(strSeriesFieldSection,"EchoTrainLength"	);
	iniFile.AddKey(strSeriesFieldSection,"FlipAngle"			);
	iniFile.AddKey(strSeriesFieldSection,"GradientShimX"	);
	iniFile.AddKey(strSeriesFieldSection,"GradientShimY"	);
	iniFile.AddKey(strSeriesFieldSection,"GradientShimZ"	);
	iniFile.AddKey(strSeriesFieldSection,"SARAvg"				);
	iniFile.AddKey(strSeriesFieldSection,"SARPeak"			);
	iniFile.AddKey(strSeriesFieldSection,"DigFilterType"	);
	iniFile.AddKey(strSeriesFieldSection,"DigFilterPar"	);//(8位)
	iniFile.AddKey(strSeriesFieldSection,"WindowLevel"		);
	iniFile.AddKey(strSeriesFieldSection,"WindowWidth"		);
	iniFile.AddKey(strSeriesFieldSection,"FlowCompensation"	);
	iniFile.AddKey(strSeriesFieldSection,"PompNumber");
	iniFile.AddKey(strSeriesFieldSection,"NumOfAngioImages");
	iniFile.AddKey(strSeriesFieldSection,"HalfKSpaceRatio"	);
	iniFile.AddKey(strSeriesFieldSection,"ContrastFlag"		);
	iniFile.AddKey(strSeriesFieldSection,"IVContrast"	);//(32位)
	iniFile.AddKey(strSeriesFieldSection,"OralContrast"	);//(32位)
	iniFile.AddKey(strSeriesFieldSection,"ContrastAmount"		);
	iniFile.AddKey(strSeriesFieldSection,"PauseTime"			);
	iniFile.AddKey(strSeriesFieldSection,"NumAvg"			);
	iniFile.AddKey(strSeriesFieldSection,"PhEncOrder"			);
	iniFile.AddKey(strSeriesFieldSection,"Saturation"			);
	iniFile.AddKey(strSeriesFieldSection,"TI"				   	 );
	iniFile.AddKey(strSeriesFieldSection,"DataType"             );
	iniFile.AddKey(strSeriesFieldSection,"ReadPoints"			);
	iniFile.AddKey(strSeriesFieldSection,"PhasePoints"		);
	iniFile.AddKey(strSeriesFieldSection,"EchoRatio"			);
	iniFile.AddKey(strSeriesFieldSection,"Reserved");//(240位)*/

	iniFile.SetKeyValue(strSeriesFieldSection,"Version",		dataTypetoString(m_SeriesParams.Version						));
	iniFile.SetKeyValue(strSeriesFieldSection,"Size",			dataTypetoString(m_SeriesParams.Size							)				);
	iniFile.SetKeyValue(strSeriesFieldSection,"Id"	,			dataTypetoString(m_SeriesParams.Id								)				  );
	iniFile.SetKeyValue(strSeriesFieldSection,"Desc"	,		dataTypetoString(m_SeriesParams.Desc					)	); //(128位)
	iniFile.SetKeyValue(strSeriesFieldSection,"Protocol" ,		dataTypetoString(m_SeriesParams.Protocol   				)      );//(32位)
	iniFile.SetKeyValue(strSeriesFieldSection,"NucType"	  ,		dataTypetoString(m_SeriesParams.NucType	    				)  	);
	iniFile.SetKeyValue(strSeriesFieldSection,"GRR"		,		dataTypetoString(m_SeriesParams.GRR							)		);
	iniFile.SetKeyValue(strSeriesFieldSection,"TXCoil"	,		dataTypetoString(m_SeriesParams.TXCoil			 				)		 	);
	iniFile.SetKeyValue(strSeriesFieldSection,"UserTxCoilDesc",	dataTypetoString(m_SeriesParams.UserTxCoilDesc				));//(32位)
	iniFile.SetKeyValue(strSeriesFieldSection,"RcvCoil"	,		dataTypetoString(m_SeriesParams.RcvCoil						)		);
	iniFile.SetKeyValue(strSeriesFieldSection,"UserRcvCoilDesc",dataTypetoString(m_SeriesParams.UserRcvCoilDesc				));//(32位)
	iniFile.SetKeyValue(strSeriesFieldSection,"PulseSeqName",	dataTypetoString(m_SeriesParams.PulseSeqName				)	);//(64位)
	iniFile.SetKeyValue(strSeriesFieldSection,"SequenceOptions",dataTypetoString(m_SeriesParams.SequenceOptions  				)  );
	iniFile.SetKeyValue(strSeriesFieldSection,"OtherOptions",	dataTypetoString(m_SeriesParams.OtherOptions     				)    );
	iniFile.SetKeyValue(strSeriesFieldSection,"RefSeries1"	,	dataTypetoString(m_SeriesParams.RefSeries1						)		  );
	iniFile.SetKeyValue(strSeriesFieldSection,"RefImage1"	,	dataTypetoString(m_SeriesParams.RefImage1						)		);
	iniFile.SetKeyValue(strSeriesFieldSection,"RefSeries2"	,	dataTypetoString(m_SeriesParams.RefSeries2						)		);
	iniFile.SetKeyValue(strSeriesFieldSection,"RefImage2"	,	dataTypetoString(m_SeriesParams.RefImage2						)		);
	iniFile.SetKeyValue(strSeriesFieldSection,"Plane"     ,		dataTypetoString(m_SeriesParams.Plane            				)       	);
	iniFile.SetKeyValue(strSeriesFieldSection,"Mode"	,		dataTypetoString(m_SeriesParams.Mode							)			);
	iniFile.SetKeyValue(strSeriesFieldSection,"FovX"	,		dataTypetoString(m_SeriesParams.FovX							)			);
	iniFile.SetKeyValue(strSeriesFieldSection,"FovY"	,		dataTypetoString(m_SeriesParams.FovY							)			);
	iniFile.SetKeyValue(strSeriesFieldSection,"FovZ"	,		dataTypetoString(m_SeriesParams.FovZ							)			);
	iniFile.SetKeyValue(strSeriesFieldSection,"ResolutionX"	,	dataTypetoString(m_SeriesParams.ResolutionX					)	);
	iniFile.SetKeyValue(strSeriesFieldSection,"ResolutionY"	,	dataTypetoString(m_SeriesParams.ResolutionY					)	);
	iniFile.SetKeyValue(strSeriesFieldSection,"ResolutionZ"	,	dataTypetoString(m_SeriesParams.ResolutionZ					)	);
	iniFile.SetKeyValue(strSeriesFieldSection,"SliceThickness",	dataTypetoString(m_SeriesParams.SliceThickness					)	);
	
	/** [zhlxu 2007.11.9] 添加DefaultSliceOrder协议功能 **/
	iniFile.SetKeyValue(strSeriesFieldSection,"SliceOrder",	    dataTypetoString(m_SeriesParams.bDefaultSliceOrder					)	);
	iniFile.SetKeyValue(strSeriesFieldSection,"SliceGap"	,	dataTypetoString(m_SeriesParams.SliceGap						)		);
	/** [zhlxu 2007.11.9] **/
	
	
	iniFile.SetKeyValue(strSeriesFieldSection,"NumSlab"	,		dataTypetoString(m_SeriesParams.NumSlab						)	);
	iniFile.SetKeyValue(strSeriesFieldSection,"SlabOrder"	,	dataTypetoString(m_SeriesParams.SlabOrder						)	);
	iniFile.SetKeyValue(strSeriesFieldSection,"NumPntsPerSlab",	dataTypetoString(m_SeriesParams.NumPntsPerSlab				));
	iniFile.SetKeyValue(strSeriesFieldSection,"SlabOverlap"	,	dataTypetoString(m_SeriesParams.SlabOverlap					)	);
	iniFile.SetKeyValue(strSeriesFieldSection,"EchoTime"	,	dataTypetoString(m_SeriesParams.EchoTime						)	);
	iniFile.SetKeyValue(strSeriesFieldSection,"Echo2Time"	,	dataTypetoString(m_SeriesParams.Echo2Time						)		);
	iniFile.SetKeyValue(strSeriesFieldSection,"EchoSpacing"   ,	dataTypetoString(m_SeriesParams.EchoSpacing     				)  );
	iniFile.SetKeyValue(strSeriesFieldSection,"RepTime"	,		dataTypetoString(m_SeriesParams.RepTime						)	);
	iniFile.SetKeyValue(strSeriesFieldSection,"NumEchoImages",	dataTypetoString(m_SeriesParams.NumEchoImages					)	);
	iniFile.SetKeyValue(strSeriesFieldSection,"AcqBandwidth",	dataTypetoString(m_SeriesParams.AcqBandwidth					)	);
	iniFile.SetKeyValue(strSeriesFieldSection,"AcqBandwidth2",	dataTypetoString(m_SeriesParams.AcqBandwidth2					)	);
	iniFile.SetKeyValue(strSeriesFieldSection,"EchoTrainLength",dataTypetoString(m_SeriesParams.EchoTrainLength				));
	iniFile.SetKeyValue(strSeriesFieldSection,"FlipAngle"	,	dataTypetoString(m_SeriesParams.FlipAngle						)	);
	iniFile.SetKeyValue(strSeriesFieldSection,"GradientShimX",	dataTypetoString(m_SeriesParams.GradientShimX					)	);
	iniFile.SetKeyValue(strSeriesFieldSection,"GradientShimY",	dataTypetoString(m_SeriesParams.GradientShimY					)	);
	iniFile.SetKeyValue(strSeriesFieldSection,"GradientShimZ",	dataTypetoString(m_SeriesParams.GradientShimZ					)	);
	iniFile.SetKeyValue(strSeriesFieldSection,"SARAvg"		,	dataTypetoString(m_SeriesParams.SARAvg							)		);
	iniFile.SetKeyValue(strSeriesFieldSection,"SARPeak"		,	dataTypetoString(m_SeriesParams.SARPeak						)	);
	iniFile.SetKeyValue(strSeriesFieldSection,"DigFilterType",	dataTypetoString(m_SeriesParams.DigFilterType					)	);
	iniFile.SetKeyValue(strSeriesFieldSection,"DigFilterPar",	F4ArraytoString(m_SeriesParams.DigFilterPar,8)	);//(8位)
	iniFile.SetKeyValue(strSeriesFieldSection,"WindowLevel"	,	dataTypetoString(m_SeriesParams.WindowLevel					)	);
	iniFile.SetKeyValue(strSeriesFieldSection,"WindowWidth"	,	dataTypetoString(m_SeriesParams.WindowWidth					)	);
	iniFile.SetKeyValue(strSeriesFieldSection,"FlowCompensation",dataTypetoString(m_SeriesParams.FlowCompensation				)	);
	iniFile.SetKeyValue(strSeriesFieldSection,"PompNumber",		dataTypetoString(m_SeriesParams.PompNumber				));
	iniFile.SetKeyValue(strSeriesFieldSection,"NumOfAngioImages",dataTypetoString(m_SeriesParams.NumOfAngioImages				));
	iniFile.SetKeyValue(strSeriesFieldSection,"HalfKSpaceRatio",dataTypetoString(m_SeriesParams.HalfKSpaceRatio				)	);
	iniFile.SetKeyValue(strSeriesFieldSection,"ContrastFlag",	dataTypetoString(m_SeriesParams.ContrastFlag					)		);
	iniFile.SetKeyValue(strSeriesFieldSection,"IVContrast"	,	dataTypetoString(m_SeriesParams.IVContrast				));//(32位)
	iniFile.SetKeyValue(strSeriesFieldSection,"OralContrast",	dataTypetoString(m_SeriesParams.OralContrast				)	);//(32位)
	iniFile.SetKeyValue(strSeriesFieldSection,"ContrastAmount",	dataTypetoString(m_SeriesParams.ContrastAmount					)	);
	iniFile.SetKeyValue(strSeriesFieldSection,"PauseTime"	,	dataTypetoString(m_SeriesParams.PauseTime						)		);
	iniFile.SetKeyValue(strSeriesFieldSection,"NumAvg"		,	dataTypetoString(m_SeriesParams.NumAvg							)	);
	iniFile.SetKeyValue(strSeriesFieldSection,"PhEncOrder"	,	dataTypetoString(m_SeriesParams.PhEncOrder						)		);
	iniFile.SetKeyValue(strSeriesFieldSection,"Saturation"	,	dataTypetoString(m_SeriesParams.Saturation						)		);
	iniFile.SetKeyValue(strSeriesFieldSection,"TI"			,	dataTypetoString(m_SeriesParams.TI				  				)	   	 );
	iniFile.SetKeyValue(strSeriesFieldSection,"DataType"       ,dataTypetoString(m_SeriesParams.DataType         				)      );
	iniFile.SetKeyValue(strSeriesFieldSection,"ReadPoints"	,	dataTypetoString(m_SeriesParams.ReadPoints						)		);
	iniFile.SetKeyValue(strSeriesFieldSection,"PhasePoints"	,	dataTypetoString(m_SeriesParams.PhasePoints					)	);
	iniFile.SetKeyValue(strSeriesFieldSection,"EchoRatio"	,	dataTypetoString(m_SeriesParams.EchoRatio						)		);
	iniFile.SetKeyValue(strSeriesFieldSection,"Reserved",		dataTypetoString(m_SeriesParams.Reserved				));//(240位)
	
	CString region_Sectiontemp("");
	//char cTemp[5];      //Modified by Tom, --2008.07.10
	for(int i=0;i<6;i++)
	{
		region_Sectiontemp.Format(presaturation_region_Section+"_%d",i);
		
/*		iniFile.AddSection(region_Sectiontemp);
		iniFile.AddKey(region_Sectiontemp,"m_bUse");
		iniFile.AddKey(region_Sectiontemp,"m_sPos");
		iniFile.AddKey(region_Sectiontemp,"m_sThickness");**/
	
		iniFile.SetKeyValue(region_Sectiontemp,"m_bUse",dataTypetoString(m_SeriesParams.PresaturationRegions[i].m_bUse	));
		iniFile.SetKeyValue(region_Sectiontemp,"m_sPos",dataTypetoString(m_SeriesParams.PresaturationRegions[i].m_sPos	));
		iniFile.SetKeyValue(region_Sectiontemp,"m_sThickness",dataTypetoString(m_SeriesParams.PresaturationRegions[i].m_sThickness	));
		
		region_Sectiontemp.Empty();
	}
	

	iniFile.AddSection(strGatingTriggerSection);
	iniFile.AddKey(strGatingTriggerSection, "GatingID");
	iniFile.AddKey(strGatingTriggerSection, "Delay");
	iniFile.AddKey(strGatingTriggerSection, "MinTimeInterval");
	iniFile.AddKey(strGatingTriggerSection, "NumOfMaxErrs");
	iniFile.AddKey(strGatingTriggerSection, "NumOfTotalErrs");
	iniFile.AddKey(strGatingTriggerSection, "NumOfTriggers");
	iniFile.AddKey(strGatingTriggerSection, "TriggerInterval");

	iniFile.SetKeyValue(strGatingTriggerSection, "GatingID", dataTypetoString(m_SeriesParams.GatingParams.nGatingID));
	iniFile.SetKeyValue(strGatingTriggerSection, "Delay", dataTypetoString(m_SeriesParams.GatingParams.nDelay));
	iniFile.SetKeyValue(strGatingTriggerSection, "MinTimeInterval", dataTypetoString(m_SeriesParams.GatingParams.nMinTimeInterval));
	iniFile.SetKeyValue(strGatingTriggerSection, "NumOfMaxErrs", dataTypetoString(m_SeriesParams.GatingParams.nNumOfMaxErrs));
	iniFile.SetKeyValue(strGatingTriggerSection, "NumOfTotalErrs", dataTypetoString(m_SeriesParams.GatingParams.nNumOfTotalErrs));
	iniFile.SetKeyValue(strGatingTriggerSection, "NumOfTriggers", dataTypetoString(m_SeriesParams.GatingParams.nNumOfTriggers));
	iniFile.SetKeyValue(strGatingTriggerSection, "TriggerInterval", dataTypetoString(m_SeriesParams.GatingParams.nTriggerInterval));


	iniFile.SetKeyValue(bidate_time_Section,"year",dataTypetoString(m_SeriesParams.DateTime.year)	);
	iniFile.SetKeyValue(bidate_time_Section,"month"	,dataTypetoString(m_SeriesParams.DateTime.month));
	iniFile.SetKeyValue(bidate_time_Section,"day"	,dataTypetoString(m_SeriesParams.DateTime.day));
	iniFile.SetKeyValue(bidate_time_Section,"hour"	,dataTypetoString(m_SeriesParams.DateTime.hour));
	iniFile.SetKeyValue(bidate_time_Section,"minute"	,dataTypetoString(m_SeriesParams.DateTime.minute));
	iniFile.SetKeyValue(bidate_time_Section,"second"	,dataTypetoString(m_SeriesParams.DateTime.second));

	int iScanFieldNum =0;
	for (CScanFieldIter it1 = m_Scans.begin(); it1 != m_Scans.end(); it1++)
    {
		
		ScanField it = **it1;
       // ar.Write(reinterpret_cast<char*>(*it), sizeof (ScanField));
		CString strTemp(scan_field_Section);
		strTemp.Format(strTemp+"%d",iScanFieldNum);

		iniFile.SetKeyValue(strTemp,CString("Version"		),dataTypetoString(it.Version	));
		iniFile.SetKeyValue(strTemp,CString("Size"			),dataTypetoString(it.Size		)	);
		iniFile.SetKeyValue(strTemp,CString("Id"			),dataTypetoString(it.Id			)		);
		iniFile.SetKeyValue(strTemp,CString("FreqDir"		),dataTypetoString(it.FreqDir	)		);
		iniFile.SetKeyValue(strTemp,CString("FreqDirX"		),dataTypetoString(it.FreqDirX	)	);
		iniFile.SetKeyValue(strTemp,CString("FreqDirY"		),dataTypetoString(it.FreqDirY	)		);
		iniFile.SetKeyValue(strTemp,CString("FreqDirZ"		),dataTypetoString(it.FreqDirZ  	)	);
		iniFile.SetKeyValue(strTemp,CString("PhaseDirX"		),dataTypetoString(it.PhaseDirX	)	);
		iniFile.SetKeyValue(strTemp,CString("PhaseDirY"		),dataTypetoString(it.PhaseDirY	)	);
		iniFile.SetKeyValue(strTemp,CString("PhaseDirZ"		),dataTypetoString(it.PhaseDirZ	)	);
		iniFile.SetKeyValue(strTemp,CString("SliceDirX"		),dataTypetoString(it.SliceDirX	)	);
		iniFile.SetKeyValue(strTemp,CString("SliceDirY"		),dataTypetoString(it.SliceDirY	)	);
		iniFile.SetKeyValue(strTemp,CString("SliceDirZ"		),dataTypetoString(it.SliceDirZ	));
		iniFile.SetKeyValue(strTemp,CString("ReadOffset"	),dataTypetoString(it.ReadOffset	));
		iniFile.SetKeyValue(strTemp,CString("PhaseOffset"	),dataTypetoString(it.PhaseOffset	));
		iniFile.SetKeyValue(strTemp,CString("SliceOffset"	),dataTypetoString(it.SliceOffset	)	);
		iniFile.SetKeyValue(strTemp,CString("RFTxLev"		),dataTypetoString(it.RFTxLev	));
		iniFile.SetKeyValue(strTemp,CString("AnaRCGain"		),dataTypetoString(it.AnaRCGain	));
		iniFile.SetKeyValue(strTemp,CString("DigRCGain"		),dataTypetoString(it.DigRCGain	));
		iniFile.SetKeyValue(strTemp,CString("O1"			),dataTypetoString(it.O1			)	);
		iniFile.SetKeyValue(strTemp,CString("ACQ"			),dataTypetoString(it.ACQ		)		);
		iniFile.SetKeyValue(strTemp,CString("Reservered")    ,dataTypetoString(it.Reservered	)	); //(256位)
		iScanFieldNum++;

    }
return true;

}

bool CSeriesProtocol::Load(CIniFile& iniFile,CString strSectionPrefix,int index)
{
	CString strSeriesProtocolSection = "SERIES_PROTOCOL_";
			strSeriesProtocolSection.Format(strSectionPrefix+"."+strSeriesProtocolSection+"%d",index);
	CString strSeriesFieldSection = "SERIES_FIELD";
			strSeriesFieldSection.Format(strSeriesProtocolSection+"."+strSeriesFieldSection);
	
	CString presaturation_region_Section = "PRESATURATION_REGION";
			presaturation_region_Section.Format(strSeriesProtocolSection+".SERIES_FIELD."+presaturation_region_Section);
	CString strGatingTriggerSection = "GATINGTRIGGER";
			strGatingTriggerSection.Format(strSeriesProtocolSection+".SERIES_FIELD."+strGatingTriggerSection);
	CString bidate_time_Section = "BIDATE_TIME";
			bidate_time_Section.Format(strSeriesProtocolSection+".SERIES_FIELD."+bidate_time_Section);

	CString scan_field_Section = "SCAN_FIELD_";
			scan_field_Section.Format(strSeriesProtocolSection+"."+scan_field_Section);

    // Read in the protocol name first.
    char pchBuf[32] = {0};
	CStringtoI1Array(iniFile.GetKeyValue(strSeriesProtocolSection,"series_protocol_name"),31,pchBuf);
	 m_strProtocolName = pchBuf;
    //UINT nCount = ar.Read(pchBuf, 32);
//	CStringArray arrayKey,arraykeyValue;
	//iniFile.GetAllKeysAndValues(strSeriesProtocolSection,arrayKey,arraykeyValue);

	m_SeriesParams.Version					= CStringtoI4(	iniFile.GetKeyValue(strSeriesFieldSection,"Version")		);
	m_SeriesParams.Size						= CStringtoU2(	iniFile.GetKeyValue(strSeriesFieldSection,"Size")		);		
	m_SeriesParams.Id						= CStringtoU1(	iniFile.GetKeyValue(strSeriesFieldSection,"Id")		);
	CStringtoI1Array(	iniFile.GetKeyValue(strSeriesFieldSection,"Desc")	,128-1,m_SeriesParams.Desc	);
	CStringtoI1Array(	iniFile.GetKeyValue(strSeriesFieldSection,"Protocol")	,32-1,m_SeriesParams.Protocol 	);
	m_SeriesParams.NucType	    			= CStringtoI2(	iniFile.GetKeyValue(strSeriesFieldSection,"NucType")		);
	m_SeriesParams.GRR						= CStringtoI4(	iniFile.GetKeyValue(strSeriesFieldSection,"GRR")		);
	m_SeriesParams.TXCoil			 		= CStringtoU1(	iniFile.GetKeyValue(strSeriesFieldSection,"TXCoil")		);
	CStringtoI1Array(	iniFile.GetKeyValue(strSeriesFieldSection,"UserTxCoilDesc")	,32-1,m_SeriesParams.UserTxCoilDesc	);
	m_SeriesParams.RcvCoil					= CStringtoU1(	iniFile.GetKeyValue(strSeriesFieldSection,"RcvCoil")		);
	CStringtoI1Array(	iniFile.GetKeyValue(strSeriesFieldSection,"UserRcvCoilDesc")	,32-1,m_SeriesParams.UserRcvCoilDesc		);
	CStringtoI1Array(	iniFile.GetKeyValue(strSeriesFieldSection,"PulseSeqName"),64-1,m_SeriesParams.PulseSeqName	);
	m_SeriesParams.SequenceOptions  		= CStringtoI4(	iniFile.GetKeyValue(strSeriesFieldSection,"SequenceOptions")		);
	m_SeriesParams.OtherOptions     		= CStringtoI4(	iniFile.GetKeyValue(strSeriesFieldSection,"OtherOptions")		);
	m_SeriesParams.RefSeries1				= CStringtoI1(	iniFile.GetKeyValue(strSeriesFieldSection,"RefSeries1")		);
	m_SeriesParams.RefImage1				= CStringtoI1(	iniFile.GetKeyValue(strSeriesFieldSection,"RefImage1")		);
	m_SeriesParams.RefSeries2				= CStringtoI1(	iniFile.GetKeyValue(strSeriesFieldSection,"RefSeries2")		);
	m_SeriesParams.RefImage2				= CStringtoI1(	iniFile.GetKeyValue(strSeriesFieldSection,"RefImage2")		);
	m_SeriesParams.Plane            		= CStringtoU1(	iniFile.GetKeyValue(strSeriesFieldSection,"Plane")		);
	m_SeriesParams.Mode						= CStringtoU1(	iniFile.GetKeyValue(strSeriesFieldSection,"Mode")		);
	m_SeriesParams.FovX						= CStringtoU2(	iniFile.GetKeyValue(strSeriesFieldSection,"FovX")		);
	m_SeriesParams.FovY						= CStringtoU2(	iniFile.GetKeyValue(strSeriesFieldSection,"FovY")		);
	m_SeriesParams.FovZ						= CStringtoU2(	iniFile.GetKeyValue(strSeriesFieldSection,"FovZ")		);
	m_SeriesParams.ResolutionX				= CStringtoU2(	iniFile.GetKeyValue(strSeriesFieldSection,"ResolutionX")		);
	m_SeriesParams.ResolutionY				= CStringtoU2(	iniFile.GetKeyValue(strSeriesFieldSection,"ResolutionY")		);
	m_SeriesParams.ResolutionZ				= CStringtoU2(	iniFile.GetKeyValue(strSeriesFieldSection,"ResolutionZ")		);
	m_SeriesParams.SliceThickness			= CStringtoF4(	iniFile.GetKeyValue(strSeriesFieldSection,"SliceThickness")		);
	m_SeriesParams.SliceGap					= CStringtoF4(	iniFile.GetKeyValue(strSeriesFieldSection,"SliceGap")		);
	
	/** [zhlxu 2007.11.3] 添加DefaultSliceOrder协议功能 **/
	m_SeriesParams.bDefaultSliceOrder		= CStringtoF4(	iniFile.GetKeyValue(strSeriesFieldSection,"SliceOrder")		);
	if ( !m_SeriesParams.bDefaultSliceOrder && m_SeriesParams.SliceGap > 0.0 )
	{
		m_SeriesParams.bDefaultSliceOrder = true;
	}
	/** [zhlxu 2007.11.3] **/
	
	m_SeriesParams.NumSlab					= CStringtoU2(	iniFile.GetKeyValue(strSeriesFieldSection,"NumSlab")		);
	m_SeriesParams.SlabOrder				= CStringtoU1(	iniFile.GetKeyValue(strSeriesFieldSection,"SlabOrder")		);
	m_SeriesParams.NumPntsPerSlab			= CStringtoU2(	iniFile.GetKeyValue(strSeriesFieldSection,"NumPntsPerSlab")		);
	m_SeriesParams.SlabOverlap				= CStringtoU2(	iniFile.GetKeyValue(strSeriesFieldSection,"SlabOverlap")		);
	m_SeriesParams.EchoTime					= CStringtoU4(	iniFile.GetKeyValue(strSeriesFieldSection,"EchoTime")		);
	m_SeriesParams.Echo2Time				= CStringtoU4(	iniFile.GetKeyValue(strSeriesFieldSection,"Echo2Time")		);
	m_SeriesParams.EchoSpacing     			= CStringtoU4(	iniFile.GetKeyValue(strSeriesFieldSection,"EchoSpacing")		);
	m_SeriesParams.RepTime					= CStringtoI4(	iniFile.GetKeyValue(strSeriesFieldSection,"RepTime")		);
	m_SeriesParams.NumEchoImages			= CStringtoU2(	iniFile.GetKeyValue(strSeriesFieldSection,"NumEchoImages")		);
	m_SeriesParams.AcqBandwidth				= CStringtoF4(	iniFile.GetKeyValue(strSeriesFieldSection,"AcqBandwidth")		);
	m_SeriesParams.AcqBandwidth2			= CStringtoF4(	iniFile.GetKeyValue(strSeriesFieldSection,"AcqBandwidth2")		);
	m_SeriesParams.EchoTrainLength			= CStringtoU2(	iniFile.GetKeyValue(strSeriesFieldSection,"EchoTrainLength")		);
	m_SeriesParams.FlipAngle				= CStringtoF4(	iniFile.GetKeyValue(strSeriesFieldSection,"FlipAngle")		);	
	m_SeriesParams.GradientShimX			= CStringtoI4(	iniFile.GetKeyValue(strSeriesFieldSection,"GradientShimX")		);
	m_SeriesParams.GradientShimY			= CStringtoI4(	iniFile.GetKeyValue(strSeriesFieldSection,"GradientShimY")		);
	m_SeriesParams.GradientShimZ			= CStringtoI4(	iniFile.GetKeyValue(strSeriesFieldSection,"GradientShimZ")		);
	m_SeriesParams.SARAvg					= CStringtoI4(	iniFile.GetKeyValue(strSeriesFieldSection,"SARAvg")		);
	m_SeriesParams.SARPeak					= CStringtoI4(	iniFile.GetKeyValue(strSeriesFieldSection,"SARPeak")		);
	m_SeriesParams.DigFilterType			= CStringtoI2(	iniFile.GetKeyValue(strSeriesFieldSection,"DigFilterType")		);
	
	bool bDigfilter =	CStringtoF4Array(	iniFile.GetKeyValue(strSeriesFieldSection,"DigFilterPar"),8,m_SeriesParams.DigFilterPar		);
	if(!bDigfilter)
		return false;

	m_SeriesParams.WindowLevel				= CStringtoI2(	iniFile.GetKeyValue(strSeriesFieldSection,"WindowLevel")		);
	m_SeriesParams.WindowWidth				= CStringtoI2(	iniFile.GetKeyValue(strSeriesFieldSection,"WindowWidth")		);
	m_SeriesParams.FlowCompensation			= CStringtoI1(	iniFile.GetKeyValue(strSeriesFieldSection,"FlowCompensation")		);
/*	if (((int)m_SeriesParams.FlowCompensation)==1) {
		TRACE("m_SeriesParams.FlowCompensation==1");
	}
	else{
		TRACE("m_SeriesParams.FlowCompensation==0\n");
	}*/
	m_SeriesParams.PompNumber				= CStringtoU1(	iniFile.GetKeyValue(strSeriesFieldSection,"PompNumber")		);
	m_SeriesParams.NumOfAngioImages			= CStringtoU1(	iniFile.GetKeyValue(strSeriesFieldSection,"NumOfAngioImages")		);
	m_SeriesParams.HalfKSpaceRatio			= CStringtoF4(	iniFile.GetKeyValue(strSeriesFieldSection,"HalfKSpaceRatio")		);
	m_SeriesParams.ContrastFlag				= CStringtoI1(	iniFile.GetKeyValue(strSeriesFieldSection,"ContrastFlag")		);
	CStringtoI1Array(	iniFile.GetKeyValue(strSeriesFieldSection,"IVContrast")	,32-1	,m_SeriesParams.IVContrast);
	CStringtoI1Array(	iniFile.GetKeyValue(strSeriesFieldSection,"OralContrast")	,32-1	,m_SeriesParams.OralContrast);
	m_SeriesParams.ContrastAmount			= CStringtoF4(	iniFile.GetKeyValue(strSeriesFieldSection,"ContrastAmount")		);
	m_SeriesParams.PauseTime				= CStringtoF4(	iniFile.GetKeyValue(strSeriesFieldSection,"PauseTime")		);
	m_SeriesParams.NumAvg					= CStringtoI2(	iniFile.GetKeyValue(strSeriesFieldSection,"NumAvg")		);
	m_SeriesParams.PhEncOrder				= CStringtoI2(	iniFile.GetKeyValue(strSeriesFieldSection,"PhEncOrder")		);
	m_SeriesParams.Saturation				= CStringtoI2(	iniFile.GetKeyValue(strSeriesFieldSection,"Saturation")		);
	m_SeriesParams.TI				  		= CStringtoI4(	iniFile.GetKeyValue(strSeriesFieldSection,"TI")		);
	m_SeriesParams.DataType         		= CStringtoU1(	iniFile.GetKeyValue(strSeriesFieldSection,"DataType")		);
	m_SeriesParams.ReadPoints				= CStringtoU2(	iniFile.GetKeyValue(strSeriesFieldSection,"ReadPoints")		);
	m_SeriesParams.PhasePoints				= CStringtoU2(	iniFile.GetKeyValue(strSeriesFieldSection,"PhasePoints")		);
	m_SeriesParams.EchoRatio				= CStringtoF4(	iniFile.GetKeyValue(strSeriesFieldSection,"EchoRatio")		);
	CStringtoI1Array(	iniFile.GetKeyValue(strSeriesFieldSection,"Reserved"),240-1,	m_SeriesParams.Reserved	);

	CString region_Sectiontemp("");
	//char cTemp[5];    //Modified by Tom, --2008.07.10
	for(int i=0;i<6;i++)
	{
		region_Sectiontemp.Format(presaturation_region_Section+"_%d",i);

		// i对应于人体方向(L(i=0),R(i=1),A(i=2),P(i=3),S(i=4),I(i=5))
		m_SeriesParams.PresaturationRegions[i].m_bUse = CStringtoI1(iniFile.GetKeyValue(region_Sectiontemp,"m_bUse"));
		m_SeriesParams.PresaturationRegions[i].m_sPos = CStringtoI2(iniFile.GetKeyValue(region_Sectiontemp,"m_sPos"));
		m_SeriesParams.PresaturationRegions[i].m_sThickness = CStringtoI2(iniFile.GetKeyValue(region_Sectiontemp,"m_sThickness"));

		region_Sectiontemp.Empty();
	}

	m_SeriesParams.GatingParams.nGatingID        = CStringtoI1(iniFile.GetKeyValue(strGatingTriggerSection, "GatingID"));
	m_SeriesParams.GatingParams.nDelay           = CStringtoI2(iniFile.GetKeyValue(strGatingTriggerSection, "Delay"));
	m_SeriesParams.GatingParams.nMinTimeInterval = CStringtoI2(iniFile.GetKeyValue(strGatingTriggerSection, "MinTimeInterval"));
	m_SeriesParams.GatingParams.nNumOfMaxErrs    = CStringtoI2(iniFile.GetKeyValue(strGatingTriggerSection, "NumOfMaxErrs"));
	m_SeriesParams.GatingParams.nNumOfTotalErrs  = CStringtoI2(iniFile.GetKeyValue(strGatingTriggerSection, "NumOfTotalErrs"));
	m_SeriesParams.GatingParams.nNumOfTriggers   = CStringtoI2(iniFile.GetKeyValue(strGatingTriggerSection, "NumOfTriggers"));
	m_SeriesParams.GatingParams.nTriggerInterval = CStringtoI2(iniFile.GetKeyValue(strGatingTriggerSection, "TriggerInterval"));
//	m_SeriesParams.RespiratoryTrigger.m_ucInterval	=	CStringtoU1(iniFile.GetKeyValue(respiratory_trigger_Section,"m_ucInterval"));
//	m_SeriesParams.RespiratoryTrigger.m_ucRate	=	CStringtoU1(iniFile.GetKeyValue(respiratory_trigger_Section,"m_ucRate"));
//	m_SeriesParams.RespiratoryTrigger.m_ucTriggerPoint	=	CStringtoU1(iniFile.GetKeyValue(respiratory_trigger_Section,"m_ucTriggerPoint"));
//	m_SeriesParams.RespiratoryTrigger.m_ucTriggerWindow	=	CStringtoU1(iniFile.GetKeyValue(respiratory_trigger_Section,"m_ucTriggerWindow"));
//	m_SeriesParams.RespiratoryTrigger.m_usInterSequenceDelay	=	CStringtoU2(iniFile.GetKeyValue(respiratory_trigger_Section,"m_usInterSequenceDelay"));

//	m_SeriesParams.CardiacGating.m_ucPhasesPerSegment	=	CStringtoU1(iniFile.GetKeyValue(cardiac_gating_Section,"m_ucPhasesPerSegment"));
//	m_SeriesParams.CardiacGating.m_ucSkipBeat	=	CStringtoU1(iniFile.GetKeyValue(cardiac_gating_Section,"m_ucSkipBeat"));
//	m_SeriesParams.CardiacGating.m_usNumOfImages	=	CStringtoU1(iniFile.GetKeyValue(cardiac_gating_Section,"m_usNumOfImages"));
//	m_SeriesParams.CardiacGating.m_usRate	=	CStringtoU2(iniFile.GetKeyValue(cardiac_gating_Section,"m_usRate"));
//	m_SeriesParams.CardiacGating.m_usTriggerDelayTime	=	CStringtoU2(iniFile.GetKeyValue(cardiac_gating_Section,"m_usTriggerDelayTime"));
//	m_SeriesParams.CardiacGating.m_usTriggerWin	=	CStringtoU1(iniFile.GetKeyValue(cardiac_gating_Section,"m_usTriggerWin"));

	m_SeriesParams.DateTime.day		=	CStringtoU1(iniFile.GetKeyValue(bidate_time_Section,"day"));
	m_SeriesParams.DateTime.hour		=	CStringtoU1(iniFile.GetKeyValue(bidate_time_Section,"hour"));
	m_SeriesParams.DateTime.minute	=	CStringtoU1(iniFile.GetKeyValue(bidate_time_Section,"minute"));
	m_SeriesParams.DateTime.month	=	CStringtoU1(iniFile.GetKeyValue(bidate_time_Section,"month"));
	m_SeriesParams.DateTime.second	=	CStringtoU1(iniFile.GetKeyValue(bidate_time_Section,"second"));
	m_SeriesParams.DateTime.year	=	CStringtoU1(iniFile.GetKeyValue(bidate_time_Section,"year"));

	int nScans = CStringtoI4(iniFile.GetKeyValue(strSeriesProtocolSection,"n_scan_fields"));

	for( i=0;i<nScans;i++)
	{
		ScanField * pScanParams = new ScanField;
		scan_field_Section.Format(scan_field_Section+"%d",i);
		pScanParams->Version			=	CStringtoI4(iniFile.GetKeyValue(scan_field_Section,"Version"));
		pScanParams->Size					=	CStringtoU2(iniFile.GetKeyValue(scan_field_Section,"Size"));
		pScanParams->Id						=	CStringtoI4(iniFile.GetKeyValue(scan_field_Section,"Id"));
		pScanParams->FreqDir				=	CStringtoU1(iniFile.GetKeyValue(scan_field_Section,"FreqDir"));
		pScanParams->FreqDirX				=	CStringtoF4(iniFile.GetKeyValue(scan_field_Section,"FreqDirX"));
		pScanParams->FreqDirY			=	CStringtoF4(iniFile.GetKeyValue(scan_field_Section,"FreqDirY"));
		pScanParams->FreqDirZ   			=	CStringtoF4(iniFile.GetKeyValue(scan_field_Section,"FreqDirZ"));
		pScanParams->PhaseDirX			=	CStringtoF4(iniFile.GetKeyValue(scan_field_Section,"PhaseDirX"));
		pScanParams->PhaseDirY			=	CStringtoF4(iniFile.GetKeyValue(scan_field_Section,"PhaseDirY"));
		pScanParams->PhaseDirZ				=	CStringtoF4(iniFile.GetKeyValue(scan_field_Section,"PhaseDirZ"));
		pScanParams->SliceDirX			=	CStringtoF4(iniFile.GetKeyValue(scan_field_Section,"SliceDirX"));
		pScanParams->SliceDirY			=	CStringtoF4(iniFile.GetKeyValue(scan_field_Section,"SliceDirY"));
		pScanParams->SliceDirZ			=	CStringtoF4(iniFile.GetKeyValue(scan_field_Section,"SliceDirZ"));
		pScanParams->ReadOffset			=	CStringtoF4(iniFile.GetKeyValue(scan_field_Section,"ReadOffset"));
		pScanParams->PhaseOffset			=	CStringtoF4(iniFile.GetKeyValue(scan_field_Section,"PhaseOffset"));
		pScanParams->SliceOffset			=	CStringtoF4(iniFile.GetKeyValue(scan_field_Section,"SliceOffset"));
		pScanParams->RFTxLev				=	CConfigManager::GetHandle().GetCoilSpec((ECoilType)m_SeriesParams.TXCoil).m_dDefaultTG;// 20060412
		pScanParams->AnaRCGain				=	CStringtoF4(iniFile.GetKeyValue(scan_field_Section,"AnaRCGain"));
		pScanParams->DigRCGain				=	CStringtoF4(iniFile.GetKeyValue(scan_field_Section,"DigRCGain"));
		pScanParams->O1						=	CStringtoF4(iniFile.GetKeyValue(scan_field_Section,"O1"));
		pScanParams->ACQ					=	CStringtoU2(iniFile.GetKeyValue(scan_field_Section,"ACQ"));
		CStringtoI1Array(iniFile.GetKeyValue(scan_field_Section,"Reservered"),256-1,pScanParams->Reservered);

		m_Scans.push_back(pScanParams);

	}


	return true;
}
/************************************************************************/
/* end                                                                     */
/************************************************************************/
/*!
    Load the series protocol from an input stream. Called from within the 
    CStudyProtocol::Load().
    \param inStream Input stream from which the protocol it to be loaded.
    \return \a true if successful, \a false otherwise.
*/
bool CSeriesProtocol::Load(std::istream& inStream)
{
    if (!inStream)
        return false;

    // Read in the protocol name first.
    char pchBuf[32] = {0};
    inStream.read(pchBuf, 32);
    if (inStream.gcount() != 32)
        return false;
    m_strProtocolName = pchBuf;

    int nScans;
    inStream.read(reinterpret_cast<char*>(&nScans), sizeof(int));
    for (int i = 0; i < nScans; i++)
    {
        ScanField * pScanParams;
        try
        {
            pScanParams = new ScanField;
        }
        catch(std::bad_alloc& e)
        {
            std::cerr << e.what();
            exit(EXIT_FAILURE);
        }
        inStream.read(reinterpret_cast<char*>(pScanParams), 
            sizeof (ScanField));
        m_Scans.push_back(pScanParams);
    }
	return true;
}

bool CSeriesProtocol::Load(CArchive& ar)
{
    if (!ar.IsLoading())
        return false;

    // Read in the protocol name first.
    char pchBuf[32] = {0};
    UINT nCount = ar.Read(pchBuf, 32);
    if (nCount != 32)
        return false;
    m_strProtocolName = pchBuf;

	ar.Read(reinterpret_cast<char*>(&m_SeriesParams), sizeof (m_SeriesParams));

    int nScans;
    ar.Read(reinterpret_cast<char*>(&nScans), sizeof(int));
    for (int i = 0; i < nScans; i++)
    {
        ScanField * pScanParams;
        try
        {
            pScanParams = new ScanField;
        }
        catch(std::bad_alloc& e)
        {
            std::cerr << e.what();
            exit(EXIT_FAILURE);
        }
        ar.Read(reinterpret_cast<char*>(pScanParams), sizeof (ScanField));
        m_Scans.push_back(pScanParams);
    }
	return true;
}



// Rodger: 编号存在问题，如果自定义brain临床协议数目超出brain编号范围（0-10），怎么办？
BOOL CSeriesProtocol::SelectProtocolfromDlg(int nProtocol)
{
	switch (nProtocol + 1)
	{
// << Brain
	case 1: //sagittal se for localization
		CProtocolExample::SeriesSESag(&Params(), Scans()[0]);
		Params().PhasePoints = 128;
		Params().ResolutionZ = 3;
		Params().RepTime = 250000;
		Params().NumAvg = 1;
		strcpy(Params().Desc, "Sag SE2D Localization");
		break;
	case 2: // Fse2d, Ax
 		CProtocolExample::SeriesFSEAx(&Params(), Scans()[0]);
		strcpy(Params().Desc, "Axial FSE 2D T2W");
		break;
	case 3:	// flair ax
		CProtocolExample::SeriesFLAIRAx(&Params(), Scans()[0]);
		strcpy(Params().Desc, "Axial FLAIR");
		break;
	case 4:// AX SE
		CProtocolExample::SeriesSEAx(&Params(), Scans()[0]);
		strcpy(Params().Desc, "Axial SE2D T1W");
		break;
	case 5: // sag se
		CProtocolExample::SeriesSESag(&Params(), Scans()[0]);
		strcpy(Params().Desc, "Sagittal SE2D T1W");
		break;
	case 6: // cor se
		CProtocolExample::SeriesSECor(&Params(), Scans()[0]);
		strcpy(Params().Desc, "Coronal SE2D T1W");
		break;
	case 7: // sagittal fse
		CProtocolExample::SeriesFSESag(&Params(), Scans()[0]);
		strcpy(Params().Desc, "Sagittal FSE2D T2W FC");
		break;
	
	case 8:	// cor fse
		CProtocolExample::SeriesFSECor(&Params(), Scans()[0]);
		strcpy(Params().Desc, "Coronal FSE2D T2W FC");
		break;
	case 9:	// sag flair
		CProtocolExample::SeriesFLAIRSag(&Params(), Scans()[0]);
		strcpy(Params().Desc, "Sagittal FLAIR");
		break;
	case 10: // cor flair
		CProtocolExample::SeriesFLAIRCor(&Params(), Scans()[0]);
		strcpy(Params().Desc, "Coronal FLAIR");
		break;
// >> Brain

// << Pelvis
	case 11: // sag se localization;
		CProtocolExample::PelvSESag(&Params(), Scans()[0]);
		Params().PhasePoints = 128;
		Params().ResolutionZ = 3;
		Params().NumAvg = 1;
		strcpy(Params().Desc, "Sag SE2D Localization");
		break;
	case 12://cor se localization.
		CProtocolExample::PelvSECor(&Params(), Scans()[0]);
		Params().ResolutionZ = 3;
		Params().NumAvg = 1;
		Params().PhasePoints = 128;
		strcpy(Params().Desc, "Cor SE2D Localization");
		break;
	case 13:
		CProtocolExample::PelvFSEAx(&Params(),	Scans()[0]);
		strcpy(Params().Desc, "Axial FSE2D T2W");
		break;
	case 14: 
		CProtocolExample::PelvSEAx(&Params(), Scans()[0]);
		strcpy(Params().Desc, "Axial SE2D T1W");
		break;
	case 15:
		CProtocolExample::PelvSTIRAx(&Params(), Scans()[0]);
		strcpy(Params().Desc, "Axial STIR");
		break;
	case 16:
		CProtocolExample::PelvFSESag(&Params(), Scans()[0]);
		strcpy(Params().Desc, "Sag FSE2D T2W FC");
		break;
	case 17:
		CProtocolExample::PelvSESag(&Params(),	Scans()[0]);
		strcpy(Params().Desc, "Sag SE2D T1W");
		break;
	case 18:
		CProtocolExample::PelvSTIRSag(&Params(), Scans()[0]);
		strcpy(Params().Desc, "Sag STIR");
		break;
	case 19:
		CProtocolExample::PelvFSECor(&Params(), Scans()[0]);
		strcpy(Params().Desc, "Cor FSE2D T2W FC");
		break;
	case 20:
		CProtocolExample::PelvSECor(&Params(), Scans()[0]);
		strcpy(Params().Desc, "Cor SE2D T1W");
		break;
	case 21:
		CProtocolExample::PelvSTIRCor(&Params(), Scans()[0]);
		strcpy(Params().Desc, "Cor STIR");
		break;
	case 22:
		CProtocolExample::PelvFSEAx(&Params(),	Scans()[0]);
		Params().PresaturationRegions[sdPRead].m_bUse = true;
		strcpy(Params().Desc, "Axial FSE2D T2W SAT1");
		break;
	case 23:
		CProtocolExample::PelvSEAx(&Params(), Scans()[0]);
		Params().PresaturationRegions[sdPRead].m_bUse = true;
		break;
// >> Pelvis

// << knee
	case 24:
		CProtocolExample::KneeSESag(&Params(), Scans()[0]);
		Params().PhasePoints = 128;
		Params().NumAvg = 1;
		Params().ResolutionZ = 3;
		strcpy(Params().Desc, "Sag SE2D Localiztion");
		break;
	case 25:
		CProtocolExample::KneeSEAx(&Params(), Scans()[0]);
		Params().PhasePoints = 128;
		Params().NumAvg = 1;
		Params().ResolutionZ = 3;
		strcpy(Params().Desc, "Axial SE2D Localiztion");
		break;
	case 26:
		CProtocolExample::KneeSECor(&Params(), Scans()[0]);
		Params().PhasePoints = 128;
		Params().NumAvg = 1;
		Params().ResolutionZ = 3;
		strcpy(Params().Desc, "Cor SE2D Localiztion");
		break;
	case 27:
		CProtocolExample::KneeFSESag(&Params(),Scans()[0]);
		strcpy(Params().Desc, "FSE2D T2W");
		break;
	case 28:
		CProtocolExample::KneeSEAx(&Params(),Scans()[0]);
		strcpy(Params().Desc, "SE2D T1W");
		break;
	case 29:
		CProtocolExample::KneeSTIRSag(&Params(),Scans()[0]);
		strcpy(Params().Desc, "STIR");
		break;
// >> knee
			
// << Body
	case 31:
		CProtocolExample::PelvSESag(&Params(), Scans()[0]);
		Params().PhasePoints = 128;
		Params().ResolutionZ = 3;
		Params().NumAvg = 1;
		strcpy(Params().Desc, "Sag SE2D Localization");
		break;
	case 32:
		CProtocolExample::PelvSECor(&Params(), Scans()[0]);
		Params().ResolutionZ = 3;
		Params().NumAvg = 1;
		Params().PhasePoints = 128;
		strcpy(Params().Desc, "Cor SE2D Localization");
		break;
	case 33:
		CProtocolExample::PelvFSEAx(&Params(),	Scans()[0]);
		strcpy(Params().Desc, "Axial FSE2D T2W");
		break;
	case 34:
		CProtocolExample::PelvSEAx(&Params(), Scans()[0]);
		strcpy(Params().Desc, "Axial SE2D T1W");
		break;
	case 35:
		CProtocolExample::PelvSTIRAx(&Params(), Scans()[0]);
		strcpy(Params().Desc, "Axial STIR");
		break;
/*	case 36:
		break;
	case 37:
		break;
	case 38:
		break; */
	case 39:
		CProtocolExample::PelvFSEAx(&Params(),	Scans()[0]);
		Params().PresaturationRegions[sdPRead].m_bUse = true;
		strcpy(Params().Desc, "Sag FSE2D T2W FC");
		break;
	case 40:
		CProtocolExample::PelvSEAx(&Params(), Scans()[0]);
		Params().PresaturationRegions[sdPRead].m_bUse = true;
		strcpy(Params().Desc, "Sag SE2D T1W");
		break;
// >> Body

// << Utilities  LZ 2004-08-25
	/*
	case 41:
		CProtocolExample::TESTSeriesSEAx(&Params(), Scans()[0]);
		strcpy(Params().Desc, "TEST Axial SE2D");
		break;
	case 42:
		CProtocolExample::TESTSeiresFSEAx(&Params(), Scans()[0]);
		strcpy(Params().Desc, "TEST Axial FSE 2D");
		break;
	case 43:
		CProtocolExample::TESTHeadSPRGCor(&Params(), Scans()[0]);
		strcpy(Params().Desc, "TEST Axial SPRG 3D");
		break;
	*/
	case 44:	//LZ 2004-08-25
		CProtocolExample::Shimming(&Params(), Scans()[0]);
		strcpy(Params().Desc, "Shimming");
		break;
// >> Unitilties

// << Cervical spine
	case 51: // "Axial SE2D Localization"
		CProtocolExample::SeriesSEAx(&Params(), Scans()[0]);
		Params().PhasePoints = 128;
		Params().ResolutionZ = 3;
		Params().NumAvg = 1;
		Params().TXCoil = Params().RcvCoil = ctSurfaceNeck; // duplex coil
		// Params().RFTxLev = 2.7f;
		Scans()[0]->DigRCGain = 1.26f;
		strcpy(Params().Desc, "Axial SE2D Localization");
		break;
	case 52: // "Sagittal FSE 2D T2W"
		CProtocolExample::SeriesFSESag(&Params(), Scans()[0]);
		Params().TXCoil = Params().RcvCoil = ctSurfaceNeck; // duplex coil
		Scans()[0]->DigRCGain = 1.26f;
		strcpy(Params().Desc, "Sagittal FSE 2D T2W");
		break;
	case 53: // "Axial FSE 2D T2W"
		CProtocolExample::SeriesFSEAx(&Params(), Scans()[0]);
		Params().TXCoil = Params().RcvCoil = ctSurfaceNeck; // duplex coil
		Scans()[0]->DigRCGain = 1.26f;
		strcpy(Params().Desc, "Axial FSE 2D T2W");
		break;
	case 54: // "Sagittal FLAIR"
		CProtocolExample::SeriesFLAIRSag(&Params(), Scans()[0]);
		Params().TXCoil = Params().RcvCoil = ctSurfaceNeck; // duplex coil
		Scans()[0]->DigRCGain = 1.26f;
		strcpy(Params().Desc, "Sagittal FLAIR");
		break;
	case 55: // "Axial FLAIR"
		CProtocolExample::SeriesFLAIRAx(&Params(), Scans()[0]);
		Params().TXCoil = Params().RcvCoil = ctSurfaceNeck; // duplex coil
		Scans()[0]->DigRCGain = 1.26f;
		strcpy(Params().Desc, "Axial FLAIR");
		break;
	case 56: // "Sagittal SE2D T1W"
		CProtocolExample::SeriesSEAx(&Params(), Scans()[0]);
		Params().TXCoil = Params().RcvCoil = ctSurfaceNeck; // duplex coil
		Scans()[0]->DigRCGain = 1.26f;
		strcpy(Params().Desc, "Sagittal SE2D T1W");
		break;
	case 57: // "Axial SE2D T1W"
		CProtocolExample::SeriesSESag(&Params(), Scans()[0]);
		Params().TXCoil = Params().RcvCoil = ctSurfaceNeck; // duplex coil
		Scans()[0]->DigRCGain = 1.26f;
		strcpy(Params().Desc, "Axial SE2D T1W");
		break;
// >> Cervical spine

// << Lumber spine
	case 61: // "Axial SE2D Localization"
		CProtocolExample::PelvSEAx(&Params(), Scans()[0]);
		Params().PhasePoints = 128;
		Params().ResolutionZ = 3;
		Params().NumAvg = 1;
		// Params().TXCoil = Params().RcvCoil = ctBodyQDL; // duplex coil
		strcpy(Params().Desc, "Axial SE2D Localization");
		break;
	case 62: // "Sagittal FSE2D T2W"
		CProtocolExample::PelvFSESag(&Params(),	Scans()[0]);
		strcpy(Params().Desc, "Sagittal FSE2D T2W");
		break;
	case 63: // "Axial FSE2D T2W"
		CProtocolExample::PelvFSEAx(&Params(),	Scans()[0]);
		strcpy(Params().Desc, "Axial FSE2D T2W");
		break;
	case 64: // "Sagittal SE2D T1W"
		CProtocolExample::PelvSESag(&Params(), Scans()[0]);
		strcpy(Params().Desc, "Sagittal SE2D T1W");
		break;
	case 65: // "Axial SE2D T1W"
		CProtocolExample::PelvSEAx(&Params(), Scans()[0]);
		strcpy(Params().Desc, "Axial SE2D T1W");
		break;
// >> Lumber spine

	default:
//		ASSERT(0);
		return FALSE;
	}

	return TRUE;
}

void CSeriesProtocol::LoadProtocolFromFileByBinary(int nIndexOfProtocolGroup, int nIndexOfProtocol)
{
	memcpy( &m_SeriesParams, 
		&CSystemSettingInterface::GetHandle().m_oProtocolFamily.vProtocolGroups[nIndexOfProtocolGroup].vProtocols[nIndexOfProtocol].oParams.oSeriesField, 
		sizeof(SeriesField) );

	int nScans = 1;
	for( int i=0;i<nScans;i++)
	{
		ScanField* pScanParams = new ScanField;
		memcpy( pScanParams, 
			&CSystemSettingInterface::GetHandle().m_oProtocolFamily.vProtocolGroups[nIndexOfProtocolGroup].vProtocols[nIndexOfProtocol].oParams.oScanField, 
			sizeof(ScanField) );
		
		m_Scans.push_back(pScanParams);
	}
}
