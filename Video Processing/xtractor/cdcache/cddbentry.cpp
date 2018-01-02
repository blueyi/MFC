#include <windows.h>
#include <stdio.h>
#include "cddbentry.h"
#include "cdcache.h"

//  internal prototypes
int getLine( char *tgt, int maxLen, char **src );
unsigned long readUnsignedLong( char *buf );
int readInt( char *buf );


int getLine( char *tgt, int maxLen, char **src )
{
  if ( !tgt || !src )
    return 0;

  if ( **src == '\0' )
    return 0;

  memset( tgt, 0, maxLen );
  while( maxLen )
  {
    if ( (*src)[0] == '\0' )
      return 1;

    if ( (*src)[0] == '\r' && (*src)[1] == '\n' )
    {
      *src += 2;
      return 1;
    }
    if ( (*src)[0] == '\n' && (*src)[1] == '\r' )
    {
      *src += 2;
      return 1;
    }
    if ( (*src)[0] == '\r' )
    {
      *src += 1;
      return 1;
    }
    if ( (*src)[0] == '\n' )
    {
      *src += 1;
      return 1;
    }
    *tgt++ = *(*src)++;
    maxLen--;
  }

  // if we never got a newline or terminating NULL
  return 0;
}


unsigned long readUnsignedLong( char *buf )
{
  unsigned long ulRetVal = 0;

  buf++;
  sscanf( buf, " %lx", &ulRetVal );

  return ulRetVal;
}


int readInt( char *buf )
{
  int retVal = 0;
  buf++;
  sscanf( buf, " %d", &retVal );
  return retVal;
}

void CddbEntry::SetEntry( char *szEntry )
{
  if ( !szEntry )
    return;
  int len = lstrlen( szEntry );
  if ( ++len > _maxEntryLen )
  {
    char *szTmp = new char[len+128];
    lstrcpy( szTmp, szEntry );
    delete _szEntry;
    _szEntry = szTmp;
    _maxEntryLen = len+128;
  }
  else
  {
    lstrcpy( _szEntry, szEntry );
//    _maxEntryLen = lstrlen(szEntry)+1;
  }
}

CddbEntry::CddbEntry( char *szEntry )
{
  if ( szEntry )
  {
    _szEntry = new char[lstrlen(szEntry)+1];
    lstrcpy( _szEntry, szEntry );
    _maxEntryLen = lstrlen(szEntry)+1;
  }
  else
  {
    _szEntry = new char[32*1024];
    _szEntry[0] = '\0';
    _maxEntryLen = 32*1024;
  }

  _checkCdLen = TRUE;
  _protoLevel5 = TRUE;
  _artist = NULL;
  _title = NULL;
  _dtitle = NULL;
  _dyear = NULL;
  _dgenre = NULL;
  _extd = NULL;
  _version = 0;
  _numtracks = 0;
  _length = 0;
  _state = 0;
  _prevTrackNo = -1;
  _numIds = 0;
  ZeroMemory( _discid, sizeof(_discid) );
  ZeroMemory( _tracks, sizeof(_tracks) );
}

CddbEntry::~CddbEntry()
{
  if ( _szEntry )
    delete _szEntry;

  if ( _artist )
    delete _artist;

  if ( _title )
    delete _title;

  if ( _dtitle )
    delete _dtitle;

  if ( _extd )
    delete _extd;
  
  if ( _dyear )
    delete _dyear;
  
  if ( _dgenre )
    delete _dgenre;

  int i;
  for( i = 0; i < 100; i++ )
  {
    if ( _tracks[i] )
      delete _tracks[i];
  }
}

void CddbEntry::reset( void )
{
  if ( _szEntry )
    _szEntry[0] = '\0';

  if ( _artist )
    _artist->reset();

  if ( _title )
    _title->reset();

  if ( _dtitle )
    _dtitle->reset();

  if ( _extd )
    _extd->reset();

  int i;
  for( i = 0; i < 100; i++ )
  {
    if ( _tracks[i] )
    {
      this->_tracks[i]->reset();
    }
  }

  _version = 0;
  _numtracks = 0;
  _length = 0;
  _state = 0;
  _prevTrackNo = -1;
  _numIds = 0;
  ZeroMemory( _discid, sizeof(_discid) );
}


