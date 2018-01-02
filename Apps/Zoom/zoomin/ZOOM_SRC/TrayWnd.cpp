// TrayWnd.cpp : implementation file
//

#include "stdafx.h"
#include <afxpriv.h>
#include "resource.h"
#include "KeyHook.h"
#include "MainSheet.h"
#include "TrayWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CTrayWnd, CFrameWnd)
BEGIN_MESSAGE_MAP(CTrayWnd, CFrameWnd)
	ON_MESSAGE(WM_MY_TRAY_NOTIFICATION, OnTrayNotification)
	//{{AFX_MSG_MAP(CTrayWnd)
	ON_COMMAND(ID_TRAY_EXITZOOMIN, OnTrayExit)
	ON_COMMAND(ID_TRAY_CHANGESETTINGS, OnTrayChangeSettings)
	ON_WM_CREATE()
	ON_COMMAND(ID_TRAY_ACTIVATE, OnTrayActivate)
	ON_UPDATE_COMMAND_UI(ID_TRAY_ACTIVATE, OnUpdateTrayActivate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CTrayWnd::CTrayWnd()
{
	m_pSheet = new CMainSheet(this);
}

CTrayWnd::~CTrayWnd()
{
	delete m_pSheet;
}

int CTrayWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	HICON myIcon = AfxGetApp()->LoadIcon(IDI_ZOOMIN_ENABLED);
	SetIcon(myIcon, TRUE);
	KHAttachHookDLL(GetSafeHwnd());
	KHEnableZoomWindow(IsValidHotKey());

	// Initialize Tray Data

	memset(&m_trayData, 0 , sizeof(NOTIFYICONDATA));
	m_trayData.cbSize = sizeof(NOTIFYICONDATA);
	m_trayData.hWnd = GetSafeHwnd();
	m_trayData.uID = IDR_MENU;
	m_trayData.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	m_trayData.uCallbackMessage = WM_MY_TRAY_NOTIFICATION;
	m_trayData.hIcon = AfxGetApp()->LoadIcon(
		IsValidHotKey() ? IDI_ZOOMIN_ENABLED : IDI_ZOOMIN_DISABLED);
	AfxLoadString(AFX_IDS_APP_TITLE, m_trayData.szTip,
		sizeof(m_trayData.szTip));
	VERIFY( Shell_NotifyIcon(NIM_ADD, &m_trayData) );
	return 0;
}

BOOL CTrayWnd::IsValidHotKey()
{
	return AfxGetApp()->GetProfileInt("", "wKey", 192) != 0;
}

LRESULT CTrayWnd::OnTrayNotification(WPARAM uID, LPARAM lEvent)
{
	if (uID != IDR_MENU || (lEvent != WM_RBUTTONUP
		&& lEvent != WM_LBUTTONDBLCLK))
	{
		return 0;
	}

	CMenu* pSubMenu;
	if (!(pSubMenu = GetMenu()->GetSubMenu(0)))
		return 0;

	if (lEvent != WM_RBUTTONUP)
		SendMessage(WM_COMMAND, pSubMenu->GetMenuItemID(0), 0);
	else
	{
		SetMenuDefaultItem(pSubMenu->m_hMenu, 0, TRUE);

		CString strMenuText;
		strMenuText.LoadString(KHIsWindowVisible() ?
			IDS_HIDEWINDOW : IDS_SHOWWINDOW);
		pSubMenu->ModifyMenu(ID_TRAY_ACTIVATE, MF_BYCOMMAND,
			ID_TRAY_ACTIVATE, strMenuText);

		CPoint mouse;
		GetCursorPos(&mouse);
		SetForegroundWindow();	
		TrackPopupMenu(pSubMenu->m_hMenu, 0, mouse.x, mouse.y,
			0, GetSafeHwnd(), NULL);

	}

	return TRUE;
}

void CTrayWnd::OnTrayExit() 
{
	if (m_pSheet->GetSafeHwnd())
	{
		m_pSheet->EndDialog(IDCANCEL);
		PostMessage(WM_COMMAND, ID_TRAY_EXITZOOMIN);
		return;
	}

	Shell_NotifyIcon(NIM_DELETE, &m_trayData);
	KHAttachHookDLL(NULL);
	DestroyWindow();
}

void CTrayWnd::OnTrayChangeSettings() 
{
	if (KHIsWindowVisible())
		OnTrayActivate();

	if (m_pSheet->GetSafeHwnd())
	{
		SetForegroundWindow();	
		m_pSheet->SetFocus();
		return;
	}

	KHEnableZoomWindow(FALSE);
	m_trayData.hIcon = AfxGetApp()->LoadIcon(IDI_ZOOMIN_DISABLED);
	VERIFY( Shell_NotifyIcon(NIM_MODIFY, &m_trayData) );

	m_pSheet->DoModal();

	BOOL bEnable = IsValidHotKey();
	UINT resID = bEnable ? IDI_ZOOMIN_ENABLED : IDI_ZOOMIN_DISABLED;
	m_trayData.hIcon = AfxGetApp()->LoadIcon(resID);
	VERIFY( Shell_NotifyIcon(NIM_MODIFY, &m_trayData) );
	KHEnableZoomWindow(bEnable);
}

void CTrayWnd::OnTrayActivate() 
{
	KHShowZoomWindow(!KHIsWindowVisible());
	SetActiveWindow();
	SetFocus();
}

void CTrayWnd::OnUpdateTrayActivate(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_pSheet->GetSafeHwnd());	
}
