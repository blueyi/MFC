#include <windows.h>
#include <stdio.h>
#include "akrip/akrip32.h"

FILE *fpOut;

int main( void )
{
  CDLIST cdlist;
  int i;
  
  fpOut = fopen( "toc.txt", "wt" );
  
  ZeroMemory( &cdlist, sizeof(cdlist) );
  cdlist.max = MAXCDLIST;
  GetCDList( &cdlist );
  
  for( i = 0; i < cdlist.num; i++ )
  {
    dumpToc( i, &cdlist.cd[i] );
  }
  
  fclose( fpOut );
  
  return 0;
}

void MSB2DWORD( DWORD *d, BYTE *b )
{
  DWORD retVal;

  retVal = (DWORD)b[0];
  retVal = (retVal<<8) + (DWORD)b[1];
  retVal = (retVal<<8) + (DWORD)b[2];
  retVal = (retVal<<8) + (DWORD)b[3];

  *d = retVal;
}

int dumpToc( int i, CDREC *pcd )
{
  HCDROM hCD;
  GETCDHAND getcdhand;
  TOC toc;
  
  ZeroMemory( &getcdhand, sizeof(getcdhand) );
  
  getcdhand.size = sizeof(getcdhand);
  getcdhand.ver = 1;
  getcdhand.ha = pcd->ha;
  getcdhand.tgt = pcd->tgt;
  getcdhand.lun = pcd->lun;
  getcdhand.readType = CDR_ANY;
  hCD = GetCDHandle( &getcdhand );
  
  if ( hCD == NULL )
  {
    return -1;
  }
  
  ModifyCDParms( hCD, CDP_MSF, FALSE );
  ZeroMemory( &toc, sizeof(toc) );
  ReadTOC( hCD, &toc );
  fprintf( fpOut, "CD #%d, LBA Addressing\n", i );
  fprintf( fpOut, "  firstTrack: %d, lastTrack: %d, tocLen: %d\n",
    toc.firstTrack, toc.lastTrack, toc.tocLen );
  for( i = 0; i < 100; i++ )
  {
    DWORD dwAddr;
    TOCTRACK *t;
    t = &toc.tracks[i];
    MSB2DWORD( &dwAddr, t->addr );
    fprintf( fpOut, "  track %3d: %08x (%d), flag: %s\n",
      t->trackNumber,
      dwAddr,
      dwAddr,
      ((t->ADR & 0x07) == 4)?"data":"audio"
    );
  }
  fprintf( fpOut, "\n" );
    
  ModifyCDParms( hCD, CDP_MSF, TRUE );
  ZeroMemory( &toc, sizeof(toc) );
  ReadTOC( hCD, &toc );
  fprintf( fpOut, "CD #%d, MSF Addressing\n", i );
  fprintf( fpOut, "  firstTrack: %d, lastTrack: %d, tocLen: %d\n",
    toc.firstTrack, toc.lastTrack, toc.tocLen );
  for( i = 0; i < 100; i++ )
  {
    DWORD dwAddr;
    TOCTRACK *t;
    t = &toc.tracks[i];
    fprintf( fpOut, "  track %3d: %02d:%02d:%02d, flag: %s\n",
      t->trackNumber,
      t->addr[1], t->addr[2], t->addr[3],
      ((t->ADR & 0x07) == 4)?"data":"audio"
    );
  }
  fprintf( fpOut, "\n--------------------------------------\n" );
    
  CloseCDHandle( hCD );
  return 0;
}