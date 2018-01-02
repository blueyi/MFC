/*
 * cddbsubmit.c - Copyright (C) 1999,2000 Jay A. Key
 *
 * Code to handle formatting and submitting CDDB entries to cddb databases
 *
 **********************************************************************
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 */
#include <windows.h>
#include <string.h>
#include "akrip/akrip32.h"
#include "globals.h"
#include "id3.h"
#include "resources.h"
#include "trackwnd.h"
#include "threads.h"


int id3NumGenres( void );
char *id3GetGenre( int which, char *buf, int bufLen );


typedef struct {
  HWND hParent;
  DWORD dwID;
  char buf[64*1024];
} SUBMITSTRUCT, *PSUBMITSTRUCT;

typedef struct {
  DWORD dwID;              // cddb discid
  DWORD discLen;           // length of CD in seconds
  DWORD numTracks;
  DWORD tracks[100];       // track offsets
} SUBMITCDINFO, *PSUBMITCDINFO;

DWORD DoCDDBSubmitThread( LPVOID lpParam );
void SetStatusMessage( char * );
void UpdateStatusBar( void );
static void CenterDialog( HWND hWnd );
BOOL validUserEmailAndGenre( HWND hWnd );
BOOL CALLBACK SubmitWiz1Proc( HWND, UINT, WPARAM, LPARAM );
int formatSubmitEntry( HWND hWnd, PSUBMITSTRUCT pSubmit );
DWORD GenCDDBDiskID( PSUBMITCDINFO pInfo );
void dbprintf( char *, ... );
void insertGenres( HWND hWnd );


static char szDGenre[256];

#ifndef TESTSUBMITMODE
#define TESTSUBMITMODE FALSE
#endif

void DoCDDBSubmit( HWND hWnd, HWND hTrackWnd )
{
  DWORD dwThreadID;
  int i;
  BOOL bThreadDestroy = FALSE;
  PSUBMITSTRUCT p;
  HANDLE hThread = NULL;
  
  ZeroMemory( szDGenre, 256 );
  
  iCddbEntryRev++;

  p = (PSUBMITSTRUCT)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(SUBMITSTRUCT) );

  p->hParent = hWnd;
  i = formatSubmitEntry( hTrackWnd, p );

  while( i != -1 )
    {
      switch( i )
	{
	case 0:
          // display the first screen
	  i = DialogBoxParam( ghInstance, "SubmitWiz1", hWnd, (DLGPROC)SubmitWiz1Proc, (LPARAM)p );
	  break;

	case 1:
          // display the second screen
          // reformat the entry with the level 5 info added
          dbprintf( "Before setting, CDDB protocol level: %d", CDDBGetOptionInt( CDDB_OPT_PROTOLEVEL, NULL ) );
          CDDBSetOption( CDDB_OPT_PROTOLEVEL, "", 5 );
          dbprintf( "After setting, CDDB protocol level: %d", CDDBGetOptionInt( CDDB_OPT_PROTOLEVEL, NULL ) );
          formatSubmitEntry( hTrackWnd, p );
	  i = DialogBoxParam( ghInstance, "SubmitWiz2", hWnd, (DLGPROC)SubmitWiz1Proc, (LPARAM)p );
	  break;

	case 2:
          // actually send the entry
	  bThreadDestroy = TRUE;
	  hThread = CREATETHREAD( NULL, 0, (LPTHREAD_START_ROUTINE)DoCDDBSubmitThread,
			(LPVOID)p, 0, &dwThreadID );
	  i = -1;
	  break;
        
        case -2:
          // Either the artist or the album title were empty.  At least
          // one of the two *must* be filled out
          MessageBox( hWnd, "This CD could not be submitted because: Artist name and album title not filled in.",
                      "Error", MB_OK | MB_ICONSTOP );
          i = -1;
          break;
        
        case -3:
          // all of the track titles must have been changed
          MessageBox( hWnd, "This CD could not be submitted because: You must enter all track titles.", 
                      "Error", MB_OK | MB_ICONSTOP );
          i = -1;
          break;
        
        case -4:
          // The TOC has not been read
          MessageBox( hWnd, "This CD could not be submitted because: The CD has not been read yet.", 
                      "Error", MB_OK | MB_ICONSTOP );
          i = -1;
          break;

	default:
	  i = -1;
	  break;
	}
    }

  if ( !bThreadDestroy )
    iCddbEntryRev--;
}


