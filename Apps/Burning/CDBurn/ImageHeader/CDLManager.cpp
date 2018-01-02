// CDLManager.cpp
//
#include "stdafx.h"
#include "CDLManager.h"
#include <cassert>
#include "../ImageHeader/Series.h"
#include "../ImageHeader/DirectionCalculator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CCDLManager CCDLManager::s_Instance;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCDLManager::CCDLManager()
{

}

CCDLManager::~CCDLManager()
{

}
EPresaturationDirection CCDLManager::CalculatePresaturationDirection(const CSeries* pSeries) const
{
	bool bUsed[6];
	EPresaturationDirection nPresatDir[6];
	
	memset( bUsed, 0, sizeof(bool)*6 );
	memset( nPresatDir, 0/*pdNone*/, sizeof(EPresaturationDirection)*6 );
	
	CPresaturationRegion PresatRegion[6];
	memcpy( PresatRegion, pSeries->SeriesParams().PresaturationRegions, sizeof(CPresaturationRegion)*6 );
	
	// 作一下转换
	if ( PresatRegion[hbdSuperior].m_bUse )
	{
		bUsed[0] = true;
	}
	nPresatDir[0] = CDirectionCalculator::GetHandle().GetPresatDirection( pSeries, hbdSuperior );
	
	if ( PresatRegion[hbdInferior].m_bUse )
	{
		bUsed[1] = true;
	}
	nPresatDir[1] = CDirectionCalculator::GetHandle().GetPresatDirection( pSeries, hbdInferior );
	
	if ( PresatRegion[hbdAnterior].m_bUse )
	{
		bUsed[2] = true;
	}
	nPresatDir[2] = CDirectionCalculator::GetHandle().GetPresatDirection( pSeries, hbdAnterior );
	
	if ( PresatRegion[hbdPosterior].m_bUse )
	{
		bUsed[3] = true;
	}
	nPresatDir[3] = CDirectionCalculator::GetHandle().GetPresatDirection( pSeries, hbdPosterior );
	
	if ( PresatRegion[hbdLeft].m_bUse )
	{
		bUsed[4] = true;
	}
	nPresatDir[4] = CDirectionCalculator::GetHandle().GetPresatDirection( pSeries, hbdLeft );
	
	if ( PresatRegion[hbdRight].m_bUse )
	{
		bUsed[5] = true;
	}
	nPresatDir[5] = CDirectionCalculator::GetHandle().GetPresatDirection( pSeries, hbdRight );
	
	
	// 获取预饱和方向(类型)
	EPresaturationDirection pdType = pdNone;
	
	for ( int i=0; i< 6; i++ )
	{
		if ( nPresatDir[i] == pdRead && bUsed[i] )
		{
			pdType = pdRead;
		}
		else if ( nPresatDir[i] == pdPhase && bUsed[i] )
		{
			pdType = pdPhase;
		}
		else if ( nPresatDir[i] == pdSlice && bUsed[i] )
		{
			pdType = pdSlice;
		}
	}	
	
	return pdType;
}

std::string CCDLManager::SelectSeCDL(const CSeries* pSeries) const
{
	bool bPomp = 
		(pSeries->SeriesParams().SequenceOptions & cnstPOMP) != 0;
	std::string strCDL;
	EPresaturationDirection presatDirection = CalculatePresaturationDirection(pSeries);
	
	strCDL = "SE2D.cdl";
	switch(presatDirection)
	{
	case pdNone:
		break;
	case pdRead:
		strCDL = "SE2DSATX.cdl";
		break;
	case pdPhase:
		strCDL = "SE2DSATY.cdl";
		break;
	case pdSlice:
		strCDL = "SE2DSATZ.cdl";
		break;
	case pdAll:
	default:
		strCDL = "SE2DSATX.cdl";
		break;
	}

	// metal artifacts removal?
	if(pSeries->SeriesParams().SequenceOptions & cnstMetalArtifactsRemoval)
		strCDL = "SE2DMAR.cdl";
	
	// gating
	if(pSeries->SeriesParams().SequenceOptions & cnstRespiratoryTriggering)
		strCDL = "SE2D_RG.cdl";
	else if(pSeries->SeriesParams().SequenceOptions & cnstECGGating)
		strCDL = "SE2D_CG.cdl";

	return strCDL;

}
	
