/********************************************************************
File Name:	BI_ImageHeader.h
Written by: Zhao Lei
Modified by: Yang Guang, Xie Haibin

Copyright(C) XinAoMDT, 2001 -

Purpose:
	This file defines following classes:

History:
    2002.7.11 Added ReadPoints, PhasePoints in the SeriesField - YG, XHB
        Now the ResolutionX and ResolutionY are used to store data points
        number after reconstruction.
    2002.7.8 Added Echo spacing to series field.
             Added reserved space at the end of each field.
    2002.7.3 Added ACQ to scan field. 
    2002.6.7 Use type definition to overcome the dependency on the compiler
    of the used data types. -- Yang Guang
    2002.6.6 Modified by Yang Guang, Xie Haibin, Li Jianqi
    -- Added some series parameters, together with some structures and constants.
    -- Move scan parameters other than localization parameters to series.

	2002.5.30 Modified by Yang Guang
        Added parameters on reference images in the series field. 
        Remove the RefImage in the scan field 
		RefSeries1, RefImage1, RefSeries2, RefImage2		
	2002.5.30 Replace time_t with CBIDateTime, Yang Guang
		-- time_t cannot used to store date earlier than 1970-1-1
	2002.5.28 Added eight parameters in the scan field. Xie Haibin
		SliceDirX,
		SliceDirY,
		SliceDirZ,
		ReadOffset,
		PhaseOffset,
		SliceOffset,
		bSingleSliceMethod,
		bInterleave,

    2002.5.1 Move four parameters from SeriesField to StudyField
        PatPostion, PatEntry, PatBodyPart, LandmarkPos
	2001.8.15   Yang Guang
		-- remove the field prefix of the member variables.
		-- remove MFC dependency by replacing COleDateTime with time_t
		-- use short for enumerate type
		-- reformat comment to maintain ANSI C compatibility
	2001.8.8    Remove the redifinition of FIELD.FreqDir. -- YG
	2001.8.8	Some typos and header file -- Yang Guang
	2001.7.23	Created.
*********************************************************************/

#ifndef _yg_BI_ImageHeader_h_1582001
#define _yg_BI_ImageHeader_h_1582001

/*!
    \page Image header.
    \remarks The image header is defined to ensure the portability to other
    platform. Taken the popularity of C++ nowadays. Some C++ features is 
    currently used (which can be easily removed with little modification).
    The dependency on MSVC compiler is delibrately avoided. However, some 
    platform dependent internal types are used in the definition. So when 
    porting to the other platform, you need ensure these types have same size
    as the MSVC 6.0 compiler. Or you change the relevent macro definitions
    to used the type of the correct size. 
*/

//Added by Tom, --2008.07.10
enum ENUM_SCAN_TYPE
{
	SCAN_TYPE___NONE = 0,
	SCAN_TYPE___PRESCAN = 1,
	SCAN_TYPE___FORMALSCAN = 2,
	SCAN_TYPE___PRESCAN_AND_FORMALSCAN = 3,
};

#include <AFX.H>
//#include <AFXVER_.H>
#include "../ImageHeader/BI_Constants.h"

#define U1 unsigned char
#define U2 unsigned short
#define U4 unsigned int

#define I1 char
#define I2 short
#define I4 int
#define I8 long

#define F4 float
#define F8 double

#define INI_FIELD_NUM	100 //dolphin

//! This struct is used to hold date time information.
/************************************************************************/
/*
	时间数据结果； 
*/
/************************************************************************/
struct BIDateTime
{
	U2	year;		//!< Four-digit year.
	U1	month;		//!< From 1 to 12.
	U1	day;		//!< Day of the month.
	U1 	hour;		//!< From 0 to 23.
	U1	minute;		//!< From 0 to 59.
	U1	second;		//!< From 0 to 59.
};

/*!
    This struct is used to hold information about one presaturation region.
    There may be six presaturation regions altogether, which are located at the
    six surfaces of the scan cube.
*/
struct CPresaturationRegion
{
	I1 m_bUse;        //!< This region is used.
	//! Position of the presaturation region, in mm.
    /*!
        This member is used to store the position of the presaturation region.
        According the requirements given by Li Jianqi, the presaturation 
        region is always parallel to one of the surfaces of the scan cube.
        The presaturation region can be characterized by its thickness in mm
        and its distance to the surface of the scan cube. This distance can
        be negative, which simply means the presaturation region starts from 
        within the scan cube (in the cube determined by fov).
     */
    I2 m_sPos;       
    //! Thickness of the presaturation region, in mm.
	I2 m_sThickness;
};

/*!
    Struct used to store respirator trigger related parameters.
*/
struct CRespiratoryTrigger
{
    //! Number of respirations between two triggers.
	U1 m_ucInterval;
	U1 m_ucTriggerPoint;			// percent	
	U1 m_ucTriggerWindow;		    // percent
	U2 m_usInterSequenceDelay;	    // in ms.
	U1 m_ucRate;					// per minute
};

