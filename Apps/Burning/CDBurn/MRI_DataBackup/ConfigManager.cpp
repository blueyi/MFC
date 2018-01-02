// ConfigManager.cpp
//

#include "stdafx.h"
#include "ConfigManager.h"
// #include "inifile.h"
// #include "Crypt.h"
// #include "Log.h"
// 
// 
// #pragma warning (disable:4786)
// #include <fstream>
// #include <sstream>
// #include <iomanip>
// 
// #include <math.h>
// 
// 
// #ifdef _DEBUG
// #define new DEBUG_NEW
// #undef THIS_FILE
// static char THIS_FILE[] = __FILE__;
// #endif
// 
// 
// AFX_EXT_CLASS CConfigManager CConfigManager::s_ConfigManager;
// 
// #define FLOAT_ZERO 1.0e-6
// 
// 
// CSystemParams::CSystemParams()
// {
// 	m_dGxFF       = 0.1274;
// 	m_dGyFF       = 0.1286;
// 	m_dGzFF       = 0.1048;
// 	m_nGxRampRate = 6000;
// 	m_nGyRampRate = 6000;
// 	m_nGzRampRate = 6000;
// 	m_nGateTime   = 30;
// 	m_nGxRFDelay  = 240;
// 	m_nGyRFDelay  = 268;
// 	m_nGzRFDelay  = 194;
// 	m_dFactorGx   = 1.0016;
// 	m_dFactorGy   = 1.006;
// 	m_dFactorGz   = 1.0078;
// }
// 
// 
// CFilmingConfig::CFilmingConfig()
// {
// 	m_strFilmSize          = _T("14INX17IN ");
// 	m_strLayout            = _T("PORTRAIT");
// 	m_strImageName         = _T("PRINTER ");
// 	m_strFilmRelease       = _T("AUTO");
// 	m_strLookupTable       = _T("KC_LUT=1");
// 	m_strMediaType         = _T("BLUE FILM ");
// 	m_strProcessor         = _T("PROCESSOR ");
// 	m_strEmptyImageDensity = _T("DICOM_PRINTPRIORITY_MED");
// 	m_strPrinterAE         = _T("DV8150");
// 	m_strLocalAE           = _T("CALLING_AE");
// 	m_strIP                = _T("172.10.0.3");
// 	m_iMax                 = 300;
// 	m_iMin                 = 0;
// 	m_strBorder            = _T("BLACK ");
// 	m_strTrim              = _T("NO");
// 	m_strPort              = _T("104");
// 	m_nImageSize           = 512;
// 	//初始化打印机类型;
//     m_nPrintType		   = 0;
// }
// 
// CTGTuneRange::CTGTuneRange()
// {  
// 	m_nStartVal    = 10;
// 	m_fStep        = 2.;
// 	m_nNumOfSteps  = 3; 
// 	m_fRange       = 3;
// }
// 
// //////////////////////////////////////////////////////////////////////
// // Construction/Destruction
// //////////////////////////////////////////////////////////////////////
// 
// /*!
//     \bug Machine ID and Series Number is hardcoded together with some other 
//     parameters.
// */
// BOOL CConfigManager::GetDirInfoFromRegistry()
// {
// 	HKEY hKey;
// 
// 	long lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\XinAoMDT\\Prospect", 0, KEY_READ, &hKey);
// 	if(lResult != ERROR_SUCCESS)
// 	{
// 		return FALSE;
// 	}
// 
// 	char szDir[MAX_PATH];
// 	DWORD dwSize = MAX_PATH;
// 	lResult = RegQueryValueEx( hKey, "InstallDir", NULL, NULL, (BYTE*) szDir, &dwSize);
// 	if(lResult != ERROR_SUCCESS)
// 	{
// 		return FALSE;
// 	}
// 
// 	m_strHomePath = szDir;
// 	m_strHomePath += "\\";
// 
// 	dwSize = MAX_PATH;
// 	lResult = RegQueryValueEx( hKey, "ImgDBDir", NULL, NULL, (BYTE*) szDir, &dwSize);
// 	m_strImageRootDirectory = szDir;
// 	m_strImageRootDirectory += "\\";
// 
// 	RegCloseKey(hKey);
// 
// 	return lResult == ERROR_SUCCESS;
// }
// 
// //////////////////////////////////////////////////////////////////////////
// //配置管理文件信息
// CConfigManager::CConfigManager()
// {	
// 	if( ! GetDirInfoFromRegistry())
// 	{
// 		CLang::GetHandle().ShowMessage( CLang::GetHandle().GetCharRes("MSG___PROSPECT_NOT_INSTALLED") );
// 		::PostQuitMessage(-1);
// //		m_strImageRootDirectory = _T("\\BIIMAGES\\");
// //		ASSERT(0); 
// 		return;
// 	}
// 
//     m_bSysTimeout        = false ;
// 	m_strFilterPath      = m_strHomePath + _T("filters\\");
//     m_strConfigFile      = m_strHomePath + _T("bin\\xbmri.cfg");
// 	m_strConfigIniFile   = m_strHomePath + _T("bin\\xbmri.ini");
// 	m_strConfigDirectory = m_strHomePath + _T("Config\\");
// 
// 	m_nFilterNum = LoadFilterPara();
// 
// 	m_bTest                = false ; //Set user state.
// 
//     m_clrTextColor         = RGB(0, 0, 0);
//     m_clrBackgroundColor   = RGB(229, 219, 204);
//     m_strInstallDirectory  = m_strHomePath + _T("bin\\");
//     m_strProtocolDirectory = m_strHomePath + _T("protocols\\");
//     m_strTempDirectory     = m_strHomePath + _T("temp\\");
//     m_strCDLDirectory      = m_strHomePath + _T("pulse_sequences\\");    
//     m_strRecycleDirectory  = _T("\\bi_recycle_bin\\");
// 	m_strRIImageFile       = _T("C:/Program Files/Resonance/Rinmr/Temp/Image.Last");
// 	m_strRIFidFile         = _T("C:/Program Files/Resonance/Rinmr/Temp/LastDat.Last");
// 
//     strcpy(m_SiteField.BISerialNum, _T("CENTAURI03000"));
//     m_SiteField.GradientStrengthX = 0;
//     m_SiteField.GradientStrengthY = 0;
//     m_SiteField.GradientStrengthZ = 0;
//     strcpy(m_SiteField.Id, _T("CENTAURI03"));
//     strcpy(m_SiteField.InstDeptName, _T("RD"));
//     strcpy(m_SiteField.InstName, _T("XinAoMDT MRI LAB"));
// 	strcpy(m_SiteField.StationName, _T("Station 1"));
// 	m_SiteField.SF = 12.68f;					//Lei Zhao, Changed from 12.63f to 12.65f, 2004.07.09
// 												//Lei Zhao, Changed from 12.65f to 12.67f, 2004.10.25 (temp is too low 18deg)
// 												//Lei Zhao, Changed from 12.63f to 12.65f, 2004.11.15 (temp is higher to 22deg)
// 
// 	m_SiteField.LastCalib.day    = 8;
// 	m_SiteField.LastCalib.month  = 5;
// 	m_SiteField.LastCalib.year   = 2005;
// 	m_SiteField.LastCalib.hour   = 12;
// 	m_SiteField.LastCalib.minute = 0;
// 	m_SiteField.LastCalib.second = 0;
// 
// 	m_DefaultShimCoil = ctHeadCoilQD;         //added by Tom, 2005.5.8//20070213.liuxuan.for shimming.7??
// 	// initialize the maximum RFA values.
// 	m_CoilSpecs[ctSystemCoil].m_dRFAMax        = 10.0f;
// 	m_CoilSpecs[ctHeadSolonoid].m_dRFAMax      = 28.0f;
//     m_CoilSpecs[ctBodySolonoidL].m_dRFAMax     = 10.0f;
//     m_CoilSpecs[ctBodySolonoidM].m_dRFAMax     = 10.0f;
//     m_CoilSpecs[ctBodySolonoidS].m_dRFAMax     = 10.0f;	
// 	m_CoilSpecs[ctNeckSolonoid].m_dRFAMax      = 10.0f;
// 	m_CoilSpecs[ctHeadQD].m_dRFAMax            = 28.0f;
// 	m_CoilSpecs[ctKneeQD].m_dRFAMax            = 28.0f;			
// 	m_CoilSpecs[ctBodyQDL].m_dRFAMax           = 42.0f; // 36.0f; 17:47 2004-8-11
// 	m_CoilSpecs[ctBodyQDM].m_dRFAMax           = 28.0f;
// 	m_CoilSpecs[ctBodyQDS].m_dRFAMax           = 28.0f;
//     m_CoilSpecs[ctSurfaceNeck].m_dRFAMax       = 10.0f;
//     m_CoilSpecs[ctSurfaceElbow].m_dRFAMax      = 10.0f;
//     m_CoilSpecs[ctSurfaceShoulder].m_dRFAMax   = 10.0f;
//     m_CoilSpecs[ctPhaseArraySpine].m_dRFAMax   = 10.0f;
//     m_CoilSpecs[ctPhaseArrayCardiac].m_dRFAMax = 10.0f;
// 
// 	m_CoilSpecs[ctSystemCoil].m_dDefaultTG     = 0.0f;
// 	m_CoilSpecs[ctHeadSolonoid].m_dDefaultTG   = 3.3f;
//     m_CoilSpecs[ctBodySolonoidL].m_dDefaultTG  = 0.0f;
//     m_CoilSpecs[ctBodySolonoidM].m_dDefaultTG  = 0.0f;
//     m_CoilSpecs[ctBodySolonoidS].m_dDefaultTG  = 0.0f;	
// 	m_CoilSpecs[ctNeckSolonoid].m_dDefaultTG   = 0.0f;
// 	m_CoilSpecs[ctHeadQD].m_dDefaultTG         = 3.3f;
// 	m_CoilSpecs[ctKneeQD].m_dDefaultTG         = 2.7f;			
// 	m_CoilSpecs[ctBodyQDL].m_dDefaultTG        = 10.0; // 12.0f;
// 	m_CoilSpecs[ctBodyQDM].m_dDefaultTG        = 0.0f;
// 	m_CoilSpecs[ctBodyQDS].m_dDefaultTG        = 0.0f;
//     m_CoilSpecs[ctSurfaceNeck].m_dDefaultTG    = 2.7f;
//     m_CoilSpecs[ctSurfaceElbow].m_dDefaultTG   = 0.0f;
//     m_CoilSpecs[ctSurfaceShoulder].m_dDefaultTG = 0.0f;
//     m_CoilSpecs[ctPhaseArraySpine].m_dDefaultTG = 0.0f;
//     m_CoilSpecs[ctPhaseArrayCardiac].m_dDefaultTG = 0.0f;
// 
// 
// 	// 3rd party RF coils
// 	const float cnstRFAMax		= 80.0f;
// 	const float cnstRFDefault	= 19.6f;
// 
// 	m_CoilSpecs[ctHeadRecv].m_dRFAMax				= cnstRFAMax;
// 	m_CoilSpecs[ctHeadRecv].m_dDefaultTG			= cnstRFDefault;
// 	m_CoilSpecs[ctHeadRecv].m_nTuneVoltage			= 0;
// 	m_CoilSpecs[ctHeadRecv].m_nMatchVoltage			= 0;
// 
// 	m_CoilSpecs[ctBodyRecvMid].m_dRFAMax			= cnstRFAMax;
// 	m_CoilSpecs[ctBodyRecvMid].m_dDefaultTG			= cnstRFDefault;
// 	m_CoilSpecs[ctBodyRecvMid].m_nTuneVoltage		= 0;
// 	m_CoilSpecs[ctBodyRecvMid].m_nMatchVoltage		= 0;
// 
// 	m_CoilSpecs[ctBodyRecvSmall].m_dRFAMax			= cnstRFAMax;
// 	m_CoilSpecs[ctBodyRecvSmall].m_dDefaultTG		= cnstRFDefault;
// 	m_CoilSpecs[ctBodyRecvSmall].m_nTuneVoltage		= 0;
// 	m_CoilSpecs[ctBodyRecvSmall].m_nMatchVoltage	= 0;
// 
// 	m_CoilSpecs[ctNeckRecv].m_dRFAMax				= cnstRFAMax;
// 	m_CoilSpecs[ctNeckRecv].m_dDefaultTG			= cnstRFDefault;
// 	m_CoilSpecs[ctNeckRecv].m_nTuneVoltage			= 0;
// 	m_CoilSpecs[ctNeckRecv].m_nMatchVoltage			= 0;
// 
// 	m_CoilSpecs[ctKneeRecv].m_dRFAMax				= cnstRFAMax;
// 	m_CoilSpecs[ctKneeRecv].m_dDefaultTG			= cnstRFDefault;
// 	m_CoilSpecs[ctKneeRecv].m_nTuneVoltage			= 0;
// 	m_CoilSpecs[ctKneeRecv].m_nMatchVoltage			= 0;
// 
// 	m_mutexRewriteTime = ::CreateMutex(NULL, false, NULL);
// 
// 	m_bEnableMrNoItem = true;
// 	ReadPatientInfoItemFlag();	
// 
// 	m_nAnnotationCodingDirType = true;
// 	ReadAnnotationCodingDirType();	
// 	
// 	m_nMethodOfCoilTuning = ReadMethodIdOfCoilTuningFromCfgFile();
// 
// 	/** [GMWU 11/10/2007] 缺省重建ZIP因子为0 **/
// 	m_nDefaultReconZipFactor = 0;
// 	/** [GMWU 11/10/2007] **/
// 	/*********zyh add 2008.2.27*********/
// 	m_bHasDACard = TRUE;
// 	/***********************************/
// 	/** [zhlxu 2008.2.2] [] 解决PACS的DCM文件临时目录不存在的问题 **/
// 	CString csDicomPath;
//     csDicomPath.Format("%sdicom\\" , m_strHomePath);
// 	BOOL nRes=CreateDirectory(csDicomPath,NULL);
// 	/** [zhlxu 2008.2.2] **/
// 
// 	GetTRLimitedValueFromFile();
// }
// 
// CConfigManager::~CConfigManager()
// {
// 
// }
// 
// /*!
// 	\bug What if the coil id isn't found?
// */
// CCoilSpec CConfigManager::GetCoilSpec(ECoilType coil)
// {
// 	return m_CoilSpecs[coil];
// }
// 
// LPCSTR CConfigManager::GetFilterPath() const
// {
// 	return m_strFilterPath;
// }
// 
// 
// const std::string& CConfigManager::GetImageRootDirectory() const
// {
// 	return m_strImageRootDirectory;
// }
// 
// void CConfigManager::SetImageRootDirectory(const std::string& strImageRootDirectory)
// {
// 	m_strImageRootDirectory = strImageRootDirectory;
// }
// 
// const std::string& CConfigManager::GetCDLDirectory() const
// {
//     return m_strCDLDirectory;
// }
// 
// const std::string& CConfigManager::GetConfigDirectory() const
// {
// 	return m_strConfigDirectory;
// }
// 
// const std::string& CConfigManager::GetTempDirectory() const
// {
//     return m_strTempDirectory;
// }
// 
// /*!
// 	\return The root directory used to store protocols.
// */
// const std::string& CConfigManager::GetProtocolDirectory() const
// {
//     return m_strProtocolDirectory;
// }
// 
// /*!
// 	\return Default background color in the user interface.
// */
// COLORREF CConfigManager::GetBackgroundColor() const
// {
//     return m_clrBackgroundColor;
// }
// 
// /*!
// 	\return Default text color used in the user interface.
// */
// COLORREF CConfigManager::GetTextColor() const
// {
//     return m_clrTextColor;
// }
// 
// /*!
//     \bug The file should be changed to XML format or something. Or maybe we
//     should save the configuration information to the registry or database?
// */
// bool CConfigManager::Save() const
// {
//     std::ofstream of(m_strConfigFile.c_str());
// 
//     if (!of)
//         return false;
// 
//     // site information
//     of << "site_id = " << m_SiteField.Id << std::endl
//         << "institution_name = " << m_SiteField.InstName << std::endl
//         << "department_name = "  << m_SiteField.InstDeptName << std::endl
//         << "station_name = " << m_SiteField.StationName << std::endl
//         << "series_number = " << m_SiteField.BISerialNum  << std::endl;
// 
//     of << "last_calibration = " 
// 		<< m_SiteField.LastCalib.year << "-"
// 		<< int (m_SiteField.LastCalib.month) << "-" 
// 		<< int (m_SiteField.LastCalib.day) << " "
// 		<< int (m_SiteField.LastCalib.hour) << ":" 
// 		<< std::setfill('0') << std::setw(2) 
// 		<< int (m_SiteField.LastCalib.minute) << ":"
// 		<< std::setfill('0') << std::setw(2) 
// 		<< int (m_SiteField.LastCalib.second) 
// 		<< std::endl;
// 	
//     of  << "calibrated_magnet_strength = " << m_SiteField.MagCalibStrength << std::endl
//         << "gradient_strength_x = " << m_SiteField.GradientStrengthX << std::endl
//         << "gradient_strength_y = " << m_SiteField.GradientStrengthY << std::endl
//         << "gradient_strength_z = " << m_SiteField.GradientStrengthZ << std::endl;
// 
// 	of << "center_frequency = " << m_SiteField.SF << std::endl;
// 
//     // directories
//     of << "install_dir = " << m_strInstallDirectory << std::endl;
//     of << "image_dir = " << m_strImageRootDirectory << std::endl;
//     of << "pulse_sequence_dir = " << m_strCDLDirectory << std::endl;
//     of << "temp_dir = " << m_strTempDirectory << std::endl;
//     of << "recycle_dir = " << m_strRecycleDirectory << std::endl;
// 	of << "config_dir = " << m_strConfigDirectory << std::endl;
//     of << "protocol_dir = " << m_strProtocolDirectory << std::endl;
// 	of << "ri_image_file = " << m_strRIImageFile << std::endl;
// 	of << "ri_fid_file = " << m_strRIFidFile << std::endl;
//         
//     // user interface preference
//     of << "background_color = " << int(GetRValue(m_clrBackgroundColor)) << " "
// 		<< int(GetGValue(m_clrBackgroundColor)) << " "
// 		<< int(GetBValue(m_clrBackgroundColor)) << std::endl;
// 
//     of << "text_color = " << int(GetRValue(m_clrTextColor)) << " "
// 		<< int(GetGValue(m_clrTextColor)) << " "
// 		<< int(GetBValue(m_clrTextColor)) << std::endl;
// 
// 	//Modified by Tom, 2005.2.27
// //	of << "hasAdFilter = " << m_nHasAdFilter << " "<< std::endl;
// 
// 	// filming
// 	std::string strIP = m_FilmingConfig.m_strIP;
// 	of << "filming_PrinterIP = " << strIP << std::endl;
// 	of << "filming_ImageSize = " << m_FilmingConfig.m_nImageSize << std::endl;
// 	of << "filming_PrinterAE = " << m_FilmingConfig.m_strPrinterAE << std::endl;
// 	of << "filming_PrinterPort = " << m_FilmingConfig.m_strPort << std::endl;
// 
//    
//     return true;
// }
// 
// bool CConfigManager::SaveIni() 
// {
// 	CIniFile inifile;
// 	CString strConfigDirectorySection("SYSTEM_BIMRI_CONFIG_DIRECTORY");
// 	CString strConfigCoilSection("SYSTEM_BIMRI_CONFIG_COIL");
// 	bool bConfigIniFile = true;
// 	if (!inifile.SetPath(m_strConfigIniFile.c_str())) {
// 		bConfigIniFile = false;
// 	}
// 	
// 	inifile.SetKeyValue(strConfigDirectorySection, "site_id" ,(m_SiteField.Id));
//     inifile.SetKeyValue(strConfigDirectorySection, "institution_name" ,( m_SiteField.InstName ));
//     inifile.SetKeyValue(strConfigDirectorySection, "department_name"  ,( m_SiteField.InstDeptName ));
//     inifile.SetKeyValue(strConfigDirectorySection,  "station_name" ,(m_SiteField.StationName ));
//     inifile.SetKeyValue(strConfigDirectorySection,  "series_number" ,( m_SiteField.BISerialNum  ));
// 
// 	inifile.SetKeyValue(strConfigDirectorySection, "last_calibration_year" , dataTypetoString(m_SiteField.LastCalib.year ));
// 	inifile.SetKeyValue(strConfigDirectorySection, "last_calibration_month" , dataTypetoString(int (m_SiteField.LastCalib.month) ));
// 	inifile.SetKeyValue(strConfigDirectorySection, "last_calibration_day" , dataTypetoString(int (m_SiteField.LastCalib.day) ));
// 	inifile.SetKeyValue(strConfigDirectorySection, "last_calibration_hour" ,dataTypetoString( int (m_SiteField.LastCalib.hour) ));
// //		inifile.SetKeyValue(strConfigDirectorySection, "last_calibration_year = " , std::setfill('0') << std::setw(2) 
// 	inifile.SetKeyValue(strConfigDirectorySection, "last_calibration_minute" , dataTypetoString(int (m_SiteField.LastCalib.minute) ));
// //		inifile.SetKeyValue(strConfigDirectorySection, "last_calibration_year = " , std::setfill('0') << std::setw(2) 
// 	inifile.SetKeyValue(strConfigDirectorySection, "last_calibration_second" , dataTypetoString(int (m_SiteField.LastCalib.second) ));
// 
// 	inifile.SetKeyValue(strConfigDirectorySection,  "calibrated_magnet_strength" ,dataTypetoString(m_SiteField.MagCalibStrength)) ;
//     inifile.SetKeyValue(strConfigDirectorySection, "gradient_strength_x" ,dataTypetoString( m_SiteField.GradientStrengthX ));
//     inifile.SetKeyValue(strConfigDirectorySection,  "gradient_strength_y" ,dataTypetoString( m_SiteField.GradientStrengthY ));
//     inifile.SetKeyValue(strConfigDirectorySection,  "gradient_strength_z" ,dataTypetoString( m_SiteField.GradientStrengthZ ));
// 
// 	inifile.SetKeyValue(strConfigDirectorySection, "center_frequency" ,dataTypetoString( m_SiteField.SF ));
// 
//     // directories
//     inifile.SetKeyValue(strConfigDirectorySection, "install_dir" ,( m_strInstallDirectory.c_str() ));
//     inifile.SetKeyValue(strConfigDirectorySection, "image_dir" ,( m_strImageRootDirectory.c_str() ));
//     inifile.SetKeyValue(strConfigDirectorySection, "pulse_sequence_dir" ,( m_strCDLDirectory.c_str() ));
//     inifile.SetKeyValue(strConfigDirectorySection, "temp_dir" ,( m_strTempDirectory.c_str() ));
//     inifile.SetKeyValue(strConfigDirectorySection, "recycle_dir" ,( m_strRecycleDirectory.c_str() ));
// 	inifile.SetKeyValue(strConfigDirectorySection, "config_dir" ,( m_strConfigDirectory.c_str() ));
//     inifile.SetKeyValue(strConfigDirectorySection, "protocol_dir" ,( m_strProtocolDirectory.c_str() ));
// 	inifile.SetKeyValue(strConfigDirectorySection, "ri_image_file" ,( m_strRIImageFile.c_str() ));
// 	inifile.SetKeyValue(strConfigDirectorySection, "ri_fid_file" ,( m_strRIFidFile.c_str() ));
//         
//     // user interface preference
//     inifile.SetKeyValue(strConfigDirectorySection, "background_color_red" ,dataTypetoString( int(GetRValue(m_clrBackgroundColor))) );
// 	inifile.SetKeyValue(strConfigDirectorySection, "background_color_green" 	,dataTypetoString( int(GetGValue(m_clrBackgroundColor)))) ;
// 	inifile.SetKeyValue(strConfigDirectorySection, "background_color_blue" 	,dataTypetoString( int(GetBValue(m_clrBackgroundColor)) ));
// 
//     inifile.SetKeyValue(strConfigDirectorySection, "text_color_red" ,dataTypetoString( int(GetRValue(m_clrTextColor)) ));
// 	inifile.SetKeyValue(strConfigDirectorySection, "text_color_green" 	,dataTypetoString( int(GetGValue(m_clrTextColor))) );
// 	inifile.SetKeyValue(strConfigDirectorySection, "text_color_blue" 	,dataTypetoString( int(GetBValue(m_clrTextColor)) ));
// 
// 	
// //	inifile.SetKeyValue(strConfigDirectorySection, "hasAdFilter" ,dataTypetoString( m_nHasAdFilter));
// 
// 	// filming
// 	std::string strTmp;
// 	strTmp = m_FilmingConfig.m_strIP;
// 	inifile.SetKeyValue(strConfigDirectorySection, "filming_PrinterIP" , ( strTmp.c_str() ));
// 	inifile.SetKeyValue(strConfigDirectorySection, "filming_ImageSize" , dataTypetoString( m_FilmingConfig.m_nImageSize ));
// 
// 	// added for filming configuration - 20051007
// 	strTmp = m_FilmingConfig.m_strPrinterAE;
// 	inifile.SetKeyValue(strConfigDirectorySection, "filming_PrinterAE"  , strTmp.c_str());
// 	strTmp = m_FilmingConfig.m_strPort;
// 	inifile.SetKeyValue(strConfigDirectorySection, "filming_PrinterPort", strTmp.c_str());
// 	inifile.SetKeyValue(strConfigDirectorySection, "filming_PrinterType", dataTypetoString(m_FilmingConfig.m_nPrintType));
	// end - 20051007
