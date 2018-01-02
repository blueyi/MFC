/**********************************************************************
//
//
//        ##########                          ######  #########   # ######    #
//      #############                      ########### ######### #########  ###
//     ######## # ###  ##                 ############# ##    ## #####  # ####
//     ####  ##    ## ###                 ###     ### # #      #####   #####
//          #     ###  #            #     ##       ##  ##      ##     ###
//         ## ###### ##      ##  ####    ####          #       #     ##
//       #########  ###  ## ### #######   ######      ##      ##    ###
//      ######      ##  ######  ##  ##       ####     #      ##     ####
//     #######     ##   ###### ##  ###          ##   ##     ###    ######
//     #########   ##  ###### ## ######         ### ##    ###      #  #####
//    ##    ###### ####### ### #### ##  ## #######  ########      ##    ####
//    ##      #### ###  #  ### ### ##  ##########   ######       ##      ####
//   ##         ##                ##   #########    ####         #         ##
//               #              ###
//                              ##
//                             ###
//                             ##
//
//
//							RingSDK演示程序
//作者：临风
//
//e-mail:ringphone@sina.com
//
//原文件：qqlike.cpp
//
//演示仿QQ2009的界面
//
**********************************************************************/
//#define WINVER 0x0500
#include "global.h"

//各系统按钮在源图象上的坐标
POINT gRcBtn[12] = {
	{0,34},		//MINNORMAL
	{25,34},		//MAXNORMAL
	{50,34},		//CLOSENORMAL
	{93,34},		//RESTORENORMAL
	{0,17},		//MINHOVER
	{25,17},		//MAXHOVER
	{50,17},		//CLOSEHOVER
	{93,17},		//RESTOREHOVER
	{0,0},		//MINDOWN
	{25,0},		//MAXDOWN
	{50,0},		//CLOSEDOWN
	{93,0}		//RESTOREDOWN
};

LPTSTR gszToolInfo[] = {
	"QQ空间信息中心",
	"打开我的邮箱",
	"拍拍购物信息中心",
	"进入我的钱包",
	"进入我的问问",
	"打开今日要闻",
	"打开消息盒子",
	"更改外观"
};

BEGIN_REGMAINMSG
	REGMSG(WM_SIZE)
	REGMSG(WM_MOVE)
	REGMSG(WM_ERASEBKGND)
	REGMSG(WM_PAINT)
	REGMSG(WM_GETMINMAXINFO)
	REGMSG(WM_NCCALCSIZE)
	REGMSG(WM_NCPAINT)
	REGMSG(WM_LBUTTONDBLCLK)
	REGMSG(WM_LBUTTONDOWN)
	REGMSG(WM_MOUSEMOVE)
	REGMSG(WM_LBUTTONUP)
	REGNOTIFY(NM_CUSTOMDRAW)
	REGMSGEX(MYWM_ICON,OnClickTaskIcon)
	REGCMD(CM_SHOWMAIN,OnShowWindow)
	REGCMD(IDC_USERSIGN,OnChangeSign)
	REGCMD(CM_EXIT,OnExit)
	REGMSG(WM_ENTERSIZEMOVE)
	REGMSG(WM_EXITSIZEMOVE)
	REGMSG(WM_DESTROY)
	REGMSG(WM_CREATE)
END_REGMSG

HANDLE g_hMutex = NULL;

int RingMain()
{
	g_hMutex = RegOnlyWindow("RINGSDK_QQLIKE_MUTEX");
	if(g_hMutex == NULL)
	{
		//已有程序运行，激活已运行程序
		HWND hWnd = FindWindow("RINGSDK_QQLIKE_WND","仿QQ2009界面");
		if(hWnd)
		{
			SendMessage(hWnd,MYWM_ICON,0,WM_LBUTTONDOWN);
			SetForegroundWindow(hWnd);
			SetActiveWindow(hWnd);
			return 0;
		}
	}
	APP_CREATEWINDOWEX("仿QQ2009界面","RINGSDK_QQLIKE_WND",WS_POPUPWINDOW|WS_THICKFRAME|WS_MINIMIZEBOX|WS_MAXIMIZEBOX,
							WS_EX_TOOLWINDOW,(LPCTSTR)NULL);
	int nRet =  RingApp.Run();
	CloseHandle(g_hMutex);
	return nRet;
}

//成员变量初始化
INITMAINWINDOW()
{
	m_hrgn = NULL;
	m_bInCapture = FALSE;
	m_editSign = NULL;
}

