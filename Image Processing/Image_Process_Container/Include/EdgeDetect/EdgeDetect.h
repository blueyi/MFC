// EdgeDetect.h: interface for the CEdgeDetect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDGEDETECT_H__F4A0E025_EDBB_45B2_B648_D93F30849A81__INCLUDED_)
#define AFX_EDGEDETECT_H__F4A0E025_EDBB_45B2_B648_D93F30849A81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ImageProcess.h"

#include <vector>
using std::vector;

class AFX_EXT_CLASS CEdgeDetect  
{
public:
	BOOL	DetectEdge(/*in*/BYTE* pImage, int iImageWidth, int iImageHeight, /*out*/vector<CPoint> &vecEdge);

	CEdgeDetect();
	virtual ~CEdgeDetect();

private:
	BOOL	FindEdge();
	BOOL	PtOnEdge(BYTE *pImage, int width, int height, int xPos, int yPos);
	BOOL	FindLongestEdge();
	void	EdgeOrder(vector<CPoint> *edge);
	void	EdgeSmoothed(vector<CPoint>* EdgeData,int smoothLength,vector<CPoint>* smoothEdge);

	void	CleanAllEdges();

private:
	vector<CPoint>				m_EdgeLongest;
	vector<CPoint>				m_EdgeOrdered;
	vector<CPoint>				m_EdgeSmoothed;

	vector<CPoint>*				m_pvecEdgeTemp;		// temporary value
	vector<vector<CPoint> *>	m_vecEdges;			// Store all edges

	BYTE*						m_pImage;
	int							m_iImageWidth;
	int							m_iImageHeight;

	CImageProcess				m_ImageProcess;
};

#endif // !defined(AFX_EDGEDETECT_H__F4A0E025_EDBB_45B2_B648_D93F30849A81__INCLUDED_)
