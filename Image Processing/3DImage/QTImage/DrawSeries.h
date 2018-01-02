// DrawSeries.h: interface for the CDrawSeries class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWSERIES_H__92675B45_C6A6_4757_90A3_A5A90026C905__INCLUDED_)
#define AFX_DRAWSERIES_H__92675B45_C6A6_4757_90A3_A5A90026C905__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "vtkImageData.h"
#include "LUT.h"

class CDrawSeries  
{
public:
	void Draw(CDC *pDC, CRect rc, vtkImageData *pBaseImage,vtkImageData *pSegmentedImage, int iSlice, int iImageType,double alpha,COLORREF color);
	void Draw(CDC *pDC, CRect rc, vtkImageData *pBaseImage, int iSlice, int iImageType);
	void Draw(CDC *pDC,  CRect rect,vtkImageData *pImage, int index=-1);
	void SetBKColor(COLORREF color);
	void GetRealDrawRect(CRect &rc);
	void EnableAutoWindowLevel();
	void SetWindowLevel(UINT window,UINT level);
	
	CDrawSeries();
	virtual ~CDrawSeries();

private:
	void CalcRealRect(double dWidthOfImage,double dHeightOfImage, int nx,int ny,CRect rcPaint);
	void TransparentBltWithAlpha( HDC hdcDest,      // 目标DC
					 int nXOriginDest,   // 目标X偏移
					 int nYOriginDest,   // 目标Y偏移
					 int nWidthDest,     // 目标宽度
					 int nHeightDest,    // 目标高度
					 HDC hdcSrc,         // 源DC
					 int nXOriginSrc,    // 源X起点
					 int nYOriginSrc,    // 源Y起点
					 int nWidthSrc,      // 源宽度
					 int nHeightSrc,     // 源高度
					 UINT crTransparent,  // 透明色,COLORREF类型
					 unsigned char alpha         //alpha 
					 );

	CBitmap* GetBitmapByDataOfImage( short nWidthOfImage, short nHeightOfImage, unsigned short* pnDataOfImage,
													int nWidth, int nLevel, CDC* pPaintDC );

	void StretchBitmap(double nWidthOfImage,double nHeightOfImage, CBitmap* pBitmap,CDC* pPaintDC,CRect rcPaint);

	CBitmap*	m_pBitmap;
	CLUT32		m_oLut32;	// 32 bits
	CLUT		m_oLut;		// 4  bits
	UINT m_Window,m_Level;
	BOOL m_bAutoWindowLevel;
	COLORREF m_bkColor;
	CRect m_rcRealDraw;

};

#endif // !defined(AFX_DRAWSERIES_H__92675B45_C6A6_4757_90A3_A5A90026C905__INCLUDED_)
