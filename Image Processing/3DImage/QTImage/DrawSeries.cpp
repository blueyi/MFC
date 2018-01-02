// DrawSeries.cpp: implementation of the CDrawSeries class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QTImage.h"
#include "DrawSeries.h"
#include "QTImageDlg.h"
#include "Buffer.h"
#include "mv.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CQTImageDlg* gpMainDlg;

CDrawSeries::CDrawSeries()
{
	m_pBitmap = new CBitmap();
	m_Window=4096;
	m_Level=2048;
	m_bAutoWindowLevel=FALSE;
	m_bkColor=RGB(0,0,0);
}

CDrawSeries::~CDrawSeries()
{
	delete m_pBitmap;
}

void CDrawSeries::Draw(CDC *pDC, CRect rect,vtkImageData *pImage, int index)
{
	int *pDim=pImage->GetDimensions();
	if(index<0)
	{
		index=pDim[2]/2;
	}

	CBitmap* pBitmap;

	
	unsigned short *pData=(unsigned short *)pImage->GetScalarPointer(0,0,0);
	double *space=pImage->GetSpacing();
	double dFov[2];
	dFov[0]=(space[0]*pDim[0]);
	dFov[1]=(space[1]*pDim[1]);

	pData+=index*pDim[0]*pDim[1];

	int window,level;
	if(m_bAutoWindowLevel)
	{
		unsigned short min=9999,max=0;
		double *pp=pImage->GetScalarRange();
		min=pp[0];
		max=pp[1];
		window=max-min;
		level=min+window/2;
	}else
	{
		window=m_Window;
		level=m_Level;
	}

	
	pBitmap = GetBitmapByDataOfImage( pDim[0], pDim[1], pData, window, level, pDC);

	if(pBitmap)
	{
		StretchBitmap(dFov[0],dFov[1],pBitmap,pDC,rect);
	}
	if(pBitmap) pBitmap->DeleteObject();
}

void CDrawSeries::StretchBitmap(double nWidthOfImage,double nHeightOfImage, CBitmap* pBitmap,CDC* pPaintDC,CRect rcPaint)
{
	
	CSize mySize = pBitmap->GetBitmapDimension();

	short nWidthOfDisplay, nHeightOfDisplay;
	nWidthOfDisplay=rcPaint.Width();
	nHeightOfDisplay=rcPaint.Height();

	CDC dcMem1;
	CBitmap *pOldBmp;

    dcMem1.CreateCompatibleDC(pPaintDC);
    pOldBmp=dcMem1.SelectObject(pBitmap);

	pPaintDC->SetStretchBltMode(HALFTONE);
	
	int left,top,width,height;
	float ratio1=(float)nWidthOfImage/(float)nHeightOfImage;
	float ratio2=(float)nWidthOfDisplay/(float)nHeightOfDisplay;
	if(ratio2>ratio1)
	{
		height=nHeightOfDisplay;
		width=nHeightOfDisplay*ratio1;
		top=0;
		left=(nWidthOfDisplay-width)/2.0;
	}else if(ratio2<ratio1)
	{
		width=nWidthOfDisplay;
		height=nWidthOfDisplay/ratio1;
		top=(nHeightOfDisplay-height)/2.0;
		left=0;
	}else
	{
		left=0;
		top=0;
		width=nWidthOfDisplay;
		height=nHeightOfDisplay;
	}
	
	pPaintDC->FillSolidRect(rcPaint.left,rcPaint.top,nWidthOfDisplay,nHeightOfDisplay,m_bkColor);
	left+=rcPaint.left;
	top+=rcPaint.top;

    pPaintDC->StretchBlt( left, 
		top, 
		width, 
		height,
		&dcMem1, 
		0, 
		0, 
		mySize.cx,
		mySize.cy,
		SRCCOPY );
	
	dcMem1.SelectObject(pOldBmp);
    dcMem1.DeleteDC();

	m_rcRealDraw.left=left;
	m_rcRealDraw.top=top;
	m_rcRealDraw.right=left+width;
	m_rcRealDraw.bottom=top+height;
}