/*!
    Struct used to store cardiac gating related parameters.
*/

/************************************************************************/
/*
	和心电门控有关的参数设置；
*/
/************************************************************************/
struct CCardiacGating
{
    //! Heart rate, per minute.
	//心率
    U2	m_usRate;
	//! Time between peak of the R wave and the peak of the echo produced in ms.
	//触发延迟时间；
	U2 m_usTriggerDelayTime;
    //! Number of images per cardiac cycle.
    // 每个心电周期的图像个数；
	U1 m_usNumOfImages;	
	//! Percent of R-R interval, based on HeartRate, prescribed as a window for a valid/usable trigger.
    U1 m_usTriggerWin;	
    //! Number of beats skipped after a detected arrhythmia.
    //心率跳过的个数；
	U1 m_ucSkipBeat;
    //! Number of phase encodings per segment.
	U1 m_ucPhasesPerSegment;	
};

/************************************************************************/
/*
	Structure used to store cardiac or respiratory gating related parameters
*/
/************************************************************************/
struct CGatingParams
{
	// gating ID - no use
	I1 nGatingID;
	/*连续错误次数后报警 */
	I1 nNumOfMaxErrs;
	/*累计错误次数后报警 */
	I1 nNumOfTotalErrs; 
	/*触发延时时间       */
	I2 nDelay;
	/*间隔触发的周期数   */
	I1 nTriggerInterval;

	/*两次触发的最短时间 */
	I2 nMinTimeInterval;
	/*触发的次数		 */
	I2 nNumOfTriggers;

	// 呼吸平均周期，ms zyh add 2007.7.19
	I2 nPeriod;

	I1 Reserved[2];		//zyh ch 4 to 2 2007.7.19
};


/************************************************************************/
/*
	和breath hold有关的参数设置； wwz 2006-01-18, store breath hold params
*/
/************************************************************************/
struct CBreathHold
{    
	// Breath hold on or off
    I1 bBreathHold;
	
	//Breath hold time for every trigger
	U4 m_BreathHoldTime;
    
    // scan slices of every trigger 
	U2 m_NumOfSlicesPerBH;	

	//the number of trigger for all slices
    U1 m_NumOfTrigger;	 
	
	// combo box index for breath hold time
	U1 m_CBoxIndex;

	// single slice scan time
	U4 m_SingleSliceScanTime;
};

// in physical coordinate system
struct STRUCT_SLICE_PLANE_INFO
{
	// 中心点坐标
	float fCenterPoint_x, fCenterPoint_y, fCenterPoint_z;
	// 方向
	float FreqDirX,  FreqDirY,  FreqDirZ;
	float PhaseDirX, PhaseDirY, PhaseDirZ;
	float SliceDirX, SliceDirY, SliceDirZ;

	// 平面类型
	unsigned char nPlaneType;
};

/************************************************************************/
/*
	图像头文件； 
*/
/************************************************************************/
struct HeaderInfo
{
    I1	BITitle[5];			/* Storing string "BIMRI"					*/
    I4	Version;			/* Header file version, format:							
		     				   (major_version << 16) + minor_version.	*/
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
};

/************************************************************************/
/*
	设备参数结构；
*/
/************************************************************************/
struct SiteField
{
    I4	Version;	    	/* version of field, format:
							   (major_version << 16) + lower_version.	*/
    U2	Size;			    /* size of field = sizeof(SiteField_Struct) */
    I1	Id[16];				/* machine's ID								*/
    I1	InstName[32];		/* name of this site institution, 
							   CHN_BJ_TIANTAN001						*/
    I1	InstDeptName[32];	/* name of department						*/
    I1	StationName[32];	/* name of machine							*/
    I1	BISerialNum[32];	/* SN of the machine, assigned by BI		*/
    BIDateTime  LastCalib;	/* date and time of last calibration		*/
    F4	MagCalibStrength;	/* Calibrated field strength. (Tesla)		*/
    F4	GradientStrengthX;	/* Calibrated maximum gradient strength	in	
							   X direction, in mTesla/m					*/    
    F4	GradientStrengthY;	/* See above								*/
    F4	GradientStrengthZ;	/* See above								*/
	F4  SF;					/* Spectrometer frequency.					*/
    U1  Reserved[128];      /* Reserved space for this field.           */
};

/************************************************************************/
/*
	病人结果结构信息； 
*/
/************************************************************************/
struct PatientField
{
    I4	Version;			/* Version of this field. Format:
							   (major_version << 16) + lower_version.	*/
    U2	Size;				/* Size of this field.                      */	
    I1	Id[16];				/* Patient ID.								*/
    I1	Name[32];			/* Patient name, "family_name, first_name".	*/
    BIDateTime	BirthDate;	/* Patient birth date.				    	*/
    U1	Age;				/* Patient age.								*/
    I1	Sex;				/* Patient Sex: 
							   'M' : MALE , 'F': FEMALE, or 'U': UNKNOWn*/
    U2	Weight;				/* Weight of patient in kilogram.			*/
    I1	Desc[128];			/* Description of patient background, 
							   history and other info					*/
    U1  Reserved[128];      /* Reserved space for this field.           */
};