DWORD DoCDDBSubmitThread( LPVOID lpParam )
{
  BOOL bTestSubmit = TESTSUBMITMODE;
  PSUBMITSTRUCT p = (PSUBMITSTRUCT)lpParam;
  char szTmp[32];
  DWORD dwRet;

  CDDBSetOption( CDDB_OPT_SERVER, szCDDBServer, 0 );
  CDDBSetOption( CDDB_OPT_USEPROXY, "", bUseProxy );
  CDDBSetOption( CDDB_OPT_PROTOLEVEL, "", 5 );
  if ( bUseProxy )
    {
      CDDBSetOption( CDDB_OPT_PROXY, szProxyAddr, 0 );
      CDDBSetOption( CDDB_OPT_PROXYPORT, "", iProxyPort );
      if ( szProxyUser[0] != '\0' && szProxyPass[0] != '\0' )
      {
        char auth[98];
        wsprintf( auth, "%s:%s", szProxyUser, szProxyPass );
        CDDBSetOption( CDDB_OPT_USERAUTH, auth, 0 );
      }
    }
  CDDBSetOption( CDDB_OPT_USER, szUserEmail, 0 );
  wsprintf( szTmp, "xtractor v%d.%02d", iMajorVer, iMinorVer );
  CDDBSetOption( CDDB_OPT_AGENT, szTmp, 0 );

  CDDBSetOption( CDDB_OPT_SUBMITCGI, szSubmitCGI, 0 );

  SetStatusMessage( "Contacting CDDB server..." );
  dbprintf( "Using %s as genre", asGetID3AsciiInfo( ID3_CDDBCAT ) );

  lstrcpy( szTmp, asGetID3AsciiInfo( ID3_CDDBCAT ) );
  dwRet = CDDBSubmit( p->dwID, bTestSubmit, szUserEmail, szTmp, p->buf );

  if ( !bTestSubmit )
    {
    if ( dwRet == SS_COMP )
      SetStatusMessage( "Entry submitted" );
    else
      SetStatusMessage( "Error submitting entry" );
    }
  else
    {
    if ( dwRet == SS_COMP )
      SetStatusMessage( "Test entry submitted" );
    else
      SetStatusMessage( "Error submitting test entry" );
    }

//  UpdateStatusBar();
  HeapFree( GetProcessHeap(), 0, lpParam );
  return 0;
}


