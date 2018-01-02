/********************************************************************
File Name:	SystemStatus.cpp
Written by: Yang Guang

Copyright(C) XinaoMDT, 2001 -

Purpose:
	This file defines following classes:
    CSystemStatus:  Used to store some system status information.
History:
	2002/6/14	Created.
*********************************************************************/

#include "stdafx.h"
#include "SystemStatus.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

AFX_EXT_CLASS CSystemStatus CSystemStatus::s_SystemStatus;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSystemStatus::CSystemStatus()
{
    m_pScanningStudy		= NULL;
    m_pDisplayedStudy		= NULL;
    m_pScanningScan			= NULL;

    m_bScanning				= false;
    m_bEmmulating			= false;
    m_bReviewParameters		= false;
	m_bFilming				= false;
	this->m_bSeriesCompare	=FALSE;
	/*********zyh add 2007.11.28*********/
	m_bActiveShimming		= FALSE;
	/**********************************************/
	/** [SHCH-15-12-2007  BUG-TITLE:XABW/CX-31-11-0089] **/
	m_bPrintProcessing		=FALSE;
	/** [SHCH-15-12-2007  BUG-TITLE:] **/
	
	//Added by Tom, --2008.07.10
	m_bConnectNavi = false ;
}

CSystemStatus::~CSystemStatus()
{
}

CSystemStatus& CSystemStatus::GetHandle()
{
	return s_SystemStatus;
}
