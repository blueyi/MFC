////////////////////////////////////////////////////////////////////////
//文件名  :MULTICOLORPLOT.CPP
//控件说明:实时曲线显示功能控件,提供LINE和BAR两种曲线显示功能
//作者:    戚高
//完成日期:2007-01-17
//版权    :可以自由使用代码
///////////////////////////////////////////////////////////////////////

#include "stdafx.h" 
#include "MultiColorPlotCtrl.h"
#include ".\multicolorplotctrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif 
/////////////////////////////////////////////////////////////////////////////
// CMultiColorPlotCtrl

CMultiColorPlotCtrl::CMultiColorPlotCtrl()
	: nPlotType(BAR) 
	, nGridResolutionX(10)
	, nGridResolutionY(10)
	, nGridScrollSpeedX(-2)
	, nGridScrollSpeedY(0)
	, nPlotGranulatrity(2)
	, nGridLineWidth(1)
	, m_clrDarkBack(RGB(0,0,75))
	, m_clrDarkLine(RGB(32,64,32))
	, nPlotData(0)
	, pfData(NULL)
	, fLow(0.0)
	, fHigh(100.0)
	, fScaleY(1.0)
	, m_clrCyanData(RGB(0,255,255))
	, nGridStarPosX(0)
	, nGridStarPosY(0)
	, bLock(true)
	, m_clrAxisScaleY(RGB(0,255,255))
	, nShowFormatDataText(0)
	, m_clrLinePen(RGB(0,255,0))
	, nLineWidth(1)
{
	// 关键代码
	// 初始化关键代码的 C_S 结构
	InitializeCriticalSection ( & g_cs ) ;
	
	// 初始化标题
	_stprintf ( szTitls , _TEXT ( "%s" ) , _TEXT ( "" ) ) ; 
	// 初始化单位
	_stprintf ( szUints , _TEXT ( "%s" ) , _TEXT ( "" ) ) ;
}

CMultiColorPlotCtrl::~CMultiColorPlotCtrl()
{
	if ( pfData )
	{
		delete [] pfData ;
	}
	
	// 释放关键代码
	DeleteCriticalSection ( & g_cs ) ;
}


BEGIN_MESSAGE_MAP(CMultiColorPlotCtrl, CStatic)
	//{{AFX_MSG_MAP(CMultiColorPlotCtrl)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiColorPlotCtrl message handlers

void CMultiColorPlotCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting  

	// 获得控件区域
	GetClientRect (&m_rectCtrl);
	// 创建内存 DC
	CMemDC *pMemDC = new CMemDC(&dc, &m_rectCtrl);

	CPoint orgBrushOrigin = pMemDC->GetBrushOrg () ;

	if(m_dcBackground.GetSafeHdc() == NULL || m_pBitmapBackground.m_hObject == NULL)
	{
		m_dcBackground.CreateCompatibleDC(&dc);
		m_pBitmapBackground.CreateCompatibleBitmap(&dc, m_rectCtrl.Width(),m_rectCtrl.Height()) ;
		m_pBitmapOldBackground = m_dcBackground.SelectObject(&m_pBitmapBackground) ;
		InitColorPlot(&m_dcBackground);
	}

	pMemDC->BitBlt(0, 0, m_rectCtrl.Width(), m_rectCtrl.Height(), 
		&m_dcBackground, 0, 0, SRCCOPY) ; 
	 
	//画曲线背景和网格
	DrawBackGroundGrid(pMemDC); 
	//画曲线数据
	DrawValue(pMemDC);
	//画曲线Y刻度
	DrawAxisScaleYValue(pMemDC);		

	pMemDC->SetBrushOrg ( orgBrushOrigin.x , orgBrushOrigin.y ) ;  
	delete pMemDC ;
}

// 设置画线的类型
void CMultiColorPlotCtrl::SetPlotType(int nType)
{
	nPlotType = nType ;	 
}

// 数据点面积大小（即：一个数据点占据的像素数）
BOOL CMultiColorPlotCtrl::SetPlotGranulatrity(int nPlotGrltiy)
{
	nPlotGranulatrity = nPlotGrltiy ;
	nPlotData = m_Size.cx / nPlotGranulatrity ;
	pfData = new float [nPlotData] ;
	if ( pfData )
	{
		// 初始化数据为 0 
		ZeroMemory ( pfData , sizeof ( pfData ) * nPlotData ) ;			
		return TRUE ;
	}		
	return FALSE ;
}

