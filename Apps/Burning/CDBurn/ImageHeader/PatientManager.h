/********************************************************************
File Name:	PatientManager.h
Written by: Yang Guang

Copyright(C) XinaoMDT, 2001 -

Purpose:
	This file defines following classes:

History:
	2002/3/27	Created.
*********************************************************************/

#if !defined(AFX_PATIENTMANAGER_H__A156B6AF_28FB_45F6_B0A7_028DEDF36BF3__INCLUDED_)
#define AFX_PATIENTMANAGER_H__A156B6AF_28FB_45F6_B0A7_028DEDF36BF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning (disable:4786)
#include <vector>

class CPatient;
typedef std::vector<CPatient*> CPatientContainer;
typedef CPatientContainer::iterator CPatientIter;

#ifdef IMAGEHEADER_IMP
   #define CLASS_DECL_IMAGEHEADER __declspec(dllexport)
#else
   #define CLASS_DECL_IMAGEHEADER __declspec(dllimport)
#endif

class CLASS_DECL_IMAGEHEADER CPatientManager  
{
protected:
	CPatientManager();
	static CPatientManager s_PatientManager;
public:
	virtual ~CPatientManager();
	static CPatientManager& GetHandle(){
		return s_PatientManager;
	}
	//! Returns pointer to the last patient.
	CPatient* GetCurrentPatient();	

	void AddPatient(CPatient* pPatient);
	CPatient* FindPatient(std::string& strPatientID);
	void RemovePatient(CPatient* pPatient);

	static CPatientContainer s_Patients;
	static CPatient* s_pCurrentPatient;
};

#endif // !defined(AFX_PATIENTMANAGER_H__A156B6AF_28FB_45F6_B0A7_028DEDF36BF3__INCLUDED_)
