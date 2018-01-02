// ConfigManager.h
//
#if !defined(AFX_CONFIGMANAGER_H__F6D52C2B_BD9B_4EB8_AAC3_647AD9D49E25__INCLUDED_)
#define AFX_CONFIGMANAGER_H__F6D52C2B_BD9B_4EB8_AAC3_647AD9D49E25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning (disable:4786)
#include <string>
#include <map>
#include <vector>

//#include "../BIGlobals/BI_ImageHeader.h"
#include "../ImageHeader/bi_constants.h"
#include "BI_ImageHeader.h"

#ifdef BIGLOBALS_IMP
   #define CLASS_DECL_BIGLOBALS  __declspec(dllexport)
#else
   #define CLASS_DECL_BIGLOBALS  __declspec(dllimport)
#endif

typedef BOOL(CALLBACK *SENDIMAGES)(char *, char *, char *, char *, char *);

typedef std::map<ECoilType, CCoilSpec> CSpecFromCoil;
typedef CSpecFromCoil::iterator CSpecFromCoilIter;

struct CBWDead2
{
	double m_dBW;
	double m_dDead2;
	double m_dDeadAct;
};

typedef std::vector<CBWDead2> CBWDead2Container;
typedef CBWDead2Container::iterator CBWDead2Iter;

class CSystemParams
{
public:
	double m_dGxFF;
	double m_dGyFF;
	double m_dGzFF;
	int m_nGxRampRate;
	int m_nGyRampRate;
	int m_nGzRampRate;
	int m_nGateTime;
	int m_nGxRFDelay;
	int m_nGyRFDelay;
	int m_nGzRFDelay;
	double m_dFactorGx;
	double m_dFactorGy;
	double m_dFactorGz;
	double m_dRFScale;

	CSystemParams();
};

class CFilmingConfig
{
public:
	CString	m_strFilmSize;
	CString	m_strLayout;
	CString	m_strImageName;
	CString	m_strFilmRelease;
	CString	m_strLookupTable;
	CString	m_strMediaType;
	CString	m_strProcessor;
	CString	m_strEmptyImageDensity;
	CString	m_strPrinterAE;
	CString	m_strLocalAE;
	CString	m_strIP;
	UINT	m_iMax;
	UINT	m_iMin;
	CString	m_strBorder;
	CString	m_strTrim;
	CString	m_strPort;
	int		m_nImageSize;
	//定义打印机类型;
	int		m_nPrintType;
	//add chenshi
	CString m_szLocalPrintPath;
	//zi字体以及页边距，以及某个字段是否书写的配置文件
	CString m_szCharactorConfigInfo;
	//打印机配置文件
	CString m_szPrintTypeInfoPath;
	//end chenshi

public:
	CFilmingConfig();
};


class CTGTuneRange
{
public:
	unsigned short m_nStartVal;
	float          m_fStep;
	unsigned short m_nNumOfSteps;
	float		   m_fRange; // 20070821 - 限制TG变动范围

	CTGTuneRange();
protected:
private:
};

//////////////////////////////////////////////////////////////////////////
// 涡流补偿数据－20061103
#define MAX_PREEMPHASIS_LEVEL 4
struct PreEmphasisParamsPair {
	float PREA;
	float PREK;
};

class CPreEmphasisParams
{
public:
	PreEmphasisParamsPair m_XChParams[MAX_PREEMPHASIS_LEVEL];
	PreEmphasisParamsPair m_YChParams[MAX_PREEMPHASIS_LEVEL];
	PreEmphasisParamsPair m_ZChParams[MAX_PREEMPHASIS_LEVEL];

	CPreEmphasisParams(){}
protected:
private:
};

//////////////////////////////////////////////////////////////////////////
// 系统调谐配置－20061103
enum TUNEMODE
{
	tmNotAvailable = 0,
	tmNotTune    = 1,
	tmAlwaysTune = 2,
	tmTuneFirstOnly = 3,
};

