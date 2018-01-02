/*
 * globals.c - Copyright (C) 1999,2000 Jay A. Key
 *
 * Global variables used by CD-DA X-Tractor
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
#include "akrip/akrip32.h"
#include "enc/bladedll.h"
#include "cdcache/cdcache.h"


int iMajorVer = 0;
int iMinorVer = 24;
char *szVersion = "v0.24";

HINSTANCE ghInstance = NULL;

unsigned char validFnameChar[256];

BOOL bAutoTOC = FALSE;            // Automatically read TOC on startup
BOOL bAutoCheck = FALSE;          // Automatically check all tracks
BOOL bHiColor = FALSE;            // use hi-color toolbar bitmaps

CDLIST cdlist;                    // list of CD drives found on machine
int cdlistIdx;                    // index of currently selected drive

HCDROM hCD = NULL;
BYTE bReadType = CDR_ANY;         // read algorithm to use
DWORD maxRip = 27;                // maximum frames to rip at once
DWORD jitterCheck = 1;            // number of frames to match
DWORD numOverlap = 3;             // number of frames to overlap
DWORD readMode = CDRM_JITTERONERR; // when to do jitter correction

//char szWavOutputDir[MAX_PATH+1] = ".";    // default output to curr. dir
char szMP3OutputDir[MAX_PATH+1] = ".";    // default output to curr. dir

/*
 * MP3 related
 */
// Generic
int iEncoder = 0;                 // which encoder to use
BOOL bWavMirror = FALSE;          // create WAV at same time as MP3?
WORD wBitrate = 192;              // bitrate to use for MP3 encoding
BOOL bCRC = FALSE;                // generate CRC for MP3 frames?
BOOL bID3 = FALSE;                // id3 tagging?
BOOL bCopyright = FALSE;
BOOL bPrivate = FALSE;
BOOL bOriginal = FALSE;
WORD wMode = BE_MP3_MODE_STEREO;

// lame_enc specific items
WORD wMaxBitrate = 320;           // Max. VBR bitrate
WORD wLameMode = BE_MP3_MODE_STEREO;
MPEG_QUALITY nQuality = HIGH_QUALITY;
BOOL bVBR = TRUE;
BOOL bVBRHeader = TRUE;
INT nVBRQuality = 5;

// vorb_enc specific items
WORD wVorbBitrate = 128;          // Bitrate for vorbis
char szVorbVersion[81] = "";
char szVorbOrganization[81] = "";
char szVorbDescription[81] = "";
char szVorbGenre[81] = "";
char szVorbDate[81] = "";
char szVorbLocation[81] = "";
char szVorbCopyright[81] = "";

// about dialog
ATOM atomBmpPanel = 0;
char *szBmpPanel = "ctrlbmppanel";

// CDDB Support
BOOL bCDDB = FALSE;
char szCDDBServer[81] = "freedb.freedb.org";
int iHTTPPort = 80;
char szCGI[81] = "/~cddb/cddb.cgi";
char szSubmitCGI[81] = "/~cddb/submit.cgi";
char szProxyAddr[81] = "";
int iProxyPort = 80;
BOOL bUseProxy = FALSE;
BOOL bSavePass = FALSE;
char szProxyUser[81] = "";
char szProxyPass[17] = "";
BOOL bInCDDBQuery = FALSE;          // when a query thread is open
                                    // should be set to TRUE
char szUserEmail[257] = "";
const char *szCDDBCat[12] = {
  "blues", "classical", "country", "data", "folk", "jazz", "misc",
  "newage", "reggae", "rock", "soundtrack", NULL
};
int iCddbEntryRev = 0;
BOOL bCddbRetrievedGenre = FALSE;
char szCddbRetrievedGenre[12] = "";


BOOL bRippingTracks = FALSE;
BOOL bNiceThreads = TRUE;

BOOL bWritePlaylist = TRUE;
BOOL bUseAlbumName = TRUE;
char szPlaylist[MAX_PATH+1] = "";

char szMangleString[MAX_PATH+1] = "";  // string used for trackname macros

HCDDBENTRY hCddbEntry = NULL;

BOOL bTocRead = FALSE;
TOC msfToc;
TOC lbaToc;
DWORD lastAudioFrame = 0;

char szArtistName[257];
char szAlbumTitle[257];

BOOL bNormalize = FALSE;
int iNormalizePercent = 94;
int iNormalizeScanPercent = 100;