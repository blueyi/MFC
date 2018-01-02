//######################################################################
//# FILENAME: CPlayColor.cpp
//#
//# DESCRIPTION:	PERFORM Fade effect, Draw bitmap transparently,
//#					Horizontal gradient, Vertical gradient, Copy HBITMAP,
//#					Transparent HBITMAP ---bitmap from HBITMAP
//#					GET THE PREVIEW OF WHOLE DRAWING.
//# AUTHOR:		Mohammad Saiful Alam (Jewel)
//# POSITION:	Senior Software Engineer
//# E-MAIL:		saiful.alam@ bjitgroup.com
//# CREATE DATE: 2008/02/1
//#
//# Copyright (c) 2007 BJIT Ltd.
//######################################################################

#include "stdafx.h"
#include "AlphaBlending.h"
#include "PlayColor.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPlayColor::CPlayColor()
{
	mSrcColor[0] = RGB(255,255,255);
	mDestColor[0] = RGB(0,0,255);

	mSrcColor[1] = RGB(255,255,255);
	mDestColor[1] = RGB(255,0,0);

	mSrcColor[2] = RGB(255,255,255);
	mDestColor[2] = RGB(0,255,0);

	mSrcColor[2] = RGB(255,255,255);
	mDestColor[3] = RGB(255,255,0);

	mBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle( ),MAKEINTRESOURCE(IDB_BITMAP_ME),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	mBitmapCheck = (HBITMAP)LoadImage(AfxGetInstanceHandle( ),MAKEINTRESOURCE(IDB_BITMAP_CHECK),IMAGE_BITMAP,0,0,LR_DEFAULTSIZE);
	mAlpha = 0;
	mClientRect = CRect(0,0,0,0);

	//mBitmapCheckTrans = getTransparentBitmap( &memDCDirty,CPoint(10,180),mBitmapCheck,0);
	mPoint = CPoint(10,180);
}

CPlayColor::~CPlayColor()
{

}
//
void CPlayColor::draw(CDC* pDC)
{
	COLORREF rectColor = RGB(0,124,125);//BACK COLOR
//	COLORREF rectColor = RGB(124,124,125);//BACK COLOR
	unsigned aFadeto = RGB(255,255,255);
	HBITMAP hBitmap;
	//ALL DRAWING PERFORM IN BITMAP SO THAT WE CAN USE THE BITMAP LATER..
	HBITMAP hBitmapDirty;
	CDC memDCDirty;	 	
	//DRAWAING STARTED...
	hBitmapDirty = getResizeBitmap( mBitmap,mClientRect.Width(),mClientRect.Height() );//LARGE BITMAP TO SUPPORT YOUR DRAWING AREA
	memDCDirty.CreateCompatibleDC( NULL );   		
	HBITMAP hBmOldDirty = (HBITMAP)::SelectObject( memDCDirty.m_hDC, hBitmapDirty );	
	memDCDirty.FillSolidRect(CRect(CPoint(0,0),CSize(600,600)),rectColor);

	//DRAW A RECTANGLE WITH ALPHA COLOR
	hBitmap = fadeBitmap( mBitmap,rectColor,mAlpha);//NO EFFECT ON ORIGINAL BITMAP
	drawBitmap(&memDCDirty,0,0,hBitmap);
	
	hBitmap = getResizeBitmap( mBitmap,50,50 );
	drawBitmap(&memDCDirty,150,0,hBitmap);
	//
	vgradient(&memDCDirty,mSrcColor[0],mDestColor[0],CRect(CPoint(0,160),CSize(50,160)));
	hgradient(&memDCDirty,mDestColor[1],mSrcColor[0],CRect(CPoint(55,160),CSize(250,50)));
	hgradient(&memDCDirty,mSrcColor[0],mDestColor[2],CRect(CPoint(55,160+110),CSize(250,50)));
	vgradient(&memDCDirty,mDestColor[3],mSrcColor[0],CRect(CPoint(310,160),CSize(50,160)));
	
	drawBitmap(&memDCDirty,160,200,mBitmapCheck);

	//hBitmap = getTransparentBitmap( &memDCDirty,mPoint,mBitmapCheck,0);
	drawBitmapTransparent(&memDCDirty,mPoint.x,mPoint.y,mBitmapCheck,0);

	memDCDirty.SelectObject( hBmOldDirty );
	memDCDirty.DeleteDC();
	//DRAWAING FINISHED...
//	//DRAW WHOLE BITMAP INTO OUTPUT
	drawBitmap(pDC,0,0,hBitmapDirty);
//	//DRAW THUMNAIL VIEW OF WHOLE DRAWING
	pDC->FillSolidRect(CRect(CPoint(259,9),CSize(102,102)),aFadeto);
	hBitmap = getResizeBitmap( hBitmapDirty,100,100);
	drawBitmap(pDC,260,10,hBitmap);//thumnail image
}
//
void CPlayColor::setGradientColor(const COLORREF aSrcClr,const COLORREF aDestClr)
{

}

