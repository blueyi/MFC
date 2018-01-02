// Text.cpp: implementation of the Text class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VGis.h"
#include "Text.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#include "GraphicsPara.h"
#include "math.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CText::CText()
{

}

CText::~CText()
{

}

CText::CText(short ColorPen, short ColorBrush, float LineWide, short LineType, short Layer, int id, bool Delete, float StartX, float StartY, float Angle1, float Angle2,float TextHeight,float TextWide,float OffWide, byte TextFont, CString text)
	 :Gis(ColorPen,ColorBrush,LineWide,LineType,Layer ,id,Delete)
{
	m_StartX=StartX;
	m_StartY=StartY;
	m_Angle1=Angle1;
	m_Angle2=Angle2;
	m_TextHeight=TextHeight;
	m_TextWide=TextWide;
	m_OffWide=OffWide;
	m_Text=text;
}

void CText::Draw(CDC *pDC, int DrawMode, int DrawMode1, short BackColor)
{
	if (m_Delete)//删除返回
		return;
	GraphicsPara *p_GP=0;
	p_GP = (GraphicsPara * )pGraphPara;

	short ColorPen=m_ColorPen;

	if (DrawMode1==2)
	{
		ColorPen=BackColor;
	}

	CFont Font;
	int high,wide,cc1,cc2,cd,angg;
	byte c1,c2;
	float x1,y1,ang1;
	char bz[4];
	const char *ls1;

	if (DrawMode==0)
		pDC->SetROP2(R2_COPYPEN);
	else if (DrawMode==1)
		pDC->SetROP2(R2_NOT);

	pDC->SetBkMode(TRANSPARENT);
	high=DLtoVL(m_TextHeight);		//获得字体逻辑高度
	ang1=(float)(m_Angle1*pi/180);	//获得文本与X轴正向弧度
	if (high<3 || high > 200)		//字体太大或者太小不显示
		return;

	x1=m_StartX-m_TextHeight*(float)sin(ang1);	//标注起点的实际横坐标
	y1=m_StartY+m_TextHeight*(float)cos(ang1);	//标注起点的实际纵坐标

	angg=(int)(m_Angle2*10);
	wide=DLtoVL(m_TextWide);		//字体逻辑坐标宽度
	DPtoVP(x1,y1,cc1,cc2);			//标注起点的逻辑坐标

	//创建字体
	Font.CreateFont(high,wide,angg,0,50,0,0,0,255,
		OUT_DEFAULT_PRECIS, 
		CLIP_DEFAULT_PRECIS, 
		DEFAULT_QUALITY, 
		DEFAULT_PITCH | FF_SWISS, 
		"宋体");                 
	CFont *pOldFont=pDC->SelectObject(&Font);	//选入字体
	pDC->SetBkMode(TRANSPARENT);				//设置绘制模式
	pDC->SetTextColor(p_GP->GetColor(ColorPen));//设置文本颜色
	ls1=(const char *)m_Text;					//字符指针指向文本
	cd=strlen(ls1);
	while (cd>0)
	{//while
		c1=*ls1;
		c2=*(ls1+1);
		if (c1>127 && c2>127)			//判断是否是汉字
		{//if 127
			strncpy(bz,ls1,2);			//拷贝该汉字
			bz[2]=0;					//
			ls1=ls1+2;					//跳过该汉字
			pDC->TextOut(cc1,cc2,bz);	//在屏幕上绘制汉字
			cd=cd-2;					//字符长度减2
			//计算下一个字符显示的位置
			x1=x1+(m_TextWide*2+m_OffWide)*(float)cos(ang1);
			y1=y1+(m_TextWide*2+m_OffWide)*(float)sin(ang1);
			DPtoVP(x1,y1,cc1,cc2);//得到下字符的位置
		}//End if 127
		else
		{
			strncpy(bz,ls1,1);		//拷贝单个字母
			bz[1]=0;
			ls1++;
			pDC->TextOut(cc1,cc2,bz);
			cd=cd-1;
			//计算下一个字符显示的位置
			x1=x1+(m_TextWide*1+m_OffWide)*(float)cos(ang1);
			y1=y1+(m_TextWide*1+m_OffWide)*(float)sin(ang1);
			DPtoVP(x1,y1,cc1,cc2);//得到下字符的位置
		}
	}//End while

	pDC->SelectObject(pOldFont);


}

void CText::Release()
{
	delete this;
}

void CText::SetPara(short ColorPen, short ColorBrush, float LineWide, short LineType, short Layer, int id, bool Delete, float StartX, float StartY, float Angle1, float Angle2,float TextHeight,float TextWide,float OffWide, byte TextFont, CString text)
{
	int nb=Delete;
	Gis::Gis(ColorPen,ColorBrush,LineWide,LineType,Layer,id,Delete);
	m_StartX=StartX;
	m_StartY=StartY;
	m_Angle1=Angle1;
	m_Angle2=Angle2;
	m_TextHeight=TextHeight;
	m_TextWide=TextWide;
	m_OffWide=OffWide;
	m_Text=text;
}


