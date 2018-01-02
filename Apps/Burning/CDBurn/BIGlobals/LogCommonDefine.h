// CommonDefine.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(__LOG_COMMON_DEFINE_H__)
#define __LOG_COMMON_DEFINE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ------------------------------------------ 系统故障诊断
// *************** 记录公共定义
// 来源模块代码, TSM--Type of Source Module
enum ENUM_TYPE_OF_SOURCE_MODULE
{
	TSM_NONE			= 0,	// NONE

	TSM_SW				= 1,	// 成像软件子系统
	TSM_MW				= 2,	// 磁体子系统
	TSM_RW				= 3,	// 射频子系统
	TSM_GW				= 4,	// 梯度子系统
};

// 数据主类型代码, TD--Type of Data
enum ENUM_TYPE_OF_DATA
{
	TD_NONE				= 0,	// NONE 
	
	// SW-成像软件子系统
	TD_TG				= 1,	// TG 
	TD_RG				= 2,	// RG
	TD_O1				= 3,	// O1
	TD_TUNING_MEAN		= 4,	// 信号平均值

	// MW-磁体子系统
	// (TBD)
};
// 数据子类型代码, TD--Type of Data
enum ENUM_SUBTYPE_OF_DATA
{
	STD_NONE			= 0,	// NONE 
		
	// SW-成像软件子系统
	// RG -- 本软件最大支持32个通道
	STD_RG1				= 1,	// 通道1
	STD_RG2				= 2,	// 通道2
	STD_RG3				= 3,	// 通道3
	STD_RG4				= 4,	// 通道4

	// TUNING -- 两个通道
	STD_TUNING_CHANNEL_I	= 33,	// 通道I
	STD_TUNING_CHANNEL_Q	= 34,	// 通道Q
};

// 记录的公共信息
struct STRUCT_DIAGNOSIS_BASE
{
	ENUM_TYPE_OF_DATA			nDataType;			// 来源模块中的数据主分类代码。即记录主类型。用于数据的记录存取
	ENUM_SUBTYPE_OF_DATA		nDataSubType;		// 来源模块中的数据子分类代码。即记录子类型。
													// 当nDataType为TD_RG时，nDataSubType为接收通道号
													// 当nDataType为TD_TUNING_MEAN时，nDataSubType为I/Q通道号
	
	ENUM_TYPE_OF_SOURCE_MODULE	nSourceModule;		// 来源模块代码
	char sEquipNo[32];								// MRI系统编号。即设备统一编号,32 Bytes, SiteField.BISerialNum
	time_t nTime;									// 记录产生的时间
	char sStudyID[16];								// Study的编号
	int  nSeriesID;									// Series的编号，不同Study中的SeriesID可重复
	BYTE nBodyPartID;								// 检查部位代码
	long nSequenceID;								// 脉冲序列代码。只有正式扫描序列才有ID
};

// *************** 具体记录定义
// 记录 (TG、RG、O1)
// 多通道也使用本结构
struct STRUCT_RECORD_DIAGNOSIS_TG_RG_O1
{
	STRUCT_DIAGNOSIS_BASE	oBaseInfo;
	int		nNumOfData;				// 实际数据个数
	float	fValue[50];				// 一组TG/RG/O1值，有效个数为nNumOfData
};

// 记录 (Coil Tuning Mean)
// I、Q通道使用本结构
struct STRUCT_RECORD_DIAGNOSIS_TUNING_MEAN
{
	STRUCT_DIAGNOSIS_BASE	oBaseInfo;	
	int		nNumOfData;				// 实际数据个数
	int		nTuneVoltage[200];		// Tune电压值，有效个数为nNumOfData
	int		nMatchVoltage[200];		// TMatch电压值，有效个数为nNumOfData
	int		nTuneStepVoltage[200];		// 电压值步长，有效个数为nNumOfData
	int		nMatchStepVoltage[200];		// 电压值步长，有效个数为nNumOfData
	float	fMean[200];				// 信号平均值，有效个数为nNumOfData
};
//主要用于记录使用的IQ通道基本数据
struct STRUCT_RECORD_POS_TUNING_MEAN
{
	CRect pRect;
	int nTuneVoltage;
	int nMatchVoltage;
	int nStepVoltage;
	float fMean;
};

// ------------------------------------------------------------------------------------------


#endif // !defined(__LOG_COMMON_DEFINE_H__)
