#ifndef _RANGESLIDER_H_INC
#define _RANGESLIDER_H_INC

#include <windows.h>


#define TOPSLIDER    0
#define BOTTOMSLIDER 1

typedef struct {
  NMHDR hdr;
  int which;  // TOPSLIDER, BOTTOMSLIDER
  DWORD start;
  DWORD finish;
  DWORD newStart;
  DWORD newFinish;
} RSBNOTIFY, FAR *LPRSBNOTIFY;


#define RSB_SETMIN       (WM_USER+100)
#define RSB_SETMAX       (WM_USER+101)
#define RSB_GETMIN       (WM_USER+102)
#define RSB_GETMAX       (WM_USER+103)
#define RSB_RESET        (WM_USER+104)
#define RSB_SETSTART     (WM_USER+105)
#define RSB_SETFINISH    (WM_USER+106)
#define RSB_GETSTART     (WM_USER+107)
#define RSB_GETFINISH    (WM_USER+108)
#define RSB_SETTIC       (WM_USER+109)
#define RSB_SNAP         (WM_USER+110)

#define RSBN_STARTCHANGING  (WM_USER+200)
#define RSBN_STARTCHANGED   (WM_USER+201)
#define RSBN_FINISHCHANGING (WM_USER+202)
#define RSBN_FINISHCHANGED  (WM_USER+203)

int InitRangeSliderClass( void );

#endif