// 前景色
void CMultiColorPlotCtrl::SetGridLineClr(COLORREF clr)
{
	m_clrDarkLine = clr ;
	m_GridPen.CreatePen ( PS_SOLID , nGridLineWidth , m_clrDarkLine ) ;		
	m_clrDarkLine = clr ; 
}

// 数据范围
void CMultiColorPlotCtrl::SetRang(float fL, float fH)
{
	fLow = fL ;
	fHigh = fH ;
}

// 创建画笔
void CMultiColorPlotCtrl::SetLinePen(int nWidth, COLORREF clr)
{
	nGridLineWidth = nWidth ;
	m_clrDarkLine = clr ;
	m_GridPen.CreatePen ( PS_SOLID , nGridLineWidth , m_clrDarkLine ) ;
}

// Y轴刻度颜色
void CMultiColorPlotCtrl::SetAxisScaleClrY(COLORREF clr)
{
	m_clrAxisScaleY = clr ; 
}

// 标题
void CMultiColorPlotCtrl::SetTitle(LPCTSTR pctTitle)
{
	_stprintf ( szTitls , _TEXT ( "%s" ) , pctTitle ) ;
}

// 数据单位例：SetUnit( _TEXT ( "(k/sec)" ) ) ;
void CMultiColorPlotCtrl::SetUnit(LPCTSTR pctUint)
{
	_stprintf ( szUints , _TEXT ( "%s" ) , pctUint ) ;
}

// 是否显示数据标题、颜色、单位
/*
nShow = 0 ; 不显示任何文本
nShow = 1 ; 仅仅显示标题
nShow = 2 ; 仅仅显示标题和流量总计
nShow = 3 ; 显示标题和最小值
nShow = 4 ; 显示标题、最小值和中值
*/
void CMultiColorPlotCtrl::ShowTitle(int nShow)
{
	nShowFormatDataText = nShow ;
}

// BAR 颜色
// clrUp -------- 顶部颜色
// clrDown -------- 底部颜色
// bfRfastness  -------- 红色分量是否固定不变  false ---- 渐变
// bfGfastness  -------- 红色分量是否固定不变  false ---- 渐变
// bfBfastness  -------- 红色分量是否固定不变  false ---- 渐变
void CMultiColorPlotCtrl::SetBarColor(COLORREF clrUp, COLORREF clrDown, bool bfRfastness, bool bfGfastness, bool bfBfastness)
{

}

// 曲线颜色
void CMultiColorPlotCtrl::SetLineColorWidth(COLORREF clrLine, int nWidth)
{
	nLineWidth = nWidth ;
	m_clrLinePen = clrLine ;
}

void CMultiColorPlotCtrl::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	// 相应通告消息
	ModifyStyle( 0 , SS_NOTIFY ) ;

	GetClientRect ( & m_rectCtrl ) ;

	// 得到该控件的宽和高
	m_Size.cx = m_rectCtrl.right - m_rectCtrl.left ;
	m_Size.cy = m_rectCtrl.bottom - m_rectCtrl.top ;

	// 计算控件可容纳可见的数据点数
	nPlotData = m_Size.cx / nPlotGranulatrity ;

	// 设置控件上显示的文字的字体和大小
	m_SmallFont.CreateFont( -11 , 0 , 0 , 0 , FW_THIN , false , false , false , DEFAULT_CHARSET ,
		OUT_DEFAULT_PRECIS , CLIP_DEFAULT_PRECIS , DEFAULT_QUALITY , VARIABLE_PITCH , _TEXT( "Times New Roman" ) ) ;

	// 给实际数据分配内存
	pfData = new float [ nPlotData ] ;
	if ( pfData )
	{
		// 初始化数据为 0 
		ZeroMemory ( pfData , sizeof ( pfData ) * nPlotData ) ;

		m_GridPen.CreatePen ( PS_SOLID , nGridLineWidth , m_clrDarkLine ) ;

		CRgn m_Rgn ;
		m_Rgn.CreateRoundRectRgn ( 0 , 0 , m_Size.cx , m_Size.cy , 10 , 10 ) ;

		SetWindowRgn ( ( HRGN ) m_Rgn , true ) ; 

		SetTimer ( GRID_TIMER , GRID_UPDATE_SPEED , NULL ) ;
	}

	CStatic::PreSubclassWindow();
}

