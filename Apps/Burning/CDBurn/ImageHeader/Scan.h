// Scan.h : This class is used to represent a scan in MRI.
//
#if !defined(AFX_SCAN_H__27C0CE4E_EA7E_43E1_9049_349FB2045157__INCLUDED_)
#define AFX_SCAN_H__27C0CE4E_EA7E_43E1_9049_349FB2045157__INCLUDED_

#include "Series.h"

#pragma warning (disable:4786)
#include <vector>
#include <map>

class CImage;
class CReconTask;


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCDL;

enum ScanState
{
	ssSetup,	// Parameters not set, pre-ready state.
	ssReady,	// Parameters set, ready for scan.
	ssPrepared,	// Pulse sequence downloaded.
	ssScanning,	// Currently under scan.
	ssPause,	// Scan paused.
	ssStopped,	// Scan stopped, transient state, should change to ssSetup
	ssComplete,	// Scan complete.
};

#ifdef IMAGEHEADER_IMP
   #define CLASS_DECL_IMAGEHEADER __declspec(dllexport)
#else
   #define CLASS_DECL_IMAGEHEADER __declspec(dllimport)
#endif

/*
	A scan contains a set of images, which have the exact same 
	contrast, with same patient position, same RF coil, same nuclei and same 
	pulse sequence name and parameters.
*/
class CLASS_DECL_IMAGEHEADER CScan  
{
public:
	explicit CScan(CSeries* pSeries, bool bComplete = false, bool bCopy = false);
	virtual ~CScan();

public:
	bool IsLastScan() const;
	BOOL IsHalfEcho() const { return ( SeriesParams().OtherOptions & cnstHalfEcho ); }

    const CImageContainer& Images() const { return m_Images; }
    CImageContainer& Images() { return m_Images; }

    CSeries* GetSeries() { return m_pSeries; }
    const CSeries* GetSeries() const { return m_pSeries; }

    CCDL* CDL() { return m_pEvaluator; }
    const CCDL* CDL() const { return m_pEvaluator; }

    void SetScanState(ScanState state) { m_ScanState = state; }
    ScanState GetScanState() { return m_ScanState; }

    int GetImageNumber() const;

public:
    ScanField& ScanParams() { return m_ScanParams; }
	const ScanField& ScanParams() const { return m_ScanParams; }

	SeriesField& SeriesParams() { return m_pSeries->SeriesParams(); }
	const SeriesField& SeriesParams() const { return m_pSeries->SeriesParams(); }

	StudyField& StudyParams() { return m_pSeries->StudyParams(); }
	const StudyField& StudyParams() const { return m_pSeries->StudyParams(); }

	SiteField& SiteParams() { return m_pSeries->SiteParams(); }
	const SiteField& SiteParams() const { return m_pSeries->SiteParams(); }

	PatientField& PatientParams() { return m_pSeries->PatientParams(); }
	const PatientField& PatientParams() const { return m_pSeries->PatientParams(); }

public:
	void GetReadDir(CThreeDim& vRead);
	void GetPhaseDir(CThreeDim& vPhase);
	void GetSliceDir(CThreeDim& vSlice);

public:
	void UpdateHBCOffset();

public:
	bool UpdateParams(bool bCDLToParam); // CDL <---> ScanField
	bool UpdateCDLParams(bool bCDLToParam);
	bool UpdateSESpecParams(bool bCDLtoParam); // Update SE parameters.

	// Update the scan field (Presaturation) parameter from CDL or vice versa.
	
    // Save all images in the scan.
    //bool Save();
	// Update the orientation characters stored in m_pchOrientations.
	void UpdateOrientations();
	//Added by Sun Shang for database function at 2002/09/19
	// Set or Get the saved to record number.
	inline long& GetSavedRecordNum()  { return m_lUniqueRecNoSaveed; }
	//End.

protected:
    void AddImage(CImage* pImage);


public:
	int		m_nMIPCountOfSlice;
    double m_dAPOffset;
	double m_dLROffset;
	double m_dSIOffset;

	//Added by Tom, --2008.07.10
	CSeries*		m_pSeries;		// Pointer to the hosting series.
	// added by xhb.
	struct CHanningWindowInfo
	{
		bool m_bDoX;
		bool m_bDoY;
		float m_fRatioX;
		float m_fRatioY;
	} m_HanWndInfo;

	// added by sunshang for fermifilter.
	struct CFermiFilter
	{
		bool  m_bEnable;
		float m_fRatioY;
	} m_FermiFilterInfo;


protected:
    //Added by Sun Shang for database function at 2002/09/19
	long m_lUniqueRecNoSaveed; // If the scan be saved then set to record number.
	//End.

	CImageContainer m_Images;		// Images in the scan.
	ScanField		m_ScanParams;	// Parameters of the scan.
	
	//Modified by Tom, --2008.07.10
//	CSeries*		m_pSeries;		//change to public.

	CCDL*			m_pEvaluator;	// Pointer to the parameter evaluator.

	ScanState		m_ScanState;	// State of the scan.

    // Just want to restrict the caller of AddImage() to CImage's constructor.
    // Any better way? -- YG
    friend class CImage;

public:
	bool m_bIsMultiSlabScanning;
	
};


#endif // !defined(AFX_SCAN_H__27C0CE4E_EA7E_43E1_9049_349FB2045157__INCLUDED_)
