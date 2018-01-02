// TcpChessSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "Chat.h"
#include "TcpChessSocket.h"
#include "ChessDlg.h"
// CTcpChessSocket

CTcpChessSocket::CTcpChessSocket()
{
}

CTcpChessSocket::~CTcpChessSocket()
{
}


// CTcpChessSocket 成员函数

void CTcpChessSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	CChessDlg * pdlg = (CChessDlg *) hwnd;
	pdlg->OnReceive();
	CSocket::OnReceive(nErrorCode);
}
void CTcpChessSocket::SetHwnd(HWND hw)
{
	hwnd = hw ;
}

void CTcpChessSocket::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	CSocket::OnAccept(nErrorCode);
}

void CTcpChessSocket::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	CChessDlg * pdlg = (CChessDlg *) hwnd;
	pdlg->SocketClose();
	CSocket::OnClose(nErrorCode);
}
