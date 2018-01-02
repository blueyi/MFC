/********************************************************************
File Name:	PatientManager.cpp
Written by: Yang Guang

Copyright(C) XinaoMDT, 2001 -

Purpose:
	This file defines following classes:

History:
	2002/3/27	Created.
*********************************************************************/

#include "stdafx.h"
#include "PatientManager.h"
#include "patient.h"

#pragma warning (disable:4786)
#include <algorithm>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPatientManager CPatientManager::s_PatientManager;
CPatient* CPatientManager::s_pCurrentPatient = NULL;
CPatientContainer CPatientManager::s_Patients;

CPatientManager::CPatientManager()
{

}

CPatientManager::~CPatientManager()
{
    // Seems every time we are using a pointer, we need to check for its validity.
    if (s_pCurrentPatient)
        s_pCurrentPatient->Release();

    for (CPatientIter it = s_Patients.begin(); it != s_Patients.end(); ++it)
    {
        delete (*it);
    }
}

void CPatientManager::AddPatient(CPatient* pPatient)
{
	ASSERT(pPatient);
	pPatient->AddRef();

	if (std::find(s_Patients.begin(), s_Patients.end(), pPatient) != s_Patients.end())
		return;
    
    s_Patients.push_back(pPatient);

	if (s_pCurrentPatient)
    {
		s_pCurrentPatient->Release();
    }
	s_pCurrentPatient = pPatient;
}

CPatient* CPatientManager::GetCurrentPatient()
{
	return s_pCurrentPatient;
}

/*!
    \todo This function should be changed to protected, you will only need to
    call GetPatient() to let the Mananger to load a patient's information
    and return the pointer to the patient. AddPatient() should also be changed
    this way.
*/
CPatient* CPatientManager::FindPatient(std::string& strPatientID)
{
	for (CPatientIter it = s_Patients.begin(); it != s_Patients.end(); it++)
	{
		if (strPatientID.compare((*it)->PatientParams().Id) == 0)
			return *it;
	}
	return NULL;
}

void CPatientManager::RemovePatient(CPatient* pPatient)
{
	CPatientIter it = 
		std::find(s_Patients.begin(), s_Patients.end(), pPatient);
	if (it != s_Patients.end())
	{
		s_Patients.erase(it);
	}
}
