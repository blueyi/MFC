// GraphicsPara.h: interface for the GraphicsPara class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHICSPARA_H__8371E831_B0A3_4599_9C6F_1FCE87722895__INCLUDED_)
#define AFX_GRAPHICSPARA_H__8371E831_B0A3_4599_9C6F_1FCE87722895__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct 
{
	char m_Name[21];	//图层的名字
	BOOL m_Disp;		//是否显示
	int	 m_reserved;	//备用
}LayerStruct;

class GraphicsPara :public CObject   
{
	DECLARE_SERIAL(GraphicsPara);	
protected:
	int m_ColorNumberAll;		//总的颜色数
	int m_LayerNumberAll;		//总的图层数
	int m_ColorNumber;			//系统当前具有的颜色数
	int	m_LayerNumber;			//系统当前具有的图层数
	COLORREF* m_ColorList;			//存储颜色的数组
	LayerStruct *m_LayerList;	//图层的数组
public:
	virtual void Serialize(CArchive &ar);
	BOOL GetDisplayStatue(int n);
	COLORREF GetColor(int n);
	GraphicsPara();
	virtual ~GraphicsPara();

};

#endif // !defined(AFX_GRAPHICSPARA_H__8371E831_B0A3_4599_9C6F_1FCE87722895__INCLUDED_)
