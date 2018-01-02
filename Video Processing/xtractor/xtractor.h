#ifndef __XTRACTOR_H_INC
#define __XTRACTOR_H_INC

#include <windows.h>
#include <wingdi.h>
#include <commctrl.h>
#ifdef _MSC_VER
#include <shlwapi.h>
#endif
#include <math.h>

#include "akrip/akrip32.h"
#include "resources.h"
#include "trackwnd.h"
#include "globals.h"
#include "id3.h"
#include "riptracks.h"
#include "statusbar.h"
#include "cddbdlg.h"
#include "config.h"
#include "enc/xtenc.h"
#include "threads.h"
#include "cdcache/cdcache.h"

#if (__IBMC__)                         /* BWT (20000127)                   */
WINCOMMCTRLAPI void WINAPI InitCommonControls(void);   /* BWT (20000127)   */
#endif                                 /* BWT (20000127)                   */


LRESULT CALLBACK akripWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
HWND createToolbar( HWND hWnd, HINSTANCE hInst );
HWND createHeader( HWND hWnd, HINSTANCE hInst );
void doPaint( HWND hWnd );
//void ComputeHeaderPos( HWND hParent );
void handleToolbarNotify( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
int WindowHeight( HWND hWnd );
void RefreshTrackList( void );
int DoConfig( HWND hParent, HINSTANCE hInst, UINT uiStartPage );
void InitAKRip( void );
void DeinitAKRip( void );
void MSB2DWORD( DWORD *d, BYTE *b );
int readRegSZ( HKEY hKey, LPCTSTR lpszValue, LPSTR lpszData, DWORD dwDataLen );
int readRegDWORD( HKEY hKey, LPCTSTR lpszValue, DWORD *pdw );
int doTrackContextMenu( HWND hParent, HWND hChild, LPARAM lParam );
BOOL InitGauge( HINSTANCE hInst );
BOOL RipTrackDlgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
BOOL loadBladeEnc( void );
void disableAutoPlay( void );
void restoreAutoPlay( void );
void GetEditItemText( int iCtlId, HWND hCtl );
BOOL CALLBACK ID3InfoDlgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
void SetEditItemText( int iCtlId, char *s );
void CheckEnableID3MenuItem( HWND hWnd );
void CheckEnableCDDBMenuItem( HWND hWnd );
void CheckEnableHiColorMenuItem( HWND hWnd );
BOOL CALLBACK AboutDialogProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
void InitBmpPanel( void );
void DynamicAboutDialog( HWND hParent );
void ShowHelpFile( HWND hWnd, int topic );
void DiffTimeToString( double d, char *buf );
//static void GetLineFromBuf( char *tgt, char **src, int len );
void DoCDDBQuery( HWND hWnd );
void SetTrackText( char *buf, int i );
DWORD DoCDDBQueryThread( LPVOID lpParam );
HCDROM findAvailableCD( void );
BOOL RipTrackSegment( HWND hParent, HWND hTrckWnd );
BOOL CALLBACK CDPropertiesDlgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
void dbprintf( char *fmt, ... );
DWORD GetDllVersion( LPCTSTR lpszDllName );
LRESULT CALLBACK SubToolbarProc( HWND hWnd, UINT uMsg, WPARAM wParam,
				 LPARAM lParam );
LRESULT CALLBACK SubToolbarEditProc( HWND hWnd, UINT uMsg, WPARAM wParam,
				 LPARAM lParam );
HIMAGELIST CreateToolbarImageList( HWND hWnd, HINSTANCE hInst, int idResource );
int AddToolbarImages( HINSTANCE hInst, HWND hWnd, BOOL bSysColorChange, BOOL bToggleHiColor );
BOOL DisplayIsHiColor( void );
void ComputeTrackWndRect( HWND hParent, LPRECT lprc );
void WriteInfo2CDPlayerINI( HWND hTrackWnd );
DWORD genCDPlayerIniIndex( HCDROM hCD );

// from cddbsubmit.c
void DoCDDBSubmit( HWND hWnd, HWND hTrackWnd );
DWORD DoCDDBSubmitThread( LPVOID lpParam );


#endif
