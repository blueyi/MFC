/********************************************************************
File Name:	Patient.cpp
Written by: Yang Guang

Copyright(C) XinaoMDT, 2001 -

Purpose:
	This file defines following classes:

History:
	2002/3/28	Created.
*********************************************************************/

#include "stdafx.h"
#include <cassert>

#include "Patient.h"
#include "PatientManager.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPatient::CPatient()
{
	m_nRefCount = 0;
	m_bPhantom = false;
    memset(&m_PatientParams, 0, sizeof(m_PatientParams));
}

CPatient::~CPatient()
{

}

/*!
	\return Increased reference count.
*/
int CPatient::AddRef()
{
	return (++m_nRefCount);
}

/*!
	\return Remaining reference count.
*/
int CPatient::Release()
{
    // you cannot use a patient without adding reference count.
    ASSERT(m_nRefCount > 0);
	--m_nRefCount;
	if (m_nRefCount == 0)
	{
//		CPatientManager::GetHandle().RemovePatient(this);
		delete this;
        return 0;
	}
	return m_nRefCount;
}

CPatient::CPatient(const PatientField& patient)
{
    // here the bit-wise copy is ok.
	m_nRefCount = 0;
	m_bPhantom = false;
    memset(&m_PatientParams, 0, sizeof(m_PatientParams));
    m_PatientParams = patient;
}

CPatient::CPatient(const CPatient& patient)
{
    // this function is here only to prevent casual use of copy constructor.
    assert(0);
}

const CPatient& CPatient::operator = (const CPatient& patient)
{
    // this function is here only to prevent casual use of assignment.
    assert(0);
    return *this;
}

bool CPatient::operator==(const CPatient& patient) const
{
    // if the patients' id is the same, the patients is equal.
    return (strcmp(m_PatientParams.Id, patient.m_PatientParams.Id) == 0);
}

bool CPatient::operator==(const PatientField& patient) const
{
    // if the patients' id is the same, the patients is equal.
    return (strcmp(m_PatientParams.Id, patient.Id) == 0);
}