BOOL CMultiColorPlotCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return TRUE;
}

void CMultiColorPlotCtrl::ReconstructControl(void)
{
}

void CMultiColorPlotCtrl::InitColorPlot(CDC *pDC)
{
	// 根据不同的曲线分别绘制
	if ( nPlotType == BAR ) 
	{
		double factor = 255.0 / ( float ) m_Size.cy ;

		BYTE r , g , b ;

		for ( int x = 0 ; x < m_Size.cy ; x ++ )
		{
			g = ( BYTE ) ( 255 - factor * x ) ;
			r = ( BYTE ) ( factor * x ) ;
			b = ( BYTE ) 64 ;

			pDC->SetPixelV ( 0 , x , RGB ( r , g , b ) ) ;
			pDC->SetPixelV ( 1 , x , RGB ( r , g , b ) ) ;
		}
	}
	else if ( nPlotType == LINE )
	{
	}
	else
	{
	} 

	pDC->SelectObject ( m_pBitmapOldBackground ) ;

	// 生成位图画刷
	m_clrBrush.CreatePatternBrush ( & m_pBitmapBackground ) ;
}

//绘制网格和背景
void CMultiColorPlotCtrl::DrawBackGroundGrid(CDC * pDC)
{
	// 填充背景色
	pDC->FillSolidRect ( & m_rectCtrl , m_clrDarkBack ) ;

	// 画网格
	int nGridLinesX = m_Size.cx / nGridResolutionX ;
	int nGridLinesY = m_Size.cy / nGridResolutionY ;

	// 选择画笔
	CPen * pOldPen = pDC->SelectObject ( & m_GridPen ) ;

	// 创建垂直线
	for ( int x = 0 ; x <= nGridLinesX ; x ++ )
	{
		pDC->MoveTo ( x * nGridResolutionX + nGridStarPosX , 0 );
		pDC->LineTo ( x * nGridResolutionX + nGridStarPosX , m_Size.cy );
	}
	// 添加水平线
	for ( int y = 0 ; y <= nGridLinesY ; y ++ )
	{
		pDC->MoveTo ( 0 , nGridStarPosY + m_Size.cy - y * nGridResolutionY - 2 ) ;
		pDC->LineTo ( m_Size.cx , nGridStarPosY + m_Size.cy - y * nGridResolutionY - 2 ) ;
	}
	// 控制网格正确移动
	nGridStarPosX += nGridScrollSpeedX ;
	nGridStarPosY += nGridScrollSpeedY ;

	if ( nGridStarPosX < 0 ) nGridStarPosX = nGridResolutionX ;
	if ( nGridStarPosX > nGridResolutionX ) nGridStarPosX = 0 ;
	if ( nGridStarPosY < 0 ) nGridStarPosY = nGridResolutionY ;
	if ( nGridStarPosY > nGridResolutionY ) nGridStarPosY = 0 ;

	// 还原网格画笔
	pDC->SelectObject ( pOldPen ) ;
}

