// Series.h : header file
//
#if !defined(AFX_SERIES_H__3F6C5FC6_6D27_4CA2_9948_0D5DB0C14D80__INCLUDED_)
#define AFX_SERIES_H__3F6C5FC6_6D27_4CA2_9948_0D5DB0C14D80__INCLUDED_

#pragma warning (disable:4786)
#include <list>
#include <sstream>

#include "Study.h"
#include "../Geometry/ThreeDim.h"
#include "../BIGlobals/ConfigManager.h"
#include "../ImageHeader/BI_Constants.h"
using namespace Geometry;


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifndef _CHEN_SHI_
#define _CHEN_SHI_
#endif

class CScan;
class CImage;
class CSeriesProtocol;


#ifdef IMAGEHEADER_IMP
   #define CLASS_DECL_IMAGEHEADER __declspec(dllexport)
#else
   #define CLASS_DECL_IMAGEHEADER __declspec(dllimport)
#endif


struct STRUCT_LOC_INFO_OF_ONE_CLUSTER
{
	float fFP2, fFP3;
	float fGReadX,  fGReadY,  fGReadZ, 
		  fGPhaseX, fGPhaseY, fGPhaseZ, 
		  fGSliceX, fGSliceY, fGSliceZ;
	unsigned char nPlaneType;
};

struct STRUCT_PARAM_RELATED_LOC_INFO_OF_ONE_CLUSTER
{
	float C5,C7;
	float D1,D2, D3, D5, D6, D9, D13;
	float G1,G2,G3,G4,G5,G9;
	float TAU;
};

// pos info of one slab
struct STRUCT_POSITION_INFO
{
	float ReadOffset, PhaseOffset, SliceOffset;
	float FreqDirX,  FreqDirY,  FreqDirZ, 
	 PhaseDirX, PhaseDirY, PhaseDirZ, 
	 SliceDirX, SliceDirY, SliceDirZ;
	unsigned char nPlaneType;
};

class CSeries;
class CLASS_DECL_IMAGEHEADER CCluster
{
public:
	CCluster()
	{
		for ( int i=0; i<2; i++ )
		{
			m_nCenterScrnX[i] = m_nCenterScrnY[i] = -999999;
		}
		m_bCanModifyParam = false;
	}
	virtual ~CCluster() { };

public:
	void SetCenter(const CThreeDim& Center) { m_Center = Center; }
	CThreeDim GetCenter() { return m_Center; }

	// set direction vector of READ dir
	void SetV0(const CThreeDim& V0) { m_V0 = V0; }
	CThreeDim GetV0() { return m_V0; }

	// set direction vector of PHASE dir
	void SetV1(const CThreeDim& V1) { m_V1 = V1; }
	CThreeDim GetV1() { return m_V1; }

	void SetV(const CThreeDim& V0, const CThreeDim& V1) { m_V0 = V0, m_V1 = V1; }

private:
	CThreeDim m_V0, m_V1, m_Center;

public:
	LONG m_nCenterScrnX[2], m_nCenterScrnY[2];	// 下标为0：第一个定位窗口的一个cluster的中心点屏幕坐标；下标为1：第二个定位窗口的一个cluster的中心点屏幕坐标
	
	bool m_bCanModifyParam;
	bool GetModifyFlag()
	{
		return m_bCanModifyParam;
	}	
	void SetModifyFlag(bool bCanModify)
	{
		m_bCanModifyParam = bCanModify;
	}

public:
	float fReadOffset, fPhaseOffset, fSliceOffset;
	STRUCT_LOC_INFO_OF_ONE_CLUSTER		oLocInfo;
	STRUCT_PARAM_RELATED_LOC_INFO_OF_ONE_CLUSTER oParamRelatedLocInfo;
	
};



typedef std::vector<CCluster>			CClusterSet;
typedef CClusterSet::iterator			CClusterIter;
typedef CClusterSet::const_iterator		CClusterCIter;


#define MAX_NUM_OF_SLICES_IN_ALL_SLABS		200



//! This class is used to represent a series of MRI series.
/*!
	\remarks Series normally comprises several scans (a set of images). 
	Different scans in the same series are normally of the same pulse sequence
	but may have different parameters. For example, three set of images that
	are used as the scannograph can be regarded as three scans in a series. 
	Also, two slabs of images for left and right eyes respectively can be 
	regarded as two scans in the same series.
*/
class CLASS_DECL_IMAGEHEADER CSeries  
{
	/*********zyh add 2007.11.4*********/
protected:
	BOOL m_bIsSendingToPACS;
	/**********************************************/
public:
	/*********zyh add 2008.1.31*********/
	//是否可裁减
	BOOL m_bEnableCuting;
	/**********************************************/
	
