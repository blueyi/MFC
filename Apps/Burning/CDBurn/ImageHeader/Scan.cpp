// Scan.cpp: implementation of the CScan class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <cassert>

#include "../BIGlobals/ConfigManager.h"
#include "../cdlParser/cdl.h"
#include "../MRIDatabase/DBInterface.h"
#include "DirectionCalculator.h"


#include "Series.h"
#include "Image.h"
#include "bi_constants.h"
#include "Scan.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// A complete scan differs from a non-complete one in that a complete scan doesn't need a
// CDL to evaluate its parameters.
CScan::CScan(CSeries* pSeries, bool bComplete, bool bCopy)
{
	// Should I say a scan cannot be initialized without series?
	assert(pSeries); // the hosting series, cannot be NULL.

	m_pSeries = pSeries;
	m_pEvaluator = NULL;

    // initialize scan field paramters
    memset(reinterpret_cast<void*>(&ScanParams()), 0x00, sizeof (ScanField));

    // create a new cdl evaluator for the scan.
    if (bComplete == false)
    {
        m_ScanState = ssSetup;
	    try
	    {
		    m_pEvaluator = new CCDL;
	    }
	    catch(CMemoryException e)
	    {
		    e.ReportError();
		    return;
	    }
    
		CString sCdlFile = CConfigManager::GetHandle().GetCDLDirectory().c_str();
		sCdlFile += m_pSeries->GetCDLFileName().c_str();
        /*VERIFY*/( m_pEvaluator->LoadCDLFile(sCdlFile.GetBuffer(255)) );

		if ( !bCopy )
		{
			int nSequence = SeriesParams().SequenceOptions & cnstBasicSequenceTypeMask;
			if(nSequence == cnstLSDI || nSequence == cnstEPDWI)
			{
				/*VERIFY*/(m_pEvaluator->SetParamValue("ui_MethodOfDI", 1));
				/*VERIFY*/(m_pEvaluator->SetParamValue("ui_MaxBFactor", 1000));
				/*VERIFY*/(m_pEvaluator->SetParamValue("ui_NumofB", 2));
			}
			else if(nSequence==cnstLSDI1B || nSequence == cnstEPDWI1B)
			{
				/*VERIFY*/(m_pEvaluator->SetParamValue("ui_MethodOfDI", 1));
				/*VERIFY*/(m_pEvaluator->SetParamValue("ui_MaxBFactor", 1000));
				/*VERIFY*/(m_pEvaluator->SetParamValue("ui_NumofB", 1));
			}
			if ( nSequence == cnstLSDI || nSequence == cnstLSDI1B ||
				nSequence == cnstEPDWI || nSequence == cnstEPDWI1B)
			{
				/*VERIFY*/(m_pEvaluator->GetParamValue("ui_MethodOfDI", SeriesParams().nMethodOfDI));
				/*VERIFY*/(m_pEvaluator->GetParamValue("ui_MaxBFactor", SeriesParams().nMaxBFactor));
				/*VERIFY*/(m_pEvaluator->GetParamValue("ui_NumofB", SeriesParams().nNumOfB));
			}
		}		
	}
    else
    {
        m_ScanState = ssComplete;
    }

	m_ScanParams.Id = pSeries->Scans().size();
    // push the scan into the scan container in the series.
    pSeries->Scans().push_back(this);

	m_dAPOffset = 0.0;
	m_dLROffset = 0.0;
	m_dSIOffset = 0.0;
	/** [yhwang 2007.12.24] 使用hanning window取消Fermi filter，改变hanning window的ratio至0.2 **/
	/** [yhwang 2007.12.24] 取消hanning window恢复Fermi filter **/
	/* 解决SNR降低，Gibbs ring严重的问题 */
	/** [xd 2007.11.30] XABW/CX-31-11-0030] 修改SPGRBH图像上有一圈一圈伪影的问题 **/
	m_HanWndInfo.m_bDoX = true;
	m_HanWndInfo.m_bDoY = true;
	/** [xd 2007.11.30] **/
	/** [yhwang 2007.12.24] **/
	m_HanWndInfo.m_fRatioX = 0.2f;
	m_HanWndInfo.m_fRatioY = 0.2f;
	/** [yhwang 2007.12.24] **/
	m_FermiFilterInfo.m_bEnable = true;
	m_FermiFilterInfo.m_fRatioY=0.05f;
   //Added by Sun Shang for database function at 2002/09/19
	GetSavedRecordNum()=0;
	//End.

	m_bIsMultiSlabScanning = false;
}


CScan::~CScan()
{
	delete m_pEvaluator;
}

/*
	\param bCDLToParam If \a true, updates the scan field parameters with the
	value stored in the cdl, if \a false, updates the cdl values with the scan
	field parameters.

	\bug To be implemented.
*/
/*
	\param bCDLToParam If \a true, updates the scan field parameters with the
	value stored in the cdl, if \a false, updates the cdl values with the scan
	field parameters.
*/
bool CScan::UpdateParams(bool bCDLToParam)
{
	UpdateCDLParams(bCDLToParam);
	UpdateCDLParams(false);
	return UpdateCDLParams(bCDLToParam);
}

