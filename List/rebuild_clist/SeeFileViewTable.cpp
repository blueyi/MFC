#include "StdAfx.h"
#include "SeeFileViewTable.h"

SeeFileViewTable::SeeFileViewTable(void)
{
	// TODO:  在此添加您专用的创建代码

	m_bSelectedFileEnable=true;								//是否需要过滤文件
	m_bDealMouseAction=true;
	m_iDragInfo=-1;											//当拖拽评级或类型到LIST中时，根据本变量对等级或类型进行设置

	m_uiViewStyle=STYLE_SMALL_PHOTO;						//ListCtrl查看的样式值

	m_hLoadImage=NULL;										//加载图象的线程指针，载入并缩放，不产生DC
	m_hLoadBaseInfo=NULL;									//加载文件基本信息

	m_cmRightButtonMenu.LoadMenuA(IDR_MENU_ALZQ_LIST_PHOTO);	//获取全部右键菜单的对象

	m_brUnselectedBrush=new Gdiplus::SolidBrush(Gdiplus::Color(227,237,255));			//未选择的ITEM背景刷
	m_brSelectedBrush=new Gdiplus::SolidBrush(Gdiplus::Color(93,147,174));				//已选择的ITEM背景刷
	m_brSelectedUnfoucBrush=new Gdiplus::SolidBrush(Gdiplus::Color(170,180,200));		//已选择的ITEM窗口无焦点背景刷
	m_brSelectBrush=new Gdiplus::SolidBrush(Gdiplus::Color(50,15,35,120));				//拖拉选择时的覆盖部分颜色
	m_brScrollBarBakBrush=new Gdiplus::SolidBrush(Gdiplus::Color(250,250,240));			//拖拉条的背景刷
	m_brScrollBarMidBakBrush=new Gdiplus::SolidBrush(Gdiplus::Color(253,246,225));		//正常情况下拖拉划块的背景刷
	m_brScrollBarMidMouseOnBrush=new Gdiplus::SolidBrush(Gdiplus::Color(255,219,108));	//鼠标悬停情况下的拖拉划块背景刷
	m_brScrollBarMidDragBrush=new Gdiplus::SolidBrush(Gdiplus::Color(200,172,85));		//拖拉情况下的拖拉划块背景刷
	m_brBakBrush=new Gdiplus::SolidBrush(Gdiplus::Color(255,255,255));					//总的背景刷
	m_penFoucItem=new Gdiplus::Pen(Gdiplus::Color(0,0,0),1);							//具有焦点的ITEM描边
	m_penFoucItem->SetDashStyle(DashStyleDot);											//设置为虚线
	m_penSelectedItem=new Gdiplus::Pen(Gdiplus::Color(0,0,0),1);						//被选择的ITEM描边
	m_penItemBorder=new Gdiplus::Pen(Gdiplus::Color(50,15,35,120),1);					//Item边缘刷
	m_penScrollBarMidBakBorder=new Gdiplus::Pen(Gdiplus::Color(232,186,88),2);			//正常情况下拖拉划块的边缘刷
	m_penScrollBarMidMouseOnBorder=new Gdiplus::Pen(Gdiplus::Color(233,159,0),2);		//鼠标悬停情况下的拖拉划块边缘刷
	m_penScrollBarMidDragBorder=new Gdiplus::Pen(Gdiplus::Color(176,121,2),2);			//拖拉情况下的拖拉划块边缘刷
	m_brFontBrush = new SolidBrush( Gdiplus::Color(0,0,0) );

	m_sbcsScrollBarColorSet.normalBak=RGB(253,246,225);
	m_sbcsScrollBarColorSet.normalBorder=RGB(232,186,88);
	m_sbcsScrollBarColorSet.mouseOnBak=RGB(255,219,108);
	m_sbcsScrollBarColorSet.mouseOnBorder=RGB(233,159,0);
	m_sbcsScrollBarColorSet.mouseDownBak=RGB(200,172,85);
	m_sbcsScrollBarColorSet.mouseDownBorder=RGB(176,121,2);

	m_imgDefaultDisk=Gdiplus::Image::FromFile(L"res\\disk.png");							//默认磁盘图标
	m_imgDefaultFloder=Gdiplus::Image::FromFile(L"res\\floder.png");						//默认文件夹图标
	m_imgDefaultPic=Gdiplus::Image::FromFile(L"res\\91See.bmp");							//ITEM默认图标
	m_imgShadowRight=Gdiplus::Image::FromFile(L"res\\shadow_right.png");					//默认文件夹图标
	m_imgShadowDown=Gdiplus::Image::FromFile(L"res\\shadow_down.png");						//ITEM默认图标
	m_imgShadowRightDown=Gdiplus::Image::FromFile(L"res\\shadow_right_down.png");			//默认文件夹图标

	m_ffFontFamily=new FontFamily(L"宋体");
	m_sfStringFormatLeft=new StringFormat();
	m_sfStringFormatLeft->SetAlignment(StringAlignmentNear);
	m_sfStringFormatRight=new StringFormat();
	m_sfStringFormatRight->SetAlignment(StringAlignmentFar);
	m_sfStringFormatCenter=new StringFormat();
	m_sfStringFormatCenter->SetAlignment(StringAlignmentCenter);
	m_fntFontBlod=new Gdiplus::Font(m_ffFontFamily,10,FontStyleBold,UnitPoint);
	m_fntFontNormal=new Gdiplus::Font(m_ffFontFamily,10,FontStyleRegular,UnitPoint);		//绘制文字的样式不加粗

	//评级的等级图标列表
	m_cilLevelsIcon=new CImageList();
	m_cilLevelsIcon->DeleteImageList();
	m_cilLevelsIcon->Create(16,16,ILC_COLOR32 | TRUE, 6, 0);
	PublicFunc::ReadImageList("res\\levels.bmp",m_cilLevelsIcon);

	//拖动条的向上
	m_cilScrollBarUp=new CImageList();
	m_cilScrollBarUp->DeleteImageList();
	m_cilScrollBarUp->Create(20,20,ILC_COLOR32 | TRUE, 3, 0);
	PublicFunc::ReadImageList("res\\scrollUp.bmp",m_cilScrollBarUp);

	//拖动条的向下
	m_cilScrollBarDown=new CImageList();
	m_cilScrollBarDown->DeleteImageList();
	m_cilScrollBarDown->Create(20,20,ILC_COLOR32 | TRUE, 3, 0);
	PublicFunc::ReadImageList("res\\scrollDown.bmp",m_cilScrollBarDown);

	//拖动条的向上
	m_cilScrollBarLeft=new CImageList();
	m_cilScrollBarLeft->DeleteImageList();
	m_cilScrollBarLeft->Create(20,20,ILC_COLOR32 | TRUE, 3, 0);
	PublicFunc::ReadImageList("res\\scrollLeft.bmp",m_cilScrollBarLeft);

	//拖动条的向下
	m_cilScrollBarRight=new CImageList();
	m_cilScrollBarRight->DeleteImageList();
	m_cilScrollBarRight->Create(20,20,ILC_COLOR32 | TRUE, 3, 0);
	PublicFunc::ReadImageList("res\\scrollRight.bmp",m_cilScrollBarRight);

	m_wndPreviewBar=NULL;
	m_wndFavoriteBar=NULL;

	m_bCreateEdit=false;


	/**
	*	----重绘部分变量----
	*/
	m_cbBakMemeryBmp=NULL;								//背景绘制图象的存储对象
	m_cbWorkAreaBmp=NULL;								//绘制显示区域的图象存储对象
	m_cbHeaderBmp=NULL;									//表头的图象存储对象
	m_cbScrollVBmp=NULL;								//表头的图象存储对象
	m_cbScrollHBmp=NULL;								//表头的图象存储对象
	m_dcMemeryDC=NULL;									//背景绘制的内存DC
	m_dcWorkAreaDC=NULL;								//显示区域部分的内存DC
	m_dcHeaderDC=NULL;									//表头部分的内存DC
	m_dcScrollVDC=NULL;									//纵向滚动条部分的内存DC
	m_dcScrollHDC=NULL;									//横向滚动条部分的内存DC
	m_dcBakDC=NULL;										//背景绘制的DC

	m_bListGetFouc=false;								//List是否获取到焦点
	m_bMouseTracking=FALSE;

	m_iWorkAreaTop=0;									//当前显示部分的顶部Y坐标-相对m_iWorkAreaHeight
	m_iWorkAreaBottom=0;								//当前显示部分的底部Y坐标-相对m_iWorkAreaHeight
	m_iOldWorkAreaTop=0;								//当前显示部分的顶部更新前Y坐标-相对m_iWorkAreaHeight
	m_iOldWorkAreaBottom=0;								//当前显示部分的底部更新前Y坐标-相对m_iWorkAreaHeight
	m_iWorkAreaLeft=0;									//当前显示部分的左边界坐标-相对m_iWorkAreaWidth
	m_iWorkAreaRight=0;									//当前显示部分的右边界坐标-相对m_iWorkAreaWidth
	m_iCurrentViewWidth=0;								//当前显示部分的宽度
	m_iCurrentViewHeight=0;								//当前显示部分的高度
	m_iCurrentStartNItem=0;								//当前显示区域显示的第一个ITEM编号
	m_iCurrentEndNItem=0;								//当前显示区域显示的最后一个ITEM编号
	m_iWorkAreaWidth=0;									//item显示区域宽度
	m_iWorkAreaHeight=0;								//item显示区域高度
	m_iWorkAreaTotalHeight=0;							//item显示区域总高度
	m_iWorkAreaTotalWidth=0;							//item显示区域总宽度
	m_iItemWidth=0;										//每个ITEM的宽度
	m_iItemHeight=0;									//每个ITEM的高度
	m_iItemWithBorderWidth=0;							//每个ITEM的宽度带空白区域
	m_iItemWithBorderHeight=0;							//每个ITEM的高度带空白区域
	m_iPerLineItemCount=0;								//当前工作区域每行存在多少个ITEM
	m_iPerPageLineCount=0;								//当前工作区域能够显示几行
	m_iTotalLineCount=0;								//总共需要显示的行数
	m_iShowItemHead=0;									//显示的ITEM范围开始
	m_iShowItemEnd=0;									//显示的ITEM范围结尾
	m_iTotalColumnCount=0;								//总列数的统计

	m_uiScrollBarType=SCROLL_BAR_NONE;					//拖动条的样式，横或竖
	InitColumnInfo();

	m_mpiMousePositionInfo.positionType=POSITION_OUT;
	m_maiMouseActionInfo.mouseCondition=MOUSE_NONE;
	m_maiMouseActionInfo.mousePositionInfo.positionType=POSITION_OUT;
	m_maiMouseActionInfo.mousePositionInfo.value=0;
}

SeeFileViewTable::~SeeFileViewTable(void)
{
	_DeleteBmp(m_cbBakMemeryBmp);							//背景绘制图象的存储对象
	_DeleteBmp(m_cbWorkAreaBmp);							//绘制显示区域的图象存储对象
	_DeleteBmp(m_cbHeaderBmp);								//表头的图象存储对象
	_DeleteBmp(m_cbScrollVBmp);								//纵向滚动条的图象存储对象
	_DeleteBmp(m_cbScrollHBmp);								//横向滚动条的图象存储对象
	_DeleteDC(m_dcMemeryDC);								//背景绘制的内存DC
	_DeleteDC(m_dcWorkAreaDC);								//显示区域部分的内存DC
	_DeleteDC(m_dcHeaderDC);								//表头部分的内存DC
	_DeleteDC(m_dcScrollVDC);								//纵向滚动条部分的内存DC
	_DeleteDC(m_dcScrollHDC);								//横向滚动条部分的内存DC

	m_cilLevelsIcon->DeleteImageList();		//评级的等级图标列表
	m_cilScrollBarUp->DeleteImageList();	//拖动条的向上
	m_cilScrollBarDown->DeleteImageList();	//拖动条的向下
	m_cilScrollBarLeft->DeleteImageList();	//拖动条的向左
	m_cilScrollBarRight->DeleteImageList();	//拖动条的向右
	delete m_cilLevelsIcon;					//评级的等级图标列表
	delete m_cilScrollBarUp;				//拖动条的向上
	delete m_cilScrollBarDown;				//拖动条的向下
	delete m_cilScrollBarLeft;				//拖动条的向左
	delete m_cilScrollBarRight;				//拖动条的向右
	PublicFunc::DeleteThread(m_hLoadImage);
	PublicFunc::DeleteThread(m_hLoadBaseInfo);
}
BEGIN_MESSAGE_MAP(SeeFileViewTable, CWnd)
	ON_WM_LBUTTONDBLCLK()
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, &SeeFileViewTable::OnLvnColumnclick)
	ON_WM_DROPFILES()
	ON_NOTIFY_REFLECT(LVN_BEGINDRAG, &SeeFileViewTable::OnLvnBegindrag)

	ON_MESSAGE(MES_ALZQ_BEGIN_DRAG_LV,&SeeFileViewTable::OnBeginDragLvOrType)
	ON_MESSAGE(MES_ALZQ_BEGIN_DRAG_TYPE,&SeeFileViewTable::OnBeginDragLvOrType)
	ON_MESSAGE(MES_ALZQ_END_DRAG_LV,&SeeFileViewTable::OnEndDragLvOrType)
	ON_MESSAGE(MES_ALZQ_END_DRAG_TYPE,&SeeFileViewTable::OnEndDragLvOrType)
	ON_MESSAGE(WM_MOUSELEAVE,&SeeFileViewTable::OnMouseLeave)
	ON_COMMAND(ID_ALZQ_LIST_VIEW, &SeeFileViewTable::OnAlzqListView)
	ON_COMMAND(ID_ALZQ_LIST_CUT, &SeeFileViewTable::OnAlzqListCut)
	ON_COMMAND(ID_ALZQ_LIST_COPY, &SeeFileViewTable::OnAlzqListCopy)
	ON_COMMAND(ID_ALZQ_LIST_CUT_FLODER, &SeeFileViewTable::OnAlzqListCutFloder)
	ON_COMMAND(ID_ALZQ_LIST_COPY_FLODER, &SeeFileViewTable::OnAlzqListCopyFloder)
	ON_COMMAND(ID_ALZQ_LIST_RENAME, &SeeFileViewTable::OnAlzqListRename)

	ON_COMMAND(ID_ALZQ_LIST_OTHER_CUT, &SeeFileViewTable::OnAlzqListCut)
	ON_COMMAND(ID_ALZQ_LIST_OTHER_COPY, &SeeFileViewTable::OnAlzqListCopy)
	ON_COMMAND(ID_ALZQ_LIST_OTHER_CUT_FLODER, &SeeFileViewTable::OnAlzqListCutFloder)
	ON_COMMAND(ID_ALZQ_LIST_OTHER_COPY_FLODER, &SeeFileViewTable::OnAlzqListCopyFloder)
	ON_COMMAND(ID_ALZQ_LIST_OTHER_RENAME, &SeeFileViewTable::OnAlzqListRename)
	ON_COMMAND(ID_ALZQ_LIST_ADDCOLECTION, &SeeFileViewTable::OnAlzqListAddcolection)

	ON_MESSAGE(MES_ALZQ_REFRESH_ALL,&SeeFileViewTable::OnRefreshAll)
	ON_MESSAGE(MES_ALZQ_REFRESH_ITEM,&SeeFileViewTable::OnRefreshItem)

	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_KILLFOCUS()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	ON_WM_NCLBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_NCHITTEST()
	ON_WM_ACTIVATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()
	

//=====================================================================
// 函 数 名：ResizeWorkAreaWithoutGroup
// 功能描述：在缩略图模式下，重新设置显示区域大小
// 输入参数：int width,int height,bool setToSelected:是否设置显示到被选择ITEM上
// 输出参数：无
// 创建日期：2008.10.11
// 修改日期:  
// 作 者：   alzq
// 附加说明： 
//=====================================================================
void SeeFileViewTable::_ResizeWorkAreaWithoutGroup(int width,int height,bool setToSelected)
{
	if(m_uiViewStyle == STYLE_SMALL_PHOTO)
	{
		//缩略图模式
		_ResizeWorkAreaWithoutGroupSmallPhoto(width,height,setToSelected);
	}
	else if(m_uiViewStyle == STYLE_REPORT)
	{
		//详细信息模式
		_ResizeWorkAreaWithoutGroupReport(width,height,setToSelected);
	}

	_BuildDC();

	if(m_uiScrollBarType)
	{
		//当拖拉条样式不为0时表示存在横向或竖向任一拖拉条
		//计算拖动条的相关数据
		ReSetScrollBarInfo();
	}
}
		

