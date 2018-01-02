/*
 * trackwnd.h - Copyright (C) 1999,2000 Jay A. Key
 *
 * Header file for the TrackWnd window class and interface
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
#ifndef _TRACKWND_H_INC
#define _TRACKWND_H_INC

#include <windows.h>

#define ALLTRACKS            0xFFFFFFFF

#define WM_ADDTRACK          (WM_USER+100)
#define WM_DELTRACK          (WM_USER+101)
#define WM_CHECKTRACK        (WM_USER+102)
#define WM_SELTRACK          (WM_USER+103)
#define WM_INVERTCHECK       (WM_USER+104)
#define WM_RENSELTRACK       (WM_USER+105)
#define WM_FINDFIRSTTRACK    (WM_USER+106)
#define WM_FINDNEXTTRACK     (WM_USER+107)
#define WM_SETSELTEXT        (WM_USER+108)
#define WM_NUMCHECKED        (WM_USER+109)
#define WM_NUMTRACKS         (WM_USER+110)
#define WM_GETTRACK          (WM_USER+111)
#define WM_SETTRACKSTATUS    (WM_USER+112)
#define WM_SETTRACKTEXT      (WM_USER+113)

typedef struct
{
  char name[MAX_PATH+1];
  char status[61];
  DWORD start;
  DWORD len;
  BOOL  bData;
  BOOL  bChecked;          // display the check mark?
  BOOL  bComplete;         // is it a full track, or just a segment?
  int   trackNo;           // ignored by TrackWnd
} ADDTRACK, *PADDTRACK, *LPADDTRACK;

int InitTrackWnd( HINSTANCE hInst );
HWND createTrackWnd( HWND hParent, HINSTANCE hInst, int idCtrl, LPRECT lprc );
void addTrack( HWND hWnd, LPADDTRACK lpAddTrack );

#endif
