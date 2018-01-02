#include "stdafx.h"
//#include <windows.h>
//#include <stdio.h>
#include "RealTime.h"

CALine::CALine()
{ 
	m_nColor		= RGB(0, 0, 0);		
	m_nLineStyle	= PS_SOLID;	
	m_nLineWidth	= 0;	
	m_pValues		= NULL;		
	m_sName			= "";		
	m_sDescription	= "";	
	m_sUnit			= "";		
	m_dMin			= 0;			
	m_dMax			= 0;			
	m_dScaleLow		= 0;	
	m_dScaleHigh	= 0;	
	m_nSize			= 0; 
}

bool CALine::Reset(DWORD size)
{
	assert(size > 0);
	if (m_pValues) free(m_pValues);
	m_pValues  = (CValue*)calloc((size_t)(size + 1), sizeof(CValue));
	if(!m_pValues) 
		return false;

	m_nSize = size;
	return true;
}

void CALine::AddValue(double& value, DWORD begin, DWORD end)
{
	if (m_pValues == NULL) return;
	if (end == m_nSize)
	{
		m_pValues[begin].bFlag	= 1;
		m_pValues[begin].YValue = value;
	}
	else
	{
		m_pValues[end].bFlag	= 1;
		m_pValues[end].YValue	= value;
	}
}

CRealTime::CRealTime()
{
	m_bSetingFailed	= true;
	m_nMaxPages		= 1;
	m_nTimeStart	= 0;
	m_nBegin		= 0;
	m_nEnd			= 0;
	m_nTimes		= 0;
	m_nCounter		= 1;
	m_nTick			= 0;
	m_sHigh			= 17;
	m_nPage			= 0;
	m_nMaxTime		= 0;
	m_nCursorTime	= 0;
	m_pValueTime	= NULL;
	m_pLineArray	= NULL;
	m_pCurLine		= NULL;
	m_wdTickLine	= 2;
	m_crTickLine	= RGB(255, 0, 0);

	m_SpeedLevel[0] = 10000;// 10 seconds	(0.1 cycle per second)
	m_SpeedLevel[1] = 5000;	// 5 seconds	(0.2 cycle per second)	
	m_SpeedLevel[2] = 2500;	// 2.5 seconds	(0.4 cycle per second)
	m_SpeedLevel[3] = 2000;	// 2 seconds	(0.5 cycle per second)
	m_SpeedLevel[4] = 1000;	// 1 seconds	(1 cycle per second)
	m_SpeedLevel[5] = 500;	// 0.5 seconds	(2 cycle per second)
	m_SpeedLevel[6] = 250;	// 0.4 seconds	(4 cycle per second)
	m_SpeedLevel[7] = 200;	// 0.2 seconds	(5 cycle per second)
	m_SpeedLevel[8] = 125;	// 0.125 seconds(8 cycle per second)
	m_SpeedLevel[9] = 100;  // 0.1 second	(10 cycle per second)
}

CRealTime::~CRealTime()
{
	if (m_pLineArray)
		free(m_pLineArray);

	if (m_pValueTime)
		free(m_pValueTime);

	int n = m_LineArray.GetSize();
	for(int i = n-1; i >= 0; i --)
		m_LineArray.RemoveAt(i);
}

RECT CRealTime::TickBarSize()
{
	m_SRect		   = m_PlotRect;
	m_SRect.top	   = m_SRect.top - m_sHigh;
	m_SRect.bottom = m_SRect.top  + m_sHigh - 1;
	m_SRect.left   = m_SRect.left - 7;
	m_SRect.right  = m_SRect.right + 7;

	return m_SRect;
}

bool CRealTime::SetRange(double xmin, double ymin, double xmax, double ymax)
{
	if (ymax <= ymin)
		return false; 

	m_Scale.xmin	= xmin;
    m_Scale.ymin	= ymin;
    m_Scale.xmax	= xmax;
    m_Scale.ymax	= ymax;
	return true; 
}