//=====================================================================
// 函 数 名：_ResizeWorkAreaWithoutGroupSmallPhoto
// 功能描述：SMALLPHOTO样式下的重新设置显示区域大小
// 输入参数：
// 输出参数：
// 创建日期：2008.10.13
// 修改日期:  
// 作 者：   alzq
// 附加说明：
//=====================================================================
void SeeFileViewTable::_ResizeWorkAreaWithoutGroupSmallPhoto(int width,int height,bool setToSelected)
{
	//进行区域部分的计算
	m_iWorkAreaWidth=width;					//确定item显示区域宽度
	m_iCurrentViewWidth=width;				//显示区域宽度
	m_iCurrentViewHeight=height;			//显示区域高度
	m_iWorkAreaHeight=height;				//item显示区域高度
	m_iPerLineItemCount=((m_iWorkAreaWidth-1)/m_iItemWithBorderWidth);				//每行显示的ITEM数量
	if(m_iPerLineItemCount<=0){m_iPerLineItemCount=1;}

	//当显示方式为缩略图时，采用如下计算
	m_iTotalLineCount=((m_ficFileControl.m_iTotalCount-1)/m_iPerLineItemCount)+1;		//计算一共需要显示几行
	if(m_ficFileControl.m_iTotalCount<=0){m_iTotalLineCount=0;}
	m_iWorkAreaTotalHeight=m_iTotalLineCount * m_iItemWithBorderHeight;					//计算需要显示的总高度，与显示区域进行比较，以确定是否需要显示拖动条

	if(m_iWorkAreaTotalHeight>height)
	{
		//当需要的显示高度大于显示区域高度时，需要有竖向的拖动条
		m_uiScrollBarType=SCROLL_BAR_V;

		//当存在竖向拖动条时，显示区域宽度减少,需要对显示的行数等进行重新计算
		m_iWorkAreaWidth=m_iWorkAreaWidth-SCROLL_BAR_WIDTH_HEIGHT;
		
		//开始重新计算每行的ITEM数量
		m_iPerLineItemCount=((m_iWorkAreaWidth-1)/m_iItemWithBorderWidth);			//每行显示的ITEM数量
		if(m_iPerLineItemCount<=0){m_iPerLineItemCount=1;}
		m_iTotalLineCount=((m_ficFileControl.m_iTotalCount-1)/m_iPerLineItemCount)+1;	//计算一共需要显示几行
		if(m_ficFileControl.m_iTotalCount<=0){m_iTotalLineCount=0;}
		m_iWorkAreaTotalHeight=m_iTotalLineCount * m_iItemWithBorderHeight;				//计算需要显示的总高度
	}
	else
	{
		m_uiScrollBarType=SCROLL_BAR_NONE;
	}

	m_iPerPageLineCount=((m_iWorkAreaHeight-1)/m_iItemWithBorderHeight)+1;				//每页能够显示的行数
	m_iWorkAreaLeft=0;
	m_iWorkAreaRight=m_iWorkAreaWidth;
	m_iWorkAreaTotalWidth=m_iWorkAreaWidth;

	//进行当前区域范围计算
	if(setToSelected)
	{
		//将显示区域设置到第一个被选择项
		int nItem=m_ficFileControl.GetFirstSelectedCode();		//获取第一个被选择项编号
		SetWorkAreaToItemWithoutGroup(nItem);
	}
	else
	{
		if(m_iWorkAreaBottom>m_iWorkAreaTotalHeight)
		{
			m_iWorkAreaBottom=m_iWorkAreaTotalHeight>m_iWorkAreaHeight?m_iWorkAreaTotalHeight:m_iWorkAreaHeight;
			m_iWorkAreaTop=m_iWorkAreaBottom-m_iWorkAreaHeight;
		}
		if(m_iWorkAreaTop<0)
		{
			m_iWorkAreaTop=0;
			m_iWorkAreaBottom=m_iWorkAreaTop+m_iWorkAreaHeight;
		}
		//设置显示范围
		ItemRange rang=SetShowItemRange(m_iWorkAreaTop,m_iWorkAreaBottom);
		m_iShowItemHead=rang.head;
		m_iShowItemEnd=rang.end;
	}
}
		

//=====================================================================
// 函 数 名：_ResizeWorkAreaWithoutGroupReport
// 功能描述：REPORT样式下的重新设置显示区域大小
// 输入参数：
// 输出参数：
// 创建日期：2008.10.13
// 修改日期:  
// 作 者：   alzq
// 附加说明：
//=====================================================================
void SeeFileViewTable::_ResizeWorkAreaWithoutGroupReport(int width,int height,bool setToSelected)
{
	//进行区域部分的计算
	m_iWorkAreaWidth=width;										//确定item显示区域宽度
	m_iCurrentViewWidth=width;									//显示区域宽度
	m_iCurrentViewHeight=height;								//显示区域高度
	m_iWorkAreaHeight=height-REPORT_HEAD_HEIGHT;				//item显示区域高度
	m_iPerLineItemCount=1;										//每行显示的ITEM数量

	//当显示方式为缩略图时，采用如下计算
	m_iTotalLineCount=m_ficFileControl.m_iTotalCount;			//一共需要显示的行数与项数相等
	m_iWorkAreaTotalHeight=m_iTotalLineCount * m_iItemWithBorderHeight;			//计算需要显示的总高度，与显示区域进行比较，以确定是否需要显示拖动条

	//从数据库中读取列信息，暂时采用固定的初始化方法
	InitColumnInfo();

	if(m_iWorkAreaTotalWidth > m_iWorkAreaWidth)
	{
		//当需要显示的宽度大于显示区域的宽度时，需要显示横向拖拉条，使用|=设置拖拉条类型
		m_uiScrollBarType=SCROLL_BAR_H;

		m_iWorkAreaHeight=m_iWorkAreaHeight-SCROLL_BAR_WIDTH_HEIGHT;
	}
	else
	{
		m_uiScrollBarType=SCROLL_BAR_NONE;
	}

	if(m_iWorkAreaHeight<0){m_iWorkAreaHeight=0;}

	if(m_iWorkAreaTotalHeight>m_iWorkAreaHeight)
	{
		//当需要的显示高度大于显示区域高度时，需要有竖向的拖动条
		m_uiScrollBarType|=SCROLL_BAR_V;

		//当存在竖向拖动条时，显示区域宽度减少,需要对显示的行数等进行重新计算
		m_iWorkAreaWidth=m_iWorkAreaWidth-SCROLL_BAR_WIDTH_HEIGHT;
	}

	m_iPerPageLineCount=((m_iWorkAreaHeight-1)/m_iItemWithBorderHeight)+1;				//每页能够显示的行数

	//进行横向区域的计算
	if(m_iWorkAreaLeft<0){m_iWorkAreaLeft=0;}
	m_iWorkAreaRight=m_iWorkAreaLeft+m_iWorkAreaWidth;
	if(m_iWorkAreaTotalWidth>m_iWorkAreaWidth && m_iWorkAreaRight>m_iWorkAreaTotalWidth)
	{
		m_iWorkAreaRight=m_iWorkAreaTotalWidth;
		m_iWorkAreaLeft=m_iWorkAreaRight-m_iWorkAreaWidth;
	}

	//进行当前区域范围计算
	if(setToSelected)
	{
		//将显示区域设置到第一个被选择项
		int nItem=m_ficFileControl.GetFirstSelectedCode();		//获取第一个被选择项编号
		SetWorkAreaToItemWithoutGroup(nItem);
	}
	else
	{
		if(m_iWorkAreaBottom>m_iWorkAreaTotalHeight)
		{
			m_iWorkAreaBottom=m_iWorkAreaTotalHeight>m_iWorkAreaHeight?m_iWorkAreaTotalHeight:m_iWorkAreaHeight;
			m_iWorkAreaTop=m_iWorkAreaBottom-m_iWorkAreaHeight;
		}
		if(m_iWorkAreaTop<0)
		{
			m_iWorkAreaTop=0;
			m_iWorkAreaBottom=m_iWorkAreaTop+m_iWorkAreaHeight;
		}
		//设置显示范围
		ItemRange rang=SetShowItemRange(m_iWorkAreaTop,m_iWorkAreaBottom);
		m_iShowItemHead=rang.head;
		m_iShowItemEnd=rang.end;
	}
}
	

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
void SeeFileViewTable::_CheckWorkArea()
{
	if(m_iWorkAreaBottom>m_iWorkAreaTotalHeight)
	{
		m_iWorkAreaBottom=m_iWorkAreaTotalHeight>m_iWorkAreaHeight?m_iWorkAreaTotalHeight:m_iWorkAreaHeight;
		m_iWorkAreaTop=m_iWorkAreaBottom-m_iWorkAreaHeight;
	}
	if(m_iWorkAreaTop<0)
	{
		m_iWorkAreaTop=0;
		m_iWorkAreaBottom=m_iWorkAreaTop+m_iWorkAreaHeight;
	}

	//进行横向区域的计算
	if(m_iWorkAreaLeft<0){m_iWorkAreaLeft=0;}
	m_iWorkAreaRight=m_iWorkAreaLeft+m_iWorkAreaWidth;
	if(m_iWorkAreaTotalWidth>m_iWorkAreaWidth && m_iWorkAreaRight>m_iWorkAreaTotalWidth)
	{
		m_iWorkAreaRight=m_iWorkAreaTotalWidth;
		m_iWorkAreaLeft=m_iWorkAreaRight-m_iWorkAreaWidth;
	}
	else if(m_iWorkAreaWidth>=m_iWorkAreaTotalWidth && m_iWorkAreaRight>m_iWorkAreaWidth)
	{
		m_iWorkAreaRight=m_iWorkAreaWidth;
		m_iWorkAreaLeft=0;
	}

	//设置显示范围
	ItemRange rang=SetShowItemRange(m_iWorkAreaTop,m_iWorkAreaBottom);
	m_iShowItemHead=rang.head;
	m_iShowItemEnd=rang.end;
}
	

//=====================================================================
// 函 数 名：ResizeWorkAreaWithoutGroup
// 功能描述：在缩略图模式下，重新设置显示区域大小
// 输入参数：bool setToSelected:是否设置显示到被选择ITEM上
// 输出参数：无
// 创建日期：2008.10.11
// 修改日期:  
// 作 者：   alzq
// 附加说明： 
//=====================================================================
void SeeFileViewTable::_ResizeWorkAreaWithoutGroup(bool setToSelected)
{
	_ResizeWorkAreaWithoutGroup(m_iCurrentViewWidth,m_iCurrentViewHeight,setToSelected);
}
	

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
void SeeFileViewTable::_ReDrawItems(int head,int end)
{
	_ReDrawItems(head,end,0,m_iWorkAreaWidth);
}
	

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
void SeeFileViewTable::_ReDrawItems(int head,int end,int leftLine,int rightLine)
{
	for(int i=head;i<=end;i++)
	{
		_PrintItem(i,leftLine,rightLine);
	}
}
	

//=====================================================================
// 函 数 名：_ReDrawRect
// 功能描述：重新绘制区域内的项
// 输入参数：CRect rect:窗口内坐标的范围
// 输出参数：无
// 创建日期：2008.10.15
// 修改日期:  
// 作 者：   alzq
// 附加说明：
//=====================================================================
void SeeFileViewTable::_ReDrawRect(CRect rect)
{
	if(m_uiViewStyle & STYLE_SMALL_PHOTO | STYLE_REPORT)
	{
		//当为缩略图样式时
		int top=rect.top+m_iWorkAreaTop;
		int bottom=rect.bottom+m_iWorkAreaTop;

		//求出在这个高度范围下的ITEM范围
		ItemRange itemRange=SetShowItemRange(top,bottom);
		_ReDrawItems(itemRange.head,itemRange.end,rect.left,rect.right);

		if(m_uiViewStyle==STYLE_SMALL_PHOTO)
		{
			//在缩略图样式中填充其余空白区域
			if((itemRange.end+1) % m_iPerLineItemCount!=0)
			{
				//当最后一个显示的Item无法将显示区域填满
				CPoint pt=GetItemPosition(itemRange.end);
				pt.x+=m_iItemWithBorderWidth;
				
				if(!(pt.x>rect.right || pt.x+m_iItemWithBorderWidth<rect.left))
				{
					//当需要填充的区域在需要重绘的区域内时
					pt.y=pt.y-m_iWorkAreaTop;
					Gdiplus::Graphics graph(m_dcWorkAreaDC->GetSafeHdc());
					graph.FillRectangle(m_brBakBrush,pt.x,pt.y,rect.right-pt.x,rect.bottom-pt.y);
				}
			}
		}
	}
}
	

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
void SeeFileViewTable::_PrintItem(int nItem,int leftLine,int rightLine)
{
	if(nItem<m_iShowItemHead || nItem>m_iShowItemEnd)
	{
		//当显示ITEM不在显示区域内则不显示
		return ;
	}

	FileInfoList * file=m_ficFileControl.GetFile(nItem);

	//计算显示的坐标
	CPoint pt=GetItemPosition(nItem);
	pt.x=pt.x-m_iWorkAreaLeft;
	pt.y=pt.y-m_iWorkAreaTop;

	if(m_uiViewStyle == STYLE_SMALL_PHOTO)
	{
		if(!(pt.x>rightLine || pt.x+m_iItemWithBorderWidth<leftLine))
		{
			_PrintItemSmallPhoto(pt,file);
		}
	}
	else if(m_uiViewStyle == STYLE_REPORT)
	{
		_PrintItemReport(pt,file,leftLine,rightLine);
	}
}
	

