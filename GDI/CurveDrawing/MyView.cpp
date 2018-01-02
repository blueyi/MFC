// MyView.cpp : implementation file   
//   

#include "stdafx.h"   
#include "CurveDrawing.h"   
#include "MyView.h"   
#include "MainFrm.h"   
#ifdef _DEBUG   
#define new DEBUG_NEW   
#undef THIS_FILE   
static char THIS_FILE[] = __FILE__;   
#endif   

/////////////////////////////////////////////////////////////////////////////   
// CMyView   

IMPLEMENT_DYNCREATE(CMyView, CView)   

CMyView::CMyView()   
{   

}   

CMyView::~CMyView()   
{   
}   


BEGIN_MESSAGE_MAP(CMyView, CView)   
	//{{AFX_MSG_MAP(CMyView)   
	ON_WM_ERASEBKGND()   
	//}}AFX_MSG_MAP   
END_MESSAGE_MAP()   

/////////////////////////////////////////////////////////////////////////////   
// CMyView drawing   

void CMyView::OnDraw(CDC* pDC)   
{   
	CCurveDrawingDoc* pDoc = (CCurveDrawingDoc*)GetDocument();   
	// TODO: add draw code here   
	CMainFrame* pMainFrame=(CMainFrame*)GetParentFrame();   
	GetClientRect(m_plot.m_ctlRect);//得到CMyView部分的视图尺寸，存入m_ctlRect   

	//绘图   

	//若是在CCurveDrawingView::OnTime中出发的OnDraw函数，则将执行DrawCurve绘制趋势图   
	if(TRUE==((CCurveDrawingDoc*)GetDocument())->ifdrawcurve)   
	{   
		m_plot.DrawCurve(pDC);   
		pDoc->ifdrawcurve=FALSE;//将标志清0，下次定时时间到在CCurveDrawingView::OnTime中置1     
	}   

}   

/////////////////////////////////////////////////////////////////////////////   
// CMyView diagnostics   

#ifdef _DEBUG   
void CMyView::AssertValid() const   
{   
	CView::AssertValid();   
}   

void CMyView::Dump(CDumpContext& dc) const   
{   
	CView::Dump(dc);   

}   
#endif //_DEBUG   

/////////////////////////////////////////////////////////////////////////////   
// CMyView message handlers   
//这里我们运用了两点技术使得我们重绘的图形看起来不闪烁   
//1.重载了OnEraseBkgnd函数,它是用来在每次重绘之前用空白位图擦除背景的函数,我们让它每次用我们自定义的   
//位图来作为背景   
//2.我们使用了双缓存的结构,即先把背景图形绘制在内存中,绘制好了一起显示出去   
BOOL CMyView::OnEraseBkgnd(CDC* pDC)    
{   
	// TODO: Add your message handler code here and/or call default   
	CDC MemDC; //首先定义一个显示设备对象   
	CBitmap MemBitmap;//定义一个位图对象   
	//随后建立与屏幕显示兼容的内存显示设备   
	MemDC.CreateCompatibleDC(NULL);   
	//这时还不能绘图，因为没有地方画   
	//下面建立一个与屏幕显示兼容的位图，至于位图的大小嘛，可以用窗口的大小   
	MemBitmap.CreateCompatibleBitmap(pDC,m_plot.m_ctlRect.Width(),m_plot.m_ctlRect.Height());   
	//将位图选入到内存显示设备中   
	//只有选入了位图的内存显示设备才有地方绘图，画到指定的位图上   
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);   
	//先用背景色将位图清除干净，这里我用的是白色作为背景   
	//你也可以用自己应该用的颜色   
	m_plot.DrawBasic(&MemDC);   
	m_plot.DrawLegendShadow(&MemDC);   
	m_plot.DrawXAxisGrid(&MemDC);   
	m_plot.DrawYAxisGrid(&MemDC);   
	m_plot.DrawLegend(&MemDC);   
	//将内存中的图拷贝到屏幕上进行显示   
	pDC->BitBlt(0,0,m_plot.m_ctlRect.Width(),m_plot.m_ctlRect.Height(),&MemDC,0,0,SRCCOPY);   
	//绘图完成后的清理   
	MemBitmap.DeleteObject();   
	MemDC.DeleteDC();   
	return TRUE;   
}   