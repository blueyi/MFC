#include "stdafx.h"
#include "Chart.h"

int round(double x) 
{
	double fCeil  = ceil(x);
	double fFloor = floor(x);
	int iResult = (int)(((x - fFloor) > 0.5) ? fCeil : fFloor);
	return iResult;
}

/***********************************************************************
 * Implementation of class C2DChart
 ***********************************************************************/
/***
 * Message map
 ***/

/***
 * public member-ship functions
 ***/
C2DChart::C2DChart() : m_pOwner(NULL), m_Origin(0., 0.), m_ReferLine(0., 0.), m_XRange(0., 100.), 
	m_YRange(0., 100.), m_Div(10, 10), m_Inc(10., 10.), m_IsAutoRange(true, true), m_IsAutoGrid(false, false), 
	m_BGColor(RGB(0,0,0)), m_Unit(1, 1)
{
	m_strTitle = "No Graph";
	m_pXValues = NULL;
	m_pYValues = NULL;
	m_nCount   = 0;
}

// default constructor
C2DChart::C2DChart(CWnd *pOwner) : m_pOwner(pOwner), m_Origin(0., 0.), m_ReferLine(0., 0.), m_XRange(0., 100.), 
	m_YRange(0., 100.), m_Div(10, 10), m_Inc(10., 10.), m_IsAutoRange(true, true), m_IsAutoGrid(false, false), 
	m_BGColor(RGB(0,0,0)), m_Unit(1, 1)
{
	m_strTitle = "No Graph";
	m_pXValues = NULL;
	m_pYValues = NULL;
	m_nCount   = 0;
}

// destructor
C2DChart::~C2DChart()
{
}

// set plot window
void C2DChart::setOwner(CWnd *pOwner)
{
	m_pOwner = pOwner;
}

// plot
void C2DChart::plot(double *pXValues, double *pYValues, UINT nCount, UINT nLines, PLOTSTYLE style)
{
	if((pXValues == NULL) || (pYValues == NULL))
	{
		m_nCount = 0;
		return;
	}
	m_pXValues = pXValues;
	m_pYValues = pYValues;
	m_nCount   = nCount;
	m_nLines   = nLines;
	long totalCount = nCount * nLines;
	
	// caculate 
	if(m_IsAutoRange.X)	
	{
		m_XRange = getMaxMinValue(pXValues, totalCount);
		m_Inc.X  = (m_XRange.Y - m_XRange.X) / m_Div.X;
	}
	if(m_IsAutoRange.Y) 
	{
		m_YRange = getMaxMinValue(pYValues, totalCount);
		if(1. * (m_YRange.Y - m_YRange.X) <= 0.1 * fabs(m_YRange.Y))
		{
			m_YRange.Y += 1;
			m_YRange.X -= 1;
		}
		m_Inc.Y  = (m_YRange.Y - m_YRange.X) / m_Div.Y;
	}
	m_DrawType  = DT_BYXY;
	m_PlotStyle = style;

	if(m_pOwner == NULL) return;

	// caculate units
	CRect rectClient;
	m_pOwner->GetClientRect(&rectClient);
	m_Unit.X = m_Inc.X * m_Div.X / (rectClient.Width() - DEFAULT_LEFT_BORDER - DEFAULT_RIGHT_BORDER);
	m_Unit.Y = m_Inc.Y * (m_Div.Y + 2) / (rectClient.Height() - DEFAULT_TOP_BORDER - DEFAULT_BOTTOM_BORDER);

	draw();
}