	/*********zyh add 2007.11.4*********/
	//是否正在传送
	BOOL GetSendingStatus(){ return m_bIsSendingToPACS; }
	void SetSendingStauts(BOOL bStatus){ m_bIsSendingToPACS = bStatus; }
	/**********************************************/
	//序列状态；
    enum State
    {
	    ssSetup,	//!< Parameter not set, pre-ready state.
		ssPrepared, //!< Parameters downloaded to spectrometer.
	    ssReady,	//!< Parameter set, ready for scan.
	    ssScanning,	//!< Currently under scan.
	    ssPause,	//!< Scan paused.
	    ssStopped,	//!< Scan stopped, transient state, should change to ssSetup.
	    ssComplete,	//!< Scan complete.
    };

public:
	CSeries(LPCSTR lpszCDLName);
	explicit CSeries(CStudy& study);
	explicit CSeries(CStudy& study, const CSeriesProtocol& protocol, bool bCopy=false);
	virtual ~CSeries();


public:
	const SeriesField& SeriesParams() const { return m_SeriesParams; }
    SeriesField& SeriesParams() { return m_SeriesParams; }

	const StudyField& StudyParams() const { return m_pStudy->StudyParams(); }
	StudyField& StudyParams() { return m_pStudy->StudyParams(); }

    const PatientField& PatientParams() const { return m_pStudy->PatientParams(); }
	PatientField& PatientParams() { return m_pStudy->PatientParams(); }

	const SiteField& SiteParams() const { return m_pStudy->SiteParams(); }
	SiteField& SiteParams() { return m_pStudy->SiteParams(); }

	//获取序列类型；
	int GetSeqenceType() const { return SeriesParams().SequenceOptions & cnstBasicSequenceTypeMask; }

public:
    void AddImage(CImage* pImage);
    int GetImageIndex(CScan* pScan, int nIndexInScan) const;

    // Returns the string representing the series id.
    std::string GetSeriesIDString() const
	{
		std::stringstream os;
		os << "Series " << int (SeriesParams().Id);
		return os.str();
	}

    std::string GetSeriesDesc() const { return SeriesParams().Desc; }

public:
    // returns estimated total scan time of this series.
    int GetTimeEstimated();
	// Sets the estimated total scan time the series will take.
    // This function may be changed to call the calculate routines.
    void SetTimeEstimated(int nTime) { m_nTimeEstimated = nTime; }

    // returns elapsed time of the series.
    int GetTimeElapsed() const { return m_nTimeElapsed; }
    //! Sets the elapsed time of this series.
    void SetTimeElapsed(int nTime) { m_nTimeElapsed = nTime; }

public:
    void SetState(State state) { m_State = state; }
    State GetState() const { return m_State; }

    std::string GetCDLFileName() { return m_strCDLFile; }


public:
	//
    CImageContainer& Images() { return m_Images; }
    const CImageContainer& Images() const { return m_Images; }

	//
    CScanContainer& Scans() { return m_Scans; }
    const CScanContainer& Scans() const { return m_Scans; }

	//
    CScan* GetScan(int nScanId);
    const CScan* GetScan(int nScanId) const;

	//
    CImage* GetImage(int nImageId);
    const CImage* GetImage(int nImageId) const;

    //
    CScan* GetCurrentScan() { return m_pCurrentScan; }
    const CScan* GetCurrentScan() const { return m_pCurrentScan; }
    void SetCurrentScan(CScan* pScan) { m_pCurrentScan = pScan; }

    //
    CStudy* GetStudy() { return m_pStudy; }
    const CStudy* GetStudy() const { return m_pStudy; }
    CImage* GetReferenceImage(int nIndex) const;

public:
#ifdef _CHEN_SHI_
	int GetCountOfImage()
	{
		 return this->m_Images.size();
	}
#endif
	//
    bool CreateFolder();			// Create the folder for the series.
	std::string GetPath() const;	// Get path in which this series is stored.

    //! Syncronizes parameteers in the cdl of all scans in this series.
	bool UpdateCDL(std::string& strCDL);

	//Added by Sun Shang for database function at 2002/09/19
	//! Set or Get the saved to record number.
	inline long& GetSavedRecordNum()
	{
		return m_lUniqueRecNoSaveed;
	}
    //! Returns total acquisition time of the series in seconds.
    int GetACQ() const;
		float GetSNR() const;//20070718.liuxuan.for RelSNR

// TG/RG Tuning
public:
	void SetScale(float fScale) { m_fScale = fScale; }
	float GetScale() { return m_fScale; }
	/**   [SHCH 25:9:2007   16:54 PURPOSE:  检测重建状态]**/
	void SetReconStatus(BOOL nFlag)
	{
		m_bReconFinished=nFlag;
	}
	BOOL GetReconStatus()
	{
		return this->m_bReconFinished;
	}
	/**   [SHCH ]  **/
	
	

protected:
// ======================== implementation ====================================
	//Added by Sun Shang for database function at 2002/09/19
	/**    [SHCH 26:9:2007   10:52  PURPOSE:]    **/
	BOOL m_bReconFinished; 
	/**    [SHCH END]    **/
	
	
	long m_lUniqueRecNoSaveed;		//!< If this series to be saved, then set to record number
	//End.

