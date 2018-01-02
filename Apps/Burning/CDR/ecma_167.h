/*
 * ecma_167.h
 *
 * This file is based on ECMA-167 3rd edition (June 1997)
 * http://www.ecma.ch
 *
 * Copyright (c) 2001-2002  Ben Fennema <bfennema@falcon.csc.calpoly.edu>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modification.
 * 2. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU Public License ("GPL").
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef _ECMA_167_H
#define _ECMA_167_H 1
#include "types.h"
#pragma pack(1)


/* Character set specification (ECMA 167r3 1/7.2.1) */
typedef struct
{
	Uchar		charSetType;
	Uchar		charSetInfo[63];
} charspec;


/* Character Set Type (ECMA 167r3 1/7.2.1.1) */
#define CHARSPEC_TYPE_CS0		0x00	/* (1/7.2.2) */
#define CHARSPEC_TYPE_CS1		0x01	/* (1/7.2.3) */
#define CHARSPEC_TYPE_CS2		0x02	/* (1/7.2.4) */
#define CHARSPEC_TYPE_CS3		0x03	/* (1/7.2.5) */
#define CHARSPEC_TYPE_CS4		0x04	/* (1/7.2.6) */
#define CHARSPEC_TYPE_CS5		0x05	/* (1/7.2.7) */
#define CHARSPEC_TYPE_CS6		0x06	/* (1/7.2.8) */
#define CHARSPEC_TYPE_CS7		0x07	/* (1/7.2.9) */
#define CHARSPEC_TYPE_CS8		0x08	/* (1/7.2.10) */

#define dstring	Uchar

/* Recorded Address (ECMA 167r3 4/7.1) */
typedef struct 
{
	Uint32	logicalBlockNum;
	Uint16	partitionReferenceNum;
}lb_addr;

/* Short Allocation Descriptor (ECMA 167r3 4/14.14.1) */
typedef struct
{
        Uint32	extLength;
        Uint32	extPosition;
} short_ad;

/* Long Allocation Descriptor (ECMA 167r3 4/14.14.2) */
typedef struct
{
	Uint32	extLength;
	lb_addr		extLocation;
	Uchar		impUse[6];
} long_ad;

/* Extended Allocation Descriptor (ECMA 167r3 4/14.14.3) */
typedef struct
{
	Uint32	extLength;
	Uint32	recordedLength;
	Uint32	informationLength;
	lb_addr		extLocation;
} ext_ad;


/* Timestamp (ECMA 167r3 1/7.3) */
typedef struct
{
	Uint16		typeAndTimezone;
	Uint16		year;
	Uchar		month;
	Uchar		day;
	Uchar		hour;
	Uchar		minute;
	Uchar		second;
	Uchar		centiseconds;
	Uchar		hundredsOfMicroseconds;
	Uchar		microseconds;
}timestamp;

/* Type and Time Zone (ECMA 167r3 1/7.3.1) */
#define TIMESTAMP_TYPE_MASK		0xF000
#define TIMESTAMP_TYPE_CUT		0x0000
#define TIMESTAMP_TYPE_LOCAL		0x1000
#define TIMESTAMP_TYPE_AGREEMENT	0x2000
#define TIMESTAMP_TIMEZONE_MASK		0x0FFF

/* Entity identifier (ECMA 167r3 1/7.4) */
typedef struct
{
	Uchar		flags;
	Uchar		ident[23];
	Uchar		identSuffix[8];
} regid;

/* Flags (ECMA 167r3 1/7.4.1) */
#define ENTITYID_FLAGS_DIRTY		0x00
#define ENTITYID_FLAGS_PROTECTED	0x01

/* Volume Structure Descriptor (ECMA 167r3 2/9.1) */
#define VSD_STD_ID_LEN			5
typedef struct 
{
	Uchar		structType;
	Uchar		stdIdent[VSD_STD_ID_LEN];
	Uchar		structVersion;
	Uchar		structData[2041];
}volStructDesc;

/* Standard Identifier (EMCA 167r2 2/9.1.2) */
#define VSD_STD_ID_NSR02		"NSR02"	/* (3/9.1) */

