// LineChartCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "LineChartCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLineChartCtrl

CLineChartCtrl::CLineChartCtrl()
{
	m_iCurSel=-1;
	m_iMode=0;
	m_iRadius=5;
	SetPixelRange(0,4000);
	m_bLeftBtnDown=FALSE;
	m_grayHistogram=NULL;
	m_bRedrawHistogram=TRUE;
	m_pOldBitmap=NULL;
	m_pOldBitmapBK=NULL;
}

CLineChartCtrl::~CLineChartCtrl()
{
	
}


BEGIN_MESSAGE_MAP(CLineChartCtrl, CStatic)
//{{AFX_MSG_MAP(CLineChartCtrl)
ON_WM_PAINT()
ON_WM_LBUTTONDOWN()
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONUP()
ON_WM_RBUTTONDOWN()
ON_WM_MBUTTONDOWN()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLineChartCtrl message handlers

void CLineChartCtrl::OnPaint() 
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


void CLineChartCtrl::DrawLine()
{
	CClientDC dc(this);
	CRect rcClient;
	GetClientRect(rcClient);
	
	if (m_memDC.GetSafeHdc() == NULL)
	{
		m_memDC.CreateCompatibleDC(&dc);
		m_bitmap.CreateCompatibleBitmap(&dc,rcClient.Width(),rcClient.Height());
		m_pOldBitmap=m_memDC.SelectObject(&m_bitmap);
		
	}else
	{
		m_memDC.SelectObject(m_pOldBitmap);
		m_bitmap.DeleteObject();
		m_bitmap.CreateCompatibleBitmap(&dc,rcClient.Width(),rcClient.Height());
		m_pOldBitmap=m_memDC.SelectObject(&m_bitmap);
	}
	
	if (m_memDC.GetSafeHdc() != NULL)
	{
		m_memDC.SetBkColor(RGB(100,100,100));
		m_memDC.FillSolidRect(rcClient,RGB(100,100,100));
		
		DrawHistogram(&m_memDC);
		
		IA_PIXEL_ITEM item;
		if(m_iMode==1 || m_iMode==0)
		{
			for(int i=0;i<rcClient.Width();i++)
			{
				GetValue(i,rcClient.Height()/2,item.pixel,item.opacity);
				COLORREF color;
				GetPixelColor(item.pixel,color);
				CPen penTmp(PS_SOLID,1,color);
				CPen* pOldPenTmp=m_memDC.SelectObject(&penTmp);
				m_memDC.MoveTo(i,0);
				m_memDC.LineTo(i,10);
				m_memDC.SelectObject(pOldPenTmp);
			}
		}

		CPen penBlack(PS_SOLID, 1, RGB(0,0,0));
		CPen* pOldPen = m_memDC.SelectObject(&penBlack);
		
		
		int x,y;
		BOOL bFirst=TRUE;
		POSITION pos=m_itemList.GetHeadPosition();
		while(pos)
		{
			item=m_itemList.GetNext(pos);
			GetPos(item.pixel,item.opacity,x,y);
			if(bFirst)
			{
				m_memDC.MoveTo(x,y);
				bFirst=FALSE;
			}else
			{
				m_memDC.LineTo(x,y);
			}
			
		}
		m_memDC.SelectObject(pOldPen);
		
		CPen penRed(PS_SOLID, 1, RGB(255,0,0));
		CBrush brushRed(RGB(255,0,0));  
		CBrush *pOldBrush;
		
		m_memDC.SelectObject(&penBlack);
		int iCount=0;
		pos=m_itemList.GetHeadPosition();
		while(pos)
		{
			
			item=m_itemList.GetNext(pos);
			GetPos(item.pixel,item.opacity,x,y);
			
			CBrush brushTmp(item.color);
			
			pOldBrush=NULL;
			if(m_iMode==1 || m_iMode==0)
			{
				pOldBrush=m_memDC.SelectObject(&brushTmp);
			}else if(iCount==m_iCurSel)
			{
				pOldBrush=m_memDC.SelectObject(&brushRed);
			}
			
			if(iCount==m_iCurSel)
			{
				m_memDC.Ellipse(x-m_iRadius-2,y-m_iRadius-2,x+m_iRadius+2,y+m_iRadius+2);
			}else
			{
				m_memDC.Ellipse(x-m_iRadius,y-m_iRadius,x+m_iRadius,y+m_iRadius);
			}
			
			if(pOldBrush)
			{
				m_memDC.SelectObject(pOldBrush);
			}
			
			
			iCount++;
		}
		
	}
	Invalidate(FALSE);
}