void CDrawSeries::CalcRealRect(double dWidthOfImage,double dHeightOfImage, int nx,int ny,CRect rcPaint)
{
	
	CSize mySize(nx,ny);

	short nWidthOfDisplay, nHeightOfDisplay;
	nWidthOfDisplay=rcPaint.Width();
	nHeightOfDisplay=rcPaint.Height();

	
	int left,top,width,height;
	float ratio1=(float)dWidthOfImage/(float)dHeightOfImage;
	float ratio2=(float)nWidthOfDisplay/(float)nHeightOfDisplay;
	if(ratio2>ratio1)
	{
		height=nHeightOfDisplay;
		width=nHeightOfDisplay*ratio1;
		top=0;
		left=(nWidthOfDisplay-width)/2.0;
	}else if(ratio2<ratio1)
	{
		width=nWidthOfDisplay;
		height=nWidthOfDisplay/ratio1;
		top=(nHeightOfDisplay-height)/2.0;
		left=0;
	}else
	{
		left=0;
		top=0;
		width=nWidthOfDisplay;
		height=nHeightOfDisplay;
	}
	
	
	left+=rcPaint.left;
	top+=rcPaint.top;
    
	m_rcRealDraw.left=left;
	m_rcRealDraw.top=top;
	m_rcRealDraw.right=left+width;
	m_rcRealDraw.bottom=top+height;
}


CBitmap* CDrawSeries::GetBitmapByDataOfImage( short nWidthOfImage, short nHeightOfImage, unsigned short* pnDataOfImage,
															int nWidth, int nLevel, CDC* pPaintDC )
{
    // Find out the color depth of the current display mode.
    
    int nDepthOfColor = pPaintDC->GetDeviceCaps(BITSPIXEL);

    // mapping the image data to grayscale bitmap.
    BOOL bCreated = m_pBitmap->CreateCompatibleBitmap(pPaintDC, nWidthOfImage, nHeightOfImage);
		
    int nArraySize = nWidthOfImage * nHeightOfImage;

    if (nDepthOfColor == 32)
    {
		if (m_oLut32.GetWidth() != nWidth || m_oLut32.GetLevel() != nLevel)
		{
			m_oLut32.SetWidth( nWidth );
			m_oLut32.SetLevel( nLevel );
			m_oLut32.Update();
		}

        CBuffer<int> bits;		
        bits.SetSize(nArraySize, false);

        for (int i = 0; i < nArraySize; i++)
        {
			if ( pnDataOfImage[i] < 0 || pnDataOfImage[i] >= 65536 /*4096*/ )
			{
				bits[i] = RGB(255,255,255);
			}
			else
			{
				bits[i] =  m_oLut32[pnDataOfImage[i]];
			}
			
        }

        m_pBitmap->SetBitmapBits(nArraySize * 4, bits.GetBuffer()); 
    }

    else if (nDepthOfColor == 24)
    {
		if (m_oLut.GetWidth() != nWidth || m_oLut.GetLevel() != nLevel)
		{
			m_oLut.SetWidth( nWidth );
			m_oLut.SetLevel( nLevel );
			m_oLut.Update();
		}
		
        CBuffer<BYTE> bits;
        bits.SetSize(nArraySize * 3, true /* set to zero */);

        for (int i = 0, k = 0; i < nArraySize; i++)
        {
            bits[k++] = bits[k++] = bits[k++] = m_oLut[pnDataOfImage[i]];
        }

        m_pBitmap->SetBitmapBits(nArraySize * 3, bits.GetBuffer());
    }
	
    else
    {
        return NULL;
    }
	m_pBitmap->SetBitmapDimension(nWidthOfImage, nHeightOfImage);

	return m_pBitmap;
}

void CDrawSeries::SetWindowLevel(UINT window, UINT level)
{
	m_Window=window;
	m_Level=level;
}

void CDrawSeries::EnableAutoWindowLevel()
{
	m_bAutoWindowLevel=TRUE;
}

void CDrawSeries::GetRealDrawRect(CRect &rc)
{
	rc.left=m_rcRealDraw.left;
	rc.top=m_rcRealDraw.top;
	rc.right=m_rcRealDraw.right;
	rc.bottom=m_rcRealDraw.bottom;
	TRACE("%i %i %i %i\n",rc.left,rc.top,rc.right,rc.bottom);
}

