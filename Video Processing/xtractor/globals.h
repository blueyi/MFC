/*
 * globals.h - Copyright (C) 1999,2000 Jay A. Key
 *
 * extern declarations for global variables used throughout the program
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
#ifndef _GLOBALS_G_INC
#define _GLOBALS_G_INC

#include <windows.h>
#include "akrip/akrip32.h"
#include "enc/bladedll.h"
#include "cdcache/cdcache.h"

typedef enum {
  NOENCODER=0,
  BLADE_ENC_DLL,
  LAME_ENC_DLL
} ENCODER;
#define MAXENCODER  LAME_ENC_DLL

extern int iMajorVer;
extern int iMinorVer;
extern char *szVersion;
extern unsigned char validFnameChar[256];
extern HINSTANCE ghInstance;
extern BOOL bAutoTOC;
extern BOOL bAutoCheck;
extern BOOL bHiColor;
extern CDLIST cdlist;
extern int cdlistIdx;
extern HCDROM hCD;
extern BYTE bReadType;
extern DWORD maxRip;
extern DWORD jitterCheck;
extern DWORD numOverlap;
extern DWORD readMode;
extern char szMP3OutputDir[MAX_PATH+1];
extern BOOL bWavMirror;
extern WORD wBitrate;
extern BOOL bCRC;
extern BOOL bID3;
extern BOOL bCopyright;
extern BOOL bPrivate;
extern BOOL bOriginal;
extern int iEncoder;
extern WORD wMaxBitrate;
extern BOOL bVBR;
extern BOOL bVBRHeader;
extern INT nVBRQuality;
extern MPEG_QUALITY nQuality;
extern WORD wMode;
extern WORD wLameMode;

extern ATOM atomBmpPanel;
extern char *szBmpPanel;
extern char szCDDBServer[81];
extern int iHTTPPort;
extern char szProxyAddr[81];
extern int iProxyPort;
extern BOOL bUseProxy;
extern BOOL bSavePass;
extern char szProxyUser[81];
extern char szProxyPass[17];
extern BOOL bInCDDBQuery;
extern char szCGI[81];
extern char szSubmitCGI[81];
extern BOOL bCDDB;
extern char szUserEmail[257];
extern const char *szCDDBCat[12];
extern BOOL bRippingTracks;
extern BOOL bNiceThreads;
extern BOOL bWritePlaylist;
extern BOOL bUseAlbumName;
extern char szPlaylist[MAX_PATH+1];
extern char szMangleString[MAX_PATH+1];
extern WORD wVorbBitrate;
extern char szVorbVersion[81];
extern char szVorbOrganization[81];
extern char szVorbDescription[81];
extern char szVorbGenre[81];
extern char szVorbDate[81];
extern char szVorbLocation[81];
extern char szVorbCopyright[81];
extern HCDDBENTRY hCddbEntry;
extern int iCddbEntryRev;
extern BOOL bCddbRetrievedGenre;
extern char szCddbRetrievedGenre[12];

extern BOOL bTocRead;
extern TOC msfToc;
extern TOC lbaToc;
extern DWORD lastAudioFrame;

extern char szArtistName[257];
extern char szAlbumTitle[257];

extern BOOL bNormalize;
extern int iNormalizePercent;
extern int iNormalizeScanPercent;

#endif