bool CRealTime::InitialSetting(double CycsPerSec, DWORD StartTime, DWORD TimeSpan,
							   DWORD MaxSeconds, int XTick, bool IsForward)
{
	if (!IsForward && 1000 * TimeSpan > StartTime)
	{
		int ret = MessageBox(NULL, "<1000 * TimeSpan - StartTime> must be positive value\nin initial backward drawing."
							 " Changed to foreward drawing?", 
							 "From InitialSetting() ...", MB_YESNO);
		if (ret == IDYES)
			IsForward = true;
		else
			return false;
	}

	assert(StartTime >= 0);
	assert(TimeSpan >= 30);
	assert(TimeSpan >= (DWORD)XTick);
	assert(MaxSeconds >= TimeSpan);
	MaxSeconds = TimeSpan * (MaxSeconds / TimeSpan);
	assert(CycsPerSec >= 0.09999 && CycsPerSec <= 10.00001f);

	if (MaxSeconds == TimeSpan ) MaxSeconds ++;
	m_nDataPerLine	= (DWORD)(0.5 + MaxSeconds * CycsPerSec + 1);

	m_pValueTime	= (DWORD*)calloc(m_nDataPerLine, sizeof(DWORD));
	if (!m_pValueTime)	return false;

	m_nMaxPages			= MaxSeconds / TimeSpan;
	m_nTimeSpan			= TimeSpan;
	m_nXTicks			= XTick;
	m_nCyclesPerSec		= CycsPerSec;
	m_nCounter			= (int)CycsPerSec;
	m_bIsForwardDrawing	= IsForward;
	m_nSTicks			= (int)(0.5 + TimeSpan * CycsPerSec);

	if (IsForward)
	{
		m_Scale.xmin = StartTime;
		m_Scale.xmax = StartTime + 1000. * TimeSpan;
	}
	else
	{
		m_Scale.xmin = StartTime - 1000. * TimeSpan;
		m_Scale.xmax = StartTime;
	}

	assert(m_Scale.xmin >= 0);
	assert(m_Scale.xmax >= 0);
	assert(m_Scale.xmax - m_Scale.xmin > 0);
	m_TimeToDraw = (DWORD)(0.5 + (m_Scale.xmax - m_Scale.xmin) / 1000 * m_nCyclesPerSec + 1);

	m_pLineArray = (POINT*)calloc(m_TimeToDraw, sizeof(POINT));
	if (!m_pLineArray)	
	{
		free(m_pValueTime);
		return false;
	}

	m_nMin = (DWORD)m_Scale.xmin;
	m_nMax = (DWORD)m_Scale.xmax;
	SetTimeRange(m_nMin, m_nMax);
	m_bAutoScrollX = true;

	EnableLegend(false);
	m_bLegendShadow = false;

	return	true;
}

void CRealTime::SetTimeRange(DWORD FromTime, DWORD ToTime)
{
	assert(ToTime - FromTime > 0);
	m_Scale.xmin = FromTime;
	m_Scale.xmax = ToTime;
	m_Scale.dx   = (m_Scale.xmax - m_Scale.xmin) / PX;
}

void CRealTime::Reset()
{
	if (m_bAutoScrollX)
		SetTimeRange(m_nMin, m_nMax);
	else
	{
		if (m_nEnd == m_nDataPerLine)
			m_nFrom = m_nBegin + m_nPage * (m_TimeToDraw - 1);
		else
			m_nFrom = m_nBegin + m_nPage * (m_TimeToDraw - 1); // -1 ;
		m_nFrom %= m_nDataPerLine;
		m_nTo    = m_nFrom + m_TimeToDraw - 1;
		m_nTo   %= m_nDataPerLine;
		SetTimeRange(m_pValueTime[m_nFrom], m_pValueTime[m_nTo]);
	}
}

