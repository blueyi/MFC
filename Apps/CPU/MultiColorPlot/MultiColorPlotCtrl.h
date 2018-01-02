////////////////////////////////////////////////////////////////////////
//文件名  :MULTICOLORPLOT.H
//控件说明:实时曲线显示功能控件,提供LINE和BAR两种曲线显示功能
//作者:    戚高
//完成日期:2007-01-17
//版权    :可以自由使用代码
///////////////////////////////////////////////////////////////////////
#if !defined(AFX_MULTICOLORPLOTCTRL_H__2C4A3AEB_9552_478C_A5DE_FF03CAA81C7B__INCLUDED_)
#define AFX_MULTICOLORPLOTCTRL_H__2C4A3AEB_9552_478C_A5DE_FF03CAA81C7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MultiColorPlotCtrl.h : header file
//
//---------------------------------user define head files
#include "afxwin.h"
#include <math.h>
#include "MemDC.h"

#define BAR 0
#define LINE 1

#define GRID_TIMER 1
//网格刷新速率
#define GRID_UPDATE_SPEED 50  

typedef struct tagData_Point
{
	float fx ;
	float fy ;
} DATA_POINT ;

/////////////////////////////////////////////////////////////////////////////
// CMultiColorPlotCtrl window

class CMultiColorPlotCtrl : public CStatic
{
// Construction
public:
	CMultiColorPlotCtrl();

private: // 公共属性

	CBitmap *m_pBitmapOldBackground ;
	CBitmap m_pBitmapBackground ;
	CDC m_dcBackground;

	int nPlotType ; // 曲线类型  BAR 或 LINE // BAR 
	// 网格X方向上的间距
	int nGridResolutionX ; // 10
	// 网格Y方向上的间距
	int nGridResolutionY ; // 10
	// 网格滚动的速度和方向（正值为从左向右滚动和从上到下，否则反之。0不动）
	int nGridScrollSpeedX ; // -1
	int nGridScrollSpeedY ; // 0
	// 数据点分辨率大小（即：一个数据点占据的像素数）
	int nPlotGranulatrity ; // 2
	// 网格线宽度
	int nGridLineWidth ; // 1
	// 背景色
	COLORREF m_clrDarkBack ; // RGB(0,0,75)
	// 前景色
	COLORREF m_clrDarkLine ; // RGB(32,64,32)
	// 控件矩形
	CRect m_rectCtrl;
	// 控件的尺寸
	CSize m_Size ;
	// 控件可容纳可见的数据点数
	int nPlotData ; // 0
	// 实际数据
	float * pfData ; // 0
	// 数据范围
	float fLow , fHigh ; // 0,0
	// 数据比例
	float fScaleY ; // 1.0
	// 数据点处的颜色
	COLORREF m_clrCyanData ; // RGB ( 0,255,255 )
	// 画笔
	CPen m_GridPen ;
	// 数据点位图画刷
	CBrush m_clrBrush ;
	// 网格开始位置
	int nGridStarPosX , nGridStarPosY ; // 0,0
	// 锁定显示范围
	bool bLock ; // true---锁定
	// 控件上显示的字体
	CFont m_SmallFont ;
	// Y轴刻度的颜色
	COLORREF m_clrAxisScaleY ; // RGB ( 0,255,255 )
	// 是否显示Y轴刻度数字
	int nShowFormatDataText ; // 0---不显示
	// 控件标题
	TCHAR szTitls [MAX_PATH * sizeof ( TCHAR ) + 1] ; // NULL
	// 曲线单位
	TCHAR szUints [32 * sizeof ( TCHAR ) + 1] ; // NULL
	
	// LINE属性
	// 曲线颜色
	COLORREF m_clrLinePen ; // RGB(0,255,0)
	// 曲线宽度
	int nLineWidth ; 

	// BAR颜色
	COLORREF m_clrUp ;
	COLORREF m_clrDown ;

	DATA_POINT * g_DataPoint ;

private:
	// 关键代码
	CRITICAL_SECTION g_cs ;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiColorPlotCtrl)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetLineColorWidth ( COLORREF clrLine = RGB ( 0 , 255 , 0 ) , int nWidth = 1 );
	void SetBarColor ( COLORREF clrUp , COLORREF clrDown , bool bfRfastness = false , bool bfGfastness = false , bool bfBfastness = false );
	void ShowTitle ( int nShow = 1 );
	void SetUnit ( LPCTSTR pctUint = NULL );
	void SetTitle ( LPCTSTR pctTitle = NULL );
	void SetAxisScaleClrY ( COLORREF clr = RGB ( 0 , 255 , 255 ) );
	void SetLinePen ( int nWidth , COLORREF clr );
	void SetRang ( float fL , float fH );
	void SetGridLineClr ( COLORREF clr );
	BOOL SetPlotGranulatrity ( int nPlotGrltiy );
	void SetPlotType ( int nType );
	virtual ~CMultiColorPlotCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMultiColorPlotCtrl)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	void ReconstructControl(void);
protected:
	void InitColorPlot(CDC *pDC);
private:
	void DrawBackGroundGrid(CDC * pDC);
protected:
	void DrawValue(CDC * pDC);
	void DrawAxisScaleYValue(CDC * pDC);
public:
	afx_msg void OnTimer(UINT nIDEvent);
	// 设置网格间距
	void SetGridResolutionX(int nGridReluX);
	// 设置网格间距
	void SetGridResolutionY(int nGridReluY);
	// 设置网格滚动速度,正值为从左向右滚动,0不动
	void SetGridScrollSpeedX(int nSpeedX);
	// 正值为从上到下滚动,0不动
	void SetGridScrollSpeedY(int nSpeedY);
	// 网格线宽度
	void SetGridLineWidth(int nWidth);
	// 背景色
	void SetGridBackClr(COLORREF clr);
	// // 锁定数据显示范围
	void LockRang(bool bfLock = true);
	// 锁定数据显示范围
	void LockRang(float fMin, float fMax);
	// 设置数据
	void SetData(float fData);
	// 曲线颜色
	void SetLineColor(COLORREF clrLine = RGB ( 0 , 255 , 0 ));
	void SetLineWidth(int nWidth = 1);
	const COLORREF GetLineColor(void);
	const int GetLineWidth(void); 
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTICOLORPLOTCTRL_H__2C4A3AEB_9552_478C_A5DE_FF03CAA81C7B__INCLUDED_)