//=====================================================================
// 函 数 名：_PrintItemSmallPhoto
// 功能描述：Item图象具体绘制函数
// 输入参数：CPoint pt:显示ITEM的坐标
//			 FileInfoList * fileInfo:ITEM指向的文件
// 输出参数：void
// 创建日期：08.10.11
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
void SeeFileViewTable::_PrintItemSmallPhoto(CPoint pt,FileInfoList * fileInfo)
{
	USES_CONVERSION;
	Gdiplus::Graphics graph(m_dcWorkAreaDC->GetSafeHdc());

	//绘制边缘的背景色
	graph.FillRectangle(
		m_brBakBrush
		,pt.x
		,pt.y
		,m_iItemWithBorderWidth,SMALL_PHOTO_ITEM_BORDER
		);
	graph.FillRectangle(
		m_brBakBrush
		,pt.x
		,pt.y+SMALL_PHOTO_ITEM_BORDER
		,SMALL_PHOTO_ITEM_BORDER
		,m_iItemWithBorderHeight-SMALL_PHOTO_ITEM_BORDER
		);
	graph.FillRectangle(
		m_brBakBrush
		,pt.x+m_iItemWithBorderWidth-SMALL_PHOTO_ITEM_BORDER
		,pt.y+SMALL_PHOTO_ITEM_BORDER
		,SMALL_PHOTO_ITEM_BORDER
		,m_iItemWithBorderHeight-SMALL_PHOTO_ITEM_BORDER
		);
	graph.FillRectangle(
		m_brBakBrush
		,pt.x+SMALL_PHOTO_ITEM_BORDER
		,pt.y+m_iItemWithBorderHeight-SMALL_PHOTO_ITEM_BORDER
		,m_iItemWithBorderWidth-(2*SMALL_PHOTO_ITEM_BORDER)
		,SMALL_PHOTO_ITEM_BORDER
		);

	CPoint printPt(pt.x+SMALL_PHOTO_ITEM_BORDER,pt.y+SMALL_PHOTO_ITEM_BORDER);

	Gdiplus::SolidBrush * brush;
	if(fileInfo->GetState(LVIS_SELECTED))
	{
		if(m_bListGetFouc)
		{
			brush=m_brSelectedBrush;
		}
		else
		{
			brush=m_brSelectedUnfoucBrush;
		}
	}
	else
	{
		//未选择
		brush=m_brUnselectedBrush;
	}
	//绘制背景
	graph.FillRectangle(brush,printPt.x,printPt.y,m_iItemWidth,m_iItemHeight);

	//绘制图象部分
	_PrintSmallPhoto(&graph,printPt,fileInfo);

	//绘制自定义信息部分

	//绘制文字
	CString name=fileInfo->GetFileName().c_str();
	WCHAR * wchar=A2W(name);
	RectF txtRectF(
		printPt.x
		,printPt.y+m_iItemHeight-PHOTO_SMALL_WORD_HEIGHT+5
		,m_iItemWidth
		,PHOTO_SMALL_WORD_HEIGHT-5);

	graph.DrawString(
		wchar
		,wcslen(wchar)
		,m_fntFontBlod
		,txtRectF
		,m_sfStringFormatCenter
		,m_brFontBrush);

	//绘制ITEM边框
	graph.DrawRectangle(m_penItemBorder,printPt.x,printPt.y,m_iItemWidth-1,m_iItemHeight-1);
}
	

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
void SeeFileViewTable::_PrintItemReport(CPoint pt,FileInfoList * fileInfo,int leftLine,int rightLine)
{
	USES_CONVERSION; 
	Gdiplus::Graphics graph(m_dcWorkAreaDC->GetSafeHdc());

	//获取整行背景色刷
	CPoint printPt(pt.x,pt.y);

	Gdiplus::SolidBrush * brush;
	if(fileInfo->GetState(LVIS_SELECTED))
	{
		if(m_bListGetFouc)
		{
			brush=m_brSelectedBrush;
		}
		else
		{
			brush=m_brSelectedUnfoucBrush;
		}
	}
	else
	{
		//未选择
		brush=m_brUnselectedBrush;
	}

	//逐列绘制
	VectorColumnInfo::iterator iter=m_vciColumnsInfo.begin();
	for(int i=0;i<m_iTotalColumnCount;i++)
	{
		int left=iter->startPosition-m_iWorkAreaLeft;
		int right=iter->endPosition-m_iWorkAreaLeft;
		if(!(left>rightLine || right<leftLine))
		{
			//绘制背景色
			printPt.x=left;
			graph.FillRectangle(brush,printPt.x,printPt.y,iter->width,REPORT_ITEM_HEIGHT);
	
			//当绘制区域在显示区域内时
			if(i==0)
			{
				//当为首列时需要进行图标绘制
				//创建首列绘制的临时绘图区域,因为可能需要绘制的区域比图标小，所以经过一个临时DC的裁剪可以使得图标在范围小时不会完全绘制
				CDC dc;
				dc.CreateCompatibleDC(NULL);
				CBitmap bmp;
				bmp.CreateCompatibleBitmap(m_dcWorkAreaDC,20,REPORT_ITEM_HEIGHT);
				dc.SelectObject(bmp);
				dc.FillSolidRect(0,0,iter->width,REPORT_ITEM_HEIGHT,RGB(255,255,255));
				//使用系统默认图标绘制文件类型图标
				SHFILEINFO shfi;
				HIMAGELIST hi=(HIMAGELIST)SHGetFileInfo(NULL,0,&shfi,sizeof(shfi),SHGFI_SYSICONINDEX|SHGFI_SMALLICON);		//图标大小16*16
				CImageList * iconList=CImageList::FromHandle(hi);

				POINT p;
				p.x=0;
				p.y=2;
				iconList->Draw(&dc,fileInfo->m_iNIcon,p,ILD_TRANSPARENT);

				m_dcWorkAreaDC->BitBlt(printPt.x,printPt.y,iter->width>20?20:iter->width,REPORT_ITEM_HEIGHT,&dc,0,0,SRCCOPY);

				dc.DeleteDC();
				bmp.DeleteObject();

				if(iter->width>20)
				{
					//当首列宽度大于图标显示所占宽度时需要显示文字
					//绘制文字
					CString str=fileInfo->GetFileBaseInfo(iter->infoType.code).c_str();
					WCHAR * wchar=A2W(str);
					RectF txtRectF(
						printPt.x+20
						,printPt.y+5
						,iter->width-20
						,REPORT_ITEM_HEIGHT-5);

					graph.DrawString(
						wchar
						,wcslen(wchar)
						,m_fntFontNormal
						,txtRectF
						,m_sfStringFormatCenter
						,m_brFontBrush);
				}
			}
			else
			{
				//其他列，只输出文字
				//绘制文字
				CString str=fileInfo->GetFileBaseInfo(iter->infoType.code).c_str();
				WCHAR * wchar=A2W(str);
				RectF txtRectF(
					printPt.x
					,printPt.y+5
					,iter->width
					,REPORT_ITEM_HEIGHT-5);

				graph.DrawString(
					wchar
					,wcslen(wchar)
					,m_fntFontNormal
					,txtRectF
					,m_sfStringFormatCenter
					,m_brFontBrush);
			}
		}

		iter++;
	}

	if(m_iWorkAreaTotalWidth<rightLine)
	{
		//当最后输出的最右边界在显示区域内，将未显示部分填充为背景色
		graph.FillRectangle(m_brBakBrush,m_iWorkAreaTotalWidth-m_iWorkAreaLeft,printPt.y,m_iWorkAreaWidth-m_iWorkAreaTotalWidth,REPORT_ITEM_HEIGHT);			//以显示宽度为ITEM背景宽度
	}
	
	if (fileInfo->GetState(LVIS_FOCUSED)) 
	{
		//如果文件为焦点状态，绘制选中状态线框
		graph.DrawRectangle(
			m_penFoucItem
			,0
			,printPt.y
			,m_iWorkAreaWidth-1
			,REPORT_ITEM_HEIGHT-1
			);
	}

	//绘制ITEM边框
	//graph.DrawRectangle(m_penItemBorder,0,printPt.y,m_iWorkAreaTotalWidth-1,m_iItemHeight-1);
}
	

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
void SeeFileViewTable::_PrintSmallPhoto(Gdiplus::Graphics * graph,CPoint pt,FileInfoList * fileInfo)
{
	int pWidth=0;
	int pHeight=0;
	//临时存储的Image指针
	Gdiplus::Image * tmpImg;
	bool defaultIcon=false;
	if(fileInfo->m_bSmallPhotoEnable)
	{
		tmpImg=fileInfo->GetSmallPhotoImage();
		pWidth=fileInfo->m_iRealPhotoWidth;
		pHeight=fileInfo->m_iRealPhotoHeight;
	}
	else
	{
		if(fileInfo->CheckFileType(FILE_FLODER))
		{
			tmpImg=m_imgDefaultFloder;
			pWidth=tmpImg->GetWidth();
			pHeight=tmpImg->GetHeight();
		}
		else if(fileInfo->CheckFileType(FILE_DISK))
		{
			tmpImg=m_imgDefaultDisk;
			pWidth=tmpImg->GetWidth();
			pHeight=tmpImg->GetHeight();
		}
		else
		{
			//使用系统默认图标显示
			SHFILEINFO shfi;
			HIMAGELIST hi=(HIMAGELIST)SHGetFileInfo(NULL,0,&shfi,sizeof(shfi),SHGFI_SYSICONINDEX|SHGFI_LARGEICON);
			m_cilIconList=CImageList::FromHandle(hi);
			defaultIcon=true;
			if(fileInfo->m_iNIcon==-1)
			{
				fileInfo->GetFileBaseInfo();
			}
			pWidth=32;
			pHeight=32;
		}
	}

	//开始计算坐标
	double scaleW=pWidth/(double)(m_ficFileControl.m_iSmallPhotoMaxWidth);
	double scaleH=pHeight/(double)(m_ficFileControl.m_iSmallPhotoMaxHeight);
	double scale=scaleW>scaleH?scaleW:scaleH;
	if(scale>1)
	{
		pWidth=(LONG)(pWidth/scale);
		pHeight=(LONG)(pHeight/scale);
	}

	//计算图片坐标
	int photoX=pt.x
		+PHOTO_BORDER_WIDTH
		+((m_ficFileControl.m_iSmallPhotoMaxWidth-pWidth-PHOTO_SHADOW_WIDTH)/2);
	int photoY=pt.y
		+PHOTO_BORDER_WIDTH
		+PHOTO_SMALL_TARGET_HEIGHT
		+((m_ficFileControl.m_iSmallPhotoMaxHeight-pHeight-PHOTO_SHADOW_WIDTH)/2);

	//绘制图象
	if(defaultIcon)
	{
		POINT p;
		p.x=photoX;
		p.y=photoY;
		m_cilIconList->Draw(m_dcWorkAreaDC,fileInfo->m_iNIcon,p,ILD_TRANSPARENT);
	}
	else
	{
		graph->DrawImage(tmpImg,photoX,photoY,pWidth,pHeight);
		
		if(!fileInfo->CheckFileType(FILE_FLODER) && !fileInfo->CheckFileType(FILE_DISK))
		{
			//绘制阴影
			graph->DrawImage(m_imgShadowRight,photoX+pWidth,photoY+PHOTO_SHADOW_MOVE,PHOTO_SHADOW_WIDTH,pHeight-PHOTO_SHADOW_MOVE);		//绘制右侧阴影
			graph->DrawImage(m_imgShadowDown,photoX+PHOTO_SHADOW_MOVE,photoY+pHeight,pWidth-PHOTO_SHADOW_MOVE,PHOTO_SHADOW_WIDTH);		//绘制阴影下部
			graph->DrawImage(m_imgShadowRightDown,photoX+pWidth,photoY+pHeight,PHOTO_SHADOW_WIDTH,PHOTO_SHADOW_WIDTH);	//绘制阴影角落部分
		}
	}

	//当非文件夹时绘制文件类型图标
	if(!fileInfo->CheckFileType(FILE_FLODER))
	{
		//使用系统默认图标绘制文件类型图标
		SHFILEINFO shfi;
		HIMAGELIST hi=(HIMAGELIST)SHGetFileInfo(NULL,0,&shfi,sizeof(shfi),SHGFI_SYSICONINDEX|SHGFI_SMALLICON);		//图标大小16*16
		CImageList * iconList=CImageList::FromHandle(hi);
		defaultIcon=true;

		POINT p;
		p.x=pt.x
			+m_iItemWidth
			-18;
		p.y=pt.y
			+2;
		iconList->Draw(m_dcWorkAreaDC,fileInfo->m_iNIcon,p,ILD_TRANSPARENT);

		//根据文件评级绘制评级标志
		p.x=pt.x
			+m_iItemWidth*3/5;
		m_cilLevelsIcon->Draw(m_dcWorkAreaDC,fileInfo->m_iPhotoLevel,p,ILD_TRANSPARENT);
	}
	
	if(fileInfo->GetState(LVIS_FOCUSED))
	{
		//如果文件为被选中状态，绘制选中状态线框
		graph->DrawRectangle(
			m_penFoucItem
			,pt.x
			,pt.y
			,m_iItemWidth-1
			,(2*PHOTO_BORDER_WIDTH)
				+PHOTO_SMALL_TARGET_HEIGHT
				+m_ficFileControl.m_iSmallPhotoMaxHeight
				+PHOTO_SHADOW_WIDTH
			);
	}
	else if (fileInfo->GetState(LVIS_SELECTED)) 
	{
		//如果文件为被选中状态，绘制选中状态线框
		graph->DrawRectangle(
			m_penSelectedItem
			,pt.x
			,pt.y
			,m_iItemWidth-1
			,(2*PHOTO_BORDER_WIDTH)
				+PHOTO_SMALL_TARGET_HEIGHT
				+m_ficFileControl.m_iSmallPhotoMaxHeight
				+PHOTO_SHADOW_WIDTH
			);
	}
}
	

//=====================================================================
// 函 数 名：_DeleteDC
// 功能描述：删除CDC对象
// 输入参数：CDC * dc
// 输出参数：void
// 创建日期：08.08.29
// 修改日期：08.08.29
// 作 者：alzq
// 附加说明：
//=====================================================================
void SeeFileViewTable::_DeleteDC(CDC * dc)
{
	if(dc)
	{
		dc->DeleteDC();
		delete dc;
	}
}
	

//=====================================================================
// 函 数 名：_DeleteBmp
// 功能描述：删除CBitmap对象
// 输入参数：CBitmap * bmp
// 输出参数：void
// 创建日期：08.08.29
// 修改日期：08.08.29
// 作 者：alzq
// 附加说明：
//=====================================================================
void SeeFileViewTable::_DeleteBmp(CBitmap * bmp)
{
	if(bmp)
	{
		bmp->DeleteObject();
		delete bmp;
	}
}
	

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
void SeeFileViewTable::_CreateDC(CDC * dc,CBitmap * bmp,CDC * pDC,int width,int height)
{
	dc=new CDC();
	dc->CreateCompatibleDC(NULL);
	bmp=new CBitmap();
	bmp->CreateCompatibleBitmap(pDC,width,height);
	dc->SelectObject(bmp);
}
	

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
void SeeFileViewTable::_BuildDC()
{
	_DeleteBmp(m_cbBakMemeryBmp);							//背景绘制图象的存储对象
	_DeleteBmp(m_cbWorkAreaBmp);							//绘制显示区域的图象存储对象
	_DeleteBmp(m_cbHeaderBmp);								//表头的图象存储对象
	_DeleteBmp(m_cbScrollVBmp);								//纵向滚动条的图象存储对象
	_DeleteBmp(m_cbScrollHBmp);								//横向滚动条的图象存储对象
	_DeleteDC(m_dcMemeryDC);								//背景绘制的内存DC
	_DeleteDC(m_dcWorkAreaDC);								//显示区域部分的内存DC
	_DeleteDC(m_dcHeaderDC);								//表头部分的内存DC
	_DeleteDC(m_dcScrollVDC);								//纵向滚动条部分的内存DC
	_DeleteDC(m_dcScrollHDC);								//横向滚动条部分的内存DC

	//相关坐标的计算在ONSIZE里进行
	m_dcBakDC=GetDC();

	//建立总的显示内存DC
	m_dcMemeryDC=new CDC();
	m_dcMemeryDC->CreateCompatibleDC(NULL);
	m_cbBakMemeryBmp=new CBitmap();
	m_cbBakMemeryBmp->CreateCompatibleBitmap(m_dcBakDC,m_iCurrentViewWidth,m_iCurrentViewHeight);
	m_dcMemeryDC->SelectObject(m_cbBakMemeryBmp);
	//_CreateDC(m_dcMemeryDC,m_cbBakMemeryBmp,m_dcBakDC,m_iCurrentViewWidth,m_iCurrentViewHeight);

	//建立显示区域的内存DC
	m_dcWorkAreaDC=new CDC();
	m_dcWorkAreaDC->CreateCompatibleDC(NULL);
	m_cbWorkAreaBmp=new CBitmap();
	m_cbWorkAreaBmp->CreateCompatibleBitmap(m_dcBakDC,m_iWorkAreaWidth,m_iWorkAreaHeight);
	m_dcWorkAreaDC->SelectObject(m_cbWorkAreaBmp);
	//_CreateDC(m_dcWorkAreaDC,m_cbWorkAreaBmp,m_dcBakDC,m_iWorkAreaWidth,m_iWorkAreaHeight);

	//建立表头的内存DC，当非详细信息样式时，设为NULL
	if(m_uiViewStyle & STYLE_REPORT)
	{
		m_dcHeaderDC=new CDC();
		m_dcHeaderDC->CreateCompatibleDC(NULL);
		m_cbHeaderBmp=new CBitmap();
		m_cbHeaderBmp->CreateCompatibleBitmap(m_dcBakDC,m_iWorkAreaTotalWidth,REPORT_HEAD_HEIGHT);
		m_dcHeaderDC->SelectObject(m_cbHeaderBmp);
		//_CreateDC(m_dcHeaderDC,m_cbHeaderBmp,m_dcBakDC,m_iWorkAreaTotalWidth,REPORT_HEAD_HEIGHT);

		//绘制表头
		DrawReportHeader(-1);
	}
	else
	{
		m_dcHeaderDC=NULL;
		m_cbHeaderBmp=NULL;
	}

	//建立纵向滚动条的内存DC，当不存在纵向滚动条时，设为NULL
	if(m_uiScrollBarType & SCROLL_BAR_V)
	{
		m_dcScrollVDC=new CDC();
		m_dcScrollVDC->CreateCompatibleDC(NULL);
		m_cbScrollVBmp=new CBitmap();
		m_cbScrollVBmp->CreateCompatibleBitmap(m_dcBakDC,SCROLL_BAR_WIDTH_HEIGHT,(m_uiScrollBarType & SCROLL_BAR_H?m_iCurrentViewHeight-SCROLL_BAR_WIDTH_HEIGHT:m_iCurrentViewHeight));
		m_dcScrollVDC->SelectObject(m_cbScrollVBmp);
		//_CreateDC(m_dcScrollVDC,m_cbScrollVBmp,m_dcBakDC,SCROLL_BAR_WIDTH_HEIGHT
		//	,(m_uiScrollBarType & SCROLL_BAR_H?m_iCurrentViewHeight-SCROLL_BAR_WIDTH_HEIGHT:m_iCurrentViewHeight));
	}
	else
	{
		m_dcScrollVDC=NULL;
		m_cbScrollVBmp=NULL;
	}

	//建立横向滚动条的内存DC，当不存在横向滚动条时，设为NULL
	if(m_uiScrollBarType & SCROLL_BAR_H)
	{
		m_dcScrollHDC=new CDC();
		m_dcScrollHDC->CreateCompatibleDC(NULL);
		m_cbScrollHBmp=new CBitmap();
		m_cbScrollHBmp->CreateCompatibleBitmap(m_dcBakDC,m_iCurrentViewWidth,SCROLL_BAR_WIDTH_HEIGHT);
		m_dcScrollHDC->SelectObject(m_cbScrollHBmp);
		//_CreateDC(m_dcScrollHDC,m_cbScrollHBmp,m_dcBakDC,m_iCurrentViewWidth,SCROLL_BAR_WIDTH_HEIGHT);
	}
	else
	{
		m_dcScrollHDC=NULL;
		m_cbScrollHBmp=NULL;
	}

	//初始化拖拉条图象以及按钮（滑动块不初始化）
	InitScrollBar();

	//建立好DC以后将不绘制的部分填充背景色
	FillOutofWorkArea();
}
	

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
void SeeFileViewTable::_MoveWorkArea(int dx,int dy)
{
	if(dx!=0)
	{
		m_iWorkAreaLeft+=dx;
		m_iWorkAreaRight+=dx;
	}
	if(dy!=0)
	{
		m_iWorkAreaTop+=dy;
		m_iWorkAreaBottom+=dy;
	}

	_CheckWorkArea();
}
	

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
void SeeFileViewTable::_DragSelect(CPoint startPt,CPoint oldPt,CPoint nowPt)
{
}
	

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
void SeeFileViewTable::InitLoadImageThread (bool killThread)
{
	if(killThread)
	{
		//如果要终止线程
		PublicFunc::DeleteThread(m_hLoadImage);
	}

	//创建加载图象的线程
	m_hLoadImage=CreateThread(NULL,0,LoadImageFunc,this,0,NULL);
}
	

//=====================================================================
// 函 数 名：InitLoadBaseInfoThread
// 功能描述：初始化加载文件基本信息的线程
// 输入参数：bool killThread:在线程运行状态时是否删除线程
// 输出参数：void
// 创建日期：08.09.15
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
void SeeFileViewTable::InitLoadBaseInfoThread (bool killThread)
{
	if(killThread)
	{
		//如果要终止线程
		PublicFunc::DeleteThread(m_hLoadBaseInfo);
	}

	//创建加载图象的线程
	m_hLoadBaseInfo=CreateThread(NULL,0,LoadBaseInfoFunc,this,0,NULL);
}
		