/*
	char chartemp[8];
	sprintf(chartemp,"%f",m_CoilSpecs[ctSystemCoil].m_dRFAMax);

//		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctSystemCoil].m_dRFAMax",dataTypetoString(m_CoilSpecs[ctSystemCoil].m_dRFAMax));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctSystemCoil].m_dRFAMax",chartemp);
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctHeadSolonoid].m_dRFAMax",dataTypetoString(m_CoilSpecs[ctHeadSolonoid].m_dRFAMax));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodySolonoidL].m_dRFAMax",dataTypetoString(m_CoilSpecs[ctBodySolonoidL].m_dRFAMax));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodySolonoidM].m_dRFAMax",dataTypetoString(m_CoilSpecs[ctBodySolonoidM].m_dRFAMax));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodySolonoidS].m_dRFAMax",dataTypetoString(m_CoilSpecs[ctBodySolonoidS].m_dRFAMax));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctNeckSolonoid].m_dRFAMax",dataTypetoString(m_CoilSpecs[ctNeckSolonoid].m_dRFAMax));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctHeadQD].m_dRFAMax",dataTypetoString(m_CoilSpecs[ctHeadQD].m_dRFAMax));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctKneeQD].m_dRFAMax",dataTypetoString(m_CoilSpecs[ctKneeQD].m_dRFAMax));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodyQDL].m_dRFAMax",dataTypetoString(m_CoilSpecs[ctBodyQDL].m_dRFAMax));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodyQDM].m_dRFAMax",dataTypetoString(m_CoilSpecs[ctBodyQDM].m_dRFAMax));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodyQDS].m_dRFAMax",dataTypetoString(m_CoilSpecs[ctBodyQDS].m_dRFAMax));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctSurfaceNeck].m_dRFAMax",dataTypetoString(m_CoilSpecs[ctSurfaceNeck].m_dRFAMax));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctSurfaceElbow].m_dRFAMax",dataTypetoString(m_CoilSpecs[ctSurfaceElbow].m_dRFAMax));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctSurfaceShoulder].m_dRFAMax",dataTypetoString(m_CoilSpecs[ctSurfaceShoulder].m_dRFAMax));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctPhaseArraySpine].m_dRFAMax",dataTypetoString(m_CoilSpecs[ctPhaseArraySpine].m_dRFAMax));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctPhaseArrayCardiac].m_dRFAMax",dataTypetoString(m_CoilSpecs[ctPhaseArrayCardiac].m_dRFAMax));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctSystemCoil].m_dDefaultTG",dataTypetoString(m_CoilSpecs[ctSystemCoil].m_dDefaultTG));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctHeadSolonoid].m_dDefaultTG",dataTypetoString(m_CoilSpecs[ctHeadSolonoid].m_dDefaultTG));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodySolonoidL].m_dDefaultTG",dataTypetoString(m_CoilSpecs[ctBodySolonoidL].m_dDefaultTG));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodySolonoidM].m_dDefaultTG",dataTypetoString(m_CoilSpecs[ctBodySolonoidM].m_dDefaultTG));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodySolonoidS].m_dDefaultTG",dataTypetoString(m_CoilSpecs[ctBodySolonoidS].m_dDefaultTG));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctNeckSolonoid].m_dDefaultTG",dataTypetoString(m_CoilSpecs[ctNeckSolonoid].m_dDefaultTG));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctHeadQD].m_dDefaultTG",dataTypetoString(m_CoilSpecs[ctHeadQD].m_dDefaultTG));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctKneeQD].m_dDefaultTG",dataTypetoString(m_CoilSpecs[ctKneeQD].m_dDefaultTG));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodyQDL].m_dDefaultTG",dataTypetoString(m_CoilSpecs[ctBodyQDL].m_dDefaultTG));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodyQDM].m_dDefaultTG",dataTypetoString(m_CoilSpecs[ctBodyQDM].m_dDefaultTG));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodyQDS].m_dDefaultTG",dataTypetoString(m_CoilSpecs[ctBodyQDS].m_dDefaultTG));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctSurfaceNeck].m_dDefaultTG",dataTypetoString(m_CoilSpecs[ctSurfaceNeck].m_dDefaultTG));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctSurfaceElbow].m_dDefaultTG",dataTypetoString(m_CoilSpecs[ctSurfaceElbow].m_dDefaultTG));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctSurfaceShoulder].m_dDefaultTG",dataTypetoString(m_CoilSpecs[ctSurfaceShoulder].m_dDefaultTG));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctPhaseArraySpine].m_dDefaultTG",dataTypetoString(m_CoilSpecs[ctPhaseArraySpine].m_dDefaultTG));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctPhaseArrayCardiac].m_dDefaultTG",dataTypetoString(m_CoilSpecs[ctPhaseArrayCardiac].m_dDefaultTG));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctHeadRecv].m_dRFAMax",dataTypetoString(m_CoilSpecs[ctHeadRecv].m_dRFAMax));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctHeadRecv].m_dDefaultTG",dataTypetoString(m_CoilSpecs[ctHeadRecv].m_dDefaultTG));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctHeadRecv].m_nTuneVoltage",dataTypetoString(m_CoilSpecs[ctHeadRecv].m_nTuneVoltage));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctHeadRecv].m_nMatchVoltage",dataTypetoString(m_CoilSpecs[ctHeadRecv].m_nMatchVoltage));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodyRecvMid].m_dRFAMax",dataTypetoString(m_CoilSpecs[ctBodyRecvMid].m_dRFAMax));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodyRecvMid].m_dDefaultTG",dataTypetoString(m_CoilSpecs[ctBodyRecvMid].m_dDefaultTG));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodyRecvMid].m_nTuneVoltage",dataTypetoString(m_CoilSpecs[ctBodyRecvMid].m_nTuneVoltage));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodyRecvMid].m_nMatchVoltage",dataTypetoString(m_CoilSpecs[ctBodyRecvMid].m_nMatchVoltage));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodyRecvSmall].m_dRFAMax",dataTypetoString(m_CoilSpecs[ctBodyRecvSmall].m_dRFAMax));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodyRecvSmall].m_dDefaultTG",dataTypetoString(m_CoilSpecs[ctBodyRecvSmall].m_dDefaultTG));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodyRecvSmall].m_nTuneVoltage",dataTypetoString(m_CoilSpecs[ctBodyRecvSmall].m_nTuneVoltage));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodyRecvSmall].m_nMatchVoltage",dataTypetoString(m_CoilSpecs[ctBodyRecvSmall].m_nMatchVoltage));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctNeckRecv].m_dRFAMax",dataTypetoString(m_CoilSpecs[ctNeckRecv].m_dRFAMax));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctNeckRecv].m_dDefaultTG",dataTypetoString(m_CoilSpecs[ctNeckRecv].m_dDefaultTG));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctNeckRecv].m_nTuneVoltage",dataTypetoString(m_CoilSpecs[ctNeckRecv].m_nTuneVoltage));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctNeckRecv].m_nMatchVoltage",dataTypetoString(m_CoilSpecs[ctNeckRecv].m_nMatchVoltage));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctKneeRecv].m_dRFAMax",dataTypetoString(m_CoilSpecs[ctKneeRecv].m_dRFAMax));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctKneeRecv].m_dDefaultTG",dataTypetoString(m_CoilSpecs[ctKneeRecv].m_dDefaultTG));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctKneeRecv].m_nTuneVoltage",dataTypetoString(m_CoilSpecs[ctKneeRecv].m_nTuneVoltage));
		inifile.SetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctKneeRecv].m_nMatchVoltage",dataTypetoString(m_CoilSpecs[ctKneeRecv].m_nMatchVoltage));
*/		
//	return true;
/*	// initialize the maximum RFA values.
	m_CoilSpecs[ctSystemCoil].m_dRFAMax        = 10.0f;
	m_CoilSpecs[ctHeadSolonoid].m_dRFAMax      = 28.0f;
    m_CoilSpecs[ctBodySolonoidL].m_dRFAMax     = 10.0f;
    m_CoilSpecs[ctBodySolonoidM].m_dRFAMax     = 10.0f;
    m_CoilSpecs[ctBodySolonoidS].m_dRFAMax     = 10.0f;	
	m_CoilSpecs[ctNeckSolonoid].m_dRFAMax      = 10.0f;
	m_CoilSpecs[ctHeadQD].m_dRFAMax            = 28.0f;
	m_CoilSpecs[ctKneeQD].m_dRFAMax            = 28.0f;			
	m_CoilSpecs[ctBodyQDL].m_dRFAMax           = 42.0f; // 36.0f; 17:47 2004-8-11
	m_CoilSpecs[ctBodyQDM].m_dRFAMax           = 28.0f;
	m_CoilSpecs[ctBodyQDS].m_dRFAMax           = 28.0f;
    m_CoilSpecs[ctSurfaceNeck].m_dRFAMax       = 10.0f;
    m_CoilSpecs[ctSurfaceElbow].m_dRFAMax      = 10.0f;
    m_CoilSpecs[ctSurfaceShoulder].m_dRFAMax   = 10.0f;
    m_CoilSpecs[ctPhaseArraySpine].m_dRFAMax   = 10.0f;
    m_CoilSpecs[ctPhaseArrayCardiac].m_dRFAMax = 10.0f;
	m_CoilSpecs[ctSystemCoil].m_dDefaultTG     = 0.0f;
	m_CoilSpecs[ctHeadSolonoid].m_dDefaultTG   = 3.3f;
    m_CoilSpecs[ctBodySolonoidL].m_dDefaultTG  = 0.0f;
    m_CoilSpecs[ctBodySolonoidM].m_dDefaultTG  = 0.0f;
    m_CoilSpecs[ctBodySolonoidS].m_dDefaultTG  = 0.0f;	
	m_CoilSpecs[ctNeckSolonoid].m_dDefaultTG   = 0.0f;
	m_CoilSpecs[ctHeadQD].m_dDefaultTG         = 3.3f;
	m_CoilSpecs[ctKneeQD].m_dDefaultTG         = 2.7f;			
	m_CoilSpecs[ctBodyQDL].m_dDefaultTG        = 10.0; // 12.0f;
	m_CoilSpecs[ctBodyQDM].m_dDefaultTG        = 0.0f;
	m_CoilSpecs[ctBodyQDS].m_dDefaultTG        = 0.0f;
    m_CoilSpecs[ctSurfaceNeck].m_dDefaultTG    = 2.7f;
    m_CoilSpecs[ctSurfaceElbow].m_dDefaultTG   = 0.0f;
    m_CoilSpecs[ctSurfaceShoulder].m_dDefaultTG = 0.0f;
    m_CoilSpecs[ctPhaseArraySpine].m_dDefaultTG = 0.0f;
    m_CoilSpecs[ctPhaseArrayCardiac].m_dDefaultTG	= 0.0f;
	m_CoilSpecs[ctHeadRecv].m_dRFAMax				= 60.0;
	m_CoilSpecs[ctHeadRecv].m_dDefaultTG			= 12.8;
	m_CoilSpecs[ctHeadRecv].m_nTuneVoltage			= 0;
	m_CoilSpecs[ctHeadRecv].m_nMatchVoltage			= 0;
	m_CoilSpecs[ctBodyRecvMid].m_dRFAMax			= 60.0;
	m_CoilSpecs[ctBodyRecvMid].m_dDefaultTG			= 12.8;
	m_CoilSpecs[ctBodyRecvMid].m_nTuneVoltage		= 0;
	m_CoilSpecs[ctBodyRecvMid].m_nMatchVoltage		= 0;
	m_CoilSpecs[ctBodyRecvSmall].m_dRFAMax			= 60.0;
	m_CoilSpecs[ctBodyRecvSmall].m_dDefaultTG		= 12.8;
	m_CoilSpecs[ctBodyRecvSmall].m_nTuneVoltage		= 0;
	m_CoilSpecs[ctBodyRecvSmall].m_nMatchVoltage	= 0;
	m_CoilSpecs[ctNeckRecv].m_dRFAMax				= 60.0;
	m_CoilSpecs[ctNeckRecv].m_dDefaultTG			= 12.8;
	m_CoilSpecs[ctNeckRecv].m_nTuneVoltage			= 0;
	m_CoilSpecs[ctNeckRecv].m_nMatchVoltage			= 0;
	m_CoilSpecs[ctKneeRecv].m_dRFAMax				= 60.0;
	m_CoilSpecs[ctKneeRecv].m_dDefaultTG			= 12.8;
	m_CoilSpecs[ctKneeRecv].m_nTuneVoltage			= 0;
	m_CoilSpecs[ctKneeRecv].m_nMatchVoltage			= 0;
*/
	
