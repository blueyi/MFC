// MacSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "Chat.h"
#include "MacSocket.h"
#include "MacDlg.h"
// CMacSocket
extern CMacDlg *pdlg;

CMacSocket::CMacSocket()
{
}

CMacSocket::~CMacSocket()
{
}


// CMacSocket 成员函数

void CMacSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	pdlg->OnReceive();

	CSocket::OnReceive(nErrorCode);
}