//=====================================================================
// 函 数 名：LoadImageFunc
// 功能描述：载入Image对象的线程主体
// 输入参数：LPVOID lpParameter带入SeeFileViewTable指针
// 输出参数：DWORD WINAPI
// 创建日期：08.09.15
// 修改日期：
// 作 者：alzq
// 附加说明：
//=====================================================================
DWORD WINAPI  LoadImageFunc(LPVOID lpParameter)
{
	SeeFileViewTable * table = (SeeFileViewTable *)lpParameter;
	FileInfoControl *control = &(table->m_ficFileControl);
	FileInfoList * tmpIter;
	int tmpPos;
	
	bool loadSuc=false;			//是否完全加载完毕，用于最后检查判断

	//载入粗略缩略图
	while(!loadSuc)
	{
		//初始化载入图象位置
		if(control->m_bLoadImagePosEnable)
		{
			tmpIter=control->m_filLoadImageBegin;
			tmpPos=control->m_iLoadImagePos;
			control->m_bLoadImagePosEnable=false;
		}
		else
		{
			tmpIter=control->GetHeader()->m_filNextItem;
			tmpPos=0;
		}

		while(tmpIter!=control->GetEnder())
		{
			if(control->m_bLoadImagePosEnable)
			{
				//当载入文件位置有效时，重新设置载入文件的位置
				tmpIter=control->m_filLoadImageBegin;
				tmpPos=control->m_iLoadImagePos;
				control->m_bLoadImagePosEnable=false;
			}

			if(tmpIter->CheckFileType(FILE_PHOTO) && tmpIter->m_bNeedGetSmallPhoto)
			{
				//设置为不需要获取缩略图
				tmpIter->m_bNeedGetSmallPhoto=false;
				//当需要获取缩略图时，此时必然需要重新创建DC
				if( tmpIter->CreateSmallImage(control->m_iSmallPhotoMaxWidth,control->m_iSmallPhotoMaxHeight))
				{
					//当缩略图获取成功时，设置缩略图有效
					tmpIter->m_bSmallPhotoEnable=true;
					//设置重绘参数
					tmpIter->m_iiItemInfo.reDrawEnable=true;
					//重绘第tmpPos个图标
					table->PostMessageA(MES_ALZQ_REFRESH_ITEM,tmpPos);
					//table->ReFresh(false,false);
				}
			}			

			tmpIter=tmpIter->m_filNextItem;
			tmpPos++;
		}

		//假设为全部加载完毕
		loadSuc=true;

		//开始循环判断所有文件信息，判断是否加载完毕
		tmpIter=control->GetHeader()->m_filNextItem;
		while(tmpIter!=control->GetEnder())
		{
			if(tmpIter->CheckFileType(FILE_PHOTO) && tmpIter->m_bNeedGetSmallPhoto)
			{
				//当还需要加载IMAGE时，设置为未加载完毕并跳出检查循环
				loadSuc=false;
				break;
			}

			tmpIter=tmpIter->m_filNextItem;
		}
	}

	//loadSuc=false;

	////载入详细缩略图
	//while(!loadSuc)
	//{
	//	//初始化载入图象位置
	//	if(control->m_bLoadImagePosEnable)
	//	{
	//		tmpIter=control->m_filLoadImageBegin;
	//		tmpPos=control->m_iLoadImagePos;
	//		control->m_bLoadImagePosEnable=false;
	//	}
	//	else
	//	{
	//		tmpIter=control->GetHeader()->m_filNextItem;
	//		tmpPos=0;
	//	}

	//	while(tmpIter!=control->GetEnder())
	//	{
	//		if(control->m_bLoadImagePosEnable)
	//		{
	//			//当载入文件位置有效时，重新设置载入文件的位置
	//			tmpIter=control->m_filLoadImageBegin;
	//			tmpPos=control->m_iLoadImagePos;
	//			control->m_bLoadImagePosEnable=false;
	//		}

	//		if(tmpIter->GetIsPhoto() && tmpIter->m_bNeedGetSmallPhoto)
	//		{
	//			//设置为不需要获取缩略图
	//			tmpIter->m_bNeedGetSmallPhoto=false;
	//			//当需要获取缩略图时，此时必然需要重新创建DC
	//			if( tmpIter->CreateSmallImage(control->m_iSmallPhotoMaxWidth,control->m_iSmallPhotoMaxHeight))
	//			{
	//				//当缩略图获取成功时，设置缩略图有效
	//				tmpIter->m_bSmallPhotoEnable=true;
	//				//设置重绘参数
	//				tmpIter->m_iiItemInfo.reDrawEnable=true;
	//				//重绘第tmpPos个图标
	//				table->RedrawItems(tmpPos,tmpPos);
	//			}
	//		}			

	//		tmpIter=tmpIter->m_filNextItem;
	//		tmpPos++;
	//	}

	//	//假设为全部加载完毕
	//	loadSuc=true;

	//	//开始循环判断所有文件信息，判断是否加载完毕
	//	tmpIter=control->GetHeader()->m_filNextItem;
	//	while(tmpIter!=control->GetEnder())
	//	{
	//		if(tmpIter->GetIsPhoto() && tmpIter->m_bNeedGetSmallPhoto)
	//		{
	//			//当还需要加载IMAGE时，设置为未加载完毕并跳出检查循环
	//			loadSuc=false;
	//			break;
	//		}

	//		tmpIter=tmpIter->m_filNextItem;
	//	}
	//}
	return 0;
}
	

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
DWORD WINAPI LoadBaseInfoFunc (LPVOID lpParameter)
{
	SeeFileViewTable * table = (SeeFileViewTable *)lpParameter;
	FileInfoControl *control = &(table->m_ficFileControl);
	FileInfoList * tmpIter;
	int tmpPos;
	
	bool loadSuc=false;			//是否完全加载完毕，用于最后检查判断

	while(!loadSuc)
	{
		//初始化载入图象位置
		if(control->m_bLoadBaseInfoEnable)
		{
			tmpIter=control->m_filLoadImageBegin;
			tmpPos=control->m_iLoadImagePos;
			control->m_bLoadBaseInfoEnable=false;
		}
		else
		{
			tmpIter=control->GetHeader()->m_filNextItem;
			tmpPos=0;
		}

		while(tmpIter!=control->GetEnder())
		{
			if(control->m_bLoadBaseInfoEnable)
			{
				//当载入文件位置有效时，重新设置载入文件的位置
				tmpIter=control->m_filLoadImageBegin;
				tmpPos=control->m_iLoadImagePos;
				control->m_bLoadBaseInfoEnable=false;
			}

			if(tmpIter->m_bNeedGetBaseInfo)
			{
				//当需要获取文件基本信息时
				if( tmpIter->GetFileBaseInfo())
				{
					//获取成功设置为基本信息不需要获取
					tmpIter->m_bNeedGetBaseInfo=false;
					//重绘第tmpPos个图标
					table->PostMessageA(MES_ALZQ_REFRESH_ITEM,tmpPos);
					//table->ReFresh(false,false);
				}
			}			

			tmpIter=tmpIter->m_filNextItem;
			tmpPos++;
		}

		//假设为全部加载完毕
		loadSuc=true;

		//开始循环判断所有文件信息，判断是否加载完毕
		tmpIter=control->GetHeader()->m_filNextItem;
		while(tmpIter!=control->GetEnder())
		{
			if(tmpIter->m_bNeedGetBaseInfo)
			{
				//当还需要加载文件基本信息时，设置为未加载完毕并跳出检查循环
				loadSuc=false;
				break;
			}

			tmpIter=tmpIter->m_filNextItem;
		}
	}

	return 0;
}
	

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
void SeeFileViewTable::OpenFloder(CString floderPath)
{
	m_sOpenFloderPath=floderPath;;
	this->GetParent()->PostMessageA(MES_ALZQ_OPEN_FLODER);
}
	

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
int SeeFileViewTable::GetItemCodeByMousePt(CPoint pt)
{
	CRect  rect;  
	CPoint  point;  
	GetWindowRect(rect);  
	point.x=pt.x-rect.left;  
	point.y=pt.y-rect.top;			//设置鼠标相对LIST的位置
	    
	return GetItemCodeByWindowPt(point);
}
	

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
int SeeFileViewTable::GetItemCodeByWindowPt(CPoint pt)
{
	if(m_uiViewStyle == STYLE_SMALL_PHOTO)
	{
		//当为缩略图时
		if(pt.x<0 || pt.y<0 || pt.x>m_iWorkAreaWidth || pt.y>m_iWorkAreaHeight)
		{
			//不在显示范围内
			return -1;
		}

		//判断位置是否处于非ITEM区域内
		pt.y+=m_iWorkAreaTop;
		if(pt.x>m_iItemWithBorderWidth * m_iPerLineItemCount)
		{
			return -1;
		}
		if(pt.y>m_iItemWithBorderHeight * m_iTotalLineCount)
		{
			return -1;
		}

		//计算坐标在第几个ITEM的范围内
		int nItem=((pt.y/m_iItemWithBorderHeight)*m_iPerLineItemCount)+(pt.x/m_iItemWithBorderWidth);
		if(nItem>=m_ficFileControl.m_iTotalCount)
		{
			return -1;
		}

		//判断是否位置处于ITEM间的空白区域
		int x=pt.x % m_iItemWithBorderWidth;
		int y=pt.y % m_iItemWithBorderHeight;
		if(x<=SMALL_PHOTO_ITEM_BORDER || m_iItemWithBorderWidth-x<=SMALL_PHOTO_ITEM_BORDER)
		{
			return -1;
		}
		if(y<=SMALL_PHOTO_ITEM_BORDER || m_iItemWithBorderHeight-y<=SMALL_PHOTO_ITEM_BORDER)
		{
			return -1;
		}

		return nItem;
	}
	else if(m_uiViewStyle == STYLE_REPORT)
	{
		//当为详细信息样式时
		if(pt.x<0 || pt.y<REPORT_HEAD_HEIGHT || pt.x>m_iWorkAreaWidth || pt.y>m_iWorkAreaHeight+REPORT_HEAD_HEIGHT)
		{
			//不在显示范围内
			return -1;
		}

		pt.y+=m_iWorkAreaTop-REPORT_HEAD_HEIGHT;
		if(pt.y>m_iItemWithBorderHeight * m_iTotalLineCount)
		{
			return -1;
		}

		//计算坐标在第几个ITEM的范围内
		int nItem=pt.y/m_iItemWithBorderHeight;
		if(nItem>=m_ficFileControl.m_iTotalCount)
		{
			return -1;
		}

		return nItem;
	}

	return -1;
}
	

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
void SeeFileViewTable::RefreshPreview(void)
{
	if(!m_wndPreviewBar)
	{
		return ;
	}

	int nItem=m_ficFileControl.GetFirstSelectedPhotoCode();

	if(nItem>=0)
	{
		FileInfoList * file=m_ficFileControl.GetFile(nItem);
		m_wndPreviewBar->m_csFileFullPath=file->GetFileFullPath().c_str();
	}
	else
	{
		m_wndPreviewBar->m_csFileFullPath="";
	}

	m_wndPreviewBar->RedrawWindow();
}
	

void SeeFileViewTable::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_mpiMousePositionInfo.positionType==POSITION_ITEM)
	{
		int nItem=GetItemCodeByWindowPt(point);
		
		if(nItem>=0)
		{
			//获取双击位置的文件信息
			FileInfoList * fileInfo=m_ficFileControl.GetFile(nItem);

			if(fileInfo->CheckFileType(FILE_FLODER) | fileInfo->CheckFileType(FILE_DISK))
			{
				//当双击文件夹时，打开文件夹
				OpenFloder((fileInfo->GetFileFullPath()+"\\").c_str());
			}
			else
			{
				if(fileInfo->CheckFileType(FILE_PHOTO))
				{
					//当为图象文件时
					GetParent()->PostMessageA(MES_ALZQ_VIEW_PHOTO,nItem);
				}
			}
		}
	}
	else
	{
		SeeFileViewTable::OnLButtonDown(nFlags,point);
	}

	CWnd::OnLButtonDblClk(nFlags, point);
}
	

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
void SeeFileViewTable::OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	if(m_ficFileControl.m_iOrderType)
	{
		//当m_ficFileControl.m_iOrderType==1时，原本列表是降序排序方式
		m_ficFileControl.SortAsc(pNMLV->iSubItem);
	}
	else
	{
		m_ficFileControl.SortDes(pNMLV->iSubItem);
	}

	Invalidate();

	*pResult = 0;
}

void SeeFileViewTable::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	 // 定义一个缓冲区来存放读取的文件名信息
	char szFileName[MAX_PATH + 1] = {0};

	// 通过设置iFiles参数为0xFFFFFFFF,可以取得当前拖动的文件数量，
	// 当设置为0xFFFFFFFF,函数间忽略后面连个参数。
	UINT nFiles = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
		
	//根据鼠标位置获取位置文件信息
	CPoint  point;  
	GetCursorPos(&point);

	int nItem=GetItemCodeByMousePt(point);

	string filePath="";					//需要拖动到的文件路径
	int floderCode=0;					//所拖动到的文件夹编号-默认为0

	if(nItem<0)
	{
		//当编号无效时，鼠标不在任何ITEM上
		if(m_ficFileControl.m_iFilePathCount>1)
		{
			//当已经选取的文件夹大于1个时无法剪切到当前文件夹
			return ;
		}
		else
		{
			MapStringInt::iterator iter=m_ficFileControl.m_msiFilePathMap.begin();
			filePath=iter->first;

			floderCode=m_ficFileControl.m_msiFilePathMap[filePath];
		}
	}
	else
	{
		FileInfoList * fileInfo=m_ficFileControl.GetFile(nItem);
		
		if(!fileInfo->CheckFileType(FILE_FLODER))
		{
			//当文件不是文件夹时不支持拖拽到文件上
			return ;
		}
		else
		{
			filePath=fileInfo->GetFileFullPath()+"\\";

			//判断目录是否在已选取文件夹集合中，在的话则需要将文件添加进文件链表
			floderCode=m_ficFileControl.m_msiFilePathMap[filePath];
		}
	}

	// 通过循环依次取得拖动文件的File Name信息，并把它添加到ListBox中
	for(UINT i=0; i<nFiles; i++)
	{
		DragQueryFile(hDropInfo, i, szFileName, MAX_PATH);
		//获取文件名
		string fullPath=string(szFileName);
		
		int mark_1=(int)fullPath.find_last_of("\\/");
		string fileName=string(fullPath,mark_1+1);
		string oldFilePath=string(fullPath,0,mark_1+1);

		if(oldFilePath.compare(filePath)!=0)
		{
			//当旧文件路径与需要复制到的新文件路径不同时才进行复制并添加进链表
			string newFileFullPath=filePath+fileName;

			int res=IDYES;
			if(access(newFileFullPath.c_str(),0)==0)
			{
				//当复制到的文件存在时询问，并且同意询问时
				res=AfxMessageBox(("文件："+newFileFullPath+" 已经存在，请问是否覆盖？").c_str(),MB_ICONQUESTION|MB_YESNO);
			}

			if(res==IDYES)
			{
				//对文件进行操作，将文件从原文件夹剪切到当前文件夹
				MoveFileEx(fullPath.c_str(),newFileFullPath.c_str(),MOVEFILE_COPY_ALLOWED|MOVEFILE_REPLACE_EXISTING);
	
				if(floderCode)
				{
					//将文件添加进链表
					FileInfoList * file=m_ficFileControl.AddFile(newFileFullPath,floderCode);
					file->GetFileBaseInfo();
				}
			}
		}
	}

	// 结束此次拖拽操作，并释放分配的资源
	DragFinish(hDropInfo);

	//设置鼠标操作相关信息
	m_maiMouseActionInfo.dragStartPt=point;
	m_maiMouseActionInfo.mouseCondition &= ~MOUSE_LBT_DOWN;			//在操作状态中使用或操作

	//设置鼠标操作为空，并释放鼠标获取，此时不论鼠标右键是否进行操作都重置鼠标操作信息
	m_maiMouseActionInfo.mouseCondition=MOUSE_NONE;
	//释放鼠标动作焦点
	ReleaseCapture();

	m_maiMouseActionInfo.mousePositionInfo.positionType=m_mpiMousePositionInfo.positionType;
	m_maiMouseActionInfo.mousePositionInfo.value=m_mpiMousePositionInfo.value;

	if(floderCode)
	{
		//刷新显示
		RedrawWorkArea(true);
		Refresh();
	}

	//CListCtrl::OnDropFiles(hDropInfo);
}

void SeeFileViewTable::OnLvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码 
	int nItem=pNMLV->iItem;

	if(nItem<0)
	{
		//当未拖拽任何ITEM时
		return;
	}


	*pResult   =   0; 
}


//=====================================================================
// 函 数 名：showEdit
// 功能描述：显示重命名编辑框
// 输入参数：用户选中的文件索引值
// 输出参数：无
// 创建日期：2008.10.7
// 修改日期: alzq 08.10.09
// 作 者：   江显华
// 附加说明： 
//=====================================================================
void SeeFileViewTable::showEdit(int nItem)
{
	if(!m_bCreateEdit)
	{
 		m_wndEdit.Create(WS_CHILD|WS_CLIPSIBLINGS|WS_EX_TOOLWINDOW|WS_BORDER,CRect(0,0,150,20),this,IDC_RENAME_EDIT);
		m_bCreateEdit=true;
	}
	CRect rcItem;
	FileInfoList * fileQ=this->m_ficFileControl.GetFile(nItem);
	//显示旧文件名
	m_wndEdit.SetWindowTextA(fileQ->GetFileName().c_str());//.append(".").append(fileQ->GetFileExtName()).c_str());
	//获得Item所在位置的矩形
	//this->GetItemRect(nItem,&rcItem,LVIR_LABEL);
	//设置重命名的对象编号
	m_nSelect=nItem;
	//把Edit移动到当前矩形的位置
	m_wndEdit.MoveWindow(rcItem);
	//显示Edit
	m_wndEdit.ShowWindow(SW_SHOW);
	//设置Edit的数据容量大小
	m_wndEdit.SetSel(0,100);
	//设置焦点在Edit上
	m_wndEdit.SetFocus();

	m_bDealMouseAction=false;
}