RINGMAINMSG(WM_CREATE)
{
	//设置窗口背景色
	SetBkgColor(0xDB9808);
	//创建画笔，绘制窗口外框
	m_pen = CreatePen(PS_SOLID,1,0x935702);
	//设置图象格式支持
	DIBREGFORMAT(GIF);
	DIBREGFORMAT(PNG);
	
	//设定按钮坐标
	SetRect(&m_rcUserBtn,55,24,87,46);			//用户头像旁按钮
	SetRect(&m_rcUserSign,55,44,187,66);		//个性签名按钮
	SetRect(&m_rcToolTop,NCB_TOOLTOP_X,NCB_TOOLTOP_Y,
				NCB_TOOLTOP_X + NCB_TOOLTOPBTNCOUNT*NCB_HOVERBTNHEIGHT,
				NCB_TOOLTOP_Y + NCB_HOVERBTNHEIGHT);			//用户头像下方工具栏，按钮尺寸同NCB_HOVERBTNHEIGHT

	//载入资源
	m_dibBkg.Load(MAKEINTRESOURCE(IDB_BKG));								//背景
	m_dibBtnRc.Load(MAKEINTRESOURCE(IDG_SYSBTN),"GIF",GIF);			//系统按钮源图象
	m_dibNCBtns.Create(NCB_ENTIREWIDTH,NCB_HEIGHT);						//创建系统按钮区图象
	m_dibCaption.Load(MAKEINTRESOURCE(IDP_QQ2009),"PNG",PNG);		//窗口标题“QQ2009”
	m_dibUser.Load(MAKEINTRESOURCE(IDG_USER),"GIF",GIF);				//用户头像
	m_dibHoverBtn.Load(MAKEINTRESOURCE(IDG_HOVERMENU),"GIF",GIF);	//按钮突起/按下状态
	m_dibToolTop.Load(MAKEINTRESOURCE(IDG_TOOLTOP),"GIF",GIF);		//用户头像下方工具栏
	m_dibMenuBkg.Load(MAKEINTRESOURCE(IDB_MENUBKG));					//菜单背景
	m_dibMenuSel.Load(MAKEINTRESOURCE(IDB_MENUSEL));					//菜单高亮图案
	m_dibBot.Load(IDB_TOOLBOT1);												//底部工具栏
	m_dibBot.SetColorKey(0x00FF00FF);

	//用户名及签名
	m_dibUserBanner.Create(WINVAR(SM_CXSCREEN),42);
	MakeUserBanner("RingSDK","编辑个性签名");
	m_dibUserBanner.SetColorKey(0x00FFFFFF);

	//创建标题栏和底栏背景图像，即双缓冲的内存图象，宽度为整个屏幕宽
	m_dibBanner.Create(WINVAR(SM_CXSCREEN)+2*WND_BORDER+10,NCB_TITLEHEIGHT + NCB_BOTTOMHEIGHT);
	
	//调色
	m_ri.SetFile("%s\\qq.ini",ringStr(RSTR_CURRPATH).string());
	UpdateHSL();

	//设置窗口图标
	HICON hIcon = LoadIcon(GetInstance(),MAKEINTRESOURCE(IDI_QQ));
	AddInTaskBar(m_hWnd,hIcon,"仿QQ2009界面");
	SetIcon(hIcon);

	//加载系统栏菜单
	m_rm = InstallCoolMenu(MAKEINTRESOURCE(IDR_MAINMENU),TRUE);
	HBITMAP hbm = m_dibMenuBkg.GetBitmap();
	m_rm->SetBkg(hbm);
	DeleteObject(hbm);
	m_hBmMenuSel = m_dibMenuSel.GetBitmap();
	m_rm->SetSelectBkg(m_hBmMenuSel,0x00FFFFFF);
	m_rm->SetItemIcon(CM_ONLINE,LoadIcon(GetInstance(),MAKEINTRESOURCE(IDI_ONLINE)));
	m_rm->SetItemIcon(CM_QME,LoadIcon(GetInstance(),MAKEINTRESOURCE(IDI_QME)));
	m_rm->SetItemIcon(CM_LEAVE,LoadIcon(GetInstance(),MAKEINTRESOURCE(IDI_LEAVE)));
	m_rm->SetItemIcon(CM_BUSY,LoadIcon(GetInstance(),MAKEINTRESOURCE(IDI_BUSY)));
	m_rm->SetItemIcon(CM_STOP,LoadIcon(GetInstance(),MAKEINTRESOURCE(IDI_STOP)));
	m_rm->SetItemIcon(CM_OFFLINE,LoadIcon(GetInstance(),MAKEINTRESOURCE(IDI_OFFLINE)));
	m_rm->SetItemIcon(CM_LOCK,LoadIcon(GetInstance(),MAKEINTRESOURCE(IDI_LOCK)));
	
	//创建个性签名编辑框并隐藏
	m_editSign = NewRingObj(itemof(RingEdit));
	m_editSign->Create(ES_AUTOHSCROLL,0,"",IDC_USERSIGN,57,45,130,22);
	m_editSign->Show(SW_HIDE);
	//创建提示信息（Tooltip）
	RECT rc = {NCB_TOOLTOP_X,NCB_TOOLTOP_Y,NCB_TOOLTOP_X+NCB_HOVERBTNHEIGHT,NCB_TOOLTOP_Y+NCB_HOVERBTNHEIGHT};
	m_tip = NewRingObj(itemof(RingToolTip));
	m_tip->Create();
	for(int i=0;i<NCB_TOOLTOPBTNCOUNT;i++)
	{
		m_tip->AddTool(i+1,gszToolInfo[i],&rc);
		OffsetRect(&rc,NCB_HOVERBTNHEIGHT,0);
	}
	//最右边两个按钮，“打开消息盒子”和“更改外观”
	rc.right = WND_MINWIDTH - NCB_HOVERBTNHEIGHT;
	rc.left = rc.right - NCB_HOVERBTNHEIGHT;
	m_tip->AddTool(HT_TOOLTR,gszToolInfo[HT_TOOLTR - HT_TOOLTOPFIRST],&rc);
	OffsetRect(&rc,NCB_HOVERBTNHEIGHT,0);
	m_tip->AddTool(HT_UIOPTION,gszToolInfo[HT_UIOPTION - HT_TOOLTOPFIRST],&rc);

	SetPos(0,0,WND_MINWIDTH,540,NULL,SWP_NOMOVE|SWP_NOZORDER);

	//底部左下角QQ按钮
	WndQQButton = NewRingObj(WndQQButton,TRUE);
	WndQQButton->Create("","RINGSDK_QQBUTTON",WS_CHILD);
	WndQQButton->Show();
	WndQQButton->EnableDock(NULL,TBS_EX_NONE,TBS_FLAG_DOCKBOTTOM);
	WndQQButton->UpdateHSL();

	//底部工具栏
	m_barbot = NewRingObj(itemof(RingToolBar));
	m_barbot->Create(IDB_TOOLBOT1,TBSTYLE_FLAT|TBSTYLE_LIST,TBSTYLE_EX_MIXEDBUTTONS);
	
	m_barbot->InsertButton(0,0,IDS_TOOL1);
	m_barbot->InsertButton(1,1,IDS_TOOL2);
	m_barbot->InsertButton(2,2,IDS_TOOL3);
	m_barbot->InsertButton(3,3,IDS_TOOL4);
	m_barbot->InsertButton(4,4,IDS_TOOL5);
	m_barbot->InsertButton(5,5,IDS_TOOL6);
	m_barbot->InsertButton(6,6,IDS_TOOL7);
	m_barbot->InsertButton(7,7,IDS_TOOL8);
	m_barbot->InsertButton(8,8,IDS_TOOL9,"查找",TBSTYLE_BUTTON|BTNS_AUTOSIZE|BTNS_SHOWTEXT);
	//加入不可用按钮，目的是占位使工具栏在需要的地方折行
	m_barbot->InsertButton(9,9,IDS_TOOL1 + 10,NULL,TBSTYLE_BUTTON,TBSTATE_INDETERMINATE);
	
	m_barbot->GetClientRect(&rc);
	rc.bottom += rc.bottom;
	m_barbot->WrapToolBar(2,&rc);
	m_barbot->EnableDock(NULL,TBS_EX_NONE);
	SetRect(&rc,NCB_QQBTNWIDTH,500,180,540);
	m_barbot->DockTo(TBS_FLAG_DOCKBOTTOM,&rc);
	UpdateBottomTool();

	//创建客户区窗口
	WndClient = NewRingObj(WndClient,TRUE);
	WndClient->Create("","RINGSDK_QQCLIENT",WS_POPUP|WS_CLIPCHILDREN|WS_CLIPSIBLINGS);
	WndClient->Show();
	WndClient->UpdateHSL();

	CenterWindow();
	::GetClientRect(m_hWnd,&rc);
	PostMessage(m_hWnd,WM_SIZE,SIZE_RESTORED,MAKELONG(rc.right,rc.bottom));
	return DefaultProc(param);
}