// 
// }
// 
// bool CConfigManager::LoadIni()
// {
// 	//Load Global parameters ,added by Tom, 2005.5.17
// 	char    cEntryVal[128] ; 
// 	DWORD   dwLen;
// 
// 	dwLen = GetPrivateProfileString("SYSTEM_BIMRI_CONFIG_DIRECTORY",
// 		                            "site_id", "CENTAURI03",cEntryVal, 
// 									128,m_strConfigIniFile.c_str());
// 	strcpy(m_SiteField.Id , cEntryVal);
// 
// 	dwLen = GetPrivateProfileString("SYSTEM_BIMRI_CONFIG_DIRECTORY",
// 		                            "institution_name", "XinaoMDT",cEntryVal, 
// 									128,m_strConfigIniFile.c_str());
//     strcpy(m_SiteField.InstName , cEntryVal);
// 
// 	dwLen = GetPrivateProfileString("SYSTEM_BIMRI_CONFIG_DIRECTORY",
// 		                            "department_name", "RD",cEntryVal, 
// 									128,m_strConfigIniFile.c_str());
//     strcpy(m_SiteField.InstDeptName , cEntryVal);
// 
// 	dwLen = GetPrivateProfileString("SYSTEM_BIMRI_CONFIG_DIRECTORY",
// 		                            "station_name", "Station01",cEntryVal, 
// 									128,m_strConfigIniFile.c_str());
//     strcpy(m_SiteField.StationName , cEntryVal);
// 
//     dwLen = GetPrivateProfileString("SYSTEM_BIMRI_CONFIG_DIRECTORY",
// 		                            "series_number", "CENTAURI03000",cEntryVal, 
// 									128,m_strConfigIniFile.c_str());
//     strcpy(m_SiteField.BISerialNum , cEntryVal);
// 
// 	dwLen = GetPrivateProfileString("SYSTEM_BIMRI_CONFIG_DIRECTORY",
// 		                            "last_calibration_year", "2005",cEntryVal, 
// 									128,m_strConfigIniFile.c_str());
// 	m_SiteField.LastCalib.year = atoi(cEntryVal);
// 
// 	dwLen = GetPrivateProfileString("SYSTEM_BIMRI_CONFIG_DIRECTORY",
// 		                            "last_calibration_month", "1",cEntryVal, 
// 									128,m_strConfigIniFile.c_str());
// 	m_SiteField.LastCalib.month = atoi(cEntryVal);
// 
// 	dwLen = GetPrivateProfileString("SYSTEM_BIMRI_CONFIG_DIRECTORY",
// 		                            "last_calibration_day", "1",cEntryVal, 
// 									128,m_strConfigIniFile.c_str());
// 	m_SiteField.LastCalib.day = atoi(cEntryVal);
// 
// 	dwLen = GetPrivateProfileString("SYSTEM_BIMRI_CONFIG_DIRECTORY",
// 		                            "last_calibration_hour", "12",cEntryVal, 
// 									128,m_strConfigIniFile.c_str());
// 	m_SiteField.LastCalib.hour = atoi(cEntryVal);
// 
// 	dwLen = GetPrivateProfileString("SYSTEM_BIMRI_CONFIG_DIRECTORY",
// 		                            "last_calibration_minute", "0",cEntryVal, 
// 									128,m_strConfigIniFile.c_str());
// 	m_SiteField.LastCalib.minute = atoi(cEntryVal);
// 
// 	dwLen = GetPrivateProfileString("SYSTEM_BIMRI_CONFIG_DIRECTORY",
// 		                            "last_calibration_second", "0",cEntryVal, 
// 									128,m_strConfigIniFile.c_str());
// 	m_SiteField.LastCalib.second = atoi(cEntryVal);
// 
// 	dwLen = GetPrivateProfileString("SYSTEM_BIMRI_CONFIG_DIRECTORY",
// 		                            "calibrated_magnet_strength", "0.3",cEntryVal, 
// 									128,m_strConfigIniFile.c_str());
// 	m_SiteField.MagCalibStrength = atof(cEntryVal);
// 
// 	dwLen = GetPrivateProfileString("SYSTEM_BIMRI_CONFIG_DIRECTORY",
// 		                            "gradient_strength_x", "0.0001",cEntryVal, 
// 									128,m_strConfigIniFile.c_str());
// 	m_SiteField.GradientStrengthX = atof(cEntryVal);
// 
// 	dwLen = GetPrivateProfileString("SYSTEM_BIMRI_CONFIG_DIRECTORY",
// 		                            "gradient_strength_y", "0.0001",cEntryVal, 
// 									128,m_strConfigIniFile.c_str());
// 	m_SiteField.GradientStrengthY = atof(cEntryVal);
// 
// 	dwLen = GetPrivateProfileString("SYSTEM_BIMRI_CONFIG_DIRECTORY",
// 		                            "gradient_strength_z", "0.0001",cEntryVal, 
// 									128,m_strConfigIniFile.c_str());
// 	m_SiteField.GradientStrengthZ = atof(cEntryVal);
// 
//     dwLen = GetPrivateProfileString("SYSTEM_BIMRI_CONFIG_DIRECTORY",
// 		                            "center_frequency", "12.68",cEntryVal, 
// 									128,m_strConfigIniFile.c_str());
// 	m_SiteField.SF = atof(cEntryVal);
// 
// 	dwLen = GetPrivateProfileString("SYSTEM_BIMRI_CONFIG_DIRECTORY",
// 		                            "testsystem", "0",cEntryVal, 
// 									128,m_strConfigIniFile.c_str());
// 	m_bTest = (atoi(cEntryVal)>0)?true:false;
// 	//end of Tom add
// 
// 	// read debug mode - 20051203
// 	dwLen = GetPrivateProfileString("SYSTEM_BIMRI_CONFIG_DIRECTORY",
// 		                            "debug_mode", "0",cEntryVal, 
// 									128,m_strConfigIniFile.c_str());
// 	m_bDebugMode = (atoi(cEntryVal)>0)?true:false;
// 
// 	//Added by Tom, --2008.07.10
// 	dwLen = GetPrivateProfileString("SYSTEM_BIMRI_CONFIG_DIRECTORY",
// 		                            "maintain_mode", "0",cEntryVal, 
// 									128,m_strConfigIniFile.c_str());
// 	m_bMaintainMode = (atoi(cEntryVal)>0)?true:false;
// 	/*
// 	dwLen = GetPrivateProfileString("SYSTEM_BIMRI_CONFIG_DIRECTORY",
// 		                            "RcvCoilTune_mode", "0",cEntryVal, 
// 									128,m_strConfigIniFile.c_str());
// 	m_bRcvCoilTuneMode = (atoi(cEntryVal)>0)?true:false;
// 	*/
// 	dwLen = GetPrivateProfileString("SYSTEM_BIMRI_CONFIG_DIRECTORY",
// 		                            "ri_install_path", "",cEntryVal, 
// 									128,m_strConfigIniFile.c_str());
// 	if (dwLen < 10)
// 	{
// 	    m_strRiInstPath = "C:\\Program Files\\Resonance\\Rinmr\\";
// 	}
// 	else
// 	{
// 		m_strRiInstPath.Format("%s", cEntryVal);
// 	}
// 
// 	/** [GMWU 11/10/2007] 读取设置的重建ZIP因子值 **/
// 	dwLen = GetPrivateProfileString("RECON_OPTIONS",
// 		                            "DEFAULT_ZIPFACTOR", "0",cEntryVal, 
// 									128, m_strConfigIniFile.c_str());
// 	m_nDefaultReconZipFactor = atoi(cEntryVal);
// 	/** [GMWU 11/10/2007] **/
// 
// 	CStringArray strKey,strKeyValue;
// 	CIniFile inifile;
// 	CString strConfigDirectorySection("SYSTEM_BIMRI_CONFIG_DIRECTORY");
// 	CString strConfigCoilSection("SYSTEM_BIMRI_CONFIG_COIL");
// 	if (!inifile.SetPath(m_strConfigIniFile.c_str())) {
// 		return false;
// 	}
// 
// 	inifile.GetAllKeysAndValues(strConfigDirectorySection,strKey,strKeyValue);
// 	for(int i =0;i<strKey.GetSize();i++)
// 	{
// 		//char* pch= new char[strKey.]
// 		std::string stdstrKey,stdstrKeyValue;
// 		stdstrKey = strKey.GetAt(i);
// 		stdstrKeyValue = strKeyValue.GetAt(i);
// 		AnalyzeIniLine(stdstrKey,stdstrKeyValue);
// 		
// 	}
// 	m_clrBackgroundColor = RGB(m_background_nR, m_background_nG, m_background_nB);
// 	m_clrTextColor = RGB(m_text_nR, m_text_nG, m_text_nB);
// 	//	m_CoilSpecs[ctSystemCoil].m_dRFAMax = inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctSystemCoil].m_dRFAMax");
// 	m_CoilSpecs[ctSystemCoil].m_dRFAMax        = (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctSystemCoil].m_dRFAMax"));
// 	m_CoilSpecs[ctHeadSolonoid].m_dRFAMax      = (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctHeadSolonoid].m_dRFAMax"));
// 	m_CoilSpecs[ctBodySolonoidL].m_dRFAMax     = (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodySolonoidL].m_dRFAMax"));
// 	m_CoilSpecs[ctBodySolonoidM].m_dRFAMax     = (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodySolonoidM].m_dRFAMax"));
// 	m_CoilSpecs[ctBodySolonoidS].m_dRFAMax     = (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodySolonoidS].m_dRFAMax"));
// 	m_CoilSpecs[ctNeckSolonoid].m_dRFAMax      = (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctNeckSolonoid].m_dRFAMax"));
// 	m_CoilSpecs[ctHeadQD].m_dRFAMax            = (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctHeadQD].m_dRFAMax"));
// 	m_CoilSpecs[ctKneeQD].m_dRFAMax            = (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctKneeQD].m_dRFAMax"));
// 	m_CoilSpecs[ctBodyQDL].m_dRFAMax           = (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodyQDL].m_dRFAMax"));
// 	m_CoilSpecs[ctBodyQDM].m_dRFAMax           = (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodyQDM].m_dRFAMax"));
// 	m_CoilSpecs[ctBodyQDS].m_dRFAMax           = (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodyQDS].m_dRFAMax"));
// 	m_CoilSpecs[ctSurfaceNeck].m_dRFAMax       = (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctSurfaceNeck].m_dRFAMax"));
// 	m_CoilSpecs[ctSurfaceElbow].m_dRFAMax      = (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctSurfaceElbow].m_dRFAMax"));
// 	m_CoilSpecs[ctSurfaceShoulder].m_dRFAMax   = (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctSurfaceShoulder].m_dRFAMax"));
// 	m_CoilSpecs[ctPhaseArraySpine].m_dRFAMax   = (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctPhaseArraySpine].m_dRFAMax"));
// 	m_CoilSpecs[ctPhaseArrayCardiac].m_dRFAMax = (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctPhaseArrayCardiac].m_dRFAMax"));
// 	m_CoilSpecs[ctSystemCoil].m_dDefaultTG     = (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctSystemCoil].m_dDefaultTG"));
// 	m_CoilSpecs[ctHeadSolonoid].m_dDefaultTG   = (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctHeadSolonoid].m_dDefaultTG"));
// 	m_CoilSpecs[ctBodySolonoidL].m_dDefaultTG  = (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodySolonoidL].m_dDefaultTG"));
// 	m_CoilSpecs[ctBodySolonoidM].m_dDefaultTG  = (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodySolonoidM].m_dDefaultTG"));
// 	m_CoilSpecs[ctBodySolonoidS].m_dDefaultTG  = (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodySolonoidS].m_dDefaultTG"));
// 	m_CoilSpecs[ctNeckSolonoid].m_dDefaultTG   = (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctNeckSolonoid].m_dDefaultTG"));
// 	m_CoilSpecs[ctHeadQD].m_dDefaultTG         = (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctHeadQD].m_dDefaultTG"));
// 	m_CoilSpecs[ctKneeQD].m_dDefaultTG         = (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctKneeQD].m_dDefaultTG"));
// 	m_CoilSpecs[ctBodyQDL].m_dDefaultTG        = (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodyQDL].m_dDefaultTG"));
// 	m_CoilSpecs[ctBodyQDM].m_dDefaultTG        = (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodyQDM].m_dDefaultTG"));
// 	m_CoilSpecs[ctBodyQDS].m_dDefaultTG        = (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodyQDS].m_dDefaultTG"));
// 	m_CoilSpecs[ctSurfaceNeck].m_dDefaultTG    = (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctSurfaceNeck].m_dDefaultTG"));
// 	m_CoilSpecs[ctSurfaceElbow].m_dDefaultTG   = (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctSurfaceElbow].m_dDefaultTG"));
// 	m_CoilSpecs[ctSurfaceShoulder].m_dDefaultTG =(double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctSurfaceShoulder].m_dDefaultTG"));
// 	m_CoilSpecs[ctPhaseArraySpine].m_dDefaultTG =(double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctPhaseArraySpine].m_dDefaultTG"));
// 
// 	m_CoilSpecs[ctPhaseArrayCardiac].m_dDefaultTG	= (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctPhaseArrayCardiac].m_dDefaultTG"));
// 	m_CoilSpecs[ctHeadRecv].m_dRFAMax				= (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctHeadRecv].m_dRFAMax"));
// 	m_CoilSpecs[ctHeadRecv].m_dDefaultTG			= (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctHeadRecv].m_dDefaultTG"));
// 	m_CoilSpecs[ctHeadRecv].m_nTuneVoltage			= (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctHeadRecv].m_nTuneVoltage"));
// 	m_CoilSpecs[ctHeadRecv].m_nMatchVoltage			= (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctHeadRecv].m_nMatchVoltage"));
// 	m_CoilSpecs[ctBodyRecvMid].m_dRFAMax			= (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodyRecvMid].m_dRFAMax"));
// 	m_CoilSpecs[ctBodyRecvMid].m_dDefaultTG			= (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodyRecvMid].m_dDefaultTG"));
// 	m_CoilSpecs[ctBodyRecvMid].m_nTuneVoltage		= (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodyRecvMid].m_nTuneVoltage"));
// 	m_CoilSpecs[ctBodyRecvMid].m_nMatchVoltage		= (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodyRecvMid].m_nMatchVoltage"));
// 	m_CoilSpecs[ctBodyRecvSmall].m_dRFAMax			= (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodyRecvSmall].m_dRFAMax"));
// 	m_CoilSpecs[ctBodyRecvSmall].m_dDefaultTG		= (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodyRecvSmall].m_dDefaultTG"));
// 	m_CoilSpecs[ctBodyRecvSmall].m_nTuneVoltage		= (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodyRecvSmall].m_nTuneVoltage"));
// 	m_CoilSpecs[ctBodyRecvSmall].m_nMatchVoltage	= (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctBodyRecvSmall].m_nMatchVoltage"));
// 	m_CoilSpecs[ctNeckRecv].m_dRFAMax				= (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctNeckRecv].m_dRFAMax"));
// 	m_CoilSpecs[ctNeckRecv].m_dDefaultTG			= (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctNeckRecv].m_dDefaultTG"));
// 	m_CoilSpecs[ctNeckRecv].m_nTuneVoltage			= (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctNeckRecv].m_nTuneVoltage"));
// 	m_CoilSpecs[ctNeckRecv].m_nMatchVoltage			= (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctNeckRecv].m_nMatchVoltage"));
// 	m_CoilSpecs[ctKneeRecv].m_dRFAMax				= (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctKneeRecv].m_dRFAMax"));
// 	m_CoilSpecs[ctKneeRecv].m_dDefaultTG			= (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctKneeRecv].m_dDefaultTG"));
// 	m_CoilSpecs[ctKneeRecv].m_nTuneVoltage			= (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctKneeRecv].m_nTuneVoltage"));
// 	m_CoilSpecs[ctKneeRecv].m_nMatchVoltage			= (double)CStringtoF4(inifile.GetKeyValue(strConfigCoilSection,"m_CoilSpecs[ctKneeRecv].m_nMatchVoltage"));
// 	double t = m_CoilSpecs[ctKneeRecv].m_dDefaultTG	;
// 	 
// 	LoadDicomNodeInfo();
// 	m_hPushDll   = LoadLibrary("SendImageSetDLL.dll");
//     m_SendImages = (SENDIMAGES)GetProcAddress(m_hPushDll,"SendImages");
// 	//提取动态库的句柄；lwzbuaa;
// 	m_hPACSDLL = LoadLibrary("DCMINT.dll");
// 	//end lwz
// 	
// 	LoadRFCoilParams();
// 
// 	LoadPreEmphasisParams();
// 	/*********zyh add 2008.2.27*********/
// 	char szTmp[20];
// 	GetPrivateProfileString("SYSTEM",
// 		"DACARD_ENABLE", "TRUE",szTmp, 
// 		20, m_strConfigIniFile.c_str());
// 	if(0 != strcmp(strupr(szTmp), "TRUE"))
// 		m_bHasDACard = FALSE;
// 	else
// 		m_bHasDACard = TRUE;
// 	/**********************************************/
// 	LoadTuneConfig();
// 	
// 	CheckLeftDays();
// 
// 	return (LoadSystemParams());
// }
// 
// bool CConfigManager::AnalyzeIniLine(const std::string& strVariable, 
//                                  const std::string& strValue)
// {
//     if (strVariable == "site_id")
//     {
//         strcpy(m_SiteField.Id, strValue.substr(0, 15).c_str());
//     }
//     else if (strVariable == "institution_name")
//     {
//         strcpy(m_SiteField.InstDeptName, strValue.substr(0, 31).c_str());
//     }
//     else if (strVariable == "department_name")
//     {
//         strcpy(m_SiteField.InstDeptName, strValue.substr(0, 31).c_str());
//     }
//     else if (strVariable == "station_name")
//     {
//         strcpy(m_SiteField.StationName, strValue.substr(0, 31).c_str());
//     }
//     else if (strVariable == "serial_number")
//     {
//         strcpy(m_SiteField.BISerialNum, strValue.substr(0, 31).c_str());
//     }
//     
// 	else if (strVariable == "last_calibration_year")
//     {
//         m_SiteField.LastCalib.year = atoi(strValue.c_str());
//     }
// 	else if (strVariable == "last_calibration_month")
//     {
//         m_SiteField.LastCalib.month = atoi(strValue.c_str());
//     }
// 	else if (strVariable == "last_calibration_day")
//     {
//                     m_SiteField.LastCalib.day = atoi(strValue.c_str());
// 
//     }
// 	else if (strVariable == "last_calibration_hour")
//     {
//                     m_SiteField.LastCalib.hour = atoi(strValue.c_str());
// 
//     }
// 	else if (strVariable == "last_calibration_minute")
//     {
//                     m_SiteField.LastCalib.minute = atoi(strValue.c_str());
// 
//     }
// 	else if (strVariable == "last_calibration_second")
//     {
//                     m_SiteField.LastCalib.second = atoi(strValue.c_str());
// 
//     }
// 
// 	
//     else if (strVariable == "calibrated_magnet_strength")
//     {
//         m_SiteField.MagCalibStrength = atof(strValue.c_str());
//     }
//     else if (strVariable == "gradient_strength_x")
//     {
//         m_SiteField.GradientStrengthX = atof(strValue.c_str());
//     }
//     else if (strVariable == "gradient_strength_y")
//     {
//         m_SiteField.GradientStrengthY = atof(strValue.c_str());
//     }
//     else if (strVariable == "gradient_strength_z")
//     {
//         m_SiteField.GradientStrengthZ = atof(strValue.c_str());
//     }
// 	else if (strVariable == "center_frequency")
// 	{
// 		m_SiteField.SF = atof(strValue.c_str());
// 	}
//     else if (strVariable == "install_dir")
//     {
//         m_strInstallDirectory = strValue;
//     }
//     else if (strVariable == "image_dir")
//     {
//         m_strImageRootDirectory = strValue;
//     }
//     else if (strVariable == "pulse_sequence_dir")
//     {
//         m_strCDLDirectory = strValue;
//     }
// 	else if (strVariable == "config_dir")
// 	{
// 		m_strConfigDirectory = strValue;
// 	}
//     else if (strVariable == "temp_dir")
//     {
//         m_strTempDirectory = strValue;
//     }
//     else if (strVariable == "recycle_dir")
//     {
//         m_strRecycleDirectory = strValue;
//     }
//     else if (strVariable == "protocol_dir")
//     {
//         m_strProtocolDirectory = strValue;
//     }
// 	else if (strVariable == "ri_image_file")
// 	{
// 		m_strRIImageFile = strValue;
// 	}
// 	else if (strVariable == "ri_fid_file")
// 	{
// 		m_strRIFidFile = strValue;
// 	}
//     else if (strVariable == "background_color_red")
//     {
//         m_background_nR = atoi(strValue.c_str());
//        // m_clrBackgroundColor = RGB(nR, nG, nB);
//     }
// 	else if (strVariable == "background_color_green")
//     {
//         m_background_nG = atoi(strValue.c_str());
//         //m_clrBackgroundColor = RGB(nR, nG, nB);
//     }
// 	else if (strVariable == "background_color_blue")
//     {
//         m_background_nB = atoi(strValue.c_str());
//         //m_clrBackgroundColor = RGB(nR, nG, nB);
//     }
// 	
//     else if (strVariable == "text_color_red")
//     {
//         m_text_nR = atoi(strValue.c_str());
//         //m_clrBackgroundColor = RGB(nR, nG, nB);
//     }
// 	else if (strVariable == "text_color_green")
//     {
//        m_text_nG = atoi(strValue.c_str());
//         //m_clrBackgroundColor = RGB(nR, nG, nB);
//     }
// 	else if (strVariable == "text_color_blue")
//     {
//        m_text_nB = atoi(strValue.c_str());
//         //m_clrBackgroundColor = RGB(nR, nG, nB);
//     }
// 
// 	// filming
// 	else if (strVariable == "filming_PrinterIP")
// 	{
// 		m_FilmingConfig.m_strIP = strValue.c_str();
// 	}
// 	else if (strVariable == "filming_ImageSize")
// 	{
// 		m_FilmingConfig.m_nImageSize = atoi(strValue.c_str());
// 	}
// 	else if (strVariable == "filming_PrinterAE")
// 	{
// 		m_FilmingConfig.m_strPrinterAE = strValue.c_str();
// 	}
// 	else if (strVariable == "filming_PrinterPort")
// 	{
// 		m_FilmingConfig.m_strPort = strValue.c_str();
// 	}
// 	else if (strVariable == "filming_PrinterType")
// 	{
// 		m_FilmingConfig.m_nPrintType = atoi(strValue.c_str());
// 	}
// 	// ...
//     else
//         return false;   // cannot recognize the variable.
// 
//     return true;
// }
// /*!
// 	This funciton loads configuration information from file (or anything
// 	equivalent).
// 	\return \a true if successful, \a false otherwise.
// */
// bool CConfigManager::Load()
// {
//     std::ifstream inFile(m_strConfigFile.c_str());
// 
//     if (!inFile)
//         return false;
// 
//     std::string strLine, strVariable, strValue;
//     char buffer[512];
// 
//     int nEqualSignPosition = 0;
// 
//     while (inFile)
//     {
//         inFile.getline(buffer, 512);    
//         strLine = buffer;
//         nEqualSignPosition = strLine.find_first_of('=');
//         if (nEqualSignPosition == strLine.npos) 
//         {
//             // '=' not found, ignore the line.
//             TRACE("\'=\' not found, ignore the line.");
//             continue;
//         }
//         
//         if (!ParseLine(buffer, strVariable, strValue))
// 		{
//             continue;
// 		}
//         else
// 		{
//             AnalyzeLine(strVariable, strValue);
// 		}
//     }
// 	LoadDicomNodeInfo();
// 	m_hPushDll = LoadLibrary("SendImageSetDLL.dll");
// 	//add lwzh
// 	m_hPACSDLL = LoadLibrary("DCMINT.dll");
// 	
// 
// 	LoadRFCoilParams();
// 
// 	return (LoadSystemParams());
// }
// 
// /*!
// 	When user deletes a study, the study is moved from <image_root> to a 
// 	recycle directory. In this way, the user can recover deleted studies 
// 	before the recycle bin is cleaned.
// 	\return The root directory used to store deleted studies and series.
// */
// const std::string& CConfigManager::GetRecycleDirectory() const
// {
//     return m_strRecycleDirectory;
// }
// 
// /*!
// 	\return The only instance of this class.
// */
// CConfigManager& CConfigManager::GetHandle()
// {
// 	return s_ConfigManager;
// }
// 
// /*!
//     Parse one line of the config file.
//     \remarks The format of one line of the config file should be:
//     <variable> = <value>.
// 	\param strSource The string of the line input.
// 	\param strVariable Output parameter used to hold the token representing 
// 	the variable's name.
// 	\param strValue Output parameter used to hold the token representing the 
// 	variable's value.
// 	\return \a true if successful, \a false otherwise.
// */
// bool CConfigManager::ParseLine(const std::string& strSource, 
//                                std::string& strVariable, 
//                                std::string& strValue) const
// {
//     // Extract the left-hand part.
//     // remove leading spaces.
//     int nPosStart = strSource.find_first_not_of(" \t");
//     if (nPosStart == strSource.npos)
//         return false;
// 
//     int nPosEnd = strSource.find_first_of(" \t=", nPosStart);
//     if (nPosStart == strSource.npos)
//         return false;
//     strVariable = strSource.substr(nPosStart, nPosEnd - nPosStart);
// 
//     // Extract the right-hand part.
//     nPosStart = strSource.find('=');
//     if (nPosStart == strSource.npos)
//         return false;
// 
//     nPosStart = strSource.find_first_not_of(" \t", nPosStart + 1);
//     if (nPosStart == strSource.npos)
//         return false;
//     nPosEnd = strSource.find_last_not_of(" \t");
//     strValue = strSource.substr(nPosStart, nPosEnd - nPosStart + 1);
// 
//     return true;
// }
// 
// /*!
// 	This funciton semantically analyze a line of input from the config file.
// 	That line is already splited by ParseLine() to two parts, that is, a token
// 	representing the variable's name and a token representing the variable's 
// 	value.
// 	\param strVariable Name of the variable.
// 	\param strValue Value of the variable.e
// 	\return \a true if successful, \a false otherwise.
// */
// bool CConfigManager::AnalyzeLine(const std::string& strVariable, 
//                                  const std::string& strValue)
// {
//     if (strVariable == "site_id")
//     {
//         strcpy(m_SiteField.Id, strValue.substr(0, 15).c_str());
//     }
//     else if (strVariable == "institution_name")
//     {
//         strcpy(m_SiteField.InstDeptName, strValue.substr(0, 31).c_str());
//     }
//     else if (strVariable == "department_name")
//     {
//         strcpy(m_SiteField.InstDeptName, strValue.substr(0, 31).c_str());
//     }
//     else if (strVariable == "station_name")
//     {
//         strcpy(m_SiteField.StationName, strValue.substr(0, 31).c_str());
//     }
//     else if (strVariable == "serial_number")
//     {
//         strcpy(m_SiteField.BISerialNum, strValue.substr(0, 31).c_str());
//     }
//     else if (strVariable == "last_calibration")
//     {
//         COleDateTime dateTime;
//         if (dateTime.ParseDateTime(strValue.c_str()))
//         {
//             m_SiteField.LastCalib.year = dateTime.GetYear();
//             m_SiteField.LastCalib.month = dateTime.GetMonth();
//             m_SiteField.LastCalib.day = dateTime.GetDay();
//             m_SiteField.LastCalib.hour = dateTime.GetHour();
//             m_SiteField.LastCalib.minute = dateTime.GetMinute();
//             m_SiteField.LastCalib.second = dateTime.GetSecond();
//         }
//     }
//     else if (strVariable == "calibrated_magnet_strength")
//     {
//         m_SiteField.MagCalibStrength = atof(strValue.c_str());
//     }
//     else if (strVariable == "gradient_strength_x")
//     {
//         m_SiteField.GradientStrengthX = atof(strValue.c_str());
//     }
//     else if (strVariable == "gradient_strength_y")
//     {
//         m_SiteField.GradientStrengthY = atof(strValue.c_str());
//     }
//     else if (strVariable == "gradient_strength_z")
//     {
//         m_SiteField.GradientStrengthZ = atof(strValue.c_str());
//     }
// 	else if (strVariable == "center_frequency")
// 	{
// 		m_SiteField.SF = atof(strValue.c_str());
// 	}
//     else if (strVariable == "install_dir")
//     {
//         m_strInstallDirectory = strValue;
//     }
//     else if (strVariable == "image_dir")
//     {
//         m_strImageRootDirectory = strValue;
//     }
//     else if (strVariable == "pulse_sequence_dir")
//     {
//         m_strCDLDirectory = strValue;
//     }
// 	else if (strVariable == "config_dir")
// 	{
// 		m_strConfigDirectory = strValue;
// 	}
//     else if (strVariable == "temp_dir")
//     {
//         m_strTempDirectory = strValue;
//     }
//     else if (strVariable == "recycle_dir")
//     {
//         m_strRecycleDirectory = strValue;
//     }
//     else if (strVariable == "protocol_dir")
//     {
//         m_strProtocolDirectory = strValue;
//     }
// 	else if (strVariable == "ri_image_file")
// 	{
// 		m_strRIImageFile = strValue;
// 	}
// 	else if (strVariable == "ri_fid_file")
// 	{
// 		m_strRIFidFile = strValue;
// 	}
//     else if (strVariable == "background_color")
//     {
//         std::istringstream inStream(strValue);
//         int nR, nG, nB;
//         inStream >> nR >> nG >> nB;
//         m_clrBackgroundColor = RGB(nR, nG, nB);
//     }
//     else if (strVariable == "text_color")
//     {
//         std::istringstream inStream(strValue);
//         int nR, nG, nB;
//         inStream >> nR >> nG >> nB;
//         m_clrTextColor = RGB(nR, nG, nB);
//     }
// 	// filming
// 	else if (strVariable == "filming_PrinterIP")
// 	{
// 		m_FilmingConfig.m_strIP = strValue.c_str();
// 	}
// 	else if (strVariable == "filming_ImageSize")
// 	{
// 		m_FilmingConfig.m_nImageSize = atoi(strValue.c_str());
// 	}
// 	// ...
//     else
//         return false;   // cannot recognize the variable.
// 
//     return true;
// }
// 
// /*!
// 	For each BW value, there is a corresponding value of spectrometer parameter
// 	dead2. We save the table of available BW values and corresnpond Dead2 
// 	values in a file named "dead2_list.txt" located in the config directory.
// 	This function loads the table from the file and stored it in m_BWDead2s
// 	vector.
// 	\return \a true if successful, \a false otherwise.
// */
// bool CConfigManager::LoadBWDead2()
// {
// 	/*std::ifstream inFile;
// 	inFile.open ((GetConfigDirectory() + "Dead2_List.txt").c_str());*/
// 
// 	std::ifstream inFile((GetConfigDirectory() + "Dead2_List.txt").c_str());
// 	
// 	if (!inFile)
// 	{
// 		ASSERT(0);
// 		return false;
// 	}
// 
// 	CBWDead2 temp, old;
// 	//zyh add 2008.5.13 ifstream 读取最后一行重复。
// 	old.m_dBW = old.m_dDead2 = old.m_dDeadAct = -1.0;
// 	while (inFile)
// 	{
// 		inFile >> temp.m_dBW >> temp.m_dDead2 >> temp.m_dDeadAct;
// 		/*********zyh add 2008.5.13*********/
// 		if((temp.m_dBW != old.m_dBW)||(temp.m_dDead2 != old.m_dDead2) || (temp.m_dDeadAct != old.m_dDeadAct))
// 		{
// 			m_BWDead2s.push_back (temp);
// 			old.m_dBW = temp.m_dBW;
// 			old.m_dDead2 = temp.m_dDead2;
// 			old.m_dDeadAct = temp.m_dDeadAct;
// 		}
// 		/**********************************************/
// 	}
// 
// 	inFile.close();
// 	return true;
// }
// 
// /*!
// 	This function searches the m_BWDead2 container to find the item whose 
// 	BW value is nearest to the given bandwidth and returns the index of that
// 	item.
// 	\param dBW Bandwidth set by the user.
// 	\return Index of the item whose BW value is the nearest to the given
// 	bandwidth.
// 	\pre The m_BWDead2 container is sorted so that items with smaller BW values
// 	occur before those with larger BW values.
// */
// int CConfigManager::GetNearestBWIndex(double dBW) const
// {
// 	// Since there are only several tens of items in the container, so not
// 	// quite necessary to use binary search.
// 	int nIndex = 0;
// 	for (; nIndex < m_BWDead2s.size(); nIndex++)
// 	{
// 		if (m_BWDead2s[nIndex].m_dBW >= dBW)
// 		{
// 			if (nIndex == 0)
// 			{
// 				// if the first bandwidth is larger than the given bandwidth,
// 				// then use that value directly.
// 				return nIndex;
// 			}
// 			else if (m_BWDead2s[nIndex].m_dBW - dBW < dBW - m_BWDead2s[nIndex - 1].m_dBW)
// 			{
// 				return nIndex;
// 			}
// 			else
// 			{
// 				return nIndex - 1;
// 			}
// 		}
// 	}
// 
// 	// if no bandwidth is larger than dBW, use the last one (the largest).
// 	return (m_BWDead2s.size());
// }
// 
// /*!
// 	\param dBW Bandwidth set by the end user.
// 	\return The item that contains nearest BW value.
// */
// CBWDead2 CConfigManager::GetBWDead2(double dBW) const
// {
// 	return m_BWDead2s[GetNearestBWIndex(dBW)];
// }
// 
// /*!
// 	\param dBW Bandwidth set by the end user.
// 	\return The nearest available BW value.
// */
// double CConfigManager::GetNearestBW(double dBW) const
// {
// 	return m_BWDead2s[GetNearestBWIndex(dBW)].m_dBW;
// }
// 
// bool CConfigManager::LoadSystemParams()
// {
//     std::ifstream inFile((GetConfigDirectory() + "system_params.txt").c_str());
// 
//     if (!inFile)
//         return false;
// 
//     std::string strLine, strVariable, strValue;
//     char buffer[512];
// 
//     int nEqualSignPosition = 0;
// 
//     while (inFile)
//     {
//         inFile.getline(buffer, 512);    
//         strLine = buffer;
//         nEqualSignPosition = strLine.find_first_of('=');
//         if (nEqualSignPosition == strLine.npos) 
//         {
//             // '=' not found, ignore the line.
//             TRACE("\'=\' not found, ignore the line.");
//             continue;
//         }
//         
//         if (!ParseLine(buffer, strVariable, strValue))
//             continue;
//         else
//             AnalyzeSystemParams(strVariable, strValue);
//     }
// 
// 	return (LoadBWDead2());
// 
// }
// 
// bool CConfigManager::AnalyzeSystemParams (const std::string& strVariable, 
// 										  const std::string& strValue)
// {
// 	if (strVariable == "sys_GxFF")
// 	{
// 		m_SystemParams.m_dGxFF = atof(strValue.c_str());
// 	}
// 	else if (strVariable == "sys_GyFF")
// 	{
// 		m_SystemParams.m_dGyFF = atof(strValue.c_str());
// 	}
// 	else if (strVariable == "sys_GzFF")
// 	{
// 		m_SystemParams.m_dGzFF = atof(strValue.c_str());
// 	}
// 	else if (strVariable == "sys_GxRampRate")
// 	{
// 		m_SystemParams.m_nGxRampRate = atoi(strValue.c_str());
// 	}
// 	else if (strVariable == "sys_GyRampRate")
// 	{
// 		m_SystemParams.m_nGyRampRate = atoi(strValue.c_str());
// 	}
// 	else if (strVariable == "sys_GzRampRate")
// 	{
// 		m_SystemParams.m_nGzRampRate = atoi(strValue.c_str());
// 	}
// 	else if (strVariable == "sys_RFGateTime")
// 	{
// 		m_SystemParams.m_nGateTime = atoi(strValue.c_str());
// 	}
// 	else if (strVariable == "sys_GxRFDelay")
// 	{
// 		m_SystemParams.m_nGxRFDelay = atoi(strValue.c_str());
// 	}
// 	else if (strVariable == "sys_GyRFDelay")
// 	{
// 		m_SystemParams.m_nGyRFDelay = atoi(strValue.c_str());
// 	}
// 	else if (strVariable == "sys_GzRFDelay")
// 	{
// 		m_SystemParams.m_nGzRFDelay = atoi(strValue.c_str());
// 	}
// 	else if (strVariable == "sys_FactorGx")
// 	{
// 		m_SystemParams.m_dFactorGx = atof(strValue.c_str());
// 	}
// 	else if (strVariable == "sys_FactorGy")
// 	{
// 		m_SystemParams.m_dFactorGy = atof(strValue.c_str());
// 	}
// 	else if (strVariable == "sys_FactorGz")
// 	{
// 		m_SystemParams.m_dFactorGz = atof(strValue.c_str());
// 	}
// 	else if (strVariable == "sys_RFScale")
// 	{
// 		m_SystemParams.m_dRFScale = atof(strValue.c_str());
// 	}
// 	else
// 	{
// 		return false;
// 	}
// 
// 	return true;
// }
// 
// int CConfigManager::HasAdFilter()
// {
//     return m_nHasAdFilter;
// }
// 
// HMODULE CConfigManager::GetCvieDllhModule()
// {
//     return m_hCvieDll ;
// }
// 
// HMODULE CConfigManager::GetPushDllhModule()
// {
//     return m_hPushDll ;
// }
// //add lwzh
// //////////////////////////////////////////////////////////////////////////
// //新的深圳的PACS模块;
// HMODULE CConfigManager::GetPACSDLLMODULE()
// {
// 	return m_hPACSDLL;
// }
// 
// void CConfigManager::LoadDicomNodeInfo()
// {
// 	char    cEntryVal[64] ;
//     
// 	CString csDicomConfigPath = m_strHomePath;
// 	csDicomConfigPath += "Config\\dicomConfig.ini" ;
// 
// 	//Open the key about Local node.
// 	DWORD dwLen = GetPrivateProfileString("LOCAL", "AE", "Centauri 0.3T",cEntryVal, 64,csDicomConfigPath);
//     if (dwLen > 0)
// 	{
// 		m_strLocalAETitle = cEntryVal;
// 	}
// 	else
// 	{
// 		m_strLocalAETitle = "Centauri 0.3T" ;
// 	}
// 
// 	dwLen = GetPrivateProfileString("LOCAL", "PORT", "106",cEntryVal, 64,csDicomConfigPath);
//     if (dwLen > 0)
// 	{
// 		m_strLocalPort = cEntryVal;
// 	}
// 	else
// 	{
// 		m_strLocalPort = "106" ;
// 	}
// 	dwLen = GetPrivateProfileString("LOCAL", "IP", "172.10.0.168",cEntryVal, 64,csDicomConfigPath);
//     if (dwLen > 0)
// 	{
// 		m_strLocalNodeIP = cEntryVal;
// 	}
// 	else
// 	{
// 		m_strLocalNodeIP = "172.10.0.168" ;
// 	}
// 
// 	//Open the key about Local node.
// 	dwLen = GetPrivateProfileString("DEFAULT", "AE", "Centauri 0.3T",cEntryVal, 64,csDicomConfigPath);
//     if (dwLen > 0)
// 	{
// 		m_strDefaultAETitle = cEntryVal;
// 	}
// 	else
// 	{
// 		m_strDefaultAETitle = "Centauri 0.3T" ;
// 	}
// 	dwLen = GetPrivateProfileString("DEFAULT", "PORT", "106",cEntryVal, 64,csDicomConfigPath);
//     if (dwLen > 0)
// 	{
// 		m_strDefaultPort = cEntryVal;
// 	}
// 	else
// 	{
// 		m_strDefaultPort = "106" ;
// 	}
// 	dwLen = GetPrivateProfileString("DEFAULT", "IP", "172.10.0.231",cEntryVal, 64,csDicomConfigPath);
//     if (dwLen > 0)
// 	{
// 		m_strDefaultNodeIP = cEntryVal;
// 	}
// 	else
// 	{
// 		m_strDefaultNodeIP = "172.10.0.231" ;
// 	}
// 	////////////////////////////////////////
// 	//add chenshi Load Print Path
// 	CString strImgDestPathFileName = GetHomePath();
// 	if(strImgDestPathFileName.Right(2)=="\\\\")
// 	{
// 		//cut off /
// 		strImgDestPathFileName=strImgDestPathFileName.Left(strImgDestPathFileName.GetLength()-1);
// 	}
// 	strImgDestPathFileName+="PrintImage\\";
// 	CString szLocalPrintPath;
// 	dwLen =GetPrivateProfileString("SAVE_PATH","SAVE_PATH",strImgDestPathFileName,cEntryVal,64,csDicomConfigPath);
// 	if(dwLen > 0)
// 	{
// 		m_szPrint_Path=cEntryVal;
// 		m_FilmingConfig.m_szLocalPrintPath=m_szPrint_Path;
// 		
// 		
// 	}
// 	else
// 	{
// 		m_szPrint_Path=strImgDestPathFileName;
// 		m_FilmingConfig.m_szLocalPrintPath=m_szPrint_Path;
// 		
// 		
// 	}
// 	////////////////////////////////////////
// 	//add chenshi
// 	//
// 	strImgDestPathFileName = GetHomePath();
// 	if(strImgDestPathFileName.Right(2)=="\\\\")
// 	{
// 		//cut off /
// 		strImgDestPathFileName=strImgDestPathFileName.Left(strImgDestPathFileName.GetLength()-1);
// 	}
// 	strImgDestPathFileName+="config\\FilmPrintParam.ini";
// 	dwLen =GetPrivateProfileString("FILM_CHARATER_SET","FILM_CHARATER_SET",strImgDestPathFileName,cEntryVal,64,csDicomConfigPath);
// 	if(dwLen > 0)
// 	{
// 		m_szLocalCharator=cEntryVal;
// 		m_FilmingConfig.m_szCharactorConfigInfo=m_szLocalCharator;
// 		
// 		
// 	}
// 	else
// 	{
// 		m_szLocalCharator=strImgDestPathFileName;
// 		m_FilmingConfig.m_szCharactorConfigInfo=m_szLocalCharator;
// 		
// 		
// 	}
// 	//m_szLocalCharator=
// 	/////////////////////////////////////////
// }
// 
// // write CH I/Q's TuneV & MatchV into the coil config file - 20050623
// bool CConfigManager::StoreRFCoilParams(ECoilType eCoilID,
// 									   int nCHITuneV, int nCHIMatchV,
// 									   int nCHQTuneV, int nCHQMatchV)
// {
// 	int       nCoilNum ,nID,i;
// 	ECoilType eCoilIDT;
// 	CString csKeyName ,csTemp,csValue;
// 	CString csCoiParasPath = m_strHomePath;
// 	csCoiParasPath        += "Config\\CoilPara.ini" ;
// 
// 	nCoilNum = GetPrivateProfileInt("CoilNum", "CoilNum", 0, csCoiParasPath);
// 	csKeyName = "Coil";
// 	csTemp    = csKeyName;
// 	for (i=0; i<nCoilNum; i++)
// 	{
// 		csKeyName.Format("%s%d",csTemp,i+1);
// 		nID      =  GetPrivateProfileInt(csKeyName, "ID", 256, csCoiParasPath);
// 		eCoilIDT = (ECoilType)nID;
// 		if (eCoilIDT == eCoilID)
// 		{
// 			csValue.Format("%d",nCHITuneV);
// 			WritePrivateProfileString(csKeyName, "TuneV1",  csValue, csCoiParasPath);
// 			csValue.Format("%d",nCHIMatchV);
// 			WritePrivateProfileString(csKeyName, "MatchV1", csValue, csCoiParasPath);
// 			csValue.Format("%d",nCHQTuneV);
// 			WritePrivateProfileString(csKeyName, "TuneV2",  csValue, csCoiParasPath);
// 			csValue.Format("%d",nCHQMatchV);
// 			WritePrivateProfileString(csKeyName, "MatchV2", csValue, csCoiParasPath);
// 			break ;
// 		}
// 	}
// 	return true;
// }
// 
// bool CConfigManager::LoadRFCoilParams()
// {
// 	//Added by Tom, 2005.4.19
// 	int     nCoilNum ,nID,nbQuad,i;
// 	char    cEntryVal[128] ; 
// 	DWORD   dwLen;
// 	float   fTemp ;
// 	CString csKeyName ,csTemp;
// 	CString csCoiParasPath = m_strHomePath;
// 	csCoiParasPath        += "Config\\CoilPara.ini" ;
// 
// 	nCoilNum = GetPrivateProfileInt("CoilNum", "CoilNum", 0, csCoiParasPath);
// 	int nNumOfChannel = GetPrivateProfileInt( "SPECTR_CHANNEL_CONFIG", "MaxNumOfChannelsSupportedBySpectr", 4, csCoiParasPath );
// 
// 	m_TGTuneRange.m_nStartVal = GetPrivateProfileInt("TGTuneRange", "StartVal", 10, csCoiParasPath);
// 	dwLen = GetPrivateProfileString("TGTuneRange", "Step", "2.0" ,cEntryVal, 64, csCoiParasPath);
// 	m_TGTuneRange.m_fStep     = atof(cEntryVal);
// 	m_TGTuneRange.m_nNumOfSteps = GetPrivateProfileInt("TGTuneRange", "NumOfSteps", 3, csCoiParasPath);
// 
// 	// 20070821 - 限制TG范围，缺省为正负3
// 	dwLen = GetPrivateProfileString("TGTuneRange", "Range", "3.0" ,cEntryVal, 64, csCoiParasPath);
// 	m_TGTuneRange.m_fRange = atof(cEntryVal);
// 	
// 	if ( nNumOfChannel <= 0 || nNumOfChannel > MAX_NUM_OF_CHANNELS_SUPPORTED_BY_SOFTWARE )
// 	{
// 		CLang::GetHandle().ShowMessage( CLang::GetHandle().GetCharRes("MSG___NUM_OF_CHANNEL_INVALID") );
// 	}
// 
// 	//Modified by Tom, --2008.07.10   
// 	bool bCompoundReconResult = 
// 		(GetPrivateProfileInt( "SPECTR_CHANNEL_CONFIG", "CompoundReconResult", 1, csCoiParasPath )!=0 );	
// 	
// 	csKeyName = "Coil";
// 	csTemp    = csKeyName;
// 
// 	for ( i=0; i<nCoilNum; i++ )
// 	{
// 		CCoilSpec oCoilSpec;
// 		oCoilSpec.nMaxNumOfChannels = nNumOfChannel;
// 		oCoilSpec.bCompoundReconResult = bCompoundReconResult;
// 		
// 		csKeyName.Format("%s%d",csTemp, i+1 );
// 		nID    = GetPrivateProfileInt(csKeyName, "ID", 256, csCoiParasPath);
// 		nbQuad = GetPrivateProfileInt(csKeyName, "CoilType", 1, csCoiParasPath);
// 		GetPrivateProfileString(csKeyName, "Name", "" ,oCoilSpec.m_sName, 50,csCoiParasPath);
// 
// 		oCoilSpec.nBodyPartID = GetPrivateProfileInt(csKeyName, "BodyPartID", 0, csCoiParasPath);
// 				
// 		oCoilSpec.m_bQuad = nbQuad;
// 		oCoilSpec.m_sId = nID; 
// 
// 		// config of channel
// 		for ( int k = 0; k < MAX_NUM_OF_CHANNELS_SUPPORTED_BY_SOFTWARE; k++ )
// 		{
// 			oCoilSpec.bMcEnabled[ k ] = false;
// 		}
// 			
// 		GetPrivateProfileString(csKeyName, "EnableChannels", "0" ,cEntryVal, 64,csCoiParasPath);
// 		CString sEnableChannels = cEntryVal;
// 		oCoilSpec.nNumOfEnableChannels = 0;
// 		for ( k = 0; k < MAX_NUM_OF_CHANNELS_SUPPORTED_BY_SOFTWARE; k++ )
// 		{
// 			int nPos = sEnableChannels.Find( ";", 0 );
// 			if ( nPos == -1 && sEnableChannels == "" )
// 			{
// 				break;
// 			}
// 				
// 			CString sEnableChannel;
// 			CString sRemainString;
// 			if ( nPos == -1 && sEnableChannels != "" )
// 			{
// 				sEnableChannel = sEnableChannels;
// 				sRemainString = "";
// 				sEnableChannels = sRemainString;
// 			}
// 			else
// 			{
// 				sEnableChannel = sEnableChannels.Left( nPos );
// 				sRemainString = sEnableChannels.Right( sEnableChannels.GetLength() - (nPos + 1) );
// 				sEnableChannels = sRemainString;
// 			}
// 
// 			int nChannelNo = atoi( sEnableChannel );
// 			if ( nChannelNo >= 1 && nChannelNo <= MAX_NUM_OF_CHANNELS_SUPPORTED_BY_SOFTWARE )
// 			{
// 				oCoilSpec.bMcEnabled[ nChannelNo - 1 ] = true;
// 				++ oCoilSpec.nNumOfEnableChannels;
// 			}			
// 		}
// 
// 		if ( oCoilSpec.nNumOfEnableChannels == 0 )
// 		{
// 			oCoilSpec.nNumOfEnableChannels = 1;
// 			oCoilSpec.bMcEnabled[ 0 ] = true;
// 		}
// 		
// 		// Recon Coeff
// 		GetPrivateProfileString(csKeyName, "ReconCoeffOfEnableChannels", "" ,cEntryVal, 64,csCoiParasPath);
// 		CString sReconCoeffOfEnableChannels = cEntryVal;
// 		sReconCoeffOfEnableChannels.TrimLeft();
// 		sReconCoeffOfEnableChannels.TrimRight();
// 		if ( sReconCoeffOfEnableChannels != "" )
// 		{
// 			for ( k = 0; k < MAX_NUM_OF_CHANNELS_SUPPORTED_BY_SOFTWARE; k++ )
// 			{
// 				if ( oCoilSpec.bMcEnabled[ k ] )
// 				{
// 					int nPos = sReconCoeffOfEnableChannels.Find( ";", 0 );
// 					if ( nPos == -1 && sReconCoeffOfEnableChannels == "" )
// 					{
// 						break;
// 					}
// 					
// 					CString sReconCoeffOfEnableChannel;
// 					CString sRemainString;
// 					if ( nPos == -1 && sReconCoeffOfEnableChannels != "" )
// 					{
// 						sReconCoeffOfEnableChannel = sReconCoeffOfEnableChannels;
// 						sRemainString = "";
// 						sReconCoeffOfEnableChannels = sRemainString;
// 					}
// 					else
// 					{
// 						sReconCoeffOfEnableChannel = sReconCoeffOfEnableChannels.Left( nPos );
// 						sRemainString = sReconCoeffOfEnableChannels.Right( sReconCoeffOfEnableChannels.GetLength() - (nPos + 1) );
// 						sReconCoeffOfEnableChannels = sRemainString;
// 					}
// 					
// 					float fReconCoeffOfEnableChannel = atof( sReconCoeffOfEnableChannel );
// 					oCoilSpec.fReconCoeff[k] = fReconCoeffOfEnableChannel;
// 				}
// 			}			
// 		}		
// 
// 		// RF Transmitting params
// 		dwLen = GetPrivateProfileString(csKeyName, "RFAMax", "8.0" ,cEntryVal, 64,csCoiParasPath);
// 		fTemp = atof(cEntryVal);
// 		oCoilSpec.m_dRFAMax  = fTemp;
// 		dwLen = GetPrivateProfileString(csKeyName, "DefaultTG", "0.0" ,cEntryVal, 64,csCoiParasPath);
// 		fTemp = atof(cEntryVal);
// 		oCoilSpec.m_dDefaultTG = fTemp;
// 
// 		oCoilSpec.m_nTuneVoltage   = GetPrivateProfileInt(csKeyName, "TuneV1",  0, csCoiParasPath);
// 		oCoilSpec.m_nMatchVoltage  = GetPrivateProfileInt(csKeyName, "MatchV1", 0, csCoiParasPath);
// 		oCoilSpec.m_nTuneVoltage1  = GetPrivateProfileInt(csKeyName, "TuneV2",  0, csCoiParasPath);
// 		oCoilSpec.m_nMatchVoltage1 = GetPrivateProfileInt(csKeyName, "MatchV2", 0, csCoiParasPath);
// 		
// 		// RF Tuning params of linear or quadrature coil
// 		if ( oCoilSpec.m_bQuad == RCV_COIL_TYPE___LINEAR 
// 			|| oCoilSpec.m_bQuad == RCV_COIL_TYPE___QUADRATURE )
// 		{
// 			// Add code here
// /*
// 			int    m_nTuneVoltage;
// 			int    m_nMatchVoltage;
// 			int    m_nTuneVoltage1;
// 			int    m_nMatchVoltage1;
// 
// 			TuneV1    =4095
// 			TuneV2    =40
// 			MatchV1   =4095
// 			MatchV2   =4095
// */
// 		}
// 		
// 		m_CoilSpecs[(ECoilType)nID] = oCoilSpec;
// 	} 
// 				
// 	std::map<ECoilType, CCoilSpec>::iterator iter = m_CoilSpecs.begin();
// 	while ( iter != m_CoilSpecs.end() )
// 	{
// 		if ( iter->second.nMaxNumOfChannels == 0 )
// 		{
// 			iter->second.m_bQuad = RCV_COIL_TYPE___QUADRATURE;
// 			iter->second.nMaxNumOfChannels = nNumOfChannel;
// 			iter->second.nNumOfEnableChannels = 1;
// 			for ( i=0; i< MAX_NUM_OF_CHANNELS_SUPPORTED_BY_SOFTWARE; i++ )
// 			{
// 				iter->second.bMcEnabled[i] = false;
// 			}
// 
// 			// 默认为第一通道
// 			iter->second.bMcEnabled[0] = true;
// 			iter->second.fReconCoeff[0] = 1.0;
// 		}
// 		
// 		++iter;
// 	}
// 	
// 	m_nModeOfIdentification = GetPrivateProfileInt( "AUTO_IDENTIFICATION_OF_COIL", "MethodOfIdent", 0, csCoiParasPath);		
// 	
// 		
// /*
// 	// 无用代码
// 	nID    = GetPrivateProfileInt("ShimCoil", "ID", 6, csCoiParasPath);
// 	m_DefaultShimCoil = (ECoilType)nID ;
// 	//Tom added End
// 
//     std::ifstream inFile((GetConfigDirectory() + "rfcoil_params.txt").c_str());
// 
//     if (!inFile)
//         return false;
// 
//     std::string strLine, strVariable, strValue;
//     char buffer[512];
// 
//     int nEqualSignPosition = 0;
// 
//     while (inFile)
//     {
//         inFile.getline(buffer, 512);    
//         strLine = buffer;
//         nEqualSignPosition = strLine.find_first_of('=');
//         if (nEqualSignPosition == strLine.npos) 
//         {
//             // '=' not found, ignore the line.
//             TRACE("\'=\' not found, ignore the line.");
//             continue;
//         }
//         
//         if (!ParseLine(buffer, strVariable, strValue))
//             continue;
//         else
//             AnalyzeSystemParams(strVariable, strValue);
//     }
// */
// 
// 	return true;
// 
// }
// 
// bool CConfigManager::LoadRFCoilParams(ECoilType eCoilID, int& nTypeOfCoil, int &nCHITuneV, int &nCHIMatchV, int &nCHQTuneV, int &nCHQMatchV)
// {
// 	int       nCoilNum ,nID,i;
// 	ECoilType eCoilIDT;
// 	CString csKeyName ,csTemp,csValue;
// 	CString csCoiParasPath = m_strHomePath;
// 	csCoiParasPath        += "Config\\CoilPara.ini" ;
// 
// 	nCoilNum = GetPrivateProfileInt("CoilNum", "CoilNum", 0, csCoiParasPath);
// 	csKeyName = "Coil";
// 	csTemp    = csKeyName;
// 	for (i=0; i<nCoilNum; i++)
// 	{
// 		csKeyName.Format("%s%d",csTemp,i+1);
// 		nID      =  GetPrivateProfileInt(csKeyName, "ID", 256, csCoiParasPath);
// 		eCoilIDT = (ECoilType)nID;
// 		if (eCoilIDT == eCoilID)
// 		{
// 			nTypeOfCoil = GetPrivateProfileInt(csKeyName, "CoilType", 1, csCoiParasPath);
// 
// 			nCHITuneV  = GetPrivateProfileInt(csKeyName, "TuneV1",  0, csCoiParasPath);
// 			nCHIMatchV = GetPrivateProfileInt(csKeyName, "MatchV1", 0, csCoiParasPath);
// 			nCHQTuneV  = GetPrivateProfileInt(csKeyName, "TuneV2",  0, csCoiParasPath);
// 			nCHQMatchV = GetPrivateProfileInt(csKeyName, "MatchV2", 0, csCoiParasPath);
// 			break ;
// 		}
// 	}
// 	return true;
// }
// 
// bool CConfigManager::AnalyzeRFCoilParams (const std::string& strVariable, 
// 										  const std::string& strValue)
// {
// 	if (strVariable == "ctHeadRecv_Tune")
// 	{
// 		m_CoilSpecs[ctHeadRecv].m_nTuneVoltage = atoi(strValue.c_str());
// 	}
// 	else if (strVariable == "ctHeadRecv_Match")
// 	{
// 		m_CoilSpecs[ctHeadRecv].m_nMatchVoltage = atoi(strValue.c_str());
// 	}
// 	//
// 	else if (strVariable == "ctBodyRecvMid_Tune")
// 	{
// 		m_CoilSpecs[ctBodyRecvMid].m_nTuneVoltage = atoi(strValue.c_str());
// 	}
// 	else if (strVariable == "ctBodyRecvMid_Match")
// 	{
// 		m_CoilSpecs[ctBodyRecvMid].m_nMatchVoltage = atoi(strValue.c_str());
// 	}
// 	//
// 	else if (strVariable == "ctBodyRecvSmall_Tune")
// 	{
// 		m_CoilSpecs[ctBodyRecvSmall].m_nTuneVoltage = atoi(strValue.c_str());
// 	}
// 	else if (strVariable == "ctBodyRecvSmall_Match")
// 	{
// 		m_CoilSpecs[ctBodyRecvSmall].m_nMatchVoltage = atoi(strValue.c_str());
// 	}
// 	//
// 	else if (strVariable == "ctNeckRecv_Tune")
// 	{
// 		m_CoilSpecs[ctNeckRecv].m_nTuneVoltage = atoi(strValue.c_str());
// 	}
// 	else if (strVariable == "ctNeckRecv_Match")
// 	{
// 		m_CoilSpecs[ctNeckRecv].m_nMatchVoltage = atoi(strValue.c_str());
// 	}
// 	//
// 	else if (strVariable == "ctKneeRecv_Tune")
// 	{
// 		m_CoilSpecs[ctKneeRecv].m_nTuneVoltage = atoi(strValue.c_str());
// 	}
// 	else if (strVariable == "ctKneeRecv_Match")
// 	{
// 		m_CoilSpecs[ctKneeRecv].m_nMatchVoltage = atoi(strValue.c_str());
// 	}
// 	//
// 	else
// 	{
// 		return false;
// 	}
// 
// 	return true;
// }
// 
// bool CConfigManager::IsQuadCoil(ECoilType coilType)
// {
//     return (m_CoilSpecs[coilType].m_bQuad)>0?true:false ;
// }
// 
// bool CConfigManager::IsSystemTest()
// {
//     return m_bTest ;
// }
// 
// bool CConfigManager::IsSysTimeout()
// {
//     return m_bSysTimeout ;
// }
// 
// bool CConfigManager::ReadCryptFile()
// {
// 	CString csCrypt,csCrypt1,csDays,csFileNo;
// 	CString csResult,csFilePath,csStationNo;
// 	CCrypt  crypt;
// 	char    cCrypt[500];
// 	int     nFileNo ,nDays;
// 	long    lResult ;
// 
// 	csFilePath = m_strHomePath + "bin\\mri.txt" ;
// 	CFile  file;
// 	if (!file.Open(csFilePath,CFile::modeRead))
// 	{
// 		return false ;
// 	}
// 
// 	WORD nKey ;
// 	int nLen = file.Read(&nKey,2);
// 	if (nLen<2)
// 	{
// 		file.Close();
// 		return false ;
// 	}
// 
// 	nLen = file.Read(cCrypt,500);
// 	if (nLen<30)
// 	{
// 		file.Close();
// 		return false ;
// 	}
// 	file.Close();
// 
// 	//Modified by Tom, 2005.6.19
// 	if (!file.Open(csFilePath,CFile::modeWrite))
// 	{
// 		return false ;
// 	}
// 	char* pcN = "";
// 	file.Write((void*)pcN,1);
// 	file.Close();
// 
// 
// 	cCrypt[nLen] = 0;
// 	csCrypt.Format("%s",cCrypt);
// 	csResult = crypt.Decrypt(csCrypt,nKey);
// 	nLen      = csResult.Find(" ",0);
// 	int nLen2 = csResult.Find(" ",nLen+1);
// 	int nLen3 = csResult.Find(" ",nLen2+1);
// 	int nLen4 = csResult.Find(" ",nLen3+1);
// 
// 	csCrypt     = csResult.Left(nLen2);
// 	csStationNo = csCrypt.Right(nLen2-nLen-1);
// 	csCrypt     = csResult.Left(nLen3);
// 	csDays      = csCrypt.Right(nLen3 - nLen2 -1);
// 	nDays       = atoi(csDays.GetBuffer(5));
// 	csCrypt     = csResult.Right(2);
// 	csFileNo    = csCrypt.Right(nLen4 - nLen3 -1);
// 	nFileNo     = atoi(csFileNo.GetBuffer(4));
//     //Write to register table.
// 	SYSTEMTIME  sysTime ;
// 	HKEY        hKey ;
// 	CString     csSysTime;
// 	nKey  += 1037 ; 
// 
// 	GetSystemTime(&sysTime);
// 	csSysTime.Format("%d-%d-%d",sysTime.wYear,sysTime.wMonth,sysTime.wDay);
//     RegCreateKeyEx(HKEY_LOCAL_MACHINE, 
// 		           "SOFTWARE\\XinAoMDT\\Prospect",
// 				   0,
// 				   NULL,
// 				   REG_OPTION_NON_VOLATILE,
// 				   KEY_ALL_ACCESS,
// 				   NULL,
// 				   &hKey,
// 				   NULL);
// 	if (nFileNo > 0)
// 	{
// 		DWORD   dwSize;
// 		WORD    nKey1 ;
// 		CString csFileNo1;
// 
// 		dwSize  = 128 ;
// 		lResult = RegQueryValueEx( hKey, "D", NULL, NULL, (BYTE*)cCrypt, &dwSize);
// 		if (lResult != ERROR_SUCCESS)
// 		{
// 			return false ;
// 		}
// 		nKey1 = atoi(cCrypt) - 503;
// 
// 		dwSize  = 128 ;
// 		lResult = RegQueryValueEx( hKey, "E", NULL, NULL, (BYTE*)cCrypt, &dwSize);
// 		if (lResult != ERROR_SUCCESS)
// 		{
// 			return false ;
// 		}
// 		csFileNo1.Format("%s",cCrypt) ;
// 		csCrypt =  crypt.Decrypt(csFileNo1,nKey1);
// 		WORD nFileNo1 = atoi(csCrypt.GetBuffer(3));
// 		if (nFileNo > nFileNo1)
// 		{
// 			csCrypt.Format("%d",nKey) ;
// 
// 			nLen    = csCrypt.GetLength();
// 			lResult = RegSetValueEx(hKey,"D",0,REG_SZ,(const unsigned char *)csCrypt.GetBuffer(nLen+1),nLen+1);
// 
// 			nKey   -= 503 ;
// 			csCrypt = crypt.Encrypt(csFileNo,nKey);
// 			nLen    = csCrypt.GetLength();
// 			lResult = RegSetValueEx(hKey,"E",0,REG_SZ,(const unsigned char *)csCrypt.GetBuffer(nLen+1),nLen+1);
// 
// 			csCrypt = crypt.Encrypt(csDays,nKey);
// 			nLen    = csCrypt.GetLength();
// 			lResult = RegSetValueEx(hKey,"F",0,REG_SZ,(const unsigned char *)csCrypt.GetBuffer(nLen+1),nLen+1);
// 
//             
// 			csCrypt = crypt.Encrypt(csStationNo,nKey);
// 			nLen    = csCrypt.GetLength();
// 			lResult = RegSetValueEx(hKey,"G",0,REG_SZ,(const unsigned char *)csCrypt.GetBuffer(nLen+1),nLen);
// 
// 			csCrypt =  crypt.Encrypt(csSysTime,nKey);
// 			nLen    = csCrypt.GetLength();
// 			lResult = RegSetValueEx(hKey,"H",0,REG_SZ,(const unsigned char *)csCrypt.GetBuffer(nLen+1),nLen+1);
// 			lResult = RegSetValueEx(hKey,"I",0,REG_SZ,(const unsigned char *)csCrypt.GetBuffer(nLen+1),nLen+1);
// 			if (nDays <= 0)
// 			{
// 				RegCloseKey(hKey);
// 				return false ;
// 			}
// 		}
// 		else
// 		{
// 			RegCloseKey(hKey);
// 			return false ;
// 		}
// 	}
// 	else if (nFileNo == 0)
// 	{
//  		csCrypt.Format("%d",nKey) ;
// 		nLen        = csCrypt.GetLength();
// 		lResult     = RegSetValueEx(hKey,"D",0,REG_SZ,(const unsigned char *)csCrypt.GetBuffer(nLen+1),nLen+1);
// 
// 		nKey   -= 503 ;
// 		csCrypt =  crypt.Encrypt(csFileNo,nKey);
// 		nLen    = csCrypt.GetLength();
// 		lResult = RegSetValueEx(hKey,"E",0,REG_SZ,(const unsigned char *)csCrypt.GetBuffer(nLen+1),nLen+1);
// 
// 		csCrypt =  crypt.Encrypt(csDays,nKey);
// 		nLen    = csCrypt.GetLength();
// 		lResult = RegSetValueEx(hKey,"F",0,REG_SZ,(const unsigned char *)csCrypt.GetBuffer(nLen+1),nLen+1);
// 
// 		csCrypt =  crypt.Encrypt(csStationNo,nKey);
// 		nLen    = csCrypt.GetLength();
// 		lResult = RegSetValueEx(hKey,"G",0,REG_SZ,(const unsigned char *)csCrypt.GetBuffer(nLen+1),nLen+1);
// 
// 		csCrypt =  crypt.Encrypt(csSysTime,nKey);
// 		nLen    = csCrypt.GetLength();
// 		lResult = RegSetValueEx(hKey,"H",0,REG_SZ,(const unsigned char *)csCrypt.GetBuffer(nLen+1),nLen+1);
// 		lResult = RegSetValueEx(hKey,"I",0,REG_SZ,(const unsigned char *)csCrypt.GetBuffer(nLen+1),nLen+1);
// 		if (nDays <= 0)
// 		{
// 			RegCloseKey(hKey);
// 			return false ;
// 		}
// 	}
// 	else
// 	{
// 		RegCloseKey(hKey);
// 		return false ;
// 	}
// 	RegCloseKey(hKey);
//     return true ;
// }
// 
// bool CConfigManager::CheckLeftDays()
// {
// 	//read registry table
// 	HKEY    hKey;
// 	DWORD   dwSize ;
// 	char    cCrypt[500] ;
// 	WORD    wCryptKey ;
//     int     nLeftDays ;
// 	CString csDate ,csCrypt,csCryptWriteDate,csCryptStationNo,csCryptDays;
// 	CString csSysTime,csDays;
// 	CCrypt  crypt;
// 	
// 	long lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\XinAoMDT\\Prospect", 
// 		                        0, KEY_READ|KEY_WRITE, &hKey);
// 
// 	dwSize       = 128 ;
// 	lResult      = RegQueryValueEx(hKey, "I", NULL, NULL, (BYTE*)cCrypt, &dwSize);
// 	if (lResult != ERROR_SUCCESS)   //cannot find "I" key
// 	{
// 		RegCloseKey(hKey);
// 		if (!ReadCryptFile())
// 		{
// 			m_bSysTimeout = true;
// 		}
// 		else
// 		{
// 			m_bSysTimeout = false;
// 		}
// 		return !m_bSysTimeout;
// 	}
// 
//     csCrypt.Format("%s",cCrypt);
// 	dwSize       = 128 ;
// 	lResult      = RegQueryValueEx(hKey, "H", NULL, NULL, (BYTE*)cCrypt, &dwSize);
// 	csCryptWriteDate.Format("%s",cCrypt);
// 
// 	dwSize       = 128 ;
// 	lResult      = RegQueryValueEx(hKey, "G", NULL, NULL, (BYTE*)cCrypt, &dwSize);
// 	csCryptStationNo.Format("%s",cCrypt);
// 
// 	dwSize       = 128 ;
// 	lResult      = RegQueryValueEx(hKey, "F", NULL, NULL, (BYTE*)cCrypt, &dwSize);
// 	csCryptDays.Format("%s",cCrypt);
// 
// 	dwSize       = 128 ;
// 	lResult      = RegQueryValueEx(hKey, "D", NULL, NULL, (BYTE*)cCrypt, &dwSize);
//     wCryptKey    = atoi(cCrypt) - 503;
// //	lResult      = RegQueryValueEx(hKey, "E", NULL, NULL, (BYTE*)cCrypt, &dwSize);
// 
// 	//Decrypt last date
// 	DWORD  dwNowDate, dwRegDate ,dwLastDate;
// 	csDate     = crypt.Decrypt(csCrypt,wCryptKey);
// 	int nLen   = csDate.GetLength();
// 	int nPos   = csDate.Find('-');
// 	int nYear  = atoi(csDate.Left(nPos).GetBuffer(4));
// 	csDate     = csDate.Right(nLen - nPos -1) ;
// 	nPos       = csDate.Find('-');
// 	int nMonth = atoi(csDate.Left(nPos).GetBuffer(2));
// 	nLen       = csDate.GetLength();
// 	nPos       = csDate.Find('-');
// 	csDate     = csDate.Right(nLen - nPos - 1) ;
// 	int nDay   = atoi(csDate.GetBuffer(2));
// 	dwLastDate = 372*nYear + 31*nMonth + nDay ;
// 
// 	//Decrypt register date
// 	csDate    = crypt.Decrypt(csCryptWriteDate,wCryptKey);
// 	nLen      = csDate.GetLength();
// 	nPos      = csDate.Find('-');
// 	nYear     = atoi(csDate.Left(nPos).GetBuffer(4));
// 	csDate    = csDate.Right(nLen - nPos -1) ;
// 	nPos      = csDate.Find('-');
// 	nMonth    = atoi(csDate.Left(nPos).GetBuffer(2));
// 	nLen      = csDate.GetLength();
// 	nPos      = csDate.Find('-');
// 	csDate    = csDate.Right(nLen - nPos - 1) ;
// 	nDay      = atoi(csDate.GetBuffer(2));
// 	dwRegDate = 372*nYear + 31*nMonth + nDay ;
// 	
// 	SYSTEMTIME  sysTime ;
// 	GetSystemTime(&sysTime);
//     dwNowDate = 372*sysTime.wYear + 31*sysTime.wMonth + sysTime.wDay ;
// 	
// 	//Decrypt left days
//     nLeftDays     = atoi(crypt.Decrypt(csCryptDays,wCryptKey).GetBuffer(5));
// 	m_csStationNo = crypt.Decrypt(csCryptStationNo,wCryptKey);
// 	if ((dwNowDate < dwRegDate)||(dwNowDate < dwLastDate))
// 	{
// 		nLeftDays-- ;
// 	}
// 	if (dwNowDate > dwLastDate)
// 	{
// 		nLeftDays -= abs(dwNowDate - dwLastDate) ;
// 		csSysTime.Format("%d-%d-%d",sysTime.wYear,sysTime.wMonth,sysTime.wDay);
// 		csCrypt =  crypt.Encrypt(csSysTime,wCryptKey);
// 		nLen = csCrypt.GetLength();
// 		lResult = RegSetValueEx(hKey,"I",0,REG_SZ,(const unsigned char *)csCrypt.GetBuffer(nLen+1),nLen+1);
// 	}
// 	csDays.Format("%d",nLeftDays);
// 	csCrypt =  crypt.Encrypt(csDays,wCryptKey);
// 	nLen = csCrypt.GetLength();
// 	lResult = RegSetValueEx(hKey,"F",0,REG_SZ,(const unsigned char *)csCrypt.GetBuffer(nLen+1),nLen+1);
// 
// 	if (nLeftDays <= 0)
// 	{
// 		if (!ReadCryptFile())
// 		{
// 			m_bSysTimeout = true;
// 		}
// 		else
// 		{
// 			m_bSysTimeout = false;
// 		}
// 	}
// 	else
// 	{
// 		m_bSysTimeout = false;
// 	}
// 
// /*  lResult   = RegQueryValueEx(hKey, "I", NULL, NULL, (BYTE*)cCrypt, &dwSize); //Get Last user time.
// 	if (lResult != ERROR_SUCCESS)
// 	{
// 		LPVOID lpMsgBuf;
// 		FormatMessage( 
// 			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
// 			FORMAT_MESSAGE_FROM_SYSTEM | 
// 			FORMAT_MESSAGE_IGNORE_INSERTS,
// 			NULL,
// 			GetLastError(),
// 			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
// 			(LPTSTR) &lpMsgBuf,
// 			0,
// 			NULL 
// 		);
// 	}*/
// 	RegCloseKey(hKey);
//     return true ;
// }
// 
// CString CConfigManager::GetStationNo()
// {
//     return m_csStationNo ;
// }
// 
// int CConfigManager::LoadFilterPara()
// {
//     //Added by Tom, 2005.4.19
// 	int     nFilterNum ,i;
// 	char    cEntryVal[128] ; 
// 	DWORD   dwLen;
// 
// 	CString csKeyName ,csTemp;
// 	CString csFilterParasPath = m_strHomePath;
// 	csFilterParasPath        += "Config\\AdFilterPara.ini" ;
// 
// 	nFilterNum   = GetPrivateProfileInt("FilterNum", "Num", 0, csFilterParasPath);
//     if (nFilterNum <= 0)
// 	{
// 		m_nHasAdFilter = 0 ;
// 		m_hCvieDll     = NULL;
// 		return 0 ;
// 	}
// 
// 	m_nHasAdFilter = GetPrivateProfileInt("FilterNum", "hasAdFilter", 0, csFilterParasPath);
// 	if (m_nHasAdFilter == 1)
// 	{
// 		m_hCvieDll = LoadLibrary("cvie.dll");  //Modified by Tom,2005.7.18
// 	}
// 	else if (m_nHasAdFilter == 2)
// 	{
// 		m_hCvieDll = LoadLibrary("gvmri.dll"); //Modified by Tom,2005.7.18
// 	}
// 	else
// 	{
// 		m_hCvieDll = NULL ;
// 	}
// 
// 	csKeyName = "Filter";
// 	csTemp    = csKeyName;
// 	for (i=0; i<nFilterNum; i++)
// 	{
// 		csKeyName.Format("%s%d",csTemp,i+1);
// 		dwLen = GetPrivateProfileString(csKeyName, "Name", "DeNoise" ,cEntryVal, 64,csFilterParasPath);
// 		m_csFilterName[i].Format("%s",cEntryVal);
// 		dwLen = GetPrivateProfileString(csKeyName, "ParaFile", "DeNoise1.par" ,cEntryVal, 64,csFilterParasPath);
// 		m_csFilterParaFileName[i].Format("%s",cEntryVal);
// 	}
// 	return nFilterNum;
// }
// 
// void CConfigManager::ReadPatientInfoItemFlag()
// {
// 	char sIniFile [_MAX_PATH], sVal[255];
// 	CString ss;
// 	::GetCurrentDirectory (_MAX_PATH, sIniFile);
// 	strcat( sIniFile, "\\xbmri.ini" );
// 	GetPrivateProfileString( "PATIENT_INFO", "EnableMrNoItem", "true" ,sVal, 255, m_strConfigIniFile.c_str()/*sIniFile*/ );
// 	ss = ::strlwr( sVal );
// 	ss.TrimLeft();
// 	ss.TrimRight();
// 	if ( ss == "false")
// 	{
// 		m_bEnableMrNoItem = false;
// 	}
// 	else
// 	{
// 		m_bEnableMrNoItem = true;
// 	}
// }
// 
// void CConfigManager::ReadAnnotationCodingDirType()
// {
// 	char sIniFile [_MAX_PATH];  // sVal[255];
// 	CString ss;
// 	::GetCurrentDirectory (_MAX_PATH, sIniFile);
// 	strcat( sIniFile, "\\xbmri.ini" );
// 	m_nAnnotationCodingDirType = GetPrivateProfileInt( "CODING_DIRECTION_ANNOTATION", "AnnotationCodingType", cdtFreqDirection, m_strConfigIniFile.c_str() );
// }
// 
// unsigned char CConfigManager::ReadMethodIdOfCoilTuningFromCfgFile()
// {
// 	return GetPrivateProfileInt( "COIL_TUNING", "Method", 0, m_strConfigIniFile.c_str() );;
// }
// 
// void CConfigManager::ReadConfigInfoFromFile()
// {
// 	char sImagePath[255];
// 	GetPrivateProfileString( "SYSTEM_BIMRI_CONFIG_DIRECTORY", "image_dir" , "", sImagePath, 255, m_strConfigIniFile.c_str() );
// 	m_strImageRootDirectory = sImagePath;
// }
// 
// void CConfigManager::LoadPreEmphasisParams()
// {
// 	CString csFilterParasPath = m_strHomePath;
// 	csFilterParasPath        += "Config\\PreEmphasisParams.ini" ;
// 
// 	DWORD dwLen;
// 	char  cEntryVal[128]; 
// 	int   iLoop;
// 	CString strItemA, strItemK;
// 
// 	// 载入X通道数据
// 	for (iLoop=1; iLoop<=MAX_PREEMPHASIS_LEVEL; iLoop++)
// 	{
// 		strItemA.Format("PREXA%d", iLoop);
// 		strItemK.Format("PREXK%d", iLoop);
// 		dwLen = GetPrivateProfileString("XCHANNEL", strItemA, "0.0", cEntryVal, 128, csFilterParasPath);
// 		m_PreEmpahsisParams.m_XChParams[iLoop-1].PREA = atof(cEntryVal);
// 		dwLen = GetPrivateProfileString("XCHANNEL", strItemK, "100.0", cEntryVal, 128, csFilterParasPath);
// 		m_PreEmpahsisParams.m_XChParams[iLoop-1].PREK = atof(cEntryVal);
// 	}
// 	// 载入Y通道数据
// 	for (iLoop=1; iLoop<=MAX_PREEMPHASIS_LEVEL; iLoop++)
// 	{
// 		strItemA.Format("PREYA%d", iLoop);
// 		strItemK.Format("PREYK%d", iLoop);
// 		dwLen = GetPrivateProfileString("YCHANNEL", strItemA, "0.0", cEntryVal, 128, csFilterParasPath);
// 		m_PreEmpahsisParams.m_YChParams[iLoop-1].PREA = atof(cEntryVal);
// 		dwLen = GetPrivateProfileString("YCHANNEL", strItemK, "100.0", cEntryVal, 128, csFilterParasPath);
// 		m_PreEmpahsisParams.m_YChParams[iLoop-1].PREK = atof(cEntryVal);
// 	}
// 	// 载入Z通道数据
// 	for (iLoop=1; iLoop<=MAX_PREEMPHASIS_LEVEL; iLoop++)
// 	{
// 		strItemA.Format("PREZA%d", iLoop);
// 		strItemK.Format("PREZK%d", iLoop);
// 		dwLen = GetPrivateProfileString("ZCHANNEL", strItemA, "0.0", cEntryVal, 128, csFilterParasPath);
// 		m_PreEmpahsisParams.m_ZChParams[iLoop-1].PREA = atof(cEntryVal);
// 		dwLen = GetPrivateProfileString("ZCHANNEL", strItemK, "100.0", cEntryVal, 128, csFilterParasPath);
// 		m_PreEmpahsisParams.m_ZChParams[iLoop-1].PREK = atof(cEntryVal);
// 	}
// }
// 
// // 装载调谐模式配置-20070413
// void CConfigManager::LoadTuneConfig(void)
// {
// 	CString strTuneCfgFile = m_strHomePath;
// 	strTuneCfgFile        += "Config\\TuneConfig.ini" ;
// 
// 	m_TuneConfig.m_tmDefaultTuneModeTG = 
// 		(TUNEMODE)GetPrivateProfileInt("DEFAULTTUNEMODE", "DefaultTuneMode_TG", tmAlwaysTune, strTuneCfgFile);
// 
// 	m_TuneConfig.m_tmDefaultTuneModeRG = 
// 		(TUNEMODE)GetPrivateProfileInt("DEFAULTTUNEMODE", "DefaultTuneMode_RG", tmAlwaysTune, strTuneCfgFile);
// 
// 	/*********zyh add 2008.2.27*********/
// 	if(m_bHasDACard)
// 		m_TuneConfig.m_tmDefaultTuneModeRFRcvCoil = 
// 		(TUNEMODE)GetPrivateProfileInt("DEFAULTTUNEMODE", "DefaultTuneMode_RFRcvCoil", tmTuneFirstOnly, strTuneCfgFile);
// 	else
// 		m_TuneConfig.m_tmDefaultTuneModeRFRcvCoil = tmNotAvailable;
// 	/**********************************************/
// 
// 	m_TuneConfig.m_tmDefaultTuneModeAutoShim = 
// 		(TUNEMODE)GetPrivateProfileInt("DEFAULTTUNEMODE", "DefaultTuneMode_AutoShim", tmTuneFirstOnly, strTuneCfgFile);
// }
// 
// bool CConfigManager::IsTuning(TUNEMODE tmTuneMode, bool bIsFirstSeries)
// {
// 	return (tmTuneMode == tmAlwaysTune) || (bIsFirstSeries && (tmTuneMode == tmTuneFirstOnly));
// }
// 
// /** [zhlxu 2008.5.5] [] 添加TR限制值的文件配置功能 **/
// void CConfigManager::GetTRLimitedValueFromFile()
// {
// 	char sVal[255];
// 	CString sConfigFile = m_strConfigDirectory.c_str();
// 	sConfigFile += "\\TR_list.txt";
// 	
// 	GetPrivateProfileString("TR", "PowerSupplyFrequency", "50.0",sVal, 255, sConfigFile);	
// 	m_fTRLimitedValue = atof( sVal );
// }
// /** [zhlxu 2008.5.5] **/
// // -----------------------------------------------------------------------------------------------------------
// // ********************************************************【语言字符资源】公共接口类
CLang CLang::s_oHandle;