void C2DChart::plot(double *pYValues, UINT nCount, UINT nLines, PLOTSTYLE style)
{
	if(pYValues == NULL)
	{
		m_nCount = 0;
		return;
	}
	m_pYValues = pYValues;
	m_nCount   = nCount;
	m_nLines   = nLines;
	long totalCount = nCount * nLines;
	
	// caculate 
	if(m_IsAutoRange.X)	
	{ 
		m_XRange.X = 0; 
		m_XRange.Y = (double)nCount; 
		m_Inc.X  = (m_XRange.Y - m_XRange.X) / m_Div.X;
	}
	if(m_IsAutoRange.Y)	
	{
		m_YRange = getMaxMinValue(pYValues, totalCount);
		if(1. * (m_YRange.Y - m_YRange.X) <= 0.1 * fabs(m_YRange.Y))
		{
			m_YRange.Y += 1;
			m_YRange.X -= 1;
		}
		m_Inc.Y  = (m_YRange.Y - m_YRange.X) / m_Div.Y;
	}
	m_DrawType = DT_BYY;
	m_PlotStyle = style;

	if(m_pOwner == NULL) return;

	// caculate units
	CRect rectClient;
	m_pOwner->GetClientRect(&rectClient);
	m_Unit.X = m_Inc.X * m_Div.X / (rectClient.Width() - DEFAULT_LEFT_BORDER - DEFAULT_RIGHT_BORDER);
	m_Unit.Y = m_Inc.Y * (m_Div.Y + 2) / (rectClient.Height() - DEFAULT_TOP_BORDER - DEFAULT_BOTTOM_BORDER);

	draw();
}

// draw coordinates
void C2DChart::drawCoordinates(CDC *pDC, CRect *pRect)
{
	pDC->DrawText(m_strTitle, pRect, DT_CENTER | DT_TOP);

	CRect rect;
	CString strLabel;
	UINT nInc;
	double fVal;
	UINT nLoop;
	CPen Pen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *pOldPen =	pDC->SelectObject(&Pen);
	CFont font;
	VERIFY(font.CreateFont(
		13,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		"Arial"));                 // lpszFacename
	pDC->SelectObject(&font);

	// draw Y labels
	nInc = round(1. * (pRect->Height() - DEFAULT_TOP_BORDER - DEFAULT_BOTTOM_BORDER)/(m_Div.Y + 2));
	for(nLoop = 1; nLoop < m_Div.Y + 2; nLoop ++)
	{
		fVal        = m_YRange.Y - m_Inc.Y * (nLoop - 1);
		rect.left	= 0;
		rect.right	= DEFAULT_LEFT_BORDER;
		rect.bottom = DEFAULT_TOP_BORDER + nInc * nLoop;
		rect.top	= rect.bottom - 15;
		strLabel.Format("%.2f", fVal);
		pDC->DrawText(strLabel, &rect, DT_RIGHT | DT_BOTTOM);
		pDC->MoveTo(rect.right, rect.bottom);
		pDC->LineTo(pRect->right - DEFAULT_RIGHT_BORDER, rect.bottom);
	}	
	// draw X labels
	nInc = round(1. * (pRect->Width() - DEFAULT_LEFT_BORDER - DEFAULT_RIGHT_BORDER)/m_Div.X);
	for(nLoop = 0; nLoop <= m_Div.X; nLoop ++)
	{
		fVal        = m_XRange.X + m_Inc.X * nLoop;
		rect.left	= 0;
		rect.right	= DEFAULT_LEFT_BORDER + nInc * nLoop;
		rect.bottom = pRect->bottom;
		rect.top	= rect.bottom - DEFAULT_BOTTOM_BORDER;
		strLabel.Format("%d", (int)fVal);
		pDC->DrawText(strLabel, &rect, DT_RIGHT | DT_BOTTOM);
		pDC->MoveTo(rect.right, rect.top);
		pDC->LineTo(rect.right, DEFAULT_TOP_BORDER);
	}	
	Pen.DeleteObject(); 
	font.DeleteObject();
	pDC->SelectObject(pOldPen);

	// draw outter frame
	pDC->MoveTo(DEFAULT_LEFT_BORDER, DEFAULT_TOP_BORDER);
	pDC->LineTo(DEFAULT_LEFT_BORDER, pRect->bottom - DEFAULT_BOTTOM_BORDER);
	pDC->LineTo(pRect->right - DEFAULT_RIGHT_BORDER, pRect->bottom - DEFAULT_BOTTOM_BORDER);
	pDC->LineTo(pRect->right - DEFAULT_RIGHT_BORDER, pRect->bottom - DEFAULT_BOTTOM_BORDER);
	pDC->LineTo(pRect->right - DEFAULT_RIGHT_BORDER, DEFAULT_TOP_BORDER);
	pDC->LineTo(DEFAULT_LEFT_BORDER, DEFAULT_TOP_BORDER);
}

