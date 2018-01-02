// GraphicsPara.cpp: implementation of the GraphicsPara class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VGis.h"
#include "GraphicsPara.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(GraphicsPara,CObject,1)

GraphicsPara::GraphicsPara()
{
	m_ColorNumberAll=500;
	m_LayerNumberAll=100;
	m_ColorList=new COLORREF[m_ColorNumberAll];
	m_LayerList=new LayerStruct[m_LayerNumberAll];
	m_ColorNumber=6;
	m_LayerNumber=1;
	///³õÊ¼»¯ÑÕÉ«
	m_ColorList[0]=RGB(0,0,0);
	m_ColorList[1]=RGB(255,0,0);
	m_ColorList[2]=RGB(0,255,0);
	m_ColorList[3]=RGB(0,0,255);
	m_ColorList[4]=RGB(0,255,255);
	m_ColorList[5]=RGB(255,255,255);
	m_LayerList[0].m_Disp=1;
	strcpy(m_LayerList[0].m_Name,"Layer 0");
}

GraphicsPara::~GraphicsPara()
{
	delete m_LayerList;
	delete m_ColorList;
}

COLORREF GraphicsPara::GetColor(int n)
{
	return m_ColorList[n];
}

BOOL GraphicsPara::GetDisplayStatue(int n)
{
	return m_LayerList[n].m_Disp;
}

void GraphicsPara::Serialize(CArchive &ar)
{
    int i;

	if (ar.IsStoring())
	{
		ar<<m_LayerNumberAll<<m_LayerNumber<<m_ColorNumberAll<<m_ColorNumber;
		for (int i=0;i<m_LayerNumber;i++)
		{
			ar<<m_LayerList[i].m_Disp<<m_LayerList[i].m_reserved;
			for (int j=0;j<21;j++)
			{
				ar<<m_LayerList[i].m_Name[j];
			}
		}
		for (i=0;i<m_ColorNumber;i++)
		{
			ar<<m_ColorList[i];
		}
	}
	else
	{
		ar>>m_LayerNumberAll>>m_LayerNumber>>m_ColorNumberAll>>m_ColorNumber;
	
		m_ColorList=new COLORREF[m_ColorNumberAll];
		m_LayerList=new LayerStruct[m_LayerNumberAll];

		for (int i=0;i<m_LayerNumber;i++)
		{
			ar>>m_LayerList[i].m_Disp>>m_LayerList[i].m_reserved;
			for (int j=0;j<21;j++)
			{
				ar>>m_LayerList[i].m_Name[j];
			}
		}
		for (i=0;i<m_ColorNumber;i++)
		{
			ar>>m_ColorList[i];
		}

	}

}
