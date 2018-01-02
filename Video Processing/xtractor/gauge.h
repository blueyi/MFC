/*
 * gauge.h - Copyright (C) 1999,2000 Jay A. Key
 *
 * Interface to gauge.c, a 3-D look gauge control
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
#ifndef _GAUGE_H_INC
#define _GAUGE_H_INC

#include <windows.h>

#define GM_SETRANGE     (WM_USER+100)
#define GM_GETRANGE     (WM_USER+101)
#define GM_SETTEXTCOLOR (WM_USER+102)
#define GM_GETTEXTCOLOR (WM_USER+103)
#define GM_SETBKCOLOR   (WM_USER+104)
#define GM_GETBKCOLOR   (WM_USER+105)
#define GM_SETPOS       (WM_USER+106)
#define GM_GETPOS       (WM_USER+107)
#define GM_SETDELTAPOS  (WM_USER+108)
#define GM_DISPPCT      (WM_USER+109)

#endif // _GAUGE_H_INC