bool CRealTime::AddALine(COLORREF color, double low, double high, 
						 const char* name, const char* desc, const char* unit, 
						 double min, double max, int style, int width)
{
	m_LineArray.Add(m_line);
	int n = m_LineArray.GetSize() - 1;

	// support only three styles : PS_SOLID, PS_DASH, PS_DOT
	if (style < PS_SOLID) style = PS_SOLID;
	if (style > PS_DOT) style	= PS_DOT;

	m_LineArray[n].m_nColor			= color;
	m_LineArray[n].m_dScaleLow		= low;			
	m_LineArray[n].m_dScaleHigh		= high;
	m_LineArray[n].m_sName			= name;
	m_LineArray[n].m_sDescription	= desc;	
	m_LineArray[n].m_sUnit			= unit;		
	m_LineArray[n].m_dMin			= min;			
	m_LineArray[n].m_dMax			= max;			
	m_LineArray[n].m_nLineStyle		= style;
	m_LineArray[n].m_nLineWidth		= width;

	if (!m_LineArray[n].Reset(m_nDataPerLine))
	{
		m_LineArray.RemoveAt(n);
		return false;
	}

	return true;
}

bool CRealTime::InsertALine(int index, COLORREF color, double low, double high, 
						 const char* name, const char* desc, const char* unit, 
						 double min, double max, int style, int width)
{
	int n = m_LineArray.GetSize();
	if (index < 0 || index > n)
		return false;

	m_LineArray.InsertAt(index, m_line);

	if (style < PS_SOLID) style = PS_SOLID;
	if (style > PS_DOT) style	= PS_DOT;

	m_LineArray[index].m_nColor			= color;
	m_LineArray[index].m_dScaleLow		= low;			
	m_LineArray[index].m_dScaleHigh		= high;
	m_LineArray[index].m_sName			= name;
	m_LineArray[index].m_sDescription	= desc;	
	m_LineArray[index].m_sUnit			= unit;		
	m_LineArray[index].m_dMin			= min;			
	m_LineArray[index].m_dMax			= max;			
	m_LineArray[index].m_nLineStyle		= style;
	m_LineArray[index].m_nLineWidth		= width;

	if (!m_LineArray[index].Reset(m_nDataPerLine))
	{
		m_LineArray.RemoveAt(index);
		return false;
	}

	return true;
}

bool CRealTime::RemoveALine(int Index)
{
	int n = m_LineArray.GetSize();
	if (n <= 0 || n <= Index)
		return false;

	m_LineArray.RemoveAt(Index);
	return true;
}

void CRealTime::DrawXAxisTimeTicks(int x, int y, DWORD& ticks)
{
	sprintf(m_sTempStr, "%d:%d:%d", ticks/3600, (ticks/60)%60, ticks%60);
	PrintString(x, y, 0, m_sTempStr);	
}

void CRealTime::XAxis()
{
	m_nStep = (m_TimeToDraw > m_nEnd) ? m_nEnd : m_TimeToDraw;
	for(int i = 0; i < m_nStep; i ++) 
	{
		DWORD sec = (DWORD)(m_Scale.xmin + i * 1000 / m_nCyclesPerSec + 0.5);
		xb = xe = (int)(GL + (sec - m_Scale.xmin) / m_Scale.dx);
		if ((sec % 1000) == 0 && ((sec / 1000) % (m_nTimeSpan / m_nXTicks)) == 0)
		{
			if (i == 0)
				SetStringAlign(LEFT, TOP);
			else if (i >= m_nStep - (int)m_nCyclesPerSec - 1 && m_TimeToDraw <= m_nEnd)
				SetStringAlign(RIGHT, TOP);
			else
				SetStringAlign(CENTER, TOP);

			ye = GB + m_bM / 7;
			DWORD ticks = sec / 1000;
			DrawXAxisTimeTicks(xb, GB + m_bM / 5, ticks);
		}
		else 
			ye = GB + m_bM / 14;

		yb=GB;
		if (!(sec % 1000) && i > 0 && i < m_nStep - 1)
			DrawLine(xb, yb, xe, ye);
	}

	PrintTime();
}

