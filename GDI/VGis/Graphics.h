// Graphics.h: interface for the Graphics class.
//
//////////////////////////////////////////////////////////////////////
#include <afxtempl.h>
#if !defined(AFX_GRAPHICS_H__26BBD078_6BA7_4859_838D_6333F78CD0B4__INCLUDED_)
#define AFX_GRAPHICS_H__26BBD078_6BA7_4859_838D_6333F78CD0B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define G_LINE 1		//线
#define G_MLINE 2		//连续线
#define G_CIRCLE 3		//圆
#define G_ARC 4			//圆弧
#define G_TEXT 5		//
#define G_TAG 6			//子图
#define G_MLINERGN 7	//多边形	
#define G_LINENET 8		//网络节点
#define G_LABEL 9		//标签
#define G_BIG 10		//放大
#define G_SMALL 11		//缩小
#define G_MOVE 12		//移动
#define G_RECT 13	//局部放大
#define G_ALL 14		//查看全图

#define MAX_STYLE 9

#include "Line.h"
#include "Circle.h"
#include "Arc.h"
#include "Text.h"
#include "MLine.h"
#include "MLineRgn.h"
#include "LineNet.h"
#include "GraphicsPara.h"
#include "Tag.h"
#include "Label.h"


class Graphics  
{
friend class CGisInterface;
private:
	int m_MaxID[MAX_STYLE];				//绘图的最大ID
private:
	//定义图形
	CTypedPtrArray<CObArray,Line*> m_LineArray;
	CTypedPtrArray<CObArray,Circle*> m_CircleArray;
	CTypedPtrArray<CObArray,CArc*> m_ArcArray;
	CTypedPtrArray<CObArray,CText*> m_TextArray;
	CTypedPtrArray<CObArray,MLine*> m_MLineArray;
	CTypedPtrArray<CObArray,MLineRgn*> m_MLineRgnArray;
	CTypedPtrArray<CObArray,LineNet*> m_LineNetArray;
	CTypedPtrArray<CObArray,Tag*> m_TagArray;
	CTypedPtrArray<CObArray,CLabel*>m_LabelArray;
	//颜色
	GraphicsPara m_GraphPara;		//颜色参数
	void *p_Interface;				//接口画板
public:
	virtual void Serialize(CArchive& ar);
	BOOL GetRect(float &MinX,float &MinY,float &MaxX,float &MaxY);
	void SetInterface(void *p);
	int CreateID(int Lb);
	void DrawBack(CDC *pDC,int cx,int cy,int bColor);
	void Draw(CDC *pDC,int DrawMode,int DrawMode1,short BackColor);

	
	//操作图形
	LineNet * AddLineNetToLineNet(int sID/*目标ID*/,int eID/*要增加的ID */);//把eID 增加到sID
	int GetGraphIndex(short Lb,int ID);//查找指定ID的图形存放下标
	int GetGraphUpperBound(short Lb);//获得指定图形的最大下标
	int GetGraphSize(short Lb);//获得指定图形存储的数量
	void DeleteGraph(int Lb,int index);//删除指定图形指定索引的
	Gis* GetGraph(short Lb,int index);//获得指定图形指定索引

	//增加新的图形	
	CLabel* AddLabel(short ColorPen, short ColorBrush, float LineWide, short LineType, short Layer, int id, bool Delete, float StartX, float StartY,float MaxDisp,float MinDisp,LOGFONT lf, CString text);
	LineNet * AddLineNet(short ColorPen, float x, float y, float rRadiu, short Layer, int id);
	MLine* AddMLine(short ColorPen,short ColorBrush,float LineWide,short LineType,short Layer ,int id,bool Delete,int Number,PointStruct *PointList);
	MLineRgn* AddMLineRgn(short ColorPen,short ColorBrush,float LineWide,short LineType,short Layer ,int id,bool Delete,int Number,PointStruct *PointList,bool bTransparent,bool bFill);
	CText* AddText(short ColorPen, short ColorBrush, float LineWide, short LineType, short Layer, int id, bool Delete, float StartX, float StartY, float Angle1, float Angle2, float TextHeight, float TextWide, float OffWide, byte TextFont, CString text);
	Circle* AddCircle(short ColorPen,short ColorBrush,float LineWide,short LineType,short Layer ,int id,bool Delete,float CircleX,float CircleY,float CircleR,bool bFill);
	CArc* AddArc(short ColorPen,short ColorBrush,float LineWide,short LineType,short Layer ,int id,bool Delete,float CircleX,float CircleY,float CircleR,bool bFill,float Angle1,float Angle2);
	Line* AddLine(short ColorPen,short ColorBrush,float LineWide,short LineType,short Layer ,int id,bool Delete,float x1,float y1,float x2,float y2);
	Tag* AddTag(short ColorPen, int Layer, bool Delete, float InsertX, float InsertY, float ScaleX, float ScaleY, float Angle, int id, int idBlock);

	Graphics();
	virtual ~Graphics();

};

#endif // !defined(AFX_GRAPHICS_H__26BBD078_6BA7_4859_838D_6333F78CD0B4__INCLUDED_)
