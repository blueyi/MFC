#ifndef __TYPEDEFS_H
#define __TYPEDEFS_H

#ifndef PURE
#define PURE =0
#endif //PURE

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { delete p; p = 0; }
#endif //SAFE_DELETE

typedef unsigned int	uint32;
typedef uint32			uint;
typedef unsigned short	uint16;
typedef unsigned char	uint8;

#endif//__TYPEDEFS_H