/************************************************************************/
/*
	Study病人信息； 
*/
/************************************************************************/
struct StudyField
{
    I4	Version;			/* Version of this field. Format:
							   (major_version << 16) + lower_version.	*/
    U2	Size;				/* Size of this field.                      */	
    I1	Id[16];				/* Study ID	== ui_studyID, it's a unique id					
							   in the range of a hospital.				*/
    I1	Desc[128];			/* Description of study	
								== ui_studyDescription					*/
    I1	Protocol[32];		/* Name of protocol: == ui_clinicalProtocol */
    U2	ProtocolVersion;	/* Version of protocol used.				*/
    BIDateTime	Time;		/* the date and time of study*/
    I1	OperatorID[16];		/* ID of the operator: == ui_operatorID		*/
    I1	Radiologist[32];	/* Name of the radologist/specialist: 
							   == ui_radiologistName					*/
    I1	RefPhy[32];			/* Name of referring physician: 
							   == ui_referalPhysician					*/
    U1	PatPosition;        /* Position of the patient: ==ui_lyingPos.   
								See enum BODYPOS.						*/
    U1	PatEntry;           /* Patient entry direction:
								== ui_bodyEntry
								enum BODYENTRY {HEAD_FIRST, FOOT_FIRST}	*/
    U1	PatBodyPart;        /* Part of body examined: ==ui_bodyPart
							   See enum BODYPART.						*/
    U1	LandmarkPos;        /* Scan landmark position reference: 
							   ==ui_landmarkPos. See enum LandPARKPOS.  */
    I1	GradientId[32];		/* ID of Gradient coil.						*/
	I1  MrNo[32];			// {ZLX,2006.01.06}
	I1  BodyPart[32];		// {ZLX,2006.01.06}
	//Added by Tom, --2008.07.10
	I1  ScanType[32];

    U1  Reserved[32];      /* Reserved space for this field.           */
};


/*********************************************************
定义序列的参数设定；
**********************************************************/
struct SeriesField
{
    I4	Version;			/* Version of this field. Format:
							   (major_version << 16) + lower_version.	*/
    U2	Size;				/* Size of this field.                      */	
    U1	Id;					/* Series ID: == ui_seriesID. Series id is				
		     				   a sequential number assigned to every 
							   series in a study.						*/
    I1	Desc[128];			/* Series description: 
							   == ui_seriesDescription					*/
    I1	Protocol[32];       /* Name of series protocol: 
							   == ui_seriesProtocolName					*/
    I2	NucType;	    	/* Type of nuclei: ==ui_nuclei. 
							   See enum NUCTYPE.						*/
    I4	GRR;				/* Gyromagnetic resonance ratio of the 
							   nuclei (Hz/Tesla): == I4 Gyro[256]		*/
	U1  TXCoil;			    /* Transmitter RF coil: == ui_coilTrans
							   See enum COILTYPE.						*/
	I1  UserTxCoilDesc[32];	/* Description of the user type transmitter
						    	coil. Used only when TXCoil == USER.	*/
	U1  RcvCoil;			/* Receiver RF coil: == oi_coilRecv.		
							   Can be same as TXCoil.					*/
	I1	UserRcvCoilDesc[32];/* Description of the user type receiver
							   coil. Used only when RcvCoil == USER.	*/
	I1	PulseSeqName[64];	/* Name of the pulse sequence, corresponds 
							   to the enum value ui_pulseSequenceName,
							   but show the descriptive name.			*/

	// added by Yang Guang
    I4  SequenceOptions;    /* Options related to pulse sequences.      */
    I4  OtherOptions;       /* Options not influence the pulse sequence.*/
	I1  RefSeries1;			/* ID of the first reference series. 
                               -1 not used.                             */
	I1	RefImage1;			/* ID of prefered reference image in the 
							   first reference series.					*/
	I1  RefSeries2;			/* ID of the second reference series.		*/
	I1	RefImage2;			/* ID of prefered reference image in the 
								   second reference series.				*/
	// end added by Yang Guang

	// following parameters are moved from ScanField.
    U1	Plane;              /* Scan plane: == ui_imagePlane;
								   See enum IMAGEPLANE.					*/
	U1	Mode;				/* == ui_imageMode; see enum IMAGEMODE		*/

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
	F4	SliceThickness;		/* Slice thickness in mm,  ==ui_sliceThk;   */
    U2	NumSlab;			/* Number of slabs in 3D scan.				*/
    U1	SlabOrder;			/* Order of a slab, see enum PhEncOrder		*/
	U2	NumPntsPerSlab;		/* Resolution along Z in one slab			*/
	U2	SlabOverlap;		/* Number of overlapped slice between two 
							   adjacent slabs.							*/
/*
	U2	SliceGap;			/ * Gap between two adjacent slices in mm. 
							   == ui_sliceGap							* /
*/
	// {xuzhl,2005.12.09} change data type from U2 to F4
	F4	SliceGap;			/* Gap between two adjacent slices in mm. 
							   == ui_sliceGap							*/

