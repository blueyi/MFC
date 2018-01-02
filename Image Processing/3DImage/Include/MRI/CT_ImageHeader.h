
/********************************************************************
File Name:	CTImageHeader.h
Written by: Zhang Xiaochun    2008.11.10

  Copyright(C) XinAoMDT, 2001 - 2020
  
	Purpose:
	This file defines CT image structs.
	
	  History:
	  2008.11.10	Created.
*********************************************************************/
#ifndef CT_IMAGEHEADER_H
#define CT_IMAGEHEADER_H

#ifndef U1
#define U1 unsigned char
#endif
#ifndef U2
#define U2 unsigned short
#endif
#ifndef U4
#define U4 unsigned int
#endif
#ifndef I1
#define I1 char
#endif
#ifndef I2
#define I2 short
#endif
#ifndef I4
#define I4 int
#endif
#ifndef I8
#define I8 long
#endif
#ifndef F4
#define F4 float
#endif
#ifndef F8
#define F8 double
#endif
#ifndef IMG_DATA_TYPE
#define IMG_DATA_TYPE	U2
#endif


/************************************************************************/
/*
日期和时间数据结构。 
*/
/************************************************************************/
struct CT_BIDateTime
{
	U2	year;		//!< Four-digit year.
	U1	month;		//!< From 1 to 12.
	U1	day;		//!< Day of the month.
	U1 	hour;		//!< From 0 to 23.
	U1	minute;		//!< From 0 to 59.
	U1	second;		//!< From 0 to 59.
};

/************************************************************************/
/*
图像头文件； size is 152 
*/
/************************************************************************/
struct CT_HeaderInfo
{
	//必备字段
	I1	BITitle[5];			/* Storing Modality Type and Image type    */
	I4	Version;			/* Header file version, format:							
							(major_version << 16) + minor_version.	*/
	
	
	//可选字段
	U2	Size;				/* the static size of this header info 
							= sizeof(HEADER_INFO)					*/
	U1  NumHdrFields;		/* Number of fields in the header, >= 6.
							for SiteField, PatientField, StudyField, 
							SeriesField, ScanField, ImageField
							and OptionalField                        */
	U2	HeaderSize;			/* Size of BI image header, which should be 
							equal to InfoSize + 
							Site_Size + Patient_Size + Study_Size
							+ Series_Size + Scan_Size, Image_Size 
							+ UserField_Size	                        */
	U4	DataMatrixSize;		/* Image data matrix size in bytes
							Width * Height * Pixel_Size * 
							DateType & IMGDAT_RAW ? 4 : 2; 
							4 bytes for raw data,  2 bytes for image */
	U1  Reserved[128];      /* Reserved space for this field.           */
};   //sizeof(IMG_HeaderInfo) = 152

/************************************************************************/
/*
设备参数结构； size is 308
*/
/************************************************************************/
struct CT_SiteField
{
	//可选字段
	I4			Version;	    	/* version of field, format:
									(major_version << 16) + lower_version.	    */
	U2			Size;			    /* size of field = sizeof(SiteField_Struct) */
	I1			Id[16];				/* machine's ID								*/
	I1          Manufacturer[64];   /* Manufacturer of the equipment            */
	I1			InstName[32];		/* name of this site institution, for example
									CHN_BJ_TIANTAN001						    */
	I1			InstDeptName[32];	/* name of department						*/
	I1			StationName[32];	/* name of machine							*/
	I1	        BISerialNum[32];	/* SN of the machine, assigned by BI		*/
	CT_BIDateTime  LastCalib;			/* date and time of last calibration		*/
	I1          SoftVer[32]	;		/*Software Version that Produced the image. */
	U1          Reserved[52];		/* Reserved space for this field.           */
};   //sizeof(IMG_SiteField) = 308