bool CScan::UpdateCDLParams(bool bCDLToParam)
{
    if (m_pEvaluator == NULL) return false;
	CSeries* pSeries = GetSeries(); 

	//bHalfKSpace, BOOL bInterleave, BOOL bSingleSliceMethod. enum EPhEncOrder
	SeriesField sf = SeriesParams();
    if (bCDLToParam)
    {
    	/** [GMWU 071016] 删除计算TE/TR最小值代码 **/
		/*********************************************/
		
		m_pEvaluator->RunScript("calculate_all"); 
        // ==== Patient parameters =====
        // No Patient parameters need to be read from CDL

        // ==== Study parameters =======
        // Currently, no study parameters are used in the evaluation.
        
        // ==== Series parameters ======
        // Currently, no series parameters are used in the evaluation.

        // ==== Scan parameters ========
        // The following parameters may need to be evaluated.
        /*VERIFY*/(m_pEvaluator->GetParamValue("scan_Plane", SeriesParams().Plane));
	    /*VERIFY*/(m_pEvaluator->GetParamValue("scan_FovX", SeriesParams().FovX));
		/*VERIFY*/(m_pEvaluator->GetParamValue("scan_FovY", SeriesParams().FovY));
		/*VERIFY*/(m_pEvaluator->GetParamValue("scan_FovZ", SeriesParams().FovZ));

        /*VERIFY*/(m_pEvaluator->GetParamValue("scan_KSpaceRatio", SeriesParams().HalfKSpaceRatio));
	    /*VERIFY*/(m_pEvaluator->GetParamValue("scan_ReadPoints", SeriesParams().ReadPoints));
		/*VERIFY*/(m_pEvaluator->GetParamValue("ui_PhasePoints", SeriesParams().PhasePoints));

		/*VERIFY*/( m_pEvaluator->GetParamValue("scan_ResolutionZ", SeriesParams().ResolutionZ) );

		/*VERIFY*/(m_pEvaluator->GetParamValue("scan_FreqDirX", m_ScanParams.FreqDirX));
		/*VERIFY*/(m_pEvaluator->GetParamValue("scan_FreqDirY", m_ScanParams.FreqDirY));
		/*VERIFY*/(m_pEvaluator->GetParamValue("scan_FreqDirZ", m_ScanParams.FreqDirZ));
		/*VERIFY*/(m_pEvaluator->GetParamValue("scan_PhaseDirX", m_ScanParams.PhaseDirX));
		/*VERIFY*/(m_pEvaluator->GetParamValue("scan_PhaseDirY", m_ScanParams.PhaseDirY));
		/*VERIFY*/(m_pEvaluator->GetParamValue("scan_PhaseDirZ", m_ScanParams.PhaseDirZ));
		/*VERIFY*/(m_pEvaluator->GetParamValue("scan_SliceDirX", m_ScanParams.SliceDirX));
		/*VERIFY*/(m_pEvaluator->GetParamValue("scan_SliceDirY", m_ScanParams.SliceDirY));
		/*VERIFY*/(m_pEvaluator->GetParamValue("scan_SliceDirZ", m_ScanParams.SliceDirZ));
		/*VERIFY*/(m_pEvaluator->GetParamValue("scan_ReadOffset", m_ScanParams.ReadOffset));
		/*VERIFY*/(m_pEvaluator->GetParamValue("scan_PhaseOffset", m_ScanParams.PhaseOffset));
		/*VERIFY*/(m_pEvaluator->GetParamValue("scan_SliceOffset", m_ScanParams.SliceOffset));
        
        bool bFlag;

		/*VERIFY*/(m_pEvaluator->GetParamValue("scan_bSingleSliceMethod", bFlag));
        if (bFlag)
            SeriesParams().OtherOptions |= cnstSingleSliceMethod;
        else 
            SeriesParams().OtherOptions &= ~cnstSingleSliceMethod;
		

        /*VERIFY*/(m_pEvaluator->GetParamValue("scan_bInterleave", bFlag));
        if (bFlag)
            SeriesParams().OtherOptions |= cnstSliceInterleave;
        else
            SeriesParams().OtherOptions &= ~cnstSliceInterleave;
        
		
        /*VERIFY*/(m_pEvaluator->GetParamValue("scan_SliceThickness", 
            SeriesParams().SliceThickness));
		/** [zhlxu 2007.9.30] 为了自动调整扫描层的顺序，避免从CDL中取出错误的Gap值,而删除代码 **/
		// 被删除的代码 ... ...
		/** [zhlxu 2007.9.30] **/
			
		/** [GMWU 11/15/2007] 修改其他参数后，更新TE及TR **/
		if (pSeries->m_bAutoMinTE)
			(m_pEvaluator->GetParamValue("out_TEMin", SeriesParams().EchoTime));
		else
			(m_pEvaluator->GetParamValue("scan_TE", SeriesParams().EchoTime));

		if (pSeries->m_bAutoMinTR) {
			m_pEvaluator->GetParamValue("out_TRMin", SeriesParams().RepTime);
		}
		else
			m_pEvaluator->GetParamValue("scan_TR", SeriesParams().RepTime);
		/** [GMWU 11/15/2007] **/

		/** [GMWU 11/15/2007] 保证SE回波序列TR为20倍数关系 **/
		int nSequence = SeriesParams().SequenceOptions & cnstBasicSequenceTypeMask;
		if( nSequence == cnstSE || nSequence == cnstFSE 
			|| nSequence == cnstFLAIR || nSequence == cnstSTIR ) 
		{
			/** [zhlxu 2008.5.5] [] 添加TR限制值的文件配置功能 **/
			float fTRLimitedValue = CConfigManager::GetHandle().m_fTRLimitedValue;	

			CString sTemp;
			sTemp.Format( "%20.5f", ((SeriesParams().RepTime/1000.0)*fTRLimitedValue) / 1000.0 );
			long iMultiple = ceil( atof(sTemp) );

			int nTempTR = ( iMultiple * 1000.0 / fTRLimitedValue) * 1000;
			
			if ( (nTempTR - SeriesParams().RepTime) != 0 )
			{
				SeriesParams().RepTime = nTempTR;
			}
			/** [zhlxu 2008.5.5] **/
		}
		/** [GMWU 11/15/2007] **/
		/*VERIFY*/(m_pEvaluator->GetParamValue("scan_TE2", SeriesParams().Echo2Time));
	    /*VERIFY*/(m_pEvaluator->GetParamValue("scan_NumEchoImages", 
            SeriesParams().NumEchoImages));
		/*VERIFY*/(m_pEvaluator->GetParamValue("scan_AcqBandwidth", 
            SeriesParams().AcqBandwidth));
		/*VERIFY*/(m_pEvaluator->GetParamValue("scan_AcqBandwidth2", 
            SeriesParams().AcqBandwidth2));
	    /*VERIFY*/(m_pEvaluator->GetParamValue("scan_EchoTrainLength", 
            SeriesParams().EchoTrainLength));
	    /*VERIFY*/(m_pEvaluator->GetParamValue("scan_FlipAngle", 
            SeriesParams().FlipAngle));
	    //VERIFY(m_pEvaluator->GetParamValue("TG", 
        //    m_ScanParams.RFTxLev));
	    /*VERIFY*/(m_pEvaluator->GetParamValue("RG", m_ScanParams.DigRCGain));
		/*VERIFY*/(m_pEvaluator->GetParamValue("O1", m_ScanParams.O1));
	    /*VERIFY*/(m_pEvaluator->GetParamValue("scan_NumAvg", SeriesParams().NumAvg));
        /*VERIFY*/(m_pEvaluator->GetParamValue("scan_PhEncOrder", 
            SeriesParams().PhEncOrder));
		/*VERIFY*/(m_pEvaluator->GetParamValue("scan_TI", SeriesParams().TI));

		//
		/*VERIFY*/(m_pEvaluator->GetParamValue("scan_SlabOrder", SeriesParams().SlabOrder));
		/*VERIFY*/(m_pEvaluator->GetParamValue("scan_NumSlabs", SeriesParams().NumSlab));
		/*VERIFY*/(m_pEvaluator->GetParamValue("scan_SlabOverlap", SeriesParams().SlabOverlap));
		/*VERIFY*/(m_pEvaluator->GetParamValue("scan_PointsPerSlab", SeriesParams().NumPntsPerSlab));

		bool bHalfEcho;
		/*VERIFY*/(m_pEvaluator->GetParamValue("scan_bHalfEcho", bHalfEcho));

		if (bHalfEcho)
			SeriesParams().OtherOptions |= cnstHalfEcho;
		else
			SeriesParams().OtherOptions &= ~cnstHalfEcho;

		// 更新采样时间估计  Rodger, 9:08 2004-10-26
		int nACQSeconds = 0;
		/*VERIFY*/(m_pEvaluator->GetParamValue("out_ACQSeconds", nACQSeconds));
		m_ScanParams.ACQ = nACQSeconds;
		
		//20070718.liuxuan.for RelSNR
		float fDefRelSNR = 0;
		/*VERIFY*/(m_pEvaluator->GetParamValue("DefRelativeSNR", fDefRelSNR));
		m_ScanParams.DefRelSNR = fDefRelSNR;
		//VERIFY(m_pEvaluator->SetParamValue("DefRelativeSNR", m_ScanParams.DefRelSNR));
		float fRelativeSNR = 0;
		/*VERIFY*/(m_pEvaluator->GetParamValue("out_relativeSNR", fRelativeSNR));
		m_ScanParams.RelSNR = fRelativeSNR;

		/*VERIFY*/(m_pEvaluator->GetParamValue("scan_EchoSpacing", SeriesParams().EchoSpacing));
		float dr = SeriesParams().EchoSpacing;

		if ( !(m_pEvaluator->GetParamValue("bBreathHold", SeriesParams().BreathHold.bBreathHold)) )
		{
			SeriesParams().BreathHold.bBreathHold = false;
		}

		bool t = (SeriesParams().BreathHold.bBreathHold>0?true:false) ; //Modified by Tom, --2008.07.10

		// RG of multi-channel - 20060407 by GMW
		for ( int i=0; i< pSeries->m_oCoilSpecs.nMaxNumOfChannels; i++ )
		{
			if ( pSeries->m_oCoilSpecs.bMcEnabled[i] )
			{
				char sRGOfOneChannel[10];
				if ( i==0 )
				{
					sprintf( sRGOfOneChannel, "RG" );
				}
				else
				{
					sprintf( sRGOfOneChannel, "RG%d", i );
				}
				/*VERIFY*/(m_pEvaluator->GetParamValue(sRGOfOneChannel, m_ScanParams.fMcRxLevel[i]) );
			}
		}

		if ( nSequence == cnstLSDI || nSequence == cnstLSDI1B ||
			nSequence == cnstEPDWI || nSequence == cnstEPDWI1B)
		{
			/*VERIFY*/(m_pEvaluator->GetParamValue("ui_MethodOfDI", SeriesParams().nMethodOfDI));
			/*VERIFY*/(m_pEvaluator->GetParamValue("ui_MaxBFactor", SeriesParams().nMaxBFactor));
			/*VERIFY*/(m_pEvaluator->GetParamValue("ui_NumofB", SeriesParams().nNumOfB));
		}

		int NumSlice;
		/*VERIFY*/(m_pEvaluator->GetParamValue("C1",NumSlice));
		
		bool bMultiPass=true;
		if( !m_pEvaluator->GetParamValue("SYS_SUPPORT_MULTI_PASS_SCANNING", bMultiPass) )
			bMultiPass=false;
		if(bMultiPass)
		{
			/*VERIFY*/(m_pEvaluator->GetParamValue("NumOfPass", SeriesParams().nNumOfPass));
			/*VERIFY*/(m_pEvaluator->GetParamValue("SlicePerPass", SeriesParams().nSlicePerPass));
		}
		else
		{
			SeriesParams().nNumOfPass = 1;
			SeriesParams().nSlicePerPass = NumSlice;
		}

		/** [yhwang 2008.3.28] 从CDL获得FC的标识 **/
		m_pEvaluator->GetParamValue("scan_FlowCompensation", SeriesParams().FlowCompensation);
		/** [yhwang 2008.3.28] **/
    }
    else 
    // update cdl according to the scan field, we can assume the parameters in
    // the scan field are all valid.
    {
        // ==== system parameters =====
        /** [GMWU 071016] 删除计算TE/TR最小值代码 **/

		/*********************************************/
		
		/*VERIFY*/(m_pEvaluator->SetParamValue("sys_Dead1", 7.0));
		float sw = SeriesParams().AcqBandwidth;
		float dead2, deadact;
		// add for over sampling, 2007-04-20
		bool bOverSampling = (SeriesParams().OtherOptions & cnstOverSampling) != 0;
		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_bOverSampling", bOverSampling));
		
		//set Dead2 and DeadAct to cdl for over sampling
		if(bOverSampling)
		{
			dead2 = CConfigManager::GetHandle().GetBWDead2(2*(SeriesParams().AcqBandwidth)).m_dDead2;
			deadact = CConfigManager::GetHandle().GetBWDead2(2*(SeriesParams().AcqBandwidth)).m_dDeadAct;
		}
		else
		{
			dead2 = CConfigManager::GetHandle().GetBWDead2(SeriesParams().AcqBandwidth).m_dDead2;
			deadact = CConfigManager::GetHandle().GetBWDead2(SeriesParams().AcqBandwidth).m_dDeadAct;
		}
		
		/*VERIFY*/(m_pEvaluator->SetParamValue("sys_Dead2", dead2));
		/*VERIFY*/(m_pEvaluator->SetParamValue("sys_DeadAct", deadact));
		/*VERIFY*/(m_pEvaluator->SetParamValue("sys_GxFF",
			CConfigManager::GetHandle().GetSystemParams().m_dGxFF));
		/*VERIFY*/(m_pEvaluator->SetParamValue("sys_GyFF",
			CConfigManager::GetHandle().GetSystemParams().m_dGyFF));
		/*VERIFY*/(m_pEvaluator->SetParamValue("sys_RFScale",
			CConfigManager::GetHandle().GetSystemParams().m_dRFScale));

		/*VERIFY*/(m_pEvaluator->SetParamValue("sys_GzFF",
		CConfigManager::GetHandle().GetSystemParams().m_dGzFF));
		/*VERIFY*/(m_pEvaluator->SetParamValue("sys_GxRampRate",
			CConfigManager::GetHandle().GetSystemParams().m_nGxRampRate));
		/*VERIFY*/(m_pEvaluator->SetParamValue("sys_GyRampRate",
			CConfigManager::GetHandle().GetSystemParams().m_nGyRampRate));
		/*VERIFY*/(m_pEvaluator->SetParamValue("sys_GzRampRate",
			CConfigManager::GetHandle().GetSystemParams().m_nGzRampRate));
		/*VERIFY*/(m_pEvaluator->SetParamValue("sys_RFGateTime",
			CConfigManager::GetHandle().GetSystemParams().m_nGateTime));

		
		/*VERIFY*/(m_pEvaluator->SetParamValue("sys_GxRFDelay",
			CConfigManager::GetHandle().GetSystemParams().m_nGxRFDelay));
		/*VERIFY*/(m_pEvaluator->SetParamValue("sys_GyRFDelay",
			CConfigManager::GetHandle().GetSystemParams().m_nGyRFDelay));
		/*VERIFY*/(m_pEvaluator->SetParamValue("sys_GzRFDelay",
			CConfigManager::GetHandle().GetSystemParams().m_nGzRFDelay));

		/*VERIFY*/(m_pEvaluator->SetParamValue("sys_FactorGx",
			CConfigManager::GetHandle().GetSystemParams().m_dFactorGx));
		/*VERIFY*/(m_pEvaluator->SetParamValue("sys_FactorGy",
			CConfigManager::GetHandle().GetSystemParams().m_dFactorGy));
		/*VERIFY*/(m_pEvaluator->SetParamValue("sys_FactorGz",
			CConfigManager::GetHandle().GetSystemParams().m_dFactorGz));
        		
        // ==== Scan parameters ========
        // The following parameters may need to be evaluated.
        /*VERIFY*/(m_pEvaluator->SetParamValue("scan_Plane", SeriesParams().Plane));
	    /*VERIFY*/(m_pEvaluator->SetParamValue("scan_FovX", SeriesParams().FovX));

		/*VERIFY*/(m_pEvaluator->SetParamValue("ui_FovRatio",(1.0*SeriesParams().FovY)/SeriesParams().FovX));
		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_FovZ", SeriesParams().FovZ));
		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_KSpaceRatio", 
            SeriesParams().HalfKSpaceRatio));
	    /*VERIFY*/(m_pEvaluator->SetParamValue("scan_ReadPoints", 
            SeriesParams().ReadPoints));
		
		bool bHalfEcho = (SeriesParams().OtherOptions & cnstHalfEcho) != 0;
		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_bHalfEcho", bHalfEcho));

		//bool bNoPhaseWrap = (SeriesParams().OtherOptions & cnstHalfEcho) != 0;
		bool bNoPhaseWrap = (SeriesParams().OtherOptions & cnstNoPhaseWrap) != 0;
		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_bNoPhaseWrap", bNoPhaseWrap));
		

