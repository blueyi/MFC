// ConfigInfo1.cpp: implementation of the CConfigInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LogServer.h"
#include "ConfigInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------------------------------
CConfigInfo CConfigInfo::m_Object;

// -----------------------------------------------------------------------------------------------------------

CConfigInfo::CConfigInfo()
{
	//	SW02,PROSPECT软件
	//	MS01,磁体温控器
	//	RS01,射频放大器
	//	GS01,梯度放大器
	//	GS02,梯度电源
	//	GS03,匀场放大器
	//	SP01,谱仪
	//	OS01,SIU
	//	OS02,门控
	//	OS03,电动病床
	//	I000,信息类
	//	UNNO,unknown
	m_mRecordFilter["SW02"] = true;
	m_mRecordFilter["MS01"] = true;
	m_mRecordFilter["RS01"] = true;
	m_mRecordFilter["GS01"] = true;
}

CConfigInfo::~CConfigInfo()
{

}

CConfigInfo& CConfigInfo::GetHandle()
{
	return m_Object;
}
