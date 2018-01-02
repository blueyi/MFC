#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "cddbentry.h"
#include "cdcache.h"

/*
 * parsecddb.cpp
 * 
 * A "C" interface to the cddb entry parser library.  Clients should
 * first create a cddb entry object by calling cddbNewEntry().
 * The client can then parse the text stored in the entry by calling
 * cddbParseEntry().  When done with the entry, it should be 
 * released by calling cddbFreeEntry().
 */


#ifdef __cplusplus
extern "C" {
#endif

void dbprintf( char *fmt, ... );


__declspec(dllexport) LPVOID cddbNewEntry( char *szEntry )
{
  CddbEntry *retVal = new CddbEntry( szEntry );
  return (LPVOID)retVal;
}


__declspec(dllexport) void cddbFreeEntry( LPVOID pArg )
{
  CddbEntry *pCddbEntry = (CddbEntry *)pArg;

  if ( pCddbEntry )
    delete pCddbEntry;
}


/*
 * Sets the text to be parsed.
 */
__declspec(dllexport) BOOL cddbSetEntry( LPVOID pObject, char *szEntry )
{
  CddbEntry *pCddbEntry = (CddbEntry *)pObject;
  
  if ( !pCddbEntry )
    return FALSE;
  
  pCddbEntry->SetEntry( szEntry );
  
  return TRUE;
}


__declspec(dllexport) BOOL cddbParseEntry( LPVOID pObject )
{
  CddbEntry *pCddbEntry = (CddbEntry *)pObject;
  
  if ( !pObject )
    return FALSE;
  
  return (BOOL)pCddbEntry->parse();
}


// copies up to len chars, saving room for a null-terminator if necessary
__declspec(dllexport) BOOL cddbGetArtist( LPVOID pObj, char *szBuf, int len )
{
  int n;
  char *p;
  CddbEntry *pCddbEntry = (CddbEntry *)pObj;
  GrowString *g;
  
  if ( !pObj || !szBuf )
    return FALSE;
  
  g = pCddbEntry->artist();
  if ( !g )
    return FALSE;
  
  p = g->strValue();
  if ( !p )
    return FALSE;
  n = lstrlen( p );
  strncpy( szBuf, p, len );
  if ( n >= len )
    szBuf[len-1] = '\0';
  
  return TRUE;
}


// copies up to len chars, saving room for a null-terminator if necessary
__declspec(dllexport) BOOL cddbGetTitle( LPVOID pObj, char *szBuf, int len )
{
  int n;
  char *p;
  CddbEntry *pCddbEntry = (CddbEntry *)pObj;
  GrowString *g;
  
  if ( !pObj || !szBuf )
    return FALSE;
  
  g = pCddbEntry->title();
  if ( !g )
    return FALSE;
  
  p = g->strValue();
  if ( !p )
    return FALSE;
  n = lstrlen( p );
  strncpy( szBuf, p, len );
  if ( n >= len )
    szBuf[len-1] = '\0';
  
  return TRUE;
}


__declspec(dllexport) BOOL cddbGetTrackTitle( LPVOID pObj, int trackNo, char *szBuf, int len )
{
  int n;
  char *p;
  CddbEntry *pCddbEntry = (CddbEntry *)pObj;
  CdTrack *pTrack;
  GrowString *g;
  
  if ( !pObj || !szBuf )
    return FALSE;
  
  pTrack = pCddbEntry->track( trackNo );
  if ( pTrack == NULL )
    return FALSE;
  
  g = pTrack->_title;;
  if ( !g )
    return FALSE;
  
  p = g->strValue();
  if ( !p )
    return FALSE;
  n = lstrlen( p );
  strncpy( szBuf, p, len );
  if ( n >= len )
    szBuf[len-1] = '\0';
  
  return TRUE;
}

__declspec(dllexport) BOOL cddbSetOption( LPVOID pObj, int opt, int val )
{
  CddbEntry *pEntry = (CddbEntry *)pObj;
  
  if ( pEntry == NULL )
    return FALSE;
  
  pEntry->setOption( opt, val );
  
  return TRUE;
}

__declspec(dllexport) int cddbGetNumTracks( LPVOID pObj )
{
  CddbEntry *pEntry = (CddbEntry *)pObj;

  if ( pEntry == NULL )
    return 0;
  
  return (int)pEntry->numtracks();
}


__declspec(dllexport) int cddbGetEntryVersion( LPVOID pObj )
{
  CddbEntry *pEntry = (CddbEntry *)pObj;
  
  if ( pEntry == NULL )
    return 0;
  
  return (int)pEntry->version();
}

__declspec(dllexport) int cddbGetDYear( HCDDBENTRY pObj )
{
  CddbEntry *pEntry = (CddbEntry *)pObj;
  
  if ( pEntry == NULL )
    return 0;
  
  GrowString *g = pEntry->dyear();
  if ( g != NULL )
    return atoi( g->strValue() );
  return 0;
}

__declspec(dllexport) BOOL cddbGetDGenre( HCDDBENTRY pObj, char *szBuf, int len )
{
  CddbEntry *pEntry = (CddbEntry *)pObj;
  
  if ( pEntry == NULL || szBuf == NULL )
    return FALSE;
  
  GrowString *g = pEntry->dgenre();
  if ( g != NULL )
  {
    lstrcpyn( szBuf, g->strValue(), len );
    return TRUE;
  }
  return FALSE;
}


#ifdef __cplusplus
}
#endif