//=====================================================================
// 函 数 名：DisposeEdit
// 功能描述：当失去焦点之后根据用户输入的新文件名判断是否更改文件名，是则更改
// 输入参数：无
// 输出参数：无
// 创建日期：2008.9.2
// 修改日期: 2008.9.4--alzq 08.10.09
// 作 者：   江显华
// 附加说明： 
//=====================================================================
void SeeFileViewTable::DisposeEdit(void)
{
	CString newname="";
	//获得用户输入的新名字字符串
	m_wndEdit.GetWindowTextA(newname);
	//获得选中的文件信息列表
	FileInfoList* renameFileInfo=this->m_ficFileControl.GetFile(m_nSelect);
	//获得选中文件的扩展名
	string oldExtname=renameFileInfo->GetFileExtName();
	//获得旧扩展名的长度
	int oldExtlength=(int)oldExtname.length();
	//判断用户输入的新文件名是否非空
	if(!newname.IsEmpty())
	{
		//输入扩展名,且扩展名不等于原先的扩展名
		if(newname.Find('.')!=-1&&(newname.Right(oldExtlength).Compare(oldExtname.c_str())!=0))
		{
			//弹出对话框提示是否去定改文件扩展名
			int nRet=AfxMessageBox("改变文件的扩展名可能导致文件不可用，你确定要改变它吗？",MB_YESNO|MB_ICONQUESTION);	
			//确定则更改
			if (nRet==IDYES)
			{
				//重命名文件
				renameFileInfo->ISetFileNameAndExtName(newname.GetString());
			}
			else
			{
				//否则返回，没有改变，仍然是原名
				//隐藏编辑框
				m_wndEdit.ShowWindow(SW_HIDE);
			}
		}
		//输入扩展名，且扩展名和原先的扩展名相等
		else if(newname.Find('.')!=-1&&(newname.Right(oldExtlength).Compare(oldExtname.c_str())==0))
		{
			//重命名文件
			renameFileInfo->ISetFileName(newname.GetString());
		}
		else
		{
			//执行到这里表示：没有输入扩展名
			//重命名文件
			string newnameNoExt=newname;
			renameFileInfo->ISetFileName(newnameNoExt.append(".").append(renameFileInfo->GetFileExtName()));
		}
		//重新绘制item
		ReDrawItem(m_nSelect);

	}
	//隐藏编辑框
	m_wndEdit.ShowWindow(SW_HIDE);
	//被重命名的文件状态设置为选中
	renameFileInfo->SetState(LVIS_SELECTED,true,LVIS_SELECTED); 

	m_bDealMouseAction=true;
}
	

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
void SeeFileViewTable::SetListStyle(UINT style)
{
	//设置样式
	m_uiViewStyle=style;

	if(style == STYLE_SMALL_PHOTO)
	{
		//以原缩略图大小设置缩略图大小，同时计算缩略图相关ITEM范围
		SetSmallPhotoSize(200,160);		//设置默认的缩略图范围
	}
	else if(style == STYLE_REPORT)
	{
		SetReportItemSize();
	}

	//全部刷新并且显示
	_ResizeWorkAreaWithoutGroup(true);
	//填补空白区域
	FillOutofWorkArea();
	RedrawWorkArea(true);
	Refresh();
}
	

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
void SeeFileViewTable::SetSmallPhotoSize()
{
	//计算当前每个ITEM的宽度与高度
	m_iItemWidth=m_ficFileControl.m_iSmallPhotoMaxWidth
		+(2*PHOTO_BORDER_WIDTH)
		+PHOTO_SHADOW_WIDTH;
	m_iItemHeight=m_ficFileControl.m_iSmallPhotoMaxHeight
		+(2*PHOTO_BORDER_WIDTH)
		+PHOTO_SHADOW_WIDTH
		+PHOTO_SMALL_TARGET_HEIGHT
		+PHOTO_SMALL_WORD_HEIGHT;
	m_iItemWithBorderWidth=m_iItemWidth+(2*SMALL_PHOTO_ITEM_BORDER);						//每个ITEM的宽度
	m_iItemWithBorderHeight=m_iItemHeight+(2*SMALL_PHOTO_ITEM_BORDER);						//每个ITEM的高度

	//重新计算坐标并且显示
	_ResizeWorkAreaWithoutGroup(true);
	//填补空白区域
	FillOutofWorkArea();
	RedrawWorkArea(true);
	Refresh();
}
	

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
void SeeFileViewTable::SetSmallPhotoSize(int width,int height)
{
	m_ficFileControl.SetSmallPhotoMaxSize(width,height);

	//计算
	SetSmallPhotoSize();
}
	

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
void SeeFileViewTable::SetReportItemSize()
{
	//计算当前每个ITEM的宽度与高度
	m_iItemHeight=REPORT_ITEM_HEIGHT;
	m_iItemWithBorderHeight=REPORT_ITEM_HEIGHT;											//每个ITEM的高度
}
	

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
void SeeFileViewTable::SetWorkAreaToItem(int nItem)
{
	if(m_ficFileControl.m_bOrderByGroup)
	{
		//当进行了分组排列时，计算方式不同
	}
	else
	{
		SetWorkAreaToItemWithoutGroup(nItem);
	}
}
	

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
void SeeFileViewTable::SetWorkAreaToItemWithoutGroup(int nItem)
{
	//当显示为缩略图样式时
	if(nItem<0 || !m_uiScrollBarType)
	{
		//当无选择项，或无拖动条（即只有一页），显示首页
		m_iWorkAreaTop=0;
		m_iWorkAreaBottom=m_iWorkAreaHeight;
	}
	else
	{
		int line=(nItem/m_iPerLineItemCount);				//ITEM所在行，行数从0开始计算
		int behindLine=m_iTotalLineCount-line;				//包含ITEM所在行到最后一行存在几行

		if(behindLine<m_iPerPageLineCount)
		{
			//当包括该行在内，到最后还不到一页时，显示最后一页
			if(m_iWorkAreaTotalHeight>m_iWorkAreaHeight)
			{
				m_iWorkAreaTop=m_iWorkAreaTotalHeight-m_iWorkAreaHeight;
				m_iWorkAreaBottom=m_iWorkAreaTotalHeight;
			}
			else
			{
				m_iWorkAreaTop=0;
				m_iWorkAreaBottom=m_iWorkAreaHeight;
			}
		}
		else
		{
			//显示以所在行为第一行的页面
			m_iWorkAreaTop=m_iItemWithBorderHeight * line;
			m_iWorkAreaBottom=m_iWorkAreaTop + m_iWorkAreaHeight;
		}
	}

	ItemRange rang=SetShowItemRange(m_iWorkAreaTop,m_iWorkAreaBottom);
	m_iShowItemHead=rang.head;
	m_iShowItemEnd=rang.end;
}
	

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
ItemRange SeeFileViewTable::SetShowItemRange(int top,int bottom)
{
	ItemRange rang;
	rang.head=((top/m_iItemWithBorderHeight)*m_iPerLineItemCount);								//显示区域的第一个ITEM
	if(m_ficFileControl.m_iTotalCount<=0)
	{
		rang.head=-1;
	}

	rang.end=((bottom/m_iItemWithBorderHeight)*m_iPerLineItemCount)+m_iPerLineItemCount-1;		//显示区域的最后一个ITEM
	if(rang.end>=m_ficFileControl.m_iTotalCount)
	{
		rang.end=m_ficFileControl.m_iTotalCount-1;
	}

	return rang;
}
	

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
CPoint SeeFileViewTable::GetItemPosition(int nItem)
{
	CPoint pt;
	pt.x=(nItem % m_iPerLineItemCount) * m_iItemWithBorderWidth;
	pt.y=(nItem/m_iPerLineItemCount)*m_iItemWithBorderHeight;
	return pt;
}
	

//=====================================================================
// 函 数 名：OpenFloderList
// 功能描述：打开文件夹
// 输入参数：CString floderPath
// 输出参数：
// 创建日期：2008.10.12
// 修改日期:  
// 作 者：   alzq
// 附加说明：
//=====================================================================
void SeeFileViewTable::OpenFloderList(CString filePath)
{
	//关闭两个载入线程
	PublicFunc::DeleteThread(m_hLoadImage);
	PublicFunc::DeleteThread(m_hLoadBaseInfo);
	
	//使用文件信息控制类，打开文件夹
	string filePathString=filePath.GetBuffer(0);
	if(filePathString.find_last_of("\\")!=filePathString.length()-1)
	{
		filePathString+="\\";
	}
	m_ficFileControl.OpenFloder(filePathString,0);

	_ResizeWorkAreaWithoutGroup(true);
	//填补空白区域
	FillOutofWorkArea();
	RedrawWorkArea(true);
	Refresh();

	//设置总的ITEM数量
	//m_sfvtFileViewTable.SetItemCount(m_sfvtFileViewTable.m_ficFileControl.m_iTotalCount);
	/*m_sfvtFileViewTable.SetItemCountEx(m_sfvtFileViewTable.m_ficFileControl.m_iTotalCount,LVSICF_NOINVALIDATEALL);
	if(m_sfvtFileViewTable.m_ficFileControl.m_iTotalCount==0)
	{
		 m_sfvtFileViewTable.Invalidate();
	}*/

	//开启Image载入线程
	InitLoadImageThread(true);
	//开启文件基本信息载入线程
	InitLoadBaseInfoThread(true);
}
	

//=====================================================================
// 函 数 名：Refresh
// 功能描述：刷新屏幕
// 输入参数：
// 输出参数：
// 创建日期：2008.10.17
// 修改日期：
// 作 者：   alzq
// 附加说明：
//=====================================================================
void SeeFileViewTable::Refresh()
{
	if(!m_dcBakDC)
	{
		return ;
	}

	int dy=0;
	if(m_uiViewStyle & STYLE_REPORT)
	{
		//当为详细信息模式时，高度需要+20
		dy=REPORT_HEAD_HEIGHT;
		//复制表头到显示DC上
		m_dcMemeryDC->BitBlt(0,0,m_iWorkAreaWidth,REPORT_HEAD_HEIGHT,m_dcHeaderDC,m_iWorkAreaLeft,0,SRCCOPY);
	}

	//复制显示区域
	m_dcMemeryDC->BitBlt(0,dy,m_iWorkAreaWidth,m_iWorkAreaHeight,m_dcWorkAreaDC,0,0,SRCCOPY);

	if(m_maiMouseActionInfo.mouseCondition & MOUSE_DRAG_SELECT)
	{
		//当鼠标进行拖拉选择的时候
		CPoint pt=m_maiMouseActionInfo.mousePositionInfo.pt;

		//计算长宽
		int x=abs(m_mpiMousePositionInfo.pt.x-pt.x);
		int y=abs(m_mpiMousePositionInfo.pt.y-pt.y);

		//计算左上角坐标
		pt.x=pt.x<m_mpiMousePositionInfo.pt.x?pt.x:m_mpiMousePositionInfo.pt.x;
		pt.y=pt.y<m_mpiMousePositionInfo.pt.y?pt.y:m_mpiMousePositionInfo.pt.y;

		//将绝对坐标计算成当前显示的窗口坐标
		pt.x-=m_iWorkAreaLeft;
		pt.y-=m_iWorkAreaTop;

		if(pt.x>m_iWorkAreaWidth)
		{
			//当左上角坐标在右边界外时不显示
		}
		else if(pt.y>m_iWorkAreaHeight)
		{
		}
		else
		{
			if(pt.x<0)
			{
				x+=pt.x;
				pt.x=0;
			}
			if(pt.y<0)
			{
				y+=pt.y;
				pt.y=0;
			}

			if(pt.x+x>m_iWorkAreaWidth)
			{
				x=m_iWorkAreaWidth-pt.x;
			}
			if(pt.y+y>m_iWorkAreaHeight)
			{
				y=m_iWorkAreaHeight-pt.y;
			}
	
			Gdiplus::Graphics graph(m_dcMemeryDC->GetSafeHdc());
			graph.FillRectangle(m_brSelectBrush,pt.x,pt.y+dy,x,y);
		}
	}

	if(m_uiScrollBarType & SCROLL_BAR_H)
	{
		//当存在横向拖拉条时
		m_dcMemeryDC->BitBlt(0,m_iCurrentViewHeight-SCROLL_BAR_WIDTH_HEIGHT,m_sbsHScrollBarState.scrollTotalLength,SCROLL_BAR_WIDTH_HEIGHT,m_dcScrollHDC,0,0,SRCCOPY);
	}

	if(m_uiScrollBarType & SCROLL_BAR_V)
	{
		//当存在纵向拖拉条时
		m_dcMemeryDC->BitBlt(m_iCurrentViewWidth-SCROLL_BAR_WIDTH_HEIGHT,0,SCROLL_BAR_WIDTH_HEIGHT,m_sbsVScrollBarState.scrollTotalLength,m_dcScrollVDC,0,0,SRCCOPY);
	}

	//绘制滑动条划块
	DrawScrollBarMidBT();

	GetDC()->BitBlt(0,0,m_iCurrentViewWidth,m_iCurrentViewHeight,m_dcMemeryDC,0,0,SRCCOPY);
}
	

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
void SeeFileViewTable::Refresh(CRect rect)
{
	int dy=0;
	if(m_uiViewStyle & STYLE_REPORT)
	{
		//当为详细信息模式时，高度需要+20
		dy=REPORT_HEAD_HEIGHT;
		if(rect.top<dy && rect.right<=m_iWorkAreaWidth)
		{
			//当区域内包含表头范围时
			//复制表头到显示DC上
			m_dcMemeryDC->BitBlt(
				rect.left
				,rect.top
				,rect.Width()
				,rect.bottom>dy?dy-rect.top:rect.Height()
				,m_dcHeaderDC
				,m_iWorkAreaLeft+rect.left
				,rect.top
				,SRCCOPY);
		}
	}

	//复制显示区域
	if(rect.bottom>dy && rect.left<m_iWorkAreaWidth)
	{
		m_dcMemeryDC->BitBlt(
			rect.left
			,rect.top>=dy?rect.top:dy
			,rect.right<=m_iWorkAreaWidth?rect.Width():m_iWorkAreaWidth-rect.left
			,rect.top>=dy?rect.Height():rect.bottom-dy
			,m_dcWorkAreaDC
			,rect.left
			,rect.top>=dy?rect.top-dy:0
			,SRCCOPY);
	}

	if(m_uiScrollBarType & SCROLL_BAR_H)
	{
		//当存在横向拖拉条时
		if(m_iCurrentViewHeight-rect.bottom<SCROLL_BAR_WIDTH_HEIGHT)
		{
			m_dcMemeryDC->BitBlt(
				rect.left
				,m_iCurrentViewHeight-rect.top<=SCROLL_BAR_WIDTH_HEIGHT?rect.top:m_iCurrentViewHeight-SCROLL_BAR_WIDTH_HEIGHT
				,rect.Width()
				,m_iCurrentViewHeight-rect.top<=SCROLL_BAR_WIDTH_HEIGHT?rect.Height():SCROLL_BAR_WIDTH_HEIGHT-(m_iCurrentViewHeight-rect.bottom)
				,m_dcScrollHDC
				,rect.left
				,m_iCurrentViewHeight-rect.top<=SCROLL_BAR_WIDTH_HEIGHT?SCROLL_BAR_WIDTH_HEIGHT-(m_iCurrentViewHeight-rect.top):0
				,SRCCOPY);
		}
	}

	if(m_uiScrollBarType & SCROLL_BAR_V)
	{
		//当存在纵向拖拉条时
		if(m_iCurrentViewWidth-rect.right<SCROLL_BAR_WIDTH_HEIGHT && rect.top<m_iWorkAreaHeight+dy)
		{
			m_dcMemeryDC->BitBlt(
				m_iCurrentViewWidth-rect.left<=SCROLL_BAR_WIDTH_HEIGHT?rect.left:m_iCurrentViewWidth-SCROLL_BAR_WIDTH_HEIGHT
				,rect.top
				,m_iCurrentViewWidth-rect.left<=SCROLL_BAR_WIDTH_HEIGHT?rect.Width():SCROLL_BAR_WIDTH_HEIGHT-(m_iCurrentViewWidth-rect.right)
				,rect.bottom>=m_iWorkAreaHeight+dy?m_iWorkAreaHeight-rect.top:rect.Height()
				,m_dcScrollVDC
				,m_iCurrentViewWidth-rect.left<=SCROLL_BAR_WIDTH_HEIGHT?SCROLL_BAR_WIDTH_HEIGHT-(m_iCurrentViewWidth-rect.left):0
				,rect.top
				,SRCCOPY);
		}
	}

	//绘制滑动条划块
	DrawScrollBarMidBT();

	GetDC()->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),m_dcMemeryDC,rect.left,rect.top,SRCCOPY);
}
	

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
void SeeFileViewTable::RefreshWorkArea()
{
	int dy=0;
	if(m_uiViewStyle & STYLE_REPORT)
	{
		//当为详细信息模式时，高度需要+20
		dy=REPORT_HEAD_HEIGHT;
	}
	GetDC()->BitBlt(0,dy,m_iWorkAreaWidth,m_iWorkAreaHeight,m_dcWorkAreaDC,0,0,SRCCOPY);
}
	

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
void SeeFileViewTable::ReDrawItem(int nItem)
{
	_ReDrawItems(nItem,nItem);
	CRect rect=GetItemRect(nItem);
	Refresh(rect);
}
	

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
void SeeFileViewTable::ReDrawItems(int head,int end)
{
	_ReDrawItems(head,end);
	RefreshWorkArea();
}
	

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
void SeeFileViewTable::DrawScrollBarBT()
{
	if(m_uiScrollBarType & SCROLL_BAR_V)
	{
		//当拖动条为垂直方向时
		CPoint pt(0,0);
		//绘制向上按钮
		m_cilScrollBarUp->Draw(m_dcScrollVDC,m_sbsVScrollBarState.upButState,pt,ILD_NORMAL);
		//绘制向下按钮
		pt.y=m_sbsVScrollBarState.scrollDragLength+SCROLL_BAR_WIDTH_HEIGHT;
		m_cilScrollBarDown->Draw(m_dcScrollVDC,m_sbsVScrollBarState.downButState,pt,ILD_NORMAL);
	}
	if(m_uiScrollBarType & SCROLL_BAR_H)
	{
		//当拖动条为水平方向时 
		CPoint pt(0,0);
		//绘制向上按钮
		m_cilScrollBarLeft->Draw(m_dcScrollHDC,m_sbsHScrollBarState.upButState,pt,ILD_NORMAL);
		//绘制向下按钮
		pt.x=m_sbsHScrollBarState.scrollDragLength+SCROLL_BAR_WIDTH_HEIGHT;
		m_cilScrollBarRight->Draw(m_dcScrollHDC,m_sbsHScrollBarState.downButState,pt,ILD_NORMAL);
	}
}
	

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
void SeeFileViewTable::InitScrollBar()
{
	if(!m_dcBakDC)
	{
		return ;
	}

	if(m_uiScrollBarType & SCROLL_BAR_V)
	{
		//当拖动条为垂直方向时
		Gdiplus::Graphics graph(m_dcScrollVDC->GetSafeHdc());
		CPoint pt(0,0);
		//绘制拖拉条背景色
		graph.FillRectangle(m_brScrollBarBakBrush,pt.x,pt.y,SCROLL_BAR_WIDTH_HEIGHT,m_sbsVScrollBarState.scrollTotalLength);
		//绘制向上按钮
		m_cilScrollBarUp->Draw(m_dcScrollVDC,m_sbsVScrollBarState.upButState,pt,ILD_NORMAL);
		//绘制向下按钮
		pt.y=m_sbsVScrollBarState.scrollDragLength+SCROLL_BAR_WIDTH_HEIGHT;
		m_cilScrollBarDown->Draw(m_dcScrollVDC,m_sbsVScrollBarState.downButState,pt,ILD_NORMAL);

		//滑动块位置
		//pt.y=m_sbsVScrollBarState.scrollMidPosition;
		//绘制中间划块的背景色
		//graph.FillRectangle(m_brScrollBarMidBakBrush,pt.x,pt.y,SCROLL_BAR_WIDTH_HEIGHT,m_sbsVScrollBarState.scrollMidButLength);
		//绘制中间划块的边缘色
		//graph.DrawRectangle(m_penScrollBarMidBakBorder,pt.x+1,pt.y+1,SCROLL_BAR_WIDTH_HEIGHT-2,m_sbsVScrollBarState.scrollMidButLength-1);
	}
	if(m_uiScrollBarType & SCROLL_BAR_H)
	{
		//当拖动条为水平方向时 
		Gdiplus::Graphics graph(m_dcScrollHDC->GetSafeHdc());
		CPoint pt(0,0);
		//绘制拖拉条背景色
		graph.FillRectangle(m_brScrollBarBakBrush,pt.x,pt.y,m_sbsHScrollBarState.scrollTotalLength,SCROLL_BAR_WIDTH_HEIGHT);
		//绘制向上按钮
		m_cilScrollBarLeft->Draw(m_dcScrollHDC,m_sbsHScrollBarState.upButState,pt,ILD_NORMAL);
		//绘制向下按钮
		pt.x=m_sbsHScrollBarState.scrollDragLength+SCROLL_BAR_WIDTH_HEIGHT;
		m_cilScrollBarRight->Draw(m_dcScrollHDC,m_sbsHScrollBarState.downButState,pt,ILD_NORMAL);

		//计算滑动块位置
		//pt.x=m_sbsHScrollBarState.scrollMidPosition;
		//绘制中间划块的背景色
		//graph.FillRectangle(m_brScrollBarMidBakBrush,pt.x,pt.y,m_sbsHScrollBarState.scrollMidButLength,SCROLL_BAR_WIDTH_HEIGHT);
		//绘制中间划块的边缘色
		//graph.DrawRectangle(m_penScrollBarMidBakBorder,pt.x+1,pt.y+1,m_sbsHScrollBarState.scrollMidButLength-1,SCROLL_BAR_WIDTH_HEIGHT-2);
	}
}
	

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
void SeeFileViewTable::DrawScrollBarMidBT()
{
	if(m_uiScrollBarType & SCROLL_BAR_V)
	{
		//计算滑动块的位置
		int x=(m_iWorkAreaTop*(m_sbsVScrollBarState.scrollDragLength-m_sbsVScrollBarState.scrollMidButLength));
		m_sbsVScrollBarState.scrollMidPosition=SCROLL_BAR_WIDTH_HEIGHT+(x/(m_iWorkAreaTotalHeight-m_iWorkAreaHeight));
		//绘制中间划块的背景色
		m_dcMemeryDC->FillSolidRect(
			m_iCurrentViewWidth-SCROLL_BAR_WIDTH_HEIGHT
			,m_sbsVScrollBarState.scrollMidPosition
			,SCROLL_BAR_WIDTH_HEIGHT
			,m_sbsVScrollBarState.scrollMidButLength
			,m_sbcsScrollBarColorSet.normalBak);
		//绘制中间划块的边缘色
		//graph.DrawRectangle(m_penScrollBarMidBakBorder,pt.x+1,pt.y+1,SCROLL_BAR_WIDTH_HEIGHT-2,m_sbsVScrollBarState.scrollMidButLength-1);
	}
	if(m_uiScrollBarType & SCROLL_BAR_H)
	{
		//计算滑动块的位置
		int x=(m_iWorkAreaLeft*(m_sbsHScrollBarState.scrollDragLength-m_sbsHScrollBarState.scrollMidButLength));
		m_sbsHScrollBarState.scrollMidPosition=SCROLL_BAR_WIDTH_HEIGHT+(x/(m_iWorkAreaTotalWidth-m_iWorkAreaWidth));
		//绘制中间划块的背景色
		m_dcMemeryDC->FillSolidRect(
			m_sbsHScrollBarState.scrollMidPosition
			,m_iCurrentViewHeight-SCROLL_BAR_WIDTH_HEIGHT
			,m_sbsHScrollBarState.scrollMidButLength
			,SCROLL_BAR_WIDTH_HEIGHT
			,m_sbcsScrollBarColorSet.normalBak);
		//graph.FillRectangle(m_brScrollBarMidBakBrush,pt.x,pt.y,m_sbsHScrollBarState.scrollMidButLength,SCROLL_BAR_WIDTH_HEIGHT);
		//绘制中间划块的边缘色
		//graph.DrawRectangle(m_penScrollBarMidBakBorder,pt.x+1,pt.y+1,m_sbsHScrollBarState.scrollMidButLength-1,SCROLL_BAR_WIDTH_HEIGHT-2);
	}
}
	

