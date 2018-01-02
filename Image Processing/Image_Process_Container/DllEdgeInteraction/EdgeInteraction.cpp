// EdgeInteraction.cpp: implementation of the CEdgeInteraction class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EdgeInteraction.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include <list>
#include <algorithm>
#include <math.h>
#include "Matrix.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEdgeInteraction::CEdgeInteraction()
{
	m_BSplineInd		= 0;
	m_rStaInd			= 0;
	m_rEndInd			= 0;
	m_ptOnOrdEdge		= FALSE;
	m_rEndPtOnEdge		= FALSE;
	m_rStaPtOnEdge		= FALSE;
	m_rBtnPtSta.x		= -100;
	m_rBtnPtSta.y		= -100;
	m_rBtnPtEnd.x		= -100;
	m_rBtnPtEnd.y		= -100;

	m_bLeftMouseDown	= FALSE;
	m_bMouseInROI		= FALSE;

	m_iEdgeOperationType	= EDGE_OPERATION_NULL;
	m_iBrushEraseRadius		= 8;
	m_ptBrushEraseCenter.x		= -100;
	m_ptBrushEraseCenter.y		= -100;
	m_rtBorder.SetRect(0,0,0,0);

	m_byImageLayer			= NULL;
	m_byImageLayerCurrent	= NULL;
	m_iImageLayerWidth		= 0;
	m_iImageLayerHeight		= 0;

	m_iEdgeSize = 6;
	m_dRate=1.0;
}

CEdgeInteraction::~CEdgeInteraction()
{
	if (m_byImageLayer) 
	{
		delete [] m_byImageLayer;
		m_byImageLayer = NULL;
	}

	if (m_byImageLayerCurrent) 
	{
		delete [] m_byImageLayerCurrent;
		m_byImageLayerCurrent = NULL;
	}
}

void CEdgeInteraction::SetEdgeOperationPara(int iEdgeOperationType, int iBrashEraseRadius)
{
	m_iEdgeOperationType = iEdgeOperationType;
	m_iBrushEraseRadius = iBrashEraseRadius;
}

void CEdgeInteraction::LButtonDown(CWnd* m_pWnd, CRect rtBorder, CPoint point, /*out*/vector<CPoint> &vecEdge)
{
	int w, h;

	if (m_iEdgeOperationType == EDGE_OPERATION_NULL) 
	{
		return;
	}
	
	if (vecEdge.size() != 0) 
	{
		m_rtBorder = rtBorder;
		CPoint ptBrushCenter = point;
		m_ptBrushEraseCenter = ptBrushCenter;
		int radius = m_iBrushEraseRadius;
		CRect clip;
		CPoint ptTLInner, ptBRInner;
		ptTLInner.x = rtBorder.TopLeft().x + radius +1;
		ptTLInner.y = rtBorder.TopLeft().y + radius +1;
		ptBRInner.x = rtBorder.BottomRight().x - radius -1;
		ptBRInner.y = rtBorder.BottomRight().y - radius -1;
		clip.SetRect(ptTLInner,ptBRInner);
			
		switch(m_iEdgeOperationType) {
		case EDGE_OPERATION_BRUSH:
			{
				if (clip.PtInRect(point)) 
				{
					m_bLeftMouseDown = TRUE;
					
					m_iImageLayerWidth = rtBorder.Width();
					m_iImageLayerHeight = rtBorder.Height();
					
					if (m_byImageLayer) 
					{
						delete [] m_byImageLayer;
						m_byImageLayer = NULL;
					}
					m_byImageLayer = new BYTE[m_iImageLayerWidth*m_iImageLayerHeight];
					RegionFill(m_byImageLayer, m_iImageLayerWidth, m_iImageLayerHeight, vecEdge);
					
					if (m_byImageLayerCurrent) 
					{
						delete [] m_byImageLayerCurrent;
						m_byImageLayerCurrent = NULL;
					}
					m_byImageLayerCurrent = new BYTE[m_iImageLayerWidth*m_iImageLayerHeight];
					memcpy(m_byImageLayerCurrent, m_byImageLayer, sizeof(BYTE)*m_iImageLayerWidth*m_iImageLayerHeight);
					
					m_vecEdgeBackUp = vecEdge;
					vecEdge.clear();
					for (h=ptBrushCenter.y-radius; h<ptBrushCenter.y+radius; h++)
					{
						for (w=ptBrushCenter.x-radius; w<ptBrushCenter.x+radius; w++)
						{
							if (((h-ptBrushCenter.y)*(h-ptBrushCenter.y)+(w-ptBrushCenter.x)*(w-ptBrushCenter.x) <= radius*radius) && 
								(h<rtBorder.top+m_iImageLayerHeight-1) && (h>rtBorder.top) && 
								(w<rtBorder.left+m_iImageLayerWidth-1) && (w>rtBorder.left)) 
							{
								*(m_byImageLayerCurrent + 
									(rtBorder.top+m_iImageLayerHeight-h)*m_iImageLayerWidth + 
									(w-rtBorder.left)) = (BYTE)0;
							}
						}
					}
					
					BYTE* pbyImage = new BYTE[m_iImageLayerWidth*m_iImageLayerHeight];
					memcpy(pbyImage, m_byImageLayerCurrent, sizeof(BYTE)*m_iImageLayerWidth*m_iImageLayerHeight);
					LaplacianEN(pbyImage, m_iImageLayerWidth, m_iImageLayerHeight);
					for (h=0; h<m_iImageLayerHeight; h++)
					{
						for (w=0; w<m_iImageLayerWidth; w++)
						{
							if (0 == *(pbyImage +h*m_iImageLayerWidth+w)) 
							{
								CPoint pt;
								pt.x = w;
								pt.y = h;
								vecEdge.push_back(pt);
							}
						}
					}
					delete [] pbyImage;
					pbyImage = NULL;
					
					{//set the range of the mouse move in ROI
						CRect clip;
						CPoint ptTLInner, ptBRInner;
						ptTLInner.x = rtBorder.TopLeft().x + radius + 1;
						ptTLInner.y = rtBorder.TopLeft().y + radius + 1;
						ptBRInner.x = rtBorder.BottomRight().x - radius - 1;
						ptBRInner.y = rtBorder.BottomRight().y - radius - 1;
						clip.SetRect(ptTLInner,ptBRInner);
						m_pWnd->ClientToScreen(clip);
						ClipCursor(clip);
					}
				}
				
			}
			break;
		case EDGE_OPERATION_ERASE:
			{
				if (clip.PtInRect(point)) 
				{
					m_bLeftMouseDown = TRUE;
					
					m_iImageLayerWidth = rtBorder.Width();
					m_iImageLayerHeight = rtBorder.Height();
					
					if (m_byImageLayer) 
					{
						delete [] m_byImageLayer;
						m_byImageLayer = NULL;
					}
					m_byImageLayer = new BYTE[m_iImageLayerWidth*m_iImageLayerHeight];
					RegionFill(m_byImageLayer, m_iImageLayerWidth, m_iImageLayerHeight, vecEdge);
					
					if (m_byImageLayerCurrent) 
					{
						delete [] m_byImageLayerCurrent;
						m_byImageLayerCurrent = NULL;
					}
					m_byImageLayerCurrent = new BYTE[m_iImageLayerWidth*m_iImageLayerHeight];
					memcpy(m_byImageLayerCurrent, m_byImageLayer, sizeof(BYTE)*m_iImageLayerWidth*m_iImageLayerHeight);
					
					m_vecEdgeBackUp = vecEdge;
					vecEdge.clear();
					for (h=ptBrushCenter.y-radius; h<ptBrushCenter.y+radius; h++)
					{
						for (w=ptBrushCenter.x-radius; w<ptBrushCenter.x+radius; w++)
						{
							if (((h-ptBrushCenter.y)*(h-ptBrushCenter.y)+(w-ptBrushCenter.x)*(w-ptBrushCenter.x) <= radius*radius) && 
								(h<rtBorder.top+m_iImageLayerHeight-1) && (h>rtBorder.top) && 
								(w<rtBorder.left+m_iImageLayerWidth-1) && (w>rtBorder.left)) 
							{
								*(m_byImageLayerCurrent + 
									(rtBorder.top+m_iImageLayerHeight-h)*m_iImageLayerWidth + 
									(w-rtBorder.left)) = (BYTE)255;
							}
						}
					}
					
					BYTE* pbyImage = new BYTE[m_iImageLayerWidth*m_iImageLayerHeight];
					memcpy(pbyImage, m_byImageLayerCurrent, sizeof(BYTE)*m_iImageLayerWidth*m_iImageLayerHeight);
					LaplacianEN(pbyImage, m_iImageLayerWidth, m_iImageLayerHeight);
					for (h=0; h<m_iImageLayerHeight; h++)
					{
						for (w=0; w<m_iImageLayerWidth; w++)
						{
							if (0 == *(pbyImage +h*m_iImageLayerWidth+w)) 
							{
								CPoint pt;
								pt.x = w;
								pt.y = h;
								vecEdge.push_back(pt);
							}
						}
					}
					delete [] pbyImage;
					pbyImage = NULL;
					
					{//set the range of the mouse move in ROI
						CRect clip;
						CPoint ptTLInner, ptBRInner;
						ptTLInner.x = rtBorder.TopLeft().x + radius + 1;
						ptTLInner.y = rtBorder.TopLeft().y + radius + 1;
						ptBRInner.x = rtBorder.BottomRight().x - radius - 1;
						ptBRInner.y = rtBorder.BottomRight().y - radius - 1;
						clip.SetRect(ptTLInner,ptBRInner);
						m_pWnd->ClientToScreen(clip);
						ClipCursor(clip);
					}
				}
			}
			break;
		case EDGE_OPERATION_DRAW:
			{
				if(!m_bLeftMouseDown && m_rtBorder.PtInRect(point))
				{
					m_iImageLayerWidth = rtBorder.Width();
					m_iImageLayerHeight = rtBorder.Height();
					if (vecEdge.size() > 0) 
					{
						m_ptOnOrdEdge = false;		//Added by hiker 2008.03.28 for bug
						if(rtBorder.PtInRect(point))
						{
							int dist = 0;
							int minDist = 1000;
							m_ptOnOrdEdge = false;
							
							for(int i = 0; i != vecEdge.size(); ++i)
							{
								CPoint temp = vecEdge[i];
								dist = abs(temp.x - (point.x - rtBorder.left)) + abs(temp.y - (rtBorder.bottom - point.y));
								if (dist < minDist)
								{
									minDist = dist;
									m_BSplineInd = i;
								}
							}
							if (minDist < m_iEdgeSize)
							{
								m_ptOnOrdEdge = true;
								::SetCursor(::LoadCursor(NULL,IDC_CROSS));
							}
							else
							{
								return;
							}
						}
					}
					m_BSplineSample.clear();
					m_OrdEgOverlap.clear();
					for(int overlap =1; overlap <= 3 ;overlap++)
					{
						for(int ind = 0; ind < vecEdge.size(); ind++)
						{
							CPoint temppt;
							temppt.x = vecEdge[ind].x;
							temppt.y = vecEdge[ind].y;
							m_OrdEgOverlap.push_back(temppt);
						}
					}
					int startInd,endInd;
					
					int ptNum;
					if(vecEdge.size() > 1200)
						ptNum = vecEdge.size() / 14;
					else if(vecEdge.size() > 1000)
						ptNum = vecEdge.size() / 12;
					else if(vecEdge.size() > 800)
						ptNum = vecEdge.size() / 9;
					else if(vecEdge.size() > 600)
						ptNum = vecEdge.size() / 8;
					else if(vecEdge.size() > 400)
						ptNum = vecEdge.size() / 7;
					else
						ptNum = vecEdge.size() / 4;
					
					ptNum = ptNum * m_dRate;
					if (ptNum >=10)
					{
						m_bLeftMouseDown = TRUE;
						int stepPt = ptNum / 9;
						startInd = vecEdge.size() + (m_BSplineInd - 4 * stepPt);
						endInd = vecEdge.size() + (m_BSplineInd + 5 * stepPt +1);
						for(int i = startInd; i < endInd; i += stepPt)
						{
							CPoint insertPt = m_OrdEgOverlap[i];
							m_BSplineSample.push_back(insertPt);
						}
						m_OrdEgOverlap.erase(m_OrdEgOverlap.end() - (2 * vecEdge.size() - startInd - 1), m_OrdEgOverlap.end());
						m_OrdEgOverlap.erase(m_OrdEgOverlap.begin(), m_OrdEgOverlap.begin() + endInd);
						{//set the range of the mouse move in ROI
							CRect clip;
							clip.SetRect(rtBorder.TopLeft(),rtBorder.BottomRight());
							m_pWnd->ClientToScreen(clip);
							ClipCursor(clip);
						}
					}
				}
			}
			break;
		case EDGE_OPERATION_CUT:
			{
				if(m_rtBorder.PtInRect(point))
				{
					m_iImageLayerWidth = rtBorder.Width();
					m_iImageLayerHeight = rtBorder.Height();
					
					int dist = 0;
					int minDist = 1000;
					m_rStaPtOnEdge = false;
					
					for(int i = 0; i != vecEdge.size(); ++i)
					{
						CPoint temp = vecEdge[i];
						dist = abs(temp.x - (point.x - m_rtBorder.left)) + abs(temp.y - (m_rtBorder.bottom - point.y));
						if (dist < minDist)
						{
							minDist = dist;
							m_rBtnPtSta.x = temp.x;
							m_rBtnPtSta.y = temp.y;
							m_rStaInd = i;
						}
					}
					if (minDist < m_iEdgeSize)
					{
						m_rStaPtOnEdge = true;
						m_bLeftMouseDown = TRUE;
						{//set the range of the mouse move in ROI
							CRect clip;
							clip.SetRect(rtBorder.TopLeft(),rtBorder.BottomRight());
							m_pWnd->ClientToScreen(clip);
							ClipCursor(clip);
						}
					}
				}
			}
		default:
			break;
		}
	}
}