//		int nPhasePoints;
//		nPhasePoints = (float)SeriesParams().PhasePoints / (float)(SeriesParams().FovY / (float)SeriesParams().FovX );
		/*VERIFY*/(m_pEvaluator->SetParamValue("ui_PhasePoints",SeriesParams().PhasePoints));
		
		if ( !m_pEvaluator->GetParamValue( "SYS_SUPPORT_MULTI_SLAB_SCANNING", m_bIsMultiSlabScanning) )
		{
			m_bIsMultiSlabScanning = false;
		}
		
		if ( m_bIsMultiSlabScanning )
		{
			// total slice number of all slabs
			if ( GetSeries()->m_ClusterSet.size() == 0 )
			{
				GetSeries()->m_nTotalSliceNumOfAllSlab = GetSeries()->SeriesParams().ResolutionZ;
			}
			else
			{
				GetSeries()->m_nTotalSliceNumOfAllSlab = GetSeries()->m_ClusterSet.size() * GetSeries()->SeriesParams().ResolutionZ;
			}
			/*VERIFY*/( m_pEvaluator->SetParamValue("scan_SliceNumOfAllSlab", GetSeries()->m_nTotalSliceNumOfAllSlab ) );
			int nn = GetSeries()->m_nTotalSliceNumOfAllSlab;
			/*VERIFY*/( m_pEvaluator->SetParamValue("scan_SliceNumPerSlab", SeriesParams().ResolutionZ ) );
		}

		/*VERIFY*/( m_pEvaluator->SetParamValue("scan_ResolutionZ", SeriesParams().ResolutionZ ) );