/* Standard Identifier (ECMA 167r3 2/9.1.2) */
#define VSD_STD_ID_BEA01		"BEA01"	/* (2/9.2) */
#define VSD_STD_ID_BOOT2		"BOOT2"	/* (2/9.4) */
#define VSD_STD_ID_CD001		"CD001"	/* (ECMA-119) */
#define VSD_STD_ID_CDW02		"CDW02"	/* (ECMA-168) */
#define VSD_STD_ID_NSR03		"NSR03"	/* (3/9.1) */
#define VSD_STD_ID_TEA01		"TEA01"	/* (2/9.3) */

/* Beginning Extended Area Descriptor (ECMA 167r3 2/9.2) */
typedef struct 
{
	Uchar		structType;
	Uchar		stdIdent[VSD_STD_ID_LEN];
	Uchar		structVersion;
	Uchar		structData[2041];
}beginningExtendedAreaDesc;

/* Terminating Extended Area Descriptor (ECMA 167r3 2/9.3) */
typedef struct 
{
	Uchar		structType;
	Uchar		stdIdent[VSD_STD_ID_LEN];
	Uchar		structVersion;
	Uchar		structData[2041];
}terminatingExtendedAreaDesc;

/* Boot Descriptor (ECMA 167r3 2/9.4) */
typedef struct 
{
	Uchar		structType;
	Uchar		stdIdent[VSD_STD_ID_LEN];
	Uchar		structVersion;
	Uchar		reserved1;
	regid		archType;
	regid		bootIdent;
	Uint32		bootExtLocation;
	Uint32		bootExtLength;
	Uint64		loadAddress;
	Uint64		startAddress;
	timestamp	descCreationDateAndTime;
	Uint16		flags;
	Uchar		reserved2[32];
	Uchar		bootUse[1906];
} bootDesc;

/* Flags (ECMA 167r3 2/9.4.12) */
#define BOOT_FLAGS_ERASE		0x01

/* Extent Descriptor (ECMA 167r3 3/7.1) */
typedef struct
{
	Uint32	extLength;
	Uint32	extLocation;
}extent_ad;

/* Descriptor Tag (ECMA 167r3 3/7.2) */
typedef struct
{
	Uint16	tagIdent;
	Uint16	descVersion;
	Uchar	tagChecksum;
	Uchar	reserved;
	Uint16	tagSerialNum;
	Uint16	descCRC;
	Uint16	descCRCLength;
	Uint32	tagLocation;
}tag;

/* Tag Identifier (ECMA 167r3 3/7.2.1) */
#define TAG_IDENT_PVD			0x0001
#define TAG_IDENT_AVDP			0x0002
#define TAG_IDENT_VDP			0x0003
#define TAG_IDENT_IUVD			0x0004
#define TAG_IDENT_PD			0x0005
#define TAG_IDENT_LVD			0x0006
#define TAG_IDENT_USD			0x0007
#define TAG_IDENT_TD			0x0008
#define TAG_IDENT_LVID			0x0009


typedef struct {
	Uchar	T;
	Uchar	D;
	Uchar	I;
	Uint16	len;
	Uchar	res;
	Uchar	lowestTrack;
	Uchar	highestTrack;
	Uchar	trackNumber;
	Uchar	recordingMethod;
	Uchar	packetSize[3];
	Uchar	res1[11];
}TDB;


/* NSR Descriptor (ECMA 167r3 3/9.1) */
typedef struct 
{
	Uchar		structType;
	Uchar		stdIdent[VSD_STD_ID_LEN];
	Uchar		structVersion;
	Uchar		reserved;
	Uchar		structData[2040];
}NSRDesc ;
	
/* Primary Volume Descriptor (ECMA 167r3 3/10.1) */
typedef struct 
{
	tag			descTag;
	Uint32		volDescSeqNum;
	Uint32		primaryVolDescNum;
	dstring		volIdent[32];
	Uint16		volSeqNum;
	Uint16		maxVolSeqNum;
	Uint16		interchangeLvl;
	Uint16		maxInterchangeLvl;
	Uint32		charSetList;
	Uint32		maxCharSetList;
	dstring		volSetIdent[128];
	charspec	descCharSet;
	charspec	explanatoryCharSet;
	extent_ad	volAbstract;
	extent_ad	volCopyright;
	regid		appIdent;
	timestamp	recordingDateAndTime;
	regid		impIdent;
	Uchar		impUse[64];
	Uint32		predecessorVolDescSeqLocation;
	Uint16		flags;
	Uchar		reserved[22];
} primaryVolDesc;

/* Flags (ECMA 167r3 3/10.1.21) */
#define PVD_FLAGS_VSID_COMMON		0x0001