	CStudy*		m_pStudy;		//!< Pointer to the hosting study.
    CScan*      m_pCurrentScan; //!< Pointer to the current scan (displayed)

    CScanContainer m_Scans;		//!< Scans in the series.
    CImageContainer m_Images;   //!< Images in the series.
	State	m_State;
    std::string m_strCDLFile;   //!< Name of the cdl file.

	int m_nTimeEstimated; // estimated time of the scan, in ms.
	int m_nTimeElapsed; // time elapsed

	float m_fScale; // normalize data after FFT to 0~4095

public:
	/**  [SHCH 20071030 记录MIP旋转轴] **/
	int m_nSelMipAxis;
	/**  [SHCH 20071030 记录MIP旋转轴] **/
	CClusterSet m_ClusterSet;
    SeriesField	m_SeriesParams;	//!< Series field parameters.

	int m_nTotalSliceNumOfAllSlab;	// total slice number of all slabs

	std::vector<STRUCT_POSITION_INFO> vPosInfo; // for annotation

	CCoilSpec m_oCoilSpecs;
	bool m_bSupportMultiChannel;

	/** [GMWU 070915] 增加是否自动最小化计算TE/TR标识 **/
	bool m_bAutoMinTE;
	bool m_bAutoMinTR;
	/***************************************************/
public:
	// for IMRI, not used for image display	, used for IMRI, Gradient correction and RF correction
	int m_nTotalNumOfSlices;
	STRUCT_SLICE_PLANE_INFO m_oCenterPointOfSlices[MAX_NUM_OF_SLICES_IN_ALL_SLABS];
	STRUCT_SLICE_PLANE_INFO* GetCenterPoint( int nNoOfSlice );

public:
	HWND m_hScanParametersPage;

	int m_nBodyPartIDOfCoil;	// for identifying coil automatically
	bool m_bCorrectCoil;

	/** [zhlxu 2007.9.30] 用于调整扫描层顺序 **/
public:
	float m_fSliceGap;	// 用于界面显示>=0.0的Gap值
						// m_fSliceGap为用于界面显示的层间距。取值范围：0.0；正值 
						// SeriesField.SliceGap为用于扫描的层间距。取值范围：0.0；正值；或负值
	/** [zhlxu 2007.9.30] **/

	/** [zhlxu 2007.10.9] 获得总层数及图形定位可视SLAB数目 **/
	unsigned int GetTotalNumofSlices();
	unsigned int GetNumofSlicesPerSlab();
	unsigned int GetNumofSlabs();
	/** [zhlxu 2007.10.9] **/

	/** [zhlxu 2007.11.22] 添加Slabs个数和Slices总层数有效性(序列能支持的)验证功能 **/

	bool ValidateTotalSlabNum();
	bool ValidateTotalSliceNum();
	bool ValidateSliceNumPerSlab();
	/** [zhlxu 2007.11.22] **/
	
	/** [zhlxu 2007.12.17] [XABW/CX-31-11-0068,XABW/CX-31-11-0069,XABW/CX-31-11-0071] 添加序列功能选项的界面限制 **/	
public:
	bool m_bSupportMT, m_bSupportNoPhaseWrap, m_bSupportOverSampling, m_bSupportFC;
	/** [zhlxu 2007.12.17] **/
	
	/*********zyh add 2008.4.28*********/
	bool m_bSupportSAT;
	/**********************************************/

	/** [zhlxu 2008.1.3] [XABW/CX-31-11-0157] 备份/恢复默认Freq、Phase方向参数 **/
public:
	void BackupToDefaultOrientationParams();
	void RestoreFromDefaultOrientationParams();
	/** [zhlxu 2008.1.3] **/

	//Added by Tom, --2008.07.10
	int  m_nNumOfScan;			// 循环扫描次数
	bool m_bFinishedPrescan ;	// 是否完成预扫描的标志
	bool m_bPrescanForFSE ;     //是否执行特定序列预扫描项的标志
	bool m_bPrescanForSSFP ;	//是否执行特定序列预扫描项的标志
	int  m_nScanCount ;
};

#endif // !defined(AFX_SERIES_H__3F6C5FC6_6D27_4CA2_9948_0D5DB0C14D80__INCLUDED_)