RINGMAINMSG(WM_ERASEBKGND)
{
	return TRUE;
}

RINGMAINMSG(WM_MOVE)
{
	LRESULT res = DefaultProc(param);
	UpdateClientWndPos();
	return res;
}

RINGMAINMSG(WM_SIZE)
{
	RECT rc;	
	LRESULT res = DefaultProc(param);
	
	if(param.wParam == SIZE_MINIMIZED)
	{
		Show(SW_HIDE);
		if(WndClient)
			WndClient->Show(SW_HIDE);
		return res;
	}
	//移动客户区窗口
	UpdateClientWndPos();

	GetWindowRect(m_hWnd,&rc);
	OffsetRect(&rc,-rc.left,-rc.top);
	
	//更新个性签名按钮坐标
	m_rcUserSign.right = rc.right - NCB_SIGNSPACE;
	//更新个性签名
	if(m_editSign)
	{
		LPCTSTR lps = m_editSign->GetText(0,MAX_PATH);
		if(lps && *lps != '\0' && lstrlen(lps) > 20)
			MakeUserBanner("RingSDK",lps);
	}

	if(m_hrgn)
		DeleteObject(m_hrgn);
	m_hrgn = CreateRoundRectRgn(rc.left,rc.top,rc.right,rc.bottom,NCB_CORNERSIZE,NCB_CORNERSIZE);
	SetWindowRgn(m_hWnd,m_hrgn,TRUE);
	
	return res;
}

//开始调整尺寸，检测个性签名编辑框是否显示，显示的话需要更新签名并隐藏
RINGMAINMSG(WM_ENTERSIZEMOVE)
{
	//如果个性签名控件已显示，更新个性签名
	if(m_editSign->IsVisible())
		OnChangeSign(EN_KILLFOCUS);
	return DefaultProc(param);
}

//尺寸调整完毕，更新最右边两个按钮TOOLTIP的坐标
RINGMAINMSG(WM_EXITSIZEMOVE)
{
	RECT rc;
	TOOLINFO ti;

	ti.lpszText = NULL;
	if(m_tip && m_tip->GetToolInfo(HT_TOOLTR,&ti))
	{
		GetClientRect(&rc);
		rc.right -= NCB_HOVERBTNHEIGHT;
		rc.left = rc.right - NCB_HOVERBTNHEIGHT;
		rc.top = m_rcToolTop.top;
		rc.bottom = m_rcToolTop.bottom;

		if(!EqualRect(&rc,&ti.rect))
		{
			CopyRect(&ti.rect,&rc);
			ti.lpszText = gszToolInfo[HT_TOOLTR - HT_TOOLTOPFIRST];
			m_tip->SetToolInfo(&ti);

			ti.lpszText = NULL;
			OffsetRect(&rc,NCB_HOVERBTNHEIGHT,0);
			m_tip->GetToolInfo(HT_UIOPTION,&ti);
			CopyRect(&ti.rect,&rc);
			ti.lpszText = gszToolInfo[HT_UIOPTION - HT_TOOLTOPFIRST];
			m_tip->SetToolInfo(&ti);
		}
	}
	return DefaultProc(param);
}

RINGMAINMSG(WM_GETMINMAXINFO)
{
	//限制窗口可调整的最小尺寸
	LRESULT res = DefaultProc(param);
	LPMINMAXINFO lpf = (LPMINMAXINFO)param.lParam;
	
	lpf->ptMinTrackSize.x = WND_MINWIDTH;
	lpf->ptMinTrackSize.y = WND_MINHEIGHT;
	return res;
}

RINGMAINMSG(WM_DESTROY)
{
	//释放资源
	DelInTaskBar(m_hWnd);
	DeleteObject(m_hBmMenuSel);
	DeleteObject(m_pen);
	if(m_hrgn)
		DeleteObject(m_hrgn);
	return Quit();
}

RINGMAINMSG(WM_NCCALCSIZE)
{
	LPRECT lprc = (LPRECT)param.lParam;
	
	lprc->top += WND_BORDER;
	lprc->left += WND_BORDER;
	lprc->right -= (WND_BORDER + 1);	  //右边框需要留出画边框线的位置，1
	lprc->bottom -= (WND_BORDER + 1);  //同理
	
	return 0;
}

RINGMAINMSG(WM_LBUTTONDBLCLK)
{
	if(HitTest(param) == HTCAPTION)
	{
		if(IsZoomed())
			SendMessage(m_hWnd,WM_SYSCOMMAND,SC_RESTORE,0);
		else
			SendMessage(m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);
	}
	return 0;
}

RINGMAINMSG(WM_LBUTTONDOWN)
{
	//如果个性签名控件已显示，更新个性签名
	if(m_editSign->IsVisible())
		OnChangeSign(EN_KILLFOCUS);

	m_nCurSysCmd = m_nCurWhere = HitTest(param);
	
	if(m_nCurSysCmd == HT_USERBUTTON)
	{
		RECT rc;
		DrawUserButton(FALSE,TRUE);
		GetWindowRect(m_hWnd,&rc);
		rc.left += m_rcUserBtn.left;
		rc.right = rc.left + m_rcUserBtn.right - m_rcUserBtn.left;
		rc.top += m_rcUserBtn.top;
		rc.bottom = rc.top + m_rcUserBtn.bottom - m_rcUserBtn.top;
		m_rm->PopupEx(m_hWnd,rc.left,rc.bottom,FALSE,&rc);
	}				
	else if(m_nCurSysCmd == HT_USERSIGN)
	{
		DrawUserButton(TRUE,FALSE);
		m_editSign->SetPos(m_rcUserSign.left+2,m_rcUserSign.top+2,
								 m_rcUserSign.right-m_rcUserSign.left-4,m_rcUserSign.bottom-m_rcUserSign.top-4,
								 NULL,SWP_SHOWWINDOW);
		m_editSign->SetFocus();
	}
	else if(m_nCurSysCmd == HTCAPTION)
		EasyMove(m_hWnd);
	else
	{
		m_bInCapture = TRUE;
		SetCapture(m_hWnd);
		CheckAndDrawButtons(m_nCurSysCmd,8);
	}
	return 0;
}

