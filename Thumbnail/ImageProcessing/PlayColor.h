//######################################################################
//# FILENAME: CPlayColor.h
//#
//# DESCRIPTION:	PERFORM Fade effect, Draw bitmap transparently,
//#					Horizontal gradient, Vertical gradient, Copy HBITMAP,
//#					Transparent HBITMAP ---bitmap from HBITMAP, Resize HBITMAP,
//#					GET THE PREVIEW OF WHOLE DRAWING.
//# AUTHOR:		Mohammad Saiful Alam (Jewel)
//# POSITION:	Senior Software Engineer
//# E-MAIL:		saiful.alam@ bjitgroup.com
//# CREATE DATE: 2008/02/1
//#
//# Copyright (c) 2007 BJIT Ltd.
//######################################################################

#ifndef _CPlayColor_H_
#define _CPlayColor_H_

class CPlayColor  
{
public:
	//TEST
	CRect mClientRect;
	CRect mDirtyRect;
	int mAlpha;
	CPoint mPoint;
	//TEST
	CPlayColor();
	virtual ~CPlayColor();
	void draw(CDC* pDC);
	//
	void fadeColor(const unsigned int aClrSrc,unsigned int& aClrDest,const int aPercent = 100);
	//
	void hgradient(CDC* pDC,const unsigned int aClrSrc,const unsigned int aClrDest,const CRect aRect);
	//
	void vgradient(CDC* pDC,const unsigned int aClrSrc,const unsigned int aClrDest,const CRect aRect);
	//
	void setGradientColor(const COLORREF aSrcClr,const COLORREF aDestClr);
	//
	HBITMAP fadeBitmap(HBITMAP aBitmap,const COLORREF aFadeto,const int aTransparency = 0);
	//
	HBITMAP getTransparentBitmap( CDC* pSrcDC,CPoint aImgCorner,HBITMAP aBitmap,COLORREF aTransprent);
	//
	HBITMAP getCloneBitmap( HBITMAP hBitmap );
	//
	HBITMAP getResizeBitmap( HBITMAP hBitmap ,const unsigned int aW,const unsigned int aH);
	//
	void drawBitmap(CDC* pDC,int aX, int aY,  HBITMAP hBitmap);
	//
	void drawBitmapTransparent( CDC* pDC,int aX,int aY,HBITMAP hBitmap,COLORREF aTransprent);
private:
	COLORREF mSrcColor[5];
	COLORREF mDestColor[5];
	//USED FOR TEST PURPOSE
	HBITMAP mBitmap;
	HBITMAP mBitmapCheck;
	HBITMAP mBitmapCheckTrans;	
	//NOT NEDDED...ONLY FOR TEST PURPOSE
};

#endif