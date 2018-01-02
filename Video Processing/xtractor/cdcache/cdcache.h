// Import definitions for cdcache.dll
#ifndef __CDCACHE_H_INC
#define __CDCACHE_H_INC

#include <windows.h>

typedef LPVOID HCDDBENTRY;

#ifndef _MAKING_DLL
__declspec(dllimport) BOOL cddbSetOption( HCDDBENTRY pObj, int opt, int val );
__declspec(dllimport) HCDDBENTRY cddbNewEntry( char *szEntry );
__declspec(dllimport) void cddbFreeEntry( HCDDBENTRY pArg );
__declspec(dllimport) BOOL cddbSetEntry( HCDDBENTRY pObject, char *szEntry );
__declspec(dllimport) BOOL cddbParseEntry( HCDDBENTRY pObject );
__declspec(dllimport) BOOL cddbGetArtist( HCDDBENTRY pObj, char *szBuf, int len );
__declspec(dllimport) BOOL cddbGetTitle( HCDDBENTRY pObj, char *szBuf, int len );
__declspec(dllimport) BOOL cddbGetTrackTitle( LPVOID pObj, int trackNo, char *szBuf, int len );
__declspec(dllexport) int cddbGetNumTracks( LPVOID pObj );
__declspec(dllexport) int cddbGetEntryVersion( LPVOID pObj );
__declspec(dllexport) int cddbGetDYear( HCDDBENTRY pObj );
__declspec(dllexport) BOOL cddbGetDGenre( HCDDBENTRY pObj, char *szBuf, int len );
#endif

#define CDCACHE_OPT_CHECKCDLEN    100
#define CDCACHE_OPT_PROTOLEVEL5   101


#endif