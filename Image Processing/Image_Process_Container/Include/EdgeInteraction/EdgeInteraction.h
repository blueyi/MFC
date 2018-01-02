// EdgeInteraction.h: interface for the CEdgeInteraction class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDGEINTERACTION_H__2C204A89_8298_49DC_A700_5E709BC501CA__INCLUDED_)
#define AFX_EDGEINTERACTION_H__2C204A89_8298_49DC_A700_5E709BC501CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
using namespace std;

enum EDGE_OPERATION_TYPE{	EDGE_OPERATION_NULL,
							EDGE_OPERATION_BRUSH,
							EDGE_OPERATION_ERASE,
							EDGE_OPERATION_DRAW,
							EDGE_OPERATION_CUT};

class AFX_EXT_CLASS CEdgeInteraction  
{
public:
	void	MouseMove(CWnd* m_pWnd, CRect rtBorder, CPoint point, /*out*/vector<CPoint> &vecEdge);
	void	LButtonUp(CWnd* m_pWnd, CRect rtBorder, CPoint point, /*out*/vector<CPoint> &vecEdge);
	void	LButtonDown(CWnd* m_pWnd, CRect rtBorder, CPoint point, /*out*/vector<CPoint> &vecEdge);
	void	RePaint(CWnd *pWnd);

	void	SetEdgeOperationPara(int iEdgeOperationType, int iBrashEraseRadius=8);

	CEdgeInteraction();
	virtual ~CEdgeInteraction();

private:
	BOOL	RegionFill(BYTE *pTissue, int width, int height, vector<CPoint>& vectEdge);
	BOOL	LaplacianEN(BYTE *pImage, int width, int height);
	BOOL	EdgeFind(vector<CPoint> &vecEdge);
	BOOL	FindLongestEdge(vector<vector<CPoint> *> &vecEdges, vector<CPoint> &vecEdge);
	BOOL	PtOnEdge(BYTE *pImage, int width, int height, int xPos, int yPos);
	BOOL	Dilate(BYTE *pImage, int width, int height, int nTempWidth, int nTempHeight, BOOL square);
	void	EdgeOrder(vector<CPoint> &vecEdge);
	void	UnLockMouse();

	CRect			m_rtBorder;
	vector<CPoint>	m_vecEdgeBackUp;

	//for BSplan
	vector<CPoint>	m_BSplineSample;
	vector<CPoint>	m_OrdEgOverlap;
	vector<CPoint>	m_BSLineFill;
	int				m_BSplineInd;
	BOOL			m_ptOnOrdEdge;
	//for cut
	vector<CPoint>	m_rFillLine;
	vector<CPoint>	m_rLineFill;
	BOOL			m_rStaPtOnEdge;
	BOOL			m_rEndPtOnEdge;
	CPoint			m_rBtnPtSta;
	CPoint			m_rBtnPtEnd;
	int				m_rStaInd;
	INT				m_rEndInd;

	BOOL			m_bLeftMouseDown;
	BOOL			m_bMouseInROI;

	BYTE*			m_byImageLayer;
	BYTE*			m_byImageLayerCurrent;
	int				m_iImageLayerWidth;
	int				m_iImageLayerHeight;

	int				m_iEdgeOperationType;	/*	0: EDGE_OPERATION_NULL		*
											 *	1: EDGE_OPERATION_BRUSH		*
											 *	2: EDGE_OPERATION_ERASE		*
											 *	3: EDGE_OPERATION_DRAW		*
											 *	4: EDGE_OPERATION_CUT		*/
	int				m_iBrushEraseRadius;
	CPoint			m_ptBrushEraseCenter;

	int             m_iEdgeSize;
	double          m_dRate;
};

#endif // !defined(AFX_EDGEINTERACTION_H__2C204A89_8298_49DC_A700_5E709BC501CA__INCLUDED_)
