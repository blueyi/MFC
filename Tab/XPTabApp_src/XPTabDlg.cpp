/***********************************************************************************************************/
// XPTabDlg.cpp : implementation file
/***********************************************************************************************************/
#include "StdAfx.h"
#include "Resource.h"
#include "XPTabDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LPCSTR g_szProfile= "XPTabDlg";

/////////////////////////////////////////////////////////////////////////////
// CXPTabDlg dialog

CXPTabDlg::CXPTabDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXPTabDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXPTabDlg)
	m_bTabExtended = 0;
	m_eTabOrientation =0;
	//}}AFX_DATA_INIT
	
	CWinApp* pApp=AfxGetApp();
	m_hIcon = pApp->LoadIcon(IDR_MAINFRAME);
	// Optional: restore state from the registry
	if(!IsThemeActiveXP()) m_bTabExtended=FALSE;
	else m_bTabExtended=pApp->GetProfileInt(g_szProfile, "TabExtended",TRUE);
	m_eTabOrientation  =pApp->GetProfileInt(g_szProfile, "TabOrientation",e_tabBottom);
}
/////////////////////////////////////////////////////////////////////////////
void CXPTabDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CXPTabDlg)
    DDX_Control(pDX, IDC_TAB_XP, m_tabCtrl);
    DDX_Radio(pDX, IDC_TAB_STANDARD, m_bTabExtended);
    DDX_Radio(pDX, IDC_TAB_TOP, m_eTabOrientation);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_CUSTOM1, m_tab);
}
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CXPTabDlg, CDialog)
	//{{AFX_MSG_MAP(CXPTabDlg)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_TAB_STANDARD, OnTabExtended)
	ON_BN_CLICKED(IDC_TAB_EXTENDED, OnTabExtended)
	ON_BN_CLICKED(IDC_TAB_TOP,   OnTabOrientation)
	ON_BN_CLICKED(IDC_TAB_BOTTOM,OnTabOrientation)
	ON_BN_CLICKED(IDC_TAB_LEFT,  OnTabOrientation)
	ON_BN_CLICKED(IDC_TAB_RIGHT, OnTabOrientation)
	//}}AFX_MSG_MAP
	ON_NOTIFY_EX(TTN_NEEDTEXT,0,OnNeedText)	// Optional tab tootips
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
#define IDM_ABOUTBOX					0x0010

// CXPTabDlg message handlers
BOOL CXPTabDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	//--------------------------
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);	// Add "About..." menu item to system menu.
	ASSERT(IDM_ABOUTBOX < 0xF000);						// IDM_ABOUTBOX must be in the system command range.
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{	CString strAboutMenu((LPCTSTR)IDS_ABOUTBOX);
		if(!strAboutMenu.IsEmpty())
		{	pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
			pSysMenu->RemoveMenu(SC_MAXIMIZE, MF_BYCOMMAND);
			pSysMenu->RemoveMenu(SC_SIZE, MF_BYCOMMAND);
	}	}
	SetIcon(m_hIcon, TRUE);					// Set big icon
	SetIcon(m_hIcon, FALSE);				// Set small icon
	//--------------------------
	m_tabCtrl.InitImageList(IDB_TABIMAGES);	// only necessary to call if tabs have images

	m_tabCtrl.InsertItem(0, "Tab 1", 0);	// add some test pages to the tab
	m_tabCtrl.InsertItem(1, "Tab 2", 1);
	m_tabCtrl.InsertItem(2, "Tab 3", 2);
	m_tabCtrl.InsertItem(3, "Tab 4", 3);
	
	TabExtended(m_bTabExtended);			// Switching on/off windows tab extension (default is "on")
	//--------------------------
	// Optional: for Themes XP dialogs: enable Themes dialog texture
	EnableThemeDialogTexture(GetSafeHwnd());


    //////////////////////////////////////////////////////////////////////////

    m_tab.ModifyStyle(0, WS_VISIBLE | CTCS_TOP | CTCS_AUTOHIDEBUTTONS | CTCS_CONTAINER);	

    //setup tab control colors
    TabItemColors ticColors;

    //get colors..
    m_tab.GetColors(&ticColors);

    //modify them..
    ticColors.crBkgActive=RGB_AVERAGE(GetSysColor(COLOR_ACTIVECAPTION), RGB(255, 255, 255));
    ticColors.crTxtActive=RGB(0, 0, 0);
    ticColors.crBkgInactive=GetSysColor(COLOR_ACTIVECAPTION);
    ticColors.crTxtInactive=RGB_AVERAGE(GetSysColor(COLOR_ACTIVECAPTION), GetSysColor(COLOR_CAPTIONTEXT));
    ticColors.crWndBkg=GetSysColor(COLOR_ACTIVECAPTION);

    //..and write back
    m_tab.SetColors(&ticColors);

    //create tabs and setup page colors

    //create the scanner dlg
    m_pTabDialog1=new CTabDialog1();
    m_pTabDialog1->Create(CTabDialog1::IDD, this);
    //..setup colors
    //m_pTabDialog1->SetBkgColor(RGB_AVERAGE(GetSysColor(COLOR_ACTIVECAPTION), RGB(255, 255, 255)));
    //m_pTabDialog1->SetFrgColor(RGB(0, 0, 0));
    //..add tab to tab control & dialog to container with the same call
    m_tab.AddDialog(0, _T("概率图"), m_pTabDialog1);

    //create the options dlg
    m_pTabDialog2=new CTabDialog2();
    m_pTabDialog2->Create(CTabDialog2::IDD, this);
    //..setup colors
    //m_pTabDialog2->SetBkgColor(RGB_AVERAGE(GetSysColor(COLOR_ACTIVECAPTION), RGB(255, 255, 255)));
    //m_pTabDialog2->SetFrgColor(RGB(0, 0, 0));
    //..add tab to tab control & dialog to container with the same call
    m_tab.AddDialog(1, _T("交易情景分析"), m_pTabDialog2);


	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// enable/disable tab control to be extended