CLang::CLang()
{
	CString sInstallDirectory = GetInstallDirectory();
	sprintf( m_sLangIniFile, "%s", sInstallDirectory );

	strcat( m_sLangIniFile, "\\config\\Lang.ini" );	

	// 创建字体
	CreateFont();
	// 读取字符资源
	ReadCharResourceFromFile();
}

CLang::~CLang()
{
}

CLang& CLang::GetHandle()
{
	return s_oHandle;
}

CString CLang::GetInstallDirectory()
{
	CString sInstallDirectory;
	HKEY hKey;
	
	long lResult = RegOpenKeyEx( HKEY_LOCAL_MACHINE, "SOFTWARE\\XinAoMDT\\Prospect", 0, KEY_READ, &hKey );
	if(lResult != ERROR_SUCCESS)
	{
		return "";
	}
	
	char szDir[MAX_PATH];
	DWORD dwSize = MAX_PATH;
	lResult = RegQueryValueEx( hKey, "InstallDir", NULL, NULL, (BYTE*) szDir, &dwSize );
	if(lResult != ERROR_SUCCESS)
	{
		return "";
	}
	
	sInstallDirectory = szDir;
	sInstallDirectory += "\\";
	sInstallDirectory += "\\";
	
	do
	{
		sInstallDirectory = sInstallDirectory.Left( sInstallDirectory.GetLength() - 1 );
	} while ( sInstallDirectory.Right( 1 ) == "\\" );
	
	return sInstallDirectory;
}