void CEdgeInteraction::MouseMove(CWnd* m_pWnd, CRect rtBorder, CPoint point, /*out*/vector<CPoint> &vecEdge)
{

	if (m_iEdgeOperationType == EDGE_OPERATION_NULL) 
	{
		return;
	}

	m_rtBorder = rtBorder;
	CPoint ptBrushCenter = point;
	m_ptBrushEraseCenter = ptBrushCenter;
	int w, h;
	int radius = m_iBrushEraseRadius;
	CRect clip;
	CPoint ptTLInner, ptBRInner;
	ptTLInner.x = rtBorder.TopLeft().x + radius +1;
	ptTLInner.y = rtBorder.TopLeft().y + radius +1;
	ptBRInner.x = rtBorder.BottomRight().x - radius -1;
	ptBRInner.y = rtBorder.BottomRight().y - radius -1;
	clip.SetRect(ptTLInner,ptBRInner);

	switch(m_iEdgeOperationType) {
	case EDGE_OPERATION_BRUSH:
		{
			if (clip.PtInRect(point)) 
			{
				m_bMouseInROI = TRUE;
				::SetCursor(::LoadCursor(NULL,IDC_ICON));
				if (m_bLeftMouseDown) 
				{
					vecEdge.clear();
					for (h=ptBrushCenter.y-radius; h<ptBrushCenter.y+radius; h++)
					{
						for (w=ptBrushCenter.x-radius; w<ptBrushCenter.x+radius; w++)
						{
							if (((h-ptBrushCenter.y)*(h-ptBrushCenter.y)+(w-ptBrushCenter.x)*(w-ptBrushCenter.x) <= radius*radius) && 
								(h<=rtBorder.top+m_iImageLayerHeight-2) && (h>=rtBorder.top+2) && 
								(w<=rtBorder.left+m_iImageLayerWidth-2) && (w>=rtBorder.left+2)) 
							{
								*(m_byImageLayerCurrent + 
									(rtBorder.top+m_iImageLayerHeight-h)*m_iImageLayerWidth + 
									(w-rtBorder.left)) = (BYTE)0;
							}
						}
					}
					
					BYTE* pbyImage = new BYTE[m_iImageLayerWidth*m_iImageLayerHeight];
					memcpy(pbyImage, m_byImageLayerCurrent, sizeof(BYTE)*m_iImageLayerWidth*m_iImageLayerHeight);
					LaplacianEN(pbyImage, m_iImageLayerWidth, m_iImageLayerHeight);
					for (h=0; h<m_iImageLayerHeight; h++)
					{
						for (w=0; w<m_iImageLayerWidth; w++)
						{
							if (0 == *(pbyImage +h*m_iImageLayerWidth+w)) 
							{
								CPoint pt;
								pt.x = w;
								pt.y = h;
								vecEdge.push_back(pt);
							}
						}
					}
					delete [] pbyImage;
					pbyImage = NULL;
				}
			}
			else
			{
				m_bMouseInROI = FALSE;
			}
		}
		break;
	case EDGE_OPERATION_ERASE:
		{
			if (clip.PtInRect(point)) 
			{
				m_bMouseInROI = TRUE;
				::SetCursor(::LoadCursor(NULL,IDC_ICON));
				if (m_bLeftMouseDown) 
				{
					vecEdge.clear();
					for (int h=ptBrushCenter.y-radius; h<ptBrushCenter.y+radius; h++)
					{
						for (int w=ptBrushCenter.x-radius; w<ptBrushCenter.x+radius; w++)
						{
							if (((h-ptBrushCenter.y)*(h-ptBrushCenter.y)+(w-ptBrushCenter.x)*(w-ptBrushCenter.x) <= radius*radius) && 
								(h<=rtBorder.top+m_iImageLayerHeight-2) && (h>=rtBorder.top+2) && 
								(w<=rtBorder.left+m_iImageLayerWidth-2) && (w>=rtBorder.left+2)) 
							{
								*(m_byImageLayerCurrent + 
									(rtBorder.top+m_iImageLayerHeight-h)*m_iImageLayerWidth + 
									(w-rtBorder.left)) = (BYTE)255;
							}
						}
					}
					
					BYTE* pbyImage = new BYTE[m_iImageLayerWidth*m_iImageLayerHeight];
					memcpy(pbyImage, m_byImageLayerCurrent, sizeof(BYTE)*m_iImageLayerWidth*m_iImageLayerHeight);
					LaplacianEN(pbyImage, m_iImageLayerWidth, m_iImageLayerHeight);
					for (h=0; h<m_iImageLayerHeight; h++)
					{
						for (w=0; w<m_iImageLayerWidth; w++)
						{
							if (0 == *(pbyImage +h*m_iImageLayerWidth+w)) 
							{
								CPoint pt;
								pt.x = w;
								pt.y = h;
								vecEdge.push_back(pt);
							}
						}
					}
					delete [] pbyImage;
					pbyImage = NULL;
				}
			}
			else
			{
				m_bMouseInROI = FALSE;
			}
		}
		break;
	case EDGE_OPERATION_DRAW:
		{
			if (!m_bLeftMouseDown)
			{
				if (vecEdge.size() > 0) 
				{
					if(rtBorder.PtInRect(point))
					{
						int dist = 0;
						int minDist = 1000;
						
						for(int i = 0; i != vecEdge.size(); ++i)
						{
							CPoint temp = vecEdge[i];
							dist = abs(temp.x - (point.x - rtBorder.left)) + abs(temp.y - (rtBorder.bottom - point.y));
							if (dist < minDist)
							{
								minDist = dist;
							}
						}
						if (minDist < m_iEdgeSize)
						{
							::SetCursor(::LoadCursor(NULL,IDC_CROSS));
						}
					}
				}
			}
			else
			{
				if (m_BSplineSample.size() > 0 && m_ptOnOrdEdge)
				{
					::SetCursor(::LoadCursor(NULL,IDC_CROSS));

					if(rtBorder.PtInRect(point))
					{
						::SetCursor(::LoadCursor(NULL,IDC_CROSS));
						vecEdge.clear();
						for(int copyid = 0; copyid != m_OrdEgOverlap.size(); copyid++)
						{
							CPoint copypt;
							copypt.x = m_OrdEgOverlap[copyid].x;
							copypt.y = m_OrdEgOverlap[copyid].y;
							vecEdge.push_back(copypt);
						}

						m_BSLineFill.clear();

						m_BSplineSample.erase(m_BSplineSample.begin() + 4);
						CPoint insertPt;	//Modified by hiker 2008.03.17
						insertPt.x = point.x - rtBorder.left;
						insertPt.y = rtBorder.bottom - point.y;
						m_BSplineSample.insert(m_BSplineSample.begin() + 4, insertPt);
						
						//Added by hiker 2008.03.17
						CPoint ptPre, ptPost;
						int tempDist[9];
						int nPointCount = 0;
						for(int i = 0; i < 9; i++)
						{
							ptPre.x = m_BSplineSample[i].x;
							ptPre.y = m_BSplineSample[i].y;
							ptPost.x = m_BSplineSample[i + 1].x;
							ptPost.y = m_BSplineSample[i + 1].y;
							tempDist[i] = abs(ptPre.x - ptPost.x) + abs(ptPre.y - ptPost.y);
							if(nPointCount < tempDist[i])
								nPointCount = tempDist[i];
						}
						//	在每一段曲线上要拟合出的点数
						if (0 != nPointCount)
						{
							for (int i = 1; i <= m_BSplineSample.size() - 3; i++)
							{
								for ( int j = 0; j <= nPointCount; j++ )
								{
									double t  = 1.0 * j / nPointCount;
									double t2 = t*t;
									double t3 = t*t*t;
									
									double xPt = 1.0 / 6 * ( 1 - 3 * t + 3 * t2 - t3 ) * m_BSplineSample[i - 1].x + 1.0 / 6  * ( 4 - 6 * t2 + 3 * t3 ) *  m_BSplineSample[i].x + 1.0 / 6 * ( 1 + 3 * t + 3 * t2 - 3 * t3 ) * m_BSplineSample[ i + 1].x + 1.0 / 6 * t3 * m_BSplineSample[i+2].x;
									double yPt = 1.0 / 6 * ( 1 - 3 * t + 3 * t2 - t3 ) * m_BSplineSample[i - 1].y + 1.0 / 6  * ( 4 - 6 * t2 + 3 * t3 ) *  m_BSplineSample[i].y + 1.0 / 6 * ( 1 + 3 * t + 3 * t2 - 3 * t3 ) * m_BSplineSample[ i + 1].y + 1.0 / 6 * t3 * m_BSplineSample[i+2].y;
									
									CPoint pt;
									pt.x = xPt;
									pt.y = yPt;
									m_BSLineFill.push_back(pt);
								}
							}
						}
						CPoint startPtS, startPtF, endPtS, endPtF;
						startPtS.x = m_BSplineSample[0].x;
						startPtS.y = m_BSplineSample[0].y;
						endPtS.x = m_BSplineSample[m_BSplineSample.size() - 1].x;
						endPtS.y = m_BSplineSample[m_BSplineSample.size() - 1].y;
						startPtF.x = m_BSLineFill[0].x;
						startPtF.y = m_BSLineFill[0].y;
						endPtF.x = m_BSLineFill[m_BSLineFill.size() -1].x;
						endPtF.y = m_BSLineFill[m_BSLineFill.size() -1].y;
						int startStoFdist = max(abs(startPtF.x - startPtS.x), abs(startPtF.y - startPtS.y));
						int endFtoSdist = max(abs(endPtS.x - endPtF.x), abs(endPtS.y - endPtF.y));

						int xcoorb, ycoorb, xcoore, ycoore;
						CPoint strInsPt, endInsPt;
						if (0 != startStoFdist)
						{
							for(int indb = 0; indb <= startStoFdist; indb++)
							{
								xcoorb = startPtF.x - indb * (startPtF.x - startPtS.x) / startStoFdist;
								ycoorb = startPtF.y - indb * (startPtF.y - startPtS.y) / startStoFdist;
								strInsPt.x = xcoorb;
								strInsPt.y = ycoorb;
								m_BSLineFill.insert(m_BSLineFill.begin(), strInsPt);
							}
						}
						if (0 != endFtoSdist)
						{
							for(int inde = 0; inde <= endFtoSdist; inde++)
							{
								xcoore = endPtF.x + inde * (endPtS.x - endPtF.x) / endFtoSdist;
								ycoore = endPtF.y + inde * (endPtS.y - endPtF.y) / endFtoSdist;
								endInsPt.x = xcoore;
								endInsPt.y = ycoore;
								m_BSLineFill.push_back(endInsPt);
							}
						}
					}
				}
			}
		}
		break;
	case EDGE_OPERATION_CUT:
		{
			int dist = 0;
			int minDist = 1000;
			
			for(int i = 0; i != vecEdge.size(); ++i)
			{
				CPoint temp = vecEdge[i];
				dist = abs(temp.x - (point.x - rtBorder.left)) + abs(temp.y - (rtBorder.bottom - point.y));
				if (dist < minDist)
				{
					minDist = dist;
					m_BSplineInd = i;
				}
			}
			if (minDist < m_iEdgeSize)
			{
				::SetCursor(::LoadCursor(NULL,IDC_CROSS));
			}

			if (m_bLeftMouseDown && m_rStaPtOnEdge)
			{
				if(m_rtBorder.PtInRect(point))
				{
					m_rFillLine.clear();
					int distance = max(abs(m_rBtnPtSta.x - (point.x - m_rtBorder.left)), abs(m_rBtnPtSta.y - (m_rtBorder.bottom - point.y)));
					if(0 != distance)
					{
						CPoint fillpt;
						for(int strind = 0; strind <= distance; strind++)
						{
							fillpt.x = m_rBtnPtSta.x + strind * ((point.x - m_rtBorder.left) - m_rBtnPtSta.x) / distance;
							fillpt.y = m_rBtnPtSta.y + strind * ((m_rtBorder.bottom - point.y) - m_rBtnPtSta.y) / distance;
							m_rFillLine.push_back(fillpt);
						}
					}
				}
			}
		}
		break;
	default:
		break;
	}
}

