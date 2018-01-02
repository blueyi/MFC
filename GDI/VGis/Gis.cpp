// Gis.cpp : implementation file
//

#include "stdafx.h"
#include "VGis.h"
#include "Gis.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "GisInterface.h"
#include "GraphicsPara.h"
/////////////////////////////////////////////////////////////////////////////
// Gis
#include <math.h>

#include "VGisView.H"

IMPLEMENT_SERIAL(Gis,CObject,1)
Gis::Gis()
{
	pGraphPara=0;
	pInetrface=0;
	m_Delete  =0;
	m_ColorPen=0;
	m_ColorBrush=0;
	m_Layer=0;
	m_LineType=0;
	m_LineWide=0;

}

Gis::~Gis()
{
}



Gis::Gis(short ColorPen, short ColorBrush, float LineWide, short LineType, short Layer, int id, BOOL Delete)
{
	m_ColorPen		=ColorPen;	//画笔颜色
	m_ColorBrush	=ColorBrush;	//填充颜色
	m_LineWide		=LineWide;	//线宽
	m_LineType		=LineType;	//线类型
	m_Layer			=Layer;		//所处图层
	m_Delete		=Delete;		//是否处于删除状态
	m_id			=id;			//唯一标识	
	pInetrface		=0;
}

int Gis::GetID()
{
	return m_id;
}

void Gis::Draw(CDC *pDC, int DrawMode, int DrawMode1, short BackColor)
{
	/*
	DrawMode 0=R2_COPYPEN 1=R2_NOT 根据需要可以加入其他模式
	DrawMode1 0=正常显示 1=特殊显示 2 用指定颜色
	BackColor  DrawMode==2 时使用此参数。 
	*/
}
float Gis::VLtoDL(int l)
{
	CGisInterface *pInter=(CGisInterface*)pInetrface;
	return pInter->VLtoDL(l);
}

int Gis::DLtoVL(float l)
{
	CGisInterface *pInter=(CGisInterface*)pInetrface;
	return pInter->DLtoVL(l);
}
float Gis::DPtoVP(float x, float y,int &X,int &Y)
{
	CGisInterface *pInter=(CGisInterface*)pInetrface;
	return pInter->DPtoVP(x, y, X, Y);
}

float Gis::VPtoDP(int x, int y, float &X, float &Y)
{
	CGisInterface *pInter=(CGisInterface*)pInetrface;
	return pInter->VPtoDP(x, y, X, Y);
}

//求一条直线的倾角0-360
double Gis::GetAngle(int x1,int y1,int x2,int y2)
{
	int dx=x2-x1,dy=y2-y1;
	double theta;
	if(dx==0){
		if(dy>0) return 90.0;
		else return  270.0;
	}
	else {
		theta=atan((double)dy/(double)dx)*180.0/pi; //弧度化为角度
		if(dx<0) theta+=180;
		else if(dy<0) theta+=360;
		return theta;
	}
}
//求一条直线的倾角，直线用浮点数表示
double Gis::GetAngle(double  x1,double y1,double x2,double y2)
{
	double dx=x2-x1,dy=y2-y1;
	double theta;
	if(dx==0){
		if(dy>0) return 90.0;
		else return  270.0;
	}
	else {
		theta=atan((double)dy/(double)dx)*180.0/pi; //弧度化为角度
		if(dx<0) theta+=180;
		else if(dy<0) theta+=360;
		return theta;
	}
}
//角度转弧度
double Gis::AngleToRadian(double Angle)
{
	return Angle*pi/180;
}

void Gis::SetGraphPara(void *p)
{
	this->pGraphPara=p;
}

void Gis::SetInterface(void *p)
{
	this->pInetrface=p;
}

void Gis::Release()
{
	delete this;
}

float Gis::GetBlc()
{
	CGisInterface *pInter=(CGisInterface*)pInetrface;
	return pInter->GetBlc();
}

void Gis::GetRect(float &MinX, float &MinY, float &MaxX, float &MaxY)
{

}

float Gis::Max(float x1, float x2)
{
	if (x1>x2)
		return x1;
	else
		return x2;
}

float Gis::Min(float x1, float x2)
{
	if (x1>x2)
		return x2;
	else
		return x1;
}

int Gis::Max(int x1, int x2)
{
	if (x1>x2)
		return x1;
	else 
		return x2;
}

int Gis::Min(int x1, int x2)
{
	if (x1>x2)
		return x2;
	else
		return x1;
}
extern CView  *g_pView;

void Gis::Serialize(CArchive &ar)
{
	/*
		short m_ColorPen;	//画笔颜色
	short m_ColorBrush;	//填充颜色
	float m_LineWide;	//线宽
	short m_LineType;	//线类型
	short m_Layer;		//所处图层
	BOOL  m_Delete;		//是否处于删除状态
	int	  m_id;			//唯一标识*/
	
	int del=0;
	if (m_Delete)
		del=1;

	if (ar.IsStoring())
	{
		ar<<m_id<<del<<m_Layer<<m_LineType<<m_ColorBrush<<m_ColorPen;
	}
	else
	{
		this->pInetrface=&((CVGisView*)g_pView)->m_Gis;
		this->pGraphPara=&((CVGisView*)g_pView)->m_Gis.m_Graph;
		ar>>m_id>>del>>m_Layer>>m_LineType>>m_ColorBrush>>m_ColorPen;
	}
}
