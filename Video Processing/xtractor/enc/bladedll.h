/*
  
  bladedll.h
  
  +++++++++++++++++++++++++++
  +   Blade's Encoder DLL   +
  +++++++++++++++++++++++++++
  
  ------------------------------------------------------
  - Version 1.00 (7 November 1998) - Jukka Poikolainen -
  ------------------------------------------------------
  
  Initial version
  
  ------------------------------------------------------
  - Version x.xx (x xxxxxxxx xxxx) - xxxxx xxxxxxxxxxx -
  ------------------------------------------------------
  
*/
/*
 * JAK - Feb 1999: Original file slightly modified for use with
 *                 Mingw32/CygWin compilers
 * JAK - Jan 2000: Modified for lame_enc.dll
 * JAK - May 2000: Added prototype for beWriteVBRHeader()
 * JAK - Jun 2000: Extended for use with vorb_enc.dll
 * JAK - Apr 2001: Modified for Vorbis beta 4
 */

#ifndef ___BLADEDLL_H_INCLUDED___

#define ___BLADEDLL_H_INCLUDED___

#pragma pack(push)
#pragma pack(1)

#ifndef __GNUC__
#define PACKED
#endif

/* encoding formats */

#define         BE_CONFIG_MP3          0
#define         BE_CONFIG_LAME         256
#define         BE_CONFIG_VORBIS       512

/* type definitions */

typedef         unsigned long          HBE_STREAM;
typedef         HBE_STREAM            *PHBE_STREAM;
typedef         unsigned long          BE_ERR;

/* error codes */

#define         BE_ERR_SUCCESSFUL      0x00000000
#define         BE_ERR_INVALID_FORMAT  0x00000001
#define         BE_ERR_INVALID_FORMAT_PARAMETERS 0x00000002
#define         BE_ERR_NO_MORE_HANDLES 0x00000003
#define         BE_ERR_INVALID_HANDLE  0x00000004
#define         BE_ERR_BUFFER_TOO_SMALL 0x00000005

/* other constants */

#define		BE_MAX_HOMEPAGE			256

/* format specific variables */

#define  BE_MP3_MODE_STEREO          0
#define  BE_MP3_MODE_JSTEREO         1
#define  BE_MP3_MODE_DUALCHANNEL     2
#define  BE_MP3_MODE_MONO            3

#define  MPEG1    1
#define  MPEG2    0

/* vorb_enc.dll struct version */
#define  VORBENCSTRUCTVER             2


typedef enum {
  NORMAL_QUALITY=0,
  LOW_QUALITY,
  HIGH_QUALITY,
  VOICE_QUALITY,
} MPEG_QUALITY;


typedef struct	{
  DWORD	dwConfig;              // BE_CONFIG_XXXXX
  union {
    struct {  
      DWORD  dwSampleRate;     // 48000, 44100 and 32000 allowed
      BYTE   byMode;           // BE_MP3_MODE_STEREO, BE_MP3_MODE_DUALCHANNEL,
                               // BE_MP3_MODE_MONO
      WORD   wBitrate;         // 32, 40, 48, 56, 64, 80, 96, 112, 128,
                               // 160, 192, 224, 256 and 320 allowed
      BOOL   bPrivate;		
      BOOL   bCRC;
      BOOL   bCopyright;
      BOOL   bOriginal;
    } PACKED mp3;  // BE_CONFIG_MP3

    struct {
      // STRUCTURE INFORMATION
      DWORD  dwStructVersion;
      DWORD  dwStructSize;

      // BASIC ENCODER SETTINGS
      DWORD  dwSampleRate;      // depends on dwMPEGVersion
      DWORD  dwReSampleRate;    // downsample rate, 0=encoder decides
      INT    nMode;             // BE_MP3_MODE_STEREO, BE_MP3_MODE_DUALCHANNEL,
                                // BE_MP3_MODE_MONO
      DWORD  dwBitrate;         // CBR bitrate, VBR min bitrate
      DWORD  dwMaxBitrate;      // CBR ignored, VBR max bitrate
      MPEG_QUALITY nQuality;    // NORMAL, HIGH, LOW, VOICE
      DWORD  dwMpegVersion;     // MPEG1 or MPEG2
      DWORD  dwPsyModel;        // currently not used
      DWORD  dwEmphasis;        // currently not used

      // BIT STREAM SETTINGS
      BOOL   bPrivate;          // Set Private Bit
      BOOL   bCRC;              // Insert CRC
      BOOL   bCopyright;        // Set copyright bit
      BOOL   bOriginal;         // Set original bit

      // VBR STUFF
      BOOL   bWriteVBRHeader;   // Write XING VBR header
      BOOL   bEnableVBR;        // Use VBR encoding
      INT    nVBRQuality;       // VBR quality 0..9

      BYTE   btReserved[255];   // Reserved for future use
    } LHV1;

    struct {
      int version;              // set to VORBENCSTRUCTVER
      int channels;             // CD audio == 2
      long rate;                // CD audio == 44100

      char *szTitle;            // track title
      char *szVersion;          // used to designate mult. versions of same
                                // track
      char *szAlbum;            // Album name
      char *szArtist;           // Artist's name
      char *szOrganization;     // Organization (or record label)
      char *szDescription;      // short description of the track contents
      char *szGenre;            // text indication of the genre
      char *szDate;             // date the track was recorded
      char *szLocation;         // place where the track was recorded
      char *szCopyright;        // copyright info
      int mode;                 // sets which info_* to use 0 = A, ...
                                // According to Monty, the info_* structs
                                // are a hack, and will likely go away.
      long minbitrate;
      long maxbitrate;
      long nominalbitrate;
    } vorb;

    struct {
      DWORD  dwSampleRate;
      BYTE   byMode;
      WORD   wBitrate;
      BYTE   byEncodingMethod;
    } PACKED aac;
    
  } PACKED format;
  
} PACKED BE_CONFIG, *PBE_CONFIG;

