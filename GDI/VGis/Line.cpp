// Line.cpp: implementation of the Line class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VGis.h"
#include "Line.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include "GraphicsPara.h"

IMPLEMENT_SERIAL(Line,CObject,1)

Line::Line()
{

}

Line::~Line()
{

}

Line::Line(short ColorPen, short ColorBrush, float LineWide, short LineType, short Layer, int id, bool Delete, float x1, float y1, float x2, float y2)
	 :Gis(ColorPen,ColorBrush,LineWide,LineType,Layer ,id,Delete)
{
	m_x1=x1;
	m_x2=x2;
	m_y1=y1;
	m_y2=y2;
}

void Line::Draw(CDC *pDC, int DrawMode, int DrawMode1, short BackColor)
{

	if (m_Delete)//删除返回
		return;
	GraphicsPara *p_GP=0;
	p_GP = (GraphicsPara * )pGraphPara;

	int x1,y1,x2,y2;

	short LineType=m_LineType;
	short LineWide=max(1,DLtoVL(m_LineWide));
	short ColorPen=m_ColorPen;

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
	}
	CPen pen(LineType,LineWide,p_GP->GetColor(ColorPen));
	CPen *pOldPen=pDC->SelectObject(&pen);
	if (DrawMode==0)
		pDC->SetROP2(R2_COPYPEN);
	else if (DrawMode==1)
		pDC->SetROP2(R2_NOT);


	DPtoVP(m_x1,m_y1,x1,y1);
	DPtoVP(m_x2,m_y2,x2,y2);
	pDC->MoveTo(x1,y1);
	pDC->LineTo(x2,y2);
	pDC->SelectObject(pOldPen);

}

void Line::Release()
{
	delete this;
}

void Line::GetRect(float &MinX, float &MinY, float &MaxX, float &MaxY)
{
	MinX=Min(m_x1,m_x2);
	MinY=Min(m_y1,m_y2);
	MaxX=Max(m_x1,m_x2);
	MaxY=Max(m_y1,m_y2);
}

void Line::Serialize(CArchive &ar)
{
	Gis::Serialize(ar);
	if (ar.IsStoring())
	{
		ar<<m_x1<<m_x2<<m_y1<<m_y2;
	}
	else
	{
		ar>>m_x1>>m_x2>>m_y1>>m_y2;
	}
}
