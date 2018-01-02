/*************************************************************************
 * Copyright (C) 2004
 *
 * Chart.h
 * Descr.   : Draw chart
 * Version  : 0.1
 * Author   : G.M. Wu
 * Date     : Nov. 27 2004
 *
 * Modify   :
 *
 *************************************************************************/
#ifndef _GMCHART_H
#define _GMCHART_H
//#include"stdafx.h"
#include <afxwin.h>
#include <math.h>
#include"vector"

#define DEFAULT_LEFT_BORDER   75 // pixels
#define DEFAULT_RIGHT_BORDER  25
#define DEFAULT_TOP_BORDER    25
#define DEFAULT_BOTTOM_BORDER 25

/*************************************************************************
 * Type definition
 *************************************************************************/
// 2-D Point
template<class TX, class TY>
class T2DPoint
{
public :
	TX  X;
	TY  Y;
	
    T2DPoint(TX XVal, TY YVal) : X(XVal), Y(YVal) {}
};

// Pair
#define TPair(TX, TY) T2DPoint<TX, TY> 

/*************************************************************************
 * C2DChart - 2-Dimension Chart 
 *************************************************************************/
class C2DChart
{
public :
	std::vector<CString>m_vMsgLisk;
	enum DRAWTYPE 
	{
		DT_BYXY,   // all data provided by user
		DT_BYY,	   // only y values provided
	};

	enum PLOTSTYLE
	{
		PS_CHART_DOT,   
		PS_CHART_SOLIDLINE,
	};
	
	// AXIS Enum
	enum AXIS {XAXIS, YAXIS, ZAXIS};

	C2DChart();
	C2DChart(CWnd *pOwner);
	~C2DChart();

	// set plot window
	void setOwner(CWnd *pOwner);
	// set origin position
	void setOrigin(double OriginX, double OriginY);
	// set X range
	void setXRange(double XMin, double XMax);
	// set Y range 
	void setYRange(double YMin, double YMax);
	// set division
	void setDivs(UINT nXDiv, UINT nYDiv);
	// set increase
	void setIncs(double XInc, double YInc);
	// set auto range control
	void setAutoRange(AXIS axis, bool bAuto);
	// set auto grid display
	void setAutoGrid(AXIS axis, bool bAuto);
	// set title
	void setTitle(CString strTitle);
	// set background color
	void setBGColor(COLORREF color);
	// get Y range
	void getYRange(double& YMin, double& YMax);

	// get value by position on the screen 
	double getValue(UINT iPos, AXIS axis);

	// plot 
	void plot(double *pXValues, double *pYValues, UINT nCount, UINT nLines=1, PLOTSTYLE style = PS_CHART_SOLIDLINE);
	void plot(double *pYValues, UINT nCount, UINT nLines=1, PLOTSTYLE style = PS_CHART_SOLIDLINE);
	// draw coordinates
	void drawCoordinates(CDC *pDC, CRect *pRect);
	// draw
	void draw(void);
protected :
private :
	CWnd					 *m_pOwner;     // pointer to Owner window
	COLORREF				 m_BGColor;		// background color
	DRAWTYPE				 m_DrawType;    // draw type
	PLOTSTYLE                m_PlotStyle;   // plot style

	T2DPoint<double, double> m_Origin;      // Origin position
	T2DPoint<double, double> m_ReferLine;   // reference line
	TPair(double, double)    m_XRange;      // Display range of X axis
	TPair(double, double)    m_YRange;      // Display range of Y axis
	TPair(UINT, UINT)  		 m_Div;		    // Division of X and Y axis
	TPair(double, double)    m_Inc;			// increase of X and Y axis
	TPair(bool, bool)		 m_IsAutoRange; // can auto control the range of X and Y axis or not
	TPair(bool, bool)        m_IsAutoGrid;  // auto grid for X and Y axis
	TPair(double, double)    m_Unit;		// value per pixel

	CString				     m_strTitle;    // Title
	double					 *m_pXValues;	// X Values
	double					 *m_pYValues;	// Y Values
	UINT                     m_nCount;      // count of data pairs
	UINT                     m_nLines;      // how many lines

	// get maximum and minimum value from an array
	TPair(double, double) getMaxMinValue(double *pValues, UINT nCount);
};

#endif