void CLang::ReadCharResourceFromFile()
{
	CFile oIniFile;
	if( oIniFile.Open(m_sLangIniFile, CFile::modeRead) == FALSE )
	{
		CString sMsg;
		sMsg.Format( "Can't open the character resource file Lang.ini" );
/*
		CLog::GetHandle().Write( sMsg );
		::PostQuitMessage(-1);
*/
		return;
	}
	
	CArchive ar(&oIniFile, CArchive::load);
	CString strLine = "";
	
	do
	{
		if(strLine.GetLength() == 0) 
			continue;
        
		// tokenize
		int split_index = strLine.Find("=");
		CString key,value;
		key = strLine.Left(split_index);
		key.TrimLeft();
		key.TrimRight();
		if ( key == "" ) continue;
		value = strLine.Mid(split_index+1);
		value.TrimLeft();
		value.TrimRight();
		
		// character resource
//		key.MakeUpper();
		m_mapCharRes[key] = value;

	} while(ar.ReadString(strLine));
	
	ar.Close();
	oIniFile.Close();	
}

CString CLang::GetCharRes( CString sKey )
{
	CString sValue;
	BOOL bRet = m_mapCharRes.Lookup( sKey, sValue );
	if ( bRet == 0 )
	{
		CString sMsg;
		sMsg.Format( "The string resource of %s was not found, please check file %s !", 
			sKey, m_sLangIniFile );
//		CLog::GetHandle().Write( sMsg );
//		ShowMessage( sMsg );
	}
	return sValue;
//	return m_mapCharRes[sKey];
}
 
