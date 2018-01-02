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
//原文件：wnduioption.cpp
//
//演示仿QQ2009的界面,界面调色设置窗口
//
**********************************************************************/
#include "global.h"

#define WND_OPWIDTH	146
#define WND_OPHEIGHT	24
#define IDC_STHEAD	20001

BEGIN_REGMSG(WndUIOp)
	REGMSG(WM_NCPAINT)
	REGMSG(WM_NCCALCSIZE)
	REGMSG(WM_ACTIVATE)
	REGCMD(IDC_STHEAD,OnSelTab)
	REGMSGEX(MYWM_COMMAND,OnHideClose)
	REGMSG(WM_DESTROY)
	REGMSG(WM_CREATE)
END_REGMSG

INITWINDOW(WndUIOp)()
{
	m_pen = NULL;
	m_stHead = NULL;
}

RINGMSG(WndUIOp,WM_CREATE)
{
	m_pen = CreatePen(PS_SOLID,1,0x00CF9365);
	SetBkgColor(0xF3F5E6);

	m_stHead = NewRingObj(itemof(RingStatic));
	m_stHead->Create(SS_CENTERIMAGE|SS_NOTIFY,0,"",IDC_STHEAD,0,0,WND_OPWIDTH,WND_OPHEIGHT);
	m_stHead->SetBkgBitmap(IDB_UICOLOR);

	DlgUIColor = NewRingObj(DlgUIColor,TRUE);
	DlgUIColor->Create();
	DlgUIColor->SetPos(0,WND_OPHEIGHT);

	DlgUITatoo = NewRingObj(DlgUITatoo,TRUE);
	DlgUITatoo->Create();
	DlgUITatoo->SetPos(0,WND_OPHEIGHT);
	DlgUITatoo->Show(SW_HIDE);

	RECT rc;
	::GetClientRect(DlgUIColor->Handle(),&rc);
	SetPos(0,0,rc.right + 11,WND_OPHEIGHT + rc.bottom + 11);		//+11:边框左5右6

	return DefaultProc(param);
}

RINGMSG(WndUIOp,WM_DESTROY)
{
	if(m_pen)
	{
		DeleteObject(m_pen);
		m_pen = NULL;
	}
	DlgUIColor->Close();
	DlgUITatoo->Close();
	return DefaultProc(param);
}

RINGMSG(WndUIOp,WM_ACTIVATE)
{
	LRESULT res = DefaultProc(param);
	//这里不能直接Close，必须消息返回后Close，否则接收不到WM_DESTROY消息，资源泄漏
	if(param.shortval.low == WA_INACTIVE)
		PostMessage(m_hWnd,MYWM_COMMAND,0xABCD,0xCDEF);	
	
	return res;
}

RINGMSGEX(WndUIOp,OnHideClose)
{
	if(param.wParam == 0xABCD && param.lParam == 0xCDEF)
		Close();
	return 0;
}

RINGMSG(WndUIOp,WM_NCCALCSIZE)
{
	LPRECT lprc = (LPRECT)param.lParam;
	
	lprc->top += 5;
	lprc->left += 5;
	lprc->right -= 6;
	lprc->bottom -= 6;
	
	return 0;
}

RINGMSG(WndUIOp,WM_NCPAINT)
{
	HDC hDC;
	RECT rc,rcClient;
		
	GetWindowRect(m_hWnd,&rc);
	GetClientRect(&rcClient);
	MapWindowPoints(m_hWnd,HWND_DESKTOP,(LPPOINT)&rcClient,2);
	OffsetRect(&rcClient,-rc.left,-rc.top);
	OffsetRect(&rc,-rc.left,-rc.top);

	rc.right --;
	rc.bottom --;

	hDC = GetWindowDC(m_hWnd);
	ExcludeClipRect(hDC,rcClient.left,rcClient.top,rcClient.right,rcClient.bottom);
	SelectObject(hDC,m_brush);
	SelectObject(hDC,m_pen);
	Rectangle(hDC,0,0,rc.right,rc.bottom);

	InflateRect(&rc,-4,-4);
	Rectangle(hDC,rc.left,rc.top,rc.right,rc.bottom);

	ReleaseDC(m_hWnd,hDC);
	return 0;
}

RINGCMD(WndUIOp,OnSelTab)
{
	if(event == STN_CLICKED)
	{
		RECT rc = {0,0,45,23};
		POINT pt;
		GetCursorPos(&pt);
		MapWindowPoints(m_hWnd,HWND_DESKTOP,(LPPOINT)&rc,2);
		if(PtInRect(&rc,pt) && !DlgUIColor->IsVisible())
		{
			m_stHead->SetBkgBitmap(IDB_UICOLOR);
			InvalidateRect(m_stHead->Handle(),NULL,TRUE);
			DlgUITatoo->Show(SW_HIDE);
			DlgUIColor->Show();
			return;
		}
		OffsetRect(&rc,46,0);
		if(PtInRect(&rc,pt) && !DlgUITatoo->IsVisible())
		{
			m_stHead->SetBkgBitmap(IDB_UITATOO);
			InvalidateRect(m_stHead->Handle(),NULL,TRUE);
			DlgUIColor->Show(SW_HIDE);
			DlgUITatoo->Show();
		}
	}
}