/* Anchor Volume Descriptor Pointer (ECMA 167r3 3/10.2) */
typedef struct 
{
	tag			descTag;
	extent_ad	mainVolDescSeqExt;
	extent_ad	reserveVolDescSeqExt;
	Uchar	 	reserved[480];
} anchorVolDescPtr;

/* Volume Descriptor Pointer (ECMA 167r3 3/10.3) */
typedef struct 
{
	tag			descTag;
	Uint32		volDescSeqNum;
	extent_ad	nextVolDescSeqExt;
	Uchar		reserved[484];
} volDescPtr;

/* LV information (UDF2.01,2.2.7.2*/
typedef struct 
{
	charspec			LVICharSet;
	Uchar				LVId[128];
	Uchar				LVInfo1[36];
	Uchar				LVInfo2[36];
	Uchar				LVInfo3[36];
	regid				impIdent;
	Uchar				impUse[128];
} LVInfo;


/* Implementation Use Volume Descriptor (ECMA 167r3 3/10.4) */
typedef struct 
{
	tag					descTag;
	Uint32				volDescSeqNum;
	regid				impIdent;
	LVInfo				impUse;
} impUseVolDesc;

/* Partition Descriptor (ECMA 167r3 3/10.5) */
typedef struct 
{
	tag		descTag;
	Uint32	volDescSeqNum;
	Uint16	partitionFlags;
	Uint16	partitionNumber;
	regid	partitionContents;
	Uchar	partitionContentsUse[128];
	Uint32	accessType;
	Uint32	partitionStartingLocation;
	Uint32	partitionLength;
	regid	impIdent;
	Uchar	impUse[128];
	Uchar	reserved[156];
}partitionDesc ;

/* Partition Flags (ECMA 167r3 3/10.5.3) */
#define PD_PARTITION_FLAGS_ALLOC	0x0001

/* Partition Contents (ECMA 167r2 3/10.5.3) */
#define PD_PARTITION_CONTENTS_NSR02	"+NSR02"

/* Partition Contents (ECMA 167r3 3/10.5.5) */
#define PD_PARTITION_CONTENTS_FDC01	"+FDC01"
#define PD_PARTITION_CONTENTS_CD001	"+CD001"
#define PD_PARTITION_CONTENTS_CDW02	"+CDW02"
#define PD_PARTITION_CONTENTS_NSR03	"+NSR03"

/* Access Type (ECMA 167r3 3/10.5.7) */
#define PD_ACCESS_TYPE_NONE		0x00000000
#define PD_ACCESS_TYPE_READ_ONLY	0x00000001
#define PD_ACCESS_TYPE_WRITE_ONCE	0x00000002
#define PD_ACCESS_TYPE_REWRITABLE	0x00000003
#define PD_ACCESS_TYPE_OVERWRITABLE	0x00000004


typedef struct {
	Uchar	type;
	Uchar	len;
	Uint16	volSeqNumber;
	Uint16	partitionNumber;
}partitionMapType1;

typedef struct {
	Uchar	type;
	Uchar	len;
	Uchar	res[2];
	regid	ident;
	Uint16	volSeqNumber;
	Uint16	partitionNumber;
	Uchar	reserved[24];
}partitionMapType2;

/* Logical Volume Descriptor (ECMA 167r3 3/10.6) */
typedef struct
{
	tag			descTag;
	Uint32		volDescSeqNum;
	charspec	descCharSet;
	dstring		logicalVolIdent[128];
	Uint32		logicalBlockSize;
	regid		domainIdent;
	long_ad		logicalVolContentsUse;
	Uint32		mapTableLength;
	Uint32		numPartitionMaps;
	regid		impIdent;
	Uchar		impUse[128];
	extent_ad	integritySeqExt;
	partitionMapType1		partitionMap1;
	partitionMapType2		partitionMap2;
} logicalVolDesc;

/* Generic Partition Map (ECMA 167r3 3/10.7.1) */
struct genericPartitionMap
{
	Uchar		partitionMapType;
	Uchar		partitionMapLength;
	Uchar		partitionMapping1stByte;
} ;

/* Partition Map Type (ECMA 167r3 3/10.7.1.1) */
#define GP_PARTITION_MAP_TYPE_UNDEF	0x00
#define GP_PARTIITON_MAP_TYPE_1		0x01
#define GP_PARTITION_MAP_TYPE_2		0x02

