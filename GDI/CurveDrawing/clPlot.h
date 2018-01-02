#if !defined(AFX_CLPLOT_H__2E93C8B4_33F9_49F3_AD16_F1A6316F37D1__INCLUDED_)
#define AFX_CLPLOT_H__2E93C8B4_33F9_49F3_AD16_F1A6316F37D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// clPlot.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// clPlot window
//我们建立的一个结构体，用于存放我们趋势图上的点信息
struct pValue
	{
		CTime ValueTime;
		float dValue;
	};
class clPlot : public CWnd
{
// Construction
public:
	clPlot();

// Attributes
public:
	COLORREF	m_ctlBkColor;		//CMyView部分的背景颜色
	CRect		m_ctlRect;			//CMyView部分的视图尺寸
	CRect		m_plotRect;         //趋势图的外边框
	COLORREF	m_gridColor;
	long		m_lNoValues;	// no values (used for array size)
	pValue*		m_pValue;		//趋势图点的结构体
	long		m_lend;			//当前有多少个点
	double smallgridwidth;      //横向小格宽度
	float intervalX; 
	float intervalY;			//我们的坐标和趋势图外框高度之间的比例
	int leftmargin;					//上下左右四个空白边框的距离           
	int rightmargin;
	int topmargin;
	int bottommargin;
	int off;					//横竖刻度长度
	float scalevalue;			//竖向刻度值
	COLORREF 	m_legendBkColor;  //左上小图标背景色
	CRect m_legendRect;				//左上小图标区域
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(clPlot)
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawLegendShadow(CDC* pDC);
	void DrawLegend(CDC* pDC);
	void DrawCurve(CDC* pDC);//绘制曲线
	BOOL AddPoint(CTime valuetime, float value);//将实时数据加入到实时数据库
	void DrawYAxisGrid(CDC * pDC);//绘制纵向栅格
	void DrawXAxisGrid(CDC * pDC);//绘制横向栅格
	void DrawBasic(CDC* pDC);//绘制背景
	virtual ~clPlot();

	// Generated message map functions
protected:
	//{{AFX_MSG(clPlot)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLPLOT_H__2E93C8B4_33F9_49F3_AD16_F1A6316F37D1__INCLUDED_)
