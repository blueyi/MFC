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
//ringeditex.cpp
//
//演示仿QQ2009的界面,搜索栏EDIT控件自绘
//
**********************************************************************/
#include "global.h"

enum
{
	PTSRC_LEFT = 0,			//左边圆角
	PTSRC_BORDER,				//边框
	PTSRC_SEARCH,				//放大镜
	PTSRC_CLOSENORMAL,		//正常关闭按钮
	PTSRC_CLOSEHOT,			//高亮关闭按钮
	PTSRC_CLOSEPUSHED,		//按下状态关闭按钮
	PTSRC_RETURNNORMAL,		//正常执行按钮
	PTSRC_RETURNHOT,			//高亮执行按钮
	PTSRC_RETURNPUSHED,		//按下执行关闭按钮

	PART_LEFT = 12,		//左边圆角宽度
	PART_RIGHT = 53,		//右边非客户区宽度
	PART_TOPBORDER = 7,	//上方非客户区高度
	PART_BOTBORDER = 5,	//下方非客户区高度

	ARROW_POS = 14,		//放大镜右边下拉箭头与右边框距离
	ARROW_WIDTH	= 8		//放大镜右边下拉箭头宽度
};

//各部件在源图象上的坐标,为方便计算，right和bottom字段为相应图象宽高
RECT gRcPart[12] = {
	{0,0,12,26},	//PTSRC_LEFT
	{8,0,3,26},		//PTSRC_BORDER
	{11,0,53,26},	//PTSRC_SEARCH
	{68,34,15,15},	//PTSRC_CLOSENORMAL
	{68,19,15,15},	//PTSRC_CLOSEHOT
	{83,19,15,15},	//PTSRC_CLOSEPUSHED
	{64,0,34,19},	//PTSRC_RETURNNORMAL
	{34,26,34,19},	//PTSRC_RETURNHOT
	{0,26,34,19},	//PTSRC_RETURNPUSHED
};

void RingEditEx::SetSkin(UINT uidImg)
{
	m_dibSrc.Load(MAKEINTRESOURCE(uidImg),"GIF",GIF);
	if(m_rm == NULL)
	{
		m_rm = new RingCoolMenu;
		m_rm->LoadPopup(MAKEINTRESOURCE(IDR_SEARCHMENU));
		HBITMAP hbm = window->m_dibMenuBkg.GetBitmap();
		m_rm->SetBkg(hbm);
		DeleteObject(hbm);
		m_rm->SetSelectBkg(window->m_hBmMenuSel,0x00FFFFFF);
		m_rm->CheckItem(CM_SEARCH);
	}
}

void RingEditEx::UpdateHSL(UINT uidImg,int h,int s,int l)
{
	m_dibSrc.Load(MAKEINTRESOURCE(uidImg),"GIF",GIF);
	m_dibSrc.GETFILTER(dibFilterEFFECT)->AdjustHSL(h,s,l);

	HBITMAP hbm = window->m_dibMenuBkg.GetBitmap();
	m_rm->SetBkg(hbm);
	DeleteObject(hbm);
	m_rm->SetSelectBkg(window->m_hBmMenuSel,0x00FFFFFF);
	OnNCPaint();
}

LRESULT RingEditEx::RingdowProc(HWND hWnd,RINGPARAMS param)
{
	switch(param.uMsg)
	{
		case WM_NCCALCSIZE:
		{	
			param.lprc->left += PART_LEFT;
			param.lprc->right -= PART_RIGHT;
			param.lprc->top += PART_TOPBORDER;
			param.lprc->bottom -= PART_BOTBORDER;
			return 0;
		}
		case WM_NCPAINT:
			return OnNCPaint();
		case WM_NCHITTEST:
		{
			LRESULT res = DefaultProc(param);
			if(res != HTCLIENT)
				res = HTCAPTION;
			return res;
		}
		case WM_NCLBUTTONDOWN:
			OnNCLButtonDown(param);
			return 0;
		case WM_COMMAND:
			if(param.shortval.low == CM_SEARCH)
			{
				m_rm->CheckItem(CM_SEARCH,(m_rm->GetItemCheckState(CM_SEARCH) == MF_UNCHECKED));
				//这里可向主窗口发送命令通知执行动作
				//SendMessage(window->Handle(),...);
			}
			break;
		case WM_MEASUREITEM:
			NotifyChild(m_hWnd,param.uMsg,param.wParam,param.lParam);
			return SendMessage(m_parent->Handle(),param);
		case WM_DRAWITEM:
			NotifyChildDrawItem(m_hWnd,param.lpdrawitem->hwndItem,param.uMsg,param.wParam,param.lParam);
			return SendMessage(m_parent->Handle(),param);
		case WM_DESTROY:
			delete m_rm;
			break;
		case WM_SETFOCUS:
			if(m_bShowTip)
			{
				m_bShowTip = FALSE;
				if(strcmp(GetText(),gszSearchTip) == 0)
				{
					SetValue("");
					SetTextColor(0);
				}
			}
			break;
		case WM_KILLFOCUS:
			if(*GetText() == '\0')
			{
				m_bShowTip = TRUE;
				SetTextColor(0x00808080);
				SetValue(gszSearchTip);
			}
			break;
	}
	return RingEdit::RingdowProc(hWnd,param);
}

LRESULT RingEditEx::OnNCPaint()
{
	RECT rc,rcClient;
	HDC hDC = GetWindowDC(m_hWnd);

	GetWindowRect(m_hWnd,&rc);
	GetClientRect(&rcClient);
	MapWindowPoints(m_hWnd,HWND_DESKTOP,(LPPOINT)&rcClient,2);

	//转换客户区坐标到相对EDIT边框左上角的坐标
	OffsetRect(&rcClient,-rc.left,-rc.top);
	OffsetRect(&rc,-rc.left,-rc.top);

	ExcludeClipRect(hDC,rcClient.left,rcClient.top,rcClient.right,rcClient.bottom);

	m_dibSrc.Draw(hDC,0,0,gRcPart[PTSRC_LEFT].left,gRcPart[PTSRC_LEFT].top,
						gRcPart[PTSRC_LEFT].right,gRcPart[PTSRC_LEFT].bottom,
						gRcPart[PTSRC_LEFT].right,gRcPart[PTSRC_LEFT].bottom);
	m_dibSrc.Draw(hDC,PART_LEFT,0,gRcPart[PTSRC_BORDER].left,gRcPart[PTSRC_BORDER].top,
						rcClient.right - rcClient.left,gRcPart[PTSRC_BORDER].bottom,
						gRcPart[PTSRC_BORDER].right,gRcPart[PTSRC_BORDER].bottom);
	m_dibSrc.Draw(hDC,rc.right - PART_RIGHT,0,gRcPart[PTSRC_SEARCH].left,gRcPart[PTSRC_SEARCH].top,
						gRcPart[PTSRC_SEARCH].right,gRcPart[PTSRC_SEARCH].bottom,
						gRcPart[PTSRC_SEARCH].right,gRcPart[PTSRC_SEARCH].bottom);

	ReleaseDC(m_hWnd,hDC);
	return 0;
}

void RingEditEx::OnNCLButtonDown(RINGPARAMS& param)
{
	POINT pt = {param.mousept.x,param.mousept.y};
	RECT rc;
	GetWindowRect(m_hWnd,&rc);

	rc.left = rc.right - ARROW_POS;
	rc.right = rc.left + ARROW_WIDTH;

	if(PtInRect(&rc,pt))
	{
		if(m_rm)
			m_rm->Popup(m_hWnd);
	}
}

