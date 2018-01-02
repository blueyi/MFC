// DestEquipCom_Intervention.cpp: implementation of the CComSocket_SysDiagnosis class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LogServer.h"
#include "ComSocket_SysDiagnosis.h"
#include "CommonDefineFunc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComSocket_SysDiagnosis::CComSocket_SysDiagnosis()
{
	m_nNumOfPort = 8050;
}

CComSocket_SysDiagnosis::~CComSocket_SysDiagnosis()
{
	if ( m_pTcpComForWindows )
	{
		delete m_pTcpComForWindows;
	}
}

void CComSocket_SysDiagnosis::Init( HWND hWnd, UINT nMessageID )
{
	m_pTcpComForWindows = new CTcpComForWindows( TYPE_SERVER, m_nNumOfPort, "", hWnd, nMessageID );
	OUT_LOG( "{SysDiagnosis} Start listen in Socket Port %d", m_nNumOfPort );
}

// 接收数据
void CComSocket_SysDiagnosis::AcceptRequest( unsigned short nTypeOfAcceptRequest )
{
	switch ( nTypeOfAcceptRequest )
	{
		case FD_ACCEPT:
			m_pTcpComForWindows->AcceptConn();
			OUT_LOG( "{SysDiagnosis} Established a connection !" );
			break;
			
		case FD_CLOSE:
			OUT_LOG( "{SysDiagnosis} Released a connection !" );
			break;
			
		case FD_READ:
			break;

		case FD_WRITE: 
			break;

		default:
			break;
	}
}

