// CArc.h: interface for the CArc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CArc_H__49D177E5_0F04_4631_BF2D_1E976AEDBA54__INCLUDED_)
#define AFX_CArc_H__49D177E5_0F04_4631_BF2D_1E976AEDBA54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Circle.h"

class CArc : public Circle  
{
	DECLARE_SERIAL(CArc);	
	friend class CGisInterface;
public:
	virtual void Serialize(CArchive &ar);
	virtual void Release();
	virtual void Draw(CDC *pDC,int DrawMode,int DrawMode1,short BackColor);
	CArc(short ColorPen,short ColorBrush,float LineWide,short LineType,short Layer ,int id,BOOL Delete,float CircleX,float CircleY,float CircleR,BOOL bFill,float Angle1,float Angle2);
	CArc();
	virtual ~CArc();
protected:
	float m_Angle1,m_Angle2;	//圆弧的起点和终点角度(用弧度表示)
};

#endif // !defined(AFX_CArc_H__49D177E5_0F04_4631_BF2D_1E976AEDBA54__INCLUDED_)
