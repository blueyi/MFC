// ROIManager.cpp: implementation of the CROIManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "qtimage.h"
#include "ROIManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CROIManager::CROIManager()
{
	m_label[0].color = RGB(128,0,255);
	m_label[1].color = RGB(255,128,64);
	m_label[2].color = RGB(128,128,0);
	m_label[3].color = RGB(0,255,0);
	m_label[4].color = RGB(255,0,255);
	m_label[5].color = RGB(0,255,255);
	m_label[6].color = RGB(0,0,255);
	m_label[7].color = RGB(128,128,255);
	m_label[8].color = RGB(0,128,0);
	m_label[9].color = RGB(255,0,0);
	
	for(int i=0;i<10;i++)
	{
		m_label[i].label=i*10;
	}
	m_iCurLabel=0;

}

CROIManager::~CROIManager()
{
	CROI *pROI;
	POSITION pos=m_ROIList.GetHeadPosition();
	while(pos)
	{
		pROI=m_ROIList.GetNext(pos);
		delete pROI;
	}

	m_ROIList.RemoveAll();

}

COLORREF CROIManager::GetColor()
{
	m_iCurLabel++;
	if(m_iCurLabel>9)
	{
		m_iCurLabel=0;
	}

	return m_label[m_iCurLabel].color;
}

short CROIManager::GetLabelByColor(COLORREF color)
{
	for(int i=0;i<10;i++)
	{
		if(m_label[i].color==color)
			return m_label[i].label;
	}

	return 300;
}

COLORREF CROIManager::GetColorByLabel(short label)
{
	for(int i=0;i<10;i++)
	{
		if(m_label[i].label==label)
			return m_label[i].color;
	}

	return RGB(0,0,0);
}

CROI* CROIManager::AddROI()
{
	CROI *pROI=new CROI();
	pROI->SetColor(GetColor());
	pROI->SetLabel(GetLabelByColor(pROI->GetColor()));
	
	m_ROIList.AddTail(pROI);
	return pROI;
}

CROI* CROIManager::GetByName(CString sName)
{
	CROI *pROI;
	POSITION pos=m_ROIList.GetHeadPosition();
	while(pos)
	{
		pROI=m_ROIList.GetNext(pos);
		if(pROI->GetName()==sName)
		{
			return pROI;
		}
	}

	return NULL;
}

int CROIManager::GetROICount(vtkImageData *pImage)
{
	CROI *pROI;
	POSITION pos=m_ROIList.GetHeadPosition();
	int iCount=0;
	while(pos)
	{
		pROI=m_ROIList.GetNext(pos);
		if(pROI->GetImage()==pImage)
		{
			iCount++;
		}
	}

	return iCount;
}

CROI* CROIManager::GetROIAt(vtkImageData *pImage, int index)
{
	CROI *pROI;
	POSITION pos=m_ROIList.GetHeadPosition();
	int iCount=0;
	while(pos)
	{
		pROI=m_ROIList.GetNext(pos);
		if(pROI->GetImage()==pImage)
		{
			if(iCount==index)
			{
				return pROI;
			}
			iCount++;
		}
	}

	return NULL;
}