void CEdgeInteraction::LButtonUp(CWnd* m_pWnd, CRect rtBorder, CPoint point, /*out*/vector<CPoint> &vecEdge)
{
	if (m_iEdgeOperationType == EDGE_OPERATION_NULL) 
	{
		return;
	}

	CRect clip;
	CPoint ptTLInner, ptBRInner;
	m_rtBorder = rtBorder;
	int radius = m_iBrushEraseRadius;
	m_ptBrushEraseCenter = point;
	ptTLInner.x = rtBorder.TopLeft().x + radius +1;
	ptTLInner.y = rtBorder.TopLeft().y + radius +1;
	ptBRInner.x = rtBorder.BottomRight().x - radius -1;
	ptBRInner.y = rtBorder.BottomRight().y - radius -1;
	clip.SetRect(ptTLInner,ptBRInner);

	switch(m_iEdgeOperationType) {
	case EDGE_OPERATION_BRUSH:
	case EDGE_OPERATION_ERASE:
		{
			if (m_byImageLayer && clip.PtInRect(point)) 
			{
				m_pWnd->BeginWaitCursor();
				m_bLeftMouseDown = FALSE;

				int i, index;
				int w, h;
				long lTissuePreviewArea, lTissueCurrentArea;
				vector<CPoint> vecSmoothEdgeBackup;
		
				//find new edge after LButtonDown
				vecEdge.clear();
				EdgeFind(vecEdge);
				EdgeOrder(vecEdge);
				
				//update m_ImageEdge.m_pTissueCurrent and initial pTissueTemp
				memset(m_byImageLayerCurrent, 255, sizeof(BYTE)*m_iImageLayerWidth*m_iImageLayerHeight);
				RegionFill(m_byImageLayerCurrent, m_iImageLayerWidth, m_iImageLayerHeight, vecEdge);

				BYTE *pTissueTemp = new BYTE[m_iImageLayerWidth*m_iImageLayerHeight];
				memcpy(pTissueTemp, m_byImageLayerCurrent, sizeof(BYTE)*m_iImageLayerWidth*m_iImageLayerHeight);

				//calculate lTissuePreviewArea and lTissueCurrentArea
				lTissuePreviewArea = 0; 
				lTissueCurrentArea = 0;
				for (h=0; h<m_iImageLayerHeight; h++)
				{
					for (w=0; w<m_iImageLayerWidth; w++)
					{
						if (*(m_byImageLayer + h*m_iImageLayerWidth + w) == 0) 
						{
							lTissuePreviewArea++;
						}
						if (*(m_byImageLayerCurrent + h*m_iImageLayerWidth + w) == 0) 
						{
							lTissueCurrentArea++;
						}
					}
				}

				//judgement condition
				if (lTissueCurrentArea == lTissuePreviewArea) 
				{
					vecEdge.clear();
					for (index=0; index<m_vecEdgeBackUp.size(); index++)
					{
						vecEdge.push_back(m_vecEdgeBackUp[index]);
					}
				}
				else
				{
					if (lTissueCurrentArea > lTissuePreviewArea)	//brush: current-preview
					{
						for (h=0; h<m_iImageLayerHeight; h++)
						{
							for (w=0; w<m_iImageLayerWidth; w++)
							{
								if (*(m_byImageLayer + h*m_iImageLayerWidth + w) == 0) 
								{
									*(pTissueTemp + h*m_iImageLayerWidth + w) = 255;
								}
							}
						}
					}
					else if (lTissueCurrentArea < lTissuePreviewArea)	//erase: preview-current
					{
						for (h=0; h<m_iImageLayerHeight; h++)
						{
							for (w=0; w<m_iImageLayerWidth; w++)
							{
								if (*(m_byImageLayer + h*m_iImageLayerWidth + w) == 0) 
								{
									if (*(pTissueTemp + h*m_iImageLayerWidth + w) == 0) 
									{
										*(pTissueTemp + h*m_iImageLayerWidth + w) = 255;
									}
									else if (*(pTissueTemp + h*m_iImageLayerWidth + w) == 255) 
									{
										*(pTissueTemp + h*m_iImageLayerWidth + w) = 0;
									}
								}
							}
						}
					}
					
					Dilate(pTissueTemp, m_iImageLayerWidth, m_iImageLayerHeight, 5, 5, FALSE);
					
					CPoint ptCurrent;
					vector<CPoint> *pVecPartContinuousEdge = NULL;
					vector<vector<CPoint> *> vecPartContinuousEdges;
					vector<bool> vecWhetherContinuous;
					vector<CPoint>::iterator iterPt;
					vector<vector<CPoint> *>::iterator iterPartContinuousEdges;
					vector<bool>::iterator iterWhetherContinuous;

					iterPt = vecEdge.begin();
					while (iterPt != vecEdge.end()) 
					{
						ptCurrent = *iterPt;
						if (*(pTissueTemp + ptCurrent.y*m_iImageLayerWidth + ptCurrent.x) == 0) 
						{
							pVecPartContinuousEdge = new vector<CPoint>;
							pVecPartContinuousEdge->push_back(ptCurrent);
							iterPt++;
							while (iterPt != vecEdge.end()) 
							{
								ptCurrent = *iterPt;
								if (*(pTissueTemp + ptCurrent.y*m_iImageLayerWidth + ptCurrent.x) != 0) 
								{
									vecPartContinuousEdges.push_back(pVecPartContinuousEdge);
									vecWhetherContinuous.push_back(false);
									break;
								}
								else
								{
									pVecPartContinuousEdge->push_back(ptCurrent);
									iterPt++;
								}
							}
							if (iterPt == vecEdge.end()) 
							{
								vecPartContinuousEdges.push_back(pVecPartContinuousEdge);
								vecWhetherContinuous.push_back(false);
							}
						}
						else
						{
							pVecPartContinuousEdge = new vector<CPoint>;
							pVecPartContinuousEdge->push_back(ptCurrent);
							iterPt++;
							while (iterPt != vecEdge.end()) 
							{
								ptCurrent = *iterPt;
								if (*(pTissueTemp + ptCurrent.y*m_iImageLayerWidth + ptCurrent.x) == 0) 
								{
									vecPartContinuousEdges.push_back(pVecPartContinuousEdge);
									vecWhetherContinuous.push_back(true);
									break;
								}
								else
								{
									pVecPartContinuousEdge->push_back(ptCurrent);
									iterPt++;
								}
							}
							if (iterPt == vecEdge.end()) 
							{
								vecPartContinuousEdges.push_back(pVecPartContinuousEdge);
								vecWhetherContinuous.push_back(true);
							}
						}
					}

					vecEdge.clear();
					for (iterPartContinuousEdges = vecPartContinuousEdges.begin(), 
						iterWhetherContinuous = vecWhetherContinuous.begin(); 
					iterPartContinuousEdges != vecPartContinuousEdges.end(); 
					iterPartContinuousEdges++, iterWhetherContinuous++)
					{
						if (!*iterWhetherContinuous) 
						{
							int iSmoothLenght = 11;
							if (iSmoothLenght > (*iterPartContinuousEdges)->size()) 
							{
								for (iterPt = (*iterPartContinuousEdges)->begin(); 
								iterPt != (*iterPartContinuousEdges)->end(); iterPt++)
								{
									ptCurrent = *iterPt;
									vecEdge.push_back(ptCurrent);
								}
							}
							else
							{
								int iLenght;
								CPoint ptStart, ptEnd, ptTemp;
								vector<CPoint> vecPtFront, vecPtMiddle, vecPtEnd;
								for (iterPt = (*iterPartContinuousEdges)->begin(), index=0; 
								iterPt != (*iterPartContinuousEdges)->end(); iterPt++, index++)
								{
									if(index >= iSmoothLenght/2 && 
										index < (*iterPartContinuousEdges)->size()-iSmoothLenght/2)
									{
										int iSumX = 0;
										int iSumY = 0;
										for (int i=-iSmoothLenght/2; i<=iSmoothLenght/2; i++)
										{
											iSumX += (*(iterPt + i)).x;
											iSumY += (*(iterPt + i)).y;
										}
										ptCurrent.x = iSumX/iSmoothLenght;
										ptCurrent.y = iSumY/iSmoothLenght;
										vecPtMiddle.push_back(ptCurrent);
									}
								}
								ptStart = *((*iterPartContinuousEdges)->begin());
								ptEnd = vecPtMiddle[0];
								iLenght = abs(ptStart.x - ptEnd.x) + abs(ptStart.y - ptEnd.y);
								if (iLenght == 0) 
								{
									;
								}
								else
								{
									for (i=0; i<=iLenght; i++)
									{
										ptTemp.x = ptStart.x + i*(ptEnd.x-ptStart.x)/iLenght;
										ptTemp.y = ptStart.y + i*(ptEnd.y-ptStart.y)/iLenght;
										vecPtFront.push_back(ptTemp);
										vecEdge.push_back(ptTemp);
									}
								}
								for (i=0; i<vecPtMiddle.size(); i++)
								{
									vecEdge.push_back(vecPtMiddle[i]);
								}
								ptStart = vecPtMiddle[vecPtMiddle.size()-1];
								ptEnd = *((*iterPartContinuousEdges)->end()-1);
								iLenght = abs(ptStart.x - ptEnd.x) + abs(ptStart.y - ptEnd.y);
								if (iLenght == 0) 
								{
									;
								}
								else
								{
									for (i=0; i<=iLenght; i++)
									{
										ptTemp.x = ptStart.x + i*(ptEnd.x-ptStart.x)/iLenght;
										ptTemp.y = ptStart.y + i*(ptEnd.y-ptStart.y)/iLenght;
										vecPtEnd.push_back(ptTemp);
										vecEdge.push_back(ptTemp);
									}
								}
							}
						}
						else
						{
							for (iterPt = (*iterPartContinuousEdges)->begin(); 
							iterPt != (*iterPartContinuousEdges)->end(); iterPt++)
							{
								ptCurrent = *iterPt;
								vecEdge.push_back(ptCurrent);
							}
						}
					}

					for (iterPartContinuousEdges = vecPartContinuousEdges.begin(); 
					iterPartContinuousEdges != vecPartContinuousEdges.end(); 
					iterPartContinuousEdges++)
					{
						if (*iterPartContinuousEdges) 
						{
							(*iterPartContinuousEdges)->clear();
							(*iterPartContinuousEdges) = NULL;
						}
					}
				}

				EdgeOrder(vecEdge);

				{//unlock the mouse
					UnLockMouse();
				}

				delete [] pTissueTemp;
				pTissueTemp = NULL;

				m_pWnd->EndWaitCursor();

				if (m_byImageLayer) 
				{
					delete [] m_byImageLayer;
					m_byImageLayer = NULL;
				}
				if (m_byImageLayerCurrent) 
				{
					delete [] m_byImageLayerCurrent;
					m_byImageLayerCurrent = NULL;
				}
			}
		}
		break;
	case EDGE_OPERATION_DRAW:
		{
			if(m_bLeftMouseDown && m_ptOnOrdEdge)
			{
				m_bLeftMouseDown = FALSE;
				if (m_BSLineFill.size() > 0) 
				{
					m_pWnd->BeginWaitCursor();
					//8个方向和起始扫描方向
					int Direction[8][2] = {{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0}};
					int BeginDirect;
					bool abnor = false;				//异常状态位
					CPoint startpt, endpt;
					
					std::list<CPoint> pixelList;
					
					startpt.x = m_BSLineFill[0].x;
					startpt.y = m_BSLineFill[0].y;
					endpt.x = m_BSLineFill[m_BSLineFill.size() - 1].x;
					endpt.y = m_BSLineFill[m_BSLineFill.size() - 1].y;
					vecEdge.push_back(startpt);
					pixelList.push_back(startpt);
					m_BSLineFill.erase(m_BSLineFill.begin());
					
					BeginDirect = 0;
					bool bFindEndpoint = false;
					std::list<CPoint>::iterator pos = pixelList.begin();
					while(pos != pixelList.end() && !bFindEndpoint)
					{
						CPoint pt;
						pt.x = (*pos).x;
						pt.y = (*pos).y;
						
						bool ptOnEdge = false;        // 边界点？
						int count = 0;		//对8邻域遍历情况计数
						while (!ptOnEdge)
						{
							int nX = pt.x + Direction[BeginDirect][0];
							int nY = pt.y + Direction[BeginDirect][1];
							
							CPoint newpt(nX,nY);
							if (nX == endpt.x && nY == endpt.y)	//找到结束点时结束
							{
								bFindEndpoint = true;
								pixelList.push_back(newpt);
								vecEdge.push_back(newpt);
								break;
							}
							
							std::vector<CPoint>::iterator iter = std::find(m_BSLineFill.begin(), m_BSLineFill.end(), newpt);
							if(iter != m_BSLineFill.end())
							{
								m_BSLineFill.erase(iter);
								pixelList.push_back(newpt);
								vecEdge.push_back(newpt);
								ptOnEdge = true;
								
								//为下次收索做准备，逆时针旋转90度
								BeginDirect--;
								if (BeginDirect == -1)
								{
									BeginDirect = 7;
								}
								BeginDirect--;
								if (BeginDirect == -1)
								{
									BeginDirect = 7;
								}
							}
							else
							{
								BeginDirect++;
								if (BeginDirect == 8)
								{
									BeginDirect = 0;
								}
								count++;
								if (count > 8)
								{
									vecEdge.clear();
									abnor = true;
									break;
								}
							}
						}
						pos++;
					}
					
					m_ptOnOrdEdge = false;		//Added by hiker 2007.12.26
					pixelList.clear();
					m_BSplineSample.clear();
					m_BSLineFill.clear();
					
					EdgeOrder(vecEdge);
					
					m_pWnd->EndWaitCursor();
				}
			}
			
			{//unlock the mouse
				UnLockMouse();
			}
		}
		break;
	case EDGE_OPERATION_CUT:
		{
			if (m_rtBorder.PtInRect(point) && m_rStaPtOnEdge && m_bLeftMouseDown)
			{
				m_pWnd->BeginWaitCursor();
				m_rFillLine.clear();
				m_rLineFill.clear();

				int dist = 0;
				int minDist = 1000;
				
				for(int i = 0; i < vecEdge.size(); ++i)
				{
					CPoint temp = vecEdge[i];
					dist = abs(temp.x - (point.x - m_rtBorder.left)) + abs(temp.y - (m_rtBorder.bottom - point.y));
					if (dist < minDist)
					{
						minDist = dist;
						m_rBtnPtEnd.x = temp.x;
						m_rBtnPtEnd.y = temp.y;
						m_rEndInd = i;
					}
				}
				if (minDist < m_iEdgeSize)
				{
					m_rEndPtOnEdge = true;
					if (m_rBtnPtSta.x == m_rBtnPtEnd.x && m_rBtnPtSta.y == m_rBtnPtEnd.y)
					{
						m_bLeftMouseDown = FALSE;
						m_rLineFill.clear();
						m_rStaPtOnEdge = false;
						m_rEndPtOnEdge = false;
					}
				}
				else
				{
					m_bLeftMouseDown = FALSE;
					m_rLineFill.clear();
					m_rStaPtOnEdge = false;
					m_rEndPtOnEdge = false;
				}

				if (m_rEndPtOnEdge)
				{	
					CPoint ptStart, ptEnd;
					vector<CPoint> vecSmoothEdgePart;
					vector<CPoint>::iterator iterPt, iterFindStart, iterFindEnd;
					m_bLeftMouseDown = FALSE;
					if (m_rStaInd > m_rEndInd)
					{
						int tempInd;
						CPoint tempPt;
						tempInd = m_rStaInd;
						m_rStaInd = m_rEndInd;
						m_rEndInd = tempInd;
						
						tempPt.x = m_rBtnPtSta.x;
						m_rBtnPtSta.x = m_rBtnPtEnd.x;
						m_rBtnPtEnd.x = tempPt.x;
						tempPt.y = m_rBtnPtSta.y;
						m_rBtnPtSta.y = m_rBtnPtEnd.y;
						m_rBtnPtEnd.y = tempPt.y;
					}
					
					int distance = max(abs(m_rBtnPtSta.x - m_rBtnPtEnd.x), abs(m_rBtnPtSta.y - m_rBtnPtEnd.y));
					CPoint fillpt;
					if (m_rEndInd - m_rStaInd <= vecEdge.size() / 2)
					{
						ptStart = vecEdge[m_rEndInd];
						ptEnd = vecEdge[m_rStaInd];
						iterFindStart = std::find(vecEdge.begin(), vecEdge.end(), ptStart);
						for (iterPt=iterFindStart; iterPt!=vecEdge.end(); iterPt++)
						{
							vecSmoothEdgePart.push_back(*iterPt);
						}
						iterFindEnd = std::find(vecEdge.begin(), vecEdge.end(), ptEnd);
						for (iterPt=vecEdge.begin(); iterPt!=iterFindEnd+1; iterPt++)
						{
							vecSmoothEdgePart.push_back(*iterPt);
						}

						for(int strind = 0; strind <= distance; strind++)	//start to end
						{
							fillpt.x = m_rBtnPtSta.x + strind * (m_rBtnPtEnd.x - m_rBtnPtSta.x) / distance;
							fillpt.y = m_rBtnPtSta.y + strind * (m_rBtnPtEnd.y - m_rBtnPtSta.y) / distance;
							m_rLineFill.push_back(fillpt);
						}
					}
					else
					{
						ptStart = vecEdge[m_rStaInd];
						ptEnd = vecEdge[m_rEndInd];
						iterFindStart = std::find(vecEdge.begin(), vecEdge.end(), ptStart);
						iterFindEnd = std::find(vecEdge.begin(), vecEdge.end(), ptEnd);
						for (iterPt=iterFindStart; iterPt!=iterFindEnd+1; iterPt++)
						{
							vecSmoothEdgePart.push_back(*iterPt);
						}
						
						for(int strind = 0; strind <= distance; strind++)	//end to start
						{
							fillpt.x = m_rBtnPtEnd.x + strind * (m_rBtnPtSta.x - m_rBtnPtEnd.x) / distance;
							fillpt.y = m_rBtnPtEnd.y + strind * (m_rBtnPtSta.y - m_rBtnPtEnd.y) / distance;
							m_rLineFill.push_back(fillpt);
						}
					}

					if (vecEdge.size() > 50) 
					{
						int iLength;
						int iSmoothLenght = 11;
						CPoint ptTemp;
						vector<CPoint> vecPtTemp, vecSmooth;
						for (iterPt=vecSmoothEdgePart.end()-iSmoothLenght/2*2; iterPt!=vecSmoothEdgePart.end(); iterPt++)
						{
							vecPtTemp.push_back(*iterPt);
						}
						for (iterPt=m_rLineFill.begin(); iterPt!=m_rLineFill.end(); iterPt++)
						{
							vecPtTemp.push_back(*iterPt);
						}
						for (iterPt=vecSmoothEdgePart.begin(); iterPt!=vecSmoothEdgePart.begin()+iSmoothLenght/2*2+1; iterPt++)
						{
							vecPtTemp.push_back(*iterPt);
						}
						m_rLineFill = vecPtTemp;
						vecSmoothEdgePart.erase(vecSmoothEdgePart.begin(), vecSmoothEdgePart.begin()+5);
						vecSmoothEdgePart.erase(vecSmoothEdgePart.end()-5, vecSmoothEdgePart.end());

						for (iterPt = m_rLineFill.begin()+iSmoothLenght/2; 
						iterPt != m_rLineFill.end()-iSmoothLenght/2; iterPt++)
						{
							int iSumX = 0;
							int iSumY = 0;
							for (int i=-iSmoothLenght/2; i<=iSmoothLenght/2; i++)
							{
								iSumX += (*(iterPt + i)).x;
								iSumY += (*(iterPt + i)).y;
							}
							ptTemp.x = iSumX/iSmoothLenght;
							ptTemp.y = iSumY/iSmoothLenght;
							vecSmooth.push_back(ptTemp);
						}
							

						ptStart = m_rLineFill[0];
						ptEnd = vecSmooth[0];
						iLength = abs(ptStart.x - ptEnd.x) + abs(ptStart.y - ptEnd.y);
						for (i=0; i<=iLength; i++)
						{
							ptTemp.x = ptStart.x + i*(ptEnd.x-ptStart.x)/iLength;
							ptTemp.y = ptStart.y + i*(ptEnd.y-ptStart.y)/iLength;
							vecSmoothEdgePart.push_back(ptTemp);
						}
						for (i=0; i<vecSmooth.size(); i++)
						{
							vecSmoothEdgePart.push_back(vecSmooth[i]);
						}
						ptStart = vecSmooth[vecSmooth.size()-1];
						ptEnd = m_rLineFill[m_rLineFill.size()-1];
						iLength = abs(ptStart.x - ptEnd.x) + abs(ptStart.y - ptEnd.y);
						for (i=0; i<=iLength; i++)
						{
							ptTemp.x = ptStart.x + i*(ptEnd.x-ptStart.x)/iLength;
							ptTemp.y = ptStart.y + i*(ptEnd.y-ptStart.y)/iLength;
							vecSmoothEdgePart.push_back(ptTemp);
						}

						vecEdge = vecSmoothEdgePart;
					}

					m_rLineFill.clear();
					m_rStaPtOnEdge = false;				//Added by hiker 2008.01.03
					m_rEndPtOnEdge = false;				//Added by hiker 2008.01.03

					EdgeOrder(vecEdge);
				}

				UnLockMouse();
				m_pWnd->EndWaitCursor();
			}
		}
		break;
	default:
		break;
	}
}