///////////////设置界面颜色，透明度///////////////////////
BEGIN_REGMSG(DlgUIColor)
	REGMSG(WM_HSCROLL)
	REGCMDRANGE(IDC_COLOR1,IDC_COLOR8,OnChooseColor)
	REGMSG(WM_DESTROY)
	REGMSG(WM_INITDIALOG)
END_REGMSG

RINGMSG(DlgUIColor,WM_INITDIALOG)
{
	int h = 0;
	RingDIB dib;
	dib.Load(IDB_UICOLORDEF);
	dib.DIBREGFILTER(dibFilterEFFECT);

	for(int i=0;i<8;i++)
	{
		m_stColor[i] = GetItem(itemof(RingStatic),IDC_COLOR1 + i);
		dib.GETFILTER(dibFilterEFFECT)->AdjustHSL(h,100,100);
		h = 40;
		m_stColor[i]->SetBitmap(dib.GetBitmap());
	}
	m_barHue = GetItem(itemof(RingTrackBarEx),IDC_ADJHUE);
	m_barHue->SetSkin(IDB_ADJHUE,IDB_ADJTHUMB);
	m_barHue->SetBkgColor(0x00FFFFFF);
	m_barHue->SetRange(-180,180);
	m_hue = window->m_ri.GetInt("mainbkg","hue",0);
	m_barHue->SetPosition(m_hue);

	m_barSum = GetItem(itemof(RingTrackBarEx),IDC_ADJSUM);
	m_barSum->SetSkin(IDB_ADJSUM,IDB_ADJTHUMB);
	m_barSum->SetBkgColor(0x00FFFFFF);
	m_barSum->SetRange(0,200);
	m_sum = window->m_ri.GetInt("mainbkg","Saturation",100);
	m_barSum->SetPosition(m_sum);

	m_barLum = GetItem(itemof(RingTrackBarEx),IDC_ADJLUM);
	m_barLum->SetSkin(IDB_ADJLUM,IDB_ADJTHUMB);
	m_barLum->SetBkgColor(0x00FFFFFF);
	m_barLum->SetRange(50,150);
	m_lum = window->m_ri.GetInt("mainbkg","light",100);
	m_barLum->SetPosition(m_lum);

	m_barAlpha = GetItem(itemof(RingTrackBarEx),IDC_ADJALPHA);
	m_barAlpha->SetSkin(IDB_ADJTRANS,IDB_ADJTHUMB);
	m_barAlpha->SetBkgColor(0x00FFFFFF);
	m_barAlpha->SetRange(25,255);
	m_barAlpha->SetPosition(255 - window->m_ri.GetInt("mainbkg","transparent",255) + 25);

	m_tip = NewRingObj(itemof(RingToolTip));
	m_tip->Create();
	m_tip->AddTool(GetDlgItem(m_hWnd,IDC_ADJHUE),"色调");
	m_tip->AddTool(GetDlgItem(m_hWnd,IDC_ADJSUM),"饱和度");
	m_tip->AddTool(GetDlgItem(m_hWnd,IDC_ADJLUM),"亮度");

	SetBkgColor(0x00FFFFFF);
	return FALSE;
}

RINGMSG(DlgUIColor,WM_DESTROY)
{
	HBITMAP hbm;
	for(int i=0;i<8;i++)
	{
		hbm = (HBITMAP)m_stColor[i]->GetBitmap();
		if(hbm)
			DeleteObject(hbm);
	}
	return FALSE;
}

RINGMSG(DlgUIColor,WM_HSCROLL)
{
	hWnd = (HWND)param.lParam;
	if(param.shortval.low == SB_ENDSCROLL)
	{
		if(hWnd == m_barAlpha->Handle())
		{
			//透明度
			int na = 255 - m_barAlpha->GetPosition() + 25;
			window->m_ri.Write("mainbkg","transparent",na);
			window->SetLayeredAlpha(na);
		}
		else
		{
			int h = m_barHue->GetPosition();
			int s = m_barSum->GetPosition();
			int l = m_barLum->GetPosition();
			window->m_ri.Write("mainbkg","hue",h);
			window->m_ri.Write("mainbkg","Saturation",s);
			window->m_ri.Write("mainbkg","light",l);
			window->UpdateHSL(h,s,l);
		}
	}
	return 0;
}

RINGCMD(DlgUIColor,OnChooseColor)
{
	int h = (event - IDC_COLOR1)*40;
	if(h > 180)
		h -= 360;
	m_barHue->SetPosition(h);

	int s = m_barSum->GetPosition();
	int l = m_barLum->GetPosition();
	window->m_ri.Write("mainbkg","hue",h);
	window->m_ri.Write("mainbkg","Saturation",s);
	window->m_ri.Write("mainbkg","light",l);
	window->UpdateHSL(h,s,l);
}