void CLineChartCtrl::SetPixelRange(unsigned short min, unsigned short max)
{
	m_pixelRange[0]=min;
	m_pixelRange[1]=max;
	if(m_iMode!=1)
	{
		m_valueRange[0]=0;
		m_valueRange[1]=1;
	}else
	{
		m_valueRange[0]=0.5;
		m_valueRange[1]=0.5;
	}
	
	IA_PIXEL_ITEM item;
	m_itemList.RemoveAll();
	
	item.pixel=m_pixelRange[0];
	item.opacity=m_valueRange[0];
	item.color=RGB(0,255,0);
	m_itemList.AddTail(item);
	
	if(m_iMode==1)
	{
		item.pixel=(m_pixelRange[1]-m_pixelRange[0])/2;
		item.opacity=(m_valueRange[1]-m_valueRange[0])/2;
		item.color=RGB(255,255,0);
		m_itemList.AddTail(item);
	}
	
	item.pixel=m_pixelRange[1];
	item.opacity=m_valueRange[1];
	item.color=RGB(255,0,0);
	m_itemList.AddTail(item);
	
}

void CLineChartCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	IA_PIXEL_ITEM itemNew;
	GetValue(point.x,point.y,itemNew.pixel,itemNew.opacity);

	int xNew,yNew;
	GetPos(itemNew.pixel,itemNew.opacity,xNew,yNew);
	if(fabs(point.x-xNew)>20)
	{
		int i=0;
	}

	AddItem(itemNew);
	
	m_bLeftBtnDown=TRUE;
	
	CStatic::OnLButtonDown(nFlags, point);
}

void CLineChartCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_iCurSel<0 || m_bLeftBtnDown==FALSE)
		return;
	
	POSITION pos;
	IA_PIXEL_ITEM item;
	GetValue(point.x,point.y,item.pixel,item.opacity);
	if(m_iCurSel==0)
	{
		item.pixel=m_pixelRange[0];
	}else if(m_iCurSel==m_itemList.GetCount()-1)
	{
		item.pixel=m_pixelRange[1];
	}else
	{
		IA_PIXEL_ITEM itemPre;
		IA_PIXEL_ITEM itemNext;
		pos=m_itemList.FindIndex(m_iCurSel-1);
		if(pos)
			itemPre=m_itemList.GetNext(pos);
		pos=m_itemList.FindIndex(m_iCurSel+1);
		if(pos)
			itemNext=m_itemList.GetNext(pos);
		
		if(item.pixel<=itemPre.pixel)
			item.pixel=itemPre.pixel+1;
		if(item.pixel>=itemNext.pixel)
			item.pixel=itemNext.pixel-1;
	}
	if(m_bLeftBtnDown && m_iCurSel>=0)
	{
		
		pos=m_itemList.FindIndex(m_iCurSel);
		if(pos)
		{
			IA_PIXEL_ITEM itemOld=m_itemList.GetAt(pos);
			item.color=itemOld.color;
			if(m_iCurSel==m_itemList.GetCount()-1)
			{
				m_itemList.RemoveAt(pos);
				m_itemList.AddTail(item);
			}else
			{
				m_itemList.RemoveAt(pos);
				pos=m_itemList.FindIndex(m_iCurSel);
				m_itemList.InsertBefore(pos,item);
			}
		}
	}
	
	DrawLine();
	
	Notify();
	
	CStatic::OnMouseMove(nFlags, point);
}