BOOL CALLBACK SubmitWiz1Proc( HWND hWnd, UINT uMsg, WPARAM wParam,
			     LPARAM lParam )
{
  WORD wID, wNotify;
  static HBRUSH hBrush;
  PSUBMITSTRUCT p;

  switch( uMsg )
    {
    case WM_COMMAND:
      wID = LOWORD(wParam);
      wNotify = HIWORD(wParam);
      switch( wID )
	{
	case IDBN_WIZ2CANCEL:
	case IDBN_WIZ1CANCEL:
	  EndDialog( hWnd, -1 );
	  break;

	case IDBN_WIZ1NEXT:
	  EndDialog( hWnd, 1 );
	  break;

	case IDBN_WIZ2BACK:
	  EndDialog( hWnd, 0 );
	  break;

	case IDBN_WIZ2NEXT:
	  EndDialog( hWnd, 2 );
	  break;

	case IDE_WIZ1EMAIL:
	  if ( wNotify == EN_CHANGE )
	    {
	      EnableWindow( GetDlgItem( hWnd, IDBN_WIZ1NEXT ), 
			    validUserEmailAndGenre( hWnd ) );
	    }
	  break;

        case IDCBX_WIZ1GENRE:
          if ( wNotify == CBN_SELCHANGE )
          {
            EnableWindow( GetDlgItem( hWnd, IDBN_WIZ1NEXT ), 
                          validUserEmailAndGenre( hWnd ) );
          }
          break;
          
        case IDE_WIZ1DGENRE:
          if ( wNotify == EN_CHANGE )
          {
            szDGenre[255] = 0;
            GetDlgItemText( hWnd, IDE_WIZ1DGENRE, szDGenre, 255 );
            dbprintf( "set szDGenre to %s", szDGenre );
          }
          break;
          
	}
      break;

    case WM_INITDIALOG:
      CenterDialog( hWnd );
      SetDlgItemText( hWnd, IDE_WIZ1EMAIL, szUserEmail );
      SendDlgItemMessage( hWnd, IDCBX_WIZ1GENRE, CB_ADDSTRING, 0, (LPARAM)"Please select" );
      SendDlgItemMessage( hWnd, IDCBX_WIZ1GENRE, CB_ADDSTRING, 0, (LPARAM)"blues" );
      SendDlgItemMessage( hWnd, IDCBX_WIZ1GENRE, CB_ADDSTRING, 0, (LPARAM)"classical" );
      SendDlgItemMessage( hWnd, IDCBX_WIZ1GENRE, CB_ADDSTRING, 0, (LPARAM)"country" );
      SendDlgItemMessage( hWnd, IDCBX_WIZ1GENRE, CB_ADDSTRING, 0, (LPARAM)"data" );
      SendDlgItemMessage( hWnd, IDCBX_WIZ1GENRE, CB_ADDSTRING, 0, (LPARAM)"folk" );
      SendDlgItemMessage( hWnd, IDCBX_WIZ1GENRE, CB_ADDSTRING, 0, (LPARAM)"jazz" );
      SendDlgItemMessage( hWnd, IDCBX_WIZ1GENRE, CB_ADDSTRING, 0, (LPARAM)"misc" );
      SendDlgItemMessage( hWnd, IDCBX_WIZ1GENRE, CB_ADDSTRING, 0, (LPARAM)"newage" );
      SendDlgItemMessage( hWnd, IDCBX_WIZ1GENRE, CB_ADDSTRING, 0, (LPARAM)"reggae" );
      SendDlgItemMessage( hWnd, IDCBX_WIZ1GENRE, CB_ADDSTRING, 0, (LPARAM)"rock" );
      SendDlgItemMessage( hWnd, IDCBX_WIZ1GENRE, CB_ADDSTRING, 0, (LPARAM)"soundtrack" );
      if ( !bCddbRetrievedGenre )
        SendDlgItemMessage( hWnd, IDCBX_WIZ1GENRE, CB_SETCURSEL, (WPARAM)0, 0 );
      else
        SendDlgItemMessage( hWnd, IDCBX_WIZ1GENRE, CB_SELECTSTRING, (WPARAM)(-1), (LPARAM)szCddbRetrievedGenre );
      insertGenres( hWnd );
      SendDlgItemMessage( hWnd, IDE_WIZ1YEAR, EM_SETLIMITTEXT, 4, 0 );
      SendDlgItemMessage( hWnd, IDE_WIZ1YEAR, WM_SETTEXT, 0, (LPARAM)asGetID3AsciiInfo( ID3_YEAR ) );
      SendDlgItemMessage( hWnd, IDE_WIZ1DGENRE, WM_SETTEXT, 0, (LPARAM)szDGenre );
      hBrush = (HBRUSH)GetStockObject( WHITE_BRUSH );
      p = (PSUBMITSTRUCT)lParam;
      if ( p )
	{
	  SetDlgItemText( hWnd, IDE_WIZ2ENTRY, p->buf );
	}
      EnableWindow( GetDlgItem( hWnd, IDBN_WIZ1NEXT ), 
                    validUserEmailAndGenre( hWnd ) );
      // set the title text if necessary
      if ( TESTSUBMITMODE )
        {
          char titleTmp[64];
          char title[76];
          ZeroMemory( titleTmp, sizeof(titleTmp) );
          ZeroMemory( title, sizeof(title) );
          GetWindowText( hWnd, titleTmp, 64 );
          wsprintf( title, "Test Mode: %s", titleTmp );
          SetWindowText( hWnd, title );
        }
      break;

    case WM_DESTROY:
      if ( validUserEmailAndGenre( hWnd ) )
	GetDlgItemText( hWnd, IDE_WIZ1EMAIL, szUserEmail, 257 );
      return FALSE;

    case WM_CTLCOLORSTATIC:
      if ( GetDlgItem( hWnd, IDE_WIZ2ENTRY ) == (HWND)lParam )
	return (BOOL)hBrush;
      return FALSE;

    default:
      return FALSE;
    }

  return TRUE;
}