/************************************************************************/
/*
病人结构信息； size if 324
*/
/************************************************************************/
struct CT_PatientField
{
	//可选字段
	I4			Version;			/* Version of this field. Format:
									(major_version << 16) + lower_version.		*/
	U2			Size;				/* Size of this field.                      */	
	I1			Id[16];				/* Patient ID.								*/
	I1			Name[32];			/* Patient name, "family_name, first_name".	*/
	CT_BIDateTime	BirthDate;			/* Patient birth date.				    	*/
	U1			Age;				/* Patient age.								*/
	I1			Sex;				/* Patient Sex: 
									'M' : MALE , 'F': FEMALE, or 'U': UNKNOWn	*/
	U2			Weight;				/* Weight of patient in kilogram.			*/
	I1			Desc[128];			/* Description of patient background, 
									history and other info						*/
	U1			Reserved[128];      /* Reserved space for this field.           */
};   //sizeof(IMG_PatientField) = 324

/************************************************************************/
/*
Study信息； size is 436
*/
/************************************************************************/
struct CT_StudyField
{
	//必备字段
	I1	Id[16];				/* Study ID	== ui_studyID, it's a unique id					
							in the range of a hospital.				*/
	U1	PatPosition;        /* Position of the patient: ==ui_lyingPos.   
							See enum BODYPOS.						*/
	U1	PatEntry;           /* Patient entry direction:
							== ui_bodyEntry
							enum BODYENTRY {HEAD_FIRST, FOOT_FIRST}	*/
	I1  BodyPart[32];		// {ZLX,2006.01.06}
	I1	Desc[128];			/* Description of study	
							== ui_studyDescription					*/
	CT_BIDateTime Time; /* the date and time of created the study   */
	F4  PtPos;              /* position of patient table */	

	//可选字段
	I4	Version;			/* Version of this field. Format:
							(major_version << 16) + lower_version.	*/
	U2	Size;				/* Size of this field.                      */	
													
	I1	Protocol[32];		/* Name of protocol: == ui_clinicalProtocol */
	U2	ProtocolVersion;	/* Version of protocol used.				*/
												
	I1	OperatorID[16];		/* ID of the operator: == ui_operatorID		*/
	I1	Radiologist[32];	/* Name of the radologist/specialist: 
							== ui_radiologistName					*/
	I1	RefPhy[32];			/* Name of referring physician: 
							== ui_referalPhysician					*/
																		
	U1	PatBodyPart;        /* Part of body examined: ==ui_bodyPart
							See enum BODYPART.						*/
	U1	LandmarkPos;        /* Scan landmark position reference: 
							==ui_landmarkPos. See enum LandPARKPOS.  */
	I1  OtherNo[32];		// {ZLX,2006.01.06}
																	
	U1  Reserved[88];       /* Reserved space for this field.           */
};   //sizeof(IMG_StudyField) = 436


/*********************************************************
定义序列的参数设定；size is 856
**********************************************************/
struct CT_SeriesField
{
	//必备字段
	U2	Id;					/* Series ID: == ui_seriesID. Series id is				
							a sequential number assigned to every 
							series in a study.						*/
	F4	SliceThickness;		/* Slice thickness in mm,  ==ui_sliceThk;   */
	F4	SliceGap;			/* Gap between two adjacent slices in mm. 
							== ui_sliceGap							*/
	U2	FovX;				/* Display field-of-view along X (mm).
							== ui_imageFOV							*/
	U2	FovY;				/* Diplay field-of-view along Y (mm).
							== ui_imageFOV * ui_phaseFOVRatio		*/
	U2	FovZ;				/* Display field-of-view along Z (mm). only 
							usable in 3D, leave it for now			*/
	U2	ResolutionX;		/* The number of data poI4s along read 
							direction  (number of read poI4s).
							== ui_readPnts							*/
	U2	ResolutionY;		/* The number of data poI4s along phase 
							direction (number of phase encoding)
							== ui_phasePnts							*/
	U2	ResolutionZ;		/* The number of data poI4s along second 
							phase direction in 3D imaging.
							== ui_phaseZPnts							*/
	I1	Desc[128];			/* Series description: 
							== ui_seriesDescription					*/
	I1	Protocol[32];       /* Name of series protocol: 
							== ui_seriesProtocolName					*/
	
