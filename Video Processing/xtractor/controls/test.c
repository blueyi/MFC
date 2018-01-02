#include <windows.h>
#include <stdio.h>
#include <ctype.h>
#include <commctrl.h>
#include "treeopt.h"
#include "resources.h"

LRESULT CALLBACK testWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
BOOL CALLBACK TestDialogProc(HWND,UINT,WPARAM,LPARAM);
BOOL CALLBACK TestDialogProc1(HWND,UINT,WPARAM,LPARAM);
void DumpResource( HWND hWnd );
void createDlg( HWND hWnd );

char szClassName[] = "testwnd";
HINSTANCE ghInst;
static FILE *fp;

static int fooCount = 0;

int WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine,
                    int nCmdShow ) 
{
  WNDCLASSEX wc;
  HWND hWnd;
  MSG msg;
  
  ghInst = hInst;

  ZeroMemory( &wc, sizeof(wc) );
  wc.cbSize        = sizeof(WNDCLASSEX);
  wc.style         = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc   = (WNDPROC)testWndProc;
  wc.hInstance     = hInst;
  wc.hCursor       = LoadCursor( NULL, IDC_ARROW );
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
  wc.lpszClassName = szClassName;
  wc.lpszMenuName  = "testMenu";

  if ( !RegisterClassEx( &wc ) )
    return FALSE;
  
  hWnd = CreateWindowEx( WS_EX_APPWINDOW, szClassName, "TreeOptionDialog Test",
                         WS_OVERLAPPEDWINDOW | WS_VSCROLL,
                         CW_USEDEFAULT, CW_USEDEFAULT,
                         540, 400,
                         NULL, NULL, hInst, NULL );
  
  if ( !hWnd )
    return FALSE;

  ShowWindow( hWnd, nCmdShow );
  UpdateWindow( hWnd );
  while( GetMessage( &msg, NULL, 0, 0 ) )
  {
    TranslateMessage( &msg );
    DispatchMessage( &msg );
  }
  
  return msg.wParam;
}


LRESULT CALLBACK testWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
  switch ( uMsg )
  {
    case WM_COMMAND:
      switch ( LOWORD( wParam ) )
      {
        case IDM_EXIT:
          DestroyWindow( hWnd );
          break;
        
        case IDM_DISPCONFIG:
          createDlg( hWnd );
          break;
      }
      break;
      
    case WM_DESTROY:
      PostQuitMessage( 0 );
      break;
    
    default:
      return DefWindowProc( hWnd, uMsg, wParam, lParam );
  }
  
  return 0L;
}

void createDlg( HWND hWnd )
{
  CTPREFDIALOG prefDlg;
  PREFSHEET prefSheet[3];
  
  ZeroMemory( &prefDlg, sizeof(prefDlg) );
  prefDlg.hWndParent = hWnd;
  prefDlg.hInst = ghInst;
  prefDlg.lpszTitle = "Just Another Test Dialog";
  
  prefDlg.lpPrefSheet = prefSheet;
  
  ZeroMemory( prefSheet, sizeof(PREFSHEET) );
  prefSheet[0].lpszTemplate = "TestDialog1";
  prefSheet[0].dlgproc = TestDialogProc1;
  prefSheet[0].child = prefSheet + 1;
  
  ZeroMemory( prefSheet + 1, sizeof(PREFSHEET) );
  prefSheet[1].lpszTemplate = "TestDialog2";
  prefSheet[1].dlgproc = TestDialogProc;
  prefSheet[1].sibling = prefSheet + 2;
  prefSheet[1].isDefault = TRUE;
  
  ZeroMemory( prefSheet + 2, sizeof(PREFSHEET) );
  prefSheet[2].lpszTemplate = "TestDialog3";
  prefSheet[2].dlgproc = TestDialogProc;
  
  
  CreateTreeOptionDialog( &prefDlg );
}


BOOL CALLBACK TestDialogProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
  switch ( uMsg )
  {
    case WM_INITDIALOG:
      return FALSE;
  }
  return FALSE;
}

BOOL CALLBACK TestDialogProc1( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
  NMHDR *l = (NMHDR *)lParam;
  
//  printf( "TestDialogProc1, %ld\n", hWnd  );
  switch ( uMsg )
  {
    case WM_INITDIALOG:
      return FALSE;
    
    case WM_NOTIFY:
      if ( l->code == PSN_KILLACTIVE )
      {
        if ( fooCount++ == 0 ) {
          printf( "got PSN_KILLACTIVE\n" );
          MessageBox( hWnd, "You must now hit cancel, since this dialog page will allows fail to allow the switch...",
                      "Error",
                      MB_APPLMODAL | MB_ICONERROR | MB_OK );
          SetWindowLong( hWnd, DWL_MSGRESULT, TRUE );
          return TRUE;
        }
      }
      break;
  }
  return FALSE;
}

void DumpResource( HWND hWnd )
{
  HRSRC hResource;
  HGLOBAL hMem;
  LPBYTE pMem;
  int i, len, pos, len2;
  HMODULE hModule;
  char buf[17];
  
  fp = fopen( "dump.txt", "wt" );
  
  hModule = LoadLibrary( "treeoptdlg.dll" );
  if ( hModule == NULL ) 
  {
    printf( "hModule was NULL: %ld\n", GetLastError() );
    return;
  }
  
  hResource = FindResource( hModule, "RipTrackDialog", RT_DIALOG );
  if ( hResource == NULL ) 
  {
    printf( "hResouce was NULL: %ld\n", GetLastError() );
    FreeLibrary( hModule );
    return;
  }
  
  hMem = LoadResource( hModule, hResource );
  pMem = LockResource( hMem );
  
  len = (int)SizeofResource( hModule, hResource );
  printf( "resource size: %d\n", len );
  len2 = len / 16;
  if ( len2 * 16 == len )
    len2 = len;
  else
    len2 = (len2 + 1) * 16;
  for ( i = 0; i < len2; i++ )
  {
    if ( i % 16 == 0 )
    {
      fprintf( fp, "%04X: ", i );
      ZeroMemory( buf, 17 );
    }
    if ( i < len )
    {
      fprintf( fp, "%02X ", pMem[i] );
      pos = i%16;
      if ( isalnum( pMem[i] ) )
        buf[pos] = pMem[i];
      else
        buf[pos] = '.';
    }
    else
      fprintf( fp, "   " );
    if ( (i+1) % 16 == 0 )
      fprintf( fp, "  %s\n", buf );
  }
  FreeLibrary( hModule );
}
