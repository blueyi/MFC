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
//原文件：wndqqbutton.cpp
//
//演示仿QQ2009的界面,底部工具栏窗口
//
**********************************************************************///////////////////////////////////////
#include "global.h"

//按钮ID定义
#define IDC_HIDETOOL		13401
#define IDC_QQMENUBTN	13402

enum
{
	QQBTN_WIDTH = 36,					//左下角QQ按钮宽
	QQBTN_HEIGHT = 36,				//左下角QQ按钮高
	QQBTN_X = 2,						//左下角QQ按钮x坐标
	QQBTN_Y = 15,						//左下角QQ按钮y坐标
	QQBTN_QQ_X = 8,					//QQ图象在QQ按钮上x坐标
	QQBTN_QQ_Y = 8,					//QQ图象在QQ按钮上y坐标
	QQBTN_QQ_WIDTH = 19,				//QQ图象宽
	QQBTN_QQ_HEIGHT = 20,			//QQ图象高

	BTN_PICWIDTH = 15,				//切换侧边工具栏按钮图象宽度
	BTN_PICHEIGHT = 14,				//切换侧边工具栏按钮图象高度
	BTN_WIDTH = 13,					//切换侧边工具栏按钮宽度
	BTN_HEIGHT = 13,					//切换侧边工具栏按钮高度
	BTN_X = 3,							//切换侧边工具栏按钮x坐标
	BTN_Y = 1,							//切换侧边工具栏按钮y坐标
};

BEGIN_REGMSG(WndQQButton)
	REGMSG(WM_LINKHOVER)
	REGMSG(WM_LINKLEAVE)
	REGMSG(WM_PAINT)
	REGCMD(IDC_HIDETOOL,OnSwitchSideTab)
	REGMSG(WM_CREATE)
END_REGMSG

RINGMSG(WndQQButton,WM_CREATE)
{
	m_bIsSideToolHide = FALSE;
	m_dibQQBtn.Create(QQBTN_WIDTH * 3,QQBTN_HEIGHT);

	//创建切换侧边工具栏按钮
	m_btn = NewRingObj(itemof(RingStatic));
	m_btn->Create(0,0,NULL,IDC_HIDETOOL,BTN_X,BTN_Y,BTN_WIDTH,BTN_HEIGHT);
	HRGN hrgn = CreateEllipticRgn(0,0,BTN_WIDTH,BTN_HEIGHT);
	SetWindowRgn(m_btn->Handle(),hrgn,TRUE);
	DeleteObject(hrgn);
	m_btn->SetHyperlink(0,0,FALSE);
	m_dibArrBtn.SetTarget(m_btn->Handle());

	//创建QQ按钮
	m_btnQQ = NewRingObj(itemof(RingStatic));
	m_btnQQ->Create(0,0,NULL,IDC_QQMENUBTN,QQBTN_X,QQBTN_Y,QQBTN_WIDTH,QQBTN_HEIGHT);
	hrgn = CreateEllipticRgn(0,0,QQBTN_WIDTH,QQBTN_HEIGHT);
	SetWindowRgn(m_btnQQ->Handle(),hrgn,TRUE);
	DeleteObject(hrgn);
	m_btnQQ->SetHyperlink(0,0,FALSE);
	//设定m_dibQQBtn和m_dibBkg的绘制目标窗口为QQ按钮
	m_dibQQBtn.SetTarget(m_btnQQ->Handle());
	m_dibBkg.SetTarget(m_btnQQ->Handle());

	//创建工具提示
	m_tip = NewRingObj(itemof(RingToolTip));
	m_tip->Create();
	m_tip->AddTool(m_btn->Handle(),"收起侧边栏");
	m_tip->AddTool(m_btnQQ->Handle(),"主菜单");

	SetPos(0,0,NCB_QQBTNWIDTH,NCB_BOTTOMHEIGHT);
	return DefaultProc(param);
}

RINGCMD(WndQQButton,OnSwitchSideTab)
{
	if(event == STN_CLICKED)
	{
		//切换侧边工具栏显示隐藏状态，该工具栏代码尚未实现，这里仅改变一下标记
		m_bIsSideToolHide = !m_bIsSideToolHide;
		if(m_bIsSideToolHide)
		{
			WndClient->m_sidebar->Show(SW_HIDE);
			m_tip->SetValue("展开侧边栏",IDC_HIDETOOL);
		}
		else
		{
			WndClient->m_sidebar->Show(SW_SHOW);
			RingDockBar* bar = WndClient->m_sidebar->GetDockBar();
			if(bar)
				bar->Show(SW_SHOW);
			m_tip->SetValue("收起侧边栏",IDC_HIDETOOL);
		}
		InvalidateRect(m_hWnd,NULL,TRUE);
	}
}

