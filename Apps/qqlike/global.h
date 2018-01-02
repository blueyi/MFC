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
//原文件：global.h
//
//演示仿QQ2009的界面
//
**********************************************************************/
#ifndef _INC_QQ2009_GLOBAL_H
#define _INC_QQ2009_GLOBAL_H
#include "ringmain.h"
#include "ringdib.h"
#include "resource.h"

enum
{
	NCB_MINNORMAL = 0,
	NCB_MAXNORMAL,
	NCB_CLOSENORMAL,
	NCB_RESTORENORMAL,
	NCB_MINHOVER,
	NCB_MAXHOVER,
	NCB_CLOSEHOVER,
	NCB_RESTOREHOVER,
	NCB_MINDOWN,
	NCB_MAXDOWN,
	NCB_CLOSEDOWN,
	NCB_RESTOREDOWN,
	
	NCB_ENTIREWIDTH = 93,			//整个系统按钮宽度
	NCB_MINWIDTH = 25,				//最小化按钮宽度
	NCB_MAXWIDTH = 25,				//最大化按钮宽度
	NCB_CLOSEWIDTH = 43,				//关闭按钮宽度
	NCB_HEIGHT = 17,					//系统按钮高度
	NCB_CORNERSIZE = 7,				//窗口园角半径
	NCB_TITLEHEIGHT = 95,			//窗口标题栏区域高度
	NCB_BOTTOMHEIGHT = 53,			//窗口底栏区域高度
	NCB_QQBTNWIDTH = 45,				//窗口底栏QQ按钮区域宽度

	NCB_SIGNSPACE = 48,				//个性签名距窗口最右边尺寸
	NCB_SPACE = 5,						//系统按钮距窗口最右边尺寸
	NCB_TOPPOS = 0,					//系统按钮距窗口上边尺寸
	NCB_HOVERBTNHEIGHT = 22,		//用户名边按钮高亮图案高度
	NCB_HOVERBORDERWIDTH = 2,		//用户名按钮边框宽度
	NCB_USERBTNPOSX = 65,			//用户名按钮相对窗口左上角横坐标
	NCB_USERBTNPOSY = 32,			//用户名按钮相对窗口左上角纵坐标
	NCB_USERBANNER_X = 54,			//用户名及个性签名横坐标
	NCB_USERBANNER_Y = 23,			//用户名及个性签名纵坐标

	NCB_TOOLTOPBTNCOUNT = 6,		//用户头像下工具栏按钮数量
	NCB_TOOLTOP_X = 8,				//用户头像下工具栏横坐标
	NCB_TOOLTOP_Y = 72,				//用户头像下工具栏纵坐标

	WND_MINWIDTH = 235,				//QQ窗口可调整最小宽度
	WND_MINHEIGHT = 329,				//QQ窗口可调整最小高度
	WND_BORDER = 2,					//窗口边框尺寸

	//HitTest扩展返回值
	HT_USERBUTTON = 3330,			//鼠标位于用户名旁按钮区域
	HT_USERSIGN,						//个性签名按钮
	HT_TOOLTOPFIRST,					//用户头像下方工具栏第一个按钮
	HT_TOOLTOPEND = HT_TOOLTOPFIRST + 5,		//用户头像下方工具栏最后一个按钮
	HT_TOOLTR,							//“打开消息盒子”按钮
	HT_UIOPTION,						//界面设置按钮
	//个性签名编辑框ID
	IDC_USERSIGN = 12301,
	IDC_MAINTAB,						//客户区TAB控件ID
	IDC_SEARCH,							//搜索栏ID
	IDC_QQFRIEND,						//好友列表
	IDC_QQGROUP,						//群列表
	IDC_QQRECENT,						//最近联系人列表
	IDC_MAIL,							//好友列表上的邮箱按钮ID

	USERIMG_SIZE = 24					//用户头像尺寸
};

#define QQLIST_EXPANDED			0x0000CDCD
#define QQLIST_ISTITLE			0xCDCD0000

extern TCHAR gszSearchTip[];

//自绘控件
class RingTrackBarEx:public RingTrackBar
{
public:
	RingTrackBarEx():m_hbmLine(NULL),m_hbmThumb(NULL){m_sizeLine.cx=m_sizeLine.cy=m_sizeThumb.cx=m_sizeThumb.cy=0;}
	~RingTrackBarEx();
	
	void SetSkin(UINT idLine,UINT idThumb);
	
protected:
	LRESULT RingdowProc(HWND,RINGPARAMS);
	
private:
	HBITMAP m_hbmLine,m_hbmThumb;
	SIZE m_sizeLine,m_sizeThumb;
};

class RingEditEx:public RingEdit
{
public:
	RingEditEx():m_bShowTip(TRUE),m_rm(NULL){}
	~RingEditEx(){}

	void SetSkin(UINT uidImg);
	void UpdateHSL(UINT uidImg,int h,int s,int l);

protected:
	LRESULT RingdowProc(HWND,RINGPARAMS);
	LRESULT OnNCPaint();
	void OnNCLButtonDown(RINGPARAMS& param);

private:
	BOOL m_bShowTip;
	RingCoolMenu* m_rm;
	RingDIB m_dibSrc;
	
};

