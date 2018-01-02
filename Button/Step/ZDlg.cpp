// ZDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Step.h"
#include "ZDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ZDlg dialog

ZDlg::ZDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ZDlg::IDD, pParent)
{
	//function SetImage() can be used any where. 
	//just for test.
	btn_Resize0.SetImage(BMP_RESIZE0);
	CString csGif;
	char sz[1024];
	::GetModuleFileName(0,sz,1000);
	char*ps=strrchr(sz,'\\');
	*ps=0;
	csGif=sz;
	csGif+="\\img\\";
	btn_Gif.SetImage(csGif+"img.gif",RGB(0,0,0));

	//--------------------------------
	i_MessageCount=0;
	//{{AFX_DATA_INIT(ZDlg)
	//}}AFX_DATA_INIT
}

void ZDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ZDlg)
	DDX_Control(pDX, STA_INF, sta_Inf);
	DDX_Control(pDX, BTN_JPG, btn_Jpg);
	DDX_Control(pDX, BTN_GIF, btn_Gif);
	DDX_Control(pDX, BTN_BMP, btn_Bmp);
	DDX_Control(pDX, BTN_RESRAISED, btn_Resize1);
	DDX_Control(pDX, BTN_RESSUNKEN, btn_Resize0);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(ZDlg, CDialog)
	//{{AFX_MSG_MAP(ZDlg)
	ON_BN_CLICKED(IDOK, On_IDOK)
	ON_BN_CLICKED(BTN_ENABLE, On_Enable)
	ON_BN_CLICKED(BTN_RESSUNKEN, On_BtnResSunken)
	ON_BN_CLICKED(BTN_RESRAISED, On_BtnResRaised)
	ON_BN_CLICKED(BTN_WEAKER, On_BtnWeaker)
	ON_BN_CLICKED(BTN_FOCUS, On_BtnFocus)
	ON_BN_CLICKED(BTN_BMP, On_BtnBmp)
	ON_BN_CLICKED(BTN_GIF, On_BtnGif)
	ON_BN_CLICKED(BTN_JPG, On_BtnJpg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

void ZDlg::On_IDOK() 
{
}

BOOL ZDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	btn_Resize1.SetImage(BMP_RESIZE0,"Disabled image is unnormal : raised",RGB(192,192,192),1,0);

	btn_Resize0.SetToolTip("Disabled image is normal : sunken");

	CString csGif;
	char sz[1024];
	::GetModuleFileName(0,sz,1000);
	char*ps=strrchr(sz,'\\');
	*ps=0;
	csGif=sz;
	csGif+="\\img\\";

	COLORREF clrBk=RGB(0,0,0);
	btn_Bmp.SetImage(csGif+"img.bmp","I am bitmap file",clrBk);
	btn_Jpg.SetImage(csGif+"img.jpg",clrBk);

	btn_Gif.SetToolTip("I am gif file");
	btn_Jpg.SetToolTip("I am jpg file");
	return 1;
}


void ZDlg::On_Enable() 
{
	BOOL b=!btn_Resize0.IsWindowEnabled();
	ButtonMine*pb[]=
	{
		&btn_Resize0,
		&btn_Resize1,
		&btn_Bmp,
		&btn_Gif,
		&btn_Jpg,
	};
	int i,iNum=sizeof(pb)/sizeof(pb[0]);
	for(i=0;i<iNum;i++)
	{
		pb[i]->EnableWindow(b);
	}
}

void ZDlg::On_BtnWeaker() 
{
	BOOL b=!btn_Resize0.GetWeaker();
	ButtonMine*pb[]=
	{
		&btn_Resize0,
		&btn_Resize1,
		&btn_Bmp,
		&btn_Gif,
		&btn_Jpg,
	};
	int i,iNum=sizeof(pb)/sizeof(pb[0]);
	for(i=0;i<iNum;i++)
	{
		pb[i]->SetWeaker(b);
	}
}

void ZDlg::On_BtnFocus() 
{
	BOOL b=!btn_Resize0.GetShowFocus();
	ButtonMine*pb[]=
	{
		&btn_Resize0,
		&btn_Resize1,
		&btn_Bmp,
		&btn_Gif,
		&btn_Jpg,
	};
	int i,iNum=sizeof(pb)/sizeof(pb[0]);
	for(i=0;i<iNum;i++)
	{
		pb[i]->SetShowFocus(b);
	}
}

void ZDlg::On_BtnResSunken() 
{
	P_DispInf("resource button (disable as sunken)");	
}

void ZDlg::On_BtnResRaised() 
{
	P_DispInf("resource button (disable as raised)");	
}

void ZDlg::On_BtnBmp() 
{
	P_DispInf("bitmap button");	
}

void ZDlg::On_BtnGif() 
{
	P_DispInf("gif button");	
}

void ZDlg::On_BtnJpg() 
{
	P_DispInf("jpg button");	
}

void ZDlg::P_DispInf(CString csBtn)
{
	i_MessageCount++;
	CString cs;
	cs.Format("message count : %d",i_MessageCount);
	sta_Inf.SetWindowText("From "+csBtn+", "+cs);
}