BOOL CEdgeInteraction::RegionFill(BYTE *pTissue, int width, int height, vector<CPoint>& vectEdge)
{
	int i, j;
	CPoint pt, tempPt;
	int edgeCnt = vectEdge.size();

	CRect rtRegionEx(0, 0, width-1+2, height-1+2);	//上下左右各扩展一个像素
	BYTE* pRegionEx = new BYTE[(rtRegionEx.Width()+1)*(rtRegionEx.Height()+1)];
	memset(pRegionEx, 0, sizeof(BYTE)*(rtRegionEx.Width()+1)*(rtRegionEx.Height()+1));

	vector<CPoint>	vecEdgeEx;
	for (i=0; i!=edgeCnt; i++)
	{
		pt.x = vectEdge[i].x + 1;
		pt.y = vectEdge[i].y + 1;
		vecEdgeEx.push_back(pt);
	}
	
	vector<CPoint> vectPts;
	vectPts.push_back(rtRegionEx.BottomRight());
	
	while (vectPts.size() > 0) 
	{
		pt.x = vectPts[vectPts.size() - 1].x;
		pt.y = vectPts[vectPts.size() - 1].y;
		vectPts.pop_back();
		*(pRegionEx + pt.y*width+pt.x) = (BYTE)255;
		if (pt.x > rtRegionEx.TopLeft().x)
		{
			tempPt.x = pt.x - 1;
			tempPt.y = pt.y;
			int ibyte = *(pRegionEx + tempPt.y*width+tempPt.x);
			if((0 == *(pRegionEx + tempPt.y*width+tempPt.x)) &&
				(std::find(vecEdgeEx.begin(), vecEdgeEx.end(), tempPt) == vecEdgeEx.end()))
			{
				vectPts.push_back(tempPt);
			}
		}
		if (pt.y > rtRegionEx.TopLeft().y)
		{
			tempPt.x = pt.x;
			tempPt.y = pt.y - 1;
			if((0 == *(pRegionEx + tempPt.y*width+tempPt.x)) &&
				(std::find(vecEdgeEx.begin(), vecEdgeEx.end(), tempPt) == vecEdgeEx.end()))
			{
				vectPts.push_back(tempPt);
			}
		}
		if (pt.x < rtRegionEx.BottomRight().x)
		{
			tempPt.x = pt.x + 1;
			tempPt.y = pt.y;
			if((0 == *(pRegionEx + tempPt.y*width+tempPt.x)) &&
				(std::find(vecEdgeEx.begin(), vecEdgeEx.end(), tempPt) == vecEdgeEx.end()))
			{
				vectPts.push_back(tempPt);
			}
		}
		if (pt.y < rtRegionEx.BottomRight().y)
		{
			tempPt.x = pt.x;
			tempPt.y = pt.y + 1;
			if((0 == *(pRegionEx + tempPt.y*width+tempPt.x)) &&
				(std::find(vecEdgeEx.begin(), vecEdgeEx.end(), tempPt) == vecEdgeEx.end()))
			{
				vectPts.push_back(tempPt);
			}
		}
	}

	for (j=0; j<height; j++)
	{
		for (i=0; i<width; i++)
		{
			*(pTissue + j*width+i) = *(pRegionEx + (j+1)*width+i+1);
		}
	}

	delete [] pRegionEx;
	pRegionEx = NULL;
	
	return TRUE;
}

