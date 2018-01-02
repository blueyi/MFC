// ConfigInfo1.h: interface for the CConfigInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFIGINFO1_H__26FC5913_B00D_474E_8F57_22DEE56ED17C__INCLUDED_)
#define AFX_CONFIGINFO1_H__26FC5913_B00D_474E_8F57_22DEE56ED17C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// -----------------------------------------------------------------------------------------------------------
#pragma warning (disable:4786)
#include <string>
#include <map>
#include <vector>

// -----------------------------------------------------------------------------------------------------------
#include "CommonDefine.h"

// -----------------------------------------------------------------------------------------------------------
class CConfigInfo  
{
public:
	CConfigInfo();
	virtual ~CConfigInfo();

	static CConfigInfo m_Object;
	static CConfigInfo& GetHandle();

public:
	std::vector<STRUCT_PACKET_FAULT_DIAGNOSIS> m_vRecords;
	std::map<CString,bool> m_mRecordFilter;

	
};

#endif // !defined(AFX_CONFIGINFO1_H__26FC5913_B00D_474E_8F57_22DEE56ED17C__INCLUDED_)