typedef struct	{
  
  // BladeEnc DLL Version number
  
  BYTE	byDLLMajorVersion;
  BYTE	byDLLMinorVersion;
  
  // BladeEnc Engine Version Number
  
  BYTE	byMajorVersion;
  BYTE	byMinorVersion;
  
  // DLL Release date
  
  BYTE	byDay;
  BYTE	byMonth;
  WORD	wYear;
  
  // BladeEnc	Homepage URL
  
  CHAR	zHomepage[BE_MAX_HOMEPAGE + 1];	
  
} PACKED BE_VERSION, *PBE_VERSION;			

#ifndef _BLADEDLL

typedef BE_ERR	(*BEINITSTREAM)		(PBE_CONFIG, PDWORD, PDWORD, PHBE_STREAM);
typedef BE_ERR	(*BEENCODECHUNK)	(HBE_STREAM, DWORD, PSHORT, PBYTE, PDWORD);
typedef BE_ERR	(*BEDEINITSTREAM)	(HBE_STREAM, PBYTE, PDWORD);
typedef BE_ERR	(*BECLOSESTREAM)	(HBE_STREAM);
typedef VOID	(*BEVERSION)		(PBE_VERSION);
typedef BE_ERR  (*BEWRITEVBRHEADER)     (LPCSTR);

#define	TEXT_BEINITSTREAM	"beInitStream"
#define	TEXT_BEENCODECHUNK	"beEncodeChunk"
#define	TEXT_BEDEINITSTREAM	"beDeinitStream"
#define	TEXT_BECLOSESTREAM	"beCloseStream"
#define	TEXT_BEVERSION		"beVersion"
#define TEXT_BEWRITEVBRHEADER   "beWriteVBRHeader"

/*	
	BE_ERR	beInitStream(PBE_CONFIG pbeConfig, PDWORD dwSamples, PDWORD dwBufferSize, PHBE_STREAM phbeStream);
	BE_ERR	beEncodeChunk(HBE_STREAM hbeStream, DWORD nSamples, PSHORT pSamples, PBYTE pOutput, PDWORD pdwOutput);
	BE_ERR	beDeinitStream(HBE_STREAM hbeStream, PBYTE pOutput, PDWORD pdwOutput);
	BE_ERR	beCloseStream(HBE_STREAM hbeStream);
	VOID	beVersion(PBE_VERSION pbeVersion);		
*/
	
#else

__declspec(dllexport) BE_ERR	beInitStream(PBE_CONFIG pbeConfig, PDWORD dwSamples, PDWORD dwBufferSize, PHBE_STREAM phbeStream);
__declspec(dllexport) BE_ERR	beEncodeChunk(HBE_STREAM hbeStream, DWORD nSamples, PSHORT pSamples, PBYTE pOutput, PDWORD pdwOutput);
__declspec(dllexport) BE_ERR	beDeinitStream(HBE_STREAM hbeStream, PBYTE pOutput, PDWORD pdwOutput);
__declspec(dllexport) BE_ERR	beCloseStream(HBE_STREAM hbeStream);
__declspec(dllexport) VOID		beVersion(PBE_VERSION pbeVersion);

#endif

#pragma pack(pop)

#endif
