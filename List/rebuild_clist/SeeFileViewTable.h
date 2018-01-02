#pragma once

#include "Resource.h"
#include "FileInfoControl.h"
#include "shellapi.h"
#include "ReNameEdit.h"

//=====================================================================
// 函 数 名：LoadImageFunc
// 功能描述：载入Image对象的线程主体
// 输入参数：LPVOID lpParameter带入SeeFileViewTable指针
// 输出参数：DWORD WINAPI
// 创建日期：08.09.16
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
DWORD WINAPI LoadImageFunc (LPVOID lpParameter);
//=====================================================================
// 函 数 名：LoadBaseInfoFunc
// 功能描述：载入文件基本信息的线程主体
// 输入参数：LPVOID lpParameter带入SeeFileViewTable指针
// 输出参数：DWORD WINAPI
// 创建日期：08.09.16
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
DWORD WINAPI LoadBaseInfoFunc (LPVOID lpParameter);

//存储滑动块相关颜色设置
struct ScrollBarcColorSet
{
	COLORREF normalBak;
	COLORREF normalBorder;
	COLORREF mouseOnBak;
	COLORREF mouseOnBorder;
	COLORREF mouseDownBak;
	COLORREF mouseDownBorder;
};

//文件显示的信息存储结构
struct ScrollBarState
{
	UINT upButState;				//向上按钮的状态
	UINT downButState;				//向下按钮的状态
	UINT midButState;				//中间拖动划块的状态
	int scrollTotalLength;			//总的拖动条长度
	int scrollMidButLength;			//中间划块的长度
	int scrollDragLength;			//允许拖动的长度
	int scrollMidPosition;			//相对总长度，滑动块所处位置坐标
};

//ITEM的范围
struct ItemRange
{
	int head;
	int end;
};

//获取文件信息时的带入参数结构
struct InfoToGetFileInfo
{
	int code;
};

//详细信息样式时，每列的相关信息存储对象
struct ColumnInfo
{
	CString columnName;					//列名称
	int width;							//列宽度
	InfoToGetFileInfo infoType;			//获取所显示内容的相关变量
	UINT orderedColumn;					//是否被排序列
	UINT headState;						//表头的状态
	UINT contentState;					//内容展示方式（对齐方式HEAD_ALI）
	int startPosition;					//开始的位置（象素）
	int endPosition;					//结束位置
};

//存储鼠标位置信息
struct MousePositionInfo
{
	CPoint pt;							//鼠标的位置(存绝对坐标)仅在鼠标在显示区域时有效
	UINT positionType;					//宏定义的数据(POSITION_)
	UINT value;							//跟位置相关信息，例如所在位置的列序号，所在ITEM的信息
};

//存储鼠标位置以及操作的相关信息
struct MouseActionInfo
{
	MousePositionInfo mousePositionInfo;//鼠标位置信息
	UINT mouseCondition;				//鼠标状态信息，宏定义（MOUSE_）
	CPoint dragStartPt;					//开始该状态时的鼠标坐标-绝对坐标(窗体坐标)
};

typedef	vector<ColumnInfo>	VectorColumnInfo;

