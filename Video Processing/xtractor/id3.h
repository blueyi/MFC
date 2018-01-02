/*
 * id3.h - Copyright (C) 1999,2000 Jay A. Key
 *
 * ID3 tagging support routines
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
#ifndef _ID3_H_INC
#define _ID3_H_INC

#include <stdio.h>

typedef struct {
  char szAlbum[31];
  char szTitle[31];
  char szArtist[31];
  char szYear[5];
  char szCDDBCat[31];
  BOOL bGenreSet; 
  BOOL bCDDBCatSet;
  unsigned char genre;
  unsigned char level;         // 0 == not used, 1 = ID3V1, 2 = ID3V2
  unsigned char trackNum;
} ID3INFO, FAR *LPID3INFO;

#define  ID3_ERASE     -2     // resets ID3INFO structure
#define  ID3_ID3INFO   -1     // provide complete filled-in ID3INFO as (char *)
#define  ID3_ARTIST     0
#define  ID3_ALBUM      1
#define  ID3_TITLE      2
#define  ID3_YEAR       3
#define  ID3_GENRE      4
#define  ID3_LEVEL      5
#define  ID3_CDDBCAT    6
#define  ID3_TRACKNUM   7


void asSetID3Info( int what, char *s, int val );
void writeID3V2Tag( FILE *fp );
void writeID3V1Tag( FILE *fp );
void id3CDDBCat2Genre( char *s );
char *asGetID3AsciiInfo( int what );
int asGetID3IntInfo( int what );

#endif
