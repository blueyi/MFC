// Text.h: interface for the Text class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXT_H__6163B3C2_83E3_4EEB_8F9A_2B36321FED6E__INCLUDED_)
#define AFX_TEXT_H__6163B3C2_83E3_4EEB_8F9A_2B36321FED6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Gis.h"

class CText : public Gis  
{
	friend class CGisInterface;
protected:
	float m_StartX;		//起点横坐标
	float m_StartY;		//起点纵坐标
	float m_Angle1;		//标注角度
	float m_Angle2;		//旋转角度
	float m_TextHeight;	//字体高度
	float m_TextWide;	//字体宽度
	float m_OffWide;	//字体间隔
	byte  m_TextFont;	//字体类型
	CString m_Text;		//文本内容
	int	  m_TextLong;	//文本长度
public:

	void SetPara(short ColorPen, short ColorBrush, float LineWide, short LineType, short Layer, int id, bool Delete, float StartX, float StartY, float Angle1, float Angle2,float TextHeight,float TextWide,float OffWide, byte TextFont, CString text);
	virtual void Release();
	virtual void Draw(CDC *pDC,int DrawMode,int DrawMode1,short BackColor);
	CText(short ColorPen, short ColorBrush, float LineWide, short LineType, short Layer, int id, bool Delete, float StartX, float StartY, float Angle1, float Angle2,float TextHeight,float TextWide,float OffWide, byte TextFont, CString text);
	CText();
	virtual ~CText();

};

#endif // !defined(AFX_TEXT_H__6163B3C2_83E3_4EEB_8F9A_2B36321FED6E__INCLUDED_)
