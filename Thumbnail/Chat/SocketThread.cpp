// SocketThread.cpp : 实现文件
//

#include "stdafx.h"
#include "Chat.h"
#include "SocketThread.h"
#include "TcpChessSocket.h"
#include "ChessDlg.h"
extern CSocket m_socket;
extern CTcpChessSocket m_con_socket;
extern CChessDlg *ppdlg;

// CSocketThread

IMPLEMENT_DYNCREATE(CSocketThread, CWinThread)

CSocketThread::CSocketThread()
{
}

CSocketThread::~CSocketThread()
{
}

BOOL CSocketThread::InitInstance()
{
	// TODO: 在此执行任意逐线程初始化
	m_socket.Listen(1) ;
	ppdlg->Accept();
	
	return TRUE;
}

int CSocketThread::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CSocketThread, CWinThread)
END_MESSAGE_MAP()


// CSocketThread 消息处理程序