//IF U CAN TRANSLATE ONE COLOR U CAN TRANSLATE WHOLE IMAGE...
void CPlayColor::fadeColor(const unsigned int aClrSrc,unsigned int& aClrDest,const int aPercent)
{
	register int rr,gg,bb,dr,dg,db,r1,g1,b1,r2,g2,b2;
	register int f1,f2,f3;
	
	r1 = (aClrSrc)&0xff;
	g1 = ((aClrSrc)>>8)&0xff;
	b1 = ((aClrSrc)>>16)&0xff;


	r2 = (aClrDest)&0xff;
	g2 = ((aClrDest)>>8)&0xff;
	b2 = ((aClrDest)>>16)&0xff;

	rr = r1 - r2;
	gg = g1 - g2;
	bb = b1 - b2;
    //aPercent = 100 means fully converted to aClrSrc;
	f1 = (rr*aPercent)/100;
	f2 = (gg*aPercent)/100;
	f3 = (bb*aPercent)/100;

	dr = r1 - f1;
	dg = g1 - f2;
	db = b1 - f3;	
	aClrDest = RGB(dr,dg,db);
}
//
void CPlayColor::hgradient(CDC* pDC,const unsigned int aClrSrc,const unsigned int aClrDest,const CRect aRect)
{
	register int rw,factor,l,t;
	CRect rg;
	unsigned dc = aClrDest;
    rw = aRect.Width(); 	
	//
	l = aRect.left;
	t = aRect.top;
	for (int i = 1;i<=rw; i++)
	{
		factor = (i*100)/rw;
		fadeColor(aClrSrc,dc,factor);		
		pDC->FillSolidRect(l,t,1,aRect.Height(),dc);		
		dc = aClrDest;
		l+=1;	
	}
}
//
void CPlayColor::vgradient(CDC* pDC,const unsigned int aClrSrc,const unsigned int aClrDest,const CRect aRect)
{
	register int rh,factor,l,t;
	CRect rg;
	unsigned dc = aClrDest;
    rh = aRect.Height();
	//
	l = aRect.left;
	t = aRect.top;
	for (int i = 1;i<=rh; i++)
	{
		factor = (i*100)/rh;
		fadeColor(aClrSrc,dc,factor);		
		pDC->FillSolidRect(l,t,aRect.Width(),1,dc);		
		dc = aClrDest;
		t+=1;	
	}
}
//
HBITMAP CPlayColor::fadeBitmap(HBITMAP aBitmap,const COLORREF aFadeto,const int aTransparency )
{
	HBITMAP hbitmap;
	CBitmap bmpSrc;
	BITMAP bmp;
	if(!bmpSrc.Attach(aBitmap))
		return NULL;
	if(!bmpSrc.GetBitmap(&bmp))
		return NULL;
	CDC memDC;
	memDC.CreateCompatibleDC( NULL );   		
	hbitmap = getCloneBitmap( aBitmap);
	HBITMAP hBmOld = (HBITMAP)::SelectObject( memDC.m_hDC, hbitmap );	
	memDC.SetBkColor(RGB(0,0,0));                // 1 -> black
	memDC.SetTextColor(RGB(255,255,255));        // 0 -> white	
	COLORREF cs;
	unsigned dc1 = aFadeto;

	for (int x = 0; x<bmp.bmHeight; x++)
	{
		for (int y = 0; y<bmp.bmWidth; y++)
		{	
			cs = memDC.GetPixel(y,x);
			fadeColor(cs,dc1,aTransparency);			
			memDC.SetPixel(y,x,dc1);
			dc1 = aFadeto;
		}
	}	
	memDC.SelectObject(hBmOld);
	memDC.DeleteDC();
	bmpSrc.Detach();	

	return hbitmap;
}
//
HBITMAP CPlayColor::getTransparentBitmap( CDC* pSrcDC,CPoint aImgCorner,HBITMAP aBitmap,COLORREF aTransprent)
{
	//PASS SOURCE DC, LEFT TOP CORNER OF IMAGE TO BE DIPLAYED..
	//PLEASE PROVIDE -----aImgCorner---- CORRECTLY
	//THIS IS VERY IMPORTANT.....THIS CORNER POINT DENOTES THAT THE IMAGE 
	//IS GOING TO BE DISPLAYED FROM THIS POINT

	HBITMAP hbitmap;
	CBitmap bmpSrc;
	BITMAP bmp;
	if(!bmpSrc.Attach(aBitmap))
		return NULL;
	if(!bmpSrc.GetBitmap(&bmp))
		return NULL;
	CDC memDC;
	memDC.CreateCompatibleDC( NULL );   		
	hbitmap = getCloneBitmap( aBitmap);
	HBITMAP hBmOld = (HBITMAP)::SelectObject( memDC.m_hDC, hbitmap );	
	memDC.SetBkColor(RGB(0,0,0));                // 1 -> black
	memDC.SetTextColor(RGB(255,255,255));        // 0 -> white	
	COLORREF cs;
	COLORREF dc1 = aTransprent;
	if (aTransprent == 0)
	{
		aTransprent = memDC.GetPixel(1,1);//GET LET TOP PIXEL AS TRANSPARENT	
	}
	for (int x = 0; x<bmp.bmHeight; x++)
	{
		for (int y = 0; y<bmp.bmWidth; y++)
		{	
			//EXACT CORNER WHERE IMAGE TO BE SHOWN
			cs = pSrcDC->GetPixel(y+aImgCorner.x,x+aImgCorner.y);
			dc1 = memDC.GetPixel(y,x);
			if (dc1 == aTransprent)//if this color is same then need to be transparent..
			{
				dc1 = cs;
			}
			memDC.SetPixel(y,x,dc1);
		}
	}	
	memDC.SelectObject(hBmOld);
	memDC.DeleteDC();
	bmpSrc.Detach();	

	return hbitmap;	
}
//CLONE A BITMAP TO ANOTHER...
HBITMAP CPlayColor::getCloneBitmap( HBITMAP hBitmap)
{
	// Create a memory DC compatible with the display
	CDC sourceDC, destDC;
	sourceDC.CreateCompatibleDC( NULL );
	destDC.CreateCompatibleDC( NULL );

	// Get logical coordinates
	BITMAP bm;
	::GetObject( hBitmap, sizeof( bm ), &bm );

	// Create a bitmap to hold the result
	HBITMAP hbmResult = ::CreateCompatibleBitmap(CClientDC(NULL),bm.bmWidth, bm.bmHeight);

	// Select bitmaps into the DCs
	HBITMAP hbmOldSource = (HBITMAP)::SelectObject( sourceDC.m_hDC, hBitmap );
	HBITMAP hbmOldDest = (HBITMAP)::SelectObject( destDC.m_hDC, hbmResult );
	destDC.BitBlt( 0, 0, bm.bmWidth, bm.bmHeight, &sourceDC,0,0, SRCCOPY );
	// Reselect the old bitmaps
	::SelectObject( sourceDC.m_hDC, hbmOldSource );
	::SelectObject( destDC.m_hDC, hbmOldDest );

	return hbmResult;
}
//
HBITMAP CPlayColor::getResizeBitmap( HBITMAP hBitmap ,const unsigned int aW,const unsigned int aH)
{
	// Create a memory DC compatible with the display
	CDC sourceDC, destDC;
	sourceDC.CreateCompatibleDC( NULL );
	destDC.CreateCompatibleDC( NULL );
	// Get logical coordinates
	BITMAP bm;
	::GetObject( hBitmap, sizeof( bm ), &bm );
	// Create a bitmap to hold the result
	HBITMAP hbmResult = ::CreateCompatibleBitmap(CClientDC(NULL),aW,aH);
	// Select bitmaps into the DCs
	HBITMAP hbmOldSource = (HBITMAP)::SelectObject( sourceDC.m_hDC, hBitmap );
	HBITMAP hbmOldDest = (HBITMAP)::SelectObject( destDC.m_hDC, hbmResult );
	
	destDC.SetStretchBltMode( HALFTONE);//for better output
	destDC.StretchBlt(0,0,aW,aH,&sourceDC,0,0,bm.bmWidth, bm.bmHeight,SRCCOPY);
	// Reselect the old bitmaps
	::SelectObject( sourceDC.m_hDC, hbmOldSource );
	::SelectObject( destDC.m_hDC, hbmOldDest );
	return hbmResult;
}
//
void CPlayColor::drawBitmap(CDC* pDC,int aX, int aY,  HBITMAP hBitmap)
{
	BITMAP bm;
	CDC memDC;
	memDC.CreateCompatibleDC(NULL);
	::GetObject( hBitmap, sizeof( bm ), &bm );
	HBITMAP hbmOld = (HBITMAP)memDC.SelectObject(hBitmap);
	pDC->BitBlt( aX,aY,bm.bmWidth,bm.bmHeight,&memDC,0,0,SRCCOPY);
	memDC.SelectObject( hbmOld );
	memDC.DeleteDC();
}
//
void CPlayColor::drawBitmapTransparent( CDC* pDC,int aX,int aY,HBITMAP hBitmap,COLORREF aTransprent)
{
	CBitmap bmpSrc;
	BITMAP bmp;
	if(!bmpSrc.Attach(hBitmap))
		return;
	if(!bmpSrc.GetBitmap(&bmp))
		return;
	CDC memDC;
	memDC.CreateCompatibleDC( NULL );   		
	HBITMAP hBmOld = (HBITMAP)::SelectObject( memDC.m_hDC, hBitmap );	
	COLORREF dc1 = aTransprent;
	if (aTransprent == 0)
	{
		aTransprent = memDC.GetPixel(1,1);//GET LET TOP PIXEL AS TRANSPARENT	
	}
	for (int x = 0; x<bmp.bmHeight; x++)
	{
		for (int y = 0; y<bmp.bmWidth; y++)
		{	
			dc1 = memDC.GetPixel(y,x);			
			if (dc1 != aTransprent)//if this color is same then skip
			{
				pDC->SetPixel( y+aX,x+aY,dc1 );
			}						
		}
	}	
	memDC.SelectObject(hBmOld);
	memDC.DeleteDC();
	bmpSrc.Detach();	
}