// SystemStatus.h : Used to store some system status information.
//
#if !defined(AFX_SYSTEMSTATUS_H__DF970EAD_201F_4FF9_8630_1F1F329E2AC2__INCLUDED_)
#define AFX_SYSTEMSTATUS_H__DF970EAD_201F_4FF9_8630_1F1F329E2AC2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*! 
    This class is implemented as a Singleton, which provides a convenient way
    of global aCess and ensures there can be only one instance of the manager
    in the application in the mean time. 
*/
class CStudy;
class CSeries;
class CScan;

#ifdef BIGLOBALS_IMP
   #define CLASS_DECL_BIGLOBALS  __declspec(dllexport)
#else
   #define CLASS_DECL_BIGLOBALS  __declspec(dllimport)
#endif

//! Enumeration type used to specify the level of a user.
enum EUserLevel
{
    ulLogoff,
    ulOperator,
    ulAdvancedUser,
    ulAdministrator,
    ulBITechnician,
    ulBIInternal,
};

class CLASS_DECL_BIGLOBALS CSystemStatus
{
protected:
	static CSystemStatus s_SystemStatus;
	CSystemStatus();
public:
	static CSystemStatus& GetHandle();
	virtual ~CSystemStatus();

    //! Pointer to the scanning study.
    /*!
        The scanning study is the study patient of which is lying on the table.
        That doesn't inplying that the scanning is in progress.
    */
    CStudy* m_pScanningStudy;
    
    //! The scan that is being scanned.
    /*!
        \remarks The scanning study refers the study patient of which is lying
        on the table for examination. However, the meaning of scanning here
        is a little different, the pointer to scanning scan is non-NULL only 
        when a scan is in progress. When a scan is finished, the next scan in 
        series will automatically be put into scanning. You can find the 
        scanning series using m_pScanningScan->GetSeries(). Don't try to 
        use m_pScanningStudy->GetCurrentSeries() to retrieve the scanning
        series, cause that function gives the displayed series instead of the
        scanning one.
    */
    CScan*  m_pScanningScan;
    
    //! Whether the scanning is in progress.
    bool m_bScanning;
	//! Whethe the filming dialog is displayed.
	bool m_bFilming;
    
    //! Pointer to the study that is being displayed in the mri view.
    CStudy* m_pDisplayedStudy;  
    EUserLevel m_UserLevel; //! User level of the logged-on user.
    CString m_strUserID;    //! User id of the current user.

    //! Whether the software is using a virtual spectrometer.
    bool m_bEmmulating;
    //! Whether to review the parameter before each scan.
    bool m_bReviewParameters;
	BOOL m_bSeriesCompare;
	/*********zyh add 2007.11.28*********/
	BOOL m_bActiveShimming;
	/**********************************************/
	/** [SHCH-15-12-2007  BUG-TITLE:XABW/CX-31-11-0089] 增加打印控制项**/
	BOOL m_bPrintProcessing;
	/** [SHCH-15-12-2007  BUG-TITLE:XABW/CX-31-11-0089] **/

	//Added by Tom, --2008.07.10
	BOOL m_bConnectNavi ;
		
};

#endif // !defined(AFX_SYSTEMSTATUS_H__DF970EAD_201F_4FF9_8630_1F1F329E2AC2__INCLUDED_)
