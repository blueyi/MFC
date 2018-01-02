// MriSeqComInterface.h: interface for the CTcpComForWindows class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCPCOMFORWINDOWS_H__2CE86DA7_0A75_4A81_A5F7_6477A4E22A57__INCLUDED_)
#define AFX_TCPCOMFORWINDOWS_H__2CE86DA7_0A75_4A81_A5F7_6477A4E22A57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ------------------------------------------------------------------------------------------
#pragma warning (disable : 4786)
#include <map>

#include <winsock2.h>
#include <ws2tcpip.h>

// ------------------------------------------------------------------------------------------
#define WM_SOCKET WM_USER+200

#define TYPE_CLIENT		0
#define TYPE_SERVER		1

#define MAX_NUM_OF_CONNECTION	20

// -----------------------------------------------------------------------------------------------------------
/*
	【基于TCP/IP的socket通信】的公共接口类
*/

class AFX_EXT_CLASS CTcpComForWindows
{
public:
	// nClientOrServer: 0 -- client; 1 -- server
	// if nClientOrServer == 1, cIPAddr is invalid
	CTcpComForWindows( BYTE nClientOrServer, short nPort, char* cIPAddr, HWND hWnd, UINT nMessageID );
	virtual ~CTcpComForWindows();
	
private:
	BYTE	m_nClientOrServer;
	HWND	m_hWnd;
	UINT	m_nMessageID;
	
	short	m_nPort;
	char*	m_sIPAddr;
	
	int		m_nErrorCode;
	int		m_nMode;
	
	SOCKET	m_hListener;
	SOCKET	m_hClientSocket;

//	int		m_nNumOfConnection;
//	SOCKET	m_hAcceptSock[MAX_NUM_OF_CONNECTION];

	std::map<CString, SOCKET> m_mapConnectedSock;
	std::map<CString, SOCKET>::iterator m_mapConnectedSockIter;
	
public:
	// for CLIENT
	int ConnectServer();
	
	// for SERVER
	int StartListen();
	int AcceptConn();
	
	// for CLIENT and SERVER
	int SendData(char* pBuff, DWORD dwLen);
	int RecvData(char* pBuff, DWORD dwLen);
	
};


#endif // !defined(AFX_TCPCOMFORWINDOWS_H__2CE86DA7_0A75_4A81_A5F7_6477A4E22A57__INCLUDED_)