void CRealTime::Grid()
{
	HPEN hPen	= ::CreatePen(PS_DOT, 0, m_nGridColor);
	HPEN hOldPen = (HPEN)::SelectObject(m_hDC, hPen);

	m_nStep = (m_TimeToDraw > m_nEnd) ? m_nEnd : m_TimeToDraw;
	for(int i = 0; i < m_nStep; i ++) 
	{
		DWORD sec = (DWORD)(m_Scale.xmin + i * 1000 / m_nCyclesPerSec + 0.5);
		xb = xe = (int)(GL + (sec - m_Scale.xmin) / m_Scale.dx);
		if (xb == GL)
			xb = xe = GL + 1;
		if ((sec % 1000) == 0 && ((sec / 1000) % (m_nTimeSpan / m_nXTicks)) == 0)
			DrawLine(xb, GT + 1, xe, GB - 1);
	}

	for(i = 1; i < YGridTicks; i ++) 
	{
		yb = ye = GT + (int)(1.0 * i * (GB-GT) / YGridTicks);
		DrawLine(GL + 1, yb, GR - 1, ye);
	}

	::SelectObject(m_hDC, hOldPen);
	::DeleteObject(hPen);
}

void CRealTime::DrawRealTimeLines()
{
	int n = m_LineArray.GetSize();
	if (m_bLegendShadow)
		DrawShadow(n);

	for(int i = 0; i < n; i ++)
	{
		m_pCurLine = &m_LineArray[i];
		DrawCurrentLine();
		if (m_bEnableLegend)
		{
			m_CurPen = ::CreatePen(m_pCurLine->m_nLineStyle, m_pCurLine->m_nLineWidth, m_pCurLine->m_nColor);
			m_OldPen = (HPEN)::SelectObject(m_hDC, m_CurPen);
			CGraphics::Legend(m_pCurLine->m_nColor, i + 1, m_pCurLine->m_sName.GetChar());
			::SelectObject(m_hDC, m_OldPen);
			::DeleteObject(m_CurPen);
		}
	}

	DrawTickLine();
}

void CRealTime::DrawCurrentLine()
{
	if (m_nEnd < 2)
		return;

	m_CurPen = ::CreatePen(m_pCurLine->m_nLineStyle, m_pCurLine->m_nLineWidth, m_pCurLine->m_nColor);
	m_OldPen = (HPEN)::SelectObject(m_hDC, m_CurPen);

	m_nP = 0;
	DWORD nB, nE;

	if (m_bAutoScrollX)
	{
		nB = m_nBegin;
		nE = m_nEnd;

		// forward drawing: something like "*******------" 
		// or "------******------", or "------******"
		if (nB == 0 && nE <= m_TimeToDraw)
		{
			m_nTimeStart = nB;
			ForwardDraw(nB, nE);
		}
		else if (nB == 0 && nE > m_TimeToDraw)
		{
			nB = nE - m_TimeToDraw;
			m_nTimeStart = nB;
			ForwardDraw(nB, nE);
		}
		else if (nB >= m_TimeToDraw)
		{
			m_nTimeStart = nB - m_TimeToDraw;
			ForwardDraw(nB - m_TimeToDraw, nB);
		}
		// backward drawing: something like "******--------******"
		else
		{
			m_nTimeStart = nE - m_TimeToDraw + nB;
			BackwardDraw(nB, nE);
		}
	}
	else
	{
		nB = m_nFrom;
		nE = m_nTo + 1;
		if (nB <= m_nDataPerLine - m_TimeToDraw)
		{
			ForwardDraw(nB, nE);
		}
		else
		{
			ForwardDraw(nB, m_nDataPerLine);
			ForwardDraw(0, nE);
		}
	}

	if(m_nP > 1)
		::Polyline(m_hDC, m_pLineArray, m_nP);

	::SelectObject(m_hDC, m_OldPen);
	::DeleteObject(m_CurPen);
}