//		VERIFY( m_pEvaluator->RunScript("calculate_all") );  //by wwz 20051117  set scan_TE无效
		
		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_FreqDirX", 
			m_ScanParams.FreqDirX));
		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_FreqDirY", 
			m_ScanParams.FreqDirY));
		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_FreqDirZ", 
			m_ScanParams.FreqDirZ));

		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_PhaseDirX", 
			m_ScanParams.PhaseDirX));
		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_PhaseDirY", 
			m_ScanParams.PhaseDirY));
		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_PhaseDirZ", 
			m_ScanParams.PhaseDirZ));
		
		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_SliceDirX", 
			m_ScanParams.SliceDirX));
		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_SliceDirY", 
			m_ScanParams.SliceDirY));
		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_SliceDirZ", 
			m_ScanParams.SliceDirZ));
		
		/*VERIFY*/( m_pEvaluator->RunScript("calculate_all") );  //by wwz 20051117  set scan_TE 有效
		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_ReadOffset", 
			m_ScanParams.ReadOffset));
		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_PhaseOffset", 
			m_ScanParams.PhaseOffset));
		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_SliceOffset", 
			m_ScanParams.SliceOffset));
			
		//20070718.liuxuan.for RelSNR
		/*VERIFY*/(m_pEvaluator->SetParamValue("DefRelativeSNR", 
			m_ScanParams.DefRelSNR));

		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_bSingleSliceMethod", 
            SeriesParams().OtherOptions & cnstSingleSliceMethod));
		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_bInterleave", 
            SeriesParams().OtherOptions & cnstSliceInterleave));
	    
		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_SliceThickness", 
            SeriesParams().SliceThickness));

		// add for breath hold, 061124
		if (SeriesParams().BreathHold.m_NumOfSlicesPerBH == 0)
		{
			(m_pEvaluator->GetParamValue("bBreathHold",		
            SeriesParams().BreathHold.bBreathHold));
		}
		if (SeriesParams().BreathHold.m_NumOfSlicesPerBH == 0)
		{
			(m_pEvaluator->GetParamValue("SSSliceMax",		
            SeriesParams().BreathHold.m_NumOfSlicesPerBH));
		}
		m_pEvaluator->SetParamValue("SSSliceMax", SeriesParams().BreathHold.m_NumOfSlicesPerBH);

		m_pEvaluator->SetParamValue("bBreathHold", SeriesParams().BreathHold.bBreathHold);
				
        //Modified by Tom, --2008.07.10
		bool bRespiratoryGating = ((SeriesParams().SequenceOptions&cnstRespiratoryTriggering)>0?true:false);
		
		m_pEvaluator->SetParamValue("bRespiratoryGating",bRespiratoryGating);		

		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_SliceGap", 
            SeriesParams().SliceGap));

		/** [GMWU 11/15/2007] 修改其他参数后，更新TE及TR **/
		if (pSeries->m_bAutoMinTE)
			(m_pEvaluator->GetParamValue("out_TEMin", SeriesParams().EchoTime));

		if (pSeries->m_bAutoMinTR) 
			m_pEvaluator->GetParamValue("out_TRMin", SeriesParams().RepTime);
		/** [GMWU 11/15/2007] **/

		/** [GMWU 11/15/2007] 保证SE回波序列TR为20倍数关系 **/
		int nSequence = SeriesParams().SequenceOptions & cnstBasicSequenceTypeMask;
		if( nSequence == cnstSE || nSequence == cnstFSE 
			|| nSequence == cnstFLAIR || nSequence == cnstSTIR ) 
		{
			/** [zhlxu 2008.5.5] [] 添加TR限制值的文件配置功能 **/
			float fTRLimitedValue = CConfigManager::GetHandle().m_fTRLimitedValue;	

			// 解决取整的精度问题
			CString sTemp;
			sTemp.Format( "%20.5f", ((SeriesParams().RepTime/1000.0)*fTRLimitedValue) / 1000.0 );
			long iMultiple = ceil( atof(sTemp) );
			
			int nTempTR = ( iMultiple * 1000.0 / fTRLimitedValue) * 1000.0;

			if ( (nTempTR - SeriesParams().RepTime) != 0 )
			{
				SeriesParams().RepTime = nTempTR;
			}
			/** [zhlxu 2008.5.5] **/
		}
		/** [GMWU 11/15/2007] **/

		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_TE", 
            SeriesParams().EchoTime));
		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_TE2", 
            SeriesParams().Echo2Time));
		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_TR", SeriesParams().RepTime));
	    /*VERIFY*/(m_pEvaluator->SetParamValue("scan_NumEchoImages", 
			SeriesParams().NumEchoImages));
		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_AcqBandwidth", 
			SeriesParams().AcqBandwidth));
		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_AcqBandwidth2", 
			SeriesParams().AcqBandwidth2));
	    /*VERIFY*/(m_pEvaluator->SetParamValue("scan_EchoTrainLength", 
			SeriesParams().EchoTrainLength));
	    /*VERIFY*/(m_pEvaluator->SetParamValue("scan_FlipAngle", 
			SeriesParams().FlipAngle));
		
		// Range of TG is 6 - 20050701
		/*double dTg = CConfigManager::GetHandle().GetCoilSpec(
			static_cast<ECoilType>(SeriesParams().TXCoil)).m_dDefaultTG;
		if(3<(m_ScanParams.RFTxLev-dTg))
			m_ScanParams.RFTxLev = dTg+3;
		else if(3<(dTg-m_ScanParams.RFTxLev))
			m_ScanParams.RFTxLev = dTg-3;
		m_ScanParams.RFTxLev = dTg;
		VERIFY(m_pEvaluator->SetParamValue("TG", m_ScanParams.RFTxLev));*/
		/*VERIFY*/(m_pEvaluator->SetParamValue("TG", m_ScanParams.RFTxLev));

	    /*VERIFY*/(m_pEvaluator->SetParamValue("RG", 
			m_ScanParams.DigRCGain));
		/*VERIFY*/(m_pEvaluator->SetParamValue("O1", 
			m_ScanParams.O1));
	    /*VERIFY*/(m_pEvaluator->SetParamValue("scan_NumAvg", 
			SeriesParams().NumAvg));
        /*VERIFY*/(m_pEvaluator->SetParamValue("scan_PhEncOrder", 
			SeriesParams().PhEncOrder));
		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_TI", 
			SeriesParams().TI));
		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_EchoSpacing", 
			SeriesParams().EchoSpacing));

		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_SlabOrder", SeriesParams().SlabOrder));
		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_NumSlabs", SeriesParams().NumSlab));
		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_SlabOverlap", SeriesParams().SlabOverlap));
		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_PointsPerSlab", SeriesParams().NumPntsPerSlab));
		/*VERIFY*/(m_pEvaluator->SetParamValue("SF",SiteParams().SF));
		/*VERIFY*/(m_pEvaluator->SetParamValue("sys_CoilRFAMax", 
			CConfigManager::GetHandle().GetCoilSpec(static_cast<ECoilType>(SeriesParams().TXCoil)).m_dRFAMax));
		
		// 更新采样时间估计  Rodger, 9:08 2004-10-26
		/*VERIFY*/( m_pEvaluator->RunScript("calculate_all") );

		bool bMTC = (SeriesParams().SequenceOptions & cnstMTC)>0?true:false ;	//Modified by Tom, --2008.07.10	
		int nSeqType = SeriesParams().SequenceOptions & cnstBasicSequenceTypeMask;
		if (bMTC && nSeqType == cnstSE)
		{
			/*VERIFY*/(m_pEvaluator->SetParamValue("scan_MTC", true));	
		}

		//{wwz, FLAIR 只支持层数为1、2、3， 及3的倍数 或 4的倍数}
		if (/*(nSeqType== cnstFLAIR)||*/(nSeqType== cnstIRSE))
		{ /*
			int nMaxNumOfSlicePerStack,nDestC9;
			int nMunOfSlice = SeriesParams().ResolutionZ;
		
			VERIFY(m_pEvaluator->GetParamValue("D15", nMaxNumOfSlicePerStack));				
			nMaxNumOfSlicePerStack = max(1, nMaxNumOfSlicePerStack);

			float fTimeSlice, fTimeFree;
			m_pEvaluator->GetParamValue("TimeSlice", fTimeSlice);
			m_pEvaluator->GetParamValue("TimeFree", fTimeFree);

			nDestC9=nMaxNumOfSlicePerStack;
			
			if ( nMunOfSlice <= nMaxNumOfSlicePerStack )
			{
				nDestC9 = nMunOfSlice;
			}
			else if (nMaxNumOfSlicePerStack>0 && nMunOfSlice % nMaxNumOfSlicePerStack == 0 )
			{
				nDestC9 = nMaxNumOfSlicePerStack;
			}
			else if ( (nMaxNumOfSlicePerStack-1)>2 && nMunOfSlice % (nMaxNumOfSlicePerStack-1) == 0  )
			{
				nDestC9 =nMaxNumOfSlicePerStack-1;
			}
			else if ((nMaxNumOfSlicePerStack-2)>2 && nMunOfSlice % (nMaxNumOfSlicePerStack-2) == 0 )
			{
				nDestC9 =nMaxNumOfSlicePerStack-2;
			}
			else if ((nMaxNumOfSlicePerStack-3)>2 && nMunOfSlice % (nMaxNumOfSlicePerStack-3) == 0  )
			{
				nDestC9 =nMaxNumOfSlicePerStack-3;
			}
			else if ((nMaxNumOfSlicePerStack-4)>2 && nMunOfSlice % (nMaxNumOfSlicePerStack-4) == 0  )
			{
				nDestC9 =nMaxNumOfSlicePerStack-4;
			}
			else
			{
				nDestC9 = nMaxNumOfSlicePerStack;
			}
			VERIFY(m_pEvaluator->SetParamValue("C9", nDestC9 ));
			int nActualNumofSlice = (int)((float)nMunOfSlice/nDestC9+0.5)*nDestC9;
			nActualNumofSlice = min((20/nDestC9)*nDestC9, nActualNumofSlice);
			nActualNumofSlice = max(1, nActualNumofSlice);
			SeriesParams().ResolutionZ = nActualNumofSlice;
		20070718.liuxuan.commented for IRSE*/}

		// 更新采样时间估计  Rodger, 9:08 2004-10-26
		/*VERIFY*/( m_pEvaluator->RunScript("calculate_all") );
		float fEchoTime= 0.0, fscan_TR = 0.0;
		

		/*VERIFY*/(m_pEvaluator->GetParamValue("scan_TE", fEchoTime));	
		/*VERIFY*/(m_pEvaluator->GetParamValue("scan_TR", fscan_TR));
		if ( fEchoTime > SeriesParams().EchoTime )
		{
			SeriesParams().EchoTime = fEchoTime;
		}
		if ( fscan_TR > SeriesParams().RepTime )
		{
			SeriesParams().RepTime = fscan_TR;
		}

		if ( !(m_pEvaluator->GetParamValue("bBreathHold", SeriesParams().BreathHold.bBreathHold)) )
		{
			SeriesParams().BreathHold.bBreathHold = false;
		}

		int nACQSeconds = 0;		

		/*VERIFY*/(m_pEvaluator->GetParamValue("out_ACQSeconds", nACQSeconds));
		m_ScanParams.ACQ = nACQSeconds;	
		
		//20070718.liuxuan.for RelSNR
		float fRelativeSNR = 0;
		/*VERIFY*/(m_pEvaluator->GetParamValue("out_relativeSNR", fRelativeSNR));
		m_ScanParams.RelSNR = fRelativeSNR;
		
		// multi-channel
		if ( pSeries->m_oCoilSpecs.m_bQuad == RCV_COIL_TYPE___LINEAR 
			|| pSeries->m_oCoilSpecs.m_bQuad == RCV_COIL_TYPE___QUADRATURE )
		{
			pSeries->m_bSupportMultiChannel = false;
		}
		else if ( pSeries->m_oCoilSpecs.m_bQuad == RCV_COIL_TYPE___PHASE_RESONANCE )
		{
			int nNoOfEnableChannels = 0;
			for ( int i=0; i< pSeries->m_oCoilSpecs.nMaxNumOfChannels; i++ )
			{
				if ( pSeries->m_oCoilSpecs.bMcEnabled[i] )
				{
					nNoOfEnableChannels |= (int) pow( 2, i );
				}
			}

			if ( m_pEvaluator->SetParamValue( "scan_Channels", nNoOfEnableChannels ) )
			{
				pSeries->m_bSupportMultiChannel = true;
			}
			else
			{
				pSeries->m_bSupportMultiChannel = false;
			}
		}
		
		if ( nSequence == cnstLSDI || nSequence == cnstLSDI1B ||
			nSequence == cnstEPDWI || nSequence == cnstEPDWI1B)
		{
			/*VERIFY*/(m_pEvaluator->SetParamValue("ui_MethodOfDI", SeriesParams().nMethodOfDI));
			/*VERIFY*/(m_pEvaluator->SetParamValue("ui_MaxBFactor", SeriesParams().nMaxBFactor));
			/*VERIFY*/(m_pEvaluator->SetParamValue("ui_NumofB", SeriesParams().nNumOfB));
		}

		/** [yhwang 2008.3.28] 向CDL传输FC标识 **/
		m_pEvaluator->SetParamValue("scan_FlowCompensation", SeriesParams().FlowCompensation);
		/** [yhwang 2008.3.28] **/
	}

	UpdateSESpecParams(bCDLToParam);
	
	return true;
}

