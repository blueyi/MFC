/********************************************************************
File Name:	BIDateTime.h
Written by: Yang Guang

Copyright(C) XinaoMDT, 2001 -

Purpose:
	This file defines following classes:
    CBIDateTime

History:
	2002/5/31	Created.
*********************************************************************/

#if !defined(AFX_BIDATETIME_H__53577DFB_97B0_4FFB_A6D0_1DE181192B9E__INCLUDED_)
#define AFX_BIDATETIME_H__53577DFB_97B0_4FFB_A6D0_1DE181192B9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../BIGlobals/BI_ImageHeader.h"

#pragma warning (disable:4786)

#ifdef IMAGEHEADER_IMP
   #define CLASS_DECL_IMAGEHEADER __declspec(dllexport)
#else
   #define CLASS_DECL_IMAGEHEADER __declspec(dllimport)
#endif

/*!
	This class is used to wrap date/time information that need to be saved 
	to the image header and without forcing the image header to depend on MFC.
	struct BIDateTime in the image header definition file is used to expose the
	file struct while this class is provided to facilitate the manipulation of
	that struct.
	\sa BIDateTime
*/
class CLASS_DECL_IMAGEHEADER CBIDateTime  
{
public:
	unsigned short	year;
	char			month;
	char			day;
	char			hour;
	char			minute;
	char			second;

	CBIDateTime();
	CBIDateTime(const COleDateTime& oleDateTime);
	const CBIDateTime& operator = (const COleDateTime& oleDateTime);
};

#endif // !defined(AFX_BIDATETIME_H__53577DFB_97B0_4FFB_A6D0_1DE181192B9E__INCLUDED_)
