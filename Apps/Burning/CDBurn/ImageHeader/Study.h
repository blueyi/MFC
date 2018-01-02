// Study.h : This class is used to represent a study in mri.
//
#if !defined(AFX_STUDY_H__3829283D_A138_4339_98FB_CEFBDAEE7D90__INCLUDED_)
#define AFX_STUDY_H__3829283D_A138_4339_98FB_CEFBDAEE7D90__INCLUDED_

#include "bi_constants.h"
#include "Patient.h"
#include "Containers.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


struct PatientField;
struct SiteField;

class CSeries;
class CStudyProtocol;


#ifdef IMAGEHEADER_IMP
   #define CLASS_DECL_IMAGEHEADER __declspec(dllexport)
#else
   #define CLASS_DECL_IMAGEHEADER __declspec(dllimport)
#endif
#ifndef _CHEN_SHI_
#define _CHEN_SHI_
#endif

/*
	A study is a complete MRI scan for imaging one anatomical 
	structure and/or a certain diseased system. It normally contains a few 
	series, which in turn contains several scans for the same purpose.
*/

//  Type or level of the protocol.
/*
    Protocols' type determines the directory in which they are stored. It 
    also determines the operation that can be done by users of different 
    levels on them. Predefined protocol types including:

    1.System: System protocols are those defined by the BI internals. 
    Users of other only have read access to these protocols. System 
    protocols are stored in the subdirectories of 
    <protocol_root>/system/<body_part>/

    2.User: User protocols are those defined by advanced users. They can 
    be modified by advanced users and bi internals. User protocols are 
    stored in the assorted subdirectories of
    <protocol_root>/users/<body_part>/

    3.Unsorted: Unsorted protocols are created by operators. Noramlly, 
    when an operator meets with a good experiment result, he can save the 
    resulting parameter set as an unsorted protocol. Then an advanced user
    may have a check on it and made it a sorted protocol if necessary.
    Unsorted protocols are stored in subdirectories of 
    <protocol_root>/system/unsorted/
*/
class CLASS_DECL_IMAGEHEADER CStudy  
{
public:
#ifdef _CHEN_SHI_
	int GetCountOfSeries()
	{
		return this->m_Series.size();
	}
	int m_nProcessPACSTran;
#endif

	//Added by Tom, --2008.07.10
	CStudy(CPatient* pPatient, SiteField& site, bool bOwnSite = false);

	CStudy(CPatient& patient, SiteField& site, bool bOwnSite = false);
	CStudy(CPatient& patient, SiteField& site, const CStudyProtocol& protocol, const std::string& strID);
	virtual ~CStudy();

public:
	CScan* GetReadyScan();

public:
    CSeriesContainer& GetSeries() { return m_Series; }
    const CSeriesContainer& GetSeries() const { return m_Series; }

    CSeries* GetSeries(int nSeriesID);
    const CSeries* GetSeries(int nSeriesID) const;

    // Returns patient field parameters.
	PatientField& PatientParams() { return m_pPatient->PatientParams(); }
	CPatient* GetPatient() {return m_pPatient;}
	const PatientField& PatientParams() const { return m_pPatient->PatientParams(); }

	SiteField& SiteParams() { return *m_pSiteParams; }
	const SiteField& SiteParams() const { return *m_pSiteParams; }

	StudyField& StudyParams() { return m_StudyParams; }
	const StudyField&   StudyParams() const { return m_StudyParams; }

public:
	BOOL InsertSeriesAfter(CSeries* pSeriesInsert, const CSeries* pSeriesPos = NULL);
	int FindSeriesIndex(const CSeries* pSeries);
	BOOL OrderSeriesID();
	void CheckSeriesID(); // for debug
	BOOL ReorderSeriesByID();
	BOOL ReorderSeriesByState();

public:
    bool IsCompleted() const;
    void SetComplete();

	bool CanFinish(); // Whether this study can be finished.

    bool CreateFolder(); // Create the study folder on the storage.
	std::string GetPath() const; // Returns the path in which the study is stored.
    bool DeleteFolder(); // Delete the study folder together with its subfolders

    const CSeries* GetCurrentSeries() const { return m_pCurrentSeries; }
    CSeries* GetCurrentSeries() { return m_pCurrentSeries; }
    void SetCurrentSeries(CSeries* pSeries) { m_pCurrentSeries = pSeries; }

    //  Load a study from disk using DB mode.
    static CStudy* Load(const CString& strStudyID);
	//  Load a study using fold mode.
	//static CStudy* LoadandSaveToDB(const CString& strStudyID);
	
    //Added by Sun Shang for database function at 2002/09/19
	//  Set or Get the saved to record number.
	inline long& GetSavedRecordNum() { return m_lUniqueRecNoSaveed; }
	//End.

public:
	//Added by Sun Shang for database function at 2002/09/19
	long m_lUniqueRecNoSaveed; // If this series had saved then be set to record number.	
	//End.

	CSeriesContainer	m_Series; 			// Series contained in the study.
	StudyField			m_StudyParams;		// Study specific parameters.
	CPatient*			m_pPatient;			// Pointer to the patient.
	SiteField*			m_pSiteParams;		// Pointer to the site info.

	CSeries*			m_pCurrentSeries;	// Pointer to the current series.
    //  Flag indicating the study is a complete study, no need to check further if true.
    bool                m_bCompleteStudy; 

    // whether the study should delete the site information in its own 
    // destructor. A study only owns a site when the site of the study is 
    // different from this site. But then, how should we deal with the studyID?
    // If a study comes from a different site, then the patient information
    // should also be different from one that stores in this site, so it must
    // own the patient information too. 
    bool                m_bOwnSite;

	/** [zhlxu 2007.10.23] 为限制某些操作增加变量 **/
	bool m_bDoingMIP;	// MIP标志
	/** [zhlxu 2007.10.23] **/
	
};


//  Function object used to compare a study's id with a given one.
class CLASS_DECL_IMAGEHEADER CompareStudyId
{
public:
    CompareStudyId(const std::string& strId): m_strId (strId) { }

    //  Function operator.
    bool operator()(CStudy* pStudy);
protected:
    std::string m_strId;
};


#endif // !defined(AFX_STUDY_H__3829283D_A138_4339_98FB_CEFBDAEE7D90__INCLUDED_)