/* Type 1 Partition Map (ECMA 167r3 3/10.7.2) */
struct genericPartitionMap1
{
	Uchar		partitionMapType;
	Uchar		partitionMapLength;
	Uint16		volSeqNum;
	Uint16		partitionNum;
} ;

/* Type 2 Partition Map (ECMA 167r3 3/10.7.3) */
struct genericPartitionMap2
{
	Uchar		partitionMapType;
	Uchar		partitionMapLength; 
	Uchar		partitionIdent[62];
} ;

/* Unallocated Space Descriptor (ECMA 167r3 3/10.8) */
typedef struct 
{
	tag		descTag;
	Uint32	volDescSeqNum;
	Uint32	numAllocDescs;
	extent_ad	allocDescs;//TODO,FIRST
} unallocSpaceDesc;

/* Terminating Descriptor (ECMA 167r3 3/10.9) */
typedef struct 
{
	tag		descTag;
	Uchar		reserved[496];
}terminatingDesc;

/* Logical Volume Integrity Descriptor (ECMA 167r3 3/10.10) */
typedef struct 
{
	tag			descTag;
	timestamp	recordingDateAndTime;
	Uint32		integrityType;
	extent_ad	nextIntegrityExt;
	Uchar		logicalVolContentsUse[32];
	Uint32		numOfPartitions;
	Uint32		lengthOfImpUse;
	Uint32		freeSpaceTable[2];
	Uint32		sizeTable[2];
	Uchar		impUse[46];
} logicalVolIntegrityDesc;

/* Integrity Type (ECMA 167r3 3/10.10.3) */
#define LVID_INTEGRITY_TYPE_OPEN	0x00000000
#define LVID_INTEGRITY_TYPE_CLOSE	0x00000001


/* Descriptor Tag (ECMA 167r3 4/7.2 - See 3/7.2) */

/* Tag Identifier (ECMA 167r3 4/7.2.1) */
#define TAG_IDENT_FSD			0x0100
#define TAG_IDENT_FID			0x0101
#define TAG_IDENT_AED			0x0102
#define TAG_IDENT_IE			0x0103
#define TAG_IDENT_TE			0x0104
#define TAG_IDENT_FE			0x0105
#define TAG_IDENT_EAHD			0x0106
#define TAG_IDENT_USE			0x0107
#define TAG_IDENT_SBD			0x0108
#define TAG_IDENT_PIE			0x0109
#define TAG_IDENT_EFE			0x010A

/* File Set Descriptor (ECMA 167r3 4/14.1) */
typedef struct 
{
	tag			descTag;
	timestamp	recordingDateAndTime;
	Uint16		interchangeLvl;
	Uint16		maxInterchangeLvl;
	Uint32		charSetList;
	Uint32		maxCharSetList;
	Uint32		fileSetNum;
	Uint32		fileSetDescNum;
	charspec	logicalVolIdentCharSet;
	dstring		logicalVolIdent[128];
	charspec	fileSetCharSet;
	dstring		fileSetIdent[32];
	dstring		copyrightFileIdent[32];
	dstring		abstractFileIdent[32];
	long_ad		rootDirectoryICB;
	regid		domainIdent;
	long_ad		nextExt;
	long_ad		streamDirectoryICB;
	Uchar		reserved[32];
} fileSetDesc;

/* Partition Header Descriptor (ECMA 167r3 4/14.3) */
typedef struct 
{
	short_ad	unallocSpaceTable;
	short_ad	unallocSpaceBitmap;
	short_ad	partitionIntegrityTable;
	short_ad	freedSpaceTable;
	short_ad	freedSpaceBitmap;
	Uchar		reserved[88];
} partitionHeaderDesc;

/* File Identifier Descriptor (ECMA 167r3 4/14.4) */
typedef struct 
{
	tag			descTag;
	Uint16		fileVersionNum;
	Uchar		fileCharacteristics;
	Uchar		lengthFileIdent;
	long_ad		icb;
	Uint16		lengthOfImpUse;
	Uchar		other[130];
} fileIdentDesc;

/* File Characteristics (ECMA 167r3 4/14.4.3) */
#define FID_FILE_CHAR_HIDDEN		0x01
#define FID_FILE_CHAR_DIRECTORY		0x02
#define FID_FILE_CHAR_DELETED		0x04
#define FID_FILE_CHAR_PARENT		0x08
#define FID_FILE_CHAR_METADATA		0x10

