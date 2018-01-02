// Patient.h
//
#if !defined(AFX_PATIENT_H__D27A9F6F_0C09_473A_BBAB_0AC07A354270__INCLUDED_)
#define AFX_PATIENT_H__D27A9F6F_0C09_473A_BBAB_0AC07A354270__INCLUDED_

#include "../BIGlobals/BI_ImageHeader.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef IMAGEHEADER_IMP
   #define CLASS_DECL_IMAGEHEADER __declspec(dllexport)
#else
   #define CLASS_DECL_IMAGEHEADER __declspec(dllimport)
#endif

class CLASS_DECL_IMAGEHEADER CPatient  
{
private:
    CPatient(const CPatient& patient);
    const CPatient& operator = (const CPatient& patient);

public:
	CPatient();
    explicit CPatient(const PatientField& patient);

	virtual ~CPatient();
    bool operator==(const CPatient& patient) const;
    bool operator==(const PatientField& patient) const;

	int AddRef(); // Add reference count.
	int Release(); // Decrease reference count by 1, 

	PatientField& PatientParams() { return m_PatientParams; }
	const PatientField& PatientParams() const { return m_PatientParams; }

	void SetPhantom(bool bIsPhantom) { m_bPhantom = bIsPhantom; }
	bool IsPhantom() const { return m_bPhantom; }

	//Added by Sun Shang for database function at 2002/09/19
	// Set or Get the saved to record number.
	inline long& GetSavedRecordNum() 
	{
		return m_lUniqueRecNoSaveed;
	}
	//End.


protected:
	bool m_bPhantom;

	//Added by Sun Shang for database function at 2002/09/19
	long m_lUniqueRecNoSaveed; // If being saved database then set to record number.
	//End.

	int m_nRefCount;
	PatientField m_PatientParams;
  
};

#endif // !defined(AFX_PATIENT_H__D27A9F6F_0C09_473A_BBAB_0AC07A354270__INCLUDED_)