RINGMSG(WndQQButton,WM_PAINT)
{
	if(m_bIsSideToolHide)
	{
		PAINTSTRUCT ps;
		BeginPaint(m_hWnd,&ps);
		m_dibArrBtn.Draw(ps.hdc,BTN_X + (BTN_WIDTH - BTN_PICWIDTH)/2,BTN_Y,m_dibArrBtn.Width()/2,0,
								BTN_PICWIDTH,BTN_PICHEIGHT,BTN_PICWIDTH,BTN_PICHEIGHT);
		EndPaint(m_hWnd,&ps);
		return 0;
	}
	else
		return DefaultProc(param);
}

RINGMSG(WndQQButton,WM_LINKHOVER)
{
	if((HWND)param.wParam == m_btn->Handle())
	{
		int sx = BTN_PICWIDTH;
		if(m_bIsSideToolHide)
			sx += m_dibArrBtn.Width()/2;
		m_dibArrBtn.Draw((BTN_WIDTH - BTN_PICWIDTH)/2,0,sx,0,BTN_PICWIDTH,BTN_PICHEIGHT,BTN_PICWIDTH,BTN_PICHEIGHT);
	}
	else if((HWND)param.wParam == m_btnQQ->Handle())
	{
		m_dibQQBtn.Draw(0,0,0,0,QQBTN_WIDTH,QQBTN_HEIGHT,QQBTN_WIDTH,QQBTN_HEIGHT);
		Sleep(80);
		m_dibQQBtn.Draw(0,0,QQBTN_WIDTH,0,QQBTN_WIDTH,QQBTN_HEIGHT,QQBTN_WIDTH,QQBTN_HEIGHT);
		Sleep(80);
		m_dibQQBtn.Draw(0,0,QQBTN_WIDTH*2,0,QQBTN_WIDTH,QQBTN_HEIGHT,QQBTN_WIDTH,QQBTN_HEIGHT);
	}
	return TRUE;
}

RINGMSG(WndQQButton,WM_LINKLEAVE)
{
	if((HWND)param.wParam == m_btn->Handle())
	{
		int sx = 0;
		if(m_bIsSideToolHide)
			sx = m_dibArrBtn.Width()/2;
		m_dibArrBtn.Draw((BTN_WIDTH - BTN_PICWIDTH)/2,0,sx,0,BTN_PICWIDTH,BTN_PICHEIGHT,BTN_PICWIDTH,BTN_PICHEIGHT);
	}
	else if((HWND)param.wParam == m_btnQQ->Handle())
	{
		m_dibQQBtn.Draw(0,0,QQBTN_WIDTH,0,QQBTN_WIDTH,QQBTN_HEIGHT,QQBTN_WIDTH,QQBTN_HEIGHT);
		Sleep(80);
		m_dibQQBtn.Draw(0,0,0,0,QQBTN_WIDTH,QQBTN_HEIGHT,QQBTN_WIDTH,QQBTN_HEIGHT);
		Sleep(80);
		m_dibBkg.Draw(0,0,QQBTN_X,QQBTN_Y,QQBTN_WIDTH,QQBTN_HEIGHT,QQBTN_WIDTH,QQBTN_HEIGHT);
	}
	return TRUE;
}

void RINGMETHOD(WndQQButton,UpdateHSL)(int h,int s,int l)
{
	if(h < 0)
	{
		h = window->m_ri.GetInt("mainbkg","hue",0);
		s = window->m_ri.GetInt("mainbkg","Saturation",100);
		l = window->m_ri.GetInt("mainbkg","light",100);
	}
	m_dibBkg.Load(IDB_QQBTN);
	m_dibBkg.GETFILTER(dibFilterEFFECT)->AdjustHSL(h,s,l);
	m_dibArrBtn.Load(IDB_ARRBTN);
	m_dibArrBtn.GETFILTER(dibFilterEFFECT)->AdjustHSL(h,s,l);
	m_dibQQ.Load(MAKEINTRESOURCE(IDP_QQ),"PNG",PNG);
	
	for(int i=0;i<3;i++)
	{
		m_dibBkg.DrawTo(&m_dibQQBtn,i*QQBTN_WIDTH,0,QQBTN_X,QQBTN_Y,QQBTN_WIDTH,QQBTN_HEIGHT,FALSE);
		m_dibQQ.AlphaTo(&m_dibQQBtn,QQBTN_QQ_X + i*QQBTN_WIDTH,QQBTN_QQ_Y,i*QQBTN_QQ_WIDTH,0,QQBTN_QQ_WIDTH,QQBTN_QQ_HEIGHT);
	}
	
	HBITMAP hbm = m_dibBkg.GetBitmap();
	SetBkgBitmap(hbm);
	DeleteObject(hbm);
}
