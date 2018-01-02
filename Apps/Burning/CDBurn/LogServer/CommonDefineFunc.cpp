// CommonDefine.cpp : implementation of the CMainFrame class
//
#include "stdafx.h"
#include "CommonDefineFunc.h"
/*
#include "CommonDefine.h"
*/

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////

void OUT_LOG( LPCSTR format, ... )
{
	// 产生LOG正文
	va_list arglist; 
	char buffer[2048]; 
	
	va_start (arglist,format); 
	sprintf( buffer, arglist );
	vsprintf( buffer, format, arglist ); 
	va_end (arglist); 
	
	// 产生LOG时间戳
	time_t nDateTime = mktime( CTime::GetCurrentTime().GetLocalTm() );			
	if ( nDateTime <= 0 ) 
	{
		return;// "无效时间";	
	}

	CString sDateTime;	
	tm * pTm = localtime( &nDateTime );
	sDateTime.Format( "%04d-%02d-%02d %02d:%02d:%02d", 
		pTm->tm_year + 1900, pTm->tm_mon + 1, pTm->tm_mday,
		pTm->tm_hour, pTm->tm_min, pTm->tm_sec );
			
	// 输出LOG全文
	CString sMsg; 
	sMsg.Format( "%s : %s\r\n", sDateTime, buffer );
	
	HWND hReceiver = ::FindWindow(NULL, _T("LogServer"));
	if (hReceiver)
	{		
		COPYDATASTRUCT cds;
		ZeroMemory(&cds, sizeof(COPYDATASTRUCT));
		
		STRUCT_PACKET_LOG oPacket;
		oPacket.nTypeOfPacket = -1/*TYPE_PACKET_LOG*/;
		sprintf( oPacket.sLogText, sMsg );
		
		cds.cbData = sizeof(STRUCT_PACKET_LOG);
		cds.lpData = &oPacket;
		
		::SendMessage( hReceiver, WM_COPYDATA, 0, (LPARAM) &cds );
	}
}

void SEND_PACKET_TO_COMSERVER( HWND hCallingWnd, PVOID pData, int nLengthOfData )
{
	int nNumOfFindWindow = 0;

BEGIN_OF_FUNCTION:

	HWND hReceiver = ::FindWindow(NULL, _T("LogServer"));
	++ nNumOfFindWindow;

	if (hReceiver)
	{
		COPYDATASTRUCT cds;
		ZeroMemory(&cds, sizeof(COPYDATASTRUCT));
		cds.cbData = nLengthOfData;;
		cds.lpData = pData;
		
		::SendMessage( hReceiver, WM_COPYDATA, (WPARAM) hCallingWnd, (LPARAM) &cds );
		
		int nTypeOfPacket;
		int nAddrOffset = sizeof(int);
		memcpy( &nTypeOfPacket, cds.lpData, nAddrOffset );
		OUT_LOG( "{SEND_MESSAGE_TO_COMSERVER} Sent a Packet to LogServer, PacketID: %d", nTypeOfPacket );
	}
	else
	{
//		AfxMessageBox( "{SEND_PACKET_TO_COMSERVER} The LogServer has not been started, Please start it ..." );
		
		// start LogServer
		STARTUPINFO startup_info;
		PROCESS_INFORMATION proc_info;
		
		memset( (void*)&startup_info,0 ,sizeof(STARTUPINFO) );
		startup_info.cb = sizeof(STARTUPINFO);
		memset( (void*)&proc_info,0,sizeof(PROCESS_INFORMATION) );
		char szExe[255], szCmdLine[50];
		
		char szCurDir [_MAX_PATH];
		::GetCurrentDirectory (_MAX_PATH, szCurDir);
		sprintf( szExe, "%s\\%s", szCurDir, "LogServer.exe");
		sprintf( szCmdLine, "" );
		
		char szPrompt[200];
		if ( !CreateProcess(szExe, "",//szCmdLine,
			NULL, NULL,	FALSE,	NORMAL_PRIORITY_CLASS,
			NULL,NULL,&startup_info,&proc_info))
		{
			sprintf(szPrompt,"启动%s失败!",szExe);
			AfxMessageBox(szPrompt);
		}

		if ( nNumOfFindWindow >= 3 )
		{
			return;
		}
		else
		{
			goto BEGIN_OF_FUNCTION;
		}		
	}
}