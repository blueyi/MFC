// GisInterface.h: interface for the CGisInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GISINTERFACE_H__DDB02E76_054A_4CF2_B961_FFF0F7F81861__INCLUDED_)
#define AFX_GISINTERFACE_H__DDB02E76_054A_4CF2_B961_FFF0F7F81861__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Graphics.h"
#include "TextDialog.h"

class CGisInterface : public CWnd  
{
private://交互数据
	CPoint pt1,pt2;
	CTextDialog m_TextDlg;				//标注文本编辑
	float T_x1,T_y1;					//标注文本坐标
	CString T_PreText;					//上一次标注文本
	PointStruct *m_Ps;					//多边形和多线的临时存储点
	HCURSOR  m_cursor;					//光标
	CBitmap   m_pBitmap;				//移动时保存的位图
	CDC m_MemDC;						//保存位图的DC
private://制图参数
	LRESULT ChangeLabel(WPARAM wParam,LPARAM lParam);
	void ChangeText(CText *pText,int lParam);

	short m_PenColor;					//当前画笔颜色序号
	short m_BkColor;					//背景颜色序号
	short m_BrushColor;					//当前画刷颜色序号
	short m_LineWide;					//当前线宽度
	short m_LineType;					//当前线型
	short m_Layer;						//当前图层
	BOOL  m_bFill;						//是否填充

protected://绘图参数
	int m_DrawCurrent;					//当前要进行的绘图样式
	int m_PushNumber;					//新的绘图样式 鼠标按下的次数
public:
	Graphics m_Graph;


protected:	//转换屏幕参数
	int	  m_Brink;						//边缘宽度
	float m_StartX,m_StartY,m_blc;		//屏幕左下角实际坐标和比例尺
	int   m_ScreenWidth,m_ScreenHeight; //存储图形屏幕的实际宽度和高度
	int	  m_MapMode;					//设备映射方式
	float m_MaxX,m_MaxY,m_MinX,m_MinY;	//最大最小坐标


public:
	BOOL  Create(CWnd* lParent,const RECT& rect , DWORD dwStyle = WS_CHILD | WS_BORDER |WS_TABSTOP | WS_VISIBLE);
	//屏幕转换，设置 函数
	void SetScreenFromMaxMin(float MaxX,float MaxY,float MinX,float MinY,int Brink);
	void SetMapMode(int MapMode);
	int DLtoVL(float l);
	float VLtoDL(int l);
	void SetStartOrg(float x,float y,float blc);
	float VPtoDP(int x,int y,float &X,float &Y);
	float DPtoVP(float x,float y,int &X,int &Y);


public:
	virtual void Serialize(CArchive &ar);
	void AllGraph();
	void SetStartXY(float x,float y);
	float GetBlc();
	void SetBlc(float blc,CPoint pt);
	int SetDraw(int style);
	BOOL GetNetXY(int NetID,float &x,float &y,BOOL &Delete);
	void SetScreen(int ScreenWidth, int ScreenHeight);
	void Draw(CDC *pDC);
	CGisInterface();
	virtual ~CGisInterface();
protected:
	// Generated message map functions
	//{{AFX_MSG(CGisInterface)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_GISINTERFACE_H__DDB02E76_054A_4CF2_B961_FFF0F7F81861__INCLUDED_)