// Update SE specific parameters.
bool CScan::UpdateSESpecParams(bool bCDLtoParam)
{
	int nSeqtype = SeriesParams().SequenceOptions & cnstBasicSequenceTypeMask;
	if ((nSeqtype != cnstSE) || (nSeqtype != cnstSEDWI) || (nSeqtype != cnstIRSE))
		return true;

	bool bPomp;

	if(bCDLtoParam)
	{
		/*VERIFY*/(m_pEvaluator->GetParamValue("scan_bPOMP", bPomp));

		if (bPomp)
			SeriesParams().SequenceOptions |= cnstPOMP;
		else
			SeriesParams().SequenceOptions &= ~cnstPOMP;
	}
	else
	{
		bPomp = (SeriesParams().SequenceOptions & cnstPOMP) != 0;
		/*VERIFY*/(m_pEvaluator->SetParamValue("scan_bPOMP", bPomp));

	}
	return true;
}

/*
    Add an image to the scan. 
    \param pImage The image to add.
    \post The image will automatically been added to the image container in the
    series which owns this scan.
*/
void CScan::AddImage(CImage* pImage)
{
	CImageIter it = m_Images.begin();
	while (it != m_Images.end() && (*it)->ImageParams().Id < pImage->ImageParams().Id)
		++it;

	m_Images.insert(it, pImage);
    m_pSeries->AddImage(pImage);
}