void CLang::ReadFontConfigFromLangIniFile( LOGFONT& oLogFont )
{
	oLogFont.lfHeight = GetPrivateProfileInt( "FONT", "Height", -13, m_sLangIniFile );
	oLogFont.lfWidth = GetPrivateProfileInt( "FONT", "Width", 0, m_sLangIniFile );
	oLogFont.lfEscapement = GetPrivateProfileInt( "FONT", "Escapement", 0, m_sLangIniFile );
	oLogFont.lfOrientation = GetPrivateProfileInt( "FONT", "Orientation", 0, m_sLangIniFile );
	oLogFont.lfWeight = GetPrivateProfileInt( "FONT", "Weight", 400, m_sLangIniFile );
	oLogFont.lfItalic = GetPrivateProfileInt( "FONT", "Italic", FALSE, m_sLangIniFile );
	oLogFont.lfUnderline = GetPrivateProfileInt( "FONT", "Underline", FALSE, m_sLangIniFile );
	oLogFont.lfStrikeOut = GetPrivateProfileInt( "FONT", "StrikeOut", 0, m_sLangIniFile );
	oLogFont.lfCharSet = GetPrivateProfileInt( "FONT", "CharSet", GB2312_CHARSET, m_sLangIniFile );
	oLogFont.lfOutPrecision = GetPrivateProfileInt( "FONT", "OutPrecision", OUT_DEFAULT_PRECIS, m_sLangIniFile );
	oLogFont.lfClipPrecision = GetPrivateProfileInt( "FONT", "ClipPrecision", CLIP_DEFAULT_PRECIS, m_sLangIniFile );
	oLogFont.lfQuality = GetPrivateProfileInt( "FONT", "Quality", DEFAULT_QUALITY, m_sLangIniFile );
	oLogFont.lfPitchAndFamily = GetPrivateProfileInt( "FONT", "PitchAndFamily", 2, m_sLangIniFile );
	GetPrivateProfileString( "FONT", "FaceName", "Times New Roman", oLogFont.lfFaceName, 64, m_sLangIniFile);
}