	//可选字段
	I4	Version;			/* Version of this field. Format:
							(major_version << 16) + lower_version.	*/
	U2	Size;				/* Size of this field.                      */	
						
						
	I1	ImageType[16];	    /* Type of image: LOCALIZER or AXIAL. 
							See enum NUCTYPE.						*/
	I1  RefSeries1;			/* ID of the first reference series. 
							-1 not used.                             */
	I1	RefImage1;			/* ID of prefered reference image in the 
							first reference series.					*/
	I1  RefSeries2;			/* ID of the second reference series.		*/
	I1	RefImage2;			/* ID of prefered reference image in the 
							second reference series.			    	*/
	U1	Plane;              /* Scan plane: == ui_imagePlane;
							See enum IMAGEPLANE.					*/
	U1	Mode;				/* == ui_imageMode; see enum IMAGEMODE		*/
																		
																		
																		
	I2	WindowLevel;		/* Display window level, determinded from
							the mean signal I4ersities of all the
							images in the scan.						*/
	I2	WindowWidth;		/* Display window width, determined from 
							the standard deviation of the pixel 
							signal I4ensities of all the images in 
							the scan.								*/
	I1	ContrastFlag;		/* Whether a contrast agent is used.        */
																								
	I1	IVContrast[32];		/* The IV contrast agent applied			*/
	I1	OralContrast[32];	/* The Oral contrast agent appied.			*/
	F4	ContrastAmount;		/* Amount of constrast agent applied in ml. */
	U1	DataType;           /* Data type of image, bit array. Flags:
							RAW,IMAGE,MAG,PHASE,REAL,IMAGINARY		*/
	CT_BIDateTime DateTime;	/* Image Date & Time, by Rodger, 2005.02.23	*/
	U2  KVP;                /* Peak kilo voltage of X-ray generator */
	U2  CollectDiameter;    /* Data collected diameter */
	U2  DataDiameter;       /* Data reconstructed diameter */
	U2  DetectorTilt;       /* Gantry/Detector Tilt in degree */
	U1  RotateDir;          /* Rotate direction of the source.0: unkown;1:clockwise;2:counter clockwise */
	I2  TableHeight;        /* Table Height in mm .Below the center is positive */
	U2  TubeCurrent ;       /* Tube Current of X-ray in mA */
	U2  Exposure ;          /* Exposure expressed in uAs. */
	I1  Reserved[176+364];
};  // sizeof(SeriesField) = 856

/*****************************************
	扫描序列信息； size is 340
*****************************************/
struct CT_ScanField
{
	//必备字段
	I4	Id;			        /* Scan ID, sequential number in series.	*/
	F4   FreqDirX;			
	F4   FreqDirY;
	F4   FreqDirZ;          /* Frequence encoding direction			*/
	
    F4   PhaseDirX;
	F4   PhaseDirY;
	F4   PhaseDirZ;			/* Phase encoding direction                 */
	
	F4	SliceDirX;
	F4	SliceDirY;
	F4	SliceDirZ;

	//可选字段
    I4	Version;			/* Version of this field. Format:
							(major_version << 16) + lower_version.	*/
    U2	Size;				/* Size of this field.                      */	
    
	U1	FreqDir;			/* The frequency encoding direciton, can 
							only be within the imaging plane, and the
							default direction is the one where the 
							human body part is longer than the other 
							direction. So, when imaging a head with
							an imaging plane of AXIAL, the frequency 
							direciton can only be either LR 
							(left/right) or AP (anterior/posterior)
							and the default is AP, as AP of a head is
							longer than LR. 
							== ui_freqDir.							*/
							
							
	F4	ReadOffset;
	F4	PhaseOffset;		/* center point, in mm						*/
	F4	SliceOffset;
	I1  Reserved[280];
};   //sizeof(IMG_ScanField) = 340

/************************************************************************/
/*
图像序列信息； size is 160
*/
/************************************************************************/
struct CT_ImageField
{
	//必备字段
	U2		Id;					/* Image ID, sequential number in scan.		*/
	
	F4 fCenterPointX;
	F4 fCenterPointY;
	F4 fCenterPointZ;			// coordinates of slice's center point
	
