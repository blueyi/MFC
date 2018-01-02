// clPlot.cpp : implementation file
//

#include "stdafx.h"
#include "curvedrawing.h"
#include "clPlot.h"
#include "CurveDrawingView.h"
#include "MyView.h"
#include "malloc.h"
#include <stdlib.h>
#include <afxwin.h>

#include  <math.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// clPlot

clPlot::clPlot()
{
	m_ctlBkColor= RGB(255,255,255);
//	m_ctlBkColor=RGB(255,0,0);
	m_gridColor	= RGB(127,127,127);
	m_lNoValues=0;
	m_lend=0;
	leftmargin=30;
	rightmargin=30;
	topmargin=25;
	bottommargin=25;
	off=3;
	scalevalue=1;
	m_legendBkColor		= RGB(255,255,255);

}

clPlot::~clPlot()
{
	if(m_pValue!=NULL)
		free(m_pValue);
}


BEGIN_MESSAGE_MAP(clPlot, CWnd)
	//{{AFX_MSG_MAP(clPlot)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// clPlot message handlers

void clPlot::DrawBasic(CDC* pDC)
{
	CBrush brushctlBkColor(m_ctlBkColor);
	pDC->FillRect(m_ctlRect,&brushctlBkColor);//给CMyView视图填充背景色
	//计算趋势图边框
	m_plotRect.left=m_ctlRect.left+leftmargin;
	m_plotRect.right=m_ctlRect.right-rightmargin;
	m_plotRect.top=m_ctlRect.top+topmargin;
	m_plotRect.bottom=m_ctlRect.bottom-bottommargin;
	//绘制趋势图边框
	pDC->Rectangle(m_plotRect);
}

void clPlot::DrawXAxisGrid(CDC *pDC)
{
	CPen *old1, *old, pen(PS_SOLID, 1, m_gridColor);//大格笔
	CPen stick(PS_SOLID,0,RGB(0,0,0));//刻度笔
	CPen mline(PS_SOLID,0,RGB(192,192,192));//小格笔
//横向小格宽度，分为了100个小格，10个大格
	smallgridwidth=((double)m_plotRect.right-(double)m_plotRect.left)/100;

	old1=pDC->SelectObject(&mline);
	double x;
	for(int i=1;i<=99;i++)
	{
		x=m_plotRect.left+smallgridwidth*i;
		//逢10画大格
		if(0==i%10)
		{
			old=pDC->SelectObject(&pen);
			pDC->MoveTo(CPoint(x,m_plotRect.bottom-2));
	    	pDC->LineTo(CPoint(x,m_plotRect.top+1));
			pDC->SelectObject(old);

		}
		//非10画小格
		else
		{
			pDC->MoveTo(CPoint(x,m_plotRect.bottom-2));
			pDC->LineTo(CPoint(x,m_plotRect.top+1));
		}
		//画横向刻度
		old=pDC->SelectObject(&stick);
		pDC->MoveTo(CPoint(x,m_plotRect.top));
		pDC->LineTo(CPoint(x,m_plotRect.top-off));
		pDC->MoveTo(CPoint(x,m_plotRect.bottom));
		pDC->LineTo(CPoint(x,m_plotRect.bottom+off));
		pDC->SelectObject(old);

	}
	pDC->SelectObject(old1);
}

void clPlot::DrawYAxisGrid(CDC *pDC)
{
	CPen *old, *old1, pen(PS_SOLID, 1, m_gridColor);
	CPen stick(PS_SOLID,0,RGB(0,0,0));
	CPen mline(PS_SOLID,0,RGB(192,192,192));
	CFont m_font;
	m_font.CreatePointFont(100,"Arial",pDC);
	pDC->SelectObject(&m_font);
	pDC->DrawText("1.0",CRect(m_plotRect.right+5,m_plotRect.bottom-10,m_plotRect.right+30,m_plotRect.bottom+10),DT_CENTER);
		pDC->DrawText("5.0",CRect(m_plotRect.right+5,m_plotRect.top-5,m_plotRect.right+30,m_plotRect.top+15),DT_CENTER);
	//竖向分为四十个小格，1-4V
	double smallgridwidth=((double)m_plotRect.top-(double)m_plotRect.bottom)/40;
	old1=pDC->SelectObject(&mline);
	double y;
	for(int i=1;i<=39;i++)
	{
		y=m_plotRect.bottom+smallgridwidth*i;
		if(0==i%10)
		{
			scalevalue++;
			old=pDC->SelectObject(&pen);
			pDC->MoveTo(CPoint(m_plotRect.right-2,y));
	    	pDC->LineTo(CPoint(m_plotRect.left+1,y));
			//输出竖向刻度值
			char b[20];
			sprintf(b,"%.1f",scalevalue);
			pDC->DrawText(b,CRect(m_plotRect.right+5,y-10,m_plotRect.right+30,y+10),DT_CENTER);
			pDC->SelectObject(old);
		}
		else
		{
			pDC->MoveTo(CPoint(m_plotRect.right-2,y));
	    	pDC->LineTo(CPoint(m_plotRect.left+1,y));
		}
		//画竖向刻度
		old=pDC->SelectObject(&stick);
		pDC->MoveTo(CPoint(m_plotRect.left,y));
		pDC->LineTo(CPoint(m_plotRect.left-off,y));
		pDC->MoveTo(CPoint(m_plotRect.right,y));
		pDC->LineTo(CPoint(m_plotRect.right+off,y));
		pDC->SelectObject(old);
	}
	pDC->SelectObject(old1);
	scalevalue=1;
}