//=====================================================================
// 函 数 名：DrawReportHeader
// 功能描述：绘制详细信息样式的表头,指定列或全部
// 输入参数：int nLine：-1为全部，否则为指定列
// 输出参数：
// 创建日期：2008.10.15
// 修改日期:  
// 作 者：   alzq
// 附加说明：
//=====================================================================
void SeeFileViewTable::DrawReportHeader(int nLine)
{
	if(!m_dcBakDC)
	{
		return ;
	}

	Gdiplus::Graphics graph(m_dcHeaderDC->GetSafeHdc());

	VectorColumnInfo::iterator iter=m_vciColumnsInfo.begin();
	for(int i=0;i<m_iTotalColumnCount;i++)
	{
		int left=iter->startPosition;
		int right=iter->endPosition;
		if(nLine==-1 || nLine==i)
		{
			//当在区域内显示表头时
			SolidBrush * brush;
			//获取背景刷
			switch(iter->headState)
			{
				case STATE_MOUSE_OVER:
					brush=m_brScrollBarMidMouseOnBrush; break;
				case STATE_MOUSE_LDOWN:
					brush=m_brScrollBarMidDragBrush; break;
				default:
					brush=m_brScrollBarMidBakBrush;
			};
			//绘制表头背景色
			graph.FillRectangle(brush,left,0,iter->width,REPORT_HEAD_HEIGHT);
			
			Pen * pen;
			//获取边缘刷
			switch(iter->headState)
			{
				case STATE_MOUSE_OVER:
					pen=m_penScrollBarMidMouseOnBorder; break;
				case STATE_MOUSE_LDOWN:
					pen=m_penScrollBarMidDragBorder; break;
				default:
					pen=m_penScrollBarMidBakBorder;
			};
			graph.DrawRectangle(pen,left+1,1,iter->width-2,REPORT_HEAD_HEIGHT-2);

			//输出文字
			//当首列宽度大于图标显示所占宽度时需要显示文字
			USES_CONVERSION;
			CString str=iter->columnName;
			WCHAR * wchar=A2W(str);
			RectF txtRectF(
				left
				,3
				,iter->width
				,REPORT_HEAD_HEIGHT-3);

			graph.DrawString(
				wchar
				,wcslen(wchar)
				,m_fntFontBlod
				,txtRectF
				,m_sfStringFormatCenter
				,m_brFontBrush);
		}

		iter++;
	}


	if(m_iWorkAreaTotalWidth<m_iWorkAreaWidth)
	{
		//当最后输出的最右边界在显示区域内，将未显示部分填充为背景色
		graph.FillRectangle(m_brScrollBarMidBakBrush,m_iWorkAreaTotalWidth,0,m_iWorkAreaWidth-m_iWorkAreaTotalWidth,REPORT_ITEM_HEIGHT);			//以显示宽度为ITEM背景宽度
	}
}
	

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
void SeeFileViewTable::ReSetScrollBarInfo()
{
	if(m_uiScrollBarType & SCROLL_BAR_H)
	{
		//将按钮状态初始化
		m_sbsHScrollBarState.upButState=STATE_NONE;
		m_sbsHScrollBarState.midButState=STATE_NONE;
		m_sbsHScrollBarState.downButState=STATE_NONE;
		m_sbsHScrollBarState.scrollTotalLength=m_iCurrentViewWidth;
		m_sbsHScrollBarState.scrollDragLength=m_sbsHScrollBarState.scrollTotalLength-(2*SCROLL_BAR_WIDTH_HEIGHT);
		m_sbsHScrollBarState.scrollMidButLength=(m_sbsHScrollBarState.scrollDragLength*m_iWorkAreaWidth)/m_iWorkAreaTotalWidth;
		if(m_sbsHScrollBarState.scrollMidButLength<6){m_sbsHScrollBarState.scrollMidButLength=6;}

		//根据鼠标位置判断是否在某一BUT上，同时根据正在进行的操作判断BUT是否需要处于按下状态
	}
	if(m_uiScrollBarType & SCROLL_BAR_V)
	{
		//将按钮状态初始化
		m_sbsVScrollBarState.upButState=STATE_NONE;
		m_sbsVScrollBarState.midButState=STATE_NONE;
		m_sbsVScrollBarState.downButState=STATE_NONE;
		m_sbsVScrollBarState.scrollTotalLength=m_iCurrentViewHeight;
		if(m_uiScrollBarType & SCROLL_BAR_H)
		{
			m_sbsVScrollBarState.scrollTotalLength=m_sbsVScrollBarState.scrollTotalLength-SCROLL_BAR_WIDTH_HEIGHT;
		}
		m_sbsVScrollBarState.scrollDragLength=m_sbsVScrollBarState.scrollTotalLength-(2*SCROLL_BAR_WIDTH_HEIGHT);
		m_sbsVScrollBarState.scrollMidButLength=(m_sbsVScrollBarState.scrollDragLength*m_iWorkAreaHeight)/m_iWorkAreaTotalHeight;
		if(m_sbsVScrollBarState.scrollMidButLength<6){m_sbsVScrollBarState.scrollMidButLength=6;}

		//根据鼠标位置判断是否在某一BUT上，同时根据正在进行的操作判断BUT是否需要处于按下状态
	}

	InitScrollBar();
}
	

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
void SeeFileViewTable::InitColumnInfo()
{
	m_vciColumnsInfo.clear();
	m_iTotalColumnCount=0;
	int totalWidth=0;

	for(int i=0;i<7;i++)
	{
		ColumnInfo columnInfo;
		columnInfo.columnName.Format("%s%i","line_",i);
		columnInfo.infoType.code=i;
		columnInfo.orderedColumn=ORDER_NONE;
		columnInfo.width=200;
		columnInfo.startPosition=totalWidth;
		columnInfo.endPosition=columnInfo.startPosition+columnInfo.width;
		columnInfo.headState=SCROLL_BAR_NONE;
		columnInfo.contentState=HEAD_ALI_CENTER;

		totalWidth+=columnInfo.width;

		m_vciColumnsInfo.push_back(columnInfo);
		m_iTotalColumnCount++;
	}

	m_iWorkAreaTotalWidth=totalWidth;
}
	

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
void SeeFileViewTable::FillOutofWorkArea()
{
	//创建DC后，判断右侧与底部是否可能存在空白，存在则先填补上背景色
	if(m_uiViewStyle == STYLE_SMALL_PHOTO)
	{
		//在缩略图样式中填充其余空白区域
		//计算纵向空白宽度
		int hBorder=m_iWorkAreaWidth -(( m_iPerPageLineCount>1?m_iPerLineItemCount:m_ficFileControl.m_iTotalCount)*m_iItemWithBorderWidth);
		if(hBorder>0)
		{
			Gdiplus::Graphics graph(m_dcWorkAreaDC->GetSafeHdc());
			graph.FillRectangle(m_brBakBrush,m_iWorkAreaWidth-hBorder,0,hBorder,m_iWorkAreaHeight);
		}

		//计算横向空白高度
		if(!(m_uiScrollBarType & SCROLL_BAR_V))
		{
			//只有当不存在竖向拖动条时才存在空白区域
			int vBorder=m_iWorkAreaHeight -(m_iTotalLineCount * m_iItemWithBorderHeight);
			if(vBorder>0)
			{
				Gdiplus::Graphics graph(m_dcWorkAreaDC->GetSafeHdc());
				graph.FillRectangle(m_brBakBrush,0,m_iWorkAreaHeight-vBorder,m_iWorkAreaWidth-hBorder,vBorder);
			}
		}
	}
	else if(m_uiViewStyle == STYLE_REPORT)
	{
		//详细信息样式时，无横向空白需要绘制
		//计算横向空白高度
		if(!(m_uiScrollBarType & SCROLL_BAR_V))
		{
			//只有当不存在竖向拖动条时才存在空白区域
			int vBorder=m_iWorkAreaHeight -(m_iTotalLineCount * m_iItemWithBorderHeight);
			if(vBorder>0)
			{
				Gdiplus::Graphics graph(m_dcWorkAreaDC->GetSafeHdc());
				graph.FillRectangle(m_brBakBrush,0,m_iWorkAreaHeight-vBorder,m_iWorkAreaWidth,vBorder);
			}
		}
	}
}
	

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
void SeeFileViewTable::SetMousePositionInfo(CPoint pt)
{
	m_mpiMousePositionInfo.pt.x=pt.x+m_iWorkAreaLeft;
	m_mpiMousePositionInfo.pt.y=pt.y+m_iWorkAreaTop;
	
	if(m_uiViewStyle & STYLE_REPORT)
	{
		m_mpiMousePositionInfo.pt.y-=REPORT_HEAD_HEIGHT;
	}

	if(m_uiScrollBarType & SCROLL_BAR_V)
	{
		//当存在纵向拖拉条时
		if(m_iCurrentViewWidth-pt.x<=SCROLL_BAR_WIDTH_HEIGHT && pt.y<=m_sbsVScrollBarState.scrollTotalLength)
		{
			//当鼠标位置在拖拉条范围内时，开始根据鼠标位置判断在拖拉条的哪个位置上
			if(pt.y<=SCROLL_BAR_WIDTH_HEIGHT)
			{
				//当鼠标在向上按钮的高度范围内
				m_mpiMousePositionInfo.positionType=POSITION_SCROLL_BAR_V_UP_BT;
				return ;
			}
			else if(pt.y>=m_sbsVScrollBarState.scrollMidPosition && pt.y<=m_sbsVScrollBarState.scrollMidPosition+m_sbsVScrollBarState.scrollMidButLength)
			{
				//当鼠标在滑动块的范围内时
				m_mpiMousePositionInfo.positionType=POSITION_SCROLL_BAR_V_MID_BT;
				m_mpiMousePositionInfo.value=m_iWorkAreaTop;
				return ;
			}
			else if(m_sbsVScrollBarState.scrollTotalLength-pt.y<=SCROLL_BAR_WIDTH_HEIGHT)
			{
				//当鼠标在向下按钮的高度范围内
				m_mpiMousePositionInfo.positionType=POSITION_SCROLL_BAR_V_DOWN_BT;
				return ;
			}
			else
			{
				m_mpiMousePositionInfo.positionType=POSITION_SCROLL_BAR_V_DRAG_SPACE;
				return ;
			}
		}
	}
	if(m_uiScrollBarType & SCROLL_BAR_H)
	{
		//当存在横向拖拉条时
		if(m_iCurrentViewHeight-pt.y<=SCROLL_BAR_WIDTH_HEIGHT)
		{
			//当鼠标位置在拖拉条范围内时，开始根据鼠标位置判断在拖拉条的哪个位置上
			if(pt.x<=SCROLL_BAR_WIDTH_HEIGHT)
			{
				//当鼠标在向上按钮的高度范围内
				m_mpiMousePositionInfo.positionType=POSITION_SCROLL_BAR_H_LEFT_BT;
				return ;
			}
			else if(pt.x>=m_sbsHScrollBarState.scrollMidPosition && pt.x<=m_sbsHScrollBarState.scrollMidPosition+m_sbsHScrollBarState.scrollMidButLength)
			{
				//当鼠标在滑动块的范围内时
				m_mpiMousePositionInfo.positionType=POSITION_SCROLL_BAR_H_MID_BT;
				m_mpiMousePositionInfo.value=m_iWorkAreaLeft;
				return ;
			}
			else if(m_sbsHScrollBarState.scrollTotalLength-pt.x<=SCROLL_BAR_WIDTH_HEIGHT)
			{
				//当鼠标在向下按钮的高度范围内
				m_mpiMousePositionInfo.positionType=POSITION_SCROLL_BAR_H_RIGHT_BT;
				return ;
			}
			else
			{
				m_mpiMousePositionInfo.positionType=POSITION_SCROLL_BAR_H_DRAG_SPACE;
				return ;
			}
		}
	}
	if(m_uiViewStyle & STYLE_REPORT)
	{
		//当列表样式存在详细信息样式时，存在表头
		if(pt.y<REPORT_HEAD_HEIGHT)
		{
			//当鼠标位置在表头范围内时
			VectorColumnInfo::iterator iter=m_vciColumnsInfo.begin();
			for(int i=0;i<m_iTotalColumnCount;i++)
			{
				if(pt.x>iter->startPosition+3 && pt.x<iter->endPosition-3)
				{
					//当鼠标不是位于表头连接处时
					m_mpiMousePositionInfo.positionType=POSITION_HEAD_ITEM;
					m_mpiMousePositionInfo.value=i;
					return ;
				}
				else if(pt.x>=iter->endPosition-3 && pt.x<=iter->endPosition+3)
				{
					//当鼠标位于表头连接处时,有效值为连接处前一个表头的编号
					m_mpiMousePositionInfo.positionType=POSITION_HEAD_MID;
					m_mpiMousePositionInfo.value=i;
					return ;
				}

				iter++;
			}
		}
	}

	//剩余只可能在显示区域内，此时取位置的ITEM编号
	int nItem=GetItemCodeByWindowPt(pt);
	if(nItem<0)
	{
		//当编号小于0，说明鼠标位置不是ITEM
		m_mpiMousePositionInfo.positionType=POSITION_WORKAREA_NONE;
		return ;
	}
	else
	{
		m_mpiMousePositionInfo.positionType=POSITION_ITEM;
		m_mpiMousePositionInfo.value=nItem;
		return ;
	}
}
	

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
void SeeFileViewTable::MoveWorkArea(int dx,int dy)
{
	if(dx!=0)
	{
		m_iWorkAreaLeft+=dx;
		m_iWorkAreaRight+=dx;
	}
	if(dy!=0)
	{
		m_iWorkAreaTop+=dy;
		m_iWorkAreaBottom+=dy;
	}

	_CheckWorkArea();
	RedrawWorkArea(true);
}
	

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
void SeeFileViewTable::SetWorkArea(CPoint pt)
{
	m_iWorkAreaLeft=pt.x;
	m_iWorkAreaTop=pt.y;
	m_iWorkAreaRight=m_iWorkAreaLeft+m_iWorkAreaWidth;
	m_iWorkAreaBottom=m_iWorkAreaTop+m_iWorkAreaHeight;

	_CheckWorkArea();
	RedrawWorkArea(true);
	Refresh();
}
	

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
void SeeFileViewTable::JumpLine(int lineCount)
{
	if(lineCount>0)
	{
		lineCount=lineCount-1;
		lineCount=(lineCount*m_iItemWithBorderHeight)+(m_iItemWithBorderHeight-(m_iWorkAreaTop%m_iItemWithBorderHeight));
		MoveWorkArea(0,lineCount);
	}
	else if(lineCount<0)
	{
		lineCount=lineCount+1;
		lineCount=(lineCount*m_iItemWithBorderHeight)-(m_iWorkAreaTop%m_iItemWithBorderHeight?m_iWorkAreaTop%m_iItemWithBorderHeight:m_iItemWithBorderHeight);
		MoveWorkArea(0,lineCount);
	}
	
	Refresh();
}
	

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
UINT SeeFileViewTable::DealLbtDownMes(UINT positionMes,UINT nFlags,CPoint point)
{
	if(positionMes==POSITION_ITEM)
	{
		//当鼠标点击在ITEM上时
		if(!(nFlags & MK_CONTROL))
		{
			//当没有按下CONTROL键时，将其他ITEM选择状态取消
 			m_ficFileControl.SetAllState(~LVIS_SELECTED,false,LVIS_SELECTED);
		}

		if(!(nFlags & MK_SHIFT))
		{
			//当未按下SHIFT键时,只进行单个文件的选择，并且将选择的文件设置为焦点文件
			int nItem=m_mpiMousePositionInfo.value;
			FileInfoList * file=m_ficFileControl.GetFile(nItem);
			file->SetState(LVIS_SELECTED,true,0);
			m_ficFileControl.SetItemFouc(nItem,file);
		}
		else
		{
			//当按下SHIFT键时，选择焦点文件到该文件的区间内文件，不改变焦点文件位置
			int nItem=m_mpiMousePositionInfo.value;
			m_ficFileControl.SetFoucToItemState(nItem);
		}
	
		RedrawWorkArea(true);
		Refresh();

		RefreshPreview();

		//不返回拖动文件的信息,一旦设置了拖动文件的信息则不再进行OLE操作,以防止重复的OLE操作
	}
	else if(positionMes==POSITION_WORKAREA_NONE)
	{
		//当鼠标点击在显示区域内的空白部分
		if(!(nFlags & (MK_CONTROL|MK_SHIFT)))
		{
			//当没有按下CONTROL键时，将其他ITEM选择状态取消
 			m_ficFileControl.SetAllState(~LVIS_SELECTED,false,LVIS_SELECTED);

			RedrawWorkArea(true);
			Refresh();
		}

		RefreshPreview();

		return MOUSE_DRAG_SELECT;
	}
	else if(positionMes==POSITION_SCROLL_BAR_V_UP_BT)
	{
		//当鼠标点击在纵向拖拉条的向上按钮
		JumpLine(-1);		//向上跳一行

		return MOUSE_SCROLL_V_UP;
	}
	else if(positionMes==POSITION_SCROLL_BAR_V_DOWN_BT)
	{
		//当鼠标点击在纵向拖拉条的向下按钮
		JumpLine(1);		//向上跳一行

		return MOUSE_SCROLL_V_DOWN;
	}
	else if(positionMes==POSITION_SCROLL_BAR_V_DRAG_SPACE)
	{
		//当鼠标点击在纵向拖拉条的拖拉空白区域
		if(point.y<m_sbsVScrollBarState.scrollMidPosition)
		{
			//当鼠标点击位置在划块以上区间时
			JumpLine(-(m_iPerPageLineCount>1?m_iPerPageLineCount-1:1));		//向上跳(一页的行数-1)，当每页一行时，向上跳转1行
		}
		else
		{
			//当鼠标点击位置在划块以下区间时
			JumpLine(m_iPerPageLineCount>1?m_iPerPageLineCount-1:1);		//向下跳(一页的行数-1)，当每页一行时，向上跳转1行
		}

		return MOUSE_SCROLL_V_AREA;
	}
	else if(positionMes==POSITION_SCROLL_BAR_V_MID_BT)
	{
		//当鼠标点击在纵向拖拉条的滑动块

		return MOUSE_DRAG_SCROLL_V;
	}
	else if(positionMes==POSITION_SCROLL_BAR_H_LEFT_BT)
	{
		//当鼠标点击在横向拖拉条的向左按钮
		MoveWorkArea(-5,0);			//向左移动
		Refresh();

		return MOUSE_SCROLL_H_LEFT;
	}
	else if(positionMes==POSITION_SCROLL_BAR_H_RIGHT_BT)
	{
		//当鼠标点击在横向拖拉条的向右按钮
		MoveWorkArea(5,0);			//向右移动
		Refresh();

		return MOUSE_SCROLL_H_RIGHT;
	}
	else if(positionMes==POSITION_SCROLL_BAR_H_DRAG_SPACE)
	{
		//当鼠标点击在横向拖拉条的向右按钮
		if(point.x<m_sbsHScrollBarState.scrollMidPosition)
		{
			//当鼠标点击位置在划块左边时,左移
			MoveWorkArea(-m_iWorkAreaWidth,0);
		}
		else
		{
			//当鼠标点击位置不在划块左边时,右移
			MoveWorkArea(m_iWorkAreaWidth,0);
		}

		Refresh();

		return MOUSE_SCROLL_H_AREA;
	}
	else if(positionMes==POSITION_SCROLL_BAR_H_MID_BT)
	{
		//当鼠标点击在横向拖拉条的滑动块

		return MOUSE_DRAG_SCROLL_H;
	}

	return MOUSE_NONE;
}
	

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
void SeeFileViewTable::DragSelectedFiles()
{
	int iLen=0;
	CStringList stringList;
	iLen=m_ficFileControl.GetSelectedFileList(&stringList,FILE_ALL);		//获取选择的文件绝对路径集合，并且得到长度

	if(iLen>0)
	{
		//当选择的文件大于0个时才进行拖拽操作
		DROPEFFECT DropResult=DROPEFFECT_NONE;						//操作结果
		iLen=iLen+sizeof(DROPFILES) +1;  
		
		//分配全局内存,准备拖放之用,注意此块内存将由接收拖放的窗口负责销毁   
		HGLOBAL hMemData = GlobalAlloc(GPTR,iLen);         
		ASSERT(hMemData != NULL);   

		//锁定分配的内存,并设置相关成员   
		LPDROPFILES lpDropFiles = (LPDROPFILES)GlobalLock(hMemData);   
		ASSERT(lpDropFiles != NULL);   
		lpDropFiles->pFiles = sizeof(DROPFILES);
		#ifdef _UNICODE   
			lpDropFiles->fWide = TRUE;   
		#else   
			lpDropFiles->fWide = FALSE;   
		#endif           

		//把选中的所有文件名依次复制到DROPFILES结构体后面(全局内存中)   
		POSITION pItemPos = stringList.GetHeadPosition();
		char * pszStart = (char*)((LPBYTE)lpDropFiles + sizeof(DROPFILES));   
		while(pItemPos != NULL)     
		{   
			lstrcpy(pszStart, (LPCTSTR)stringList.GetNext(pItemPos));   
			pszStart = strchr(pszStart,'\0')   +   1;   //下次的起始位置是上一次结尾+1   
		} 

		m_DragSource.Empty(); 
		m_DragSource.CacheGlobalData(CF_HDROP,hMemData); 

		DropResult=m_DragSource.DoDragDrop(DROPEFFECT_COPY|DROPEFFECT_MOVE); 
		//对处理结果进行判断，剪切情况下需要将文件从链表中删除
		switch(DropResult)   
		{   
			case DROPEFFECT_MOVE:
			case DROPEFFECT_COPY:   
				break;   
			default:   
				break;   
		}

		if(m_ficFileControl.CheckSelectedFile())
		{
			//刷新显示
			Invalidate();
		}

		//接锁内存
		GlobalUnlock(hMemData);
	}
}
	

