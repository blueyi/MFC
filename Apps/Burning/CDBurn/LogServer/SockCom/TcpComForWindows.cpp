// MriSeqComInterface.cpp: implementation of the CTcpComForWindows class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TcpComForWindows.h"
#include "..\\CommonDefine.h"
#include "..\\CommonDefineFunc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTcpComForWindows::CTcpComForWindows( BYTE nClientOrServer, short nPort, char* cIPAddr, HWND hWnd, UINT nMessageID )
{
	m_nClientOrServer = nClientOrServer;

	m_hWnd = hWnd;
	m_nMessageID = nMessageID;
	
	m_nPort = nPort;
	m_sIPAddr = cIPAddr;	

	if ( m_nClientOrServer == TYPE_SERVER )
	{
		StartListen();
	}
	else if ( m_nClientOrServer == TYPE_CLIENT )
	{
		ConnectServer();
	}
}

CTcpComForWindows::~CTcpComForWindows()
{
}

int CTcpComForWindows::ConnectServer()
{
	if ( m_nClientOrServer != TYPE_CLIENT )
	{
		return 0;
	}


	struct  sockaddr_in serverAddr;
	WSADATA wsd;
		
	//初始化SOCKET环境
	m_hClientSocket = NULL;
	m_nErrorCode    = 0;
	if (WSAStartup(MAKEWORD(2,2),&wsd) !=0)
	{
		m_nErrorCode = -1;      //Not install the correct libary of SOCKET 2.0
		return m_nErrorCode;
	}
    //创建Client SOCKET
    m_hClientSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
	if (m_hClientSocket == SOCKET_ERROR)
	{
		m_nErrorCode    = -2;      //Failure to create SOCKET
		WSACleanup();
		m_hClientSocket = NULL;
		return m_nErrorCode ;
	}
	serverAddr.sin_family      = AF_INET ;
    serverAddr.sin_port        = htons(m_nPort);
	serverAddr.sin_addr.s_addr = inet_addr(m_sIPAddr);
	
    int nConn = connect(m_hClientSocket,(sockaddr*)&serverAddr,sizeof(serverAddr));
	if (nConn != 0)
	{
		m_nErrorCode = -4;
		WSACleanup();
		m_hClientSocket = NULL;
		return m_nErrorCode;
	}
	WSAAsyncSelect(m_hClientSocket,m_hWnd,m_nMessageID,FD_ACCEPT|FD_CLOSE|FD_WRITE|FD_READ);
    return m_nErrorCode;
}

int CTcpComForWindows::StartListen()
{
	if ( m_nClientOrServer != TYPE_SERVER )
	{
		return 0;
	}

	
	struct  sockaddr_in local;
	WSADATA wsd;

	//初始化SOCKET环境
	m_hListener  = NULL;
	m_nErrorCode = 0;

	if (WSAStartup(MAKEWORD(2,2),&wsd) !=0)
	{
		m_nErrorCode = -1;      //Not install the correct libary of SOCKET 2.0
		return m_nErrorCode;
	}
	
    //创建监听SOCKET
    m_hListener = socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
	if (m_hListener == SOCKET_ERROR)
	{
		m_nErrorCode = -2;      //Failure to create SOCKET
		WSACleanup();
		m_hListener = NULL;
		return m_nErrorCode;
	}
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	local.sin_family      = AF_INET;
	local.sin_port        = htons(m_nPort);

	if (bind(m_hListener,(struct sockaddr*)&local,sizeof(local)) == SOCKET_ERROR)
	{
		m_hListener = NULL ;
		WSACleanup();
		m_nErrorCode = -3;      //Failure to Bind the socket.
		return m_nErrorCode ;
	}
	WSAAsyncSelect(m_hListener,m_hWnd,m_nMessageID,FD_ACCEPT|FD_CLOSE);
	listen(m_hListener,8);
	
	return m_nErrorCode;
}

int CTcpComForWindows::AcceptConn()
{
	struct sockaddr_in addr;
	int addrlen = sizeof(addr);
	
//	SOCKET m_hAcceptedSock = accept( m_hListener,NULL,NULL );
	SOCKET m_hAcceptedSock = accept( m_hListener, (struct sockaddr *)&addr, &addrlen );

	char* sAddr = inet_ntoa( addr.sin_addr );
	u_short nPortNum = ntohs( addr.sin_port );
	
	if (m_hAcceptedSock == INVALID_SOCKET)
	{
		OUT_LOG( "Request connection is INVALID_SOCKET" );
		::closesocket( m_hAcceptedSock );
		m_nErrorCode = -5 ;  //Failure to connect server.
		return m_nErrorCode;
	}
	
	
/*
	getpeername( m_hAcceptedSock, (struct sockaddr *)&addr, &addrlen );
	char* sAddr = inet_ntoa( addr.sin_addr );
	u_short nPortNum = ntohs( addr.sin_port );
*/
	CString sSockID;
	sSockID.Format( "%s : %d", sAddr, nPortNum );
	
/*
	m_mapConnectedSockIter = m_mapConnectedSock.find( sSockID/ *sAddr* / );
	if ( m_mapConnectedSockIter != m_mapConnectedSock.end() )
	{
		OUT_LOG( "Request connection from client(%s) has been established", sAddr );
//		::closesocket( m_hAcceptedSock );
//		::shutdown( m_hAcceptedSock, SD_BOTH );
		return 0;
	}
	else
	{
*/
		m_mapConnectedSock[ sSockID/*sAddr*/ ] = m_hAcceptedSock;
		OUT_LOG( "Established a connection for Client: %s; Port: %d", sAddr, nPortNum );
/*
	}
*/


	WSAAsyncSelect(m_hAcceptedSock,m_hWnd,m_nMessageID,FD_READ|FD_WRITE|FD_CLOSE);
	
	return 0;
}

int CTcpComForWindows::SendData(char* pBuff, DWORD dwLen)
{		
	int nDataLen = 0;

	if ( m_nClientOrServer == TYPE_CLIENT )
	{
		nDataLen = send(m_hClientSocket,pBuff,dwLen,NULL);
	}
	else if ( m_nClientOrServer == TYPE_SERVER )
	{
		for ( m_mapConnectedSockIter = m_mapConnectedSock.begin(); 
		m_mapConnectedSockIter != m_mapConnectedSock.end(); m_mapConnectedSockIter ++ )
		{
			nDataLen = send( m_mapConnectedSockIter->second, pBuff, dwLen, NULL );
			OUT_LOG( "Send data to host: %s", m_mapConnectedSockIter->first );
		}
	}
	
	return nDataLen;
}

int CTcpComForWindows::RecvData(char* pBuff, DWORD dwLen)
{
	int nDataLen = 0;

	if ( m_nClientOrServer == TYPE_CLIENT )
	{
		nDataLen = recv(m_hClientSocket,pBuff,dwLen,NULL);
	}
	else if ( m_nClientOrServer == TYPE_SERVER )
	{
		nDataLen = recv( m_mapConnectedSock.begin()->second, pBuff, dwLen, NULL );
	}

	return nDataLen;
}