// draw
void C2DChart::draw()
{
	if(m_pOwner == NULL) return;

	const COLORREF lineColor[7] = {RGB(0, 0, 255), RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 0),
		                           RGB(255, 255, 0), RGB(255, 0, 255), RGB(0, 255, 255)};

	// get the drawing area
	CRect rectClient;
	m_pOwner->GetClientRect(&rectClient);

	// get DC
	CClientDC dc(m_pOwner);
	CBrush brush(RGB(255,255,255));
	dc.FillRect(&rectClient, &brush);
	// draw X and Y coordinates
	drawCoordinates(&dc, &rectClient);

	// plot 
	if(m_nCount == 0) return;
	// else plot the curve
	double fX0, fY0;
	int iX, iY;

	// set pen and brush
	CPen Pen(PS_SOLID, 1, lineColor[0]);
    CBrush  Brush(RGB(0, 0, 255));
	CBrush  *pOldBrush = dc.SelectObject(&Brush);
	CPen *pOldPen =	dc.SelectObject(&Pen);
	fX0 = m_XRange.X;
	fY0 = m_YRange.Y + m_Inc.Y;

	UINT counter = 0, nLoop, nOuterLoop;
	for(nOuterLoop = 0; nOuterLoop < m_nLines; )
	{
		// move to the first point
		if(m_DrawType == DT_BYXY)
		{
			iX = DEFAULT_LEFT_BORDER + round((m_pXValues[counter] - fX0) / m_Unit.X);
			iY = DEFAULT_TOP_BORDER + round((fY0 - m_pYValues[counter]) / m_Unit.Y);
		}
		else if(m_DrawType == DT_BYY)
		{
			iX = DEFAULT_LEFT_BORDER + round((0 - fX0) / m_Unit.X);
			iY = DEFAULT_TOP_BORDER + round((fY0 - m_pYValues[counter]) / m_Unit.Y);
		}
		if(m_PlotStyle == PS_CHART_DOT)
			dc.Rectangle(iX-1, iY-1, iX+1, iY+1);
		else
			dc.MoveTo(iX, iY);
		dc.Rectangle(iX-3, iY-3, iX+3, iY+3);

		// draw 
		counter++;
		for(nLoop = 1; nLoop < m_nCount; nLoop ++)
		{
			if(m_DrawType == DT_BYXY)
			{
				iX = DEFAULT_LEFT_BORDER + round((m_pXValues[counter] - fX0) / m_Unit.X);
				iY = DEFAULT_TOP_BORDER + round((fY0 - m_pYValues[counter]) / m_Unit.Y);
			}
			else if(m_DrawType == DT_BYY)
			{
				iX = DEFAULT_LEFT_BORDER + round((nLoop - fX0) / m_Unit.X);
				iY = DEFAULT_TOP_BORDER + round((fY0 - m_pYValues[counter]) / m_Unit.Y);
			}
			else
				break;
			if(m_PlotStyle == PS_CHART_DOT)
				dc.Rectangle(iX-1, iY-1, iX+1, iY+1);
			else
				dc.LineTo(iX, iY);
			dc.Rectangle(iX-3, iY-3, iX+3, iY+3);
			counter++;
		}
//		if(m_nLines>1)
//		{
//			CString szNum;
//			szNum.Format("RG: %d",nOuterLoop+1);
//			dc.TextOut(iX,iY,szNum);
//
//		}
		int nCount=m_vMsgLisk.size();
		for(int t=0;t<nCount;t++)
		{
			CString szNum;
			szNum.Format("%s",m_vMsgLisk[nOuterLoop]);
			CSize nSize=dc.GetTextExtent(szNum);
			dc.TextOut(iX+3,iY-nSize.cy/2,szNum);

		}
		

		nOuterLoop++;
		dc.SelectObject(pOldPen);
		Pen.DeleteObject();
		Pen.CreatePen(PS_SOLID, 1, lineColor[nOuterLoop % 7]);
		dc.SelectObject(&Pen);
	}
	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);
	Pen.DeleteObject();
	Brush.DeleteObject();
}