class SeeFileViewTable :
	public CWnd
{
public:
	SeeFileViewTable(void);
	~SeeFileViewTable(void);

// Attributes //属性, 品质, 特征, 加于, 归结
public:
	FileInfoControl m_ficFileControl;					//文件链表控制对象，控制对文件的基本操作

	bool m_bSelectedFileEnable;							//是否需要过滤文件
	bool m_bDealMouseAction;							//判断是否对鼠标操作做出响应

	UINT m_uiViewStyle;									//ListCtrl查看的样式值
	int m_iDragInfo;									//当拖拽评级或类型到LIST中时，根据本变量对等级或类型进行设置

	string m_sOpenFloderPath;							//打开的文件夹路

	CImageList * m_cilIconList;							//
	CImageList * m_cilLevelsIcon;						//评级的等级图标列表
	CImageList * m_cilScrollBarUp;						//拖动条的向上
	CImageList * m_cilScrollBarDown;					//拖动条的向下
	CImageList * m_cilScrollBarLeft;					//拖动条的向左
	CImageList * m_cilScrollBarRight;					//拖动条的向右

	CMenu m_cmRightButtonMenu;							//右键菜单总列表
	CMenu * m_cmMenuChild;								//获取的详细右键菜单指针

	PreviewBar * m_wndPreviewBar;							//文件预览窗口指针
	FavoriteBar * m_wndFavoriteBar;							//收藏夹窗口指针

public:
	SolidBrush * m_brUnselectedBrush;						//未选择的ITEM背景刷
	SolidBrush * m_brSelectedBrush;							//已选择的ITEM背景刷
	SolidBrush * m_brSelectedUnfoucBrush;					//已选择的ITEM窗口无焦点背景刷
	SolidBrush * m_brSelectBrush;							//拖拉选择时的覆盖部分颜色
	SolidBrush * m_brScrollBarBakBrush;						//拖拉条的背景刷
	SolidBrush * m_brScrollBarMidBakBrush;					//正常情况下拖拉划块的背景刷
	SolidBrush * m_brScrollBarMidMouseOnBrush;				//鼠标悬停情况下的拖拉划块背景刷
	SolidBrush * m_brScrollBarMidDragBrush;					//拖拉情况下的拖拉划块背景刷
	SolidBrush * m_brBakBrush;								//总的背景刷
	Pen * m_penFoucItem;									//具有焦点的ITEM描边
	Pen * m_penSelectedItem;								//被选择的ITEM描边
	Pen * m_penItemBorder;									//Item边缘刷
	Pen * m_penScrollBarMidBakBorder;						//正常情况下拖拉划块的边缘刷
	Pen * m_penScrollBarMidMouseOnBorder;					//鼠标悬停情况下的拖拉划块边缘刷
	Pen * m_penScrollBarMidDragBorder;						//拖拉情况下的拖拉划块边缘刷
	SolidBrush * m_brFontBrush;								//文字刷

	HANDLE m_hLoadImage;								//加载图象的线程指针，载入并缩放，不产生DC
	HANDLE m_hLoadBaseInfo;								//加载文件基本信息

	Gdiplus::Image * m_imgDefaultDisk;					//默认磁盘图标
	Gdiplus::Image * m_imgDefaultFloder;				//默认文件夹图标
	Gdiplus::Image * m_imgDefaultPic;					//ITEM默认图标
	Gdiplus::Image * m_imgShadowRight;					//阴影图标右侧
	Gdiplus::Image * m_imgShadowDown;					//阴影图标下面
	Gdiplus::Image * m_imgShadowRightDown;				//阴影图标角落

	FontFamily * m_ffFontFamily;						//绘制文件的字体
	StringFormat * m_sfStringFormatLeft;				//绘制文字的格式
	StringFormat * m_sfStringFormatRight;				//绘制文字的格式
	StringFormat * m_sfStringFormatCenter;				//绘制文字的格式
	Gdiplus::Font * m_fntFontBlod;						//绘制文字的样式加粗
	Gdiplus::Font * m_fntFontNormal;					//绘制文字的样式不加粗

	COleDataSource m_DragSource;						//执行拖拽操作时的OLE对象

	/**
	*	----重绘部分变量----
	*/
	CBitmap * m_cbBakMemeryBmp;							//背景绘制图象的存储对象
	CBitmap * m_cbWorkAreaBmp;							//绘制显示区域的图象存储对象
	CBitmap * m_cbHeaderBmp;							//表头的图象存储对象
	CBitmap * m_cbScrollVBmp;							//表头的图象存储对象
	CBitmap * m_cbScrollHBmp;							//表头的图象存储对象
	CDC * m_dcMemeryDC;									//背景绘制的内存DC
	CDC * m_dcWorkAreaDC;								//显示区域部分的内存DC
	CDC * m_dcHeaderDC;									//表头部分的内存DC
	CDC * m_dcScrollVDC;								//纵向滚动条部分的内存DC
	CDC * m_dcScrollHDC;								//横向滚动条部分的内存DC
	CDC * m_dcBakDC;									//背景绘制的DC

	bool m_bListGetFouc;								//List是否获取到焦点
	BOOL m_bMouseTracking;								//是否定义了鼠标离开的信息

	int m_iCurrentViewWidth;							//当前显示部分的宽度
	int m_iCurrentViewHeight;							//当前显示部分的高度
	int m_iCurrentStartNItem;							//当前显示区域显示的第一个ITEM编号
	int m_iCurrentEndNItem;								//当前显示区域显示的最后一个ITEM编号
	int m_iWorkAreaTop;									//当前显示部分的顶部Y坐标-相对m_iWorkAreaHeight
	int m_iWorkAreaBottom;								//当前显示部分的底部Y坐标-相对m_iWorkAreaHeight
	int m_iOldWorkAreaTop;								//当前显示部分的顶部更新前Y坐标-相对m_iWorkAreaHeight
	int m_iOldWorkAreaBottom;							//当前显示部分的底部更新前Y坐标-相对m_iWorkAreaHeight
	int m_iWorkAreaLeft;								//当前显示部分的左边界坐标-相对m_iWorkAreaWidth
	int m_iWorkAreaRight;								//当前显示部分的右边界坐标-相对m_iWorkAreaWidth
	int m_iOldWorkAreaLeft;								//当前显示部分的左边界更新前坐标-相对m_iWorkAreaWidth
	int m_iOldWorkAreaRight;							//当前显示部分的右边界更新前坐标-相对m_iWorkAreaWidth
	int m_iWorkAreaWidth;								//item显示区域宽度
	int m_iWorkAreaHeight;								//item显示区域高度
	int m_iWorkAreaTotalHeight;							//item显示区域总高度
	int m_iWorkAreaTotalWidth;							//item显示区域总宽度
	int m_iItemWidth;									//每个ITEM的宽度
	int m_iItemHeight;									//每个ITEM的高度
	int m_iItemWithBorderWidth;							//每个ITEM的宽度带空白区域
	int m_iItemWithBorderHeight;						//每个ITEM的高度带空白区域
	int m_iPerLineItemCount;							//当前工作区域每行存在多少个ITEM
	int m_iPerPageLineCount;							//当前工作区域能够显示几行
	int m_iTotalLineCount;								//总共需要显示的行数
	int m_iShowItemHead;								//显示的ITEM范围开始
	int m_iShowItemEnd;									//显示的ITEM范围结尾
	int m_iTotalColumnCount;							//总列数的统计

	UINT m_uiScrollBarType;								//拖动条的样式，横或竖

	ScrollBarState m_sbsHScrollBarState;				//横向拖动条的状态
	ScrollBarState m_sbsVScrollBarState;				//纵向拖动条的状态
	VectorColumnInfo m_vciColumnsInfo;					//详细信息样式时的每列信息存储对象
	MouseActionInfo m_maiMouseActionInfo;				//鼠标操作信息
	MousePositionInfo m_mpiMousePositionInfo;			//鼠标位置信息
	ScrollBarcColorSet m_sbcsScrollBarColorSet;			//滑动条颜色设置
	/**
	*	----重绘部分结束----
	*/

	// 重命名时的编辑框
	ReNameEdit m_wndEdit;
	bool m_bCreateEdit;			//是否创建重命名的编辑窗口
	//标记选中的文件
	int m_nSelect;

// Operations //运转, 操作, 实施, 作用, 业务, 工作, 手术, 军事行动
public:
	//=====================================================================
	// 函 数 名：InitLoadImageThread
	// 功能描述：初始化加载图象的线程
	// 输入参数：bool killThread:在线程运行状态时是否删除线程
	// 输出参数：void
	// 创建日期：08.09.15
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	void InitLoadImageThread (bool killThread);
	//=====================================================================
	// 函 数 名：InitLoadBaseInfoThread
	// 功能描述：初始化加载文件基本信息的线程
	// 输入参数：bool killThread:在线程运行状态时是否删除线程
	// 输出参数：void
	// 创建日期：08.09.16
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	void InitLoadBaseInfoThread (bool killThread);
	//=====================================================================
	// 函 数 名：OpenFloder
	// 功能描述：打开文件夹
	// 输入参数：string floderPath:带\号的文件夹路径
	// 输出参数：void
	// 创建日期：08.09.27
	// 修改日期：
	// 作 者：alzq
	// 附加说明：传入CDC，相关绘制参数结构体，是否被选择，是否窗口为焦点
	//=====================================================================
	void OpenFloder(CString floderPath);
	//=====================================================================
	// 函 数 名：GetItemCodeByMousePt
	// 功能描述：获取鼠标位置下的ITEM编号
	// 输入参数：CPoint pt
	// 输出参数：void
	// 创建日期：08.10.07
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	int GetItemCodeByMousePt(CPoint pt);
	//=====================================================================
	// 函 数 名：GetItemCodeByWindowPt
	// 功能描述：获取窗口相对位置下的ITEM编号
	// 输入参数：CPoint pt
	// 输出参数：void
	// 创建日期：08.10.07
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	int GetItemCodeByWindowPt(CPoint pt);
	//=====================================================================
	// 函 数 名：RefreshPreview
	// 功能描述：刷新预览窗口
	// 输入参数：无
	// 输出参数：无
	// 创建日期：2008.10.10
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明： 
	//=====================================================================
	void RefreshPreview(void);

	//=====================================================================
	// 函 数 名：showEdit
	// 功能描述：显示重命名编辑框
	// 输入参数：用户选中的文件索引值
	// 输出参数：无
	// 创建日期：2008.10.7
	// 修改日期: 
	// 作 者：   江显华
	// 附加说明： 
	//=====================================================================
	void showEdit(int nItem);
	//=====================================================================
	// 函 数 名：DisposeEdit
	// 功能描述：当失去焦点之后根据用户输入的新文件名判断是否更改文件名，是则更改
	// 输入参数：无
	// 输出参数：无
	// 创建日期：2008.10.7
	// 修改日期:  
	// 作 者：   江显华
	// 附加说明： 
	//=====================================================================
	void DisposeEdit(void);
	//=====================================================================
	// 函 数 名：SetListStyle
	// 功能描述：设置列表的显示样式
	// 输入参数：UINT style
	// 输出参数：无
	// 创建日期：2008.10.11
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明： 
	//=====================================================================
	void SetListStyle(UINT style);
	//=====================================================================
	// 函 数 名：SetSmallPhotoSize
	// 功能描述：设置缩略图大小
	// 输入参数：
	// 输出参数：无
	// 创建日期：2008.10.11
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明： 
	//=====================================================================
	void SetSmallPhotoSize();
	//=====================================================================
	// 函 数 名：SetSmallPhotoSize
	// 功能描述：设置缩略图大小
	// 输入参数：int width,int height
	// 输出参数：无
	// 创建日期：2008.10.11
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明： 
	//=====================================================================
	void SetSmallPhotoSize(int width,int height);
	//=====================================================================
	// 函 数 名：SetReportItemSize
	// 功能描述：设置详细信息样式时的相关ITEM信息
	// 输入参数：
	// 输出参数：无
	// 创建日期：2008.10.11
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明： 
	//=====================================================================
	void SetReportItemSize();
	//=====================================================================
	// 函 数 名：SetWorkAreaToItem
	// 功能描述：将显示区域设置到编号为nItem的Item所在区域
	// 输入参数：int nItem
	// 输出参数：无
	// 创建日期：2008.10.11
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	void SetWorkAreaToItem(int nItem);
	//=====================================================================
	// 函 数 名：SetWorkAreaToItemWithoutGroup
	// 功能描述：在未分组的情况下，将显示区域设置到编号为nItem的Item所在区域
	// 输入参数：int nItem
	// 输出参数：无
	// 创建日期：2008.10.11
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	void SetWorkAreaToItemWithoutGroup(int nItem);
	//=====================================================================
	// 函 数 名：SetShowItemRange
	// 功能描述：获取在高度top到bottom内显示的Item范围
	// 输入参数：int top,int bottom
	// 输出参数：ItemRange
	// 创建日期：2008.10.11
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	ItemRange SetShowItemRange(int top,int bottom);
	//=====================================================================
	// 函 数 名：GetItemPosition
	// 功能描述：获取第nItem个ITEM的位置:相对显示区域的内存DC(m_dcWorkAreaDC)
	// 输入参数：int nItem
	// 输出参数：CPoint
	// 创建日期：2008.10.12
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	CPoint GetItemPosition(int nItem);
	//=====================================================================
	// 函 数 名：OpenFloderList
	// 功能描述：打开文件夹
	// 输入参数：CString filePath
	// 输出参数：
	// 创建日期：2008.10.12
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	void OpenFloderList(CString filePath);
	//=====================================================================
	// 函 数 名：Refresh
	// 功能描述：刷新屏幕
	// 输入参数：
	// 输出参数：
	// 创建日期：2008.10.17
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	void Refresh();
	//=====================================================================
	// 函 数 名：Refresh
	// 功能描述：刷新屏幕指定范围的图象
	// 输入参数：CRect rect:刷新的范围
	// 输出参数：
	// 创建日期：2008.10.17
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	void Refresh(CRect rect);
	//=====================================================================
	// 函 数 名：RefreshWorkArea
	// 功能描述：刷新屏幕中的显示区域
	// 输入参数：
	// 输出参数：
	// 创建日期：2008.10.17
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	void RefreshWorkArea();
	//=====================================================================
	// 函 数 名：ReDrawItem
	// 功能描述：绘制一个ITEM并刷新ITEM的范围
	// 输入参数：int nItem
	// 输出参数：
	// 创建日期：2008.10.17
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	void ReDrawItem(int nItem);
	//=====================================================================
	// 函 数 名：ReDrawItems
	// 功能描述：绘制范围内的项,并刷新屏幕
	// 输入参数：int head,int end
	// 输出参数：
	// 创建日期：2008.10.17
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	void ReDrawItems(int head,int end);
	//=====================================================================
	// 函 数 名：DrawScrollBarBT
	// 功能描述：绘制拖动条DC上的按钮
	// 输入参数：
	// 输出参数：
	// 创建日期：2008.10.17
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	void DrawScrollBarBT();
	//=====================================================================
	// 函 数 名：InitScrollBar
	// 功能描述：初始化滑动条图象
	// 输入参数：
	// 输出参数：
	// 创建日期：2008.10.17
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	void InitScrollBar();
	//=====================================================================
	// 函 数 名：DrawScrollBarMidBT
	// 功能描述：绘制滑动条的滑动块（在显示DC上）
	// 输入参数：
	// 输出参数：
	// 创建日期：2008.10.17
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	void DrawScrollBarMidBT();
	//=====================================================================
	// 函 数 名：DrawReportHeader
	// 功能描述：绘制详细信息样式的表头
	// 输入参数：int nLine：-1为全部，否则为指定列
	// 输出参数：
	// 创建日期：2008.10.15
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	void DrawReportHeader(int nLine);
	//=====================================================================
	// 函 数 名：ReSetScrollBarInfo
	// 功能描述：重新计算拖动条的相关参数
	// 输入参数：
	// 输出参数：
	// 创建日期：2008.10.13
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	void ReSetScrollBarInfo();
	//=====================================================================
	// 函 数 名：InitColumnInfo
	// 功能描述：初始化列信息，需要读取数据库，暂时采用固定初始化
	// 输入参数：
	// 输出参数：
	// 创建日期：2008.10.13
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	void InitColumnInfo();
	//=====================================================================
	// 函 数 名：FillOutofWorkArea
	// 功能描述：填充非工作区的显示部分
	// 输入参数：
	// 输出参数：
	// 创建日期：2008.10.14
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	void FillOutofWorkArea();
	//=====================================================================
	// 函 数 名：SetMousePositionTypeAndValue
	// 功能描述：设置鼠标操作信息中的位置信息与相关值
	// 输入参数：CPoint pt:相对窗口的坐标
	// 输出参数：
	// 创建日期：2008.10.14
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	void SetMousePositionInfo(CPoint pt);
	//=====================================================================
	// 函 数 名：MoveWorkArea
	// 功能描述：移动可视区域
	// 输入参数：int dx,int dy
	// 输出参数：
	// 创建日期：2008.10.16
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	void MoveWorkArea(int dx,int dy);
	//=====================================================================
	// 函 数 名：SetWorkArea
	// 功能描述：设置可视区域位置
	// 输入参数：CPoint pt
	// 输出参数：
	// 创建日期：2008.10.16
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	void SetWorkArea(CPoint pt);
	//=====================================================================
	// 函 数 名：JumpLine
	// 功能描述：跳越行
	// 输入参数：int lineCount:以正负控制行的切换
	// 输出参数：
	// 创建日期：2008.10.16
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	void JumpLine(int lineCount);
	//=====================================================================
	// 函 数 名：DealLbtDownMes
	// 功能描述：处理左键按下时，相关位置的操作
	// 输入参数：UINT positionMes:位置信息
	// 输出参数：UINT：返回鼠标的操作信息，用于放置在鼠标动作信息对象中,UINT nFlags,CPoint point
	// 创建日期：2008.10.16
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	UINT DealLbtDownMes(UINT positionMes,UINT nFlags,CPoint point);
	//=====================================================================
	// 函 数 名：DragSelectedFiles
	// 功能描述：将所有被选中文件放入OLE拖拽对象，开始拖拽操作
	// 输入参数：
	// 输出参数：
	// 创建日期：2008.10.17
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	void DragSelectedFiles();
	//=====================================================================
	// 函 数 名：RedrawWorkArea
	// 功能描述：重新绘制显示区域的DC部分
	// 输入参数：bool reDraw
	// 输出参数：void
	// 创建日期：2008.10.17
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	void RedrawWorkArea(bool reDraw);
	//=====================================================================
	// 函 数 名：GetItemRect
	// 功能描述：获取ITEM在当前显示区域的区间
	// 输入参数：int nItem
	// 输出参数：CRect
	// 创建日期：2008.10.17
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	CRect GetItemRect(int nItem);

	//=====================================================================
	// 函 数 名：OnBeginDragLvOrType
	// 功能描述：开始拖拽等级或类型时
	// 输入参数：无
	// 输出参数：无
	// 创建日期：2008.10.09
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明： 
	//=====================================================================
	afx_msg LRESULT OnBeginDragLvOrType(WPARAM wParam,LPARAM lParam);
	//=====================================================================
	// 函 数 名：OnEndDragLvOrType
	// 功能描述：结束拖拽等级或类型时
	// 输入参数：无
	// 输出参数：无
	// 创建日期：2008.10.09
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明： 
	//=====================================================================
	afx_msg LRESULT OnEndDragLvOrType(WPARAM wParam,LPARAM lParam);
	//=====================================================================
	// 函 数 名：OnMouseLeave
	// 功能描述：鼠标离开窗口触发函数
	// 输入参数：无
	// 输出参数：无
	// 创建日期：2008.10.15
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明： 
	//=====================================================================
	afx_msg LRESULT OnMouseLeave(WPARAM wParam,LPARAM lParam);
	//=====================================================================
	// 函 数 名：OnRefreshAll
	// 功能描述：根据各个内存存储DC,刷新显示
	// 输入参数：无
	// 输出参数：无
	// 创建日期：2008.10.20
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明： 
	//=====================================================================
	afx_msg LRESULT OnRefreshAll(WPARAM wParam,LPARAM lParam);
	//=====================================================================
	// 函 数 名：OnRefreshItem
	// 功能描述：根据内存存储DC刷新第一个参数指定的ITEM
	// 输入参数：无
	// 输出参数：无
	// 创建日期：2008.10.20
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明： 
	//=====================================================================
	afx_msg LRESULT OnRefreshItem(WPARAM wParam,LPARAM lParam);

protected:
	//=====================================================================
	// 函 数 名：_ResizeWorkAreaWithoutGroup
	// 功能描述：在缩略图模式下，重新设置显示区域大小
	// 输入参数：int width,int height,bool setToSelected
	// 输出参数：无
	// 创建日期：2008.10.11
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明： 
	//=====================================================================
	void _ResizeWorkAreaWithoutGroup(int width,int height,bool setToSelected);
	//=====================================================================
	// 函 数 名：_ResizeWorkAreaWithoutGroup
	// 功能描述：在缩略图模式下，重新设置显示区域大小
	// 输入参数：bool setToSelected
	// 输出参数：无
	// 创建日期：2008.10.11
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明： 
	//=====================================================================
	void _ResizeWorkAreaWithoutGroup(bool setToSelected);
	//=====================================================================
	// 函 数 名：_ResizeWorkAreaWithoutGroupSmallPhoto
	// 功能描述：SMALLPHOTO样式下的重新设置显示区域大小
	// 输入参数：int width,int height,bool setToSelected
	// 输出参数：
	// 创建日期：2008.10.13
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	void _ResizeWorkAreaWithoutGroupSmallPhoto(int width,int height,bool setToSelected);
	//=====================================================================
	// 函 数 名：_ResizeWorkAreaWithoutGroupReport
	// 功能描述：REPORT样式下的重新设置显示区域大小
	// 输入参数：int width,int height,bool setToSelected
	// 输出参数：
	// 创建日期：2008.10.13
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	void _ResizeWorkAreaWithoutGroupReport(int width,int height,bool setToSelected);
	//=====================================================================
	// 函 数 名：_CheckWorkArea
	// 功能描述：验证显示区域是否超出范围
	// 输入参数：
	// 输出参数：
	// 创建日期：2008.10.18
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	void _CheckWorkArea();
	//=====================================================================
	// 函 数 名：_ReDrawItems
	// 功能描述：重新绘制范围内的Item
	// 输入参数：int head,int end
	// 输出参数：无
	// 创建日期：2008.10.11
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	void _ReDrawItems(int head,int end);
	//=====================================================================
	// 函 数 名：_ReDrawItems
	// 功能描述：重新绘制范围内的Item
	// 输入参数：int head,int end,int leftLine,int rightLine
	// 输出参数：无
	// 创建日期：2008.10.11
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	void _ReDrawItems(int head,int end,int leftLine,int rightLine);
	//=====================================================================
	// 函 数 名：_ReDrawRect
	// 功能描述：重新绘制区域内的项
	// 输入参数：CRect rect
	// 输出参数：无
	// 创建日期：2008.10.15
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	void _ReDrawRect(CRect rect);
	//=====================================================================
	// 函 数 名：_PrintItem
	// 功能描述：绘制编号为nItem的ITEM
	// 输入参数：int nItem:编号,int leftLine,int rightLine
	// 输出参数：void
	// 创建日期：08.10.11
	// 修改日期：
	// 作 者：alzq
	// 附加说明：绘制在存放的背景DC上
	//=====================================================================
	void _PrintItem(int nItem,int leftLine,int rightLine);
	//=====================================================================
	// 函 数 名：_PrintItemSmallPhoto
	// 功能描述：Item图象具体绘制函数
	// 输入参数：CPoint pt:显示ITEM的坐标
	//			 FileInfoList * fileInfo:ITEM指向的文件
	// 输出参数：void
	// 创建日期：08.10.13
	// 修改日期：
	// 作 者：alzq
	// 附加说明：传入CDC，相关绘制参数结构体，是否窗口为焦点
	//=====================================================================
	void _PrintItemSmallPhoto(CPoint pt,FileInfoList * fileInfo);
	//=====================================================================
	// 函 数 名：_PrintItemReport
	// 功能描述：Item图象具体绘制函数
	// 输入参数：CPoint pt:显示ITEM的坐标
	//			 FileInfoList * fileInfo:ITEM指向的文件
	//			 int leftLine,int rightLine:绘制的左右边界
	// 输出参数：void
	// 创建日期：08.10.14
	// 修改日期：
	// 作 者：alzq
	// 附加说明：传入CDC，相关绘制参数结构体，是否窗口为焦点
	//=====================================================================
	void _PrintItemReport(CPoint pt,FileInfoList * fileInfo,int leftLine,int rightLine);
	//=====================================================================
	// 函 数 名：_PrintSmallPhoto
	// 功能描述：缩略图部分的绘制函数，只绘制图象与评级标志，图标等
	// 输入参数：Gdiplus::Graphics * graph,CPoint pt:显示ITEM的坐标
	//			 FileInfoList * fileInfo:ITEM指向的文件
	// 输出参数：void
	// 创建日期：08.08.29
	// 修改日期：08.08.29
	// 作 者：alzq
	// 附加说明：传入CDC，相关绘制参数结构体，是否被选择，是否窗口为焦点
	//=====================================================================
	void _PrintSmallPhoto(Gdiplus::Graphics * graph,CPoint pt,FileInfoList * fileInfo);
	//=====================================================================
	// 函 数 名：_DeleteDC
	// 功能描述：删除CDC对象
	// 输入参数：CDC * dc
	// 输出参数：void
	// 创建日期：08.10.17
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	void _DeleteDC(CDC * dc);
	//=====================================================================
	// 函 数 名：_DeleteBmp
	// 功能描述：删除CBitmap对象
	// 输入参数：CBitmap * bmp
	// 输出参数：void
	// 创建日期：08.10.17
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	void _DeleteBmp(CBitmap * bmp);
	//=====================================================================
	// 函 数 名：_CreateDC
	// 功能描述：建立DC对象
	// 输入参数：CDC * dc,CBitmap * bmp,CDC * pDC,int width,int height
	// 输出参数：void
	// 创建日期：08.10.17
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	void _CreateDC(CDC * dc,CBitmap * bmp,CDC * pDC,int width,int height);
	//=====================================================================
	// 函 数 名：_BuildDC
	// 功能描述：建立显示的DC
	// 输入参数：
	// 输出参数：
	// 创建日期：2008.10.17
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	void _BuildDC();
	//=====================================================================
	// 函 数 名：_MoveWorkArea
	// 功能描述：移动可视区域,但是不刷新显示
	// 输入参数：int dx,int dy
	// 输出参数：
	// 创建日期：2008.10.20
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	void _MoveWorkArea(int dx,int dy);
	//=====================================================================
	// 函 数 名：_DragSelect
	// 功能描述：移动可视区域,但是不刷新显示
	// 输入参数：CPoint startPt:开始拖拉选择的绝对坐标
	//			 CPoint oldPt:上一个拖拉选择结束的绝对坐标
	//			 CPoint nowPt:当前的绝对坐标
	// 输出参数：
	// 创建日期：2008.10.20
	// 修改日期:  
	// 作 者：   alzq
	// 附加说明：
	//=====================================================================
	void _DragSelect(CPoint startPt,CPoint oldPt,CPoint nowPt);

// Overridables //可重载的

// Implementation //实现
public:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//=====================================================================
	// 函 数 名：OnLvnColumnclick
	// 功能描述：对列内容进行排序
	// 输入参数：NMHDR *pNMHDR, LRESULT *pResult
	// 输出参数：void
	// 创建日期：08.09.27
	// 修改日期：
	// 作 者：alzq
	// 附加说明：
	//=====================================================================
	afx_msg void OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnLvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnAlzqListView();
	afx_msg void OnAlzqListCut();
	afx_msg void OnAlzqListCopy();
	afx_msg void OnAlzqListCutFloder();
	afx_msg void OnAlzqListCopyFloder();
	afx_msg void OnAlzqListRename();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnAlzqListAddcolection();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
