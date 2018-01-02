// Circle.cpp: implementation of the Circle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VGis.h"
#include "Circle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#include "GraphicsPara.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(Circle,CObject,1)
Circle::Circle()
{

}

Circle::~Circle()
{

}

Circle::Circle(short ColorPen, short ColorBrush, float LineWide, short LineType, short Layer, int id, bool Delete, float CircleX, float CircleY, float CircleR, bool bFill)
	   :Gis(ColorPen,ColorBrush,LineWide,LineType,Layer ,id,Delete)
{
	m_CircleX=CircleX;
	m_CircleY=CircleY;
	m_CircleR=CircleR;
	m_bFill=bFill;
}

void Circle::Draw(CDC *pDC, int DrawMode, int DrawMode1, short BackColor)
{
	if (m_Delete)//删除返回
		return;
	GraphicsPara *p_GP=0;
	p_GP = (GraphicsPara * )pGraphPara;

	int x,y,r;
	short LineType=m_LineType;
	short LineWide=max(1,DLtoVL(m_LineWide));
	short ColorPen=m_ColorPen;
	short ColorBrush=m_ColorBrush;
	if (DrawMode1==1)//如果效果图需要特殊显示
	{
		if (m_LineType!=2)//采用虚线
			LineType=2;
		else
			LineType++;
	}
	else if (DrawMode1==2)
	{
		ColorPen=BackColor;
		ColorBrush=BackColor;
	}
	CPen pen(LineType,LineWide,p_GP->GetColor(ColorPen));
	CPen *pOldPen=pDC->SelectObject(&pen);

	CBrush brush(p_GP->GetColor(m_ColorBrush));
	CBrush *pOldBrush=pDC->SelectObject(&brush);

	if (DrawMode==0)
		pDC->SetROP2(R2_COPYPEN);
	else if (DrawMode==1)
		pDC->SetROP2(R2_NOT);

	if (!this->m_bFill)
		pDC->SelectStockObject(NULL_BRUSH);

	DPtoVP(m_CircleX,m_CircleY,x,y);
	r=DLtoVL(m_CircleR);

	pDC->Ellipse(x-r,y-r,x+r,y+r);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);

}

void Circle::Release()
{
	delete this;
}

void Circle::GetRect(float &MinX, float &MinY, float &MaxX, float &MaxY)
{
	MinX=m_CircleX-m_CircleR;
	MinY=m_CircleY-m_CircleR;
	MaxX=m_CircleX+m_CircleR;
	MaxY=m_CircleY+m_CircleR;
}

void Circle::Serialize(CArchive &ar)
{
	Gis::Serialize(ar);
	if (ar.IsStoring())
	{
		ar<<m_CircleX<<m_CircleY<<m_CircleR<<m_CircleLong<<m_CircleArea<<m_bFill;
	}
	else
	{
		ar>>m_CircleX>>m_CircleY>>m_CircleR>>m_CircleLong>>m_CircleArea>>m_bFill;
	}
}