// set origin position
void C2DChart::setOrigin(double OriginX, double OriginY)
{
	m_Origin.X = OriginX;
	m_Origin.Y = OriginY;
}

// set X range
void C2DChart::setXRange(double XMin, double XMax)
{
	m_XRange.X = XMin;
	m_XRange.Y = XMax;
}

// set Y range 
void C2DChart::setYRange(double YMin, double YMax)
{
	m_YRange.X = YMin;
	m_YRange.Y = YMax;
}

// set division
void C2DChart::setDivs(UINT nXDiv, UINT nYDiv)
{
	m_Div.X = nXDiv;
	m_Div.Y = nYDiv;
}

// set increase
void C2DChart::setIncs(double XInc, double YInc)
{
	if(XInc == 0 || YInc == 0) return;

	m_Inc.X = XInc;
	m_Inc.Y = YInc;
}
	
// set auto range control
void C2DChart::setAutoRange(AXIS axis, bool bAuto)
{
	bool bUpdate = false;
	if(axis == XAXIS)
	{
		bUpdate = m_IsAutoRange.X == bAuto;
		m_IsAutoRange.X = bAuto;
	}
	else if(axis == YAXIS)
	{
		bUpdate = m_IsAutoRange.Y == bAuto;
		m_IsAutoRange.Y = bAuto;
	}

	if(bUpdate) draw();
}
	
// set auto grid display
void C2DChart::setAutoGrid(AXIS axis, bool bAuto)
{
	bool bUpdate = false;
	if(axis == XAXIS)
	{
		bUpdate = m_IsAutoGrid.X == bAuto;
		m_IsAutoGrid.X = bAuto;
	}
	else if(axis == YAXIS)
	{
		bUpdate = m_IsAutoGrid.Y == bAuto;
		m_IsAutoGrid.Y = bAuto;
	}

	if(bUpdate) draw();
}
	
// set title
void C2DChart::setTitle(CString strTitle)
{
	m_strTitle = strTitle;
//	draw();
}

// set background color
void C2DChart::setBGColor(COLORREF color)
{
	m_BGColor = color;
//	draw();
}

// get Y range
void C2DChart::getYRange(double& YMin, double& YMax)
{
	YMin = m_YRange.X;
	YMax = m_YRange.Y;	
}

// get value by position on the screen 
double C2DChart::getValue(UINT iPos, AXIS axis)
{
	double fResult = 0.;
	switch(axis)
	{
	case XAXIS :
		fResult = (iPos - DEFAULT_LEFT_BORDER) * m_Unit.X + m_XRange.X;
		break;
	case YAXIS :
		fResult = m_YRange.Y - (iPos - DEFAULT_TOP_BORDER) * m_Unit.Y;
		break;
	default :
		break;
	}
	return fResult;
}

/***
 * private member-ship functions
 ***/
// get maximum and minimum value from an double-type array
TPair(double, double) C2DChart::getMaxMinValue(double *pValues, UINT nCount)
{
	TPair(double, double) Result(0, 0);
	
	if(nCount > 0)
	{
		Result.X = pValues[0];
		Result.Y = pValues[0];
		for(UINT nLoop = 1; nLoop < nCount; nLoop ++)
		{
			if(pValues[nLoop] < Result.X) Result.X = pValues[nLoop];
			if(pValues[nLoop] > Result.Y) Result.Y = pValues[nLoop];
		}
	}

	return Result;
}
