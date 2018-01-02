// ROI.h: interface for the CROI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROI_H__46256432_F294_4DE0_9004_7E0B73DE0DBB__INCLUDED_)
#define AFX_ROI_H__46256432_F294_4DE0_9004_7E0B73DE0DBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GlobalHeader.h"
#include "Mv.h"
#include "vtkImageData.h"

class CROI  
{
public:
	short GetLabel();
	void SetLabel(short label);
	BOOL PtInRegion(int x,int y,int z,ROI *pROI);

	
	int GetOpacity();
	void SetOpacity(int opacity);

	void DrawROI(CDC *pDC,CRect rc,int imageType,int imageIndex);
	void DrawROI(CDC *pDC, CRect rc, ROI *pROI);

	ROI* GetAt(int i);
	int GetCount();
	ROI* AddROI();

	void SetImage(vtkImageData *pImage);
	vtkImageData* GetImage();

	CString GetName();
	void SetName(CString name);
	void SetColor(COLORREF color);
	COLORREF GetColor();

	void SetPoints(ROI* pROI,int num,ROI_POINT *pnts);
	void SetBase(Matrix base1,Matrix base2,Matrix base3);

	CROI();
	virtual ~CROI();

private:
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
	CList<ROI*,ROI*> m_ROIList;
	Matrix m_base1,m_base2,m_base3;
	CString m_sName;
	vtkImageData *m_pImage;
	COLORREF m_color;

	int m_opacity;

	short m_label;
};

#endif // !defined(AFX_ROI_H__46256432_F294_4DE0_9004_7E0B73DE0DBB__INCLUDED_)