class CTuneConfig
{
public:
	TUNEMODE m_tmDefaultTuneModeTG;
	TUNEMODE m_tmDefaultTuneModeRG;
	TUNEMODE m_tmDefaultTuneModeRFRcvCoil;
	TUNEMODE m_tmDefaultTuneModeAutoShim;

	CTuneConfig()
	{
		m_tmDefaultTuneModeTG = tmAlwaysTune;
		m_tmDefaultTuneModeRG = tmAlwaysTune;
		m_tmDefaultTuneModeRFRcvCoil = tmTuneFirstOnly;
		m_tmDefaultTuneModeAutoShim  = tmTuneFirstOnly;
	}
};


enum ENUM_ANNOTATION_CODING_DIR_TYPE
{
	cdtFreqDirection = 0,
	cdtPhaseDirection = 1,
	cdtFreqAndPhaseDirection = 2,
};


//////////////////////////////////////////////////////////////////////////


//! This class provides a centralized management of the application configuration.
/*!
	There are many different software configurations in this application, such
	as the base directories used to store studies, protocols, and hardware 
	databases, and user preferences etc. This class provides a centralized and
	convenient way to manage all these configurations.

	Since there should be only one configuration manager in the whole system,
	this class is implemented as a Singleton, which provides a convenient way 
	of global access and ensures there can be only one instance of the manager
	in the application in the mean time.
*/
class CLASS_DECL_BIGLOBALS CConfigManager  
{
public:	//zyh change to public 2008.4.29
	CBWDead2Container m_BWDead2s;

public:
	CString GetStationNo();
	bool IsSysTimeout();
	bool IsSystemTest();
	SENDIMAGES m_SendImages;
	bool       IsQuadCoil(ECoilType coilType);
	ECoilType  GetDefaultSimmCoil(){return m_DefaultShimCoil;};
	HMODULE    GetCvieDllhModule();
	int        HasAdFilter();
	//! Destructor.
	virtual ~CConfigManager();
    //! Returns the handle to the only instance of this class.
	static CConfigManager& GetHandle();

    bool Save() const;
	bool SaveIni() ;//dolphin
	bool LoadIni() ;//dolphin
    bool Load();
	bool LoadBWDead2();
	bool LoadSystemParams();

	bool StoreRFCoilParams(ECoilType eCoilID, int nCHITuneV, int nCHIMatchV, int nCHQTuneV=0, int nCHQMatchV=0);
	bool LoadRFCoilParams(ECoilType eCoilID, int& nTypeOfCoil, int &nCHITuneV, int &nCHIMatchV, int &nCHQTuneV, int &nCHQMatchV);
	bool LoadRFCoilParams(void);
	bool AnalyzeRFCoilParams (const std::string& strVariable, const std::string& strValue);

	// 装载涡流补偿数据－20061103
	void LoadPreEmphasisParams(void);
	// 装载调谐模式配置-20070413
	void LoadTuneConfig(void);

	LPCSTR GetFilterPath() const;
	LPCSTR GetHomePath() const { return m_strHomePath; }

	//add by Tom. 2005.4.2
	//Dicom Push  Get Paras.
	HMODULE GetPushDllhModule();
	//add lwzh
	HMODULE GetPACSDLLMODULE();


	// check whether this program is running in debug mode?
	bool IsDebugMode(void) { return m_bDebugMode;}

	//Added by Tom, --2008.07.10
	bool    IsMaintainMode(void) { return m_bMaintainMode;}
	CString GetRIInstallPath(void) { return m_strRiInstPath;}