	U4	EchoTime;			/* TE, the echo time in ms, == ui_TE		*/
	U4	Echo2Time;			/* TE2, the second echo time, this is used 
							   for multiple images with different 
							   T2/T2* weighting.						*/
    U4  EchoSpacing;        /* Space between echos, in us. Used in FSE. */
	I4	RepTime;			/* pusle repetition time in ms, == ui_TR	*/
	U2	NumEchoImages;		/* Number of different T2/T2* weighted 
							   images, == ui_numEchoImages				*/
	F4	AcqBandwidth;		/* Acquisition bandwidth of the first echo,
							   == ui_acqBandwidthArray[0]				*/
	F4	AcqBandwidth2;		/* Bandwidth of second or higher echoes,
							   == ui_acqBandwidthArray[1]				*/
	U2	EchoTrainLength;	/* Echo train length for EPI or FSE,
							   == ui_echoTrainLength					*/
	F4	FlipAngle;			/* Flip angle of the excitation pulse. It's
							   normally 90 degrees for Spin Echo pulse
							   sequence and it will not be displayed or 
							   changed. It ranges from -180 to 180 deg. */

    I4	GradientShimX;		/* Gradient shimming level along X-axix		*/
    I4	GradientShimY;		/* Gradient shimming level along Y-axix		*/
    I4	GradientShimZ;		/* Gradient shimming level along Z-axix		*/
    I4	SARAvg;				/* Calculated whole body average Specific 
							   Absorption Rate in watts/kilogram		*/
    I4	SARPeak;			/* Calculated peak Specific Absorption Rate
							   in watts/kilogram						*/
    I2	DigFilterType;		/* Digital filter type. 0 means None		*/
    F4	DigFilterPar[8];	/* Parameters used to define the digital
							   filter whose type is DigFilterType.		*/
    I2	WindowLevel;		/* Display window level, determinded from
							   the mean signal I4ersities of all the
							   images in the scan.						*/
    I2	WindowWidth;		/* Display window width, determined from 
							   the standard deviation of the pixel 
							   signal I4ensities of all the images in 
							   the scan.								*/
//	I2	NumSlices;			/* Number of slices in 2D scan,
//							   == ui_numSlices							*/
//    I1	CardiacGate;		/* Flag for cardiac gating, TRUE or FALSE
//							   == ui_cardiacGating						*/

	I1  FlowCompensation;
	CPresaturationRegion	PresaturationRegions[6];
	//CRespiratoryTrigger     RespiratoryTrigger;
	//CCardiacGating			CardiacGating;	// shared by cardiac and peripheral
	CGatingParams  GatingParams;
	U1	PompNumber;
	U1	NumOfAngioImages;

	F4	HalfKSpaceRatio;	/* The ratio of phase and frequency 
							   encodings for half Fourier imaging.		*/

	I1	ContrastFlag;		/* Whether a contrast agent is used.        */

    I1	IVContrast[32];		/* The IV contrast agent applied			*/
    I1	OralContrast[32];	/* The Oral contrast agent appied.			*/
	F4	ContrastAmount;		/* Amount of constrast agent applied in ml. */

    F4	PauseTime;			/* The pause time between scan. (slice)		*/
    I2	NumAvg;				/* Number of scans, == ui_NumAvg			*/
    I2	PhEncOrder;			/* The phase encodig order. 
							   see enum PhEncOrder.						*/
    I2	Saturation;			/* Type of saturation, see enum SAT.		*/
    I4	TI;				    /* Saturation inversion time in ms.			*/

    U1	DataType;           /* Data type of image, bit array. Flags:
	                           RAW,IMAGE,MAG,PHASE,REAL,IMAGINARY		*/
	U2  ReadPoints;			/* Points sampled in each fid.				*/
	U2  PhasePoints;		/* Phase encoding number.					*/
	F4  EchoRatio;			/* Half echo ratio.							*/
	BIDateTime DateTime;	/* Image Date & Time, by Rodger, 2005.02.23	*/
	F4  ScaleRatio ;        /*Modified by Tom, 2005.6.23*/
    //用于标识MRA序列是否做过MIP;
	//0: 代表没有做过;1: 代表做过MIP;
	I1  i_flag;             //Modified by Lwz  2005-07-04;
	I1	nPlaneType;			// {xuzhl,2005.12.02} store plane type of series
	
	I1 bSliceZip;			// {DX,2005.12.29} for slice reconstruction	

	CBreathHold BreathHold;	// wwz 2006-01-18, store breath hold params

	I4 nTI2;				// added for double inversion pulses 2006-06-22
	I2 nNumOfCardiacPhase;  // added for Cine imaging 2006-06-22