void CLineChartCtrl::GetPos(unsigned short pixel, float value, int &x, int &y)
{
	CRect rcClient;
	GetClientRect(&rcClient);
	x=m_iRadius+(int)(rcClient.Width()-m_iRadius*2)*(pixel-m_pixelRange[0])/(m_pixelRange[1]-m_pixelRange[0]);
	if(m_iMode!=1)
	{
		y=rcClient.Height() - m_iRadius - (int)((rcClient.Height()-m_iRadius*2)*((value-m_valueRange[0])/(m_valueRange[1]-m_valueRange[0])));
	}else
	{
		y=rcClient.Height()/2;
	}
	
}

void CLineChartCtrl::GetValue(int x, int y, unsigned short &pixel, float &value)
{
	short pixelValue;
	CRect rcClient;
	GetClientRect(rcClient);
	pixelValue = m_pixelRange[0]+(x-m_iRadius)*(m_pixelRange[1]-m_pixelRange[0])/(rcClient.Width()-m_iRadius*2);
	value = m_valueRange[0] + (rcClient.Height()-y-m_iRadius) *(m_valueRange[1]-m_valueRange[0]) / (rcClient.Height()-m_iRadius*2);
	if(pixelValue<m_pixelRange[0])
		pixelValue=m_pixelRange[0];
	if(pixelValue>m_pixelRange[1])
		pixelValue=m_pixelRange[1];
	if(value<m_valueRange[0])
		value=m_valueRange[0];
	if(value>m_valueRange[1])
		value=m_valueRange[1];
	pixel=pixelValue;
}

void CLineChartCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bLeftBtnDown=FALSE;
	IA_PIXEL_ITEM item;

	CWnd *parent=this->GetParent();
	int iResult=11;
	if(m_iMode==1)
	{
		iResult=21;
	}else if(m_iMode==2)
	{
		iResult=31;
	}
		
	parent->SendMessage(WM_NOTIFY,WPARAM(&iResult),LPARAM(&item));

	CStatic::OnLButtonUp(nFlags, point);	
}



void CLineChartCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_iCurSel<0 && m_iMode!=2)
		return;
	
	IA_PIXEL_ITEM item;
	POSITION pos=m_itemList.FindIndex(m_iCurSel);
	item=m_itemList.GetAt(pos);
	
	CColorDialog dlg(item.color, CC_FULLOPEN);
	dlg.DoModal();
	
	item.color=dlg.GetColor();
	
	if(m_iCurSel==m_itemList.GetCount()-1)
	{
		m_itemList.RemoveAt(pos);
		m_itemList.AddTail(item);
	}else
	{
		m_itemList.RemoveAt(pos);
		pos=m_itemList.FindIndex(m_iCurSel);
		m_itemList.InsertBefore(pos,item);
	}
	
	Notify();
	
	DrawLine();
	
	CStatic::OnRButtonDown(nFlags, point);
}

void CLineChartCtrl::AddItem(IA_PIXEL_ITEM itemNew)
{
	if(itemNew.pixel<m_pixelRange[0] ||
		itemNew.pixel>m_pixelRange[1])
		return;
	
	m_iCurSel=-1;
	int iCount=0;
	int iInsertIndex=m_itemList.GetCount()-1;
	BOOL bFind=FALSE;
	IA_PIXEL_ITEM item;
	int x,y;
	int xNew,yNew;
	GetPos(itemNew.pixel,itemNew.opacity,xNew,yNew);
	
	POSITION pos=m_itemList.GetHeadPosition();
	while(pos)
	{
		item=m_itemList.GetNext(pos);
		GetPos(item.pixel,item.opacity,x,y);
		if(abs(xNew-x)<m_iRadius && abs(yNew-y)<m_iRadius)
		{
			m_iCurSel=iCount;
			break;
		}
		
		/*按照从小到大的排序，可能的插入位置*/
		if(!bFind && itemNew.pixel<item.pixel)
		{
			iInsertIndex=iCount;
			bFind=TRUE;
		}
		
		
		iCount++;
		
	}
	
	if(m_iCurSel<0) //没有找到则插入
	{
		
		pos=m_itemList.FindIndex(iInsertIndex);
		if(pos)
		{
			GetPixelColor(itemNew.pixel,itemNew.color);
			m_itemList.InsertBefore(pos,itemNew);
			m_iCurSel=iInsertIndex;
		}
		
	}
	
	Notify();
	
	DrawLine();
}