void CMultiColorPlotCtrl::DrawValue(CDC * pDC)
{
	float fx , fy ;

	// 用关键代码同步和SetData
	EnterCriticalSection ( & g_cs ) ;

	if ( nPlotType == BAR )
	{
		RECT rFill ;

		for ( int nData = 0 ; nData < nPlotData ; nData ++ )
		{
			fx = ( float ) ( m_rectCtrl.left + nData * nPlotGranulatrity ) ;
			fy = ( float ) fabs ( ( float ) ( m_rectCtrl.bottom - ( ( ( ( pfData[nData] - fLow ) / ( fHigh - fLow ) ) * m_Size.cy ) ) ) ) ;

			rFill.bottom = ( LONG ) m_rectCtrl.bottom ;
			rFill.top = ( LONG ) fy ;
			rFill.left = ( LONG ) fx ;
			rFill.right = ( LONG ) ( fx + nPlotGranulatrity ) ;

			pDC->SetBrushOrg ( ( int ) fx , m_rectCtrl.bottom ) ;

			// 用初始化画刷时生成的渐变位图画刷填充矩形
			pDC->FillRect ( & rFill , & m_clrBrush ) ;
			// 画数据点处的颜色
			pDC->SetPixelV ( ( int ) fx , ( int ) fy , m_clrCyanData ) ;
		}
	}
	else if ( nPlotType == LINE )
	{
		CPoint * g_DataPoint = new CPoint [nPlotData] ;

		// 创建曲线画笔
		CPen m_Pen ;
		m_Pen.CreatePen ( PS_SOLID , nLineWidth , m_clrLinePen ) ;
		CPen * m_pOldPen = pDC->SelectObject ( & m_Pen ) ;

		for ( int nData = 0 ; nData < nPlotData ; nData ++ )
		{
			g_DataPoint[nData].x  =  ( LONG ) ( m_rectCtrl.left + nData * nPlotGranulatrity ) ;
			g_DataPoint[nData].y  =  ( LONG ) fabs ( ( float ) ( m_rectCtrl.bottom - ( ( ( ( pfData[nData] - fLow ) / ( fHigh - fLow ) ) * m_Size.cy ) ) ) ) ;
		}

		pDC->Polyline ( g_DataPoint , nPlotData ) ;

		pDC->SelectObject ( m_pOldPen ) ;

		delete [] g_DataPoint ;
	}
	else
	{
	}
}

void CMultiColorPlotCtrl::DrawAxisScaleYValue(CDC * pDC)
{
	CFont * pOldFont ;
	// 绘制Y轴刻度
	TCHAR szAxisScaleYMax [MAX_PATH * sizeof ( TCHAR ) + 1] ;
	TCHAR szAxisScaleYMin [MAX_PATH * sizeof ( TCHAR ) + 1] ;
	TCHAR szAxisScaleY  [MAX_PATH * sizeof ( TCHAR ) + 1] ;

	ZeroMemory ( & szAxisScaleYMax , sizeof ( szAxisScaleYMax ) ) ;
	ZeroMemory ( & szAxisScaleYMin , sizeof ( szAxisScaleYMin ) ) ;
	ZeroMemory ( & szAxisScaleY , sizeof ( szAxisScaleY ) ) ;

	COLORREF clrText = pDC->GetTextColor () ;
	int nBkMode = pDC->GetBkMode () ;
	pDC->SetTextColor ( m_clrAxisScaleY ) ;
	pDC->SetBkMode ( TRANSPARENT ) ;

	pOldFont = pDC->SelectObject ( & m_SmallFont ) ;

	// 如果要求现实Y轴刻度数字
	switch ( nShowFormatDataText )
	{
	case 0 : // 不显示
		{
		} 
		break ;
	case 1 : // 仅显示标题
		{
			_stprintf ( szAxisScaleYMax , _TEXT ( "%s" ) , szTitls ) ;

			pDC->TextOut ( 0 ,  0 , szAxisScaleYMax ) ;
		} 
		break ;
	case 2 : // 显示标题和流量比例
		{
			_stprintf ( szAxisScaleYMax , _TEXT ( "%s %8.1f %s / %8.1f" ) , szTitls , pfData [ nPlotData - 1 ] , szUints , fHigh ) ;

			pDC->TextOut ( 0 ,  0 , szAxisScaleYMax ) ;
		} 
		break ;
	case 3 : // 显示最大最小值
		{
			// 格式化最大值和标题及单位
			_stprintf ( szAxisScaleYMax , _TEXT ( "%s %8.1f %s / %8.1f" ) , szTitls , pfData [ nPlotData - 1 ] , szUints , fHigh ) ;
			// 格式化最小值
			_stprintf ( szAxisScaleYMin , _TEXT ( "%8.1f" ) , fLow ) ;

			pDC->TextOut ( 0 ,  0 , szAxisScaleYMax ) ;
			pDC->TextOut ( 0 , m_Size.cy - 10 , szAxisScaleYMin ) ;
		} 
		break ;
	case 4 : // 显示全部
		{
			// 格式化最大值和标题及单位
			_stprintf ( szAxisScaleYMax , _TEXT ( "%s %8.1f %s / %8.1f" ) , szTitls , pfData [ nPlotData - 1 ] , szUints , fHigh ) ;
			// 格式化最小值
			_stprintf ( szAxisScaleYMin , _TEXT ( "%8.1f" ) , fLow ) ;
			// 格式化中值
			_stprintf ( szAxisScaleY , _TEXT ( "%8.1f" ) , ( ( fHigh - fLow ) / 2.0 + fLow ) ) ;


			// 绘制Y轴刻度
			pDC->TextOut ( 0 ,  0 , szAxisScaleYMax ) ;
			pDC->TextOut ( 0 , m_Size.cy - 10 , szAxisScaleYMin ) ;
			pDC->TextOut ( 0 , m_Size.cy /  2 , szAxisScaleY ) ;
		} break ;

	}


	pDC->SetTextColor ( clrText ) ;
	pDC->SetBkMode ( nBkMode ) ;
	pDC->SelectObject ( pOldFont ) ;

	// 离开关键代码
	LeaveCriticalSection ( & g_cs ) ;
}

