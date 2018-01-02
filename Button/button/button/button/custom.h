/* File custom.h
 * (custom control interface)
 */

#ifndef CUSTOM_H
#define CUSTOM_H

#include <tchar.h>
#include <windows.h>


/* Window class */
#define CUSTOM_WC              _T("CustomControl")

/* Style correspondiding to BS_DEFPUSHBUTTON. (When not used, we look as BS_PUSHBUTTON). */
#define XXS_DEFAULT              (0x0001)

/* Style to request using double buffering. */
#define XXS_DOUBLEBUFFER         (0x0002)


/* Register/unregister the window class */
void WINAPI CustomRegister(void);
void WINAPI CustomUnregister(void);


#endif  /* CUSTOM_H */