class RingTabEx:public RingTab
{
public:
	RingTabEx():m_nHot(-1){}
	~RingTabEx(){}

	void SetSkin(UINT uBkg,UINT uIcon);
	void UpdateHSL(UINT uBkg,UINT uIcon,int h,int s,int l);

protected:
	LRESULT RingdowProc(HWND,RINGPARAMS);
	LRESULT OnPaint(RINGPARAMS&);

private:
	RingDIB m_dibBkgSrc,m_dibIcons,m_dibTab;
	int m_nHot;
};

class RingListBoxEx:public RingListBox
{
public:
	RingListBoxEx():m_nHot(-1),m_bTrack(FALSE),m_btn(NULL){}
	~RingListBoxEx(){}

	int GetHotItem(){return m_nHot;}
	void InitMailButton(UINT uId);
	void DrawMailButton(RingDIB* dib,BOOL bHot,int x,int y);
	void DrawMailButtonHot();

protected:
	LRESULT RingdowProc(HWND,RINGPARAMS);
	void ReDrawItem(int nIndex);

private:
	int m_nHot;
	BOOL m_bTrack;
	RingStatic* m_btn;
	RingDIB m_dib;
};

BEGIN_SETUPMAINWINDOW(IS_WINDOW)
	BEGIN_DEF_VAR(NEED_INIT)
		HRGN m_hrgn;
		HPEN m_pen;
		HBITMAP m_hBmMenuSel;
		int m_nCurWhere,m_nCurSysCmd,m_nSelTab;
		BOOL m_bInCapture;
		RECT m_rcUserBtn,m_rcUserSign,m_rcToolTop;
		RingEdit* m_editSign;
		RingToolBar *m_barbot;
		RingToolTip *m_tip;
		RingCoolMenu* m_rm;		
		ringINI m_ri;
		RingDIB m_dibBkg,m_dibBanner,m_dibBtnRc,m_dibNCBtns,m_dibCaption,m_dibUser,m_dibBot,m_dibBtnState;
		RingDIB m_dibUserBanner,m_dibHoverBtn,m_dibTatoo,m_dibToolTop,m_dibMenuBkg,m_dibMenuSel;
	END_DEF_VAR

	//绘制用户名，个性签名
	void MakeUserBanner(LPCTSTR lpsName,LPCTSTR lpsSign);
	//检测鼠标位置
	int HitTest(RINGPARAMS& param);
	//检测绘制按钮
	void CheckAndDrawButtons(int nWhich,int nOffset);
	//绘制三态系统按钮
	void DrawNCButton(int nIdx,int offset);
	//绘制工具栏按钮
	void DrawToolButton(int nIdx,BOOL bDrawNormal);
	int DrawToolTopBtn(int nIdx,BOOL bDrawNormal,LPRECT lprc);
	int DrawToolRightBtn(int nIdx,BOOL bDrawNormal,LPRECT lprc);
	//绘制用户头像旁按钮
	void DrawUserButton(BOOL bSign,BOOL bDrawNormal);
	//辅助函数，绘制按钮高亮和按下状态
	void DrawButtonState(RingDIB* dest,BOOL bPushed,int x,int y,int w,int h);
	//界面调色
	void UpdateHSL();
	void UpdateHSL(int h,int s,int l);
	void UpdateBottomTool();
	//更新客户区窗口尺寸及位置
	void UpdateClientWndPos();
		
	BEGIN_DEFMSG
		DEFMSG(WM_CREATE)
		DEFMSG(WM_ERASEBKGND)
		DEFMSG(WM_SIZE)
		DEFMSG(WM_MOVE)
		DEFMSG(WM_GETMINMAXINFO)
		DEFMSG(WM_NCCALCSIZE)
		DEFMSG(WM_NCPAINT)
		DEFMSG(WM_PAINT)
		DEFNOTIFY(NM_CUSTOMDRAW)
		DEFMSG(WM_ENTERSIZEMOVE)
		DEFMSG(WM_EXITSIZEMOVE)
		DEFMSG(WM_LBUTTONDBLCLK)
		DEFMSG(WM_LBUTTONDOWN)
		DEFMSG(WM_MOUSEMOVE)
		DEFMSG(WM_LBUTTONUP)
		DEFMSGEX(OnClickTaskIcon)		
		DEFCMD(OnShowWindow)
		DEFCMD(OnChangeSign)
		DEFCMD(OnExit)
		DEFMSG(WM_DESTROY)
	END_DEFMAINMSG
END_SETUPMAINWINDOW