BOOL clPlot::AddPoint(CTime valuetime, float value)
{
//为新产生的点分配内存,此处注意malloc与realloc，我们在《项目文档》中有一篇文章谈到了他们
	if(m_lNoValues > 0)
		m_pValue = (pValue*)realloc(m_pValue, (m_lNoValues+1)*sizeof(pValue));
	else
		m_pValue = (pValue*)malloc((m_lNoValues+1)*sizeof(pValue));
	//注意m_pValue为指向pValue结构体的指针，但我们可以把当作数组来使用
	m_pValue[m_lend].dValue=value;
	m_pValue[m_lend].ValueTime=valuetime;
	m_lNoValues++;
	m_lend++;
	return TRUE;
}



void clPlot::DrawCurve(CDC* pDC)
{
	static int docnumber=0;
	docnumber++;
	CPen m_pen(PS_SOLID,1,RGB(255,0,0));//为趋势图曲线建立的红色画笔
	CPen* m_oldpen=pDC->SelectObject(&m_pen);
	//实验用的产生1-4的随机数
	float y=(double)(abs(rand())%20);
	float cy=y/4;
	if(cy<=1)
	{
		cy=1;
	}
	//以上为实验用数
	//将随机产生的存入内存（实时数据库）
	AddPoint(CTime::GetCurrentTime(),cy);
	//当有了两个数据后才可以画第一条线
	if(docnumber>=2)
	{
		int docnumber1=docnumber;
		//计算我们的坐标和趋势图外框尺寸之间的比例
		intervalY=m_plotRect.Height()/4;
		//点的个数小于等于101时
		if(docnumber<=100)
		{
			for(int i=0;i<docnumber-1;i++)
			{
				docnumber1--;
				//注意VC的GDI视图的Y坐标正向是朝下的，所以我们需要m_plotRect.Height()+topmargin-视图中的位置
				pDC->MoveTo(CPoint(m_plotRect.left+smallgridwidth*(100-docnumber1),m_plotRect.Height()+topmargin-
					((m_pValue[i].dValue-1)*intervalY)));
				pDC->LineTo(CPoint(m_plotRect.left+smallgridwidth*(100-docnumber1+1),m_plotRect.Height()+topmargin-
					((m_pValue[i+1].dValue-1)*intervalY)));
			}
		}
		//点的格数大于101时，由于我们的趋势图只能显示101个点（100个格），所以当点的个数超过
		//101时，我们需要显示后101个点
		else
		{
			for(int i=0;i<100;i++)
			{
				pDC->MoveTo(CPoint(m_plotRect.left+smallgridwidth*(i),m_plotRect.Height()+topmargin-
					((m_pValue[i+docnumber-1-100].dValue-1)*intervalY)));
				pDC->LineTo(CPoint(m_plotRect.left+smallgridwidth*(i+1),m_plotRect.Height()+topmargin-
					((m_pValue[i+docnumber-100].dValue-1)*intervalY)));
			}
		}
		pDC->SelectObject(m_oldpen);
	}
}

void clPlot::DrawLegend(CDC *pDC)
{
	//m_legendRect为左上小图标的区域
		m_legendRect.top=m_plotRect.top+50;
		m_legendRect.bottom=m_plotRect.top-15;
		m_legendRect.left=m_plotRect.left+20;
		m_legendRect.right=m_plotRect.left+150;
		CPen pen(PS_SOLID, 1, RGB(0,0,0));
		CPen *oPen = pDC->SelectObject(&pen);
		CBrush *oBrush , brush(m_legendBkColor);
		oBrush = pDC->SelectObject(&brush);
		pDC->Rectangle(m_legendRect);
		pDC->SelectObject(oBrush);
		CPen m_pen(PS_SOLID,1,RGB(255,0,0));//为趋势图曲线建立的红色画笔
		pDC->SelectObject(&m_pen);
		pDC->MoveTo(CPoint(m_legendRect.left+10,m_legendRect.bottom+10));
		pDC->LineTo(CPoint(m_legendRect.left+40,m_legendRect.bottom+10));
		CFont m_font;
		m_font.CreatePointFont(90,"Arial",pDC);
		pDC->SelectObject(&m_font);
		pDC->TextOut(m_legendRect.left+60,m_legendRect.bottom+5,"通道0");
		pDC->SelectObject(oPen);
}

void clPlot::DrawLegendShadow(CDC *pDC)
{
	
	CPen pen(PS_SOLID, 1, RGB(127,127,127));
	CPen *oPen = pDC->SelectObject(&pen);
	CBrush *oBrush , brush(RGB(127,127,127));
	oBrush = pDC->SelectObject(&brush);
	pDC->Rectangle(CRect(m_legendRect.left+5,m_legendRect.top+5,m_legendRect.right+5, m_legendRect.bottom+5));
	pDC->SelectObject(oBrush);
	pDC->SelectObject(oPen);
	
}