RINGMAINMSG(WM_MOUSEMOVE)
{
	int nWhere = HitTest(param);
	
	if(m_bInCapture)
	{
		if(m_nCurSysCmd == nWhere && m_nCurWhere != nWhere)
		{
			//绘制按下状态按钮
			CheckAndDrawButtons(nWhere,8);
		}
		else if(m_nCurSysCmd != nWhere && m_nCurSysCmd == m_nCurWhere)
		{
			//绘制正常按钮
			CheckAndDrawButtons(m_nCurSysCmd,0);
		}
		m_nCurWhere = nWhere;
		return 0;
	}
	else
	{
		LRESULT res;
		if(nWhere != m_nCurWhere)
		{
			//需要绘制按钮，高亮或恢复原状
			if(nWhere != HTCAPTION)
				CheckAndDrawButtons(nWhere,4);	//高亮状态
			else
				CheckAndDrawButtons(m_nCurWhere,0);	//恢复原状
		}
		res = DefaultProc(param);
		m_nCurWhere = nWhere;
		return res;
	}
}

RINGMAINMSG(WM_LBUTTONUP)
{
	if(m_bInCapture)
	{
		ReleaseCapture();
		m_bInCapture = FALSE;
		if(m_nCurWhere == m_nCurSysCmd)
		{
			//绘制正常按钮
			CheckAndDrawButtons(m_nCurWhere,0);
			//发送系统命令
			switch(m_nCurSysCmd)
			{
			case HTMINBUTTON:
				m_nCurSysCmd = SC_MINIMIZE;
				break;
			case HTMAXBUTTON:					
				if(IsZoomed())
					m_nCurSysCmd = SC_RESTORE;
				else
					m_nCurSysCmd = SC_MAXIMIZE;
				break;
			case HTCLOSE:
				m_nCurSysCmd = SC_CLOSE;
				break;
			case HT_UIOPTION:
				WndUIOp = window->NewRingObj(WndUIOp,TRUE);
				WndUIOp->Create("","RINGSDK_QQUICONFIG",WS_POPUP|WS_CLIPCHILDREN|WS_CLIPSIBLINGS);
				{
					RECT rc;
					GetWindowRect(m_hWnd,&rc);
					OffsetRect(&rc,-rc.left,-rc.top);
					POINT pt = {rc.right - NCB_HOVERBTNHEIGHT,NCB_TITLEHEIGHT};
					ClientToScreen(m_hWnd,&pt);
					WndUIOp->SetPos(pt.x,pt.y);
				}
				WndUIOp->Show();
				return 0;
			default:
				m_nCurSysCmd = HTCAPTION;
				return 0;
			}
			SendMessage(m_hWnd,WM_SYSCOMMAND,m_nCurSysCmd,0);
		}
		return 0;
	}
	else
		return DefaultProc(param);
}

RINGMAINMSG(WM_PAINT)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;
	int yPos = 0;

	if(IsZoomed())
		yPos += WINVAR_BORDER_Y;

	hdc = BeginPaint(m_hWnd,&ps);

	::GetClientRect(m_hWnd,&rc);
	
	m_dibBkg.StretchTo(&m_dibBanner,0,0,rc.right,m_dibBanner.Height(),0,0,m_dibBkg.Width(),m_dibBkg.Height(),FALSE);
	//标题
	m_dibCaption.AlphaTo(&m_dibBanner,8,5,0,0);
	//装饰图案，即QQ所谓的“底纹”
	m_dibTatoo.AlphaTo(&m_dibBanner,rc.right-m_dibTatoo.Width(),0,0,0);
	//用户头像
	m_dibUser.DrawTo(&m_dibBanner,7,25,0,0,45,m_dibUser.Height());
	//用户名及签名
	m_dibUserBanner.DrawTo(&m_dibBanner,NCB_USERBANNER_X,NCB_USERBANNER_Y,0,0,
									max(176,m_rcUserSign.right-NCB_USERBANNER_X),m_dibUserBanner.Height());
	//用户头像下方工具栏
	m_dibToolTop.DrawTo(&m_dibBanner,NCB_TOOLTOP_X,NCB_TOOLTOP_Y,0,0,NCB_TOOLTOPBTNCOUNT*NCB_HOVERBTNHEIGHT,NCB_HOVERBTNHEIGHT);
	//用户头像下方靠右停靠工具栏
	m_dibToolTop.DrawTo(&m_dibBanner,rc.right - 44,NCB_TOOLTOP_Y,NCB_TOOLTOPBTNCOUNT*NCB_HOVERBTNHEIGHT,0,2*NCB_HOVERBTNHEIGHT,NCB_HOVERBTNHEIGHT);
	//系统按钮
	//最小化
	m_dibBtnRc.DrawTo(&m_dibBanner,rc.right - NCB_ENTIREWIDTH - NCB_SPACE,yPos,gRcBtn[0].x,gRcBtn[0].y,
							NCB_MINWIDTH,NCB_HEIGHT);
	//关闭
	m_dibBtnRc.DrawTo(&m_dibBanner,rc.right - NCB_CLOSEWIDTH - NCB_SPACE,yPos,
							gRcBtn[NCB_CLOSENORMAL].x,gRcBtn[NCB_CLOSENORMAL].y,NCB_CLOSEWIDTH,NCB_HEIGHT);
	//最大化/还原
	if(IsZoomed())
	{
		m_dibBtnRc.DrawTo(&m_dibBanner,rc.right - NCB_ENTIREWIDTH - NCB_SPACE + NCB_MINWIDTH,yPos,
								gRcBtn[NCB_RESTORENORMAL].x,gRcBtn[NCB_RESTORENORMAL].y,NCB_MAXWIDTH,NCB_HEIGHT);
	}
	else
	{
		m_dibBtnRc.DrawTo(&m_dibBanner,rc.right - NCB_ENTIREWIDTH - NCB_SPACE + NCB_MINWIDTH,yPos,
								gRcBtn[NCB_MAXNORMAL].x,gRcBtn[NCB_MAXNORMAL].y,NCB_MAXWIDTH,NCB_HEIGHT);
	}
	//保存系统按钮图案，高亮和按下状态按钮可在此基础上叠加
	m_dibBanner.DrawTo(&m_dibNCBtns,0,0,rc.right - NCB_ENTIREWIDTH - NCB_SPACE,yPos,NCB_ENTIREWIDTH,NCB_HEIGHT,FALSE);
	//绘制到窗口，标题栏区域
	m_dibBanner.Draw(hdc,0,0,0,0,rc.right,NCB_TITLEHEIGHT,rc.right,NCB_TITLEHEIGHT);
	//中间区域，该区域其实可以不用绘制，将来会有控件遮挡
	rc.top += NCB_TITLEHEIGHT;
	rc.bottom -= NCB_BOTTOMHEIGHT;
	FillRect(hdc,&rc,m_brush);		//m_brush为基类成员函数

	EndPaint(m_hWnd,&ps);
	return 0;
}

