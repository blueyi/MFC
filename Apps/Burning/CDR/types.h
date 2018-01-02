
#ifndef	_TYPES_H
#define	_TYPES_H
#define _BIT_FIELDS_LTOH
/*
typedef struct{
	BYTE bytes[2];
}Uint16;

typedef struct{
	BYTE bytes[4];
}Uint32;

typedef struct{
	BYTE bytes[8];
}Uint64;

typedef struct{
	BYTE bytes[2];
}int16;

typedef struct{
	BYTE bytes[4];
}int32;
*/

typedef	__int8				int8;
typedef	__int16				int16;
typedef	__int32				int32;
typedef	__int64				int64;

typedef	unsigned __int16		Uint16;
typedef	unsigned __int32		Uint32;
typedef	unsigned __int64		Uint64;

typedef	unsigned short		Ushort;
typedef	unsigned char		Uchar;
typedef	unsigned char		Ucbit;

#define Ulong	Uint64;
/*
static int reverseUint32(Uint32 input){
	return (input.bytes[3]<<24)+(input.bytes[2]<<16)+
		(input.bytes[1]<<8)+input.bytes[0];
}
static int reverseUint16(Uint16 input){
	return 	(input.bytes[1]<<8)+input.bytes[0];
}
*/
#endif	/* _TYPES_H */
