// SeriesProtocol.h
//
#if !defined(AFX_SERIESPROTOCOL_H__F3B693C6_D7A4_46F3_B681_F5E999AF8507__INCLUDED_)
#define AFX_SERIESPROTOCOL_H__F3B693C6_D7A4_46F3_B681_F5E999AF8507__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../BIGlobals/BI_ImageHeader.h"
#include "StudyProtocol.h"
#include "../BIGlobals/inifile.h"

#pragma warning (disable:4786)
#include <vector>
#include <string>

#include <fstream>
#include <exception>
#include <iostream>
#include <cassert>

//! Container used to hold ScanField struct.
typedef std::vector<ScanField*> CScanFieldContainer;
typedef CScanFieldContainer::iterator CScanFieldIter;
typedef CScanFieldContainer::const_iterator CScanFieldConstIter;

#ifdef IMAGEHEADER_IMP
   #define CLASS_DECL_IMAGEHEADER __declspec(dllexport)
#else
   #define CLASS_DECL_IMAGEHEADER __declspec(dllimport)
#endif

//! Class to represent a series protocol.
/*!
	\remarks A series protocol is a template to create a series. So it should
	hold all series parameters. Since a series can contain multi-scans, as in
	the series for scanograph, a series protocol may have multiple sets of 
	scan parameters. However, it does not have any image data nor the image 
	field parameters, since these are not necessary for creating a new series.
*/
class CLASS_DECL_IMAGEHEADER CSeriesProtocol  
{
public:
	CSeriesProtocol();
	explicit CSeriesProtocol(CStudyProtocol& studyProtocol);
    explicit CSeriesProtocol(CStudyProtocol&, const CSeries& series);
	virtual ~CSeriesProtocol();

public:
    //! Load the series protocol from an input stream.
    bool Load(std::istream& inStream);
	bool Load(CArchive& ar);

	bool Load(CIniFile& iniFile,CString strSectionPrefix,int index);//dolphin
	bool Save(CIniFile& iniFile,CString strSectionPrefix,int index);//dolphin	
    //! Save the series protocol to an output stream.
    bool Save(std::ostream& outStream);
	bool Save(CArchive& ar);


public:
	SeriesField& Params()
	{
		return m_SeriesParams;
	}
	const SeriesField& Params() const
	{
		return m_SeriesParams;
	}
	CScanFieldContainer& Scans()
	{
		return m_Scans;
	}
	const CScanFieldContainer& Scans() const
	{
		return m_Scans;
	}

public:
	std::string GetName() const { return m_strProtocolName; };
	CStudyProtocol* GetParentStudyProtocol() const { return m_pStudyProtocol; }
	void SetParentStudyProtocol(CStudyProtocol* pStudyProtocol){ m_pStudyProtocol = pStudyProtocol; }

public:
	BOOL SelectProtocolfromDlg(int nProtocol);
	void CopyParametersFrom(const CSeriesProtocol& SeriesProtocol);
	void CopyParametersFrom(const CSeries& series);
	void ClearAllScans();

protected:
	SeriesField	m_SeriesParams;     //!< Series parameters.
	CScanFieldContainer m_Scans;    //!< Scan paramaeters.

    //! Study protocol to which this series protocol belongs.
    CStudyProtocol* m_pStudyProtocol;
    std::string m_strProtocolName;

public:
	void LoadProtocolFromFileByBinary(int nIndexOfProtocolGroup, int nIndexOfProtocol);
	
};

#endif // !defined(AFX_SERIESPROTOCOL_H__F3B693C6_D7A4_46F3_B681_F5E999AF8507__INCLUDED_)
