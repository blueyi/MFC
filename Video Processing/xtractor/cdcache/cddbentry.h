#ifndef __CDDBENTRY_H_INC
#define __CDDBENTRY_H_INC

#include <windows.h>

#include "growstring.h"


class CdTrack
{
public:
  CdTrack() { _offset = 0; _title = new GrowString(); _extt = NULL; };
  ~CdTrack() { if ( _title ) delete _title; if ( _extt ) delete _extt; };
  void reset() { if ( _title ) _title->reset(); if ( _extt ) _extt->reset(); _offset = 0; };

  long _offset;
  GrowString *_title;
  GrowString *_extt;
};


class CddbEntry
{
public:
  CddbEntry( char *sz );
  ~CddbEntry();
  void reset( void );
  CdTrack *track( int i ) { if ( i<0 || i>99) return NULL; return _tracks[i]; };
  GrowString *dtitle() { return _dtitle; };
  GrowString *artist() { return _artist; };
  GrowString *title() { return _title; };
  GrowString *dyear() { return _dyear; };
  GrowString *dgenre() { return _dgenre; };
  long version() { return _version; };
  unsigned char numtracks() { return _numtracks; };
  long length() { return _length; };
  long discid(int i) { if ( i<0 || i>9 ) return 0; return _discid[i]; };
  int parse();
  GrowString *extd() { return _extd; };
  void SetEntry( char *szEntry );
  void setOption( int opt, int val );

private:
  int parseLine( char *szBuf );
  int parseCommentLine( char *szBuf );
  int parseDataLine( char *szBuf );
  int readTrackOffset( char *szBuf);
  void parseDTitle( void );

  BOOL _checkCdLen;
  BOOL _protoLevel5;

  int _state;
  int _prevTrackNo;
  int _offIdx;
  BOOL _bComment;

  char *_szEntry;
  int _maxEntryLen;
  GrowString *_artist;
  GrowString *_title;
  GrowString *_dtitle;
  GrowString *_extd;
  GrowString *_dgenre;
  GrowString *_dyear;
  long _version;
  unsigned char _numtracks;
  long _length;
  int _numIds;
  long _discid[10];
  CdTrack *_tracks[100];
};


#endif