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
//ringtrackbarex.cpp
//
//演示仿QQ2009的界面,Slider控件自绘
//
**********************************************************************/
#include "global.h"

RingTrackBarEx::~RingTrackBarEx()
{
	DeleteObject(m_hbmLine);
	DeleteObject(m_hbmThumb);
}

LRESULT RingTrackBarEx::RingdowProc(HWND hWnd,RINGPARAMS param)
{
	switch(param.uMsg)
	{
		case WM_PRINTCLIENT:
		case WM_PAINT:
		{
			RECT rc,rcc;
			HDC hdc,hMemDC;
			PAINTSTRUCT ps;
			GetWindowRect(m_hWnd,&rc);
			OffsetRect(&rc,-rc.left,-rc.top);
			hdc = param.wParam?(HDC)param.wParam:BeginPaint(hWnd,&ps);
			FillRect(hdc,&rc,m_brush);

			hMemDC = CreateCompatibleDC(hdc);
			SelectObject(hMemDC,m_hbmLine);
			GetChannelRect(&rcc);
			StretchBlt(hdc,rcc.left,(rc.bottom - m_sizeLine.cy)/2,rcc.right-rcc.left,m_sizeLine.cy,
							hMemDC,0,0,m_sizeLine.cx,m_sizeLine.cy,SRCCOPY);
			SelectObject(hMemDC,m_hbmThumb);
			GetThumbRect(&rc);
			BitBlt(hdc,rc.left,rc.top,rc.right-rc.left,rc.bottom-rc.top,hMemDC,0,0,SRCCOPY);

			DeleteDC(hMemDC);
			if(param.wParam == 0)
				EndPaint(hWnd, &ps);
			return 0;
		}
	}
	
	return DefaultProc(param);
}

void RingTrackBarEx::SetSkin(UINT idLine,UINT idThumb)
{
	m_hbmLine = LoadBitmap(GetInstance(),MAKEINTRESOURCE(idLine));
	m_hbmThumb = LoadBitmap(GetInstance(),MAKEINTRESOURCE(idThumb));

	BITMAP bm;
	if(m_hbmLine)
	{
		GetObject(m_hbmLine,sizeof(BITMAP),&bm);
		m_sizeLine.cx = bm.bmWidth;
		m_sizeLine.cy = bm.bmHeight;
	}
	if(m_hbmThumb)
	{
		GetObject(m_hbmThumb,sizeof(BITMAP),&bm);
		m_sizeThumb.cx = bm.bmWidth;
		m_sizeThumb.cy = bm.bmHeight;
		ReplaceStyle(0,TBS_FIXEDLENGTH);
		SetThumbLength(m_sizeThumb.cy + 2);
	}
}
