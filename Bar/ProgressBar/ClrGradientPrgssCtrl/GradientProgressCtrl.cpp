// GradientProgressCtrl.cpp : implementation file

#include "stdafx.h"
#include "GradientProgressCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGradientProgressCtrl

CGradientProgressCtrl::CGradientProgressCtrl()
{
	//初始化
	m_nLower = 0;
	m_nUpper = 100;
	m_nCurrentPosition = 0;
	m_nStep = 10;	
	
	m_clrStart	= COLORREF(RGB(255, 0,0));
	m_clrEnd =	 COLORREF(RGB(0,0,255));
	m_clrBkGround = ::GetSysColor(COLOR_3DFACE);
	m_clrText = COLORREF(RGB(255, 255, 255));

	m_bShowPercent = FALSE;
}

CGradientProgressCtrl::~CGradientProgressCtrl()
{
}


BEGIN_MESSAGE_MAP(CGradientProgressCtrl, CProgressCtrl)
	//{{AFX_MSG_MAP(CGradientProgressCtrl)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGradientProgressCtrl message handlers

void CGradientProgressCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	//如果进度条的当前位置不正确，则渐变到背景色
	if (m_nCurrentPosition <= m_nLower || m_nCurrentPosition >= m_nUpper)
	{
		CRect rect;
		GetClientRect(rect);
		CBrush brush;
		brush.CreateSolidBrush(::GetSysColor(COLOR_3DFACE));
		dc.FillRect(&rect, &brush);
		VERIFY(brush.DeleteObject());
		return;
	}


	//获得需要渐变的区域
	CRect rectClient;
	GetClientRect(&rectClient);
	float maxWidth((float)m_nCurrentPosition/(float)m_nUpper * (float)rectClient.right);


	//画渐变颜色
	DrawGradient(&dc, rectClient, (int)maxWidth);

	//如果需要显示百分数，则显示
	if (m_bShowPercent)
	{
		CString percent;
		percent.Format("%.0f%%", 100.0f*(float)m_nCurrentPosition/(float)m_nUpper);
		dc.SetTextColor(m_clrText);
		dc.SetBkMode(TRANSPARENT);
		dc.DrawText(percent, &rectClient, DT_VCENTER |  DT_CENTER | DT_SINGLELINE);
	}
}


//设置进度条范围
void CGradientProgressCtrl:: SetRange(int nLower, int nUpper)
{
	m_nLower = nLower;
	m_nUpper = nUpper;
	m_nCurrentPosition = nLower;
	CProgressCtrl::SetRange(nLower, nUpper);
}

//设置进度条的位置
int CGradientProgressCtrl:: SetPos(int nPos)
{
	m_nCurrentPosition = nPos;
	return (CProgressCtrl::SetPos(nPos));
}

//设置进度条的步长
int CGradientProgressCtrl:: SetStep(int nStep)
{
	m_nStep = nStep;
	return (CProgressCtrl::SetStep(nStep));
}

int CGradientProgressCtrl:: StepIt(void)
{
	m_nCurrentPosition += m_nStep;
	return (CProgressCtrl::StepIt());
}

//在适当区域画渐变颜色
void CGradientProgressCtrl::DrawGradient(CPaintDC *pDC, const RECT &rectClient, const int &nMaxWidth)
{
	RECT rectFill;			   
	float fStep;              
	CBrush brush;			

	
	CMemDC memDC(pDC);

	//找到其实颜色和结束颜色之间的最大颜色值，决定渐变步长等
	int r, g, b;							
	float rStep, gStep, bStep;		

	r = (GetRValue(m_clrEnd) - GetRValue(m_clrStart));
	g = (GetGValue(m_clrEnd) - GetGValue(m_clrStart));
	b =  (GetBValue(m_clrEnd) - GetBValue(m_clrStart));

	int nSteps = max(abs(r), max(abs(g), abs(b)));

	fStep = (float)rectClient.right / (float)nSteps;

	//计算每个颜色的步长
	rStep = r/(float)nSteps;
	gStep = g/(float)nSteps;
	bStep = b/(float)nSteps;

	r = GetRValue(m_clrStart);
	g = GetGValue(m_clrStart);
	b = GetBValue(m_clrStart);


	// 开始填充颜色
	for (int iOnBand = 0; iOnBand < nSteps; iOnBand++) 
	{
		
		::SetRect(&rectFill,
					(int)(iOnBand * fStep),       
					 0,									 
					(int)((iOnBand+1) * fStep),         
					rectClient.bottom+1);			
	
		VERIFY(brush.CreateSolidBrush(RGB(r+rStep*iOnBand, g + gStep*iOnBand, b + bStep *iOnBand)));
		memDC.FillRect(&rectFill,&brush);
		VERIFY(brush.DeleteObject());

		if (rectFill.right > nMaxWidth)
		{
			::SetRect(&rectFill, rectFill.right, 0, rectClient.right, rectClient.bottom);
			VERIFY(brush.CreateSolidBrush(m_clrBkGround));
			memDC.FillRect(&rectFill, &brush);
			VERIFY(brush.DeleteObject());
			return;
		}
	}
}

BOOL CGradientProgressCtrl::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}
