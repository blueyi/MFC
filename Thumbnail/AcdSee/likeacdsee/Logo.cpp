// Logo.cpp : implementation file
//

#include "stdafx.h"
#include "BigSee.h"
#include "Logo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogo

CLogo::CLogo()
{
}

CLogo::~CLogo()
{
}


BEGIN_MESSAGE_MAP(CLogo, CWnd)
	//{{AFX_MSG_MAP(CLogo)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLogo message handlers

void CLogo::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	 CDC dcComp;
	 dcComp.CreateCompatibleDC(&dc);
	 dcComp.SelectObject(&m_bitmap);
	 dc.BitBlt(0
		       ,0
		       ,m_bmpStruct.bmWidth
			   ,m_bmpStruct.bmHeight
			   ,&dcComp
		       ,0
			   ,0
			   ,SRCCOPY);
	// Do not call CWnd::OnPaint() for painting messages
}
void CLogo::CreateLogo(CWnd*pWnd,UINT nBitmapID,UINT nChildID)
{
	m_bitmap.LoadBitmap(nBitmapID);
    m_bitmap.GetBitmap(&m_bmpStruct);
	CRect rect(0,0,0,0);
	Create(NULL,_T(""),WS_CHILD|WS_VISIBLE,rect,pWnd,nChildID);
}



void CLogo::MoveLogo(int nWidth,int nHeight)
{
	MoveWindow(nWidth-m_bmpStruct.bmWidth,
		0,
		m_bmpStruct.bmWidth,
		nHeight);
}