/* Allocation Ext Descriptor (ECMA 167r3 4/14.5) */
typedef struct 
{
	tag		descTag;
	Uint32	previousAllocExtLocation;
	Uint32	lengthAllocDescs;
} allocExtDesc;

/* ICB Tag (ECMA 167r3 4/14.6) */
typedef struct
{
	Uint32	priorRecordedNumDirectEntries;
	Uint16	strategyType;
	Uint16	strategyParameter;
	Uint16	numEntries;
	Uchar	reserved;
	Uchar	fileType;
	lb_addr	parentICBLocation;
	Uint16	flags;
}icbtag;

/* Strategy Type (ECMA 167r3 4/14.6.2) */
#define ICBTAG_STRATEGY_TYPE_UNDEF	0x0000
#define ICBTAG_STRATEGY_TYPE_1		0x0001
#define ICBTAG_STRATEGY_TYPE_2		0x0002
#define ICBTAG_STRATEGY_TYPE_3		0x0003
#define ICBTAG_STRATEGY_TYPE_4		0x0004

/* File Type (ECMA 167r3 4/14.6.6) */
#define ICBTAG_FILE_TYPE_UNDEF		0x00
#define ICBTAG_FILE_TYPE_USE		0x01
#define ICBTAG_FILE_TYPE_PIE		0x02
#define ICBTAG_FILE_TYPE_IE			0x03
#define ICBTAG_FILE_TYPE_DIRECTORY	0x04
#define ICBTAG_FILE_TYPE_REGULAR	0x05
#define ICBTAG_FILE_TYPE_BLOCK		0x06
#define ICBTAG_FILE_TYPE_CHAR		0x07
#define ICBTAG_FILE_TYPE_EA			0x08
#define ICBTAG_FILE_TYPE_FIFO		0x09
#define ICBTAG_FILE_TYPE_SOCKET		0x0A
#define ICBTAG_FILE_TYPE_TE			0x0B
#define ICBTAG_FILE_TYPE_SYMLINK	0x0C
#define ICBTAG_FILE_TYPE_STREAMDIR	0x0D

/* Flags (ECMA 167r3 4/14.6.8) */
#define ICBTAG_FLAG_AD_MASK			0x0007
#define ICBTAG_FLAG_AD_SHORT		0x0000
#define ICBTAG_FLAG_AD_LONG			0x0001
#define ICBTAG_FLAG_AD_EXTENDED		0x0002
#define ICBTAG_FLAG_AD_IN_ICB		0x0003
#define ICBTAG_FLAG_SORTED			0x0008
#define ICBTAG_FLAG_NONRELOCATABLE	0x0010
#define ICBTAG_FLAG_ARCHIVE			0x0020
#define ICBTAG_FLAG_SETUID			0x0040
#define ICBTAG_FLAG_SETGID			0x0080
#define ICBTAG_FLAG_STICKY			0x0100
#define ICBTAG_FLAG_CONTIGUOUS		0x0200
#define ICBTAG_FLAG_SYSTEM			0x0400
#define ICBTAG_FLAG_TRANSFORMED		0x0800
#define ICBTAG_FLAG_MULTIVERSIONS	0x1000
#define ICBTAG_FLAG_STREAM			0x2000

/* Indirect Entry (ECMA 167r3 4/14.7) */
typedef struct 
{
	tag			descTag;
	icbtag		icbTag;
	long_ad		indirectICB;
} indirectEntry;

/* Terminal Entry (ECMA 167r3 4/14.8) */
typedef struct 
{
	tag			descTag;
	icbtag		icbTag;
} terminalEntry;

/* File Entry (ECMA 167r3 4/14.9) */
typedef struct 
{
	tag			descTag;
	icbtag		icbTag;
	Uint32		uid;
	Uint32		gid;
	Uint32		permissions;
	Uint16		fileLinkCount;
	Uchar		recordFormat;
	Uchar		recordDisplayAttr;
	Uint32		recordLength;
	Uint64		informationLength;
	Uint64		logicalBlocksRecorded;
	timestamp	accessTime;
	timestamp	modificationTime;
	timestamp	attrTime;
	Uint32		checkpoint;
	long_ad		extendedAttrICB;
	regid		impIdent;
	Uint64		uniqueID;
	Uint32		lengthExtendedAttr;
	Uint32		lengthAllocDescs;
	Uchar		other[2048-176];
} fileEntry;

