#ifndef _CONFIG_H_INC
#define _CONFIG_H_INC

/*
 * When commctrl.h does not define the DLLVERSIONINFO structure, set
 * _CONFIG_DLLVERINFO to 1.  The headers used in mingw32 do not define
 * this structure.
 */
#ifndef _MSC_VER
#define _CONFIG_DLLVERINFO    0
#else
#define _CONFIG_DLLVERINFO    1
#endif


/*
 * Handle some missing defines in the mingw32 headers
 */
#ifndef TB_SETIMAGELIST
#define TB_SETIMAGELIST (WM_USER+48)
#endif

#ifndef TB_SETHOTIMAGELIST
#define TB_SETHOTIMAGELIST (WM_USER+52)
#endif

#ifndef TB_SETDISABLEDIMAGELIST
#define TB_SETDISABLEDIMAGELIST (WM_USER+54)
#endif

#ifndef TB_SETSTYLE
#define TB_SETSTYLE (WM_USER+56)
#endif

#ifndef TB_GETSTYLE
#define TB_GETSTYLE (WM_USER+57)
#endif

#ifndef TTN_GETDISPINFO
  #define TTN_GETDISPINFOA        (TTN_FIRST - 0)
  #define TTN_GETDISPINFOW        (TTN_FIRST - 10)

  #ifdef UNICODE
  #define TTN_GETDISPINFO         TTN_GETDISPINFOW
  #else
  #define TTN_GETDISPINFO         TTN_GETDISPINFOA
  #endif
#endif

/*
 * Use the "flat" style toolbar?
 */
#ifndef TBSTYLE_FLAT
#define TBSTYLE_FLAT        0x0800
#define TBSTYLE_TRANSPARENT 0x8000
#endif
#define _CONFIG_FLAT_TOOLBAR 1

#endif
