// MLine.cpp: implementation of the MLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VGis.h"
#include "MLine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#include "GraphicsPara.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(MLine,CObject,1)
MLine::MLine()
{
	m_Number=0;
}

MLine::~MLine()
{
	if (m_Number>0)
		delete m_PointList;
}

MLine::MLine(short ColorPen, short ColorBrush, float LineWide, short LineType, short Layer, int id, bool Delete, int Number, PointStruct *PointList)
	  :Gis(ColorPen,ColorBrush,LineWide,LineType,Layer ,id,Delete)
{
	m_Number=Number;
	m_PointList=new PointStruct[Number+1];
	if (Number>0)
	{
		for (int i=0;i<Number;i++)
			m_PointList[i]=PointList[i];
	}
}

void MLine::Draw(CDC *pDC, int DrawMode, int DrawMode1, short BackColor)
{
	if (m_Delete)//删除返回
		return;
	GraphicsPara *p_GP=0;
	p_GP = (GraphicsPara * )pGraphPara;


		int x1,y1;

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

	for (int i=0;i<m_Number;i++)
	{
		DPtoVP(m_PointList[i].x,m_PointList[i].y,x1,y1);
		if (i==0)
			pDC->MoveTo(x1,y1);
		else
			pDC->LineTo(x1,y1);
	}

	pDC->SelectObject(pOldPen);


}

void MLine::Release()
{
	delete this;
}

void MLine::GetRect(float &MinX, float &MinY, float &MaxX, float &MaxY)
{
	MinX=m_PointList[0].x;
	MinY=m_PointList[0].y;
	MaxX=m_PointList[0].x;
	MaxY=m_PointList[0].y;
	for (int i=1;i<m_Number;i++)
	{
		MinX=Min(MinX,m_PointList[i].x);
		MaxX=Max(MaxX,m_PointList[i].x);

		MinY=Min(MinY,m_PointList[i].y);
		MaxY=Max(MaxY,m_PointList[i].y);

	}
}

void MLine::Serialize(CArchive &ar)
{
	Gis::Serialize(ar);
	if (ar.IsStoring())
	{
		ar<<m_Number;
		for (int i=0;i<m_Number;i++)
		{
			ar<<m_PointList[i].x<<m_PointList[i].y;
		}
	}
	else
	{
		ar>>m_Number;
		for (int i=0;i<m_Number;i++)
		{
			ar>>m_PointList[i].x>>m_PointList[i].y;
		}
	}
}