void CLang::CreateFont()
{
	LOGFONT oLogFont;
	ReadFontConfigFromLangIniFile( oLogFont );
/*
	oLogFont.lfHeight = -12;
	oLogFont.lfWidth = 0;
	oLogFont.lfEscapement = 0;
	oLogFont.lfOrientation = 0;
	oLogFont.lfWeight = 400;
	oLogFont.lfItalic = FALSE;
	oLogFont.lfUnderline = FALSE;
	oLogFont.lfStrikeOut = 0;
	oLogFont.lfCharSet = / *GB2312_CHARSET* /ANSI_CHARSET;
	oLogFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	oLogFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	oLogFont.lfQuality = DEFAULT_QUALITY;
	oLogFont.lfPitchAndFamily = DEFAULT_PITCH|FF_SWISS/ *18* // *0* /;
	memcpy(oLogFont.lfFaceName,/ *"Arial"* /"Times New Roman"/ *"宋体"* /,sizeof(oLogFont.lfFaceName));			
*/
/*
	oLogFont.lfHeight = -13; // -15
	oLogFont.lfWidth = 0;
	oLogFont.lfEscapement = 0;
	oLogFont.lfOrientation = 0;
	oLogFont.lfWeight = 400;
	oLogFont.lfItalic = FALSE;
	oLogFont.lfUnderline = FALSE;
	oLogFont.lfStrikeOut = 0;
	oLogFont.lfCharSet = 134;
	oLogFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	oLogFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	oLogFont.lfQuality = DEFAULT_QUALITY;
	oLogFont.lfPitchAndFamily = 2;
	memcpy(oLogFont.lfFaceName,"宋体",sizeof(oLogFont.lfFaceName));			
*/
	
	if (m_oFont.m_hObject)
	{
		VERIFY (m_oFont.DeleteObject ());
	}
	m_oFont.CreateFontIndirect( &oLogFont );
}