	HANDLE m_mutexRewriteTime;		//< Mutex used to protect write system time.
	LPCSTR GetLocalIP()
	{
		return  m_strLocalNodeIP.c_str();
	};
	LPCSTR GetLocalPort()
	{
		return  m_strLocalPort.c_str();
	};
	LPCSTR GetLocalAE()
	{
		return  m_strLocalAETitle.c_str();
	};
	LPCSTR GetRemoteIP()
	{
		return  m_strDefaultNodeIP.c_str() ;
	};
	LPCSTR GetRemotePort()
	{
		return  m_strDefaultPort.c_str();
	};
	LPCSTR GetRemoteAE()
	{
		return  m_strDefaultAETitle.c_str();
	};
	//Dicom Push  Set Paras.
	void SetLocalIP(CString csIP)
	{
		m_strLocalNodeIP = csIP;
	};
	void SetLocalPort(CString csPort)
	{
		m_strLocalPort = csPort;
	};
	void SetLocalAE(CString csAE)
	{
		m_strLocalAETitle = csAE;
	};
	void SetRemoteIP(CString csNodeIP)
	{
		m_strDefaultNodeIP = csNodeIP;
	};
	void SetRemotePort(CString csPort)
	{
		m_strDefaultPort = csPort;
	};
	void SetRemoteAE(CString csAE)
	{
		m_strDefaultAETitle = csAE;
	};
    //! Returns the root directory used to store image files.
	const std::string& GetImageRootDirectory() const;
	void SetImageRootDirectory(const std::string& strImageRootDirectory);

    //! Returns the directory used to store cdl files.
    const std::string& GetCDLDirectory() const;
    //! Returns the directory used to store temporary files.
    const std::string& GetTempDirectory() const;
    //! Returns the directory used to store deleted files.
    const std::string& GetRecycleDirectory() const;
    //! Returns the directory used to store protocols.
    const std::string& GetProtocolDirectory() const;
	//! Returns the directory used to store hardware configurations.
	const std::string& GetConfigDirectory() const;
	//! Returns path of the RI raw data file for images.
	const std::string& GetRIImageFile() const
	{
		return m_strRIImageFile;
	}
	//! Returns path of the RI raw data file for FID.
	const std::string& GetRIFidFile() const
	{
		return m_strRIFidFile;
	}
    //! Returns path of the installation files where binaries exist.
    const std::string& GetInstallDirectory() const
    {
        return m_strInstallDirectory;
    }

    //! Returns the site field
	SiteField& GetSiteField()
	{
		return m_SiteField;
	}

    //! Retuns the background color used for buttons, dialogs etc.
    COLORREF GetBackgroundColor() const;
    //! Returns the text color used for buttons, dialogs etc.
    COLORREF GetTextColor() const;
	//! Returns the maximum RFA value for a given coil.
	CCoilSpec GetCoilSpec(ECoilType coil);
	CTGTuneRange GetTGTuneRange() const {
		return m_TGTuneRange;
	}
	CPreEmphasisParams GetPreEmphasisPrams() const {
		return m_PreEmpahsisParams;
	}
	CTuneConfig GetTuneConfig(void) const {
		return m_TuneConfig;
	}
	bool IsTuning(TUNEMODE tmTuneMode, bool bIsFirstSeries);

	//! Returns the dead2 corresponding to the given bandwidth.
	CBWDead2 GetBWDead2(double dBW) const;
	//! Returns the nearest available bandwidth value according to the given one.
	double GetNearestBW(double dBW) const;

	CSystemParams& GetSystemParams() {
		return m_SystemParams;
	}
	const CSystemParams& GetSystemParams() const {
		return m_SystemParams;
	}

	CFilmingConfig& GetFilmingConfig() {
		return m_FilmingConfig;
	}
	const CFilmingConfig& GetFilmingConfig() const {
		return m_FilmingConfig;
	}

//Added by Tom, 2005.7.17
public:
	int     LoadFilterPara();
	CString m_csFilterName[15];
	int     m_nFilterNum;
	CString m_csFilterParaFileName[15];

protected:
	BOOL GetDirInfoFromRegistry();

// ===================== implement ============================================
public:
	CString m_csStationNo;
	bool CheckLeftDays();
	bool ReadCryptFile();
	bool m_bSysTimeout;
	bool m_bTest;
	void LoadDicomNodeInfo();
	/*********zyh add 2008.2.27*********/
	BOOL m_bHasDACard;
	/**********************************************/
	