void CMultiColorPlotCtrl::OnTimer(UINT nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch ( nIDEvent )
	{
	case GRID_TIMER :
		{
		} 
		break ;
	}
	
	Invalidate ( false ) ;

	CStatic::OnTimer(nIDEvent);
}

// 设置网格间距
void CMultiColorPlotCtrl::SetGridResolutionX(int nGridReluX)
{
	nGridResolutionX = nGridReluX ;
}

// 设置网格间距
void CMultiColorPlotCtrl::SetGridResolutionY(int nGridReluY)
{
	nGridResolutionY = nGridReluY ;
}

// 设置网格滚动速度,正值为从左向右滚动,0不动
void CMultiColorPlotCtrl::SetGridScrollSpeedX(int nSpeedX)
{
	nGridScrollSpeedX = nSpeedX ; 
}

// 正值为从上到下滚动,0不动
void CMultiColorPlotCtrl::SetGridScrollSpeedY(int nSpeedY)
{
	nGridScrollSpeedY = nSpeedY ;
}

// 网格线宽度
void CMultiColorPlotCtrl::SetGridLineWidth(int nWidth)
{
	nGridLineWidth = nWidth ;
}

// 背景色
void CMultiColorPlotCtrl::SetGridBackClr(COLORREF clr)
{
	m_clrDarkBack = clr ;
}

// // 锁定数据显示范围
void CMultiColorPlotCtrl::LockRang(bool bfLock)
{
	bLock = bfLock ;
}

// 锁定数据显示范围
void CMultiColorPlotCtrl::LockRang(float fMin, float fMax)
{
	fLow = fMin ;
	fHigh = fMax ;	
	LockRang ( true ) ;
}

// 设置数据
void CMultiColorPlotCtrl::SetData(float fData)
{
	// 用关键代码同步
	EnterCriticalSection ( & g_cs ) ;
	
	for ( int n = 0 ; n < nPlotData - 1 ; n ++ )
	{
		pfData [ n ] = pfData [ n + 1 ] ;
	}
	
	pfData [ nPlotData - 1 ] = fData ;
	
	if ( bLock ) // 锁定比例范围
	{
	}
	else
	{
		// 保存最小值
		if ( fLow > fData )
		{
			fLow = fData ;
		}
		// 保存最大值
		if ( fHigh < fData )
		{
			fHigh = fData ;
		}
	}
	
	// 离开关键代码
	LeaveCriticalSection ( & g_cs ) ;
}

// 曲线颜色
void CMultiColorPlotCtrl::SetLineColor(COLORREF clrLine)
{
	m_clrLinePen = clrLine ;
}

void CMultiColorPlotCtrl::SetLineWidth(int nWidth)
{
	nLineWidth = nWidth ;
}

const COLORREF CMultiColorPlotCtrl::GetLineColor(void)
{
	return m_clrLinePen ;
}

const int CMultiColorPlotCtrl::GetLineWidth(void)
{
	return nLineWidth ;
}
 
