/*
 * wrqueue.h - Copyright (C) 1999,2000 Jay A. Key
 *
 * Header file for simple wrap-around queue used by CD-DA X-Tractor
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
#ifndef _WRQUEUE_H_
#define _WRQUEUE_H_

#include <windows.h>

#ifndef FAR
#define FAR
#endif

typedef struct
{
  unsigned char *data;
  unsigned char *head;
  unsigned char *tail;
  int dataLen;                    /* max size of queue */
  int bytesUsed;
  CRITICAL_SECTION inUse;
  HANDLE hWaitForDequeue;
  int iNumWait;
} WRQUEUE, *PWRQUEUE, FAR *LPWRQUEUE;

void wrqSetWait( LPWRQUEUE, HANDLE, int );
int wrqInitQueue( LPWRQUEUE q, int max );
void wrqDeinitQueue( LPWRQUEUE q );
int wrqFreeSpace( LPWRQUEUE q );
int wrqEnqueue( LPWRQUEUE q, unsigned char *buf, int numBytes );
int wrqDequeue( LPWRQUEUE q, unsigned char **buf, int max );
int wrqNumUsed( LPWRQUEUE q );

#endif
