// SeriesManager.h: interface for the CSeriesManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERIESMANAGER_H__6980D118_67AA_4B5A_A70A_54E342EE3870__INCLUDED_)
#define AFX_SERIESMANAGER_H__6980D118_67AA_4B5A_A70A_54E342EE3870__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "vtkImageData.h"
#include "AfxTempl.h"
#include "GlobalHeader.h"
#include "mv.h"

class CSeriesManager  
{
public:
	vtkImageData* GetSegmentedImage(vtkImageData *pImage);
	BOOL SetSegmentedImage(vtkImageData *pImage,vtkImageData *pSegmentedImage);
	BOOL SetBase(vtkImageData *pImage,Matrix m1,Matrix m2,Matrix m3);
	BOOL GetBase(vtkImageData *pImage,Matrix &m1,Matrix &m2,Matrix &m3);
	BOOL SaveSeries(vtkImageData* pImage,CString sFile);
	CString GetName(vtkImageData *pImage);
	vtkImageData* GetAt(int index);
	int Count();
	vtkImageData* OpenSeries(CString sFile);
	CSeriesManager();
	virtual ~CSeriesManager();

private:
	CList<SERIES,SERIES&> m_list;
	vtkImageData* ReadDcmFile(CString sFile);
	vtkImageData* ReadImgSeries(CString sFile);
	vtkImageData* ReadVtiData(CString sFile);
	vtkImageData* ReadJPGFile(CString sFileNoExt,CString sFile);
	vtkImageData* ReadPNGFile(CString sFileNoExt,CString sFile);
	vtkImageData* ReadBMPFile(CString sFileNoExt,CString sFile);
	BOOL WritePNGSeries(vtkImageData *pImage, CString sFile);
	BOOL WriteVTISeries(vtkImageData *pImage, CString sFile);
	BOOL WriteRAWSeries(vtkImageData *pImage, CString sFile);
};

#endif // !defined(AFX_SERIESMANAGER_H__6980D118_67AA_4B5A_A70A_54E342EE3870__INCLUDED_)