/* Permissions (ECMA 167r3 4/14.9.5) */
#define FE_PERM_O_EXEC			0x00000001U
#define FE_PERM_O_WRITE			0x00000002U
#define FE_PERM_O_READ			0x00000004U
#define FE_PERM_O_CHATTR		0x00000008U
#define FE_PERM_O_DELETE		0x00000010U
#define FE_PERM_G_EXEC			0x00000020U
#define FE_PERM_G_WRITE			0x00000040U
#define FE_PERM_G_READ			0x00000080U
#define FE_PERM_G_CHATTR		0x00000100U
#define FE_PERM_G_DELETE		0x00000200U
#define FE_PERM_U_EXEC			0x00000400U
#define FE_PERM_U_WRITE			0x00000800U
#define FE_PERM_U_READ			0x00001000U
#define FE_PERM_U_CHATTR		0x00002000U
#define FE_PERM_U_DELETE		0x00004000U

/* Record Format (ECMA 167r3 4/14.9.7) */
#define FE_RECORD_FMT_UNDEF		0x00
#define FE_RECORD_FMT_FIXED_PAD		0x01
#define FE_RECORD_FMT_FIXED		0x02
#define FE_RECORD_FMT_VARIABLE8		0x03
#define FE_RECORD_FMT_VARIABLE16	0x04
#define FE_RECORD_FMT_VARIABLE16_MSB	0x05
#define FE_RECORD_FMT_VARIABLE32	0x06
#define FE_RECORD_FMT_PRINT		0x07
#define FE_RECORD_FMT_LF		0x08
#define FE_RECORD_FMT_CR		0x09
#define FE_RECORD_FMT_CRLF		0x0A
#define FE_RECORD_FMT_LFCR		0x0B

#define Record Display Attributes (ECMA 167r3 4/14.9.8) */
#define FE_RECORD_DISPLAY_ATTR_UNDEF	0x00
#define FE_RECORD_DISPLAY_ATTR_1	0x01
#define FE_RECORD_DISPLAY_ATTR_2	0x02
#define FE_RECORD_DISPLAY_ATTR_3	0x03

/* Extended Attribute Header Descriptor (ECMA 167r3 4/14.10.1) */
typedef struct 
{
	tag		descTag;
	Uint32	impAttrLocation;
	Uint32	appAttrLocation;
} extendedAttrHeaderDesc;

/* Generic Format (ECMA 167r3 4/14.10.2) */
typedef struct 
{
	Uint32		attrType;
	Uchar		attrSubtype;
	Uchar		reserved[3];
	Uint32		attrLength;
	Uchar		attrData1stByte;
} genericFormat;

typedef struct 
{
	extendedAttrHeaderDesc		header;
	genericFormat				content;
} extenedAttributes;


/* Character Set Information (ECMA 167r3 4/14.10.3) */
typedef struct 
{
	Uint32		attrType;
	Uchar		attrSubtype;
	Uchar		reserved[3];
	Uint32		attrLength;
	Uint32		escapeSeqLength;
	Uchar		charSetType;
	Uchar		escapeSeq1stByte;
} charSetInfo;

/* Alternate Permissions (ECMA 167r3 4/14.10.4) */
typedef struct 
{
	Uint32	attrType;
	Uchar	attrSubtype;
	Uchar	reserved[3];
	Uint32	attrLength;
	Uint16	ownerIdent;
	Uint16	groupIdent;
	Uint16	permission;
} altPerms;

/* File Times Extended Attribute (ECMA 167r3 4/14.10.5) */
typedef struct 
{
	Uint32	attrType;
	Uchar	attrSubtype;
	Uchar	reserved[3];
	Uint32	attrLength;
	Uint32	dataLength;
	Uint32	fileTimeExistence;
	timestamp	fileTimes;
} fileTimesExtAttr;

/* FileTimeExistence (ECMA 167r3 4/14.10.5.6) */
#define FTE_CREATION			0x00000001
#define FTE_DELETION			0x00000004
#define FTE_EFFECTIVE			0x00000008
#define FTE_BACKUP				0x00000002

/* Information Times Extended Attribute (ECMA 167r3 4/14.10.6) */
typedef struct 
{
	Uint32		attrType;
	Uchar		attrSubtype;
	Uchar		reserved[3];
	Uint32		attrLength;
	Uint32		dataLength;
	Uint32		infoTimeExistence;
	Uchar		infoTimes1stByte;
} infoTimesExtAttr;

