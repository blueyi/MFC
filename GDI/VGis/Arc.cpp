// CArc.cpp: implementation of the CArc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VGis.h"
#include "Arc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#include "GraphicsPara.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include "Math.H"

IMPLEMENT_SERIAL(CArc,Circle,1)

CArc::CArc()
{

}

CArc::~CArc()
{

}

CArc::CArc(short ColorPen, short ColorBrush, float LineWide, short LineType, short Layer, int id, BOOL Delete, float CircleX, float CircleY, float CircleR, BOOL bFill, float Angle1, float Angle2)
	:Circle( ColorPen, ColorBrush, LineWide, LineType, Layer , id, Delete, CircleX, CircleY,CircleR,bFill)
{
	m_Angle1=Angle1;
	m_Angle2=Angle2;
}

void CArc::Draw(CDC *pDC, int DrawMode, int DrawMode1, short BackColor)
{
	if (m_Delete)//É¾³ý·µ»Ø
		return;
	GraphicsPara *p_GP=0;
	p_GP = (GraphicsPara * )pGraphPara;

	int x,y,rr;
	int x1,x2,y1,y2;
	short LineType=m_LineType;
	short LineWide=Max(1,DLtoVL(m_LineWide));
	short ColorPen=m_ColorPen;
	if (DrawMode1==1)
	{
		if (m_LineType!=2)
			LineType=2;
		else
			LineType++;
	}
	else if (DrawMode==2)
		ColorPen=BackColor;

	CPen pen(LineType,LineWide,p_GP->GetColor(ColorPen));
	CPen *pOldPen=pDC->SelectObject(&pen);

	if (DrawMode==0)
		pDC->SetROP2(R2_COPYPEN);
	else if (DrawMode==1)
		pDC->SetROP2(R2_NOT);

	DPtoVP(m_CircleX,m_CircleY,x,y);
	rr=DLtoVL(m_CircleR);

	x1=x+DLtoVL(m_CircleR*(float)cos(m_Angle1));
	y1=y-DLtoVL(m_CircleR*(float)sin(m_Angle1));

	x2=x+DLtoVL(m_CircleR*(float)cos(m_Angle1));
	y2=y-DLtoVL(m_CircleR*(float)sin(m_Angle1));

	pDC->Arc(x-rr,y-rr,x+rr,y+rr,x1,y1,x2,y2);
	pDC->SelectObject(pOldPen);

}

void CArc::Release()
{
	delete this;
}

void CArc::Serialize(CArchive &ar)
{
	Circle::Serialize(ar);
	if (ar.IsStoring())
	{
		ar<<m_Angle1<<m_Angle2;
	}
	else
	{
		ar>>m_Angle1>>m_Angle2;
	}
}
