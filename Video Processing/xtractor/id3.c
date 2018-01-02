/*
 * id3.c - Copyright (C) 1999,2000 Jay A. Key
 *
 * ID3 configuration dialog. Lets the user input the album name, artist,
 * year, and select a genre.
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
#include <stdio.h>
#include <malloc.h>
#include "id3.h"
#include "resources.h"
#include "globals.h"

void CheckEnableID3MenuItem( HWND hWnd );
void InitID3Dialog( HWND hWnd );
void SaveID3DialogValues( HWND hWnd );
void SetEditItemText( int iCtlId, char *s );
char*ID3Genre2CDDBCat( int genre );

static ID3INFO id3info;

static BYTE genre[12] = { 0, 32, 2, 17, 53, 8, 17, 10, 16, 17, 24, 17 };

#define NUMGENRES 80
static char *genres[NUMGENRES] = {
  "Blues          ", "Classic Rock   ", "Country        ", "Dance          ",
  "Disco          ", "Funk           ", "Grunge         ", "Hip-Hop        ",
  "Jazz           ", "Metal          ", "New Age        ", "Oldies         ",
  "Other          ", "Pop            ", "R&B            ", "Rap            ",
  "Reggae         ", "Rock           ", "Techno         ", "Industrial     ",
  "Alternative    ", "Ska            ", "Death Metal    ", "Pranks         ",
  "Soundtrack     ", "Euro-Techno    ", "Ambient        ", "Trip-Hop       ",
  "Vocal          ", "Jazz+Funk      ", "Fusion         ", "Trance         ",
  "Classical      ", "Instrumental   ", "Acid           ", "House          ",
  "Game           ", "Sound Clip     ", "Gospel         ", "Noise          ",
  "Altern Rock    ", "Bass           ", "Soul           ", "Punk           ",
  "Space          ", "Meditative     ", "Inst. Pop      ", "Instrum. Rock  ",
  "Ethnic         ", "Gothic         ", "Darkwave       ", "Techno-Indus   ",
  "Electronic     ", "Pop-Folk       ", "Eurodance      ", "Dream          ",
  "Southern Rock  ", "Comedy         ", "Cult           ", "Gangsta        ",
  "Top 40         ", "Christian Rap  ", "Pop/Funk       ", "Jungle         ",
  "Native American", "Cabaret        ", "New Wave       ", "Psychadelic    ",
  "Rave           ", "Showtunes      ", "Trailer        ", "Lo-Fi          ",
  "Tribal         ", "Acid Punk      ", "Acid Jazz      ", "Polka          ",
  "Retro          ", "Musical        ", "Rock & Roll    ", "Hard Rock      "
};

static int gen2cat[NUMGENRES] = {
  0, 9, 2, 9, 9, 9, 6, 9, 5, 9, 7, 9, 6, 9, 0, 9, 8, 9, 9, 9,
  7, 6, 9, 6,10, 7, 6, 9, 6, 5, 5, 6, 1, 6, 9, 9, 6, 6, 4, 6,
  9, 6, 9, 9, 6, 7, 9, 9, 6, 6, 6, 6, 6, 9, 6, 6, 9, 6, 6, 6,
  9, 6, 9, 6, 6, 6, 7, 9, 9,10, 6, 6, 6, 9, 5, 4, 9,10, 9, 9
};


void asSetID3Info( int what, char *s, int val )
{
  switch( what )
    {
    case ID3_ERASE:
      ZeroMemory( &id3info, sizeof(id3info) );
      break;
    case ID3_ARTIST:
      ZeroMemory( id3info.szArtist, 31 );
      strncpy( id3info.szArtist, s, 30 );
      id3info.szArtist[30] = '\0';
      break;
    case ID3_ALBUM:
      ZeroMemory( id3info.szAlbum, 31 );
      strncpy( id3info.szAlbum, s, 30 );
      id3info.szAlbum[30] = '\0';
      break;
    case ID3_TITLE:
      ZeroMemory( id3info.szTitle, 31 );
      strncpy( id3info.szTitle, s, 30 );
      id3info.szTitle[30] = '\0';
      break;
    case ID3_YEAR:
      ZeroMemory( id3info.szYear, 5 );
      strncpy( id3info.szYear, s, 4 );
      id3info.szYear[4] = '\0';
      break;
    case ID3_GENRE:
      id3info.genre = (BYTE)val;
      id3info.bGenreSet = TRUE;
      if ( !id3info.bCDDBCatSet )
        asSetID3Info( ID3_CDDBCAT, ID3Genre2CDDBCat( id3info.genre ), 0 );
      break;
    case ID3_LEVEL:
      id3info.level = (BYTE)val;
      break;
    case ID3_TRACKNUM:
      id3info.trackNum = (BYTE)val;
      break;
    case ID3_CDDBCAT:
      ZeroMemory( id3info.szCDDBCat, 31 );
      strncpy( id3info.szCDDBCat, s, 30 );
      if ( !id3info.bGenreSet )
        id3CDDBCat2Genre( s );
      break;
    }
}


#define ID3V2TAGSIZE 1034
void writeID3V2Tag( FILE *fp )
{
  DWORD size = ID3V2TAGSIZE - 10;
  BYTE *tag = (BYTE *)malloc( ID3V2TAGSIZE );
  BYTE *hdr = tag;
  BYTE *p = tag + 10;
  unsigned int len;

  memset( tag, 0, ID3V2TAGSIZE );
  memcpy( hdr, "ID3", 3 );
  hdr[3] = 0x03;
  hdr[6] = (BYTE)((size >> 21) & 0x7F);
  hdr[7] = (BYTE)((size >> 14) & 0x7F);
  hdr[8] = (BYTE)((size >> 7) & 0x7F);
  hdr[9] = (BYTE)(size & 0x7F);

  memcpy( p, "TALB", 4 ); p += 4;
  p[3] = len = lstrlen( id3info.szAlbum ) + 1;
  p += 7;
  memcpy( p, id3info.szAlbum, len - 1 );
  p += ( len - 1 );

  memcpy( p, "TIT2", 4 ); p += 4;
  p[3] = len = lstrlen( id3info.szTitle ) + 1;
  p += 7;
  memcpy( p, id3info.szTitle, len - 1 );
  p += ( len - 1 );

  memcpy( p, "TPE1", 4 ); p += 4;
  p[3] = len = lstrlen( id3info.szArtist ) + 1;
  p += 7;
  memcpy( p, id3info.szArtist, len - 1 );
  p += ( len - 1 );

  fwrite( tag, 1, ID3V2TAGSIZE, fp );
  free( tag );
}


void writeID3V1Tag( FILE *fp )
{
  unsigned char buf[129];
  unsigned char *p = buf;

  // don't write the tag if any of the info is missing
  if ( (lstrlen( id3info.szAlbum ) == 0)
       || (lstrlen( id3info.szArtist ) == 0)
       || (lstrlen( id3info.szTitle ) == 0) )
    return;

  memset( buf, 0, 129 );
  memcpy( p, "TAG", 3 ); p += 3;
  memcpy( p, id3info.szTitle, lstrlen( id3info.szTitle ) ); p += 30;
  memcpy( p, id3info.szArtist, lstrlen( id3info.szArtist ) ); p += 30;
  memcpy( p, id3info.szAlbum, lstrlen( id3info.szAlbum ) ); p += 30;
  memcpy( p, id3info.szYear, 4 ); p += 4;
  buf[126] = id3info.trackNum;
  buf[127] = id3info.genre;

  fwrite( buf, 1, 128, fp );
}


BOOL CALLBACK ID3InfoDlgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
  lParam = lParam;

  switch( uMsg )
    {
    case WM_INITDIALOG:
      InitID3Dialog( hWnd );
      break;

    case WM_COMMAND:
      switch( LOWORD(wParam) )
	{
	case IDBN_ID3OK:
	  SaveID3DialogValues( hWnd );
	  EndDialog( hWnd, 0 );
	  break;
	case IDBN_ID3CANCEL:
	case IDCANCEL:
	  EndDialog( hWnd, 0 );
	  break;
	}
      break;

    default:
      // message not processed
      return FALSE;
    }

  // message processed
  return TRUE;
}


void InitID3Dialog( HWND hWnd )
{
  int i;

  for( i = 0; i < 80; i++ )
    SendDlgItemMessage( hWnd, IDCBX_GENRE, CB_ADDSTRING, 0,
			(LPARAM)genres[i] );
  SendDlgItemMessage( hWnd, IDCBX_GENRE, CB_SETCURSEL, (WPARAM)id3info.genre, 0L );
  SendDlgItemMessage( hWnd, IDE_ARTIST2, EM_SETLIMITTEXT, 30, 0L );

  SendDlgItemMessage( hWnd, IDE_ALBUM2, EM_SETLIMITTEXT, 30, 0L );
  SendDlgItemMessage( hWnd, IDE_YEAR, EM_SETLIMITTEXT, 4, 0L );
  SendDlgItemMessage( hWnd, IDE_ARTIST2, WM_SETTEXT, 0,
		      (LPARAM)id3info.szArtist );
  SendDlgItemMessage( hWnd, IDE_ALBUM2, WM_SETTEXT, 0,
		      (LPARAM)id3info.szAlbum );
  SendDlgItemMessage( hWnd, IDE_YEAR, WM_SETTEXT, 0, (LPARAM)id3info.szYear );
  CheckDlgButton( hWnd, IDCKB_ID3, bID3?BST_CHECKED:BST_UNCHECKED );
}


void SaveID3DialogValues( HWND hWnd )
{
  char buf[41];
  int i;

  i = SendDlgItemMessage( hWnd, IDCBX_GENRE, CB_GETCURSEL, 0, 0L );
  asSetID3Info( ID3_GENRE, NULL, i );

  ZeroMemory( buf, 41 );
  SendDlgItemMessage( hWnd, IDE_ARTIST2, WM_GETTEXT, 31, (LPARAM)buf );
  asSetID3Info( ID3_ARTIST, buf, i );
  SetEditItemText( IDE_ARTIST, buf );

  ZeroMemory( buf, 41 );
  SendDlgItemMessage( hWnd, IDE_ALBUM2, WM_GETTEXT, 31, (LPARAM)buf );
  asSetID3Info( ID3_ALBUM, buf, i );
  SetEditItemText( IDE_ALBUM, buf );

  ZeroMemory( buf, 41 );
  SendDlgItemMessage( hWnd, IDE_YEAR, WM_GETTEXT,5, (LPARAM)buf );
  asSetID3Info( ID3_YEAR, buf, i );

  bID3 = (BOOL)IsDlgButtonChecked( hWnd, IDCKB_ID3 );
  CheckEnableID3MenuItem( GetParent( hWnd ) );
}


void id3CDDBCat2Genre( char *s )
{
  int i;

  id3info.genre = 17;  // default to "rock"
  id3info.bGenreSet = TRUE;
  for( i = 0; i < 11; i++ )
    {
      if ( !lstrcmpi( s, szCDDBCat[i] ) )
	{
	  id3info.genre = genre[i];
	}
    }
}

char *asGetID3AsciiInfo( int what )
{
  switch( what )
    {
    case ID3_ARTIST:
      return id3info.szArtist;
    case ID3_ALBUM:
      return id3info.szAlbum;
    case ID3_TITLE:
      return id3info.szTitle;
    case ID3_YEAR:
      return id3info.szYear;
    case ID3_GENRE:
      if ( id3info.bGenreSet )
        return genres[id3info.genre];
      break;
    case ID3_CDDBCAT: 
      return id3info.szCDDBCat;
   }
  return "";
}


int asGetID3IntInfo( int what )
{
  switch( what )
    {
    case ID3_GENRE:
      if ( id3info.bGenreSet )
        return id3info.genre;
      return -1;

    case ID3_LEVEL:
      return id3info.level;
    
    case ID3_TRACKNUM:
      return id3info.trackNum;
    }
  return 0;
}


char *ID3Genre2CDDBCat( int genre )
{
  static char tmp[32];

  tmp[0] = '\0';
  if ( genre < 80 )
    lstrcpy( tmp, szCDDBCat[gen2cat[genre]] );

  return tmp;
}


int id3NumGenres( void )
{
  return NUMGENRES;
}


char *id3GetGenre( int which, char *buf, int bufLen )
{
  if ( (buf != NULL) && (which < NUMGENRES) && (which >= 0) )
    lstrcpyn( buf, genres[which], bufLen );
  
  return buf;
}