RINGMAINMSG(WM_NCPAINT)
{
	RECT rc,rcc;
	HDC hdc = GetWindowDC(m_hWnd);
	
	GetWindowRect(m_hWnd,&rc);
	::GetClientRect(m_hWnd,&rcc);
	MapWindowPoints(m_hWnd,HWND_DESKTOP,(LPPOINT)&rcc,2);
	
	OffsetRect(&rcc,-rc.left,-rc.top);
	OffsetRect(&rc,-rc.left,-rc.top);
	
	ExcludeClipRect(hdc,rcc.left,rcc.top,rcc.right,rcc.bottom);
	FillRect(hdc,&rc,m_brush);

	SelectObject(hdc,GetStockObject(NULL_BRUSH));
	SelectObject(hdc,m_pen);
	rc.bottom --;
	rc.right --;
	RoundRect(hdc,rc.left,rc.top,rc.right,rc.bottom,NCB_CORNERSIZE,NCB_CORNERSIZE);
	ReleaseDC(m_hWnd, hdc);
	return 0;
}

RINGMAINNOTIFY(NM_CUSTOMDRAW)
{
	if(param.lpnmhdr->hwndFrom == m_barbot->Handle())
	{
		if(param.lpnmcustomdraw->dwDrawStage == CDDS_PREPAINT)
			return CDRF_NOTIFYITEMDRAW;	//指定通知按钮自绘
		else if(param.lpnmcustomdraw->dwDrawStage == CDDS_ITEMPREPAINT)
		{
			int sx,h = m_dibBtnState.Height();
			int w = h,off = (param.lpnmcustomdraw->rc.bottom - param.lpnmcustomdraw->rc.top - h)/2;
			
			if(MASK_MATCH(param.lpnmcustomdraw->uItemState,CDIS_SELECTED))
			{
				//按下状态
				if(param.lpnmcustomdraw->dwItemSpec == IDS_TOOL9)
				{
					w = (m_dibBtnState.Width() - h*2)/2;
					sx = h * 2 + w;
				}
				else
					sx = h;
			}
			else if(MASK_MATCH(param.lpnmcustomdraw->uItemState,CDIS_HOT))
			{
				//高亮状态
				if(param.lpnmcustomdraw->dwItemSpec == IDS_TOOL9)
				{
					w = (m_dibBtnState.Width() - h*2)/2;
					sx = h * 2;
				}
				else
					sx = 0;
			}
			else
				return TBCDRF_NOEDGES;
			
			m_dibBtnState.Draw(param.lpnmcustomdraw->hdc,
									param.lpnmcustomdraw->rc.left + off,param.lpnmcustomdraw->rc.top + off,
									sx,0,w,h,w,h);
			return TBCDRF_NOEDGES;	//其余交给系统绘制，指定不需要绘制按钮外边框
		}
	}	
	return DefaultProc(param);
}

RINGMAINMSGEX(OnClickTaskIcon)
{
	if(param.lParam == WM_LBUTTONDOWN)
	{
		SetForegroundWindow(m_hWnd);
		SetActiveWindow(m_hWnd);
		Show(SW_SHOW);
		WndClient->Show();

		if(IsIconic())
			Show(SW_RESTORE);
	}
	else if(param.lParam == WM_RBUTTONDOWN)
	{
		if(m_rm)
			m_rm->Popup(m_hWnd);
	}
	return 0;
}

RINGMAINCMD(OnShowWindow)
{
	SetForegroundWindow(m_hWnd);
	SetActiveWindow(m_hWnd);
	Show(SW_SHOW);
	if(IsIconic())
		Show(SW_RESTORE);
}

RINGMAINCMD(OnChangeSign)
{
	if(event == EN_KILLFOCUS)
	{
		m_editSign->Show(SW_HIDE);
		LPCTSTR lps = m_editSign->GetText(0,MAX_PATH);
		if(lps && *lps != '\0')
			MakeUserBanner("RingSDK",lps);
		else
			MakeUserBanner("RingSDK","编辑个性签名");
		InvalidateRect(m_hWnd,&m_rcUserSign,TRUE);
	}
}

RINGMAINCMD(OnExit)
{
	SendExit();
}

void RINGMAINMETHOD(MakeUserBanner)(LPCTSTR lpsName,LPCTSTR lpsSign)
{
	RECT rc = {0,0,1,1};
	ringFont rfont;
	
	rfont.SetFont("宋体",9,RINGFONT_BOLD);
	m_dibUserBanner.FillRect(0x00FFFFFF,0,0,m_dibUserBanner.Width(),m_dibUserBanner.Height());
	HDC hDC = GetDC(m_hWnd);
	SelectObject(hDC,rfont.GetFont());
	DrawText(hDC,lpsName,lstrlen(lpsName),&rc,DT_CALCRECT);
	ReleaseDC(m_hWnd,hDC);
	m_dibUserBanner.DrawText(lpsName,36,5,0,&rfont);
	rfont.SetFont("宋体",9);
	m_dibUserBanner.DrawText("[我在线上]",36 + rc.right + 3,5,0,&rfont);
	SetRect(&rc,4,24,4+m_rcUserSign.right-m_rcUserSign.left,42);
	m_dibUserBanner.DrawText(lpsSign,&rc,DT_LEFT|DT_TOP|DT_END_ELLIPSIS,0x0,&rfont);
	m_dibUser.DrawTo(&m_dibUserBanner,0,0,47,0);
}

