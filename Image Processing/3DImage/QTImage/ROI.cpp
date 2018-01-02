// ROI.cpp: implementation of the CROI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "qtimage.h"
#include "ROI.h"
#include "MemDC.h"
#include "QTImageDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CQTImageDlg* gpMainDlg;

int  round(double f)
{   
    
	if   ((int)f+0.5>f)   
		
		return   (int)f;   
    
	else   
		
		return   (int)f   +   1;   
    
}

CROI::CROI()
{
	m_base1.Identity();
	m_base2.Identity();
	m_base3.Identity();

	m_sName="New ROI";
	m_color=RGB(0,0,255);
	m_pImage=NULL;

	m_opacity=120;
	m_label=10;
}

CROI::~CROI()
{
	ROI *pROI;
	POSITION pos=m_ROIList.GetHeadPosition();
	while(pos)
	{
		pROI=m_ROIList.GetNext(pos);
		if(pROI->pntNum>0)
		{
			delete pROI->pnts;
		}
		delete pROI;
	}
	m_ROIList.RemoveAll();
}

void CROI::SetBase(Matrix base1,Matrix base2,Matrix base3)
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			m_base1.value[i][j]=base1.value[i][j];
			m_base2.value[i][j]=base2.value[i][j];
			m_base3.value[i][j]=base3.value[i][j];
		}
	}
}

void CROI::SetPoints(ROI* pROI,int num, ROI_POINT *pnts)
{
	if(pROI->pntNum>0)
	{
		delete pROI->pnts;
		pROI->pnts=NULL;
		pROI->pntNum=0;
	}
	
	if(num>0)
	{
		pROI->pntNum=num;
		pROI->pnts=new ROI_POINT[num];
		memcpy(pROI->pnts,pnts,sizeof(ROI_POINT)*num);
	}
}

void CROI::SetColor(COLORREF color)
{
	m_color=color;
}

void CROI::SetName(CString name)
{
	m_sName=name;
}

CString CROI::GetName()
{
	return m_sName;
}

vtkImageData* CROI::GetImage()
{
	return m_pImage;
}

void CROI::SetImage(vtkImageData *pImage)
{
	m_pImage=pImage;
}

ROI* CROI::AddROI()
{
	ROI *pROI=new ROI[1];
	pROI->pntNum=0;
	pROI->color=m_color;
	pROI->alpha=m_opacity/255.0;

	m_ROIList.AddTail(pROI);
	
	return pROI;
}

int CROI::GetCount()
{
	return m_ROIList.GetCount();
}

ROI* CROI::GetAt(int i)
{
	if(i>=0 && i< GetCount())
	{
		return m_ROIList.GetAt(m_ROIList.FindIndex(i));
	}else
	{
		return NULL;
	}
}

void CROI::DrawROI(CDC *pDC, CRect rc,int imageType, int imageIndex)
{
	ROI *pROI;
	POSITION pos=m_ROIList.GetHeadPosition();
	while(pos)
	{
		pROI=m_ROIList.GetNext(pos);
		if(pROI->iImageIndex==imageIndex && pROI->iImageType==imageType)
		{
			DrawROI(pDC,rc,pROI);
		}
	}
}

void CROI::DrawROI(CDC *pDC, CRect rc, ROI *pROI)
{
	double alpha=pROI->alpha;
	if(pROI->pntNum<=0)
		return;
	
	if(!m_pImage)
		return;
	
	int *pDim=m_pImage->GetDimensions();
	int dim[2];
	if(pROI->iImageType==1)
	{
		dim[0]=pDim[0];
		dim[1]=pDim[1];
	}else if(pROI->iImageType==2)
	{
		dim[0]=pDim[0];
		dim[1]=pDim[2];
	}else
	{
		dim[0]=pDim[1];
		dim[1]=pDim[2];
	}

		
	CRgn rgn;
	POINT *pnts=new POINT[pROI->pntNum];
	for(int i=0;i<pROI->pntNum;i++)
	{
		pnts[i].x=rc.Width() * pROI->pnts[i].x/dim[0];
		pnts[i].y=rc.Height() * pROI->pnts[i].y/dim[1];
	}
	rgn.CreatePolygonRgn(pnts,pROI->pntNum,WINDING);
	
	
	

	int cx = rc.Width();
	int cy = rc.Height();
	
	BITMAPINFOHEADER BMI;
				
	ZeroMemory (&BMI, sizeof(BMI));
	BMI.biSize = sizeof(BITMAPINFOHEADER);
	BMI.biWidth = cx;
	BMI.biHeight = cy;
	BMI.biPlanes = 1;
	BMI.biBitCount = 32;
	BMI.biCompression = BI_RGB;   // No compression
				
	BYTE * pDestBits = NULL;
	HBITMAP hbmDest = CreateDIBSection (NULL, (BITMAPINFO *)&BMI, DIB_RGB_COLORS, (void **)&pDestBits, 0, 0l);
				
				
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	HBITMAP hbmpOld = (HBITMAP) ::SelectObject(dc, hbmDest);
	
	CBrush pBrush(pROI->color);
	dc.FillRgn(&rgn,&pBrush);

	TransparentBltWithAlpha(pDC->GetSafeHdc(),rc.left, rc.top, rc.Width(), rc.Height(),
		dc.GetSafeHdc(),0,0,rc.Width(),rc.Height(),RGB(0,0,0),pROI->alpha*255);
	//pDC->BitBlt(rc.left, rc.top, rc.Width(), rc.Height(), &dc, 0, 0, MERGEPAINT);
	
	dc.SelectObject(hbmpOld);
	::DeleteObject(hbmDest);
	dc.DeleteDC();
				
	rgn.DeleteObject();
	delete []pnts;
				
}