void CLineChartCtrl::GetPixelColor(int pixel, COLORREF &color)
{
	IA_PIXEL_ITEM item;
	if(pixel<=m_pixelRange[0])
	{
		item=m_itemList.GetHead();
		color=item.color;
		return;
	}
	if(pixel>=m_pixelRange[1])
	{
		item=m_itemList.GetTail();
		color=item.color;
		return;
	}
	
	BOOL bFind=FALSE;
	IA_PIXEL_ITEM item2;
	for(int i=0;i<m_itemList.GetCount()-1;i++)
	{
		item=m_itemList.GetAt(m_itemList.FindIndex(i));
		item2=m_itemList.GetAt(m_itemList.FindIndex(i+1));
		if(pixel>=item.pixel && pixel<item2.pixel)
		{
			bFind=TRUE;
			break;
		}
	}
	if(bFind && (item2.pixel-item.pixel>0))
	{
		float radio=float(pixel-item.pixel)/(item2.pixel-item.pixel);
		int r,g,b;
		r=GetRValue(item.color);// + (int)((GetRValue(item2.color)-GetRValue(item.color))*radio);
		g=GetGValue(item.color);// + (int)((GetGValue(item2.color)-GetGValue(item.color))*radio);
		b=GetBValue(item.color);// + (int)((GetBValue(item2.color)-GetBValue(item.color))*radio);
		r=GetRValue(item2.color);// + (int)((GetRValue(item2.color)-GetRValue(item.color))*radio);
		g=GetGValue(item2.color);// + (int)((GetGValue(item2.color)-GetGValue(item.color))*radio);
		b=GetBValue(item2.color);// + (int)((GetBValue(item2.color)-GetBValue(item.color))*radio);
		
		
		r=GetRValue(item.color) + (int)((GetRValue(item2.color)-GetRValue(item.color))*radio);
		g=GetGValue(item.color) + (int)((GetGValue(item2.color)-GetGValue(item.color))*radio);
		b=GetBValue(item.color) + (int)((GetBValue(item2.color)-GetBValue(item.color))*radio);
		color=RGB(r,g,b);
	}
}


void CLineChartCtrl::Notify()
{
	if(m_iCurSel<0)
		return;
	
	POSITION pos=m_itemList.FindIndex(m_iCurSel);
	if(pos)
	{
		IA_PIXEL_ITEM item=m_itemList.GetAt(pos);
		
		CWnd *parent=this->GetParent();
		int iResult=10;
		if(m_iMode==1)
		{
			iResult=20;
		}else if(m_iMode==2)
		{
			iResult=30;
		}
		
		if(m_iCurSel==0)
			item.pixel++;
		parent->SendMessage(WM_NOTIFY,WPARAM(&iResult),LPARAM(&item));
	}
}

void CLineChartCtrl::OnMButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_iCurSel>0 && m_iCurSel<m_itemList.GetCount()-1) //delete
	{
		POSITION pos=m_itemList.FindIndex(m_iCurSel);
		if(pos)
		{
			m_itemList.RemoveAt(pos);
			m_iCurSel-=1;
			Notify();
		}
		DrawLine();
	}
	CStatic::OnMButtonDown(nFlags, point);
}