void CDrawSeries::SetBKColor(COLORREF color)
{
	m_bkColor=color;
}

void CDrawSeries::Draw(CDC *pDC, CRect rc, vtkImageData *pBaseImage, vtkImageData *pSegmentedImage, int iSlice, int iImageType,double alpha,COLORREF color)
{
	
	if(pBaseImage==NULL || pSegmentedImage==NULL)
		return;

	int *pDim=pBaseImage->GetDimensions();
	int dim[3];
	if(iImageType==1)
	{
		dim[0]=pDim[0];
		dim[1]=pDim[1];
		dim[2]=pDim[2];
	}else if(iImageType==2)
	{
		dim[0]=pDim[0];
		dim[1]=pDim[2];
		dim[2]=pDim[1];
	}else
	{
		dim[0]=pDim[1];
		dim[1]=pDim[2];
		dim[2]=pDim[0];
	}

	if(iSlice<0 || iSlice >= dim[2])
		return;
		

	unsigned short *pData=(unsigned short *)pSegmentedImage->GetScalarPointer(0,0,0);;

	int cx = dim[0];
	int cy = dim[1];
	
	BITMAPINFOHEADER BMI;
				
	ZeroMemory (&BMI, sizeof(BMI));
	BMI.biSize = sizeof(BITMAPINFOHEADER);
	BMI.biWidth = cx;
	BMI.biHeight = cy;
	BMI.biPlanes = 1;
	BMI.biBitCount = 32;
	BMI.biCompression = BI_RGB;   // No compression
				
	BYTE *pDestBits = NULL;
	HBITMAP hbmDest = CreateDIBSection (NULL, (BITMAPINFO *)&BMI, DIB_RGB_COLORS, (void **)&pDestBits, 0, 0l);
				
				
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	HBITMAP hbmpOld = (HBITMAP) ::SelectObject(dc, hbmDest);
	
	BOOL bFixedColor=TRUE;
	if(color==RGB(0,0,0))
	{
		bFixedColor=FALSE;
	}
	short preLabel=-1;
	COLORREF preColor;
	CQTImageDlg* pMainDlg = gpMainDlg;

	int x,y,z,iTmp;
	for(int i=0;i<cx;i++)
	{
		for(int j=0;j<cy;j++)
		{
			x=i;
			y=j;
			z=iSlice;
			if(iImageType==2)
			{
				
				iTmp=y;
				y=pDim[1]-z-1;
				z=iTmp;
			}else if(iImageType==3)
			{
				
				iTmp=x;
				x=z;
				z=y;
				y=iTmp;
			}

			int index=z*pDim[0]*pDim[1]+y*pDim[0]+x;
			if(pData[index]>0)
			{
				if(bFixedColor)
				{
					pDestBits[((cy-1-j)*cx+i)*4]=GetBValue(color);
					pDestBits[((cy-1-j)*cx+i)*4+1]=GetGValue(color);
					pDestBits[((cy-1-j)*cx+i)*4+2]=GetRValue(color);
				}else
				{
					if(preLabel!=pData[index])
					{
						preLabel=pData[index];
						preColor=pMainDlg->m_roiManager.GetColorByLabel(preLabel);
					}
					pDestBits[((cy-1-j)*cx+i)*4]=GetBValue(preColor);
					pDestBits[((cy-1-j)*cx+i)*4+1]=GetGValue(preColor);
					pDestBits[((cy-1-j)*cx+i)*4+2]=GetRValue(preColor);
				}
			}
		}
	}

	TransparentBltWithAlpha(pDC->GetSafeHdc(),rc.left, rc.top, rc.Width(), rc.Height(),
		dc.GetSafeHdc(),0,0,cx,cy,RGB(0,0,0),alpha*255);
	
	
	dc.SelectObject(hbmpOld);
	::DeleteObject(hbmDest);
	dc.DeleteDC();
}