void CROI::SetOpacity(int opacity)
{
	m_opacity=opacity;
	ROI *pROI;

	for(int i=0;i<GetCount();i++)
	{
		pROI=GetAt(i);
		pROI->alpha=opacity/255.0;
	}

}

int CROI::GetOpacity()
{
	return m_opacity;
}

COLORREF CROI::GetColor()
{
	return m_color;
}

void CROI::TransparentBltWithAlpha( HDC hdcDest,      // 目标DC
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
					 )
{
	HBITMAP hOldImageBMP, hImageBMP = CreateCompatibleBitmap(hdcDest, nWidthDest, nHeightDest);	// 创建兼容位图
	HDC		hImageDC = CreateCompatibleDC(hdcDest);
	hOldImageBMP = (HBITMAP)SelectObject(hImageDC, hImageBMP);
	
	// 将目标DC中的位图拷贝到临时DC中
	BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hdcDest, nXOriginDest, nYOriginDest, SRCCOPY);
			
	::TransparentBlt(hImageDC,0, 0, nWidthDest, nHeightDest,
		hdcSrc,nXOriginSrc,nYOriginSrc,nWidthSrc,nHeightSrc,
		crTransparent);

	BLENDFUNCTION blend;
	blend.BlendOp =AC_SRC_OVER;
	blend.BlendFlags=0;
	blend.SourceConstantAlpha=alpha;
	blend.AlphaFormat=0;
	::AlphaBlend(hdcDest,nXOriginDest,nYOriginDest,nWidthDest,nHeightDest,
		hImageDC,0,0,nWidthDest, nHeightDest,
		blend);
		

	SelectObject(hImageDC, hOldImageBMP);
	DeleteDC(hImageDC);
	DeleteObject(hImageBMP);
	
}

BOOL CROI::PtInRegion(int x, int y, int z, ROI *pROI)
{
	CQTImageDlg* pMainDlg = gpMainDlg;
	
	Matrix m1(4,4),m2(4,4),m3(4,4),mTmp(4,4);
	pMainDlg->m_seriesManager.GetBase(m_pImage,m1,m2,m3);

	if(pROI->iImageType==1)
	{
		if(z!=pROI->iImageIndex)
		{
			return FALSE;
		}
		CRgn rgn;
		POINT *pnts=new POINT[pROI->pntNum];
		for(int i=0;i<pROI->pntNum;i++)
		{
			pnts[i].x=pROI->pnts[i].x;
			pnts[i].y=pROI->pnts[i].y;
		}
		rgn.CreatePolygonRgn(pnts,pROI->pntNum,WINDING);
		delete []pnts;

		POINT pnt;
		pnt.x=x;pnt.y=y;
		if(rgn.PtInRegion(pnt))
		{
			return TRUE;
		}else
		{
			return FALSE;
		}
	}

	if(pROI->iImageType==2)
	{
		Vector v(4),vNew(4);
		v.value[0]=x;
		v.value[1]=y;
		v.value[2]=z;
		v.value[3]=1;

		v=m1 * v;

		Matrix m=m2.Inverse();
		vNew=m * v;
		
		x=round(vNew.value[0]);
		y=round(vNew.value[1]);
		z=round(vNew.value[2]);

		if(z!=pROI->iImageIndex)
		{
			return FALSE;
		}
		CRgn rgn;
		POINT *pnts=new POINT[pROI->pntNum];
		for(int i=0;i<pROI->pntNum;i++)
		{
			pnts[i].x=pROI->pnts[i].x;
			pnts[i].y=pROI->pnts[i].y;
		}
		rgn.CreatePolygonRgn(pnts,pROI->pntNum,WINDING);
		delete []pnts;

		POINT pnt;
		pnt.x=x;pnt.y=y;
		if(rgn.PtInRegion(pnt))
		{
			return TRUE;
		}else
		{
			return FALSE;
		}
	}

	if(pROI->iImageType==3)
	{
		Vector v(4),vNew(4);
		v.value[0]=x;
		v.value[1]=y;
		v.value[2]=z;
		v.value[3]=1;

		v=m1 * v;

		Matrix m=m3.Inverse();
		vNew=m * v;
		
		x=round(vNew.value[0]);
		y=round(vNew.value[1]);
		z=round(vNew.value[2]);

		if(z!=pROI->iImageIndex)
		{
			return FALSE;
		}
		CRgn rgn;
		POINT *pnts=new POINT[pROI->pntNum];
		for(int i=0;i<pROI->pntNum;i++)
		{
			pnts[i].x=pROI->pnts[i].x;
			pnts[i].y=pROI->pnts[i].y;
		}
		rgn.CreatePolygonRgn(pnts,pROI->pntNum,WINDING);
		delete []pnts;

		POINT pnt;
		pnt.x=x;pnt.y=y;
		if(rgn.PtInRegion(pnt))
		{
			return TRUE;
		}else
		{
			return FALSE;
		}
	}
	return FALSE;
}



void CROI::SetLabel(short label)
{
	m_label=label;
}

short CROI::GetLabel()
{
	return m_label;
}
