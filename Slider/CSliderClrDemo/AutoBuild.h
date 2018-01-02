// If you have the Auto Build Numbering Add-In for Visual Studio, then you can
// use it by moving the VERSION information from your *.rc file into the
// corresponding *.rc2 file and replacing the numbers and strings with references
// to these symbols.

#ifndef __AUTOBUILD_H__
#define __AUTOBUILD_H__
//change the FALSE to TRUE for autoincrement of build number
#define INCREMENT_BUILD_NUM FALSE
#define BUILD_NUM 0
#define NUMFILEVER        1,0,0,1
#define NUMPRODUCTVER     1,0,0,1
#define STRFILEVER     "1, 0, 0, 1\0"
#define STRPRODUCTVER  "1, 0, 0, 1\0"
#define STRBUILDTIME	"Date and Time\0"
#endif //__AUTOBUILD_H__
