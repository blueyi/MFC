// SeriesShower.cpp : implementation file
//

#include "stdafx.h"
#include "qtimage.h"
#include "SeriesShower.h"
#include "DrawSeries.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeriesShower

CSeriesShower::CSeriesShower()
{
}

CSeriesShower::~CSeriesShower()
{
}


BEGIN_MESSAGE_MAP(CSeriesShower, CStatic)
	//{{AFX_MSG_MAP(CSeriesShower)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSeriesShower message handlers

void CSeriesShower::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect rcClient;
	GetClientRect(rcClient);
	
	// draw scale
	if (m_memDC.GetSafeHdc() != NULL)
		dc.BitBlt(0, 0, rcClient.Width(), rcClient.Height(), &m_memDC, 0, 0, SRCCOPY);
	// Do not call CStatic::OnPaint() for painting messages
}


void CSeriesShower::Update(vtkImageData *pImage, int index)
{
	if(!this->GetSafeHwnd())
		return;

	CClientDC dc(this);
	CRect rcClient;
	GetClientRect(rcClient);
	
	if (m_memDC.GetSafeHdc() == NULL)
	{
		m_memDC.CreateCompatibleDC(&dc);
		m_bitmap.CreateCompatibleBitmap(&dc,rcClient.Width(),rcClient.Height());
		m_pOldBitmap=m_memDC.SelectObject(&m_bitmap);
		
	}
	
	if (m_memDC.GetSafeHdc() != NULL)
	{
		CDrawSeries draw;
		draw.EnableAutoWindowLevel();
		draw.Draw(&m_memDC,rcClient,pImage,index);
	}
	Invalidate(FALSE);
}