void CXPTabDlg::TabExtended(BOOL bTabExtended)
{
	m_tabCtrl.SetExtended(bTabExtended);
	TabOrientation((ETabOrientation)m_eTabOrientation);	// update orientation
	RedrawTab();
}
/////////////////////////////////////////////////////////////////////////////
// change tab control orientation
void CXPTabDlg::TabOrientation(ETabOrientation eTabOrientation) 
{
	m_tabCtrl.ModifyStyle(TCS_VERTICAL|TCS_BOTTOM|TCS_MULTILINE,(eTabOrientation&1?TCS_BOTTOM:0) | 
					(eTabOrientation>e_tabBottom?(TCS_VERTICAL|(m_bTabExtended && IsThemeActiveXP()?0:TCS_MULTILINE)):0));
	CWnd* pWnd=GetDlgItem(IDC_TAB_EXTENDED);
	if(pWnd) pWnd->EnableWindow(IsThemeActiveXP()?TRUE:FALSE);
}
/////////////////////////////////////////////////////////////////////////////
void CXPTabDlg::RedrawTab() 
{
	CWnd* pWnd=GetDlgItem(IDC_TAB_XP);
	if(pWnd)
	{	CRect rcInv;
		pWnd->GetWindowRect(rcInv); ScreenToClient(rcInv);
		InvalidateRect(rcInv);
	}
	else Invalidate();
}
/////////////////////////////////////////////////////////////////////////////
void CXPTabDlg::OnTabExtended() 
{
	BOOL bTabExtendedOld=m_bTabExtended;
	UpdateData();
	if(bTabExtendedOld!=m_bTabExtended)
		TabExtended(m_bTabExtended);
}
/////////////////////////////////////////////////////////////////////////////
void CXPTabDlg::OnTabOrientation() 
{
	UpdateData();
	TabOrientation((ETabOrientation)m_eTabOrientation);
	RedrawTab();
}
//////////////////////////////////////////////////////////////////////////////
// Optional: tab tootips
BOOL CXPTabDlg::OnNeedText(UINT id, NMHDR * pNotifyStruct, LRESULT * result)
{
	static CString c_sLastToolTip;
    TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNotifyStruct;
    UINT nID =pNotifyStruct->idFrom;

    if (pTTT->uFlags & TTF_IDISHWND)   // idFrom is actually the HWND of the tool
        nID = ::GetDlgCtrlID((HWND)nID);
    //if(nID!=IDC_TAB_XP) return FALSE;
    	
	TCHITTESTINFO hti;	hti.flags=0;
	::GetCursorPos(&hti.pt); m_tabCtrl.ScreenToClient(&hti.pt);
	int ixItem=m_tabCtrl.HitTest(&hti);
    if(ixItem<0)
		return FALSE;
		
	TC_ITEM tci; tci.mask=TCIF_TEXT;
	tci.pszText=c_sLastToolTip.GetBuffer(128);
	tci.cchTextMax=127;
	m_tabCtrl.GetItem(ixItem,&tci);
	c_sLastToolTip.ReleaseBuffer();
    if(c_sLastToolTip.GetLength()<0)
		return FALSE;

	pTTT->hinst=NULL;
	pTTT->lpszText=(char*)(LPCSTR)c_sLastToolTip;
	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// Optional: save state to the registry
BOOL CXPTabDlg::DestroyWindow() 
{
	CWinApp* pApp=AfxGetApp();
	pApp->WriteProfileInt(g_szProfile, "TabExtended",	m_bTabExtended);
	pApp->WriteProfileInt(g_szProfile, "TabOrientation",m_eTabOrientation);
	return CDialog::DestroyWindow();
}
/////////////////////////////////////////////////////////////////////////////
void CXPTabDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
		CDialog::OnSysCommand(nID, lParam);
}
/***********************************************************************************************************/
// CAboutDlg dialog used for App About
/***********************************************************************************************************/
CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}
/////////////////////////////////////////////////////////////////////////////
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}
/////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/***********************************************************************************************************/
// Helper functions
/***********************************************************************************************************/
// constant string definitions here (or you can put it into resource string table)
#define IDS_UTIL_UXTHEME        "UxTheme.dll"
#define IDS_UTIL_THEMETEXTURE   "EnableThemeDialogTexture"
/////////////////////////////////////////////////////////////////////////////
void EnableThemeDialogTexture(HWND hwndDlg)
{
	HINSTANCE hDll=LoadLibrary(CString((LPCTSTR)IDS_UTIL_UXTHEME));							// 'UxTheme.dll'
	if(hDll==NULL)
		return;	// the DLL won't be available on anything except Windows XP
	ULONG (PASCAL *lpfnEnableTheme)(HWND, DWORD);
	(FARPROC&)lpfnEnableTheme=GetProcAddress(hDll,CString((LPCTSTR)IDS_UTIL_THEMETEXTURE));	// 'EnableThemeDialogTexture'
	if(lpfnEnableTheme)
		lpfnEnableTheme(hwndDlg, 6);		// ETDT_ENABLETAB = (ETDT_ENABLE | ETDT_USETABTEXTURE) = (2|4) = 6
	else ASSERT(FALSE);
	FreeLibrary(hDll);
}
/***********************************************************************************************************/
//
/***********************************************************************************************************/