	I2		WindowLevel;        /* Display window level, which is determined
								by the mean I4ensity of the image		*/
	I2		WindowWidth;        /* Display window width, which is determined 
														by the standard deviation of the signal 
								I4ersities of the image.				*/
	//可选字段
	I4		Version;			/* Version of this field. Format:
								(major_version << 16) + lower_version.	*/
	U2		Size;				/* Size of this field.                      */	
							
	U1	    Type;               /* Image type, which can be one of the 
								following: {MPR, PROJECTION_IMAGE, T1_MAP, 
								T2_MAP, DIFFUSION_MAP, DENSITY_MAP, 
								PHASE_MAP,VELOCITY_MAP,IMAGE_ADDITION,
								PHASE_SUBTRACT, MODULUS_SUBTRACT, OTHER}	*/
	I2		IntensityMean;		/* Mean I4ensity of the image.				*/
	I2		IntensityDev;		/* Standard deviation of I4ensity of image */
														
	I2		OffsetSI;           /* Distance from the center of image to the 
								center of reference poI4 along superior-
								inferior line (superior is positive, mm) */
	I2		OffsetAP;           /* Distance from the center of image to the
								center of reference poI4 along anterior-
								posterior (anterior is positive, mm)		*/
	I2		OffsetLR;           /* Distance from the center of image to the
								center of reference poI4 along left-right
								line	(left is positive). (mm)			*/
	CT_BIDateTime DateTime;		/* Image Date & Time, by Rodger, 2005.02.23	*/
																					
																					
	F4 fFreqDirX;
	F4 fFreqDirY;
	F4 fFreqDirZ;	        // direction of read encoding
	F4 fPhaseDirX;
	F4 fPhaseDirY;
	F4 fPhaseDirZ;	        // direction of phase encoding
	F4 fSliceDirX;
	F4 fSliceDirY; 
	F4 fSliceDirZ;	        // direction of slice encoding
	U1 nPlaneType;
	U1 Reserved[ 64+8];  /* Reserved space for this field.           */
};   //sizeof(IMG_ImageField) = 160

typedef CT_HeaderInfo		CT_HEADER_INFO;
typedef	CT_SiteField		CT_SITE_FIELD;
typedef CT_PatientField	    CT_PATIENT_FIELD;
typedef CT_StudyField		CT_STUDY_FIELD;
typedef CT_SeriesField		CT_SERIES_FIELD;
typedef CT_ScanField		CT_SCAN_FIELD;
typedef CT_ImageField		CT_IMAGE_FIELD;

/************************************************************************/
/*
BIImage Header Information  
*/
/************************************************************************/
struct CT_ImageHeader
{
    CT_HEADER_INFO		headInfo;
    CT_SITE_FIELD		siteField;
    CT_PATIENT_FIELD	patientField;
    CT_STUDY_FIELD		studyField;
    CT_SERIES_FIELD	    seriesField;
    CT_SCAN_FIELD		scanField;
    CT_IMAGE_FIELD		imageField;
	
	CT_ImageHeader()
	{
		memset( &headInfo, 0, sizeof(CT_HEADER_INFO) );
		memset( &siteField, 0, sizeof(CT_SITE_FIELD) );
		memset( &patientField, 0, sizeof(CT_PATIENT_FIELD) );
		memset( &studyField, 0, sizeof(CT_STUDY_FIELD) );
		memset( &seriesField, 0, sizeof(CT_SERIES_FIELD) );
		memset( &scanField, 0, sizeof(CT_SCAN_FIELD) );
		memset( &imageField, 0, sizeof(CT_IMAGE_FIELD) );
	}
};

struct CT_STRUCT_IMAGE
{
	CT_ImageHeader	oHeader;
	IMG_DATA_TYPE*	pData;
	
	CT_STRUCT_IMAGE()
	{
		memset( &oHeader, 0, sizeof(CT_ImageHeader) );
		pData = NULL;
	}
};

typedef CT_STRUCT_IMAGE* LPCT_STRUCT_IMAGE;


#endif