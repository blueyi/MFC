// Canvas.cpp : implementation file
//

#include "stdafx.h"
#include "AlphaBlending.h"
#include "Canvas.h"
#include "PlayColor.h"
#include "MemDC.h"

#include <process.h>//For _beginthreadex

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCanvas

CCanvas::CCanvas()
{
	mpCPlayColor = NULL;
	mAlpha = 0;
	mpMemDC = NULL;
	mFade = 0;
}

CCanvas::~CCanvas()
{
	if (mpCPlayColor)
	{
		delete mpCPlayColor;
		mpCPlayColor = NULL;
	}
	if (mpMemDC)
	{
		delete mpMemDC;
		mpMemDC = NULL;
	}
}


BEGIN_MESSAGE_MAP(CCanvas, CStatic)
	//{{AFX_MSG_MAP(CCanvas)
	ON_WM_PAINT()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCanvas message handlers

void CCanvas::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect rect;
	GetClientRect(&rect);
	if ( NULL == mpCPlayColor)
	{
		mpCPlayColor = new CPlayColor;
		mpCPlayColor->mClientRect = rect;
	}	
	if (NULL == mpMemDC)
	{
		mpMemDC = new CMemDC(&dc,&rect);
	}
	mpCPlayColor->draw( mpMemDC );
	dc.BitBlt(0,0,rect.Width(),rect.Height(),mpMemDC,0,0,SRCCOPY);
	// Do not call CStatic::OnPaint() for painting messages;
}
//
void CCanvas::applyChange()
{	
	mpCPlayColor->mAlpha = mAlpha;
	Invalidate();
}

void CCanvas::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (2 == mFade)
	{
		mpCPlayColor->mPoint.x += 50; 
		if (mpCPlayColor->mPoint.x >= 400)
		{
			mpCPlayColor->mPoint.x = 0;
		}
	}
	else if ( 0 == mFade )//fade in 
	{
		if (mAlpha >=100)
		{
			mAlpha = 0;
		}
		mAlpha += 20;		
		mpCPlayColor->mAlpha = mAlpha;
	}
	else
	{
		if (mAlpha <= 0)
		{
			mAlpha = 100;
		}
		mAlpha -= 10;
		mpCPlayColor->mAlpha = mAlpha;
	}	
	
	Invalidate();
	CStatic::OnTimer(nIDEvent);
}
//
void CCanvas::fadeEffect(int aStart)
{
	if (0 == aStart)
	{
		KillTimer(100);
		return;
	}	
	SetTimer(100,10,NULL);
}
