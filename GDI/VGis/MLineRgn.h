// MLineRgn.h: interface for the MLineRgn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MLINERGN_H__265C6502_A264_46CD_A423_7EDBE824855C__INCLUDED_)
#define AFX_MLINERGN_H__265C6502_A264_46CD_A423_7EDBE824855C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MLine.h"

class MLineRgn : public MLine  
{
	DECLARE_SERIAL(MLineRgn);	
	friend class CGisInterface;
protected:
	bool	m_bTransparent;		//是否透明
	float	m_mRgnArea;			//多边形区域面积
	bool	m_bFill;			//是否需要填充
public:
	virtual void Serialize(CArchive &ar);
	virtual void GetRect(float &MinX, float &MinY, float &MaxX, float &MaxY);
	virtual void Release();
	virtual void Draw(CDC *pDC,int DrawMode,int DrawMode1,short BackColor);
	MLineRgn(short ColorPen,short ColorBrush,float LineWide,short LineType,short Layer ,int id,bool Delete,int Number,PointStruct *PointList,bool bTransparent,bool bFill);
	MLineRgn();
	virtual ~MLineRgn();

};

#endif // !defined(AFX_MLINERGN_H__265C6502_A264_46CD_A423_7EDBE824855C__INCLUDED_)