int CRealTime::ForwardDraw(int nB, int nE)
{
	for(int i = nB; i < nE; i ++)
	{
		if (m_pCurLine->m_pValues[i].bFlag)
		{
			m_Pt.x = (int)(GL + ((m_pValueTime[i] - m_Scale.xmin) / m_Scale.dx));
			m_Pt.y = (int)(GB - ((m_pCurLine->m_pValues[i].YValue - m_Scale.ymin) / m_Scale.dy));
			if(m_Pt.x >= GL && m_Pt.x <= GR)
			{
				assert(m_nP<m_nDataPerLine);
				m_pLineArray[m_nP].x = m_Pt.x;
				m_pLineArray[m_nP].y = m_Pt.y;
				m_nP++;
			}
			else // something wrong
				assert(false);
		}
	}

	return m_nP;
}

int CRealTime::BackwardDraw(int nB, int nE)
{
	//-----------------------------******
	ForwardDraw(nE - m_TimeToDraw + nB, nE);	
	nE = nB;
	nB = 0;
	//******-----------------------------
	ForwardDraw(nB, nE);

	return m_nP;
}

void CRealTime::UpdateTimeRange(DWORD& vtime)
{
	if ((int)m_nCyclesPerSec == 0)
		m_nTimes += (int)(0.5 + 1 / m_nCyclesPerSec);
	else
	{
		if (m_nCounter == (int)m_nCyclesPerSec)
		{
			m_nTimes ++;
			m_nCounter = 1;
		}
		else
			m_nCounter ++;
	}

	if (m_nEnd == m_nDataPerLine)
	{
		if (m_nBegin == m_nDataPerLine)	m_nBegin = 0;
		m_pValueTime[m_nBegin++] = vtime;
	}
	else
		m_pValueTime[m_nEnd++] = vtime;

	if (vtime > (DWORD)m_Scale.xmax)
	{
		DWORD span	 = (DWORD)(m_Scale.xmax - m_Scale.xmin);
		m_nMin = vtime - span; 
		m_nMax = vtime;
	}

	if(m_bAutoScrollX)
		SetTimeRange(m_nMin, m_nMax);
	else
	{
		m_nFrom ++; 
		m_nTo ++;

		if (m_nFrom == m_nDataPerLine)
			m_nFrom = 0;
		if (m_nTo == m_nDataPerLine)
			m_nTo = 0;
		
		SetTimeRange(m_pValueTime[m_nFrom], m_pValueTime[m_nTo]);
	}
}

DWORD CRealTime::GetCursorTime()
{
	DWORD time;
	if (m_bAutoScrollX)
	{
		if (m_nEnd < (int)m_TimeToDraw) 
		{
			time = m_pValueTime[m_nTick];
		}
		else if (m_nEnd < m_nDataPerLine)
		{
			time = m_pValueTime[m_nEnd - m_TimeToDraw + m_nTick];
		}
		else
		{
			int tv = m_nDataPerLine - m_nSTicks + m_nBegin + m_nTick - 1;
			tv %= m_nDataPerLine;
			time = m_pValueTime[tv];
		}
	}
	else
	{
		int tv = m_nFrom % m_nDataPerLine;
		tv += m_nTick;
		tv %= m_nDataPerLine;
		time = m_pValueTime[tv];
	}

	return time;
}