//=====================================================================
// 函 数 名：RedrawWorkArea
// 功能描述：重新绘制显示区域的DC部分
// 输入参数：bool reDraw:是否全部重新绘制，否则利用旧DC进行比较后拷贝能够重新利用的部分
// 输出参数：void
// 创建日期：2008.10.17
// 修改日期:  
// 作 者：   alzq
// 附加说明：
//=====================================================================
void SeeFileViewTable::RedrawWorkArea(bool reDraw)
{
	if(!m_dcBakDC)
	{
		//当无建立绘制DC时，直接跳过
		return ;;
	}

	if(reDraw)
	{
		if(m_ficFileControl.m_iTotalCount>0)
		{
			//当总的ITEM数量不为0时才开始绘制，否则不进行绘制
			_ReDrawItems(m_iShowItemHead,m_iShowItemEnd);

			if(m_uiViewStyle == STYLE_SMALL_PHOTO)
			{
				//在缩略图样式中填充其余空白区域
				if((m_iShowItemEnd+1) % m_iPerLineItemCount!=0)
				{
					//当最后一个显示的Item无法将显示区域填满
					CPoint pt=GetItemPosition(m_iShowItemEnd);
					pt.x+=m_iItemWithBorderWidth;
					pt.y=pt.y-m_iWorkAreaTop;
					Gdiplus::Graphics graph(m_dcWorkAreaDC->GetSafeHdc());
					graph.FillRectangle(m_brBakBrush,pt.x,pt.y,(m_iPerLineItemCount*m_iItemWithBorderWidth)-pt.x,m_iItemWithBorderHeight);
				}
			}
		}
	}
	else
	{
		//求出新的上限与旧的上限之间差距
		int y=m_iWorkAreaTop-m_iOldWorkAreaTop;
		int x=m_iWorkAreaLeft-m_iOldWorkAreaLeft;

		if(y==0 && x==0)
		{
			//当差距为0时，不需要重新绘制
			return ;
		}

		//当DC可以重新利用时
		int dy=0;
		if(m_uiViewStyle & STYLE_REPORT)
		{
			//当为详细信息样式时，利用显示DC做交换DC时，高度需要加20
			dy=20;
		}

		//设置需要重新绘制的上下范围
		int top=m_iWorkAreaTop;
		int bottom=m_iOldWorkAreaTop;
		if(abs(y)<m_iWorkAreaHeight-m_iItemWithBorderHeight)
		{
			//当移动差值比高度少一行还小时，表示此时旧DC的利用是有价值的
			if(y>0)
			{
				//当差值大于0时表示图象向上移动，需要重新绘制的范围重新设置
				top=m_iOldWorkAreaBottom;
				bottom=m_iWorkAreaBottom;

				//将显示区域DC可用部分拷贝到显示DC中，再将显示DC中可用部分拷贝回显示区域DC
				m_dcMemeryDC->BitBlt(0,dy,m_iWorkAreaWidth,m_iWorkAreaHeight-y,m_dcWorkAreaDC,0,y,SRCCOPY);
				m_dcWorkAreaDC->BitBlt(0,0,m_iWorkAreaWidth,m_iWorkAreaHeight-y,m_dcMemeryDC,0,dy,SRCCOPY);
			}
			if(y<0)
			{
				//将显示区域DC可用部分拷贝到显示DC中，再将显示DC中可用部分拷贝回显示区域DC
				m_dcMemeryDC->BitBlt(0,-y+dy,m_iWorkAreaWidth,m_iWorkAreaHeight+y,m_dcWorkAreaDC,0,0,SRCCOPY);
				m_dcWorkAreaDC->BitBlt(0,-y,m_iWorkAreaWidth,m_iWorkAreaHeight+y,m_dcMemeryDC,0,-y+dy,SRCCOPY);
			}
		}
		else
		{
			top=m_iWorkAreaTop;
			bottom=m_iWorkAreaBottom;
		}

		//设置需要重新绘制的左右范围
		int left=m_iWorkAreaLeft;
		int right=m_iOldWorkAreaLeft;
		if(abs(x)<m_iWorkAreaWidth)
		{
			if(x>0)
			{
				//当差值大于0时，表示向左拖动
				left=m_iOldWorkAreaRight;
				right=m_iWorkAreaRight;

				//将显示区域DC可用部分拷贝到显示DC中，再将显示DC中可用部分拷贝回显示区域DC
				m_dcMemeryDC->BitBlt(0,dy,m_iWorkAreaWidth-x,m_iWorkAreaHeight,m_dcWorkAreaDC,x,0,SRCCOPY);
				m_dcWorkAreaDC->BitBlt(0,0,m_iWorkAreaWidth-x,m_iWorkAreaHeight,m_dcMemeryDC,0,dy,SRCCOPY);
			}
			if(x<0)
			{
				//将显示区域DC可用部分拷贝到显示DC中，再将显示DC中可用部分拷贝回显示区域DC
				m_dcMemeryDC->BitBlt(-x,dy,m_iWorkAreaWidth+x,m_iWorkAreaHeight,m_dcWorkAreaDC,0,0,SRCCOPY);
				m_dcWorkAreaDC->BitBlt(-x,0,m_iWorkAreaWidth+x,m_iWorkAreaHeight,m_dcMemeryDC,-x,dy,SRCCOPY);
			}
		}
		else
		{
			left=m_iWorkAreaLeft;
			right=m_iWorkAreaRight;
		}

		if(m_ficFileControl.m_iTotalCount>0)
		{
			if(y!=0)
			{
				//纵向滚动
				CRect rect(0,top-m_iWorkAreaTop,m_iWorkAreaWidth,bottom-m_iWorkAreaTop);
				//重新绘制区域内对象
				_ReDrawRect(rect);
			}
			if(x!=0)
			{
				//横向滚动,需要绘制全部高度的信息
				CRect rect(left-m_iWorkAreaLeft,0,right-m_iWorkAreaLeft,m_iWorkAreaHeight);
				//重新绘制区域内对象
				_ReDrawRect(rect);
			}
		}

		return ;
	}

	m_iOldWorkAreaTop=m_iWorkAreaTop;								//当前显示部分的顶部更新前Y坐标-相对m_iWorkAreaHeight
	m_iOldWorkAreaBottom=m_iWorkAreaBottom;							//当前显示部分的底部更新前Y坐标-相对m_iWorkAreaHeight
	m_iOldWorkAreaLeft=m_iWorkAreaLeft;								//当前显示部分的左边界更新前坐标-相对m_iWorkAreaWidth
	m_iOldWorkAreaRight=m_iWorkAreaRight;							//当前显示部分的右边界更新前坐标-相对m_iWorkAreaWidth
}
	

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
CRect SeeFileViewTable::GetItemRect(int nItem)
{
	CPoint pt;
	pt=GetItemPosition(nItem);
	pt.x-=m_iWorkAreaLeft;
	pt.y-=m_iWorkAreaTop;
	//根据ITEM的显示区域顶点坐标,求出ITEM的显示区域范围
	CRect rect(
		pt.x
		,pt.y
		,pt.x+m_iItemWithBorderWidth==0?m_iWorkAreaWidth:m_iItemWithBorderWidth
		,pt.y+m_iItemWithBorderHeight);

	//超出显示范围的部分,去掉
	if(rect.top<0){rect.top=0;}
	if(rect.left<0){rect.left=0;}
	if(rect.bottom>m_iWorkAreaHeight){rect.bottom=m_iWorkAreaHeight;}
	if(rect.right>m_iWorkAreaWidth){rect.right=m_iWorkAreaWidth;}

	if(m_uiViewStyle & STYLE_REPORT)
	{
		//当为详细信息样式时，存在表头高度
		rect.top+=REPORT_HEAD_HEIGHT;
		rect.bottom+=REPORT_HEAD_HEIGHT;
	}

	return rect;
}
	

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
afx_msg LRESULT SeeFileViewTable::OnBeginDragLvOrType(WPARAM wParam,LPARAM lParam)
{
	m_iDragInfo=wParam;		//设置拖拽后设置的评级与分类值

	return 0;
}
	

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
afx_msg LRESULT SeeFileViewTable::OnEndDragLvOrType(WPARAM wParam,LPARAM lParam)
{
	CPoint point;
	GetCursorPos(&point);

	int nItem=GetItemCodeByMousePt(point);
	if(nItem<0)
	{
		//当拖拽到空白区域时，不操作
		return 0;
	}

	FileInfoList * file=m_ficFileControl.GetFile(nItem);

	if(m_iDragInfo!=-1)
	{
		//当所存储的设置信息有效时才进行设置
		if(file->GetState(LVIS_SELECTED))
		{
			//当拖拽到的文件被选择时，设置所有被选择文件
			m_ficFileControl.SetSelectedLvOrType(m_iDragInfo,wParam);
		}
		else
		{
			//当文件未被选择时，仅设置该文件
			m_ficFileControl.SetItemLvOrType(nItem,m_iDragInfo,wParam);
		}
	}

	m_iDragInfo=-1;

	//设置完信息后刷新显示
	Invalidate();
	return 0;
}
	

//=====================================================================
// 函 数 名：OnAlzqListView
// 功能描述：查看图片
// 输入参数：无
// 输出参数：无
// 创建日期：2008.10.09
// 修改日期:  
// 作 者：   alzq
// 附加说明： 
//=====================================================================
void SeeFileViewTable::OnAlzqListView()
{
	// TODO: 在此添加命令处理程序代码
	int nItem=m_ficFileControl.GetFirstSelectedCode();
	
	if(nItem>=0)
	{
		//当为图象文件时
		GetParent()->PostMessageA(MES_ALZQ_VIEW_PHOTO,nItem);
	}
}

//=====================================================================
// 函 数 名：OnAlzqListCut
// 功能描述：剪切
// 输入参数：无
// 输出参数：无
// 创建日期：2008.10.09
// 修改日期:  
// 作 者：   alzq
// 附加说明： 
//=====================================================================
void SeeFileViewTable::OnAlzqListCut()
{
	// TODO: 在此添加命令处理程序代码
	m_ficFileControl.DealSelectedFile(DEAL_FILE_CUT);
}

//=====================================================================
// 函 数 名：OnAlzqListCopy
// 功能描述：复制
// 输入参数：无
// 输出参数：无
// 创建日期：2008.10.09
// 修改日期:  
// 作 者：   alzq
// 附加说明： 
//=====================================================================
void SeeFileViewTable::OnAlzqListCopy()
{
	// TODO: 在此添加命令处理程序代码
	m_ficFileControl.DealSelectedFile(DEAL_FILE_COPY);
}

//=====================================================================
// 函 数 名：OnAlzqListCutFloder
// 功能描述：移动到
// 输入参数：无
// 输出参数：无
// 创建日期：2008.10.09
// 修改日期:  
// 作 者：   alzq
// 附加说明： 
//=====================================================================
void SeeFileViewTable::OnAlzqListCutFloder()
{
	// TODO: 在此添加命令处理程序代码
	MoveOrCopyToDlg copyDlg;
	if (copyDlg.DoModal()==IDOK)
	{
		string newFolderPath;
		newFolderPath=copyDlg.m_targePath.GetBuffer(0);
		//判断最后一个字符是否是"\",不是则添加
		if (newFolderPath.find_last_of("\\")!=newFolderPath.length()-1)
		{
			newFolderPath+="\\";
		}
		m_ficFileControl.DealSelectedFile(newFolderPath,DEAL_ASK,DEAL_FILE_CUT);
	}
}

