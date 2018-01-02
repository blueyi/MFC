// ImageProcess.h: interface for the CImageProcess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEPROCESS_H__81641AD8_D936_49DA_9FA6_E4B2CC7D9220__INCLUDED_)
#define AFX_IMAGEPROCESS_H__81641AD8_D936_49DA_9FA6_E4B2CC7D9220__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS CImageProcess  
{
public:
	BOOL	MedianFilter(BYTE *pImage, int width, int height, int iTempWidth, int iTempHeight);
	BYTE	ThreshDivide(BYTE* pImage,int width,int height, BYTE nThreshold = 0);
	double*	InteTotal(BYTE* pImage,int width,int height, double* dbGrayLevel);
	BYTE	FindThresh(double *pGrayLevel);
	BOOL	OpenOperate(BYTE *pImage, int width, int height, int nTempWidth=3, int nTempHeight=3, BOOL square=TRUE);
	BOOL	Erode(BYTE* pImage,int width,int height, int nTempWidth, int nTempHeight, BOOL square);
	BOOL	Dilate(BYTE *pImage, int width, int height, int nTempWidth, int nTempHeight, BOOL square);

	CImageProcess();
	virtual ~CImageProcess();

};

#endif // !defined(AFX_IMAGEPROCESS_H__81641AD8_D936_49DA_9FA6_E4B2CC7D9220__INCLUDED_)