void CLineChartCtrl::DrawHistogram(CDC *pDC)
{
	if(!m_grayHistogram)
		return;

	
	CRect rcClient;
	GetClientRect(rcClient);
	
	if (m_bkDC.GetSafeHdc() == NULL)
	{
		CClientDC dc(this);
		
		m_bkDC.CreateCompatibleDC(&dc);
		m_bitmapBK.CreateCompatibleBitmap(&dc,rcClient.Width(),rcClient.Height());
		m_pOldBitmapBK=m_bkDC.SelectObject(&m_bitmapBK);
	}

	if(m_bRedrawHistogram)  
	{
		m_bkDC.SetBkColor(RGB(100,100,100));
		m_bkDC.FillSolidRect(rcClient,RGB(100,100,100));

		CPen penBlack(PS_SOLID, 1, RGB(120,120,120));
		CPen* pOldPen = m_bkDC.SelectObject(&penBlack);
		
		
		int iPixelCount=m_pixelRange[1]-m_pixelRange[0]+1;
		
		
		
		
		int xMin,xMax,yMin,yMax;
		unsigned short pixel;
		float value;
		unsigned short pixelPre=m_pixelRange[0];
		
		GetPos(m_pixelRange[0],0.0,xMin,yMin);
		yMin=rcClient.Height() - m_iRadius -10 ;
		GetPos(m_pixelRange[1],1.0,xMax,yMax);
		yMax=m_iRadius;

		//计算画直方图时一个像素对应的直方图数值大小
		int iHitCount=0;
		int iMin=20000,iMax=-1000,iMax2=-2000,iMax3=-3000;
		for(int i=xMin;i<=xMax;i++)
		{
			GetValue(i,0,pixel,value);
			
			iPixelCount=0;
			for(int j=pixelPre;j<pixel;j++)
			{
				iPixelCount+=m_grayHistogram[j-m_pixelRange[0]].count;
			}
			pixelPre=pixel;

			if(iPixelCount>iMax)
			{
				iMax3=iMax2;
				iMax2=iMax;
				iMax=iPixelCount;
			}

			if(iPixelCount<iMax && iPixelCount >iMax2)
			{
				iMax3=iMax2;
				iMax2=iPixelCount;
			}

			if(iPixelCount<iMax2 && iPixelCount>iMax3)
			{
				iMax3=iPixelCount;
			}

			if(iPixelCount<iMin)
				iMin=iPixelCount;
		}

		
		iHitCount = iMax3; 
		if(iHitCount<=0)
		{
			iHitCount=iMax;
		}

		pixelPre=m_pixelRange[0];
		for(i=xMin;i<=xMax;i++)
		{
			GetValue(i,0,pixel,value);
			
			iPixelCount=0;
			for(int j=pixelPre;j<pixel;j++)
			{
				iPixelCount+=m_grayHistogram[j-m_pixelRange[0]].count;
			}
			pixelPre=pixel;

			
			if(iPixelCount>iHitCount)
			{
				iPixelCount =iHitCount;
			}
				
			int yCur=int((iPixelCount/((float)iHitCount))*(yMin-yMax));
			m_bkDC.MoveTo(i,yMin);
			m_bkDC.LineTo(i,yMin-yCur);

			
			
		}
		
		m_bkDC.SelectObject(pOldPen);
		m_bRedrawHistogram=FALSE;
	}

	pDC->BitBlt(0, 0, rcClient.Width(), rcClient.Height(), &m_bkDC, 0, 0, SRCCOPY);
	
	
}

void CLineChartCtrl::GetPixelOpacity(int pixel, float &opacity)
{
	IA_PIXEL_ITEM item;
	opacity=0;

	if(pixel<=m_pixelRange[0])
	{
		item=m_itemList.GetHead();
		opacity=item.opacity;
		return;
	}
	if(pixel>=m_pixelRange[1])
	{
		item=m_itemList.GetTail();
		opacity=item.opacity;
		return;
	}
	
	BOOL bFind=FALSE;
	IA_PIXEL_ITEM item2;
	for(int i=0;i<m_itemList.GetCount()-1;i++)
	{
		item=m_itemList.GetAt(m_itemList.FindIndex(i));
		item2=m_itemList.GetAt(m_itemList.FindIndex(i+1));
		if(pixel>=item.pixel && pixel<item2.pixel)
		{
			bFind=TRUE;
			break;
		}
	}
	if(bFind && (item2.pixel-item.pixel>0))
	{
		float radio=float(pixel-item.pixel)/(item2.pixel-item.pixel);
		opacity=item.opacity+radio*(item2.opacity-item.opacity);
	}
}

void CLineChartCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CStatic::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_bRedrawHistogram=TRUE;
	DrawLine();
}
