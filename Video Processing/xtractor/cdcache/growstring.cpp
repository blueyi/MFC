#include <windows.h>
#include "growstring.h"

GrowString::GrowString()
{
  _s = new char[64];
  if ( _s )
  {
    memset( _s, 0, 64 );
    _max = 64;
    _len = 0;
  }
  else
    _max = _len = 0;
}

GrowString::GrowString( char *szVal )
{
  _len = lstrlen( szVal );
  _max = 129 + _len;
  _s = new char[_max];
  strcpy( _s, szVal );
}

GrowString::~GrowString()
{
  delete[] _s;
}

char *GrowString::append( char *szVal )
{
  int len = lstrlen( szVal );

  if ( (_len + len) >= _max )
  {
    len = len + _len + 128;
    char *pTmp = new char[len];
    memset( pTmp, 0, len );
    strcpy( pTmp, _s );
    _max = len;
    delete[] _s;
    _s = pTmp;
  }
  strcat( _s, szVal );
  _len += strlen( szVal );

  return _s;
}
