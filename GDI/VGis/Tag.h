// Tag.h: interface for the Tag class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TAG_H__5DA24C03_E573_415D_BC93_F2C45FB23950__INCLUDED_)
#define AFX_TAG_H__5DA24C03_E573_415D_BC93_F2C45FB23950__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Gis.h"

#include "Block.h"

class Tag : public Gis  
{
	friend class CGisInterface;
protected:
	int m_idBlock;		//子图块的标识号
	float m_InsertX;	//插入点的横坐标
	float m_InsertY;	//插入点的纵坐标
	float m_ScaleX;		//横向放缩比例
	float m_ScaleY;		//纵向放缩比例
	float m_Angle;		//子图旋转角度
	CBlock * p_Block;	//指向子块的指针
	
public:
	virtual void Release();
	Tag(short ColorPen,int Layer,bool Delete ,float InsertX,float InsertY,float ScaleX,float ScaleY,float Angle,int id,int idBlock);
	Tag();
	virtual ~Tag();

};

#endif // !defined(AFX_TAG_H__5DA24C03_E573_415D_BC93_F2C45FB23950__INCLUDED_)