static void CenterDialog( HWND hWnd )
{
  RECT rc, rc2;
  GetWindowRect( hWnd, &rc );
  GetWindowRect( GetParent( hWnd ), &rc2 );
  SetWindowPos( hWnd, NULL,
		((rc2.right+rc2.left) - (rc.right-rc.left))/2,
		((rc2.bottom+rc2.top) - (rc.bottom-rc.top))/2,
		0, 0, SWP_NOSIZE | SWP_NOACTIVATE );
}


BOOL validUserEmailAndGenre( HWND hWnd )
{
  char szEmail[257];
  char szYear[5];
  char szCDDBCat[32];
  char *p1, *p2;
  int i;

  // validate the email
  ZeroMemory( szEmail, 257 );
  GetDlgItemText( hWnd, IDE_WIZ1EMAIL, szEmail, 256 );

  if ( szEmail[0] == '\0' )
    return FALSE;

  p2 = p1 = strstr( szEmail, "@" );
  if ( p1 )
    p2 = strstr( p1+1, "@" );

  // one, and only one "@" allowed
  if ( !p1 || (p1 && p2) )
    {
      return FALSE;
    }

  p2 = strstr( p1, "." );

  if ( p2 == NULL )
    return FALSE;
  
  i = SendDlgItemMessage( hWnd, IDCBX_WIZ1GENRE, CB_GETCURSEL, 0, 0 );
  if ( ( i == CB_ERR ) || ( i == 0 ) )
    return FALSE;
  
  GetDlgItemText( hWnd, IDCBX_WIZ1GENRE, szCDDBCat, 32 );
  dbprintf( "Retrieved CDDB genre %s\n", szCDDBCat );
  
  asSetID3Info( ID3_CDDBCAT, szCDDBCat, 0 );
  dbprintf( "Genre is \"%s\", %d", asGetID3AsciiInfo( ID3_GENRE ), asGetID3IntInfo( ID3_GENRE ) );
  
  SendDlgItemMessage( hWnd, IDE_WIZ1YEAR, WM_GETTEXT, 5, (LPARAM)szYear );
  asSetID3Info( ID3_YEAR, szYear, 0 );
  
  return TRUE;
}


/*
 * Actually format the entry with currently entered values.  Returns:
 *    0: all data present and entry formatted successfully
 *   -2: Missing either the artist or album title (at least one
 *       of the two must be present)
 *   -3: All of the track titles were filled in with default values,
 *       ie. 'Track 01' and so on
 *   -4: The TOC has not been read, so no tracks are present
 */