//界面设置窗口
BEGIN_SETUPWINDOW(WndUIOp,IS_WINDOW)
	BEGIN_DEF_VAR(NEED_INIT)
		HPEN m_pen;
		RingStatic *m_stHead;
	END_DEF_VAR

	BOOL SetNavChild(LPCTSTR lpszCaption,HWND hWnd);

	BEGIN_DEFMSG
		DEFMSG(WM_ACTIVATE)
		DEFMSG(WM_NCCALCSIZE)
		DEFMSG(WM_NCPAINT)
		DEFCMD(OnSelTab)
		DEFMSGEX(OnHideClose)
		DEFMSG(WM_DESTROY)
		DEFMSG(WM_CREATE)
	END_DEFMSG(WndUIOp)
END_SETUPWINDOW(WndUIOp)

BEGIN_SETUPWINDOW(DlgUIColor,IS_DIALOG)
	BINDID(IDD_UICONFIG)
	BEGIN_DEF_VAR(NO_INIT)
		RingStatic* m_stColor[8];
		RingTrackBarEx *m_barHue,*m_barSum,*m_barLum,*m_barAlpha;
		RingToolTip* m_tip;
		int m_hue,m_sum,m_lum;
	END_DEF_VAR
	
	BEGIN_DEFMSG
		DEFMSG(WM_INITDIALOG)
		DEFMSG(WM_HSCROLL)
		DEFMSG(WM_DESTROY)
		DEFCMD(OnChooseColor)
	END_DEFMSG(DlgUIColor)
END_SETUPWINDOW(DlgUIColor)

BEGIN_SETUPWINDOW(DlgUITatoo,IS_DIALOG)
	BINDID(IDD_TATOOCONFIG)
	BEGIN_DEF_VAR(NO_INIT)
		RingStatic* m_stTatoo[9];
		RingToolTip* m_tip;
		int m_nTatooCnt,m_nCurrTatoo;
		HPEN m_pen;
	END_DEF_VAR
	
	BEGIN_DEFMSG
		DEFMSG(WM_INITDIALOG)
		DEFMSG(WM_PAINT)
		DEFMSG(WM_DESTROY)
		DEFCMD(OnSelTatoo)
		DEFCMD(OnSel1)
		DEFCMD(OnSel2)
		DEFCMD(OnSel3)
		DEFCMD(OnSel4)
		DEFCMD(OnSel5)
		DEFCMD(OnSel6)
		DEFCMD(OnSel7)
		DEFCMD(OnSel8)
		DEFCMD(OnSel9)
	END_DEFMSG(DlgUITatoo)
END_SETUPWINDOW(DlgUITatoo)

//QQ按钮窗口
BEGIN_SETUPWINDOW(WndQQButton,IS_WINDOW)
	BEGIN_DEF_VAR(NO_INIT)
		RingStatic *m_btn,*m_btnQQ;
		RingToolTip *m_tip;
		RingDIB m_dibBkg,m_dibQQ,m_dibArrBtn,m_dibQQBtn;
		BOOL m_bIsSideToolHide;
	END_DEF_VAR

	void UpdateHSL(int h=-1,int s=-1,int l=-1);

	BEGIN_DEFMSG
		DEFMSG(WM_LINKHOVER)
		DEFMSG(WM_LINKLEAVE)
		DEFMSG(WM_CREATE)
		DEFMSG(WM_PAINT)
		DEFCMD(OnSwitchSideTab)
	END_DEFMSG(WndQQButton)
END_SETUPWINDOW(WndQQButton)

//客户区窗口
BEGIN_SETUPWINDOW(WndClient,IS_WINDOW)
	BEGIN_DEF_VAR(NEED_INIT)
		int m_nCurrTab;
		RingEditEx *m_edSearch;
		RingToolBar *m_sidebar;
		RingTabEx *m_tab;
		RingListBoxEx *m_list[3];
		RingCoolMenu* m_rm;
		RingDIB m_dibBkg,m_dibBtnState,m_dibBtnBorder,m_dibList,m_dibListSrc,m_dibHorzArr,m_dibUsers;
		ringStr m_str;
	END_DEF_VAR

	void UpdateHSL(int h=-1,int s=-1,int l=-1);
	//生成QQ好友，群，最近联系人3个列表
	void MakeFriendList();
	void MakeGroupList();
	void MakeRecentList();
	//列表自绘函数
	void DrawListTitle(int nIndex,LPDRAWITEMSTRUCT lpdraw,int w,int h);
	void DrawUserList(RingListBoxEx* list,LPDRAWITEMSTRUCT lpdraw,int w,int h);
	//列表标题点击的处理
	BOOL ExpandList(RingListBox* list,int nIndex);

	BEGIN_DEFMSG
		DEFNOTIFY(NM_CUSTOMDRAW)
		DEFNOTIFY(TCN_SELCHANGE)
		DEFMSG(WM_DRAWITEM)
		DEFMSG(WM_SIZE)
		DEFMSG(WM_CREATE)
		DEFMSG(WM_LINKHOVER)
		DEFMSG(WM_LINKLEAVE)
		DEFMSGEX(OnTabMenuPop)
		DEFCMD(OnUserListClick)
		DEFCMD(OnGroupListClick)
	END_DEFMSG(WndClient)
END_SETUPWINDOW(WndClient)

#endif