	// 用于LSDWI
	// 最大B值
	U2 nMaxBFactor;	
	// B值个数。各个B值由nMaxBFactor计算得到。
	U1 nNumOfB;
	// 扩散成像扫描方法，DI－Diffusion Imaging。编码如下：
	//	1－DWI（1D）；
	//	2－DWI（3D）；
	//	3－扩散张量（DTI）。
	U1 nMethodOfDI;	

	// 预扫描执行标志
	bool bAdjustTG;
	bool bAdjustRG;
	bool bTuningRFCoil;
	
	bool bAuto1stShimming3Chn;

	U1 nNumOfPass;	/* Number of pass */ //added by WYH for multi pass
	U1 nSlicePerPass;
	F4 FOVRatio;

	/** [zhlxu 2007.9.30] 用于调整扫描层顺序 **/
	bool bDefaultSliceOrder;
	/** [zhlxu 2007.9.30] **/
	
	//Added by Tom, --2008.07.10
	U1  nInterval;			//pause time between scans, for cycle scan
	U1  bRemote ;           //if 0: Loc Series; >0:Remote(intervention).

	I1  Reserved[193];

	SeriesField()
	{
		nMethodOfDI = 1;
		
		bAdjustTG = true;
		bAdjustRG = true;
		bTuningRFCoil = false;
		bDefaultSliceOrder = true;
	}

};  // sizeof(SeriesField) = 586

/*****************************************
扫描序列信息；
 *****************************************/
struct ScanField
{
    I4	Version;			/* Version of this field. Format:
							   (major_version << 16) + lower_version.	*/
    U2	Size;				/* Size of this field.                      */	
    I4	Id;			        /* Scan ID, sequential number in series.	*/
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
	F4   FreqDirX;			
	F4   FreqDirY;
	F4   FreqDirZ;          /* Frequence encoding direction			*/
	
    F4   PhaseDirX;
	F4   PhaseDirY;
	F4   PhaseDirZ;			/* Phase encoding direction                 */

    // added by Xie
	F4	SliceDirX;
	F4	SliceDirY;
	F4	SliceDirZ;

	F4	ReadOffset;
	F4	PhaseOffset;		/* center point, in mm						*/
	F4	SliceOffset;
    // end added by Xie

    F4	RFTxLev;			/* Hardware RF transmitter power level (TG)	*/
    F4	AnaRCGain;			/* Hardware analog receiver level (.1db).
							   NO analog gain for RI system(?)   		*/
    F4	DigRCGain;			/* Digital receiver gain. (.1db)(?)	RxLevel	*/
    F4	O1;					/* Transmitter center frequency offset.		*/
	U2  ACQ;				/* ACQ time of scan, in seconds.			*/

	// {xuzhl, 2005.12.07} store default orientation params of slab
	F4  DefaultFreqDirX;			
	F4  DefaultFreqDirY;
	F4  DefaultFreqDirZ;          /* Frequence encoding direction			*/
	
    F4  DefaultPhaseDirX;
	F4  DefaultPhaseDirY;
	F4  DefaultPhaseDirZ;			/* Phase encoding direction                 */
	
	F4	DefaultSliceDirX;
	F4	DefaultSliceDirY;
	F4	DefaultSliceDirZ;
	
	F4	DefaultReadOffset;
	F4	DefaultPhaseOffset;		/* center point, in mm						*/
	F4	DefaultSliceOffset;
    
    F4	fMcRxLevel[10];				/* Digital RF receiver gain. (.1db)(?)	(Multi-Channel RG)		*/

	F4  RelSNR;//20070718.liuxuan.for RelSNR
	F4  DefRelSNR;//20070718.liuxuan.for RelSNR

	bool bDefaultFreqDir;

	//Added by Tom, --2008.07.10
	I4  nNumOfScans;		// IMRI, 重复扫描时，对扫描次数进行编号
	I1	Reservered[150];	/* User defined scan variables.				*/

	ScanField()
	{
		DigRCGain = 0.0;
		for ( int i=0; i<10; i++)
		{
			fMcRxLevel[i] = 0.0;
		}
	}
};

/************************************************************************/
/*
	图像序列信息； 
*/
/************************************************************************/
struct ImageField
{
    I4		Version;			/* Version of this field. Format:
								   (major_version << 16) + lower_version.	*/
    U2		Size;				/* Size of this field.                      */	
    U2		Id;					/* Image ID, sequential number in scan.		*/
    U1	    Type;               /* Image type, which can be one of the 
								   following: {MPR, PROJECTION_IMAGE, T1_MAP, 
								   T2_MAP, DIFFUSION_MAP, DENSITY_MAP, 
	                               PHASE_MAP,VELOCITY_MAP,IMAGE_ADDITION,
	                               PHASE_SUBTRACT, MODULUS_SUBTRACT, OTHER}	*/
    I2		IntensityMean;		/* Mean I4ensity of the image.				*/
    I2		IntensityDev;		/* Standard deviation of I4ensity of image */
    I2		WindowLevel;        /* Display window level, which is determined
	                               by the mean I4ensity of the image		*/
    I2		WindowWidth;        /* Display window width, which is determined 
								   by the standard deviation of the signal 
								   I4ersities of the image.				*/
    U2		EchoNum;            /* Echo number corresponding to this image	*/
    I2		OffsetSI;           /* Distance from the center of image to the 
								   center of reference poI4 along superior-
								   inferior line (superior is positive, mm) */
    I2		OffsetAP;           /* Distance from the center of image to the
								   center of reference poI4 along anterior-
								   posterior (anterior is positive, mm)		*/
    I2		OffsetLR;           /* Distance from the center of image to the
								   center of reference poI4 along left-right
								   line	(left is positive). (mm)			*/
	I4		CardDelayTime;		/* The cardiac delay time in usec.			*/
	BIDateTime DateTime;		/* Image Date & Time, by Rodger, 2005.02.23	*/