int RINGMAINMETHOD(HitTest)(RINGPARAMS& param)
{
	int xPos = param.mousept.x;
	int yPos = param.mousept.y;
	
	RECT rc;
	GetClientRect(&rc);
	
	if(xPos > rc.right - NCB_ENTIREWIDTH - NCB_SPACE && 
		yPos > rc.top + NCB_TOPPOS && yPos < rc.top + NCB_TOPPOS + NCB_HEIGHT)
	{
		//系统按钮区域
		if(xPos <= rc.right - NCB_ENTIREWIDTH - NCB_SPACE + NCB_MINWIDTH)
			return HTMINBUTTON;
		else if(xPos <= rc.right - NCB_SPACE - NCB_CLOSEWIDTH)
			return HTMAXBUTTON;
		else if(xPos <= rc.right - NCB_SPACE)
			return HTCLOSE;
	}
	else 
	{
		POINT pt = {xPos,yPos};
		
		rc.left = rc.right - 2*NCB_HOVERBTNHEIGHT;
		rc.top = NCB_TOOLTOP_Y;
		rc.bottom = rc.top + NCB_HOVERBTNHEIGHT;
		
		if(PtInRect(&m_rcUserBtn,pt))
			return HT_USERBUTTON;
		else if(PtInRect(&m_rcUserSign,pt))
			return HT_USERSIGN;
		else if(PtInRect(&m_rcToolTop,pt))
			return HT_TOOLTOPFIRST + ((pt.x - m_rcToolTop.left)/NCB_HOVERBTNHEIGHT);
		else if(PtInRect(&rc,pt))
			return HT_TOOLTR + ((pt.x - rc.left)/NCB_HOVERBTNHEIGHT);
	}
	return HTCAPTION;
}

//检测绘制按钮
void RINGMAINMETHOD(CheckAndDrawButtons)(int nWhich,int nOffset)
{
	if(nWhich >= HT_TOOLTOPFIRST && nWhich <= HT_UIOPTION)
		DrawToolButton(nWhich-HT_TOOLTOPFIRST,(nOffset==0));
	else
	{
		int nIdx=-1,offset=-1;
		switch(nWhich)
		{
		case HTMINBUTTON:
			offset = 0;
			nIdx = NCB_MINNORMAL;
			break;
		case HTMAXBUTTON:
			offset = NCB_MINWIDTH;
			if(IsZoomed())
				nIdx = NCB_RESTORENORMAL;
			else
				nIdx = NCB_MAXNORMAL;
			break;
		case HTCLOSE:
			offset = NCB_MINWIDTH + NCB_MAXWIDTH;
			nIdx = NCB_CLOSENORMAL;
			break;
		case HT_USERBUTTON:
			DrawUserButton(FALSE,m_bInCapture || nOffset==0);
			return;
		case HT_USERSIGN:
			DrawUserButton(TRUE,m_bInCapture || nOffset==0);
			//DrawSignButton(m_bInCapture || nOffset==0);
			return;
		}
		if(nIdx >= 0)
			DrawNCButton(nIdx + nOffset,offset);
	}
}

//绘制三态系统按钮,
//nIdx为按钮序号，gRcBtn[nIdx]记录了要绘制按钮在源图象的坐标
//offset为该按钮的绘制目的坐标横向偏移量（以最小化按钮的目标坐标为基准）
void RINGMAINMETHOD(DrawNCButton)(int nIdx,int offset)
{
	RECT rc;
	GetClientRect(&rc);

	int dx = rc.right - NCB_ENTIREWIDTH - NCB_SPACE;
	int dy = NCB_TOPPOS;
	int w = 0;
	if(IsZoomed())
		dy += WINVAR_BORDER_Y;
		
	//先恢复正常状态按钮，m_dibNCBtns在WM_PAINT消息中保存了正常状态的三个按钮图象
	m_dibNCBtns.DrawTo(&m_dibBanner,dx,dy,0,0,0,0,FALSE);
	if(offset == 0)
		w = NCB_MINWIDTH;
	else if(offset == NCB_MINWIDTH)
		w = NCB_MAXWIDTH;
	else if(offset == NCB_MINWIDTH + NCB_MAXWIDTH)
		w = NCB_CLOSEWIDTH;
	
	//绘制高亮或按下状态按钮
	if(nIdx >= 0)
		m_dibBtnRc.DrawTo(&m_dibBanner,dx + offset,dy,gRcBtn[nIdx].x,gRcBtn[nIdx].y,w,NCB_HEIGHT);
		
	HDC hdc = GetDC(m_hWnd);
	m_dibBanner.Draw(hdc,dx,dy,dx,dy,NCB_ENTIREWIDTH,NCB_HEIGHT,NCB_ENTIREWIDTH,NCB_HEIGHT);
	ReleaseDC(m_hWnd,hdc);
}

//绘制工具栏按钮
void RINGMAINMETHOD(DrawToolButton)(int nIdx,BOOL bDrawNormal)
{
	if(nIdx >= 0)
	{
		int dx,w;
		RECT rc;
		GetClientRect(&rc);

		if(nIdx < NCB_TOOLTOPBTNCOUNT)
		{
			w = NCB_TOOLTOPBTNCOUNT * NCB_HOVERBTNHEIGHT;
			dx = DrawToolTopBtn(nIdx,bDrawNormal,&rc);
		}
		else 
		{
			w = 2 * NCB_HOVERBTNHEIGHT;
			dx = DrawToolRightBtn(nIdx,bDrawNormal,&rc);
		}

		HDC hdc = GetDC(m_hWnd);
		m_dibBanner.Draw(hdc,dx,NCB_TOOLTOP_Y,dx,NCB_TOOLTOP_Y,w,NCB_HOVERBTNHEIGHT,w,NCB_HOVERBTNHEIGHT);
		ReleaseDC(m_hWnd, hdc);
	}
}
	
//辅助函数，绘制按钮高亮和按下状态
void RINGMAINMETHOD(DrawButtonState)(RingDIB* dest,BOOL bPushed,int x,int y,int w,int h)
{
	int off = 0;
	if(bPushed)
		off = NCB_HOVERBORDERWIDTH*2+1;		//按下图案在源图象的坐标
	//绘制状态图案，该图案格式为左边框（2像素）+中间图案（1像素）+右边框（2像素），高亮图案和按下图案并列
	//左边框
	m_dibHoverBtn.StretchTo(dest,x,y,NCB_HOVERBORDERWIDTH,h,off,0,NCB_HOVERBORDERWIDTH,m_dibHoverBtn.Height());
	//中间图案
	m_dibHoverBtn.StretchTo(dest,x+NCB_HOVERBORDERWIDTH,y,w-NCB_HOVERBORDERWIDTH*2,h,
									off+NCB_HOVERBORDERWIDTH,0,1,m_dibHoverBtn.Height());
	//右边框
	m_dibHoverBtn.StretchTo(dest,x+w-NCB_HOVERBORDERWIDTH,y,NCB_HOVERBORDERWIDTH,h,
									off+NCB_HOVERBORDERWIDTH+1,0,NCB_HOVERBORDERWIDTH,m_dibHoverBtn.Height());
}