enum states 
{
  BADSTATE=0,
  DISCID,
  DTITLE,
  DYEAR,
  DGENRE,
  TTITLE,
  EXTD,
  EXTT,
  PLAYORDER
};

int CddbEntry::parseDataLine( char *szBuf )
{
  char *pTmp;
  int i;
  int state = BADSTATE;

  if ( _bComment )
  {
    // check that we read everything we wanted in the comment section
    if ( _state != 4 )
      return 0; 

    // and set the state
    _state = 0;
    _prevTrackNo = -1;
    _bComment = FALSE;
  }

  if ( !strncmp( szBuf, "DISCID=", 7 ) )
    state = DISCID;
  else if ( !strncmp( szBuf, "DTITLE=", 7 ) )
    state = DTITLE;
  else if ( !strncmp( szBuf, "DYEAR=", 6 ) )
    state = DYEAR;
  else if ( !strncmp( szBuf, "DGENRE=", 7 ) )
    state = DGENRE;
  else if ( !strncmp( szBuf, "TTITLE", 6 ) )
    state = TTITLE;
  else if ( !strncmp( szBuf, "EXTD=", 5 ) )
    state = EXTD;
  else if ( !strncmp( szBuf, "EXTT", 4 ) )
    state = EXTT;
  else if ( !strncmp( szBuf, "PLAYORDER=", 10 ) )
    state = PLAYORDER;

  switch( state )
  {
  case BADSTATE:
    return 0;

  case DISCID:
    pTmp = strstr( szBuf, "=" );
//    if ( _state == DISCID )
//      return 0;
    for( i = _numIds; pTmp; i++ )
    {
      if ( i < 10 )
      {
        _discid[i] = readUnsignedLong( pTmp );
        _numIds++;
      }
      pTmp = strstr( pTmp+1, "," );
    }
    if ( _discid[0] == 0 )
      return 0;
    break;

  case DTITLE:
    if ( !_dtitle )
      _dtitle = new GrowString();
    else if ( (_dtitle->length() != 0) && (_state != state) )
      return 0;
    pTmp = strstr( szBuf, "=" );
    _dtitle->append( pTmp+1 );
    break;

  case DYEAR:
    if ( !_dyear )
      _dyear = new GrowString();
    if ( !_protoLevel5 || (_state != DTITLE) )
      return 0;
    pTmp = strstr( szBuf, "=" );
    _dyear->append( pTmp+1 );
    break;
    
  case DGENRE:
    if ( !_dgenre )
      _dgenre = new GrowString();
    if ( !_protoLevel5 || (_state != DYEAR) )
      return 0;
    pTmp = strstr( szBuf, "=" );
    _dgenre->append( pTmp+1 );
    break;

  case TTITLE:
    i = readInt( szBuf+5 );
    if ( i < 0 || i > 99 )
      return 0;
    if ( _state == DTITLE )
    {
      if ( _prevTrackNo != -1 )
        return 0;
    }
    if ( _state == TTITLE )
    {
      if ( (i != _prevTrackNo) && (i != _prevTrackNo+1) )
        return 0;
    }
    if ( !this->_tracks[i] )
      return 0;
    pTmp = strstr( szBuf, "=" );
    if ( !pTmp || !(*(pTmp+1)) )
      return 0;
    if ( this->_tracks[i]->_title == NULL )
      this->_tracks[i]->_title = new GrowString();
    this->_tracks[i]->_title->append( pTmp+1 );
    _prevTrackNo = i;
    break;

  case EXTD:
    if ( _state != TTITLE && _state != EXTD )
      return 0;
    pTmp = strstr( szBuf, "=" );
    if ( !pTmp )
      return 0;
    if ( !(*(pTmp+1)) )
      break;
    if ( this->_extd == NULL )
      _extd = new GrowString();
    _extd->append( pTmp+1 );
    break;

  case EXTT:
    i = readInt( szBuf+3 );
    if ( i < 0 || i > 99 )
      return 0;
    if ( _state != EXTD && _state != EXTT )
      return 0;
    if ( _state == EXTT )
    {
      if ( i != _prevTrackNo && i != _prevTrackNo+1 )
        return 0;
    }
    if ( !this->_tracks[i] )
      return 0;
    pTmp = strstr( szBuf, "=" );
    if ( !pTmp )
      return 0;
    if ( *(pTmp+1) )
    {
      if ( !this->_tracks[i]->_extt )
        this->_tracks[i]->_extt = new GrowString();
      this->_tracks[i]->_extt->append( pTmp+1 );
    }
    _prevTrackNo = i;
    break;


  case PLAYORDER:
    break;
  }

  _state = state;

  return 1;
}