/* Device Specification (ECMA 167r3 4/14.10.7) */
typedef struct 
{
	Uint32		attrType;
	Uchar		attrSubtype;
	Uchar		reserved[3];
	Uint32		attrLength;
	Uint32		impUseLength;
	Uint32		majorDeviceIdent;
	Uint32		minorDeviceIdent;
	Uchar		impUse1stByte;
} deviceSpec;

/* Implementation Use Extended Attr (ECMA 167r3 4/14.10.8) */
typedef struct 
{
	Uint32		attrType;
	Uchar		attrSubtype;
	Uchar		reserved[3];
	Uint32		attrLength;
	Uint32		impUseLength;
	regid		impIdent;
	Uchar		impUse1stByte;
} impUseExtAttr;

/* Application Use Extended Attribute (ECMA 167r3 4/14.10.9) */
typedef struct 
{
	Uint32		attrType;
	Uchar		attrSubtype;
	Uchar		reserved[3];
	Uint32		attrLength;
	Uint32		appUseLength;
	regid		appIdent;
	Uchar		appUse1stByte;
} appUseExtAttr;

#define EXTATTR_CHAR_SET		1
#define EXTATTR_ALT_PERMS		3
#define EXTATTR_FILE_TIMES		5
#define EXTATTR_INFO_TIMES		6
#define EXTATTR_DEV_SPEC		12
#define EXTATTR_IMP_USE			2048
#define EXTATTR_APP_USE			65536


/* Unallocated Space Entry (ECMA 167r3 4/14.11) */
typedef struct 
{
	tag			descTag;
	icbtag		icbTag;
	Uint32		lengthAllocDescs;
	Uchar		allocDescs1stByte;
} unallocSpaceEntry;

/* Space Bitmap Descriptor (ECMA 167r3 4/14.12) */
typedef struct 
{
	tag		descTag;
	Uint32	numOfBits;
	Uint32	numOfBytes;
	Uchar	bitmap1stByte;
} spaceBitmapDesc;

/* Partition Integrity Entry (ECMA 167r3 4/14.13) */
typedef struct 
{
	tag			descTag;
	icbtag		icbTag;
	timestamp	recordingDateAndTime;
	Uchar		integrityType;
	Uchar		reserved[175];
	regid		impIdent;
	Uchar		impUse[256];
} partitionIntegrityEntry;

/* Short Allocation Descriptor (ECMA 167r3 4/14.14.1) */

/* Extent Length (ECMA 167r3 4/14.14.1.1) */
#define EXT_RECORDED_ALLOCATED		0x00000000
#define EXT_NOT_RECORDED_ALLOCATED	0x40000000
#define EXT_NOT_RECORDED_NOT_ALLOCATED	0x80000000
#define EXT_NEXT_EXTENT_ALLOCDECS	0xC0000000

/* Long Allocation Descriptor (ECMA 167r3 4/14.14.2) */

/* Extended Allocation Descriptor (ECMA 167r3 4/14.14.3) */

/* Logical Volume Header Descriptor (ECMA 167r3 4/14.15) */
typedef struct 
{
	Uint64		uniqueID;
	Uchar		reserved[24];
} logicalVolHeaderDesc;

/* Path Component (ECMA 167r3 4/14.16.1) */
typedef struct 
{
	Uchar		componentType;
	Uchar		lengthComponentIdent;
	Uint16		componentFileVersionNum;
	dstring		componentIdent1stByte;
} pathComponent;

/* File Entry (ECMA 167r3 4/14.17) */
typedef struct 
{
	tag			descTag;
	icbtag		icbTag;
	Uint32		uid;
	Uint32		gid;
	Uint32		permissions;
	Uint16		fileLinkCount;
	Uchar		recordFormat;
	Uchar		recordDisplayAttr;
	Uint32		recordLength;
	Uint64		informationLength;
	Uint64		objectSize;
	Uint64		logicalBlocksRecorded;
	timestamp	accessTime;
	timestamp	modificationTime;
	timestamp	createTime;
	timestamp	attrTime;
	Uint32		checkpoint;
	Uint32		reserved;
	long_ad		extendedAttrICB;
	long_ad		streamDirectoryICB;
	regid		impIdent;
	Uint64		uniqueID;
	Uint32		lengthExtendedAttr;
	Uint32		lengthAllocDescs;
	Uchar		extendedAttr1stByte;
} extendedFileEntry;

#endif /* _ECMA_167_H */