	// for Intervention, Gradient correction, RF correction
	// in physical coordinate system
	// FovX and FovY are in ScanField
	// ReadPoints and PhasePoints are in SeriesField
	F4 fCenterPointX, fCenterPointY, fCenterPointZ;		// coordinates of slice's center point
	F4 fFreqDirX,  fFreqDirY,  fFreqDirZ;	// direction of read encoding
	F4 fPhaseDirX, fPhaseDirY, fPhaseDirZ;	// direction of phase encoding
	F4 fSliceDirX, fSliceDirY, fSliceDirZ;	// direction of slice encoding
	U1 nPlaneType;
	
	// 用于LSDWI
	// 扩散成像的图形类型。用于显示。编码如下：
	//	1－ADC（1D）。子类型：11。标注：B：ADC。
	//	2－ADC（3D）。子类型：21－ADC（3D）1，标注：B：ADC；22－ADC（3D）FA，标注：B：FA。
	//	3－扩散张量（DTI）。子类型，31－子类型1（SubType1），标注：B：SubType1；32－子类型2（SubType2），标注：B：SubType2
	U2 nTypeOfDiffusionImage;
	// 扩散成像的B值。用于显示，根据nTypeOfDiffusionImage的类型值进行显示处理。
	U2 nBFactor;		
	//Modified by Tom, --2008.07.10
    U1      Reserved[ 64];      /* Reserved space for this field.           */
};

typedef HeaderInfo		HEADER_INFO;
typedef	SiteField		SITE_FIELD;
typedef PatientField	PATIENT_FIELD;
typedef StudyField		STUDY_FIELD;
typedef SeriesField		SERIES_FIELD;
typedef ScanField		SCAN_FIELD;
typedef ImageField		IMAGE_FIELD;

/************************************************************************/
/*
   BIImage Header Information  
*/
/************************************************************************/
struct CBIImageHeader
{
    HEADER_INFO		headInfo;
    SITE_FIELD		siteField;
    PATIENT_FIELD	patientField;
    STUDY_FIELD		studyField;
    SERIES_FIELD	seriesField;
    SCAN_FIELD		scanField;
    IMAGE_FIELD		imageField;
};

struct CBIPushStruct
{
	short           *pImageData;
	CBIImageHeader  imageHeader;
};

enum RF_RCV_COIL_TYPE
{
	RCV_COIL_TYPE___LINEAR = 0,
		RCV_COIL_TYPE___QUADRATURE = 1,
		RCV_COIL_TYPE___PHASE_RESONANCE = 2,
};

#define MAX_NUM_OF_CHANNELS_SUPPORTED_BY_SOFTWARE		32

struct CCoilSpec
{
	BYTE   m_bQuad;				// type of coil
	
	double m_dRFAMax;
	double m_dDefaultTG;
	int    m_nTuneVoltage;
	int    m_nMatchVoltage;
	int    m_nTuneVoltage1;
	int    m_nMatchVoltage1;
	short  m_sId;
	char   m_sName[50];
	int	   nBodyPartID;
		
	short  nMaxNumOfChannels;		// 0 < nMaxNumOfChannel <= 20
	bool   bMcEnabled[ MAX_NUM_OF_CHANNELS_SUPPORTED_BY_SOFTWARE ];
	float  fReconCoeff[MAX_NUM_OF_CHANNELS_SUPPORTED_BY_SOFTWARE];	// 重建时各个通道的加权系数
	short  nNumOfEnableChannels;	// 0 < nNumOfEnableChannels <= 20
	bool   bCompoundReconResult;
	
	CCoilSpec()
	{
		nMaxNumOfChannels = 0;
		nNumOfEnableChannels = 0;
		for ( int i=0; i< MAX_NUM_OF_CHANNELS_SUPPORTED_BY_SOFTWARE; i++ )
		{
			bMcEnabled[i]  = false;
			fReconCoeff[i] = 1.0;
			bCompoundReconResult = true;
		}
	}
};

/************************************************************************/
/* beign //dolphin                                                      */
/************************************************************************/
#pragma warning (disable:4076)
#pragma warning (disable:4518)