/*
    Save a scan to disk.
    \return \a true if successful, \a false otherwise.
*/
/*bool CScan::Save()
{
    // create the series directory if necessary
    m_pSeries->CreateFolder();

    CString strDir = 
        CConfigManager::GetHandle().GetImageRootDirectory().c_str();
    strDir.Format(strDir + StudyParams().Id + _T("\\%d\\"), SeriesParams().Id);
//Added by Sun Shang for database function on 2002/09/19 

	CDBInterface* pDB = CDBInterface::GetInstance();
	long lDB_Scan_Id = 0l;
	lDB_Scan_Id = pDB->SaveStudyByScan(this);

//End.

    CString strFile;
    for (CImageIter it = m_Images.begin(); it != m_Images.end(); ++it)
    {
        strFile.Format(strDir + _T("%d.img"), (*it)->ImageParams().Id);
        if ((*it)->SaveToFile(std::string(strFile)) == false)
            return false;
		else
//Added by Sun Shang for database function on 2002/09/19 
			if (lDB_Scan_Id > 0)
				pDB->SaveImagePara(*it, lDB_Scan_Id);
//End.

    }
    return true;
}
*/

void CScan::UpdateOrientations()
{
	
}

// Returns if this scan is the last scan in the series.
bool CScan::IsLastScan() const
{
	return (ScanParams().Id == GetSeries()->Scans().size() - 1);
}