void CDrawSeries::Draw(CDC *pDC, CRect rc, vtkImageData *pBaseImage, int iSlice, int iImageType)
{
	if(!pBaseImage)
		return;

	double alpha=1.0;
	
	int *pDim=pBaseImage->GetDimensions();
	double *dSpace=pBaseImage->GetSpacing();
	double dFov[3];
	dFov[0]=(dSpace[0]*pDim[0]);
	dFov[1]=(dSpace[1]*pDim[1]);
	dFov[2]=(dSpace[2]*pDim[2]);

	int dim[3];
	double fov[3];
	if(iImageType==1)
	{
		dim[0]=pDim[0];
		dim[1]=pDim[1];
		dim[2]=pDim[2];

		fov[0]=dFov[0];
		fov[1]=dFov[1];
		fov[2]=dFov[2];
	}else if(iImageType==2)
	{
		dim[0]=pDim[0];
		dim[1]=pDim[2];
		dim[2]=pDim[1];

		fov[0]=dFov[0];
		fov[1]=dFov[2];
		fov[2]=dFov[1];
	}else
	{
		dim[0]=pDim[1];
		dim[1]=pDim[2];
		dim[2]=pDim[0];

		fov[0]=dFov[1];
		fov[1]=dFov[2];
		fov[2]=dFov[0];
	}

	if(iSlice<0 || iSlice >= dim[2])
		return;
		

	CalcRealRect(fov[0],fov[1],dim[0],dim[1],rc);

	int nWidth=4096;
	int nLevel=2048;
	if(m_bAutoWindowLevel)
	{
		unsigned short min=9999,max=0;
		double *pp=pBaseImage->GetScalarRange();
		min=pp[0];
		max=pp[1];
		nWidth=max-min;
		nLevel=min+nWidth/2;
	}
	if (m_oLut32.GetWidth() != nWidth || m_oLut32.GetLevel() != nLevel)
	{
		m_oLut32.SetWidth( nWidth );
		m_oLut32.SetLevel( nLevel );
		m_oLut32.Update();
	}  

	unsigned short *pData=(unsigned short *)pBaseImage->GetScalarPointer(0,0,0);;

	int cx = dim[0];
	int cy = dim[1];
	
	BITMAPINFOHEADER BMI;
				
	ZeroMemory (&BMI, sizeof(BMI));
	BMI.biSize = sizeof(BITMAPINFOHEADER);
	BMI.biWidth = cx;
	BMI.biHeight = cy;
	BMI.biPlanes = 1;
	BMI.biBitCount = 32;
	BMI.biCompression = BI_RGB;   // No compression
				
	BYTE *pDestBits = NULL;
	HBITMAP hbmDest = CreateDIBSection (NULL, (BITMAPINFO *)&BMI, DIB_RGB_COLORS, (void **)&pDestBits, 0, 0l);
				
				
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	HBITMAP hbmpOld = (HBITMAP) ::SelectObject(dc, hbmDest);
	
	int x,y,z,iTmp;
	for(int i=0;i<cx;i++)
	{
		for(int j=0;j<cy;j++)
		{
			x=i;
			y=j;
			z=iSlice;
			if(iImageType==2)
			{
				
				iTmp=y;
				y=pDim[1]-z;
				z=iTmp;
			}else if(iImageType==3)
			{
				
				iTmp=x;
				x=z;
				z=y;
				y=iTmp;
			}

			int index=z*pDim[0]*pDim[1]+y*pDim[0]+x;
			int bits=m_oLut32[pData[index]];
			BYTE *bit=(BYTE*)(&bits);
			pDestBits[((cy-1-j)*cx+i)*4]=GetRValue(bits);
			pDestBits[((cy-1-j)*cx+i)*4+1]=GetGValue(bits);
			pDestBits[((cy-1-j)*cx+i)*4+2]=GetBValue(bits);
			
		}
	}

	pDC->FillSolidRect(rc,m_bkColor);
	pDC->SetStretchBltMode(HALFTONE);
	pDC->StretchBlt(m_rcRealDraw.left, m_rcRealDraw.top, m_rcRealDraw.Width(), m_rcRealDraw.Height(),
		&dc,0,0,cx,cy,SRCCOPY);
	
	
	dc.SelectObject(hbmpOld);
	::DeleteObject(hbmDest);
	dc.DeleteDC();
}


void CDrawSeries::TransparentBltWithAlpha( HDC hdcDest,      // 目标DC
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