int RINGMAINMETHOD(DrawToolTopBtn)(int nIdx,BOOL bDrawNormal,LPRECT lprc)
{	
	int sx = nIdx * NCB_HOVERBTNHEIGHT;
	int dx = NCB_TOOLTOP_X;
	int dy = NCB_TOOLTOP_Y;
	int w = NCB_TOOLTOPBTNCOUNT * NCB_HOVERBTNHEIGHT;
	int h = NCB_HOVERBTNHEIGHT;
	
	//恢复图象
	m_dibBkg.StretchTo(&m_dibBanner,dx,dy,w,h,0,dy,m_dibBkg.Width(),h,FALSE);
	if(dx+w > lprc->right-m_dibTatoo.Width())
		m_dibTatoo.AlphaTo(&m_dibBanner,lprc->right-m_dibTatoo.Width(),dy,0,dy,dx+w-(lprc->right-m_dibTatoo.Width()),h);
	if(!bDrawNormal)
	{
		if(m_bInCapture)
		{
			//按下状态
			DrawButtonState(&m_dibBanner,TRUE,dx + sx,dy,h,h);
			//按下的工具栏按钮，向右下方偏移1像素绘制
			m_dibToolTop.DrawTo(&m_dibBanner,dx+sx+1,dy+1,sx,0,h,h);
			//绘制其余工具栏按钮，左边部分
			m_dibToolTop.DrawTo(&m_dibBanner,dx,dy,0,0,sx,h);
			//右边部分
			m_dibToolTop.DrawTo(&m_dibBanner,dx+sx+h,dy,sx+h,0,w-sx-h,h);
			return dx;
		}
		else
		{
			//高亮状态
			DrawButtonState(&m_dibBanner,FALSE,dx + sx,dy,h,h);
		}
	}
	//绘制整条工具栏
	m_dibToolTop.DrawTo(&m_dibBanner,dx,dy,0,0,w,h);
	return dx;
}

int RINGMAINMETHOD(DrawToolRightBtn)(int nIdx,BOOL bDrawNormal,LPRECT lprc)
{	
	int sx = nIdx * NCB_HOVERBTNHEIGHT;
	int w = 2 * NCB_HOVERBTNHEIGHT;
	int dx = lprc->right - w;
	int dy = NCB_TOOLTOP_Y;
	int h = NCB_HOVERBTNHEIGHT;
	int realx = (nIdx - NCB_TOOLTOPBTNCOUNT) * NCB_HOVERBTNHEIGHT;
	
	//恢复图象
	m_dibBkg.StretchTo(&m_dibBanner,dx,dy,w,h,0,dy,m_dibBkg.Width(),h,FALSE);
	m_dibTatoo.AlphaTo(&m_dibBanner,dx,dy,m_dibTatoo.Width()-w,dy,w,h);
	if(!bDrawNormal)
	{
		if(m_bInCapture)
		{
			//按下图案
			DrawButtonState(&m_dibBanner,TRUE,dx + realx,dy,h,h);
			//按下的工具栏按钮，向右下方偏移1像素绘制
			m_dibToolTop.DrawTo(&m_dibBanner,dx+realx+1,dy+1,sx,0,h,h);
			//绘制另一个工具栏按钮
			if(realx == 0)
				m_dibToolTop.DrawTo(&m_dibBanner,dx+h,dy,sx+h,0,h,h);	//绘制“更改外观”按钮
			else
				m_dibToolTop.DrawTo(&m_dibBanner,dx,dy,sx-h,0,h,h);
			return dx;
		}
		else
		{
			//高亮状态
			DrawButtonState(&m_dibBanner,FALSE,dx + realx,dy,h,h);
		}
	}
	//绘制整条工具栏
	m_dibToolTop.DrawTo(&m_dibBanner,dx,dy,NCB_TOOLTOPBTNCOUNT * NCB_HOVERBTNHEIGHT,0,w,h);
	return dx;
}

//绘制用户头像旁按钮高亮状态，根据bSign：是，绘制个性签名按钮，否，绘制下拉菜单按钮
void RINGMAINMETHOD(DrawUserButton)(BOOL bSign,BOOL bDrawNormal)
{
	int x,y,w;
	int h = NCB_HOVERBTNHEIGHT;
	int tw = m_rcUserSign.right - m_rcUserBtn.left;
	int th = m_rcUserSign.bottom - m_rcUserBtn.top;
	RECT rc;
	GetClientRect(&rc);
	if(bSign)
	{
		x = m_rcUserSign.left;
		y = m_rcUserSign.top;
		w = m_rcUserSign.right - m_rcUserSign.left;
	}
	else
	{
		x = m_rcUserBtn.left;
		y = m_rcUserBtn.top;
		w = m_rcUserBtn.right - m_rcUserBtn.left;
	}

	//恢复图象，需要同时恢复用户签名的区域
	m_dibBkg.StretchTo(&m_dibBanner,m_rcUserBtn.left,m_rcUserBtn.top,tw,th,0,m_rcUserBtn.top,m_dibBkg.Width(),th,FALSE);
	//绘制底纹与此区域有交叉的部分
	m_dibTatoo.AlphaTo(&m_dibBanner,rc.right-m_dibTatoo.Width(),m_rcUserBtn.top,0,m_rcUserBtn.top,
								 m_rcUserSign.right-(rc.right-m_dibTatoo.Width()),th);
	if(!bDrawNormal)
	{
		//绘制高亮图案
		DrawButtonState(&m_dibBanner,FALSE,x,y,w,h);
	}
	//绘制按钮
	m_dibUserBanner.DrawTo(&m_dibBanner,NCB_USERBANNER_X,NCB_USERBANNER_Y,0,0,tw,th);

	HDC hdc = GetDC(m_hWnd);
	if(m_editSign->IsVisible())
		ExcludeClipRect(hdc,m_rcUserSign.left,m_rcUserSign.top,m_rcUserSign.right,m_rcUserSign.bottom);
	m_dibBanner.Draw(hdc,NCB_USERBANNER_X,NCB_USERBANNER_Y,NCB_USERBANNER_X,NCB_USERBANNER_Y,tw,th,tw,th);
	ReleaseDC(m_hWnd, hdc);
}

