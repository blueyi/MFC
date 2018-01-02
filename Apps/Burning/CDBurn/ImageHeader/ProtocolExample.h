// ProtocolExample.h: interface for the CProtocolExample class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROTOCOLEXAMPLE_H__CE3BB3BD_8510_4DDB_9824_069E375D3131__INCLUDED_)
#define AFX_PROTOCOLEXAMPLE_H__CE3BB3BD_8510_4DDB_9824_069E375D3131__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../BIGlobals/BI_ImageHeader.h"
#ifdef IMAGEHEADER_IMP
   #define CLASS_DECL_IMAGEHEADER __declspec(dllexport)
#else
   #define CLASS_DECL_IMAGEHEADER __declspec(dllimport)
#endif


class CLASS_DECL_IMAGEHEADER CProtocolExample  
{
public:
	//brain
	static void SeriesSESag(SeriesField* seriesField, ScanField* scanField);
	static void SeriesSEAx(SeriesField* seriesField,  ScanField* scanField);
	static void SeriesSECor(SeriesField* seriesField, ScanField* scanField);
		
	static void SeriesFSEAx(SeriesField* seriesField, ScanField* scanField);
	static void SeriesFSESag(SeriesField* seriesField, ScanField* scanField);
	static void SeriesFSECor(SeriesField* seriesField, ScanField* scanField);

	static void SeriesFLAIRAx(SeriesField* seriesField, ScanField* scanField);
	static void SeriesFLAIRSag(SeriesField* seriesField, ScanField* scanField);
	static void SeriesFLAIRCor(SeriesField* seriesField, ScanField* scanField);
	
	///
	static void PelvSESag(SeriesField* seriesField, ScanField* scanField);
	static void PelvSEAx(SeriesField* seriesField,  ScanField* scanField);
	static void PelvSECor(SeriesField* seriesField, ScanField* scanField);
		
	static void PelvFSEAx(SeriesField* seriesField, ScanField* scanField);
	static void PelvFSESag(SeriesField* seriesField, ScanField* scanField);
	static void PelvFSECor(SeriesField* seriesField, ScanField* scanField);

	static void PelvSTIRAx(SeriesField* seriesField, ScanField* scanField);
	static void PelvSTIRSag(SeriesField* seriesField, ScanField* scanField);
	static void PelvSTIRCor(SeriesField* seriesField, ScanField* scanField);
	//knee.
	static void KneeSESag(SeriesField* seriesField, ScanField* scanField);
	static void KneeSEAx(SeriesField* seriesField,  ScanField* scanField);
	static void KneeSECor(SeriesField* seriesField, ScanField* scanField);
	static void KneeFSESag(SeriesField* seriesField, ScanField* scanField);
	static void KneeSTIRSag(SeriesField* seriesField, ScanField* scanField);


	//for Utilities. LZ 2004-08-25
	/* Removed for release version
	static void TESTSeriesSEAx(SeriesField* seriesField,  ScanField* scanField);
	static void TESTSeiresFSEAx(SeriesField* seriesField, ScanField* scanField);
	static void TESTHeadSPRGCor(SeriesField* seriesField, ScanField* scanField);
	*/
	static void Shimming(SeriesField* seriesField, ScanField* scanField);
	
	static void SeriesGE2D(SeriesField* seriesField);


	CProtocolExample();
	virtual ~CProtocolExample();

protected:	

	//
	static void ScanAxial(ScanField* scanField);
	static void ScanCoronal(ScanField* scanField);
	static void ScanSagital(ScanField* scanField);

	static void PelvScanAxial(ScanField* scanField);
	static void PelvScanCoronal(ScanField* scanField);
	static void PelvScanSagital(ScanField* scanField);


	static void SeriesSE(SeriesField* seriesField);
		
	static void SeriesFSE(SeriesField* seriesField);

	static void SeriesSPGR3DCor(SeriesField* seriesField);


};

#endif // !defined(AFX_PROTOCOLEXAMPLE_H__CE3BB3BD_8510_4DDB_9824_069E375D3131__INCLUDED_)