///////////////设置界面图案///////////////////////
BEGIN_REGMSG(DlgUITatoo)
	REGMSG(WM_PAINT)
	REGCMD(IDC_BKG1,OnSel1)
	REGCMD(IDC_BKG2,OnSel2)
	REGCMD(IDC_BKG3,OnSel3)
	REGCMD(IDC_BKG4,OnSel4)
	REGCMD(IDC_BKG5,OnSel5)
	REGCMD(IDC_BKG6,OnSel6)
	REGCMD(IDC_BKG7,OnSel7)
	REGCMD(IDC_BKG8,OnSel8)
	REGCMD(IDC_BKG9,OnSel9)
	REGMSG(WM_DESTROY)
	REGMSG(WM_INITDIALOG)
END_REGMSG

LPTSTR gszTatooInfo[] = {
	"沙滩",
	"风景",
	"卡通",
	"原野",
	"诛仙"
};

RINGMSG(DlgUITatoo,WM_INITDIALOG)
{
	m_nTatooCnt = 0;
	m_nCurrTatoo = window->m_ri.GetInt("mainbkg","tatoo",0);
	m_pen = CreatePen(PS_SOLID,1,0x000289FC);
	m_tip = NewRingObj(itemof(RingToolTip));
	m_tip->Create();

	RingDIB dib;//,dinPrev;
	for(int i=0;i<9;i++)
	{
		m_stTatoo[i] = GetItem(itemof(RingStatic),IDC_BKG1 + i);
		if(dib.Load(MAKEINTRESOURCE(IDB_TATOO1+i),GetInstance()))
		{
			m_stTatoo[i]->SetBitmap(dib.GetBitmap());
			m_tip->AddTool(m_stTatoo[i]->Handle(),gszTatooInfo[i]);
			m_nTatooCnt ++;
		}
		else
			m_stTatoo[i]->Disable();
	}
	SetBkgColor(0x00FFFFFF);
	return FALSE;
}

RINGCMD(DlgUITatoo,OnSel1)
{
	if(event == STN_CLICKED)
		OnSelTatoo(0);
}

RINGCMD(DlgUITatoo,OnSel2)
{
	if(event == STN_CLICKED)
		OnSelTatoo(1);
}

RINGCMD(DlgUITatoo,OnSel3)
{
	if(event == STN_CLICKED)
		OnSelTatoo(2);
}

RINGCMD(DlgUITatoo,OnSel4)
{
	if(event == STN_CLICKED)
		OnSelTatoo(3);
}

RINGCMD(DlgUITatoo,OnSel5)
{
	if(event == STN_CLICKED)
		OnSelTatoo(4);
}

RINGCMD(DlgUITatoo,OnSel6)
{
	if(event == STN_CLICKED)
		OnSelTatoo(5);
}

RINGCMD(DlgUITatoo,OnSel7)
{
	if(event == STN_CLICKED)
		OnSelTatoo(6);
}

RINGCMD(DlgUITatoo,OnSel8)
{
	if(event == STN_CLICKED)
		OnSelTatoo(7);
}

RINGCMD(DlgUITatoo,OnSel9)
{
	if(event == STN_CLICKED)
		OnSelTatoo(8);
}

RINGCMD(DlgUITatoo,OnSelTatoo)
{
	if(m_nCurrTatoo != (int)event)
	{
		m_nCurrTatoo = event;
		window->m_dibTatoo.Load(MAKEINTRESOURCE(IDP_SEA+event),"PNG",PNG,GetInstance());
		window->m_ri.Write("mainbkg","tatoo",m_nCurrTatoo);
		InvalidateRect(window->Handle(),NULL,TRUE);
		InvalidateRect(m_hWnd,NULL,TRUE);
	}
}

RINGMSG(DlgUITatoo,WM_PAINT)
{
	if(m_nTatooCnt > 0 && m_nCurrTatoo >= 0 && m_nCurrTatoo <= 9) 
	{
		RECT rc;
		PAINTSTRUCT ps;

		GetClientRect(&rc);
		BeginPaint(m_hWnd,&ps);
		FillRect(ps.hdc,&rc,m_brush);
		
		m_stTatoo[m_nCurrTatoo]->GetClientRect(&rc);
		MapWindowPoints(m_stTatoo[m_nCurrTatoo]->Handle(),m_hWnd,(LPPOINT)&rc,2);
		InflateRect(&rc,2,2);

		SelectObject(ps.hdc,m_pen);
		Rectangle(ps.hdc,rc.left,rc.top,rc.right,rc.bottom);

		EndPaint(m_hWnd,&ps);
	}
	return FALSE;
}

RINGMSG(DlgUITatoo,WM_DESTROY)
{
	HBITMAP hbm;
	for(int i=0;i<m_nTatooCnt;i++)
	{
		hbm = (HBITMAP)m_stTatoo[i]->GetBitmap();
		if(hbm)
			DeleteObject(hbm);
	}
	DeleteObject(m_pen);
	return FALSE;
}
