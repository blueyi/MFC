/*
 * wrqueue.c - Copyright (C) 1999,2000 Jay A. Key
 *
 * Implements a simple wrap-around queue.  Add to the tail and read from
 * the head.
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
#include <stdio.h>
#include <malloc.h>
#include "wrqueue.h"

int wrqInitQueue( LPWRQUEUE q, int max )
{
  if ( !q )
    return 0;

  memset( q, 0, sizeof(*q) );

  if ( max <= 0 )
    return 0;

  q->data = (unsigned char *)malloc( max );
  if ( !q->data )
    return 0;

  q->head = q->tail = q->data;
  q->dataLen = max;

  memset( q->data, ' ', max );

  InitializeCriticalSection( &q->inUse );

  return -1;
}

void wrqDeinitQueue( LPWRQUEUE q )
{
  if ( !q )
    return;

  DeleteCriticalSection( &q->inUse );

  if ( q->data && q->dataLen )
    free( q->data );

  memset( q, 0, sizeof(*q) );
}


int wrqFreeSpace( LPWRQUEUE q )
{
  int retVal;

  if ( !q )
    return 0;
  EnterCriticalSection( &q->inUse );
  retVal = q->dataLen - q->bytesUsed;
  LeaveCriticalSection( &q->inUse );

  return retVal;
}

int wrqNumUsed( LPWRQUEUE q )
{
  int retVal;

  if ( !q )
    return 0;

  EnterCriticalSection( &q->inUse );
  retVal = q->bytesUsed;
  LeaveCriticalSection( &q->inUse );

  return retVal;
}


/*
 * returns the number of bytes enqueued
 */
int wrqEnqueue( LPWRQUEUE q, unsigned char *buf, int numBytes )
{
  unsigned char *end;
  int retVal = 0;

  if ( !q || !buf )
    return 0;

  EnterCriticalSection( &q->inUse );

  //debugQueue( q );

  end = q->data + q->dataLen;

  if ( numBytes > ( q->dataLen - q->bytesUsed ) )
    numBytes = q->dataLen - q->bytesUsed;

  q->bytesUsed += numBytes;
  retVal = numBytes;

  /* if it all fits without wrap-around, just copy it */
  if ( q->tail + numBytes < end )
    {
      memcpy( q->tail, buf, numBytes );
      q->tail += numBytes;
    }
  else
    {
      memcpy( q->tail, buf, end - q->tail );
      buf += (end - q->tail);
      numBytes -= (end - q->tail);
      q->tail = q->data;
      memcpy( q->tail, buf, numBytes );
      q->tail += numBytes;
    }

  //debugQueue( q );
  LeaveCriticalSection( &q->inUse );
  return retVal;
}


int wrqDequeue( LPWRQUEUE q, unsigned char **buf, int max )
{
  unsigned char *end;
  int retVal = 0;

  if ( !q || !buf || !q->bytesUsed  || !*buf )
    return 0;

  EnterCriticalSection( &q->inUse );

  //debugQueue( q );

  end = q->data + q->dataLen;

  if ( max > q->bytesUsed )
    max = q->bytesUsed;
  retVal = max;
  q->bytesUsed -= max;

  if ( q->head + max < end )
    {
#if 1
      memcpy( *buf, q->head, max );
#else
      // return a pointer to the memory instead of copying it,
      // to try and speed up.  Since 1 min of audio represents
      // 10 MB of data, this could have a rather large effect
      *buf = q->head;
#endif
      q->head += max;
    }
  else
    {
      unsigned char *p;

      p = *buf;

      memcpy( p, q->head, end - q->head );
      p += (end - q->head);
      max -= (end - q->head);
      q->head = q->data;
      memcpy( p, q->head, max );
      q->head += max;
    }

  if ( q->bytesUsed == 0 )
    q->head = q->tail = q->data;

  //debugQueue( q );

#if 0
  if ( q->hWaitForDequeue && (wrqNumUsed( q ) < 15000) )
#else
  if ( q->hWaitForDequeue && (wrqFreeSpace( q ) > q->iNumWait) )
#endif
    {
      SetEvent( q->hWaitForDequeue );
      q->hWaitForDequeue = NULL;
    }
  LeaveCriticalSection( &q->inUse );

  return retVal;
}

#if 0
int debugQueue( LPWRQUEUE q )
{
  int i;

  printf( "--------------------\n" );
  printf( "data = 0x%08X, head = 0x%08X, tail = 0x%08X\n", q->data,
	  q->head, q->tail );
  printf( "dataLen = %d, bytesUsed = %d, end = 0x%08X\n", q->dataLen,
	  q->bytesUsed, q->data + q->dataLen );
  for( i = 0; i < q->dataLen; i++ )
    {
      printf( "%c", q->data[i] );
    }
  printf( "\n--------------------\n" );

  return 0;
}
#endif


void wrqSetWait( LPWRQUEUE q, HANDLE hWait, int numBytes )
{
  if ( !q )
    return;

  EnterCriticalSection( &q->inUse );

  q->hWaitForDequeue = hWait;
  q->iNumWait = numBytes;

  LeaveCriticalSection( &q->inUse );
}
