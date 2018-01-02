/*
 * threads.h - Copyright (C) 1999,2000 Jay A. Key
 *
 * Macros for thread creation, allowing the use of _beginthreadex when using
 * the MSVC runtime, and CreateThread when using CRT.
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
#ifndef __THREADS_H_INC
#define __THREADS_H_INC

#include <windows.h>
#include <process.h>


#ifdef __MSVCRT__
  typedef unsigned (__stdcall *PTHREAD_START) (void *);
  #define CREATETHREAD( a, b, c, d, e, f )  \
          ((HANDLE)_beginthreadex(          \
            (void *)(a),                    \
	    (unsigned)(b),                  \
            (PTHREAD_START)(c),             \
            (void *)(d),                    \
            (unsigned)(e),                  \
            (unsigned *)(f)))
#else
  #define CREATETHREAD( a, b, c, d, e, f )  \
          (CreateThread(                    \
            (LPSECURITY_ATTRIBUTES)(a),     \
	    (DWORD)(b),                     \
            (LPTHREAD_START_ROUTINE)(c),    \
            (PVOID)(d),                     \
            (DWORD)(e),                     \
            (PDWORD)(f)))
#endif


#endif