CString	AFX_EXT_API dataTypetoString(int iParam);
CString	AFX_EXT_API dataTypetoString(long iParam);
CString	AFX_EXT_API dataTypetoString( char* iParam);
CString	AFX_EXT_API dataTypetoString( short iParam);
CString	AFX_EXT_API dataTypetoString( double iParam);
CString	AFX_EXT_API dataTypetoString( float iParam);

CString	AFX_EXT_API dataTypetoString(unsigned int iParam);
CString	AFX_EXT_API dataTypetoString(unsigned long iParam);
CString	AFX_EXT_API dataTypetoString(unsigned  char* iParam);
CString	AFX_EXT_API dataTypetoString(unsigned  short iParam);
//CString	AFX_EXT_API dataTypetoString(unsigned  double iParam);
//CString	AFX_EXT_API dataTypetoString(unsigned  float iParam);
CString	AFX_EXT_API F4ArraytoString( float iParam[],int length);

U1	AFX_EXT_API	CStringtoU1(CString parameter);
U2	AFX_EXT_API	CStringtoU2(CString parameter);
U4	AFX_EXT_API	CStringtoU4(CString parameter);
I1	AFX_EXT_API	CStringtoI1(CString parameter);
I2	AFX_EXT_API	CStringtoI2(CString parameter);
I4	AFX_EXT_API	CStringtoI4(CString parameter);
I8	AFX_EXT_API	CStringtoI8(CString parameter);
F4	AFX_EXT_API	CStringtoF4(CString parameter);
F8	AFX_EXT_API	CStringtoF8(CString parameter);

bool	AFX_EXT_API	CStringtoI1Array(CString parameter,int length,I1 I1Array[]);
//I1*	AFX_EXT_API	CStringtoI1Array(CString parameter,int length);
bool AFX_EXT_API	CStringtoF4Array(CString parameter,int length,F4 F4Array[]);