int CddbEntry::parseCommentLine( char *szBuf )
{
  char *p;

  if ( !_bComment )
    return 0;

  switch( _state )
  {
  case 0:
    if ( strstr( szBuf, "Track frame offsets:" ) )
    {
      _state = 1;
      _prevTrackNo = -1;
    }
    break;

  case 1:
    int offset;
    offset = readTrackOffset( szBuf );
    if ( offset == -1 )
    {
      // finished reading tracks
      _numtracks = _prevTrackNo + 1;

      // see if it's a "Disc length:" line
      // there should be a "# " line in between,
      // but a lot of entries seem to be missing it
      _state = 2;

      return parseCommentLine( szBuf );
    }
    else if ( offset == -2 )
    {
      // if it wasn't even a comment, just fail horribly
      _state = -99;
      return 0;
    }
    _prevTrackNo++;
    if ( _tracks[_prevTrackNo] == NULL )
      _tracks[_prevTrackNo] = new CdTrack();
    _tracks[_prevTrackNo]->_offset = offset;
    break;

  case 2:
    // looking for "Disc length:"
    if ( (p = strstr( szBuf, "Disc length:" )) != NULL )
    {
      _state = 3;
      p = p + 12;
      return sscanf( p, "%ld", &_length );
    }
    break;

  case 3:
    // looking for revision
    if ( (p = strstr( szBuf, "Revision:" )) != NULL )
    {
      _state = 4;
      p = p + 9;
      return sscanf( p, "%ld", &_version );
    }
    break;

  case 4:
    break;

  default:
    return 0;
  }

  return 1;
}


int CddbEntry::parseLine( char *szBuf )
{
  if ( !szBuf || !*szBuf )
    return 0;

  if ( szBuf[0] == '#' )
  {
    return parseCommentLine( szBuf );
  }

  return parseDataLine( szBuf );
}


int CddbEntry::parse()
{
  char buf[257];
  char *p;

  if ( !_szEntry || !*_szEntry )
    return 0;

  _offIdx = _state = 0;
  _prevTrackNo = -1;
  _bComment = TRUE;  // initially process comments

  p = _szEntry;
  while( getLine( buf, 257, &p ) )
  {
    if ( !parseLine( buf ) )
      return 0;
  }

  // verify that we have track info for
  // all tracks
  if ( _checkCdLen )
  {
    int i;
    for( i = 0; i < _numtracks; i++ )
    {
      if ( !_tracks[i]->_title->length() )
        return 0;
    }
    if ( (_length*75) <= _tracks[_numtracks-1]->_offset )
      return 0;
  }

  // verify that the disc length is greater
  // than the starting offset of the last track
  parseDTitle();

  return 1;
}


// looking for lines of format "# \t%d
// returns track offset, or -1 on failure
// returns -2 if it wasn't a comment line
int CddbEntry::readTrackOffset( char *szBuf )
{
  int i, retval;
  char c = ' ';

  retval = sscanf( szBuf, "%c %d", &c, &i );

  if ( c == '#' )
  {
    if ( retval == 1 )
      return -1;
    else if ( retval == 2 )
      return i;
  }

  return -2;
}



void CddbEntry::parseDTitle()
{
  char *pTmp;
  char *szDTitle;

  if ( this->_artist == NULL )
    _artist = new GrowString();
  if ( this->_title == NULL )
    _title = new GrowString();

  szDTitle = this->_dtitle->strValue();
  pTmp = strstr( szDTitle, " / " );
  if ( !pTmp )
  {
    _artist->append( szDTitle );
    _title->append( szDTitle );
  }
  else
  {
    pTmp[0] = '\0';
    _artist->append( szDTitle );
    _title->append( pTmp+3 );
  }
}


void CddbEntry::setOption( int opt, int val )
{
  switch( opt )
  {
    case CDCACHE_OPT_CHECKCDLEN:
      _checkCdLen = (BOOL)val;
      break;
    
    case CDCACHE_OPT_PROTOLEVEL5:
      _protoLevel5 = (BOOL)val;
      break;
  }
}