// void CLang::ChangeWndFont(CWnd* pWnd)
// {
// 	if ( !pWnd )
// 	{
// 		return;
// 	}
// 
// 	pWnd->SendMessageToDescendants( WM_SETFONT, (WPARAM)m_oFont.GetSafeHandle(), TRUE );
// 	
// 	// iterate through and change font of all child windows
// 	CWnd* pChildWnd = pWnd->GetWindow(GW_CHILD);	
// 	while (pChildWnd)
// 	{
// 		pChildWnd->SendMessageToDescendants( WM_SETFONT, (WPARAM)m_oFont.GetSafeHandle(), TRUE );
// 		pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT);
// 	}
// }
// 
// CFont* CLang::GetFont()
// {
// 	return &m_oFont;
// }
// 
// CMapStringToString* CLang::GetCharResPointer()
// {
// 	return &m_mapCharRes;
// }
// 
int CLang::ShowMessage( CString sMsg, UINT nType )
{
	return AfxMessageBox( sMsg, nType );
}
// 
// 
// // -----------------------------------------------------------------------------------------------------------
// // ********************************************************【故障诊断日志】文件存取公共类
// AFX_EXT_CLASS CLogFileAccess CLogFileAccess::s_oHandle;
// 
// CLogFileAccess::CLogFileAccess()
// {
// 	m_pFile = NULL;
// 	m_sNameOfLogFile = "";
// 	m_sNameOfLogTextFile = "";
// 
// 	char sAppPath[255];
// 	::GetCurrentDirectory( 255, sAppPath );
// 	m_sPathOfLogFile.Format( "%s\\Log", sAppPath );
// 	::CreateDirectory( m_sPathOfLogFile, NULL );
// 	
// 	m_pTime = new tm();
// 	memset( m_pTime, 0, sizeof(tm) );
// 	
// 	OpenLogFileName();
// }
// 
// CLogFileAccess::~CLogFileAccess()
// {
// 	delete m_pTime;
// 	
// 	if ( m_pFile )
// 	{
// 		fclose( m_pFile );
// 	}
// }
// 
// CLogFileAccess& CLogFileAccess::GetHandle()
// {
// 	return s_oHandle;
// }
// 
// bool CLogFileAccess::OpenLogFileName()
// {
// 	time_t nDateTime = mktime( CTime::GetCurrentTime().GetLocalTm() );	
// 	tm * pTm = localtime( &nDateTime );
// 	
// 	if ( m_pTime->tm_year != pTm->tm_year 
// 		|| m_pTime->tm_mon + 1 != pTm->tm_mon + 1 
// 		|| m_pTime->tm_mday != pTm->tm_mday )
// 	{
// 		memcpy( m_pTime, pTm, sizeof(tm) );
// 		m_sNameOfLogFile.Format( "%s\\XABW_MRI_%04d%02d%02d.log", 
// 			m_sPathOfLogFile, 
// 			pTm->tm_year + 1900, pTm->tm_mon + 1, pTm->tm_mday );
// 		m_sNameOfLogTextFile.Format( "%s\\XABW_MRI_%04d%02d%02d.txt", 
// 			m_sPathOfLogFile, 
// 			pTm->tm_year + 1900, pTm->tm_mon + 1, pTm->tm_mday );
// 		
// 		if ( m_pFile )
// 		{
// 			fclose( m_pFile );
// 		}
// 		
// 		m_pFile = fopen( m_sNameOfLogFile, "a+b" );
// 		if ( !m_pFile )
// 		{
// 			return false;
// 		}
// 	}
// 	
// 	if ( !m_pFile )
// 	{
// 		return false;
// 	}
// 	
// 	return true;
// }
// 
// time_t CLogFileAccess::GetCurrTime()
// {
// 	return mktime( CTime::GetCurrentTime().GetLocalTm() );
// }
// 
// void CLogFileAccess::SaveToFile( STRUCT_RECORD_DIAGNOSIS_TG_RG_O1 oTG_RG_O1 )
// {
// 	if ( !OpenLogFileName() || oTG_RG_O1.oBaseInfo.nDataType == TD_NONE )
// 	{
// 		return;
// 	}
// 
// 	oTG_RG_O1.oBaseInfo.nTime = GetCurrTime();
// 
// 	fwrite( &oTG_RG_O1.oBaseInfo.nDataType, sizeof(ENUM_TYPE_OF_DATA), 1, m_pFile );		// 用于读文件
// 	fwrite( &oTG_RG_O1, sizeof(STRUCT_RECORD_DIAGNOSIS_TG_RG_O1), 1, m_pFile );
// 	fflush( m_pFile );
// }
// 
// void CLogFileAccess::SaveToFile( STRUCT_RECORD_DIAGNOSIS_TUNING_MEAN oTuningMean )
// {
// 	if ( !OpenLogFileName() || oTuningMean.oBaseInfo.nDataType == TD_NONE )
// 	{
// 		return;
// 	}
// 	
// 	oTuningMean.oBaseInfo.nTime = GetCurrTime();
// 
// 	fwrite( &oTuningMean.oBaseInfo.nDataType, sizeof(ENUM_TYPE_OF_DATA), 1, m_pFile );		// 用于读文件
// 	fwrite( &oTuningMean, sizeof(STRUCT_RECORD_DIAGNOSIS_TUNING_MEAN), 1, m_pFile );
// 	fflush( m_pFile );
// }
// 
// void CLogFileAccess::SaveToFile( std::vector<STRUCT_RECORD_DIAGNOSIS_TG_RG_O1>* pvTG_RG_O1 )
// {
// 	for ( int i=0; i< (*pvTG_RG_O1).size(); i++ )
// 	{
// 		SaveToFile( (*pvTG_RG_O1)[i] );
// 	}
// }
// 
// void CLogFileAccess::SaveToFile( std::vector<STRUCT_RECORD_DIAGNOSIS_TUNING_MEAN>* pvTuningMean )
// {
// 	for ( int i=0; i< (*pvTuningMean).size(); i++ )
// 	{
// 		SaveToFile( (*pvTuningMean)[i] );
// 	}
// }
// 
// 
// // 输入：
// //		oSeriesTime -- Series的时间，用于查找LOG文件
// //		sStudyID  -- 若为""，则查询此LOG文件中所有Study；否则查询指定Study
// //		nSeriesID -- 若为-1，则查询sStudyID下的所有Series，否则查询sStudyID下的指定Series
// // 输出：
// //		pvTG_RG_O1, pvTuningMean
// 
// bool CLogFileAccess::ReadFromFile( BIDateTime oSeriesTime, CString sStudyID, int nSeriesID,
// 								  std::vector<STRUCT_RECORD_DIAGNOSIS_TG_RG_O1>* pvTG_RG_O1,
// 								  std::vector<STRUCT_RECORD_DIAGNOSIS_TUNING_MEAN>* pvTuningMean )
// {
// 	CString sNameOfLogFile;
// 	sNameOfLogFile.Format( "%s\\XABW_MRI_%04d%02d%02d.log", 
// 		m_sPathOfLogFile, oSeriesTime.year, oSeriesTime.month, oSeriesTime.day );
// 	FILE* pInFile = fopen( sNameOfLogFile, "r+b" );
// 	if ( !pInFile )
// 	{
// 		return false;
// 	}
// 	
// 	(*pvTG_RG_O1).clear();
// 	(*pvTuningMean).clear();
// 
// 	while ( !feof( pInFile ) )
// 	{
// 		ENUM_TYPE_OF_DATA nDataType;
// 		fread( &nDataType, sizeof(ENUM_TYPE_OF_DATA), 1, pInFile );
// 		
// 		STRUCT_RECORD_DIAGNOSIS_TG_RG_O1		oTG_RG_O1;
// 		STRUCT_RECORD_DIAGNOSIS_TUNING_MEAN		oTuningMean;
// 		
// 		switch ( nDataType )
// 		{
// 			case TD_TG:
// 			case TD_RG:
// 			case TD_O1:
// 				fread( &oTG_RG_O1, sizeof(STRUCT_RECORD_DIAGNOSIS_TG_RG_O1), 1, pInFile );
// 				if ( sStudyID == oTG_RG_O1.oBaseInfo.sStudyID 
// 					&& nSeriesID == oTG_RG_O1.oBaseInfo.nSeriesID )
// 				{
// 					(*pvTG_RG_O1).push_back( oTG_RG_O1 );
// 				}
// 				break;
// 				
// 			case TD_TUNING_MEAN:
// 				fread( &oTuningMean, sizeof(STRUCT_RECORD_DIAGNOSIS_TUNING_MEAN), 1, pInFile );
// 				if ( sStudyID == oTG_RG_O1.oBaseInfo.sStudyID 
// 					&& nSeriesID == oTG_RG_O1.oBaseInfo.nSeriesID )
// 				{
// 					(*pvTuningMean).push_back( oTuningMean );
// 				}
// 				break;
// 				
// 			default:
// 				break;
// 		}
// 	}
// 	
// 	fclose( pInFile );
// 
// 	if ( (*pvTG_RG_O1).size() == 0 && (*pvTuningMean).size() == 0 )
// 	{
// 		return false;
// 	}
// 
// 	return true;
// }
// 
// CString CLogFileAccess::MakeDateTimeStr( time_t nDateTime )
// {
// 	CString sDateTime;	
// 	tm * pTm = localtime( &nDateTime );
// 	sDateTime.Format( "%04d-%02d-%02d %02d:%02d:%02d", 
// 		pTm->tm_year + 1900, pTm->tm_mon + 1, pTm->tm_mday,
// 		pTm->tm_hour, pTm->tm_min, pTm->tm_sec );
// 	
// 	return sDateTime;
// }
// 
// 
// /***********************************************************************
// 函数名称: GetProcessMemory
// 描述: 获取一个进程的占用内存大小
// 输入: iProcessID－进程ID
// 输出: 占用内存大小 （kBytes）
// 返回: 
// 其它: 
// 修改历史:
//        <修改人> <时间>     <版本 >   <描述>
//     1. zhlxu    2007.11.2 v3.5.5.01 建立函数
//     2. 
// ***********************************************************************/
// #include "psapi.h "
// #pragma comment( lib, "Psapi.lib " ) 
//   
// unsigned long GetProcessMemory( DWORD iProcessID )
// { 
// 	HANDLE hProcess;
// 	PROCESS_MEMORY_COUNTERS PMC; 
// 	DWORD iTotalMemory, iMemory, iVirtualMemory; 
// 	
// 	hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | 
// 		PROCESS_VM_READ, 
// 		FALSE, iProcessID ); 
// 	if ( NULL == hProcess )
// 	{
// 		return 0;
// 	}
// 	
// 	GetProcessMemoryInfo( hProcess,&PMC, sizeof(PMC) ); 
//     CloseHandle( hProcess );
// 	
// 	iMemory = PMC.WorkingSetSize;
// 	iVirtualMemory = PMC.PagefileUsage;
// 	
// 	iTotalMemory = iMemory + iVirtualMemory
// 		+ PMC.PageFaultCount + PMC.QuotaPagedPoolUsage + PMC.QuotaNonPagedPoolUsage;
// 	
// 	return (iTotalMemory / 1024);
// } 
// 
// /***********************************************************************
// 函数名称: CheckMemory
// 描述: 检查内存占用大小是否在允许大小内
// 输入: 
// 输出: true－未超出限制；false－超出限制
// 返回: 
// 其它: 
// 修改历史:
//        <修改人> <时间>     <版本 >   <描述>
//     1. zhlxu    2007.11.2 v3.5.5.01 建立函数
//     2. 
// ***********************************************************************/
//    
// bool CheckMemory() 
// {   
// 	// 获取所有用户进程ID
// 	DWORD aProcesses[1024], cbNeeded, cProcesses;
// 	unsigned long iTotalMemorySize;
// 	unsigned int i; 
// 	
// 	if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) ) 
// 	{
// 		return 0;
// 	}
// 	
// 	// 计算用户进程个数
// 	cProcesses = cbNeeded / sizeof(DWORD);
// 	
// 	// 统计各个用户进程占用内存大小，并获得总的占用内存大小
// 	iTotalMemorySize = 0;
// 	for ( i = 0; i < cProcesses; i++ ) 
// 	{
// 		unsigned long iMemoryOfOneProcess = 0;
// 		iMemoryOfOneProcess = GetProcessMemory( aProcesses[i] );
// 		iTotalMemorySize += iMemoryOfOneProcess;
// 	}
// 
// 	// 从配置文件读取占用内存大小限定值
// 	CString sConfigFile = CConfigManager::GetHandle().m_strConfigIniFile.c_str();
// 	unsigned long iLimitedMemory = GetPrivateProfileInt("MEMORY_LIMITE", "PermittedSize", 
// 		                                                1500000, sConfigFile);
// 	
// 	// 判断占用内存大小是否在允许范围内
// 	// 默认为1.5G Bytes, iTotalMemorySize统计值比Monitor的值少约200M Bytes
// 	if ( iTotalMemorySize >= iLimitedMemory )
// 	{
// 		//Modified by Tom, --2008.07.10
// 		/*
// 		CString sMsg;
// 		sMsg.Format( "%s", 
// 			         CLang::GetHandle().GetCharRes("MSG___PROSPECT_NOT_ENOUGH_MEMORY") );
// 		CLang::GetHandle().ShowMessage( sMsg );
// 		*/
// 		return false;
// 	}
// 	
// 	return true;
// }   
