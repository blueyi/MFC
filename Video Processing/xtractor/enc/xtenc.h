/*
 * xtenc.h - Copyright (C) 2000 Jay A. Key
 *
 * Interface to xtenc.dll
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
#ifndef _XTENC_H_INC
#define _XTENC_H_INC

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  XT_FMT_RAW = 0,
  XT_FMT_WAV,
  XT_FMT_MP3,
  XT_FMT_OGG,
} xt_formats;

typedef enum {
  XT_ENC_RAW = 0,
  XT_ENC_WAV,
  XT_ENC_LAME1,
  XT_ENC_LAME2,
  XT_ENC_BLADE,
  XT_ENC_VORBIS,
} xt_encoders;


typedef enum {
  XT_OPT_BASEDIR = 0,
  XT_OPT_FILENAME,
  XT_OPT_FILEEXT,
  XT_OPT_OPENMODE,
  XT_OPT_UPPERBITRATE,
  XT_OPT_NOMINALBITRATE,
  XT_OPT_LOWERBITRATE,
  XT_OPT_ID3LEVEL,
  XT_OPT_ID3GENRE,
  XT_OPT_ID3YEAR,
  XT_OPT_ARTIST,
  XT_OPT_ALBUM,
  XT_OPT_TRACK,
  XT_OPT_CBITRATE,
  XT_OPT_MAXBITRATE,
  XT_OPT_MP3MODE,
  XT_OPT_ORIGINAL,
  XT_OPT_CRC,
  XT_OPT_COPYRIGHT,
  XT_OPT_PRIVATE,
  XT_OPT_MPEGQUALITY,
  XT_OPT_MPEGVERSION,
  XT_OPT_ENABLEVBR,
  XT_OPT_VBRQUALITY,
  XT_OPT_VORBMODE,
  XT_OPT_NOWRITE,
  XT_OPT_VBITRATE,         // vorbis VBR bitrate
  XT_OPT_TRACKNUM,
  XT_OPT_FILEDIR,          // appended to the base dir, may be created if not exists
  XT_OPT_LAME_MODE
} xt_options;


typedef int HXTENCODER;

HXTENCODER xtGetEncoder( int which );
int xtSetAsciiOption( HXTENCODER hEnc, int iOpt, char *pszVal );
int xtSetIntOption( HXTENCODER hEnc, int iOpt, int iVal );
int xtOpenOutputFile( HXTENCODER hEnc );
int xtCheckOutputFileExists( HXTENCODER hEnc );
int xtGetOutputFileName( HXTENCODER hEnc, char *szBuf, int len );
int xtEncode( HXTENCODER hEnc, unsigned char *buf, int len );
int xtClose( HXTENCODER hEnc );
int xtFlush( HXTENCODER hEnc );
int xtInit( HXTENCODER hEnc );
int xtFormatAvail( int fmt );
int xtEncoderAvail( int enc );
char *xtGetExtension( HXTENCODER hEnc );
char *xtGetFilename( HXTENCODER hEnc );

#ifdef __cplusplus
}
#endif

#endif