	ECoilType        m_DefaultShimCoil;
	CSystemParams	m_SystemParams;
	CFilmingConfig	m_FilmingConfig;

	CString m_strFilterPath;
	CString m_strHomePath;

	//Added by Tom, --2008.07.10
	CString m_strRiInstPath ;

    std::string m_strConfigFile;        //!< Full name of the config file.
	std::string m_strConfigIniFile;
    
    std::string m_strInstallDirectory;  //!< Directory where application is installed.
    std::string m_strImageRootDirectory;//!< Directory used to store images.
    std::string m_strCDLDirectory;      //!< Directory used to store cdl files.
    std::string m_strTempDirectory;     //!< Directory used to store temp files.
    std::string m_strRecycleDirectory;  //!< Directory used to store deleted files.
    std::string m_strProtocolDirectory; //!< Directory used to store protocols.
	std::string m_strConfigDirectory;	//!< Directory used to store hardware configurations.
	std::string m_strRIImageFile;		//!< Path of RI raw data for images.
	std::string m_strRIFidFile;			//!< Path of RI raw data for FID.

	CString m_sLocalDbPathName, m_sLocalDbPathNameForBackup, m_sDbPathNameInBackupDevice;
	
	//Add by Tom. 2005.4.2
    std::string m_strDefaultAETitle;    //!< Remote Default Node AE Title.
	std::string m_strDefaultNodeIP ;    //!< Remote Default Node IP.
	std::string m_strDefaultPort   ;    //!< Remote Default Port.
	std::string m_strLocalAETitle  ;    //!< Local Default Node AE Title.
	std::string m_strLocalNodeIP   ;    //!< Local Default Node IP.
	std::string m_strLocalPort     ;    //!< Local Default Port.
	//add chenshi
	CString m_szPrint_Path;
	CString m_szLocalCharator;
	//end chenshi

	SiteField	m_SiteField;		    //!< Struct used to store site info.
    COLORREF    m_clrBackgroundColor;   //!< Background color.
    COLORREF    m_clrTextColor;         //!< Text color.
	//Modified by Tom, 2005.2.27
	int         m_nHasAdFilter;         //!<If install CVIE filter. 
	HMODULE     m_hCvieDll ;
	HMODULE     m_hPushDll ;
	//////////////////////////////////////////////////////////////////////////
	//new PACS Module;add liwenzhe
	HMODULE     m_hPACSDLL ;

	int m_background_nR,m_background_nG,m_background_nB;
	int m_text_nR,m_text_nG,m_text_nB;

	// debug mode - 20051203
	bool		m_bDebugMode;

	//Added by Tom, --2008.07.10
	bool        m_bMaintainMode;

	CTGTuneRange  m_TGTuneRange;
	CPreEmphasisParams  m_PreEmpahsisParams;
	CTuneConfig m_TuneConfig;

	/** [GMWU 11/10/2007] 增加重建ZIP因子限制 **/
	int m_nDefaultReconZipFactor;
	/** [GMWU 11/10/2007] **/

    CSpecFromCoil m_CoilSpecs;
	int m_nModeOfIdentification; // Mode of automatic identification
	
	//! This is the single instance of this class.
	static CConfigManager s_ConfigManager;
	//! Protected constructor.
	CConfigManager();

    bool ParseLine(const std::string& strSource, std::string& strVariable, 
        std::string& strValue) const;
    bool AnalyzeLine(const std::string& strVariable, const std::string& strValue);
	bool AnalyzeIniLine(const std::string& strVariable, const std::string& strValue);
    bool AnalyzeSystemParams (const std::string& strVariable, 
		const std::string& strValue);

	
	int GetNearestBWIndex(double dBW) const;

	bool m_bEnableMrNoItem;
	void ReadPatientInfoItemFlag();

	short m_nAnnotationCodingDirType;
	void ReadAnnotationCodingDirType();
	
