// Line.h: interface for the Line class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINE_H__26A69DF0_53F9_43D5_84AF_682E1154A425__INCLUDED_)
#define AFX_LINE_H__26A69DF0_53F9_43D5_84AF_682E1154A425__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Gis.h"

class Line : public Gis  
{
	DECLARE_SERIAL(Line);		
	friend class CGisInterface;
public:
	virtual void Serialize(CArchive &ar);
	virtual void GetRect(float &MinX,float &MinY,float &MaxX,float &MaxY);
	virtual void Release();
	virtual void Draw(CDC *pDC,int DrawMode,int DrawMode1,short BackColor);
	Line(short ColorPen,short ColorBrush,float LineWide,short LineType,short Layer ,int id,bool Delete,float x1,float y1,float x2,float y2);
	Line();
	virtual ~Line();
protected:
	float m_x1,m_y1,m_x2,m_y2;	//直线的起止点
	float m_LineLong;			//线的长度

};

#endif // !defined(AFX_LINE_H__26A69DF0_53F9_43D5_84AF_682E1154A425__INCLUDED_)
