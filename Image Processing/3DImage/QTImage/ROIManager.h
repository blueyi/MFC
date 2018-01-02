// ROIManager.h: interface for the CROIManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROIMANAGER_H__D410757A_8800_4DEC_82EB_37DF44BFDE28__INCLUDED_)
#define AFX_ROIMANAGER_H__D410757A_8800_4DEC_82EB_37DF44BFDE28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ROI.h"

class CROIManager  
{
public:
	CROI* GetROIAt(vtkImageData *pImage,int index);
	int GetROICount(vtkImageData *pImage);
	CROI* GetByName(CString sName);
	CROI* AddROI();
	COLORREF GetColorByLabel(short label);
	

	CROIManager();
	virtual ~CROIManager();

private:
	short GetLabelByColor(COLORREF color);
	CList<CROI*,CROI*> m_ROIList;
	COLORREF GetColor();
	LABEL_COLOR m_label[10];
	int m_iCurLabel;
	short m_curLabel;
};

#endif // !defined(AFX_ROIMANAGER_H__D410757A_8800_4DEC_82EB_37DF44BFDE28__INCLUDED_)