//=====================================================================
// 函 数 名：OnAlzqListCopyFloder
// 功能描述：复制到
// 输入参数：无
// 输出参数：无
// 创建日期：2008.10.09
// 修改日期:  
// 作 者：   alzq
// 附加说明： 
//=====================================================================
void SeeFileViewTable::OnAlzqListCopyFloder()
{
	// TODO: 在此添加命令处理程序代码
	MoveOrCopyToDlg copyDlg;
	if (copyDlg.DoModal()==IDOK)
	{
 		string newFolderPath;
		newFolderPath=copyDlg.m_targePath.GetBuffer(0);
		//判断最后一个字符是否是"\",不是则添加
		if (newFolderPath.find_last_of("\\")!=newFolderPath.length()-1)
		{
			newFolderPath+="\\";
		}
		m_ficFileControl.DealSelectedFile( newFolderPath,DEAL_ASK,DEAL_FILE_COPY);
	}
}

//=====================================================================
// 函 数 名：OnAlzqListRename
// 功能描述：重命名
// 输入参数：无
// 输出参数：无
// 创建日期：2008.10.09
// 修改日期:  
// 作 者：   alzq
// 附加说明： 
//=====================================================================
void SeeFileViewTable::OnAlzqListRename()
{
	// TODO: 在此添加命令处理程序代码
	//获取选中的第一个文件
	int nSel=m_ficFileControl.GetFirstSelectedCode();
	//显示Edit
	showEdit(nSel);
}

//=====================================================================
// 函 数 名：OnAlzqListAddcolection
// 功能描述：添加到收藏夹
// 输入参数：无
// 输出参数：无
// 创建日期：2008.10.10
// 修改日期:  
// 作 者：   alzq
// 附加说明： 
//=====================================================================
void SeeFileViewTable::OnAlzqListAddcolection()
{
	if(!m_wndFavoriteBar)
	{
		return ;
	}

	// TODO: 在此添加命令处理程序代码
	CStringList stringList;
	int len=m_ficFileControl.GetSelectedFileList(&stringList,FILE_FLODER|FILE_PHOTO);		//返回所有字符串相加总长度
	if(!len)
		return ;

	//CStringList的起始位置
	POSITION pItemPos = stringList.GetHeadPosition();
	while(pItemPos != NULL)     
	{   
		CString path=stringList.GetNext(pItemPos);
		m_wndFavoriteBar->InsertFovoriteItem(path.GetBuffer(0));
	}
}

void SeeFileViewTable::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	RefreshPreview();

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL SeeFileViewTable::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE;//CListCtrl::OnEraseBkgnd(pDC);
}

void SeeFileViewTable::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	//当存储的显示DC与当前显示DC不符合时，重新建立内存DC，同时设置
	if(!m_dcBakDC)
	{
		//建立相关绘制
		_BuildDC();
		// 不为绘图消息调用 CListCtrl::OnPaint()
		RedrawWorkArea(true);
		Refresh();
	}
	else
	{
		Refresh();
	}
}

//=====================================================================
// 函 数 名：OnSize
// 功能描述：当窗口大小变更时
// 输入参数：UINT nType, int cx, int cy
// 输出参数：无
// 创建日期：2008.10.10
// 修改日期:  
// 作 者：   alzq
// 附加说明：当窗口大小变更时，需要计算新的工作区域
//			 根据第一个被选择项确定显示区域；
//			 显示区域内ITEM编号范围
//=====================================================================
void SeeFileViewTable::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if(m_ficFileControl.m_bOrderByGroup)
	{
		//当进行分组排列时，计算方式不同，暂时预留位置
	}
	else
	{
		//计算新坐标
		_ResizeWorkAreaWithoutGroup(cx,cy,true);
		//填补空白区域
		FillOutofWorkArea();
		//重画整个DC
		RedrawWorkArea(true);
		//刷新显示
		Refresh();
	}
}

void SeeFileViewTable::OnMouseMove(UINT nFlags, CPoint point)
{
	MousePositionInfo oldInfo;
	oldInfo.pt=m_mpiMousePositionInfo.pt;
	oldInfo.positionType=m_mpiMousePositionInfo.positionType;
	oldInfo.value=m_mpiMousePositionInfo.value;
	//获取当前位置鼠标信息
	SetMousePositionInfo(point);

	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_maiMouseActionInfo.mouseCondition & MOUSE_DRAG_SCROLL_H)
	{
		//当鼠标在拖动横向拖拉条时，根据鼠标位置Y坐标判断是否有效拖动，否则设置位置回原位置
		int dy=point.y-(m_iCurrentViewHeight-(SCROLL_BAR_WIDTH_HEIGHT/2));
		if(abs(dy)<=SCROLL_DRAG_ENABLE_DISTANCE)
		{
			//当鼠标在有效范围内时,计算显示区域
			int x=point.x;
			x=(x-m_maiMouseActionInfo.dragStartPt.x)
				*(m_iWorkAreaTotalWidth-m_iWorkAreaWidth);
			x=x /(m_sbsHScrollBarState.scrollTotalLength-m_sbsHScrollBarState.scrollMidButLength-(2*SCROLL_BAR_WIDTH_HEIGHT));
			x=x+m_maiMouseActionInfo.mousePositionInfo.value;

			//纠正显示范围
			if(x<0)
			{
				x=0;
			}
			else if(x+m_iWorkAreaWidth>m_iWorkAreaTotalWidth)
			{
				x=m_iWorkAreaTotalWidth-m_iWorkAreaWidth;
			}

			if(x==m_iWorkAreaLeft)
			{
				//当需要显示的范围与当前范围相同时，直接显示内存DC
				RefreshWorkArea();
			}
			else
			{
				//设置显示位置后重新绘制
				SetWorkArea(CPoint(x,m_iWorkAreaTop));
			}
		}
		else
		{
			if(m_maiMouseActionInfo.mousePositionInfo.value==m_iWorkAreaLeft)
			{
				//当需要显示的范围与当前范围相同时，直接显示内存DC
				RefreshWorkArea();
			}
			else
			{
				//设置显示位置后重新绘制
				SetWorkArea(CPoint(m_maiMouseActionInfo.mousePositionInfo.value,m_iWorkAreaTop));
			}
		}
	}
	else if(m_maiMouseActionInfo.mouseCondition & MOUSE_DRAG_SCROLL_V)
	{
		//当鼠标在拖动横向拖拉条时，根据鼠标位置Y坐标判断是否有效拖动，否则设置位置回原位置
		int dx=point.x-(m_iCurrentViewWidth-(SCROLL_BAR_WIDTH_HEIGHT/2));
		if(abs(dx)<=SCROLL_DRAG_ENABLE_DISTANCE)
		{
			//当鼠标在有效范围内时,计算显示区域
			int y=point.y;
			y=(y-m_maiMouseActionInfo.dragStartPt.y)*(m_iWorkAreaTotalHeight-m_iWorkAreaHeight);
			y=y/(m_sbsVScrollBarState.scrollTotalLength-m_sbsVScrollBarState.scrollMidButLength-(2*SCROLL_BAR_WIDTH_HEIGHT));
			y=y+m_maiMouseActionInfo.mousePositionInfo.value;

			//纠正显示范围
			if(y<0)
			{
				y=0;
			}
			else if(y+m_iWorkAreaHeight>m_iWorkAreaTotalHeight)
			{
				y=m_iWorkAreaTotalHeight-m_iWorkAreaHeight;
			}

			if(y==m_iWorkAreaTop)
			{
				//当需要显示的范围与当前范围相同时，直接显示内存DC
				RefreshWorkArea();
			}
			else
			{
				//设置显示位置后重新绘制
				SetWorkArea(CPoint(m_iWorkAreaLeft,y));
			}
		}
		else
		{
			if(m_maiMouseActionInfo.mousePositionInfo.value==m_iWorkAreaTop)
			{
				//当需要显示的范围与当前范围相同时，直接显示内存DC
				RefreshWorkArea();
			}
			else
			{
				//设置显示位置后重新绘制
				SetWorkArea(CPoint(m_iWorkAreaLeft,m_maiMouseActionInfo.mousePositionInfo.value));
			}
		}
	}
	else if(m_maiMouseActionInfo.mouseCondition & MOUSE_LBT_DOWN && m_maiMouseActionInfo.mousePositionInfo.positionType==POSITION_ITEM && !(m_maiMouseActionInfo.mouseCondition & MOUSE_DRAG_FILE))
	{
		//当鼠标事件为左键按下，且按下的位置是ITEM位置时，根据鼠标位移判断是否文件拖拽
		CPoint pt(point.x,point.y);			//计算鼠标相对总体显示区域的绝对坐标
		if(abs(pt.x-m_maiMouseActionInfo.dragStartPt.x)+abs(pt.y-m_maiMouseActionInfo.dragStartPt.y)>20)
		{
			//当当前鼠标的X位移与Y位移相加，大于20时，认为此时为文件拖拽操作
			DragSelectedFiles();
		}
	}
	else if(m_maiMouseActionInfo.mouseCondition & MOUSE_DRAG_SELECT)
	{
		//当鼠标进行拖拉选择时

		//根据鼠标位置判断是否移动显示区域
		int dx=0;
		int dy=0;
		if(point.x<0)
		{
			//当鼠标在左边界外时,显示区域向左移动
			dx=point.x;
			m_mpiMousePositionInfo.pt.x=m_iWorkAreaLeft;
		}
		else if(point.x>m_iCurrentViewWidth)
		{
			dx=point.x-m_iCurrentViewWidth;
			m_mpiMousePositionInfo.pt.x=m_iWorkAreaRight;
		}

		if(point.y<0)
		{
			//当鼠标在上边界以上时,显示区域向上移动
			dy=point.y;
			m_mpiMousePositionInfo.pt.y=m_iWorkAreaTop;
		}
		else if(point.y>m_iCurrentViewHeight)
		{
			dy=point.y-m_iCurrentViewHeight;
			m_mpiMousePositionInfo.pt.y=m_iWorkAreaBottom;
		}

		if(dx!=0 || dy!=0)
		{
			//当鼠标在显示区域外时,需要移动显示区域,并计算选中项,移动区域时并不刷新显示
			_MoveWorkArea(dx,dy);
			//纠正当前鼠标信息所在绝对坐标
			m_mpiMousePositionInfo.pt.x+=dx;
			if(m_mpiMousePositionInfo.pt.x<0)
			{
				m_mpiMousePositionInfo.pt.x=0;
			}
			else if(m_mpiMousePositionInfo.pt.x>m_iWorkAreaTotalWidth)
			{
				m_mpiMousePositionInfo.pt.x=m_iWorkAreaTotalWidth;
			}

			m_mpiMousePositionInfo.pt.y+=dy;
			int maxHeight=m_iWorkAreaTotalHeight>m_iWorkAreaHeight?m_iWorkAreaTotalHeight:m_iWorkAreaHeight;
			if(m_mpiMousePositionInfo.pt.y<0)
			{
				m_mpiMousePositionInfo.pt.y=0;
			}
			else if(m_mpiMousePositionInfo.pt.y>maxHeight)
			{
				m_mpiMousePositionInfo.pt.y=maxHeight;
			}
		}

		//设置当前选择部分的ITEM状态,并将显示部分的ITEM重新绘制后刷新显示
		_DragSelect(m_maiMouseActionInfo.mousePositionInfo.pt,oldInfo.pt,m_mpiMousePositionInfo.pt);

		RedrawWorkArea(true);
		Refresh();
	}

	if   (!m_bMouseTracking)   
	{
		TRACKMOUSEEVENT   tme;   
		tme.cbSize   =   sizeof(TRACKMOUSEEVENT);   
		tme.dwFlags   =   TME_LEAVE;   
		tme.hwndTrack   =   m_hWnd;   
		tme.dwHoverTime   =   HOVER_DEFAULT;   
		m_bMouseTracking=::_TrackMouseEvent(&tme);
	}
	CWnd::OnMouseMove(nFlags, point);
}

void SeeFileViewTable::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);

	// TODO: 在此处添加消息处理程序代码
	if(!m_bListGetFouc)
	{
		m_bListGetFouc=true;
	
		RedrawWorkArea(true);
		Refresh();
	}
}

void SeeFileViewTable::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);

	// TODO: 在此处添加消息处理程序代码
	if(m_bListGetFouc)
	{
		m_bListGetFouc=false;
	
		RedrawWorkArea(true);
		Refresh();
	}
}

void SeeFileViewTable::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_maiMouseActionInfo.mouseCondition!=MOUSE_NONE)
	{
		//当正在进行鼠标操作时，不进行任何操作
	}
	else
	{
		//处理鼠标操作，并设置当前鼠标操作信息
		m_maiMouseActionInfo.mouseCondition|=DealLbtDownMes(m_mpiMousePositionInfo.positionType,nFlags,point);

		//设置鼠标操作相关信息
		m_maiMouseActionInfo.dragStartPt=point;
		m_maiMouseActionInfo.mousePositionInfo.pt=m_mpiMousePositionInfo.pt;
		m_maiMouseActionInfo.mousePositionInfo.positionType=m_mpiMousePositionInfo.positionType;
		m_maiMouseActionInfo.mousePositionInfo.value=m_mpiMousePositionInfo.value;
	}
	m_maiMouseActionInfo.mouseCondition|=MOUSE_LBT_DOWN;			//在鼠标状态中添加左键按下状态

	//获取鼠标动作焦点
	SetCapture();

	return ;//CWnd::OnLButtonDown(nFlags, point);
}

void SeeFileViewTable::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//获取鼠标动作焦点
	SetCapture();

	return ;//CWnd::OnRButtonDown(nFlags, point);
}

void SeeFileViewTable::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	RefreshPreview();
	
	CPoint pt;
	GetCursorPos(&pt);

	int nItem=GetItemCodeByMousePt(pt);

	if(nItem<0)
	{
		//当右键点击区域无ITEM时
	}
	else
	{
		FileInfoList * file=m_ficFileControl.GetFile(nItem);
		if(file->CheckFileType(FILE_PHOTO))
		{
			//当文件是图象时
			m_cmMenuChild=m_cmRightButtonMenu.GetSubMenu(0);
		}
		else
		{
			//当文件不是图象时
			m_cmMenuChild=m_cmRightButtonMenu.GetSubMenu(1);
		}

		m_cmMenuChild->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);
	}

	CWnd::OnRButtonUp(nFlags, point);
}

void SeeFileViewTable::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CWnd::OnRButtonDblClk(nFlags, point);
}

void SeeFileViewTable::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//设置鼠标操作相关信息
	m_maiMouseActionInfo.dragStartPt=point;
	m_maiMouseActionInfo.mouseCondition &= ~MOUSE_LBT_DOWN;			//在操作状态中使用或操作

	//设置鼠标操作为空，并释放鼠标获取，此时不论鼠标右键是否进行操作都重置鼠标操作信息
	m_maiMouseActionInfo.mouseCondition=MOUSE_NONE;
	//释放鼠标动作焦点
	ReleaseCapture();

	m_maiMouseActionInfo.mousePositionInfo.positionType=m_mpiMousePositionInfo.positionType;
	m_maiMouseActionInfo.mousePositionInfo.value=m_mpiMousePositionInfo.value;

	Refresh();

	CWnd::OnLButtonUp(nFlags, point);
}

void SeeFileViewTable::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//释放鼠标动作焦点
	//ReleaseCapture();

	CWnd::OnNcLButtonUp(nHitTest, point);
}

BOOL SeeFileViewTable::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int i=-zDelta/120;
	JumpLine(i);

	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

LRESULT SeeFileViewTable::OnNcHitTest(CPoint point)
{
	CRect  rect;  
	CPoint  pt;  
	GetWindowRect(rect);  
	pt.x=point.x-rect.left;  
	pt.y=point.y-rect.top;			//设置鼠标相对LIST的位置
	 
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_maiMouseActionInfo.mouseCondition!=MOUSE_NONE)
	{
		//当鼠标正在进行操作时
		if(m_maiMouseActionInfo.mousePositionInfo.positionType==m_mpiMousePositionInfo.positionType)
		{
			//当鼠标开始操作的位置与当前所在位置类型相同时
			if(m_maiMouseActionInfo.mouseCondition & (MOUSE_SCROLL_H_AREA|MOUSE_SCROLL_H_LEFT|MOUSE_SCROLL_H_RIGHT|MOUSE_SCROLL_V_AREA|MOUSE_SCROLL_V_DOWN|MOUSE_SCROLL_V_UP))
			{
				//当鼠标时间是某些事件时，处理方式与鼠标左键按下时处理方式相同
				DealLbtDownMes(m_mpiMousePositionInfo.positionType,0,pt);
			}
		}
	}

	//根据鼠标位置信息对比进行处理

	return CWnd::OnNcHitTest(point);
}

LRESULT SeeFileViewTable::OnMouseLeave(WPARAM wParam,LPARAM lParam)
{
	//鼠标离开窗口时进行的操作

	m_bMouseTracking = FALSE;
	return TRUE;
}

void SeeFileViewTable::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CWnd::OnActivate(nState, pWndOther, bMinimized);

	// TODO: 在此处添加消息处理程序代码
}
	

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
afx_msg LRESULT SeeFileViewTable::OnRefreshAll(WPARAM wParam,LPARAM lParam)
{
	Refresh();
	
	return TRUE;
}
	

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
afx_msg LRESULT SeeFileViewTable::OnRefreshItem(WPARAM wParam,LPARAM lParam)
{
	ReDrawItem(wParam);

	return TRUE;
}

void SeeFileViewTable::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent & (MOUSE_DRAG_SELECT|MOUSE_DRAG_FILE))
	{
		//当是拖拽文件或者拖拉选择文件时,根据鼠标位置移动窗口
		CPoint pt;
		GetCursorPos(&pt);
		CRect rect;
		GetWindowRect(&rect);
		if(!rect.PtInRect(pt))
		{
			//当鼠标不在窗口内时
			OnNcHitTest(pt);
		}
	}

	CWnd::OnTimer(nIDEvent);
}