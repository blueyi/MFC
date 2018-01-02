/********************************************************************
File Name:	BIDateTime.cpp
Written by: Yang Guang

Copyright(C) XinaoMDT, 2001 -

Purpose:
	This file defines following classes:
    CBIDateTime

History:
	2002/5/31	Created.
*********************************************************************/

#include "stdafx.h"
#include <afxdisp.h> 
#include "BIDateTime.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBIDateTime::CBIDateTime()
{ 
	year	= 0;
	month	= 0;
	day		= 0;
	hour	= 0;
	minute	= 0;
	second	= 0;
}

/*!
    This constructor allows us to construct a CBIDateTime object from a 
    COleDateTime object, this is a convenient way to initialize a CBIDateTime
    object.
*/
CBIDateTime::CBIDateTime(const COleDateTime& oleDateTime)
{
	year = oleDateTime.GetYear();
	month = oleDateTime.GetMonth();
	day	= oleDateTime.GetDay();
	hour = oleDateTime.GetHour();
	minute = oleDateTime.GetMinute();
	second = oleDateTime.GetSecond();
}

const CBIDateTime& CBIDateTime::operator= (const COleDateTime& oleDateTime)
{
	year = oleDateTime.GetYear();
	month = oleDateTime.GetMonth();
	day	= oleDateTime.GetDay();
	hour = oleDateTime.GetHour();
	minute = oleDateTime.GetMinute();
	second = oleDateTime.GetSecond();

    return *this;
}
