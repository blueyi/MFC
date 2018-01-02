#include <windows.h>
#include <stdio.h>

#include "cdcache.h"

unsigned long readUnsignedLong( char *buf );


int main( void )
{
  HCDDBENTRY hEntry;
  char buf[32] = "ffffffff";
  
  hEntry = cddbNewEntry( "foo" );
  printf( "hEntry == %08x\n", hEntry );
  cddbFreeEntry( hEntry );
  
  printf( "val == %lx\n", readUnsignedLong( "ffffffff" ) );
  
  return 0;
}


unsigned long readUnsignedLong( char *buf )
{
  unsigned long ulRetVal = 0;

  sscanf( buf, "%lx", &ulRetVal );

  return ulRetVal;
}