BOOL CEdgeInteraction::LaplacianEN(BYTE *pImage, int width, int height)
{
	long lWidth, lHeight;
	long gray = 0;
	BYTE* pImageLap = new BYTE[width*height];
	memcpy(pImageLap, pImage, sizeof(BYTE)*width*height);
	for (lHeight=1; lHeight<height-1; lHeight++)
	{
		for (lWidth=1; lWidth<width-1; lWidth++)
		{
			gray = (long)(*(pImage + (lHeight-1)*width+(lWidth-1))) + (long)(*(pImage + lHeight*width+(lWidth-1))) + (long)(*(pImage + (lHeight+1)*width+(lWidth-1)))
				+(long)(*(pImage + (lHeight-1)*width+lWidth)) - 8*(long)(*(pImage + lHeight*width+lWidth)) + (long)(*(pImage + (lHeight+1)*width+lWidth))
				+(long)(*(pImage + (lHeight-1)*width+(lWidth+1))) + (long)(*(pImage + lHeight*width+(lWidth+1))) + (long)(*(pImage + (lHeight+1)*width+(lWidth+1)));
			
			if (gray<10) 
			{
				*(pImageLap + lHeight*width+lWidth) = (BYTE)255;
			}
			else
			{
				*(pImageLap + lHeight*width+lWidth) = (BYTE)0;
			}
		}
	}
	memcpy(pImage, pImageLap, sizeof(BYTE)*width*height);
	delete [] pImageLap;
	pImageLap = NULL;
	return TRUE;
}

