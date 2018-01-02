// CDLManager.h
//
#if !defined(AFX_CDLMANAGER_H__B294C810_D340_4634_BFB4_37F00F2271D7__INCLUDED_)
#define AFX_CDLMANAGER_H__B294C810_D340_4634_BFB4_37F00F2271D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning (disable:4786)
#include <string>
#include "../BiGlobals/Bi_ImageHeader.h"

#ifdef IMAGEHEADER_IMP
   #define CLASS_DECL_IMAGEHEADER __declspec(dllexport)
#else
   #define CLASS_DECL_IMAGEHEADER __declspec(dllimport)
#endif

class CSeries;

/*!
	Given the basic type of pulse sequence and pulse sequence options, this
	class can figure out the name of the appropriate cdl file. The sequence
	type and options are all defined in the series field.
*/

class CLASS_DECL_IMAGEHEADER CCDLManager  
{
protected:
	static CCDLManager s_Instance;
	CCDLManager();

	std::string SelectFseCDL(const CSeries* pSeries) const;
	std::string SelectSeCDL(const CSeries* pSeries) const;
		
public:
	static CCDLManager& GetHandle(){
		return s_Instance;
	}
	virtual ~CCDLManager();

	//! Returns the name of the cdl file according to the pulse sequence options.
	std::string GetCDLName(const CSeries* pSeries) const;
	
	EPresaturationDirection CalculatePresaturationDirection(const CSeries* pSeries) const;
	
};

#endif // !defined(AFX_CDLMANAGER_H__B294C810_D340_4634_BFB4_37F00F2271D7__INCLUDED_)