std::string CCDLManager::SelectFseCDL(const CSeries* pSeries) const
{
	std::string strCDL;
	EPresaturationDirection presatDirection;
	presatDirection = CalculatePresaturationDirection(pSeries);
	int SeqType = pSeries->GetSeqenceType();
	/** [yhwang 2008.3.28] 修改cdl选择 **/
	switch(SeqType)
	{
	case cnstFSE:
		switch(presatDirection)
		{
		case pdNone:
			strCDL = "FSE2D.cdl";
			break;
		case pdRead:
		case pdPhase:
		case pdSlice:
			strCDL = "FSE2DSAT.cdl";
			break;
		default:
			strCDL = "FSE2D.cdl";
			break;
		}
		break;
	case cnstSTIR:
		strCDL = "IRFSE2D.cdl";
		break;
	case cnstFLAIR:
		strCDL = "FLAIR2D.cdl";
		break;
	default:
		strCDL = "FSE2D.cdl";
		break;
	}
	/** [yhwang 2008.3.28] **/
			
	return strCDL;
}
/*!
	\remarks This function should be modified to get the result from a database
	table in the future version, so that user pulse sequences can be added
	conveniently.
*/
std::string CCDLManager::GetCDLName(const CSeries* pSeries) const
{
	int nSequence = 
		pSeries->SeriesParams().SequenceOptions & cnstBasicSequenceTypeMask;

	std::string strCDL;
	switch (nSequence)
	{
	case cnstGRE:
		strCDL = "GE2D.cdl";
		break;
	case cnstIRSE:
		strCDL = "IRSE2D.cdl";
		break;
	case cnstSE:
		strCDL = SelectSeCDL(pSeries);//"SE2D.cdl";
		break;
	case cnstFLAIR:
	case cnstSTIR:
	case cnstFSE:
		strCDL = SelectFseCDL(pSeries);
		break;
	case cnstTOF2D:
		strCDL = "TOF2D.CDL";
		break;
	case cnstTOF3D:
		strCDL = "TOF3D.cdl";
		break;
	case cnstSSFSE:
		strCDL = "SSFSE2D.CDL";
		break;
	case cnstSEDWI:
		strCDL = "SEDWI.CDL";
		break;
	case cnstSPGR:
		strCDL = "SPGR3D.cdl";
		break;
	case cnstSPGR2D:
		strCDL = "SPGR2D.cdl";
		break;
	case cnstSPGR2DBH:
		strCDL = "SPGR2DBH.cdl";
		break;
	//Added by Tom, --2008.07.10
	/**[xd 2008.12.06]增加spgr预饱和 Begin**/
	case cnstSPGR2DSAT:
		strCDL = "SPGR2DSAT.cdl";
	break;
	/**[xd 2008.12.06]增加spgr预饱和 End**/
	case cnstLSDI:
	case cnstLSDI1B:
		strCDL = "LSDI.cdl";
		break;
	case cnstDeGhost:
		strCDL = "SE2DGH.cdl";
		break;		
	case cnstWFI:
		strCDL = "SE2D_wfi.cdl";
		break;		
	/**[xd 2008.03.10]增加SSFP Begin**/
	case cnstSSFP:
		strCDL = "truefisp2d.cdl";
		break;
	case cnstSSFP3D:
		strCDL = "truefisp3d.cdl";
		break;
	/**[xd 2008.03.10]增加SSFP End**/
	/*case cnstEPI:
		strCDL = "SEEPIDB3.cdl";
		break;*/
	case cnstShimming:
		strCDL = "SHIM2D.cdl";
		break;
	case cnstSSFSE3D:
		strCDL = "SSFSE3D.cdl";
		break;
	case cnstEPDWI:
	case cnstEPDWI1B:
		strCDL = "EPDWI.cdl";
		break;
	default:
		ASSERT(0);
	}

	return strCDL;
}