BOOL CEdgeInteraction::EdgeFind(vector<CPoint> &vecEdge)
{
	CMatrix<int> matrix(m_iImageLayerWidth, m_iImageLayerHeight);   // 记录图像遍历状态（0 -未遍历 1-已遍历）
	vector<vector<CPoint> *> m_vecEdges;
	
	for(int xroll = 0; xroll < m_iImageLayerWidth;  xroll++)
	{
		for(int yroll = 0; yroll < m_iImageLayerHeight; ++ yroll)
		{
			BYTE *pPixel = (m_byImageLayerCurrent + yroll * m_iImageLayerWidth + xroll);
			if(!(*pPixel) && !(matrix[xroll][yroll]))	// The point is dark and unused
			{
				vector<CPoint> *m_pvecEdgeTemp = new vector<CPoint>;
				std::list<CPoint> pixelList;
				
				// 起点加入表中
				CPoint pt(xroll, yroll);
				
				pixelList.push_back(pt);
				matrix[xroll][yroll] = 1;
				
				std::list<CPoint>::iterator pos = pixelList.begin();
				while(pos != pixelList.end())   // 搜索邻域
				{
					CPoint pt;
					pt.x = (*pos).x;
					pt.y = (*pos).y;
					
					bool ptOnEdge = false;        // 边界点？
					
					for(int xloop = -1; xloop < 2; ++ xloop)
					{
						for(int yloop = -1; yloop < 2; ++ yloop)
						{
							if((xloop == 0) && (yloop == 0))
							{
								continue;
							}
							
							int nX = pt.x + xloop;
							int nY = pt.y + yloop;
							
							if((nX < 0) || (nY < 0) || (nX >= m_iImageLayerWidth) || (nY >= m_iImageLayerHeight)) // 越界无效
							{
								continue;
							}
							
							BYTE *pCurr = m_byImageLayerCurrent + nY * m_iImageLayerWidth + nX;
							
							if(!(*pCurr) && !(matrix[nX][nY]))
							{
								CPoint p(nX, nY);
								// Check to make sure the point is not already in the list
								// This is time consuming and need to be improved
								// Another way is to add the points and then remove them from list later
								//
								if(std::find(pixelList.begin(), pixelList.end(), p) == pixelList.end())
								{
									// make sure the point is on the edge
									if(PtOnEdge(m_byImageLayerCurrent, m_iImageLayerWidth, m_iImageLayerHeight, nX, nY))
									{
										pixelList.push_back(p);
										ptOnEdge = true;
									}
								}
								
								matrix[nX][nY] = 1;
							}
							else
							{
								ptOnEdge = true;
							}
						}
					}
					
					if(ptOnEdge)
					{
						m_pvecEdgeTemp->push_back(pt);
					}
					++ pos;
				}
				if(m_pvecEdgeTemp->size() > 5)            // 边界大于10个像素的保存
				{
					m_vecEdges.push_back(m_pvecEdgeTemp);
					
					m_pvecEdgeTemp = NULL;
				}
				else
				{
					m_pvecEdgeTemp->clear();
					delete m_pvecEdgeTemp;
					m_pvecEdgeTemp = NULL;
				}
				pixelList.clear();
			}
		}
	}

	FindLongestEdge(m_vecEdges, vecEdge);

	return TRUE;
}