int CScan::GetImageNumber() const
{
    return m_Images.size();
}


void CScan::GetReadDir(CThreeDim& vRead)
{
	vRead.x = m_ScanParams.FreqDirX;
	vRead.y = m_ScanParams.FreqDirY;
	vRead.z = m_ScanParams.FreqDirZ;
}


void CScan::GetPhaseDir(CThreeDim& vPhase)
{
	vPhase.x = m_ScanParams.PhaseDirX;
	vPhase.y = m_ScanParams.PhaseDirY;
	vPhase.z = m_ScanParams.PhaseDirZ;
}


void CScan::GetSliceDir(CThreeDim& vSlice)
{
	vSlice.x = m_ScanParams.SliceDirX;
	vSlice.y = m_ScanParams.SliceDirY;
	vSlice.z = m_ScanParams.SliceDirZ;
}


void CScan::UpdateHBCOffset()
{
	CThreeDim vRead, vPhase, vSlice;

	GetReadDir(vRead);
	GetPhaseDir(vPhase);
	GetSliceDir(vSlice);

	float xOffset = m_ScanParams.ReadOffset * vRead.x + 
					m_ScanParams.PhaseOffset * vPhase.x + 
					m_ScanParams.SliceOffset * vSlice.x;

	float yOffset = m_ScanParams.ReadOffset * vRead.y + 
					m_ScanParams.PhaseOffset * vPhase.y + 
					m_ScanParams.SliceOffset * vSlice.y;

	float zOffset = m_ScanParams.ReadOffset * vRead.z + 
					m_ScanParams.PhaseOffset * vPhase.z + 
					m_ScanParams.SliceOffset * vSlice.z;

	CThreeDim vAP, vLR, vSI;

	StudyField& studyField = StudyParams();
	CDirectionCalculator::GetHandle().GetPhysicalDirection_ALS(
					(EBodyPosition) studyField.PatPosition,
					(EBodyEntry) studyField.PatEntry,
					vAP, vLR, vSI);

	m_dAPOffset = vAP.x * xOffset + vAP.y * yOffset + vAP.z * zOffset;
	m_dLROffset = vLR.x * xOffset + vLR.y * yOffset + vLR.z * zOffset;
	m_dSIOffset = vSI.x * xOffset + vSI.y * yOffset + vSI.z * zOffset;
}