//更新背景颜色，亮度，对比度等
void RINGMAINMETHOD(UpdateHSL)()
{
	int h = m_ri.GetInt("mainbkg","hue",0);
	int s = m_ri.GetInt("mainbkg","Saturation",100);
	int l = m_ri.GetInt("mainbkg","light",100);
	//系统按钮调色，是将IDG_SYSBTNADJ调色后绘制到m_dibBtnRc
	RingDIB dib;
	dib.Load(MAKEINTRESOURCE(IDG_SYSBTNADJ),"GIF",GIF);
	dib.GETFILTER(dibFilterEFFECT)->AdjustHSL(h,s,l);
	dib.SetColorKey(dib.GetPixel(0,0));
	dib.DrawTo(&m_dibBtnRc);
	//背景，高亮/按下按钮调色
	m_dibBkg.GETFILTER(dibFilterEFFECT)->AdjustHSL(h,s,l);
	m_dibHoverBtn.GETFILTER(dibFilterEFFECT)->AdjustHSL(h,s,l);
	m_dibMenuBkg.GETFILTER(dibFilterEFFECT)->AdjustHSL(h,s,l);
	m_dibMenuSel.GETFILTER(dibFilterEFFECT)->AdjustHSL(h,s,l);

	SetLayeredAlpha((BYTE)m_ri.GetInt("mainbkg","transparent",255));
	
	m_dibTatoo.Load(MAKEINTRESOURCE(IDP_SEA + m_ri.GetInt("mainbkg","tatoo",0)),"PNG",PNG,GetInstance());
}

void RINGMAINMETHOD(UpdateHSL)(int h,int s,int l)
{
	//系统按钮调色，是将IDG_SYSBTNADJ调色后绘制到m_dibBtnRc
	RingDIB dib;
	dib.Load(MAKEINTRESOURCE(IDG_SYSBTNADJ),"GIF",GIF);
	dib.GETFILTER(dibFilterEFFECT)->AdjustHSL(h,s,l);
	dib.SetColorKey(dib.GetPixel(0,0));
	dib.DrawTo(&m_dibBtnRc);

	m_dibBkg.Load(MAKEINTRESOURCE(IDB_BKG));
	m_dibHoverBtn.Load(MAKEINTRESOURCE(IDG_HOVERMENU),"GIF",GIF);	//按钮突起/按下状态
	m_dibMenuBkg.Load(MAKEINTRESOURCE(IDB_MENUBKG));					//菜单背景
	m_dibMenuSel.Load(MAKEINTRESOURCE(IDB_MENUSEL));					//菜单高亮图案
	m_dibBkg.GETFILTER(dibFilterEFFECT)->AdjustHSL(h,s,l);
	m_dibHoverBtn.GETFILTER(dibFilterEFFECT)->AdjustHSL(h,s,l);
	m_dibMenuBkg.GETFILTER(dibFilterEFFECT)->AdjustHSL(h,s,l);
	m_dibMenuSel.GETFILTER(dibFilterEFFECT)->AdjustHSL(h,s,l);
	HBITMAP hbm = m_dibMenuBkg.GetBitmap();
	m_rm->SetBkg(hbm);
	DeleteObject(hbm);
	m_hBmMenuSel = m_dibMenuSel.GetBitmap();
	hbm = m_rm->SetSelectBkg(m_hBmMenuSel,0x00FFFFFF);
	DeleteObject(hbm);
	
	UpdateBottomTool();
	WndQQButton->UpdateHSL(h,s,l);
	WndClient->UpdateHSL(h,s,l);

	InvalidateRect(m_hWnd,NULL,TRUE);
}

//更新底栏区域
void RINGMAINMETHOD(UpdateBottomTool)()
{
	//设置/更新底部停靠坞背景
	HDC hDC = GetDC(m_hWnd);
	HDC hMemDC = CreateCompatibleDC(hDC);
	HBITMAP hbm = CreateCompatibleBitmap(hDC,1,NCB_BOTTOMHEIGHT);
	HBITMAP hbmPrev = (HBITMAP)SelectObject(hMemDC,hbm);
	m_dibBkg.Draw(hMemDC,0,0,0,NCB_TITLEHEIGHT,1,NCB_BOTTOMHEIGHT,1,NCB_BOTTOMHEIGHT);
	DeleteObject(hMemDC);
	ReleaseDC(m_hWnd,hDC);
	SetDockBackGround(hbm,FALSE,TBS_FLAG_DOCKBOTTOM);//,m_barbot->Handle());
	DeleteObject(hbm);
	//创建工具栏按钮及带文字按钮的按下和高亮图象，该图象为顺序排列的标准按钮的高亮/按下图案和带文字按钮的高亮/按下图案
	//图案仅为按下和高亮状态的方框，无按钮图象和文字
	int h = m_dibBot.Height();
	if(m_dibBtnState.Height() == 0)
	{
		RECT rc;
		m_barbot->GetButtonRect(8,&rc);
		int off = rc.bottom - rc.top - h;
		m_dibBtnState.Create(h*2 + (rc.right - rc.left - off)*2,h);
	}
	m_dibBkg.StretchTo(&m_dibBtnState,0,0,m_dibBtnState.Width(),m_dibBtnState.Height(),0,NCB_TITLEHEIGHT,
							1,m_dibBtnState.Height(),FALSE);
	DrawButtonState(&m_dibBtnState,FALSE,0,0,h,h);
	DrawButtonState(&m_dibBtnState,TRUE,h,0,h,h);
	DrawButtonState(&m_dibBtnState,FALSE,h*2,0,(m_dibBtnState.Width()-h*2)/2,h);
	DrawButtonState(&m_dibBtnState,TRUE,h*2+(m_dibBtnState.Width()-h*2)/2,0,(m_dibBtnState.Width()-h*2)/2,h);
}

void RINGMAINMETHOD(UpdateClientWndPos)()
{
	RECT rc;	
	GetClientRect(&rc);
	MapWindowPoints(m_hWnd,HWND_DESKTOP,(LPPOINT)&rc,2);
	
	if(WndClient)
	{
		MoveWindow(WndClient->Handle(),rc.left,rc.top + NCB_TITLEHEIGHT,rc.right - rc.left,
						rc.bottom - rc.top - NCB_TITLEHEIGHT,TRUE);
	}
}
