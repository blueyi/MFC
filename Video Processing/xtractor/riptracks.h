/*
 * riptracks.h - Copyright (C) 1999,2000 Jay A. Key
 *
 * Interface to riptracks.c
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
#ifndef _RIPTRACKS_H_INC
#define _RIPTRACKS_H_INC

#include <windows.h>
#include <stdio.h>
#include <time.h>
#include "wrqueue.h"
#include "enc/xtenc.h"

#define WM_TRACKDONE   (WM_USER+9090)
#define WM_CANCELRIP   (WM_USER+9091)

/*
 * WAV file header format
 */
typedef struct
{
  BYTE  riff[4];            /* must be "RIFF"                */
  DWORD len;                /* #bytes + 44 - 8               */
  BYTE  cWavFmt[8];         /* must be "WAVEfmt"             */
  DWORD dwHdrLen;
  WORD  wFormat;
  WORD  wNumChannels;
  DWORD dwSampleRate;
  DWORD dwBytesPerSec;
  WORD  wBlockAlign;
  WORD  wBitsPerSample;
  BYTE  cData[4];            /* must be "data"               */
  DWORD dwDataLen;           /* #bytes                       */
} PACKED WAVHDR, *PWAVHDR, *LPWAVHDR;

#define RIPTHREAD 0
#define ENCTHREAD 1

typedef struct
{
  HXTENCODER hEnc;
  FILE *fpOut;
  WRQUEUE q;
  DWORD startFrame;
  DWORD endFrame;
  DWORD trackLen;
  DWORD totalWritten;
  int idx;
  time_t tstart, tnow;
  double pctDone, pctLeft;
  DWORD hrs, min, sec;
  BOOL bForceRipExit;
  BOOL bForceEncExit;
  BOOL bNormalExit;
  int status;
  HWND hDlg;
  HANDLE aHandles[2];  // Rip = 0, Enc = 1
  HANDLE hRipCancel;
  CRITICAL_SECTION cs;
  BOOL bOldLame;
  DWORD maxbufread;
  DWORD queueSize;
  BOOL bRip2Memory;
  char fname[MAX_PATH+1];
} ENCODETHREAD, FAR *LPENCODETHREAD;

#define EST_SUCCESS    0
#define EST_ABORTED    1
#define EST_ERROR      2
#define EST_ENCODERINITERR 3

#endif