BOOL CEdgeInteraction::FindLongestEdge(vector<vector<CPoint> *> &vecEdges, vector<CPoint> &vecEdge)
{
	vecEdge.clear();

	if(vecEdges.size() != 0)
	{
		int edgeNum = vecEdges.size();
		int iMax = 0;
		vector<CPoint> *tmpedge = NULL;
		for(int roll = 0; roll < edgeNum; ++ roll)
		{
			vector<CPoint> *edge = vecEdges[roll];
			if (iMax < edge->size())
			{
				iMax = edge->size();
				tmpedge = edge;
			}
		}
		if (tmpedge)
		{
			for(int loop = 0; loop < tmpedge->size(); ++ loop)
			{
				POINT pt = tmpedge->operator[](loop);
				vecEdge.push_back(pt);
			}
		}
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CEdgeInteraction::PtOnEdge(BYTE *pImage, int width, int height, int xPos, int yPos)
{
	for(int xloop = -1; xloop < 2; ++ xloop)
	{
		for(int yloop = -1; yloop < 2; ++ yloop)
		{
			if((xloop == 0) && (yloop == 0))
			{
				continue;
			}
			
			int nX = xPos + xloop;
			int nY = yPos + yloop;
			
			if((nX < 0) || (nY < 0) || (nX >= width) || (nY >= height))
			{
				continue;
			}
			
			BYTE *pCurr = pImage + nY * width + nX;
			
			if(*pCurr)
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CEdgeInteraction::Dilate(BYTE *pImage, int width, int height, int nTempWidth, int nTempHeight, BOOL square)
{
	LPBYTE	lpSrc;			// 指向源图像的指针	
	LPBYTE	lpDst;			// 指向缓存图像的指针	
	
	long i,j,n,m;			//循环变量
	unsigned char pixel;	//像素值
	
	LPBYTE temp=new BYTE[width*height];
	
	if (temp == NULL)
	{
		return false;
	}
	
	// 初始化新分配的内存，设定初始值为255
	lpDst = temp;
	memset(lpDst, (BYTE)255, width * height);
	
	//使用自定义的结构元素进行膨胀
	for(j = nTempHeight / 2; j <height- nTempHeight / 2; j++)
	{
		for(i = nTempWidth / 2;i <width-nTempWidth / 2; i++)
		{
			// 由于使用n×n的结构元素，为防止越界，所以不处理最左边和最右边
			// 的两列像素和最上边和最下边的两列像素
			
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = pImage + width * j + i;
			// 指向目标图像倒数第j行，第i个象素的指针			
			lpDst = temp + width * j + i;
			//取得当前指针处的像素值，注意要转换为unsigned char型
			pixel = (unsigned char)*lpSrc;
			
			//目标图像中含有0和255外的其它灰度值
			if(pixel != 255 && *lpSrc != 0)
			{
				delete [] temp;
				return FALSE;
			}
			
			//目标图像中的当前点先赋成黑色
			*lpDst = 255;
			
			//如果原图像中对应结构元素中的那些点中有一个是黑色，
			//则将目标图像中的当前点赋成黑色，注意在DIB图像中内
			//容是上下倒置的
			if(square)
			{
				for (m = -1;m < 2;m++ )
				{
					for (n = -1;n < 2;n++)
					{
						
						pixel = *(lpSrc + m*width + n);
						if (pixel == 255 )
						{	
							*lpDst = (unsigned char)255;
							break;
						}
					}
				}
			}
			else
			{
				int radius = nTempHeight / 2;
				for (m = -nTempHeight / 2;m <= nTempHeight / 2;m++ )
				{
					for (n = -nTempWidth / 2;n <= nTempWidth / 2;n++)
					{
						int dis = (int)sqrt(m * m + n * n);
						
						if(dis <= radius)
						{
							// 在圆内
							pixel = *(lpSrc + m*width + n);
							if (pixel == 0 )
							{	
								*lpDst = (unsigned char)0;
								break;
							}
						}
					}
				}
			}			
		}
	}
	// 复制膨胀后的图像
	memcpy(pImage, temp, width * height);
	delete [] temp;
	temp=NULL;
	
	return true;
}

void CEdgeInteraction::EdgeOrder(vector<CPoint> &vecEdge)
{
	vector<CPoint> vecTemp;

	//8个方向和起始扫描方向
	int Direction[8][2] = {{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0}};
	int BeginDirect;
	int startx, starty;
	
	std::list<CPoint> pixelList;
	bool bFindStartpoint = false;
	for(int xroll = 0; xroll < m_iImageLayerWidth && !bFindStartpoint;  xroll++)
	{
		for(int yroll = 0; yroll < m_iImageLayerHeight && !bFindStartpoint; ++ yroll)
		{
			CPoint p(xroll, yroll);
			if(std::find(vecEdge.begin(), vecEdge.end(), p) != vecEdge.end())
			{
				startx = xroll;
				starty = yroll;
				bFindStartpoint = true;
				vecTemp.push_back(p);
				pixelList.push_back(p);
			}
		}
	}
	
	bool bFindStartpt = false;
	BeginDirect = 0;
	//	std::vector<CPoint>::iterator pos = m_OrderedEdge.begin();
	std::list<CPoint>::iterator pos = pixelList.begin();
	while(pos != pixelList.end() && !bFindStartpt)
	{
		bFindStartpt = false;
		CPoint pt;
		pt.x = (*pos).x;
		pt.y = (*pos).y;
		
		bool ptOnEdge = false;        // 边界点？
		int count = 0;		//对8邻域遍历情况计数
		while (!ptOnEdge)
		{
			int nX = pt.x + Direction[BeginDirect][0];
			int nY = pt.y + Direction[BeginDirect][1];
			
			if((nX < 0) || (nY < 0) || (nX >= m_iImageLayerWidth) || (nY >= m_iImageLayerHeight)) // 越界无效
			{
				BeginDirect++;
				if (BeginDirect == 8)
				{
					BeginDirect = 0;
				}
				count++;
				continue;
			}
			if (nX == startx && nY == starty)	//回到起点时结束
			{
				bFindStartpt = true;
				break;
			}
			
			CPoint newpt(nX,nY);			
			if(std::find(vecEdge.begin(), vecEdge.end(), newpt) != vecEdge.end())
			{				
				vecTemp.push_back(newpt);
				pixelList.push_back(newpt);
				ptOnEdge = true;
				
				//为下次收索做准备，逆时针旋转90度
				BeginDirect--;
				if (BeginDirect == -1)
				{
					BeginDirect = 7;
				}
				BeginDirect--;
				if (BeginDirect == -1)
				{
					BeginDirect = 7;
				}
			}
			else
			{
				BeginDirect++;
				if (BeginDirect == 8)
				{
					BeginDirect = 0;
				}
				count++;
				ptOnEdge = false;
			}
			if (count == 8)
				break;
		}
		pos++;
	}
	vecEdge = vecTemp;
}

void CEdgeInteraction::UnLockMouse()
{
	int pixelX = GetSystemMetrics(SM_CXSCREEN);
	int pixelY = GetSystemMetrics(SM_CYSCREEN);	//取得屏幕的大小
	
	RECT Rect;
	BOOL bLock;
	Rect.left=0;//设置锁定区域大小；
	Rect.top=0;
	Rect.right=pixelX;
	Rect.bottom=pixelY;
	bLock = ClipCursor(&Rect);
}

void CEdgeInteraction::RePaint(CWnd *pWnd)
{
	CClientDC dc(pWnd);
	
	switch(m_iEdgeOperationType) {
	case EDGE_OPERATION_BRUSH:
		{
			CPen penGreen(PS_SOLID, 1, RGB(0,255,0));
			CPen *pOldPen = dc.SelectObject(&penGreen);
			CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
			CBrush *pOldBrush = dc.SelectObject(pBrush);
			if (m_bMouseInROI) 
			{
				int radius = m_iBrushEraseRadius;
				CPoint ptCenter = m_ptBrushEraseCenter;
				dc.Ellipse(	ptCenter.x-radius, 
							ptCenter.y-radius, 
							ptCenter.x+radius, 
							ptCenter.y+radius);
				dc.MoveTo(ptCenter.x-radius/2, ptCenter.y);
				dc.LineTo(ptCenter.x+radius/2, ptCenter.y);
				dc.MoveTo(ptCenter.x, ptCenter.y-radius/2);
				dc.LineTo(ptCenter.x, ptCenter.y+radius/2);
			}
			dc.SelectObject(pOldPen);
			dc.SelectObject(pOldBrush);
		}
		break;
	case EDGE_OPERATION_ERASE:
		{
			CPen penRed(PS_SOLID, 1, RGB(255,0,0));
			CPen *pOldPen = dc.SelectObject(&penRed);
			CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
			CBrush *pOldBrush = dc.SelectObject(pBrush);
			if (m_bMouseInROI) 
			{
				int radius = m_iBrushEraseRadius;
				CPoint ptCenter = m_ptBrushEraseCenter;
				dc.Ellipse(ptCenter.x-radius, ptCenter.y-radius, ptCenter.x+radius, ptCenter.y+radius);
				dc.MoveTo(ptCenter.x-radius/2, ptCenter.y);
				dc.LineTo(ptCenter.x+radius/2, ptCenter.y);
			}
			dc.SelectObject(pOldPen);
			dc.SelectObject(pOldBrush);
		}
		break;
	case EDGE_OPERATION_DRAW:
		{
			if (m_BSLineFill.size() > 0)
			{
				for(int temploop = 0; temploop < m_BSLineFill.size(); ++ temploop)
				{
					POINT temppt = m_BSLineFill[temploop];
					dc.SetPixel(m_rtBorder.left + temppt.x, m_rtBorder.bottom - temppt.y, RGB(0, 255, 0));
				}
			}
		}
		break;
	case EDGE_OPERATION_CUT:
		{
			if (m_rFillLine.size() > 0)
			{
				for(int temploop = 0; temploop < m_rFillLine.size(); ++ temploop)
				{
					CPoint temppt = m_rFillLine[temploop];
					dc.SetPixel(m_rtBorder.left + temppt.x, m_rtBorder.bottom - temppt.y, RGB(0, 255, 0));
				}
			}
		}
		break;
	default:
		break;
	}

	pWnd->ReleaseDC(&dc);
}