	// Tuning的方法选择
public:
	unsigned char m_nMethodOfCoilTuning;	// 从xbmri.ini中读取，默认为0。0--RF Tuning; 1--FID Tuning
	unsigned char ReadMethodIdOfCoilTuningFromCfgFile();
	
public:
	void ReadConfigInfoFromFile();
	
	/** [zhlxu 2008.5.5] [] 添加TR限制值的文件配置功能 **/
public:
	float m_fTRLimitedValue;
	void GetTRLimitedValueFromFile();
	/** [zhlxu 2008.5.5] **/
};

// -----------------------------------------------------------------------------------------------------------
/*
【语言字符资源】公共接口类
*/

class  AFX_EXT_CLASS CLang
{
public:
	CLang();
	virtual ~CLang();
	
public:
	static CLang s_oHandle;
	static CLang& GetHandle();
	
private:
	char m_sLangIniFile[255];
	CMapStringToString m_mapCharRes;
	CFont m_oFont;
	
private:
	// 从文件中读取软件所需的字符资源
	void ReadCharResourceFromFile();
	// 从Lang.ini文件中读取字体配置
	void ReadFontConfigFromLangIniFile( LOGFONT& oLogFont );
	// 创建字体
	void CreateFont();
	
public:
	CString GetInstallDirectory();
	// 从内存中获取某个关键字的字符资源
	CString GetCharRes( CString sKey );
	// 根据m_oFont的设置，改变窗体的字体
	void ChangeWndFont(CWnd* pWnd);
	// 获取统一的字体对象
	CFont* GetFont();
	// 获取字符资源的指针(用于通用平台)
	CMapStringToString* GetCharResPointer();
	// 显示提示信息
	// nType的取值为其中任意一个: MB_YESNO, MB_OKCANCEL, MB_OK
	int ShowMessage( CString sMsg, UINT nType = MB_OK );
	
};

// -----------------------------------------------------------------------------------------------------------
/*
【故障诊断日志】文件存取公共类
*/
#include "LogCommonDefine.h"
#include "..\\LogServer\\CommonDefine.h"

class AFX_EXT_CLASS CLogFileAccess  
{
public:
	CLogFileAccess();
	virtual ~CLogFileAccess();

public:
	static CLogFileAccess s_oHandle;
	static CLogFileAccess& GetHandle();
	
private:
	CString m_sPathOfLogFile, m_sNameOfLogFile, m_sNameOfLogTextFile;
	
	FILE *m_pFile;
	bool OpenLogFileName();

	tm*		m_pTime;
	time_t  GetCurrTime();
	CString MakeDateTimeStr( time_t nDateTime );

private:
	// Binary file
	void SaveToFile( STRUCT_RECORD_DIAGNOSIS_TG_RG_O1 oTG_RG_O1 );
	void SaveToFile( STRUCT_RECORD_DIAGNOSIS_TUNING_MEAN oTuningMean );
	
	// 外部调用
public:
	void SaveToFile( std::vector<STRUCT_RECORD_DIAGNOSIS_TG_RG_O1>* pvTG_RG_O1 );
	void SaveToFile( std::vector<STRUCT_RECORD_DIAGNOSIS_TUNING_MEAN>* pvTuningMean );

	bool ReadFromFile( BIDateTime oSeriesTime, CString sStudyID, int nSeriesID,
		std::vector<STRUCT_RECORD_DIAGNOSIS_TG_RG_O1>* pvTG_RG_O1 /*包括多通道的RG*/,
		std::vector<STRUCT_RECORD_DIAGNOSIS_TUNING_MEAN>* pvTuningMean /*包括I、Q通道*/);

};

/** [zhlxu 2007.11.9] 添加内存检测函数 **/
AFX_EXT_CLASS bool CheckMemory();
/** [zhlxu 2007.11.9] **/

#endif // !defined(AFX_CONFIGMANAGER_H__F6D52C2B_BD9B_4EB8_AAC3_647AD9D49E25__INCLUDED_)
