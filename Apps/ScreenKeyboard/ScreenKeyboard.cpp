// ScreenKeyboard.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "ScreenKeyboard.h"
#include "ScreenKeyboardDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CScreenKeyboardApp

BEGIN_MESSAGE_MAP(CScreenKeyboardApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CScreenKeyboardApp 构造

CScreenKeyboardApp::CScreenKeyboardApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CScreenKeyboardApp 对象

CScreenKeyboardApp theApp;


// CScreenKeyboardApp 初始化

BOOL CScreenKeyboardApp::InitInstance()
{
	if(IsProgrameRunning()) return FALSE; //如果有一个版本运行就关闭

	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();


	CScreenKeyboardDlg dlg;
	m_pMainWnd = &dlg;
//	dlg.Create(IDD_SCREENKEYBOARD_DIALOG);
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO：在此放置处理何时用“确定”来关闭
		//对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO：在此放置处理何时用“取消”来关闭
		//对话框的代码
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	// 而不是启动应用程序的消息泵。
	return FALSE;
}


BOOL CScreenKeyboardApp::IsProgrameRunning(void)
{
	/////////////////////////////////////////////////////////////
	HANDLE hSem = CreateSemaphore(NULL, 1, 1, m_pszAppName); 
	// 信号量已存在 
	// 信号量存在，则程序已有一个实例运行 
	if (GetLastError() == ERROR_ALREADY_EXISTS) 
	{ 
		// 关闭信号量句柄 
		CloseHandle(hSem); 
		// 寻找先前实例的主窗口 
		HWND hWndPrevious = ::GetWindow(::GetDesktopWindow(),GW_CHILD); 
		while (::IsWindow(hWndPrevious)) 
		{ 
			// 检查窗口是否有预设的标记? 
			// 有，则是我们寻找的主窗 
			if (::GetProp(hWndPrevious, m_pszExeName)) //在OnInitDialog()中设置这个属性
			{ 
				// 主窗口已最小化，则恢复其大小 
				if (::IsIconic(hWndPrevious)) 
					::ShowWindow(hWndPrevious,SW_RESTORE); 

				// 将主窗激活 
				::SetForegroundWindow(hWndPrevious); 

				// 将主窗的对话框激活 
				::SetForegroundWindow( 
					::GetLastActivePopup(hWndPrevious)); 
				// 退出本实例 
				return TRUE; 
			} 
			// 继续寻找下一个窗口 
			hWndPrevious = ::GetWindow(hWndPrevious,GW_HWNDNEXT);
		} 
		// 前一实例已存在，但找不到其主窗 
		// 可能出错了 
		// 退出本实例 
		return TRUE; 
	} 
	return FALSE;
}