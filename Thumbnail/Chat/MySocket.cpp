// MySocket.cpp : 实现文件
//

#include "stdafx.h"
#include "Chat.h"
#include "MySocket.h"
#include "ChatDlg.h"

// CMySocket

CMySocket::CMySocket()
{

}

CMySocket::~CMySocket()
{
}


// CMySocket 成员函数

void CMySocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	CChatDlg *pdlg = (CChatDlg*)m_hwnd;
	pdlg->OnReceive();
	CAsyncSocket::OnReceive(nErrorCode);
}
void CMySocket::SetHWnd(HWND hwnd)
{
	m_hwnd = hwnd;
}