int CRealTime::GetCursorTimeAndIndex(DWORD& time)
{
	int Index;
	if (m_bAutoScrollX)
	{
		
		if (m_nEnd < (int)m_TimeToDraw) 
		{
			Index = m_nTick;
			time  = m_pValueTime[Index];
		}
		else if (m_nEnd < m_nDataPerLine)
		{
			Index = m_nEnd - m_TimeToDraw + m_nTick;
			time = m_pValueTime[Index];
		}
		else
		{
			int tv = m_nDataPerLine - m_nSTicks + m_nBegin + m_nTick - 1;
			tv %= m_nDataPerLine;
			Index = tv;
			time = m_pValueTime[Index];
		}
	}
	else
	{
		int tv = m_nFrom % m_nDataPerLine;
		tv += m_nTick;
		tv %= m_nDataPerLine;
		Index = tv;
		time = m_pValueTime[Index];
	}

	return Index;
}

void CRealTime::Redraw(HWND hWnd)
{
	RECT rt;
	rt.left   = GL;
	rt.top    = GT - 1;
	rt.right  = GR;
	rt.bottom = m_Rect.bottom - 1;
	::InvalidateRect(hWnd, &rt, FALSE);
}

void CRealTime::DrawTickLine()
{
	POINT pt;
	if (m_nEnd < (int)m_TimeToDraw)
	{
		if (m_nTick == 0) return;
		else if (!m_bIsForwardDrawing)
			pt.x = GR - 1;
		else
			pt.x = GL + PX * (m_nTick - 1) / (m_TimeToDraw - 1);
	}
	else
		pt.x = GL + PX * m_nTick / (m_TimeToDraw - 1);

	if (pt.x == GL)
		pt.x ++;
	if (pt.x == GR)
		pt.x --;

	pt.y = GT + 1;

	m_CurPen = ::CreatePen(PS_SOLID, m_wdTickLine, RGB(0, 0, 0));
	m_OldPen = (HPEN)::SelectObject(m_hDC, m_CurPen);
	::MoveToEx(m_hDC, pt.x + 1, pt.y, NULL);
	pt.y = GB - 1;
	::LineTo(m_hDC, pt.x + 1, pt.y);
	::SelectObject(m_hDC, m_OldPen);
	::DeleteObject(m_CurPen);

	m_CurPen = ::CreatePen(PS_SOLID, m_wdTickLine, m_crTickLine);
	m_OldPen = (HPEN)::SelectObject(m_hDC, m_CurPen);
	::MoveToEx(m_hDC, pt.x, pt.y, NULL);
	pt.y = GT + 1;
	::LineTo(m_hDC, pt.x, pt.y);
	::SelectObject(m_hDC, m_OldPen);
	::DeleteObject(m_CurPen);

}

void CRealTime::SetPrintTime(DWORD time, int flag)
{
	if (flag == MaxTime)
		m_nMaxTime = time / 1000;
	else
		m_nCursorTime = time / 1000;
}

void CRealTime::PrintTime()
{
	int n = 5;
	if (m_bPrinting)	n *= m_nPrintScale;
	n = m_Rect.bottom - n - 1;
	SetStringAlign(LEFT, BOTTOM);
	ShowTime(GL, n, "Cursor time", m_nCursorTime);
	SetStringAlign(RIGHT, BOTTOM);
	ShowTime(GR, n, "Total lapse time", m_nMaxTime);
}

void CRealTime::ShowTime(int x, int y, const char* Tag, DWORD& cTime)
{
	if (m_nCyclesPerSec > 0.9999 && m_nCyclesPerSec < 1.0001)
		sprintf(m_sTempStr, "%s (%d:%d:%d)", Tag, 
				cTime / 3600, (cTime / 60) % 60, cTime % 60);
	else
		sprintf(m_sTempStr, "%s (%d:%d:%d / %d:%d:%d)", Tag,
			    ((DWORD)(m_nCyclesPerSec * cTime)) / 3600, 
				(((DWORD)(m_nCyclesPerSec * cTime)) / 60) % 60, 
				((DWORD)(m_nCyclesPerSec * cTime)) % 60, 
				cTime / 3600, (cTime / 60) % 60, cTime % 60);
	PrintString(x, y, 0, m_sTempStr);	
}