int formatSubmitEntry( HWND hWnd, PSUBMITSTRUCT pSubmit )
{
  static char szEntryHeader[] =
    "# xmcd\r\n#\r\n# Track frame offsets:\r\n";
  DWORD i;
  char *p;
  BOOL bNotModified;
  SUBMITCDINFO cdinfo;
  
  dbprintf( "in formatSubmitEntry..." );
  
  memset( &cdinfo, 0, sizeof(cdinfo) );
  if ( GenCDDBDiskID( &cdinfo ) == SS_ERR )
    return -4;

  pSubmit->dwID = cdinfo.dwID;

  p = pSubmit->buf;

  // format the entry
  lstrcpy( p, szEntryHeader );
  p += lstrlen( p );
  for( i = 0; i < cdinfo.numTracks; i++ )
    {
      wsprintf( p, "#       %d\r\n", cdinfo.tracks[i] );
      p += lstrlen( p );
    }

  /*
   * The disc length here is just the offset of the leadout, NOT
   * the same as the length used when querying.
   */
  wsprintf( p, "#\r\n# Disc length: %d seconds\r\n#\r\n# Revision: %d\r\n",
	    cdinfo.discLen, iCddbEntryRev );
  p += lstrlen( p );

  wsprintf( p, "# Submitted via: CD-DA_X-Tractor v%d.%02d\r\n#\r\n",
    iMajorVer, iMinorVer );
  p += lstrlen( p );

  wsprintf( p, "DISCID=%08x\r\nDTITLE=%s / %s\r\n", 
	    cdinfo.dwID,
	    szArtistName,
	    szAlbumTitle );
  p += lstrlen( p );

  dbprintf( "CDDB protocol level: %d", CDDBGetOptionInt( CDDB_OPT_PROTOLEVEL, NULL ) );
  if ( CDDBGetOptionInt( CDDB_OPT_PROTOLEVEL, NULL ) == 5 )
  {
    dbprintf( "Year: %s, Genre: \"%s\"", asGetID3AsciiInfo( ID3_YEAR ),
              asGetID3AsciiInfo( ID3_GENRE ) );
    wsprintf( p, "DYEAR=%s\r\nDGENRE=%s\r\n", asGetID3AsciiInfo( ID3_YEAR ),
              szDGenre );
    p += lstrlen( p );
  }

  // either the artist name or the album title must be filled in
  if ( (lstrlen( szArtistName ) == 0) &&
       (lstrlen( szAlbumTitle ) == 0) )
    return -2;

  bNotModified = FALSE;
  for( i = 0; i < cdinfo.numTracks; i++ )
    {
      char szTmp[16];
      ADDTRACK at;
      wsprintf( szTmp, "Track %02d", i+1 );
      ZeroMemory( &at, sizeof(at) );
      SendMessage( hWnd, WM_GETTRACK, i, (LPARAM)&at );
      wsprintf( p, "TTITLE%d=%s\r\n", i, at.name );
      if ( !lstrcmp( at.name, szTmp ) )
        bNotModified = TRUE;
      p += lstrlen( p );
    }

  // no track is allowed to have a default title
  if ( bNotModified )
    return -3;

  lstrcpy( p, "EXTD=\r\n" );
  p += lstrlen( p );
  for( i = 0; i < cdinfo.numTracks; i++ )
    {
      wsprintf( p, "EXTT%d=\r\n", i );
      p += lstrlen( p );
    }
  lstrcat( p, "PLAYORDER=\r\n" );
    
  return 0;
}


DWORD CDDBSum( DWORD n )
{
  DWORD retVal = 0;

  while( n > 0 )
    {
      retVal += ( n % 10 );
      n /= 10;
    }

  return retVal;
}

/*
 * Uses the stored TOC to generate the cddbid and other
 * data used in formatting and submitting a CD.
 * Returns SS_COMP if successful, or SS_ERR if the TOC has
 * not been read yet.
 */
DWORD GenCDDBDiskID( PSUBMITCDINFO pInfo )
{
  TOCTRACK *t1, *t2;
  DWORD t, n;
  int i, j;
  
  memset( pInfo, 0, sizeof(*pInfo) );

  if ( !bTocRead )
    return SS_ERR;

  n = t = 0;
  for( j = 0, i = msfToc.firstTrack - 1; i < msfToc.lastTrack; i++, j++ )
    {
      t1 = &(msfToc.tracks[i]);
      pInfo->tracks[j] = (((t1->addr[1]*60)+t1->addr[2])*75)+t1->addr[3];
      n += CDDBSum( 60 * msfToc.tracks[i].addr[1] + msfToc.tracks[i].addr[2] );
    }

  t2 = &(msfToc.tracks[msfToc.lastTrack-msfToc.firstTrack+1]);
  t = 60 * t2->addr[1] + t2->addr[2];
  t2 = &(msfToc.tracks[0]);
  t -= ( 60 * t2->addr[1] + t2->addr[2] );

  pInfo->dwID = ((n%0xFF) << 24) | (t << 8) | (msfToc.lastTrack - msfToc.firstTrack + 1);

  t1 = &(msfToc.tracks[msfToc.lastTrack-msfToc.firstTrack+1]);
  pInfo->discLen = 60 * t1->addr[1] + t1->addr[2];

  pInfo->numTracks = msfToc.lastTrack - msfToc.firstTrack + 1;
    
  return SS_COMP;
}


void insertGenres( HWND hWnd )
{
  int year;
  char buf[64];
  
  ZeroMemory( buf, sizeof(buf) );
  if ( hCddbEntry )
  {
    cddbGetDGenre( hCddbEntry, buf, sizeof(buf) );
    SetDlgItemText( hWnd, IDE_WIZ1DGENRE, buf );
    year = cddbGetDYear( hCddbEntry );
    if ( year != 0 )
      SetDlgItemInt( hWnd, IDE_WIZ1YEAR, year, TRUE );
  }
}
