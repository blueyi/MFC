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
//tabex.cpp
//
//演示仿QQ2009的界面,ListBox控件高亮子项支持。
//
**********************************************************************/
#include "global.h"

LRESULT RingListBoxEx::RingdowProc(HWND hWnd,RINGPARAMS param)
{
	switch(param.uMsg)
	{
		case WM_MOUSEMOVE:
		{
			int nHot = LOWORD(SendMessage(m_hWnd,LB_ITEMFROMPOINT,0,param.lParam));
			RECT rc = {0,0,0,0};
			if(GetItemRect(nHot,&rc))
			{
				POINT pt = {param.mousept.x,param.mousept.y};
				if(PtInRect(&rc,pt))
				{
					if(m_nHot != nHot)
					{
						ReDrawItem(m_nHot);
						m_nHot = nHot;
						if(MASK_MATCH(GetData(nHot),QQLIST_ISTITLE))
							m_btn->Show(SW_HIDE);
						else
							m_btn->SetPos(rc.left + USERIMG_SIZE + 8,rc.top + 34,-999,-999,NULL,SWP_SHOWWINDOW);
						ReDrawItem(nHot);
					}
				}
				else
				{
					if(m_nHot != -1)
					{
						m_nHot = -1;
						m_btn->Show(SW_HIDE);
						ReDrawItem(nHot);
					}
				}
			}
			if(!m_bTrack)
			{
				SetMouseTrack(WM_MOUSEMOVE,TME_LEAVE);
				m_bTrack = TRUE;
			}
			return 0;
		}
		case WM_MOUSELEAVE:
			m_bTrack = FALSE;
			if(m_nHot != -1)
			{
				RECT rc;
				POINT pt;
				GetCursorPos(&pt);
				ScreenToClient(m_hWnd,&pt);
				GetItemRect(m_nHot,&rc);
				if(PtInRect(&rc,pt))
					return 0;
			}			
			ReDrawItem(m_nHot);
			m_nHot = -1;
			return 0;
		case WM_ERASEBKGND:
		{
			RECT rc;
			GetClientRect(&rc);
			int nBot = rc.bottom;
			GetItemRect(GetCount()-1,&rc);
			rc.top = rc.bottom;
			rc.bottom = nBot;
			FillRect(param.hdc,&rc,m_brush);
			return TRUE;
		}
		case WM_CTLCOLORSTATIC:
			return (LONG)GetStockObject(NULL_BRUSH);
		case WM_LINKHOVER:
			return SendMessage(WndClient->Handle(),param);
		case WM_LINKLEAVE:
			return SendMessage(WndClient->Handle(),param);
	}
	return RingListBox::RingdowProc(m_hWnd,param);
}

void RingListBoxEx::ReDrawItem(int nIndex)
{
	if(nIndex != -1)
	{
		RECT rc;
		GetItemRect(nIndex,&rc);
		InvalidateRect(m_hWnd,&rc,TRUE);
	}
}

void RingListBoxEx::InitMailButton(UINT uId)
{
	m_dib.Load(MAKEINTRESOURCE(uId),"GIF",GIF);
	if(m_btn == NULL)
	{
		m_btn = NewRingObj(m_btn);
		if(m_btn)
		{
			m_btn->Create(0,0,NULL,IDC_MAIL,0,0,m_dib.Height(),m_dib.Height());
			m_btn->SetHyperlink(0,0,FALSE);
			m_dib.SetTarget(m_btn->Handle());
			m_btn->Show(SW_HIDE);
		}
	}
}

void RingListBoxEx::DrawMailButton(RingDIB* dib,BOOL bHot,int x,int y)
{
	m_dib.DrawTo(dib,x,y,bHot?m_dib.Height():0,0,m_dib.Height(),m_dib.Height());
}

void RingListBoxEx::DrawMailButtonHot()
{
	m_dib.Draw(0,0,m_dib.Height(),0,m_dib.Height(),m_dib.Height(),m_dib.Height(),m_dib.Height());
}