/*
CString	AFX_EXT_API dataTypetoString(int iParam)
{
	char *cTemp = new char[15];
	itoa(iParam,cTemp,10);
	CString temp(cTemp);
	delete[] cTemp;
	return temp;

}


CString	AFX_EXT_API dataTypetoString(long iParam)
{
	char *cTemp = new char[15];
	ltoa(iParam,cTemp,10);
	CString temp(cTemp);
	delete[] cTemp;
	return temp;
}

CString	AFX_EXT_API dataTypetoString( char* iParam)
{
	int iCount=0;
	char* cTemp = iParam;
	while ((cTemp++)!='\0')
	{
		iCount++;
	}
	char* cTemp1 = new char[iCount+1];
	for(int i=0;i<=iCount;i++)
		*(cTemp1++) = *(iParam++);
	CString temp(cTemp);
	delete[] cTemp1;
	return temp;
}
CString	AFX_EXT_API dataTypetoString( short iParam)
{
	char *cTemp = new char[15];
	itoa(iParam,cTemp,10);
	CString temp(cTemp);
	delete[] cTemp;
	return temp;
}

CString	AFX_EXT_API dataTypetoString( double iParam)
{
	char *cTemp = new char[15];
	ltoa((long)iParam,cTemp,10);
	CString temp(cTemp);
	delete[] cTemp;
	return temp;
}

CString	AFX_EXT_API dataTypetoString( float iParam)
{
	char *cTemp = new char[15];
	ltoa((long)iParam,cTemp,10);
	CString temp(cTemp);
	delete[] cTemp;
	return temp;
}

CString	AFX_EXT_API F4ArraytoString( float iParam[],int length)
//用以下格式存储(以S字符为分隔)：float[0]Sfloat[1]S.....
{
	char *cTemp = new char[15];
	CString temp("");
	for(int i=0;i<length;i++){
		ltoa((long)iParam[i],cTemp,10);
		temp.Format(temp+cTemp+'S');
	}
		
	delete[] cTemp;
	return temp;
}

CString	AFX_EXT_API dataTypetoString(unsigned float iParam)
{
	char *cTemp = new char[15];
	ltoa((long)iParam,cTemp,10);
	CString temp(cTemp);
	delete[] cTemp;
	return temp;
}
/*
CString	AFX_EXT_API dataTypetoString(unsigned double iParam)
{
	char *cTemp = new char[15];
	ltoa((long)iParam,cTemp,10);
	CString temp(cTemp);
	delete[] cTemp;
	return temp;
}
*//*
CString	AFX_EXT_API dataTypetoString(unsigned short iParam)
{
	char *cTemp = new char[15];
	itoa(iParam,cTemp,10);
	CString temp(cTemp);
	delete[] cTemp;
	return temp;
}



/*
CString	AFX_EXT_API dataTypetoString(unsigned int iParam)
{
	char *cTemp = new char[15];
	itoa(iParam,cTemp,10);
	CString temp(cTemp);
	delete[] cTemp;
	return temp;

}*//*

CString	AFX_EXT_API dataTypetoString(unsigned long iParam)
{
	char *cTemp = new char[15];
	ltoa(iParam,cTemp,10);
	CString temp(cTemp);
	delete[] cTemp;
	return temp;
}

CString	AFX_EXT_API dataTypetoString(unsigned char* iParam)
{
	int iCount=0;
	unsigned char* cTemp = iParam;
	while ((cTemp++)!='\0')
	{
		iCount++;
	}
	char* cTemp1 = new char[iCount+1];
	for(int i=0;i<=iCount;i++)
		*(cTemp1++) = *(iParam++);
	CString temp(cTemp);
	delete[] cTemp1;
	return temp;
}





U1*	AFX_EXT_API	CStringtoU1(CString parameter)
{
	char *cTemp = new char[parameter.GetLength()];
	for(int i =0;i<parameter.GetLength();i++)
		cTemp[i] = parameter.GetAt(i);
	delete[] cTemp;
	return (U1*)cTemp;
}

U2	AFX_EXT_API	CStringtoU2(CString parameter)
{
	char *cTemp = new char[parameter.GetLength()];
	for(int i =0;i<parameter.GetLength();i++)
		cTemp[i] = parameter.GetAt(i);
	int iTemp = atoi(cTemp);
		delete[] cTemp;

	return (U2) iTemp;
	
}
U4	AFX_EXT_API	CStringtoU4(CString parameter)
{
	char *cTemp = new char[parameter.GetLength()];
	for(int i =0;i<parameter.GetLength();i++)
		cTemp[i] = parameter.GetAt(i);
	int iTemp = atoi(cTemp);
		delete[] cTemp;

	return (U4) iTemp;
}
I1*	AFX_EXT_API	CStringtoI1(CString parameter)
{
	char *cTemp = new char[parameter.GetLength()];
	for(int i =0;i<parameter.GetLength();i++)
		cTemp[i] = parameter.GetAt(i);
	delete[] cTemp;

	return (I1*)cTemp;
}
I2	AFX_EXT_API	CStringtoI2(CString parameter)
{
	char *cTemp = new char[parameter.GetLength()];
	for(int i =0;i<parameter.GetLength();i++)
		cTemp[i] = parameter.GetAt(i);
	int iTemp = atoi(cTemp);
	delete[] cTemp;

	return (I2) iTemp;
}
I4	AFX_EXT_API	CStringtoI4(CString parameter)
{
	char *cTemp = new char[parameter.GetLength()];
	for(int i =0;i<parameter.GetLength();i++)
		cTemp[i] = parameter.GetAt(i);
	int iTemp = atoi(cTemp);
	delete[] cTemp;

	return (I4) iTemp;
}
I8	AFX_EXT_API	CStringtoI8(CString parameter)
{
	char *cTemp = new char[parameter.GetLength()];
	for(int i =0;i<parameter.GetLength();i++)
		cTemp[i] = parameter.GetAt(i);
	long iTemp = atol(cTemp);
	delete[] cTemp;

	return (U4) iTemp;
}
F4	AFX_EXT_API	CStringtoF4(CString parameter)
{
	char *cTemp = new char[parameter.GetLength()];
	for(int i =0;i<parameter.GetLength();i++)
		cTemp[i] = parameter.GetAt(i);
	double iTemp = atof(cTemp);
	delete[] cTemp;

	return (F4) iTemp;
}
F8	AFX_EXT_API	CStringtoF8(CString parameter)
{
	char *cTemp = new char[parameter.GetLength()];
	for(int i =0;i<parameter.GetLength();i++)
		cTemp[i] = parameter.GetAt(i);
	double iTemp = atof(cTemp);
	delete[] cTemp;

	return (F8) iTemp;
}

bool AFX_EXT_API	CStringtoF4Array(CString parameter,int length,F4 F4Array[])
//解析格式： float[0]Sfloat[1]S.....float[length]S
/*{
	int iCount =0,iNum =0;
	while (iCount++<parameter.GetLength()) {
		if (parameter.GetAt(iCount) =='S') {
			iNum++;
		}
	}
	if (iNum!=length) 
	{
		for(int i =0;i<length;i++)
			F4Array[i] = 0.0;
		return false;
	}
		 
	/*	F4 resultF4Array = new F4[iNum] ;
		for(int i =0;i<iNum;i++)
			resultF4Array[i] = 0.0*/
/*
	char *cTemp = new char[parameter.GetLength()];
	iCount =0;
	int istrF4ValueCount =0,iF4NumeberCount =0;
	//double F4ValueTemp = 0.0;
	while (iCount<parameter.GetLength()) {
		cTemp[istrF4ValueCount] = parameter.GetAt(iCount);
		istrF4ValueCount++;
		iCount++;
		if (parameter.GetAt(iCount) != 'S') {
			cTemp ="";
			iCount++;
			istrF4ValueCount =0;
			if (iF4NumeberCount<length) 
			F4Array[iF4NumeberCount] = (F4)atof(cTemp);
			iF4NumeberCount++;
		}
	}
	return true;
	
}
/************************************************************************/
/* end                                                                     */
/************************************************************************/


#endif
